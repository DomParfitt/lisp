#include <stdbool.h>
#include <stdio.h>
#include "interpreter/scope.h"
#include "interpreter/type.h"
#include "lexer/token.h"
#include "parser/tree.h"

bool truthy(type_struct t);

bool initialised = false;
scope* scp;

void init() {
  if (!initialised) {
    scp = new_scope(NULL);
    initialised = true;
  }
}

void close() {
  delete_map(scp->map);
  // free(scp);
}

type_struct* eval(tree* tree) {
  init();
  if (tree->t.kind == IDENT) {
    if (tree->kind == BIND) {
      return new_type_struct(STR, tree->t.literal);
    }

    type_struct* val = get(scp->map, tree->t.literal);
    if (val == NULL) {
      return new_type_struct(STR, tree->t.literal);
    } else {
      return val;
    }
  }

  if (tree->t.kind == NUM) {
    return new_type_struct(INT, strtoll(tree->t.literal, NULL, 10));
  }

  if (tree->t.kind == STRING) {
    return new_type_struct(STR, tree->t.literal);
  }

  type_struct *left, *right, *third;
  if (tree->left != NULL) {
    left = eval(tree->left);
  }

  if (tree->right != NULL) {
    right = eval(tree->right);
  }

  if (tree->third != NULL) {
    third = eval(tree->third);
  }

  type_struct* t;
  switch (tree->t.kind) {
    case PLUS:
      t = new_type_struct(INT, left->value.i + right->value.i);
      break;
    case MINUS:
      t = new_type_struct(INT, left->value.i - right->value.i);
      break;
    case MULT:
      t = new_type_struct(INT, left->value.i * right->value.i);
      break;
    case DIV:
      t = new_type_struct(INT, left->value.i / right->value.i);
      break;
    case EQ:
      t = new_type_struct(BOOL, left->value.i == right->value.i);
      break;
    case GT:
      t = new_type_struct(BOOL, left->value.i > right->value.i);
      break;
    case LT:
      t = new_type_struct(BOOL, left->value.i < right->value.i);
      break;
    case GTE:
      t = new_type_struct(BOOL, left->value.i >= right->value.i);
      break;
    case LTE:
      t = new_type_struct(BOOL, left->value.i <= right->value.i);
      break;
    case DEF:
      put(scp->map, left->value.str, right);
      free(left);
      free(third);
      return right;
    case IF:
      if (truthy(*left)) {
        free(left);
        free(third);
        return right;
      } else {
        free(left);
        free(right);
        return third;
      }
    default:
      t = new_type_struct(ERR, -1);
  }

  free(left);
  free(right);
  free(third);
  return t;
}

type_struct* num_bin_op(token_kind kind, type_struct* left,
                        type_struct* right) {
  if (left->type != INT || right->type != INT) {
    return new_type_struct(ERR, -1);
  }

  switch (kind) {
    case PLUS:
      return new_type_struct(INT, left->value.i + right->value.i);
    case MINUS:
      return new_type_struct(INT, left->value.i - right->value.i);
    case MULT:
      return new_type_struct(INT, left->value.i * right->value.i);
    case DIV:
      return new_type_struct(INT, left->value.i / right->value.i);
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

type_struct* error(char* msg) { return new_type_struct(ERR, msg); }