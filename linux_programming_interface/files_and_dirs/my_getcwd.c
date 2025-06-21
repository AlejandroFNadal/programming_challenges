/**
 * Alejandro Nadal 2025
 *
 * Implementing getcwd. Works in most ocassions, not complete on home: perhaps a
 * mounting point problem? The book suggest actually changing current
 * directories every time, something I have not done. home is a different
 * partition and then the inodes belong to different fs inside and outside home.
 *
 * To discuss with Oscar Pilkington
 *
 * */
#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* I dont want to show this interface with the recursive upward path*/
void my_getcwd_rec(char *dir, long int inode, char *pathBuffer[],
                   int *stack_pointer, long int dev_id) {
  struct stat info;
  stat(dir, &info);
  printf("Searching for inode %ld", inode);
  DIR *parent_dir = opendir(dir);
  struct dirent *curr_dir;
  struct stat device_finder;
  do {
    device_finder.st_dev = 0;
    curr_dir = readdir(parent_dir);
    char *temp = malloc(PATH_MAX);
    strcat(temp, dir);
    strcat(temp, curr_dir->d_name);
    stat(temp, &device_finder);
    printf("curr dir:%s inode %ld device id %ld\n", curr_dir->d_name,
           curr_dir->d_ino, device_finder.st_dev);
    free(temp);
  } while (curr_dir != NULL && curr_dir->d_ino != inode &&
           device_finder.st_dev != dev_id);
  if (curr_dir == NULL) {
    printf("You are in a broken fs\n");
  } else {
    printf("Found parent %s\n", curr_dir->d_name);
  }
  pathBuffer[*stack_pointer] = malloc(255);
  strcpy(pathBuffer[*stack_pointer], curr_dir->d_name);
  strcat(dir, "/..");
  (*stack_pointer)++;
  if (info.st_ino == inode) {
    return;
  }
  my_getcwd_rec(dir, info.st_ino, pathBuffer, stack_pointer, dev_id);
}

void my_getcwd(char *pathBuffer[]) {
  struct stat info;
  stat(".", &info);
  printf("%ld", info.st_ino);
  char *parent_dir_buffer = malloc(PATH_MAX);
  strcat(parent_dir_buffer, "..");
  int stack_pointer = 0;
  my_getcwd_rec(parent_dir_buffer, info.st_ino, pathBuffer, &stack_pointer,
                info.st_dev);
  // now inverting pathBuffer. The last element of the stack, root, has no name,
  // and therefore we skip it
  // stack_pointer--;
  while (stack_pointer >= 0) {
    printf("/%s", pathBuffer[stack_pointer]);
    stack_pointer--;
  }
  printf("\n");
}

int main() {
  char *path[PATH_MAX];
  my_getcwd(path);
}
