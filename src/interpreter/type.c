
#include "interpreter/type.h"

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
  // return (type_struct){type, val};
}

void print_type_struct(type_struct* t) {
  switch (t->type) {
    case BOOL:
      printf("BOOL: %s\n", t->value.b == 0 ? "false" : "true");
      break;
    case INT:
      printf("INT: %d\n", t->value.i);
      break;
    case STR:
      printf("STR: %s\n", t->value.str);
      break;
    default:
      printf("UNKNOWN: %d\n", t->value.i);
  }
}