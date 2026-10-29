// #define SIZE (1024*512)
// #define SIZE (1024*1024*2)
#define SIZE (1024*64)


void linear_work(int* work, int size) {
  for (int i = 0; i < size; i++) {
    int new_i = (i / 64) + 1;
    work[i] = new_i;
    // More work every 64 locations
  }
}
