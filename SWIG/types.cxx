/**********************************************************************
 * Simplified Wrapper and Interface Generator  (SWIG)
 * 
 * Dave Beazley
 * 
 * Theoretical Division (T-11)           Department of Computer Science
 * Los Alamos National Laboratory        University of Utah
 * Los Alamos, New Mexico  87545         Salt Lake City, Utah  84112
 * beazley@lanl.gov                      beazley@cs.utah.edu
 *
 * Copyright (c) 1995-1996
 * The Regents of the University of California and the University of Utah
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
 * The author requests that all users of this software return any
 * improvements made to beazley@cs.utah.edu and grant the author
 * full redistribution rights.
 *
 **************************************************************************/
/***********************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.2/SWIG/RCS/types.cxx,v 1.35 1997/07/25 04:03:08 beazley Exp $
 *
 * types.cxx
 *
 * This file contains functions for dealing with datatypes.  This
 * is a combination of the file typedef.cc (now obsolete) and functions
 * that used to be in the swig.h header.
 *
 ***********************************************************************/

#include "internal.h"

// -------------------------------------------------------------------
// class DataType member functions.
// -------------------------------------------------------------------

DataType::DataType() {
    type = 1;
    name[0] = 0;
    is_pointer = 0;
    implicit_ptr = 0;
    qualifier = 0;
    is_reference = 0;
    status = 0;
    arraystr = 0;
    id = type_id++;
}

// Create a data type only from the type code (used to form constants)

DataType::DataType(int t) {
  switch(t) {
  case T_BOOL:
    strcpy(name,"bool");
    break;
  case T_INT: case T_SINT:
    strcpy(name,"int");
    break;
  case T_UINT:
    strcpy(name,"unsigned int");
    break;
  case T_SHORT: case T_SSHORT:
    strcpy(name,"short");
    break;
  case T_USHORT:
    strcpy(name,"unsigned short");
    break;
  case T_LONG: case T_SLONG:
    strcpy(name,"long");
    break;
  case T_ULONG:
    strcpy(name,"unsigned long");
    break;
  case T_FLOAT:
    strcpy(name, "float");
    break;
  case T_DOUBLE:
    strcpy(name, "double");
    break;
  case T_CHAR: case T_SCHAR:
    strcpy(name, "char");
    break;
  case T_UCHAR:
    strcpy(name,"unsigned char");
    break;
  case T_VOID:
    strcpy(name,"void");
    break;
  case T_USER:
    strcpy(name,"USER");
    break;
  default :
    strcpy(name,"UNKNOWN");
    break;
  }
  type = t;
  is_pointer = 0;
  implicit_ptr = 0;
  qualifier = 0;
  is_reference = 0;
  status = 0;
  arraystr = 0;
  id = type_id++;
}
 	
DataType::DataType(DataType *t) {
    type = t->type;
    strcpy(name,t->name);
    is_pointer = t->is_pointer;
    implicit_ptr = t->implicit_ptr;
    qualifier = copy_string(t->qualifier);
    is_reference = t->is_reference;
    status = t->status;
    arraystr = copy_string(t->arraystr);
    id = t->id;
}

DataType::~DataType() {
    if (qualifier) delete qualifier;
    if (arraystr) delete arraystr;
}

// --------------------------------------------------------------------
// DataType::primitive()
//
// Turns a datatype into its bare-bones primitive type.  Rarely used,
// but sometimes used for typemaps.  Permanently alters the datatype!
// --------------------------------------------------------------------

void DataType::primitive() {
  switch(type) {
  case T_BOOL:
    strcpy(name,"bool");
    break;
  case T_INT: case T_SINT:
    strcpy(name,"int");
    break;
  case T_SHORT: case T_SSHORT:
    strcpy(name,"short");
    break;
  case T_LONG: case T_SLONG:
    strcpy(name,"long");
    break;
  case T_CHAR: 
    strcpy(name,"char");
    break;
  case T_SCHAR:
    strcpy(name,"signed char");
    break;
  case T_UINT:
    strcpy(name,"unsigned int");
    break;
  case T_USHORT:
    strcpy(name,"unsigned short");
    break;
  case T_ULONG:
    strcpy(name,"unsigned long");
    break;
  case T_UCHAR:
    strcpy(name,"unsigned char");
    break;
  case T_FLOAT:
    strcpy(name,"float");
    break;
  case T_DOUBLE:
    strcpy(name,"double");
    break;
  case T_VOID:
    strcpy(name,"void");
    break;
  case T_USER:
    strcpy(name,"USER");
    break;
  default:
    strcpy(name,"UNKNOWN");
    break;
  }
  //  if (is_pointer) {
  //    if (!((is_pointer == 1) && (type == T_CHAR))) {
  //      is_pointer = 1;
  //      strcpy(name,"POINTER");
  //    } 
  //  }

  implicit_ptr = 0;          // Gets rid of typedef'd pointers

  // Ditch qualifiers (const, volatile, etc...)

  if (qualifier) {
    delete qualifier;
    qualifier = 0;
  }
  qualifier = 0;
  status = 0;
}

// --------------------------------------------------------------------
// char *print_type()
//
// Print the datatype, but without qualifiers (ie. const, volatile)
// Returns a string containing the result.
//
// If a datatype is marked as an implicit ptr it means that is_pointer
// is at least one, but we don't print '*'.
//
// If the type status is STAT_REPLACETYPE, it means that we can't
// use this type as a valid type.  We'll substitute it's old name in.
// --------------------------------------------------------------------

char *DataType::print_type() {
  static String result[8];
  static int    ri = 0;

  DataType *t = this;
  
  if (status & STAT_REPLACETYPE) {
    t = new DataType(this);
    t->typedef_replace();   // Upgrade type
  }

  ri = ri % 8;
  result[ri] = "";
  result[ri] << t->name << " ";
  for (int i = 0; i < (t->is_pointer-t->implicit_ptr); i++)
    result[ri] << '*';

  if (status & STAT_REPLACETYPE) {
    delete t;
  };

  return result[ri++].get();

}

// --------------------------------------------------------------------
// char *print_full()
//
// Prints full type, with qualifiers.
// --------------------------------------------------------------------

char *DataType::print_full() {
  static String result[8];
  static int ri = 0;

  ri = ri % 8;
  result[ri] = "";
  if (qualifier)
    result[ri] << qualifier << " " << print_type();
  else 
    result[ri] << print_type();

  return result[ri++].get();

}

// --------------------------------------------------------------------
// char *print_real()
//
// Prints real type, with qualifiers and arrays if necessary.
// --------------------------------------------------------------------

char *DataType::print_real(char *local) {
  static String result[8];
  static int    ri = 0;
  int           oldstatus;

  oldstatus = status;
  status = status & (~STAT_REPLACETYPE);
  ri = ri % 8;
  result[ri] = "";
  if (arraystr) is_pointer--;
  result[ri] << print_full();
  if (local) result[ri] << local;
  if (arraystr) {
    result[ri] << arraystr;
    is_pointer++;
  }
  status = oldstatus;
  return result[ri++].get();
}

// --------------------------------------------------------------------
// char *print_cast()
//
// Prints a cast.  (Basically just a type but with parens added).
// --------------------------------------------------------------------

char *DataType::print_cast() {
  static String result[8];
  static int    ri = 0;

  ri = ri % 8;
  result[ri] = "";
  result[ri] << "(" << print_type() << ")";
  return result[ri++].get();

}

// --------------------------------------------------------------------
// char *print_arraycast()
//
// Prints a cast, but for array datatypes.  Super ugly, but necessary
// for multidimensional arrays.
// --------------------------------------------------------------------

char *DataType::print_arraycast() {
  static String result[8];
  static int    ri = 0;
  int  ndim;
  char *c;
  DataType     *t;

  t = this;
  if (status & STAT_REPLACETYPE) {
    t = new DataType(this);
    t->typedef_replace();   // Upgrade type
  }

  ri = ri % 8;
  result[ri] = "";

  if (t->arraystr) {
    ndim = 0;
    c = t->arraystr;
    while (*c) {
      if (*c == '[') ndim++;
      c++;
    }
    if (ndim > 1) {
      // a Multidimensional array.  Provide a special cast for it
      int oldstatus = status;
      t->status = t->status & (~STAT_REPLACETYPE);
      t->is_pointer--;
      result[ri] << "(" << t->print_type();
      t->is_pointer++;
      t->status = oldstatus;
      result[ri] << " (*)";
      c = t->arraystr;
      while (*c) {
	if (*c == ']') break;
	c++;
      }
      if (*c) c++;
      result[ri] << c << ")";
    }
  }
  if (status & STAT_REPLACETYPE) {
    delete t;
  }
  return result[ri++].get();
}

// --------------------------------------------------------------------
// char *print_mangle_default()
//
// Prints a mangled version of this datatype.   Used for run-time type
// checking in order to print out a "language friendly" version (ie. no
// spaces and no weird characters).
// --------------------------------------------------------------------

char *DataType::print_mangle_default() {
  static String result[8];
  static int    ri = 0;
  int   i;
  char *c;

  ri = ri % 8;
  result[ri] = "";
  c = name;

  result[ri] << '_';
  for (; *c; c++) {
      if (*c == ' ') result[ri] << '_';
      else result[ri] << *c;
    }
    if ((is_pointer-implicit_ptr)) result[ri] << '_';
    for (i = 0; i < (is_pointer-implicit_ptr); i++)
      result[ri] << 'p';

    return result[ri++].get();
}

// This is kind of ugly but needed for each language to support a
// custom name mangling mechanism.  (ie. Perl5).

char *DataType::print_mangle() {

  // Call into target language for name mangling.
  return lang->type_mangle(this);
}

// --------------------------------------------------------------------
// int DataType::array_dimensions()
//
// Returns the number of dimensions in an array or 0 if not an array.
// --------------------------------------------------------------------
int DataType::array_dimensions() {
  char *c;
  int  ndim = 0;

  if (!arraystr) return 0;
  c = arraystr;
  while (*c) {
    if (*c == '[') {
      ndim++;
    }
    c++;
  }
  return ndim;
}

// --------------------------------------------------------------------
// char *DataType::get_dimension(int n)
// 
// Returns a string containing the value specified for dimension n.
// --------------------------------------------------------------------

char *DataType::get_dimension(int n) {
  static String dim;
  char  *c;

  dim = "";
  if (n >= array_dimensions()) return dim; 
  
  // Attemp to locate the right dimension

  c = arraystr;
  while ((*c) && (n >= 0)) {
    if (*c == '[') n--;
    c++;
  }
  
  // c is now at start of array dimension
  if (*c) {
    while ((*c) && (*c != ']')) {
      dim << *c;
      c++;
    }
  }
  return dim;
}

// --------------------------------------------------------------------
// char *DataType::get_array()
//
// Returns the array string for a datatype.
// --------------------------------------------------------------------

char *DataType::get_array() {
  return arraystr;
}

// --------------------------------------------------------------------
// typedef support.  This needs to be scoped.
// --------------------------------------------------------------------

Hash *DataType::typedef_hash[MAXSCOPE];
int   DataType::scope = 0;            // Current scope

static Hash undefined_types;          // Hash table containing undefined datatypes.

// -----------------------------------------------------------------------------
// int DataType::check_defined()
//
// Checks to see if a datatype is defined.   If not, returns -1 and puts an entry
// into an internal hash table
// -----------------------------------------------------------------------------

int DataType::check_defined() {
  if (type == T_USER) {

    // Type might be in typedef hash.  Check for that
    int s = scope;
    while (s >= 0) {
      if (typedef_hash[s]->lookup(name)) return 0;
      s--;
    }

    // Nope.  Add as an undefined type and continue.

    char *st;
    st = copy_string(name);
    undefined_types.add(st,st);
    return -1;
  }
  return 0;
}

// -----------------------------------------------------------------------------
// void DataType::init_typedef() 
// 
// Inputs : None
//
// Output : None
//
// Side Effects : Initializes the typedef hash tables
// -----------------------------------------------------------------------------

void DataType::init_typedef() {
  int i;
  for (i = 0; i < MAXSCOPE; i++)
    typedef_hash[i] = 0;
  scope = 0;
  // Create a new hash
  typedef_hash[scope] = new Hash;
}

// --------------------------------------------------------------------
// void DataType::typedef_add(char *typename, int mode = 0)
//
// Adds this datatype to the typedef hash table.  mode is an optional
// flag that can be used to only add the symbol as a typedef, but not
// generate any support code for the SWIG typechecker.  This is used
// for some of the more obscure datatypes like function pointers,
// arrays, and enums.
// --------------------------------------------------------------------

void DataType::typedef_add(char *tname, int mode) {
  String name1,name2;
  DataType *nt, t1;
  void typeeq_addtypedef(char *name, char *eqname);

  // Check to see if this typedef already defined
  // We only check in the local scope.   C++ classes may make typedefs
  // that shadow global ones.

  if (typedef_hash[scope]->lookup(tname)) {
    fprintf(stderr,"%s : Line %d. Warning. Datatype %s already defined (2nd definition ignored).\n",
	    input_file, line_number, tname);
      return;
  }

  // Make a new datatype that we will place in our hash table

  nt = new DataType(this);
  nt->implicit_ptr = (is_pointer-implicit_ptr); // Record if mapped type is a pointer
  nt->is_pointer = (is_pointer-implicit_ptr); // Adjust pointer value to be correct
  nt->typedef_resolve();                   // Resolve any other mappings of this type
  //  strcpy(nt->name,tname);              // Copy over the new name
  
  // Add this type to our hash table
  typedef_hash[scope]->add(tname,(void *) nt);

  // Now add this type mapping to our type-equivalence table

  if (mode == 0) {
      if ((type != T_VOID) && (strcmp(name,tname) != 0)) {
	strcpy(t1.name,tname);
	name2 << t1.print_mangle();
	name1 << print_mangle();
	typeeq_addtypedef(name1,name2);
	typeeq_addtypedef(name2,name1);
      }
  }
  // Call into the target language with this typedef
  lang->add_typedef(this,tname);
}


// --------------------------------------------------------------------
// void DataType::typedef_resolve(int level = 0)
//
// Checks to see if this datatype is in the typedef hash and
// resolves it if necessary.   This will check all of the typedef
// hash tables we know about.
//
// level is an optional parameter that determines which scope to use.
// Usually this is only used with a bare :: operator in a datatype.
// 
// The const headache :
//
// Normally SWIG will fail if a const variable is used in a typedef
// like this :
//
//       typedef const char *String;
//
// This is because future occurrences of "String" will be treated like
// a char *, but without regard to the "constness".  To work around 
// this problem.  The resolve() method checks to see if these original 
// data type is const.  If so, we'll substitute the name of the original
// datatype instead.  Got it? Whew.   In a nutshell, this means that
// all future occurrences of "String" will really be "const char *".
// --------------------------------------------------------------------

void DataType::typedef_resolve(int level) {

  DataType *td;
  int       s = scope - level;

  while (s >= 0) {
    if ((td = (DataType *) typedef_hash[s]->lookup(name))) {
      type = td->type;
      is_pointer += td->is_pointer;
      implicit_ptr += td->implicit_ptr;
      status = status | td->status;

      // Check for constness, and replace type name if necessary

      if (td->qualifier) {
	if (strcmp(td->qualifier,"const") == 0) {
	  strcpy(name,td->name);
	  qualifier = copy_string(td->qualifier);
	  implicit_ptr -= td->implicit_ptr;
	}
      }
      return;
    }
    s--;
  }
  // Not found, do nothing
  return;
}

// --------------------------------------------------------------------
// void DataType::typedef_replace()
//
// Checks to see if this datatype is in the typedef hash and
// replaces it with the hash entry. Only applies to current scope.
// --------------------------------------------------------------------

void DataType::typedef_replace () {
  DataType *td;
  String temp;

  if ((td = (DataType *) typedef_hash[scope]->lookup(name))) {
    type = td->type;
    is_pointer = td->is_pointer;
    implicit_ptr -= td->implicit_ptr;
    strcpy(name, td->name);
    if (td->arraystr) {
      if (arraystr) {
	temp << arraystr;    
	delete arraystr;
      }
      temp << td->arraystr;
      arraystr = copy_string(temp);
    }
  }
  // Not found, do nothing
  return;
}

// ---------------------------------------------------------------
// int DataType::is_typedef(char *t)
//
// Checks to see whether t is the name of a datatype we know
// about.  Returns 1 if there's a match, 0 otherwise
// ---------------------------------------------------------------

int DataType::is_typedef(char *t) {
  int s = scope;
  while (s >= 0) {
    if (typedef_hash[s]->lookup(t)) return 1;
    s--;
  }
  return 0;
}

// ---------------------------------------------------------------
// void DataType::typedef_updatestatus(int newstatus)
//
// Checks to see if this datatype is in the hash table.  If
// so, we'll update its status.   This is sometimes used with
// typemap handling.  Only applies to current scope.
// ---------------------------------------------------------------

void DataType::typedef_updatestatus(int newstatus) {

  DataType *t;
  if ((t = (DataType *) typedef_hash[scope]->lookup(name))) {
    t->status = newstatus;
  }
}


// -----------------------------------------------------------------------------
// void DataType::merge_scope(Hash *h) 
// 
// Copies all of the entries in scope h into the current scope.  This is
// primarily done with C++ inheritance.
//
// Inputs : Hash table h.
//
// Output : None
//
// Side Effects : Copies all of the entries in h to current scope.
// -----------------------------------------------------------------------------

void DataType::merge_scope(Hash *h) {
  char  *key;
  DataType *t, *nt;

  if (h) {
    // Copy all of the entries in the given hash table to this new one
    key = h->firstkey();
    while (key) {
      //      printf("%s\n", key);
      t = (DataType *) h->lookup(key);
      nt = new DataType(t);
      typedef_hash[scope]->add(key,(void *) nt);
      key = h->nextkey();
    }
  }
}

// -----------------------------------------------------------------------------
// void DataType::new_scope(Hash *h = 0)
//
// Creates a new scope for handling typedefs.   This is used in C++ handling
// to create typedef local to a class definition. 
// 
// Inputs : h = Optional hash table scope (Used for C++ inheritance).
//
// Output : None
//
// Side Effects : Creates a new hash table and increments the scope counter
// -----------------------------------------------------------------------------

void DataType::new_scope(Hash *h) {
  scope++;
  typedef_hash[scope] = new Hash;

  if (h) {
    merge_scope(h);
  }
}

// -----------------------------------------------------------------------------
// Hash *DataType::collapse_scope(char *prefix) 
// 
// Collapses the current scope into the previous one, but applies a prefix to
// all of the datatypes.   This is done in order to properly handle C++ stuff.
// For example :
//
//      class Foo {
//         ... 
//         typedef double Real;
//      }
//
// will have a type mapping of "double --> Real" within the class itself. 
// When we collapse the scope, this mapping will become "double --> Foo::Real"
//
// Inputs : None
//
// Output : None
//
// Side Effects : Returns the hash table corresponding to the current scope
// -----------------------------------------------------------------------------

Hash *DataType::collapse_scope(char *prefix) {
  DataType *t,*nt;
  char     *key;
  char     *temp;
  Hash     *h;

  if (scope > 0) {
    if (prefix) {
      key = typedef_hash[scope]->firstkey();
      while (key) {
	t = (DataType *) typedef_hash[scope]->lookup(key);
	nt = new DataType(t);
	temp = new char[strlen(prefix)+strlen(key)+3];
	sprintf(temp,"%s::%s",prefix,key);
	//	printf("creating %s\n", temp);
	typedef_hash[scope-1]->add(temp,(void *) nt);
	delete temp;
	key = typedef_hash[scope]->nextkey();
      }
    }
    h = typedef_hash[scope];
    typedef_hash[scope] = 0;
    scope--;
    return h;
  }
  return (Hash *) 0;
}
		
// -------------------------------------------------------------
// Class equivalency lists
// 
// These are used to keep track of which datatypes are equivalent.
// This information can be dumped in tabular form upon completion
// for use in the pointer type checker.
//
// cast is an extension needed to properly handle multiple inheritance
// --------------------------------------------------------------

struct EqEntry {
  char *name;
  char *cast;
  EqEntry *next;
  char *sz;
};

static Hash typeeq_hash;
static int  te_init = 0;

void typeeq_init() {
  void typeeq_standard();
  te_init = 1;
  typeeq_standard();
}


// --------------------------------------------------------------
// typeeq_add(char *name, char *eqname, char *cast) 
//
// Adds a new name to the type-equivalence tables.
// Creates a new entry if it doesn't exit.
//
// Cast is an optional name for a pointer casting function.
// --------------------------------------------------------------

void typeeq_add(char *name, char *eqname, char *cast = 0) {
  EqEntry *e1,*e2;

  if (!te_init) typeeq_init();

  if (strcmp(name,eqname) == 0) return;   // If they're the same, forget it.
  
  // Search for "name" entry in the hash table

  e1 = (EqEntry *) typeeq_hash.lookup(name);

  if (!e1) {
    // Create a new entry
    e1 = new EqEntry;
    e1->name = copy_string(name);
    e1->next = 0;
    e1->cast = 0;
    // Add it to the hash table
    typeeq_hash.add(name,(void *) e1);
  }



  // Add new type to the list
  // We'll first check to see if it's already been added

  e2 = e1->next;
  while (e2) {
    if (strcmp(e2->name, eqname) == 0) {
      if (cast) 
	e2->cast = copy_string(cast);
      return;
    }
    e2 = e2->next;
  }

  e2 = new EqEntry;
  e2->name = copy_string(eqname);
  e2->cast = copy_string(cast);
  e2->next = e1->next;               // Add onto the linked list for name
  e1->next = e2;

}

// --------------------------------------------------------------
// typeeq_addtypedef(char *name, char *eqname) 
//
// Adds a new typedef declaration to the equivelency list.
// --------------------------------------------------------------

void typeeq_addtypedef(char *name, char *eqname) {
  EqEntry  *e1,*e2;

  if (!te_init) typeeq_init();

  // First we're going to add the equivalence, no matter what
  
  typeeq_add(name,eqname);

  // Now find the hash entry

  e1 = (EqEntry *) typeeq_hash.lookup(name);
  if (!e1) return;

  // Walk down the list and make other equivalences

  e2 = e1->next;
  while (e2) {
    if (strcmp(e2->name, eqname) != 0) {
      typeeq_add(e2->name, eqname,e2->cast);
      typeeq_add(eqname, e2->name,e2->cast);
    }
    e2 = e2->next;
  }
}

// ----------------------------------------------------------------
// void emit_ptr_equivalence(FILE *f)
//
// Dump out the pointer equivalence table to file.
//
// Changed to register datatypes with the type checker in order
// to support proper type-casting (needed for multiple inheritance)
// ----------------------------------------------------------------

void emit_ptr_equivalence(FILE *f) {

  EqEntry  *e1,*e2;
  void     typeeq_standard();

  if (!te_init) typeeq_init();

  fprintf(f,"\
/*\n\
 * These are the pointer type-equivalency mappings. \n\
 * (Used by the SWIG pointer type-checker).\n\
 */\n");

  e1 = (EqEntry *) typeeq_hash.first();
  while (e1) {
    e2 = e1->next;
    // Walk through the equivalency list
    while (e2) {
      if (e2->cast) 
	fprintf(f,"\t SWIG_RegisterMapping(\"%s\",\"%s\",%s);\n",e1->name,e2->name,e2->cast);
      else
	fprintf(f,"\t SWIG_RegisterMapping(\"%s\",\"%s\",0);\n",e1->name,e2->name);
      e2 = e2->next;
    }
    e1 = (EqEntry *) typeeq_hash.next();
  }
}


// ----------------------------------------------------------------
// void emit_ptr_equivalence(WrapperFunction &f)
//
// Dump out the pointer equivalence table to a wrapper function
//
// Changed to register datatypes with the type checker in order
// to support proper type-casting (needed for multiple inheritance)
// ----------------------------------------------------------------

void emit_ptr_equivalence(WrapperFunction &f) {

  EqEntry  *e1,*e2;
  void     typeeq_standard();

  if (!te_init) typeeq_init();

  f.code << "\
/*\n\
 * These are the pointer type-equivalency mappings. \n\
 * (Used by the SWIG pointer type-checker).\n\
 */\n";

  e1 = (EqEntry *) typeeq_hash.first();
  while (e1) {
    e2 = e1->next;
    // Walk through the equivalency list
    while (e2) {
      if (e2->cast) 
	f.code << tab4 << "SWIG_RegisterMapping(\"" << e1->name << "\",\"" << e2->name
	       << "\"," << e2->cast << ");\n";
      else
	f.code << tab4 << "SWIG_RegisterMapping(\"" << e1->name << "\",\"" << e2->name
	       << "\",0);\n";
      e2 = e2->next;
    }
    e1 = (EqEntry *) typeeq_hash.next();
  }
}

// ------------------------------------------------------------------------------
// typeeq_derived(char *n1, char *n2, char *cast=)
//
// Adds a one-way mapping between datatypes.
// ------------------------------------------------------------------------------

void typeeq_derived(char *n1, char *n2, char *cast=0) {
  DataType   t,t1;
  String     name,name2;
  EqEntry    *e1;

  if (!te_init) typeeq_init();

  strcpy(t.name,n1);
  strcpy(t1.name,n2);
  name << t.print_mangle();
  name2 << t1.print_mangle();
  typeeq_add(name,name2,cast);

  // Now find the hash entry

  e1 = (EqEntry *) typeeq_hash.lookup(name);

  // Walk down the list and make other equivalences

  /* I don't think this is necessary, but we'll keep this code in case

  e2 = e1->next;
  while (e2) {
    if (strcmp(e2->name, name2) != 0) {
      typeeq_add(e2->name, name2,e2->cast);
    }
    e2 = e2->next;
  }
  */

}

// ------------------------------------------------------------------------------
// typeeq_mangle(char *n1, char *n2, char *cast=)
//
// Adds a single type equivalence
// ------------------------------------------------------------------------------

void typeeq_mangle(char *n1, char *n2, char *cast=0) {
  DataType   t,t1;
  String     name,name2;

  if (!te_init) typeeq_init();

  strcpy(t.name,n1);
  strcpy(t1.name,n2);
  name << t.print_mangle();
  name2 << t1.print_mangle();
  typeeq_add(name,name2,cast);
}

// ------------------------------------------------------------------------------
// typeeq_standard(void)
//
// Generate standard type equivalences (well, pointers that can map into
// other pointers naturally).
// 
// -------------------------------------------------------------------------------
  
void typeeq_standard(void) {
  
  typeeq_mangle("int", "signed int");
  typeeq_mangle("int", "unsigned int");
  typeeq_mangle("signed int", "int");
  typeeq_mangle("unsigned int", "int");
  typeeq_mangle("short","signed short");
  typeeq_mangle("signed short","short");
  typeeq_mangle("short","unsigned short");
  typeeq_mangle("unsigned short","short");
  typeeq_mangle("long","signed long");
  typeeq_mangle("signed long","long");
  typeeq_mangle("long","unsigned long");
  typeeq_mangle("unsigned long","long");

}

// ------------------------------------------------------------------------------
// type_undefined_check(void)
//
// Checks the hash table for undefined datatypes and prints a warning message.
// -------------------------------------------------------------------------------

void type_undefined_check(void) {
  char *s;

  s = (char *) undefined_types.first();
  if (s) {
    fprintf(stderr,"The following datatypes were used, but undefined.\n");
    while (s) {
      fprintf(stderr,"     %s\n",s);
      s = (char *) undefined_types.next();
    }
  }
}

/*********************************************************************************
 *
 * -- Revision History
 * $Log: types.cxx,v $
 * Revision 1.35  1997/07/25 04:03:08  beazley
 * Added an extra field to print_real() so that we can declare variables
 * of array types and other things.
 *
 * Revision 1.34  1997/06/17 04:46:42  beazley
 * Minor changes.
 *
 * Revision 1.33  1997/05/28 17:01:41  beazley
 * Moved revision history to end.
 *
 * Revision 1.32  1997/05/24 04:14:15  beazley
 * Added support needed for default typemaps.
 *
 * Revision 1.31  1997/04/25 22:40:45  beazley
 * Minor fixes
 *
 * Revision 1.30  1997/04/18 04:07:22  beazley
 * Added a check for used, but undefined datatypes.
 *
 * Revision 1.29  1997/03/29 17:43:21  beazley
 * Added check functions for determining if datatypes have been
 * defined or not.
 *
 * Revision 1.28  1997/03/18 22:40:26  beazley
 * Added primitive() function.
 *
 * Revision 1.27  1997/03/18 17:16:48  beazley
 * Minor tweak to DataType(int t) constructor.
 *
 * Revision 1.26  1997/03/08 19:18:24  beazley
 * Added a few helper functions for dealing with arrays.
 *
 * Revision 1.25  1997/02/26 03:30:00  beazley
 * Removed a few compiler warnings.
 *
 * Revision 1.24  1997/02/16 20:15:29  beazley
 * Added type identifier to solve problems with typemap scoping
 *
 * Revision 1.23  1997/01/17 06:12:01  beazley
 * Made type string generation routines a little more robust
 *
 * Revision 1.22  1997/01/15 05:45:07  beazley
 * Added scoping mechanism to the typedef handler in order to properly
 * support C++ datatypes declared inside class definitions.
 *
 * Revision 1.21  1997/01/09 00:22:14  beazley
 * Fixed bug with default args.
 *
 * Revision 1.20  1997/01/08 01:24:51  beazley
 * Pre 1.1b3 checkin
 *
 * Revision 1.19  1997/01/06 17:08:17  beazley
 * Reorganized internal operation of this module.   Moved typedef
 * mechanism into a hash table.
 *
 * Revision 1.18  1996/12/26 22:31:43  beazley
 * Changed type-equivalence tables to allow a pointer-casting
 * function in preparation for multiple inheritance support
 *
 * Revision 1.17  1996/12/26 04:43:01  beazley
 * Changed type status bits to unsigned char to be more efficient.
 * Added support for read-only datatypes (primarily used for arrays)
 *
 * Revision 1.16  1996/11/12 19:49:29  beazley
 * Added Is_TypeDef() function to support improved parsing.
 *
 * Revision 1.15  1996/10/29 19:23:01  beazley
 * Fixed a bug in the copy constructor
 *
 * Revision 1.14  1996/10/22 16:42:32  beazley
 * Added support for 'bool' type (from David Fletcher).
 *
 * Revision 1.13  1996/09/07 18:37:54  dmb
 * Fixed bug in typedef mechanism.
 *
 * Revision 1.12  1996/08/27 05:06:46  dmb
 * Fixed bug in typedef
 *
 * Revision 1.11  1996/08/21 05:48:39  dmb
 * Made some changes to how default type-equivalences are added.
 *
 * Revision 1.10  1996/08/15 05:05:26  dmb
 * Fixed problem with default type-mappings and Perl5
 *
 * Revision 1.9  1996/08/12 01:51:36  dmb
 * Some changes for better support of C++ references
 *
 * Revision 1.8  1996/06/10 23:53:52  beazley
 * Fixed bug in typedef mechanism.
 *
 * Revision 1.7  1996/06/10  23:34:14  beazley
 * Took out annoying undefined type warning.
 *
 * Revision 1.6  1996/06/02  00:14:56  beazley
 * Added function to copy datatypes
 *
 * Revision 1.5  1996/05/28  23:17:26  beazley
 * Changed technique for handling typedef equivalences
 *
 * Revision 1.4  1996/05/22  20:20:21  beazley
 * Added functions to keep track of class equivalences.
 * (Used for pointer type-checking).
 *
 * Revision 1.3  1996/05/14  23:24:10  beazley
 * Added reference field.
 *
 * Revision 1.2  1996/04/14  15:24:48  dmb
 * Fixed headers.
 *
 * Revision 1.1  1996/03/28 02:47:28  beazley
 * Initial revision
 *
 * Revision 1.1  1996/03/16  06:29:42  beazley
 * Initial revision
 *
 * Revision 1.1  1996/02/15  22:36:27  beazley
 * Initial revision
 *
 *********************************************************************************/

    
