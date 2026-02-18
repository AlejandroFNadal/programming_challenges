/**
 * Alejandro Nadal 2026
 *
 * Ex 3. LPI. Demonstration of SA_RESETHAND
 *
 * One time executing a signal handler
 *
 * */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

void exit_handler();

const struct sigaction sigaction_struct = {
    .sa_handler = exit_handler,
    .sa_flags = SA_RESETHAND,
};

void exit_handler() {
  printf("Are you sure you want to exit? Y/N\n");
  char confirm = getchar();
  if (confirm == 'Y') {
    printf("Press Control + C again to exit\n");
  } else {
    sigaction(SIGINT, &sigaction_struct, NULL);
  }
}

int main() {
  sigaction(SIGINT, &sigaction_struct, NULL);
  while (1 == 1) {
  };
}
