// Simple database-like module.
// This shows how one can convert to and from C structures
// from Tcl lists

%module db

%{
#include "db.h"
%}

// We use a typemap to define how we want to parse User records

// Define how a User record is to be passed into a C function
// This works for both "User" and "User *"

%typemap(tcl,in) User * {
	int tempc;
	char **tempa;
	static User temp;
	if (Tcl_SplitList(interp,$source,&tempc,&tempa) == TCL_ERROR) return TCL_ERROR;
	if (tempc != 5) {
	  free((char *) tempa);
	  interp->result = "Not a valid User record";
	  return TCL_ERROR;
	}
	/* Split out the different fields */
	strncpy(temp.login,tempa[0],16);
	temp.uid = atoi(tempa[1]);
	temp.gid = atoi(tempa[2]);
	strncpy(temp.name,tempa[3],32);
	strncpy(temp.home,tempa[4],256);
	$target = &temp;
	free((char *) tempa);
}

// Describe how we want to return a user record

%typemap(tcl,out) User * {
  char temp[20];
  if ($source) {
    Tcl_AppendElement(interp,$source->login);
    sprintf(temp,"%d",$source->uid);
    Tcl_AppendElement(interp,temp);
    sprintf(temp,"%d",$source->gid);
    Tcl_AppendElement(interp,temp);
    Tcl_AppendElement(interp,$source->name);
    Tcl_AppendElement(interp,$source->home);
  }
}

extern void add_user(User u);
extern void sort_users();
extern User *lookup_user(char *name);
extern User *get_user(int index);
extern int num_users();


