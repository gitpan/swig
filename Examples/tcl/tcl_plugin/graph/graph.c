/* SWIG Graph Example
 *
 * Dave Beazley
 *
 * This code implements a few simple graph algorithms.
 * Our data structures are basically as follows :
 *
 *   1.  A linked list of nodes (containing all of the current
 *       nodes).
 *   2.  Each node has an adjacency list which is a linked list
 *       of all of the edges to other nodes.
 */

#include <stdio.h>
#include "graph.h"

int   V = 0;           /* Number of nodes */

Node    *head;         /* Linked list of nodes */
Node    *z; 
AdjList *az;           /* Terminator of the adjaceny lists */


/* ------------------------------------------------------------
  void init_graph()
 
  Initializes the graph code by clearing the linked list of nodes
  ------------------------------------------------------------ */
void init_graph() {

  Node *n, *n1;
  AdjList *l, *l1;
  int i;

  V = 0;
  if (head) {
    n = head->next_node;
    while (n != z) {
      l = n->adj;
      while (l != az) {
	l1 = l->next;
	free(l);
	l = l1;
      }
      n1 = n->next_node;
      free(n);
      n = n1;
    }
  }
    
  head = (Node *) malloc(sizeof(Node));
  z = (Node *) malloc(sizeof(Node));
  z->next_node = z;
  head->next_node = z;
  az = (AdjList *) malloc(sizeof(AdjList));
  az->next = az;
  az->v = 0;
}

/* --------------------------------------------------------
  Node *new_node()
 
  Creates a new node.   This node is added onto the linked
  list of nodes.   Returns a pointer to the new node.
  -------------------------------------------------------- */
                 
Node *new_node() {

  Node *t;
  t = (Node *) malloc(sizeof(Node));
  t->num = V++;
  t->adj = az;
  t->oldadj = az;
  t->next_node = head->next_node;
  head->next_node = t;
  return t;
}

/* --------------------------------------------------------
  void AddLink(Node *v1, Node *v2)
 
  Adds a directional link between node v1 and v2.  This
  just adds node v2 to node v1's adjacency list. Also checks
  for duplication.
  --------------------------------------------------------- */

void AddLink(Node *v1, Node *v2) {

  AdjList *l;

  /* First make sure we don't already have this link */

  l = v1->adj;
  while (l != az) {
    if ((Node *) l->v == v2) return;
    l = l->next;
  }
  if (v1 == v2) return;

  /* Create a new adjacency entry */

  l = (AdjList *) malloc(sizeof(AdjList));
  l->v = (Node *) v2;
  l->next = v1->adj;
  v1->adj = l;

}

/* -----------------------------------------------------------
   void FreeAdjList(AdjList *l)

   Frees the memory used by a adjacency list
   ----------------------------------------------------------- */

void FreeAdjList(AdjList *l) {

  AdjList *l1;
  while (l != az) {
    l1 = l->next;
    free(l);
    l = l1;
  }

}

/* -----------------------------------------------------------
   PrintNodes()

   A debugging function for printing out all of the nodes and
   and their adjacency lists.
   ------------------------------------------------------------ */

void PrintNodes() {

  Node *n, *v;
  AdjList *l;

  /* Print out all of the nodes */

  n = head->next_node;
  while (n != z) {
    printf("Node %d : ", n->num);
    l = n->adj;
    while (l != az) {
      v = (Node *) l->v;
      printf("%d ", v->num);
      l = l->next;
    }
    printf("\n");
    n = n->next_node;
  }

}

/* -------------------------------------------------------------
   find_Connected(Node *n)

   A function that finds all of the nodes connected to node N.
   Sets the node->visit flag to 1 for each node that is connected
   to n.   You'll probably want to set the node->visit flags to 0
   before calling this the first time.
   ------------------------------------------------------------- */

void find_Connected(Node *n) {
  AdjList *l;
  Node *v;

  if (n->visit) return;    /* Return if already seen this node */
  n->visit = 1;

  /* Walk down my adjacency list and look at those nodes */

  l = n->adj;
  while (l != az) {
    v = (Node *) l->v;
    find_Connected(v);
    l = l->next;
  }
}

/* --------------------------------------------------------------
   Connected(Node *n)

   Finds all of the nodes connected to node n.   Basically this is
   just the initialization code that sets all of the n->visit bytes
   to 0 and calls find_Connected.
   --------------------------------------------------------------- */
   
void Connected(Node *n) {

  Node *v;
  v = head->next_node;
  while (v != z) {
    v->visit = 0;
    v = v->next_node;
  }
  find_Connected(n);
}

/* --------------------------------------------------------------
   Closure_Step()
   
   This function computes one step of a transitive closure
   algorithm by adding more links.    Basically, whereever
   we have a link n1 --> n2 --> n3, this function will add
   the link n1 --> n3.    Call repeatedly to compute the
   transitive closure.

   Note : this is pretty ugly due to our choice of data structures
   --------------------------------------------------------------- */

void Closure_Step() {

  Node    *v,*v1,*n;
  AdjList *l, *l1, *l2;
  int  found;

  n = head->next_node;

  /* First save old adjacency lists and clear new ones */
  while (n != z) {
    n->oldadj = n->adj;
    n->adj = az;
    n = n->next_node;
  }

  /* Now go figure out who my new nodes ares */

  n = head->next_node;
  while (n != z) {

    /* Go down my adjacency list and add arcs */

    l = n->oldadj;
    while (l != az) {    /* Walk down my adjacency list */
      v = (Node *) l->v;
      l1 = v->oldadj;    /* Find out who's connected to my neighbors */
      while (l1 != az) { 
	v1 = (Node *) l1->v;
	l2 = n->oldadj;
	found = 0;
	while (l2 != az) {
	  if ((Node *) l2->v == v1) found = 1;
	  l2 = l2->next;
	}
	if ((!found) && (n != v1))
	  AddLink(n,v1);           /* Add an arc */
	l1 = l1->next;
      }
      l = l->next;
    }
    n = n->next_node;
  }

  /* Now connect everything back up again */

  n = head->next_node;
  while (n != z) {
    l = n->oldadj;
    if (l != az) {
      while (l->next != az) l = l->next;
      l->next = n->adj;  
      n->adj = n->oldadj;
      n->oldadj = az;
    }
    n = n->next_node;
  }
}

/* ----------------------------------------------------------------
   Shortest Path

   The following few functions compute the shortest path between
   two nodes.    This is done by using a breadth-first search
   algorithm.   Thus, I also need to implement some sort of queuing
   system as shown below 
   ---------------------------------------------------------------- */

typedef struct q {
  Node *n;
  struct q *next;
  struct q *prev;
} QNode;

QNode *qhead;
QNode *qtail;

/* Put something on the queue */

void queue_put(Node *n) {
  QNode *q;

  if (!qhead) {
    qhead = (QNode *) malloc(sizeof(QNode));
    qtail = (QNode *) malloc(sizeof(QNode));
    qhead->next = qtail;
    qtail->next = qtail;
    qhead->prev = qhead;
    qtail->prev = qhead;
  }

  q = (QNode *) malloc(sizeof(QNode));
  q->n = n;
  q->next = qtail;
  q->prev = qtail->prev;
  q->prev->next = q;
  qtail->prev = q;

}

/* Take something off the queue */

Node *queue_get() {

  QNode *q;
  Node *n;

  q = qhead->next;
  if (q == qtail) return NULL;
  qhead->next = q->next;
  q->next->prev = qhead;
  n = q->n;
  free(q);
  return n;
}

/* -----------------------------------------------------------
   AdjList *FindShort(Node *n1, Node *n2)

   Finds the shortest path between node n1 and node n2.
   Returns a linked list of nodes in the path.   This can easily
   be expressed using the AdjList structure already defined.
   ----------------------------------------------------------- */

AdjList *FindShort(Node *n1, Node *n2) {

  Node *v, *v1;
  AdjList *l;
  AdjList *path;
  
  v = head->next_node;
  while (v != z) {
    v->visit = 0;
    v->oldadj = az;
    v = v->next_node;
  }

  queue_put(n1);
  n1->visit = 1;
  while ((v = queue_get())) {
    if (v == n2) 
      break;
    else {
      l = v->adj;
      while (l != az) {
	v1 = (Node *) l->v;
	if (!v1->visit) {
	  queue_put(v1);
	  v1->visit = 1;
	  v1->oldadj = (AdjList *) malloc(sizeof(AdjList));
	  v1->oldadj->v = v;
	  v1->oldadj->next = az;
	}
	l = l->next;
      }
    }
  }

  /* Flush out queue */
  while ((v1 = queue_get()));

  /* If v is non-null, then we found something */

  if (v) {
    /* Backtrack through parents to trace out path */
    path = (AdjList *) malloc(sizeof(AdjList));
    path->next = az;
    path->v = n2;
    while (v != n1) {
      v->oldadj->next = path;
      path = v->oldadj;
      v->visit = 1;
      v1 = (Node *) (v->oldadj->v);
      v->oldadj = az;
      v = v1;
    }
    l = (AdjList *) malloc(sizeof(AdjList));
    l->v = n1;
    l->next = path;
  } else {
    l = 0;
  }

  /* Go through and clean up */
  
  v = head->next_node;
  while (v != z) {
    if (v->oldadj != az) free(v->oldadj);
    v = v->next_node;
  }

  /* Return the path */

  return l;

}





