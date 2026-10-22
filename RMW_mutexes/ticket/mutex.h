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
    now_serving = 0;
    counter = 0;
  }
    
  void lock(int thread_id) {
    int my_num = atomic_fetch_add(&counter, 1);
    while (my_num != now_serving.load())
       this_thread::yield();
  }
  
  void unlock(int thread_id) {
    int tmp = now_serving.load();
    tmp += 1;
    now_serving.store(tmp);
  }

 private:
  atomic_int counter;
  atomic_int now_serving;
};

}
