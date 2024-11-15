#include <fcntl.h>
#include "../lib/tlpi_hdr.h"
#include <assert.h>

int mydup(int fd){
  int newfd = fcntl(fd,  F_DUPFD, 0); 
  return newfd;
}
// This is not atomic, and I dont know how to make it 
// atomic.
int mydup2(int fd, int new_desired_fd){
  close(new_desired_fd);
  int newfd = fcntl(fd,  F_DUPFD, new_desired_fd); 
  return newfd;
}

int main(int argc, char *argv[]){
  int old_fd = open(argv[1], O_CREAT | O_RDWR, S_IRUSR| S_IWUSR);
  write(old_fd, "start\n", 6); 
  int newfd = mydup(old_fd);
  write(newfd, "writing with new fd\n", 20); 
  write(old_fd, "writing with old fd\n", 20); 
  int newfd2 = mydup2(old_fd, 10);
  assert(newfd2 == 10);
  printf("newfd2 = %d\n", newfd2);
  write(newfd2, "writing with new fd2\n", 21);
  return 0;
}

