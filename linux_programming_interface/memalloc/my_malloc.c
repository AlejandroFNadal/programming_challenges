#include <assert.h>
// #include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h> // used for uint32_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

void debug_log(const char *msg) { write(STDOUT_FILENO, msg, strlen(msg)); }
extern long int etext, edata, end;
struct free_area {
  uint8_t marker;
  struct free_area *prev;
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
const int BLOCK_MARKER = 0xDD;
const int FIRST_BLOCK_OFFSET = sizeof(area);

// Assumes that the magical bytes are at the beginning
int *add_used_block(ssize_t size) {
  long int *heap_start = &end;
  // format the heap_start with the shape of stats
  my_stats *malloc_header = (my_stats *)(heap_start);
  assert(malloc_header->magical_bytes == MAGICAL_BYTES);
  while (malloc_header->my_simple_lock) {
    sleep(1);
  };
  malloc_header->my_simple_lock = true;
  // find smallest space in the free blocks and add there.
  area *block = (area *)((char *)heap_start + sizeof(my_stats));
  area *smallest_block = NULL;
  area *last_block = block;
  while (block != NULL) {
    assert(block->marker == BLOCK_MARKER);
    if ((block->length + sizeof(area)) >= size && block->in_use == false) {
      if (smallest_block == NULL || smallest_block->length > block->length) {
        smallest_block = block;
      }
    }
    last_block = block;
    block = block->next;
  }
  // no big enough blocks.
  if (smallest_block == NULL) {
    sbrk(4096);
    smallest_block =
        (area *)((char *)last_block + sizeof(area) + last_block->length);
    last_block->next = smallest_block;
    smallest_block->prev = last_block;
    smallest_block->next = NULL;
    smallest_block->length = 4096 - sizeof(area);
  }
  // found a block
  if (smallest_block != NULL) {
    smallest_block->in_use = true;
    // create a new block, which will be free
    // only create if the size is big enough
    int remaining_size = smallest_block->length - size - sizeof(area);
    if (remaining_size > 0) {
      area *new_block = (area *)((char *)smallest_block + sizeof(area) +
                                 smallest_block->length);
      new_block->marker = BLOCK_MARKER;
      new_block->prev = smallest_block;
      new_block->next = smallest_block->next;
      if (new_block->next != NULL) {
        (new_block->next)->prev = new_block;
      }
      smallest_block->next = new_block;
      new_block->length = smallest_block->length - size;
    }
    smallest_block->length = size;
  }
  malloc_header->my_simple_lock = false;
  return (int *)smallest_block + sizeof(area);
}
void *an_malloc(ssize_t size) {
  // First, we check if the magical bytes are at the beggining of the heap
  long int *heap_start = &end;
  // printf("Heap start is %p\n", heap_start);
  long int *heap_end = sbrk(0);
  // printf("Heap end is %p\n", heap_end);
  long int length = heap_end - heap_start;
  // printf("Heap size in KB is %ld\n", length/1024);
  if ((*heap_start) != MAGICAL_BYTES) {
    *(heap_start) = MAGICAL_BYTES;
    area *first_block = (area *)((char *)heap_start + sizeof(my_stats));
    first_block->marker = BLOCK_MARKER;
    first_block->in_use = false;
    first_block->length = length;
    first_block->next = NULL;
    first_block->prev = NULL;
  }
  return add_used_block(size);
}
int main() {
  // printf("Etext: %p\n", &etext);
  // printf("Edata: %p\n", &edata);
  // printf("End: %p\n", &end);
  an_malloc(1);
  an_malloc(1);
  debug_log("test");
}
