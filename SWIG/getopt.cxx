
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
 * $Header: /home/beazley/SWIG/SWIG1.1/SWIG/RCS/getopt.cxx,v 1.4 1997/05/28 06:08:02 beazley Exp $
 *
 * File : getopt.cxx
 *
 * This file defines a few functions for handling command line arguments.
 * C++ makes this really funky---especially since each language module
 * may want to extract it's own command line arguments.
 *
 * My own special version of getopt.   This is a bit weird, because we
 * don't know what the options are in advance (they could be determined
 * by a language module).
 *******************************************************************************/

static char **args;
static int    numargs;
static int   *marked;

// -----------------------------------------------------------------------------
// void init_args(int argc, char **argv)
// 
// Initializes the argument list.
//
// Inputs :
//          argc      = Argument count
//          argv      = Argument array
//
// Output : None
//
// Side Effects : Saves local copy of argc and argv
// -----------------------------------------------------------------------------

void
init_args(int argc, char **argv)
{
  int i;
  numargs = argc;
  args = argv;
  marked = new int[numargs];
  for (i = 0; i < argc; i++) {
    marked[i] = 0;
  }
  marked[0] = 1;
}

// -----------------------------------------------------------------------------
// void mark_arg(int n)
// 
// Marks an argument as being parsed.  All modules should do this whenever they
// parse a command line option.
//
// Inputs : n  =  Argument number
//
// Output : None
//
// Side Effects : Sets a status bit internally
// -----------------------------------------------------------------------------

void
mark_arg(int n) {
  if (marked)
    marked[n] = 1;
}

// -----------------------------------------------------------------------------
// void check_options()
// 
// Checks for unparsed command line options.  If so, issues an error and exits.
//
// Inputs : None
//
// Output : None
//
// Side Effects : exits if there are unparsed options
// -----------------------------------------------------------------------------
 
void check_options() {
 
    int error = 0;
    int i;

    if (!marked) {
      fprintf(stderr,"Must specify an input file.  Use -help for available options.\n");
      SWIG_exit(1);
    }
    for (i = 1; i < numargs-1; i++) {
        if (!marked[i]) {
            fprintf(stderr,"swig error : Unrecognized option %s\n", args[i]);
            error=1;
        }
    }
 
    if (error) {
        fprintf(stderr,"Use 'swig -help' for available options.\n");
        SWIG_exit(1);
    }

    if (marked[numargs-1]) {
      fprintf(stderr,"Must specify an input file. Use -help for available options.\n");
      SWIG_exit(1);
    }
}

// -----------------------------------------------------------------------------
// void arg_error()
// 
// Generates a generic error message and exits.
//
// Inputs : None
//
// Output : None
//
// Side Effects : Exits
// -----------------------------------------------------------------------------

void arg_error() {
  fprintf(stderr,"SWIG : Unable to parse command line options.\n");
  fprintf(stderr,"Use 'swig -help' for available options.\n");
  SWIG_exit(1);
}

  
/*******************************************************************************
 *
 * -- Revision History
 * $Log: getopt.cxx,v $
 * Revision 1.4  1997/05/28 06:08:02  beazley
 * Moved revision history to end.
 *
 * Revision 1.3  1997/03/21 00:11:47  beazley
 * Changed exit() to SWIG_exit()
 *
 * Revision 1.2  1997/01/06 17:08:17  beazley
 * Cleanup. A few minor modifications
 *
 *
 *******************************************************************************/


	
		
