#include <stdio.h>

typedef void (*CALLBACK)(void);
CALLBACK my_callback = 0;

void set_callback(CALLBACK c) {
  my_callback = c;
}

void test(void) {
  printf("Testing the callback function\n");
  if (my_callback) (*my_callback)();
  else printf("No callback registered\n");
}


