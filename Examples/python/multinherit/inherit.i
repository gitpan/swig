%module inherit

%inline %{
class A {
public:
  A() { printf("Creating A\n");}
  ~A() { printf("Destroying A\n");}
  void *foo() {
	printf("A->foo()\n");
	return (void *) this;
  };
  double x; 
};

class B {
public:
  B() { printf("Creating B\n");}
  ~B() { printf("Destroying B\n");}
  void *bar() {
    printf("B->bar()\n");
    return (void *) this;
  };
  double y;
};

class C {
public:
  C() {
    a = 7;
    b = 2.81828;
    ptr = (void *) 1234;
  };
  int a;
  double b;
  void  *ptr;
};

class D : public A, public B, public C {
public:
  D() { printf("Creating D\n");
        x = 1;
        y = 2;
        z = 3;
      }
  ~D() { printf("Destroying D\n"); }
  void *grok() {
    printf("D->grok()\n");
    return (void *) this;
  };
  double z;
};

%}


