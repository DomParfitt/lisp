
#include "interpreter/type.h"

type_struct new_type_struct(type type, void* value) {
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
  return (type_struct){type, val};
}