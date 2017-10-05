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
#include <time.h>

#include "red-black-tree.h"

#define MAXVALUE 10

/**
 *
 *  Main function. Contains a simple example using a red-black-tree. 
 *
 */

int main(int argc, char **argv)
{
  int a, maxnum, ct;

  RBTree *tree;
  RBData *treeData;

  if (argc != 2)
  {
    printf("Usage: %s maxnum\n", argv[0]);
    exit(1);
  }

  maxnum = atoi(argv[1]);

  printf("Test with red-black-tree\n");

  /* Random seed */
  srand(time(NULL));

  /* Allocate memory for tree */
  tree = (RBTree *) malloc(sizeof(RBTree));

  /* Initialize the tree */
  initTree(tree);

  for (ct = 0; ct < maxnum; ct++) {
    /* Generate random key to be inserted in the tree */
    a = rand() % MAXVALUE + 1;

    /* Search if the key is in the tree */
    treeData = findNode(tree, a); 

    if (treeData != NULL) {

      /* If the key is in the tree increment 'num' */
      treeData->num_vegades++;
    } else {

      /* If the key is not in the tree, allocate memory for the data
       * and insert in the tree */

      treeData = malloc(sizeof(RBData));
      
      /* This is the key by which the node is indexed in the tree */
      treeData->key = a;
      
      /* This is additional information that is stored in the tree */
      treeData->num_vegades = 1;

      /* We insert the node in the tree */
      insertNode(tree, treeData);
    }
  }
  
  /* We now dump the information of the tree to screen */

  ct = 0;

  for(a = 1; a <= MAXVALUE; a++)
  {
    treeData = findNode(tree, a);

    if (treeData) { 
      printf("El numero %d apareix %d cops a l'arbre.\n", a, treeData->num_vegades);
      ct += treeData->num_vegades;
    }
  }

  printf("Nombre total que vegades que s'ha accedit a l'arbre: %d\n", ct);
  
  /* Delete the tree */
  deleteTree(tree);
  free(tree);

  return 0;
}

