%module pde
%{
#include "pde.h"
%}

%include pde.h

// Add a few "helper" functions to extract grid data 


%inline %{

double  Grid2d_get(Grid2d *g, int i, int j) {
      return g->data[i][j];
}
void    Grid2d_set(Grid2d *g, int i, int j, double val) {
      g->data[i][j] = val;
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
%}

#ifdef STATIC
%include embed.i
#endif

