
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

/**************************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.1b5/Modules/RCS/guile.h,v 1.4 1997/03/08 23:51:08 beazley Exp $
 *
 * class GUILE
 *
 * Guile implementation
 * (Caution : This is *somewhat* experimental)
 *
 * Seeking : highly motivated individual with plenty of spare time and
 *           a love of Guile.   Must be willing to modify this code and
 *           make it better.
 *
 * $Log: guile.h,v $
 * Revision 1.4  1997/03/08 23:51:08  beazley
 * Updated to use the "gh" interface
 *
 * Revision 1.2  1997/01/06 17:12:35  beazley
 * Added support for typemaps and multiple inheritance
 *
 * Revision 1.1  1996/12/26 04:51:07  beazley
 * Initial revision
 *
 * Revision 1.7  1996/08/12 01:53:06  dmb
 * Changes to language class structure
 *
 * Revision 1.6  1996/05/13 23:46:52  beazley
 * Minor modifications to class structure for better module
 * support
 *
 * Revision 1.5  1996/03/28  02:47:59  beazley
 * Fixed to work with new class structure.
 *
 **************************************************************************/

class GUILE : public Language {
private:
  char   *guile_path;
  char   *module;
  void   get_pointer(char *iname, int parm, DataType *t);
  void   usage_var(char *, DataType *, char **);
  void   usage_func(char *, DataType *, ParmList *, char **);
  void   usage_const(char *, DataType *, char *, char **);
public :
  GUILE() {
     module = 0;
     guile_path = "guile";
  }
  void parse_args(int, char *argv[]);
  void parse();
  void create_function(char *, char *, DataType *, ParmList *);
  void link_variable(char *, char *, DataType *);
  void declare_const(char *, char *, DataType *, char *);
  void initialize();
  void headers(void);
  void close(void);
  void set_module(char *, char **);
  void set_init(char *);
  void create_command(char *, char *) { };
};




