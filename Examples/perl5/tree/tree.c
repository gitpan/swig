/* tree.c
 * A few C functions for binary trees.
 */

int tree_size = 0;

#include "tree.h"
#include <string.h>
#include <stdlib.h>

/* Make a new node with given key and value */

Node  *new_node(char *key, char *value) {
  Node *n;

  n = (Node *) malloc(sizeof(Node));
  n->key = (char *) malloc(strlen(key)+1);
  strcpy(n->key, key);
  n->value = (char *) malloc(strlen(value)+1);
  strcpy(n->value, value);
  n->left = NULL;
  n->right = NULL;
  return n;
}

/* Insert an item into the tree.  */

void insert_tree(char *key, char *value, Node *head, Node *z) {
  Node *p;
  Node *x;
  
  p = head;
  x = head->right;
  while (x != z) {
    p = x;
    if (strcmp(key, x->key) < 0) 
      x = x->left;
    else 
      x = x->right;
  }
  x = new_node(key,value);
  if (strcmp(key,p->key) < 0)
    p->left = x;
  else
    p->right = x;
  x->left = z;
  x->right = z;
  tree_size++;
}

char *search_tree(char *key, Node *head, Node *z) {
  Node *x;
  int i;
  x = head->right;
  while (x != z) {
    if ((i = strcmp(x->key,key)) == 0) return x->value;
    else if (i < 0) x = x->left;
    else x = x->right;
  }

  return key;
}

