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
  parse_result* parse_res;
  char* input = malloc(sizeof(char) * INPUT_SIZE);
  init();
  while (true) {
    printf("%s", PROMPT);
    fgets(input, INPUT_SIZE, stdin);

    if (strcmp(input, EXIT) == 0) {
      printf("Exiting...");
      break;
    }

    printf("%s", PROMPT);
    array = lex(input);
    parse_res = parse(array);
    if (parse_res->success) {
      type_struct* result = eval(parse_res->trees[0]);
      print_type_struct(result);
      free(result);
    } else {
      printf("%s\n", parse_res->error);
    }

    break;
  }

  free(input);
  delete_token_array(array);
  for (size_t i = 0; i < parse_res->size; i++) {
    tree* t = parse_res->trees[i];
    // print_tree(t);
    if (t != NULL) {
      delete_tree(t);
    }
  }
  free(parse_res);
  return 0;
}