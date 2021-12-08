#include <stdio.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/operacoes.h"
#include "headers/tabelaHash.h"

Pessoa retornarPessoaApartirDeJson(char *data)
{
	struct json_object *parsed_json;
	struct json_object *name;
	struct json_object *email;
	struct json_object *cpf;
	Pessoa pessoa;

	parsed_json = json_tokener_parse(data);

	json_object_object_get_ex(parsed_json, "name", &name);
	json_object_object_get_ex(parsed_json, "email", &email);
	json_object_object_get_ex(parsed_json, "cpf", &cpf);

	strncpy(pessoa.nome, json_object_get_string(name), strlen(json_object_get_string(name)));
	strncpy(pessoa.email, json_object_get_string(email), json_object_get_string(email));
	pessoa.cpf = json_object_get_int(cpf);

	return pessoa;
}
