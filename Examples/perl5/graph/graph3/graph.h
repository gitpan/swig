/* Simple data structures for directed graph of
   Nodes and Edges */

struct Edge;

typedef struct Node {
  int           v;            /* Vertex number              */
  struct Edge  *adj;          /* Adjacency List             */
} Node;

typedef struct Edge {
  Node          *node;        /* Connecting Node            */
  double         w;
  struct Edge   *next;        /* Next edge                  */
} Edge;

#define UNSEEN          -1
#define MAX_NODES     1000

extern Node *new_Node();
extern Edge *Node_addedge(Node *mynode, Node *othernode, double w);
extern int   Node_search(Node *start, int v);



