// Simple database-like module.
// This shows how one can convert to and from C structures
// from Perl5 array references.

%module db

%{
#include "db.h"
%}

// We use a typemap to define how we want to parse User records

// Define how a User record is to be passed into a C function
// This works for both "User" and "User *"

%typemap(perl5,in) User * {
  static User temp;                /* A temporary holding place */
  AV *tempav;
  I32 len;
  SV  **tv;

  char       *login,*name,*home;   /* Temporary variables       */
  	
  if (!SvROK($source))
    croak("$source is not a reference.");
  if (SvTYPE(SvRV($source)) != SVt_PVAV)
    croak("$source is not an array.");
  tempav = (AV*)SvRV($source);
  len = av_len(tempav);
  if (len != 4) 
    croak("Invalid array size.");
  
  /* Now grab values out of the array */
  tv = av_fetch(tempav,0,0);
  login = (char *) SvPV(*tv,na);
  strncpy(temp.login,login,16);
  tv = av_fetch(tempav,1,0);
  temp.uid = (int) SvIV(*tv);
  tv = av_fetch(tempav,2,0);
  temp.gid = (int) SvIV(*tv);
  tv = av_fetch(tempav,3,0);
  name = (char *) SvPV(*tv,na);
  strncpy(temp.name,name,32);
  tv = av_fetch(tempav,4,0);
  home = (char *) SvPV(*tv,na);
  strncpy(temp.home,home,256);

  /* Set the User * pointer to our temporary structure */

  $target = &temp;
}

// Describe how we want to return a user record

%typemap(perl5,out) User * {
  AV *myav;
  SV **svs;
  if ($source) {
    svs = (SV **) malloc(5*sizeof(SV *));
    svs[0] = sv_newmortal();
    sv_setpv((SV*) svs[0],$source->login);
    svs[1] = sv_newmortal();
    sv_setiv((SV*) svs[1],$source->uid);
    svs[2] = sv_newmortal();
    sv_setiv((SV*) svs[2],$source->uid);
    svs[3] = sv_newmortal();
    sv_setpv((SV*) svs[3],$source->name);
    svs[4] = sv_newmortal();
    sv_setpv((SV*) svs[4],$source->home);
    myav = av_make(5,svs);
    free(svs);
    $target = newRV((SV *) myav);
    sv_2mortal($target);
    argvi++;
  } 
}

extern void add_user(User u);
extern void sort_users();
extern User *lookup_user(char *name);
extern User *get_user(int index);
extern int num_users();


