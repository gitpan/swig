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

#include "internal.h"
#include <ctype.h>


// -----------------------------------------------------------------------
// $Header: /home/beazley/SWIG/SWIG1.2/SWIG/RCS/lang.cxx,v 1.17 1997/06/20 22:37:02 beazley Exp $
//
// lang.cxx
//
// This file contains some default methods for the SWIG language class.   
// Default C++ handling is implemented here as well as a few utility functions.
//
// -----------------------------------------------------------------------


// -----------------------------------------------------------------
// void Language::set_init(char *iname)
//
// Called to make an initialization function by %init (obsolete)
// ----------------------------------------------------------------- 

void Language::set_init(char *iname) {
  set_module(iname,0);
}

// -----------------------------------------------------------------
// void Language::create_command(char *cname, char *iname
//
// Method for adding a previous wrapped C function.
// ----------------------------------------------------------------- 

void Language::create_command(char *, char *) {
  fprintf(stderr,"SWIG Warning. No command creation procedure defined.\n");
  fprintf(stderr,"C++ inheritance may not work correctly.\n");
}

// -----------------------------------------------------------------
// void Language::add_native(char *targetlang, char *funcname)
//
// Method for adding a native function
// ----------------------------------------------------------------- 

void
Language::add_native(char *, char *funcname) {

  fprintf(stderr,"%s : Line %d.  Adding native function %s not supported (ignored).\n", input_file, line_number, funcname);

}

static char  *ClassName = 0;        // This is the real name of the current class
static char  *ClassRename = 0;      // This is non-NULL if the class has been renamed
static char  *ClassType = 0;        // Type of class (ie. union, struct, class) 

// ---------------------------------------------------------------------------------
// void Language::cpp_open_class(char *classname, char *classrename, char *ctype, int strip)
//
// Open a new C++ class.
//
// INPUTS:
//      classname          = Real name of the C++ class
//      classrename        = New name of the class (if %name was used)
//      ctype              = Class type (struct, class, union, etc...)
//      strip              = Flag indicating whether we should strip the class type off
//
// This function is in charge of creating a new class.   The SWIG parser has
// already processed the entire class definition prior to calling this
// function (which should simplify things considerably).
//
// ---------------------------------------------------------------------------------

void Language::cpp_open_class(char *classname, char *classrename, char *ctype, int strip) {

  // Copy the class name

  if (ClassName) delete ClassName;
  ClassName = copy_string(classname);

  // Copy the class renaming

  if (ClassRename) delete ClassRename;
  if (classrename) {
    ClassRename = copy_string(classrename);
  } else {
    ClassRename = 0;           // No renaming
  }

  // Make the class type

  if (ClassType) delete ClassType;
  ClassType = new char[strlen(ctype)+2];
  if (strip) ClassType[0] = 0;
  else sprintf(ClassType,"%s ",ctype);

  if (doc_entry) {
    doc_entry->usage = "";
    doc_entry->name = copy_string(classname);
    doc_entry->usage << "class ";
    if (ClassRename) doc_entry->usage << ClassRename;
    else doc_entry->usage << ClassName;
    doc_entry->cinfo << "created from " << ctype 
		     << " " << classname;
  }
}

// ---------------------------------------------------------------------------------
// void Language::cpp_close_class()
//
// Close the current class
// ---------------------------------------------------------------------------------

void Language::cpp_close_class() {


  // Doesn't really do anything 
}

// ---------------------------------------------------------------------------------
// void Language::cpp_member_func(char *name, char *iname, DataType *t, ParmList *l)
//
// Method for adding C++ member function
//
// INPUTS:
//      name        - name of the member function
//      iname       - renaming (if given)
//      t           - Return datatype
//      l           - Parameter list
//
// By default, we're going to create a function of the form :
//
//         Foo_bar(this,args)
//
// Where Foo is the classname, bar is the member name and the this pointer is
// explicitly attached to the beginning.
//
// The renaming only applies to the member function part, not the full classname.
//
// ---------------------------------------------------------------------------------

void Language::cpp_member_func(char *name, char *iname, DataType *t, ParmList *l) {
  char       cname[256];       // Name of the C function
  char       new_name[256];
  char       *prefix;

  // Generate the C wrapper function name and interpreter name of this function
  
  // Set the classname prefix
  if (ClassRename) {
    prefix = ClassRename;
  } else {
    prefix = ClassName;
  }

  // Generate the C wrapper name for this method
  
  if (AddMethods) {
    char *bc = cplus_base_class(name);         // Get base class name of this method
    if (bc)
      strcpy(cname, name_member(name,bc));
    else
      strcpy(cname, name_member(name,ClassName));
  } else {
    strcpy(cname, name_member(name,ClassName));
  }

  // Create the actual function name

  if (iname) {
    strcpy(new_name, name_member(iname, prefix));
  } else {
    strcpy(new_name, name_member(name,prefix));
  }

  // Now do a symbol table lookup on it :

  if (add_symbol(new_name, 0,0)) {
    fprintf(stderr,"%s : Line %d. Function %s (member %s) multiply defined (2nd definition ignored).\n",
	    input_file, line_number, cname, name);
    return;
  }
  
  // Now produce the resulting wrapper function
  if (doc_entry) {
    doc_entry->cinfo << "Member : ";
  }
  cplus_emit_member_func(ClassName, ClassType, ClassRename, name, iname, t, l, AddMethods);
}

// ---------------------------------------------------------------------------------
// void Language::cpp_constructor(char *name, char *iname, ParmList *l)
//
// Method for adding C++ member constructor
//
// INPUTS:
//      name           - Name of the constructor (usually same as classname)
//      iname          - Renamed version
//      l              - parameters
// ---------------------------------------------------------------------------------

void Language::cpp_constructor(char *name, char *iname, ParmList *l) {

  char *prefix, *cname;

  if ((strcmp(name,ClassName)) && (!ObjCClass)) {
    fprintf(stderr,"%s : Line %d.  Function %s must have a return type.\n", 
	    input_file, line_number, name);
    return;
  }

  // Set the prefix

  if (ClassRename)
    prefix = ClassRename;
  else
    prefix = ClassName;

  if (iname)
    cname = name_construct(iname);
  else
    cname = name_construct(prefix);

  // Add this function to the SWIG symbol table

  if (add_symbol(cname, 0,0)) {
    fprintf(stderr,"%s : Line %d. Constructor %s multiply defined (2nd definition ignored).\n",
	    input_file, line_number, cname);
    return;
  }

  // Attach a note to the cinfo field.

  if (doc_entry) 
    doc_entry->cinfo << "Constructor: ";

  // Call our default method

  cplus_emit_constructor(ClassName, ClassType, ClassRename, name, iname, l, AddMethods);

}

// ---------------------------------------------------------------------------------
// void Language::cpp_destructor(char *name, char *iname)
//
// Method for adding C++ member destructor
//
// INPUT:
//     name        -  Name of the destructor (classname)
//     iname       -  Renamed destructor
//
// ---------------------------------------------------------------------------------

void Language::cpp_destructor(char *name, char *iname) {

  char *cname;

  if (ClassRename) 
    cname = name_destroy(ClassRename);
  else
    cname = name_destroy(ClassName);

  // Add this function to the SWIG symbol table

  if (add_symbol(cname, 0,0)) {
    fprintf(stderr,"%s : Line %d. Destructor %s multiply defined (2nd definition ignored).\n",
	    input_file, line_number, cname);
    return;
  }


  // Attach a note to the description

  if (doc_entry)
    doc_entry->cinfo << "Destructor: ";

  // Call our default method

  cplus_emit_destructor(ClassName, ClassType, ClassRename, name, iname, AddMethods);

}

// ---------------------------------------------------------------------------------
// void Language::cleanup()
//
// Perform any necessary cleanup after reaching end of interface file
// ---------------------------------------------------------------------------------

void Language::cpp_cleanup() {

  // This doesn't do anything (well, not be default)

}

// ---------------------------------------------------------------------------------
// void Language::cpp_inherit(char **baseclass, int mode)
//
// Inherit attributes from given baseclass.  
//
// INPUT:
//     baseclass       = NULL terminate list of baseclasses
//
// ---------------------------------------------------------------------------------

void Language::cpp_inherit(char **baseclass, int mode) {
  
  extern void cplus_inherit_members(char *, int);
  int    i = 0;

  if (!baseclass) return;
  while (baseclass[i]) {
    cplus_inherit_members(baseclass[i],mode);
    i++;
  }
}

// ---------------------------------------------------------------------------------
// void Language::cpp_variable(char *name, char *iname, DataType *t)
//
// Wrap a C++ data member
//
// INPUTS :
//      name       = Name of the C++ member
//     iname       = Name as used in the interpreter
//         t       = Datatype
//
// This creates a pair of functions to set/get the variable of a member.
// ---------------------------------------------------------------------------------

void Language::cpp_variable(char *name, char *iname, DataType *t) {
  char *prefix, *cname;

  // Set the class prefix
  
  if (ClassRename) {
    prefix = ClassRename;
  } else {
    prefix = ClassName;
  }

  if (iname)
    cname = name_get(name_member(iname,prefix));
  else
    cname = name_get(name_member(name,prefix));

  // Check the symbol table

  if (add_symbol(cname,(DataType *) 0,(char *) 0)) {
    fprintf(stderr,"%s : Line %d. Variable %s multiply defined (2nd definition ignored).\n", input_file, line_number, cname);
    return;
  }

  // Attach a c descriptor

  if (doc_entry)
    doc_entry->cinfo << "Member data: ";

  // Create a function to set the value of the variable

  if (!(Status & STAT_READONLY)) {
    cplus_emit_variable_set(ClassName, ClassType, ClassRename, name, iname, t, AddMethods);
    // Add a new line to the documentation entry
    if (doc_entry) doc_entry->usage << "\n";
  }

  // Create a function to get the value of a variable

  cplus_emit_variable_get(ClassName,ClassType, ClassRename, name, iname, t, AddMethods);

}

// ---------------------------------------------------------------------------------
// void Language::cpp_static_func(char *name, char *iname, DataType *t, ParmList *l)
//
// Wrap a static C++ function
//
// INPUTS:
//      name           = Real name of the function
//     iname           = New name in interpreter
//      t              = Return datatype
//      l              = Parameters
// ---------------------------------------------------------------------------------

void Language::cpp_static_func(char *name, char *iname, DataType *t, ParmList *l) {

  char  *prefix;
  char  *mname;
  char  *cname;

  // Set the classname prefix
  
  if (ClassRename) 
    prefix = ClassRename;
  else
    prefix = ClassName;

  // Set the member function name

  if (iname)
    mname = iname;
  else
    mname = name;

  cname = name_member(mname,prefix);

  // Now do a symbol table lookup on it :

  if (add_symbol(cname, 0,0)) {
    if (ObjCClass)
      fprintf(stderr,"%s : Line %d. class function %s multiply defined (2nd definition ignored).\n",
	      input_file, line_number, cname);
    else
      fprintf(stderr,"%s : Line %d. static function %s multiply defined (2nd definition ignored).\n",
	      input_file, line_number, cname);
    return;
  }

  if (doc_entry) {
    if (ObjCClass)
      doc_entry->cinfo << "Class method : ";
    else
      doc_entry->cinfo << "Static member : ";
  }

  cplus_emit_static_func(ClassName,ClassType, ClassRename, name, iname, t, l, AddMethods);

}

// ---------------------------------------------------------------------------------
// void Language::cpp_declare_const(char *name, char *iname, DataType *t, char *value)
//
// Create a C++ constant
//
// INPUTS :
//       name          = Real name of the constant
//       iname         = new name
//       t             = Datatype
//       value         = value as a string
//
// ---------------------------------------------------------------------------------

void Language::cpp_declare_const(char *name, char *iname, DataType *type, char *value)
{

  char  *cname;
  char  mname[256];
  char  *new_value;
  char  *prefix;

  // Set the classname prefix
  
  if (ClassRename) {
    prefix = ClassRename;
  } else {
    prefix = ClassName;
  }

  // Set the constant name

  if (iname)
    cname = name_member(iname,prefix);
  else
    cname = name_member(name,prefix);

  // Now do a symbol table lookup on it :

  if (add_symbol(cname, 0,0)) {
    fprintf(stderr,"%s : Line %d. Constant %s (member %s) multiply defined (2nd definition ignored).\n",
	    input_file, line_number, cname, name);
    return;
  }

  // Form correct C++ name

  sprintf(mname,"%s::%s",ClassName,name);

  // Declare a constant
  if (!value) {
    new_value = new char[strlen(ClassName)+strlen(name)+3];
    sprintf(new_value,"%s::%s",ClassName,name);
  } else {
    new_value = value;
  }

  lang->declare_const(cname,cname,type, new_value);
  
  if (!value) {
    delete new_value;
  }
}

// ---------------------------------------------------------------------------------
// void Language::cpp_static_var(char *name, char *iname, DataType *t)
//
// Wrap a static C++ variable
//
// INPUT :
//      name        = name of the variable
//     iname        = interpreter name
//         t        = Datatype
//
// ---------------------------------------------------------------------------------

void Language::cpp_static_var(char *name, char *iname, DataType *t) {

  char  *cname;
  char  mname[256];
  char  *prefix;

  // Set the classname prefix
  
  if (ClassRename) {
    prefix = ClassRename;
  } else {
    prefix = ClassName;
  }

  // Create the variable name
  
  if (iname) 
    cname = name_member(iname,prefix);
  else
    cname = name_member(name,prefix);

  // Now do a symbol table lookup on it :

  if (add_symbol(cname, 0,0)) {
    fprintf(stderr,"%s : Line %d. Variable %s (member %s) multiply defined (2nd definition ignored).\n",
	    input_file, line_number, cname, name);
    return;
  }

  // Form correct C++ name

  sprintf(mname,"%s::%s",ClassName,name);

  if (doc_entry)
    doc_entry->cinfo << "Static member : ";

  // Link with this variable

  lang->link_variable(mname,cname,t);
}

// ---------------------------------------------------------------------------------
// void Language::cpp_class_decl(char *classtype, char *classrename, char *classname)
//
// A forward class declaration
// ---------------------------------------------------------------------------------

void Language::cpp_class_decl(char *, char *, char *) {

  // Does nothing by default

}

// ---------------------------------------------------------------------------------
// void Language::add_typedef(DataType *t, char *name)
//
// Process a typedef declaration.
// ---------------------------------------------------------------------------------

void Language::add_typedef(DataType *, char *) {

}


// ---------------------------------------------------------------------------------
// void Language::pragma(char *target, char *var, char *value)
//
// A pragma declaration
// ---------------------------------------------------------------------------------

void Language::pragma(char *, char *, char *) {

  // Does nothing by default

}

// ---------------------------------------------------------------------------------
// void Language::import(char *filename)
//
// An import directive
// ---------------------------------------------------------------------------------

void Language::import(char *) {

  // Does nothing by default

}

/**********************************************************************************
 * --- Revision history
 * $Log: lang.cxx,v $
 * Revision 1.17  1997/06/20 22:37:02  beazley
 * Eliminated compiler warnings.
 *
 * Revision 1.16  1997/06/17 04:48:46  beazley
 * Changed to use new naming system.
 *
 * Revision 1.15  1997/05/28 06:16:18  beazley
 * Moved revision history to end.
 *
 *
 *
 **********************************************************************************/









