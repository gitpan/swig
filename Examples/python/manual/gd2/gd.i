%module gd
%{
#include "gd.h"
%}

%include "/usr/local/include/gd.h"

%addmethods gdPoint {
  gdPoint(int npoints) {
    return (gdPoint *) malloc(npoints*sizeof(gdPoint));
  };
  ~gdPoint() {
    free(self);
  };
  gdPoint *__getitem__(int i) {
    return self+i;
  };
};

FILE *fopen(char *, char *);
void fclose(FILE *f);

%include embed.i
