%title "Perl5 Shadow Class Example"
//
// This SWIG module shows how shadow classes can be created
// in Perl5
%module shadow
%{

typedef struct Vector {
	double x;
	double y;
	double z;
} Vector;

Vector *new_Vector(double x, double y, double z) {
	Vector *v;
	v = (Vector *) malloc(sizeof(Vector));
	v->x = x;
	v->y = y;
	v->z = z;
	return v;
}

// A more complex data structure

typedef struct Particle {
    Vector r;
    Vector v;
    Vector f;
    int    type;
} Particle;

Particle   part;

typedef struct Bond {
    Particle *p1;
    Particle *p2;
    double   strength;
} Bond;

Bond * new_Bond(Particle *p1, Particle *p2) {
    Bond *b;
    b = (Bond *) malloc(sizeof(Bond));
    b->p1 = p1;
    b->p2 = p2;
    b->strength = 0;
    return b;
}

void print_Particle(Particle *p) {
    printf("r = [%g, %g, %g]\n", p->r.x, p->r.y, p->r.z);
    printf("v = [%g, %g, %g]\n", p->v.x, p->v.y, p->v.z);
    printf("f = [%g, %g, %g]\n", p->f.x, p->f.y, p->f.z);
    printf("type = %d\n", p->type);
}

class List {
  private:
    struct node {
	char *value;
	node *next;
    };
    node *head;
    node *z;
  public:
    List() {
	head = new node();
	z = new node();
	head->next = z;
	z->next = z;
    };

    List(int n) {
	head = new node();
	z = new node();
	head->next = z;
	z->next = z;
    };
    ~List() {
	node *n,*n1;
	n = head->next;
	while (n != z) {
	    n1 = n->next;
	    delete n;
	    n = n1;
	}
	delete head;
	delete z;
    }
    void insert(char *value) {
	node *n;
	n = new node();
	n->value = new char[strlen(value)+1];
	strcpy(n->value,value);
	n->next = head->next;
	head->next = n;
    }
    int search(char *value) {
	node *n;
	n = head->next;
	while (n != z) {
	    if (strcmp(value,n->value) == 0) return 1;
	    n = n->next;
	}
	return 0;
    }
    char *get(int i) {
	node *n;
	int j;
	n = head->next;
	for (j = 0; j < i; j++) {
	    if (n == z) return "";
	    n = n->next;
	}
	return n->value;
    }
    void print() {
	node *n;
	n = head->next;
	while (n != z) {
	    printf("%s ", n->value);
	    n = n->next;
	}
	printf("\n");
    }
};

void print_list(List &l) {
	l.print();
}

#define PI   3.141592654

class Shape {
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

Circle *a_circle;

double My_variable = 3.56;

%}

// First a simple structure (ala C)

struct Vector {
	double x;
	double y;
	double z;
};

Vector *new_Vector(double x = 0,double y = 0,double z = 0);

struct Particle {
    Particle();
    ~Particle();
    Vector r;
    Vector v;
    Vector f;
    int    type;
};

Particle part;

void print_Particle(Particle *);

struct Bond {
    Particle *p1;
    Particle *p2;
    double   strength;
};

Bond *new_Bond(Particle *, Particle *);

class List {
  public:
    List();
%name(List_max)    List(int n);
    ~List();
    void insert(char *value);
    int search(char *value);
    char *get(int i);
%name(print_list)  void print();
    const int FOOBAR = 7;
};

void print_list(List &l);

class Shape {
public:
  virtual double area() = 0;
  virtual double perimeter() = 0;
  void    set_center(double _x, double _y);
  void    print_center();
};

class Circle: public Shape {
 public:
  Circle(double _r);
  double area();
  double perimeter();
};

class Square : public Shape {
public:
  Square(double _w);
  double area();
  double perimeter();

};

%section "Miscellaneous"

Circle *a_circle;

// Static constructors are PURE EVIL.   Here's how you can 
// initialize a C++ object upon loading of a C++ module.

%init %{
	a_circle = new Circle(5.0);
%}

%inline %{
	void print_part() {
		printf("part : \n");
		printf("       [%g,%g,%g]\n",part.r.x,part.r.y,part.r.z);
		printf("       [%g,%g,%g]\n",part.v.x,part.v.y,part.v.z);
	}
%}

int system(char *);
double My_variable;

#define E 2.71828

