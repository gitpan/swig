#include <stdio.h>
#include "list.h"
#include <string.h>

List::List() {
	head = new node();
	z = new node();
	head->next = z;
	z->next = z;
    };
List::~List() {
	node *n,*n1;
	n = head->next;
	while (n != z) {
	    n1 = n->next;
	    delete n;
	    n = n1;
	}
	delete head;
	delete z;
    }
void List::insert(char *value) {
	node *n;
	n = new node();
	n->value = new char[strlen(value)+1];
	strcpy(n->value,value);
	n->next = head->next;
	head->next = n;
    }
int List::search(char *value) {
	node *n;
	n = head->next;
	while (n != z) {
	    if (strcmp(value,n->value) == 0) return 1;
	    n = n->next;
	}
	return 0;
    }
char *List::get(int i) {
	node *n;
	int j;
	n = head->next;
	for (j = 0; j < i; j++) {
	    if (n == z) return "";
	    n = n->next;
	}
	return n->value;
    }
void List::output() {
	node *n;
	n = head->next;
	while (n != z) {
	    printf("%s ", n->value);
	    n = n->next;
	}
	printf("\n");
    }

