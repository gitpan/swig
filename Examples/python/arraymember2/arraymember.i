// This file shows how one can access array members of structures and
// classes.

%module arraymember
%inline %{
#include "struct.h"

/* Create a structure for holding integer pointers */
typedef struct {
     int *iptr;
} IntArray;
%}

%addmethods IntArray {
  IntArray(int *iptr) {
    IntArray *i = (IntArray *) malloc(sizeof(IntArray));
    i->iptr = iptr;
    return i;
  }
  ~IntArray() {
    free(self);
  }
  int __getitem__(int index) {
    return self->iptr[index];
  }
  void __setitem__(int index, int val) {
    self->iptr[index] = val;
  }
};

// Now a "clever" typemap

// Return an IntArray instead of an int *
%typemap(memberout) IntArray * {
  static IntArray i;
  i.iptr = $source;
  $target = &i;
}

// Set an IntArray
%typemap(memberin) IntArray * {
  $target = $source->iptr;
}
  
// Now declare your structure (but in a different way).

struct foo {
  int a;
  IntArray *b;
};

// A helper function

%inline %{
  
  struct foo *bar(int n) {
    struct foo *f = (struct foo *) malloc(sizeof(struct foo));
    int i;
    f->a = n;
    f->b = (int *) malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
      f->b[i] = i;
    return f;
  }
%}


  
