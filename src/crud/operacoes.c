#include <stdio.h>
#include "../../headers/leiturajson.h"

void insert_table(char *data) {
  Pessoa pessoa =  retornarPessoaApartirDeJson(data);
  printf("Insert Operação \n");
}