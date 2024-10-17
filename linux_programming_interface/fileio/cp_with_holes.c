#include "../lib/tlpi_hdr.h" 
#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int read_file_desc = open(argv[1],O_RDONLY);
  int write_file_desc = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR);
  int offset;
  if (read_file_desc == -1){
    errExit("Cannot open first file");
  }
  if (write_file_desc== -1){
    errExit("Cannot open second file");
  }
  int buffer[1];
  while(read(read_file_desc, buffer, 1) == 1){
    // if we find a hole, we keep moving 
    while(buffer[0] == 0x00){
      read(read_file_desc, buffer, 1);
      if(buffer[0] != 0x00){
        offset = lseek(read_file_desc, 0, SEEK_CUR); // hack to get current offset
        lseek(write_file_desc, offset, SEEK_SET);
      }
    }
    write(write_file_desc, buffer, 1);
  }
  return 0;
}
