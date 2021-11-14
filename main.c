#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "headers/operacoes.h"
#include "headers/commands.h"

int main(int argc, char *argv[])
{
  if (insert_op(argv))
  {
    printf("\nEh Insert\n\n");
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