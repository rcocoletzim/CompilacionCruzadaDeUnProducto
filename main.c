#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cat.h"

/*Agregar el define del comando que se agrego*/
#define CAT_COMMAND 1U

int main(int argc, char const *argv[])
{
    /*local variables*/
    int opcion = 0U;
    char *file_name = NULL;
    /**/
    printf("Bienvenido\n Que programa desea ejecutar:\n");
    printf("1.- Cat\n");
    /*Agregar las demas opciones*/


    scanf("%d",&opcion);
    switch (opcion)
    {
    case CAT_COMMAND:
        printf("Que archivos deseas leer: ");
        file_name = (char*)malloc(100*(sizeof(char)));
        if (file_name != NULL)
        {
            scanf("%s",file_name);
            cat_command((const char*)file_name);
        }
        else
        {
            printf("Dynamic memory error");
            return 1;
        }
        free(file_name);
        file_name = NULL;
        break;

    // case comando:
    //     break;

    default:
        printf("Opcion no valida X,D\n");
        break;
    }
    return 0;
}
