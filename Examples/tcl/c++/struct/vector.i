//
// SWIG File for a normal "structure"
//

%module vector
%{

#include <math.h>

struct Vector {
  double x,y,z;
};

typedef struct Vector Vector;
void Vector_print(Vector *v) {
  printf("x = %g, y = %g, z = %g\n", v->x, v->y, v->z);
}

void Vector_add(struct Vector *v1, struct Vector *v2, struct Vector *v3) {
  v3->x = v1->x + v2->x;
  v3->y = v1->y + v2->y;
  v3->z = v1->z + v2->z;
}

double Vector_mag(struct Vector *v) {
  return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}

Vector V;
%}

// This generates default constructors for the structure below
%pragma make_default

// SWIG Stuff

struct Vector {
  double x,y,z;
};

void Vector_print(Vector *v);
void Vector_add(struct Vector *v1, struct Vector *v2, struct Vector *v3);
double Vector_mag(struct Vector *v);
Vector V;




