#include <stdio.h> 
#include <stdbool.h>
#include <string.h>

bool compareTo(char *argv[], char *op) {
  char *operation;
  bool response = false;
  char arg[strlen(argv[1])];

  strncpy(arg, argv[1], strlen(argv[1]));

  operation = strtok(arg,"=");
  if (strcmp(operation, op)) response = true;

  return !response;
}

/**
 * Verifica se a operação é do tipo "--insert"
 * @param *argv[], parâmetro passado na cli 
 * @return bool, resultado da comparação
 */
bool insert_op(char *argv[]) {
 return compareTo(argv, "--insert");
}

/**
 * Verifica se a operação é do tipo "--remove"
 * @param *argv[], parâmetro passado na cli 
 * @return bool, resultado da comparação
 */
bool remove_op(char *argv[]) {
 return compareTo(argv, "--remove");
}

/**
 * Verifica se a operação é do tipo "--search"
 * @param *argv[], parâmetro passado na cli 
 * @return bool, resultado da comparação
 */
bool search_op(char *argv[]) {
 return compareTo(argv, "--search");
}

/**
 * Verifica se a operação é do tipo "--update"
 * @param *argv[], parâmetro passado na cli 
 * @return bool, resultado da comparação
 */
bool update_op(char *argv[]) {
 return compareTo(argv, "--update");
}

/**
 * Verifica se a operação é do tipo "--list"
 * @param *argv[], parâmetro passado na cli 
 * @return bool, resultado da comparação
 */
bool list_op(char *argv[]) {
 return compareTo(argv, "--list");
}

