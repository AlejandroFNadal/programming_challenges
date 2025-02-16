#include <assert.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>

struct passwd *an_getpwnam(const char *name) {
  struct passwd *temp = getpwent();
  // yes, I know, strcmp is evil, but this is a textbook exercise
  while (temp != NULL && strcmp(temp->pw_name, name)) {
    temp = getpwent();
  }
  endpwent();
  if (temp != NULL) {
    printf("The user shell is %s \n", temp->pw_shell);
  }
  return temp;
}

int main() {
  assert(an_getpwnam("ale") != NULL);
  assert(an_getpwnam("test22") == NULL);
}
