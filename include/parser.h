#ifndef PARSER_HEADER
#define PARSER_HEADER

#include "constants.h"

typedef struct {
  char* left_argv[MAXARGSIZE];
  char* right_argv[MAXARGSIZE];
  int redirect_index;
  int pipe_index;
  int error;
} ParseResult;

char** Tokenize(char** argv, char* buf);
ParseResult ParsePrompt(char** buf);
ParseResult ParseArgv(char** argv);
ParseResult NewParseResult();
void CreatBothSideArgv(ParseResult* result, char** argv);

#endif  // PARSER_HEADER
