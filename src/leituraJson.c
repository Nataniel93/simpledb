#include <stdio.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/operacoes.h"

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *name;
	struct json_object *email;
	struct json_object *cpf;
	

	fp = fopen("teste.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "name", &name);
	json_object_object_get_ex(parsed_json, "age", &email);
	json_object_object_get_ex(parsed_json, "cpf", &cpf);

	printf("Name: %s\n", json_object_get_string(name));
	printf("Email: %d\n", json_object_get_string(email));
	printf("CPF: %d\n", json_object_get_int(cpf));
}