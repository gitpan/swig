//
// $Header: /b2/dmb/SWIG/SWIG1.0b3/swig_lib/tcl/RCS/expect.i,v 1.1 1996/05/22 19:47:45 beazley Exp $
// SWIG File for building expect
// Dave Beazley
// March 18, 1996
//
/* Revision History
 * $Log: expect.i,v $
 * Revision 1.1  1996/05/22 19:47:45  beazley
 * Initial revision
 *
 */

#ifdef AUTODOC
%subsection "expect.i"
%text %{
This module provides a main() function for building an extended version of
Expect.  It has been tested with Expect 5.19, but may need modification
for newer versions.
%}
#endif


%{

/* main.c - main() and some logging routines for expect

Written by: Don Libes, NIST, 2/6/90

Design and implementation of this program was paid for by U.S. tax
dollars.  Therefore it is public domain.  However, the author and NIST
would appreciate credit if this program or parts of it are used.
*/

#include "expect_cf.h"
#include <stdio.h>
#include INCLUDE_TCL
#include "expect_tcl.h"

void
main(argc, argv)
int argc;
char *argv[];
{
	int rc = 0;
	Tcl_Interp *interp = Tcl_CreateInterp();
	int SWIG_init(Tcl_Interp *);

	if (Tcl_Init(interp) == TCL_ERROR) {
		fprintf(stderr,"Tcl_Init failed: %s\n",interp->result);
		exit(1);
	}

	if (Exp_Init(interp) == TCL_ERROR) {
		fprintf(stderr,"Exp_Init failed: %s\n",interp->result);
		exit(1);
	}

	/* SWIG initialization. --- 2/11/96  */

	if (SWIG_init(interp) == TCL_ERROR) {
	        fprintf(stderr,"SWIG initialization failed: %s\n", interp->result);
		exit(1);
	}

	exp_parse_argv(interp,argc,argv);

	/* become interactive if requested or "nothing to do" */
	if (exp_interactive)
		(void) exp_interpreter(interp);
	else if (exp_cmdfile)
		rc = exp_interpret_cmdfile(interp,exp_cmdfile);
	else if (exp_cmdfilename)
		rc = exp_interpret_cmdfilename(interp,exp_cmdfilename);

	/* assert(exp_cmdlinecmds != 0) */

	exp_exit(interp,rc);
	/*NOTREACHED*/
}

%}
