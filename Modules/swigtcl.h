
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
 * class TCL
 *
 * A Simple TCL implementation.
 **************************************************************************/

class TCL : public Language {
private:
  char   interp_name[256];
  char  *prefix;                   // Package prefix
  char  *module;                   // Name of the module
  char   tcl_include[256];
  char   tk_include[256];
  char  *tcl_path;
  char  *init_name;
  int    Plugin;
  int    nspace;
  char  *safe_name;
  void   get_pointer(char *iname, char *srcname, char *src, char *dest, DataType *t,
		     String &f, char *ret);
  char  *char_result;
  char  *usage_string(char *, DataType *, ParmList *);
  char  *usage_func(char *, DataType *, ParmList *);
  char  *usage_var(char *, DataType *);
  char  *usage_const(char *, DataType *, char *);
  
  // C++ handling

  int    have_constructor;
  int    have_destructor;
  int    have_methods;
  int    have_config;
  int    have_cget;
  String config;
  String cget;
  String methods;
  String options;
  String config_options;
  String methodnames;
  String postinit;
  int    shadow;
  char   *class_name;
  char   *class_type;
  char   *real_classname;
  char   *base_class;
  Hash   hash;
  Hash   repeatcmd;

  // C++ Code generation strings

  String delcmd;
  String methodcmd;
  String objcmd;

public :
    TCL() {
    prefix = 0;
    module = 0;
    init_name = 0;
    safe_name = 0;
    Plugin = 0;
    nspace = 0;
    shadow = 1;
    char_result = "TCL_VOLATILE";
    tcl_path = "tcl";
    sprintf(interp_name,"interp");
    sprintf(tcl_include,"tcl.h");
    sprintf(tk_include,"tk.h");
    class_name = 0;
    class_type = 0;
    real_classname = 0;
    base_class = 0;
  };
  void parse_args(int, char *argv[]);
  void parse();
  void create_function(char *, char *, DataType *, ParmList *);
  void link_variable(char *, char *, DataType *);
  void declare_const(char *, char *, DataType *, char *);
  void initialize(void);
  void headers(void);
  void close(void);
  void set_module(char *,char **);
  void set_init(char *);
  void add_native(char *, char *);
  void pragma(char *,char *, char *);
  void create_command(char *, char *);

  // Stubs for processing C++ classes in Tcl

  void cpp_open_class(char *classname, char *rename, char *ctype, int strip);
  void cpp_close_class();
  void cpp_member_func(char *name, char *iname, DataType *t, ParmList *l);
  void cpp_variable(char *name, char *iname, DataType *t);
  void cpp_constructor(char *name, char *iname, ParmList *l);
  void cpp_destructor(char *name, char *newname);
  void cpp_inherit(char **baseclass, int mode = INHERIT_ALL);
  void cpp_declare_const(char *name, char *iname, DataType *type, char *value);
  void cpp_class_decl(char *, char *, char *);
  void add_typedef(DataType *, char *);
};






