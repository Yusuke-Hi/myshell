#include "parser.h"

#include <stdio.h>
#include <string.h>

char** Tokenize(char** argv, char* buf) {
  char* token = strtok(buf, " ");
  int argv_i = 0;
  while (token != NULL) {
    argv[argv_i] = token;
    ++argv_i;
    token = strtok(NULL, " ");
  }
  argv[argv_i] = NULL;
}

ParseResult ParsePrompt(char** argv) {
  ParseResult parse_result = ParseArgv(argv);
  if (parse_result.error) {
    fprintf(stderr, "failed to parse argv\n");
    return NewParseResult();
  }

  return parse_result;
}

ParseResult ParseArgv(char** argv) {
  ParseResult result = NewParseResult();
  for (int i = 0; argv[i] != NULL; ++i) {
    if (strcmp(argv[i], ">") == 0) {
      if (result.redirect_index != -1) {
        fprintf(stderr, ">: use only one time\n");
        result.error = 1;
        break;
      }
      if (argv[i + 1] == NULL) {
        fprintf(stderr, ">: missing argument\n");
        result.error = 1;
        break;
      }
      result.redirect_index = i;
      argv[i] = NULL;
    } else if (strcmp(argv[i], "|") == 0) {
      if (result.pipe_index != -1) {
        fprintf(stderr, "|: use only one time\n");
        result.error = 1;
        break;
      }
      if (argv[i + 1] == NULL) {
        fprintf(stderr, "|: missing argument\n");
        result.error = 1;
        break;
      }
      result.pipe_index = i;
    }
  }

  if (result.pipe_index != -1) {
    CreatBothSideArgv(&result, argv);
  }

  return result;
}

ParseResult NewParseResult() {
  ParseResult result = {.redirect_index = -1, .pipe_index = -1, .error = 0};
  return result;
}

void CreatBothSideArgv(ParseResult* result, char** argv) {
  for (int i = 0; i < result->pipe_index; ++i) {
    result->left_argv[i] = argv[i];
  }
  result->left_argv[result->pipe_index] = NULL;

  int index = 0;
  while (1) {
    result->right_argv[index] = argv[result->pipe_index + 1 + index];
    if (argv[result->pipe_index + 1 + index] == NULL) {
      break;
    }
    ++index;
  }
}
