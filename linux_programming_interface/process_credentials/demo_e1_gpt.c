// Asked GPT to verify my answers with code:
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/fsuid.h>
#include <sys/types.h>
#include <unistd.h>

void print_uids(const char *msg) {
  uid_t ruid, euid, suid, fsuid;
  getresuid(&ruid, &euid, &suid); // Get real, effective, and saved UIDs
  fsuid = setfsuid(-1);           // Get file-system UID

  printf("%s\n", msg);
  printf("Real UID: %d, Effective UID: %d, Saved UID: %d, FSUID: %d\n\n", ruid,
         euid, suid, fsuid);
}

int main() {
  // Initial state
  print_uids("Initial UID state:");

  // (a) setuid(2000)
  // setuid(2000);
  // print_uids("After setuid(2000):");

  // (b) setreuid(-1, 2000)
  // setreuid(-1, 2000);
  // print_uids("After setreuid(-1, 2000):");

  // (c) seteuid(2000)
  // seteuid(2000);
  // print_uids("After seteuid(2000):");

  // (d) setfsuid(2000)
  setfsuid(2000);
  print_uids("After setfsuid(2000):");

  // (e) setresuid(-1, 2000, 3000)
  setresuid(-1, 2000, 3000);
  print_uids("After setresuid(-1, 2000, 3000):");

  return 0;
}
