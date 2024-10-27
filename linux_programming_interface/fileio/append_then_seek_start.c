#include "../lib/tlpi_hdr.h" 
#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

/* Very cool concept. SEEK_SET in a file with the append flag,
 * is at the end of the file. That is why the write does not appear
 * in the beggining*/
int main(int argc, char *argv[]){
  int fd = open(argv[1], O_APPEND | O_WRONLY);
  if (lseek(fd, 0, SEEK_SET) == -1){
    errExit("lseek");
  }
  if(write(fd, "test", 4) == -1){
    errExit("write failed");
  }
  return 0;
}

