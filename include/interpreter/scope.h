#ifndef SCOPE_H
#define SCOPE_H

#include "map.h"
#include "type.h"

typedef struct scope {
  struct scope* parent;
  map* map;
} scope;

scope* new_scope(scope* parent);
void delete_scope(scope* s);
type_struct* lookup(scope* s, char* var);

#endif