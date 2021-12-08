#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "headers/operacoes.h"
#include "headers/commands.h"
#include "headers/utils.h"

int main(int argc, char *argv[])
{

  /**
   * @brief Verifica se o comando do CLI é insert.
   * 
   */
  if (insert_op(argv))
  {    
    printf("\nEh Insert\n\n");
    char** data = buildData(argv, false);

    if (!data) {
      printf ("ERROR: Unable to allocate data!\n");
      return 1;
    }
    else {
      insert_table();
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

  /**
   * @brief Verifica se o camando do CLI é de update.
   * 
   */
  else if (update_op(argv))
  {
    printf("\nEh Update\n\n");
    char** data = buildData(argv, true);

    if (!data) {
      printf ("ERROR: Unable to allocate data!\n");
      return 1;
    }
    else {
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

  return 0;
}