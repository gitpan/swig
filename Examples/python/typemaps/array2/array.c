/* Some C functions for manipulating arrays */

#include <stdio.h>

void add(double a[4], double b[4], double out[4]) {
  int i;
  for (i = 0; i < 4; i++)
    out[i] = a[i] + b[i];
}

double *new_double(int n) {
  int i;
  double *a = (double *) malloc(n*sizeof(double));
  for (i = 0; i < n; i++) a[i] = 0.0;
  return a;
};

void print2d(double a[4][4]) {
  int i,j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      printf("[%d][%d] = %g\n",i,j,a[i][j]);
};

void printdoubleptr(double *a) {
  printf("%g\n",*a);
}


