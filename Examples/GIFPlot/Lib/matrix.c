
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

/**************************************************************************
 * matrix.c
 *
 * Operations on 4x4 matrices
 **************************************************************************/

#define MATRIX
#include "gifplot.h"
#include <math.h>

/* ------------------------------------------------------------------------
   Matrix new_Matrix()

   Create a new 4x4 matrix.
   ------------------------------------------------------------------------ */
Matrix
new_Matrix() {
  Matrix m;
  m = (Matrix) malloc(16*sizeof(double));
  return m;
}

/* ------------------------------------------------------------------------
   delete_Matrix(Matrix *m);

   Destroy a matrix
   ------------------------------------------------------------------------ */

void
delete_Matrix(Matrix m) {
  if (m)
    free((char *) m);
}

/* ------------------------------------------------------------------------
   Matrix Matrix_copy(Matrix a)

   Makes a copy of matrix a and returns it.
   ------------------------------------------------------------------------ */

Matrix Matrix_copy(Matrix a) {
  int i;
  Matrix r = 0;
  if (a) {
    r = new_Matrix();
    if (r) {
      for (i = 0; i < 16; i++)
	r[i] = a[i];
    }
  }
  return r;
}
    
/* ------------------------------------------------------------------------
   Matrix_multiply(Matrix a, Matrix b, Matrix c)

   Multiplies a*b = c
   c may be one of the source matrices
   ------------------------------------------------------------------------ */
void
Matrix_multiply(Matrix a, Matrix b, Matrix c) {
  double temp[16];
  int    i,j,k;

  for (i =0; i < 4; i++)
    for (j = 0; j < 4; j++) {
      temp[i*4+j] = 0.0;
      for (k = 0; k < 4; k++) 
	temp[i*4+j] += a[i*4+k]*b[k*4+j];
    }
  for (i = 0; i < 16; i++)
    c[i] = temp[i];
}
  
/* ------------------------------------------------------------------------
   Matrix_identity(Matrix a)

   Puts an identity matrix in matrix a
   ------------------------------------------------------------------------ */

void
Matrix_identity(Matrix a) {
  int i;
  for (i = 0; i < 16; i++) a[i] = 0;
  a[0] = 1;
  a[5] = 1;
  a[10] = 1;
  a[15] = 1;
}

/* ------------------------------------------------------------------------
   Matrix_zero(Matrix a)
   
   Puts a zero matrix in matrix a
   ------------------------------------------------------------------------ */
void
Matrix_zero(Matrix a) {
  int i;
  for (i = 0; i < 16; i++) a[i] = 0;
}

/* ------------------------------------------------------------------------
   Matrix_transpose(Matrix a, Matrix result)

   Transposes matrix a and puts it in result.
   ------------------------------------------------------------------------ */
void
Matrix_transpose(Matrix a, Matrix result) {
  double temp[16];
  int i,j;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++) 
      temp[4*i+j] = a[4*j+i];

  for (i = 0; i < 16; i++)
    result[i] = temp[i];
}


/* ------------------------------------------------------------------------
   Matrix_gauss(Matrix a, Matrix b)

   Solves ax=b for x, using Gaussian elimination. Destroys a.
   Really only used for calculating inverses of 4x4 transformation
   matrices.
   ------------------------------------------------------------------------ */

void Matrix_gauss(Matrix a, Matrix b) {
  int ipiv[4], indxr[4], indxc[4];
  int i,j,k,l,ll;
  int irow=0, icol=0;
  double big, pivinv;
  double dum;
  for (j = 0; j < 4; j++)
    ipiv[j] = 0;
  for (i = 0; i < 4; i++) {
    big = 0;
    for (j = 0; j < 4; j++) {
      if (ipiv[j] != 1) {
	for (k = 0; k < 4; k++) {
	  if (ipiv[k] == 0) {
	    if (fabs(a[4*j+k]) >= big) {
	      big = fabs(a[4*j+k]);
	      irow = j;
	      icol = k;
	    }
	  } else if (ipiv[k] > 1)
	    return;  /* Singular matrix */
	}
      }
    }
    ipiv[icol] = ipiv[icol]+1;
    if (irow != icol) {
      for (l = 0; l < 4; l++) {
	dum = a[4*irow+l];
	a[4*irow+l] = a[4*icol+l];
	a[4*icol+l] = dum;
      }
      for (l = 0; l < 4; l++) {
	dum = b[4*irow+l];
	b[4*irow+l] = b[4*icol+l];
	b[4*icol+l] = dum;
      }
    }
    indxr[i] = irow;
    indxc[i] = icol;
    if (a[4*icol+icol] == 0) return;
    pivinv = 1.0/a[4*icol+icol];
    a[4*icol+icol] = 1.0;
    for (l = 0; l < 4; l++)
      a[4*icol+l] = a[4*icol+l]*pivinv;
    for (l = 0; l < 4; l++)
      b[4*icol+l] = b[4*icol+l]*pivinv;
    for (ll = 0; ll < 4; ll++) {
      if (ll != icol) {
	dum = a[4*ll+icol];
	a[4*ll+icol] = 0;
	for (l = 0; l < 4; l++)
	  a[4*ll+l] = a[4*ll+l] - a[4*icol+l]*dum;
	for (l = 0; l < 4; l++)
	  b[4*ll+l] = b[4*ll+l] - b[4*icol+l]*dum;
      }
    }
  }
  for (l = 3; l >= 0; l--) {
    if (indxr[l] != indxc[l]) {
      for (k = 0; k < 4; k++) {
	dum = a[4*k+indxr[l]];
	a[4*k+indxr[l]] = a[4*k+indxc[l]];
	a[4*k+indxc[l]] = dum;
      }
    }
  }
}

/* ------------------------------------------------------------------------
   Matrix_invert(Matrix a, Matrix inva)

   Inverts Matrix a and places the result in inva.
   Relies on the Gaussian Elimination code above. (See Numerical recipes).
   ------------------------------------------------------------------------ */
void
Matrix_invert(Matrix a, Matrix inva) {

  double  temp[16];
  int     i;

  for (i = 0; i < 16; i++)
    temp[i] = a[i];
  Matrix_identity(inva);
  Matrix_gauss(temp,inva);
}
    
/* ------------------------------------------------------------------------
   Matrix_transform(Matrix a, GL_Vector *r, GL_Vector *t)

   Transform a vector.    a*r ----> t
   ------------------------------------------------------------------------ */

void   Matrix_transform(Matrix a, GL_Vector *r, GL_Vector *t) {

  double  rx, ry, rz, rw;

  rx = r->x;
  ry = r->y;
  rz = r->z;
  rw = r->w;
  t->x = a[0]*rx + a[1]*ry + a[2]*rz + a[3]*rw;
  t->y = a[4]*rx + a[5]*ry + a[6]*rz + a[7]*rw;
  t->z = a[8]*rx + a[9]*ry + a[10]*rz + a[11]*rw;
  t->w = a[12]*rx + a[13]*ry + a[14]*rz + a[15]*rw;
}

/* ------------------------------------------------------------------------
   Matrix_transform4(Matrix a, double x, double y, double z, double w, GL_Vector *t)

   Transform a vector from a point specified as 4 doubles
   ------------------------------------------------------------------------ */

void   Matrix_transform4(Matrix a, double rx, double ry, double rz, double rw,
			 GL_Vector *t) {

  t->x = a[0]*rx + a[1]*ry + a[2]*rz + a[3]*rw;
  t->y = a[4]*rx + a[5]*ry + a[6]*rz + a[7]*rw;
  t->z = a[8]*rx + a[9]*ry + a[10]*rz + a[11]*rw;
  t->w = a[12]*rx + a[13]*ry + a[14]*rz + a[15]*rw;
}

/* ---------------------------------------------------------------------
   Matrix_translate(Matrix a, double tx, double ty, double tz)

   Put a translation matrix in Matrix a
   ---------------------------------------------------------------------- */

void Matrix_translate(Matrix a, double tx, double ty, double tz) {
  Matrix_identity(a);
  a[3] = tx;
  a[7] = ty;
  a[11] = tz;
  a[15] = 1;
}

/* -----------------------------------------------------------------------
   Matrix_rotatex(Matrix a, double deg)

   Produce an x-rotation matrix for given angle in degrees.
   ----------------------------------------------------------------------- */
void
Matrix_rotatex(Matrix a, double deg) {
  double r;

  r = 3.1415926*deg/180.0;
  Matrix_zero(a);
  a[0] = 1.0;
  a[5] = cos(r);
  a[6] = -sin(r);
  a[9] = sin(r);
  a[10] = cos(r);
  a[15] = 1.0;
}

/* -----------------------------------------------------------------------
   Matrix_rotatey(Matrix a, double deg)

   Produce an y-rotation matrix for given angle in degrees.
   ----------------------------------------------------------------------- */
void
Matrix_rotatey(Matrix a, double deg) {
  double r;

  r = 3.1415926*deg/180.0;
  Matrix_zero(a);
  a[0] = cos(r);
  a[2] = sin(r);
  a[5] = 1.0;
  a[8] = -sin(r);
  a[10] = cos(r);
  a[15] = 1;
  
}
/* -----------------------------------------------------------------------
   Matrix_RotateZ(Matrix a, double deg)

   Produce an z-rotation matrix for given angle in degrees.
   ----------------------------------------------------------------------- */
void
Matrix_rotatez(Matrix a, double deg) {
  double r;

  r = 3.1415926*deg/180.0;
  Matrix_zero(a);
  a[0] = cos(r);
  a[1] = -sin(r);
  a[4] = sin(r);
  a[5] = cos(r);
  a[10] = 1.0;
  a[15] = 1.0;
}


/* A debugging routine */

void Matrix_set(Matrix a, int i, int j, double val) {
  a[4*j+i] = val;
}

void Matrix_print(Matrix a) {
  int i,j;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      fprintf(stdout,"%10f ",a[4*i+j]);
    }
    fprintf(stdout,"\n");
  }
  fprintf(stdout,"\n");
}

