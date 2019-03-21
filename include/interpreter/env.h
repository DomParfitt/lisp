#ifndef ENV_H
#define ENV_H

#include "type.h"

typedef struct environ {
  char* binding;
  type_struct value;
} environ;

#endif