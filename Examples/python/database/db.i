// Simple database-like module.
// This shows how one can convert to and from C structures
// and Python tuples

%module db

%{
#include "db.h"
%}

// We use a typemap to define how we want to parse User records

// Define how a User record is to be passed into a C function
// This works for both "User" and "User *"

%typemap(python,in) User * {
  static User temp;                /* A temporary holding place */
  char       *login,*name,*home;   /* Temporary variables       */
  if (!PyArg_ParseTuple($source,"siiss",&login,&temp.uid,&temp.gid,&name,&home))
    return NULL;

  /* Safely copy passed values into our structure */

  strncpy(temp.login,login,16);
  strncpy(temp.name,name,32);
  strncpy(temp.home,home,256);

  /* Set the User * pointer to our temporary structure */

  $target = &temp;
}

// Describe how we want to return a user record

%typemap(python,out) User * {
  if ($source) {
    $target = Py_BuildValue("(siiss)",$source->login,$source->uid,
			    $source->gid,$source->name,$source->home);
  } else {
    $target = Py_None;
    Py_INCREF(Py_None);
  }
}

extern void add_user(User u);
extern void sort_users();
extern User *lookup_user(char *name);
extern User *get_user(int index);
extern int num_users();


