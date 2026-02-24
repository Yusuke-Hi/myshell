#include <stdio.h>
#include <string.h>

#define MAXPROMPTSIZE 1024
#define MAXARGSIZE 128

int main() {
  while (1) {
    printf("$ ");
    // input
    char buf[MAXPROMPTSIZE];
    fgets(buf, sizeof(buf), stdin);
    char* p = strchr(buf, '\n');
    if (p != NULL) {
      *p = '\0';
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
  }
}