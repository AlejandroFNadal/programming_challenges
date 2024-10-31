#include "../lib/tlpi_hdr.h"
#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
  bool append = argv[3][0] == 'x';
  long long int counter = atoll(argv[2]);
  int fd;
  int arr[1] = {1};
  if(append) {
    fd = open(argv[1], O_APPEND);
  } else {
    fd = open(argv[1], 0);
    lseek(fd, 0, SEEK_END);
  }
  while (counter > 0) {
    write(fd,arr,1);
    counter--;
  }
   
}
