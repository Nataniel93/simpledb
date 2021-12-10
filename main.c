#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <operacoes.h>
#include <commands.h>
#include <utils.h>
#include <leiturajson.h>

int main(int argc, char *argv[])
{
  inicializar_tabela();
  // while(!exit_op(argv))
  // {
    if (insert_op(argv))
    {
      printf("\n argv[0] %s", argv[0]);
      printf("\n argv[1] %s", argv[1]);
      printf("\n argv[2] %s", argv[2]);

      char **data = buildData(argv, false);

      if (!data)
      {
        printf("\nErro: Não foi possível computar a entrada\n");
      }
      else
      {
        int retorno = inserir_pessoa(data[1]);

        if (retorno)
        {
          printf("\nPessoa inserida com sucesso!\n");
        }
        else
        {
          printf("\nFalha ao inserir pessoa\n");
        }
      }
    }
    else if (search_op(argv))
    {
      printf("\nEh Search\n\n");
    }
    else if (remove_op(argv))
    {
      printf("\nEh Remove\n\n");
    }
    else if (update_op(argv))
    {
      printf("\nEh Update\n\n");
      char **data = buildData(argv, true);

      if (!data)
      {
        printf("ERROR: Unable to allocate data!\n");
        return 1;
      }
      else
      {
        printf("\nDeu certo!\n");
      }
    }
    else if (list_op(argv))
    {
      printf("\nEh List\n\n");
    }
    else
    {
      printf("\nOperacao inválida\n\n");
    }
  // }

  return 0;
}