#ifndef BASE_H
#define BASE_H

#include <stdio.h>

class Base {
public:
  int   base_var;
  Base() { };
  ~Base() { };
  void  base_method() {
    printf("I'm a base-class method\n");
  }
};

#endif
