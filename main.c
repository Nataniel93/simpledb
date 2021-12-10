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

  int insercao = inserir_pessoa("{'nome':'joao','cpf':'123456789','email':'joao@joao.com.br'}");

  if (insercao)
  {
    printf("\nPessoa inserida com sucesso!\n");
  }
  else
  {
    printf("\nFalha ao inserir pessoa\n");
  }

  imprimir_tabela();
  
  int atualizacao = atualizar_pessoa("{'nome':'Ícaro','cpf':'123456789', 'email':'icaro@icaro.com.br'}");

  if (atualizacao)
  {
    printf("\nPessoa atualizada com sucesso!\n");
  }
  else
  {
    printf("\nFalha ao atualizar pessoa\n");
  }

  imprimir_tabela();

  return 0;
}