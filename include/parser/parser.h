#include <stdbool.h>
#include "lexer/token.h"
#include "tree.h"

typedef struct parse_result {
  bool success;
  tree** trees;
  size_t size;
  char* error;
} parse_result;

parse_result parse(token_array tokens);