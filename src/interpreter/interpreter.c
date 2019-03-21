#include "interpreter/env.h"
#include "interpreter/type.h"
#include "lexer/token.h"
#include "parser/tree.h"

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
      return new_type_struct(INT, (int)left.value + (int)right.value);
    case MINUS:
      return new_type_struct(INT, (int)left.value - (int)right.value);
    case MULT:
      return new_type_struct(INT, (int)left.value * (int)right.value);
    case DIV:
      return new_type_struct(INT, (int)left.value / (int)right.value);
    case DEF:
      env.binding = (char*)left.value;
      env.value = right;
      return new_type_struct(right.type, right.value);
    default:
      return new_type_struct(ERR, -1);
  }
}