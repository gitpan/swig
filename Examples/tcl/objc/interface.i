%module list
%{
#import "list.h"
#import "user.h"
%}
%include objc.i              // Objective-C library
%include pointer.i           // Pointer library (useful to have)
%include list.h
%include user.h

%addmethods User{
-(char *) str {
    static char temp[512];
    sprintf(temp,"%s : %d : %s", self->name, self->uid, self->home);
    return temp;
  }
}


