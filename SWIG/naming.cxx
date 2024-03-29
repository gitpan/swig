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

#include "internal.h"
#include <limits.h>
#include <ctype.h>

// --------------------------------------------------------------------------------
// $Header: /home/beazley/SWIG/SWIG1.1/SWIG/RCS/naming.cxx,v 1.1 1997/06/17 04:47:11 beazley Exp $
//
// naming.cxx
//
// SWIG naming service.
//
// This module provides universal naming services for manufacturing function names.
// All language modules use this so it provides a convenient centralized
// mechanism for producing names.
// --------------------------------------------------------------------------------

// Structure for holding names

struct NamingScheme {
  char            *format;
  int             first;                // Scoping information
  int             last;                 // Scoping information
  NamingScheme    *next;
  NamingScheme(char *n) {
    format = copy_string(n);
    first = type_id;
    last = INT_MAX;
    next = 0;
  };
};

// Hash table containing naming data

static Hash naming_hash;

// Variable indicating naming scope

static naming_scope = -1;

//-----------------------------------------------------------------
// make_wrap_name(char *s)
//
// Takes the name at src, and converts it into a syntactically
// valid identifier name.   This is a hack to get the wrapper
// generator to support class member functions and other things.
//
// ie.  We can define a function name as obj->foo(),
// but we'll need to call the wrapper function something like
// _wrap_obj__foo()
//-----------------------------------------------------------------

void make_wrap_name(char *s) {

  char *c1 = s;
  int  i;

  for (i = 0; i < (int) strlen(s); i++, c1++) {
    if(!isalnum(*c1)) *c1 = '_';
  }
}

// --------------------------------------------------------------------------------
// int name_scope(int scope)
//
// Set the scope variable.  This is used to determine what naming scheme to
// use.    Returns the current value of the scope.
// --------------------------------------------------------------------------------

int name_scope(int scope) {
  int s = naming_scope;
  naming_scope = scope;
  return s;
}

// --------------------------------------------------------------------------------
// void name_register(char *method, char *format)
//
// Registers a new naming scheme.
// --------------------------------------------------------------------------------

void name_register(char *method, char *format) {
  NamingScheme *ns, *nns;

  ns = (NamingScheme *) naming_hash.lookup(method);
  if (ns) {
    naming_hash.remove(method);
  }

  nns = new NamingScheme(format);      // Create a new naming scheme
  if (ns) ns->last = type_id;
  nns->next = ns;

  naming_hash.add(method,nns);
};

// --------------------------------------------------------------------------------
// char *name_getformat(char *method)
//
// Looks up a naming scheme in the hash table.  The scope of the name should have
// been set prior to calling this.  If not set, we just use the last name entered.
// Returns the format string or NULL if no name has been set.
// --------------------------------------------------------------------------------

static char *name_getformat(char *method) {
  
  NamingScheme *ns;
  int scope;
  if (naming_scope == -1) scope = type_id;
  else scope = naming_scope;

  ns = (NamingScheme *) naming_hash.lookup(method);
  while (ns) {
    if ((ns->first <= scope) && (scope < ns->last))
      return ns->format;
    ns = ns->next;
  }
  return 0;
}

// --------------------------------------------------------------------------------
// char *name_wrapper(char *fname, char *prefix, int suppress)
//
// Returns the name of a wrapper function.  The following variables are
// available :
//
//         %f          -> fname
//         %p          -> prefix
//         %l          -> language
//
// By default a wrapper function gets the name _wrap_prefixfname.
//
// --------------------------------------------------------------------------------

char *name_wrapper(char *fname, char *prefix, int suppress) {
  static String fmt;
  char   *f;

  f = name_getformat("wrapper");
  if (!f) {
    f = "_wrap_%p%f";                  // Default wrapper name
  }
  fmt = f;
  fmt.replace("%f",fname);
  fmt.replace("%l",typemap_lang);
  fmt.replace("%p",prefix);
  if (!suppress)
    make_wrap_name(fmt);
  return fmt;
}


// --------------------------------------------------------------------------------
// char *name_member(char *fname, char *classname, int suppress)
//
// Returns the name of a method function.  The following variables are
// available :
//
//         %f          -> fname
//         %c          -> classname
//         %l          -> language
//
// By default, the name of a method is given as Classname_method.
// --------------------------------------------------------------------------------

char *name_member(char *fname, char *classname, int suppress) {
  static String fmt;
  char   *f;

  f = name_getformat("member");
  if (!f) {
    f = "%c_%f";
  }
  fmt = f;
  fmt.replace("%f",fname);
  fmt.replace("%l",typemap_lang);
  fmt.replace("%c",classname);
  if (!suppress)
    make_wrap_name(fmt);
  return fmt;
}


// --------------------------------------------------------------------------------
// char *name_get(char *vname, int suppress)
//
// Returns the name of the accessor function used to get a variable.
//
//         %v          -> variable name
//
// --------------------------------------------------------------------------------

char *name_get(char *vname, int suppress) {
  static String fmt;
  char   *f;

  f = name_getformat("get");
  if (!f) {
    f = "%v_get";
  }
  fmt = f;
  fmt.replace("%v",vname);
  if (!suppress)
    make_wrap_name(fmt);
  return fmt;
}

// --------------------------------------------------------------------------------
// char *name_set(char *vname, int suppress)
//
// Returns the name of the accessor function used to set a variable.
//
//         %v          -> variable name
// --------------------------------------------------------------------------------

char *name_set(char *vname, int suppress) {
  static String fmt;
  char   *f;

  f = name_getformat("set");
  if (!f) {
    f = "%v_set";
  }
  fmt = f;
  fmt.replace("%v",vname);
  if (!suppress)
    make_wrap_name(fmt);
  return fmt;
}
  

// --------------------------------------------------------------------------------
// char *name_construct(char *classname, int suppress)
//
// Returns the name of the accessor function used to create an object.
// By default this is "new_classname"
//
//         %c          -> classname
//         %l          -> language
//
// --------------------------------------------------------------------------------

char *name_construct(char *classname, int suppress) {
  static String fmt;
  char   *f;

  f = name_getformat("construct");
  if (!f) {
    f = "new_%c";
  }
  fmt = f;
  fmt.replace("%l",typemap_lang);
  fmt.replace("%c",classname);
  if (!suppress)
    make_wrap_name(fmt);
  return fmt;
}
  

// --------------------------------------------------------------------------------
// char *name_destroy(char *classname, int suppress)
//
// Returns the name of the accessor function used to destroy an object.
// By default this is "delete_classname"
//
//         %c          -> classname
//         %l          -> language
//
// --------------------------------------------------------------------------------

char *name_destroy(char *classname, int suppress) {
  static String fmt;
  char   *f;

  f = name_getformat("destroy");
  if (!f) {
    f = "delete_%c";
  }
  fmt = f;
  fmt.replace("%l",typemap_lang);
  fmt.replace("%c",classname);
  if (!suppress)
    make_wrap_name(fmt);
  return fmt;
}

/*********************************************************************************
 * -- Revision History
 *
 * $Log: naming.cxx,v $
 * Revision 1.1  1997/06/17 04:47:11  beazley
 * Initial revision
 *
 *
 *********************************************************************************/




