#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer/token.h"

bool whitespace(char c);
bool digit(char c);
bool alpha(char c);
bool quote(char c);
token* keyword(char* str);
token identifier(char* str, size_t* idx);
token num(char* str, size_t* idx);
token strng(char* str, size_t* idx);
char* substr(char* str, size_t from, size_t len);

int line = 0;
int col = 0;

token_array lex(char* str) {
  line = 0;
  col = 0;

  token* tokens = malloc(sizeof(token) * strlen(str) + 1);
  int count = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    if (whitespace(str[i])) {
      continue;
    }

    if (digit(str[i])) {
      tokens[count++] = num(str, &i);
      continue;
    }

    if (alpha(str[i])) {
      tokens[count++] = identifier(str, &i);
      continue;
    }

    if (quote(str[i])) {
      tokens[count++] = strng(str, &i);
      continue;
    }

    // token t;
    token_kind kind;
    char* c = substr(str, i, 1);
    switch (*c) {
      case '(':
        kind = OPEN_PAREN;
        break;
      case ')':
        kind = CLOSE_PAREN;
        break;
      case '+':
        kind = PLUS;
        break;
      case '-':
        kind = MINUS;
        break;
      case '*':
        kind = MULT;
        break;
      case '/':
        kind = DIV;
        break;
      case '=':
        kind = EQ;
        break;
      case '>':
        kind = GT;
        break;
      case '<':
        kind = LT;
        break;
      default:
        continue;
    }

    tokens[count++] = (token){kind, c, line, col++};
  }
  tokens[count++] = (token){END, "END", 0, strlen(str)};
  return (token_array){count, tokens};
}

bool whitespace(char c) {
  switch (c) {
    case ' ':
    case '\t':
      return true;
    case '\n':
    case '\r':
      line++;
      col = 0;
      return true;
    default:
      return false;
  }
}

token num(char* str, size_t* idx) {
  size_t start = *idx;
  while (digit(str[*idx])) {
    (*idx)++;
  }
  size_t len = ((*idx)--) - start;
  return (token){NUM, substr(str, start, len), line, col++};
}

token identifier(char* str, size_t* idx) {
  size_t start = *idx;
  while (alpha(str[*idx])) {
    (*idx)++;
  }
  size_t len = ((*idx)--) - start;

  char* ident = substr(str, start, len);

  token* key;
  if ((key = keyword(ident)) != NULL) {
    return *key;
  }

  return (token){IDENT, ident, line, col++};
}

token strng(char* str, size_t* idx) {
  size_t start = ++(*idx);
  while (!quote(str[*idx])) {
    (*idx)++;
  }
  size_t len = ((*idx)--) - start;
  (*idx)++;
  return (token){STRING, substr(str, start, len), line, col++};
}

token* keyword(char* str) {
  if (strcmp(str, "def") == 0) {
    return &(token){DEF, str, line, col++};
  }

  if (strcmp(str, "if") == 0) {
    return &(token){IF, str, line, col++};
  }

  return NULL;
}

bool digit(char c) { return c >= 48 && c <= 57; }

bool alpha(char c) { return (c >= 65 && c <= 90) || (c >= 97 && c <= 122); }

bool quote(char c) { return c == 34; }

char* substr(char* str, size_t from, size_t len) {
  char* c = malloc(sizeof(char) * len);
  strncpy(c, &str[from], len);
  return c;
}
