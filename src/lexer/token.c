#include "lexer/token.h"
#include <stdio.h>
#include <stdlib.h>

char* str_token_kind(token_kind kind) {
  switch (kind) {
    case OPEN_PAREN:
      return "OPEN_PAREN";
    case CLOSE_PAREN:
      return "CLOSE_PAREN";
    case PLUS:
      return "PLUS";
    case MINUS:
      return "MINUS";
    case MULT:
      return "MULT";
    case DIV:
      return "DIV";
    case NUM:
      return "NUM";
    case DEF:
      return "DEF";
    case IDENT:
      return "IDENT";
    case END:
      return "END";
    default:
      return "UNKNOWN";
  }
};

char* str_token(token token) {
  char* str = malloc(sizeof(char) * 64);
  sprintf(str, "[%s: '%s' @ (%d, %d)]", str_token_kind(token.kind),
          token.literal, token.line, token.col);
  return str;
}

void delete_token_array(token_array array) {
  for (size_t i = 0; i < array.size; i++) {
    token t = array.tokens[i];
    if (t.kind != END) {
      free(t.literal);
    }
  }
  free(array.tokens);
}