
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

/**********************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.2/Modules/RCS/pycpp.cxx,v 1.24 1997/07/27 20:31:19 beazley Exp $
 *
 * pycpp.cxx
 *
 * This module contains code to generate Python shadow classes of C/C++
 * objects.  
 **************************************************************************/


#include "swig.h"
#include "python.h"

static  String   *setattr;
static  String   *getattr;
static  String   *pyclass;
static  String   *construct;
static  String   *cinit;
static  String   *additional;
static  int       have_constructor;
static  int       have_destructor;
static  int       have_getattr;
static  int       have_setattr;
static  int       have_repr;
static  char     *class_name;
static  char     *class_type;
static  char     *real_classname;
static  String   *base_class;
static  String   base_getattr;
static  String   base_setattr;
static  int      class_renamed = 0;

// --------------------------------------------------------------------------
// PYTHON::cpp_open_class(char *classname, char *rname, char *ctype, int strip)
//
// Opens a new C++ class or structure.
// --------------------------------------------------------------------------

void PYTHON::cpp_open_class(char *classname, char *rname, char *ctype, int strip) {

  char  temp[256];

  this->Language::cpp_open_class(classname, rname, ctype, strip);
  
  if (shadow) {
    /* Create new strings for building up a wrapper function */
    
    setattr   = new String();
    getattr   = new String();
    pyclass   = new String();
    construct = new String();
    cinit     = new String();
    additional= new String();
    base_class = 0;
    base_getattr = "";
    base_setattr = "";

    
    //  *pyclass << "class " << rname << ":\n";
    *setattr << tab4 << "def __setattr__(self,name,value):\n";
    *getattr << tab4 << "def __getattr__(self,name):\n";
    have_constructor = 0;
    have_destructor = 0;
    have_getattr = 0;
    have_setattr = 0;
    have_repr = 0;
    if (rname) {
      class_name = copy_string(rname);
      class_renamed = 1;
    } else {
      class_name = copy_string(classname);
      class_renamed = 0;
    }
  }

  real_classname = copy_string(classname);
  class_type = copy_string(ctype);

  // Build up the hash table
  hash.add(real_classname,copy_string(class_name));
  
  sprintf(temp,"%s %s", class_type, real_classname);
  hash.add(temp,copy_string(class_name));

}

// --------------------------------------------------------------------------
// PYTHON::cpp_member_func(char *name, char *iname, DataType *t, ParmList *l)
//
// Creates a C++ member function
// --------------------------------------------------------------------------

void PYTHON::cpp_member_func(char *name, char *iname, DataType *t, ParmList *l) {

  Parm *p;
  int   i;
  char *realname;
  int   oldshadow;
  int   pcount;
  int   numopt;
  int   have_optional;

  String cname = "python:";
  String translate = "";

  // Create the default member function
  
  oldshadow = shadow;    // Disable shadowing when wrapping member functions
  if (shadow) shadow = shadow | PYSHADOW_MEMBER;
  this->Language::cpp_member_func(name,iname,t,l);
  shadow = oldshadow;
  if (shadow) {
    if (!iname)
      realname = name;
    else
      realname = iname;
    
    // Check to see if we've already seen this
    cname << class_name << "::" << realname;
    if (add_symbol(cname.get(), 0,0)) {
      return;   // Forget it, already saw it
    }
    
    if (strcmp(realname,"__repr__") == 0) 
      have_repr = 1;

    // Now add it to the class
    
    *pyclass << tab4 << "def " << realname << "(self";
    p = l->get_first();
    if (p) 
      if (!p->ignore) *pyclass << ",";
    i = 0;
    pcount = l->nparms;
    numopt = l->numopt();
    have_optional = 0;
    while(p) {
      if (!p->ignore) {
	if (i >= pcount-numopt) {
	  have_optional = 1;
	  *pyclass << "*args";
	  shadow_defargs(p,l,i,pcount,numopt,translate,tab8);
	  break;
	}
	*pyclass << "arg" << i;
	p = l->get_next();
	if (p)
	  if (!p->ignore)
	    *pyclass << ",";
	i++;
      } else {
	p = l->get_next();
	if (p)
	  //	  if ((i > 0) && (!p->ignore))
	  if (!p->ignore)
	    *pyclass << ",";
      }
    }

    *pyclass << "):\n";
    
    // Create a doc string
    if (docstring && doc_entry) {
      *pyclass << tab8 << "\"\"\"" << add_docstring(doc_entry) << "\"\"\"\n";
    }
    *pyclass << translate;
    *pyclass << tab8;
    //    if ((t->type != T_VOID) || (t->is_pointer > 0))
    *pyclass << "val = ";
    
    //if ((hash.lookup(t->name)) && (t->is_pointer <=1))
    //      *pyclass << (char *) hash.lookup(t->name) << "Ptr(";
    if (have_optional) {
      *pyclass << "apply(" << module << "." << name_member(realname,class_name) << ",(self.this";
    } else {
      *pyclass << module << "." << name_member(realname,class_name) << "(self.this";
    }
    p = l->get_first();
    i = 0;
    if (p) {
      if (!p->ignore) *pyclass << ",";
    }
    while(p) {
      if (!p->ignore) {
	if (i >= (pcount - numopt)) {
	  *pyclass << ")+args";
	  break;
	}
	*pyclass << "arg" << i;
	if ((hash.lookup(p->t->name)) && (p->t->is_pointer <= 1))
	  *pyclass << ".this";
	p = l->get_next();
	if (p)
	  if (!p->ignore)
	    *pyclass << ",";
	i++;
      } else {
	p = l->get_next();
	if (p) 
	  if (!p->ignore)
	    *pyclass << ",";
      }
    }

    //if ((hash.lookup(t->name)) && (t->is_pointer <=1))
    //      *pyclass << "))\n";
    //    else
    *pyclass << ")\n";

    // Check to see if the return type is an object
    if ((hash.lookup(t->name)) && (t->is_pointer <= 1)) {
      if (!typemap_check("out",typemap_lang,t,name_member(realname,class_name))) {
	if (!have_output) {
	  *pyclass << tab8 << "val = " << (char *) hash.lookup(t->name) << "Ptr(val)\n";
	  if (((hash.lookup(t->name)) && (t->is_pointer < 1)) ||
	      ((hash.lookup(t->name)) && (t->is_pointer == 1) && NewObject))
	    *pyclass << tab8 << "val.thisown = 1\n";
	} else {
	  // Do nothing!
	}
#ifdef OLD_OUTPUT
	if (have_output) {
	  *pyclass << tab8 << "val = [" << (char *) hash.lookup(t->name) << "Ptr(val[0])] + val[1:]\n";
	  if (((hash.lookup(t->name)) && (t->is_pointer < 1)) ||
	      ((hash.lookup(t->name)) && (t->is_pointer == 1) && NewObject))
	    *pyclass << tab8 << "val[0].thisown = 1\n";
	} else {
	  *pyclass << tab8 << "val = " << (char *) hash.lookup(t->name) << "Ptr(val)\n";
	  if (((hash.lookup(t->name)) && (t->is_pointer < 1)) ||
	      ((hash.lookup(t->name)) && (t->is_pointer == 1) && NewObject))
	    *pyclass << tab8 << "val.thisown = 1\n";
	}
#endif
      }
    }
    //    if ((t->type != T_VOID) || (t->is_pointer))
    *pyclass << tab8 << "return val\n";

    // Change the usage string to reflect our shadow class

    if (doc_entry) {
      doc_entry->usage = "";
      doc_entry->usage << usage_func(realname,t,l);
    }
  }
}

// -----------------------------------------------------------------------------
// void PYTHON::cpp_constructor(char *name, char *iname, ParmList *l)
//
// Make a constructor for our class
// -----------------------------------------------------------------------------

void PYTHON::cpp_constructor(char *name, char *iname, ParmList *l) {
  char *realname;
  Parm *p;
  int   i;
  int   oldshadow = shadow;
  String cname = "python:constructor:";
  String translate = "";
  int pcount, numopt;
  int have_optional;

  if (shadow) shadow = shadow | PYSHADOW_MEMBER;
  this->Language::cpp_constructor(name,iname,l);
  shadow = oldshadow;

  if (shadow) {
    if (iname)
      realname = iname;
    else {
      if (class_renamed) realname = class_name;
      else realname = class_name;
    }
    
    // Check to see if we've already seen this
    cname << class_name << "::" << realname;
    if (add_symbol(cname.get(), 0,0)) {
      return;   // Forget it, already seen it
    }

    if (!have_constructor) { 

      // Create a new constructor 

      *construct << tab4 << "def __init__(self";
      pcount = l->nparms;
      numopt = l->numopt();
      have_optional = 0;
      p = l->get_first();
      i = 0;
      if (p)
	if (!p->ignore)
	  *construct << ",";
      while (p) {
	if (!p->ignore) {
	  if (i >= pcount-numopt) {
	    *construct << "*args";
	    have_optional = 1;
	    shadow_defargs(p,l,i,pcount,numopt,translate,tab8);
	    break;
	  }
	  *construct << "arg" << i;
	  p = l->get_next();
	  if (p)
	    if (!p->ignore)
	      *construct << ",";
	  i++;
	} else {
	  p = l->get_next();
	  if (p) 
	    if (!p->ignore)
	      *construct << ",";
	}
      }
      *construct << ") :\n";
      if (docstring && doc_entry) 
	*construct << tab8 << "\"\"\"" << add_docstring(doc_entry) << "\"\"\"\n";

      // Dump out default argument translation code (if any)
      *construct << translate;
      
      *construct << tab8 << "self.this = ";
      if (have_optional) {
	*construct << "apply(" << module << "." << name_construct(realname) << ",(";
      } else {
	*construct << module << "." << name_construct(realname) << "(";
      }

      p = l->get_first();
      i = 0;
      while (p) {
	if (!p->ignore) {
	  if (i >= (pcount - numopt)) {
	    *construct << ")+args";
	    break;
	  }
	  *construct << "arg" << i;
	  if ((hash.lookup(p->t->name)) && (p->t->is_pointer <= 1))
	    *construct << ".this";
	  p = l->get_next();
	  if (p)
	    if (!p->ignore)
	      *construct << ",";
	  i++;
	} else {
	  p = l->get_next();
	  if (p)
	    if ((i > 0) && (!p->ignore))
	      *construct << ",";
	}
      }
      *construct << ")\n";
      *construct << tab8 << "self.thisown = 1\n";
      have_constructor = 1;
    } else {

      // Hmmm. We seem to be creating a different constructor.  We're just going to create a
      // function for it.

      *additional << "def " << realname << "(";
      pcount = l->nparms;
      numopt = l->numopt();
      have_optional = 0;
      p = l->get_first();
      i = 0;
      while (p) {
	if (!p->ignore) {
	  if (i >= pcount-numopt) {
	    *additional << "*args";
	    have_optional = 1;
	    shadow_defargs(p,l,i,pcount,numopt,translate,tab4);
	    break;
	  }
	  *additional << "arg" << i;
	  p = l->get_next();
	  if (p)
	    if (!p->ignore)
	      *additional << ",";
	  i++;
	} else {
	  p = l->get_next();
	  if (p) {
	    if ((i > 0) && (!p->ignore)) *additional << ",";
	  }
	}
      }
      *additional << ") :\n";
      *additional << translate;
      *additional << tab4 << "val = " << class_name << "Ptr(";
      if (have_optional) {
	*additional << "apply(" << module << "." << name_construct(realname) << ",(";
      } else {
	*additional << module << "." << name_construct(realname) << "(";
      }
      p = l->get_first();
      i = 0;
      while (p) {
	if (!p->ignore) {
	  if (i >= (pcount - numopt)) {
	    *additional << ")+args";
	    break;
	  }
	  *additional << "arg" << i;
	  if ((hash.lookup(p->t->name)) && (p->t->is_pointer <= 1))
	    *additional << ".this";
	  p = l->get_next();
	  if (p)
	    if (!p->ignore)
	      *additional << ",";
	  i++;
	} else {
	  p = l->get_next();
	  if (p)
	    if ((i > 0) && (!p->ignore))
	      *additional << ",";
	}
      }
      *additional << "))\n";
      *additional << tab4 << "val.thisown = 1\n"
		  << tab4 << "return val\n\n";
    }
    // Patch up the documentation entry

    if (doc_entry) {
      doc_entry->usage = "";
      doc_entry->usage << usage_func(class_name,0,l);
    }
  }
}

// ------------------------------------------------------------------------------
// void PYTHON::cpp_destructor(char *name, char *newname)
//
// Creates a destructor for this object
// ------------------------------------------------------------------------------

void PYTHON::cpp_destructor(char *name, char *newname) {
  char *realname;
  int oldshadow = shadow;

  if (shadow) shadow = shadow | PYSHADOW_MEMBER;
  this->Language::cpp_destructor(name,newname);
  shadow = oldshadow;
  if (shadow) {
    if (newname) realname = newname;
    else {
      if (class_renamed) realname = class_name;
      else realname = name;
    }
    
    *pyclass << tab4 << "def __del__(self):\n"
	     << tab8 << "if self.thisown == 1 :\n"
	     << tab8 << tab4 << module << "." << name_destroy(realname) << "(self.this)\n";
    
    have_destructor = 1;

    if (doc_entry) {
      doc_entry->usage = "";
      doc_entry->usage << "del this";
    }
  }
}

// -------------------------------------------------------------------------------
// PYTHON::cpp_close_class()
//
// Closes a Python class and writes out a wrapper
// -------------------------------------------------------------------------------
    
void PYTHON::cpp_close_class() {
  String    ptrclass;
  String    repr;

  if (shadow) {

    if (!have_constructor) {
      // Build a constructor that takes a pointer to this kind of object
      *construct << tab4 << "def __init__(self,this):\n";
      *construct << tab8 << "self.this = this\n";
    }

    // First, build the pointer base class

    if (base_class) {
      ptrclass << "class " << class_name << "Ptr(" << *base_class << "):\n";
    } else {
    ptrclass << "class " << class_name << "Ptr :\n";
    }

    //    *getattr << tab8 << "return self.__dict__[name]\n";
    *getattr << tab8 << "raise AttributeError,name\n";
    *setattr << tab8 << "self.__dict__[name] = value\n";

    ptrclass << *cinit 
	     << tab4 << "def __init__(self,this):\n"
	     << tab8 << "self.this = this\n"
	     << tab8 << "self.thisown = 0\n";

    classes << ptrclass
	    << *pyclass;
    if (have_setattr)
      classes << *setattr;
    if (have_getattr)
      classes << *getattr;
    
    if (!have_repr) {
      // Supply a repr method for this class 
      repr << tab4 << "def __repr__(self):\n"
	   << tab8 << "return \"<C " << class_name <<" instance>\"\n";

      classes << repr;
    }

    // Now build the real class with a normal constructor

    classes << "class " << class_name << "(" << class_name << "Ptr):\n";
    
    if (docstring && doc_entry) {
      classes << tab4 << "\"\"\"" << add_docstring(doc_entry) << "\"\"\"\n";
    }

    classes << *construct << "\n\n"
	    << "\n" << *additional << "\n";

    delete pyclass;
    delete setattr;
    delete getattr;
    delete additional;
  }
}

void PYTHON::cpp_cleanup() { };

void PYTHON::cpp_inherit(char **baseclass,int) {

  char *bc;
  int   i = 0, first_base = 0;

  if (!shadow) {
    this->Language::cpp_inherit(baseclass);
    return;
  }

  // We'll inherit variables and constants, but not methods

  this->Language::cpp_inherit(baseclass, INHERIT_VAR);

  if (!baseclass) return;
  base_class = new String;

  // Now tell the Python module that we're inheriting from a base class

  while (baseclass[i]) {
    bc = (char *) hash.lookup(baseclass[i]);
    if (bc) {
      if (first_base) *base_class << ",";
      *base_class << bc << "Ptr";
      first_base = 1;
    }
    i++;
  }
  if (!first_base) {
    delete base_class;
    base_class = 0;
  }
}

// --------------------------------------------------------------------------------
// PYTHON::cpp_variable(char *name, char *iname, DataType *t)
//
// Adds an instance member.
// --------------------------------------------------------------------------------

void PYTHON::cpp_variable(char *name, char *iname, DataType *t) {
  char *realname;
  int   inhash = 0;
  int   oldshadow = shadow;
  String cname = "python:";

  if (shadow) shadow = shadow | PYSHADOW_MEMBER;
  this->Language::cpp_variable(name,iname,t);
  shadow = oldshadow;

  if (shadow) {
    have_getattr = 1;
    have_setattr = 1;
    if (!iname)
      realname = name;
    else
      realname = iname;

    // Check to see if we've already seen this

    cname << class_name << "::" << realname;
    if (add_symbol(cname.get(), 0,0)) {
      return;   // Forget it, already seen it
    }
    
    // Figure out if we've seen this datatype before
    
    if ((hash.lookup(t->name)) && (t->is_pointer <= 1)) inhash = 1;
    
    // Now write some code to set the variable
    *setattr << tab8 << "if name == \"" << realname << "\" :\n";
    if (inhash) {
      *setattr << tab8 << tab4 << module << "." << name_set(name_member(realname,class_name)) << "(self.this,value.this)\n";
    } else {
      *setattr << tab8 << tab4 << module << "." << name_set(name_member(realname,class_name)) << "(self.this,value)\n";
    }
    *setattr << tab8 << tab4 << "return\n";
    
    // Write some code to get the variable
    *getattr << tab8 << "if name == \"" << realname << "\" : \n";
    if (inhash) {
      *getattr << tab8 << tab4 << "return " << (char *) hash.lookup(t->name) << "Ptr(" << module << "."
	       << name_get(name_member(realname,class_name)) << "(self.this))\n";
    } else {
      *getattr << tab8 << tab4 << "return " << module << "." << name_get(name_member(realname,class_name)) << "(self.this)\n";
    }

    // Patch up ye old documentation entry
    
    if (doc_entry) {
      doc_entry->usage = "";
      doc_entry->usage << "self." << realname;
    }
  }
}

// --------------------------------------------------------------------------------
// PYTHON::cpp_declare_const(char *name, char *iname, DataType *type, char *value)
//
// Add access to a C++ constant
// --------------------------------------------------------------------------------

void PYTHON::cpp_declare_const(char *name, char *iname, DataType *type, char *value) {
  char *realname;
  int   oldshadow = shadow;
  String cname = "python:";

  if (shadow) shadow = shadow | PYSHADOW_MEMBER;
  this->Language::cpp_declare_const(name,iname,type,value);
  shadow = oldshadow;

  if (shadow) {
    if (!iname)
      realname = name;
    else
      realname = iname;

    // Check to see if we've already seen this

    cname << class_name << "::" << realname;
    if (add_symbol(cname.get(), 0,0)) {
      return;   // Forget it, already seen it
    }
    
    *cinit << tab4 << realname << " = " << module << "." << name_member(realname,class_name) << "\n";

    if (doc_entry) {
      doc_entry->usage = "";
      doc_entry->usage << "self." << realname;
      if (value) {
	doc_entry->usage << " = " << value;
      }
    }
  }
}
 
// --------------------------------------------------------------------------------
// PYTHON::add_typedef(DataType *t, char *name)
//
// This is called whenever a typedef is encountered.   When shadow classes are
// used, this function lets us discovered hidden uses of a class.  For example :
//
//     struct FooBar {
//            ...
//     }
//
// typedef FooBar *FooBarPtr;
//
// --------------------------------------------------------------------------------

void PYTHON::add_typedef(DataType *t, char *name) {

  if (!shadow) return;

  // First check to see if there aren't too many pointers

  if (t->is_pointer > 1) return;

  if (hash.lookup(name)) return;      // Already added


  // Now look up the datatype in our shadow class hash table

  if (hash.lookup(t->name)) {

    // Yep.   This datatype is in the hash
    
    // Put this types 'new' name into the hash

    hash.add(name,copy_string((char *) hash.lookup(t->name)));
  }
}


/*********************************************************************************    
 *
 * $Log: pycpp.cxx,v $
 * Revision 1.24  1997/07/27 20:31:19  beazley
 * Changes to shadow classes and output typemaps.
 *
 * Revision 1.23  1997/07/03 03:26:01  beazley
 * Fixed problems with shadow classes and output arguments.
 *
 * Revision 1.22  1997/06/29 18:57:12  beazley
 * Modified shadow classes so output arguments work correctly.
 *
 * Revision 1.21  1997/06/20 05:22:38  beazley
 * Minor bug fix related to Objective-C generation.
 *
 * Revision 1.20  1997/06/17 04:43:28  beazley
 * Fixed some shadow class bugs with %name().  Moved to unified
 * renaming scheme.
 *
 * Revision 1.19  1997/05/28 21:40:12  beazley
 * Moved revision history to end.
 *
 * Revision 1.18  1997/04/23 05:00:43  beazley
 * Support for %new directive
 *
 * Revision 1.17  1997/04/09 03:35:11  beazley
 * Fixed bugs related to class renaming.
 *
 * Revision 1.16  1997/03/10 16:46:43  beazley
 * Fixed bug with ignored arguments and shadow classes.
 *
 * Revision 1.15  1997/03/02 22:40:57  beazley
 * Changed processing of C++ enums
 *
 * Revision 1.14  1997/02/16 18:52:45  beazley
 * Fixed bugs in default argument handling.
 *
 * Revision 1.13  1997/01/27 05:13:30  beazley
 * Added support for default arguments in shadow classes.
 *
 * Revision 1.12  1997/01/09 01:21:42  beazley
 * Changed inherit method slightly
 *
 * Revision 1.11  1997/01/06 17:12:03  beazley
 * Added support for typemaps.  Multiple inheritance.
 *
 * Revision 1.10  1996/12/26 04:48:00  beazley
 * Minor bug fixes
 *
 * Revision 1.9  1996/12/03 08:41:26  beazley
 * pre-1.1b2 checkin
 *
 * Revision 1.8  1996/11/12 20:01:57  beazley
 * Changes to support new documentation and C++ handling
 *
 * Revision 1.7  1996/10/30 05:37:03  beazley
 * Fixed some problems with inheriting data members
 *
 * Revision 1.6  1996/09/26 21:50:08  dmb
 * Minor fixes to constructors
 *
 * Revision 1.5  1996/08/26 23:34:37  dmb
 * Minor fixes
 *
 * Revision 1.4  1996/08/26 16:31:42  dmb
 * Made it so shadow class modules do not include the low-level C
 * interface functions
 *
 * Revision 1.3  1996/08/25 00:04:57  dmb
 * Made some more improvements to shadow classes
 *
 * Revision 1.2  1996/08/21 05:50:00  dmb
 * Changed method of accessing structure attributes
 *
 * Revision 1.1  1996/08/18 03:32:14  dmb
 * Initial revision
 *
 *********************************************************************************/
