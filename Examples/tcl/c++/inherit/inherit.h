#include <math.h>

class Point1 {
 public:
  double x;
  double mag() {
    return x;
  }
};

class Point2 : public Point1 {
 public:
  double y;
  double mag() {
    return sqrt(x*x + y*y);
  }
};

class Point3 : public Point2 {
 public:
  double z;
  double mag() {
    return sqrt(x*x + y*y + z*z);
  }
};




