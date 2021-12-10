#include <stdio.h>
#include <string.h>
#include <leiturajson.h>

/**
 * @brief Adiciona uma pessoa a tabela hash
 * 
 * @param data Recebe o json necessário para adicionar uma pessoa. A estrutura deve conter nome, cpf e email
 * @return int Retorna 1 caso consiga adicionar a pessoa ou 0 caso contrário
 */
int inserir_pessoa(char *data)
{
  int retorno = 0;
  char *arg = data;
  Pessoa pessoa =  retornarPessoaApartirDeJson(arg);

  retorno = inserir_pessoa_tabela(pessoa);

  return retorno;
}

int remover_pessoa(char *data)
{
  int retorno = 0;
  char *arg = data;

  retorno = remover_pessoa_tabela(arg);

  return retorno;
}