#include "parser/tree.h"
#include <stdlib.h>
#include <string.h>

tree* create_tree(token tok) {
  tree* t = malloc(sizeof(tree));
  t->t = tok;
  t->left = NULL;
  t->right = NULL;
  return t;
}

void delete_tree(tree* tree) {
  if (tree->left == NULL && tree->right == NULL) {
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

  delete_tree(tree);
}

char* str_tree(tree* tree) {
  char* str = malloc(sizeof(char) * 64);
  strcat(str, "(");
  strcat(str, tree->t.literal);

  if (tree->left != NULL) {
    char* left = str_tree(tree->left);
    strcat(str, left);
    free(left);
  }

  if (tree->right != NULL) {
    char* right = str_tree(tree->right);
    strcat(str, right);
    free(right);
  }
  strcat(str, ")");
  return str;
}