#ifdef __cplusplus
extern "C" {
#endif
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#ifdef __cplusplus
}
#endif


MODULE = produce		PACKAGE = produce

double *
create(nitems)
	int nitems
	CODE:
	double *a;
	int i;
	a = (double *) malloc(nitems*sizeof(double));
	for (i = 0; i < nitems; i++)
		a[i] = drand48();
	RETVAL = a;
	OUTPUT:
	RETVAL

void
print_array(a,nitems)
	double *a
	int	nitems
	CODE:
	{
	int i;
	for (i = 0; i < nitems; i++)
		printf("a[%d] = %g\n", i,a[i]);
	}
	

