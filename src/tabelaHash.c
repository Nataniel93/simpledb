#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Representa o tamanho da tabela hash.
 * 
 */
#define M 49

/**
 * @brief Cria uma STRUCT para armazenar os dados de uma "pessoa" em um tipo pessoa.
 * 
 */
typedef struct {
    long unsigned cpf;
    char nome[50];
    char email[50];
} Pessoa;

/**
 * @brief Cria uma STRUCT do tipo NO.
 * 
 */
typedef struct no {
    Pessoa pessoa;
    struct no *proximo;
} No;

/**
 * @brief Cria uma STRUCT do tipo Lista.
 * 
 */
typedef struct {
    No *inicio;
    int tam;
} Lista;

/**
 * @brief Vetor de ponteiros para Lista.
 * 
 */
Lista *tabela[M];


/**
 * @brief Insere os dados de uma pessoa na tabela hash.
 * 
 * @return Pessoa 
 */
Pessoa inserir_pessoa() {
    Pessoa p;
    
    p.cpf;
    p.email;
    p.nome;

    return p;
}

/**
 * @brief Imprime na tela os dados de uma pessoa.
 * 
 * @param p Representa uma variável do tipo pessoa.
 */
void imprimir_pessoa(Pessoa p) {
    printf("\tNome: %s\tCPF: %ld\tEmail: %s\n", p.nome, p.cpf, p.email);
}

/**
 * @brief Cria uma lista vazia e retorna seu endereço na memória
 * 
 * @return Lista* 
 */
Lista* criar_lista() {
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
void insercao_dados_lista(Pessoa p, Lista *lista) {
    No *no = malloc(sizeof(No));
    no->pessoa = p;
    no->proximo = lista->inicio;
    lista->inicio = no;
    lista->tam++;
}

/**
 * @brief Buscar um elemento na lista.
 * 
 * @param cpf CPF da pessoa a ser procurada na tabela.
 * @param inicio 
 * @return No* Retorna null se o cpf não for encontrado.
 */
No* buscar_no(long cpf, No *inicio) {

    while(inicio != NULL) {
        if(inicio->pessoa.cpf == cpf)
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
void imprimir_lista(No *inicio) {
    while(inicio != NULL) {
        imprimir_pessoa(inicio->pessoa);
        inicio = inicio->proximo;
    }
}

/**
 * @brief Inicializa a tabela com uma lista vazia em cada posição do vetor
 * 
 */
void inicializar(){
    int i;
    for(i = 0; i < M; i++)
        tabela[i] = criar_Lista();
}

/**
 * @brief Função de conversão hash.
 * 
 * @param cpf Representa o cpf da pessoa.
 * @return int 
 */
int funcao_espalhamento(long cpf){
    return cpf % M;
}

/**
 * @brief Cria uma nova pessoa e insere os dados na tabela.
 * 
 */
void inserir_pessoa_tabela(){
    Pessoa pes = inserir_pessoa();
    int indice = funcao_espalhamento(pes.cpf);
    insercao_dados_lista(pes, tabela[indice]);
}

/**
 * @brief Busca uma pessoa na tabela.
 * 
 * @param cpf CPF da pessoa a ser buscada.
 * @return Pessoa* 
 */
Pessoa* buscar_pessoa_tabela(long cpf){
    int indice = funcao_espalhamento(cpf);
    No *no = buscar_no(cpf, tabela[indice]->inicio);
    if(no)
        return &no->pessoa;
    else
        return NULL;
}

/**
 * @brief Impressão da tabela hash.
 * 
 */
void imprimir_tabela(){
    int i;
    printf("\n---------------------TABELA-------------------------\n");
    for(i = 0; i < M; i++){
        printf("%d Lista tamanho: %d\n", i, tabela[i]->tam);
        imprimir_lista(tabela[i]->inicio);
    }
    printf("---------------------FIM TABELA-----------------------\n");
}

int main() {
    int op, mat;
    Pessoa *p;

    inicializar();

    do {
        printf("\n0 - Sair\n1 - Inserir\n2 - Buscar\n3 - Imprimir tabela\n");
        scanf("%d", &op);
        switch(op) {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            inserir_pessoa_tabela();
            break;
        case 2:
            printf("Qual a matricula a ser buscada? ");
            scanf("%d", &mat);
            p = buscar_pessoa_tabela(mat);
            if(p) {
                printf("Pessoa encontrada: Matricula: %d\tNome: %s", p->cpf, p->nome);
            } else
                printf("Pessoa nao contrada!\n");
            break;
        case 3:
            imprimirTabela();
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while(op != 0);

    return 0;
}