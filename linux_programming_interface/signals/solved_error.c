#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void horribly_slow_handler() {
  for (int i = 0; i < 3; i++) {
    printf("Handler secs: %d\n", i);
    sleep(1);
  }
}

int main() {
  char dumb_buffer[100];
  struct sigaction act = {0};
  act.sa_handler = horribly_slow_handler;
  act.sa_flags = SA_RESTART | SA_NODEFER;
  sigaction(SIGINT, &act, NULL);
  int bytes_read = read(0, &dumb_buffer, 100);
  printf("Bytes read %d\n", bytes_read);
  if (bytes_read == -1) {
  	perror("Status: ");
  }
}
