#pragma once

#include <atomic>
#include <thread>
using namespace std;

namespace my {

// A spinlock, as in RMW_mutexes/cas_relaxed and cas_backoff.
// Unlike std::mutex, a waiting thread never blocks in the kernel.
// It peeks at the lock word with a plain load until it looks free,
// then tries to take it with a CAS.
// Uncomment the yield to give up the time slice while the lock is held.
class mutex {
 public:
  mutex() {
    flag = false;
  }

  void lock() {
    bool e = false;
    bool acquired = false;
    while (!acquired) {
      while (flag.load(memory_order_relaxed) == true) {
        this_thread::yield();
      }
      e = false;
      acquired = atomic_compare_exchange_strong(&flag, &e, true);
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
