
/**********************************************************************
 * Simplified Wrapper and Interface Generator  (SWIG)
 * Version 2.0 (pre-pre-pre Alpha)
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

// ------------------------------------------------------------------
// wrapfunc.cxx
//
// Created : June 22, 1996
// Dave Beazley
//
// This file defines a class for writing wrappers.  Instead of worrying
// about I/O problems, this wrapper class can be used to write functions
// out of order.
// 
// Defines 3 string objects.
//     def      - Wrapper function definition (function name and arguments)
//     locals   - Local variable definitions
//     code     - The actual wrapper function code
//
//-------------------------------------------------------------------

#include "internal.h"
#include <ctype.h>

// -------------------------------------------------------------------
// Print out a wrapper function.
//
// -------------------------------------------------------------------

void WrapperFunction::print(FILE *f) {
  fprintf(f,"%s\n",def.get());
  fprintf(f,"%s\n",locals.get());
  fprintf(f,"%s\n",code.get());
}

// -------------------------------------------------------------------
// Print out a wrapper function.
//
// -------------------------------------------------------------------

void WrapperFunction::print(String &f) {
  f << def << "\n"
    << locals << "\n"
    << code << "\n";
}

// -------------------------------------------------------------------
// Safely add a local variable.
//
// Maintains a hash table to prevent double adding.
// -------------------------------------------------------------------

void WrapperFunction::add_local(char *type, char *name, char *defarg) {
  char *stored_type;
  char *new_type;
  char temp[256],*c,*t;

  new_type = new char[strlen(type)+1];
  strcpy(new_type,type);

  // Figure out what the name of this variable is

  c = name;
  t = temp;
  while ((isalnum(*c) || (*c == '_') || (*c == '$')) && (*c)) {
    *(t++) = *c;
    c++;
  }
  *t = 0;
  if (h.add(temp,new_type,WrapperFunction::del_type) == -1) {
    // Check to see if a type mismatch has occurred
    stored_type = (char *) h.lookup(temp);
    if (strcmp(type,stored_type) != 0) 
      fprintf(stderr,"Error. Type %s conflicts with previously declared type of %s\n",
	      type, stored_type);
    return;    
  }

  // Successful, write some wrapper code

  if (!defarg)
    locals << tab4 << type << " " << name << ";\n";
  else
    locals << tab4 << type << " " << name << " = " << defarg << ";\n";
}


// -------------------------------------------------------------------
// char *WrapperFunction::new_local(char *type, char *name, char *defarg) {
//
// A safe way to add a new local variable.  type and name are used as
// a starting point, but a new local variable will be created if these
// are already in use.
// -------------------------------------------------------------------

char *WrapperFunction::new_local(char *type, char *name, char *defarg) {
  char *new_type;
  static String new_name;
  char *c;
  new_type = new char[strlen(type)+1];

  strcpy(new_type,type);
  new_name = "";
  c = name;
  for (c = name; ((isalnum(*c) || (*c == '_') || (*c == '$')) && (*c)); c++)
    new_name << *c;

  // Try to add a new local variable
  if (h.add(new_name,new_type,WrapperFunction::del_type) == -1) {
    // Local variable already exists, try to generate a new name
    int i = 0;
    new_name = "";
    // This is a little funky.  We copy characters until we reach a nonvalid
    // identifier symbol, add a number, then append the rest.   This is
    // needed to properly handle arrays.
    c = name;
    for (c = name; ((isalnum(*c) || (*c == '_') || (*c == '$')) && (*c)); c++)
      new_name << *c;
    new_name << i;
    while (h.add(new_name,new_type,WrapperFunction::del_type) == -1) {
      i++;
      c = name;
      new_name = "";
      for (c = name; ((isalnum(*c) || (*c == '_') || (*c == '$')) && (*c)); c++)
	new_name << *c;
      new_name << i;
    }
  }
  new_name << c;
  // Successful, write some wrapper code
  if (!defarg)
    locals << tab4 << type << " " << new_name << ";\n";
  else
    locals << tab4 << type << " " << new_name << " = " << defarg << ";\n";

  // Need to strip off the array symbols now

  c = new_name.get();
  while ((isalnum(*c) || (*c == '_') || (*c == '$')) && (*c))
    c++;
  *c = 0;
  return new_name;
}

// ------------------------------------------------------------------
// static WrapperFunction::del_type(void *obj)
//
// Callback function used when cleaning up the hash table.
// ------------------------------------------------------------------

void WrapperFunction::del_type(void *obj) {
  delete (char *) obj;
}
    
/*********************************************************************************
 * --- Revision History
 *
 * $Log: wrapfunc.cxx,v $
 * Revision 1.10  1997/06/17 04:49:26  beazley
 * Minor changes.
 *
 * Revision 1.9  1997/05/28 17:02:16  beazley
 * Added revision history
 *
 *********************************************************************************/
  
