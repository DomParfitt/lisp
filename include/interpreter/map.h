#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include "type.h"

typedef struct map_entry {
  char* key;
  type_struct value;
} map_entry;

typedef struct map {
  size_t size;
  size_t count;
  map_entry entries[];
} map;

map* create_map(size_t size);
void delete_map(map* map);
void put(map map, char* key, type_struct value);
type_struct* get(map map, char* key);

#endif