#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void memchk() {
  FILE *maps = fopen("/proc/self/maps", "r");
  if (!maps) {
    perror("Could not open /proc/self/maps");
    return 1;
  }

  char line[256];
  unsigned long heap_start = 0, heap_end = 0;

  while (fgets(line, sizeof(line), maps)) {
    if (strstr(line, "[heap]")) {
      sscanf(line, "%lx-%lx", &heap_start, &heap_end);
      break;
    }
  }

  fclose(maps);

  if (heap_start && heap_end) {
    printf("Heap start: 0x%lx\n", heap_start);
    printf("Heap end: 0x%lx\n", heap_end);
    printf("Heap size: %lu bytes\n", heap_end - heap_start);
  } else {
    printf("Heap information not found.\n");
  }
}

int main() {
  memchk();
  int page_size = getpagesize();
  printf("Page size is %d\n", page_size);
  malloc_info(0, stdout);
  void *heap_start = sbrk(0);
  printf("Heap start %p\n", heap_start);
  // resize the heap to 0 fails, it needs to be 1
  brk(heap_start + 1);
  memchk();
  malloc_info(0, stdout);
  void *new_heap_start = sbrk(0);
  printf("Heap start 2 %p\n", new_heap_start);
  // the rest should fail
  char *heap_end = heap_start;
  *(heap_end + 2) = 'T';
  printf("Got to 2\n");
  *(heap_end + 512) = 'T';
  printf("Got to 512\n");
  *(heap_end + 1024) = 'T';
  printf("Got to 1024\n");
  *(heap_end + 2048) = 'T';
  printf("Got to 2048\n");
  *(heap_end + 4095) = 'T';
  printf("Got to 4095\n");
  *(heap_end + 4096) = 'T'; // It fails here.
  printf("Got to 4096\n");
  // 100K later
  *(heap_end + 100000) = 'T';
  printf("Got to 100K\n");
  // 1M later
  *(heap_end + 1000000) = 'T';
  printf("Got to 1M\n");
}
