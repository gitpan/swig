
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
 * class PERL5
 *
 * A Perl 5 implementation
 **************************************************************************/

class PERL5 : public Language {
private:
  int    export_all;
  char   *package;
  char   *module;
  String  vinit;
  FILE   *f_pm;
  String  pm;                      // Package initialization code
  String  magic;                   // Magic variable wrappers

  char   *perl_path;
  int    is_static;
  void   get_pointer(char *iname, char *srcname, char *src, char *dest,
			DataType *t, String &f, char *ret);
  char     *usage_var(char *, DataType *);
  char     *usage_func(char *, DataType *, ParmList *);
  char     *usage_const(char *, DataType *, char *);

  char   *alt_header;   

// The following variables are used to manage Perl5 classes

  int      blessed;                // Enable object oriented features
  Hash     classes;                // A hash table for storing the classes we've seen so far
  int      have_constructor;
  int      have_destructor;
  int      have_data_members;
  char     *class_name;            // Name of the class (what Perl thinks it is)
  char     *class_type;            // Type of class "struct", "class", "union"
  char     *real_classname;        // Real name of C/C++ class
  String   *base_class;            // Base class (if using inheritance)
  String   *pcode;                 // Perl code associated with each class
  String   *blessedmembers;        // Member data associated with each class
  int      member_func;            // Set to 1 when wrapping a member function
  char     *realpackage;           // Name of real module 
  String   func_stubs;             // Function stubs
  String   var_stubs;              // Variable stubs
  String   *member_keys;            // Keys for all member data
  String   exported;               // Exported symbols

public :
  PERL5() {
    package = 0;
    module = 0;
    perl_path = "perl5";
    is_static = 0;
    blessed = 0;
    alt_header = 0;
    member_func = 0;
  };
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
  char *type_mangle(DataType *);

  // Support for blessed perl thingies....

  void cpp_open_class(char *classname, char *rename, char *ctype, int strip);
  void cpp_close_class();
  void cpp_member_func(char *name, char *iname, DataType *t, ParmList *l);
  void cpp_static_func(char *name, char *iname, DataType *t, ParmList *l);
  void cpp_variable(char *name, char *iname, DataType *t);
  void cpp_constructor(char *name, char *iname, ParmList *l);
  void cpp_destructor(char *name, char *newname);
  void cpp_inherit(char **baseclass, int mode = INHERIT_ALL);
  void cpp_declare_const(char *name, char *iname, DataType *type, char *value);
  void cpp_class_decl(char *, char *, char *);
  void add_typedef(DataType *t, char *name);
  void pragma(char *, char *, char *);
  void import(char *filename);
};



