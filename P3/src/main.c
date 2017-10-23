/**
 *
 * Practica 3 
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // per les funcions isalpha, isdigit, ...
#include <time.h>

#include "red-black-tree.h"

#define MAXLINE      200
#define MAGIC_NUMBER 0x0133C8F9

void inserirParaules(RBTree*, RBData*, FILE*);

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
    RBTree *tree;
    RBData *treeData;

    tree = (RBTree *) malloc(sizeof(RBTree));
    initTree(tree);

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
		deleteTree(tree);
		free(tree);

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

                treeData = findNode(tree, str);

		if (treeData) { 
		  printf("La paraula %s apareix %d cops a l'arbre.\n", str, treeData->num_vegades);
		}

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

void inserirParaules(RBTree* tree, RBData* treeData, FILE *fpout){
	int i, j, len;
	int inicio=0, fin;
	int dist;
	char line[MAXLINE], *palabra;

	while (fgets(line, MAXLINE, stdin) != NULL) {
     
        if (fputs(line, fpout) == EOF) {
            printf("ERROR: no puc escriure a la canonada.\n");
            exit(EXIT_FAILURE);
        }
        len = strlen(line);
        for(i = 0; i < len; i++){
            if(!isalpha(line[i]) && !isdigit(line[i])){
                fin=i;
                dist=fin-inicio;
                palabra = (char*)malloc(dist*sizeof(char));
                for(j=0;j<dist;j++){
                    palabra[j]=tolower(line[inicio+j]);
                }
                if(strlen(palabra)!=0){ 
                    //printf("%s\n", palabra);
                    /* Search if the key is in the tree */
                    treeData = findNode(tree, palabra); 

                    if (treeData != NULL) {
                        /* If the key is in the tree increment 'num' */
                        treeData->num_vegades++;
                    } else{

                        /* If the key is not in the tree, allocate memory for the data
                        * and insert in the tree */

                        treeData = malloc(sizeof(RBData));
                        
                        /* This is the key by which the node is indexed in the tree */
                        treeData->key = palabra;
                        
                        /* This is additional information that is stored in the tree */
                        treeData->num_vegades = 1;

                        /* We insert the node in the tree */
                        insertNode(tree, treeData);
                    }
                }
                inicio=i+1;
                free(palabra);
            }
        }
        inicio=0;
    }
}

