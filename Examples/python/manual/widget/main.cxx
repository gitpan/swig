// Simple main program to test out our widget

#include <stdio.h>
#include "widget.h"
#include <math.h>

// Callback function

double my_func(double a, void *clientdata) {
  return sin(a);
}

int main(int argc, char **argv) {
  PlotWidget *w;
  FILE *f;

  w = new PlotWidget(500,500,-6.3,-1.5,6.3,1.5);
  w->set_method(my_func,0);
  w->plot();
  f = fopen("plot.gif","w");
  w->save(f);

  printf("wrote plot.gif\n");
}




  
