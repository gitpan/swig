// typemap.i

// Remap constants if in Tcl mode

#ifdef SWIGTCL

// Declare some variables for later use

%{
static Tcl_HashTable  constTable;      /* Hash table          */
static int           *swigconst;       /* Temporary variable  */
static Tcl_HashEntry *entryPtr;        /* Hash entry          */
static int            dummy;           /* dummy value         */
%}

// Initialize the hash table

%init %{
  Tcl_InitHashTable(&constTable,TCL_STRING_KEYS);
%}

// Create some typemaps

%typemap(tcl,const) int, unsigned int, long, unsigned long {
  entryPtr = Tcl_CreateHashEntry(&constTable,"$target",&dummy);
  swigconst = (int *) malloc(sizeof(int));
  *swigconst = $source;
  Tcl_SetHashValue(entryPtr, swigconst);
  /* Make it so constants can also be used as variables */
  Tcl_LinkVar(interp,"$target", (char *) swigconst, TCL_LINK_INT | TCL_LINK_READ_ONLY);
};

// Now change integer handling to look for names

%typemap(tcl,in) int, unsigned int, long, unsigned long {
  Tcl_HashEntry *entryPtr;        
  entryPtr = Tcl_FindHashEntry(&constTable,$source);
  if (entryPtr) {
    $target = ($type) (*((int *) Tcl_GetHashValue(entryPtr)));
  } else {
    $target = ($type) atoi($source);
  }
}

#endif




