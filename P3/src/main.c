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
#define SIZE_MAGIC_NUMBER 8

void inserirParaules(RBTree*, RBData*, FILE*);
void writeTree(RBTree*, FILE *fp);
void writeTreeRecursive(Node*, FILE*);
void writeRBData(RBData*, FILE*);
int countTreeRecursive(Node*);

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
    char str[MAXLINE], *palabra;
    int opcio, magicNumber, len_str, n, i, num_vegades;
    RBTree *tree;
    RBData *treeData;
    FILE *fp;

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

                fp = fopen(str, "r");
                
                if (!fp) {
                  printf("ERROR: no he pogut obrir el fitxer.\n");
                  exit(EXIT_FAILURE);
                }

                fwrite(&magicNumber, SIZE_MAGIC_NUMBER, 1, fp);
                
                num_vegades = countTreeRecursive(tree->root);
                fwrite(&num_vegades, sizeof(int), 1, fp);

                writeTree(tree, fp);

                break;

            case 3:
                
                deleteTree(tree);
                free(tree);
                
                /* Allocate memory for tree */
                tree = (RBTree *) malloc(sizeof(RBTree));

                /* Initialize the tree */
                initTree(tree);
                if (!tree){
                  printf("ERROR: no he pogut crear l'arbre.\n");
                  exit(EXIT_FAILURE);
                }

                printf("Introdueix nom del fitxer amb l'arbre: ");
                fgets(str, MAXLINE, stdin);
                str[strlen(str)-1] = 0;

                fp = fopen(str, "r");
                
                if (!fp) {
                  printf("ERROR: no he pogut obrir el fitxer.\n");
                  exit(EXIT_FAILURE);
                }

                fread(&magicNumber, SIZE_MAGIC_NUMBER, 1, fp);

                if(magicNumber == MAGIC_NUMBER){

                    fread(&n, sizeof(int), 1, fp);
                    for (i = 0; i < n; ++i){
                      fread(&len_str, sizeof(int), 1, fp);
                      palabra = (char *) malloc(sizeof(char) * (len_str + 1) );

                      if (!palabra){
                        printf("ERROR: malloc error.\n");
                        exit(EXIT_FAILURE);
                      }

                      fread(palabra, sizeof(char), len_str, fp);
                      palabra[len_str] = 0;
                      fread(&num_vegades, sizeof(int), 1, fp);
                      
                      treeData = findNode(tree, palabra);
                      
                      if(treeData!=NULL){
                          treeData->num_vegades += num_vegades;
                          printf("%s\n", palabra);
                      }else{
                        treeData = malloc(sizeof(RBData));
        
                        /* This is the key by which the node is indexed in the tree */
                        treeData->key = palabra;
                        
                        /* This is additional information that is stored in the tree */
                        treeData->num_vegades = num_vegades;

                        /* We insert the node in the tree */
                        insertNode(tree, treeData);
                        
                        printf("%s\n", palabra);
                      }

                    }

                    fclose(fp);

                }else{
                  printf("ERROR: magic number erroni.\n");
                }

                break;

            case 4:
                printf("Introdueix la paraula: ");
                fgets(str, MAXLINE, stdin);
                str[strlen(str)-1]=0;

                treeData = findNode(tree, str);

                if (treeData) { 
                    printf("La paraula %s apareix %d cops a l'arbre.\n", str, treeData->num_vegades);
                }else{
                    printf("La paraula %s no apareix a l'arbre.\n", str);    
                }

                break;

            case 5:

                deleteTree(tree);
                free(tree);

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

void writeRBData(RBData *data, FILE *fp){
  int len = strlen(data->key);
  fwrite(&len, sizeof(int), 1, fp);
  fwrite(data->key, sizeof(char), strlen(data->key), fp);
  fwrite(&data->num_vegades, sizeof(int), 1, fp);
}

/**
 * 
 *  Recorre recursivamente los hijos de un nodo para escribir los datos en un archivo
 *  FILE *fp -> stream a archivo donde guardar los datos
 *  Node *x -> nodo desde el cual se hace la recursion
 */
void writeTreeRecursive(Node *x, FILE *fp){
  if (x->right != NIL)
    writeTreeRecursive(x->right, fp);

  if (x->left != NIL)
    writeTreeRecursive(x->left, fp);

  writeRBData(x->data, fp);
}


/**
 * 
 *  Recorre un arbol para escribir los datos en un archivo
 *  FILE *fp -> stream a archivo donde guardar los datos
 *  RBTree *tree -> arbol a recorrer
 */
void writeTree(RBTree *tree, FILE *fp)
{
  if (tree->root != NIL)
    writeTreeRecursive(tree->root, fp);
}


/**
 * 
 *  Recorre recursivamente los hijos de un nodo para contar los nodos del arbol
 *  Node *x -> nodo desde el cual se hace la recursion
 */
int countTreeRecursive(Node *x){
  int rightCount, leftCount;
  rightCount = 0;
  leftCount = 0;
  if (x->right != NIL)
    rightCount = countTreeRecursive(x->right);

  if (x->left != NIL)
    leftCount = countTreeRecursive(x->left);

  return ((int)1) + rightCount + leftCount;
}

