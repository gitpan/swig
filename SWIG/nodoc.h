
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
 * $Header: /home/beazley/SWIG/SWIG1.1b2/SWIG/RCS/nodoc.h,v 1.2 1996/11/12 19:53:57 beazley Exp $
 *
 * nodoc.h
 *
 * A null documentation header.  Does nothing.
 *
 * -- Revision History
 * $Log: nodoc.h,v $
 * Revision 1.2  1996/11/12 19:53:57  beazley
 * Modified to use new documentation system
 *
 * Revision 1.1  1996/03/22 23:43:23  beazley
 * Initial revision
 *
 *
 ***********************************************************************/

class NODOC : public Documentation {
private:
public:
  NODOC() { };
  void parse_args(int, char **) { };
  void title(DocEntry *) { };
  void newsection(DocEntry *, int) { };
  void endsection() { };
  void print_decl(DocEntry *) { };
  void print_text(DocEntry *) { };
  void separator() { };
  void init(char *) { };
  void close(void) { };
  void style(char *, char *) { };
};

    
      



    
    
  






  
  
