%title "Shapes"
/* This module contains a few simple class definitions to test
SWIG's inheritance handling. */

%module shapes
%{
#include "shapes.h"
%}

// An inheritance example with shapes

#define PI 3.141592654

class Shape {
/* Shape base class */
private:
  double xc, yc;
public:
  virtual double area() = 0;
  virtual double perimeter() = 0;
  void    set_center(double _x, double _y) {
    xc = _x;
    yc = _y;
  };
  void    print_center() {
    printf("xc = %g, yc = %g\n", xc, yc);
  };
};

class Circle: public Shape {
/* Circle class.   Inherits from Shape */
 private:
  double radius;
 public:
  Circle(double _r) {
    radius = _r;
  };
  double area() {
    return PI*radius*radius;
  };
  double perimeter() {
    return 2*PI*radius;
  };
};


class SolidCircle: public Circle {
 private:
  int color;
 public:
  SolidCircle(double _r, int _c) {
    radius = _r;
    color = _c;
  };
};

class Square : public Shape {
/* Square class. Inherits from Shape */
private:
  double width;
public:
  Square(double _w) {
    width = _w;
  };
  double area() {
    return width*width;
  };
  double perimeter() {
    return 4*width;
  };
};


// This method should show up in all derived classes.

%addmethods Shape {
	void identify() {
		printf("I'm a shape with area %g\n",self->area());
	}
}



