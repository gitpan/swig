// ------------------------------------------------------------------------
// Experimental MATLAB Language module
//
// Produces wrappers for MATLAB 4.x/5.0
// ------------------------------------------------------------------------

#include "swig.h"
#include "matlab.h"

static char *usage = "\
MATLAB Options\n\
     -module name    - Set name of module\n\n";

static String constants;

// ---------------------------------------------------------------------
// MATLAB::parse_args(int argc, char *argv[])
//
// Parse my command line options and initialize by variables.
// ---------------------------------------------------------------------

void MATLAB::parse_args(int argc, char *argv[]) {

  // Look for certain command line options
  for (int i = 1; i < argc; i++) {
    if (argv[i]) {
      if (strcmp(argv[i],"-module") == 0) {
	if (argv[i+1]) {
	  set_module(argv[i+1],0);
	  mark_arg(i);
	  mark_arg(i+1);
	  i++;
	} else {
	  arg_error();
	}
      } else if (strcmp(argv[i],"-help") == 0) {
	fprintf(stderr,"%s\n", usage);
      }
    }
  }

  // Set location of SWIG library
  strcpy(LibDir,"matlab");

  // Add a symbol to the parser for conditional compilation
  add_symbol("SWIGMATLAB",0,0);

  // Add typemap definitions
  typemap_lang = "matlab";
}

// ---------------------------------------------------------------------
// void MATLAB::parse()
//
// Start parsing an interface file for MATLAB.
// ---------------------------------------------------------------------

void MATLAB::parse() {

  fprintf(stderr,"Making wrappers for MATLAB (Experimental)\n");

  headers();       // Emit header files and other supporting code

  // Tell the parser to first include a typemap definition file

  if (include_file("matlab.map") == -1) {
    fprintf(stderr,"Unable to find matlab.map!\n");
    SWIG_exit(1);
  }
  yyparse();       // Run the SWIG parser
}

// ---------------------------------------------------------------------
// MATLAB::set_module(char *mod_name,char **mod_list)
//
// Sets the module name.  Does nothing if it's already set (so it can
// be overriddent as a command line option).
//
// mod_list is a NULL-terminated list of additional modules.  This
// is really only useful when building static executables.
//----------------------------------------------------------------------

void MATLAB::set_module(char *mod_name, char **mod_list) {
  if (module) return;
  module = new char[strlen(mod_name)+1];
  strcpy(module,mod_name);
}

// ---------------------------------------------------------------------
// MATLAB::headers(void)
//
// Generate the appropriate header files for MATLAB interface.
// ----------------------------------------------------------------------

void MATLAB::headers(void)
{
  emit_banner(f_header);               // Print the SWIG banner message
  fprintf(f_header,"/* Implementation : MATLAB */\n\n");

  // Include header file code fragment into the output
  if (insert_file("mlheader.swg",f_header) == -1) {
    fprintf(stderr,"Fatal Error. Unable to locate 'mlheader.swg'.\n");
    SWIG_exit(1);
  }

  // Emit the default SWIG pointer type-checker (for strings)
  if (insert_file("swigptr.swg",f_header) == -1) {
    fprintf(stderr,"Fatal Error. Unable to locate 'swigptr.swg'.\n");
    SWIG_exit(1);
  }
}

// --------------------------------------------------------------------
// MATLAB::initialize(void)
//
// Produces an initialization function.   Assumes that the init function
// name has already been specified.
// ---------------------------------------------------------------------

void MATLAB::initialize() {

  if (!module) module = "swig";

  // Start generating the initialization function
  if (insert_file("mlinit.swg",f_init) == -1) {
    fprintf(stderr,"Fatal Error. Unabled to locate 'mlinit.swg'.\n");
    SWIG_exit(1);
  }
}

// ---------------------------------------------------------------------
// MATLAB::close(void)
//
// Wrap things up.  Close initialization function.
// ---------------------------------------------------------------------

void MATLAB::close(void) {
  // Dump the pointer equivalency table
  fprintf(f_wrappers,"void initialize_module() { \n");
  fprintf(f_wrappers,"mexPrintf(\"Initializing module %s\\n\");\n", module);
  fprintf(f_wrappers,"%s", constants.get());
  emit_ptr_equivalence(f_wrappers);
  fprintf(f_wrappers,"}\n");

  // Finish off our init function and print it to the init file
  fprintf(f_init,"\t mexErrMsgTxt(\"Unknown method.\");\n");
  fprintf(f_init,"}\n");
}

// ----------------------------------------------------------------------
// MATLAB::create_command(char *cname, char *iname)
//
// Creates a MATLAB command from a C function.  Really, we just do a
// string compare in the init function and call to the real function
// ----------------------------------------------------------------------

void MATLAB::create_command(char *cname, char *iname) {
  char *wname;

  wname = name_wrapper(cname,"");
  fprintf(f_init,"\t if (strcmp(command,\"%s\") == 0) {\n", iname);
  fprintf(f_init,"\t\t%s(nlhs,plhs,nrhs-1,&prhs[1]);\n",wname);
  fprintf(f_init,"\t\treturn;\n");
  fprintf(f_init,"\t}\n");
}

// ----------------------------------------------------------------------
// MATLAB::create_function(char *name, char *iname, DataType *d, ParmList *l)
//
// Create a function declaration and register it with the interpreter.
// ----------------------------------------------------------------------

void MATLAB::create_function(char *name, char *iname, DataType *t, ParmList *l)
{
  String           source, target;
  char             *tm;
  String           cleanup, outarg;

  // A new wrapper function object

  WrapperFunction  f;

  // Make a wrapper name for this function
  
  char *wname = name_wrapper(iname,"");

  // Now write the wrapper function itself....this is pretty ugly

  f.def << "static void " << wname << "(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) { \n";

  // Emit all of the local variables for holding arguments.
  int pcount = emit_args(t,l,f);

  // Get number of optional/default arguments
  int numopt = l->numopt();

  // Emit count to check the number of arguments
  f.code << tab4 << "if ((nrhs < " << (pcount-numopt) << ") || (nrhs > " << l->numarg() << ")) {\n"
	 << tab8 << "mexErrMsgTxt(\"" << iname << ". Wrong # args.\");\n"
	 << tab8 << "return;\n"
	 << tab4 << "}\n";

  // Now walk the function parameter list and generate code to get arguments
  int j = 0;                // Total number of non-optional arguments

  for (int i = 0; i < pcount ; i++) {
    Parm &p = (*l)[i];         // Get the ith argument
    source = "";
    target = "";

    // Produce string representation of source and target arguments
    source << "prhs[" << j << "]";
    target << "_arg" << i;

    if (!p.ignore) {
      if (j >= (pcount-numopt))  // Check if parsing an optional argument
	f.code << tab4 << "if (nrhs >" << j << ") {\n";
      
      // Get typemap for this argument
      
      tm = typemap_lookup("in",typemap_lang,p.t,p.name,source,target,&f);
      if (tm) {
	f.code << tm << "\n";
	f.code.replace("$arg",source);   // Perform a variable replacement
      } else {
	fprintf(stderr,"%s : Line %d. No typemapping for datatype %s\n",
		input_file,line_number, p.t->print_type());
      }
      if (j >= (pcount-numopt))
	f.code << tab4 << "} \n";
      j++;
    }
    
    // Check to see if there was any sort of a constaint typemap
    if ((tm = typemap_lookup("check",typemap_lang,p.t,p.name,source,target))) {
      // Yep.  Use it instead of the default
      f.code << tm << "\n";
      f.code.replace("$arg",source);
    }
    
    // Check if there was any cleanup code (save it for later)
    if ((tm = typemap_lookup("freearg",typemap_lang,p.t,p.name,target,"plhs[0]"))) {
      // Yep.  Use it instead of the default
      cleanup << tm << "\n";
      cleanup.replace("$arg",source);
    }
    if ((tm = typemap_lookup("argout",typemap_lang,p.t,p.name,target,"plhs[0]"))) {
      // Yep.  Use it instead of the default
      outarg << tm << "\n";
      outarg.replace("$arg",source);
    }
  }

  // Now write code to make the function call

  emit_func_call(name,t,l,f);

  // Return value if necessary 

  if ((t->type != T_VOID) || (t->is_pointer)) {
    if ((tm = typemap_lookup("out",typemap_lang,t,name,"_result","plhs[0]"))) {
      // Yep.  Use it instead of the default
      f.code << tm << "\n";
    } else {
      fprintf(stderr,"%s : Line %d. No return typemap for datatype %s\n",
	      input_file,line_number,t->print_type());
    }
  }

  // Dump argument output code;
  f.code << outarg;

  // Dump the argument cleanup code
  f.code << cleanup;

  // Look for any remaining cleanup

  if (NewObject) {
    if ((tm = typemap_lookup("newfree",typemap_lang,t,iname,"_result",""))) {
      f.code << tm << "\n";
    }
  }

  if ((tm = typemap_lookup("ret",typemap_lang,t,name,"_result",""))) {
    f.code << tm << "\n";
  }

  // Wrap things up (in a manner of speaking)
  f.code << tab4 << "return;\n}";

  // Substitute the cleanup code (some exception handlers like to have this)
  f.code.replace("$cleanup",cleanup);
 
  // Emit the function
  
  f.print(f_wrappers);
  
  // Now register the function with the language

  create_command(name,iname);
  
  // If there's a documentation entry, produce a usage string
  
  if (doc_entry) {

    static DocEntry *last_doc_entry = 0;

    // Use usage as description
    doc_entry->usage << iname;

    // Set the cinfo field to specific a return type 

    if (last_doc_entry != doc_entry) {
      doc_entry->cinfo << "returns " << t->print_type();
      last_doc_entry = doc_entry;
    }
  }
}

// -----------------------------------------------------------------------
// MATLAB::link_variable(char *name, char *iname, DataType *t)
//
// Create a MATLAB link to a C variable.
// -----------------------------------------------------------------------

void MATLAB::link_variable(char *name, char *iname, DataType *t)
{
  emit_set_get(name,iname,t);
}

// -----------------------------------------------------------------------
// MATLAB::declare_const(char *name, char *iname, DataType *type, char *value)
//
// Makes a constant.  A quick trick is to make a variable and create a
// link to it.
// ------------------------------------------------------------------------

void MATLAB::declare_const(char *name, char *iname, DataType *type, char *value) {
  
  // Returns a constant value
  char *tm;
  tm = typemap_lookup("const",typemap_lang, type, name, name, iname);
  if (tm) {
    String str = tm;
    str.replace("$value",value);
    constants << str;
  }
}


