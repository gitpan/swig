
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

#define COLORMAP
#include "gifplot.h"
#include <string.h>

/*************************************************************************
 * color.c
 *
 * This file defines a whole bunch of stuff for colormaps.
 **************************************************************************/

/* ------------------------------------------------------------------------
   ColorMap *new_ColorMap(char *filename)

   Read a colormap from a file.
   ------------------------------------------------------------------------ */

ColorMap *new_ColorMap(char *filename) {
  ColorMap *c;
  FILE *cm;
  void ColorMap_default(ColorMap *);
  
  if (!filename) {
    c = (ColorMap *) malloc(sizeof(ColorMap));
    c->cmap = (unsigned char *) malloc(768*sizeof(char));
    ColorMap_default(c);
    return c;
  }
  if (strlen(filename) == 0) {
    c = (ColorMap *) malloc(sizeof(ColorMap));
    c->cmap = (unsigned char *) malloc(768*sizeof(char));
    ColorMap_default(c);
    return c;
  }
  if ((cm = fopen(filename,"rb")) == NULL) {
    return (ColorMap *) 0;
  }
  c = (ColorMap *) malloc(sizeof(ColorMap));
  c->cmap = (unsigned char *) malloc(768*sizeof(char));
  if (fread(c->cmap, 768, 1, cm) != 1) {
    free((char *)c->cmap);
    free((char *)c);
    fclose(cm);
    return (ColorMap *) 0;
  }
  fclose(cm);
  c->name = (char *) malloc(strlen(filename)+1);
  strcpy(c->name, filename);
  ColorMap_default(c);
  return c;
}

/* --------------------------------------------------------------------------
   delete_ColorMap(ColorMap *cm)

   Destroy a ColorMap
   -------------------------------------------------------------------------- */

void delete_ColorMap(ColorMap *cm) {
  if (cm) {
    free((char *)cm->cmap);
    free((char *)cm->name);
    free((char *)cm);
  }
}

/* --------------------------------------------------------------------------
   ColorMap_default(ColorMap *cm)

   This function fills in default values for the first 8 entries of the
   colormap.  These are *fixed* values---used internally.
   -------------------------------------------------------------------------- */

void ColorMap_default(ColorMap *cm) {
  unsigned char *r,*g,*b;
  if (cm) {
    r = cm->cmap;
    g = cm->cmap+256;
    b = cm->cmap+512;

    r[0] = 0;   g[0] = 0;   b[0] = 0;      /* BLACK */
    r[1] = 255; g[1] = 255; b[1] = 255;    /* WHITE */
    r[2] = 255; g[2] = 0;   b[2] = 0;      /* RED   */
    r[3] = 0;   g[3] = 255; b[3] = 0;      /* GREEN */
    r[4] = 0;   g[4] = 0;   b[4] = 255;    /* BLUE  */
    r[5] = 255; g[5] = 255; b[5] = 0;      /* YELLOW */
    r[6] = 0;   g[6] = 255; b[6] = 255;    /* CYAN   */
    r[7] = 255; g[7] = 0;   b[7] = 255;    /* MAGENTA */
  }
}

void ColorMap_assign(ColorMap *cm, int index, int r, int g, int b) {
  unsigned char *rb,*gb,*bb;

  rb = cm->cmap;
  gb = cm->cmap+256;
  bb = cm->cmap+512;

  rb[index] = r;
  gb[index] = g;
  bb[index] = b;
}

int ColorMap_getitem(ColorMap *cm, int index) {
  if ((index < 0) && (index >= 768)) return -1;
  return cm->cmap[index];
}

void ColorMap_setitem(ColorMap *cm, int index, int value) {
  if ((index < 0) && (index >= 768)) return;
  cm->cmap[index]=value;
}  

/* --------------------------------------------------------------------
   ColorMap_write(ColorMap *cm, char *filename)

   Write out a colormap to disk.
   -------------------------------------------------------------------- */

int ColorMap_write(ColorMap *cm, char *filename) {

  FILE *f;
  if (!cm) return -1;
  if (!filename) return -1;
  if (strlen(filename) == 0) return -1;

  f = fopen(filename,"w");
  
  fwrite(cm->cmap,768,1,f);
  fclose(f);
  return 0;
}

#undef COLORMAP
