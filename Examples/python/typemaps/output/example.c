
/* Some functions involving pointers */

void add(double *a, double *b, double *result) {
  *result = *a + *b;
}
void sub(double *a, double *b, double *result) {
  *result = *a - *b;
}
void mul(double *a, double *b, double *result) {
  *result = (*a)*(*b);
}
void fdiv(double *a, double *b, double *result) {
  *result = (*a)/(*b);
}
void neg(double *x) {
  *x = -(*x);
}

