%module graph
%{
#include "graph.h"
%}

%include graph.h

%addmethods Node {
	Node();
        Edge *addedge(Node *othernode, double w);
        int   search(int v);
}

%{
/* Get seen value for a particular node  */

int get_seen(int index) {
  extern int node_count;
  extern int seen[];
  if ((index < 0) || (index >= node_count)) return -1;
  else return seen[index];
}
%}

int get_seen(int index);



