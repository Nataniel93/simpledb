#include <stdio.h>
#include <string.h>
#include "../../headers/leiturajson.h"

void inserir_pessoa(char *data) {

  char *arg = data;

  Pessoa pessoa =  retornarPessoaApartirDeJson(arg);

  inicializar_tabela();
  inserir_pessoa_tabela(pessoa);
  imprimir_tabela();

  printf("Insert Operação \n");
}