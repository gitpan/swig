
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
 * $Header: /home/beazley/SWIG/SWIG1.1/SWIG/RCS/main.cxx,v 1.49 1997/06/23 21:18:13 beazley Exp $
 *
 * main.cxx
 *
 * The main program.
 *
 ***********************************************************************/

#define WRAP

#include "internal.h"
#include "ascii.h"
#include "latex.h"
#include "html.h"
#include "nodoc.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

class SwigException {};

static char *usage = "\
\nDocumentation Options\n\
     -dascii         - ASCII documentation.\n\
     -dhtml          - HTML documentation.\n\
     -dlatex         - LaTeX documentation.\n\
     -dnone          - No documentation.\n\n\
General Options\n\
     -c              - Produce raw wrapper code (omit support code)\n\
     -c++            - Enable C++ processing\n\
     -ci             - Check a file into the SWIG library\n\
     -co             - Check a file out of the SWIG library\n\
     -d docfile      - Set name of the documentation file.\n\
     -Dsymbol        - Define a symbol (for conditional compilation)\n\
     -I<dir>         - Look for SWIG files in <dir>\n\
     -l<ifile>       - Include SWIG library file.\n\
     -make_default   - Create default constructors/destructors\n\
     -nocomment      - Ignore all comments (for documentation).\n\
     -o outfile      - Set name of the output file.\n\
     -objc           - Enable Objective C processing\n\
     -stat           - Print statistics\n\
     -strict n       - Set pointer type-checking strictness\n\
     -swiglib        - Report location of SWIG library and exit\n\
     -t typemap_file - Use a typemap file.\n\
     -v              - Run in verbose mode\n\
     -version        - Print SWIG version number\n\
     -help           - This output.\n\n";

//-----------------------------------------------------------------
// main()
//
// Main program.    Initializes the files and starts the parser.
//-----------------------------------------------------------------

char  infilename[256];
char  filename[256];
char  fn_header[256];
char  fn_wrapper[256];
char  fn_init[256];
char  output_dir[512];

#ifdef MACSWIG
FILE  *swig_log;
#endif

char *SwigLib;

int SWIG_main(int argc, char *argv[], Language *l, Documentation *d) {

  int    i;
  char   *c;
  extern  FILE   *LEX_in;
  extern  void   add_directory(char *);
  extern  char   *get_time();
  char    temp[512];
  char    infile[512];

  char   *outfile_name = 0;
  extern  int add_iname(char *);
  int     help = 0;
  int     ignorecomments = 0;
  int     checkout = 0;
  int     checkin = 0;
  char   *typemap_file = 0;

  extern  void check_suffix(char *);
  extern  void scanner_file(FILE *);

#ifdef MACSWIG
  try {
#endif

  f_wrappers = 0;
  f_init = 0;
  f_header = 0;

  lang = l;
  doc = d;
  Status = 0;
  TypeStrict = 2;                   // Very strict type checking
  Verbose = 0;
  char    *doc_file = 0;
  
  DataType::init_typedef();         // Initialize the type handler

  // Set up some default symbols (available in both SWIG interface files
  // and C files)

  add_symbol("SWIG",0,0);            // Define the SWIG symbol
#ifdef MACSWIG
  add_symbol("SWIGMAC",0,0);
#endif
#ifdef SWIGWIN32
  add_symbol("SWIGWIN32",0,0);
#endif
  
  // Check for SWIG_LIB environment variable

  if ((c = getenv("SWIG_LIB")) == (char *) 0) {
      sprintf(LibDir,"%s",SWIG_LIB);    // Build up search paths
  } else {
      strcpy(LibDir,c);
  }
  
  SwigLib = copy_string(LibDir);        // Make a copy of the real library location
#ifdef MACSWIG
  sprintf(temp,"%s:config", LibDir);
  add_directory(temp);
  add_directory(":swig_lib:config");
  add_directory(LibDir);
  add_directory(":swig_lib");
#else
  sprintf(temp,"%s/config", LibDir);
  add_directory(temp);
  add_directory("./swig_lib/config");
  add_directory(LibDir);
  add_directory("./swig_lib");
  sprintf(InitName,"init_wrap");
#endif

  sprintf(InitName,"init_wrap");  

  // Get options
  for (i = 1; i < argc; i++) {
      if (argv[i]) {
	  if (strncmp(argv[i],"-I",2) == 0) {
	    // Add a new directory search path 
	    add_directory(argv[i]+2);
	    mark_arg(i);
	  } else if (strncmp(argv[i],"-D",2) == 0) {
	    // Create a symbol
	    add_symbol(argv[i]+2, (DataType *) 0, (char *) 0);
	    mark_arg(i);
	  } else if (strcmp(argv[i],"-strict") == 0) {
	    if (argv[i+1]) {
	      TypeStrict = atoi(argv[i+1]);
	      mark_arg(i);
	      mark_arg(i+1);
	      i++;
	    } else {
	      arg_error();
	    }
	  } else if ((strcmp(argv[i],"-verbose") == 0) || (strcmp(argv[i],"-v") == 0)) {
	      Verbose = 1;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-dascii") == 0) {
	      doc = new ASCII;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-dnone") == 0) {
	      doc = new NODOC;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-dhtml") == 0) {
	      doc = new HTML;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-dlatex") == 0) {
	      doc = new LATEX;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-nocomment") == 0) {
	      ignorecomments = 1;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-stat") == 0) {
	      Stats=1;
	      mark_arg(i);
	  } else if (strcmp(argv[i],"-c++") == 0) {
	      CPlusPlus=1;
	      mark_arg(i);  
          } else if (strcmp(argv[i],"-objc") == 0) {
	      ObjC = 1;
              mark_arg(i);
	  } else if (strcmp(argv[i],"-c") == 0) {
	      NoInclude=1;
	      mark_arg(i);
          } else if (strcmp(argv[i],"-make_default") == 0) {
	    GenerateDefault = 1;
	    mark_arg(i);
          } else if (strcmp(argv[i],"-swiglib") == 0) {
	    printf("%s\n", LibDir);
	    SWIG_exit(0);
	  } else if (strcmp(argv[i],"-o") == 0) {
	      mark_arg(i);
	      if (argv[i+1]) {
		outfile_name = copy_string(argv[i+1]);
		mark_arg(i+1);
		i++;
	      } else {
		arg_error();
	      }
	  } else if (strcmp(argv[i],"-d") == 0) {
	      mark_arg(i);
	      if (argv[i+1]) {
		doc_file = copy_string(argv[i+1]);
		mark_arg(i+1);
		i++;
	      } else {
		arg_error();
	      }
	  } else if (strcmp(argv[i],"-t") == 0) {
	      mark_arg(i);
	      if (argv[i+1]) {
		typemap_file = copy_string(argv[i+1]);
		mark_arg(i+1);
		i++;
	      } else {
		arg_error();
	      }
	  } else if (strcmp(argv[i],"-version") == 0) {
 	      fprintf(stderr,"\nSWIG Version %d.%d %s\n", SWIG_MAJOR_VERSION,
		      SWIG_MINOR_VERSION, SWIG_SPIN);
	      fprintf(stderr,"Copyright (c) 1995-98\n");
	      fprintf(stderr,"University of Utah and the Regents of the University of California\n");
	      fprintf(stderr,"\nCompiled with %s\n", SWIG_CC);
	      SWIG_exit(0);
	  } else if (strncmp(argv[i],"-l",2) == 0) {
	    // Add a new directory search path 
	    library_add(argv[i]+2);
	    mark_arg(i);
          } else if (strcmp(argv[i],"-co") == 0) {
	    checkout = 1;
	    mark_arg(i);
	  } else if (strcmp(argv[i],"-ci") == 0) {
	    checkin = 1;
	    mark_arg(i);
	  } else if (strcmp(argv[i],"-help") == 0) {
	    fputs(usage,stderr);
	    mark_arg(i);
	    help = 1;
	  }
      }
  }

  // Create a new documentation handler

  if (doc == 0) doc = new ASCII;  

  // Open up a comment handler

  comment_handler = new CommentHandler();
  comment_handler->parse_args(argc,argv);
  if (ignorecomments) comment_handler->style("ignore",0);

  // Create a new documentation entry

  doctitle = new DocTitle("",0);
  doctitle->parse_args(argc,argv);
  doc_entry = doctitle;

  // Handle documentation module options

  doc->parse_args(argc,argv);

  // Parse language dependent options

  lang->parse_args(argc,argv);

  if (help) SWIG_exit(0);              // Exit if we're in help mode

  // Check all of the options to make sure we're cool.
  
  check_options();

  // If we made it this far, looks good. go for it....

  // Create names of temporary files that are created

  sprintf(infilename,"%s", argv[argc-1]);
  input_file = new char[strlen(infilename)+1];
  strcpy(input_file, infilename);

  // If the user has requested to check out a file, handle that

  if (checkout) {
    int stat;
    char *outfile = input_file;
    if (outfile_name)
      outfile = outfile_name;
    stat = checkout_file(input_file,outfile);
    if (!stat) {
      fprintf(stderr,"%s checked out from the SWIG library\n",input_file);
    } else {
      FILE * f = fopen(input_file,"r");
      if (f) {
	fprintf(stderr,"Unable to check-out %s. File already exists.\n", input_file);
	fclose(f);
      } else {
	fprintf(stderr,"Unable to check-out %s\n", input_file);
      }
    }
  } else if (checkin) {
    // Try to check-in a file to the SWIG library
    int stat;
    char *outname = input_file;
    if (outfile_name)
      outname = outfile_name;
    stat = checkin_file(SwigLib, LibDir, input_file, outname);
    if (!stat) {
      fprintf(stderr,"%s checked-in to %s/%s/%s\n", input_file, SwigLib, LibDir, outname);
    } else {
      fprintf(stderr,"Unable to check-in %s to %s/%s\n", input_file, SwigLib, LibDir);
    }
  } else {
    doctitle->file = copy_string(input_file);
    doctitle->line_number = -1000;
    doctitle->end_line = -1000;
    
    // Check the suffix for a .c file.  If so, we're going to 
    // declare everything we see as "extern"
    
    check_suffix(infilename);
    
    // Strip off suffix 
    
    c = infilename + strlen(infilename);
    while (c != infilename) {
      if (*c == '.') {
	*c = 0;
	break;
      } else {
	c--;
      }
    }

    if (!outfile_name) {
      sprintf(fn_header,"%s_wrap.c",infilename);
      strcpy(infile,infilename);
      strcpy(output_dir,"");
    } else {
      sprintf(fn_header,"%s",outfile_name);
      // Try to identify the output directory
      char *cc = outfile_name;
      char *lastc = outfile_name;
      while (*cc) {
#ifdef MACSWIG
	if (*cc == ':') lastc = cc+1;
#else
	if (*cc == '/') lastc = cc+1;
#endif
	cc++;
      }
      cc = outfile_name;
      char *dd = output_dir;
      while (cc != lastc) {
	*dd = *cc;
	dd++;
	cc++;
      }
      *dd = 0;
      // Patch up the input filename
      cc = infilename + strlen(infilename);
      while (cc != infilename) {
#ifdef MACSWIG
	if (*cc == ':') {
	  cc++;
	  break;
	}
#else
	if (*cc == '/') {
	  cc++;
	  break;
	}
#endif
	cc--;
      }
      strcpy(infile,cc);
    }

    sprintf(fn_wrapper,"%s%s_wrap.wrap",output_dir,infile);
    sprintf(fn_init,"%s%s_wrap.init",output_dir,infile);
    
    sprintf(title,"%s", fn_header);
    
    // Open up files
    
    if ((f_input = fopen(input_file,"r")) == 0) {
      // Okay. File wasn't found right away.  Let's see if we can
      // extract it from the SWIG library instead.
      if ((checkout_file(input_file,input_file)) == -1) {
	fprintf(stderr,"Unable to open %s\n", input_file);
	SWIG_exit(0);
      } else {
	// Successfully checked out a file from the library, print a warning and
        // continue
	checkout = 1;
	fprintf(stderr,"%s checked out from the SWIG library.\n",input_file);
	if ((f_input = fopen(input_file,"r")) == 0) {
	  fprintf(stderr,"Unable to open %s\n", input_file);
	  SWIG_exit(0);
	}
      }
    }
    
    // Add to the include list
    
    add_iname(infilename);

    // Initialize the scanner
    
    LEX_in = f_input;
    scanner_file(LEX_in);
    
//    printf("fn_header = %s\n", fn_header);
//    printf("fn_wrapper = %s\n", fn_wrapper);
//    printf("fn_init = %s\n", fn_init);

    if((f_header = fopen(fn_header,"w")) == 0) {
      fprintf(stderr,"Unable to open %s\n", fn_header);
      exit(0);
    }
    if((f_wrappers = fopen(fn_wrapper,"w")) == 0) {
      fprintf(stderr,"Unable to open %s\n",fn_wrapper);
      exit(0);
    }
    if ((f_init = fopen(fn_init,"w")) == 0) {
      fprintf(stderr,"Unable to open %s\n",fn_init);
      exit(0);
    }
    
    // Open up documentation
    
    if (doc_file) {
      doc->init(doc_file);
    } else {
      doc_file = new char[strlen(infile)+strlen(output_dir)+8];
      sprintf(doc_file,"%s%s_wrap",output_dir,infile);
      doc->init(doc_file);
    }
    
    // Set up the typemap for handling new return strings
    {
      DataType *temp_t = new DataType(T_CHAR);
      temp_t->is_pointer++;
      if (CPlusPlus) 
	typemap_register("newfree",typemap_lang,temp_t,"","delete [] $source;\n",0);
      else 
	typemap_register("newfree",typemap_lang,temp_t,"","free($source);\n",0);

      delete temp_t;
    }

    // Define the __cplusplus symbol
    if (CPlusPlus)
      add_symbol("__cplusplus",0,0);           


    // Load up the typemap file if given

    if (typemap_file) {
      if (include_file(typemap_file) == -1) {
	fprintf(stderr,"Unable to locate typemap file %s.  Aborting.\n", typemap_file);
	SWIG_exit(1);
      }
    }

    // If in Objective-C mode.  Load in a configuration file

    if (ObjC) {
      // Add the 'id' object type as a void *
      /*      DataType *t = new DataType(T_VOID);
      t->is_pointer = 1;
      t->implicit_ptr = 0;
      t->typedef_add("id");
      delete t;
      */
    }

    // Pass control over to the specific language interpreter    

    lang->parse();
    
    fclose(f_wrappers);
    fclose(f_init);
    
    swig_append(fn_wrapper,f_header);
    swig_append(fn_init,f_header);
    
    fclose(f_header);
    
    // Print out documentation.  Due to tree-like nature of documentation,
    // printing out the title prints out everything.
    
    while(doctitle) {
      doctitle->output(doc);
      doctitle = doctitle->next;
    }
    
    doc->close();
    
    // Remove temporary files
    
    remove(fn_wrapper);
    remove(fn_init);

    // If only producing documentation, remove the wrapper file as well

    if (DocOnly) 
      remove(fn_header);

    // Check for undefined types that were used.

    if (Verbose)
      type_undefined_check();

    if (Stats) {
      fprintf(stderr,"Wrapped %d functions\n", Stat_func);
      fprintf(stderr,"Wrapped %d variables\n", Stat_var);
      fprintf(stderr,"Wrapped %d constants\n", Stat_const);
      type_undefined_check();
    }

    if (checkout) {
      // File was checked out from the SWIG library.   Remove it now
      remove(input_file);
    }
  }
#ifdef MACSWIG
  fclose(swig_log);
  } catch (SwigException) {
    fclose(swig_log);
  }
#else
  exit(error_count);
#endif
  return(error_count);
}

// --------------------------------------------------------------------------
// SWIG_exit()
//
// Fatal parser error. Exit and cleanup
// --------------------------------------------------------------------------

void SWIG_exit(int) {

  if (f_wrappers) {
    fclose(f_wrappers);
    remove(fn_wrapper);
  }
  if (f_header) {
    fclose(f_header);
    remove(fn_header);
  }
  if (f_init) {
    fclose(f_init);
    remove(fn_init);
  }
#ifndef MACSWIG
  exit(1);
#else
  throw SwigException();
#endif
}


// --------------------------------------------------------------------------
// swig_pragma(char *name, char *value)
//
// Handle pragma directives.  Not many supported right now
// --------------------------------------------------------------------------

void swig_pragma(char *name, char *value) {
  
  if (strcmp(name,"make_default") == 0) {
    GenerateDefault = 1;
  }
  if (strcmp(name,"no_default") == 0) {
    GenerateDefault = 0;
  }
  if (strcmp(name,"objc_new") == 0) {
    objc_construct = copy_string(value);
  }
  if (strcmp(name,"objc_delete") == 0) {
    objc_destruct = copy_string(value);
  }
}

/***********************************************************************
 *
 * -- Revision History
 * $Log: main.cxx,v $
 * Revision 1.49  1997/06/23 21:18:13  beazley
 * Added support for %doconly directive.
 *
 * Revision 1.48  1997/06/22 20:50:18  beazley
 * Added -swiglib option.
 *
 * Revision 1.47  1997/06/20 05:22:21  beazley
 * Added -ci and -t options.  Minor changes related to Objective-C.
 *
 * Revision 1.46  1997/05/28 16:15:45  beazley
 * Moved revision history to end.
 *
 * Revision 1.45  1997/05/25 23:05:47  beazley
 * Added objective-C option and setup.
 *
 * Revision 1.44  1997/05/05 15:57:35  beazley
 * Added a SWIGMAC and SWIGWIN32 symbols.
 *
 * Revision 1.43  1997/05/02 22:05:11  beazley
 * Added SWIGMAC and SWIGWIN32 symbols
 *
 * Revision 1.42  1997/04/19 21:59:24  beazley
 * Added __cplusplus symbol.   Added default typemaps for freeing and releasing
 * character strings.
 *
 * Revision 1.41  1997/03/29 17:41:27  beazley
 * Fixed error handling.
 *
 * Revision 1.40  1997/03/24 22:40:18  beazley
 * Some improvements to error recovery
 *
 * Revision 1.39  1997/03/12 05:03:09  beazley
 * Added the -l option.
 *
 * Revision 1.38  1997/03/02 22:40:12  beazley
 * Removed warning messages
 *
 * Revision 1.37  1997/02/16 20:15:29  beazley
 * Added support for the Macintosh
 *
 * Revision 1.36  1997/01/15 05:46:13  beazley
 * Added initialization of typedef handler.
 *
 * Revision 1.35  1997/01/06 17:08:17  beazley
 * Some slight cleanup.   New '-c' option added
 *
 * Revision 1.34  1996/12/05 00:51:45  beazley
 * A few minor bug fixes
 *
 * Revision 1.33  1996/12/03 08:38:58  beazley
 * pre-1.1b2 checkin
 *
 * Revision 1.32  1996/11/26 04:08:16  beazley
 * Some changes to fix problems with the documentation system.
 *
 * Revision 1.31  1996/11/12 19:49:29  beazley
 * Major changes to support new documentation system and a few new
 * command line options.
 *
 * Revision 1.30  1996/10/26 05:04:17  beazley
 * Fixed compiler warning in SWIG_exit()
 *
 * Revision 1.29  1996/10/07 20:04:34  beazley
 * Added SWIG symbol definition
 *
 * Revision 1.28  1996/08/27 22:59:17  dmb
 * Minor changes to error handling
 *
 * Revision 1.27  1996/08/26 16:30:55  dmb
 * Minor fixes to command line processing
 *
 * Revision 1.26  1996/08/21 16:48:40  dmb
 * Minor cleanup to eliminate compiler warnings.
 *
 * Revision 1.25  1996/08/21 05:48:16  dmb
 * Fixed -v option
 *
 * Revision 1.24  1996/08/15 05:04:55  dmb
 * Minor cleanup
 *
 * Revision 1.23  1996/08/12 01:48:57  dmb
 * Lot's of changes---mainly to finally support proper handling of command
 * line options.
 *
 * Revision 1.22  1996/05/22 20:20:21  beazley
 * Cleaned up file output.  Moved SWIG banner into the language modules.
 *
 * Revision 1.21  1996/05/20  23:37:00  beazley
 * Added -o option
 *
 * Revision 1.20  1996/05/17  05:54:14  beazley
 * Added -dirty option.   Might take it out though....
 *
 * Revision 1.19  1996/05/13  23:44:26  beazley
 * Added path for configuration files.
 *
 * Revision 1.18  1996/05/10  23:38:06  beazley
 * Took out some obsolete various (Wrap_Only and Wrap_Extern)
 *
 * Revision 1.17  1996/05/03  22:28:45  dmb
 * Added SWIG_LIB environment variables.
 *
 * Revision 1.16  1996/05/03 05:11:46  dmb
 * Added -c++ option.
 *
 * Revision 1.15  1996/05/01 22:40:56  dmb
 * Cleaned up command line option handling.
 *
 * Revision 1.14  1996/04/14 15:23:53  dmb
 * Fixed header files.
 *
 * Revision 1.13  1996/04/08 19:44:15  beazley
 * Added -stat option.
 *
 * Revision 1.12  1996/04/03  22:48:38  beazley
 * Minor fixes.
 *
 * Revision 1.11  1996/03/28  02:47:05  beazley
 * Added -version option.
 *
 * Revision 1.10  1996/03/24  22:14:38  beazley
 * Cleaned up file construction.
 *
 * Revision 1.9  1996/03/22  23:40:40  beazley
 * Added -dnone option.  A few minor fixes.
 *
 * Revision 1.8  1996/03/16  06:26:24  beazley
 * Major changes.   Took out language dependence.   Changed
 * main() to SWIG_main() that can be called by the user.
 *
 * Revision 1.7  1996/02/20  04:15:54  beazley
 * Took out streams.
 *
 * Revision 1.6  1996/02/19  05:32:24  beazley
 * Add call to print hex conversion functions.
 *
 * Revision 1.5  1996/02/17  23:37:58  beazley
 * Fixed problem with printing titles for documentation.
 *
 * Revision 1.4  1996/02/17  22:55:04  beazley
 * Cleaned up output a little bit.
 *
 * Revision 1.3  1996/02/16  05:20:22  beazley
 * Minor changes.  Added Perl5 support.
 *
 * Revision 1.2  1996/02/15  22:36:13  beazley
 * Minor bug fixes. changed copyright.
 *
 * Revision 1.1  1996/02/12  08:19:06  beazley
 * Initial revision
 *
 *
 ***********************************************************************/
