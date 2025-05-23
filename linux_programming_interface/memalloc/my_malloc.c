#include <assert.h>
// #include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h> // used for uint32_t
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
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
// extern long int etext, edata, end;
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
  uint32_t amount_of_blocks;
  uint16_t amount_of_pages;
};

typedef struct stats my_stats;
typedef struct free_area area;

const int MAGICAL_BYTES = 0x55;
const int BLOCK_MARKER = 0xDD;
const int FIRST_BLOCK_OFFSET = sizeof(area);
const int PAGE_SIZE = 4096;

char *heap_start = NULL;

area *find_last_block();

my_stats *get_malloc_header() {
  assert(heap_start != NULL);
  my_stats *malloc_header = (my_stats *)heap_start;
  assert(malloc_header->magical_bytes == MAGICAL_BYTES);
  return malloc_header;
}

area *find_previous_used_block(area *ptr) {
  area *mov_ptr = ptr;
  while (mov_ptr->prev != NULL) {
    mov_ptr = mov_ptr->prev;
    if (mov_ptr->in_use == true) {
      return mov_ptr;
    }
  }
  return NULL;
}

area *find_first_block() {
  my_stats *malloc_header = get_malloc_header();
  return (area *)((char *)malloc_header + sizeof(my_stats));
}

void reduce_heap_size_if_possible() {
  area *last_block = find_last_block();
  area *prev_used_block = find_previous_used_block(last_block);
  if (prev_used_block == NULL) {
    // It is the only block, which should never be deleted. We
    // could only reduce its size to 1 Page
    if (last_block->length > PAGE_SIZE) {
      last_block->length = PAGE_SIZE;
    }
    prev_used_block = last_block;
  }
  void *new_end =
      (void *)prev_used_block + sizeof(area) + prev_used_block->length;
  void *heap_end = sbrk(0);
  while (new_end < heap_end - PAGE_SIZE) {
    sbrk(-PAGE_SIZE);
    heap_end = sbrk(0);
    my_stats *malloc_header = get_malloc_header();
    malloc_header->amount_of_pages -= 1;
  }
  // Now, in most cases, there is a gap between the last used block and the end
  // of the heap. If there is enough space, we can inyect there an empty block.
  // At least, we write 1 element in the block
  if (heap_end - new_end > sizeof(area) + 1) {
    area *new_not_used_block = (area *)new_end;
    new_not_used_block->marker = BLOCK_MARKER;
    new_not_used_block->in_use = false;
    new_not_used_block->prev = prev_used_block;
    new_not_used_block->next = NULL;
    new_not_used_block->length = heap_end - new_end - sizeof(area);
    prev_used_block->next = new_not_used_block;
  }
}

bool an_free(void *ptr) {
  my_stats *malloc_header = get_malloc_header();
  while (malloc_header->my_simple_lock) {
    sleep(1);
  };
  malloc_header->my_simple_lock = true;
  // free does not get the start of the block but the start of the data area of
  // the block.
  area *block = ptr - sizeof(area);
  if (block->marker != BLOCK_MARKER) {
    // the given pointer is not the start of any malloc block
    return false;
  } else {
    block->in_use = false;
    memset(ptr, 0, block->length);
    if (block->next != NULL && (block->next)->in_use == false) {
      // Next block is not used, we can merge them
      area *not_used_next_block = block->next;
      // skip next block in linked list.
      if (not_used_next_block != NULL) {
        // connect current block and two blocks ahead
        block->next = not_used_next_block->next;
        // if two blocks ahead, the block is not null, we connect it back.
        if (not_used_next_block->next != NULL) {
          not_used_next_block->next->prev = block;
        }
      } else {
        block->next = NULL; // not necessary, compiler will optimize away, only
                            // for clarity
      }
      // current block adds the next block
      block->length += sizeof(area) + not_used_next_block->length;
      // erase header and data
      // TODO: here we have to take into account the bloody header of the malloc
      // structure
      memset((void *)not_used_next_block, 0,
             sizeof(area) + not_used_next_block->length);
      malloc_header->amount_of_blocks -= 1;
      // 10);
    }
    if (block->prev != NULL && (block->prev)->in_use == false) {
      // previous block can be merged with current, so we delete current.
      area *to_delete_block = block;
      block = block->prev;
      // previous block gets new extra size
      block->length += sizeof(area) + to_delete_block->length;
      // skip next block. to_delete_block cannot be null, because we check that
      // above
      block->next = to_delete_block->next;
      // backward connection
      if (block->next != NULL) {
        block->next->prev = block;
      }
      malloc_header->amount_of_blocks -= 1;
    }
    reduce_heap_size_if_possible();
  }
  malloc_header->my_simple_lock = false;
  return true;
}

area *find_last_block() {
  my_stats *malloc_header = get_malloc_header();
  area *block = (area *)((char *)malloc_header + sizeof(my_stats));
  while (block->next != NULL) {
    block = block->next;
  }
  return block;
}

int *add_used_block(ssize_t size) {
  // long int *heap_start = &end;
  // format the heap_start with the shape of stats
  my_stats *malloc_header = get_malloc_header();
  while (malloc_header->my_simple_lock) {
    sleep(1);
  };
  malloc_header->my_simple_lock = true;
  // find smallest space in the free blocks and add there.
  area *block = (area *)((char *)heap_start + sizeof(my_stats));
  area *smallest_block = NULL;
  area *last_block = block;
  // best fit
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
    area *last_block = find_last_block();
    while (last_block->length < size) {
      sbrk(4096);
      last_block->length += 4096;
      malloc_header->amount_of_pages += 1;
    }
    smallest_block = last_block;
  }
  // found a block
  smallest_block->in_use = true;
  // create a new block, which will be free. The list always must end on a free
  // block. The size of area header is part of the check because it will need
  // space too for the new block. Also, at least one byte is needed for the new
  // block's content
  int must_have_size = smallest_block->length - size - sizeof(area) - 1;
  if (must_have_size <= 0) {
    sbrk(4096);
    malloc_header->amount_of_pages += 1;
    last_block->length += 4096;
    must_have_size = smallest_block->length - size - sizeof(area) - 1;
  }
  int remaining_size = must_have_size + 1;
  malloc_header->amount_of_blocks += 1;
  area *new_block = (area *)((char *)smallest_block + sizeof(area) + size);
  new_block->marker = BLOCK_MARKER;
  new_block->prev = smallest_block;
  new_block->next = smallest_block->next;
  if (new_block->next != NULL) {
    (new_block->next)->prev = new_block;
  }
  smallest_block->next = new_block;
  new_block->length = remaining_size;
  smallest_block->length = size;
  malloc_header->my_simple_lock = false;
  return (int *)((char *)smallest_block + sizeof(area));
}

int *an_malloc(ssize_t size) {
  if (heap_start == NULL) {
    heap_start = sbrk(0);
    sbrk(4096);
  }
  char *heap_end = sbrk(0);
  long int length = heap_end - heap_start;
  // First, we check if the magical bytes are at the beggining of the heap
  if ((*heap_start) != MAGICAL_BYTES) {
    *(heap_start) = MAGICAL_BYTES;
    my_stats *malloc_header = (my_stats *)heap_start;
    malloc_header->amount_of_blocks = 1;
    malloc_header->amount_of_pages = 1;
    area *first_block = (area *)((char *)heap_start + sizeof(my_stats));
    first_block->marker = BLOCK_MARKER;
    first_block->in_use = false;
    first_block->length = length - sizeof(my_stats) - sizeof(area);
    first_block->next = NULL;
    first_block->prev = NULL;
  }
  return add_used_block(size);
}

void test_basic_malloc() {
  char *ptr = (char *)an_malloc(1);
  area *first_block = (void *)ptr - sizeof(area);
  assert(first_block->marker == BLOCK_MARKER);
  *ptr = 'C';
  assert(*ptr == 'C');
}

void test_bigger_than_available_malloc() {
  uint16_t *ptr = (uint16_t *)an_malloc(5000);
  area *first_block = (void *)ptr - sizeof(area);
  for (uint16_t i = 0; i <= 2499; i = i + 1) {
    *(ptr + i) = i;
  }
  assert(first_block->marker == BLOCK_MARKER);
  assert(*ptr == 0);
  assert(*(ptr + 2) == 2);
  assert(*(ptr + 2499) == 2499);
  // little endian valid only
  assert(*((uint8_t *)ptr + 4999) == (2499 >> 8));
  assert(*((uint8_t *)ptr + 4998) == (2499 & 0xFF));
}

void test_free() {
  uint8_t *first = (uint8_t *)an_malloc(2048);
  area *first_block = (void *)first - sizeof(area);
  assert(first_block->next != NULL);
  assert(first_block->length == 2048);
  area *second_block = first_block->next;
  assert(second_block->marker == BLOCK_MARKER);
  assert(second_block->in_use == false);
  assert(second_block->next == NULL);
  assert(second_block->length == PAGE_SIZE - sizeof(my_stats) -
                                     (2 * sizeof(area)) - first_block->length);
  an_free(first);
  assert(first_block->marker == BLOCK_MARKER);
  assert(first_block->next == NULL);
  assert(first_block->length == PAGE_SIZE - sizeof(my_stats) - sizeof(area));
}

void complex_set_of_malloc_and_free_calls() {
  uint8_t *first =
      (uint8_t *)an_malloc(2048); // will leave another 2048 on the first page
  area *first_block = find_first_block();
  assert(first_block->length == 2048);
  area *second_block = first_block->next;
  assert(second_block->length ==
         PAGE_SIZE - sizeof(my_stats) - 2 * sizeof(area) - first_block->length);
  assert(second_block->next == NULL);
  assert(second_block->prev == first_block);
  uint8_t *second =
      (uint8_t *)an_malloc(10000); // will need around two more pages
  assert(second_block->length == 10000);
  assert(second_block->next != NULL);
  area *third_block = second_block->next;
  assert(third_block->length == 3 * PAGE_SIZE - sizeof(my_stats) -
                                    3 * sizeof(area) - first_block->length -
                                    second_block->length);
  my_stats *malloc_header = get_malloc_header();
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 3);
  an_free(second);
  assert(malloc_header->amount_of_pages == 1);
  assert(malloc_header->amount_of_blocks == 2);
  int heap_size = sbrk(0) - (void *)heap_start;
  assert(heap_size == PAGE_SIZE);
  // The second block is whatever is left from the first page
  assert(second_block->in_use == false);
  assert(first_block->length == 2048);
  assert(second_block->length ==
         PAGE_SIZE - sizeof(my_stats) - 2 * sizeof(area) - first_block->length);
  assert(second_block->next == NULL);
  // test block unification, add three blocks, free the left, free the right,
  // and then free the middle
  uint8_t *third = (uint8_t *)an_malloc(1000);
  assert(malloc_header->amount_of_pages == 1);
  assert(malloc_header->amount_of_blocks == 3);
  // A third, empty block has been created
  area *third_block_new = second_block->next;
  assert(third_block_new->marker == BLOCK_MARKER);
  assert(third_block_new->in_use == false);
  // The second block, which before was longer, now is used for the call. The
  // third block is the one that is empty
  assert(second_block->length == 1000);
  assert(third_block_new->length == PAGE_SIZE - sizeof(my_stats) -
                                        3 * sizeof(area) - first_block->length -
                                        second_block->length);
  assert(third_block_new->next == NULL);
  uint8_t *fourth = (uint8_t *)an_malloc(5000);
  // third block has been used for the fourth malloc call
  assert(third_block_new->length == 5000);
  assert(third_block_new->next != NULL);
  assert(third_block_new->in_use == true);
  assert(third_block_new->prev == second_block);
  assert(malloc_header->amount_of_pages ==
         3); // the 5000 needed a second page, and then another page was needed
             // to create a third block
  assert(malloc_header->amount_of_blocks == 4);
  uint8_t *fifth = (uint8_t *)an_malloc(1000);
  // a new block has been created
  area *fourth_block = third_block_new->next;
  assert(fourth_block->marker == BLOCK_MARKER);
  assert(third_block_new->length == 5000);
  assert(fourth_block->length == 1000);
  assert(fourth_block->in_use == true);
  assert(fourth_block->next != NULL);
  area *fifth_block = fourth_block->next;
  assert(fifth_block->marker == BLOCK_MARKER);
  assert(fifth_block->in_use == false);
  assert(fifth_block->next == NULL);
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 5); // fifth malloc made a new block
  uint8_t *sixth = (uint8_t *)an_malloc(
      1000); // just as buffer between the end and the fifth block
  assert(fifth_block->in_use == true);
  assert(fifth_block->length == 1000);
  assert(fifth_block->next != NULL);
  assert(fifth_block->prev == fourth_block);
  area *sixth_block = fifth_block->next;
  assert(sixth_block->marker == BLOCK_MARKER);
  assert(sixth_block->in_use == false);
  assert(sixth_block->next == NULL);
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 6);
  an_free(third);
  assert(second_block->in_use == false);
  assert(second_block->length == 1000); // should be unchanged
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 6); // because we have a free block
  an_free(fifth);
  assert(fourth_block->in_use == false);
  assert(malloc_header->amount_of_pages == 3);
  assert(malloc_header->amount_of_blocks == 6);
  an_free(fourth);
  assert(third_block_new->in_use == false);
  assert(malloc_header->amount_of_pages == 3);  // that is normal, as block six is still there
  assert(malloc_header->amount_of_blocks == 4); // three blocks have become one
}

void call_test(void (*test_func)(), const char *msg) {
  pid_t pid = fork();
  if (pid == 0) {
    test_func();
    exit(0);
  } else {
    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status)) {
      printf("%s crashed with signal %d\n", msg, WTERMSIG(status));
    } else {
      printf("%s passed\n", msg);
    }
  }
}

int main() {
  call_test(test_basic_malloc, "Basic Malloc");
  call_test(test_bigger_than_available_malloc, "Request more memory Malloc");
  call_test(test_free, "Basic Free");
  call_test(complex_set_of_malloc_and_free_calls, "Complex");
  debug_log("DONE");
}
