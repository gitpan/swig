
%include gd.i


%{
#include "location.h"
%}

/* Data structure for holding longitude and lattitude information */

typedef struct Location {
  char    *name;
  double  lat_degrees;
  double  lat_minutes;
  double  lat_seconds;
  char    lat_direction;
  double  long_degrees;
  double  long_minutes;
  double  long_seconds;
  char    long_direction;
  %addmethods {
	Location(char *);
  }
} Location;

extern double xmin,ymin,xmax,ymax;
extern void plot_cities(gdImagePtr im, Location *city1, Location *city2, int color);


