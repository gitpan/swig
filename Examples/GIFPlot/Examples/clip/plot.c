#include "gifplot.h"
#include <math.h>

int main(int argc, char **argv) {

    FrameBuffer *f;
    Plot2D      *p2;
    ColorMap    *cm;

    double      x1,x2,y1,y2;
    double      dx;
    
    /* Create a framebuffer */

    f = new_FrameBuffer(600,600);

    /* Load a colormap */

    cm = new_ColorMap("cm15");

    /* Create a new 2D image */

    FrameBuffer_clear(f,BLACK);

    p2 = new_Plot2D(f,-6.3,-1.5,6.3,1.5);

    /* Set viewing region in 2D plot */
    
    Plot2D_setview(p2,50,50,550,550);
    
    /* Now make a plot of the sin() function */
    
    /* Make a frame */

    FrameBuffer_noclip(f);
    FrameBuffer_box(f,50,50,550,550,WHITE);
    FrameBuffer_drawstring(f,290,555,YELLOW,BLACK,"sin(x)",HORIZONTAL);

    Plot2D_start(p2);   /* Always call this prior to making an image */
    Plot2D_xaxis(p2,0,0,3.14159/4.0,4, WHITE);
    Plot2D_yaxis(p2,0,0,0.25,4, WHITE);
    
    x1 = -6.3;
    y1 = sin(x1);
    dx = 0.05;
    while (x1 < 6.3) {
	x2 = x1+dx;
	y2 = sin(x2);
	Plot2D_line(p2,x1,y1,x2,y2,YELLOW);
	x1 = x2;
	y1 = y2;
    }

    /* Make a GIF file */

    FrameBuffer_writeGIF(f,cm,"plot.gif");

}

	    

       

    

