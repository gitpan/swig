/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"

double inline1(double &a) {
   inlined definition 1
}
double inline2() {
   inlined definition 2
}
double inline3() {
   inlined definition 3
}
int inline4();

int a;

static int foo1(int) {
   A static, but inlined function
}


#define BAR  4
static double foo()
{
   inlined definition 4;
}
WRAPPER : double inline1(double &);

WRAPPER : double inline2();

WRAPPER : double inline3();

WRAPPER : int inline4();

WRAPPER : int  a; 
WRAPPER : int foo1(int );

WRAPPER : double bar();

WRAPPER : double grok();

WRAPPER : double foo();

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : inline1 --> double inline1(double &);
     ADD COMMAND    : inline2 --> double inline2();
     ADD COMMAND    : inline3 --> double inline3();
     ADD COMMAND    : inline4 --> int inline4();
     ADD VARIABLE   : a --> int  a; 
     ADD COMMAND    : foo1 --> int foo1(int );
     ADD CONSTANT   : (int ) BAR = 4
     ADD COMMAND    : bar --> double bar();
     ADD COMMAND    : grok --> double grok();
     ADD COMMAND    : foo --> double foo();
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
