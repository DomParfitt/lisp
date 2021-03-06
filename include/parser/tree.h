#ifndef TREE_H
#define TREE_H

#include "lexer/token.h"

typedef enum node_kind { BIND, CALL } node_kind;

typedef struct tree {
  node_kind kind;
  token t;
  struct tree* left;
  struct tree* right;
  struct tree* third;
} tree;

tree* create_tree(token t);
void delete_tree(tree* tree);
void print_tree(tree* tree);

#endif