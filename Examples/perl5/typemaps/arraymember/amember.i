
// This file shows how to remap the treatment of a structure member

%module amember

// Tell SWIG how to set any class member of type char[32]

%typemap(memberin) char [32] {
    strncpy($target,$source,31);
};

// Now a structure with a string member

%inline %{

typedef struct {
       char name[32];
       char address[32];
} Person;

Person *new_Person() {
	return (Person *) malloc(sizeof(Person));
};

%}

