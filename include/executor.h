#ifndef EXECUTOR_HEADER
#define EXECUTOR_HEADER

#include "parser.h"

void Execute(const ParseResult* parse_result, char* const* argv);
void ExecutePipe(const ParseResult* parse_result);
void ExecuteNormal(const ParseResult* parse_result, char* const* argv);

#endif  // EXECUTOR_HEADER
