
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

/***********************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.2/Modules/RCS/swigmain.cxx,v 1.17 1997/05/28 21:42:30 beazley Exp beazley $
 *
 * swigmain.cxx
 *
 * The main program.
 *
 ***********************************************************************/

#include "wrap.h"
#include "swigtcl.h"
#include "tcl8.h"
#include "perl4.h"
#include "perl5.h"
#include "python.h"
// #include "pythoncom.h"
#include "guile.h"
#include "debug.h"
#include "ascii.h"
#include "latex.h"
#include "html.h"
#include "nodoc.h"
#include <ctype.h>

static char  *usage = "\
swig <options> filename\n\n\
Target Language Options:\n\
     -tcl            - Generate Tcl wrappers.\n\
     -tcl8           - Generate Tcl 8.0 wrappers.\n\
     -python         - Generate Python wrappers.\n\
     -perl5          - Generate Perl5 wrappers.\n\
     -perl4          - Generate Perl4 wrappers.\n\
     -guile          - Generate Guile wrappers.\n\
     -debug          - Parser debugging module.\n";

#ifdef MACSWIG     
static char *macmessage = "\
Copyright (c) 1995-1997\n\
University of Utah and the Regents of the University of California\n\n\
Enter SWIG processing options and filename below. For example :\n\
\n\
      -tcl -c++ interface.i\n\
\n\
-help displays a list of all available options.\n\
\n\
Note : Macintosh filenames should be enclosed in quotes if they contain whitespace.\n\
\n";

#endif

//-----------------------------------------------------------------
// main()
//
// Main program.    Initializes the files and starts the parser.
//-----------------------------------------------------------------

#ifndef MACSWIG
int main(int argc, char **argv) {
#else
int Mac_main(int argc, char **argv) {
#endif

  int i;

  Language *dl = new SWIG_LANG;
  Documentation *dd = new SWIG_DOC;
  extern int SWIG_main(int, char **, Language *, Documentation *);

  init_args(argc,argv);
  
  // Get options
  for (i = 1; i < argc; i++) {
      if (argv[i]) {
	  if(strcmp(argv[i],"-tcl") == 0) {
	      dl = new TCL;
	      mark_arg(i);
          } else if (strcmp(argv[i],"-tcl8") == 0) {
	      dl = new TCL8;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-perl5") == 0) {
	      dl = new PERL5;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-python") == 0) {
	      dl = new PYTHON;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-debug") == 0) {
	      dl = new DEBUGLANG;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-perl4") == 0) {
	      dl = new PERL4;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-guile") == 0) {
	      dl = new GUILE;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-help") == 0) {
	      fputs(usage,stderr);
	      mark_arg(i);
	  }
      }
  }
  SWIG_main(argc,argv,dl,dd);
  return 0;
}

#ifdef MACSWIG
int MacMainEntry(char *options) {
	static char *_argv[256];
	int i,argc;
	char *c,*s,*t;

	swig_log = fopen("swig_log","w");
	fprintf(swig_log,"SWIG 1.1\n");
	fprintf(swig_log,"Options : %s\n", options);
	fprintf(swig_log,"-----------------------------------------------------\n");

	// Tokenize the user input
	
	_argv[0] = "swig";
	i=1;
	c = options;
	while (*c) {
	    while(isspace(*c)) c++;
	    if (*c) {
	      s = c;             // Starting character
	      while(isgraph(*c)) {
		if (*c == '\"') {
		  c++;
		  while ((*c) && (*c != '\"'))
		    c++;
		  c++;
		} else {
		  c++;
		}
	      }
	      // Found some whitespace 
	      if (*c) {
		*c = 0;
		c++;
	      }
	      _argv[i] = copy_string(s);
	      // Go through and remove quotes (if necessary)
	      
	      t = _argv[i];
	      while(*s) {
		if (*s != '\"') 
		  *(t++) = *s;
		s++;
	      }
	      *t = 0;
	      i++;
	    }
	}
	argc = i;
	_argv[i] = 0;
	return Mac_main(argc,_argv);
}
	
#endif	

/*********************************************************************************
 * -- Revision History
 * $Log: swigmain.cxx,v $
 * Revision 1.17  1997/05/28 21:42:30  beazley
 * Moved revision history to end.
 *
 * Revision 1.16  1997/03/29 17:44:18  beazley
 * Minor changes for Macintosh
 *
 * Revision 1.15  1997/02/26 04:28:04  beazley
 * Removed warning message
 *
 * Revision 1.14  1997/02/19 23:07:15  beazley
 * Added simple support for Macintosh.
 *
 * Revision 1.13  1997/01/06 17:12:03  beazley
 * Added support for typemaps.  Multiple inheritance.
 *
 * Revision 1.12  1996/12/26 04:48:00  beazley
 * Added Perl4 and Guile modules back in.
 * Added Tcl8 target language
 *
 * Revision 1.11  1996/11/12 20:01:57  beazley
 * Changes to support new documentation and C++ handling
 *
 * Revision 1.10  1996/10/29 19:27:11  beazley
 * Added hooks for debugging module
 *
 * Revision 1.9  1996/08/21 05:50:43  dmb
 * Minor changes
 *
 * Revision 1.8  1996/08/12 01:51:19  dmb
 * Changed handling of command line options
 *
 * Revision 1.7  1996/05/22 20:20:21  beazley
 * Changed name of tcl class
 * 
 * Revision 1.6  1996/05/01  22:42:30  dmb
 * Cleaned up command line options and fixed -help option
 *
 * Revision 1.5  1996/04/14 15:24:20  dmb
 * Changed name of the file. Fixed headers.
 *
 * Revision 1.4  1996/03/28 02:47:41  beazley
 * Added Guile3 support back in
 *
 * Revision 1.3  1996/03/24  22:15:03  beazley
 * Added python support.
 *
 * Revision 1.2  1996/03/22  23:42:04  beazley
 * Added Perl4, Perl5
 *
 * Revision 1.1  1996/03/16  06:28:54  beazley
 * Initial revision
 *
 *********************************************************************************/
