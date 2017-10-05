#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

/**
 *
 * Red-black tree header 
 *
 *
 */

#define TYPE_RBTREE_KEY int

/**
 *
 * This structure holds the information to be stored at each node. Change this
 * structure according to your needs.  In order to make this library work, you
 * also need to adapt the functions compLT, compEQ and freeRBData. For the
 * current implementation the "key" member is used to index data within the
 * tree. 
 *
 */

typedef struct RBData_
{
  // The variable used to index the tree has to be called "key".
  // The type may be any you want (float, char *, etc)
  TYPE_RBTREE_KEY key;     

  // This is the additional information that will be stored
  // within the structure. You may adapt it to your needs:
  // add or remove fields as you need.
  int num_vegades;   
} RBData; 

/**
 *
 * The node structure 
 *
 */

typedef enum { BLACK, RED } nodeColor;

typedef struct Node_ {
    /* For internal use of the structure. Do not change. */
    struct Node_ *left;         /* left child */
    struct Node_ *right;        /* right child */
    struct Node_ *parent;       /* parent */
    nodeColor color;            /* node color (BLACK, RED) */

    /* Data to be stored at each node */
    RBData *data; /* data stored in node */
} Node;


/**
 * 
 * Some definitions
 * 
 */

#define NIL &sentinel  /* all leafs are sentinels */
extern Node sentinel;  /* declared in file red-black-tree.c */

/**
 *
 * The tree structure. It just contains the root node, from
 * which we may go through all the nodes of the binary tree.
 * Add any field you may find useful.
 *
 */

typedef struct RBTree_ {
  Node *root;                   /* root of Red-Black tree */
} RBTree;

/*
 * Function headers. Note that not all the functions of
 * red-black-tree.c have been included here.
 */

void initTree(RBTree *tree);
void insertNode(RBTree *tree, RBData *data);
RBData *findNode(RBTree *tree, TYPE_RBTREE_KEY key); 
void deleteTree(RBTree *tree);

#endif
