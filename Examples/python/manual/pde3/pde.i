%module pde
%{
#include "pde.h"
%}


%include pde.h

%addmethods Grid2d {
  double get(int i, int j) {
    return self->data[i][j];
  };
  void set(int i, int j, double val) {
    self->data[i][j] = val;
  };
};

%addmethods Heat2d {
  void dump(char *filename) {
    FILE *f;
    int   i,j;

    f = fopen(filename,"w");
    for (i = 0; i < self->grid->xpoints; i++)
      for (j = 0; j < self->grid->ypoints; j++)
	fprintf(f,"%0.17f\n",self->grid->data[i][j]);
    fclose(f);
  };
};

#ifdef STATIC
%include embed.i
#endif





