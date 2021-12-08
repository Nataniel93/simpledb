#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

/**
 * @brief Representa o tamanho da tabela hash.
 * 
 */
#define M 1024

/**
 * @brief Current Number of Readers
 */
static unsigned nreaders = 0;

/**
 * @brief Semaphore for Hashtable
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
 * @brief Mutex for Hashtable
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

static void reader_enter(void)
{
    MUTEX_LOCK();
    nreaders++;
    if (nreaders == 1)
        SEMAPHORE_DOWN();
    MUTEX_UNLOCK();
}

static void reader_leave(void)
{
    MUTEX_LOCK();
    nreaders--;
    if (nreaders == 0)
        SEMAPHORE_UP();
    MUTEX_UNLOCK();
}

/**
 * @brief Cria uma STRUCT para armazenar os dados de uma "pessoa" em um tipo pessoa.
 * 
 */
typedef struct
{
    long unsigned cpf;
    char nome[50];
    char email[50];
} Pessoa;

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
static Lista *tabela[M];

/**
 * @brief Insere os dados de uma pessoa na tabela hash.
 * 
 * @return Pessoa 
 */

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

    if (no != NULL)
        retorno = 0;

    return (retorno);
}

/**
 * @brief Buscar um elemento na lista.
 * 
 * @param cpf CPF da pessoa a ser procurada na tabela.
 * @param inicio 
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
void inicializar()
{
    int i;
    nreaders = 0;
    MUTEX_INIT();
    SEMAPHORE_INIT();
    for (i = 0; i < M; i++)
        tabela[i] = criar_Lista();
}

/**
 * @brief Função de conversão hash.
 * 
 * @param cpf Representa o cpf da pessoa.
 * @return int 
 */
int funcao_espalhamento(long cpf)
{
    return cpf % M;
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

int atualizar_pessoa(unsigned cpf, const char *nome, const char *email)
{
    int retorno = -1;
    Pessoa *pessoa;

    SEMAPHORE_DOWN();
    pessoa = buscar_pessoa_tabela(cpf);

    if (pessoa == NULL)
        return retorno;

    if ((nome != NULL) && (strlen(strtrim(nome)) > 0 && strlen(strtrim(nome)) <= 50))
    {
        strncpy(pessoa->nome, nome, strlen(nome));
    }

    if ((email != NULL) && (strlen(strtrim(email)) > 0 && strlen(strtrim(email)) <= 50))
    {
        strncpy(pessoa->email, email, strlen(email));
    }

    retorno = 0;

    SEMAPHORE_UP();

    return (retorno);
}

No *fim_lista(No *inicio, int tamanho){
    No *ultimo;
    int i = 0;

    while(i < tamanho){
        ultimo = inicio->proximo;
    }

    return ultimo;
}

int remover_pessoa(unsigned cpf)
{
    int retorno = -1;
    int achou;
    No *no_pessoa;

    No *aux;
    No *anterior;

    int indice = funcao_espalhamento(cpf);

    Lista *li = tabela[indice];
    reader_enter();

    No *fim = fim_lista(li->inicio, li->tam);

    reader_leave();

    SEMAPHORE_DOWN();
    no_pessoa = buscar_no(cpf, li->inicio);
    if (no_pessoa == NULL) return retorno;

     /*utilizando o ponteiro aux,  fazemos com ele aponte para o mesmo endereço que inicio aponta*/
        aux = li->inicio;
        /*utilizando o ponteiro ele,  fazemos com ele aponte para NULL*/
        anterior = NULL;
        achou = 0;
        do{
            /*caso aux-> num seja igual ao número a ser removido*/
            if(aux->pessoa.cpf == cpf){
                /*incrementamos achou*/
                achou = achou + 1;
                /*se o elemento a ser removido for o primeiro da lista*/
                if(aux == li->inicio){
                    /*inicio apontará para o segundo elemento da lista ou para NULL
                      caso o elemento removido seja o único elemento da lista*/
                    li->inicio = aux ->proximo;
                    /*desalocamos o espaço para onde aux apontava*/
                    free(aux);
                    /*aux aponta para o inicio da lista*/
                    aux = li->inicio;
                /*se o elemento a ser removido for o último da lista*/
                }else if (aux == fim){
                    /*o elemento anterior a fim, no atributo prox apontará para NULL*/
                    anterior->proximo = NULL;
                     /*fim aponta para o elemento apontado por anterior*/
                    fim = anterior;
                    /*desalocamos o espaço para onde aux apontava*/
                    free(aux);
                    /*como era o últmo elemento da lista, aux recebe NULL*/
                    aux = NULL;
                /*se o elemento a ser removido não for nem o primeiro nem o último da lista */
                }else{
                    /*o elemento anterior ao elemento a ser removido, no atributo prox apontará para o elemento
                      para qual aux->prox apontava*/
                    anterior->proximo = aux->proximo;
                    /*desalocamos o espaço para onde aux apontava*/
                    free(aux);
                    /*aux aponta para o próximo elemento da lista, aquele que era o seguinte ao número removido*/
                    aux = anterior -> proximo;
                }
				 /*caso aux-> num não seja igual ao número a ser removido*/
				 }else{
				     anterior = aux;
				     aux = aux -> proximo;
				 }
        /*essa operação será feita até aux ser diferente de NULL, ou seja, não houverem mais elementos a serem pesquisados*/
        }while(aux != NULL);
         if(achou == 0){
            printf("Numero nao encontrado!");
        }else{
            printf("Numero removido %d vez(es)",achou);
        }

    SEMAPHORE_UP();

    return retorno;
}



/**
 * @brief Impressão da tabela hash.
 * 
 */
void imprimir_tabela()
{
    int i;
    printf("\n---------------------TABELA-------------------------\n");
    for (i = 0; i < M; i++)
    {
        printf("%d Lista tamanho: %d\n", i, tabela[i]->tam);
        imprimir_lista(tabela[i]->inicio);
    }
    printf("---------------------FIM TABELA-----------------------\n");
}
