/*
 * $Header: /b2/dmb/SWIG/SWIG1.0b3/swig_lib/tcl/RCS/swigtcl.cfg,v 1.1 1996/05/22 19:47:45 beazley Exp $
 * 
 * swigtcl.cfg
 *
 * This file is modified from a platform independent file provided
 * by Sun.   With any luck this will allow SWIG generated wrapper
 * files to work on Unix, Windows, and Macintosh.
 *
 * Revision History
 * $Log: swigtcl.cfg,v $
 * Revision 1.1  1996/05/22 19:47:45  beazley
 * Initial revision
 *
 *
 * -- Dave Beazley, May 2, 1996.
 *
 *	This file is an example of a Tcl dynamically loadable extension.
 *
 * Copyright (c) 1996 by Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#if defined(__WIN32__)
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   undef WIN32_LEAN_AND_MEAN

/*
 * VC++ has an alternate entry point called DllMain, so we need to rename
 * our entry point.
 */

#   if defined(_MSC_VER)
#	define SWIGEXPORT(a,b) __declspec(dllexport) a b
#	define DllEntryPoint DllMain
#   else
#	if defined(__BORLANDC__)
#	    define SWIGEXPORT(a,b) a _export b
#	else
#	    define SWIGEXPORT(a,b) a b
#	endif
#   endif
#else
#   define SWIGEXPORT(a,b) a b
#endif

/*
 *----------------------------------------------------------------------
 *
 * DllEntryPoint --
 *
 *	This wrapper function is used by Windows to invoke the
 *	initialization code for the DLL.  If we are compiling
 *	with Visual C++, this routine will be renamed to DllMain.
 *	routine.
 *
 * Results:
 *	Returns TRUE;
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

#ifdef __WIN32__
BOOL APIENTRY
DllEntryPoint(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
    return TRUE;
}
#endif

