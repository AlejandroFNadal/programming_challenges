#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "../lib/tlpi_hdr.h" 

#define MAX_FILES 100



static void
 /* Display information from inotify_event structure */
  displayInotifyEvent(struct inotify_event *i){
  printf("wd =%2d; ", i->wd);
  if (i->cookie > 0)
    printf("cookie =%4d; ", i->cookie);
  printf("mask = ");
  if (i->mask & IN_ACCESS) printf("IN_ACCESS ");

  if (i->mask & IN_ATTRIB) printf("IN_ATTRIB ");
  if (i->mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
  if (i->mask & IN_CLOSE_WRITE) printf("IN_CLOSE_WRITE ");

  if (i->mask & IN_CREATE) printf("IN_CREATE ");
  if (i->mask & IN_DELETE) printf("IN_DELETE ");
  if (i->mask & IN_DELETE_SELF) printf("IN_DELETE_SELF ");
  if (i->mask & IN_IGNORED) printf("IN_IGNORED ");
  if (i->mask & IN_ISDIR) printf("IN_ISDIR ");
  if (i->mask & IN_MODIFY) printf("IN_MODIFY ");
  if (i->mask & IN_MOVE_SELF) printf("IN_MOVE_SELF ");
  if (i->mask & IN_MOVED_FROM) printf("IN_MOVED_FROM ");
  if (i->mask & IN_MOVED_TO) printf("IN_MOVED_TO ");
  if (i->mask & IN_OPEN) printf("IN_OPEN ");
  if (i->mask & IN_Q_OVERFLOW) printf("IN_Q_OVERFLOW ");
  if (i->mask & IN_UNMOUNT) printf("IN_UNMOUNT ");
  if (i->name > 0){
    printf("%s\n", i->name);
  }
  
}

int inotify_fd;
char buffer[4096];
struct inotify_event event;


// function to be called for each file in the directory tree
int process_file(const char *path, const struct stat *sb, int typeflag,
                 struct FTW *ftwbuf) {
  printf("Visited: %s\n", path);
  inotify_add_watch(inotify_fd, path, IN_ALL_EVENTS);
  return 0;
}

int main() {
  // Create an inotify instance
  inotify_fd = inotify_init();
  if (inotify_fd < 0) {
    perror("inotify_init");
    return 1;
  }
  nftw("./test", process_file, MAX_FILES, 0);
  // iterate until user terminates
  while (1) {
    read(inotify_fd, &event, 4096);
    displayInotifyEvent(&event);
  }

  return 0;
}
