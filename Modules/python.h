
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
 * $Header: /home/beazley/SWIG/SWIG1.2/Modules/RCS/python.h,v 1.17 1997/07/03 03:25:30 beazley Exp beazley $
 *
 * python.h
 *
 * Header file for Python module.   Warning ; this is work in progress.
 *
 * $Log: python.h,v $
 * Revision 1.17  1997/07/03 03:25:30  beazley
 * Added have_output flag.
 *
 * Revision 1.16  1997/06/17 04:41:32  beazley
 * Changed cpp_class_decl() prototype.
 *
 * Revision 1.15  1997/03/12 05:04:25  beazley
 * Minor changes
 *
 * Revision 1.14  1997/02/19 23:06:44  beazley
 * Added create_command method.
 *
 * Revision 1.13  1997/01/27 05:14:01  beazley
 * Added support for default arguments in shadow classes.
 *
 * Revision 1.12  1997/01/09 01:22:19  beazley
 * Fixed inheritance slightly
 *
 * Revision 1.11  1997/01/06 17:12:35  beazley
 * Added support for typemaps and multiple inheritance
 *
 * Revision 1.10  1996/12/26 04:51:07  beazley
 * Minor tweaks
 *
 * Revision 1.9  1996/12/05 00:49:23  beazley
 * Minor cleanup
 *
 * Revision 1.8  1996/11/12 20:02:44  beazley
 * Changes to support new documentation and C++ handling
 *
 * Revision 1.7  1996/09/26 21:50:31  dmb
 * Minor fixes
 *
 * Revision 1.6  1996/08/21 05:51:32  dmb
 * Changes to support shadow classing
 *
 * Revision 1.5  1996/08/12 01:52:21  dmb
 * Changes to language class structure
 *
 * Revision 1.4  1996/05/13 23:46:52  beazley
 * Minor modifications to class structure for better module
 * support
 *
 * Revision 1.3  1996/05/10  23:39:50  beazley
 * Minor changes
 *
 * Revision 1.2  1996/04/13  19:02:17  beazley
 * Fixed bug with modules.
 *
 * Revision 1.1  1996/03/24  22:15:34  beazley
 * Initial revision
 *
 **************************************************************************/

class PYTHON : public Language {
protected:
  char   *module;               // Module name
  char   *path;                 // Pathname of where to look for library files
  char   *methods;              // Method table name
  char   *global_name;          // Name of global variables.
  void    get_pointer(char *iname, char *srcname, char *src, char *dest, DataType *t, String &f, char *ret);
  int     shadow;
  int     have_defarg;
  int     docstring;
  int     have_output;
  FILE    *f_shadow;
  struct Method {               // Methods list.  Needed to build methods
    char   *name;               // Array at very end.
    char   *function;
    Method *next;
  };
  Method  *head;
  Hash     hash;
  String   classes;
  String   func;
  String   vars;
  String   modinit;
  String   modextern;

  char     *import_file;
  void add_method(char *name, char *function);
  void print_methods();
  char *usage_var(char *, DataType *);
  char *usage_func(char *, DataType *, ParmList *);
  char *usage_const(char *, DataType *, char *);
  void shadow_defargs(Parm *p, ParmList *l, int i, int pcount, int numopt,
		      String &code, char *indent);
  char *add_docstring(DocEntry *de);

  // Add for Python-COM support
  virtual void initialize_cmodule();
  virtual void close_cmodule();
  virtual void emit_function_header(WrapperFunction &emit_to, char *wname);
  virtual char *convert_self(WrapperFunction &f);
  virtual char *make_funcname_wrapper(char *fnName);

public :
  PYTHON() {
    module = (char *) 0;
    path = "python";     // Set this to subdirectory where language
                                  // Dependent library files will be stored
    head = 0;                     // Head of method list
    global_name = "cvar";
    shadow = 0;
    have_defarg = 0;
    import_file = 0;
  };

  // Don't change any of this
  void parse_args(int, char *argv[]);
  void parse();
  void create_function(char *, char *, DataType *, ParmList *);
  void link_variable(char *, char *, DataType *);
  void declare_const(char *, char *, DataType *, char *);
  void initialize(void);
  void headers(void);
  void close(void);
  void set_module(char *, char **);
  void set_init(char *);
  void add_native(char *, char *);
  void create_command(char *, char *);
  void import(char *);

  // C++ extensions---for creating shadow classes
  
  void cpp_member_func(char *name, char *iname, DataType *t, ParmList *l);
  void cpp_constructor(char *name, char *iname, ParmList *l);
  void cpp_destructor(char *name, char *newname);
  void cpp_open_class(char *classname, char *rname, char *ctype, int strip);
  void cpp_close_class();
  void cpp_cleanup();
  void cpp_inherit(char **baseclass, int mode = INHERIT_ALL);
  void cpp_variable(char *name, char *iname, DataType *t);
  void cpp_declare_const(char *name, char *iname, DataType *type, char *value);
  void cpp_class_decl(char *, char *,char *);
  void pragma(char *, char *, char *);
  void add_typedef(DataType *t, char *name);
};

#define PYSHADOW_MEMBER  0x2

