// This was supposed to fail with big (larger than 4gb files) but it doesnt.
// I think it could be because it is now a 64 bit system.
#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  int fd;
  long long int off;
  fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  off = atoll(argv[2]);
  if (lseek(fd, off, SEEK_SET) == -1) {
    errExit("lseek");
  }
  if (write(fd, "test", 4) == -1) {
    errExit("write");
  }
  exit(EXIT_SUCCESS);
}
