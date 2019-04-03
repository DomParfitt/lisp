#ifndef TYPE_H
#define TYPE_H

#include <stdbool.h>

typedef enum type { BOOL, INT, STR, ERR } type;

typedef union type_val {
  bool b;
  int i;
  char* str;
} type_val;

typedef struct type_struct {
  type type;
  type_val value;
} type_struct;

type_struct* new_type_struct(type type, void* value);
void print_type_struct(type_struct* t);

#endif