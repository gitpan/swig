
#include "widget.h"

/* Constructor */

PlotWidget::PlotWidget(int w, int h, double x1, double y1, double x2, double y2) {
  width = w;
  height = h;
  xmin = x1;
  xmax = x2;
  ymin = y1;
  ymax = y2;
  npoints = 100;
  callback = 0;
  im = gdImageCreate(w,h);
  black = gdImageColorAllocate(im,0,0,0);
  white = gdImageColorAllocate(im,255,255,255);
}

/* Destructor */

PlotWidget::~PlotWidget() {
  gdImageDestroy(im);
}

/* Set the callback method */

void PlotWidget::set_method(PLOTFUNC func, void *cdata) {
  callback = func;
  clientdata = cdata;
}

/* Transform points */

void PlotWidget::transform(double x, double y, int &ix, int &iy) {
  ix = (int) (((x-xmin)/(xmax-xmin))*width);
  iy = (int) (((ymin-y)/(ymax-ymin))*height)+height;
}

/* Make a plot of the data */

void PlotWidget::plot() {
  double dx;
  double x,y;
  int i,ix0,iy0,ix1,iy1;

  gdImageFilledRectangle(im,0,0,width-1,height-1,black);
  if (!callback) {
    printf("Error. No method specified.\n");
    return;
  }
  dx = (xmax-xmin)/npoints;
  x = xmin;
  y = (callback)(x,clientdata);
  transform(x,y,ix0,iy0);
  for (i = 0; i < npoints; i++) {
    x+=dx;
    y = (callback)(x,clientdata);
    transform(x,y,ix1,iy1);
    gdImageLine(im,ix0,iy0,ix1,iy1,white);
    ix0 = ix1;
    iy0 = iy1;
  }
}

/* Save a plot of the data */

void PlotWidget::save(FILE *f) {
  gdImageGif(im,f);
}

/* Set plot range */

void PlotWidget::set_range(double x1, double y1, double x2, double y2) {
  xmin = x1;
  ymin = y1;
  xmax = x2;
  ymax = y2;
};
