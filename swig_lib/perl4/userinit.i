//
// $Header: /b2/dmb/SWIG/SWIG1.0b3/swig_lib/perl4/RCS/userinit.i,v 1.1 1996/05/22 20:01:02 beazley Exp $
// SWIG interface file for building a perl4 module.
// Supplies the userinit() function needed for initialization.
//
/* Revision History
 * $Log: userinit.i,v $
 * Revision 1.1  1996/05/22 20:01:02  beazley
 * Initial revision
 *
 */

%{
int userinit() {
  int SWIG_init();
  return SWIG_init();
}
%}

