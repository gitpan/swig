
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

#include <stdio.h>
#include <fcntl.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#ifndef GIFPLOT_H

/* Pixel is 8-bits */

typedef unsigned char Pixel;
typedef float Zvalue;

/* ------------------------------------------------------------------------
   ColorMap

   Definition and methods for colormaps
   ------------------------------------------------------------------------ */

typedef struct ColorMap {
  unsigned char          *cmap;
  char          *name;
} ColorMap;

extern ColorMap *new_ColorMap(char *filename);
extern void      delete_ColorMap(ColorMap *c);
extern void      ColorMap_default(ColorMap *c);
extern void      ColorMap_assign(ColorMap *c, int index, int r, int g, int b);
extern int       ColorMap_getitem(ColorMap *c, int index);
extern void      ColorMap_setitem(ColorMap *c, int index, int value);
extern int       ColorMap_write(ColorMap *c, char *filename);

/* Some default colors */

#define BLACK   0
#define WHITE   1
#define RED     2
#define GREEN   3
#define BLUE    4
#define YELLOW  5
#define CYAN    6
#define MAGENTA 7

/*-------------------------------------------------------------------------
  FrameBuffer

  This structure defines a simple 8 bit framebuffer.  
  ------------------------------------------------------------------------- */

typedef struct FrameBuffer {
  Pixel         **pixels;
  Zvalue        **zbuffer;
  unsigned int    height;
  unsigned int    width;
  int             xmin;      /* These are used for clipping */
  int             ymin;
  int             xmax;
  int             ymax;
} FrameBuffer;

/* #define ZMIN     FLT_MAX   */ /* Minimum Z coordinate */
#define ZMIN  1e+36

/* FrameBuffer Methods */

extern FrameBuffer *new_FrameBuffer(unsigned int width, unsigned int height);
extern void         delete_FrameBuffer(FrameBuffer *frame);
extern int          FrameBuffer_resize(FrameBuffer *frame, int width, int height);
extern void         FrameBuffer_clear(FrameBuffer *frame, Pixel color);
extern void         FrameBuffer_plot(FrameBuffer *frame, int x, int y, Pixel color);
extern void         FrameBuffer_horizontal(FrameBuffer *frame, int xmin,
					   int xmax, int y, Pixel color);
extern void         FrameBuffer_horizontalInterp(FrameBuffer *f, int xmin,
						 int xmax, int y,  Pixel c1, Pixel c2);
extern void         FrameBuffer_vertical(FrameBuffer *frame, int ymin, int ymax,
					 int x, Pixel color);

extern void         FrameBuffer_box(FrameBuffer *frame, int x1, int y1,
				    int x2, int y2, Pixel color);
extern void         FrameBuffer_solidbox(FrameBuffer *frame, int x1, int y1,
					 int x2, int y2, Pixel color);
extern void         FrameBuffer_interpbox(FrameBuffer *f, int x1, int y1, int x2, int y2,
					  Pixel c1, Pixel c2, Pixel c3, Pixel c4);

extern void         FrameBuffer_circle(FrameBuffer *frame, int x1, int y1,
				       int radius, Pixel color);
extern void         FrameBuffer_solidcircle(FrameBuffer *frame, int x1, int y1,
					    int radius, Pixel color);
extern void         FrameBuffer_line(FrameBuffer *frame, int x1, int y1,
				     int x2, int y2, Pixel color);
extern void         FrameBuffer_setclip(FrameBuffer *frame, int xmin, int ymin,
					int xmax, int ymax);
extern void         FrameBuffer_noclip(FrameBuffer *frame);
extern int          FrameBuffer_makeGIF(FrameBuffer *frame, ColorMap *cmap,
					void *buffer, unsigned int maxsize);
extern int FrameBuffer_writeGIF(FrameBuffer *f, ColorMap *c, char *filename);
extern void         FrameBuffer_zresize(FrameBuffer *f, int width, int height);
extern void         FrameBuffer_zclear(FrameBuffer *f);

extern void         FrameBuffer_solidtriangle(FrameBuffer *f, int x1, int y1, int x2, int y2, int x3, int y3, Pixel c);

void FrameBuffer_interptriangle(FrameBuffer *f, int tx1, int ty1, Pixel c1,
				int tx2, int ty2, Pixel c2,
				int tx3, int ty3, Pixel c3);


#define  HORIZONTAL  1
#define  VERTICAL    2

extern void FrameBuffer_drawchar(FrameBuffer *frame, int x, int y, int fgcolor, int bgcolor, char chr, int orientation);
extern void FrameBuffer_drawstring(FrameBuffer *f, int x, int y, int fgcolor, int bgcolor, char *text, int orientation);

/* ------------------------------------------------------------------------
   PixMap

   The equivalent of "bit-maps".
   ------------------------------------------------------------------------ */

typedef struct PixMap {
  int    width;
  int    height;
  int    centerx;
  int    centery;
  int   *map;
} PixMap;

/* PIXMAP methods */

extern PixMap   *new_PixMap(int width, int height, int centerx, int centery);
extern void      delete_PixMap(PixMap *pm);
extern void      PixMap_set(PixMap *pm, int x, int y, int pix);
extern void      FrameBuffer_drawpixmap(FrameBuffer *f, PixMap *pm, int x, int y, int fgcolor, int bgcolor);

#define   TRANSPARENT  0
#define   FOREGROUND   1
#define   BACKGROUND   2

/* ------------------------------------------------------------------------
   Plot2D

   Definition and methods for 2D plots.
   ------------------------------------------------------------------------ */

typedef struct Plot2D {
  FrameBuffer    *frame;        /* what frame buffer are we using     */
  int             view_xmin;    /* Minimum coordinates of view region */
  int             view_ymin;    
  int             view_xmax;    /* Maximum coordinates of view region */
  int             view_ymax;    
  double          xmin;         /* Minimum coordinates of plot region */
  double          ymin;
  double          xmax;         /* Maximum coordinates of plot region */
  double          ymax;
  int             xscale;       /* Type of scaling (LINEAR, LOG, etc..) */
  int             yscale;       
  double          dx;           /* Private scaling parameters         */
  double          dy;
} Plot2D;

/* 2D Plot methods */

extern Plot2D  *new_Plot2D(FrameBuffer *frame,double xmin,double ymin,
			   double xmax, double ymax);
extern void     delete_Plot2D(Plot2D *p2);
extern Plot2D  *Plot2D_copy(Plot2D *p2);
extern void     Plot2D_clear(Plot2D *p2, Pixel c);
extern void     Plot2D_setview(Plot2D *p2, int vxmin, int vymin, int vxmax, int vymax);
extern void     Plot2D_setrange(Plot2D *p2, double xmin, double ymin,
				double xmax, double ymax);
extern void     Plot2D_setscale(Plot2D *p2, int xscale, int yscale);
extern void     Plot2D_plot(Plot2D *p2, double x, double y, Pixel color);
extern void     Plot2D_box(Plot2D *p2, double x1, double y1,
			   double x2, double y2, Pixel color);
extern void     Plot2D_solidbox(Plot2D *p2, double x1, double y1,
				double x2, double y2, Pixel color);
extern void     Plot2D_interpbox(Plot2D *p2, double x1, double y1, double x2,
				 double y2, Pixel c1, Pixel c2, Pixel c3, Pixel c4);

extern void     Plot2D_circle(Plot2D *p2, double x, double y,
			      double radius, Pixel color);
extern void     Plot2D_solidcircle(Plot2D *p2, double x, double y,
				   double radius, Pixel color);
extern void     Plot2D_line(Plot2D *p2, double x1, double y1,
			    double x2, double y2, Pixel color);
extern void     Plot2D_start(Plot2D *p2);
extern void     Plot2D_drawpixmap(Plot2D *p2, PixMap *pm, double x, double y, Pixel color, Pixel bgcolor);
extern void     Plot2D_xaxis(Plot2D *p2, double x, double y, double xtick, int ticklength, Pixel c);
extern void     Plot2D_yaxis(Plot2D *p2, double x, double y, double ytick, int ticklength, Pixel c);
extern void     Plot2D_triangle(Plot2D *p2, double x1, double y1, double x2, double y2, double x3, double y3, Pixel c);

extern void     Plot2D_solidtriangle(Plot2D *p2, double x1, double y1, double x2, double y2, double x3, double y3, Pixel c);

extern void Plot2D_interptriangle(Plot2D *p2, double x1, double y1, Pixel c1,
			   double x2, double y2, Pixel c2,
			   double x3, double y3, Pixel c3);

#define LINEAR     10
#define LOG        11

/* -----------------------------------------------------------------------
   Matrix
   
   Operations on 4x4 transformation matrices and vectors.
   Matrices are represented as a double array of 16 elements
   ----------------------------------------------------------------------- */

typedef  double *Matrix;
typedef struct GL_Vector {
  double x;
  double y;
  double z;
  double w;
} GL_Vector;

extern Matrix new_Matrix();
extern void   delete_Matrix(Matrix a);
extern Matrix Matrix_copy(Matrix a);
extern void   Matrix_multiply(Matrix a, Matrix b, Matrix c);
extern void   Matrix_identity(Matrix a);
extern void   Matrix_zero(Matrix a);
extern void   Matrix_transpose(Matrix a, Matrix result);
extern void   Matrix_invert(Matrix a, Matrix inva);
extern void   Matrix_transform(Matrix a, GL_Vector *r, GL_Vector *t);
extern void   Matrix_transform4(Matrix a, double rx, double ry, double rz,
				double rw, GL_Vector *t);

extern void   Matrix_print(Matrix a);
extern void   Matrix_translate(Matrix a, double tx, double ty, double tz);
extern void   Matrix_rotatex(Matrix a, double deg);
extern void   Matrix_rotatey(Matrix a, double deg);
extern void   Matrix_rotatez(Matrix a, double deg);

/* -----------------------------------------------------------------------
   Plot3D

   Data Structure for 3-D plots
   ------------------------------------------------------------------------ */

typedef struct Plot3D {
  FrameBuffer   *frame;      /* Frame buffer being used */
  int            view_xmin;  /* Viewing region */
  int            view_ymin;
  int            view_xmax;
  int            view_ymax;
  double         xmin;       /* Bounding box */
  double         ymin;
  double         zmin;
  double         xmax;
  double         ymax;
  double         zmax;
  double         xcenter;    /* Center point */
  double         ycenter;
  double         zcenter;
  double         fovy;       /* Field of view */
  double         aspect;     /* Aspect ratio  */
  double         znear;      /* near "clipping" plane */
  double         zfar;       /* far "clipping" plane */
  Matrix         center_mat; /* Matrix used for centering the model */
  Matrix         model_mat;  /* Model rotation matrix */
  Matrix         view_mat;   /* Viewing matrix */
  Matrix         fullmodel_mat;  /* Full model matrix.  Used by sphere plot */
  Matrix         trans_mat;  /* Total transformation matrix */
  double         lookatz;    /* Where is the z-lookat point */
  double         xshift;     /* Used for translation and stuff */
  double         yshift;
  double         zoom;
  int            width;
  int            height;
  int            pers_mode;  /* Perspective mode (private) */
  double         ortho_left,ortho_right,ortho_bottom,ortho_top;
} Plot3D;

extern Plot3D *new_Plot3D(FrameBuffer *frame, double xmin, double ymin, double zmin,
			  double xmax, double ymax, double zmax);
extern void   delete_Plot3D(Plot3D *p3);
extern Plot3D *Plot3D_copy(Plot3D *p3);
extern void   Plot3D_clear(Plot3D *p3, Pixel Color);
extern void   Plot3D_perspective(Plot3D *p3, double fovy, double znear, double zfar);
extern void   Plot3D_ortho(Plot3D *p3, double left, double right, double top, double bottom);
extern void   Plot3D_lookat(Plot3D *p3, double z);
extern void   Plot3D_autoperspective(Plot3D *p3, double fovy);
extern void   Plot3D_autoortho(Plot3D *p3);
extern void   Plot3D_rotx(Plot3D *p3, double deg);
extern void   Plot3D_roty(Plot3D *p3, double deg);
extern void   Plot3D_rotz(Plot3D *p3, double deg);
extern void   Plot3D_rotl(Plot3D *p3, double deg);
extern void   Plot3D_rotr(Plot3D *p3, double deg);
extern void   Plot3D_rotd(Plot3D *p3, double deg);
extern void   Plot3D_rotu(Plot3D *p3, double deg);
extern void   Plot3D_rotc(Plot3D *p3, double deg);
extern void   Plot3D_zoom(Plot3D *p3, double percent);
extern void   Plot3D_left(Plot3D *p3, double percent);
extern void   Plot3D_right(Plot3D *p3, double percent);
extern void   Plot3D_down(Plot3D *p3, double percent);
extern void   Plot3D_up(Plot3D *p3, double percent);
extern void   Plot3D_center(Plot3D *p3, double cx, double cy);

extern void   Plot3D_plot(Plot3D *p3, double x, double y, double z, Pixel Color);

extern void   Plot3D_setview(Plot3D *p3, int vxmin, int vymin, int vxmax, int vymax);
extern void   Plot3D_start(Plot3D *p3);
extern void   Plot3D_line(Plot3D *p3, double x1, double y1, double z1,
			 double x2, double y2, double z2, Pixel color);
extern void   Plot3D_triangle(Plot3D *p3, double x1, double y1, double z1,
		     double x2, double y2, double z2,
		     double x3, double y3, double z3, Pixel color);
extern void   Plot3D_solidtriangle(Plot3D *p3, double x1, double y1, double z1,
		     double x2, double y2, double z2,
		     double x3, double y3, double z3, Pixel color);

extern void Plot3D_interptriangle(Plot3D *p3,
			   double x1, double y1, double z1, Pixel c1,
			   double x2, double y2, double z2, Pixel c2,
			   double x3, double y3, double z3, Pixel c3);

extern void   Plot3D_quad(Plot3D *p3, double x1, double y1, double z1,
		 double x2, double y2, double z2,
		 double x3, double y3, double z3,
		 double x4, double y4, double z4,
		 Pixel color);

extern void   Plot3D_solidquad(Plot3D *p3, double x1, double y1, double z1,
		 double x2, double y2, double z2,
		 double x3, double y3, double z3,
		 double x4, double y4, double z4,
		 Pixel color);

extern void   Plot3D_interpquad(Plot3D *p3, double x1, double y1, double z1, Pixel c1,
		       double x2, double y2, double z2, Pixel c2,
		       double x3, double y3, double z3, Pixel c3,
		       double x4, double y4, double z4, Pixel c4);


extern void   Plot3D_solidsphere(Plot3D *p3, double x, double y, double z, double radius,Pixel c);

extern void   Plot3D_outlinesphere(Plot3D *p3, double x, double y, double z, double radius,Pixel c, Pixel bc);

extern PixMap  PixMap_SQUARE;
extern PixMap  PixMap_TRIANGLE;
extern PixMap  PixMap_CROSS;

#endif
#define GIFPLOT_H



