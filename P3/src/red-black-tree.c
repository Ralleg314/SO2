/**
 *
 * Red-black tree implementation. 
 * 
 * Binary search trees work best when they are balanced or the path length from
 * root to any leaf is within some bounds. The red-black tree algorithm is a
 * method for balancing trees. The name derives from the fact that each node is
 * colored red or black, and the color of the node is instrumental in
 * determining the balance of the tree. During insert and delete operations,
 * nodes may be rotated to maintain tree balance. Both average and worst-case
 * search time is O(lg n).
 *
 * This implementation is original from John Morris, University of Auckland, at
 * the following link
 *
 * http://www.cs.auckland.ac.nz/~jmor159/PLDS210/niemann/s_rbt.htm
 *
 * and has been adapted here by Lluis Garrido, September 2017.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "red-black-tree.h"

/**
 *
 * Free data element. The user should adapt this function to their needs.  This
 * function is called internally by deleteNode and is used to free the
 * dynamic memory that is stored inside RBData. The memory is allocated
 * by the user code, just before the node is inserted in the tree. 
 *
 */

static void freeRBData(RBData *data)
{
  free(data);
}

/**
 *
 * Compares if key1 is less than key2. Should return 1 (true) if condition
 * is satisfied, 0 (false) otherwise.
 *
 */

static int compLT(TYPE_RBTREE_KEY key1, TYPE_RBTREE_KEY key2)
{
  int rc;

  rc = 0;

  if (strcmp(key1,key2)<0)
    rc = 1;

  return rc;
}

/**
 *
 * Compares if key1 is equal to key2. Should return 1 (true) if condition
 * is satisfied, 0 (false) otherwise.
 *
 */

static int compEQ(TYPE_RBTREE_KEY key1, TYPE_RBTREE_KEY key2)
{
  int rc;

  rc = 0;

  if (strcmp(key1, key2) == 0)
    rc = 1;

  return rc;
}

/**
 * 
 * NO CANVIEU EL CODI QUE HI HA A SOTA LLEVAT QUE SAPIGUEU EL QUE ESTEU FENT.
 * PER FER LES PRACTIQUES NO CAL MODIFICAR EL CODI QUE HI HA A SOTA.
 *
 */


Node sentinel = { NIL, NIL, 0, BLACK, NULL};

/**
 *
 * Initialize the tree.
 * 
 *
 */

void initTree(RBTree *tree)
{
  tree->root = NIL;
}

/**
 *
 *  Rotate node x to left. Should not be called directly by the user. This
 *  function is used internally by other functions.
 *
 */

static void rotateLeft(RBTree *tree, Node *x) {

  Node *y = x->right;

  /* establish x->right link */
  x->right = y->left;
  if (y->left != NIL) y->left->parent = x;

  /* establish y->parent link */
  if (y != NIL) y->parent = x->parent;
  if (x->parent) {
    if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
  } else {
    tree->root = y;
  }

  /* link x and y */
  y->left = x;
  if (x != NIL) x->parent = y;
}

/**
 *  
 *  Rotate node x to right. Should not be called directly by the user. This
 *  function is used internally by other functions.
 *
 */

static void rotateRight(RBTree *tree, Node *x) {
  Node *y = x->left;

  /* establish x->left link */
  x->left = y->right;
  if (y->right != NIL) y->right->parent = x;

  /* establish y->parent link */
  if (y != NIL) y->parent = x->parent;
  if (x->parent) {
    if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;
  } else {
    tree->root = y;
  }

  /* link x and y */
  y->right = x;
  if (x != NIL) x->parent = y;
}

/** 
 *
 * Maintain Red-Black tree balance  after inserting node x. Should not be
 * called directly by the user. This function is used internally by other
 * functions.
 *
 */

static void insertFixup(RBTree *tree, Node *x) {
  /* check Red-Black properties */
  while (x != tree->root && x->parent->color == RED) {
    /* we have a violation */
    if (x->parent == x->parent->parent->left) {
      Node *y = x->parent->parent->right;
      if (y->color == RED) {

	/* uncle is RED */
	x->parent->color = BLACK;
	y->color = BLACK;
	x->parent->parent->color = RED;
	x = x->parent->parent;
      } else {

	/* uncle is BLACK */
	if (x == x->parent->right) {
	  /* make x a left child */
	  x = x->parent;
	  rotateLeft(tree,x);
	}

	/* recolor and rotate */
	x->parent->color = BLACK;
	x->parent->parent->color = RED;
	rotateRight(tree, x->parent->parent);
      }
    } else {

      /* mirror image of above code */
      Node *y = x->parent->parent->left;
      if (y->color == RED) {

	/* uncle is RED */
	x->parent->color = BLACK;
	y->color = BLACK;
	x->parent->parent->color = RED;
	x = x->parent->parent;
      } else {

	/* uncle is BLACK */
	if (x == x->parent->left) {
	  x = x->parent;
	  rotateRight(tree, x);
	}
	x->parent->color = BLACK;
	x->parent->parent->color = RED;
	rotateLeft(tree,x->parent->parent);
      }
    }
  }
  tree->root->color = BLACK;
}

/**
 *  
 * Allocate node for data and insert in tree. This function does not perform a
 * copy of data when inserting it in the tree, it rather creates a node and
 * makes this node point to the data. Thus, the contents of data should not be
 * overwritten after calling this function.
 *
 */

void insertNode(RBTree *tree, RBData *data) {
  Node *current, *parent, *x;

  /* Find where node belongs */
  current = tree->root;
  parent = 0;
  while (current != NIL) {
    if (compEQ(data->key, current->data->key)) {
      printf("insertNode: trying to insert but primary key is already in tree.\n");
      exit(1);
    }
    parent = current;
    current = compLT(data->key, current->data->key) ?
      current->left : current->right;
  }

  /* setup new node */
  if ((x = malloc (sizeof(*x))) == 0) {
    printf ("insufficient memory (insertNode)\n");
    exit(1);
  }

  /* Note that the data is not copied. Just the pointer
     is assigned. This means that the pointer to the 
     data should not be overwritten after calling this
     function. */

  x->data = data;

  /* Copy remaining data */
  x->parent = parent;
  x->left = NIL;
  x->right = NIL;
  x->color = RED;

  /* Insert node in tree */
  if(parent) {
    if(compLT(data->key, parent->data->key))
      parent->left = x;
    else
      parent->right = x;
  } else {
    tree->root = x;
  }

  insertFixup(tree, x);
}

/**
 *
 *  Find node containing the specified key. Returns the node.
 *  Returns NULL if not found.
 *
 */

RBData *findNode(RBTree *tree, TYPE_RBTREE_KEY key) {

  Node *current = tree->root;
  while(current != NIL)
    if(compEQ(key, current->data->key))
      return (current->data);
    else
      current = compLT(key, current->data->key) ?
	current->left : current->right;

  return NULL;
}

/**
 *
 *  Function used to delete a tree. Do not call directly. 
 *
 */

static void deleteTreeRecursive(Node *x)
{
  if (x->right != NIL)
    deleteTreeRecursive(x->right);

  if (x->left != NIL)
    deleteTreeRecursive(x->left);

  freeRBData(x->data);
  free(x);
}


/**
 *
 *  Delete a tree. All the nodes and all the data pointed to by
 *  the tree is deleted. 
 *
 */

void deleteTree(RBTree *tree)
{
  if (tree->root != NIL)
    deleteTreeRecursive(tree->root);
}


