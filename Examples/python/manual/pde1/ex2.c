// Test performance of just straight C++

#include "pde.h"
#include <stdio.h>

int main(int argc, char **argv) {

  Heat2d *h;

  h = new Heat2d(50,50);
  printf("Dt = %g\n", h->dt);
  
  h->set_temp(1.0);

  for (int i = 0; i < 25; i++) {
    h->solve(100);
    printf("time = %g\n", h->time);
  }
}
