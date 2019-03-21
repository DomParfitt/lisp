#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

typedef struct map {
  size_t size;
  void** keys;
  void* values[];
} map;

void put(map map, void* key, void* value);
void* get(map map, void* key);

#endif