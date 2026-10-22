// Why the optimization level matters for this lock
//
// Build with -O2. At -O0 the plain CAS lock (cas_plain) beats this one; at
// -O2 this one wins. The two locks have opposite sensitivities to how fast
// the waiting loop runs.
//
// Plain CAS gets worse with a faster loop. Its waiters hurt the holder:
// every failed CAS pulls the lock's cache line away from the holder, who
// must pull it back to finish the critical section. At -O0 each attempt
// goes through a function call, so a waiter issues a CAS only every hundred
// nanoseconds or so and the holder is barely disturbed. At -O2 the loop is
// three instructions, the CAS rate doubles.
//
// Peeking gets better with a faster loop. Its waiters do not hurt the
// holder, since they read a local copy. Their cost is reaction time: after
// the release they need a load miss to see the flag flip, then a CAS. At
// -O0 that reaction includes the slow loop iteration and a function call,
// so the lock sits idle longer between handoffs than it does with plain
// CAS. At -O2 the reaction is a few nanoseconds.
//
// At -O2 the storm for the plain version is real, the reaction for relaxed 
// version is fast, and peeking wins.

#pragma once

#include <atomic>
using namespace std;


namespace my {

// alignas(128) makes every mutex object start on a 128-byte boundary and
// pads its size up to a multiple of 128, so the lock's state gets a cache
// line of its own (lines are 128 bytes on Apple Silicon, 64 on x86).
// Without it the lock shares a line with the neighboring globals in
// main.cpp, total_number and histogram, and every increment inside the
// critical section invalidates the copy that each spinning thread is
// reading. This is false sharing: the spinners all refetch the line at
// once, in the middle of the critical section, and the holder pays for it.
class alignas(128) mutex {
 public:
  mutex() {
    flag = 0;
  }
    
  void lock() {
    bool e = false;
    bool acquired = false;
    while (!acquired) {
      while (flag.load(memory_order_relaxed) == true);
      e = false;
      acquired = atomic_compare_exchange_strong(&flag, &e, true);
    }
  }
  
  void unlock() {
    flag.store(false);
  }

 private:
  atomic_bool flag;
};

}
