#include <stdio.h>
#include <string.h>
#include <leiturajson.h>

/**
 * @brief Adiciona uma pessoa a tabela hash
 * 
 * @param data Json com os dados de Pessoa. As chaves nome, email e cpf são *Obrigatórias.
 * Nome e Email devem conter até 50 caracteres. Cpf deve ser diferente de 0.
 * @return int Retorna 1 caso consiga adicionar a pessoa ou 0 caso contrário
 */
int inserir_pessoa(char *data)
{
  int retorno = 0;
  char *arg = data;
  Pessoa pessoa =  retornarPessoaApartirDeJson(arg);

  if (pessoa.cpf != 0 && pessoa.email != NULL && pessoa.nome != NULL &&
    strcmp(pessoa.nome, "") && strcmp(pessoa.email, ""))
  {
    retorno = inserir_pessoa_tabela(pessoa);
  }

  return retorno;
}

/**
 * @brief Atualiza os dados de uma Pessoa já cadastrada
 * 
 * @param data Json com os dados de Pessoa. A chave cpf é *Obrigatória. As chaves nome, email são *Opcionais.
 * Nome e Email devem conter até 50 caracteres. Cpf deve ser diferente de 0.
 * @return int Retorna 1 caso consiga atualizar a pessoa ou 0 caso contrário
 */
int atualizar_pessoa(char *data)
{
  int retorno = 0;
  int erros = 0;
  int cpf = retornarCpfJson(data);
  char *arg = data;
  char **nomeEmail = retornarNomeEmailJson(arg);

  if (strcmp(nomeEmail[0], "") && strlen(nomeEmail[0]) > 50)
  {
    printf("\nChave nome possui tamanho inválido. Tamanho máximo de 50 caracteres. \n");
    erros++;
  }

  if (strcmp(nomeEmail[1], "") && strlen(nomeEmail[1]) > 50)
  {
    printf("\nChave email possui tamanho inválido. Tamanho máximo de 50 caracteres. \n");
    erros++;
  }

  if (cpf == 0)
  {
    printf("\nChave cpf não preenchida.\n");
    erros++;
  }

  if (erros == 0)
  {
    retorno = atualizar_pessoa_tabela(cpf, nomeEmail[0], nomeEmail[1]);
  }

  return retorno;
}