typedef struct atype {
  void *v;
  struct atype *next;
} AdjList;

typedef struct ntype {
  int            num;        /* Node number */
  int            visit;      /* Used for searching */
  AdjList       *adj;    
  AdjList       *oldadj;     /* Used in transitive closure */
  struct ntype  *next_node;
} Node;


  

