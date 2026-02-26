#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXPROMPTSIZE 1024
#define MAXARGSIZE 128

int main() {
  while (1) {
    printf("myshell> ");
    fflush(stdin);
    // input
    char buf[MAXPROMPTSIZE];
    fgets(buf, sizeof(buf), stdin);
    char* p = strchr(buf, '\n');
    if (p != NULL) {
      *p = '\0';
    }
    if (buf[0] == '\0') {
      continue;
    }

    char* argv[MAXARGSIZE];
    int argv_i = 0;
    char* token = strtok(buf, " ");
    while (token != NULL) {
      argv[argv_i] = token;
      ++argv_i;
      token = strtok(NULL, " ");
    }
    argv[argv_i] = NULL;

    // builtin
    if (strcmp(argv[0], "cd") == 0) {
      if (argv[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
      } else if (argv[2] != NULL) {
        fprintf(stderr, "cd: too many arguments\n");
      } else if (chdir(argv[1]) == -1) {
        perror("cd");
      }
      continue;
    }

    // fork
    signal(SIGINT, SIG_IGN);
    pid_t pid = fork();
    switch (pid) {
      case -1:
        perror("fork");
        exit(EXIT_FAILURE);
      case 0:
        signal(SIGINT, SIG_DFL);
        if (execvp(argv[0], argv) == -1) {
          perror("execvp failed");
          exit(EXIT_FAILURE);
        }
      default:
        wait(NULL);
        signal(SIGINT, SIG_DFL);
    }
  }
}
