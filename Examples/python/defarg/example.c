#include <stdio.h>

int    print_error(int code, char *message) {
  printf("Error code %d : ", code);
  if (message)
    printf("%s\n",message);
  else
    printf("\n");
  return -1;
}
  
void  set_range(int width, int height, double xmin,double xmax,
                 double ymin, double ymax) {
  printf("Setting range :\n");
  printf("\twidth  = %d\n",width);
  printf("\theight = %d\n",height);
  printf("\txmin   = %g\n",xmin);
  printf("\txmax   = %g\n",xmax);
  printf("\tymin   = %g\n",ymin);
  printf("\tymax   = %g\n",ymax);
};

