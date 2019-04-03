#include "parser/parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer/token.h"
#include "parser/tree.h"

// Grammar functions
tree* exprs(token_array* tokens);
tree* expr(token_array* tokens);
tree* expr_val(token_array* tokens);
tree* operation(token_array* tokens);
tree* bind(token_array* tokens);
tree* if_expr(token_array* tokens);
tree* op(token_array* tokens);
tree* value(token_array* tokens);
tree* identifer(token_array* tokens);

// Helper functions
token current(token_array* tokens);
token peek(token_array* tokens);
bool expect(token_array* tokens, token_kind kind);

// Token pointer
int tp = 0;
char err[256];

parse_result parse(token_array tokens) {
  tp = 0;

  tree* trees[10];
  bool success = true;

  size_t count = 0;
  token t = peek(&tokens);
  while (t.kind != END) {
    tree* tree = exprs(&tokens);
    if (tree == NULL) {
      success = false;
      break;
    }
    trees[count++] = tree;
    t = peek(&tokens);
  }

  return (parse_result){success, trees, count, err};
}

tree* exprs(token_array* tokens) {
  if (!expect(tokens, OPEN_PAREN)) {
    return value(tokens);
  }

  tree* t = expr(tokens);
  if (t == NULL) {
    return NULL;
  }

  if (!expect(tokens, CLOSE_PAREN)) {
    return NULL;
  }

  return t;
}

tree* expr(token_array* tokens) {
  tree* t = value(tokens);
  if (t != NULL) {
    return t;
  }

  t = operation(tokens);
  if (t != NULL) {
    return t;
  }

  t = identifer(tokens);
  if (t != NULL) {
    return t;
  }

  t = bind(tokens);
  if (t != NULL) {
    return t;
  }

  t = if_expr(tokens);
  if (t != NULL) {
    return t;
  }

  t = exprs(tokens);

  return t;
}

tree* operation(token_array* tokens) {
  tree* t = op(tokens);
  if (t != NULL) {
    tree* left = expr(tokens);
    if (left == NULL) {
      return NULL;
    }
    t->left = left;

    tree* right = expr(tokens);
    if (right == NULL) {
      return NULL;
    }
    t->right = right;
    return t;
  }
  return NULL;
}

tree* bind(token_array* tokens) {
  token token = peek(tokens);
  if (token.kind != DEF) {
    return NULL;
  }
  tree* t = create_tree(current(tokens));

  tree* left = identifer(tokens);
  if (left == NULL) {
    return NULL;
  }
  left->kind = BIND;

  tree* right = exprs(tokens);
  if (right == NULL) {
    return NULL;
  }

  t->left = left;
  t->right = right;
  return t;
}

tree* if_expr(token_array* tokens) {
  token token = peek(tokens);
  if (token.kind != IF) {
    return NULL;
  }
  tree* t = create_tree(current(tokens));

  tree* left = exprs(tokens);
  if (left == NULL) {
    return NULL;
  }

  tree* right = exprs(tokens);
  if (right == NULL) {
    return NULL;
  }

  tree* third = exprs(tokens);
  if (third == NULL) {
    return NULL;
  }
  t->left = left;
  t->right = right;
  t->third = third;
  return t;
}

tree* op(token_array* tokens) {
  token token = peek(tokens);
  if (token.kind == PLUS || token.kind == MINUS || token.kind == MULT ||
      token.kind == DIV) {
    return create_tree(current(tokens));
  } else {
    return NULL;
  }
}

tree* value(token_array* tokens) {
  token token = peek(tokens);
  if (token.kind == NUM) {
    return create_tree(current(tokens));
  }
  return NULL;
}

tree* identifer(token_array* tokens) {
  token token = peek(tokens);
  if (token.kind == IDENT) {
    return create_tree(current(tokens));
  } else {
    return NULL;
  }
}

// Helper functions

token current(token_array* tokens) { return tokens->tokens[tp++]; }

token peek(token_array* tokens) { return tokens->tokens[tp]; }

bool expect(token_array* tokens, token_kind kind) {
  token token = peek(tokens);
  if (token.kind != kind) {
    sprintf(err, "Unexpected '%s' at line: %d, col: %d", token.literal,
            token.line, token.col);
    return false;
  }

  current(tokens);
  return true;
}

// token* expect_t(token_array* tokens, token_kind kind) {
//   token token = peek(tokens);
//   if (token.kind != kind) {
//     sprintf(err, "Unexpected '%s' at line: %d, col: %d", token.literal,
//             token.line, token.col);
//     return NULL;
//   }

//   token = current(tokens);
//   return &token;
// }
