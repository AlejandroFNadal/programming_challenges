#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  size_t bufSize, numBytes, thisWrite, totWritten;
  char *buf;
  int fd, openFlags;

  numBytes = getLong(argv[2], GN_GT_0, "num-bytes");
  bufSize = getLong(argv[3], GN_GT_0, "buf-size");

  buf = malloc(bufSize);
  openFlags = O_CREAT | O_WRONLY;

#if defined(USE_O_SYNC) && defined(O_SYNC)
  openFlags |= O_SYNC;
#endif

  fd = open(argv[1], openFlags, S_IRUSR | S_IWUSR);
  if (fd == -1)
    errExit("open");

  for (totWritten = 0; totWritten < numBytes; totWritten += thisWrite) {
    thisWrite = min(bufSize, numBytes - totWritten);
    if (write(fd, buf, thisWrite) != thisWrite)
      fatal("partial/failed write");
  }

#ifdef USE_FSYNC
  if (fsync(fd))
    errExit("fsync");
#endif
  if (close(fd) == -1)
    errExit("close");
  exit(EXIT_SUCCESS);
}
