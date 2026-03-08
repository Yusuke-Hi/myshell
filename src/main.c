#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "builtin.h"
#include "constants.h"
#include "executor.h"
#include "mysignal.h"

enum {
  MAXPROMPTSIZE = 1024,
};

int main() {
  while (1) {
    printf("myshell> ");
    fflush(stdout);
    // input
    char buf[MAXPROMPTSIZE];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
      printf("\n");
      break;
    }
    char* p = strchr(buf, '\n');
    if (p != NULL) {
      *p = '\0';
    }
    if (buf[0] == '\0') {
      continue;
    }

    // parse
    char* argv[MAXARGSIZE];
    Tokenize(argv, buf);
    ParseResult parse_result = ParsePrompt(argv);

    // builtin
    if (Builtin(argv)) {
      continue;
    }

    // execute
    Execute(&parse_result, argv);
  }
}
