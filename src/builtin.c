#include "builtin.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int Builtin(char** argv) {
  if (CdFunc(argv)) {
    return 1;
  };

  return 0;
}

int CdFunc(char** argv) {
  if (strcmp(argv[0], "cd") == 0) {
    if (argv[1] == NULL) {
      fprintf(stderr, "cd: missing argument\n");
    } else if (argv[2] != NULL) {
      fprintf(stderr, "cd: too many arguments\n");
    } else if (chdir(argv[1]) == -1) {
      perror("cd");
    }
    return 1;
  }
  return 0;
}
