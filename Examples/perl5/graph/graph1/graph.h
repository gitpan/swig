/* Simple data structures for directed graph of
   Nodes and Edges */

struct Edge;

typedef struct Node {
  int           v;            /* Vertex number              */
  struct Edge  *adj;          /* Adjacency List             */
} Node;

typedef struct Edge {
  Node          *node;        /* Connecting Node            */
  double            w;        /* Weight (optional)          */
  struct Edge   *next;        /* Next edge                  */
} Edge;




