
#include "interpreter/type.h"

type_struct new_type_struct(type type, void* value) {
  return (type_struct){type, value};
}