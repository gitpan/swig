
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

class DEBUGLANG : public Language {
private:
  char *path;
  char *module;
public:
  DEBUGLANG() {
    path = "debug";
    module = "swig";
  }
  void parse_args(int argc, char *argv[]);
  void parse();
  void create_function(char *, char *, DataType *, ParmList *); 
  void link_variable(char *, char *, DataType *) ;
  void declare_const(char *, char *, DataType *, char *);
  void initialize(void);
  void headers(void);
  void close(void);
  void set_module(char *mod_name, char **mod_list);
  void set_init(char *init_name);
  void add_native(char *, char *);
  char *type_mangle(DataType *t) {
    return t->print_mangle_default();
  }
  void cpp_member_func(char *, char *, DataType *, ParmList *);
  void cpp_constructor(char *, char *, ParmList *);
  void cpp_destructor(char *, char *);
  void cpp_open_class(char *, char *, char *, int strip);
  void cpp_close_class();
  void cpp_inherit(char **, int mode = INHERIT_ALL);
  void cpp_variable(char *, char *, DataType *);
  void cpp_static_func(char *, char *, DataType *, ParmList *);
  void cpp_declare_const(char *, char *, DataType *, char *);
  void cpp_static_var(char *, char *, DataType *);
  void pragma(char *, char *, char *);
  void cpp_class_decl(char *, char *, char *);
  
};
