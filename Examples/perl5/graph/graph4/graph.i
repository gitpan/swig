%module graph
%{
#include "graph.h"
%}

/* Simple data structures for directed graph of
   Nodes and Edges */

struct Edge;
typedef struct Node {
  int           v;            /* Vertex number              */
  struct Edge  *adj;          /* Adjacency List             */
  %addmethods {
    Node();
    Edge *addedge(Node *othernode, double w);
    int   search(int v);
  }
} Node;

typedef struct Edge {
  Node          *node;        /* Connecting Node            */
  double         w;
  struct Edge   *next;        /* Next edge                  */
} Edge;

#define UNSEEN          -1
#define MAX_NODES     1000

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

%include location.i

