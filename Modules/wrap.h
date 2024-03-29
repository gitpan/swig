
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
 * $Header: /home/beazley/SWIG/SWIG1.1b3/Modules/RCS/wrap.h,v 1.3 1997/01/06 17:12:35 beazley Exp $
 *
 * wrap.h
 *
 * -- Revision History
 * $Log: wrap.h,v $
 * Revision 1.3  1997/01/06 17:12:35  beazley
 * Minor changes
 *
 * Revision 1.2  1996/08/21 05:51:53  dmb
 * minor changes
 *
 * Revision 1.1  1996/03/16 06:32:42  beazley
 * Initial revision
 *
 ***********************************************************************/

#include "swig.h"

#ifndef SWIG_LIB
#define SWIG_LIB = "./swig_lib"
#endif

#ifndef SWIG_LANG
#define SWIG_LANG TCL
#endif

#ifndef SWIG_DOC
#define SWIG_DOC ASCII
#endif

