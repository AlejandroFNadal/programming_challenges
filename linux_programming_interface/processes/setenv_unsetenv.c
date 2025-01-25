#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
int ale_setenv(const char *name, const char *value, int overwrite) {
  char **env_pointer;
  // perhaps it is already there
  if (getenv(name) != NULL) {
    printf("Name is already there\n");
    if (overwrite == 0) {
      printf("Not overwriting\n");
      return 0;
    } else {
      char *concated = malloc(sizeof(name) + sizeof(value) + 2);
      sprintf(concated, "%s=%s", name, value);
      printf("Overwritten with %s\n", concated);
      putenv(concated);
      //  we know it is there, so we have to find it to overwrite it
      /*
      for (env_pointer = environ; *env_pointer != NULL; env_pointer++) {
        printf("envar analyzed is %s\n", *env_pointer);
        const char *env_name = strtok(*env_pointer, "=");
        printf("ENV var name analyzed is: %s\n", env_name);
        if (strcmp(name, env_name) == 0) {
          printf("Found it");
          return 0;
        } else {
          printf("Not it\n");
        }
      }*/
      return 0;
    }
  } else {
    printf("Name not there, writing");
    char *concated = malloc(sizeof(name) + sizeof(value) + 2);
    sprintf(concated, "%s=%s", name, value);
    printf("Overwritten with %s\n", concated);
    putenv(concated);
    return 0;
  }
}

int ale_unsetenv(const char *name) {
  char **read_pointer = environ;
  char **write_pointer = environ;
  while (*read_pointer != NULL) {
    // obtain pointer to position of the char
    char *equal = strchr(*read_pointer, '=');
    if (equal != NULL) {
      // pointer of pos - position of start
      int len = equal - *read_pointer;
      if (strncmp(name, *read_pointer, len) == 0) {
        printf("envar analyzed is %s\n", *read_pointer);
        read_pointer++;
        continue;
      }
      *write_pointer = *read_pointer;
      read_pointer++;
      write_pointer++;
    }
  }
  *write_pointer = NULL; // I WAS MISSING THIS
  return 0;
}
// char *val = "TEST=TRUE";
int main() {
  // putenv(val);
  ale_setenv("TEST", "FALSE", 0);
  ale_setenv("TEST", "FALSE\0", 1);
  printf("---------------------\n");
  char *val = getenv("TEST");
  printf("TEST: %s\n", val);
  assert(strcmp(getenv("TEST"), "FALSE") == 0);
  ale_unsetenv("TEST");
  char *val2 = getenv("TEST");
  printf("TEST: %s\n", val2);
  assert(getenv("TEST") == NULL);
}
