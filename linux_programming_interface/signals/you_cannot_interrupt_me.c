/*
 * Alejandro Nadal 2026
 *
 * Ex 2 LPI Signals
 *
 * Show that using SIG_IGN, the signal is not received by the process
 *
 * Use the command "kill -s SIGINT <pid>" to send the signal to the process, and
 * see that it does not terminate
 *
 * */
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("My PID is %d, try to kill me\n", getpid());
  signal(SIGINT, SIG_IGN);
  while (1 == 1) {
  }
  return 0;
}
