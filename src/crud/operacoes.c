#include <stdio.h>
#include "headers/tabelaHash.h"
#include "headers/leituraJson.h"

void insert_table(char *data) {
  Pessoa pessoa =  retornarPessoaApartirDeJson(data);
  printf("Insert Operação \n");
}