/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"


typedef double Real;
typedef Real   Double;
typedef double * Array;

double * new_Array(int size) {
	return (double *) malloc(size*sizeof(double));
}

Double get_n(Array a, int n) {
	return a[n];
}

Real set_n(Real *a, int n, Real value) {
	a[n] = value;
}

void print_Array(Array a, int n) {
	int i;
	for (i = 0; i < n; i++) 
	  printf("a[%d] = %g\n", i, a[i]);
}

WRAPPER : Double *new_Array(int );

WRAPPER : double get_n(double *,int );

WRAPPER : Real set_n(Real *,int ,Real );

WRAPPER : void print_Array(Double *,int );

WRAPPER : void free(void *);

WRAPPER : void set_callback(PFI ,PFD );

C++ CLASS DECLARATION : struct Vector
C++ CLASS DECLARATION : union Union
C++ CLASS DECLARATION : class MyClass
C++ CLASS DECLARATION : struct Point
C++ CLASS DECLARATION : struct Point2
WRAPPER : int * iarray; 
WRAPPER : char * str; 
WRAPPER : char ** argv; 
WRAPPER : intptr  iarray2; 
C++ CLASS DECLARATION : struct Test
C++ CLASS START : struct Vector  ========================================

        ATTRIBUTE     : double  x; 
        ATTRIBUTE     : double  y; 
        ATTRIBUTE     : double  z; 
C++ CLASS END ===================================================

C++ CLASS START : union Union  ========================================

        ATTRIBUTE     : int  a; 
        ATTRIBUTE     : double  b; 
        ATTRIBUTE     : char * c; 
        ATTRIBUTE     : Matrix  m; 
C++ CLASS END ===================================================

C++ CLASS START : class MyClass  ========================================

        MEMBER FUNC   : int member_func();

        ATTRIBUTE     : double  member_data; 
C++ CLASS END ===================================================

C++ CLASS START : struct Point  ========================================

        ATTRIBUTE     : double  x; 
        ATTRIBUTE     : double  y; 
        ATTRIBUTE     : double  z; 
C++ CLASS END ===================================================

C++ CLASS START : struct Point2  ========================================

        ATTRIBUTE     : double  x; 
        ATTRIBUTE     : double  y; 
C++ CLASS END ===================================================

C++ CLASS START : struct Test  ========================================

        ATTRIBUTE     : int * a; 
        ATTRIBUTE     : char * str; 
        ATTRIBUTE     : int  b; 
        ATTRIBUTE     : int * c; 
        ATTRIBUTE     : int  d; 
C++ CLASS END ===================================================

SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD COMMAND    : new_Array --> Double *new_Array(int );
     ADD COMMAND    : get_n --> double get_n(double *,int );
     ADD COMMAND    : set_n --> Real set_n(Real *,int ,Real );
     ADD COMMAND    : print_Array --> void print_Array(Double *,int );
     ADD COMMAND    : free --> void free(void *);
     ADD COMMAND    : set_callback --> void set_callback(PFI ,PFD );
     ADD VARIABLE   : iarray --> int * iarray; 
     ADD VARIABLE   : str --> char * str; 
     ADD VARIABLE   : argv --> char ** argv; 
     ADD VARIABLE   : iarray2 --> intptr  iarray2; 
     ADD CONSTANT   : (int ) A = A
     ADD CONSTANT   : (int ) B = B
     ADD CONSTANT   : (int ) C = C
     ADD CONSTANT   : (int ) D = D

     // C++ CLASS START : struct Vector
     ADD MEMBER     : x --> double  x; 
     ADD MEMBER     : y --> double  y; 
     ADD MEMBER     : z --> double  z; 
     // C++ CLASS END 


     // C++ CLASS START : union Union
     ADD MEMBER     : a --> int  a; 
     ADD MEMBER     : b --> double  b; 
     ADD MEMBER     : c --> char * c; 
     ADD MEMBER     : m --> Matrix  m; 
     // C++ CLASS END 


     // C++ CLASS START : class MyClass
     ADD MEMBER FUN : member_func --> int member_func();
     ADD MEMBER     : member_data --> double  member_data; 
     // C++ CLASS END 


     // C++ CLASS START : struct Point
     ADD MEMBER     : x --> double  x; 
     ADD MEMBER     : y --> double  y; 
     ADD MEMBER     : z --> double  z; 
     // C++ CLASS END 


     // C++ CLASS START : struct Point2
     ADD MEMBER     : x --> double  x; 
     ADD MEMBER     : y --> double  y; 
     // C++ CLASS END 


     // C++ CLASS START : struct Test
     ADD MEMBER     : a --> int * a; 
     ADD MEMBER     : str --> char * str; 
     ADD MEMBER     : b --> int  b; 
     ADD MEMBER     : c --> int * c; 
     ADD MEMBER     : d --> int  d; 
     // C++ CLASS END 

}  /* END INIT */
/*
 * These are the pointer type-equivalency mappings. 
 * (Used by the SWIG pointer type-checker).
 */
	 SWIG_RegisterMapping("_GLfloat","_Myfloat",0);
	 SWIG_RegisterMapping("_struct_Test","_Test",0);
	 SWIG_RegisterMapping("_signed_long","_long",0);
	 SWIG_RegisterMapping("_IntArray","_intptr",0);
	 SWIG_RegisterMapping("_IntArray","_int_p",0);
	 SWIG_RegisterMapping("_Array","_FloatPtr",0);
	 SWIG_RegisterMapping("_Array","_double_p",0);
	 SWIG_RegisterMapping("_Point2Ptr","_Point2_p",0);
	 SWIG_RegisterMapping("_double","_Float",0);
	 SWIG_RegisterMapping("_double","_Mydouble",0);
	 SWIG_RegisterMapping("_double","_GLdouble",0);
	 SWIG_RegisterMapping("_double","_Double",0);
	 SWIG_RegisterMapping("_double","_Real",0);
	 SWIG_RegisterMapping("_struct_point_p","_PointPtr",0);
	 SWIG_RegisterMapping("_int_p","_intptr",0);
	 SWIG_RegisterMapping("_int_p","_IntArray",0);
	 SWIG_RegisterMapping("_Union","_union_Union",0);
	 SWIG_RegisterMapping("_Vector","_struct_Vector",0);
	 SWIG_RegisterMapping("_intptr","_int_p",0);
	 SWIG_RegisterMapping("_intptr","_IntArray",0);
	 SWIG_RegisterMapping("_int1","_int8",0);
	 SWIG_RegisterMapping("_int1","_int7",0);
	 SWIG_RegisterMapping("_int1","_int6",0);
	 SWIG_RegisterMapping("_int1","_int5",0);
	 SWIG_RegisterMapping("_int1","_int4",0);
	 SWIG_RegisterMapping("_int1","_int3",0);
	 SWIG_RegisterMapping("_int1","_int2",0);
	 SWIG_RegisterMapping("_int1","_int",0);
	 SWIG_RegisterMapping("_int1","_signed_int",0);
	 SWIG_RegisterMapping("_int1","_unsigned_int",0);
	 SWIG_RegisterMapping("_int2","_int8",0);
	 SWIG_RegisterMapping("_int2","_int7",0);
	 SWIG_RegisterMapping("_int2","_int6",0);
	 SWIG_RegisterMapping("_int2","_int5",0);
	 SWIG_RegisterMapping("_int2","_int4",0);
	 SWIG_RegisterMapping("_int2","_int3",0);
	 SWIG_RegisterMapping("_int2","_int",0);
	 SWIG_RegisterMapping("_int2","_signed_int",0);
	 SWIG_RegisterMapping("_int2","_unsigned_int",0);
	 SWIG_RegisterMapping("_int2","_int1",0);
	 SWIG_RegisterMapping("_int3","_int8",0);
	 SWIG_RegisterMapping("_int3","_int7",0);
	 SWIG_RegisterMapping("_int3","_int6",0);
	 SWIG_RegisterMapping("_int3","_int5",0);
	 SWIG_RegisterMapping("_int3","_int4",0);
	 SWIG_RegisterMapping("_int3","_int",0);
	 SWIG_RegisterMapping("_int3","_signed_int",0);
	 SWIG_RegisterMapping("_int3","_unsigned_int",0);
	 SWIG_RegisterMapping("_int3","_int1",0);
	 SWIG_RegisterMapping("_int3","_int2",0);
	 SWIG_RegisterMapping("_int4","_int8",0);
	 SWIG_RegisterMapping("_int4","_int7",0);
	 SWIG_RegisterMapping("_int4","_int6",0);
	 SWIG_RegisterMapping("_int4","_int5",0);
	 SWIG_RegisterMapping("_int4","_int",0);
	 SWIG_RegisterMapping("_int4","_signed_int",0);
	 SWIG_RegisterMapping("_int4","_unsigned_int",0);
	 SWIG_RegisterMapping("_int4","_int1",0);
	 SWIG_RegisterMapping("_int4","_int2",0);
	 SWIG_RegisterMapping("_int4","_int3",0);
	 SWIG_RegisterMapping("_Real","_Float",0);
	 SWIG_RegisterMapping("_Real","_Mydouble",0);
	 SWIG_RegisterMapping("_Real","_GLdouble",0);
	 SWIG_RegisterMapping("_Real","_Double",0);
	 SWIG_RegisterMapping("_Real","_double",0);
	 SWIG_RegisterMapping("_int5","_int8",0);
	 SWIG_RegisterMapping("_int5","_int7",0);
	 SWIG_RegisterMapping("_int5","_int6",0);
	 SWIG_RegisterMapping("_int5","_int4",0);
	 SWIG_RegisterMapping("_int5","_int3",0);
	 SWIG_RegisterMapping("_int5","_int2",0);
	 SWIG_RegisterMapping("_int5","_int1",0);
	 SWIG_RegisterMapping("_int5","_unsigned_int",0);
	 SWIG_RegisterMapping("_int5","_signed_int",0);
	 SWIG_RegisterMapping("_int5","_int",0);
	 SWIG_RegisterMapping("_int6","_int8",0);
	 SWIG_RegisterMapping("_int6","_int7",0);
	 SWIG_RegisterMapping("_int6","_int5",0);
	 SWIG_RegisterMapping("_int6","_int",0);
	 SWIG_RegisterMapping("_int6","_signed_int",0);
	 SWIG_RegisterMapping("_int6","_unsigned_int",0);
	 SWIG_RegisterMapping("_int6","_int1",0);
	 SWIG_RegisterMapping("_int6","_int2",0);
	 SWIG_RegisterMapping("_int6","_int3",0);
	 SWIG_RegisterMapping("_int6","_int4",0);
	 SWIG_RegisterMapping("_int7","_int8",0);
	 SWIG_RegisterMapping("_int7","_int6",0);
	 SWIG_RegisterMapping("_int7","_int4",0);
	 SWIG_RegisterMapping("_int7","_int3",0);
	 SWIG_RegisterMapping("_int7","_int2",0);
	 SWIG_RegisterMapping("_int7","_int1",0);
	 SWIG_RegisterMapping("_int7","_unsigned_int",0);
	 SWIG_RegisterMapping("_int7","_signed_int",0);
	 SWIG_RegisterMapping("_int7","_int",0);
	 SWIG_RegisterMapping("_int7","_int5",0);
	 SWIG_RegisterMapping("_char_pp","_Argv",0);
	 SWIG_RegisterMapping("_long","_unsigned_long",0);
	 SWIG_RegisterMapping("_long","_signed_long",0);
	 SWIG_RegisterMapping("_int8","_int3",0);
	 SWIG_RegisterMapping("_int8","_int2",0);
	 SWIG_RegisterMapping("_int8","_int1",0);
	 SWIG_RegisterMapping("_int8","_unsigned_int",0);
	 SWIG_RegisterMapping("_int8","_signed_int",0);
	 SWIG_RegisterMapping("_int8","_int",0);
	 SWIG_RegisterMapping("_int8","_int4",0);
	 SWIG_RegisterMapping("_int8","_int5",0);
	 SWIG_RegisterMapping("_int8","_int6",0);
	 SWIG_RegisterMapping("_int8","_int7",0);
	 SWIG_RegisterMapping("_double_p","_FloatPtr",0);
	 SWIG_RegisterMapping("_double_p","_Array",0);
	 SWIG_RegisterMapping("_Point2_p","_Point2Ptr",0);
	 SWIG_RegisterMapping("_enum_Foo","_Foo",0);
	 SWIG_RegisterMapping("_PointPtr","_struct_point_p",0);
	 SWIG_RegisterMapping("_Class","_MyClass",0);
	 SWIG_RegisterMapping("_Class","_class_Class",0);
	 SWIG_RegisterMapping("_Double","_Float",0);
	 SWIG_RegisterMapping("_Double","_Mydouble",0);
	 SWIG_RegisterMapping("_Double","_GLdouble",0);
	 SWIG_RegisterMapping("_Double","_Real",0);
	 SWIG_RegisterMapping("_Double","_double",0);
	 SWIG_RegisterMapping("_OP","_float_p",0);
	 SWIG_RegisterMapping("_Argv","_char_pp",0);
	 SWIG_RegisterMapping("_char_p","_String",0);
	 SWIG_RegisterMapping("_float_p","_OP",0);
	 SWIG_RegisterMapping("_unsigned_long","_long",0);
	 SWIG_RegisterMapping("_double_pp","_FloatPtrPtr",0);
	 SWIG_RegisterMapping("_Point","_struct_point",0);
	 SWIG_RegisterMapping("_Point","_point",0);
	 SWIG_RegisterMapping("_signed_int","_int8",0);
	 SWIG_RegisterMapping("_signed_int","_int7",0);
	 SWIG_RegisterMapping("_signed_int","_int6",0);
	 SWIG_RegisterMapping("_signed_int","_int5",0);
	 SWIG_RegisterMapping("_signed_int","_int4",0);
	 SWIG_RegisterMapping("_signed_int","_int3",0);
	 SWIG_RegisterMapping("_signed_int","_int2",0);
	 SWIG_RegisterMapping("_signed_int","_int1",0);
	 SWIG_RegisterMapping("_signed_int","_int",0);
	 SWIG_RegisterMapping("_unsigned_short","_short",0);
	 SWIG_RegisterMapping("_union_Union","_Union",0);
	 SWIG_RegisterMapping("_signed_short","_short",0);
	 SWIG_RegisterMapping("_unsigned_int","_int8",0);
	 SWIG_RegisterMapping("_unsigned_int","_int7",0);
	 SWIG_RegisterMapping("_unsigned_int","_int6",0);
	 SWIG_RegisterMapping("_unsigned_int","_int5",0);
	 SWIG_RegisterMapping("_unsigned_int","_int4",0);
	 SWIG_RegisterMapping("_unsigned_int","_int3",0);
	 SWIG_RegisterMapping("_unsigned_int","_int2",0);
	 SWIG_RegisterMapping("_unsigned_int","_int1",0);
	 SWIG_RegisterMapping("_unsigned_int","_int",0);
	 SWIG_RegisterMapping("_GLdouble","_Float",0);
	 SWIG_RegisterMapping("_GLdouble","_Mydouble",0);
	 SWIG_RegisterMapping("_GLdouble","_Real",0);
	 SWIG_RegisterMapping("_GLdouble","_double",0);
	 SWIG_RegisterMapping("_GLdouble","_Double",0);
	 SWIG_RegisterMapping("_short","_unsigned_short",0);
	 SWIG_RegisterMapping("_short","_signed_short",0);
	 SWIG_RegisterMapping("_String","_char_p",0);
	 SWIG_RegisterMapping("_int","_int8",0);
	 SWIG_RegisterMapping("_int","_int7",0);
	 SWIG_RegisterMapping("_int","_int6",0);
	 SWIG_RegisterMapping("_int","_int5",0);
	 SWIG_RegisterMapping("_int","_int4",0);
	 SWIG_RegisterMapping("_int","_int3",0);
	 SWIG_RegisterMapping("_int","_int2",0);
	 SWIG_RegisterMapping("_int","_int1",0);
	 SWIG_RegisterMapping("_int","_unsigned_int",0);
	 SWIG_RegisterMapping("_int","_signed_int",0);
	 SWIG_RegisterMapping("_struct_point","_Point",0);
	 SWIG_RegisterMapping("_struct_point","_point",0);
	 SWIG_RegisterMapping("_struct_Vector","_Vector",0);
	 SWIG_RegisterMapping("_point","_Point",0);
	 SWIG_RegisterMapping("_point","_struct_point",0);
	 SWIG_RegisterMapping("_Test","_struct_Test",0);
	 SWIG_RegisterMapping("_Myfloat","_GLfloat",0);
	 SWIG_RegisterMapping("_class_Class","_MyClass",0);
	 SWIG_RegisterMapping("_class_Class","_Class",0);
	 SWIG_RegisterMapping("_Mydouble","_Float",0);
	 SWIG_RegisterMapping("_Mydouble","_GLdouble",0);
	 SWIG_RegisterMapping("_Mydouble","_Double",0);
	 SWIG_RegisterMapping("_Mydouble","_double",0);
	 SWIG_RegisterMapping("_Mydouble","_Real",0);
	 SWIG_RegisterMapping("_Float","_double",0);
	 SWIG_RegisterMapping("_Float","_Real",0);
	 SWIG_RegisterMapping("_Float","_Double",0);
	 SWIG_RegisterMapping("_Float","_GLdouble",0);
	 SWIG_RegisterMapping("_Float","_Mydouble",0);
	 SWIG_RegisterMapping("_MyClass","_class_Class",0);
	 SWIG_RegisterMapping("_MyClass","_Class",0);
	 SWIG_RegisterMapping("_FloatPtr","_double_p",0);
	 SWIG_RegisterMapping("_FloatPtr","_Array",0);
	 SWIG_RegisterMapping("_FloatPtrPtr","_double_pp",0);
	 SWIG_RegisterMapping("_Foo","_enum_Foo",0);
