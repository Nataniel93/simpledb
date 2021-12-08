#ifndef TABELAHASH_H_
#define TABELAHASH_H_

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


extern int hashtable_init(void);
extern int hashtable_insert(const struct object *obj);
extern const struct object *hashtable_remove(unsigned key);
extern const struct object *hashtable_search(unsigned key);
extern int hashtable_update(unsigned key, const char *value);

#endif /* TABELAHASH_H_ */