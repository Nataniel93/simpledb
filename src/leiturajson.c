#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tabelahash.h>

/**
 * @brief Retorna o cpf a partir do json passado
 * 
 * @param data Json contendo os dados
 * @return int cpf
 */
int retornarCpfJson(char *data)
{
  struct json_object *parsed_json;
  struct json_object *cpf;

  parsed_json = json_tokener_parse(data);
  json_object_object_get_ex(parsed_json, "cpf", &cpf);

  int parsed_cpf = json_object_get_int(cpf);

  return parsed_cpf;
}

/**
 * @brief Retorna o nome e email a partir da entrada passada
 * 
 * @param data Json contendo os dados
 * @return char** vetor[0] = nome; vetor[1] = email
 */
char **retornarNomeEmailJson(char *data)
{
  struct json_object *parsed_json;
  struct json_object *nome;
  struct json_object *email;

  parsed_json = json_tokener_parse(data);
  json_object_object_get_ex(parsed_json, "nome", &nome);
  json_object_object_get_ex(parsed_json, "email", &email);

  const char *parsed_nome = json_object_get_string(nome);
  const char *parsed_email = json_object_get_string(email);
  char **campos = malloc(sizeof(char *) * 2);
  
  if (!campos) return NULL;
  
  campos[0] = malloc(sizeof(char));
  strcpy(campos[0], "");

  campos[1] = malloc(sizeof(char));
  strcpy(campos[1], "");

  if (parsed_nome != NULL)
  {
    campos[0] = realloc(campos[0], strlen(parsed_nome) * sizeof(char));
    strncpy(campos[0], parsed_nome, strlen(parsed_nome));
  }

  if (parsed_email != NULL)
  {
    campos[1] = realloc(campos[1], strlen(parsed_email) * sizeof(char));
    strncpy(campos[1], parsed_email, strlen(parsed_email));
  }

  return campos;
}

/**
 * @brief Cria uma Pessoa a partir dos dados da primeira posição retornados pela função buildData
 * 
 * @param data String dentro da 1° posição do vetor retornado pela função buildData
 * @return Pessoa 
 */
Pessoa retornarPessoaApartirDeJson(char *data)
{ 
	Pessoa pessoa;
  char **nomeEmail = retornarNomeEmailJson(data);
  int cpf = retornarCpfJson(data);
  int erros = 0;

  if (strlen(nomeEmail[0]) <= 0 || strlen(nomeEmail[0]) > 50)
  {
    printf("\nChave nome é obrigatória e deve possuir tamanho máximo de 50 caracteres. \n");
    erros++;
  }

  if (strlen(nomeEmail[1]) <= 0 || strlen(nomeEmail[1]) > 50)
  {
    printf("\nChave email é obrigatória e deve possuir tamanho máximo de 50 caracteres. \n");
    erros++;
  }

  if (cpf == 0)
  {
    printf("\nChave cpf não preenchida.\n");
    erros++;
  }

  if (erros == 0)
  {
    strncpy(pessoa.nome, nomeEmail[0], strlen(nomeEmail[0]));
    strncpy(pessoa.email, nomeEmail[1], strlen(nomeEmail[1]));
    pessoa.cpf = cpf;
  }

	return pessoa;
}