
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
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*******************************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.1/SWIG/RCS/include.cxx,v 1.23 1997/06/20 05:24:18 beazley Exp $
 *
 * File : include.cxx
 *
 * Code for including files into a wrapper file.
 *
 *******************************************************************************/

/* Delimeter used in accessing files and directories */

#ifdef MACSWIG
#define  DELIMETER  ':'
#else
#define  DELIMETER  '/'
#endif

/* Linked list containing search directories */

struct   Dnode {
  char    *dirname;
  Dnode   *next;
};

Dnode   ihead, iz;
int     include_init = 0;

/* Linked list containing included files */

struct  Inode {
  char    *name;
  Inode   *next;
};

Inode  *include_list = 0;

// -----------------------------------------------------------------------------
// void add_directory(char *dirname)
//
// Adds a directory to the SWIG search path.
// 
// Inputs : dirname  = Pathname
//
// Output : None
//
// Side Effects : Adds dirname to linked list of pathnames.
// -----------------------------------------------------------------------------

void add_directory(char *dirname) {
  Dnode  *d;

  if (!include_init) {
    ihead.next = &iz;
    iz.next = &iz;
    iz.dirname = new char[2];
    iz.dirname[0] = 0;
    include_init = 1;
  }

  d = new Dnode;
  d->dirname = new char[strlen(dirname)+1];
  strcpy(d->dirname,dirname);
  d->next = ihead.next;
  ihead.next = d;

}

// -----------------------------------------------------------------------------
// int add_iname(char *name)
// 
// Adds an include file to the list of processed files.  If already present,
// returns 1. 
//
// Inputs : name  = filename
//
// Output : 0 on success, 1 on failure.
//
// Side Effects : Adds name to linked list.
// -----------------------------------------------------------------------------

int add_iname(char *name) {

  Inode *newi, *i;

  if (include_list) {
    /* Search list */
    i = include_list;
    while (i) {
      if (strcmp(i->name, name) == 0) return 1;
      i = i->next;
    }
  }

  newi = new Inode;
  newi->name = new char[strlen(name)+1];
  strcpy(newi->name, name);
  newi->next = include_list;
  include_list = newi;
  return 0;
}

// -----------------------------------------------------------------------------
// void check_suffix(char *name)
// 
// Checks the suffix of an include file to see if we need to handle it
// differently.  C and C++ source files need a little extra help.
//
// Inputs : name  = include file name.
//
// Output : None
//
// Side Effects : 
//          Sets ForceExtern status variable if a C/C++ source file
//          is detected.
//
// -----------------------------------------------------------------------------

void check_suffix(char *name) {
  char *c;

  if (!name) return;
  if (strlen(name) == 0) return;
  c = name+strlen(name)-1;
  while (c != name) {
    if (*c == '.') break;
    c--;
  }
  if (c == name) return;

  /* Check suffixes */

  if (strcmp(c,".c") == 0) {
    ForceExtern = 1;
  } else if (strcmp(c,".C") == 0) {
    ForceExtern = 1;
  } else if (strcmp(c,".cc") == 0) {
    ForceExtern = 1;
  } else if (strcmp(c,".cxx") == 0) {
    ForceExtern = 1;
  } else if (strcmp(c,".c++") == 0) {
    ForceExtern = 1;
  } else if (strcmp(c,".cpp") == 0) {
    ForceExtern = 1;
  } else {
    ForceExtern = 0;
  }
}
// -----------------------------------------------------------------------------
// int include_file(char *name)
// 
// Includes a new SWIG wrapper file. Returns -1 if file not found.
//
// Inputs : name  = filename
//
// Output : 0 on success. -1 on failure.
//
// Side Effects : sets scanner to read from new file.
// -----------------------------------------------------------------------------

int include_file(char *name) {

  FILE  *f;
  char   filename[256];
  int    found = 0;
  Dnode  *d;
  extern void scanner_file(FILE *);

  if (!include_init) return -1;    // Not initialized yet
  if (add_iname(name)) {
    if (Verbose) fprintf(stderr,"file %s already included.\n", name);
    return -1;  // Already included this file
  }

  if (Verbose) {
    fprintf(stderr,"Wrapping %s...\n", name);	
    fprintf(stderr,"Looking for ./%s\n", name);
  }

  if ((f = fopen(name,"r")) != NULL) {
    input_file = new char[strlen(name)+1];
    strcpy(input_file,name);
    scanner_file(f);
    check_suffix(name);
    return 0;
  }

  // Now start searching libraries

  d = ihead.next;               // Start of search list
  while (d != &iz) {
    // Look for the wrap file in language directory
    sprintf(filename,"%s%c%s%c%s", d->dirname,DELIMETER,LibDir,DELIMETER,name);
    if (Verbose) fprintf(stderr,"Looking for %s\n", filename);
    if((f = fopen(filename,"r")) != NULL) {
      found = 1;
    } else {
      sprintf(filename,"%s%c%s", d->dirname, DELIMETER,name);
      if (Verbose) fprintf(stderr,"Looking for %s\n", filename);
      if ((f = fopen(filename,"r")) != NULL) {
	found = 1;
      }
    }
    if (found) {
      // Found it, open it up for input
      input_file = new char[strlen(filename)+1];
      strcpy(input_file,filename);
      scanner_file(f);
      check_suffix(name);
      return 0;
    }
    d = d->next;
  }

  if (!found) fprintf(stderr,"%s : Line %d. Unable to find include file %s (ignored).\n",input_file, line_number, name);

  return -1;
}


static char  buffer[1024];

// -----------------------------------------------------------------------------
// void copy_data(FILE *f1, FILE *f2)
//
// Copies data from file f1 to file f2.
// 
// Inputs : f1  = FILE 1
//          f2  = FILE 2
//
// Output : None
//
// Side Effects : Closes file f1 upon exit.
// -----------------------------------------------------------------------------

void copy_data(FILE *f1, FILE *f2) {

  while (fgets(buffer,1023,f1)) {
    fputs(buffer, f2);
  }
  fclose(f1);
}

// -----------------------------------------------------------------------------
// void copy_data(FILE *f1, String *s2)
//
// Copies data from file f1 to String s2.
// 
// Inputs : f1  = FILE 1
//          s2  = String
//
// Output : None
//
// Side Effects : Closes file f1 upon exit.
// -----------------------------------------------------------------------------

void copy_data(FILE *f1, String &s2) {

  while (fgets(buffer,1023,f1)) {
    s2 << buffer;
  }
  fclose(f1);
}

// -----------------------------------------------------------------------------
// int insert_file(char *name, FILE *f)
//
// Looks for a file and inserts into file f.
//
// Inputs : name  = filename
//          f     = FILE
//
// Output : 0 on success, -1 on failure.
//
// Side Effects : None
// -----------------------------------------------------------------------------

int insert_file(char *name, FILE *f_out) {

  FILE  *f;
  char   filename[256];
  int    found = 0;
  Dnode  *d;

  if (!include_init) return -1;    // Not initialized yet
  if (add_iname(name)) {
    if (Verbose) fprintf(stderr,"file %s already included.\n", name);
    return -1;  // Already included this file
  }

  if (Verbose) fprintf(stderr,"Looking for ./%s\n", name);
  if ((f = fopen(name,"r")) != NULL) {
      copy_data(f,f_out);
      return 0;
  }

  // Now start searching libraries

  d = ihead.next;               // Start of search list
  while (d != &iz) {
    // Look for the wrap file in language directory
    sprintf(filename,"%s%c%s%c%s", d->dirname,DELIMETER,LibDir,DELIMETER,name);
    if (Verbose) fprintf(stderr,"Looking for %s\n", filename);
    if((f = fopen(filename,"r")) != NULL) {
      found = 1;
    } else {
      sprintf(filename,"%s%c%s", d->dirname, DELIMETER, name);
      if (Verbose) fprintf(stderr,"Looking for %s\n", filename);
      if ((f = fopen(filename,"r")) != NULL) {
	found = 1;
      }
    }
    if (found) {
	copy_data(f,f_out);
	return 0;
    }
    d = d->next;
  }

  if ((!found) && (Verbose)) fprintf(stderr,"unable to find %s. (Ignored)\n",name);
  return -1;
}

// -----------------------------------------------------------------------------
// void swig_append(char *filename, FILE *f)
// 
// Appends the contents of filename to stream f.
//
// Inputs : 
//          filename  = File to append
//          f         = FILE handle 
//
// Output : None
//
// Side Effects : None
// -----------------------------------------------------------------------------

void swig_append(char *filename, FILE *f) {

  FILE *in_file;

  if ((in_file = fopen(filename,"r")) == NULL) {
      fprintf(stderr,"** SWIG ERROR ** file %s not found.\n",filename);
      FatalError();
      return;
  }
  while (fgets(buffer,1023,in_file)) {
    fputs(buffer, f);
  }
  fclose(in_file);
}


// -----------------------------------------------------------------------------
// int get_file(char *name, String &str)
//
// Looks for a file and converts it into a String.  
//
// Inputs : name  = filename
//          str   = String
//
// Output : 0 on success, -1 on failure.
//
// Side Effects : None
// -----------------------------------------------------------------------------

int get_file(char *name, String &str) {

  FILE  *f;
  char   filename[256];
  int    found = 0;
  Dnode  *d;

  if (!include_init) return -1;    // Not initialized yet

  if (Verbose) fprintf(stderr,"Looking for %s\n", name);
  if ((f = fopen(name,"r")) != NULL) {
      copy_data(f,str);
      return 0;
  }

  // Now start searching libraries

  d = ihead.next;               // Start of search list
  while (d != &iz) {
    // Look for the wrap file in language directory
    sprintf(filename,"%s%c%s%c%s", d->dirname,DELIMETER,LibDir,DELIMETER,name);
    if (Verbose) fprintf(stderr,"Looking for %s\n", filename);
    if((f = fopen(filename,"r")) != NULL) {
      found = 1;
    } else {
      sprintf(filename,"%s%c%s", d->dirname, DELIMETER, name);
      if (Verbose) fprintf(stderr,"Looking for %s\n", filename);
      if ((f = fopen(filename,"r")) != NULL) {
	found = 1;
      }
    }
    if (found) {
	copy_data(f,str);
	return 0;
    }
    d = d->next;
  }

  if ((!found)) fprintf(stderr,"SWIG Error. Unable to find %s. Possible installation problem.\n",name);
  FatalError();
  return -1;
}

static char *libs[1000];
static int   nlibs = 0;

// -----------------------------------------------------------------------------
// void library_add(char *name)
//
// Adds a filename to the list of libraries.   This is usually only called by
// the SWIG main program.
//
// Inputs : name  = library name
//
// Outputs: None
//
// Side Effects : Adds the library name to the libs array above
// -----------------------------------------------------------------------------

void library_add(char *name) {
  int i;

  // Check to make sure it's not already added

  if (!(*name)) return;

  for (i = 0; i < nlibs; i++) {
    if (strcmp(libs[i],name) == 0) return;
  }

  libs[nlibs] = copy_string(name);
  nlibs++;
}

// -----------------------------------------------------------------------------
// void library_insert()
// 
// Starts parsing all of the SWIG library files.
// 
// Inputs : None
//
// Output : None
//
// Side Effects : Opens and attaches all of the specified library files to
//                the scanner.
//
// Bugs : Opens all of the files.   Will fail if there are too many open files.
//
// -----------------------------------------------------------------------------

void library_insert() {
  int i;

  i = nlibs-1;
  while (i >= 0) {
    include_file(libs[i]);
    i--;
  }
}

// -----------------------------------------------------------------------------
// int checkout(char *filename,char *dest) 
// 
// Tries to check a file out of the SWIG library. If found, it will save it in
// the current directory.   This is a useful mechanism for using SWIG as a code
// manager and for extracting library files.
//
// Inputs : filename = Library file
//          dest     = Destination file
//
// Output : 0 on success
//         -1 on failure.
//
// Side Effects :  None
// -----------------------------------------------------------------------------

int checkout_file(char *filename,char *dest) {

  FILE *f1;
  char tempn[256];

  // First check to see if the file already exists in current directory
  f1 = fopen(dest,"r");
  if (f1) {
    if (Verbose)
      fprintf(stderr,"Warning. Unable to check-out %s. File already exists.\n", filename);
    fclose(f1);
    return -1;
  } 

  while (!f1) {
    sprintf(tempn,"%s%d",dest,rand());
    f1 = fopen(tempn,"r");
    if (f1) {
      fclose(f1);
      f1 = 0;
    } else {
      f1 = fopen(tempn,"w");
      if (!f1) {
	fprintf(stderr,"Unable to open %s for writing\n", tempn);
	return -1;
      }
    }
  }

  // Now try to insert the library file into the destination file
  if ((insert_file(filename,f1)) == -1) {
    fprintf(stderr,"Unable to check-out '%s'. File does not exist in SWIG library.\n",filename);
    fclose(f1);
    remove(tempn);       // Unsuccessful, remove file we created
    return -1;
  }
  fclose(f1);
  // Now move the file
  rename(tempn,dest);
  return 0;
}


// -----------------------------------------------------------------------------
// int checkin_file(char *dir, char *lang, char *source,char *dest) 
// 
// Attempts to check a file into the SWIG library.  
//
// Inputs : dir      = Location of the SWIG library.
//          lang     = Language specific subdirectory.
//          source   = Source file.
//          dest     = Destination file.
//
// Output : 0 on success
//         -1 on failure.
//
// Side Effects :  None
// -----------------------------------------------------------------------------

int checkin_file(char *dir, char *lang, char *source, char *dest) {

  FILE *f1;
  char tempn[256];
  String s;

  // First check to see if the file exists
  
  f1 = fopen(source,"r");
  if (!f1) return -1;

  copy_data(f1,s);

  // Now try to open the destination file
  sprintf(tempn,"%s/%s/%s", dir,lang,dest);
  f1 = fopen(tempn,"w");
  if (!f1) return -1;
  fprintf(f1,"%s",s.get());
  fclose(f1);
  return 0;
}

/*******************************************************************************
 *
 * -- Revision History
 * $Log: include.cxx,v $
 * Revision 1.23  1997/06/20 05:24:18  beazley
 * Added check-in function.
 *
 * Revision 1.22  1997/05/28 06:15:08  beazley
 * Moved revision history to end.
 *
 * Revision 1.21  1997/05/09 06:24:31  beazley
 * Fixed segmentation fault in checkout_file() when running under windows.
 *
 * Revision 1.20  1997/05/05 15:55:09  beazley
 * Fixed bugs in checkout option.
 *
 * Revision 1.19  1997/03/29 17:40:39  beazley
 * Added support for checking files out of the SWIG library.
 *
 * Revision 1.18  1997/03/12 05:02:32  beazley
 * Added library option
 *
 * Revision 1.17  1997/02/19 23:09:46  beazley
 * Added get_file() function for loading files into strings.
 *
 * Revision 1.16  1997/02/16 20:15:29  beazley
 * Added support for the Macintosh
 *
 * Revision 1.15  1997/01/06 17:08:17  beazley
 * Cleanup. A few minor modifications
 *
 * Revision 1.14  1996/11/12 19:49:29  beazley
 * A few minor changes to support -config command line option
 *
 * Revision 1.13  1996/09/26 21:47:57  dmb
 * Added support for new %extern directive
 *
 * Revision 1.12  1996/08/21 16:48:40  dmb
 * Minor cleanup to eliminate compiler warnings.
 *
 * Revision 1.11  1996/08/21 05:47:54  dmb
 * Cleanup up output slightly
 *
 * Revision 1.10  1996/08/15 05:04:42  dmb
 * Modified to do some suffix checking.
 *
 * Revision 1.9  1996/05/22 20:20:21  beazley
 * Minor changes
 *
 * Revision 1.8  1996/05/03  22:28:17  dmb
 * Added IncludeFile subroutine.  Will be used to load general configuration files.
 *
 * Revision 1.7  1996/04/14 15:23:44  dmb
 * Fixed header files.
 *
 * Revision 1.6  1996/03/24 22:14:25  beazley
 * Added swig_append() function to replace some "system" calls.
 *
 * Revision 1.5  1996/03/22  23:40:19  beazley
 * Took out old %include directive.  Replaced with a new and
 * improved version.
 *
 * Revision 1.4  1996/03/16  06:27:42  beazley
 * Changed to use new headers.
 *
 * Revision 1.3  1996/02/20  04:06:46  beazley
 * Took out streams stuff.
 *
 * Revision 1.2  1996/02/15  22:38:04  beazley
 * Changed copyright
 *
 * Revision 1.1  1996/02/12  08:19:16  beazley
 * Initial revision
 *
 *
 *******************************************************************************/


     

