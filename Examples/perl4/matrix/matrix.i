//
// FILE : matrix.i

%init Matrix_init
%{

void set_m(double **M, int i, int j, double val) {
  M[i][j] = val;
}

double get_m(double **M, int i, int j) {
  return M[i][j];
}
%}

%section "Matrix Operations"
extern double **new_matrix();
/* Creates a new matrix and returns a pointer to it */

extern void   destroy_matrix(double **M);
/* Destroys the matrix M */

extern void print_matrix(double **M);
/* Prints out the matrix M */

extern void   set_m(double **M, int i, int j, double val);
/* Sets M[i][j] = val*/

extern double get_m(double **M, int i, int j);
/* Returns M[i][j] */

extern void   mat_mult(double **a, double **b, double **c);
/* Multiplies matrix a by b and places the result in c*/





