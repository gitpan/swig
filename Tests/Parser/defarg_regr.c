/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"
WRAPPER : int foo(int ,double ,char *);

WRAPPER : int bar(double ,char *,char ,void *);

C++ CLASS DECLARATION : class Foo
WRAPPER : void grok(Foo *);

WRAPPER : void ref(String &);

C++ CLASS START : class Foo  ========================================

        C++ CONST     : (int ) LAGER = [None]
        C++ CONST     : (int ) ALE = [None]
        C++ CONST     : (int ) STOUT = [None]
        MEMBER FUNC   : void test(double ,Foo::SWIG );

        MEMBER FUNC   : void test2(double ,Foo::SWIG );

C++ CLASS END ===================================================

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : foo --> int foo(int ,double ,char *);
     ADD COMMAND    : bar --> int bar(double ,char *,char ,void *);
     ADD COMMAND    : grok --> void grok(Foo *);
     ADD COMMAND    : ref --> void ref(String &);

     // C++ CLASS START : class Foo
     ADD C++ CONST  : LAGER --> (int ) = [None]
     ADD C++ CONST  : ALE --> (int ) = [None]
     ADD C++ CONST  : STOUT --> (int ) = [None]
     ADD MEMBER FUN : test --> void test(double ,Foo::SWIG );
     ADD MEMBER FUN : test2 --> void test2(double ,Foo::SWIG );
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
