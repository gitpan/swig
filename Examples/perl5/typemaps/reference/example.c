
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

void factor(int n, int *f1, int *f2) {
  int i;
  for (i = 2; i < n; i++) {
    if ((n/i)*i == n) {
      *f1 = i;
      *f2 = n/i;
      return;
    }
  }
  *f1 = 1;
  *f2 = n;
}
