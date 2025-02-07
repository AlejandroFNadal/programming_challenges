#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf env;

int calculate_math(int a, int b) {
  printf("a %d, b:%d\n", a, b);
  switch (setjmp(env)) {
  case 0:
    printf("no jump\n");
    break;
  case 1:
    printf("jump\n");
    break;
  }
  return a + b;
}

int calculate_more_math(int c, int d) {
  printf("c %d, d:%d ", c, d);
  return c + d;
}
int main() {
  calculate_math(1, 2);
  longjmp(env, 1);
  calculate_more_math(3, 4);
}
