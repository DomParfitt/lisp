#include "interpreter/map.h"
#include <stdio.h>
#include <string.h>

map_entry* create_map_entry(char* key, type_struct* value) {
  map_entry* entry = malloc(sizeof(map_entry));
  char* k = malloc(sizeof(char) * 16);
  strcpy(k, key);
  entry->key = k;
  entry->value = value;
  return entry;
}

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

void put(map* map, char* key, type_struct* value) {
  print_type_struct(&value);
  for (size_t i = 0; i < map->count; i++) {
    map_entry* entry = map->entries[i];
    if (strcmp(key, entry->key) == 0) {
      entry->value = value;
      return;
    }
  }
  map->entries[map->count++] = create_map_entry(key, value);
}

type_struct* get(map* map, char* key) {
  for (size_t i = 0; i < map->count; i++) {
    map_entry* entry = map->entries[i];
    if (strcmp(key, entry->key) == 0) {
      return entry->value;
    }
  }
  return NULL;
}

void print_map(map* map) {
  printf("Map address %p\n", &map);
  printf("Map has %d entries\n", map->count);
  for (size_t i = 0; i < map->count; i++) {
    map_entry* entry = map->entries[i];
    printf("Entry #%lu\n", i);
    printf("Key: %s\n", entry->key);
    type_struct* t = entry->value;
    print_type_struct(t);
    printf("Type struct address: %p\n", &t);
  }
}