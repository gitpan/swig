#import <objc/Object.h>

@interface User : Object { 
@public
  char *name;
  int   uid;
  char *home;
}

+new : (char *) n : (int) u : (char *) h;
-free;
@end


