#include "gifplot.h"

int main(int argc, char **argv) {

    FrameBuffer *f;
    Plot3D      *p3;
    ColorMap    *cm;

    /* Create a framebuffer */

    f = new_FrameBuffer(300,300);

    /* Load a colormap */

    cm = new_ColorMap(0);

    /* Create a new 3D image */

    FrameBuffer_clear(f,BLACK);
    p3 = new_Plot3D(f,0,0,0,1,1,1);

    Plot3D_lookat(p3,5);
    Plot3D_autoperspective(p3,40);
    Plot3D_rotz(p3,45);
    Plot3D_rotu(p3,40);
    Plot3D_zoom(p3,200);
    
    Plot3D_start(p3);   
    Plot3D_clear(p3,BLACK);
    Plot3D_line(p3,0,0,0,0,0,1,WHITE);
    Plot3D_line(p3,0,1,0,0,1,1,WHITE);
    Plot3D_line(p3,1,0,0,1,0,1,WHITE);
    Plot3D_line(p3,1,1,0,1,1,1,WHITE);
    Plot3D_line(p3,0,0,0,1,0,0,WHITE);
    Plot3D_line(p3,0,0,1,1,0,1,WHITE);
    Plot3D_line(p3,0,1,0,1,1,0,WHITE);
    Plot3D_line(p3,0,1,1,1,1,1,WHITE);
    Plot3D_line(p3,0,0,0,0,1,0,WHITE);
    Plot3D_line(p3,1,0,0,1,1,0,WHITE);
    Plot3D_line(p3,0,0,1,0,1,1,WHITE);
    Plot3D_line(p3,1,0,1,1,1,1,WHITE);
    
    /* Make a GIF file */

    FrameBuffer_writeGIF(f,cm,"plot.gif");

}

	    

       

    

