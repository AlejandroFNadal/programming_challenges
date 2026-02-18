/*
 *  Alejandro Nadal 2026
 *
 *  Implementing my own siginterrupt function. Deprecated in SUSv4
 *  Ex 4 of LPI
 *
 *  siginterrupt changes the behavior of the signal disposition, so that you can
 * add or remove the SA_RESETHAND flag of the sigaction struct
 * */
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

void horribly_slow_handler() {
  for (int i = 0; i < 3; i++) {
    printf("Handler secs: %d\n", i);
    sleep(1);
  }
}

void an_sig_interrupt(int sig, bool on) {
  struct sigaction current = {0};
  sigaction(sig, NULL, &current);
  if (on == true) {
    current.sa_flags |= SA_RESTART;
  } else {
    // we remove it without damaging any other flags
    current.sa_flags &= !(SA_RESTART);
  }
  sigaction(sig, &current, NULL);
}

int main() {
  char dumb_buffer[100];
  struct sigaction act = {0};
  act.sa_handler = horribly_slow_handler;
  act.sa_flags = SA_RESTART | SA_NODEFER;
  sigaction(SIGINT, &act, NULL);
  int bytes_read = read(0, &dumb_buffer, 100);
  printf("Bytes read %d\n", bytes_read);
  perror("Status: ");
  // if (bytes_read == -1) {
  //   perror("Status: ");
  // }
  an_sig_interrupt(SIGINT, false);
  bytes_read = read(0, &dumb_buffer, 100);
  printf("Bytes read %d\n", bytes_read);
  perror("Status: ");
  // if (bytes_read == -1) {
  //   perror("Status: ");
  // }
}
