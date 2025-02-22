/*
Ex 9.3 Linux Programming Interface
Alejandro Nadal
Implementing initgroups using setgroups
*/
#include <errno.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int an_init_groups(const char *user, gid_t group) {
  struct group *group_entry = getgrent();
  __gid_t group_list[1024]; // fancy integers
  int amount = 0;
  while (group_entry != NULL) {
    char **member_name = group_entry->gr_mem;
    while (*member_name != NULL) {
      if (strcmp(user, *member_name) == 0) {
        printf("Group Name %s\n", group_entry->gr_name);
        group_list[amount] = group_entry->gr_gid;
        printf("Member %s GID: %d\n", *member_name, group_list[amount]);
        amount += 1;
      }
      member_name += 1;
    }
    group_entry = getgrent();
  }
  group_list[amount] = group;
  amount++;
  int res = setgroups(amount, group_list);
  if (res == -1) {
    if (errno == EPERM) {
      printf("Invalid permissions\n");
    }
    if (errno == EINVAL) {
      printf("Too many groups");
    }
    endgrent();
    return -1;
  } else {
    printf("Successfully added groups\n");
    endgrent();
    return 0;
  }
}
int main() {
  int current_groups = getgroups(0, NULL);
  printf("Before calling an_init_groups, current groups %d", current_groups);
  an_init_groups("ale", 1);
  int new_groups = getgroups(0, NULL);
  printf("After calling an_init_groups, current groups %d\n", new_groups);
}
