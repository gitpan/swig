%module graph
%{
#include "graph.h"
%}

%include graph.h

extern Node *new_Node();
extern Edge *Node_addedge(Node *mynode, Node *othernode, double w);
extern int   Node_search(Node *start, int v);

%inline %{
/* Get seen value for a particular node  */

int get_seen(int index) {
  extern int node_count;
  extern int seen[];
  if ((index < 0) || (index >= node_count)) return -1;
  else return seen[index];
}
%}


