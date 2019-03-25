#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

typedef enum token_kind {
  OPEN_PAREN,
  CLOSE_PAREN,
  PLUS,
  MINUS,
  MULT,
  DIV,
  NUM,
  DEF,
  IF,
  IDENT,
  END
} token_kind;

char* str_token_kind(token_kind kind);

typedef struct token {
  token_kind kind;
  char* literal;
  int line;
  int col;
} token;

typedef struct token_array {
  size_t size;
  token* tokens;
} token_array;

void print_token(token token);
void delete_token_array(token_array array);

#endif