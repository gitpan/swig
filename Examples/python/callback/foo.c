#include <stdio.h>
#include "widget.h"

/* This function is a normal C callback function */

double foo(double a, void *clientdata) {
  printf("Callback function implemented in C : Received %g\n",a);
  return a;
}

/* This function fills in an array of values from the callback function */

void fill_array(Widget *w, double *data, int nitems) {
  int i;
  for (i = 0; i < nitems; i++) 
    data[i] = widget_op(w, (double) i);
}

  

  
  
