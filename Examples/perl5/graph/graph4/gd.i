%module gd
%{
#include "gd.h"
%}

#define gdMaxColors 256

typedef struct gdImageStruct gdImage;
typedef gdImage * gdImagePtr;

/* Functions to manipulate images. */

gdImagePtr gdImageCreate(int sx, int sy);
void gdImageDestroy(gdImagePtr im);
void gdImageSetPixel(gdImagePtr im, int x, int y, int color);
int  gdImageGetPixel(gdImagePtr im, int x, int y);
void gdImageLine(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
void gdImageDashedLine(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
void gdImageRectangle(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
void gdImageFilledRectangle(gdImagePtr im, int x1, int y1, int x2, int y2, int color);
int  gdImageColorAllocate(gdImagePtr im, int r, int g, int b);
int  gdImageColorClosest(gdImagePtr im, int r, int g, int b);
int  gdImageColorExact(gdImagePtr im, int r, int g, int b);
void gdImageColorDeallocate(gdImagePtr im, int color);
void gdImageColorTransparent(gdImagePtr im, int color);
void gdImageArc(gdImagePtr im, int cx, int cy, int w, int h, int s, int e, int color);
void gdImageFillToBorder(gdImagePtr im, int x, int y, int border, int color);
void gdImageFill(gdImagePtr im, int x, int y, int color);

%{
  /* Shortcut for dumping a file */

  void dump_gif(gdImagePtr im, char *filename) {
    FILE *f;

    f = fopen(filename, "w");
    gdImageGif(im,f);
    fclose(f);
  }
%}

void dump_gif(gdImagePtr im, char *filename);

