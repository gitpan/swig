/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"
WRAPPER : double bar(int );

WRAPPER : int grok(double );

WRAPPER : double frob2(double );

WRAPPER : int grok2(int );

WRAPPER : int  a; 
WRAPPER : double  d; 
SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : bar --> double bar(int );
     ADD COMMAND    : grok --> int grok(double );
     ADD COMMAND    : frob2 --> double frob2(double );
     ADD COMMAND    : grok2 --> int grok2(int );
     ADD VARIABLE   : a --> int  a; 
     ADD VARIABLE   : d --> double  d; 
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
