%module pde,gdc
%{
#include "pde.h"
%}

%include pde.h

%{
  // Define a new Grid2d row class 
  
  struct Grid2dRow {
    Grid2d *g;       // Grid
    int    row;      // Row number
    double __getitem__(int i) {
      return g->data[row][i];
    };
    void __setitem__(int i, double val) {
      g->data[row][i] = val;
    };
  };
%}

struct Grid2dRow {
  Grid2d *g;
  int     row;
  double  __getitem__(int i);
  void    __setitem__(int i, double val);
};

%addmethods Grid2d {
  Grid2dRow __getitem__(int i) {
    Grid2dRow r;
    r.g = self;
    r.row = i;
    return r;
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





