#include "gifplot.h"
#include <math.h>

double func(double x, double y) {
    double r;
    double f;
    r = sqrt(x*x + y*y);

    f = (sin(0.30*r*x)+cos(0.30*r*y))/(1.0+r);
    return f;

    
}

int main(int argc, char **argv) {

    FrameBuffer *f;
    Plot2D      *p2;
    ColorMap    *cm;
    
    double      x,y;
    double      dx,dy;
    double      z1,z2,z3,z4;
    int         c1,c2,c3,c4;
    
    /* Create a framebuffer */

    f = new_FrameBuffer(600,600);

    /* Load a colormap */

    cm = new_ColorMap("cm15");

    /* Create a new 2D image */

    FrameBuffer_clear(f,BLACK);
    p2 = new_Plot2D(f,-6.3,-6.3,6.3,6.3);

    /* Set viewing region in 2D plot */
    
    Plot2D_setview(p2,50,50,550,550);

    /* Make a frame */

    FrameBuffer_noclip(f);
    FrameBuffer_box(f,49,49,550,550,WHITE);
    Plot2D_start(p2);   /* Always call this prior to making an image */
    Plot2D_clear(p2,BLACK);
    x = -6.3;
    dx = 0.25;
    while (x < 6.3) {
	y = -6.3;
	dy = 0.25;
	while (y < 6.3) {
	    z1 = func(x,y);
	    z2 = func(x+dx,y);
	    z3 = func(x+dx,y+dy);
	    z4 = func(x,y+dy);
	    c1 = (int) ((z1 + 1.0)*120) + 16;
	    if (c1 < 16) c1 = 16;
	    if (c1 > 254) c1 = 254;

	    c2 = (int) ((z2 + 1.0)*120) + 16;
	    if (c2 < 16) c2 = 16;
	    if (c2 > 254) c2 = 254;

	    c3 = (int) ((z3 + 1.0)*120) + 16;
	    if (c3 < 16) c3 = 16;
	    if (c3 > 254) c3 = 254;

	    c4 = (int) ((z4 + 1.0)*120) + 16;
	    if (c4 < 16) c4 = 16;
	    if (c4 > 254) c4= 254;

	    /* Colors must be assigned to the corners of the box
	       in the following order :

	       (x,y), (x, y+dy), (x+dx,y), (x+dx,y+dy)
             */
	      
	    Plot2D_interpbox(p2,x,y,x+dx,y+dy,c1,c4,c2,c3);
	    y = y + dy;
	}
	x = x + dx;
    }
    
    /* Make a GIF file */

    FrameBuffer_writeGIF(f,cm,"plot.gif");

}

	    

       

    

