#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief 
 * 
 * @param argv Recebe os parâmetros passados via linha de comando para a main()
 * @param updating Parâmetro passado no caso de operação de update
 * @return char** Retorna um array de 2 ou 3 posições contendo strings. A 1° posição contém a 
 * sortKey passada, a 2° contém o json passado e a 3° só é retornada caso o parâmetro updating 
 * receba true, ela retorna a key passada 
 */
char **buildData(char *argv[], bool updating)
{
  char *pch;
  char *key;
  int data_size = 2;
  char arg[strlen(argv[1])];
  strncpy(arg, argv[1], strlen(argv[1]));

  pch = strtok(argv[1], "=,,");

  if (updating)
  {
    data_size = 3;
    pch = strtok(NULL, "=,,");
    key = pch;
  }

  pch = strtok(NULL, "=,,");
  char *sortKey = pch;

  //separa o JSON sem as chaves.
  pch = strtok(NULL, "=");
  char *json = pch;

  // Vetor de dados. Pode conter as chaves sort_key, value(json), key(caso a operação for --update)
  char **data = malloc(sizeof(char *) * data_size);

  // Retorna NULL em caso de não conseguir alocar o data
  if (!data) return NULL;

  data[0] = malloc(sizeof(char));
  strcpy(data[0], "");

  data[1] = malloc(sizeof(char));
  strcpy(data[1], "");

  if (sortKey != NULL && strlen(sortKey) > 0)
  {
    data[0] = realloc(data[0], strlen(sortKey) * sizeof(char));
    strncpy(data[0], sortKey, strlen(sortKey));
  }

  if (json != NULL && strlen(json) > 0)
  {
    data[1] = realloc(data[1], strlen(json) * sizeof(char));
    strncpy(data[1], json, strlen(json));
  }

  if (updating)
  {
    data[2] = malloc(sizeof(char));
    strcpy(data[2], "");

    if (key != NULL && strlen(key) > 0)
    {
      data[2] = realloc(data[2], strlen(key) * sizeof(char));
      strncpy(data[2], key, strlen(key));
    }
  }

  return data;
}