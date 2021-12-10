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
  // char str[] = "--insert=3,{'nome':'Cinderela','autor':'Pedro','CPF':1233456,'ano':1940}";
  // char str[] = "--update=1233456,3,{'nome':'Branca de Neve','autor':'Qualquer','CPF':1233456,'ano':1940}";
  printf("\nbuildData\n");
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
  if (!data)
    return NULL;

  // Aloca as posições dos dados
  data[0] = malloc(strlen(sortKey) + 1);
  data[1] = malloc(strlen(json) + 1);
  if (updating)
  {
    data[2] = malloc(strlen(key) + 1);
  }

  // Preencher as posições do data
  strcpy(data[0], sortKey);
  strcpy(data[1], json);

  if (updating)
  {
    strncpy(data[2], key, sizeof(data[2]));
  }

  return data;
}