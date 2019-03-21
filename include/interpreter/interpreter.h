#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser/tree.h"
#include "type.h"

type_struct eval(tree* tree);

#endif