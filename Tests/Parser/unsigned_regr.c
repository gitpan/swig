/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"
WRAPPER : unsigned foo(unsigned );

WRAPPER : signed bar(signed );

WRAPPER : short grok(long );

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : foo --> unsigned foo(unsigned );
     ADD COMMAND    : bar --> signed bar(signed );
     ADD COMMAND    : grok --> short grok(long );
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
