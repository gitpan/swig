/* Definitions for compiling Perl extensions on a variety of machines */

#if defined(WIN32) || defined(__WIN32__)
#   if defined(_MSC_VER)
#	define SWIGEXPORT(a,b) __declspec(dllexport) a b
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

#ifdef PERL_OBJECT
#define MAGIC_PPERL  CPerl *pPerl = (CPerl *) this;
#define MAGIC_CAST   (int (CPerl::*)(SV *, MAGIC *))
#define SWIGCLASS_STATIC 
#else
#define MAGIC_PPERL
#define MAGIC_CAST
#define SWIGCLASS_STATIC static
#endif


