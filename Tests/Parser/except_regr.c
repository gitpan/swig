/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"
WRAPPER : int f1(double );

WRAPPER : int f2(double );

WRAPPER : int f3(int );

C++ CLASS DECLARATION : class Foo
C++ CLASS START : class Foo  ========================================

        MEMBER FUNC   : int f1(double );

        MEMBER FUNC   : int f2(double );

        MEMBER FUNC   : int f3(double );

C++ CLASS END ===================================================

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : f1 --> int f1(double );
     ADD COMMAND    : f2 --> int f2(double );
     ADD COMMAND    : f3 --> int f3(int );

     // C++ CLASS START : class Foo
     ADD MEMBER FUN : f1 --> int f1(double );
     ADD MEMBER FUN : f2 --> int f2(double );
     ADD MEMBER FUN : f3 --> int f3(double );
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
