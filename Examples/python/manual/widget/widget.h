// --------------------------------------------------------------------
// Create a C++ plotting "widget" around the gd-1.2 library by Thomas Boutell
//  
// This example primarily illustrates how callback functions can be
// implemented in Python.
// --------------------------------------------------------------------

#include <stdio.h>
extern "C" {
#include "gd.h"
}

typedef double (*PLOTFUNC)(double, void *);

class PlotWidget {
private:
  double      xmin,ymin,xmax,ymax;         // Plotting range
  PLOTFUNC    callback;                    // Callback function
  void       *clientdata;                  // Client data for callback
  int         npoints;                     // Number of points to plot
  int         width;                       // Image width
  int         height;                      // Image height
  int         black,white;
  gdImagePtr  im;
  void        transform(double,double,int&,int&);
public:
  PlotWidget(int w, int h,double,double,double,double);
  ~PlotWidget();
  void set_method(PLOTFUNC func, void *clientdata);
  void set_range(double,double,double,double);
  void set_points(int np) {npoints = np;}
  void plot();
  void save(FILE *f);
};




  

