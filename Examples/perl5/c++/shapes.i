%module shapes
%{
#include "shapes.h"
%}

// An inheritance example with shapes

#define PI 3.141592654

class Shape {
private:
  double xc, yc;
public:
  virtual double area() = 0;
  virtual double perimeter() = 0;
  void    set_center(double _x = 0, double _y = 0) {
    xc = _x;
    yc = _y;
  };
  void    print_center() {
    printf("xc = %g, yc = %g\n", xc, yc);
  };
};

class Circle: public Shape {
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

class Square : public Shape {
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




