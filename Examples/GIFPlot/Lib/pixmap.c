
/**********************************************************************
 * GIFPlot 0.0
 * 
 * Dave Beazley
 * 
 * Department of Computer Science        Theoretical Division (T-11)        
 * University of Utah                    Los Alamos National Laboratory     
 * Salt Lake City, Utah 84112            Los Alamos, New Mexico  87545      
 * beazley@cs.utah.edu                   beazley@lanl.gov                   
 *
 * Copyright (c) 1996
 * The Regents of the University of California and the University of Utah
 * All Rights Reserved
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that 
 * (1) The above copyright notice and the following two paragraphs
 * appear in all copies of the source code and (2) redistributions
 * including binaries reproduces these notices in the supporting
 * documentation.   Substantial modifications to this software may be
 * copyrighted by their authors and need not follow the licensing terms
 * described here, provided that the new terms are clearly indicated in
 * all files where they apply.
 * 
 * IN NO EVENT SHALL THE AUTHOR, THE UNIVERSITY OF CALIFORNIA, THE 
 * UNIVERSITY OF UTAH OR DISTRIBUTORS OF THIS SOFTWARE BE LIABLE TO ANY
 * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHORS OR ANY OF THE ABOVE PARTIES HAVE BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR, THE UNIVERSITY OF CALIFORNIA, AND THE UNIVERSITY OF UTAH
 * SPECIFICALLY DISCLAIM ANY WARRANTIES,INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND 
 * THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 **************************************************************************/

/*************************************************************************
 * pixmap.c
 *
 * Primitives for doing putting bit-maps on the screen
 *************************************************************************/
#define PIXMAP
#include "gifplot.h"

/* -----------------------------------------------------------------------
   PixMap *new_PixMap(int width, int height, int centerx, int centery)

   Create a new pixmap of given size
   ----------------------------------------------------------------------- */
PixMap *new_PixMap(int width, int height, int centerx, int centery) {
  PixMap *pm;
  if ((width > 0) && (height > 0)) {
    pm = (PixMap *) malloc(sizeof(PixMap));
    pm->width = width;
    pm->height = height;
    pm->centerx = centerx;
    pm->centery = centery;
    pm->map = (int *) malloc(height*width*sizeof(int));
    return pm;
  }
  return (PixMap *) 0;
}

/* --------------------------------------------------------------------------
   void delete_PixMap(PixMap *pm)

   Destroy a pixmap
   -------------------------------------------------------------------------- */

void delete_PixMap(PixMap *pm) {
  if (pm) {
    free((char *) pm->map);
    free((char *) pm);
  }
}

/* ---------------------------------------------------------------------------
   void PixMap_set(PixMap *pm, int x, int y, int pix)

   Set a pixel in the bitmap
   --------------------------------------------------------------------------- */
void
PixMap_set(PixMap *pm, int x, int y, int pix) {
  if ((x < 0) || (x>=pm->width)) return;
  if ((y < 0) || (y>=pm->height)) return;

  pm->map[pm->width*y + x] = pix;
}

/* -----------------------------------------------------------------------------
   void FrameBuffer_drawpixmap(FrameBuffer *f, PixMap *pm, int x, int y, int fgcolor, int bgcolor) 

   Draw a pixmap onto the framebuffer.   This is somewhat optimized for speed.
   ------------------------------------------------------------------------------ */

void
FrameBuffer_drawpixmap(FrameBuffer *f, PixMap *pm, int x, int y, int fgcolor, int bgcolor) {

  int startx, starty;         /* Starting location on framebuffer */
  int startpixx = 0, startpixy = 0;   /* Starting location in pixmap      */
  int endx, endy;             /* Ending location on framebuffer   */
  int i,j, px, py;
  int c;
  
  startx = x - pm->centerx;
  starty = y + pm->centery;
  endx = startx + pm->width;
  endy = starty - pm->height;

  /* Figure out if we need to clip */

  if (startx < f->xmin) {
    startpixx = f->xmin - startx;
    startx = f->xmin;
  }
  if (starty >= f->ymax) {
    startpixy = starty - f->ymax;
    starty = f->ymax-1;
  }
  if (endx >= f->xmax) {
    endx = f->xmax-1;
  }
  if (endy < f->ymin) {
    endy = f->ymin;
  }
  py = startpixy;
  for (j = starty; j >= endy; j--) {
    px = startpixx;
    for (i = startx; i < endx; i++) {
      c = pm->map[py*pm->width + px];
      switch (c) {
      case FOREGROUND:
	f->pixels[j][i] = fgcolor;
	break;
      case BACKGROUND:
	f->pixels[j][i] = bgcolor;
	break;
      default:
	break;
      }
      px++;
    }
    py++;
  }
}

/**************************************************************************
 * Some common PixMaps  (for plotting)
 *
 **************************************************************************/

int _SQUARE_MAP[] = {
  0,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,
  0,0,0,0,0,0,0,0 };

PixMap  PixMap_SQUARE = { 8,8,4,4, _SQUARE_MAP};

int _TRIANGLE_MAP[] = {
  0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,
  0,0,1,1,1,0,0,0,
  0,0,1,1,1,0,0,0,
  0,1,1,1,1,1,0,0,
  0,1,1,1,1,1,0,0,
  1,1,1,1,1,1,1,0,
  0,0,0,0,0,0,0,0 };

PixMap  PixMap_TRIANGLE = { 8,8,4,4,_TRIANGLE_MAP};

int _CROSS_MAP[] = {
  0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,
  1,1,1,1,1,1,1,0,
  0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,
  0,0,0,1,0,0,0,0,
  0,0,0,0,0,0,0,0 };

PixMap  PixMap_CROSS = { 8,8,4,4,_CROSS_MAP};

  
      
