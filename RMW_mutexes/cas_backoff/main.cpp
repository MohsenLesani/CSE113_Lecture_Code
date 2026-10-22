#include <iostream>
#include <thread>
#include <chrono>
#include "mutex.h"
using namespace std;
using namespace chrono;

#define SECONDS 1
#define WORK 1000

int total_number = 0;
int *histogram;
my::mutex m;
// mutex m;


void test_mutex(int thread_id) {
  auto start = high_resolution_clock::now();
  int duration = 0.0;
  while (duration < SECONDS) {
    
    // Perform the lock and unlock
    m.lock();
    total_number++;
    histogram[thread_id]++;
    // Critical section work, see WORK above. volatile keeps the compiler
    // from folding the loop away at -O2.
    volatile unsigned x = thread_id;
    for (int i = 0; i < WORK; i++) {
      x = x * 1664525u + 1013904223u;
    }
    m.unlock();
    
    // Update the timer
    auto now = high_resolution_clock::now();
    duration = duration_cast<seconds>(now - start).count();      
  }
}

int main(int argc, char *argv[]) {

  // int num_threads = 8;
  int num_threads = 12; // Not to hit the efficiency cores with special scheduling.  
  // int num_threads = 16;
  // int num_threads = 64;
  
  if (argc == 2) {
    num_threads = atoi(argv[1]);   
  }

  thread *thread_array = new thread[num_threads];

  histogram = new int[num_threads];
  for (int i = 0; i < num_threads; i++) {
    histogram[i] = 0;
  }

  for (int i = 0; i < num_threads; i++) {
    thread_array[i] = thread(test_mutex, i);
  }

  for (int i = 0; i < num_threads; i++) {
    thread_array[i].join();
  }

  cout << "total number: " << total_number << endl;

  for (int i = 0; i < num_threads; i++) {
    cout << i << ":histogram: " << histogram[i] << endl;
  }


  delete[] thread_array;
  delete[] histogram;
}
