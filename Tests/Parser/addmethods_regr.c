/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"
C++ CLASS DECLARATION : struct Foo
C++ CLASS DECLARATION : struct Foo2
C++ CLASS DECLARATION : struct Foo3
C++ CLASS DECLARATION : class BarBase
C++ CLASS DECLARATION : class Bar
C++ CLASS DECLARATION : class EBase
C++ CLASS DECLARATION : class EE
C++ CLASS DECLARATION : class FF
C++ CLASS DECLARATION : struct Vector
C++ CLASS START : struct Foo  ========================================

        ATTRIBUTE     : int  x; 
        ATTRIBUTE     : int  y; 
        ATTRIBUTE     : int  z; 
        CONSTRUCTOR   : Foo *Foo();
        DESTRUCTOR    : ~Foo();
        MEMBER FUNC   : int bar();

        ATTRIBUTE     : double  a; 
C++ CLASS END ===================================================

C++ CLASS START : struct Foo2  ========================================

        CONSTRUCTOR   : Foo2 *Foo2();
        DESTRUCTOR    : ~Foo2();
        MEMBER FUNC   : int grok();

        STATIC FUNC   : int st_func(double );
        ATTRIBUTE     : double  x; 
        ATTRIBUTE     : double  y; 
        ATTRIBUTE     : double  z; 
C++ CLASS END ===================================================

C++ CLASS START : struct Foo3  ========================================

        MEMBER FUNC   : double bar(double );

        MEMBER FUNC   : double ref(Foo &,Foo &,Foo *);

        STATIC FUNC   : int grok(int );
C++ CLASS END ===================================================

C++ CLASS START : class BarBase  ========================================

        ATTRIBUTE     : int  x; 
        MEMBER FUNC   : int foo();

        CONSTRUCTOR   : BarBase *BarBase();
        DESTRUCTOR    : ~BarBase();
        MEMBER FUNC   : void added_method(double *);

C++ CLASS END ===================================================

C++ CLASS START : class Bar  ========================================

inheriting from baseclass : BarBase
static void *SwigBarToBarBase(void *ptr) {
    Bar *src;
    BarBase *dest;
    src = (Bar *) ptr;
    dest = (BarBase *) src;
    return (void *) dest;
}

        ATTRIBUTE     : int  y; 
        CONSTRUCTOR   : Bar *Bar();
        DESTRUCTOR    : ~Bar();
        ATTRIBUTE     : int  x; 
        MEMBER FUNC   : int foo();

        MEMBER FUNC   : void added_method(double *);

C++ CLASS END ===================================================

C++ CLASS START : class EE  ========================================

inheriting from baseclass : EBase
static void *SwigEEToEBase(void *ptr) {
    EE *src;
    EBase *dest;
    src = (EE *) ptr;
    dest = (EBase *) src;
    return (void *) dest;
}

        MEMBER FUNC   : void emethod(double );

        MEMBER FUNC   : void emethod2(double );

C++ CLASS END ===================================================

C++ CLASS START : class FF  ========================================

inheriting from baseclass : EE
static void *SwigFFToEE(void *ptr) {
    FF *src;
    EE *dest;
    src = (FF *) ptr;
    dest = (EE *) src;
    return (void *) dest;
}

static void *SwigFFToEBase(void *ptr) {
    FF *src;
    EBase *dest;
    src = (FF *) ptr;
    dest = (EBase *) src;
    return (void *) dest;
}

        MEMBER FUNC   : void emethod(double );

        MEMBER FUNC   : void emethod2(double );

C++ CLASS END ===================================================

C++ CLASS START : struct Vector  ========================================

        ATTRIBUTE     : double  x; 
        ATTRIBUTE     : double  y; 
        ATTRIBUTE     : double  z; 
C++ CLASS END ===================================================

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {

     // C++ CLASS START : struct Foo
     ADD MEMBER     : x --> int  x; 
     ADD MEMBER     : y --> int  y; 
     ADD MEMBER     : z --> int  z; 
     ADD CONSTRUCT  : Foo --> Foo *Foo();
     ADD DESTRUCT  : Foo --> ~Foo();
     ADD MEMBER FUN : bar --> int bar();
     ADD MEMBER     : a --> double  a; 
     // C++ CLASS END 


     // C++ CLASS START : struct Foo2
     ADD CONSTRUCT  : Foo2 --> Foo2 *Foo2();
     ADD DESTRUCT  : Foo2 --> ~Foo2();
     ADD MEMBER FUN : grok --> int grok();
     ADD STATIC FUNC: st_func --> int st_func(double );
     ADD MEMBER     : x --> double  x; 
     ADD MEMBER     : y --> double  y; 
     ADD MEMBER     : z --> double  z; 
     // C++ CLASS END 


     // C++ CLASS START : struct Foo3
     ADD MEMBER FUN : bar --> double bar(double );
     ADD MEMBER FUN : ref --> double ref(Foo &,Foo &,Foo *);
     ADD STATIC FUNC: grok --> int grok(int );
     // C++ CLASS END 


     // C++ CLASS START : class BarBase
     ADD MEMBER     : x --> int  x; 
     ADD MEMBER FUN : foo --> int foo();
     ADD CONSTRUCT  : BarBase --> BarBase *BarBase();
     ADD DESTRUCT  : BarBase --> ~BarBase();
     ADD MEMBER FUN : added_method --> void added_method(double *);
     // C++ CLASS END 


     // C++ CLASS START : class Bar
     ADD MEMBER     : y --> int  y; 
     ADD CONSTRUCT  : Bar --> Bar *Bar();
     ADD DESTRUCT  : Bar --> ~Bar();
     ADD MEMBER     : x --> int  x; 
     ADD MEMBER FUN : foo --> int foo();
     ADD MEMBER FUN : added_method --> void added_method(double *);
     // C++ CLASS END 


     // C++ CLASS START : class EE
     ADD MEMBER FUN : emethod --> void emethod(double );
     ADD MEMBER FUN : emethod2 --> void emethod2(double );
     // C++ CLASS END 


     // C++ CLASS START : class FF
     ADD MEMBER FUN : emethod --> void emethod(double );
     ADD MEMBER FUN : emethod2 --> void emethod2(double );
     // C++ CLASS END 


     // C++ CLASS START : struct Vector
     ADD MEMBER     : x --> double  x; 
     ADD MEMBER     : y --> double  y; 
     ADD MEMBER     : z --> double  z; 
     // C++ CLASS END 

}  /* END INIT */
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_signed_long","_long",0);
	 SWIG_RegisterMapping("_class_EE","_class_FF",SwigFFToEE);
	 SWIG_RegisterMapping("_class_EE","_FF",SwigFFToEE);
	 SWIG_RegisterMapping("_class_EE","_EE",0);
	 SWIG_RegisterMapping("_Vector","_struct_Vector",0);
	 SWIG_RegisterMapping("_class_FF","_FF",0);
	 SWIG_RegisterMapping("_long","_unsigned_long",0);
	 SWIG_RegisterMapping("_long","_signed_long",0);
	 SWIG_RegisterMapping("_EBase","_class_FF",SwigFFToEBase);
	 SWIG_RegisterMapping("_EBase","_FF",SwigFFToEBase);
	 SWIG_RegisterMapping("_EBase","_class_EE",SwigEEToEBase);
	 SWIG_RegisterMapping("_EBase","_EE",SwigEEToEBase);
	 SWIG_RegisterMapping("_EBase","_class_EBase",0);
	 SWIG_RegisterMapping("_struct_Foo2","_Foo2",0);
	 SWIG_RegisterMapping("_struct_Foo3","_Foo3",0);
	 SWIG_RegisterMapping("_Bar","_class_Bar",0);
	 SWIG_RegisterMapping("_class_BarBase","_class_Bar",SwigBarToBarBase);
	 SWIG_RegisterMapping("_class_BarBase","_Bar",SwigBarToBarBase);
	 SWIG_RegisterMapping("_class_BarBase","_BarBase",0);
	 SWIG_RegisterMapping("_class_Bar","_Bar",0);
	 SWIG_RegisterMapping("_unsigned_long","_long",0);
	 SWIG_RegisterMapping("_EE","_class_FF",SwigFFToEE);
	 SWIG_RegisterMapping("_EE","_FF",SwigFFToEE);
	 SWIG_RegisterMapping("_EE","_class_EE",0);
	 SWIG_RegisterMapping("_signed_int","_int",0);
	 SWIG_RegisterMapping("_struct_Foo","_Foo",0);
	 SWIG_RegisterMapping("_FF","_class_FF",0);
	 SWIG_RegisterMapping("_unsigned_short","_short",0);
	 SWIG_RegisterMapping("_signed_short","_short",0);
	 SWIG_RegisterMapping("_unsigned_int","_int",0);
	 SWIG_RegisterMapping("_short","_unsigned_short",0);
	 SWIG_RegisterMapping("_short","_signed_short",0);
	 SWIG_RegisterMapping("_class_EBase","_class_FF",SwigFFToEBase);
	 SWIG_RegisterMapping("_class_EBase","_FF",SwigFFToEBase);
	 SWIG_RegisterMapping("_class_EBase","_class_EE",SwigEEToEBase);
	 SWIG_RegisterMapping("_class_EBase","_EE",SwigEEToEBase);
	 SWIG_RegisterMapping("_class_EBase","_EBase",0);
	 SWIG_RegisterMapping("_int","_unsigned_int",0);
	 SWIG_RegisterMapping("_int","_signed_int",0);
	 SWIG_RegisterMapping("_struct_Vector","_Vector",0);
	 SWIG_RegisterMapping("_Foo","_struct_Foo",0);
	 SWIG_RegisterMapping("_Foo2","_struct_Foo2",0);
	 SWIG_RegisterMapping("_Foo3","_struct_Foo3",0);
	 SWIG_RegisterMapping("_BarBase","_class_Bar",SwigBarToBarBase);
	 SWIG_RegisterMapping("_BarBase","_Bar",SwigBarToBarBase);
	 SWIG_RegisterMapping("_BarBase","_class_BarBase",0);
