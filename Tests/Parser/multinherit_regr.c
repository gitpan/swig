/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"
C++ CLASS DECLARATION : class a
C++ CLASS DECLARATION : class b
C++ CLASS DECLARATION : class c
C++ CLASS DECLARATION : class d
C++ CLASS DECLARATION : class foo
C++ CLASS DECLARATION : class foo1
C++ CLASS DECLARATION : class foo2
C++ CLASS DECLARATION : class foo3
C++ CLASS DECLARATION : class foo4
C++ CLASS DECLARATION : class foo5
C++ CLASS DECLARATION : class foo6
C++ CLASS DECLARATION : class foo7
C++ CLASS DECLARATION : class foo8
C++ CLASS DECLARATION : class A
C++ CLASS DECLARATION : class B
C++ CLASS DECLARATION : class C
C++ CLASS DECLARATION : class D
C++ CLASS START : class a  ========================================

C++ CLASS END ===================================================

C++ CLASS START : class b  ========================================

C++ CLASS END ===================================================

C++ CLASS START : class c  ========================================

C++ CLASS END ===================================================

C++ CLASS START : class d  ========================================

C++ CLASS END ===================================================

C++ CLASS START : class foo  ========================================

inheriting from baseclass : a b c d
static void *SwigfooToa(void *ptr) {
    foo *src;
    a *dest;
    src = (foo *) ptr;
    dest = (a *) src;
    return (void *) dest;
}

static void *SwigfooTob(void *ptr) {
    foo *src;
    b *dest;
    src = (foo *) ptr;
    dest = (b *) src;
    return (void *) dest;
}

static void *SwigfooToc(void *ptr) {
    foo *src;
    c *dest;
    src = (foo *) ptr;
    dest = (c *) src;
    return (void *) dest;
}

static void *SwigfooTod(void *ptr) {
    foo *src;
    d *dest;
    src = (foo *) ptr;
    dest = (d *) src;
    return (void *) dest;
}

        MEMBER FUNC   : double bar();

C++ CLASS END ===================================================

C++ CLASS START : class foo1  ========================================

inheriting from baseclass : a
static void *Swigfoo1Toa(void *ptr) {
    foo1 *src;
    a *dest;
    src = (foo1 *) ptr;
    dest = (a *) src;
    return (void *) dest;
}

        MEMBER FUNC   : double bar();

C++ CLASS END ===================================================

C++ CLASS START : class foo2  ========================================

inheriting from baseclass : a
static void *Swigfoo2Toa(void *ptr) {
    foo2 *src;
    a *dest;
    src = (foo2 *) ptr;
    dest = (a *) src;
    return (void *) dest;
}

        MEMBER FUNC   : double bar();

C++ CLASS END ===================================================

C++ CLASS START : class foo3  ========================================

inheriting from baseclass : a b c
static void *Swigfoo3Toa(void *ptr) {
    foo3 *src;
    a *dest;
    src = (foo3 *) ptr;
    dest = (a *) src;
    return (void *) dest;
}

static void *Swigfoo3Tob(void *ptr) {
    foo3 *src;
    b *dest;
    src = (foo3 *) ptr;
    dest = (b *) src;
    return (void *) dest;
}

static void *Swigfoo3Toc(void *ptr) {
    foo3 *src;
    c *dest;
    src = (foo3 *) ptr;
    dest = (c *) src;
    return (void *) dest;
}

        MEMBER FUNC   : double bar();

C++ CLASS END ===================================================

C++ CLASS START : class foo4  ========================================

        MEMBER FUNC   : double bar();

C++ CLASS END ===================================================

C++ CLASS START : class foo5  ========================================

        MEMBER FUNC   : double bar();

C++ CLASS END ===================================================

C++ CLASS START : class foo6  ========================================

        MEMBER FUNC   : double bar();

C++ CLASS END ===================================================

C++ CLASS START : class foo7  ========================================

        MEMBER FUNC   : double bar();

C++ CLASS END ===================================================

C++ CLASS START : class foo8  ========================================

inheriting from baseclass : a b c
static void *Swigfoo8Toa(void *ptr) {
    foo8 *src;
    a *dest;
    src = (foo8 *) ptr;
    dest = (a *) src;
    return (void *) dest;
}

static void *Swigfoo8Tob(void *ptr) {
    foo8 *src;
    b *dest;
    src = (foo8 *) ptr;
    dest = (b *) src;
    return (void *) dest;
}

static void *Swigfoo8Toc(void *ptr) {
    foo8 *src;
    c *dest;
    src = (foo8 *) ptr;
    dest = (c *) src;
    return (void *) dest;
}

C++ CLASS END ===================================================

C++ CLASS START : class A  ========================================

C++ CLASS END ===================================================

C++ CLASS START : class B  ========================================

inheriting from baseclass : A
static void *SwigBToA(void *ptr) {
    B *src;
    A *dest;
    src = (B *) ptr;
    dest = (A *) src;
    return (void *) dest;
}

C++ CLASS END ===================================================

C++ CLASS START : class C  ========================================

inheriting from baseclass : A
static void *SwigCToA(void *ptr) {
    C *src;
    A *dest;
    src = (C *) ptr;
    dest = (A *) src;
    return (void *) dest;
}

C++ CLASS END ===================================================

C++ CLASS START : class D  ========================================

inheriting from baseclass : B C
static void *SwigDToB(void *ptr) {
    D *src;
    B *dest;
    src = (D *) ptr;
    dest = (B *) src;
    return (void *) dest;
}

static void *SwigDToA(void *ptr) {
    D *src;
    A *dest;
    src = (D *) ptr;
    dest = (A *) src;
    return (void *) dest;
}

static void *SwigDToC(void *ptr) {
    D *src;
    C *dest;
    src = (D *) ptr;
    dest = (C *) src;
    return (void *) dest;
}

C++ CLASS END ===================================================

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {

     // C++ CLASS START : class a
     // C++ CLASS END 


     // C++ CLASS START : class b
     // C++ CLASS END 


     // C++ CLASS START : class c
     // C++ CLASS END 


     // C++ CLASS START : class d
     // C++ CLASS END 


     // C++ CLASS START : class foo
     ADD MEMBER FUN : bar --> double bar();
     // C++ CLASS END 


     // C++ CLASS START : class foo1
     ADD MEMBER FUN : bar --> double bar();
     // C++ CLASS END 


     // C++ CLASS START : class foo2
     ADD MEMBER FUN : bar --> double bar();
     // C++ CLASS END 


     // C++ CLASS START : class foo3
     ADD MEMBER FUN : bar --> double bar();
     // C++ CLASS END 


     // C++ CLASS START : class foo4
     ADD MEMBER FUN : bar --> double bar();
     // C++ CLASS END 


     // C++ CLASS START : class foo5
     ADD MEMBER FUN : bar --> double bar();
     // C++ CLASS END 


     // C++ CLASS START : class foo6
     ADD MEMBER FUN : bar --> double bar();
     // C++ CLASS END 


     // C++ CLASS START : class foo7
     ADD MEMBER FUN : bar --> double bar();
     // C++ CLASS END 


     // C++ CLASS START : class foo8
     // C++ CLASS END 


     // C++ CLASS START : class A
     // C++ CLASS END 


     // C++ CLASS START : class B
     // C++ CLASS END 


     // C++ CLASS START : class C
     // C++ CLASS END 


     // C++ CLASS START : class D
     // C++ CLASS END 

}  /* END INIT */
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_a","_class_foo8",Swigfoo8Toa);
	 SWIG_RegisterMapping("_a","_foo8",Swigfoo8Toa);
	 SWIG_RegisterMapping("_a","_class_foo3",Swigfoo3Toa);
	 SWIG_RegisterMapping("_a","_foo3",Swigfoo3Toa);
	 SWIG_RegisterMapping("_a","_class_foo2",Swigfoo2Toa);
	 SWIG_RegisterMapping("_a","_foo2",Swigfoo2Toa);
	 SWIG_RegisterMapping("_a","_class_foo1",Swigfoo1Toa);
	 SWIG_RegisterMapping("_a","_foo1",Swigfoo1Toa);
	 SWIG_RegisterMapping("_a","_class_foo",SwigfooToa);
	 SWIG_RegisterMapping("_a","_foo",SwigfooToa);
	 SWIG_RegisterMapping("_a","_class_a",0);
	 SWIG_RegisterMapping("_foo2","_class_foo2",0);
	 SWIG_RegisterMapping("_signed_long","_long",0);
	 SWIG_RegisterMapping("_b","_class_foo8",Swigfoo8Tob);
	 SWIG_RegisterMapping("_b","_foo8",Swigfoo8Tob);
	 SWIG_RegisterMapping("_b","_class_foo3",Swigfoo3Tob);
	 SWIG_RegisterMapping("_b","_foo3",Swigfoo3Tob);
	 SWIG_RegisterMapping("_b","_class_foo",SwigfooTob);
	 SWIG_RegisterMapping("_b","_foo",SwigfooTob);
	 SWIG_RegisterMapping("_b","_class_b",0);
	 SWIG_RegisterMapping("_foo3","_class_foo3",0);
	 SWIG_RegisterMapping("_c","_class_foo8",Swigfoo8Toc);
	 SWIG_RegisterMapping("_c","_foo8",Swigfoo8Toc);
	 SWIG_RegisterMapping("_c","_class_foo3",Swigfoo3Toc);
	 SWIG_RegisterMapping("_c","_foo3",Swigfoo3Toc);
	 SWIG_RegisterMapping("_c","_class_foo",SwigfooToc);
	 SWIG_RegisterMapping("_c","_foo",SwigfooToc);
	 SWIG_RegisterMapping("_c","_class_c",0);
	 SWIG_RegisterMapping("_foo4","_class_foo4",0);
	 SWIG_RegisterMapping("_class_A","_class_D",SwigDToA);
	 SWIG_RegisterMapping("_class_A","_D",SwigDToA);
	 SWIG_RegisterMapping("_class_A","_class_C",SwigCToA);
	 SWIG_RegisterMapping("_class_A","_C",SwigCToA);
	 SWIG_RegisterMapping("_class_A","_class_B",SwigBToA);
	 SWIG_RegisterMapping("_class_A","_B",SwigBToA);
	 SWIG_RegisterMapping("_class_A","_A",0);
	 SWIG_RegisterMapping("_d","_class_foo",SwigfooTod);
	 SWIG_RegisterMapping("_d","_foo",SwigfooTod);
	 SWIG_RegisterMapping("_d","_class_d",0);
	 SWIG_RegisterMapping("_foo5","_class_foo5",0);
	 SWIG_RegisterMapping("_class_B","_class_D",SwigDToB);
	 SWIG_RegisterMapping("_class_B","_D",SwigDToB);
	 SWIG_RegisterMapping("_class_B","_B",0);
	 SWIG_RegisterMapping("_foo6","_class_foo6",0);
	 SWIG_RegisterMapping("_class_C","_class_D",SwigDToC);
	 SWIG_RegisterMapping("_class_C","_D",SwigDToC);
	 SWIG_RegisterMapping("_class_C","_C",0);
	 SWIG_RegisterMapping("_foo7","_class_foo7",0);
	 SWIG_RegisterMapping("_class_D","_D",0);
	 SWIG_RegisterMapping("_foo8","_class_foo8",0);
	 SWIG_RegisterMapping("_long","_unsigned_long",0);
	 SWIG_RegisterMapping("_long","_signed_long",0);
	 SWIG_RegisterMapping("_class_foo1","_foo1",0);
	 SWIG_RegisterMapping("_class_a","_class_foo8",Swigfoo8Toa);
	 SWIG_RegisterMapping("_class_a","_foo8",Swigfoo8Toa);
	 SWIG_RegisterMapping("_class_a","_class_foo3",Swigfoo3Toa);
	 SWIG_RegisterMapping("_class_a","_foo3",Swigfoo3Toa);
	 SWIG_RegisterMapping("_class_a","_class_foo2",Swigfoo2Toa);
	 SWIG_RegisterMapping("_class_a","_foo2",Swigfoo2Toa);
	 SWIG_RegisterMapping("_class_a","_class_foo1",Swigfoo1Toa);
	 SWIG_RegisterMapping("_class_a","_foo1",Swigfoo1Toa);
	 SWIG_RegisterMapping("_class_a","_class_foo",SwigfooToa);
	 SWIG_RegisterMapping("_class_a","_foo",SwigfooToa);
	 SWIG_RegisterMapping("_class_a","_a",0);
	 SWIG_RegisterMapping("_class_foo2","_foo2",0);
	 SWIG_RegisterMapping("_class_b","_class_foo8",Swigfoo8Tob);
	 SWIG_RegisterMapping("_class_b","_foo8",Swigfoo8Tob);
	 SWIG_RegisterMapping("_class_b","_class_foo3",Swigfoo3Tob);
	 SWIG_RegisterMapping("_class_b","_foo3",Swigfoo3Tob);
	 SWIG_RegisterMapping("_class_b","_class_foo",SwigfooTob);
	 SWIG_RegisterMapping("_class_b","_foo",SwigfooTob);
	 SWIG_RegisterMapping("_class_b","_b",0);
	 SWIG_RegisterMapping("_class_foo3","_foo3",0);
	 SWIG_RegisterMapping("_class_c","_class_foo8",Swigfoo8Toc);
	 SWIG_RegisterMapping("_class_c","_foo8",Swigfoo8Toc);
	 SWIG_RegisterMapping("_class_c","_class_foo3",Swigfoo3Toc);
	 SWIG_RegisterMapping("_class_c","_foo3",Swigfoo3Toc);
	 SWIG_RegisterMapping("_class_c","_class_foo",SwigfooToc);
	 SWIG_RegisterMapping("_class_c","_foo",SwigfooToc);
	 SWIG_RegisterMapping("_class_c","_c",0);
	 SWIG_RegisterMapping("_class_foo4","_foo4",0);
	 SWIG_RegisterMapping("_class_d","_class_foo",SwigfooTod);
	 SWIG_RegisterMapping("_class_d","_foo",SwigfooTod);
	 SWIG_RegisterMapping("_class_d","_d",0);
	 SWIG_RegisterMapping("_class_foo5","_foo5",0);
	 SWIG_RegisterMapping("_class_foo6","_foo6",0);
	 SWIG_RegisterMapping("_class_foo7","_foo7",0);
	 SWIG_RegisterMapping("_class_foo8","_foo8",0);
	 SWIG_RegisterMapping("_unsigned_long","_long",0);
	 SWIG_RegisterMapping("_signed_int","_int",0);
	 SWIG_RegisterMapping("_unsigned_short","_short",0);
	 SWIG_RegisterMapping("_signed_short","_short",0);
	 SWIG_RegisterMapping("_unsigned_int","_int",0);
	 SWIG_RegisterMapping("_short","_unsigned_short",0);
	 SWIG_RegisterMapping("_short","_signed_short",0);
	 SWIG_RegisterMapping("_foo","_class_foo",0);
	 SWIG_RegisterMapping("_A","_class_D",SwigDToA);
	 SWIG_RegisterMapping("_A","_D",SwigDToA);
	 SWIG_RegisterMapping("_A","_class_C",SwigCToA);
	 SWIG_RegisterMapping("_A","_C",SwigCToA);
	 SWIG_RegisterMapping("_A","_class_B",SwigBToA);
	 SWIG_RegisterMapping("_A","_B",SwigBToA);
	 SWIG_RegisterMapping("_A","_class_A",0);
	 SWIG_RegisterMapping("_int","_unsigned_int",0);
	 SWIG_RegisterMapping("_int","_signed_int",0);
	 SWIG_RegisterMapping("_B","_class_D",SwigDToB);
	 SWIG_RegisterMapping("_B","_D",SwigDToB);
	 SWIG_RegisterMapping("_B","_class_B",0);
	 SWIG_RegisterMapping("_C","_class_D",SwigDToC);
	 SWIG_RegisterMapping("_C","_D",SwigDToC);
	 SWIG_RegisterMapping("_C","_class_C",0);
	 SWIG_RegisterMapping("_D","_class_D",0);
	 SWIG_RegisterMapping("_class_foo","_foo",0);
	 SWIG_RegisterMapping("_foo1","_class_foo1",0);
