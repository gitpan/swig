/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"
WRAPPER : void foo(vector< complex > *,vector< int > *);

WRAPPER : void foo2(vector< complex > &,vector< int > &);

WRAPPER : void foo3(pair< complex,double > *,triple< int,int,double > *);

WRAPPER : void foo4(pair< unsigned int,double > *,triple< const unsigned int,double,complex > *);

WRAPPER : int bar();

WRAPPER : int bar1();

WRAPPER : int bar2();

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : foo --> void foo(vector< complex > *,vector< int > *);
     ADD COMMAND    : foo2 --> void foo2(vector< complex > &,vector< int > &);
     ADD COMMAND    : foo3 --> void foo3(pair< complex,double > *,triple< int,int,double > *);
     ADD COMMAND    : foo4 --> void foo4(pair< unsigned int,double > *,triple< const unsigned int,double,complex > *);
     ADD COMMAND    : bar --> int bar();
     ADD COMMAND    : bar1 --> int bar1();
     ADD COMMAND    : bar2 --> int bar2();
}  /* END INIT */
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_signed_long","_long",0);
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
