
/*******************************************************************************
 * Simplified Wrapper and Interface Generator  (SWIG)
 * 
 * Dave Beazley
 * 
 * Department of Computer Science        Theoretical Division (T-11)
 * University of Utah                    Los Alamos National Laboratory
 * Salt Lake City, Utah  84112           Los Alamos, New Mexico  87545
 * beazley@cs.utah.edu                   beazley@lanl.gov
 *
 * Copyright (c) 1995-1997
 * The University of Utah and the Regents of the University of California
 * All Rights Reserved
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that 
 * (1) The above copyright notice and the following two paragraphs
 * appear in all copies of the source code and (2) redistributions
 * including binaries reproduces these notices in the supporting
 * documentation.   Substantial modifications to this software may be
 * copyrighted by their authors and need not follow the licensing terms
 * described here, provided that the new terms are clearly indicated in
 * all files where they apply.
 * 
 * IN NO EVENT SHALL THE AUTHOR, THE UNIVERSITY OF CALIFORNIA, THE 
 * UNIVERSITY OF UTAH OR DISTRIBUTORS OF THIS SOFTWARE BE LIABLE TO ANY
 * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHORS OR ANY OF THE ABOVE PARTIES HAVE BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR, THE UNIVERSITY OF CALIFORNIA, AND THE UNIVERSITY OF UTAH
 * SPECIFICALLY DISCLAIM ANY WARRANTIES,INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND 
 * THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 *******************************************************************************/
/**********************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.2/Modules/RCS/python.cxx,v 1.60 1997/07/27 20:29:59 beazley Exp $
 *
 * python.cxx
 *
 * Python module.
 **************************************************************************/


#include "swig.h"
#include "python.h"

// Structures for managing doc strings

struct DocString {
  DocEntry    *de;
  char        *name;
  DocString    *next;
};

static   int          doc_index = 0;
static   DocString   *doc_strings = 0;

static char *usage = "\
Python Options (available with -python)\n\
     -docstring      - Produce docstrings (only applies to shadow classes)\n\
     -globals name   - Set name used to access C global variable ('cvar' by default).\n\
     -module name    - Set module name\n\
     -shadow         - Generate shadow classes. \n\n";

static String pragma_include;

// ---------------------------------------------------------------------
// PYTHON::parse_args(int argc, char *argv[])
//
// ---------------------------------------------------------------------

void PYTHON::parse_args(int argc, char *argv[]) {

  int i = 1;

  sprintf(LibDir,"%s",path);

  docstring = 0;

  // Look for additional command line options.
  for (i = 1; i < argc; i++) {	
      if (argv[i]) {
	  if(strcmp(argv[i],"-module") == 0) {
	    if (argv[i+1]) {
	      module = new char[strlen(argv[i+1])+2];
	      strcpy(module, argv[i+1]);
	      mark_arg(i);
	      mark_arg(i+1);
	      i+=1;
	    } else {
	      arg_error();
	    } 
	  } else if (strcmp(argv[i],"-globals") == 0) {
	    if (argv[i+1]) {
	      global_name = new char[strlen(argv[i+1])+1];
	      strcpy(global_name, argv[i+1]);
	      mark_arg(i);
	      mark_arg(i+1);
	      i++;
	    } else {
	      arg_error();
	    }
	  } else if (strcmp(argv[i],"-shadow") == 0) {
	    shadow = 1;
	    mark_arg(i);
          } else if (strcmp(argv[i],"-docstring") == 0) {
	    docstring = 1;
	    mark_arg(i);
	  } else if (strcmp(argv[i],"-help") == 0) {
	    fputs(usage,stderr);
	  }
      }
  }
  // Create a symbol for this language
  add_symbol("SWIGPYTHON",0,0);

  // Set name of typemaps

  typemap_lang = "python";

}

// ---------------------------------------------------------------------
// PYTHON::parse()
//
// Parse the interface file
// ---------------------------------------------------------------------

void
PYTHON::parse() {
  
  printf("Generating wrappers for Python\n"); 
  headers();
  
  // Run the SWIG parser
  
  yyparse();
}

// ---------------------------------------------------------------------
// PYTHON::set_module(char *mod_name, char **mod_list)
//
// Sets the module name.
// Does nothing if it's already set (so it can be overridden as a command
// line option).
//
//----------------------------------------------------------------------

void PYTHON::set_module(char *mod_name, char **mod_list) {
  int i;

  // If an "import" method has been set and we're in shadow class mode,
  // output a python command to load the module

  if (import_file) {
    if (!(strcmp(import_file,input_file+strlen(input_file)-strlen(import_file)))) {
      if (shadow) {
	fprintf(f_shadow,"\nfrom %s import *\n", mod_name);
      }
      delete import_file;
      import_file = 0;
    }
  }

  if (module) return;

  module = new char[strlen(mod_name)+1];
  strcpy(module,mod_name);

  // If there was a mod_list specified, make this incredible hack
  if  (mod_list) {
    modinit << "#define SWIGMODINIT ";
    modextern << "#ifdef __cplusplus\n"
	      << "extern \"C\" {\n"
	      << "#endif\n";
    i = 0;
    while(mod_list[i]) {
      modinit << "swig_add_module(\"" << mod_list[i] << "\",init"
	      << mod_list[i] << "); \\\n";
      
      modextern << "extern void init" << mod_list[i] << "();\n";
      i++;
    }
    modextern << "#ifdef __cplusplus\n"
	      << "}\n"
	      << "#endif\n";
    modinit << "/* End of extern module initialization */\n";

  }
}

// ---------------------------------------------------------------------
// PYTHON::set_init(char *iname)
//
// Sets the initialization function name.
// Does nothing if it's already set
//
//----------------------------------------------------------------------

void PYTHON::set_init(char *iname) {
  set_module(iname,0);
}


// ---------------------------------------------------------------------
// PYTHON::import(char *filename)
//
// Imports a SWIG module as a separate file.
//----------------------------------------------------------------------

void PYTHON::import(char *filename) {
  if (import_file) delete import_file;
  import_file = copy_string(filename);
}

// ----------------------------------------------------------------------
// PYTHON::add_method(char *name, char *function)
//
// Add some symbols to the methods table
// ----------------------------------------------------------------------

void PYTHON::add_method(char *name, char *function) {

  Method *n;

  n = new Method;
  n->name = new char[strlen(name)+1];
  strcpy(n->name,name);
  n->function = new char[strlen(function)+1];
  strcpy(n->function, function);

  n->next = head;
  head = n;
}

// ---------------------------------------------------------------------
// PYTHON::print_methods()
//
// Prints out the method array.
// ---------------------------------------------------------------------

void PYTHON::print_methods() {

  Method *n;

  fprintf(f_wrappers,"static PyMethodDef %sMethods[] = {\n", module);
  n = head;
  while (n) {
    fprintf(f_wrappers,"\t { \"%s\", %s, 1 },\n", n->name, n->function);
    n = n->next;
  }
  fprintf(f_wrappers,"\t { NULL, NULL }\n");
  fprintf(f_wrappers,"};\n");
}

// ---------------------------------------------------------------------
// char *PYTHON::add_docstring(DocEntry *de)
//
// Adds a documentation entry to the doc-string generator.   Returns a
// unique character symbol that will be used to fill in the doc-string
// at a later time.
// ---------------------------------------------------------------------

char *PYTHON::add_docstring(DocEntry *de) {
  DocString *s;
  String str;

  str = "@doc";
  str << doc_index << "@";
  
  s = new DocString();
  s->de = de;
  s->name = copy_string(str);
  s->next = doc_strings;
  doc_strings = s;
  doc_index++;
  return s->name;
}

// ---------------------------------------------------------------------
// PYTHON::headers(void)
//
// ----------------------------------------------------------------------

void PYTHON::headers(void)
{

  emit_banner(f_header);

  fprintf(f_header,"/* Implementation : PYTHON */\n\n");
  fprintf(f_header,"#define SWIGPYTHON\n");
  fprintf(f_header,"#include <string.h>\n");
  fprintf(f_header,"#include <stdlib.h>\n");
  

  if (!NoInclude) {
    if (insert_file("python.swg", f_header) == -1) {
      fprintf(stderr,"SWIG : Fatal error. Unable to locate python.swg. (Possible installation problem).\n");
      SWIG_exit(1);
    }
    emit_hex(f_header);
  } else {
    if (insert_file("pyexp.swg", f_header) == -1) {
      fprintf(stderr,"SWIG : Fatal error. Unable to locate pyexp.swg. (Possible installation problem).\n");
      SWIG_exit(1);
    }
  }
}


// --------------------------------------------------------------------
// PYTHON::initialize(void)
//
// This function outputs the starting code for a function to initialize
// your interface.   It is only called once by the parser.
//
// ---------------------------------------------------------------------

void PYTHON::initialize(void)
{

  char  filen[256];
  char  *temp;
  char  *oldmodule = 0;

  if (!module) {
    module = "swig";
    fprintf(stderr,"SWIG : *** Warning. No module name specified.\n");
  }

  // If shadow classing is enabled, we're going to change the module
  // name to "modulec"

  if (shadow) {
    temp = new char[strlen(module)+2];
    sprintf(temp,"%sc",module);
    oldmodule = module;
    module = temp;
  } 
  /* Initialize the C code for the module */
  initialize_cmodule();
  /* Create a shadow file (if enabled).*/
  if (shadow) {
    sprintf(filen,"%s%s.py", output_dir, oldmodule);
    if ((f_shadow = fopen(filen,"w")) == 0) {
      fprintf(stderr,"Unable to open %s\n", filen);
      SWIG_exit(0);
    }
    fprintf(f_shadow,"# This file was created automatically by SWIG.\n");
    fprintf(f_shadow,"import %s\n", module);
  }

  // Dump out external module declarations

  if (strlen(modinit.get()) > 0) {
    fprintf(f_header,"%s\n",modinit.get());
  }
  if (strlen(modextern.get()) > 0) {
    fprintf(f_header,"%s\n",modextern.get());
  }
}

// ---------------------------------------------------------------------
// PYTHON::initialize_cmodule(void)
//
// Initializes the C module.
// 
// ---------------------------------------------------------------------
void PYTHON::initialize_cmodule(void)
{
  int i;
  fprintf(f_header,"#define SWIG_init    init%s\n\n", module);
  fprintf(f_header,"#define SWIG_name    \"%s\"\n", module);	

  // Output the start of the init function.  
  // Modify this to use the proper return type and arguments used
  // by the target Language

  fprintf(f_init,"static PyObject *SWIG_globals;\n");

  fprintf(f_init,"#ifdef __cplusplus\n");
  fprintf(f_init,"extern \"C\" \n");
  fprintf(f_init,"#endif\n");

  fprintf(f_init,"SWIGEXPORT(void,init%s)() {\n",module);
  fprintf(f_init,"\t PyObject *m, *d;\n");

  if (InitNames) {
    i = 0;
    while (InitNames[i]) {
      fprintf(f_init,"\t %s();\n", InitNames[i]);
      i++;
    }
  }
  fprintf(f_init,"\t SWIG_globals = SWIG_newvarlink();\n");
  fprintf(f_init,"\t m = Py_InitModule(\"%s\", %sMethods);\n", module, module);
  fprintf(f_init,"\t d = PyModule_GetDict(m);\n");
}


// ---------------------------------------------------------------------
// PYTHON::close(void)
//
// Called when the end of the interface file is reached.  Closes the
// initialization function and performs cleanup as necessary.
// ---------------------------------------------------------------------

void PYTHON::close(void)
{

  print_methods();
  close_cmodule();
  if ((doc_entry) && (module)){
    String temp;
    temp << "Python Module : ";
    if (shadow) {
      module[strlen(module)-1] = 0;
    }
    temp << module; 
    doc_entry->cinfo << temp;
  }
  if (shadow) {
    String  fullshadow;
    fullshadow << classes
               << "\n\n#-------------- FUNCTION WRAPPERS ------------------\n\n"
               << func
               << "\n\n#-------------- VARIABLE WRAPPERS ------------------\n\n"
               << vars;

    if (strlen(pragma_include) > 0) {
      fullshadow << "\n\n#-------------- USER INCLUDE -----------------------\n\n"
                 << pragma_include;
    }

    // Go through all of the docstrings and replace the docstrings

    DocString *s;
    s = doc_strings;
    while (s) {
      fullshadow.replace(s->name, s->de->text);
      s = s->next;
    }
    /*
    fprintf(f_shadow,"\n\n#-------------- FUNCTION WRAPPERS ------------------\n\n");
    fprintf(f_shadow,"%s",func.get());
    fprintf(f_shadow,"\n\n#-------------- VARIABLE WRAPPERS ------------------\n\n");
    fprintf(f_shadow,"%s",vars.get());
    if (strlen(pragma_include) > 0) {
      fprintf(f_shadow,"\n\n#-------------- USER INCLUDE -----------------------\n\n");
      fprintf(f_shadow,"%s",pragma_include.get());
    }
    */
    fprintf(f_shadow, "%s", fullshadow.get());
    fclose(f_shadow);
  }
}

// --------------------------------------------------------------------
// PYTHON::close_cmodule(void)
//
// Called to cleanup the C module code
// --------------------------------------------------------------------
void PYTHON::close_cmodule(void)
{
  emit_ptr_equivalence(f_init);
  fprintf(f_init,"}\n");
}

// ----------------------------------------------------------------------
// PYTHON::get_pointer(char *iname, char *srcname, char *src, char *target,
//                     DataType *t, WrapperFunction &f, char *ret)
//
// Emits code to get a pointer and do type checking.
//      iname = name of the function/method  (used for error messages)
//      srcname = Name of source (used for error message reporting).
//      src   = name of variable where source string is located.
//      dest  = name of variable where pointer value is stored.
//      t     = Expected datatype of the parameter
//      f     = Wrapper function object being used to generate code.
//      ret   = return code upon failure.
//
// Note : pointers are stored as strings so you first need to get
// a string and then call _swig_get_hex() to extract a point.
//
// This module is pretty ugly, but type checking is kind of nasty
// anyways.
// ----------------------------------------------------------------------

void
PYTHON::get_pointer(char *iname, char *srcname, char *src, char *dest,
		    DataType *t, String &f, char *ret)
{

  // Now get the pointer value from the string and save in dest
  
  f << tab4 << "if (" << src << ") {\n";
  f << tab8 << "if (SWIG_GetPtr(" << src << ",(void **) &" << dest << ",";

  // If we're passing a void pointer, we give the pointer conversion a NULL
  // pointer, otherwise pass in the expected type.
  
  if (t->type == T_VOID) f << "(char *) 0 )) {\n";
  else
    f << "\"" << t->print_mangle() << "\")) {\n";

  // This part handles the type checking according to three different
  // levels.   0 = no checking, 1 = warning message, 2 = strict.

  switch(TypeStrict) {
  case 0: // No type checking
    f << tab8 << "}\n";
    break;

  case 1: // Warning message only

    // Change this part to how you want to handle a type-mismatch warning.
    // By default, it will just print to stderr.

    f << tab8 << tab4 << "fprintf(stderr,\"Warning : type mismatch in " << srcname
	   << " of " << iname << ". Expected " << t->print_mangle()
	   << ", received %s\\n\"," << src << ");\n"
	   << tab8 << "}\n";

    break;
  case 2: // Super strict mode.

    // Change this part to return an error.

    f << tab8 << tab4 << "PyErr_SetString(PyExc_TypeError,\"Type error in " << srcname
	   << " of " << iname << ". Expected " << t->print_mangle() << ".\");\n"
	   << tab8 << "return " << ret << ";\n"
	   << tab8 << "}\n";
    break;
    
  default :
    fprintf(stderr,"SWIG Error. Unknown strictness level\n");
    break;
  }
  f << tab4 << "}\n";
}

// ----------------------------------------------------------------------
// PYTHON::shadow_defargs(Parm *p, ParmList *l, int i, int pcount, int numopt,
//                        String &code, char *indent)
//
// Internal function for extracting from default arguments on shadow classes.
// Note : the index refers to the arguments in a Python function.  C arguments
// that are ignored will not affect the index.
//
// p = Current parameter
// l = Parameter list
// i = Current parameter index
// pcount = Number of parameters
// numopt = Number of default arguments
// code   = String object containing output.
// indent = Base indentation
//
// -----------------------------------------------------------------------

void PYTHON::shadow_defargs(Parm *p, ParmList *l, int i, int pcount, int numopt,
			    String &code, char *indent)
{

  int need_translate = 0;

  code << indent << "argl = map(None,args)\n";

  // Now check for arguments that need translation

  while (p) {
    // If parameter is ignored, forget it
    if (!p->ignore) {
      if ((hash.lookup(p->t->name)) && (p->t->is_pointer <= 1)) {
	need_translate = 1;
	code << indent << "try: " << "argl[" << (i - (pcount-numopt)) << "] = argl["
	     << (i-(pcount-numopt)) << "].this\n"
	     << indent << "except: pass\n";
      }
      i++;
    }
    p = l->get_next();
  }
  code << indent << "args = tuple(argl)\n";
  if (!need_translate) code = "";
}

// ----------------------------------------------------------------------
// PYTHON::emit_function_header()
//
// Return the code to be used as a function header
// ----------------------------------------------------------------------
void PYTHON::emit_function_header(WrapperFunction &emit_to, char *wname)
{
  emit_to.def << "static PyObject *" << wname
	      << "(PyObject *self, PyObject *args) {";
  emit_to.code << tab4 << "self = self;\n";
}

// ----------------------------------------------------------------------
// PYTHON::convert_self()
//
// Called during the function generation process, to determine what to
// use as the "self" variable during the call.  Derived classes may emit code
// to convert the real self pointer into a usable pointer.
//
// Returns the name of the variable to use as the self pointer
// ----------------------------------------------------------------------
char *PYTHON::convert_self(WrapperFunction &)
{
  // Default behaviour is no translation
  return "";
}

// ----------------------------------------------------------------------
// PYTHON::make_funcname_wrapper()
//
// Called to create a name for a wrapper function
// ----------------------------------------------------------------------
char *PYTHON::make_funcname_wrapper(char *fnName)
{
  return name_wrapper(fnName,"");
}

// ----------------------------------------------------------------------
// PYTHON::create_command(char *cname, char *iname)
//
// Create a new command in the interpreter.  Used for C++ inheritance 
// stuff.
// ----------------------------------------------------------------------

void PYTHON::create_command(char *cname, char *iname) {

  // Create the name of the wrapper function

  char *wname = name_wrapper(cname,"");

  // Now register the function with the interpreter.  

  add_method(iname, wname);

}

// ----------------------------------------------------------------------
// PYTHON::create_function(char *name, char *iname, DataType *d,
//                             ParmList *l)
//
// This function creates a wrapper function and registers it with the
// interpreter.   
//  
// Inputs :
//     name  = actual name of the function that's being wrapped
//    iname  = name of the function in the interpreter (may be different)
//        d  = Return datatype of the functions.
//        l  = A linked list containing function parameter information.
//
// ----------------------------------------------------------------------

void PYTHON::create_function(char *name, char *iname, DataType *d, ParmList *l)
{
  Parm    *p;
  int     pcount,i,j;
  String  wname, self_name, call_name;
  char    source[64], target[64], temp[256], argnum[20];
  char    *usage = 0;
  WrapperFunction f;
  String   parse_args;
  String   arglist;
  String   get_pointers;
  String   cleanup, outarg;
  String   check;
  String   build;
  int      have_build = 0;
  char     *tm;
  int      numopt = 0;

  have_output = 0;

  // Make a valid name for this function.   This removes special symbols
  // that would cause problems in the C compiler.

  wname = make_funcname_wrapper(iname);

  // Now emit the function declaration for the wrapper function.  You
  // should modify this to return the appropriate types and use the
  // appropriate parameters.

  emit_function_header(f, wname);

  f.add_local("PyObject *","_resultobj");

  // Get the function usage string for later use
  
  usage = usage_func(iname,d,l);   

  // Write code to extract function parameters.
  // This is done in one pass, but we need to construct three independent
  // pieces.
  //      1.    Python format string such as "iis"
  //      2.    The actual arguments to put values into
  //      3.    Pointer conversion code.
  //
  // If there is a type mapping, we will extract the Python argument
  // as a raw PyObject and let the user deal with it.
  //

  pcount = emit_args(d, l, f);
  parse_args << tab4 << "if(!PyArg_ParseTuple(args,\"";
  i = 0;
  j = 0;
  numopt = l->numopt();        // Get number of optional arguments
  if (numopt) have_defarg = 1;
  p = l->get_first();
  while (p != 0) {
    
    // Generate source and target strings
    sprintf(source,"_obj%d",i);
    sprintf(target,"_arg%d",i);
    sprintf(argnum,"%d",j+1);

    // Only consider this argument if it's not ignored

    if (!p->ignore) {
      arglist << ",";
      // Add an optional argument separator if needed
    
      if (j == pcount-numopt) {  
	parse_args << "|";
      }

      // Look for input typemap

      if ((tm = typemap_lookup("in","python",p->t,p->name,source,target,&f))) {
	parse_args << "O";        // Grab the argument as a raw PyObject
	f.add_local("PyObject *",source,"0");
	arglist << "&" << source;
	if (i >= (pcount-numopt))
	  get_pointers << tab4 << "if (" << source << ")\n";
	get_pointers << tm << "\n";
	get_pointers.replace("$argnum", argnum);
	get_pointers.replace("$arg",source);
      } else {

	// Check if this parameter is a pointer.  If not, we'll get values

	if (!p->t->is_pointer) {
	  // Extract a parameter by "value"
	
	  switch(p->t->type) {
	  
	    // Handle integers here.  Usually this can be done as a single
	    // case if you appropriate cast things.   However, if you have
	    // special cases, you'll need to add more code.  
	    
	  case T_INT : case T_UINT: case T_SINT: 
	    parse_args << "i";
	    break;
	  case T_SHORT: case T_USHORT: case T_SSHORT:
	    parse_args << "h";
	    break;
	  case T_LONG : case T_ULONG: case T_SLONG :
	    parse_args << "l";
	    break;
	  case T_SCHAR : case T_UCHAR :
	    parse_args << "b";
	    break;
	  case T_CHAR:
	    parse_args << "c";
	    break;
	  case T_FLOAT :
	    parse_args << "f";
	    break;
	  case T_DOUBLE:
	    parse_args << "d";
	    break;
	    
	  case T_BOOL:
	    {
	      String tempb;
	      tempb << "tempbool" << i;
	      parse_args << "i";
	      f.add_local("int",tempb.get());
	      get_pointers << tab4 << target << " = " << p->t->print_cast() << " " << tempb << ";\n";
	      arglist << "&" << tempb;
	    }
	  break;

	    // Void.. Do nothing.
	    
	  case T_VOID :
	    break;
	    
	    // User defined.   This is usually invalid.   No way to pass a
	    // complex type by "value".  We'll just pass into the unsupported
	    // datatype case.
	    
	  case T_USER:
	    
	    // Unsupported data type
	    
	  default :
	    fprintf(stderr,"%s : Line %d. Unable to use type %s as a function argument.\n",input_file, line_number, p->t->print_type());
	    break;
	  }
	  
	  // Emit code for parameter list
	  
	  if ((p->t->type != T_VOID) && (p->t->type != T_BOOL))
	    arglist << "&_arg" << i;
	  
	} else {
	  
	  // Is some other kind of variable.   
	  
	  parse_args << "s";
	  
	  if ((p->t->type == T_CHAR) && (p->t->is_pointer == 1)) {
	    arglist << "&_arg" << i;
	  } else {
	    
	    // Have some sort of pointer variable.  Create a temporary local
	    // variable for the string and read the pointer value into it.
	    
	    sprintf(source,"_argc%d", i);
	    sprintf(target,"_arg%d", i);
	    sprintf(temp,"argument %d",i+1);
	    
	    f.add_local("char *", source,"0");
	    arglist << "&" << source;
	    get_pointer(iname, temp, source, target, p->t, get_pointers, "NULL");
	  }
	}
      }
      j++;
    }
    // Check if there was any constraint code
    if ((tm = typemap_lookup("check","python",p->t,p->name,source,target))) {
      check << tm << "\n";
      check.replace("$argnum", argnum);
    }
    // Check if there was any cleanup code
    if ((tm = typemap_lookup("freearg","python",p->t,p->name,target,source))) {
      cleanup << tm << "\n";
      cleanup.replace("$argnum", argnum);
      cleanup.replace("$arg",source);
    }
    if ((tm = typemap_lookup("argout","python",p->t,p->name,target,"_resultobj"))) {
      outarg << tm << "\n";
      outarg.replace("$argnum", argnum);
      outarg.replace("$arg",source);
      have_output++;
    } 
    if ((tm = typemap_lookup("build","python",p->t,p->name,source,target))) {
      build << tm << "\n";
      have_build = 1;
    }
    p = l->get_next();
    i++;
  }

  parse_args << ":" << iname << "\"";     // No additional arguments
  parse_args << arglist << ")) \n"
	     << tab8 << "return NULL;\n";
  
  self_name = convert_self(f);

  /* Now slap the whole first part of the wrapper function together */

  f.code << parse_args << get_pointers << check;


  // Special handling for build values

  if (have_build) {
    char temp1[256];
    char temp2[256];
    l->sub_parmnames(build);            // Replace all parameter names
    for (i = 0; i < l->nparms; i++) {
      p = l->get(i);
      if (strlen(p->name) > 0) {
	sprintf(temp1,"_in_%s", p->name);
      } else {
	sprintf(temp1,"_in_arg%d", i);
      }
      sprintf(temp2,"_obj%d",i);
      build.replaceid(temp1,temp2);
    }
    f.code << build;
  }

  // This function emits code to call the real function.  Assuming you read
  // the parameters in correctly, this will work.

  call_name = "";
  call_name << self_name << name;
  emit_func_call(call_name,d,l,f);

  // Now emit code to return the functions return value (if any).
  // If there was a result, it was saved in _result.
  // If the function is a void type, don't do anything.
  
  if ((tm = typemap_lookup("out","python",d,iname,"_result","_resultobj"))) {
    // Yep.  Use it instead of the default
    f.code << tm << "\n";
  } else {

    if ((d->type != T_VOID) || (d->is_pointer)) {
      // Now have return value, figure out what to do with it.
      
      if (!d->is_pointer) {
	
	// Function returns a "value"
	
	switch(d->type) {
	  
	  // Return an integer type
	  
	case T_INT: case T_SINT: case T_UINT: case T_BOOL:
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"i\",_result);\n";
	  break;
	case T_SHORT: case T_SSHORT: case T_USHORT:
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"h\",_result);\n";
	  break;
	case T_LONG : case T_SLONG : case T_ULONG:
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"l\",_result);\n";
	  break;
	case T_SCHAR: case T_UCHAR :
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"b\",_result);\n";
	  break;
	  
	  // Return a floating point value
	  
	case T_DOUBLE :
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"d\",_result);\n";
	  break;
	case T_FLOAT :
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"f\",_result);\n";
	  break;
	  
	  // Return a single ASCII value.  Usually we need to convert
	  // it to a NULL-terminate string and return that instead.
	  
	case T_CHAR :
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"c\",_result);\n";
	  break;
	  
	case T_USER :
	  
	  // Return something by value
	  // We're living dangerously here, but life is short...play hard
	  
	  // Oops.  Need another local variable
	  f.add_local("char","_ptemp[128]");
	  
	  d->is_pointer++;
	  f.code << tab4 << "SWIG_MakePtr(_ptemp, (void *) _result,\""
		 << d->print_mangle() << "\");\n";
	  d->is_pointer--;
	  // Return a character string containing our pointer.
	  
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"s\",_ptemp);\n";
	  break;
	default :
	  fprintf(stderr,"%s: Line %d. Unable to use return type %s in function %s.\n", input_file, line_number, d->print_type(), name);
	  break;
	}
      } else {
	
	// Return type is a pointer.   We'll see if it's a char * and return
	// a string. Otherwise, we'll convert it into a SWIG pointer and return
	// that.
	
	if ((d->type == T_CHAR) && (d->is_pointer == 1)) {
	  
	  // Return a character string
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"s\", _result);\n";

	  // If declared as a new object, free the result

	} else {
	  
	  // Build a SWIG pointer.
	  f.add_local("char","_ptemp[128]");
	  
	  f.code << tab4 << "SWIG_MakePtr(_ptemp, (char *) _result,\""
		 << d->print_mangle() << "\");\n";
	  
	  // Return a character string containing our pointer.
	  f.code << tab4 << "_resultobj = Py_BuildValue(\"s\",_ptemp);\n";
	}
      }
    } else {
      // no return value and no output args
      //if (!have_output) {
	f.code << tab4 << "Py_INCREF(Py_None);\n";
	f.code << tab4 << "_resultobj = Py_None;\n";
      //} 
    }
  }

  // Check to see if there were any output arguments, if so we're going to
  // create a Python list object out of the current result

  f.code << outarg;

  // If there was any other cleanup needed, do that

  f.code << cleanup;

  // Look to see if there is any newfree cleanup code

  if (NewObject) {
    if ((tm = typemap_lookup("newfree","python",d,iname,"_result",""))) {
      f.code << tm << "\n";
    }
  }

  // See if there is any argument cleanup code

  if ((tm = typemap_lookup("ret","python",d,iname,"_result",""))) {
    // Yep.  Use it instead of the default
    f.code << tm << "\n";
  }
  
  f.code << tab4 << "return _resultobj;\n";
  f.code << "}\n";

  // Substitute the cleanup code
  f.code.replace("$cleanup",cleanup);

  // Substitute the function name
  f.code.replace("$name",iname);

  // Dump the function out
  f.print(f_wrappers);

  // Now register the function with the interpreter.  

  add_method(iname, wname);

  // Create a documentation entry for this

  if (doc_entry) {
    static DocEntry *last_doc_entry = 0;
    doc_entry->usage << usage;
    if (last_doc_entry != doc_entry) {
      doc_entry->cinfo << "returns " << d->print_type();
      last_doc_entry = doc_entry;
    }
  }

  // ---------------------------------------------------------------------------
  // Create a shadow for this function (if enabled and not in a member function)
  // ---------------------------------------------------------------------------

  if ((shadow) && (!(shadow & PYSHADOW_MEMBER))) {
    String translate;

    int need_wrapper = 0;
    int have_optional = 0;

    // First, we're going to check to see if this function needs modification
    p = l->get_first();
    while (p) {
      if ((!p->ignore) && (hash.lookup(p->t->name)) && (p->t->is_pointer <= 1))
	need_wrapper = 1;
      p = l->get_next();
    }
    
    // Check return code for modification

    if ((hash.lookup(d->name)) && (d->is_pointer <=1))
      need_wrapper = 1;

    // If no modification is needed. We're just going to play some
    // symbol table games instead

    if (docstring && doc_entry) 
      need_wrapper = 1;

    if (!need_wrapper) {
      func << iname << " = " << module << "." << iname << "\n\n";
    } else {
      func << "def " << iname << "(";
      p = l->get_first();
      i = 0;
      while(p) {
	if (!p->ignore) {
	  if (i >= pcount-numopt) {
	    have_optional = 1;
	    func << "*args";
	    shadow_defargs(p,l,i,pcount,numopt,translate,tab4);
	    break;
	  }
	  func << "arg" << i;
	  p = l->get_next();
	  if (p)
	    if (!p->ignore)
	      func << ",";
	  i++;
	} else {
	  p = l->get_next();
	  if (p)
	    if ((i > 0) && (!p->ignore))
	      func << ",";
	}
      }
      func << "):\n";

      // Create a docstring for this 
      if (docstring && doc_entry) {
	func << tab4 << "\"\"\"" << add_docstring(doc_entry) << "\"\"\"\n";
      }
      func << translate;
      func << tab4;

      //      if ((d->type != T_VOID) || (d->is_pointer > 0))

      func << "val = ";
      
      //      if ((hash.lookup(d->name)) && (d->is_pointer <=1))
      //	func << (char *) hash.lookup(d->name) << "Ptr(";
      
      // Big, big, big ugly hack.  If default arguments are involved, we've got
      // to go through a handler function instead.  Bleah!

      if (have_optional) {
	func << "apply(" << module << "." << iname << ",(";
      } else {
	func << module << "." << iname << "(";
      }
      p = l->get_first();
      i = 0;
      while(p) {
	if (!p->ignore) {
	  if (i >= (pcount-numopt)) {
	    func << ")+args";
	    break;
	  }
	  func << "arg" << i;
	  if ((hash.lookup(p->t->name)) && (p->t->is_pointer <= 1))
	    func << ".this";
	  p = l->get_next();
	  if (p)
	    if (!p->ignore)
	      func << ",";
	  i++;
	} else {
	  p = l->get_next();
	  if (p)
	    if ((i > 0) && (!p->ignore))
	      func << ",";
	}
      }
      //      if ((hash.lookup(d->name)) && (d->is_pointer <=1))
      //	func << "))\n";
      //      else
      func << ")\n";

      // Check to see if return type is an object
      if ((hash.lookup(d->name)) && (d->is_pointer <= 1)) {
	
	//  If the output of this object has been remapped in any way, we're
	//  going to return it as a bare object.
	
	if (!typemap_check("out",typemap_lang,d,iname)) {

	  // If there are output arguments, we are going to return the value
          // unchanged.  Otherwise, emit some shadow class conversion code.

	  if (!have_output) {
	    func << tab4 << "val = " << (char *) hash.lookup(d->name) << "Ptr(val)\n";
	    if (((hash.lookup(d->name)) && (d->is_pointer < 1)) ||
		((hash.lookup(d->name)) && (d->is_pointer == 1) && NewObject))
	      func << tab4 << "val.thisown = 1\n";
	  } else {
	    // Does nothing--returns the value unmolested
	  }
#ifdef OLD_METHOD
	  // This is the old behavior.  Now obsolete 
	  if (have_output) {
	    func << tab4 << "val = [" << (char *) hash.lookup(d->name) << "Ptr(val[0])] + val[1:]\n";
	    if (((hash.lookup(d->name)) && (d->is_pointer < 1)) ||
		((hash.lookup(d->name)) && (d->is_pointer == 1) && NewObject))
	      func << tab4 << "val[0].thisown = 1\n";
	  } else {
	    func << tab4 << "val = " << (char *) hash.lookup(d->name) << "Ptr(val)\n";
	    if (((hash.lookup(d->name)) && (d->is_pointer < 1)) ||
		((hash.lookup(d->name)) && (d->is_pointer == 1) && NewObject))
	      func << tab4 << "val.thisown = 1\n";
	  }
#endif
	}
      }
      func << tab4 << "return val\n\n";
    }
  }
}

// -----------------------------------------------------------------------
// PYTHON::link_variable(char *name, char *iname, DataType *d)
//
// Input variables:
//     name = the real name of the variable being linked
//    iname = Name of the variable in the interpreter (may be different)
//        d = Datatype of the variable.
//
// This creates a pair of functions for evaluating/setting the value
// of a variable.   These are then added to the special SWIG global
// variable type.
// -----------------------------------------------------------------------

void PYTHON::link_variable(char *name, char *iname, DataType *t) {

    char   *wname;
    static int have_globals = 0;
    char   *tm;

    WrapperFunction getf, setf;

    // If this is our first call, add the globals variable to the
    // Python dictionary.

    if (!have_globals) {
      fprintf(f_init,"\t PyDict_SetItemString(d,\"%s\", SWIG_globals);\n",global_name);
      have_globals=1;
      if ((shadow) && (!(shadow & PYSHADOW_MEMBER))) {
	vars << global_name << " = " << module << "." << global_name << "\n";
      }
    }
    // First make a sanitized version of the function name (in case it's some
    // funky C++ thing).
    
    wname = name_wrapper(name,"");

    // ---------------------------------------------------------------------
    // Create a function for setting the value of the variable
    // ---------------------------------------------------------------------

    setf.def << "static int " << wname << "_set(PyObject *val) {";
    if (!(Status & STAT_READONLY)) {
      if ((tm = typemap_lookup("varin","python",t,name,"val",name))) {
	setf.code << tm << "\n";
	setf.code.replace("$name",iname);
      } else {
	if ((t->type != T_VOID) || (t->is_pointer)) {
	  if (!t->is_pointer) {
	    
	    // Have a real value here 
	    
	    switch(t->type) {
	    case T_INT: case T_SHORT: case T_LONG :
	    case T_UINT: case T_USHORT: case T_ULONG:
	    case T_SINT: case T_SSHORT: case T_SLONG:
	    case T_SCHAR: case T_UCHAR: case T_BOOL:
	      // Get an integer value
	      setf.add_local(t->print_type(), "tval");
	      setf.code << tab4 << "tval = " << t->print_cast() << "PyInt_AsLong(val);\n"
			<< tab4 << "if (PyErr_Occurred()) {\n"
			<< tab8 << "PyErr_SetString(PyExc_TypeError,\"C variable '"
			<< iname << "'(" << t->print_type() << ")\");\n"
			<< tab8 << "return 1; \n"
			<< tab4 << "}\n"
			<< tab4 << name << " = tval;\n";
	      break;
	      
	    case T_FLOAT: case T_DOUBLE:
	      // Get a floating point value
	      setf.add_local(t->print_type(), "tval");
	      setf.code << tab4 << "tval = " << t->print_cast() << "PyFloat_AsDouble(val);\n"
			<< tab4 << "if (PyErr_Occurred()) {\n"
			<< tab8 << "PyErr_SetString(PyExc_TypeError,\"C variable '"
			<< iname << "'(" << t->print_type() << ")\");\n"
			<< tab8 << "return 1; \n"
			<< tab4 << "}\n"
			<< tab4 << name << " = tval;\n";
	      break;
	      
	      // A single ascii character
	      
	    case T_CHAR:
	      setf.add_local("char *", "tval");
	      setf.code << tab4 << "tval = (char *) PyString_AsString(val);\n"
			<< tab4 << "if (PyErr_Occurred()) {\n"
			<< tab8 << "PyErr_SetString(PyExc_TypeError,\"C variable '"
			<< iname << "'(" << t->print_type() << ")\");\n"
			<< tab8 << "return 1; \n"
			<< tab4 << "}\n"
			<< tab4 << name << " = *tval;\n";
	      break;
	    case T_USER:
	      setf.add_local("char *", "tval");
	      t->is_pointer++;
	      setf.add_local(t->print_type(),"temp");
	      setf.code << tab4 << "tval = (char *) PyString_AsString(val);\n"
			<< tab4 << "if (PyErr_Occurred()) {\n"
			<< tab8 << "PyErr_SetString(PyExc_TypeError,\"C variable '"
			<< iname << "'(" << t->print_type() << ")\");\n"
			<< tab8 << "return 1; \n"
			<< tab4 << "}\n";
	      
	      get_pointer(iname,"value","tval","temp",t,setf.code,"1");
	      setf.code << tab4 << name << " = *temp;\n";
	      t->is_pointer--;
	      break;
	    default:
	      fprintf(stderr,"%s : Line %d. Unable to link with type %s.\n", input_file, line_number, t->print_type());
	    }
	  } else {
	    
	    // Parse a pointer value
	    
	    if ((t->type == T_CHAR) && (t->is_pointer == 1)) {
	      setf.add_local("char *", "tval");
	      setf.code << tab4 << "tval = (char *) PyString_AsString(val);\n"
			<< tab4 << "if (PyErr_Occurred()) {\n"
			<< tab8 << "PyErr_SetString(PyExc_TypeError,\"C variable '"
			<< iname << "'(" << t->print_type() << ")\");\n"
			<< tab8 << "return 1; \n"
			<< tab4 << "}\n";
	      
	      if (CPlusPlus) {
		setf.code << tab4 << "if (" << name << ") delete [] " << name << ";\n"
			  << tab4 << name << " = new char[strlen(tval)+1];\n"
			  << tab4 << "strcpy(" << name << ",tval);\n";
	      } else {
		setf.code << tab4 << "if (" << name << ") free(" << name << ");\n"
			  << tab4 << name << " = (char *) malloc(strlen(tval)+1);\n"
			  << tab4 << "strcpy(" << name << ",tval);\n";
	      }
	    } else {
	      
	      // Is a generic pointer value.
	      
	      setf.add_local("char *", "tval");
	      setf.add_local(t->print_type(),"temp");
	      setf.code << tab4 << "tval = (char *) PyString_AsString(val);\n"
			<< tab4 << "if (PyErr_Occurred()) {\n"
			<< tab8 << "PyErr_SetString(PyExc_TypeError,\"C variable '"
			<< iname << "'(" << t->print_type() << ")\");\n"
			<< tab8 << "return 1; \n"
			<< tab4 << "}\n";
	      
	      get_pointer(iname,"value","tval","temp",t,setf.code,"1");
	      setf.code << tab4 << name << " = temp;\n";
	    }
	  }
	}
      }
      setf.code << tab4 << "return 0;\n";
    } else {
      // Is a readonly variable.  Issue an error
      setf.code << tab4 << "PyErr_SetString(PyExc_TypeError,\"Variable " << iname
		<< " is read-only.\");\n"
		<< tab4 << "return 1;\n";
    }
    
    setf.code << "}\n";
    
    // Dump out function for setting value
    
    setf.print(f_wrappers);
    
    // ----------------------------------------------------------------
    // Create a function for getting the value of a variable
    // ----------------------------------------------------------------
    
    getf.def << "static PyObject *" << wname << "_get() {";
    getf.add_local("PyObject *","pyobj");
    if ((tm = typemap_lookup("varout","python",t,name,name,"pyobj"))) {
      getf.code << tm << "\n";
      getf.code.replace("$name",iname);
    } else if ((tm = typemap_lookup("out","python",t,name,name,"pyobj"))) {
      getf.code << tm << "\n";
      getf.code.replace("$name",iname);
    } else {
      if ((t->type != T_VOID) || (t->is_pointer)) {
	if (!t->is_pointer) {
	  
	  /* Is a normal datatype */
	  switch(t->type) {
	  case T_INT: case T_SINT: case T_UINT: 
	  case T_SHORT: case T_SSHORT: case T_USHORT:
	  case T_LONG: case T_SLONG: case T_ULONG:
	  case T_SCHAR: case T_UCHAR: case T_BOOL:
	    getf.code << tab4 << "pyobj = PyInt_FromLong((long) " << name << ");\n";
	    break;
	  case T_FLOAT: case T_DOUBLE:
	    getf.code << tab4 << "pyobj = PyFloat_FromDouble((double) " << name << ");\n";
	    break;
	  case T_CHAR:
	    getf.add_local("char","ptemp[2]");
	    getf.code << tab4 << "ptemp[0] = " << name << ";\n"
		      << tab4 << "ptemp[1] = 0;\n"
		      << tab4 << "pyobj = PyString_FromString(ptemp);\n";
	    break;
	  case T_USER:
	    // Hack this into a pointer
	    getf.add_local("char", "ptemp[128]");
	    t->is_pointer++;
	    getf.code << tab4 << "SWIG_MakePtr(ptemp,(char *) &" << name
		      << "," << quote << t->print_mangle() << quote << ");\n"
		      << tab4 << "pyobj = PyString_FromString(ptemp);\n";
	    t->is_pointer--;
	    break;
	  default:
	    fprintf(stderr,"Unable to link with type %s\n", t->print_type());
	    break;
	  }
	} else {
	  
	  // Is some sort of pointer value
	  if ((t->type == T_CHAR) && (t->is_pointer == 1)) {
	    getf.code << tab4 << "if (" << name << ")\n"
		      << tab8 << "pyobj = PyString_FromString(" << name << ");\n"
		      << tab4 << "else pyobj = PyString_FromString(\"(NULL)\");\n";
	  } else {
	    getf.add_local("char","ptemp[128]");
	    getf.code << tab4 << "SWIG_MakePtr(ptemp, (char *) " << name << ",\""
		      << t->print_mangle() << "\");\n"
		      << tab4 << "pyobj = PyString_FromString(ptemp);\n";
	  }
	}
      }
    }
    
    getf.code << tab4 << "return pyobj;\n"
	      << "}\n";
    
    getf.print(f_wrappers);
    
    // Now add this to the variable linking mechanism

    fprintf(f_init,"\t SWIG_addvarlink(SWIG_globals,\"%s\",%s_get, %s_set);\n", iname, wname, wname);


    // Fill in the documentation entry

    if (doc_entry) {
      doc_entry->usage << usage_var(iname, t);
      doc_entry->cinfo << "Global : " << t->print_type() << " " << name;
    }

    // ----------------------------------------------------------
    // Output a shadow variable.  (If applicable and possible)
    // ----------------------------------------------------------
    if ((shadow) && (!(shadow & PYSHADOW_MEMBER))) {
      if ((hash.lookup(t->name)) && (t->is_pointer <= 1)) {
	vars << iname << " = " << (char *) hash.lookup(t->name) << "Ptr(" << module << "." << global_name
	     << "." << iname << ")\n";
      }
    }
}

// -----------------------------------------------------------------------
// PYTHON::declare_const(char *name, char *iname, DataType *type, char *value)
//
// Makes a constant as defined with #define.  Constants are added to the
// module's dictionary and are **NOT** guaranteed to be read-only,
// sorry.
//
// ------------------------------------------------------------------------

void PYTHON::declare_const(char *name, char *, DataType *type, char *value) {

  char   *tm;

  // Make a static python object

  if ((tm = typemap_lookup("const","python",type,name,value,name))) {
    fprintf(f_init,"%s\n",tm);
  } else {

    if ((type->type == T_USER) && (!type->is_pointer)) {
      fprintf(stderr,"%s : Line %d.  Unsupported constant value.\n", input_file, line_number);
      return;
    }
    
    if (type->is_pointer == 0) {
      switch(type->type) {
      case T_INT:case T_SINT: case T_UINT: case T_BOOL:
      case T_SHORT: case T_SSHORT: case T_USHORT:
      case T_LONG: case T_SLONG: case T_ULONG:
      case T_SCHAR: case T_UCHAR:
	fprintf(f_init,"\t PyDict_SetItemString(d,\"%s\", PyInt_FromLong((long) %s));\n",name,value);
	break;
      case T_DOUBLE:
      case T_FLOAT:
	fprintf(f_init,"\t PyDict_SetItemString(d,\"%s\", PyFloat_FromDouble((double) %s));\n",name,value);
	break;
      case T_CHAR :
	fprintf(f_init,"\t PyDict_SetItemString(d,\"%s\", PyString_FromString(\"%s\"));\n",name,value);
	break;
      default:
	fprintf(stderr,"%s : Line %d. Unsupported constant value.\n", input_file, line_number);
	break;
      }
    } else {
      if ((type->type == T_CHAR) && (type->is_pointer == 1)) {
	fprintf(f_init,"\t PyDict_SetItemString(d,\"%s\", PyString_FromString(\"%s\"));\n",name,value);
      } else {
	// A funky user-defined type.  We're going to munge it into a string pointer value
	fprintf(f_init,"\t {\n");
	fprintf(f_init,"\t\t char %s_char[%d];\n", name, (int) strlen(type->print_mangle()) + 20);
	fprintf(f_init,"\t\t SWIG_MakePtr(%s_char, (void *) (%s),\"%s\");\n",
		name, value, type->print_mangle());
	fprintf(f_init,"\t\t PyDict_SetItemString(d,\"%s\", PyString_FromString(%s_char));\n",name,name);
	fprintf(f_init,"\t }\n");
      }
    }
  }
  if ((shadow) && (!(shadow & PYSHADOW_MEMBER))) {
    vars << name << " = " << module << "." << name << "\n";
  }    
  if (doc_entry) {
    doc_entry->usage = "";
    doc_entry->usage << usage_const(name,type,value);
    doc_entry->cinfo = "";
    doc_entry->cinfo << "Constant: " << type->print_type();
  }
}

// ----------------------------------------------------------------------
// PYTHON::usage_var(char *iname, DataType *t)
//
// This function produces a string indicating how to use a variable.
// It is called by the documentation system to produce syntactically
// correct documentation entires.
//
// s is a pointer to a character pointer.   You should create
// a string and set this pointer to point to it.
// ----------------------------------------------------------------------

char *PYTHON::usage_var(char *iname, DataType *) {

  static String temp;

  temp = "";
  temp << global_name << "." << iname;

  // Create result.  Don't modify this

  return temp.get();
}

// ---------------------------------------------------------------------------
// PYTHON::usage_func(char *iname, DataType *t, ParmList *l)
// 
// Produces a string indicating how to call a function in the target
// language.
//
// ---------------------------------------------------------------------------

char *PYTHON::usage_func(char *iname, DataType *, ParmList *l) {

  static String temp;
  Parm  *p;
  int    i;

  temp = "";
  temp << iname << "(";
  
  // Now go through and print parameters 
  // You probably don't need to change this

  i = 0;
  p = l->get_first();
  while (p != 0) {
    if (!p->ignore) {
      i++;
      /* If parameter has been named, use that.   Otherwise, just print a type  */

      if ((p->t->type != T_VOID) || (p->t->is_pointer)) {
	if (strlen(p->name) > 0) {
	  temp << p->name;
	} else {
	  temp << p->t->print_type();
	}
      }
      p = l->get_next();
      if (p != 0) {
	if (!p->ignore)
	  temp << ",";
      }
    } else {
      p = l->get_next();
      if (p) {
	if ((!p->ignore) && (i > 0))
	  temp << ",";
      }
    }
  }

  temp << ")";

  // Create result. Don't change this

  return temp.get();

}


// ----------------------------------------------------------------------
// PYTHON::usage_const(char *iname, DataType *type, char *value)
//
// Produces a string for a constant.   Really about the same as
// usage_var() except we'll indicate the value of the constant.
// ----------------------------------------------------------------------

char *PYTHON::usage_const(char *iname, DataType *, char *value) {

  static String temp;
  temp = "";
  temp << iname << " = " << value;

  return temp.get();
}

// -----------------------------------------------------------------------
// PYTHON::add_native(char *name, char *funcname)
//
// Add a native module name to the methods list.
// -----------------------------------------------------------------------

void PYTHON::add_native(char *name, char *funcname) {
  add_method(name, funcname);
  if (shadow) {
    func << name << " = " << module << "." << name << "\n\n";
  }
}

// -----------------------------------------------------------------------
// PYTHON::cpp_class_decl(char *name, char *rename, char *type)
//
// Treatment of an empty class definition.    Used to handle
// shadow classes across modules.
// -----------------------------------------------------------------------

void PYTHON::cpp_class_decl(char *name, char *rename, char *type) {
    char temp[256];
    if (shadow) {
	hash.add(name,copy_string(rename));
	// Add full name of datatype to the hash table
	if (strlen(type) > 0) {
	  sprintf(temp,"%s %s", type, name);
	  hash.add(temp,copy_string(rename));
	}
    }
}

// -----------------------------------------------------------------------
// PYTHON::pragma(char *name, char *type)
//
// Pragma directive. Used to do various python specific things
// -----------------------------------------------------------------------

void PYTHON::pragma(char *lang, char *cmd, char *value) {

    if (strcmp(lang,"python") == 0) {
	if (strcmp(cmd,"CODE") == 0) {
	  if (shadow) {
	    fprintf(f_shadow,"%s\n",value);
	  }
	} else if (strcmp(cmd,"code") == 0) {
	  if (shadow) {
	    fprintf(f_shadow,"%s\n",value);
	  }
	} else if (strcmp(cmd,"include") == 0) {
	  if (shadow) {
	    if (value) {
	      if (get_file(value,pragma_include) == -1) {
		fprintf(stderr,"%s : Line %d. Unable to locate file %s\n", input_file, line_number, value);
	      }
	    }
	  }
	} else {
	  fprintf(stderr,"%s : Line %d. Unrecognized pragma.\n", input_file, line_number);
	}
    }
}
	    
/*********************************************************************************
 *
 * $Log: python.cxx,v $
 * Revision 1.60  1997/07/27 20:29:59  beazley
 * Changes to shadow class mechanism for output typemaps.
 *
 * Revision 1.59  1997/07/09 03:10:52  beazley
 * First cut at eliminating compiler warnings.
 *
 * Revision 1.58  1997/07/08 05:19:47  beazley
 * Fixed bug in shadow-class generation for non-class functions returning
 * values via argout typemaps.
 *
 * Revision 1.57  1997/07/03 03:25:46  beazley
 * Fixed some code generation problems with shadow classes and output
 * arguments.
 *
 * Revision 1.56  1997/06/29 19:08:25  beazley
 * Changed EXPORT to SWIGEXPORT
 *
 * Revision 1.55  1997/06/22 20:51:20  beazley
 * Minor change to docstring option.
 *
 * Revision 1.54  1997/06/22 16:53:22  beazley
 * Minor changes.
 *
 * Revision 1.53  1997/06/20 22:37:59  beazley
 * Fixed compiler warnings
 *
 * Revision 1.52  1997/06/17 04:43:10  beazley
 * Fixed bugs with %name().  Moved to unified naming scheme.
 *
 * Revision 1.51  1997/05/28 21:41:21  beazley
 * Moved revision history to end.
 *
 * Revision 1.50  1997/05/24 05:15:52  beazley
 * Added the "build" typemap.
 *
 * Revision 1.49  1997/05/19 19:10:39  beazley
 * Fixed bug in native functions and shadow classes.
 *
 * Revision 1.48  1997/05/19 16:27:52  beazley
 * Added a few more typemap variables.
 *
 * Revision 1.47  1997/05/09 16:29:14  beazley
 * Fixed a bug in the "check" typemap.
 *
 * Revision 1.46  1997/05/08 05:42:21  beazley
 * Added $cleanup symbol.   Fixed core dump on empty files.
 *
 * Revision 1.45  1997/05/05 15:52:08  beazley
 * A few minor bug fixes in code generation.  Added support for
 * parameterized typemaps.   Bug fixes with "ignore" and "argout"
 * typemaps.
 *
 * Revision 1.44  1997/04/19 21:26:01  beazley
 * Added support for %new directive.  A few new pragma directives.
 *
 * Revision 1.43  1997/03/19 23:48:04  beazley
 * Changed "constrain" typemap to "check"
 *
 * Revision 1.42  1997/03/18 22:27:29  beazley
 * Added constrain typemap
 *
 * Revision 1.41  1997/03/16 21:26:58  beazley
 * Fixed bug with -c option.
 *
 * Revision 1.40  1997/03/12 05:03:43  beazley
 * Minor bug fixes
 *
 * Revision 1.39  1997/03/08 23:11:54  beazley
 * Minor tweak to code generation and change of ordering in a few spots.
 *
 * Revision 1.38  1997/03/02 22:40:57  beazley
 * Removed warnings.   Minor improvements
 *
 * Revision 1.37  1997/02/19 23:03:42  beazley
 * Added create_command() function for C++ optimization.
 *
 * Revision 1.36  1997/02/16 18:51:51  beazley
 * Modified to allowed ignore arguments.   Bug fixes to default argument
 * handling.
 *
 * Revision 1.35  1997/01/30 05:51:32  beazley
 * Fixed Dec alpha bug with extra space inserted before an endif.
 *
 * Revision 1.34  1997/01/27 05:13:45  beazley
 * Added support for default arguments in shadow classes.
 *
 * Revision 1.33  1997/01/08 05:43:06  beazley
 * Pre 1.1b3 checkin
 *
 * Revision 1.32  1997/01/06 17:12:03  beazley
 * Added support for typemaps.  Multiple inheritance.
 *
 * Revision 1.31  1996/12/26 23:03:19  beazley
 * Modified to use new pointer type-checker
 *
 * Revision 1.30  1996/12/26 04:48:00  beazley
 * Added support for %module directive with multiple modules
 *
 * Revision 1.29  1996/12/03 08:41:26  beazley
 * pre-1.1b2 checkin
 *
 * Revision 1.28  1996/11/12 20:01:57  beazley
 * Changes to support new documentation and C++ handling
 *
 * Revision 1.27  1996/10/23 05:24:33  beazley
 * Added support for 'bool' datatype
 *
 * Revision 1.26  1996/09/26 21:50:17  dmb
 * Minor fixes
 *
 * Revision 1.25  1996/08/29 05:41:00  dmb
 * Fixed help message
 *
 * Revision 1.24  1996/08/27 23:02:21  dmb
 * Minor changes to error handling
 *
 * Revision 1.23  1996/08/25 00:05:13  dmb
 * More improvements to shadow classes
 *
 * Revision 1.22  1996/08/21 16:51:37  dmb
 * Cleanup to eliminate warning messages
 *
 * Revision 1.21  1996/08/21 05:50:28  dmb
 * More changes to shadow classes.
 *
 * Revision 1.20  1996/08/16 04:17:21  dmb
 * Added SWIG_name declaration
 *
 * Revision 1.19  1996/08/12 01:50:03  dmb
 * Almost a completely new version. Changed variable linking, constants,
 * and added support for new language class structure
 *
 * Revision 1.18  1996/08/02 02:57:41  dmb
 * Modified to use better parameter list functions()
 *
 * Revision 1.17  1996/07/17 15:06:30  dmb
 * Fixed a few more bugs with -strict 1 mode.
 *
 * Revision 1.16  1996/07/17 14:57:42  dmb
 * Fixed bug in -strict 1 pointer type checking mode.
 *
 * Revision 1.15  1996/06/02 00:14:36  beazley
 * Minor fixes
 *
 * Revision 1.14  1996/05/22  20:20:21  beazley
 * Add banner and cleanup functions to headers() and close() functions
 *
 * Revision 1.13  1996/05/20  23:36:07  beazley
 * Added a few more constant datatypes.
 *
 * Revision 1.12  1996/05/17  05:53:32  beazley
 * Added return by value support
 *
 * Revision 1.11  1996/05/16  03:58:34  beazley
 * Fixed bug in function return type error message.
 *
 * Revision 1.10  1996/05/13  23:45:37  beazley
 * Reworked the module/init procedure
 *
 * Revision 1.9  1996/05/10  23:38:26  beazley
 * Minor changes
 *
 * Revision 1.8  1996/05/07  03:24:10  beazley
 * Fixed bug with linking pointer variable types.
 *
 * Revision 1.7  1996/05/03  05:11:15  dmb
 * Fixed up some C++ linking problems.
 *
 * Revision 1.6  1996/05/01 22:42:01  dmb
 * Cleaned up command line option handling.
 *
 * Revision 1.5  1996/04/13 19:02:05  beazley
 * Fixed bug in module system and variable linking.
 *
 * Revision 1.4  1996/04/09  20:18:35  beazley
 * Minor cleanup.
 *
 * Revision 1.3  1996/04/08  22:09:36  beazley
 * Minor cleanup
 *
 * Revision 1.2  1996/03/28  02:47:14  beazley
 * Some bug fixes, etc...
 *
 * Revision 1.1  1996/03/24  22:15:14  beazley
 * Initial revision
 *
 *********************************************************************************/
