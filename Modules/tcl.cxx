
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

/***********************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.2/Modules/RCS/tcl.cxx,v 1.66 1997/07/09 02:40:41 beazley Exp $
 *
 * tcl.cxx
 *
 * Definitions for creating a simple, stand-alone TCL implementation.
 *
 ***********************************************************************/

#include "swig.h"
#include "swigtcl.h"
#include <ctype.h>

static char *Tcl_config="swigtcl.swg";
static char *usage = "\
Tcl Options (available with -tcl)\n\
     -module name    - Set name of module\n\
     -prefix name    - Set a prefix to be appended to all names\n\
     -htcl tcl.h     - Specify the name of the \"tcl.h\" header file\n\
     -htk tk.h       - Specify the name of the \"tk.h\" header file\n\
     -namespace      - Build module into a Tcl8 namespace. \n\
     -plugin         - Produce code compatible with Tcl Netscape Plugin\n\
     -noobject       - Omit code for object oriented interface.\n\
     -old            - Use old SWIG interface (same as -noobject).\n\n";


static char *ns_name = 0;

static String mod_init;
static String mod_extern;

// ---------------------------------------------------------------------
// TCL::parse_args(int argc, char *argv[])
//
// Parse tcl specific command line options
// ---------------------------------------------------------------------

void TCL::parse_args(int argc, char *argv[]) {
  
  int i = 1;
  sprintf(LibDir,"%s",tcl_path);

  // Look for certain command line options

  for (i = 1; i < argc; i++) {
      if (argv[i]) {
	  if (strcmp(argv[i],"-htcl") == 0) {
	    if (argv[i+1]) {
	      strcpy(tcl_include,argv[i+1]);
	      mark_arg(i);
	      mark_arg(i+1);
	      i++;
	    } else {
	      arg_error();
	    }
	  } else if (strcmp(argv[i],"-htk") == 0) {
	    if (argv[i+1]) {
	      strcpy(tk_include,argv[i+1]);
	      mark_arg(i);
	      mark_arg(i+1);
	      i++;
	    } else {
	      arg_error();
	    }
	  } else if (strcmp(argv[i],"-prefix") == 0) {
	    if (argv[i+1]) {
	      prefix = new char[strlen(argv[i+1])+2];
	      strcpy(prefix, argv[i+1]);
	      mark_arg(i);
	      mark_arg(i+1);
	      i++;
	    } else {
	      arg_error();
	    }
	  } else if (strcmp(argv[i],"-module") == 0) {
	    if (argv[i+1]) {
	      set_module(argv[i+1],0);
	      mark_arg(i);
	      mark_arg(i+1);
	      i++;
	    } else {
	      arg_error();
	    }
	  } else if (strcmp(argv[i],"-plugin") == 0) {
	    Plugin = 1;
	    mark_arg(i);
	  } else if (strcmp(argv[i],"-namespace") == 0) {
	    nspace = 1;
	    mark_arg(i);
	  } else if (strcmp(argv[i],"-old") == 0) {
	    shadow = 0;
	    mark_arg(i);
          } else if (strcmp(argv[i],"-noobject") == 0) {
	    shadow = 0;
	    mark_arg(i);
	  } else if (strcmp(argv[i],"-help") == 0) {
	    fputs(usage,stderr);
	  }
      }
  }

  // If a package has been specified, make sure it ends with a '_'

  if (prefix) {
    ns_name = copy_string(prefix);
    if (prefix[strlen(prefix)] != '_') {
      prefix[strlen(prefix)+1] = 0;
      prefix[strlen(prefix)] = '_';
    }
  } else 
    prefix = "";

  // Create a symbol SWIGTCL

  add_symbol("SWIGTCL",0,0);
  typemap_lang = "tcl";

  // Attempt to load up the C++ configuration files

  get_file("delcmd.swg",delcmd);
  get_file("methodcmd.swg",methodcmd);
  get_file("objcmd.swg",objcmd);

}

// ---------------------------------------------------------------------
// void TCL::parse()
//
// Start parsing an interface file for Tcl.
// ---------------------------------------------------------------------

void TCL::parse() {

  fprintf(stderr,"Making wrappers for Tcl\n");
  
  // Print out TCL specific headers
  
  headers();
  
  // Run the parser
  
  yyparse();

}

// ---------------------------------------------------------------------
// TCL::set_module(char *mod_name,char **mod_list)
//
// Sets the module name.
// Does nothing if it's already set (so it can be overridden as a command
// line option).
//
// mod_list is a NULL-terminated list of additional modules.  This
// is really only useful when building static executables and other
// things.
//----------------------------------------------------------------------

void TCL::set_module(char *mod_name, char **mod_list) {

  char temp[256], *c;
  int  i;

  if (module) return;
  
  module = new char[strlen(mod_name)+1];
  strcpy(module,mod_name);

  // Fix capitalization for Tcl 

  c = module;
  while (*c) {
    *c = (char) tolower(*c);
    c++;
  }

  // Now create an initialization function

  sprintf(temp,"%s_Init", module);
  init_name = new char[strlen(temp) + 1];
  strcpy(init_name, temp);
  *init_name = toupper(*init_name);
  sprintf(temp,"%s_SafeInit",module);
  safe_name = new char[strlen(temp)+1];
  strcpy(safe_name,temp);
  *safe_name = toupper(*safe_name);

  if (!ns_name) ns_name = copy_string(module);

  // If namespaces have been specified, set the prefix to the module name

  if ((nspace) && (strlen(prefix) < 1)) {
    prefix = new char[strlen(module)+2];
    strcpy(prefix,module);
    prefix[strlen(module)] = '_';
    prefix[strlen(module)+1] = 0;
  }

  // If additional modules have been specified, create some code for
  // initializing them.

  if (mod_list) {
    i = 0;
    while (mod_list[i]) {
      c = mod_list[i];
      while (*c) {
	*c = (char) tolower(*c);
	c++;
      }
      sprintf(temp,"%s_Init",mod_list[i]);
      temp[0] = toupper(temp[0]);
      
      // Dump out some initialization code
      
      mod_init << tab4 << "if (" << temp << "(" << interp_name << ") == TCL_ERROR) {\n"
	       << tab8 << "return TCL_ERROR;\n"
	       << tab4 << "}\n\n";
      mod_extern << "extern int " << temp << "(Tcl_Interp *);\n";
      i++;
    }
  }
}


// ---------------------------------------------------------------------
// TCL::set_init(char *iname)
//
// Sets the initialization function name.
// Does nothing if it's already set
//
//----------------------------------------------------------------------

void TCL::set_init(char *iname) {

  if (init_name) return;

  init_name = new char[strlen(iname)+1];
  strcpy(init_name, iname);

}

// ---------------------------------------------------------------------
// TCL::headers(void)
//
// Generate the appropriate header files for TCL interface.
// ----------------------------------------------------------------------

void TCL::headers(void)
{

  emit_banner(f_header);
  if (!Plugin) 
    fprintf(f_header,"/* Implementation : TCL 7.x */\n\n");
  else
    fprintf(f_header,"/* Implementation : TCL - Netscape plugin */\n\n");
  fprintf(f_header,"#define INCLUDE_TCL    <%s>\n", tcl_include);
  fprintf(f_header,"#define INCLUDE_TK     <%s>\n", tk_include);
  fprintf(f_header,"#include INCLUDE_TCL\n");
  fprintf(f_header,"#include <string.h>\n");
  fprintf(f_header,"#include <stdlib.h>\n");
  fprintf(f_header,"#define SWIGTCL\n");
  
  // Include a Tcl configuration file for Unix,Mac,Wintel.
  
  if (insert_file(Tcl_config, f_header) == -1) {
    fprintf(f_header,"#define SWIGEXPORT(a,b) a b\n");
  }
  // Write out hex conversion functions for pointers  

  if (!NoInclude)
    emit_hex(f_header);
  else {
    fprintf(f_header,"#ifdef __cplusplus\n");
    fprintf(f_header,"extern \"C\" {\n");
    fprintf(f_header,"#endif\n");
    fprintf(f_header,"extern void SWIG_MakePtr(char *, void *, char *);\n");
    fprintf(f_header,"extern void SWIG_RegisterMapping(char *, char *, void *(*)(void *));\n");
    fprintf(f_header,"extern char *SWIG_GetPtr(char *, void **, char *);\n");
    fprintf(f_header,"#ifdef __cplusplus\n");
    fprintf(f_header,"}\n");
    fprintf(f_header,"#endif\n");
  }
}

// --------------------------------------------------------------------
// TCL::initialize(void)
//
// Produces an initialization function.   Assumes that the init function
// name has already been specified.
// ---------------------------------------------------------------------

void TCL::initialize() 
{

  if ((!ns_name) && (nspace)) {
    fprintf(stderr,"Tcl error.   Must specify a namespace.\n");
    SWIG_exit(1);
  }

  if (!init_name) {
    init_name = "Swig_Init";
    fprintf(stderr,"SWIG : *** Warning. No module name specified.\n");
  }

  fprintf(f_header,"#define SWIG_init    %s\n", init_name);
  if (!module) module = "swig";
  fprintf(f_header,"#define SWIG_name    \"%s\"\n", module);
  if (nspace) {
    fprintf(f_header,"#define SWIG_prefix  \"%s::\"\n", ns_name);
    fprintf(f_header,"#define SWIG_namespace \"%s\"\n\n", ns_name);
  } else {
    fprintf(f_header,"#define SWIG_prefix  \"%s\"\n", prefix);
    fprintf(f_header,"#define SWIG_namespace \"\"\n\n");
  }
  fprintf(f_header,"#ifdef __cplusplus\n");
  fprintf(f_header,"extern \"C\" {\n");
  fprintf(f_header,"#endif\n");
  fprintf(f_header,"#ifdef MAC_TCL\n");
  fprintf(f_header,"#pragma export on\n");
  fprintf(f_header,"#endif\n");
  if (Plugin)
  	fprintf(f_header,"SWIGEXPORT(int,%s)(Tcl_Interp *);\n", safe_name);
  fprintf(f_header,"SWIGEXPORT(int,%s)(Tcl_Interp *);\n", init_name);
  fprintf(f_header,"#ifdef MAC_TCL\n");
  fprintf(f_header,"#pragma export off\n");
  fprintf(f_header,"#endif\n");
  fprintf(f_header,"#ifdef __cplusplus\n");
  fprintf(f_header,"}\n");
  fprintf(f_header,"#endif\n");
  
  fprintf(f_init,"SWIGEXPORT(int,%s)(Tcl_Interp *%s) {\n", init_name, interp_name);
  
  fprintf(f_init,"\t if (%s == 0) \n", interp_name);
  fprintf(f_init,"\t\t return TCL_ERROR;\n");

  /* Check to see if other initializations need to be performed */

  if (strlen(mod_extern.get())) {
    fprintf(f_init,"%s\n",mod_init.get());
    fprintf(f_header,"#ifdef __cplusplus\n");
    fprintf(f_header,"extern \"C\" {\n");
    fprintf(f_header,"#endif\n");
    fprintf(f_header,"%s\n",mod_extern.get());
    fprintf(f_header,"#ifdef __cplusplus\n");
    fprintf(f_header,"}\n");
    fprintf(f_header,"#endif\n");
  }

  /* Check to see if we're adding support for Tcl8 nspaces */
  if (nspace) {
    fprintf(f_init,"#if (TCL_MAJOR_VERSION >= 8)\n");
    fprintf(f_init,"\t Tcl_Eval(%s,\"namespace eval %s { }\");\n", interp_name, ns_name);
    fprintf(f_init,"#endif\n");
  }
}

// ---------------------------------------------------------------------
// TCL::close(void)
//
// Wrap things up.  Close initialization function.
// ---------------------------------------------------------------------

void TCL::close(void)
{

  // Dump the pointer equivalency table

  emit_ptr_equivalence(f_init);

  // Close the init file and quit
  fprintf(f_init,"%s",postinit.get());
  fprintf(f_init,"\t return TCL_OK;\n");
  fprintf(f_init,"}\n");

  if (Plugin) {
    fprintf(f_init,"SWIGEXPORT(int,%s)(Tcl_Interp *interp) {\n",safe_name);
    fprintf(f_init,"#ifdef SAFE_SWIG\n");
    fprintf(f_init,"   return %s(interp);\n", init_name); 
    fprintf(f_init,"#else\n");
    fprintf(f_init,"   return TCL_ERROR;\n");
    fprintf(f_init,"#endif\n");	
    fprintf(f_init,"}\n");
  }
}

// ----------------------------------------------------------------------
// TCL::get_pointer(char *iname, char *srcname, char *src, char *dest,
//                  DataType *t, String &f, char *ret)
//
// iname     = name of function or variable
// srcname   = name of source
// src       = source variable in wrapper code
// dest      = destination variable in wrapper code
// t         = Datatype 
// f         = String where output is going to go
// ret       = Return action
// ----------------------------------------------------------------------

void TCL::get_pointer(char *iname, char *srcname, char *src, char *dest,
		      DataType *t, String &f, char *ret) {

  // Pointers are read as hex-strings with encoded type information

  f << tab4 << "if (SWIG_GetPtr(" << src << ",(void **) &" << dest << ",";

  if (t->type == T_VOID) f << "(char *) 0)) {\n";
  else 
    f << "\"" << t->print_mangle() << "\")) {\n";

  // Now emit code according to the level of strictness desired

  switch(TypeStrict) {
  case 0: // No type checking
    f << tab4 << "}\n";
    break;
  case 1: // Warning message only
    f << tab8 << "fprintf(stderr,\"Warning : type mismatch in " << srcname 
      << " of " << iname << ". Expected " << t->print_mangle() 
      << ", received %s\\n\"," << src << ");\n"
      << tab4 << "}\n";
  case 2: // Super strict mode.
    f << tab8 << "Tcl_SetResult(interp, \"Type error in " << srcname << " of " << iname
      << ". Expected " << t->print_mangle() << ", received \", TCL_STATIC);\n"
      << tab8 << "Tcl_AppendResult(interp, " << src << ", (char *) NULL);\n"
      << tab8 << ret << ";\n"
      << tab4 << "}\n";
    break;
  default :
    fprintf(stderr,"Unknown strictness level\n");
    break;
  }
}

// ----------------------------------------------------------------------
// TCL::create_command(char *cname, char *iname)
//
// Creates a Tcl command from a C function.
// ----------------------------------------------------------------------

void TCL::create_command(char *cname, char *iname) {


  char *wname = name_wrapper(cname,prefix);

  fprintf(f_init,"\t Tcl_CreateCommand(%s,SWIG_prefix \"%s\",%s, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);\n", interp_name, iname, wname);

  // Add interpreter name to repeatcmd hash table.  This hash is used in C++ code
  // generation to try and find repeated wrapper functions.

  repeatcmd.add(iname,copy_string(wname));
}

// ----------------------------------------------------------------------
// TCL::create_function(char *name, char *iname, DataType *d, ParmList *l)
//
// Create a function declaration and register it with the interpreter.
// ----------------------------------------------------------------------

void TCL::create_function(char *name, char *iname, DataType *d, ParmList *l)
{
  Parm            *p;
  int              pcount,i,j;
  char             *wname;
  char            *usage = 0;
  char             source[256], target[256], argnum[32], *tm;
  String           cleanup, outarg;
  int              numopt;
  int              have_build = 0;        // Status indicating build typemap
  String           build;

  WrapperFunction  f;

  // Make a wrapper name for this function

  wname = name_wrapper(iname,prefix);

  // Now write the wrapper function itself....this is pretty ugly

  f.def << "static int " << wname << "(ClientData clientData, Tcl_Interp *interp, int argc, char *argv[]) {\n";
  f.code << tab4 << "clientData = clientData; argv = argv;\n";

  // Print out variables for storing arguments.

  pcount = emit_args(d, l, f);

  // Get number of optional arguments

  numopt = l->numopt();

  // Check the number of arguments

  usage = usage_func(iname,d,l);       // Create a usage string
  f.code << tab4 << "if ((argc < " << (pcount-numopt) +1 << ") || (argc > " << l->numarg()+1 << ")) {\n"
	 << tab8 << "Tcl_SetResult(interp, \"Wrong # args. " << usage << "\",TCL_STATIC);\n"
	 << tab8 << "return TCL_ERROR;\n"
	 << tab4 << "}\n";

  // Extract parameters.    This case statement should be used to extract
  // Function parameters.   Add more cases if you want to do more.

  i = 0;
  j = 0;
  p = l->get_first();
  while (p != 0) {
    // Produce string representations of the source and target arguments
    sprintf(source,"argv[%d]",j+1);
    sprintf(target,"_arg%d",i);
    sprintf(argnum,"%d",j+1);

    // See if this argument is being ignored

    if (!p->ignore) {
      if (j >= (pcount-numopt))
	f.code << tab4 << "if (argc >" << j+1 << ") { \n";

      // See if there is a type-mapping

      if ((tm = typemap_lookup("in","tcl",p->t,p->name,source,target,&f))) {
	// Yep.  Use it instead of the default
	f.code << tm << "\n";
	f.code.replace("$argnum",argnum);
	f.code.replace("$arg",source);
      } else {
	
	if (!p->t->is_pointer) {
	  
	  // Extract a parameter by value.
	  
	  switch(p->t->type) {
	    
	    // Signed Integers
	    
	  case T_BOOL:
	  case T_INT:
	  case T_SINT:
	  case T_SHORT:
	  case T_SSHORT:
	  case T_LONG:
	  case T_SLONG:
	  case T_SCHAR:
	    f.code << tab4 << "_arg" << i << " = " << p->t->print_cast() << " atol(argv[" << j+1 << "]);\n";
	    break;
	    
	    // Unsigned Integers
	    
	  case T_UINT:
	  case T_USHORT:
	  case T_ULONG:
	  case T_UCHAR:
	    f.code << tab4 << "_arg" << i << " = " << p->t->print_cast() << " strtoul(argv[" << j+1 
		   << "],(char **) NULL,0);\n";
	    break;
	    
	    // Floating point
	    
	  case T_FLOAT:
	  case T_DOUBLE:
	    f.code << tab4 << "_arg" << i << " = " << p->t->print_cast() << " atof(argv[" << j+1 << "]);\n";
	    break;
	    
	    // A single character
	    
	  case T_CHAR :
	    f.code << tab4 << "_arg" << i << " = *argv[" << j+1 << "];\n";
	    break;
	    
	    // Void.. Do nothing.
	    
	  case T_VOID :
	    break;
	    
	    // User defined.   This is an error.
	    
	  case T_USER:
	    
	    // Unsupported data type
	    
	  default :
	    fprintf(stderr,"%s : Line %d: Unable to use type %s as a function argument.\n",
		    input_file, line_number, p->t->print_type());
	    break;
	  }
	} else { /* Pointer type */
	  
	  // Function argument is some sort of pointer
	  // Look for a string.   Otherwise, just pull off a pointer.
	  
	  if ((p->t->type == T_CHAR) && (p->t->is_pointer == 1)) {
	    f.code << tab4 << "_arg" << i << " = argv[" << j+1 << "];\n";
	  } else {
	    
	    // Have a generic pointer type here.    Read it in as
	    // a hex-string
	    
	    char arg_temp[256];
	    sprintf(arg_temp,"argument %d",j+1);
	    get_pointer(iname,arg_temp,source,target,p->t,f.code,"return TCL_ERROR");
	  }
	}
      }
      if (j >= (pcount-numopt))
	f.code << tab4 << "} \n";
      j++;
    }

    // Check to see if there is any sort of "build" typemap (highly complicated)

    if ((tm = typemap_lookup("build","tcl",p->t,p->name,source,target))) {
      build << tm << "\n";
      have_build = 1;
    }

    // Check to see if there was any sort of a constaint typemap
    if ((tm = typemap_lookup("check","tcl",p->t,p->name,source,target))) {
      // Yep.  Use it instead of the default
      f.code << tm << "\n";
      f.code.replace("$argnum",argnum);
      f.code.replace("$arg",source);
    }

    // Check if there was any cleanup code (save it for later)
    if ((tm = typemap_lookup("freearg","tcl",p->t,p->name,target,"interp->result"))) {
      // Yep.  Use it instead of the default
      cleanup << tm << "\n";
      cleanup.replace("$argnum",argnum);
      cleanup.replace("$arg",source);
    }
    if ((tm = typemap_lookup("argout","tcl",p->t,p->name,target,"interp->result"))) {
      // Yep.  Use it instead of the default
      outarg << tm << "\n";
      outarg.replace("$argnum",argnum);
      outarg.replace("$arg",source);
    }
    p = l->get_next();   // Get next parameter and continue
    i++;
  }

  // If there was a "build" typemap, we need to go in and perform a serious hack
  
  if (have_build) {
    char temp1[32];
    char temp2[256];
    l->sub_parmnames(build);            // Replace all parameter names
    j = 1;
    for (i = 0; i < l->nparms; i++) {
      p = l->get(i);
      if (strlen(p->name) > 0) {
	sprintf(temp1,"_in_%s", p->name);
      } else {
	sprintf(temp1,"_in_arg%d", i);
      }
      sprintf(temp2,"argv[%d]",j);
      build.replaceid(temp1,temp2);
      if (!p->ignore) 
	j++;
    }
    f.code << build;
  }
    
  // Now write code to make the function call

  emit_func_call(name,d,l,f);

  // Return value if necessary 

  if ((tm = typemap_lookup("out","tcl",d,name,"_result","interp->result"))) {
    // Yep.  Use it instead of the default
    f.code << tm << "\n";
  } else if ((d->type != T_VOID) || (d->is_pointer)) {
    // Normal SWIG mappings
      
    if (!d->is_pointer) {
      
      // Function returns a "value"
      
      switch(d->type) {
	// Is a signed integer
      case T_BOOL:
      case T_INT:
      case T_SINT:
      case T_SHORT:
      case T_SSHORT:
      case T_LONG :
      case T_SLONG:
      case T_SCHAR:
	f.code << tab4 << "sprintf(interp->result,\"%ld\", (long) _result);\n";
	break;
	
	// Is an unsigned integer
      case T_UINT:
      case T_USHORT:
      case T_ULONG:
      case T_UCHAR:
	f.code << tab4 << "sprintf(interp->result,\"%lu\", (unsigned long) _result);\n";
	break;
	
	// Is a single character.  Assume we return it as a string
      case T_CHAR :
	f.code << tab4 << "sprintf(interp->result,\"%c\", _result);\n";
	break;
	
	// Floating point number
      case T_DOUBLE :
      case T_FLOAT :
	f.code << tab4 << "Tcl_PrintDouble(interp,(double) _result, interp->result);\n";
	//sprintf(interp->result,\"%0.17f\",(double) _result);\n";
	break;
	
	// User defined type
      case T_USER :
	
	// Okay. We're returning malloced memory at this point.
	// Probably dangerous, but what the hell
	
	d->is_pointer++;
	f.code << tab4 << "SWIG_MakePtr(interp->result, (void *) _result,\"" << d->print_mangle()
	       << "\");\n";
	d->is_pointer--;
	break;
	
	// Unknown type
      default :
	fprintf(stderr,"%s : Line %d: Unable to use return type %s in function %s.\n",
		input_file, line_number, d->print_type(), name);
	break;
      }
    } else {
      
      // Is a pointer return type
      
      if ((d->type == T_CHAR) && (d->is_pointer == 1)) {
	// Return a character string
	f.code << tab4 << "Tcl_SetResult(interp, (char *) _result, " << char_result << ");\n";
      } else {
	f.code << tab4 << "SWIG_MakePtr(interp->result, (void *) _result,\"" << d->print_mangle() << "\");\n";
      }
    }
  }

  // Dump argument output code;
  f.code << outarg;

  // Dump the argument cleanup code
  f.code << cleanup;

  // Look for any remaining cleanup

  if (NewObject) {
    if ((tm = typemap_lookup("newfree","tcl",d,iname,"_result",""))) {
      f.code << tm << "\n";
    }
  }

  if ((tm = typemap_lookup("ret","tcl",d,name,"_result",""))) {
    // Yep.  Use it instead of the default
    f.code << tm << "\n";
  }

  // Wrap things up (in a manner of speaking)
  
  f.code << tab4 << "return TCL_OK;\n}";

  // Substitute the cleanup code
  f.code.replace("$cleanup",cleanup);
  f.code.replace("$name",iname);

  // Dump out the function
  
  f.print(f_wrappers);

  // Add interpreter name to repeatcmd hash table.  This hash is used in C++ code
  // generation to try and find repeated wrapper functions.

  fprintf(f_init,"\t Tcl_CreateCommand(%s, SWIG_prefix \"%s\", %s, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);\n", interp_name, iname, wname);

  // If there's a documentation entry, produce a usage string
  
  if (doc_entry) {

    static DocEntry *last_doc_entry = 0;

    // Use usage as description
    doc_entry->usage << usage;

    // Set the cinfo field to specific a return type 

    if (last_doc_entry != doc_entry) {
      doc_entry->cinfo << "returns " << d->print_type();
      last_doc_entry = doc_entry;
    }
  }
}

// -----------------------------------------------------------------------
// TCL::link_variable(char *name, char *iname, DataType *t,
//                           int ex)
//
// Create a TCL link to a variable.
// -----------------------------------------------------------------------

void TCL::link_variable(char *name, char *iname, DataType *t)
{

  String    s;
  char *tm,*tm1;
  String    realname;

  
  // See if there were any typemaps

  tm = typemap_lookup("varin","tcl",t,name,"","");
  tm1 = typemap_lookup("varout","tcl",t,name,"","");
  if (tm || tm1) {
    fprintf(stderr,"%s : Line %d. Warning. varin/varout typemap methods not supported.",
	    input_file, line_number);
  }

  // Check the datatype.  Must be a valid Tcl type (there aren't many)

  if (((t->type == T_INT) && (!t->is_pointer)) ||
      ((t->type == T_UINT) && (!t->is_pointer)) ||
      ((t->type == T_SINT) && (!t->is_pointer)) ||
      ((t->type == T_DOUBLE) && (!t->is_pointer)) ||
      ((t->type == T_BOOL) && (!t->is_pointer)) ||
      ((t->type == T_CHAR) && (t->is_pointer == 1))) {

    // This is a valid TCL type. 

    if (t->type == T_UINT)
      fprintf(stderr,"%s : Line %d : ** Warning. Linkage of unsigned type may be unsafe.\n",
              input_file,  line_number);

    // Now add symbol to the TCL interpreter

    switch(t->type) {
    case T_CHAR :
      if (t->arraystr) {
	// Is an array.  We have to do something different
	fprintf(f_wrappers,"static char *tclvar%s = %s;\n",name,name);
	s << "(char *) &tclvar" << name << ", TCL_LINK_STRING";
      } else {
	s << "(char *) &" << name << ", TCL_LINK_STRING";
      }
      break;
    case T_BOOL:
    case T_INT :
    case T_UINT:
    case T_SINT:
      s << "(char *) &" << name << ", TCL_LINK_INT";
      break;
    case T_DOUBLE :
      s << "(char *) &" << name << ", TCL_LINK_DOUBLE";
      break;
    default :
      fprintf(f_init,"Fatal error. Internal error (Tcl:link_variable)\n");
      break;
    }

    if (Status & STAT_READONLY)
      s << " | TCL_LINK_READ_ONLY);\n";
    else
      s << ");\n";

    fprintf(f_init,"\t Tcl_LinkVar(%s, SWIG_prefix \"%s\", %s",interp_name, iname, s.get());    
    
    // Make a usage string for it

    if (doc_entry) {
      doc_entry->usage << usage_var(iname,t);
      doc_entry->cinfo = "";
      doc_entry->cinfo << "Global : " << t->print_type() << " " << name;
    }
  } else {

    // Have some sort of "other" type.
    // We're going to emit some functions to set/get it's value instead
    
    emit_set_get(name,iname, t);
    if (doc_entry) {
      doc_entry->cinfo = "";
      doc_entry->cinfo << "Global : " << t->print_type() << " " << iname;
    }

    // If shadow classes are enabled and we have a user-defined type
    // that we know about, create a command for it.  

    if (shadow) {
      if ((t->type == T_USER) && (t->is_pointer < 1)) {
	// See if the datatype is in our hash table
	if (hash.lookup(t->name)) {
	  // Yep.  Try to create a command for it
	  //	  postinit << tab4 << "Tcl_CreateCommand(interp, SWIG_prefix \"" << iname << "\",Tcl" << (char *) hash.lookup(t->name)
	  // << "MethodCmd, (ClientData)";

	  postinit << tab4 << "{\n"
		   << tab8 << "char cmd[] = \"" 
		   << (char *) hash.lookup(t->name) << " " << iname << " -this ["
		   << iname << "_get ]\";\n"
		   << tab8 << "Tcl_GlobalEval(interp,cmd);\n"
		   << tab4 << "}\n";

	  //	  postinit << tab4 << "Tcl_GlobalEval(interp,\"set " << iname << " [" << iname << "_get ];" 
	  //		   << (char *) hash.lookup(t->name) << " -this $" << iname << "\");\n";

	}
      }
    }
  }  
}

// -----------------------------------------------------------------------
// TCL::declare_const(char *name, char *iname, DataType *type, char *value)
//
// Makes a constant.  Really just creates a variable and links to it.
// Tcl variable linkage allows read-only variables so we'll use that
// instead of just creating a Tcl variable.
// ------------------------------------------------------------------------

void TCL::declare_const(char *name, char *, DataType *type, char *value) {

  int OldStatus = Status;      // Save old status flags
  DataType *t; 
  char   var_name[256];
  char     *tm;
  String   rvalue;

  Status = STAT_READONLY;      // Enable readonly mode.

  // Make a static variable;

  sprintf(var_name,"_wrap_const_%s",name);
  
  // See if there's a typemap

  rvalue = value;
  if ((type->type == T_CHAR) && (type->is_pointer == 1)) {
    rvalue << "\""; 
    "\"" >> rvalue;
  } 
  if ((type->type == T_CHAR) && (type->is_pointer == 0)) {
    rvalue << "'";
    "'" >> rvalue;
  }
  if ((tm = typemap_lookup("const","tcl",type,name,rvalue.get(),name))) {
    // Yep.  Use it instead of the default
    fprintf(f_init,"%s\n",tm);
  } else {

    // Create variable and assign it a value
    
    if (type->is_pointer == 0) {
      switch(type->type) {
      case T_BOOL: case T_INT: case T_SINT: case T_DOUBLE:
	fprintf(f_header,"static %s %s = %s;\n", type->print_type(), var_name, value);
	link_variable(var_name,name,type);
	break;
      case T_SHORT:
      case T_LONG:
      case T_SSHORT:
      case T_SCHAR:
      case T_SLONG:
	fprintf(f_header,"static %s %s = %s;\n", type->print_type(), var_name, value);
	fprintf(f_header,"static char *%s_char;\n", var_name);
	if (CPlusPlus)
	  fprintf(f_init,"\t %s_char = new char[32];\n",var_name);
	else
	  fprintf(f_init,"\t %s_char = (char *) malloc(32);\n",var_name);
	
	fprintf(f_init,"\t sprintf(%s_char,\"%%ld\", (long) %s);\n", var_name, var_name);
	sprintf(var_name,"%s_char",var_name);
	t = new DataType(T_CHAR);
	t->is_pointer = 1;
	link_variable(var_name,name,t);
	delete t;
	break;
      case T_UINT:
      case T_USHORT:
      case T_ULONG:
      case T_UCHAR:
	fprintf(f_header,"static %s %s = %s;\n", type->print_type(), var_name, value);
	fprintf(f_header,"static char *%s_char;\n", var_name);
	if (CPlusPlus)
	  fprintf(f_init,"\t %s_char = new char[32];\n",var_name);
	else
	  fprintf(f_init,"\t %s_char = (char *) malloc(32);\n",var_name);
	
	fprintf(f_init,"\t sprintf(%s_char,\"%%lu\", (unsigned long) %s);\n", var_name, var_name);
	sprintf(var_name,"%s_char",var_name);
	t = new DataType(T_CHAR);
	t->is_pointer = 1;
	link_variable(var_name,name,t);
	delete t;
	break;
      case T_FLOAT:
	type->type = T_DOUBLE;
	strcpy(type->name,"double");
	fprintf(f_header,"static %s %s = %s (%s);\n", type->print_type(), var_name, type->print_cast(), value);
	link_variable(var_name,name,type);
	break;
	
      case T_CHAR:
	type->is_pointer++;
	fprintf(f_header,"static %s %s = \"%s\";\n", type->print_type(), var_name, value);
	link_variable(var_name,name,type);
	type->is_pointer--;
	break;
      default:
	fprintf(stderr,"%s : Line %d. Unsupported constant value.\n", input_file, line_number);
	break;
      }
    } else {
      // Have some sort of pointer value here
      if ((type->type == T_CHAR) && (type->is_pointer == 1)) {
	// Character string
	fprintf(f_header,"static %s %s = \"%s\";\n", type->print_type(), var_name, value);
	link_variable(var_name,name,type);
      } else {
	// Something else.   Some sort of pointer value
	fprintf(f_header,"static %s %s = %s;\n", type->print_type(), var_name, value);
	fprintf(f_header,"static char *%s_char;\n", var_name);
	if (CPlusPlus)
	  fprintf(f_init,"\t %s_char = new char[%d];\n",var_name,(int) strlen(type->print_mangle())+ 20);
	else
	  fprintf(f_init,"\t %s_char = (char *) malloc(%d);\n",var_name,(int) strlen(type->print_mangle())+ 20);
	
	t = new DataType(T_CHAR);
	t->is_pointer = 1;
	fprintf(f_init,"\t SWIG_MakePtr(%s_char, (void *) %s,\"%s\");\n",
		var_name, var_name, type->print_mangle());
	sprintf(var_name,"%s_char",var_name);
	link_variable(var_name,name,t);
	delete t;
      }
    }
  }

  // Create a documentation entry for this

  if (doc_entry) {
    doc_entry->usage = "";       // Destroy any previous information from linking
    doc_entry->usage << usage_const(name, type, value);
    doc_entry->cinfo = "";
    doc_entry->cinfo << "Constant : " << type->print_type();
  }
  Status = OldStatus;
}

// ----------------------------------------------------------------------
// TCL::usage_var(char *iname, DataType *t, char **s)
//
// Produces a usage string for a tcl variable.  Stores it in s
// ----------------------------------------------------------------------

char *TCL::usage_var(char *iname, DataType *t) {

  static String temp;

  temp = "";
  if (!nspace) {
    temp << "$" << prefix << iname;
  } else { 
    temp << ns_name << "::" << iname;
  }
  if (!(((t->type == T_INT) && (!t->is_pointer)) ||
	((t->type == T_UINT) && (!t->is_pointer)) ||
	((t->type == T_DOUBLE) && (!t->is_pointer)) ||
	((t->type == T_BOOL) && (!t->is_pointer)) ||
	((t->type == T_CHAR) && (t->is_pointer)))) {
    /* We emitted a pair of set/get functions instead.  Doc will be generated for that */
    return temp;
  }
  return temp;
}


// ---------------------------------------------------------------------------
// char *TCL::usage_string(char *iname, DataType *t, ParmList *l),
// 
// Generates a generic usage string for a Tcl function.
// ---------------------------------------------------------------------------

char * TCL::usage_string(char *iname, DataType *, ParmList *l) {

  static String temp;
  Parm  *p;
  int   i, numopt,pcount;

  temp = "";
  temp << iname << " ";
  
  /* Now go through and print parameters */
  i = 0;
  pcount = l->nparms;
  numopt = l->numopt();
  p = l->get_first();
  while (p != 0) {

    // Only print an argument if not ignored

    if (!typemap_check("ignore","tcl",p->t,p->name)) {
      if (i >= (pcount-numopt))
	temp << "?";

      /* If parameter has been named, use that.   Otherwise, just print a type  */

      if ((p->t->type != T_VOID) || (p->t->is_pointer)) {
	if (strlen(p->name) > 0) {
	  temp << p->name;
	}
	else {
	  temp << "{ " << p->t->print_type() << " }";
	}
      }
      if (i >= (pcount-numopt))
	temp << "?";
      temp << " ";
      i++;
    }
    p = l->get_next();
  }
  return temp;
}

// ---------------------------------------------------------------------------
// char *TCL::usage_func(char *iname, DataType *t, ParmList *l),
// 
// Produces a usage string for a function in Tcl
// ---------------------------------------------------------------------------

char * TCL::usage_func(char *iname, DataType *t, ParmList *l) {

  String temp;

  if (nspace) {
    temp << ns_name << "::" << iname;
  } else {
    temp << prefix << iname;
  }
  return usage_string(temp,t,l);
}

// -----------------------------------------------------------------
// TCL::usage_const(char *name, DataType *type, char *value)
//                         char **s)
//
// Makes a usage string and returns it
// -----------------------------------------------------------------

char *TCL::usage_const(char *name, DataType *, char *value) {
  static String temp;
  temp = "";
  if (nspace) {
    temp << ns_name << "::" << name << " = " << value;
  } else {
    temp << "$" << prefix << name << " = " << value;
  }
  return temp;
}
    
// -------------------------------------------------------------------
// TCL::add_native(char *name, char *funcname)
//
// This adds an already written Tcl wrapper function to our
// initialization function.
// -------------------------------------------------------------------


void TCL::add_native(char *name, char *funcname) {

  fprintf(f_init,"\t Tcl_CreateCommand(%s, SWIG_prefix \"%s\", %s, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);\n",interp_name, name, funcname);

  if (doc_entry) {
    if (nspace) 
      doc_entry->usage << ns_name << "::" << name << " args";
    else
      doc_entry->usage << prefix << name << " args";

    doc_entry->cinfo << "Native method : " << funcname;
  }
    
}
 
// -------------------------------------------------------------------
// TCL::pragma(char *lname, char *name, char *value)
//
// This is an experimental %pragma handler.  Officially unsupported
// in this release, but requested in e-mail.
// --------------------------------------------------------------------

void TCL::pragma(char *lname, char *name, char *) {

  if (strcmp(lname,"tcl") == 0) {
    if (strcmp(name,"dynamic") == 0) {
      char_result = "TCL_DYNAMIC";
    } else if (strcmp(name,"static") == 0) {
      char_result = "TCL_STATIC";
    } else if (strcmp(name,"volatile") == 0) {
      char_result = "TCL_VOLATILE";
    }
  }
}


// ---------------------------------------------------------------------
// C++ Handling
//
// The following functions provide some support for C++ classes and
// C structs.   
// ---------------------------------------------------------------------

void TCL::cpp_open_class(char *classname, char *rename, char *ctype, int strip) {
  char temp[256];
  this->Language::cpp_open_class(classname,rename,ctype,strip);

  if (shadow) {
  
    config = "";
    cget = "";
    methods = "";
    options = "";
    config_options = "";
    methodnames = "";
    
    have_constructor = 0;
    have_destructor = 0;
    have_methods = 0;
    have_config = 0;
    have_cget = 0;

    if (rename)
      class_name = copy_string(rename);
    else
      class_name = copy_string(classname);
  
    base_class = (char *) 0;
    if (!strip) {
      class_type = new char[strlen(ctype)+2];
      sprintf(class_type,"%s ", ctype);
    } else
      class_type = "";

    real_classname = copy_string(classname);

    // Build up the hash table

    hash.add(real_classname,copy_string(class_name));
    sprintf(temp,"%s %s", class_type, real_classname);
    hash.add(temp,copy_string(class_name));
  }
}

void TCL::cpp_close_class() {
  String code;
  DataType *t;
  String temp;

  this->Language::cpp_close_class();
  if (shadow) {

    t = new DataType;
    sprintf(t->name,"%s%s", class_type, real_classname);
    t->type = T_USER;
    t->is_pointer = 1;
    
    // Note : The object oriented interface is defined by three files
    //     delcmd.swg          - Object deletion wrapper
    //     methodcmd.swg       - Method invocation command
    //     objcmd.swg          - Command to create a new object
    //
    // These files are located in the SWIG library.  This module
    // grabs the files and performs marker replacements to
    // build the wrapper function.
    
    // Generate a Tcl function for object destruction
    
    if (have_destructor) {
      code << delcmd;
    }

    // Dump out method code
    code << methodcmd;

    // Dump out object creation command
    code << objcmd;

    // Now perform marker replacements
    code.replace("@CLASS@",class_name);
    temp = "";
    temp << name_destroy(class_name);
    code.replace("@DESTRUCTOR@",temp);
    code.replace("@CLASSTYPE@",t->print_type());
    "configure " >> methodnames;
    "cget " >> methodnames;
    code.replace("@METHODLIST@", methodnames);
    code.replace("@CLASSMANGLE@",t->print_mangle());
    code.replace("@METHODS@",methods);
    code.replace("@CONFIGMETHODS@",config);
    code.replace("@CGETMETHODS@",cget);
    if (have_constructor) {
      temp = "";
      temp << name_wrapper(name_construct(class_name),prefix);
    } else {
      temp = "0";
    }
    code.replace("@TCLCONSTRUCTOR@",temp);
    code.replace("@CONFIGLIST@",config_options);
    code.replace("@CGETLIST@",options);
    if (have_destructor) {
      temp = "TclDelete";
      temp << class_name;
    } else {
      temp = "0";
    }
    code.replace("@TCLDESTRUCTOR@",temp);
    fprintf(f_wrappers,"%s\n", code.get());
    fprintf(f_init,"\t Tcl_CreateCommand(interp, SWIG_prefix \"%s\",Tcl%sCmd, (ClientData) NULL, NULL);\n", class_name, class_name);
  }
}

void TCL::cpp_member_func(char *name, char *iname, DataType *t, ParmList *l) {

  char *realname;
  String temp;
  char *rname;

  this->Language::cpp_member_func(name,iname,t,l);

  if (shadow) {
    if (iname) 
      realname = iname;
    else
      realname = name;
    
    // Add stubs for this member to our class handler function

    if (have_methods) 
      methods << tab4 << "else ";
    else 
      methods << tab4;

    // Try to figure out if there is a wrapper for this function
    
    temp = "";
    temp << name_member(realname,class_name);
    
    rname = (char *) repeatcmd.lookup(temp);

    if (!rname) 
      rname = name_wrapper(temp.get(),prefix);
    
    methods << "if (strcmp(argv[1],\"" << realname << "\") == 0) {\n"
	    << tab4 << tab4 << "cmd = " << rname << ";\n"
	    << tab4 << "}";

    have_methods = 1;
    methodnames << realname << " ";

    if (doc_entry) {
      doc_entry->usage = "";
      doc_entry->usage << usage_string(realname,t,l);
    }
  }
}

void TCL::cpp_variable(char *name, char *iname, DataType *t) {
  char *realname;
  String temp, temp1;
  char *rname;

  this->Language::cpp_variable(name, iname, t);

  if (shadow) {
    if (iname)
      realname = iname;
    else
      realname = name;
    
    // Write config code

    char *bc = class_name;

    if (!(Status & STAT_READONLY)) {
      if (!have_config) {
	config << tab8 << tab8;
      } else {
	config << " else ";
      }
      
      temp = "";
      temp << name_set(name_member(realname,bc));
      rname = (char *) repeatcmd.lookup(temp);
      if (!rname) 
	rname = name_wrapper(temp.get(),prefix);

      config << "if (strcmp(argv[i],\"-" << realname << "\") == 0) {\n"
	     << tab8 << tab8 << tab4 << "cmd = " << rname << ";\n"
	     << tab8 << tab8 << "} ";
      
      have_config = 1;
    }
    
    // Write cget code
    
    if (!have_cget) {
      cget << tab8 << tab8;
    } else {
      cget << " else ";
    }

    // Try to figure out if there is a wrapper for this function
    temp = "";
    temp << name_get(name_member(realname,bc));
    rname = (char *) repeatcmd.lookup(temp);
    if (!rname) 
      rname = name_wrapper(temp.get(),prefix);
    
    cget << "if (strcmp(argv[2],\"-" << realname << "\") == 0) {\n"
	 << tab8 << tab8 << tab4 << "cmd = " << rname << ";\n"
	 << tab8 << tab8 << "} ";
    have_cget = 1;
    
    options << "-" << realname << " ";
    if (!(Status & STAT_READONLY)) {
      config_options << "-" << realname << " ";
    }
    if (doc_entry){
      doc_entry->usage = "";
      doc_entry->usage << "-" << realname << "\n";
    }
  }
}

void TCL::cpp_constructor(char *name, char *iname, ParmList *l) {
  this->Language::cpp_constructor(name,iname,l);

  if (shadow) {
    if ((!have_constructor) && (doc_entry)) {
      doc_entry->usage = "";
      doc_entry->usage << class_name << usage_string(" name",0,l);
    }
    have_constructor = 1;
  }
}
void TCL::cpp_destructor(char *name, char *newname) {
  this->Language::cpp_destructor(name,newname);
  if (shadow) {
    if (!have_destructor) {
      if (doc_entry) {
	doc_entry->usage = "rename obj {}";
      }
    }
    have_destructor = 1;
  }
}

void TCL::cpp_inherit(char **baseclass, int) {
  this->Language::cpp_inherit(baseclass);
}

void TCL::cpp_declare_const(char *name, char *iname, DataType *type, char *value) {
  this->Language::cpp_declare_const(name,iname,type,value);
}


// --------------------------------------------------------------------------------
// TCL::add_typedef(DataType *t, char *name)
//
// This is called whenever a typedef is encountered.   When shadow classes are
// used, this function lets us discovered hidden uses of a class.  For example :
//
//     struct FooBar {
//            ...
//     }
//
// typedef FooBar *FooBarPtr;
//
// --------------------------------------------------------------------------------

void TCL::add_typedef(DataType *t, char *name) {

  if (!shadow) return;

  // First check to see if there aren't too many pointers

  if (t->is_pointer > 1) return;
  if (hash.lookup(name)) return;      // Already added

  // Now look up the datatype in our shadow class hash table

  if (hash.lookup(t->name)) {

    // Yep.   This datatype is in the hash
    // Put this types 'new' name into the hash
    hash.add(name,copy_string((char *) hash.lookup(t->name)));
  }
}

// -----------------------------------------------------------------------
// TCL::cpp_class_decl(char *name, char *rename, char *type)
//
// Treatment of an empty class definition.    Used to handle
// shadow classes across modules.
// -----------------------------------------------------------------------

void TCL::cpp_class_decl(char *name, char *rename, char *type) {
  char temp[256];
  this->Language::cpp_class_decl(name,rename, type);
  if (shadow) {
    hash.add(name,copy_string(rename));
    // Add full name of datatype to the hash table
    if (strlen(type) > 0) {
      sprintf(temp,"%s %s", type, name);
      hash.add(temp,copy_string(rename));
    }
  }
}


/*********************************************************************************
 *
 * -- Revision History
 * $Log: tcl.cxx,v $
 * Revision 1.66  1997/07/09 02:40:41  beazley
 * First cut at eliminating compiler warning messages.
 *
 * Revision 1.65  1997/06/29 19:08:06  beazley
 * Changed EXPORT to SWIGEXPORT
 *
 * Revision 1.64  1997/06/17 04:42:28  beazley
 * Fixed some bugs with %name() directive.  Cleaned up naming
 * strategy.
 *
 * Revision 1.63  1997/05/28 21:43:20  beazley
 * Moved revision history to end.
 *
 * Revision 1.62  1997/05/24 05:15:33  beazley
 * Added the "build" typemap.
 *
 * Revision 1.61  1997/05/19 16:28:01  beazley
 * Added a few more typemap variables.
 *
 * Revision 1.60  1997/05/08 05:41:56  beazley
 * Added $cleanup symbol.
 *
 * Revision 1.59  1997/05/05 15:51:38  beazley
 * Added support for parameterized typemaps.
 *
 * Revision 1.58  1997/04/19 21:25:24  beazley
 * Added support for %new directive.
 *
 * Revision 1.57  1997/03/29 17:41:15  beazley
 * Fixed minor code generation bug.
 *
 * Revision 1.56  1997/03/24 23:04:17  beazley
 * Added some modifications for Macintosh support
 *
 * Revision 1.55  1997/03/19 23:46:39  beazley
 * Changed name of "constrain" typemap to "check"
 *
 * Revision 1.54  1997/03/18 22:27:40  beazley
 * Added constrain typemap.
 *
 * Revision 1.53  1997/03/18 21:45:20  beazley
 * Minor changes to typemap handling.
 *
 * Revision 1.52  1997/03/02 22:40:57  beazley
 * Minor bug fixes.  Removed warnings.
 *
 * Revision 1.51  1997/02/19 23:03:13  beazley
 * Added create_command() function needed for C++ optimizations.
 *
 * Revision 1.50  1997/02/16 19:55:38  beazley
 * Added support for ignored arguments.
 * Modified handling of global variables of complex datatypes.
 *
 * Revision 1.49  1997/01/09 01:21:42  beazley
 * Changed inherit method slightly
 *
 * Revision 1.48  1997/01/08 05:43:06  beazley
 * Pre 1.1b3 checkin
 *
 * Revision 1.47  1997/01/06 17:12:03  beazley
 * Added support for typemaps.  Multiple inheritance.
 *
 * Revision 1.46  1996/12/26 23:03:19  beazley
 * Modified to use new pointer type-checker
 *
 * Revision 1.45  1996/12/26 04:48:00  beazley
 * Added new object-oriented interface
 *
 * Revision 1.44  1996/12/03 08:41:26  beazley
 * pre-1.1b2 checkin
 *
 * Revision 1.43  1996/11/12 20:01:57  beazley
 * Changes to support new documentation and C++ handling
 *
 * Revision 1.42  1996/10/30 22:11:36  beazley
 * Minor change to eliminate compiler warning.
 *
 * Revision 1.41  1996/10/29 19:27:11  beazley
 * Added support for bool type
 *
 * Revision 1.40  1996/08/27 23:02:06  dmb
 * Minor changes to error handling
 *
 * Revision 1.39  1996/08/26 16:31:21  dmb
 * Fixed spelling error in help message.
 *
 * Revision 1.38  1996/08/25 00:05:25  dmb
 * Added ability to change Tcl result string behavior with %pragma
 *
 * Revision 1.37  1996/08/21 16:51:23  dmb
 * Fixed bugs in constant code.
 *
 * Revision 1.36  1996/08/21 05:50:48  dmb
 * Added support for [incr Tcl] namespaces
 *
 * Revision 1.35  1996/08/16 04:17:34  dmb
 * Added support for Netscape plugin
 *
 * Revision 1.34  1996/08/12 01:51:27  dmb
 * Changes to support new language class
 *
 * Revision 1.33  1996/08/02 02:58:56  dmb
 * Changed to use better parameter list functions
 *
 * Revision 1.32  1996/07/17 14:55:36  dmb
 * Fixed bug in -strict 1 pointer type checking mode.
 *
 * Revision 1.31  1996/06/16 02:22:58  beazley
 * Fixed bug in constant creation.
 *
 * Revision 1.30  1996/06/02  00:14:48  beazley
 * Minor changes
 *
 * Revision 1.29  1996/05/28  23:17:14  beazley
 * Minor fix to initialize function
 *
 * Revision 1.28  1996/05/22  20:20:21  beazley
 * Added banner and cleanup functions to headers() and close() functions.
 * Changed name of class
 *
 * Revision 1.27  1996/05/20  23:36:17  beazley
 * Added a few more constant datatypes.
 *
 * Revision 1.26  1996/05/17  05:53:22  beazley
 * Added return by value support.
 *
 * Revision 1.25  1996/05/14  23:24:04  beazley
 * Minor changes
 *
 * Revision 1.24  1996/05/13  23:45:08  beazley
 * Reworked the module/init procedure
 *
 * Revision 1.23  1996/05/09  23:27:25  beazley
 * Minor changes
 *
 * Revision 1.22  1996/05/06  23:09:58  beazley
 * Some fixes to forward declarations for C++
 *
 * Revision 1.21  1996/05/03  22:29:09  dmb
 * Modified to look for swigtcl.swg file.   Used to include code for
 * UNIX and Windows.
 *
 * Revision 1.20  1996/05/03 05:11:30  dmb
 * Fixed some C++ linking problems.
 *
 * Revision 1.19  1996/05/01 22:42:44  dmb
 * Cleaned up command line option handling.
 *
 * Revision 1.18  1996/04/14 15:24:28  dmb
 * Changed filename to tcl.cc. Fixed some of the headers
 *
 * Revision 1.17  1996/04/09 20:19:10  beazley
 * Minor cleanup.
 *
 * Revision 1.16  1996/04/09  19:29:31  beazley
 * Minor changes to documentation.
 *
 * Revision 1.15  1996/03/28  02:46:38  beazley
 * Minor bug fix to documentation.
 *
 * Revision 1.14  1996/03/22  23:42:16  beazley
 * Added constants.  Cleaned up some stuff.
 *
 * Revision 1.13  1996/03/16  06:29:05  beazley
 * Major overhaul.  Has too many new features to mention
 * here.  Biggest change = run-time type checking.
 *
 * Revision 1.12  1996/03/04  21:29:13  beazley
 * Change usage(), made changes to pointer handling.
 *
 * Revision 1.11  1996/02/19  05:31:35  beazley
 * Changed treatment of pointers to avoid weird problems with
 * scanf("%p").
 *
 * Revision 1.10  1996/02/16  07:06:58  beazley
 * Fixed problems with sprintf()
 *
 * Revision 1.9  1996/02/16  06:38:49  beazley
 * Removed a few unused variables.
 *
 * Revision 1.8  1996/02/15  22:38:31  beazley
 * Fixed several significant bugs.  Changed copyright
 *
 * Revision 1.7  1996/02/12  08:19:34  beazley
 * A few minor changes to the include path.
 *
 * Revision 1.6  1996/02/09  04:54:31  beazley
 * Added "tcl" to wrapper names.
 *
 * Revision 1.5  1996/02/07  05:22:10  beazley
 * A complete rewrite.   Uses new emit functions and now supports
 * almost any datatype (including pointers and complex types).
 *
 * Revision 1.4  1996/01/23  19:41:25  beazley
 * Fixed a few bugs.
 *
 * Revision 1.3  1996/01/13  01:34:26  beazley
 * A few minor changes.
 *
 * Revision 1.2  1996/01/05  22:40:54  dmb
 * *** empty log message ***
 *
 * Revision 1.1  1995/12/30 04:34:14  dmb
 * Initial revision
 *
 *********************************************************************************/
