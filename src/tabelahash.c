#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>
#include "../headers/tabelahash.h"

/**
 * @brief Cria uma STRUCT do tipo NO.
 * 
 */
typedef struct no
{
  Pessoa pessoa;
  struct no *proximo;
} No;

/**
 * @brief Cria uma STRUCT do tipo Lista.
 * 
 */
typedef struct
{
  No *inicio;
  int tam;
} Lista;

/**
 * @brief Vetor de ponteiros para Lista.
 * 
 */
static Lista *tabela[__HASHTABLE_LENGTH];

/**
 * @brief Número de leitores
 */
static unsigned nreaders = 0;

/**
 * @brief Semáforo para a Tabela Hash
 */
static sem_t semaphore;

void SEMAPHORE_INIT(void)
{
  assert(sem_init(&semaphore, 0, 1) == 0);
}

void SEMAPHORE_DOWN(void)
{
  assert(sem_wait(&semaphore) == 0);
}

void SEMAPHORE_UP(void)
{
  assert(sem_post(&semaphore) == 0);
}

/**
 * @brief Mutex para a Tabela Hash
 */
static pthread_mutex_t lock;

void MUTEX_INIT(void)
{
  assert(pthread_mutex_init(&lock, NULL) == 0);
}

void MUTEX_LOCK(void)
{
  assert(pthread_mutex_lock(&lock) == 0);
}

void MUTEX_UNLOCK(void)
{
  assert(pthread_mutex_unlock(&lock) == 0);
}

/**
 * @brief Bloqueia região de memória acessada pelos leitores 
 * 
 */
static void reader_enter(void)
{
  MUTEX_LOCK();
  nreaders++;
  if (nreaders == 1)
    SEMAPHORE_DOWN();
  MUTEX_UNLOCK();
}

/**
 * @brief Libera região de memória acessada pelos leitores 
 * 
 */
static void reader_leave(void)
{
  MUTEX_LOCK();
  nreaders--;
  if (nreaders == 0)
    SEMAPHORE_UP();
  MUTEX_UNLOCK();
}

/**
 * @brief Imprime na tela os dados de uma pessoa.
 * 
 * @param p Representa uma variável do tipo pessoa.
 */
void imprimir_pessoa(Pessoa p)
{
  printf("\tNome: %s\tCPF: %ld\tEmail: %s\n", p.nome, p.cpf, p.email);
}

/**
 * @brief Cria uma lista vazia e retorna seu endereço na memória
 * 
 * @return Lista* 
 */
Lista *criar_lista()
{
  Lista *l = malloc(sizeof(Lista));
  l->inicio = NULL;
  l->tam = 0;
  return l;
}

/**
 * @brief 
 * 
 * @param p Representa uma nova pessoa a ser inserida na lista.
 * @param lista Endereço de uma lista encadeada
 */
int insercao_dados_lista(Pessoa p, Lista *lista)
{
  int retorno = -1;
  No *no = malloc(sizeof(No));
  no->pessoa = p;
  no->proximo = lista->inicio;
  lista->inicio = no;
  lista->tam++;

  if (no != NULL) retorno = 0;

  return (retorno);
}

/**
 * @brief Buscar um nó na lista.
 * 
 * @param cpf CPF da pessoa a ser procurada na tabela.
 * @param inicio Nó de início da Lista
 * @return No* Retorna null se o cpf não for encontrado.
 */
No *buscar_no(long cpf, No *inicio)
{
  while (inicio != NULL)
  {
    if (inicio->pessoa.cpf == cpf)
      return inicio;
    else
      inicio = inicio->proximo;
  }

  return NULL;
}

/**
 * @brief Impressão completa da lista
 * 
 * @param inicio 
 */
void imprimir_lista(No *inicio)
{
  while (inicio != NULL)
  {
    imprimir_pessoa(inicio->pessoa);
    inicio = inicio->proximo;
  }
}

/**
 * @brief Inicializa a tabela com uma lista vazia em cada posição do vetor
 * 
 */
void inicializar_tabela()
{
  int i;
  nreaders = 0;
  MUTEX_INIT();
  SEMAPHORE_INIT();
  for (i = 0; i < __HASHTABLE_LENGTH; i++)
    tabela[i] = criar_lista();
}

/**
 * @brief Função de conversão hash.
 * 
 * @param cpf Representa o cpf da pessoa.
 * @return int 
 */
int funcao_espalhamento(long cpf)
{
  return cpf % __HASHTABLE_LENGTH;
}

/**
 * @brief Cria uma nova pessoa e insere os dados na tabela.
 * 
 */
int inserir_pessoa_tabela(Pessoa pes)
{
  int retorno = -1;
  int indice = funcao_espalhamento(pes.cpf);

  SEMAPHORE_DOWN();

    retorno = insercao_dados_lista(pes, tabela[indice]);

  SEMAPHORE_UP();

  return (retorno);
}

/**
 * @brief Busca uma pessoa na tabela.
 * 
 * @param cpf CPF da pessoa a ser buscada.
 * @return Pessoa* 
 */
Pessoa *buscar_pessoa_tabela(long cpf)
{
  int indice = funcao_espalhamento(cpf);

  reader_enter();

    No *no = buscar_no(cpf, tabela[indice]->inicio);

  reader_leave();

  if (no)
    return &no->pessoa;
  else
    return NULL;
}

int atualizar_pessoa_tabela(long cpf, const char *nome, const char *email)
{
  int retorno = -1;
  Pessoa *pessoa;

  SEMAPHORE_DOWN();

    pessoa = buscar_pessoa_tabela(cpf);

    if (pessoa != NULL)
    {
      if (nome != NULL && strlen(nome) > 0 && strlen(nome) <= 50)
      {
        strncpy(pessoa->nome, nome, strlen(nome));
      }

      if (email != NULL && strlen(email) > 0 && strlen(email) <= 50)
      {
        strncpy(pessoa->email, email, strlen(email));
      }

      retorno = 0;
    }

  SEMAPHORE_UP();

  return (retorno);
}

No *fim_lista(No *inicio, int tamanho)
{
  No *ultimo;

  for (int i = 0; i < tamanho; i++)
  {
    ultimo = inicio->proximo;
  }

  return ultimo;
}

int remover_pessoa_tabela(long cpf)
{
  int retorno = -1;
  int achou;
  int indice = funcao_espalhamento(cpf);
  No *no_pessoa;
  No *aux;
  No *anterior;
  Lista *li = tabela[indice];
  
  reader_enter();

    No *fim = fim_lista(li->inicio, li->tam);

  reader_leave();

  SEMAPHORE_DOWN();

    no_pessoa = buscar_no(cpf, li->inicio);
    
    if (no_pessoa != NULL)
    {
      aux = li->inicio;
      anterior = NULL;
      achou = 0;

      do
      {
        if (aux->pessoa.cpf == cpf)
        {
          achou = achou + 1;

          if (aux == li->inicio)
          {
            li->inicio = aux->proximo;
            free(aux);
            aux = li->inicio;
          }
          else if (aux == fim)
          {
            anterior->proximo = NULL;
            fim = anterior;
            free(aux);
            aux = NULL;
          }
          else
          {
            anterior->proximo = aux->proximo;
            free(aux);
            aux = anterior->proximo;
          }
        }
        else
        {
          anterior = aux;
          aux = aux->proximo;
        }
      } while (aux != NULL);

      if (achou != 0) retorno = 0;
    }

  SEMAPHORE_UP();

  return (retorno);
}

/**
 * @brief Impressão da tabela hash.
 * 
 */
void imprimir_tabela()
{
  int i;
  printf("\n---------------------TABELA-------------------------\n");
  for (i = 0; i < __HASHTABLE_LENGTH; i++)
  {
    printf("%d Lista tamanho: %d\n", i, tabela[i]->tam);
    imprimir_lista(tabela[i]->inicio);
  }
  printf("---------------------FIM TABELA-----------------------\n");
}
