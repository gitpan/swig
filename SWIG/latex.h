
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
/***********************************************************************
 * $Header: /home/beazley/SWIG/SWIG1.1b3/SWIG/RCS/latex.h,v 1.4 1996/12/26 04:45:36 beazley Exp $
 *
 * latex.h
 *
 * Latex specific functions for producing documentation.
 *
 * -- Revision History
 * $Log: latex.h,v $
 * Revision 1.4  1996/12/26 04:45:36  beazley
 * Fixed function prototype bug
 *
 * Revision 1.3  1996/12/03 08:40:28  beazley
 * pre-1.1b2 checkin
 *
 * Revision 1.2  1996/02/15 22:35:18  beazley
 * Changed copyright
 *
 * Revision 1.1  1996/02/07  05:24:56  beazley
 * Initial revision
 *
 *
 ***********************************************************************/
class LATEX : public Documentation {
private:
  FILE  *f_doc;
  String s_doc;
  char  fn[256];
  char *start_tag(char *);
  char *end_tag(char *);
  void  print_string(char *s, String &str);
  int   sect_count;      // Section counter
  int   sect_num[20];    // Section numbers
  // Style parameters

  char  *tag_parindent;
  char  *tag_textwidth;
  char  *tag_documentstyle;
  char  *tag_oddsidemargin;
  char  *tag_title;
  char  *tag_preformat;
  char  *tag_usage;
  char  *tag_descrip;
  char  *tag_text;
  char  *tag_cinfo;
  char  *tag_pagestyle;
  char  *tag_section;
  char  *tag_subsection;
  char  *tag_subsubsection;

public:
  LATEX();
  void parse_args(int argc, char **argv);
  void title(DocEntry *de);
  void newsection(DocEntry *de, int sectnum);
  void endsection();
  void print_decl(DocEntry *de);
  void print_text(DocEntry *de);
  void separator();
  void init(char *filename);
  void close(void);
  void style(char *name, char *value);
};


       
      



    
    
  






  
  
