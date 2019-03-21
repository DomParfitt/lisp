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
const size_t INPUT_SIZE = 256;

int repl() {
  token_array array;
  parse_result parse_res;
  char* input = malloc(sizeof(char) * INPUT_SIZE);
  while (true) {
    printf("%s", PROMPT);
    fgets(input, INPUT_SIZE, stdin);

    if (strncmp(input, "exit", 4) == 0) {
      printf("Exiting...");
      break;
    }

    printf("%s", PROMPT);
    array = lex(input);
    parse_res = parse(array);
    if (parse_res.success) {
      type_struct result = eval(parse_res.trees[0]);
      switch (result.type) {
        case BOOL:
          printf(result.value ? "true\n" : "false\n");
          break;
        case INT:
          printf("%d\n", (int)result.value);
          break;
        case STR:
          printf("%s\n", (char*)result.value);
          break;
        default:
          printf("%d\n", (int)result.value);
          break;
      }
    } else {
      printf("%s\n", parse_res.error);
    }
  }

  free(input);
  delete_token_array(array);
  for (size_t i = 0; i < parse_res.size; i++) {
    delete_tree(parse_res.trees[i]);
  }
  return 0;
}