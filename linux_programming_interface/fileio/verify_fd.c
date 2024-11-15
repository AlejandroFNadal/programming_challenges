#include "../lib/tlpi_hdr.h"
#include <assert.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
  int fd1 = open(argv[1], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if(fd1 == -1){
    errExit("open");
  }
  if(write(fd1, "test", 4) == -1){
    errExit("write");
  }
  int f2 = dup(fd1);
  int offset_f1 = lseek(fd1,0,  SEEK_CUR);
  int offset_f2 = lseek(f2, 0, SEEK_CUR);
  printf("Offsets are %d %d\n", offset_f1, offset_f2);
  assert(offset_f1 == offset_f2);
  int flags_f1 = fcntl(fd1, F_GETFL); 
  int flags_f2 = fcntl(f2, F_GETFL);
  assert(flags_f1 == flags_f2);
  return 0;
}
