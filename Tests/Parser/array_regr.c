/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"


extern int foo(int [4],int [4][4],int [4][4][3]);
extern int func(int ,char *[]);
extern float matrix(MATRIX4 );
extern float matrixofmatrix(MATRIX4 [4]);
WRAPPER : int foo(int [4],int [4][4],int [4][4][3]);

WRAPPER : int func(int ,char *[]);

WRAPPER : float matrix(MATRIX4 );

WRAPPER : float matrixofmatrix(MATRIX4 [4]);

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : foo --> int foo(int [4],int [4][4],int [4][4][3]);
     ADD COMMAND    : func --> int func(int ,char *[]);
     ADD COMMAND    : matrix --> float matrix(MATRIX4 );
     ADD COMMAND    : matrixofmatrix --> float matrixofmatrix(MATRIX4 [4]);
}  /* END INIT */
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_signed_long","_long",0);
	 SWIG_RegisterMapping("_long","_unsigned_long",0);
	 SWIG_RegisterMapping("_long","_signed_long",0);
	 SWIG_RegisterMapping("_MATRIX4","_float_p",0);
	 SWIG_RegisterMapping("_float_p","_MATRIX4",0);
	 SWIG_RegisterMapping("_unsigned_long","_long",0);
	 SWIG_RegisterMapping("_signed_int","_int",0);
	 SWIG_RegisterMapping("_unsigned_short","_short",0);
	 SWIG_RegisterMapping("_signed_short","_short",0);
	 SWIG_RegisterMapping("_unsigned_int","_int",0);
	 SWIG_RegisterMapping("_short","_unsigned_short",0);
	 SWIG_RegisterMapping("_short","_signed_short",0);
	 SWIG_RegisterMapping("_int","_unsigned_int",0);
	 SWIG_RegisterMapping("_int","_signed_int",0);
