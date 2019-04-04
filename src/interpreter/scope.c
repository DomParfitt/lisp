#include "scope.h"
#include <stdlib.h>

scope* new_scope(map* map) {
  scope* s = malloc(sizeof(scope));
  s->parent = NULL;
  s->map = map;
}

delete_scope(scope* s) {
  delete_map(s->map);
  free(s);
}