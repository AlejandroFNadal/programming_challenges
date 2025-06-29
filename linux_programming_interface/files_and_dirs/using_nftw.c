/*
 * Alejandro Nadal 2025
 *
 * Write a program that uses nftw() to traverse a directory tree and finishes by
 * printing out counts and percentages of the various types (regular, directory,
 * symbolic link, and so on) of files in the tree.
 */

// I don't know why that is required
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>

struct statistics {
  int directories;
  int cannot_read;
  int files;
  int symlinks;
  int broken_symlinks;
};

struct statistics gl_stats;
static int traverser(const char *pathname, const struct stat *sbuf, int type,
                     struct FTW *ftwb) {
  // printf("%s\n", pathname);
  if (type == FTW_D)
    gl_stats.directories++;
  if (type == FTW_F)
    gl_stats.files++;
  if (type == FTW_DNR || type == FTW_NS)
    gl_stats.cannot_read++;
  if (type == FTW_SL)
    gl_stats.symlinks++;
  if (type == FTW_SLN)
    gl_stats.broken_symlinks++;
  return 0;
}

int main(int argc, char *argv[]) {
  const int max_descriptors = 20;
  int flag = FTW_PHYS;
  int dir_amount = 0;
  nftw(argv[1], traverser, max_descriptors, flag);
  printf("Directories: %d\n", gl_stats.directories);
  printf("Files %d\n", gl_stats.files);
  printf("Cannot read %d\n", gl_stats.cannot_read);
  printf("Symlinks: %d\n", gl_stats.symlinks);
  printf("Broken symlinks %d\n", gl_stats.broken_symlinks);
  return 0;
}
