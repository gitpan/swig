
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

/*******************************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.1/SWIG/RCS/symbol.cxx,v 1.3 1997/05/28 16:59:48 beazley Exp $
 *
 * File : symbol.cxx
 *
 * Symbol table management.
 *
 *******************************************************************************/

// -----------------------------------------------------------------------------
// Symbol object
// -----------------------------------------------------------------------------

struct   Symbol {
  ~Symbol() {
    if (name) delete name;
    if (type) delete type;
    if (value) delete value;
  }
  char      *name;
  DataType  *type;        // Optional datatype
  char      *value;       // Optional value (for constant expressions)
};

static Hash    SymHash;   // SWIG Symbol table

// -----------------------------------------------------------------------------
// int add_symbol(char *name, DataType *type, char *value)
// 
// Adds a symbol to the symbol table. Returns -1 if symbol is already in the
// table.
//
// Inputs :
//          name     =  Symbol name
//          type     =  Datatype (for constants).  Optional.
//          value    =  Value string. Optional.
//
// Output : 0 on success, -1 if symbol already exists.
//
// Side Effects : None
// -----------------------------------------------------------------------------

int add_symbol(char *name, DataType *type, char *value) {

  Symbol *s;
  int ret;
  
  s = new Symbol;
  s->name = copy_string(name);
  if (type)
    s->type = new DataType(type);
  else s->type = (DataType *) 0;
  if (value) 
    s->value = copy_string(value);
  else s->value = (char *) 0;

  // Add this to the symbol table

  ret = SymHash.add(s->name, s);
  if (ret == -1) {
    delete s;
  } 
  return ret;
}

// -----------------------------------------------------------------------------
// int lookup_symbol(char *name)
// 
// Checks to see if a symbol is in the symbol table.
//
// Inputs : name   = Symbol name
//
// Output : 0 if not found, 1 if found.
//
// Side Effects : None
// -----------------------------------------------------------------------------

int lookup_symbol(char *name) {
  Symbol *s;

  s = (Symbol *) SymHash.lookup(name);
  if (s) return 1;
  else return 0;
}

// -----------------------------------------------------------------------------
// DataType *lookup_symtype(char *name)
// 
// Returns the datatype of a symbol or NULL if not found.
//
// Inputs : name   = Symbol name
//
// Output : Datatype of symbol, NULL if not found.
//
// Side Effects : None
// -----------------------------------------------------------------------------

DataType *lookup_symtype(char *name) {

  Symbol *s;

  s = (Symbol *) SymHash.lookup(name);
  if (s) return s->type;
  else return (DataType *) 0;
}

// -----------------------------------------------------------------------------
// char *lookup_symvalue(char *name)
// 
// Returns the value associate with a symbol.
//
// Inputs : name = Symbol name
//
// Output : Symbol value (or NULL if not present).
//
// Side Effects : None
// -----------------------------------------------------------------------------

char *lookup_symvalue(char *name) {

  Symbol *s;

  s = (Symbol *) SymHash.lookup(name);
  if (s) return s->value;
  else return (char *) 0;
}

// -----------------------------------------------------------------------------
// int update_symbol(char *name, DataType *type, char *value)
//
// Updates a symbol (or create it) in the hash table.
//
// Inputs : 
//          name   = Name of symbol
//          type   = Datatype of symbol (optional)
//          value  = Symbol value (optional)
//
// Output : 0
//
// Side Effects : None
// -----------------------------------------------------------------------------

int update_symbol(char *name, DataType *type, char *value) {

  Symbol *s;

  s = (Symbol *) SymHash.lookup(name);
  if (s) {
    if (s->type) delete s->type;
    if (s->value) delete s->value;
    if (type) 
      s->type = new DataType(type);
    else
      s->type = (DataType *) 0;
    if (value) 
      s->value = copy_string(value);
    else
      s->value = (char *) 0;
    return 0;
  } else {
    return add_symbol(name, type, value);
  }
}

// -----------------------------------------------------------------------------
// void remove_symbol(char *name)
// 
// Removes a symbol from the symbol table.
//
// Inputs : name = Symbol name.
//
// Output : None
//
// Side Effects : None
// -----------------------------------------------------------------------------

void remove_symbol(char *name) {
  SymHash.remove(name);
}

/*********************************************************************************
 *
 * -- Revision History
 * $Log: symbol.cxx,v $
 * Revision 1.3  1997/05/28 16:59:48  beazley
 * Moved revision history to end.
 *
 * Revision 1.2  1997/01/06 17:08:17  beazley
 * Cleaned up code.  Changed name of a few functions
 *
 * Revision 1.1  1996/11/12 19:49:29  beazley
 * Initial revision
 *********************************************************************************/
