/* Simple example from documentation */
/* File : example.c */

int fact(int n) {
  if (n <= 1) return 1;
  else return n*fact(n-1);
}

