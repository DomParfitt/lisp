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
    case IF:
      return "IF";
    case IDENT:
      return "IDENT";
    case END:
      return "END";
    default:
      return "UNKNOWN";
  }
};

void print_token(token token) {
  printf("[%s: '%s' @ (%d, %d)]\n", str_token_kind(token.kind), token.literal,
         token.line, token.col);
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