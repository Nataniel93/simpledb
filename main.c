#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <operacoes.h>
#include <commands.h>
#include <utils.h>
#include <leiturajson.h>

int main(int argc, char *argv[])
{
  inicializar_tabela();

  int retorno = inserir_pessoa("{'nome':'Joao','cpf':'123456789','email':'joao@joao.com.br'}");

  if (retorno)
  {
    printf("\nPessoa inserida com sucesso!\n");
  }
  else
  {
    printf("\nFalha ao inserir pessoa\n");
  }

  imprimir_tabela();

  
  return 0;
}