#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tabelahash.h"

Pessoa retornarPessoaApartirDeJson(char *data)
{ 
	struct json_object *parsed_json;
	struct json_object *nome;
	struct json_object *email;
	struct json_object *cpf;
	Pessoa pessoa;
  int erros = 0;
  
	parsed_json = json_tokener_parse(data);

	json_object_object_get_ex(parsed_json, "nome", &nome);
	json_object_object_get_ex(parsed_json, "email", &email);
	json_object_object_get_ex(parsed_json, "cpf", &cpf);

  const char *parsed_nome = json_object_get_string(nome);
  const char *parsed_email = json_object_get_string(email);

  if (strlen(parsed_nome) <= 0 || strlen(parsed_nome) > 50)
  {
    printf("\n Chave nome possui tamanho inválido. Tamanho máximo de 50 caracteres. \n");
    erros++;
  }

  if (strlen(parsed_email) <= 0 || strlen(parsed_email) > 50)
  {
    printf("\n Chave email possui tamanho inválido. Tamanho máximo de 50 caracteres. \n");
    erros++;
  }

  if (erros == 0)
  {
    strncpy(pessoa.nome, parsed_nome, strlen(parsed_nome));
    strncpy(pessoa.email, parsed_email, strlen(parsed_email));
    pessoa.cpf = json_object_get_int(cpf);
  }
  

	return pessoa;
}
