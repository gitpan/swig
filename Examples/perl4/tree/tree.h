/* Tree.h
   Defines a node for building binary trees
*/

#include <stdio.h>

typedef struct Node {
  char        *key;
  char        *value;
  struct Node *left;
  struct Node *right;
} Node;

