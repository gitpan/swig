#include "gifplot.h"
#include <math.h>

int main(int argc, char **argv) {

    FrameBuffer *f;
    ColorMap    *cm;
    int i;
    int x1,y1,x2,y2,c;
    
    /* Create a framebuffer */

    f = new_FrameBuffer(300,300);

    /* Load a colormap */

    cm = new_ColorMap("cm15");

    /* Create a new 2D image */

    FrameBuffer_clear(f,BLUE);
    FrameBuffer_setclip(f,0,0,200,200);
    FrameBuffer_solidbox(f,0,0,300,300,BLACK);
    for (i = 0; i < 400; i++) {
	x1 = rand() % 400;
	y1 = rand() % 400;
	x2 = rand() % 400;
	y2 = rand() % 400;
	c = rand() % 256;
	FrameBuffer_line(f,x1,y1,x2,y2,c);
    }
    FrameBuffer_box(f,0,0,199,199,WHITE);
    FrameBuffer_setclip(f,175,175,300,300);
    FrameBuffer_solidbox(f,0,0,300,300,BLACK);
    for (i = 0; i < 100; i++) {
	x1 = rand() % 400;
	y1 = rand() % 400;
	x2 = rand() % 400;
	y2 = rand() % 400;
	c = rand() % 256;
	FrameBuffer_box(f,x1,y1,x2,y2,c);
    }
    FrameBuffer_box(f,175,175,299,299,WHITE);

    FrameBuffer_writeGIF(f,cm,"plot.gif");

}

	    

       

    

