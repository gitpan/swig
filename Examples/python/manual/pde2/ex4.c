// Test performance of just straight C++

#include "pde.h"
#include <stdio.h>

void initcond(Heat2d *h) {
  int i;
  h->set_temp(0.0);
  
  for (i = 0; i < h->grid->xpoints; i++)
    h->grid->data[i][0] = 1.0;

}
  
void dump(Heat2d *h, char *filename) {
  FILE *f;
  int   i,j;

  f = fopen(filename,"w");
  
  for (i = 0; i < h->grid->xpoints; i++)
    for (j = 0; j < h->grid->ypoints; j++)
      fprintf(f,"%0.17f\n",h->grid->data[i][j]);

  fclose(f);

}

int main(int argc, char **argv) {

  Heat2d *h;
  char    fname[256];
  int     fileno;

  h = new Heat2d(50,50);
  initcond(h);

  for (int i = 0; i < 25; i++) {
    h->solve(100);
    sprintf(fname,"Dat%d",fileno);
    dump(h,fname);
    printf("time = %g\n", h->time);
    fileno++;
  }
}
