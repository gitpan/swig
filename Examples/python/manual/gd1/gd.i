%module gd
%{
#include "gd.h"
%}

%section "gd-1.2",ignore
%include "/usr/local/include/gd.h"

FILE *fopen(char *, char *);
void fclose(FILE *f);

%include embed.i

