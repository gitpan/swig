/* DEBUG : Language specific headers go here */

/* DEBUG : Pointer conversion function here */

/* DEBUG : Language specific code here */

#define   SWIG_init     swig_init

#define   SWIG_name    "swig"


int fact(int n) {
  if (n <= 1) return 1;
  else return n*fact(n-1);
}

int wrap_fact(ClientData clientdata, Tcl_Interp *interp,
	      int argc, char *argv[]) {
  int _result;
  int _arg0;
  if (argc != 2) {
    interp->result = "wrong # args";
    return TCL_ERROR;
  }

  _arg0 = atoi(argv[1]);
  _result = fact(_arg0);
  sprintf(interp->result,"%d",_result);
  return _result;
}
	      
extern int wrap_fact(ClientData ,Tcl_Interp *,int ,char **);
extern "C" int wrap_fact(ClientData ,Tcl_Interp *,int ,char **);
SWIG POINTER-MAPPING TABLE


/* MODULE INITIALIZATION */

void swig_init() {
     ADD NATIVE     : fact --> wrap_fact
     ADD NATIVE     : fact3 --> wrap_fact
     ADD NATIVE     : fact4 --> wrap_fact
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
