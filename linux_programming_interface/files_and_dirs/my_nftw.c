/*
 * Alejandro Nadal 2025
 *
 * My implementation of nftw: new file tree walk
 *
 * Implemented as an exercise for the Linux Programming Interface book
 **/

#define _XOPEN_SOURCE 500
#include <sys/stat.h>
#include <dirent.h>
#include <ftw.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct func_pars {
  char *pathname;
  struct stat *statbuf;
  int typeflag;
  struct FTW *ftwbuf;
};

// Len is both the amount of items and also the position where to write the next
// element.
struct dyn_array {
  unsigned int len;
  unsigned int cap;
  struct func_pars *first;
};

struct dyn_array stack;

void push(struct dyn_array *a_stack, struct func_pars new_el){
  if (a_stack->first == NULL){
    a_stack->first = malloc(sizeof(struct func_pars) * 100);
    a_stack->cap = 100;
    a_stack->len = 0;
  }
  if(a_stack->len == a_stack->cap){
    printf("Here we should deal with realloc\n");
  }
  a_stack->first[a_stack->len] = new_el;
  a_stack->len++;
  printf("Length of the stack is %d\n", a_stack->len);

}

void pop(struct dyn_array *a_stack) {
  if (a_stack->first == NULL) {
    return;
  }
  if (a_stack->len == 0) {
    a_stack->first = NULL;
    return;
  }
  if(a_stack->len == 1){
    free(a_stack->first);
    a_stack->first = NULL;
  }
  for (int i = 1; i <= a_stack->len; i++) {
    a_stack->first[i - 1] = a_stack->first[i];
  }
  a_stack->len--;
}

// Did not implement depth, only breadth. Also did not implement symlinks. This is a conceptual thing.
void an_nftw(const char *pathname,
             int (*func)(const char *pathname, const struct stat *statbuf,
                         int typeflag, struct FTW *ftwbuf)) {
  struct __dirstream *stream = opendir(pathname);
  struct dirent *entry = readdir(stream);
  struct stat statbuf;
  struct FTW *ftwbuf;

  while (entry != NULL) {
    printf("Length of the stack is %d\n", stack.len);
    if ((strcmp(entry->d_name, "..") == 0) ||strcmp(entry->d_name, ".") == 0){
      entry = readdir(stream);
      continue;
    }
    char *full_path = malloc(4096);
    strcat(full_path, pathname);
    strcat(full_path, "/");
    strcat(full_path, entry->d_name);
    int err = stat(full_path, &statbuf);
    if (err != 0){
      printf("Error on Stat");
    }
    struct func_pars node;
    node.pathname = full_path;
    node.statbuf = &statbuf;
    node.ftwbuf = ftwbuf;
    // just a file
    if (S_ISDIR(statbuf.st_mode)) {
      node.typeflag = FTW_D;
      printf("Adding to stack %s\n", node.pathname);
      push(&stack, node);
    } else if (S_ISREG(statbuf.st_mode)){
      node.typeflag = FTW_F;
    }
    func(node.pathname, node.statbuf, node.typeflag, node.ftwbuf);
    entry = readdir(stream);
  }
  printf("Length of the stack is %d\n", stack.len);
  while (stack.len != 0) {
    printf("Going through stack\n");
    an_nftw(stack.first[0].pathname, func);
    pop(&stack);
  }
};

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
  printf("%s\n", pathname);
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
  char *parameter = argv[1];
  if(parameter == NULL){
    parameter = ".";
  }
  an_nftw(parameter, traverser);
}
