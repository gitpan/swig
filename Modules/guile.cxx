
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
 * $Header: /home/beazley/SWIG/SWIG1.2/Modules/RCS/guile.cxx,v 1.13 1997/07/08 05:15:10 beazley Exp $
 *
 * guile.cxx
 *
 * Definitions for adding functions to Guile 3.0
 ***********************************************************************/

#include "swig.h"
#include "guile.h"

static char *guile_usage = "\
Guile Options (available with -guile)\n\
     None available. \n\n";     

// ---------------------------------------------------------------------
// GUILE::parse_args(int argc, char *argv[])
//
// Parse arguments.
// ---------------------------------------------------------------------

void GUILE::parse_args(int argc, char *argv[]) {

  int i;
  
  sprintf(LibDir,"%s",guile_path);

  // Look for certain command line options

  // Look for additional command line options.
  for (i = 1; i < argc; i++) {  
      if (argv[i]) {
          if (strcmp(argv[i],"-help") == 0) {
            fputs(guile_usage,stderr);
            SWIG_exit(0);
          }
      }
  }
  // Add a symbol for this module

  add_symbol("SWIGGUILE",0,0);

  // Set name of typemaps

  typemap_lang = "guile";

}

// --------------------------------------------------------------------
// GUILE::parse()
//
// Parse the input file
// --------------------------------------------------------------------

void GUILE::parse()
{

  printf("Generating wrappers for Guile\n");

  // Print out GUILE specific headers
  
  headers();
  
  // Run the parser
  
  yyparse();

}

// ---------------------------------------------------------------------
// GUILE::set_module(char *mod_name)
//
// Sets the module name.
// Does nothing if it's already set (so it can be overridden as a command
// line option).
//
//----------------------------------------------------------------------

void GUILE::set_module(char *mod_name, char **) {

  if (module) return;
  
  module = new char[strlen(mod_name)+1];
  strcpy(module,mod_name);

}

// ---------------------------------------------------------------------
// GUILE::set_init(char *iname)
//
// Sets the initialization function name.
// Does nothing if it's already set
//
//----------------------------------------------------------------------

void GUILE::set_init(char *iname) {
  set_module(iname,0);
}

// ---------------------------------------------------------------------
// GUILE::headers(void)
//
// Generate the appropriate header files for GUILE interface.
// ----------------------------------------------------------------------

void GUILE::headers(void)
{

  emit_banner(f_header);

  fprintf(f_header,"/* Implementation : GUILE */\n\n");
  fprintf(f_header,"#define SWIGGUILE\n");
  fprintf(f_header,"#include <stdio.h>\n");
  fprintf(f_header,"#include <string.h>\n");
  fprintf(f_header,"#include <stdlib.h>\n");

  // Write out hex conversion functions

  if (!NoInclude) {
      if (insert_file("guile.swg", f_header) == -1) {
          fprintf(stderr,"SWIG : Fatal error.  Unable to locate 'guile.swg' in SWIG library.\n");
          SWIG_exit(1);
      }
      emit_hex(f_header);
  } else {
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
// GUILE::initialize()
//
// Output initialization code that registers functions with the
// interface.
// ---------------------------------------------------------------------
void GUILE::initialize()
{

  int i;
        
  if (!module) {
    module = "swig_init";
    fprintf(stderr,"SWIG : *** Warning. No module name specified.\n");
  }
  
  fprintf(f_header,"#define SWIG_init    %s\n\n", module);
  fprintf(f_init,"void %s() {\n", module);

  if (InitNames) {
    i = 0;
    while (InitNames[i]) {
      fprintf(f_init,"\t %s();\n",InitNames[i]);
      i++;
    }
  }
}

// ---------------------------------------------------------------------
// GUILE::close(void)
//
// Wrap things up.  Close initialization function.
// ---------------------------------------------------------------------

void GUILE::close(void)
{

  emit_ptr_equivalence(f_init);
  fprintf(f_init,"}\n");

}

// ----------------------------------------------------------------------
// GUILE::get_pointer(int parm, DataType *t)
//
// Emits code to get a pointer from a parameter and do type checking.
// parm is the parameter number.   This function is only used
// in create_function().
// ----------------------------------------------------------------------

void GUILE::get_pointer(char *iname, int parm, DataType *t) {

  // Pointers are read as hex-strings with encoded type information
  fprintf(f_wrappers,"\t _tempc = gh_scm2newstr(s_%d, &_len);\n",parm);
  fprintf(f_wrappers,"\t if (SWIG_GetPtr(_tempc, (void **) &_arg%d,",parm);
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
      "\t fprintf(stderr,\"Warning : type mismatch in argument %d of %s. Expected %s, received %%s\\n\", _tempc);\n", parm+1,iname, t->print_mangle());
    fprintf(f_wrappers,"\t }\n");
    break;
  case 2: // Super strict mode.

//    fprintf(f_wrappers,"\t\t gscm_error(\"Type error in argument %d of %s. Expected %s.\", s_%d);\n", parm+1,iname,t->print_mangle(),parm);
    fprintf(f_wrappers,"\t}\n");
    break;

  default :
    fprintf(stderr,"Unknown strictness level\n");
    break;
  }
}

// ----------------------------------------------------------------------
// GUILE::create_function(char *name, char *iname, DataType *d,
//                             ParmList *l)
//
// Create a function declaration and register it with the interpreter.
// ----------------------------------------------------------------------

void GUILE::create_function(char *name, char *iname, DataType *d, ParmList *l)
{

  Parm *p;
  int   pcount;
  char  wname[256];
  char  source[64];
  char  target[64];
  char  *tm;
  String cleanup;

  // Make a wrapper name for this

  strcpy(wname,iname);
  make_wrap_name(wname);

  // Now write the wrapper function itself....this is pretty ugly

  fprintf(f_wrappers,"SCM _wrap_gscm_%s(",wname);

  int i = 0;
  p = l->get_first();
  while (p != 0) {
    if ((p->t->type != T_VOID) || (p->t->is_pointer)) {
      fprintf(f_wrappers,"SCM s_%d", i);
    }
    p = l->get_next();
    if (p != 0) fprintf(f_wrappers,",");
    i++;
  }

  fprintf(f_wrappers,") {\n");

  // Declare return variable and arguments

  pcount = emit_args(d,l,f_wrappers);
  
  // Now declare a few helper variables here
  if (d->is_pointer) {
    fprintf(f_wrappers,"\t char   _ptemp[128];\n");
  }

  fprintf(f_wrappers,"\t int _len;\n");
  fprintf(f_wrappers,"\t char *_tempc;\n");
  fprintf(f_wrappers,"\t SCM  scmresult;\n");

  // Now write code to extract the parameters(this is super ugly)

  i = 0;
  p = l->get_first();
  while (p != 0) {
    // Produce names of source and target
    sprintf(source,"s_%d",i);
    sprintf(target,"_arg%d",i);

    if ((tm = typemap_lookup("in","guile",p->t,p->name,source,target))) {
      // Yep.  Use it instead of the default
      fprintf(f_wrappers,"%s\n", tm);
    } else {
      if (!p->t->is_pointer) {
        switch(p->t->type) {

          // Signed Integers
          
        case T_INT :
        case T_SINT :
        case T_SHORT:
        case T_SSHORT:
        case T_LONG:
        case T_SLONG:
        case T_SCHAR:
          fprintf(f_wrappers,"\t _arg%d = %s gh_scm2long(s_%d);\n",i, p->t->print_cast(), i);
          break;
          
          // Unsigned Integers
          
        case T_UINT:
        case T_USHORT:
        case T_ULONG:
        case T_UCHAR:
          fprintf(f_wrappers,"\t _arg%d = %s gh_scm2ulong(s_%d);\n", i, p->t->print_cast(), i);
          break;
          
          // A single character
          
        case T_CHAR :
          fprintf(f_wrappers,"\t _arg%d = %s gh_scm2char(s_%d);\n", i, p->t->print_cast(), i);
          break;
          
          // Floating point
          
        case T_DOUBLE :
        case T_FLOAT:
          fprintf(f_wrappers,"\t _arg%d = %s gh_scm2double(s_%d);\n", i, p->t->print_cast(), i);
          break;
          
          // Void.. Do nothing.
          
        case T_VOID :
          break;
          
          // This is some sort of user-defined call by value type.   We're
          // going to try and wing it here....
          
        case T_USER:
          
          // User defined type not allowed by value.
          
        default :
          fprintf(stderr,"%s : Line %d. Unable to use type %s as a function argument.\n",
                  input_file, line_number, p->t->print_type());
          break;
        }
      } else {
        
        // Argument is a pointer type.   Special case is for char *
        // since that is usually a string.
        
        if ((p->t->type == T_CHAR) && (p->t->is_pointer == 1)) {
          fprintf(f_wrappers,"\t _arg%d = gh_scm2newstr(s_%d, &_len);\n",i,i);
        } else {
          
          // Have a generic pointer type here.    
          
          get_pointer(iname, i, p->t);
        }
      }
    }
    if ((tm = typemap_lookup("check","guile",p->t,p->name,source,target))) {
      // Yep.  Use it instead of the default
      fprintf(f_wrappers,"%s\n",tm);
    }
    if ((tm = typemap_lookup("freearg","guile",p->t,p->name,target,"scmresult"))) {
      // Yep.  Use it instead of the default
      cleanup << tm << "\n";
    }
    p = l->get_next();
    i++;
  }

  // Now write code to make the function call

  fprintf(f_wrappers,"\t SCM_DEFER_INTS;\n");
  emit_func_call(name,d,l,f_wrappers);

  fprintf(f_wrappers,"\t SCM_ALLOW_INTS;\n");
  // Now have return value, figure out what to do with it.

  if ((d->type != T_VOID) || (d->is_pointer)) {
    if ((tm = typemap_lookup("out","guile",d,name,"_result","scmresult"))) {
      // Yep.  Use it instead of the default
      fprintf(f_wrappers,"%s\n",tm);
    } else {
      if (!d->is_pointer) {
        switch(d->type) {
        case T_INT:  case T_SINT:
        case T_SHORT: case T_SSHORT:
        case T_LONG: case T_SLONG:
        case T_SCHAR:
          fprintf(f_wrappers,"\t scmresult = gh_long2scm((long) _result);\n");
          break;
        case T_UINT:
        case T_USHORT:
        case T_ULONG:
        case T_UCHAR:
          fprintf(f_wrappers,"\t scmresult = gh_ulong2scm((unsigned long) _result);\n");
          break;
        case T_DOUBLE :
        case T_FLOAT:
          fprintf(f_wrappers,"\t scmresult = gh_double2scm((double) _result);\n");
          break;
        case T_CHAR :
          fprintf(f_wrappers,"\t scmresult = gh_char2scm(_result);\n");
          break;
        default:
          fprintf(stderr,"%s : Line %d: Unable to use return type %s in function %s.\n",
                  input_file, line_number, d->print_type(), name);
          break;
        }
      } else {
        
        // Is a pointer return type
        
        if ((d->type == T_CHAR) && (d->is_pointer == 1)) {
          fprintf(f_wrappers,"\t scmresult = gh_str02scm(_result);\n");
        } else {
          
          // Is an ordinary pointer type.
          
          fprintf(f_wrappers,"\t  SWIG_MakePtr(_ptemp, _result,\"%s\");\n",
                  d->print_mangle());
          fprintf(f_wrappers,"\t scmresult = gh_str02scm(_ptemp);\n");
        }
      }
    }
  } else {
    /* Some void type.   Need to return something.  I'll return 1 */
    fprintf(f_wrappers,"\t scmresult = gh_int2scm(1);\n");
  }

  // Dump the argument cleanup code
  fprintf(f_wrappers,"%s\n",cleanup.get());

  // Look for any remaining cleanup

  if (NewObject) {
    if ((tm = typemap_lookup("newfree","guile",d,iname,"_result",""))) {
      fprintf(f_wrappers,"%s\n",tm);
    }
  }

  if ((tm = typemap_lookup("ret","guile",d,name,"_result",""))) {
    // Yep.  Use it instead of the default
    fprintf(f_wrappers,"%s\n",tm);
  }
  
  // Wrap things up (in a manner of speaking)
  
  fprintf(f_wrappers,"\t return scmresult;\n");
  fprintf(f_wrappers,"}\n");

  // Now register the function
  fprintf(f_init,"\t gh_new_procedure(\"%s\", _wrap_gscm_%s, %d, 0, 0);\n", 
          iname, wname, pcount);

  // Make a documentation entry for this

  if (doc_entry) {
    static DocEntry *last_doc_entry = 0;
    char *usage = 0;
    usage_func(iname,d,l,&usage);
    doc_entry->usage << usage;
    if (last_doc_entry != doc_entry) {
      doc_entry->cinfo << "returns " << d->print_type();
      last_doc_entry = doc_entry;
    }
    delete usage;
  }
}

// -----------------------------------------------------------------------
// GUILE::link_variable(char *name, char *iname, DataType *d)
//
// Create a link to a C variable.
// This creates a single function _wrap_gscm_var_varname().
// This function takes a single optional argument.   If supplied, it means
// we are setting this variable to some value.  If ommitted, it means we are
// simply evaluating this variable.  Either way, we return the variables
// value.
// -----------------------------------------------------------------------

void GUILE::link_variable(char *name, char *iname, DataType *t)
{

  char  var_name[256];
  char  *tm;

  // evaluation function names

  sprintf(var_name,"_wrap_gscm_var_%s",iname);

  if ((t->type != T_USER) || (t->is_pointer)) {

    fprintf(f_wrappers,"SCM %s(SCM s_0) {\n", var_name);

    if ((t->type == T_CHAR) || (t->is_pointer)){
      fprintf(f_wrappers,"\t char *_temp, _ptemp[128];\n");
      fprintf(f_wrappers,"\t int  _len;\n");
    }
    fprintf(f_wrappers,"\t SCM scmresult;\n");

    // Check for a setting of the variable value

    fprintf(f_wrappers,"\t if (s_0 != GH_NOT_PASSED) {\n");
    
    // Yup. Extract the type from s_0 and set variable value 
    if (Status & STAT_READONLY) {
//      fprintf(f_wrappers,"\t\t gscm_error(\"Unable to set %s. Variable is read only.\", s_0);\n", iname);
    } else {
      if ((tm = typemap_lookup("varin","guile",t,name,"s_0",name))) {
        // Yep.  Use it instead of the default
        fprintf(f_wrappers,"%s\n",tm);
      } else {
        if (!t->is_pointer) {

          switch(t->type) {
            // Signed Integer
            
          case T_INT:  case T_SINT:
          case T_SHORT: case T_SSHORT:
          case T_LONG: case T_SLONG:
          case T_SCHAR:
            fprintf(f_wrappers,"\t\t %s = %s gh_scm2long(s_0);\n",name, t->print_cast());
            break;
            
            // Unsigned integer
            
          case T_UINT:
          case T_USHORT:
          case T_ULONG:
          case T_UCHAR:
            fprintf(f_wrappers,"\t\t %s = %s gh_scm2ulong(s_0);\n",name, t->print_cast());
            break;
            
            // Floating point
            
          case T_FLOAT:
          case T_DOUBLE:
            fprintf(f_wrappers,"\t\t %s = %s gh_scm2double(s_0);\n",name, t->print_cast());
            break;
            
            // Character value
            
          case T_CHAR:
            fprintf(f_wrappers,"\t\t %s = gh_scm2char(s_0);\n", name);
            break;
            
            // Unknown value 
            
          default:
            fprintf(stderr,"Line %d.  Error, unsupported data-type.\n", line_number);
            break;
          }
        } else {
          
          // Have some sort of pointer type here, Process it differently
          
          if ((t->type == T_CHAR) && (t->is_pointer == 1)) {
            fprintf(f_wrappers,"\t\t _temp = gh_scm2newstr(s_0, &_len);\n");
            fprintf(f_wrappers,"\t\t if (%s) { free(%s);}\n", name,name);
            fprintf(f_wrappers,"\t\t %s = (char *) malloc((_len+1)*sizeof(char));\n",name);
            fprintf(f_wrappers,"\t\t strncpy(%s,_temp,_len);\n",name);
            fprintf(f_wrappers,"\t\t %s[_len] = 0;\n", name);
          } else {
            // Set the value of a pointer
            fprintf(f_wrappers,"\t\t _temp = gh_scm2newstr(s_0,&_len);\n");
            fprintf(f_wrappers,"\t if (SWIG_GetPtr(_temp, (void **) &%s,",name);
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
                      "\t fprintf(stderr,\"Warning : type mismatch in variable %s. Expected %s, received %%s\\n\", _temp);\n", name, t->print_mangle());
              fprintf(f_wrappers,"\t }\n");
              break;
            case 2: // Super strict mode.
              
//            fprintf(f_wrappers,"\t\t gscm_error(\"Type error in variable %s. Expected %s.\", s_0);\n", name,t->print_mangle());
              fprintf(f_wrappers,"\t}\n");
              break;
              
            default :
              fprintf(stderr,"Unknown strictness level\n");
              break;
            }
          }
        }
      }
    }
    fprintf(f_wrappers,"\t}\n");

    // Now return the value of the variable (regardless of evaluating or setting)

    if ((tm = typemap_lookup("varout","guile",t,name,name,"scmresult"))) {
      // Yep.  Use it instead of the default
      fprintf(f_wrappers,"%s\n",tm);
    } else {
      if (!t->is_pointer) {
        /* Return variable by value */
        
        switch(t->type) {
          
          // Signed Integer
          
        case T_INT: case T_SINT:
        case T_SHORT: case T_SSHORT:
        case T_LONG: case T_SLONG:
        case T_SCHAR:
          fprintf(f_wrappers,"\t scmresult = gh_long2scm((long) %s);\n", name);
          break;
          
          // Unsigned integer
          
        case T_UINT:
        case T_USHORT:
        case T_ULONG:
        case T_UCHAR:
          fprintf(f_wrappers,"\t scmresult = gh_ulong2scm((unsigned long) %s);\n",name);
          break;
          
          // Floats
          
        case T_DOUBLE:
        case T_FLOAT:
          fprintf(f_wrappers,"\t scmresult = gh_double2scm((double) %s);\n", name);
          break;
        case T_CHAR:
          fprintf(f_wrappers,"\t scmresult = gh_char2scm(%s);\n",name);
          break;
        default :
          /* Unknown type */
          break;
        }
      } else {
        
        // Is a pointer return type
        
        if ((t->type == T_CHAR) && (t->is_pointer == 1)) {
          fprintf(f_wrappers,"\t scmresult = gh_str02scm(%s);\n",name);
        } else {
          // Is an ordinary pointer type.
          fprintf(f_wrappers,"\t  SWIG_MakePtr(_ptemp, %s,\"%s\");\n",name,
                  t->print_mangle());
          fprintf(f_wrappers,"\t scmresult = gh_str02scm(_ptemp);\n");
        }
      }
    }
    fprintf(f_wrappers,"\t return scmresult;\n");
    fprintf(f_wrappers,"}\n");
    
    // Now add symbol to the Guile interpreter
    
    fprintf(f_init,"\t gh_new_procedure(\"%s\", %s, 0, 1, 0);\n",iname, var_name);
    
  } else {
    fprintf(stderr,"%s : Line %d. ** Warning. Unable to link with type %s (ignored).\n",
            input_file, line_number, t->print_type());
  }

  // Add a documentation entry
  
  if (doc_entry) {
    char *usage = 0; 
    usage_var(iname,t,&usage);
    doc_entry->usage << usage;
    doc_entry->cinfo << "Global : " << t->print_type() << " " << name;
    delete usage;
  }

}

// -----------------------------------------------------------------------
// GUILE::declare_const(char *name, char *iname, DataType *type, char *value)
//
// Makes a constant.   Not sure how this is really supposed to work.
// I'm going to fake out SWIG and create a variable instead.
// ------------------------------------------------------------------------

void GUILE::declare_const(char *name, char *, DataType *type, char *value) {

  int OldStatus = Status;      // Save old status flags
  char   var_name[256];

  Status = STAT_READONLY;      // Enable readonly mode.

  // Make a static variable;

  sprintf(var_name,"_wrap_const_%s",name);

  if ((type->type == T_USER) && (!type->is_pointer)) {
    fprintf(stderr,"%s : Line %d.  Unsupported constant value.\n", input_file, line_number);
    return;
  }

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
// GUILE::usage_var(char *iname, DataType *t, char **s)
//
// Produces a usage string for a Guile variable.
// ----------------------------------------------------------------------

void GUILE::usage_var(char *iname, DataType *t, char **s) {

  char temp[1024], *c;

  sprintf(temp,"(%s)", iname);
  c = temp + strlen(temp);

  if (!((t->type != T_USER) || (t->is_pointer))) {
    sprintf(c," - unsupported");
  }

  if (*s == 0) 
    *s = new char[strlen(temp)+1];
  strcpy(*s,temp);
}

// ---------------------------------------------------------------------------
// GUILE::usage_func(char *iname, DataType *t, ParmList *l, char **s)
// 
// Produces a usage string for a function in Guile
// ---------------------------------------------------------------------------

void GUILE::usage_func(char *iname, DataType *, ParmList *l,
                        char **s) {

  char temp[1024];
  char *c;
  int  i;
  Parm  *p;

  sprintf(temp,"(%s ", iname);
  c = temp + strlen(temp);
  
  /* Now go through and print parameters */

  p = l->get_first();
  while (p != 0) {
    
    /* If parameter has been named, use that.   Otherwise, just print a type  */

    if ((p->t->type != T_VOID) || (p->t->is_pointer)) {
      if (strlen(p->name) > 0) {
        sprintf(c,"%s ",p->name);
        c += strlen(p->name)+1;
      }
      else {
        sprintf(c,"%s",p->t->name);
        c += strlen(p->t->name);
        if (p->t->is_pointer) {
          for (i = 0; i < (p->t->is_pointer-p->t->implicit_ptr); i++) {
            sprintf(c,"*");
            c++;
          }
        }
      }
    }
      p = l->get_next();
      if (p != 0) {
        sprintf(c," ");
        c++;
      }
  }
  sprintf(c,")");
  if (*s == 0) 
    *s = new char[strlen(temp)+1];
  strcpy(*s,temp);
}


// ----------------------------------------------------------------------
// GUILE::usage_const(char *iname, DataType *type, char *value, char **s)
//
// Produces a usage string for a Guile constant
// ----------------------------------------------------------------------

void GUILE::usage_const(char *iname, DataType *, char *value, char **s) {

  char temp[1024];

  sprintf(temp,"(%s %s)", iname, value);

  if (*s == 0) 
    *s = new char[strlen(temp)+1];
  strcpy(*s,temp);

}

/*********************************************************************************
 *
 * -- Revision History
 * $Log: guile.cxx,v $
 * Revision 1.13  1997/07/08 05:15:10  beazley
 * Incorporated changes for Guile 1.2.   Contributed by Dominique Sidou.
 *
 * Revision 1.12  1997/06/22 16:35:38  beazley
 * Added SWIGGUILE define
 *
 * Revision 1.11  1997/06/20 05:25:35  beazley
 * Added warning message about missing module name
 *
 * Revision 1.10  1997/05/28 21:36:45  beazley
 * Moved revision history to end.
 *
 * Revision 1.9  1997/04/19 21:25:02  beazley
 * Added support for %new directive
 *
 * Revision 1.8  1997/03/21 00:10:16  beazley
 * Changed exit() to SWIG_exit()
 *
 * Revision 1.7  1997/03/19 23:48:52  beazley
 * changed constrain typemap to check.
 *
 * Revision 1.6  1997/03/18 22:28:04  beazley
 * Added constrain typemap.
 *
 * Revision 1.5  1997/03/08 23:50:55  beazley
 * Updated to use the "gh" interface
 *
 * Revision 1.4  1997/01/08 05:43:06  beazley
 * Pre 1.1b3 checkin
 *
 * Revision 1.3  1997/01/06 17:12:03  beazley
 * Added support for typemaps.  Multiple inheritance.
 *
 * Revision 1.2  1996/12/26 23:03:19  beazley
 * Modified to use new pointer type-checker
 *
 * Revision 1.1  1996/12/26 04:48:00  beazley
 * Initial revision
 *
 * Revision 1.17  1996/08/21 16:51:07  dmb
 * Fixed bug in printf()
 *
 * Revision 1.16  1996/08/12 01:48:36  dmb
 * Changes to support new language class.
 *
 * Revision 1.15  1996/08/02 02:58:39  dmb
 * Changed to use better parameter list functions.
 *
 * Revision 1.14  1996/07/17 14:58:39  dmb
 * Fixed bug in -strict 1 pointer type checking mode.
 *
 * Revision 1.13  1996/05/22 20:20:21  beazley
 * Changed initialize and close functions to work with new emit functions
 *
 * Revision 1.12  1996/05/20  23:35:35  beazley
 * Added a few more constant datatypes.
 *
 * Revision 1.11  1996/05/13  23:44:53  beazley
 * Reworked the module/init procedure.
 *
 * Revision 1.10  1996/05/01  22:40:42  dmb
 * Cleaned up command line options.
 *
 * Revision 1.9  1996/04/09 20:18:53  beazley
 * Minor cleanup
 *
 * Revision 1.8  1996/04/08  22:09:20  beazley
 * Minor cleanup
 *
 * Revision 1.7  1996/03/28  02:46:27  beazley
 * Minor bug fix to documentation functions.
 *
 * Revision 1.6  1996/03/04  21:28:19  beazley
 * Made slight changes to usage() functions.
 *
 * Revision 1.5  1996/02/19  05:30:24  beazley
 * Changed treatment of pointers.
 *
 * Revision 1.4  1996/02/16  07:25:03  beazley
 * Fixed problem with sprintf();
 *
 * Revision 1.3  1996/02/16  06:38:49  beazley
 * Removed a few unused variables.
 *
 * Revision 1.2  1996/02/15  22:37:36  beazley
 * Changed copyright
 *
 * Revision 1.1  1996/02/12  08:19:53  beazley
 * Initial revision
 *
 * Revision 1.3  1996/01/23  19:41:25  beazley
 * Fixed a few bugs.
 *
 * Revision 1.2  1996/01/16  00:55:45  beazley
 * Minor changes
 *
 * Revision 1.1  1996/01/15  22:11:41  beazley
 * Initial revision
 *
 * Revision 1.1  1996/01/13  01:34:04  beazley
 * Initial revision
 *
 ***********************************************************************/

