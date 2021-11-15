#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char **buildData(char *argv[], bool updating)
{
  // char str[] = "--insert=3,{'nome':'Cinderela','autor':'Pedro','CPF':1233456,'ano':1940}";
  // char str[] = "--update=1233456,3,{'nome':'Branca de Neve','autor':'Qualquer','CPF':1233456,'ano':1940}";

  char *pch;
  char *key;
  int data_size = 2;
  char arg[strlen(argv[1])];
  strncpy(arg, argv[1], strlen(argv[1]));

  pch = strtok (arg,"=,,");

  if (updating)
  {
    data_size = 3;
    pch = strtok (NULL,"=,,");
    key = pch;
    printf("key %s\n", key);
  }

  pch = strtok (NULL,"=,,");
  char *sortKey = pch;
  printf("sortKey %s\n", sortKey);

  //separa o JSON sem as chaves.
  pch = strtok (NULL,"=");
  char *json = pch;
  printf("json %s\n", json);

  // Vetor de dados. Pode conter as chaves sort_key, value(json), key(caso a operação for --update)
  char **data = malloc (sizeof (char *) * data_size);

  // Retorna NULL em caso de não conseguir alocar o data 
  if (!data) return NULL;

  // Aloca as posições dos dados
  data[0] = malloc (strlen(sortKey) + 1);
  data[1] = malloc (strlen(json) + 1);
  if (updating) data[2] = malloc (strlen(key) + 1);

  // Preencher as posições do data
  strncpy(data[0], sortKey, sizeof(data[0]));
  strncpy(data[1], json, sizeof(data[1]));
  if (updating) strncpy(data[2], key, sizeof(data[2]));

  return data;
}