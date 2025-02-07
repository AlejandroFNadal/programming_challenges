#include "../lib/tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  size_t len;
  off_t offset;
  int file_descriptor, parameter_index, j;
  char *buffer;
  ssize_t num_read, num_written;

  if (argc < 3 || strcmp(argv[1], "--help") == 0) {
    usageErr("%s file {r<len> | w<string>|s<offset>}.../n", argv[0]);
  }
  file_descriptor = open(argv[1], O_RDWR | S_IRUSR | S_IWUSR |
                                      S_IRGRP | S_IROTH | S_IWOTH);

  if (file_descriptor == -1) {
    errExit("Could not open");
  }

  for (parameter_index = 2; parameter_index < argc;
       parameter_index = parameter_index + 2) {
    switch (argv[parameter_index][0]) {
      case 'r':
      case 'R':
        len = getLong(argv[parameter_index + 1], GN_ANY_BASE,
                      argv[parameter_index]);
        buffer = malloc(len);
        if (buffer == NULL) {
          errExit("Malloc fail");
        }
        num_read = read(file_descriptor, buffer, len);
        if (num_read == -1) {
          errExit("Read Failed");
        }
        if (num_read == 0) {
          printf("%s: end of file/n", argv[parameter_index]);
        } else {
          printf("%s: ", argv[parameter_index]);
          for (j = 0; j < num_read; j++) {
              if(argv[parameter_index][0] == 'R'){
                printf("%c", isprint((unsigned char) buffer[j]) ? buffer[j] :'?');
              } else {
                printf("%02x", (unsigned int)buffer[j]);
              }
          }
        }
        free(buffer);
        break;
      case 'w':
        num_written =
            write(file_descriptor, argv[parameter_index + 1], strlen(argv[parameter_index + 1]));
        if (num_written == -1) {
          errExit("Failed to write");
        }
        printf("%s: wrote %ld bytes/n", argv[parameter_index], (long)num_written);
        break;

      case 's':
        offset = getLong(argv[parameter_index + 1], GN_ANY_BASE,
                         argv[parameter_index]);
        if (lseek(file_descriptor, offset, SEEK_SET) == -1) {
          errExit("Lseek failed");
        }
        printf("%s seek succeeded/n", argv[parameter_index]);
        break;
    }
  }
  return 0;
}
