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
    double      z1,z2,z3,z4;
    int         c1,c2,c3,c4;
    
    /* Create a framebuffer */

    f = new_FrameBuffer(700,400);

    /* Load a colormap */

    cm = new_ColorMap("cm15");

    /* Create a new 2D image */

    FrameBuffer_clear(f,BLACK);
    p3 = new_Plot3D(f,-6.3,-6.3,-1.5,6.3,6.3,1.5);

    /* Set viewing region in 2D plot */
    
    Plot3D_setview(p3,50,50,650,350);

    /* Set how far away from the image we are */
    Plot3D_lookat(p3,20);

    /* Set the field of view for the perspective */
    

//    Plot3D_autoperspective(p3,40);

    Plot3D_autoortho(p3);
    
    /* Now make a plot of a 3D function */
    
    /* Make a frame */

    FrameBuffer_noclip(f);
    FrameBuffer_box(f,49,49,650,350,WHITE);
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

	    Plot3D_interpquad(p3,x,y,z1,c1,
			      x+dx,y,z2,c2,
			      x+dx,y+dy,z3,c3,
			      x,y+dy,z4,c4);
	    y = y + dy;
	}
	x = x + dx;
    }
    
    /* Make a GIF file */

    FrameBuffer_writeGIF(f,cm,"plot.gif");

}

	    

       

    

