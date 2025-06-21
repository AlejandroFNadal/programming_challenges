/*
 * Alejandro Nadal 2025.
 *
 * My implementation of RealPath
 *
 * Note: It was tempting just to chdir into the path and then use getcwd. Buuut,
 *then the program would work only if the user had the right to use the program
 *
 * Strat: Create a stack (just an array here, because the size is limited).
 *Then, traverse the stack, to resolve the double slashes, dots, and double
 *dots.
 **/
#include <assert.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// note: my stack pointer points to my next write position
void pop_stack(char *stack[], short unsigned int *stack_pointer) {
  stack[*stack_pointer] = NULL;
  if (*stack_pointer > 0) {
    (*stack_pointer)--;
  }
}

void dotdot_operation(char *stack[], short unsigned int *stack_pointer) {
  pop_stack(stack, stack_pointer);
  pop_stack(stack, stack_pointer);
}

void print_stack(char *stack[]) {
  short unsigned int stack_pointer = 0;
  if (stack[0] == NULL) {
    printf("/");
  }
  while (stack[stack_pointer] != NULL) {
    printf("/%s", stack[stack_pointer]);
    stack_pointer += 1;
  }
  printf("\n");
}

char *stack_to_string_until_a_pos(char *stack[], short unsigned int pos) {
  char *temp = malloc(PATH_MAX);
  short unsigned int stack_pointer = 0;
  if (stack[0] == NULL) {
    temp[0] = '/';
  }
  while (stack[stack_pointer] != NULL && stack_pointer < pos) {
    strcat(temp, "/");
    strcat(temp, stack[stack_pointer]);
  }
  return temp;
}

int main(int argc, char **argv) {
  // first is name, second is the path
  if (argc < 2) {
    printf("Pass a path\n");
    return 1;
  }
  if (strlen(argv[1]) > PATH_MAX) {
    printf("Too Long");
    return 1;
  }
  // technically, the max path could be 4096 slashes
  char *stack[PATH_MAX];
  short unsigned int stack_index = 0;
  // to load the path in the stack
  const char delimiter = '/';
  char *input_string = malloc(PATH_MAX);
  if (argv[1][0] != '/') {
    // relative path -- null terminated string
    getcwd(input_string, PATH_MAX);
    strcat(input_string, "/");
  }
  // first part, without the delimiter
  strcat(input_string, argv[1]);
  char *save_ptr = NULL;
  while ((stack[stack_index] = strtok_r(input_string, &delimiter, &save_ptr)) !=
         NULL) {
    if (stack[stack_index][0] == '.' && stack[stack_index][1] == '.') {
      printf("dotdot\n");
      // dotdot_operation(stack, &stack_index);
      pop_stack(stack, &stack_index);
      pop_stack(stack, &stack_index);
    } else if (stack[stack_index][0] == '.') {
      pop_stack(stack, &stack_index);
    }
    stack_index += 1;
    // after first call, it has to be NULL (C is just horrible sometimes)
    input_string = NULL;
    char *path_minus_one = stack_to_string_until_a_pos(stack, stack_index - 1);
    struct stat statbuf;
    printf("path_minus_one %s\n", path_minus_one);
    if (stat(path_minus_one, &statbuf) == -1) {
      printf("Path does not exist");
      return -1;
    }
  }
  print_stack(stack);
  return 0;
}
