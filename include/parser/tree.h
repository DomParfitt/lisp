#ifndef TREE_H
#define TREE_H

#include "lexer/token.h"

typedef enum node_kind { OP, VALUE } node_kind;

typedef struct tree {
  // node_kind kind;
  token t;
  struct tree* left;
  struct tree* right;
} tree;

tree* create_tree(token t);
void delete_tree(tree* tree);
char* str_tree(tree* tree);

#endif