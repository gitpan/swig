#include "list.h"
#include <stdio.h>
#include <string.h>

List::List() {
   head = new node;
   z = new node;
   head->value = "__head__";
   z->value = "__end__";
   head->next = z;
   z->next = z;
   length = 0;
 }

List::~List() {
  node *n,*n1;
  n = head->next;
  while (n != z) {
    n1 = n->next;
    delete n->value;
    delete(n);
    n = n1;
  }
  delete head;
  delete z;
}

int List::search(char *key) {

  node *n;
  n = head->next;
  while (n != z) {
    if (strcmp(n->value,key) == 0)
      return 1;
    n = n->next;
  }
  return 0;
}

void List::insert(char *key) {
  node *n;
  n = new node;
  n->value = new char[strlen(key)+1];
  strcpy(n->value, key);
  n->next = head->next;
  head->next = n;
  length++;
}

void List::remove(char *key) {
  node *n1, *n2;

  n1 = head->next;
  n2 = head;

  while (n1 != z) {
    if (strcmp(n1->value,key) == 0) {
      n2->next = n1->next;
      delete n1->value;
      delete n1;
      length--;
      return;
    }
    n2 = n1;
    n1 = n1->next;
  }
}

char *List::get(int count) {
  node *n;
  int i;

  n = head->next;
  i = 0;
  while ((n != z) && (i < count)) {
    n = n->next;
    i++;
  }

  return n->value;

}

void List::print(List *l) {
  node *n;

  n = l->head->next;
  while (n != l->z) {
    fprintf(stdout,"%s\n", n->value);
    n = n->next;
  }

}


void List::print1(List &l) {
  node *n;

  n = l.head->next;
  while (n != l.z) {
    fprintf(stdout,"%s\n", n->value);
    n = n->next;
  }

}

  


