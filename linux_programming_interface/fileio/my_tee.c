#include "../lib/tlpi_hdr.h" 
#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int command_opts, file_descriptor;
  char single_byte_buffer[1];
  bool append = false;

  while((command_opts = getopt(argc, argv, ":a")) != -1){
    switch(command_opts){
      case 'a': append = true; break; 
    }
  }
  printf("Append behavior is %d\n", append);
  printf("Processing file %s\n", argv[optind]);
  int default_flags = O_RDWR | O_CREAT ;
  int mode = S_IRUSR | S_IWUSR;
  if(append){
    file_descriptor = open(argv[optind], default_flags | O_APPEND, mode);
  } else {
    file_descriptor = open(argv[optind], default_flags | O_TRUNC, mode);
  }
  if (file_descriptor == -1) {
    errExit("Could not open");
  }
  int result = read(STDIN_FILENO, single_byte_buffer, 1);
  int write_res;
  while(result == 1){
      write_res = write(file_descriptor, single_byte_buffer, 1);
      if(write_res == -1){
        printf("Error when writing the file");
      }
    printf("%c", single_byte_buffer[0]);
    result = read(STDIN_FILENO, single_byte_buffer, 1);
  }
  return 0;
}
