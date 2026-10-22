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
    int acquired = false;
    while (acquired == false) {
      acquired = atomic_compare_exchange_strong(&flag, &e, true);      
      e = false;
//       if (acquired == false)
//          this_thread::yield();
    }
  }

  bool try_lock() {
    bool e = false;
    return atomic_compare_exchange_strong(&flag, &e, true);
  }
  
  void unlock() {
    flag.store(false);
  }

 private:
  atomic_bool flag;
};

}
