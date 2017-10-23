/**
 *
 * Practica 3 
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "red-black-tree.h"

#define MAXLINE      200
#define MAGIC_NUMBER 0x0133C8F9

/**
 * 
 *  Menu
 * 
 */

int menu() 
{
    char str[5];
    int opcio;

    printf("\n\nMenu\n\n");
    printf(" 1 - Creacio de l'arbre\n");
    printf(" 2 - Emmagatzemar arbre a disc\n");
    printf(" 3 - Llegir arbre de disc\n");
    printf(" 4 - Consultar informacio d'un node\n");
    printf(" 5 - Sortir\n\n");
    printf("   Escull opcio: ");

    fgets(str, 5, stdin);
    opcio = atoi(str); 

    return opcio;
}

/**
 * 
 *  Main procedure
 *
 */

int main(int argc, char **argv)
{
    char str[MAXLINE];
    int opcio;

    if (argc != 1)
        printf("Opcions de la linia de comandes ignorades\n");

    do {
        opcio = menu();
        printf("\n\n");

       /* Feu servir aquest codi com a pantilla */

        switch (opcio) {
            case 1:
                printf("Introdueix fitxer que conte llistat fitxers PDF: ");
                fgets(str, MAXLINE, stdin);
                str[strlen(str)-1]=0;

                /* Falta codi */

                break;

            case 2:
                printf("Introdueix el nom de fitxer en el qual es desara l'arbre: ");
                fgets(str, MAXLINE, stdin);
                str[strlen(str)-1]=0;

                /* Falta codi */

                break;

            case 3:
                printf("Introdueix nom del fitxer amb l'arbre: ");
                fgets(str, MAXLINE, stdin);
                str[strlen(str)-1]=0;

                /* Falta codi */

                break;

            case 4:
                printf("Introdueix la paraula: ");
                fgets(str, MAXLINE, stdin);
                str[strlen(str)-1]=0;

                /* Falta codi */

                break;

            case 5:

                /* Falta codi */

                break;

            default:
                printf("Opcio no valida\n");

        } /* switch */
    }
    while (opcio != 5);

    return 0;
}

