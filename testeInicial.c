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

    if (insert_op(argv))
    {
        char **data = buildData(argv, false);

        if (!data)
        {
            printf("\nErro: Não foi possível computar a entrada\n");
        }
        else
        {
            for (int i = 0; i < 2; i++)
            {
                printf("\nDATA[%i] -> %s \n", i, data[i]);
            }
            
            int retorno = inserir_pessoa(data[1]);
            imprimir_tabela();

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
    }

    else
    {
        printf("\nOperacao inválida\n\n");
    }

    return 0;
}