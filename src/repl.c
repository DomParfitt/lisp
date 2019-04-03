#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "interpreter/interpreter.h"
#include "interpreter/type.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/parser.h"
#include "parser/tree.h"

const char* PROMPT = "> ";
const char* EXIT = "exit";
const size_t INPUT_SIZE = 256;

int repl() {
  token_array array;
  parse_result parse_res;
  char* input = malloc(sizeof(char) * INPUT_SIZE);
  while (true) {
    printf("%s", PROMPT);
    fgets(input, INPUT_SIZE, stdin);

    if (strcmp(input, EXIT) == 0) {
      printf("Exiting...");
      break;
    }

    printf("%s", PROMPT);
    array = lex(input);
    // for (size_t i = 0; i < array.size; i++) {
    //   print_token(array.tokens[i]);
    // }
    parse_res = parse(array);
    if (parse_res.success) {
      type_struct* result = eval(parse_res.trees[0]);
      switch (result->type) {
        case BOOL:
          printf(result->value.b ? "true\n" : "false\n");
          break;
        case INT:
          printf("(int) %d\n", result->value.i);
          break;
        case STR:
          printf("(str) %s\n", result->value.str);
          break;
        default:
          printf("(unknown) %d\n", result->value.i);
          break;
      }
    } else {
      printf("%s\n", parse_res.error);
    }
    // break;
  }

  free(input);
  delete_token_array(array);
  for (size_t i = 0; i < parse_res.size; i++) {
    tree* t = parse_res.trees[i];
    print_tree(t);
    if (t != NULL) {
      delete_tree(t);
    }
  }
  return 0;
}