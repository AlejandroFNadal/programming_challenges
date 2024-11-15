#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <stdint.h>
#include <sys/uio.h>

int my_readv(int fd, const struct iovec *iov, int iovcnt){
// to keep atomicty, I actually need to calculate the full size of the read and perform a single read. Otherwise, 
// if the fd were to be shared among threads, the reads could end up being incorrect.
  int full_size_to_read = 0;
  for(int i = 0; i < iovcnt; i++){
    full_size_to_read += iov->iov_len;
  }
  void* buffer = malloc(full_size_to_read);
  int total_read = read(fd, buffer, full_size_to_read);
  printf("Debugging: %s\n", (char *) buffer);
  int buffer_pos = 0;
  for(int i = 0; i < iovcnt; i++){
    memcpy(iov[i].iov_base, buffer + buffer_pos, iov[i].iov_len);
    buffer_pos += iov[i].iov_len;
  }
  return total_read;
}
struct Train{
    char train_id[6];
    char train_country_id[2];
  };

void TrainPrint(struct Train train){
  for(int i = 0; i < 6; i++){
    printf("%c", train.train_id[i]);
  }
  printf("\n");
  for(int i = 0; i < 2; i++){
    printf("%c", train.train_country_id[i]);
  }
  printf("\n");
}
int main(int argc, char *argv[]) {
  
  struct iovec iov[2];
  struct Train first_train;
  struct Train sec_train;
  iov[0].iov_base = &first_train;
  iov[0].iov_len = sizeof(first_train);
  iov[1].iov_base = &sec_train;
  iov[1].iov_len = sizeof(sec_train);
  int fd = open(argv[1], O_RDONLY);
  int bytes_read = my_readv(fd, iov, 2);
  printf("Bytes read %d\n", bytes_read);
  printf("First train:");
  TrainPrint(first_train);
  TrainPrint(sec_train);
}
