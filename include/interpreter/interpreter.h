#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser/tree.h"
#include "type.h"

void init();
void close();
type_struct* eval(tree* tree);

#endif