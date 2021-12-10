#include "tabelahash.h"

#ifndef LEITURAJSON_H_INCLUDED
#define LEITURAJSON_H_INCLUDED

Pessoa retornarPessoaApartirDeJson(char *data);
int retornarCpfJson(char *data);
char **retornarNomeEmailJson(char *data);

#endif /* LEITURAJSON_H_INCLUDED */