
#import "user.h"

@implementation User

-init : (char *) n : (int) u : (char *) h {
  name = (char *) malloc(strlen(n)+1);
  strcpy(name,n);
  uid = u;
  home = (char *) malloc(strlen(h)+1);
  strcpy(home,h);
  return self;
}

+new : (char *) n : (int) u : (char *) h {
  self = [super alloc];
  return [self init: n : u : h];
}

-free {
  free(name);
  free(home);
}

@end

