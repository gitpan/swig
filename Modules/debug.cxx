
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
/**************************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.1/Modules/RCS/debug.cxx,v 1.11 1997/06/20 22:38:09 beazley Exp $
 *
 * debug.cxx
 *
 * This is a dummy language module that is used only for testing the SWIG
 * parser.
 *
 * It creates a wrapper file, but only containing descriptions of what
 * was wrapped.
 *
 ***************************************************************************/

#include "swig.h"
#include "debug.h"

void DEBUGLANG::parse_args(int, char **) {
  sprintf(LibDir,"%s",path);
  typemap_lang = "debug";
}

void DEBUGLANG::parse() { 
  headers();
  yyparse();
}

void DEBUGLANG::set_module(char *mod_name, char **) { 
  if (module) return;
  module = new char[strlen(mod_name)+1];
  strcpy(module,mod_name);
}

void DEBUGLANG::set_init(char *init_name) { 
  set_module(init_name,0);
}

void DEBUGLANG::headers(void) { 
  fprintf(f_header,"/* DEBUG : Language specific headers go here */\n\n");
  fprintf(f_header,"/* DEBUG : Pointer conversion function here */\n\n");
  fprintf(f_header,"/* DEBUG : Language specific code here */\n\n");
}

void DEBUGLANG::initialize(void) {
  
  fprintf(f_header,"#define   SWIG_init     %s_init\n\n", module);
  fprintf(f_header,"#define   SWIG_name    \"%s\"\n", module);
  
  fprintf(f_init,"\n/* MODULE INITIALIZATION */\n\n");
  fprintf(f_init,"void %s_init() {\n", module);

}

void DEBUGLANG::close(void) { 
  fprintf(f_init,"}  /* END INIT */\n");
  
  fprintf(f_wrappers,"SWIG POINTER-MAPPING TABLE\n\n");
  emit_ptr_equivalence(f_init);
}

void DEBUGLANG::create_function(char *name, char *iname, DataType *d, ParmList *l) {
  
  fprintf(f_wrappers,"WRAPPER : ");
  emit_extern_func(name,d,l,0,f_wrappers);
  fprintf(f_wrappers,"\n");

  fprintf(f_init,"     ADD COMMAND    : %s --> ", iname);
  emit_extern_func(name,d,l,0,f_init);

}
 
void DEBUGLANG::link_variable(char *name, char *iname, DataType *t)  { 
  fprintf(f_wrappers,"WRAPPER : ");
  emit_extern_var(name,t,0,f_wrappers);
  
  fprintf(f_init,"     ADD VARIABLE   : %s --> ", iname);
  emit_extern_var(name,t,0,f_init);

}

void DEBUGLANG::declare_const(char *name, char *, DataType *type, char *value) { 
  if (!value) value = "[None]";
  fprintf(f_init,"     ADD CONSTANT   : %s %s = %s\n", type->print_cast(),name,value);
}

void DEBUGLANG::add_native(char *name, char *funcname) { 
  fprintf(f_init,"     ADD NATIVE     : %s --> %s\n", name, funcname);
}

void DEBUGLANG::cpp_member_func(char *name, char *iname, DataType *t, ParmList *l) {
  fprintf(f_wrappers,"        MEMBER FUNC   : ");
  emit_extern_func(name,t,l,0,f_wrappers);
  fprintf(f_wrappers,"\n");
  if (!iname) iname = name;
  fprintf(f_init,"     ADD MEMBER FUN : %s --> ", iname);
  emit_extern_func(name,t,l,0,f_init);
}

void DEBUGLANG::cpp_constructor(char *name, char *iname, ParmList *l) { 
  DataType *t;
  fprintf(f_wrappers,"        CONSTRUCTOR   : ");
  t = new DataType(T_USER);
  sprintf(t->name,"%s",name);
  t->is_pointer=1;
  emit_extern_func(name,t,l,0,f_wrappers);
  if (!iname) iname = name;
  fprintf(f_init,"     ADD CONSTRUCT  : %s --> ", iname);
  emit_extern_func(name,t,l,0,f_init);
}

void DEBUGLANG::cpp_destructor(char *name, char *iname) {
  fprintf(f_wrappers,"        DESTRUCTOR    : ~%s();\n", name);
  if (!iname) iname = name;
  fprintf(f_init,"     ADD DESTRUCT  : %s --> ~%s();\n",iname,name);
}

void DEBUGLANG::cpp_open_class(char *name, char *iname, char *ctype, int strip) { 
  this->Language::cpp_open_class(name, iname, ctype,strip);
  fprintf(f_wrappers,"C++ CLASS START : %s %s  ========================================\n\n",ctype,name);
  fprintf(f_init,"\n     // C++ CLASS START : %s %s\n",ctype,name);
}

void DEBUGLANG::cpp_close_class() { 
  fprintf(f_wrappers,"C++ CLASS END ===================================================\n\n");
  fprintf(f_init,"     // C++ CLASS END \n\n");
}

void DEBUGLANG::cpp_inherit(char **baseclass, int) { 
  int i = 0;
  if (baseclass) {
    fprintf(f_wrappers,"inheriting from baseclass :");
    while (baseclass[i]) {
      fprintf(f_wrappers," %s",baseclass[i]);
      i++;
    }
    fprintf(f_wrappers,"\n");
  }
  this->Language::cpp_inherit(baseclass);
}

void DEBUGLANG::cpp_variable(char *name, char *iname, DataType *t) { 
  fprintf(f_wrappers,"        ATTRIBUTE     : ");
  emit_extern_var(name,t,0,f_wrappers);
  if (!iname) iname = name;
  fprintf(f_init,"     ADD MEMBER     : %s --> ", iname);
  emit_extern_var(name,t,0,f_init);
}
void DEBUGLANG::cpp_static_func(char *name, char *iname, DataType *t, ParmList *l) {

  fprintf(f_wrappers,"        STATIC FUNC   : ");
  emit_extern_func(name,t,l,0,f_wrappers);
  fprintf(f_init,"     ADD STATIC FUNC: %s --> ", iname);
  emit_extern_func(name,t,l,0,f_init);

}

void DEBUGLANG::cpp_declare_const(char *name, char *iname, DataType *t, char *value) { 
  if (!value) value = "[None]";
  fprintf(f_wrappers,"        C++ CONST     : %s %s = %s\n", t->print_cast(), name, value);
  if (!iname) iname = name;
  fprintf(f_init,"     ADD C++ CONST  : %s --> %s = %s\n", iname, t->print_cast(), value);
}

void DEBUGLANG::cpp_static_var(char *name, char *iname, DataType *t) { 
  fprintf(f_wrappers,"        C++ STATIC VAR: ");
  emit_extern_var(name,t,0,f_wrappers);
  if (!iname) iname = name;
  fprintf(f_init,"     ADD STATIC VAR : %s --> ",iname);
  emit_extern_var(name,t,0,f_init);
}

void DEBUGLANG::pragma(char *lname, char *name, char *value) { 
  fprintf(f_wrappers,"PRAGMA : LANG = %s, NAME = %s ", lname, name);
  if (value) {
    fprintf(f_wrappers,", VALUE = %s\n", value);
  } else {
    fprintf(f_wrappers,"\n");
  }
}

void DEBUGLANG::cpp_class_decl(char *name, char *, char *type) { 
  fprintf(f_wrappers,"C++ CLASS DECLARATION : %s %s\n", type,name);
}


