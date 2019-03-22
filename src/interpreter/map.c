#include "interpreter/map.h"
#include <stdio.h>
#include <string.h>

map* create_map(size_t size) {
  map* map = malloc(sizeof(map));
  map->size = size;
  map->count = 0;
  map->entries[size];
  return map;
}

void delete_map(map* map) {
  free(map->entries);
  free(map);
}

void put(map map, char* key, type_struct value) {
  for (size_t i = 0; i < map.count; i++) {
    map_entry entry = map.entries[i];
    if (strcmp(key, entry.key) == 0) {
      entry.value = value;
      return;
    }
  }
  map.entries[map.count++] = (map_entry){key, value};
}

type_struct* get(map map, char* key) {
  for (size_t i = 0; i < map.count; i++) {
    map_entry entry = map.entries[i];
    if (strcmp(key, entry.key) == 0) {
      return &entry.value;
    }
  }
  return NULL;
}
