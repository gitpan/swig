
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
 * $Header: /home/beazley/SWIG/SWIG1.1/Modules/RCS/perl4.cxx,v 1.32 1997/06/22 20:51:31 beazley Exp $
 *
 * perl4.c
 *
 * Definitions for adding functions to Perl 4
 *
 * How to extend perl4 (note : this is totally different in Perl 5) :
 *
 * 1.   Variable linkage
 *
 *      Must declare two functions :
 *
 *          _var_set(int ix, STR *str) 
 *          _var_get(int ix, STR *str)
 *
 *      ix is an index number, which is ignored in this implementation.
 *      str is a pointer to supplied by perl. 
 *
 *      For numbers, the functions str_gnum(str) and str_numset(str)
 *      should be used for getting or setting values.   By default
 *      these deal with double precision values as indicated in
 *      "Programming Perl.".
 *
 *      For strings, the functions str_get(str) and str_set(str)
 *      should be used.   
 *
 *      Variables are added to Perl4 by the following call :
 *
 *           struct ufuncs uf;
 *           uf.uf_index = 0;    // Index.  ignored here
 *           uf.uf_set = _var_set;
 *           uf.uf_get = _var_get;
 *           magicname("varname", &uf, sizeof(uf));
 *
 * 2.   Function extension
 *
 *      Functions must take the following arguments :
 *          int _wrap_func(int ix, register sp, register int items)
 * 
 *          ix = index value (ignored here)
 *          sp = Perl stack pointer
 *          items = number of arguments
 *
 *      A global variable called "stack" is used to pull of
 *      function arguments :
 *
 *          STR **st = stack->ary_array + sp;
 *     
 *      Values can be extracted using the normal str_get, str_gnum, etc..
 *      commands.     A return value, if any, should be place in st[0]
 *      Each function should return the value of the stack pointer sp.
 *
 * 3.   Compilation.
 *
 *      The wrapper file should be linked with the uperl.o object file
 *      in the perl distribution.
 ***********************************************************************/

#include "swig.h"
#include "perl4.h"
static char *usage = "\
Perl4 Options (available with -perl4)\n\
     -module name    - Set name of module\n\
     -prefix name    - Set a prefix to be appended to all names\n\n";


static String mod_init;
static String mod_extern;

// ---------------------------------------------------------------------
// PERL4::parse_args(int argc, char *argv[])
//
// Parse command line options
// ---------------------------------------------------------------------

void PERL4::parse_args(int argc, char *argv[]) {

  int i = 1;

  sprintf(LibDir,"%s",perl_path);
  sprintf(InitName,"wrap_init");

  for (i = 1; i < argc; i++) {
      if (argv[i]) {
	  if (strcmp(argv[i],"-prefix") == 0) {
	    if (argv[i+1]) {
	      prefix = new char[strlen(argv[i+1])+2];
	      strcpy(prefix, argv[i+1]);
	      mark_arg(i);
	      mark_arg(i+1);
	      i+=1;
	    } else {
	      arg_error();
	    }
	  } else if (strcmp(argv[i],"-module") == 0) {
	    if (argv[i+1]) {
	      module = new char[strlen(argv[i+1])+2];
	      strcpy(module,argv[i+1]);
	      mark_arg(i);
	      mark_arg(i+1);
	      i+=1;
	    } else {
	      arg_error();
	    }
	  } else if (strcmp(argv[i],"-help") == 0) {
	    fputs(usage,stderr);
	    SWIG_exit(0);
	  }
      }
  }

  // If a prefix has been specified, make sure it ends with a '_'

  if (prefix) {
    if (prefix[strlen(prefix)] != '_') {
      prefix[strlen(prefix)+1] = 0;
      prefix[strlen(prefix)] = '_';
    }
  } else 
    prefix = "";

  // Add a symbol for this module

  add_symbol("SWIGPERL",0,0);
  add_symbol("SWIGPERL4",0,0);

  // Set name of typemaps

  typemap_lang = "perl4";


}

// ---------------------------------------------------------------------
// void PERL4::parse()
//
// Start parsing an interface file for Perl4
// ---------------------------------------------------------------------

void PERL4::parse() {

  fprintf(stderr,"Making wrappers for Perl4\n");
  
  // Print out Perl4 specific headers
  
  headers();
  
  // Run the parser
  
  yyparse();

}

// ---------------------------------------------------------------------
// PERL4::set_module(char *mod_name, char **mod_list)
//
// Sets the module name.
// Does nothing if it's already set (so it can be overridden as a command
// line option).
//
//----------------------------------------------------------------------

void PERL4::set_module(char *mod_name, char **mod_list) {

  if (module) return;
  
  module = new char[strlen(mod_name)+1];
  strcpy(module,mod_name);

  // If there were additional modules, dump out initialization code

  if (mod_list) {
    int i = 0;
    while (mod_list[i]) {
      mod_init << tab4 << mod_list[i] << "();\n";
      mod_extern << "extern int " << mod_list[i] << "();\n";
      i++;
    }
  }
}

// ---------------------------------------------------------------------
// PERL4::set_init(char *iname)
//
// Sets the initialization function name.
// Does nothing if it's already set
//
//----------------------------------------------------------------------

void PERL4::set_init(char *iname) {
  set_module(iname,0);
}

// ---------------------------------------------------------------------
// PERL4::headers(void)
//
// Generate the appropriate header files for PERL4 interface.
// ----------------------------------------------------------------------

void PERL4::headers(void)
{

  emit_banner(f_header);
  fprintf(f_header,"/* Implementation : PERL 4 */\n\n");
  fprintf(f_header,"#define SWIGPERL\n");
  fprintf(f_header,"#define SWIGPERL4\n");
  fprintf(f_header,"#include \"EXTERN.h\"\n");
  fprintf(f_header,"#include \"perl.h\"\n");
  fprintf(f_header,"#include <string.h>\n");
  fprintf(f_header,"#include <stdlib.h>\n");

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
// PERL4::initialize(void)
//
// Output initialization code that registers functions with the
// interface.
// ---------------------------------------------------------------------


void PERL4::initialize()
{

  if (!module) {
    module = "swig_init";
    fprintf(stderr,"SWIG : *** Warning. No module name specified.\n");
  }

  fprintf(f_header,"#define SWIG_init    %s\n\n", module);
  fprintf(f_init,"int %s() {\n", module);
  fprintf(f_init,"\t struct ufuncs uf;\n");
  fprintf(f_init,"\t uf.uf_index = 0;\n");
  fprintf(f_init,"%s\n", mod_init.get());
  fprintf(f_header,"%s\n",mod_extern.get());
}

// ---------------------------------------------------------------------
// PERL4::close(void)
//
// Wrap things up.  Close initialization function.
// ---------------------------------------------------------------------

void PERL4::close(void)
{

  // Dump the pointer equivalency table */

  emit_ptr_equivalence(f_init);
  
  // Outta here..

  fprintf(f_init,"\t return 0;\n");
  fprintf(f_init,"}\n");
  
}

// ----------------------------------------------------------------------
// PERL4::get_pointer(int parm, DataType *t)
//
// Emits code to get a pointer from a parameter and do type checking.
// parm is the parameter number.   This function is only used
// in create_function().
// ----------------------------------------------------------------------

void PERL4::get_pointer(char *iname, int parm, DataType *t) {

  // Pointers are read as hex-strings with encoded type information

  fprintf(f_wrappers,"\t if (SWIG_GetPtr(str_get(_st[%d]), (void **) &_arg%d,",parm+1,parm);
  if (t->type == T_VOID) fprintf(f_wrappers,"(char *) 0)) {\n");
  else 
    fprintf(f_wrappers,"\"%s\")) {\n", t->print_mangle());

  // Now emit code according to the level of strictness desired

  switch(TypeStrict) {
  case 0: // No type checking
    fprintf(f_wrappers,"\t}\n");
    break;
  case 1: // Warning message only
    fprintf(f_wrappers,
      "\t fprintf(stderr,\"Warning : type mismatch in argument %d of %s. Expected %s, received %%s\\n\", str_get(_st[%d]));\n", parm+1,iname, t->print_mangle(), parm+1);
    fprintf(f_wrappers,"\t }\n");
    break;
  case 2: // Super strict mode.

    fprintf(f_wrappers,"\t\t fatal(\"Type error in argument %d of %s. Expected %s.\");\n", parm+1,iname,t->print_mangle());
    fprintf(f_wrappers,"\t\t return _sp;\n");
    fprintf(f_wrappers,"\t}\n");
    break;

  default :
    fprintf(stderr,"Unknown strictness level\n");
    break;
  }
}

// ----------------------------------------------------------------------
// PERL4::create_command(char *cname, char *iname)
//
// Creates a new command mapped onto an already existing wrapper.
// ----------------------------------------------------------------------

void PERL4::create_command(char *cname, char *iname) {
  
  // Now register the function

  fprintf(f_init,"\t make_usub(\"%s%s\", 0, %s, \"%s\");\n", prefix, iname, name_wrapper(cname,""), input_file);

}

// ----------------------------------------------------------------------
// PERL4::create_function(char *name, char *iname, DataType *d, ParmList *l)
//
// Create a function declaration and register it with the interpreter.
// ----------------------------------------------------------------------

void PERL4::create_function(char *name, char *iname, DataType *d, ParmList *l)
{
  Parm *p;
  int   pcount,i,j;
  char  *wname;
  char  source[64];
  char  target[64];
  char  *usage = 0, *tm;
  String cleanup;
  int    numopt = 0;

  // Make a wrapper name for this

  wname = name_wrapper(iname,"");
  
  // Now write the wrapper function itself....this is pretty ugly

  fprintf(f_wrappers,"int %s(int _ix, register int _sp, register int _nitems) {\n", wname);

  // Print out arguments
  fprintf(f_wrappers,"\t STR **_st = stack->ary_array + _sp;\n");
  if ((d->is_pointer) || (d->type == T_CHAR)) {
    fprintf(f_wrappers,"\t char   _ptemp[256];\n");
  }

  // Print out variable declarations for storing for parameters

  pcount = emit_args(d, l, f_wrappers);
  numopt = l->numopt();

  // Check the number of arguments

  usage_func(iname,d,l,&usage);
  fprintf(f_wrappers,"\n\t if ((_nitems < %d) || (_nitems > %d))\n",(pcount-numopt),l->numarg());
  fprintf(f_wrappers,"\t\t fatal(\"wrong # args  %s\");\n",usage);


  // Write code to extract parameters.
  // This section should be able to extract virtually any kind 
  // parameter, represented as a string

  i = 0;
  j = 0;
  p = l->get_first();
  while (p != 0) {
    // Create source and target names for typemaps
    sprintf(source,"_st[%d]",j+1);
    sprintf(target,"_arg%d",i);

    if (!p->ignore) {

      if (j >= (pcount-numopt))
	fprintf(f_wrappers,"\t if (_nitems > %d) {\n", i);

      if ((tm = typemap_lookup("in","perl4",p->t,p->name,source,target))) {
	// Yep.  Use it instead of the default
	fprintf(f_wrappers,"%s\n",tm);
      } else {

	if (!p->t->is_pointer) {
	  
	  // Extract a parameter by "value"
	  
	  switch(p->t->type) {
	    
	    // All Numbers.  As far as I can tell all nums in Perl4 are doubles.
	    // See pg.65 of "Programming Perl", by Wall and Schwartz.
	    
	  case T_INT :
	  case T_SINT:
	  case T_SHORT:
	  case T_SSHORT:
	  case T_LONG:
	  case T_SLONG:
	  case T_SCHAR:
	  case T_UINT:
	  case T_USHORT:
	  case T_ULONG:
	  case T_UCHAR:
	  case T_FLOAT:
	  case T_DOUBLE:
	    fprintf(f_wrappers,"\t _arg%d = %s str_gnum(_st[%d]);\n",
		    i, p->t->print_cast(),j+1);
	    break;
	    
	    // A single character 
	    
	  case T_CHAR :
	    fprintf(f_wrappers,"\t _arg%d =  *(str_get(_st[%d]));\n",i,j+1);
	    break;
	    
	    // Void.. Do nothing.
	    
	  case T_VOID :
	    break;
	    
	    // User-defined.   Is an error.
	    
	  case T_USER:
	    
	    // Unsupported data type
	    
	  default :
	    fprintf(stderr,"%s : Line %d: Unable to use type %s as a function argument.\n",
		    input_file, line_number, p->t->print_type());
	    break;
	  }
	} else {
	  
	  // Argument is a pointer type.   Special case is for char *
	  // since that is usually a string.
	  
	  if ((p->t->type == T_CHAR) && (p->t->is_pointer == 1)) {
	    fprintf(f_wrappers,"\t _arg%d = str_get(_st[%d]);\n",i,j+1);
	  } else {
	    
	    // Have a generic pointer type here.    Read it in as
	    // a string 0x--------
	    
	    get_pointer(iname,i,p->t);
	    
	  }
	}
      }
      if (i >= (pcount-numopt))
	fprintf(f_wrappers,"\t }\n");
      j++;
    } 
    // Check for a constraint typemap
    if ((tm = typemap_lookup("check","perl4",p->t,p->name,source,target))) {
      // Yep.  Use it instead of the default
      fprintf(f_wrappers,"%s\n",tm);
    }
    // Check for cleanup code
    if ((tm = typemap_lookup("freearg","perl4",p->t,p->name,target,"_st[0]"))) {
      // Yep.  Use it instead of the default
      cleanup << tm << "\n";
    }
    p = l->get_next();
    i++;
  }

  // Now write code to make the function call

  emit_func_call(name,d,l,f_wrappers);

  if ((d->type != T_VOID) || (d->is_pointer)) {
    if ((tm = typemap_lookup("out","perl4",d,name,"_result","_st[0]"))) {
      // Yep.  Use it instead of the default
      fprintf(f_wrappers,"%s\n",tm);
    } else {
      
      // Now have return value, figure out what to do with it.
      
      if (!d->is_pointer) {
	
	// Function returns a "value"
	
	switch(d->type) {
	case T_INT: case T_SINT: case T_UINT:
	case T_SHORT: case T_SSHORT: case T_USHORT:
	case T_LONG : case T_SLONG: case T_ULONG:
	case T_SCHAR: case T_UCHAR:
	case T_DOUBLE :
	case T_FLOAT :
	  fprintf(f_wrappers,"\t str_numset(_st[0], (double) _result);\n");
	  break;
	case T_CHAR :
	  fprintf(f_wrappers,"\t sprintf(_ptemp,\"%%c\",_result);\n");
	  fprintf(f_wrappers,"\t str_set(_st[0], _ptemp);\n");
	  break;
	  
	  // Return a complex type by value
	  
	case T_USER :
	  d->is_pointer++;
	  // Is an ordinary pointer type.
	  fprintf(f_wrappers,"\t  SWIG_MakePtr(_ptemp,_result,\"%s\");\n",
		  d->print_mangle());
	  fprintf(f_wrappers,"\t str_set(_st[0],_ptemp);\n");
	  d->is_pointer--;
	  break;
	default :
	  fprintf(stderr,"Line %d: Unable to use return type %s in function %s.\n",
		  line_number,d->print_type(), name);
	  fprintf(f_wrappers,"ERROR : Unable to use return type %s",d->print_type());
	  break;
	}
      } else {
	
	// Is a pointer return type

	if ((d->type == T_CHAR) && (d->is_pointer == 1)) {
	  fprintf(f_wrappers,"\t str_set(_st[0],_result);\n");
	} else {
	  // Is an ordinary pointer type.
	  fprintf(f_wrappers,"\t  SWIG_MakePtr(_ptemp,_result,\"%s\");\n",
		  d->print_mangle());
	  fprintf(f_wrappers,"\t str_set(_st[0],_ptemp);\n");
	}
      }
    }
  }

  // Dump the argument cleanup code
  fprintf(f_wrappers,"%s\n",cleanup.get());

  // Look for any remaining cleanup

  if (NewObject) {
    if ((tm = typemap_lookup("newfree","perl4",d,iname,"_result",""))) {
      fprintf(f_wrappers,"%s\n",tm);
    }
  }

  if ((tm = typemap_lookup("ret","perl4",d,name,"_result",""))) {
    // Yep.  Use it instead of the default
    fprintf(f_wrappers,"%s\n",tm);
  }

  // Wrap things up (in a manner of speaking)

  fprintf(f_wrappers,"\t return _sp;\n}\n");

  // Now register the function

  fprintf(f_init,"\t make_usub(\"%s%s\", 0, %s, \"%s\");\n", prefix, iname, wname, input_file);

  // Make a documentation entry for this

  if (doc_entry) {
    static DocEntry *last_doc_entry = 0;
    doc_entry->usage << usage;
    if (last_doc_entry != doc_entry) {
      doc_entry->cinfo << "returns " << d->print_type();
      last_doc_entry = doc_entry;
    }
  }

  delete usage;
}

// -----------------------------------------------------------------------
// PERL4::link_variable(char *name, char *iname, DataType *d)
//
// Create a link to a C variable.
// -----------------------------------------------------------------------

void PERL4::link_variable(char *name, char *iname, DataType *t)
{
  char  set_name[256];
  char  val_name[256];
  char  *tm;

  // Create set and evaluation function names
  
  sprintf(set_name,"_wrap_perl4_set_%s",iname);
  sprintf(val_name,"_wrap_perl4_val_%s",iname);
  
  // Create a Perl function for setting the variable value

  fprintf(f_wrappers,"%s(int ix, STR *str) {\n",set_name);
  if (Status & STAT_READONLY) {
    fprintf(f_wrappers,"\t fatal(\"Unable to set %s. Variable is read-only.\");\n",iname);
  } else {
    if ((tm = typemap_lookup("varin","perl4",t,name,"str",name))) {
      // Yep.  Use it instead of the default
      fprintf(f_wrappers,"%s\n",tm);
    } else {
      if (!t->is_pointer) {
	if (t->type != T_USER)
	  fprintf(f_wrappers,"\t %s = ", name);
	switch(t->type) {
	case T_INT : case T_SINT: case T_UINT:
	case T_SHORT : case T_SSHORT : case T_USHORT:
	case T_LONG : case T_SLONG: case T_ULONG:
	case T_SCHAR: case T_UCHAR:
	case T_DOUBLE : 
	case T_FLOAT :
	  fprintf(f_wrappers,"%s str_gnum(str);\n", t->print_cast());
	  break;
	case T_CHAR :
	  fprintf(f_wrappers,"*(str_get(str));\n");
	  break;
	case T_USER:
	  // Set a user-defined type here
	  t->is_pointer++;
	  fprintf(f_wrappers,"\t void *temp;\n");
	  
	  // Get pointer value
	  
	  fprintf(f_wrappers,"\t if (SWIG_GetPtr(str_get(str), (void **) &temp,");
	  if (t->type == T_VOID) fprintf(f_wrappers,"(char *) 0)) {\n");
	  else 
	    fprintf(f_wrappers,"\"%s\")) {\n", t->print_mangle());
	  
	  // Now emit code according to the level of strictness desired
	  
	  switch(TypeStrict) {
	  case 0: // No type checking
	    fprintf(f_wrappers,"\t}\n");
	    break;
	  case 1: // Warning message only
	    fprintf(f_wrappers,
		    "\t fprintf(stderr,\"Warning : type mismatch in variable %s. Expected %s, received %%s\\n\", str_get(str));\n", name, t->print_mangle());
	    fprintf(f_wrappers,"\t }\n");
	    break;
	  case 2: // Super strict mode.
	    
	    fprintf(f_wrappers,"\t\t fatal(\"Type error in variable %s. Expected %s.\");\n", name,t->print_mangle());
	    fprintf(f_wrappers,"\t}\n");
	    break;
	    
	  default :
	    fprintf(stderr,"Unknown strictness level\n");
	    break;
	  }
	  fprintf(f_wrappers,"\t %s = *(%s temp);\n", name, t->print_cast());
	  t->is_pointer--;
	  break;
	default :
	  break;
	}
      } else {
	// Have some sort of pointer type here, Process it differently
	if ((t->type == T_CHAR) && (t->is_pointer == 1)) {
	  fprintf(f_wrappers,"\t %s = savestr(str_get(str));\n",name);
	} else {
	  fprintf(f_wrappers,"\t void *temp;\n");
	  
	  // Set the value of a pointer
	  
	  fprintf(f_wrappers,"\t if (SWIG_GetPtr(str_get(str), (void **) &temp,");
	  if (t->type == T_VOID) fprintf(f_wrappers,"(char *) 0)) {\n");
	  else 
	    fprintf(f_wrappers,"\"%s\")) {\n", t->print_mangle());
	  
	  // Now emit code according to the level of strictness desired
	  
	  switch(TypeStrict) {
	  case 0: // No type checking
	    fprintf(f_wrappers,"\t}\n");
	    break;
	  case 1: // Warning message only
	    fprintf(f_wrappers,
		    "\t fprintf(stderr,\"Warning : type mismatch in variable %s. Expected %s, received %%s\\n\", str_get(str));\n", name, t->print_mangle());
	    fprintf(f_wrappers,"\t }\n");
	    break;
	  case 2: // Super strict mode.
	    
	    fprintf(f_wrappers,"\t\t fatal(\"Type error in variable %s. Expected %s.\");\n", name,t->print_mangle());
	    fprintf(f_wrappers,"\t}\n");
	    break;
	    
	  default :
	    fprintf(stderr,"Unknown strictness level\n");
	    break;
	  }
	  
	  fprintf(f_wrappers,"\t %s = %s temp;\n", name, t->print_cast());
	}
      }
    }
  }
 
  fprintf(f_wrappers,"}\n");

  // Now write a function to evaluate the variable
  
  fprintf(f_wrappers,"%s(int ix, STR *str) {\n",val_name);
  if ((tm = typemap_lookup("varout","perl4",t,name,name,"str"))) {
    // Yep.  Use it instead of the default
    fprintf(f_wrappers,"%s\n",tm);
  } else {
    if (!t->is_pointer) {
      switch(t->type) {
      case T_INT : case T_SINT: case T_UINT:
      case T_SHORT : case T_SSHORT: case T_USHORT:
      case T_LONG : case T_SLONG: case T_ULONG:
      case T_SCHAR: case T_UCHAR:
      case T_DOUBLE :
      case T_FLOAT :
	fprintf(f_wrappers,"\t str_numset(str, (double) %s);\n", name);
	break;
      case T_CHAR :
	fprintf(f_wrappers,"\t char _ptemp[8];\n");
	fprintf(f_wrappers,"\t sprintf(_ptemp,\"%%c\",%s);\n",name);
	fprintf(f_wrappers,"\t str_set(str, _ptemp);\n");
	break;
      default :
	break;
      }
    } else {
      
      // Have some sort of arbitrary pointer type.  Return it as a string
      
      if ((t->type == T_CHAR) && (t->is_pointer == 1))
	fprintf(f_wrappers,"\t str_set(str,%s);\n", name);
      else {
	fprintf(f_wrappers,"\t char _ptemp[128];\n");
	// Is an ordinary pointer type.
	fprintf(f_wrappers,"\t  SWIG_MakePtr(_ptemp, (void *) %s,\"%s\");\n", name,
		t->print_mangle());
	fprintf(f_wrappers,"\t str_set(str,_ptemp);\n");
      }
    }
    fprintf(f_wrappers,"}\n");
    
    // Now add symbol to the PERL interpreter
    
    fprintf(f_init,"\t uf.uf_set = %s;\n", set_name);
    fprintf(f_init,"\t uf.uf_val = %s;\n", val_name);
    fprintf(f_init,"\t magicname(\"%s\", &uf, sizeof(uf));\n", iname);
    
    // Add a documentation entry
    
    if (doc_entry) {
      char *usage = 0; 
      usage_var(iname,t,&usage);
      doc_entry->usage << usage;
      doc_entry->cinfo << "Global : " << t->print_type() << " " << name;
      delete usage;
    }
  }
}

// -----------------------------------------------------------------------
// PERL4::declare_const(char *name, char *iname, DataType *type, char *value)
//
// Makes a constant.   Not sure how this is really supposed to work.
// I'm going to fake out SWIG and create a variable instead.
// ------------------------------------------------------------------------

void PERL4::declare_const(char *name, char *, DataType *type, char *value) {

  int OldStatus = Status;      // Save old status flags
  char   var_name[256];

  Status = STAT_READONLY;      // Enable readonly mode.

  if (typemap_lookup("const","perl4",type,name,"","")) {
    fprintf(stderr,"%s : Line %d. Warning. const typemap ignored.\n", input_file, line_number);
  }

  // Make a static variable;

  sprintf(var_name,"_wrap_const_%s",name);

  // Create variable and assign it a value
  
  fprintf(f_header,"static %s %s = ", type->print_type(), var_name);
  if ((type->type == T_CHAR) && (type->is_pointer <= 1)) {
    fprintf(f_header,"\"%s\";\n", value);
  } else {
    fprintf(f_header,"%s;\n", value);
  }

  // Now create a variable declaration

  link_variable(var_name, name, type);
  Status = OldStatus;

  if (doc_entry) {
    char *usage = 0;
    usage_const(name,type,value,&usage);
    doc_entry->usage = "";
    doc_entry->usage << usage;
    doc_entry->cinfo = "";
    doc_entry->cinfo << "Constant: " << type->print_type();
    delete usage;
  }
}

// ----------------------------------------------------------------------
// PERL4::usage_var(char *iname, DataType *t, char **s)
//
// Produces a usage string for a Perl 4 variable.
// ----------------------------------------------------------------------

void PERL4::usage_var(char *iname, DataType *, char **s) {

  char temp[1024];

  sprintf(temp,"$%s%s", prefix, iname);
  if (*s == 0) 
    *s = new char[strlen(temp)+1];
  strcpy(*s,temp);

}

// ---------------------------------------------------------------------------
// PERL4::usage_func(char *iname, DataType *t, ParmList *l, char **s)
// 
// Produces a usage string for a function in Perl
// ---------------------------------------------------------------------------

void PERL4::usage_func(char *iname, DataType *, ParmList *l,
                       char **s) {

  char temp[1024];
  Parm  *p;
  int   i;

  sprintf(temp,"&%s%s(", prefix, iname);

  /* Now go through and print parameters */

  p = l->get_first();
  i = 0;
  while (p != 0) {
    if (!p->ignore) {
      /* If parameter has been named, use that.   Otherwise, just print a type  */

      if ((p->t->type != T_VOID) || (p->t->is_pointer)) {
	if (strlen(p->name) > 0) {
	  strcat(temp,p->name);
	} else {
	  strcat(temp,p->t->print_type());
	}
      }
      p = l->get_next();
      if (p != 0) 
	if (!p->ignore)
	  strcat(temp,",");
      i++;
    } else {
      p = l->get_next();
      if (p != 0)
	if ((!p->ignore) && (i)) strcat(temp,",");
    }
  }
  strcat(temp,");");

  if (*s == 0) 
    *s = new char[strlen(temp)+1];
  strcpy(*s,temp);

}

// ----------------------------------------------------------------------
// PERL4::usage_const(char *iname, DataType * type, char *value, char **s)
//
// Produces a usage string for a Perl 4 constant
// ----------------------------------------------------------------------

void PERL4::usage_const(char *iname, DataType *, char *value, char **s) {

  char temp[1024];

  sprintf(temp,"$%s%s = %s", prefix, iname, value);

  if (*s == 0) 
    *s = new char[strlen(temp)+1];
  strcpy(*s,temp);

}

/*********************************************************************************
 *
 * -- Revision History
 * $Log: perl4.cxx,v $
 * Revision 1.32  1997/06/22 20:51:31  beazley
 * Changed to use new naming module.
 *
 * Revision 1.31  1997/06/17 04:43:52  beazley
 * Minor changes.
 *
 * Revision 1.30  1997/05/28 21:37:59  beazley
 * Moved revision history to end.
 *
 * Revision 1.29  1997/05/05 15:46:50  beazley
 * Fixed minor bug related to "ignore" typemap.
 *
 * Revision 1.28  1997/04/19 21:25:12  beazley
 * Added support for %new directive
 *
 * Revision 1.27  1997/03/21 00:10:37  beazley
 * Changed exit() to SWIG_exit()
 *
 * Revision 1.26  1997/03/19 23:48:26  beazley
 * Changed constrain typemap to check.
 *
 * Revision 1.25  1997/03/18 22:27:50  beazley
 * Added constrain typemap.
 *
 * Revision 1.24  1997/02/19 23:04:12  beazley
 * Added create_command function for C++ optimization.
 *
 * Revision 1.23  1997/01/08 05:43:06  beazley
 * Pre 1.1b3 checkin
 *
 * Revision 1.22  1997/01/06 17:12:03  beazley
 * Added support for typemaps.  Multiple inheritance.
 *
 * Revision 1.21  1996/12/26 23:03:19  beazley
 * Modified to use new pointer type-checker
 *
 * Revision 1.20  1996/12/26 04:48:00  beazley
 * Fixed to work with new documentation system.
 * Added support complex datatypes by value.
 *
 * Revision 1.19  1996/08/12 01:49:21  dmb
 * Changes to support new language class.
 *
 * Revision 1.18  1996/08/02 02:58:18  dmb
 * Changed to use better parameter list functions
 *
 * Revision 1.17  1996/07/17 14:56:52  dmb
 * Fixed bug in -strict 1 type checking mode.
 *
 * Revision 1.16  1996/05/22 20:20:21  beazley
 * Add banner and cleanup functions to headers() and close() functions
 *
 * Revision 1.15  1996/05/20  23:35:46  beazley
 * Added a few more constant datatypes.
 *
 * Revision 1.14  1996/05/13  23:45:19  beazley
 * Reworked the module/init procedure
 *
 * Revision 1.13  1996/05/01  22:41:43  dmb
 * Cleaned up command line option handling.
 *
 * Revision 1.12  1996/03/28 02:46:46  beazley
 * Minor bug fix to documentation.
 *
 * Revision 1.11  1996/03/22  23:41:18  beazley
 * Fixed to work with new class structure. Added constant support.
 *
 * Revision 1.10  1996/03/04  21:28:34  beazley
 * Changed usage() functions and made minor modifications to pointer handling.
 *
 * Revision 1.9  1996/02/19  05:31:13  beazley
 * Changed treatment of hexadecimal pointers.
 *
 * Revision 1.8  1996/02/16  07:14:38  beazley
 * Fixed problems with sprintf().
 *
 * Revision 1.7  1996/02/16  06:38:49  beazley
 * Removed a few unused variables.
 *
 * Revision 1.6  1996/02/15  22:36:01  beazley
 * Minor bug fixes.  Changed copyight.
 * ,
 *
 * Revision 1.5  1996/02/12  08:19:45  beazley
 * Minor changes to the include path
 *
 * Revision 1.4  1996/02/09  04:54:16  beazley
 * Added "perl4" to wrapper names.
 *
 * Revision 1.3  1996/02/07  05:22:42  beazley
 * A complete rewrite.  Now uses emit() functions and supports
 * almost all datatypes.
 *
 * Revision 1.2  1996/01/23  19:41:25  beazley
 * Fixed a few bugs.
 *
 * Revision 1.1  1996/01/13  01:34:04  beazley
 * Initial revision
 *
 ***********************************************************************/
