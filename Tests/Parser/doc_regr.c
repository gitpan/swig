/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"


WRAPPER : int foo(int );

WRAPPER : double bar(double );

WRAPPER : double grok(int );

WRAPPER : int frob(int );

WRAPPER : double foobar(double );

WRAPPER : double spam(int );

WRAPPER : int spif(double );

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : foo --> int foo(int );
     ADD COMMAND    : bar --> double bar(double );
     ADD COMMAND    : grok --> double grok(int );
     ADD COMMAND    : frob --> int frob(int );
     ADD COMMAND    : foobar --> double foobar(double );
     ADD COMMAND    : spam --> double spam(int );
     ADD COMMAND    : spif --> int spif(double );
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
