/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"


struct Vector {
	double x,y,z;
};

class FooBar {
public:
    FooBar(Vector &v) {
	vec = v;
    }
    Vector vec;
    void dump() {
        printf("vec.x = %g, vec.y = %g, vec.z = %g\n", vec.x,vec.y,vec.z);
    }
};

C++ CLASS DECLARATION : struct Vector
C++ CLASS DECLARATION : class FooBar
C++ CLASS START : struct Vector  ========================================

        CONSTRUCTOR   : Vector *Vector();
        DESTRUCTOR    : ~Vector();
        ATTRIBUTE     : double  x; 
        ATTRIBUTE     : double  y; 
        ATTRIBUTE     : double  z; 
C++ CLASS END ===================================================

C++ CLASS START : class FooBar  ========================================

        CONSTRUCTOR   : FooBar *FooBar(Vector &);
        ATTRIBUTE     : Vector  vec; 
        MEMBER FUNC   : void dump();

C++ CLASS END ===================================================

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {

     // C++ CLASS START : struct Vector
     ADD CONSTRUCT  : Vector --> Vector *Vector();
     ADD DESTRUCT  : Vector --> ~Vector();
     ADD MEMBER     : x --> double  x; 
     ADD MEMBER     : y --> double  y; 
     ADD MEMBER     : z --> double  z; 
     // C++ CLASS END 


     // C++ CLASS START : class FooBar
     ADD CONSTRUCT  : FooBar --> FooBar *FooBar(Vector &);
     ADD MEMBER     : vec --> Vector  vec; 
     ADD MEMBER FUN : dump --> void dump();
     // C++ CLASS END 

}  /* END INIT */
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_signed_long","_long",0);
	 SWIG_RegisterMapping("_Vector","_struct_Vector",0);
	 SWIG_RegisterMapping("_long","_unsigned_long",0);
	 SWIG_RegisterMapping("_long","_signed_long",0);
	 SWIG_RegisterMapping("_unsigned_long","_long",0);
	 SWIG_RegisterMapping("_FooBar","_class_FooBar",0);
	 SWIG_RegisterMapping("_signed_int","_int",0);
	 SWIG_RegisterMapping("_unsigned_short","_short",0);
	 SWIG_RegisterMapping("_class_FooBar","_FooBar",0);
	 SWIG_RegisterMapping("_signed_short","_short",0);
	 SWIG_RegisterMapping("_unsigned_int","_int",0);
	 SWIG_RegisterMapping("_short","_unsigned_short",0);
	 SWIG_RegisterMapping("_short","_signed_short",0);
	 SWIG_RegisterMapping("_int","_unsigned_int",0);
	 SWIG_RegisterMapping("_int","_signed_int",0);
	 SWIG_RegisterMapping("_struct_Vector","_Vector",0);
