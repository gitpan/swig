
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

#include "swig.h"
#include "ascii.h"
#include <ctype.h>

/*******************************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.1/SWIG/RCS/ascii.cxx,v 1.14 1997/05/28 06:03:00 beazley Exp $
 *
 * File : ascii.cxx
 *
 * Module for producing ASCII documentation.
 *
 *******************************************************************************/

// -----------------------------------------------------------------------------
// ASCII::ASCII()
//
// Constructor.  Initializes the ASCII module. 
// 
// Inputs : None
//
// Output : Documentation module object   
//
// Side Effects :
//     Sets page-width and indentation.
// -----------------------------------------------------------------------------

ASCII::ASCII() {
  sect_count = 0;
  indent     = 8;
  columns    = 70;
}

// -----------------------------------------------------------------------------
// void ASCII::print_string(char *s, int margin, int mode) 
// 
// Prints a string to the documentation file.  Performs line wrapping and
// other formatting.
//
// Inputs :
//          s      = NULL terminate ASCII string
//          margin = Number of characters to be inserted on left side
//          mode   = If set, text will be reformatted.  Otherwise, it's 
//                   printed verbatim (with indentation).
//
// Output : None
//
// Side Effects : None
// -----------------------------------------------------------------------------

void ASCII::print_string(char *s, int margin, int mode) { 

  char *c;
  int i;
  int lbreak = 0;
  int col;

  c = s;

  if (!s) return;
  // Apply indentation

  for (i = 0; i < margin; i++)
    fputc(' ',f_doc);

  col = margin;
  if (mode) {

    // Dump out text in formatted mode

    // Strip leading white-space

    while ((*c) && (isspace(*c))) {
      c++;
    }
    while (*c) {
      switch(*c) {
      case '\n':
      case '\\':
	if (lbreak) {
	  col = margin;
	  fputc('\n',f_doc);
	  for (i = 0; i < margin; i++)
	    fputc(' ',f_doc);
	  lbreak = 0;
	} else {
	  if ((*c) == '\n') {
	    col++;
	  }
	  lbreak++;
	}
	break;
      case ' ':
      case '\t':
      case '\r':
      case '\f':
	if (col > columns) {
	  fputc('\n',f_doc);
	  for (i = 0; i < margin; i++)
	    fputc(' ',f_doc);
	  col = margin;
	} else {
	  fputc(' ',f_doc);
	  col++;
	}
	// Skip over rest of white space found 
	while ((*c) && isspace(*c)) c++;
	c--;
	lbreak = 0;
	break;
      default :
	if (lbreak) fputc(' ',f_doc);
	lbreak = 0;
	fputc(*c,f_doc);
	col++;
	break;
      }
      c++;
    }
  } else {
    // Dump out text in pre-formatted mode
    while (*c) {
      switch(*c) {
      case '\n':
	fputc('\n',f_doc);
	for (i = 0; i < margin; i++)
	  fputc(' ',f_doc);
	break;
      default :
	fputc(*c,f_doc);
	col++;
	break;
      }
      c++;
    }
  } 
}

// -----------------------------------------------------------------------------
// void ASCII::print_decl(DocEntry *de)
// 
// Prints the documentation entry corresponding to a declaration
//
// Inputs : 
//          de = Documentation entry (which should be for a declaration)
//
// Output : None
//
// Side Effects : None
// -----------------------------------------------------------------------------

void ASCII::print_decl(DocEntry *de) { 

  int i;
  char *c;

  c = de->usage.get();
  fprintf(f_doc,"%s\n",c);

  // If there is any C annotation, print that
  if (de->print_info) {
    c = de->cinfo.get();
    if (strlen(c) > 0) {
      for (i = 0; i < indent; i++)
	fputc(' ',f_doc);
      fprintf(f_doc,"[ ");
      print_string(c,0,1);
      fprintf(f_doc," ]\n");
    }
  }

  c = de->text.get();
  if (strlen(c) > 0) {
    print_string(c,indent,de->format);
    fprintf(f_doc,"\n");
    if (de->format) fputc('\n',f_doc);
  } else {
    fprintf(f_doc,"\n");
  }
}

// -----------------------------------------------------------------------------
// void ASCII::print_text(DocEntry *de)
//
// Prints the documentation for a block of text.  Will strip any leading white
// space from the text block.
// 
// Inputs : 
//          de = Documentation entry of text
//
// Output : None
//
// Side Effects : None
// -----------------------------------------------------------------------------

void ASCII::print_text(DocEntry *de) {
  char *c;
  c = de->text.get();
  if (strlen(c) > 0) {
    while ((*c == '\n')) c++;
    print_string(c,0,de->format);
    fprintf(f_doc,"\n\n");
  }
}

// -----------------------------------------------------------------------------
// void ASCII::title(DocEntry *de)
// 
// Sets the title of the documentation file.
//
// Inputs : 
//          de = Documentation entry of the title.
//
// Output : None
//
// Side Effects : None
// -----------------------------------------------------------------------------

void ASCII::title(DocEntry *de) { 
  char *c;

  c = de->usage.get();
  if (strlen(c) > 0) {
    fprintf(f_doc,"%s\n\n",c);
  }

  // If there is any C annotation, print that
  if (de->print_info) {
    c = de->cinfo.get();
    if (strlen(c) > 0) {
      fprintf(f_doc,"[ ");
      print_string(c,0,1);
      fprintf(f_doc," ]\n");
    }
  }

  c = de->text.get();
  if (strlen(c)) {
    print_string(c,0,de->format);
  }
  fprintf(f_doc,"\n\n");
}

// -----------------------------------------------------------------------------
// void ASCII::newsection(DocEntry *de, int sectnum) 
// 
// Starts a new section.  Will underline major sections and subsections, but
// not minor subsections.
//
// Inputs : 
//          de      = Documentation entry of the section
//          sectnum = Section number.
//
// Output : None
//
// Side Effects :
//          Forces a new subsection to be created within the ASCII module.
// -----------------------------------------------------------------------------

void ASCII::newsection(DocEntry *de,int sectnum) {
  int i,len = 0;
  char temp[256];
  char *c;

  sect_num[sect_count] = sectnum;
  sect_count++;
  for (i = 0; i < sect_count; i++) {
    sprintf(temp,"%d.",sect_num[i]);
    fprintf(f_doc,"%s",temp);
    len += strlen(temp);
  }
  c = de->usage.get();
  fprintf(f_doc,"  %s\n", c);
  len += strlen(c) + 2;

  // Print an underline if this is a major category

  if (sect_count <= 1) {
    for (i = 0; i < len; i++) 
      fputc('=',f_doc);
    fputc('\n',f_doc);
  } else if (sect_count == 2) {
    for (i = 0; i < len; i++) 
      fputc('-',f_doc);
    fputc('\n',f_doc);
  } else {
    fputc('\n',f_doc);
  }
  
  // If there is any C annotation, print that
  if (de->print_info) {
    c = de->cinfo.get();
    if (strlen(c) > 0) {
      fprintf(f_doc,"[ ");
      print_string(c,0,1);
      fprintf(f_doc," ]\n\n");
    }
  }

  // If there is a description text. Print it

  c = de->text.get();
  if (strlen(c) > 0) {
    print_string(c,0,de->format);
    fprintf(f_doc,"\n");
  }
  fprintf(f_doc,"\n");
}

// -----------------------------------------------------------------------------
// void ASCII::endsection()
// 
// Ends the current section.  It is an error to call this without having first
// called newsection().
// 
// Inputs : None
//
// Output : None
//
// Side Effects : 
//          Pops out of the current section, moving back into the parent section
// -----------------------------------------------------------------------------

void ASCII::endsection() {
  if (sect_count > 0) sect_count--;
}

// -----------------------------------------------------------------------------
// void ASCII::separator()
// 
// Prints a small dashed line that is used to designate the end of C++ class
// subsections.
//
// Inputs : None
//
// Output : None
//
// Side Effects : None
// -----------------------------------------------------------------------------

void ASCII::separator() {
  int i;
  for (i = 0; i < 10; i++)
    fputc('-',f_doc);
  fprintf(f_doc,"\n\n");
}

// -----------------------------------------------------------------------------
// void ASCII::init(char *filename)
// 
// Initializes the documentation module and opens up the documentation file.
//
// Inputs : filename = name of documentation file (without suffix)
//
// Output : None
//
// Side Effects : Opens the documentation file.
// -----------------------------------------------------------------------------

void ASCII::init(char *filename) {
  char f[256];

  sprintf(f,"%s.doc",filename);
  sprintf(fn,"%s",filename);
  f_doc = fopen(f,"w");
  if (f_doc == NULL) {
    fprintf(stderr, "Unable to open %s\n", fn);
    SWIG_exit(1);
  }

}

// -----------------------------------------------------------------------------
// void ASCII::close() 
//
// Closes the documentation module.  This function should only be called once
// 
// Inputs : None
//
// Output : None
//
// Side Effects : Closes the documentation file.
// -----------------------------------------------------------------------------

void ASCII::close(void) {

  fclose(f_doc);
  if (Verbose) 
    fprintf(stderr,"Documentation written to %s.doc\n", fn);

}

// -----------------------------------------------------------------------------
// void ASCII::style(char *name, char *value) 
// 
// Looks for style parameters that the user might have supplied using the
// %style directive.   Unrecognized options are simply ignored.
//
// Inputs : 
//          name    = name of the style parameter
//          value   = value of the style parameter (optional)
//
// Output : None
//
// Side Effects : Can change internal settings of 'indent' and 'columns' members.
// -----------------------------------------------------------------------------

void ASCII::style(char *name, char *value) {
  if (strcmp(name,"ascii_indent") == 0) {
    if (value) {
      indent = atoi(value);
    }
  } else if (strcmp(name,"ascii_columns") == 0) {
    if (value) {
      columns = atoi(value);
    }
  }
}

// -----------------------------------------------------------------------------
// void ASCII::parse_args(int argc, char **argv) 
// 
// Function for processing options supplied on the SWIG command line.
//
// Inputs : 
//          argc = Number of arguments
//          argv = Argument strings
//
// Output : None
//
// Side Effects : May set various internal parameters.
// -----------------------------------------------------------------------------

static char *ascii_usage = "\
ASCII Documentation Options (available with -dascii)\n\
     None available.\n\n";

void ASCII::parse_args(int argc, char **argv) {
  int i;

  for (i = 0; i < argc; i++) {
    if (argv[i]) {
      if (strcmp(argv[i],"-help") == 0) {
	fputs(ascii_usage,stderr);
      }
    }
  }
}

/*******************************************************************************
 * -- Revision History
 * $Log: ascii.cxx,v $
 * Revision 1.14  1997/05/28 06:03:00  beazley
 * Moved revision history to end.
 *
 * Revision 1.13  1997/01/06 17:07:33  beazley
 * Reformatted to look nicer
 *
 * Revision 1.12  1996/12/26 04:40:24  beazley
 * Minor fixes
 *
 * Revision 1.11  1996/12/03 08:38:58  beazley
 * Major revision.  Pre-1.1b2 checkin.
 *
 * Revision 1.10  1996/11/12 19:49:29  beazley
 * Complete rewrite to support new documentation system
 *
 * Revision 1.9  1996/08/27 22:58:14  dmb
 * Minor fix to error handling
 *
 * Revision 1.8  1996/08/21 16:48:40  dmb
 * Minor cleanup to eliminate compiler warnings.
 *
 * Revision 1.7  1996/08/21 05:46:43  dmb
 * Minor cleanup of output
 *
 * Revision 1.6  1996/05/22 20:20:21  beazley
 * Fixed bug with uninitialized usage vars.
 *
 * Revision 1.5  1996/05/10  23:37:16  beazley
 * Cleaned up documentation a little bit.  Added support for text blocks.
 *
 * Revision 1.4  1996/03/16  06:25:25  beazley
 * Changed to work with new headers.
 *
 * Revision 1.3  1996/02/20  04:06:58  beazley
 * Took out streams stuff.
 *
 * Revision 1.2  1996/02/15  22:36:52  beazley
 * Changed copyright
 *
 * Revision 1.1  1996/02/07  05:24:20  beazley
 * Initial revision
 *
 *
 *******************************************************************************/

  
  
