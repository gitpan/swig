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
 **************************************************************************/

/* ------------------------------------------------------------------------
   $Header: /home/beazley/SWIG/SWIG1.1/SWIG/RCS/parms.cxx,v 1.12 1997/06/23 21:18:00 beazley Exp $

   parms.cxx

   This file is used to manage function parameters and parameter lists.
   Rewritten (10/27) to solve a bunch of problems with memory management
   and proper cleanup of things.
   ------------------------------------------------------------------------ */

#include "swig.h"

// ------------------------------------------------------------------------
// Parm::Parm(DataType *type, char *n)
//
// Create a new parameter from datatype 'type' and name 'n'.
// Copies will be made of type and n, unless they aren't specified.
// ------------------------------------------------------------------------

Parm::Parm(DataType *type, char *n) {
  if (type) {
    t = new DataType(type);
  } else {
    t = 0;
  }
  name = copy_string(n);
  call_type = 0;
  defvalue = 0;
  ignore = 0;
  objc_separator = 0;
}

// ------------------------------------------------------------------------
// Parm::Parm(Parm *p)
//
// Make a copy of a parameter
// ------------------------------------------------------------------------

Parm::Parm(Parm *p) {
  if (p->t) t = new DataType(p->t);
  name = copy_string(p->name);
  call_type = p->call_type;
  defvalue = copy_string(p->defvalue);
  ignore = p->ignore;
  objc_separator = copy_string(p->objc_separator);
}

// ------------------------------------------------------------------------
// Parm::~Parm()
//
// Destroy a parameter
// ------------------------------------------------------------------------

Parm::~Parm() {
  if (t) delete t;
  if (name) delete name;
  if (defvalue) delete defvalue;
  if (objc_separator) delete objc_separator;
}

/********************************************************************
 class ParmList

 These functions are used to manipulate lists of parameters
 ********************************************************************/

// ------------------------------------------------------------------
// ParmList::ParmList()
//
// Create a new (empty) parameter list
// ------------------------------------------------------------------

ParmList::ParmList() {

  nparms = 0;
  maxparms = MAXPARMS;
  parms = new Parm *[maxparms];     // Create an array of parms
  for (int i = 0; i < MAXPARMS; i++)
    parms[i] = (Parm *) 0;
}

// ------------------------------------------------------------------
// ParmList::ParmList(ParmList *l)
//
// Make a copy of parameter list
// ------------------------------------------------------------------

ParmList::ParmList(ParmList *l) {
  int i;

  if (l) {
    nparms = l->nparms;
    maxparms = l->maxparms;
    parms = new Parm *[maxparms];
  
    for (i = 0; i < maxparms; i++) {
      if (l->parms[i])
	parms[i] = new Parm(l->parms[i]);
      else
	parms[i] = 0;
    }

  } else {
    nparms = 0;
    maxparms = MAXPARMS;
    parms = new Parm *[maxparms];     // Create an array of parms

    for (i = 0; i < MAXPARMS; i++)
      parms[i] = (Parm *) 0;
  }
}

// ------------------------------------------------------------------
// ParmList::~ParmList()
//
// Delete a parameter list
// ------------------------------------------------------------------
  
ParmList::~ParmList() {
  for (int i = 0; i < maxparms; i++) {
    if (parms[i]) delete parms[i];
  }
}


// ------------------------------------------------------------------
// void ParmList::moreparms()               (PRIVATE)
//
// Doubles the amount of parameter memory available.  
// ------------------------------------------------------------------

void ParmList::moreparms() {
  Parm  **newparms;
  int     i;

  newparms = new Parm *[maxparms*2];
  for (i = 0; i < 2*maxparms; i++)
    newparms[i] = (Parm *) 0;
  for (i = 0; i < maxparms; i++) {
    newparms[i] = parms[i];
  }
  maxparms = 2*maxparms;
  delete parms;
  parms = newparms;
}

// ------------------------------------------------------------------
// void ParmList::append(Parm *p)
//
// Add a new parameter to the end of a parameter list
// ------------------------------------------------------------------

void ParmList::append(Parm *p) {

  if (nparms == maxparms) moreparms();

  // Add parm onto the end 

  parms[nparms] = new Parm(p);
  nparms++;
}

// ------------------------------------------------------------------
// void ParmList::insert(Parm *p, int pos)
//
// Inserts a parameter at position pos.   Parameters are inserted
// *before* any existing parameter at position pos.
// ------------------------------------------------------------------

void ParmList::insert(Parm *p, int pos) {

  // If pos is out of range, we'd better fix it

  if (pos < 0) pos = 0;
  if (pos > nparms) pos = nparms;

  // If insertion is going to need more memory, take care of that now

  if (nparms >= maxparms) moreparms();

  // Now shift all of the existing parms to the right

  for (int i = nparms; i > pos; i--) {
    parms[i] = parms[i-1];
  }

  // Set new parameter
  
  parms[pos] = new Parm(p);
  nparms++;

}
  
// ------------------------------------------------------------------
// void ParmList::del(int pos)
//
// Deletes the parameter at position pos.
// ------------------------------------------------------------------

void ParmList::del(int pos) {

  if (nparms <= 0) return;
  if (pos < 0) pos = 0;
  if (pos >= nparms) pos = nparms-1;

  // Delete the parameter (if it exists)

  if (parms[pos]) delete parms[pos];

  // Now slide all of the parameters to the left

  for (int i = pos; i < nparms-1; i++) {
    parms[i] = parms[i+1];
  }
  nparms--;

}

// ------------------------------------------------------------------
// Parm *ParmList::get(int pos)
//
// Gets the parameter at location pos.  Returns 0 if invalid
// position.
// ------------------------------------------------------------------

Parm *ParmList::get(int pos) {

  if ((pos < 0) || (pos >= nparms)) return 0;
  return parms[pos];
}

// ------------------------------------------------------------------
// int ParmList::numopt()
//
// Gets the number of optional arguments. 
// ------------------------------------------------------------------
int ParmList::numopt() {
  int  n = 0;
  int  state = 0;

  for (int i = 0; i < nparms; i++) {
    if (parms[i]->defvalue) {
      n++;
      state = 1;
    } else if (typemap_check("default",typemap_lang,parms[i]->t,parms[i]->name)) {
      n++;
      state = 1;
    } else if (typemap_check("ignore",typemap_lang,parms[i]->t,parms[i]->name)) {
      n++;
    } else if (typemap_check("build",typemap_lang,parms[i]->t,parms[i]->name)) {
      n++;
    } else {
      if (state) {
	fprintf(stderr,"%s : Line %d.  Argument %d must have a default value!\n", input_file,line_number,i+1);
      }
    }
  }
  return n;
}

// ------------------------------------------------------------------
// int ParmList::numarg()
//
// Gets the number of arguments
// ------------------------------------------------------------------
int ParmList::numarg() {
  int  n = 0;

  for (int i = 0; i < nparms; i++) {
    if (!parms[i]->ignore)
      n++;
  } 
  return n;
}

// ------------------------------------------------------------------
// Parm &ParmList::operator[](int n)
//
// Returns parameter n in the parameter list.   May generate
// an error if that parameter is out of range.
// ------------------------------------------------------------------

Parm &ParmList::operator[](int n) {
  
  if ((n < 0) || (n >= nparms)) {
    fprintf(stderr,"ParmList : Fatal error.  subscript out of range in ParmList.operator[]\n");
    SWIG_exit(1);
  }

  return *parms[n];
}

// ---------------------------------------------------------------------
// Parm * ParmList::get_first()
//
// Returns the first item on a parameter list.
// ---------------------------------------------------------------------

Parm *ParmList::get_first() {
  current_parm = 0;
  if (nparms > 0) return parms[current_parm++];
  else return (Parm *) 0;
}

// ----------------------------------------------------------------------
// Parm *ParmList::get_next()
//
// Returns the next item on the parameter list.
// ----------------------------------------------------------------------

Parm * ParmList::get_next() {
  if (current_parm >= nparms) return 0;
  else return parms[current_parm++];
}

// ---------------------------------------------------------------------
// void ParmList::print_types(FILE *f)
//
// Prints a comma separated list of all of the parameter types.
// This is for generating valid C prototypes.   Has to do some
// manipulation of pointer types depending on how the call_type
// variable has been set.
// ----------------------------------------------------------------------

void ParmList::print_types(FILE *f) {

  int   is_pointer;
  int   pn;
  pn = 0;
  while(pn < nparms) {
    is_pointer = parms[pn]->t->is_pointer;
    if (parms[pn]->t->is_reference) {
      if (parms[pn]->t->is_pointer) {
	parms[pn]->t->is_pointer--;
	fprintf(f,"%s&", parms[pn]->t->print_real());
	parms[pn]->t->is_pointer++;
      } else {
	fprintf(f,"%s&", parms[pn]->t->print_real());
      }
    } else {
      if (parms[pn]->call_type & CALL_VALUE) parms[pn]->t->is_pointer++;
      if (parms[pn]->call_type & CALL_REFERENCE) parms[pn]->t->is_pointer--;
      fprintf(f,"%s", parms[pn]->t->print_real());
      parms[pn]->t->is_pointer = is_pointer;
    }
    pn++;
    if (pn < nparms)
      fprintf(f,",");
  }
}


// ---------------------------------------------------------------------
// void ParmList::print_types(String &f)
//
// Generates a comma separated list of function types.   Is used in
// C++ code generation when generating hash keys and for function overloading.
// ----------------------------------------------------------------------

void ParmList::print_types(String &f) {

  int   is_pointer;
  int   pn;
  pn = 0;
  while(pn < nparms) {
    is_pointer = parms[pn]->t->is_pointer;
    if (parms[pn]->t->is_reference) {
      if (parms[pn]->t->is_pointer) {
	parms[pn]->t->is_pointer--;
	f << parms[pn]->t->print_real() << "&";
	parms[pn]->t->is_pointer++;
      } else {
	f << parms[pn]->t->print_real() << "&";
      }
    } else {
      if (parms[pn]->call_type & CALL_VALUE) parms[pn]->t->is_pointer++;
      if (parms[pn]->call_type & CALL_REFERENCE) parms[pn]->t->is_pointer--;
      f << parms[pn]->t->print_real();
      parms[pn]->t->is_pointer = is_pointer;
    }
    pn++;
    if (pn < nparms)
      f << ",";
  }
}


// ---------------------------------------------------------------------
// void ParmList::print_args(FILE *f)
//
// Prints a comma separated list of all of the parameter arguments.
// ----------------------------------------------------------------------

void ParmList::print_args(FILE *f) {

  int   is_pointer;
  int   pn;
  pn = 0;
  while(pn < nparms) {
    is_pointer = parms[pn]->t->is_pointer;
    if (parms[pn]->t->is_reference) {
      if (parms[pn]->t->is_pointer) {
	parms[pn]->t->is_pointer--;
	fprintf(f,"%s&", parms[pn]->t->print_full());
	parms[pn]->t->is_pointer++;
      } else {
	fprintf(f,"%s&", parms[pn]->t->print_full());
      }
    } else {
      if (parms[pn]->call_type & CALL_VALUE) parms[pn]->t->is_pointer++;
      if (parms[pn]->call_type & CALL_REFERENCE) parms[pn]->t->is_pointer--;
      fprintf(f,"%s", parms[pn]->t->print_full());
      parms[pn]->t->is_pointer = is_pointer;
    }
    fprintf(f,"%s",parms[pn]->name);
    pn++;
    if (pn < nparms)
      fprintf(f,",");
  }
}

// -------------------------------------------------------------------
// int check_defined()
//
// Checks to see if all of the datatypes are defined.
// -------------------------------------------------------------------

int ParmList::check_defined() {
  int   a = 0;
  int   i;
  for (i = 0; i < nparms; i++) {
    if (parms[i]) {
      a+=parms[i]->t->check_defined();
    }
  }
  if (a) return 1;
  else return 0;
}


// -------------------------------------------------------------------
// void ParmList::sub_parmnames(String &s)
//
// Given a string, this function substitutes all of the parameter
// names with their internal representation.   Used in very special
// kinds of typemaps.
// -------------------------------------------------------------------

void ParmList::sub_parmnames(String &s) {
  Parm *p;  
  extern char *emit_local(int i);
  for (int i = 0; i < nparms; i++) {
    p = get(i);
    if (strlen(p->name) > 0) {
      s.replaceid(p->name, emit_local(i));
    }
  }
}

#ifdef OLD
// -------------------------------------------------------------------
// void ParmList::make_string(FILE *f)
//
// Makes a string containing the parameters of a function
// -----------------------------------------------------------------

void ParmList::make_string(FILE *f)
{
  Pnode *pn;
  pn = head->next;
  while (pn != z) {
    if (pn->p->name == 0) fprintf(f,"%s",pn->p->t->print_type());
    else {
      if (strlen(pn->p->name) > 0)
	fprintf(f,"%s",pn->p->name);
      else
	fprintf(f,"%s",pn->p->t->print_type());
    }
    if (pn->next != z)
      fprintf(f,",");
    pn = pn->next;
  }
}

#endif

/* ------------------------------------------------------------------------

   --- Revision history
   $Log: parms.cxx,v $
   Revision 1.12  1997/06/23 21:18:00  beazley
   Added objc_separator parameter to Parm.

   Revision 1.11  1997/06/17 04:49:58  beazley
   Got rid of unused function.

   Revision 1.10  1997/05/28 16:17:59  beazley
   Moved revision history to end.

   Revision 1.9  1997/05/24 04:17:53  beazley
   Added sub_parmnames() method used for the "build" typemap.

   Revision 1.8  1997/03/29 17:42:42  beazley
   Added mechanism for checking definitions

   Revision 1.7  1997/03/21 00:11:28  beazley
   Changed exit() to SWIG_exit()

   Revision 1.6  1997/02/16 20:15:29  beazley
   Added support for ignored and default arguments

   Revision 1.5  1997/01/08 01:24:51  beazley
   Pre 1.1b3 checkin

   Revision 1.4  1997/01/06 17:08:17  beazley
   Added field for default argument values

   Revision 1.3  1996/12/26 04:43:01  beazley
   Fixed some bugs related to C++ references

   Revision 1.2  1996/10/30 05:42:06  beazley
   Fixed some C++ portability problems

   Revision 1.1  1996/10/29 19:21:58  beazley
   Initial revision

   ------------------------------------------------------------------------ */





  
  



  



