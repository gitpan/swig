%module inherit
%{
#include "inherit.h"
%}

class Point1 {
 public:
  Point1();
  double x;
  double mag();
};

class Point2 : public Point1 {
 public:
  Point2();
  double y;
  double mag();
};

class Point3 : public Point2 {
 public:
  Point3();
  double z;
  double mag();
};




