//
%{
#include "glaux.h"
%}

/* glaux.h */

/*
 * Mesa - a 3-D graphics library
 * Version:  1.0 beta
 * Copyright (C) 1995  Brian Paul  (brianp@ssec.wisc.edu)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


/*
 * This code originated from SGI and was modified for use with Mesa.
 */


#ifndef AUX_INCLUDED
#define AUX_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

/*
** ToolKit Window Types
** In the future, AUX_RGBA may be a combination of both RGB and ALPHA
*/

#define AUX_RGB		0
#define AUX_RGBA	AUX_RGB
#define AUX_INDEX	1
#define AUX_SINGLE	0
#define AUX_DOUBLE	2
#define AUX_DIRECT	0
#define AUX_INDIRECT	4

#define AUX_ACCUM	8
#define AUX_ALPHA	16
#define AUX_DEPTH	32
#define AUX_STENCIL	64
#define AUX_AUX		128

/* 
** Window Masks
*/

#define AUX_WIND_IS_RGB(x)	(((x) & AUX_INDEX) == 0)
#define AUX_WIND_IS_INDEX(x)	(((x) & AUX_INDEX) != 0)
#define AUX_WIND_IS_SINGLE(x)	(((x) & AUX_DOUBLE) == 0)
#define AUX_WIND_IS_DOUBLE(x)	(((x) & AUX_DOUBLE) != 0)
#define AUX_WIND_IS_INDIRECT(x)	(((x) & AUX_INDIRECT) != 0)
#define AUX_WIND_IS_DIRECT(x)	(((x) & AUX_INDIRECT) == 0)
#define AUX_WIND_HAS_ACCUM(x)	(((x) & AUX_ACCUM) != 0)
#define AUX_WIND_HAS_ALPHA(x)	(((x) & AUX_ALPHA) != 0)
#define AUX_WIND_HAS_DEPTH(x)	(((x) & AUX_DEPTH) != 0)
#define AUX_WIND_HAS_STENCIL(x)	(((x) & AUX_STENCIL) != 0)

/*
** Display Mode Selection Criteria
*/

enum {
    AUX_USE_ID = 1,
    AUX_EXACT_MATCH,
    AUX_MINIMUM_CRITERIA
};


#define AUX_OFF 0
#define AUX_ON 1


/*
** ToolKit Event Structure
*/

//typedef struct _AUX_EVENTREC {
//    GLint event;
//    GLint data[4];
//} AUX_EVENTREC;

/* 
** ToolKit Event Types
*/
#define AUX_EXPOSE	1
#define AUX_CONFIG	2
#define AUX_DRAW	4
#define AUX_KEYEVENT	8
#define AUX_MOUSEDOWN	16
#define AUX_MOUSEUP	32	
#define AUX_MOUSELOC	64

/*
** Toolkit Event Data Indices
*/
#define AUX_WINDOWX		0
#define AUX_WINDOWY		1
#define AUX_MOUSEX		0
#define AUX_MOUSEY		1
#define AUX_MOUSESTATUS		3
#define AUX_KEY			0
#define AUX_KEYSTATUS		1

/*
** ToolKit Event Status Messages
*/
#define	AUX_LEFTBUTTON		1
#define	AUX_RIGHTBUTTON		2
#define	AUX_MIDDLEBUTTON	4
#define	AUX_SHIFT		1
#define	AUX_CONTROL		2

/* 
** ToolKit Key Codes
*/
#define AUX_RETURN		0x0D
#define AUX_ESCAPE		0x1B
#define AUX_SPACE		0x20
#define AUX_LEFT		0x25
#define AUX_UP			0x26
#define AUX_RIGHT		0x27
#define AUX_DOWN		0x28
#define AUX_A			'A'
#define AUX_B			'B'
#define AUX_C			'C'
#define AUX_D			'D'
#define AUX_E			'E'
#define AUX_F			'F'
#define AUX_G			'G'
#define AUX_H			'H'
#define AUX_I			'I'
#define AUX_J			'J'
#define AUX_K			'K'
#define AUX_L			'L'
#define AUX_M			'M'
#define AUX_N			'N'
#define AUX_O			'O'
#define AUX_P			'P'
#define AUX_Q			'Q'
#define AUX_R			'R'
#define AUX_S			'S'
#define AUX_T			'T'
#define AUX_U			'U'
#define AUX_V			'V'
#define AUX_W			'W'
#define AUX_X			'X'
#define AUX_Y			'Y'
#define AUX_Z			'Z'
#define AUX_a			'a'
#define AUX_b			'b'
#define AUX_c			'c'
#define AUX_d			'd'
#define AUX_e			'e'
#define AUX_f			'f'
#define AUX_g			'g'
#define AUX_h			'h'
#define AUX_i			'i'
#define AUX_j			'j'
#define AUX_k			'k'
#define AUX_l			'l'
#define AUX_m			'm'
#define AUX_n			'n'
#define AUX_o			'o'
#define AUX_p			'p'
#define AUX_q			'q'
#define AUX_r			'r'
#define AUX_s			's'
#define AUX_t			't'
#define AUX_u			'u'
#define AUX_v			'v'
#define AUX_w			'w'
#define AUX_x			'x'
#define AUX_y			'y'
#define AUX_z			'z'
#define AUX_0			'0'
#define AUX_1			'1'
#define AUX_2			'2'
#define AUX_3			'3'
#define AUX_4			'4'
#define AUX_5			'5'
#define AUX_6			'6'
#define AUX_7			'7'
#define AUX_8			'8'
#define AUX_9			'9'

/*
** ToolKit Gets and Sets
*/
#define AUX_FD			1  /* return fd (long) */
#define AUX_COLORMAP		3  /* pass buf of r, g and b (unsigned char) */
#define AUX_GREYSCALEMAP	4
#define AUX_FOGMAP		5  /* pass fog and color bits (long) */
#define AUX_ONECOLOR		6  /* pass index, r, g, and b (long) */

/*
** Color Macros
*/

enum {
    AUX_BLACK = 0,
#ifdef __WIN32__
    AUX_RED=10,
#else
    AUX_RED,
#endif
    AUX_GREEN,
    AUX_YELLOW,
    AUX_BLUE,
    AUX_MAGENTA,
    AUX_CYAN,
    AUX_WHITE
};

#ifdef __WIN32__
    float auxRGBMap[17][3];
#else
    float auxRGBMap[8][3];
#endif

#define AUX_SETCOLOR(x, y) (AUX_WIND_IS_RGB((x)) ? \
		           glColor3fv(auxRGBMap[(y)]) : glIndexf((y)))

/*
** RGB Image Structure
*/

typedef struct _AUX_RGBImageRec {
    GLint sizeX, sizeY;
    unsigned char *data;
} AUX_RGBImageRec;

/*
** Prototypes
*/

 void auxInitDisplayMode(GLbitfield);
 void auxInitPosition(int, int, int, int);
 GLenum auxInitWindow(char *);
 void auxCloseWindow(void);
 void auxQuit(void);
 void auxSwapBuffers(void);

// Display *auxXDisplay(void);
// Window auxXWindow(void);

// void auxMainLoop(void (*)());
// void auxExposeFunc(void (*)(int, int));
// void auxReshapeFunc(void (*)(int, int));
// void auxIdleFunc(void (*)());
// void auxKeyFunc(int, void (*)());
// void auxMouseFunc(int, int, void (*)(AUX_EVENTREC *));

// void auxDeleteMouseFunc( int, int , void (*)(AUX_EVENTREC *));

 int auxGetColorMapSize(void);
 void auxGetMouseLoc(int *, int *);
 void auxSetOneColor(int, float, float, float);
 void auxSetFogRamp(int, int);
 void auxSetGreyRamp(void);
 void auxSetRGBMap(int, float *);

 AUX_RGBImageRec *auxRGBImageLoad(char *);

 void auxCreateFont(void);
 void auxDrawStr(char *);

 void auxWireSphere(GLdouble);
 void auxSolidSphere(GLdouble);
 void auxWireCube(GLdouble);
 void auxSolidCube(GLdouble);
 void auxWireBox(GLdouble, GLdouble, GLdouble);
 void auxSolidBox(GLdouble, GLdouble, GLdouble);
 void auxWireTorus(GLdouble, GLdouble);
 void auxSolidTorus(GLdouble, GLdouble);
 void auxWireCylinder(GLdouble, GLdouble);
 void auxSolidCylinder(GLdouble, GLdouble);
 void auxWireIcosahedron(GLdouble);
 void auxSolidIcosahedron(GLdouble);
 void auxWireOctahedron(GLdouble);
 void auxSolidOctahedron(GLdouble);
 void auxWireTetrahedron(GLdouble);
 void auxSolidTetrahedron(GLdouble);
 void auxWireDodecahedron(GLdouble);
 void auxSolidDodecahedron(GLdouble);
 void auxWireCone(GLdouble, GLdouble);
 void auxSolidCone(GLdouble, GLdouble);
 void auxWireTeapot(GLdouble);
 void auxSolidTeapot(GLdouble);

/* added for viewperf benchmark */
 void auxInitDisplayModePolicy( GLenum type );
 GLenum auxGetDisplayModePolicy( void );
 GLenum auxInitDisplayModeID( GLint id );
 GLint auxGetDisplayModeID( void );
 GLenum auxGetDisplayMode( void );

/*
 void auxGetScreenSize( GLint *width, GLint *height );

 void auxAnimation( GLint flag );
*/


#ifdef __cplusplus
}
#endif


#endif /* AUX_INCLUDED */

