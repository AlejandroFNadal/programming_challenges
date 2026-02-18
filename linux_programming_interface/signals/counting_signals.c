/*
 * Alejandro Nadal 2026
 *
 * Ex 3 of LPI, analyzing effect of NO_DEFER signal
 *
 * Pressing Control C once will count up. Pressing it again during the count
 * will restart it, and when that count finishes, it will continue with the
 * previous one
 *
 * */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void horribly_slow_handler() {
  for (int i = 0; i < 10; i++) {
    printf("Handler secs: %d\n", i);
    sleep(1);
  }
}

int main() {
  struct sigaction act;
  act.sa_handler = horribly_slow_handler;
  act.sa_flags = SA_NODEFER;
  sigaction(SIGINT, &act, NULL);
  while (1 == 1)
    ;
}
