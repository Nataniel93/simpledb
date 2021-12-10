#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED

/**
 * @brief Tamanho da tabela Hash
 */
#define __HASHTABLE_LENGTH 1024

/**
 * @brief Tipo pessoa
 */
typedef struct
{
  long unsigned cpf;
  char nome[50];
  char email[50];
} Pessoa;

extern void inicializar_tabela(void);
extern int inserir_pessoa_tabela(Pessoa pessoa);
extern Pessoa *buscar_pessoa_tabela(long cpf);
extern int atualizar_pessoa_tabela(long cpf, const char *nome, const char *email);
extern int remover_pessoa_tabela(long cpf);
extern void imprimir_tabela(void);
extern void imprimir_pessoa(Pessoa pessoa);

#endif /* TABELAHASH_H_INCLUDED */