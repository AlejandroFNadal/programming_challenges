/*
Program which imitates the behavior of the tail command in the GNU Coreutils
*/
#include "../lib/tlpi_hdr.h"
#include <assert.h>
#include <bits/posix2_lim.h>
#include <fcntl.h>
#include <unistd.h>

void tail(char *filePath, int amount_lines) {
  int openFlags = O_RDONLY;
  int fd = open(filePath, openFlags);
  // We dont need readahead if we are going to go to the end and read back.
  posix_fadvise(fd, 0, 0, POSIX_FADV_RANDOM);
  int remainingFileSize = lseek(fd, 0, SEEK_END);
  // now we need to read back in blocks, put the content in a buffer, and search
  // for linejump characters. Every time we find one, we will store it in a
  // stack and at the end we will empty the stack to stdout. Traditionally, many
  // conventions said that lines should not be longer than 80 chars. We will
  // consider for this century that the average line will be double that.
  int blockSize = 160 * amount_lines;
  int lineJumpsFound = 0;
  char lineJump = '\n';
  // finding out what is the minimum requirement for a tool in my system for
  // line lenght
  int lineLength = sysconf(_SC_LINE_MAX);
  printf("Max length line %d\n", lineLength);
  printf("Amount lines: %d\n", amount_lines);
  char *lines[amount_lines];
  for (int i = 0; i < amount_lines; i++) {
    lines[i] = (char *)malloc(lineLength);
    lines[i][0] = '\0';
  }
  // a buffer either the blockSize or the filesize, whatever is smaller
  char *buffer = malloc(min(blockSize, remainingFileSize));
  while (lineJumpsFound < amount_lines && remainingFileSize > 0) {
    int bufferSize = min(blockSize, remainingFileSize);
    int pos = lseek(fd, -bufferSize, SEEK_CUR);
    assert(pos != -1);
    pread(fd, buffer, bufferSize, pos);
    int i = bufferSize - 1;
    int lastLineJump = bufferSize - 1;
    while (i >= 0 && lineJumpsFound < amount_lines) {
      if (buffer[i] == lineJump) {
        int sizeCopy = lastLineJump - i;
        assert(sizeCopy >= 0);
        memcpy(lines[lineJumpsFound], &buffer[i], sizeCopy);
        lineJumpsFound++;
        lastLineJump = i;
      }
      i--;
    }
    remainingFileSize = remainingFileSize - bufferSize;
  }
  for (int i = lineJumpsFound - 1; i >= 0; i--) {
    printf("%s", lines[i]);
  }
}
int main(int argc, char *argv[]) {
  int numLines = atoi(argv[2]);
  tail(argv[1], numLines);
}
