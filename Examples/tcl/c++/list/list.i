%module List
%{

#include "list.h"

%}

// Very simple C++ examples

%text %{
This example implements a very simple linked list that you can search,
insert, remove, and get specific items.
%}

%section "List Class"

class List {
public:
  List();  // Create a new list
  ~List(); // Destroy a list
  int  search(char *value);
/* Search the list for the given value.  Returns 1 if found, 0 if not. */
  void insert(char *);  // Insert a new item into the list
  void remove(char *);  // Remove item from list
  char *get(int n);     // Get the nth item in the list
  int  length;          // The current length of the list
static void print(List *l);  // Print out the contents of the list
static void print1(List &l);
};

%section "Misc"

int rand();   // Generate a random number


  
      

  
      



