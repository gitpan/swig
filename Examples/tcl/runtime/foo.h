#ifndef FOO_H
#define FOO_H
#include "base.h"

class Foo : public Base {
public:
  int foo_var;
  Foo() { };
  ~Foo() { };
  void foo_method() {
    printf("I'm a foo method\n");
  }
};

#endif

