/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"
WRAPPER : char *return_string();

C++ CLASS DECLARATION : class Foo
WRAPPER : Foo *create_foo2();

C++ CLASS START : class Foo  ========================================

        CONSTRUCTOR   : Foo *Foo();
        DESTRUCTOR    : ~Foo();
        MEMBER FUNC   : Foo *create_foo();

C++ CLASS END ===================================================

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : return_string --> char *return_string();
     ADD COMMAND    : create_foo2 --> Foo *create_foo2();

     // C++ CLASS START : class Foo
     ADD CONSTRUCT  : Foo --> Foo *Foo();
     ADD DESTRUCT  : Foo --> ~Foo();
     ADD MEMBER FUN : create_foo --> Foo *create_foo();
     // C++ CLASS END 

}  /* END INIT */
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_signed_long","_long",0);
	 SWIG_RegisterMapping("_class_Foo","_Foo",0);
	 SWIG_RegisterMapping("_long","_unsigned_long",0);
	 SWIG_RegisterMapping("_long","_signed_long",0);
	 SWIG_RegisterMapping("_unsigned_long","_long",0);
	 SWIG_RegisterMapping("_signed_int","_int",0);
	 SWIG_RegisterMapping("_unsigned_short","_short",0);
	 SWIG_RegisterMapping("_signed_short","_short",0);
	 SWIG_RegisterMapping("_unsigned_int","_int",0);
	 SWIG_RegisterMapping("_short","_unsigned_short",0);
	 SWIG_RegisterMapping("_short","_signed_short",0);
	 SWIG_RegisterMapping("_int","_unsigned_int",0);
	 SWIG_RegisterMapping("_int","_signed_int",0);
	 SWIG_RegisterMapping("_Foo","_class_Foo",0);
