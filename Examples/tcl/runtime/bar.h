#ifndef BAR_H
#define BAR_H
#include "base.h"

class Bar : public Base {
public:
  int bar_var;
  Bar() { };
  ~Bar() { };
  void bar_method() {
    printf("I'm a bar method\n");
  }
};

#endif

