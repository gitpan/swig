// tree.i
// This file adds a simple C data structure that we will use
// To build a binary search tree in Tcl.
// Dave Beazley
// March 27, 1996

%module Tree
%{

#undef malloc
#undef free

#include "tree.h"
#include <math.h>

/* These are helper functions to get various parts of the tree
 * data structure.  Don't need them in C, but we'll use them in
 * scripts.
 */

Node  *get_left(Node *n) {
  return (n->left);
}

void   set_left(Node *n, Node *l) {
  n->left = l;
}

Node *get_right(Node *n) {
  return (n->right);
}

void   set_right(Node *n, Node *r) {
  n->right = r;
}

char *get_key(Node *n) {
  return (n->key);
}

char *get_value(Node *n) {
  return (n->value);
}

void  set_key(Node *n, char *key) {
  if (n->key) free(n->key);
  n->key = (char *) malloc(strlen(key)+1);	
  strcpy(n->key, key);
}

%}

%include timers.i

extern Node  *new_node(char *key, char *value);
       Node  *get_left(Node *n);
       void   set_left(Node *n, Node *l);
       Node  *get_right(Node *n);
       void   set_right(Node *n, Node *r);
       char  *get_key(Node *n);
       char  *get_value(Node *n);
       void   set_key(Node *n, char *key);
extern void   insert_tree(char *key, char *value, Node *head, Node *z);
extern char *search_tree(char *key, Node *head, Node *z);
extern int    tree_size;

       int    rand();








