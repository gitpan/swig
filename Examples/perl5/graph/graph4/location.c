/* C code to make an image and plot latitude and longitude points */

#include <gd.h>
#include <gdfonts.h>
#include "location.h"
#include <string.h>

double xmin,ymin,xmax,ymax;

/* Make a new location */

Location *new_Location(char *name) {
  Location *l;

  l = (Location *) malloc(sizeof(Location));
  l->name = (char *) malloc(strlen(name)+1);
  strcpy(l->name,name);
  return l;
}

/* Make a plot of two locations with a line between them */

void plot_cities(gdImagePtr im, Location *city1, Location *city2, int color) {
  
  double x1,y1,x2,y2;
  int    ix1,iy1,ix2,iy2;
  int    width,height;

  /* Convert the two locations into coordinates */
  
  x1 = city1->long_degrees + city1->long_minutes/60 + city1->long_seconds/3600;
  y1 = city1->lat_degrees + city1->lat_minutes/60 + city1->lat_seconds/3600;
  if (city1->long_direction == 'W') x1 = -x1;

  x2 = city2->long_degrees + city2->long_minutes/60 + city2->long_seconds/3600;
  y2 = city2->lat_degrees + city2->lat_minutes/60 + city2->lat_seconds/3600;
  if (city1->long_direction == 'W') x2 = -x2;

  width = gdImageSX(im);
  height = gdImageSY(im);
  
  ix1 = (x1-xmin)/(xmax-xmin)*width;
  iy1 = (y1-ymin)/(ymax-ymin)*height;
  ix2 = (x2-xmin)/(xmax-xmin)*width;
  iy2 = (y2-ymin)/(ymax-ymin)*height;

  /* Draw the cities */

  gdImageString(im,gdFontSmall,ix1 - strlen(city1->name)*gdFontSmall->w/2,height-iy1,city1->name,color);
  gdImageString(im,gdFontSmall,ix2 - strlen(city2->name)*gdFontSmall->w/2,height-iy2,city2->name,color);

  /* Draw a line */

  gdImageLine(im,ix1,height-iy1,ix2,height-iy2,color);

}



  
  
