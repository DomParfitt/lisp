#include <stdbool.h>
#include "interpreter/env.h"
#include "interpreter/type.h"
#include "lexer/token.h"
#include "parser/tree.h"

bool truthy(type_struct t);

environ env;

type_struct eval(tree* tree) {
  env = (environ){malloc(sizeof(char) * 256), 0};

  if (tree->t.kind == IDENT) {
    return new_type_struct(STR, tree->t.literal);
  }

  if (tree->t.kind == NUM) {
    return new_type_struct(INT, strtoll(tree->t.literal, NULL, 10));
  }

  type_struct left, right;
  if (tree->left != NULL) {
    left = eval(tree->left);
  }

  if (tree->right != NULL) {
    right = eval(tree->right);
  }

  switch (tree->t.kind) {
    case PLUS:
      return new_type_struct(INT, left.value.i + right.value.i);
    case MINUS:
      return new_type_struct(INT, left.value.i - right.value.i);
    case MULT:
      return new_type_struct(INT, left.value.i * right.value.i);
    case DIV:
      return new_type_struct(INT, left.value.i / right.value.i);
    case DEF:
      env.binding = left.value.str;
      env.value = right;
      return right;
    case IF:
      if (truthy(left)) {
        return right;
      } else {
        return eval(tree->third);
      }
    default:
      return new_type_struct(ERR, -1);
  }
}

bool truthy(type_struct t) {
  switch (t.type) {
    case BOOL:
      return t.value.b;
    case INT:
      return t.value.i != 0;
    default:
      return false;
  }
}