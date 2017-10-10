/**
 *
 * Main file 
 * 
 * This file calls the red-black-tree.c functions.
 *
 * Lluis Garrido, September 2017.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // per la funcio strlen
#include <ctype.h>  // per les funcions isalpha, isdigit, ...
#include <time.h>

#include "red-black-tree.h"

#define MAXVALUE 10
#define MAXLINE 100

/**
 *
 *  Main function. Contains a simple example using a red-black-tree. 
 *
 */

int main(int argc, char **argv)
{
  int i, j, len;
  int inicio=0, fin;
  int dist;
  char line[MAXLINE], *palabra;
  FILE	*fpout;

  RBTree *tree;
  RBData *treeData;

  /*if (argc != 1)
  {
    printf("Usage: %s maxnum\n", argv[0]);
    exit(1);
  }

  maxnum = atoi(argv[1]);*/

  printf("Test with red-black-tree\n");

  /* Random seed */
  srand(time(NULL));

  /* Allocate memory for tree */
  tree = (RBTree *) malloc(sizeof(RBTree));

  /* Initialize the tree */
  initTree(tree);
  fpout = popen("wc", "w");
  if (!fpout)
  {
    printf("ERROR: no puc crear canonada.\n");
    exit(EXIT_FAILURE);
  }

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

    if (pclose(fpout) == -1) {
        printf("ERROR: pclose.\n");
        exit(EXIT_FAILURE);
    }
  
  
  /* We now dump the information of the tree to screen */

 /* ct = 0;

  for(i = 1; i <= MAXVALUE; i++)
  {
    treeData = findNode(tree, a);

    if (treeData) { 
      printf("El numero %s apareix %d cops a l'arbre.\n", a, treeData->num_vegades);
      ct += treeData->num_vegades;
    }
  }

  printf("Nombre total que vegades que s'ha accedit a l'arbre: %d\n", ct);*/
  
  /* Delete the tree */
  deleteTree(tree);
  free(tree);

  return 0;
}

