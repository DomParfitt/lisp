#include <stdbool.h>
#include <stdio.h>
#include "interpreter/env.h"
#include "interpreter/type.h"
#include "lexer/token.h"
#include "parser/tree.h"

bool truthy(type_struct t);

bool first = true;
environ env;

void init() {
  env = (environ){create_map(10)};
  first = false;
}

type_struct* eval(tree* tree) {
  if (first) {
    init();
  }

  // TODO: This needs to diff between writing to and reading from an identifier
  if (tree->t.kind == IDENT) {
    if (tree->kind == BIND) {
      return new_type_struct(STR, tree->t.literal);
    }

    type_struct* val = get(env.map, tree->t.literal);
    if (val == NULL) {
      return new_type_struct(STR, tree->t.literal);
    } else {
      print_type_struct(val);
      return val;
    }
  }

  if (tree->t.kind == NUM) {
    return new_type_struct(INT, strtoll(tree->t.literal, NULL, 10));
  }

  type_struct *left, *right;
  if (tree->left != NULL) {
    left = eval(tree->left);
  }

  if (tree->right != NULL) {
    right = eval(tree->right);
  }

  switch (tree->t.kind) {
    case PLUS:
      return new_type_struct(INT, left->value.i + right->value.i);
    case MINUS:
      return new_type_struct(INT, left->value.i - right->value.i);
    case MULT:
      return new_type_struct(INT, left->value.i * right->value.i);
    case DIV:
      return new_type_struct(INT, left->value.i / right->value.i);
    case DEF:
      put(env.map, left->value.str, right);
      return right;
    case IF:
      if (truthy(*left)) {
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