/* Directed graph functions */

#include "graph.h"
#include <stdlib.h>

static int node_count = 0;          /* Number of nodes created */

/* Create a new Node */

Node *new_Node() {
  Node *node;
  node = (Node *) malloc(sizeof(Node));
  node->v = node_count++;
  node->adj = (Edge *) 0;           
  return node;
}

/* Add an "edge" to an existing node */

Edge *Node_addedge(Node *mynode, Node *othernode, double w) {
  Edge *edge;
  edge = (Edge *) malloc(sizeof(Edge));
  edge->node = othernode;        
  edge->w = w;
  edge->next = mynode->adj;    /* add to my adjacency list */
  mynode->adj = edge;           
  return edge;
}


  

  
