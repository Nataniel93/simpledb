#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <operacoes.h>
#include <commands.h>
#include <utils.h>
#include <leiturajson.h>
#include <assert.h>

static void validaOperacao(int operacao, char tipo[])
{

  if (operacao && operacao != NULL)
  {
    printf("Operação de %s efetuado com sucesso!\n", tipo);
  }
  else
  {
    printf("Falha na operação de %s\n", tipo);
  }
}

static void exclusao(int operacao, char tipo[])
{

  if (!operacao)
  {
    printf("Operação de %s efetuado com sucesso!\n", tipo);
  }
  else
  {
    printf("Falha na operação de %s\n", tipo);
  }
}

static void *worker1(void *arg)
{
  ((void)arg);

  fprintf(stdout, "thread 1 running...\n");

  /**
   * Teste Inserção
   */
  int insercao;
  insercao = inserir_pessoa("{'nome':'Joao','cpf':'111111111','email':'joao@joao.com.br'}");
  validaOperacao(insercao, "insercao");
  insercao = inserir_pessoa("{'nome':'Ricardo','cpf':'222222222','email':'ricardo@ricardo.com.br'}");
  validaOperacao(insercao, "insercao");
  insercao = inserir_pessoa("{'nome':'Maria','cpf':'333333333','email':'maria@maria.com.br'}");
  validaOperacao(insercao, "insercao");
  insercao = inserir_pessoa("{'nome':'Jose','cpf':'444444444','email':'jose@jose.com.br'}");
  validaOperacao(insercao, "insercao");
  insercao = inserir_pessoa("{'nome':'Jaqueline','cpf':'555555555','email':'jaqueline@jaqueline.com.br'}");
  validaOperacao(insercao, "insercao");

  /**
   * Teste Atualização
   */
  int atualizacao;
  atualizacao = atualizar_pessoa("{'nome':'Icaro','cpf':'111111111', 'email':'icaro@icaro.com.br'}");
  validaOperacao(atualizacao, "atualizacao");
  atualizacao = atualizar_pessoa("{'nome':'Nataniel','cpf':'222222222', 'email':'nataniel@nataniel.com.br'}");
  validaOperacao(atualizacao, "atualizacao");
  atualizacao = atualizar_pessoa("{'nome':'Helen','cpf':'444444444', 'email':'helen@helen.com.br'}");
  validaOperacao(atualizacao, "atualizacao");


    /**
   * Teste Busca
   */
    Pessoa *pessoa = buscar_pessoa(333333333);
    printf("\nResultado da busca\n");
    imprimir_pessoa(*pessoa);
    printf("\n");
    validaOperacao(pessoa, "pesquisa");

  fprintf(stdout, "thread 1 exiting...\n");

  return (NULL);
}

static void *worker2(void *arg)
{
  ((void)arg);

  fprintf(stdout, "thread 2 running...\n"); 

  /**
   * Teste Exclusão
   */
  int retorno;
  long cpf = 555555555;
  retorno = remover_pessoa(cpf);
  exclusao(retorno, "remocao");

  cpf = 333333333;
  retorno = remover_pessoa(cpf);
  exclusao(retorno, "remocao");

  fprintf(stdout, "thread 2 exiting...\n");

  return (NULL);
}

int main(int argc, char *argv[])
{

  pthread_t workers[2];

  fprintf(stdout, "initializing...\n");

  inicializar_tabela();

  /* Launch threads. */
  assert(pthread_create(&workers[0], NULL, worker1, NULL) == 0);
  assert(pthread_create(&workers[1], NULL, worker2, NULL) == 0);

  /* Wait for threads to terminate. */
  assert(pthread_join(workers[0], NULL) == 0);
  assert(pthread_join(workers[1], NULL) == 0);

  imprimir_tabela();
  fprintf(stdout, "shutting down...\n");

  return (EXIT_SUCCESS);
}