/*
 * This file was generated automatically by xsubpp version 1.935 from the 
 * contents of Test1.xs. Don't edit this file, edit Test1.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#ifdef __cplusplus
extern "C" {
#endif
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#ifdef __cplusplus
}
#endif


XS(XS_produce_create)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: produce::create(nitems)");
    {
	int	nitems = (int)SvIV(ST(0));
	double *	RETVAL;
	double *a;
	int i;
	a = (double *) malloc(nitems*sizeof(double));
	for (i = 0; i < nitems; i++)
		a[i] = drand48();
	RETVAL = a;
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "doublePtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_produce_print_array)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: produce::print_array(a,nitems)");
    {
	double *	a;
	int	nitems = (int)SvIV(ST(1));

	if (sv_isa(ST(0), "doublePtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    a = (double *) tmp;
	}
	else
	    croak("a is not of type doublePtr");
	{
	int i;
	for (i = 0; i < nitems; i++)
		printf("a[%d] = %g\n", i,a[i]);
	}
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_produce)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXS("produce::create", XS_produce_create, file);
        newXS("produce::print_array", XS_produce_print_array, file);
    ST(0) = &sv_yes;
    XSRETURN(1);
}
