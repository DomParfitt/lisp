#include "interpreter/scope.h"
#include <stdlib.h>

scope* new_scope(scope* parent) {
  scope* s = malloc(sizeof(scope));
  s->parent = parent;
  s->map = create_map(10);
}

delete_scope(scope* s) {
  delete_map(s->map);
  free(s);
}

type_struct* lookup(scope* s, char* var) {
  type_struct* val = get(s->map, var);

  if (s->parent == NULL) {
    return val;
  }

  if (val != NULL) {
    return val;
  }

  return lookup(s->parent, var);
}