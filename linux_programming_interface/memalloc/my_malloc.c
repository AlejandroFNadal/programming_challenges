#include <stddef.h> // for size_t
#include <inttypes.h>
#include <malloc.h>
#include <stdint.h> // used for uint32_t
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
/*
 * Author: Alejandro Nadal
 * Making my own memory allocator for C.
 *
 * Requirements:
 * - On allocation, it should search for the smallest available block of free
 * space in the stack. If the space exists, it should remove that space from the
 * free space blocks and return a pointer to it.
 * - On allocation, if the space is not available, then it should first increase
 * the end of the stack and then return the new space.
 * - On free, if the area freed is at the end of the reserved area and the end
 * of the stack can be moved, it should move the end of the stack to use less
 * memory.
 *
 */

void debug_log(const char *msg){
  write(STDOUT_FILENO, msg, strlen(msg));
}
extern long int etext, edata, end;
struct free_area {
  uint8_t marker;
  void *start;
  bool in_use;
  uint32_t length;
  struct free_area *next;
};

struct stats {
  int magical_bytes;
  bool my_simple_lock;
  int amount_of_blocks;
};
typedef struct stats my_stats;
typedef struct free_area area;

const int MAGICAL_BYTES = 0x55AA;
const int BLOCK_MARKET = 0xDD;
const int FIRST_BLOCK_OFFSET = sizeof(area);

// Assumes that the magical bytes are at the beginning
void add_used_block(size_t size){
  long int *heap_start = &end;
  assert(*heap_start == MAGICAL_BYTES);
  my_stats *malloc_header = (my_stats*) (heap_start);
  while(malloc_header->my_simple_lock){};
  // find smallest space in the free blocks and add there.
  area *first_block = (area*)(heap_start + FIRST_BLOCK_OFFSET);
  assert(first_block->marker == BLOCK_MARKET);
  // increase used block counter
}
void *an_malloc(size_t size) {
  // First, we check if the magical bytes are at the beggining of the heap
  long int *heap_start = &end;
  //printf("Heap start is %p\n", heap_start);
  long int *heap_end = sbrk(0);
  //printf("Heap end is %p\n", heap_end);
  long int length = heap_end - heap_start;
  //printf("Heap size in KB is %ld\n", length/1024);
  if ((*heap_start) == MAGICAL_BYTES){
    add_used_block(size);
  } else {
    *(heap_start) = MAGICAL_BYTES; 
    area *first_block = (area*) heap_start + sizeof(my_stats);
    first_block->start = (heap_start + 2);
    first_block->in_use = true;
    first_block->length = size;
    first_block->next = NULL;
  }
  return 0;
}

int main() {
  //printf("Etext: %p\n", &etext);
  //printf("Edata: %p\n", &edata);
  //printf("End: %p\n", &end);
  an_malloc(1);
  an_malloc(1);
  debug_log("test");
}
