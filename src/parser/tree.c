#include "parser/tree.h"
#include <stdio.h>
#include <stdlib.h>

tree* create_tree(token tok) {
  tree* t = malloc(sizeof(tree));
  t->t = tok;
  t->left = NULL;
  t->right = NULL;
  t->third = NULL;
  return t;
}

void delete_tree(tree* tree) {
  if (tree->left == NULL && tree->right == NULL && tree->third == NULL) {
    free(tree);
    return;
  }

  if (tree->left != NULL) {
    delete_tree(tree->left);
    tree->left = NULL;
  }

  if (tree->right != NULL) {
    delete_tree(tree->right);
    tree->right = NULL;
  }

  if (tree->third != NULL) {
    delete_tree(tree->third);
    tree->third = NULL;
  }

  delete_tree(tree);
}

void print_tree(tree* tree) {
  printf("(%s", tree->t.literal);

  if (tree->left != NULL) {
    print_tree(tree->left);
  }

  if (tree->right != NULL) {
    print_tree(tree->right);
  }

  if (tree->third != NULL) {
    print_tree(tree->third);
  }

  printf(")");
}