#include "../lib/tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  bool append = false;
  printf("argc: %d\n", argc);
  if (argc == 4) {
    append = argv[3][0] == 'x';
  }
  printf("Append: %d\n", append);
  long long int counter = atoll(argv[2]);
  printf("Counter: %lld\n", counter);
  int fd;
  int arr[1] = {1};
  if (append) {
    fd = open(argv[1], O_APPEND | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
      errExit("open");
    }
  } else {
    fd = open(argv[1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
      errExit("open");
    }
    if (lseek(fd, 0, SEEK_END) == -1) {
      errExit("lseek");
    }
  }
  while (counter > 0) {
    if (write(fd, arr, 1) == -1) {
      errExit("write");
    }
    if (append == false) {
      if (lseek(fd, 0, SEEK_END) == -1) {
        errExit("lseek");
      }
    }
    counter--;
  }
}
