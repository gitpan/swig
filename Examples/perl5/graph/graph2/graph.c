/* Directed graph functions */

#include <stdio.h>
#include "graph.h"
#include <stdlib.h>

int node_count = 0;          /* Number of nodes created */
int seen[MAX_NODES];

/* Create a new Node */

Node *new_Node() {
  Node *node;
  if (node_count == MAX_NODES) {
    fprintf(stderr,"Out of memory.\n");
    return 0;
  }
  node = (Node *) malloc(sizeof(Node));
  node->v = node_count++;
  node->adj = (Edge *) 0;           
  return node;
}

/* Add an "edge" to an existing node */

Edge *Node_addedge(Node *mynode, Node *othernode,double w) {
  Edge *edge;
  edge = (Edge *) malloc(sizeof(Edge));
  edge->node = othernode;        
  edge->w = w;
  edge->next = mynode->adj;    /* add to my adjacency list */
  mynode->adj = edge;           
  return edge;
}

/* Function to search for node with given vertex number */

static int visit(Node *n,int v) {
  Edge *e;

  if (seen[n->v] != UNSEEN) return UNSEEN;    /* Cycle detected, bail out */
  if (n->v == v) return 1;                    /* Match found              */
  e = n->adj;
  while (e) {
    seen[n->v] = e->node->v;
    if (visit(e->node,v) > 0) return 1;     
    e = e->next;
  }
  return 0;
}

/* Depth-first search for a given node */

int Node_search(Node *start, int v) {
  int i;
  
  for (i = 0; i < node_count; i++)
    seen[i] = UNSEEN;

  return visit(start,v);
}




  

  
