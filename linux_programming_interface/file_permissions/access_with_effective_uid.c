#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int access_euid(const char *pathname, int mode) {
  int me = geteuid();
  int mygroup = getegid();
  struct stat file_attrs;
  file_attrs.st_uid = -1;
  stat(pathname, &file_attrs);
  if (mode == F_OK && file_attrs.st_uid != -1) {
    return 0;
  }
  // first check if euid is root, group is root, or uid matches
  if (me == 0 || mygroup == 0 || file_attrs.st_uid == me) {
    if (mode == R_OK && file_attrs.st_mode & S_IRUSR) {
      return 0;
    } else if (mode == W_OK && file_attrs.st_mode & S_IWUSR) {
      return 0;
    } else if (mode == X_OK &&
               (file_attrs.st_mode & S_IXUSR || file_attrs.st_mode & S_IXGRP ||
                file_attrs.st_mode & S_IXOTH)) {
      return 0;
    }
  } else if (file_attrs.st_gid == mygroup) {
    // check for group ownership{}
    if (mode == R_OK && file_attrs.st_mode & S_IRGRP) {
      return 0;
    } else if (mode == W_OK && file_attrs.st_mode & S_IWGRP) {
      return 0;
    } else if (mode == X_OK && file_attrs.st_mode & S_IXGRP) {
      return 0;
    }
  } else {
    // check for other ownership{}
    if (mode == R_OK && file_attrs.st_mode & S_IROTH) {
      return 0;
    } else if (mode == W_OK && file_attrs.st_mode & S_IWOTH) {
      return 0;
    } else if (mode == X_OK && file_attrs.st_mode & S_IXOTH) {
      return 0;
    }
  }
  return 1;
}
int main() {}
