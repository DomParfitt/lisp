
#include "interpreter/type.h"
#include <stdio.h>
#include <stdlib.h>

type_struct* new_type_struct(type type, void* value) {
  type_val val;
  switch (type) {
    case BOOL:
      val.b = (bool)value;
      break;
    case INT:
      val.i = (int)value;
      break;
    case STR:
      val.str = (char*)value;
      break;
    default:
      val.i = (int)value;
      break;
  }
  type_struct* ts = malloc(sizeof(type_struct));
  ts->type = type;
  ts->value = val;
  return ts;
}

void print_type_struct(type_struct* t) {
  switch (t->type) {
    case BOOL:
      printf("%s (bool)\n", t->value.b == 0 ? "false" : "true");
      break;
    case INT:
      printf("%d (int)\n", t->value.i);
      break;
    case STR:
      printf("\"%s\" (str)\n", t->value.str);
      break;
    default:
      printf("%d (unknown)\n", t->value.i);
  }
}