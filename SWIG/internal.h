
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
 * The author requests that all users of this software return any
 * improvements made to beazley@cs.utah.edu and grant the author
 * full redistribution rights.
 *
 **************************************************************************/
/***********************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.1/SWIG/RCS/internal.h,v 1.27 1997/06/23 19:20:28 beazley Exp $
 *
 * internals.h
 *
 * Contains global variables used in libswig, but which are otherwise
 * inaccessible to the user.
 *
 ***********************************************************************/

#include "swig.h"

// -------------------------------------------------------------------
// class DocTitle : public DocEntry
//
// Top level class for managing documentation.     Prints out a title,
// date, etc...
// -------------------------------------------------------------------

class DocTitle : public DocEntry {
public:
  DocTitle(char *title, DocEntry *_parent);  // Create a new title
  void output(Documentation *d);             // Output documentation
};

// --------------------------------------------------------------------
// class DocSection : public DocEntry
//
// Documentation entry for a section
// --------------------------------------------------------------------

class DocSection : public DocEntry {
public:
  DocSection(char *section, DocEntry *_parent);
  void output(Documentation *d);
};

// --------------------------------------------------------------------
// class DocFunction : public DocEntry
//
// Documentation entry for generic sorts of declarations
// --------------------------------------------------------------------

class DocDecl : public DocEntry {
public:
  DocDecl(char *fname, DocEntry *_parent);
  DocDecl(DocEntry *de, DocEntry *_parent);
  void output(Documentation *d);
};

// --------------------------------------------------------------------
// class DocClass : public DocEntry
//
// Documentation entry for a C++ class or C struct
// --------------------------------------------------------------------

class DocClass : public DocEntry {
public:
  DocClass(char *classname, DocEntry *_parent);
  void output(Documentation *d);
};

// --------------------------------------------------------------------
// class DocText : public DocEntry
//
// Documentation entry for some plain ole text.  Declared using
// the %text %{,%} directive.
// --------------------------------------------------------------------

class DocText : public DocEntry {
public:
  DocText(char *_text, DocEntry *_parent);
  void output(Documentation *d);
};

// --------------------------------------------------------------------
// class CommentHandler
//
// Class for managing comment processing.
// --------------------------------------------------------------------

class CommentHandler {
public:
  CommentHandler();
  CommentHandler(CommentHandler *c);
  ~CommentHandler();
  void        add_comment(char *text, int line_num, int col, char *file); // Add a comment
  void        set_entry(DocEntry *d);                            // Set documentation entry
  static void cleanup();                                         // Clean-up everything before quitting
  void        style(char *name, char *value);
  void        parse_args(int argc, char **argv);                 // Parse command line options

  // Comment handling style parameters
  int           skip_lines;                   // # blank lines before comment is throw away
  int           location;                     // Comment location (BEFORE or AFTER)
  int           chop_top;                     // Lines to chop from the top of a comment
  int           chop_bottom;                  // Lines to chop from the bottom
  int           chop_left;                    // Characters to chop from left
  int           chop_right;                   // Characters to chop from right
  int           untabify;                     // Expand tabs
  int           ignore;                       // Ignore comments
};

#define   BEFORE     0
#define   AFTER      1


extern    int           include_file(char *);         // Insert library file
extern    char          category[256];
extern    char          title[256];
extern    DocEntry      *doc_entry;
extern    DocEntry      *doctitle;               // The very first docentry
extern    DocEntry       *doc_stack[256];             // Stack of documentation entries
extern    CommentHandler *handler_stack[256];         // Stack of comment handlers
extern    int            doc_stack_top;           // Top of stack

extern    Language      *lang;
extern    Documentation *doc;
extern    CommentHandler *comment_handler;      // Comment handling system
extern    void          swig_append(char *, FILE *);
extern    int           Stat_func, Stat_var, Stat_const;
extern    int           IgnoreDoc;
extern    int           ForceExtern;
extern    int           WrapExtern;
extern    String        CCode;
extern    int           GenerateDefault;
extern    int           type_id;
extern    char         *ConfigFile;
extern    char         *objc_construct;
extern    char         *objc_destruct;
extern    int           DocOnly;

// Structure for holding typemap parameters
// A typemap parameter consists of a single parameter (type + name)
// and an optional list of arguments corresponding to local variables.
// Has an optional link for building linked lists of parameter lists

struct TMParm {
  Parm     *p;
  ParmList *args;
  TMParm   *next;
  TMParm() {
    next = 0;
  }
};

/* Global variables.   Needs to be cleaned up */

#ifdef WRAP

    FILE      *f_header;                        // Some commonly used
    FILE      *f_wrappers;                      // FILE pointers
    FILE      *f_init;
    FILE      *f_input;
    char      InitName[256];             
    char      LibDir[512];                      // Library directory
    char     **InitNames = 0;
    int       Status; 
    int       TypeStrict;                       // Type checking strictness
    int       Verbose;
    char       category[256];                   // Variables for documentation
    char       title[256];
    DocEntry  *doc_entry = 0;                   // Current documentation entry
    DocEntry  *doctitle = 0;                    // First doc entry
    DocEntry       *doc_stack[256];             // Stack of documentation entries
    CommentHandler *handler_stack[256];         // Stack of comment handlers
    int            doc_stack_top = 0;           // Top of stack

    Language  *lang;                            // Language method
    Documentation  *doc;                        // Documentation method
    int        Stat_func = 0;
    int        Stat_var = 0;
    int        Stat_const = 0;
    int        CPlusPlus = 0;
    int        ObjC = 0;
    int        ObjCClass = 0;
    int        AddMethods = 0;                  // AddMethods flag
    int        NewObject = 0;                   // NewObject flag
    int        Inline = 0;                      // Inline mode
    int        Stats = 0;
    int        IgnoreDoc = 0;                   // Ignore documentation mode
    int        ForceExtern = 0;                 // Force extern mode
    int        WrapExtern = 0;
    int        GenerateDefault = 0;            // Generate default constructors
    char      *Config = 0;
    int        NoInclude = 0;
    char      *typemap_lang = 0;                // Typemap name
    int        type_id = 0;                     // Type identifier
    int        error_count = 0;                 // Error count
    char      *ConfigFile = 0;
    int        DocOnly = 0;                     // Only produce documentation

#endif

/* Number of initialization names that can be used */

#define NI_NAMES    512

extern void type_undefined_check(void);

/***********************************************************************
 *
 * -- Revision History
 * $Log: internal.h,v $
 * Revision 1.27  1997/06/23 19:20:28  beazley
 * Added DocOnly flag.
 *
 * Revision 1.26  1997/06/20 05:24:46  beazley
 * Added objective-C constructor variables.
 *
 * Revision 1.25  1997/05/28 21:12:30  beazley
 * Moved revision history to the end.
 *
 * Revision 1.24  1997/05/25 23:06:44  beazley
 * Added objective-C flags
 *
 * Revision 1.23  1997/05/05 15:52:49  beazley
 * Added a TMParm structure for extended parsing of typemaps.
 *
 * Revision 1.22  1997/04/23 04:59:36  beazley
 * Minor updates
 *
 * Revision 1.21  1997/03/29 17:41:38  beazley
 * Added error_count variable.
 *
 * Revision 1.20  1997/03/02 22:44:59  beazley
 * Minor changes
 *
 * Revision 1.19  1997/01/08 01:25:34  beazley
 * Added typemap variable
 *
 * Revision 1.18  1997/01/06 17:11:35  beazley
 * Changed names of a few internal functions
 *
 * Revision 1.17  1996/12/26 04:45:36  beazley
 * Cleaned up a few things.  Added Inline parameter.
 *
 * Revision 1.16  1996/12/05 00:52:03  beazley
 * A few minor tweaks.
 *
 * Revision 1.15  1996/12/03 08:40:28  beazley
 * pre-1.1b2 checkin
 *
 * Revision 1.14  1996/11/26 04:09:51  beazley
 * Fixes for documentation system
 *
 * Revision 1.13  1996/11/12 19:53:57  beazley
 * Added some new variables and classes for documentation system
 *
 * Revision 1.12  1996/09/26 21:48:39  dmb
 * Added new variable for external wrapping
 *
 * Revision 1.11  1996/08/15 05:05:50  dmb
 * Added some more internal variables
 *
 * Revision 1.10  1996/08/12 01:53:06  dmb
 * Changes to language class structure
 *
 * Revision 1.9  1996/05/17 05:51:40  beazley
 * *** empty log message ***
 *
 * Revision 1.8  1996/05/13  23:47:20  beazley
 * A few minor changes
 *
 * Revision 1.7  1996/05/10  23:39:12  beazley
 * Removed a few obsolete variables
 *
 * Revision 1.6  1996/05/03  05:11:59  dmb
 * Added CPlusPlus flag
 *
 * Revision 1.5  1996/04/08 19:44:50  beazley
 * Added stats variables.
 *
 * Revision 1.4  1996/04/03  22:49:11  beazley
 * Added IgnoreComments variable.
 *
 * Revision 1.3  1996/03/24  22:15:23  beazley
 * Added declaration of swig_append().
 *
 * Revision 1.2  1996/03/22  23:43:12  beazley
 * Cleaned this up.
 *
 * Revision 1.1  1996/03/16  06:30:22  beazley
 * Initial revision
 *
 *
 ***********************************************************************/
