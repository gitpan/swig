/* SWIG Graph Example.  
 *
 * Dave Beazley
 * Adds some simple graph algorithms to Tcl/Tk. 
 */

%module Graph
%{

#define SAFE_SWIG
#include "graph.h"
extern AdjList *az;

/* Helper functions.   These are needed to access certain data
   structures from within Tcl */

int GetNum(Node *n) {
	return n->num;
}

int GetVisit(Node *n) {
	return n->visit;
}

AdjList *GetAdj(Node *n) {
	if (n->adj == az) return 0;
	else return n->adj;
}

AdjList *GetNext(AdjList *l) {
	if (l->next == az) return 0;
	else return l->next;
}

Node *GetNode(AdjList *l) {
	return l->v;
}

%}

extern  void     init_graph();
extern  Node     *new_node();
extern  void     AddLink(Node *v1, Node *v2);
extern  void     FreeAdjList(AdjList *l);
extern  void     PrintNodes(void);
        int      GetNum(Node *node);
extern  void     Connected(Node *n);
        int      GetVisit(Node *node);
extern  void     Closure_Step();
        AdjList *GetAdj(Node *);
        AdjList *GetNext(AdjList *);
        Node    *GetNode(AdjList *);
extern  AdjList *FindShort(Node *, Node *);




