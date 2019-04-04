#ifndef SCOPE_H
#define SCOPE_H

#include "map.h"
#include "type.h"

typedef struct scope {
  scope* parent;
  map* map;
} scope;

scope* new_scope(map* map);
void delete_scope(scope* s);

#endif