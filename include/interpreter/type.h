#ifndef TYPE_H
#define TYPE_H

typedef enum type { BOOL, INT, STR, ERR } type;

typedef struct type_struct {
  type type;
  void* value;
} type_struct;

type_struct new_type_struct(type type, void* value);

#endif