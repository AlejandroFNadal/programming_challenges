#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  void *heap_start = sbrk(0);
  printf("Heap start %p\n", heap_start);
  char *heap_end = heap_start + 2;
  *heap_end = 'T';
  // 100K later
  *(heap_end + 100000) = 'T';
  printf("Got to 100K\n");
  // 1M later
  *(heap_end + 1000000) = 'T';
  printf("Got to 1M\n");
}
