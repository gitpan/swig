// Use a typemap to allow a C program to operate on a 
// Perl5 scalar reference.

%module passref

%typemap(perl5,in) int * {
  SV* tempsv;
  static int ivalue;
  if (!SvROK($source)) {
    croak("expected a reference\n");
  }
  tempsv = SvRV($source);
  if (SvTYPE(tempsv) != SVt_IV) {
    croak("expected a integer reference\n");
  }
  ivalue = SvIV(tempsv);
  $target = &ivalue;
}

%typemap(perl5,argout) int * {
  SV *tempsv;
  tempsv = SvRV($arg);
  sv_setiv(tempsv, (IV) *$source);
}
		
%inline %{

  void add(int *a, int *b, int *c) {
    *c = *a+*b;
  }

  void negate(int *a) {
    *a = -(*a);
  }
%}


