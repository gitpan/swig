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
    Plot3D      *p3;
    ColorMap    *cm;
    
    double      x,y;
    double      dx,dy;
    double      z1,z2,z3,z4,za;
    int         c;
    
    /* Create a framebuffer */

    f = new_FrameBuffer(600,600);

    /* Load a colormap */

    cm = new_ColorMap("cm15");

    /* Create a new 2D image */

    FrameBuffer_clear(f,BLACK);
    p3 = new_Plot3D(f,-6.3,-6.3,-1.5,6.3,6.3,1.5);

    /* Set viewing region in 2D plot */
    
    Plot3D_setview(p3,50,50,550,550);

    /* Set how far away from the image we are */
    Plot3D_lookat(p3,20);

    /* Set the field of view for the perspective */
    
    Plot3D_autoperspective(p3,40);
    
    /* Now make a plot of a 3D function */
    
    /* Make a frame */

    FrameBuffer_noclip(f);
    FrameBuffer_box(f,49,49,550,550,WHITE);
    Plot3D_start(p3);   /* Always call this prior to making an image */
    Plot3D_clear(p3,BLACK);
    Plot3D_rotu(p3,60);
    Plot3D_rotz(p3,40);
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
	    za = 0.25*(z1+z2+z3+z4);
	    c = (int) ((za + 1.0)*120) + 16;
	    if (c < 16) c = 16;
	    if (c > 254) c = 254;
	    Plot3D_solidquad(p3,x,y,z1,x+dx,y,z2,x+dx,y+dy,z3,x,y+dy,z4,c);
	    y = y + dy;
	}
	x = x + dx;
    }
    
    /* Make a GIF file */

    FrameBuffer_writeGIF(f,cm,"plot.gif");

}

	    

       

    

