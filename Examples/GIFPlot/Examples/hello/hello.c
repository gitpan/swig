#include "gifplot.h"

int main(int argc, char **argv) {

    FrameBuffer *f;
    ColorMap    *cm;

    /* Create a framebuffer */

    f = new_FrameBuffer(300,300);

    /* Load a colormap */

    cm = new_ColorMap(0);

    /* Create a new 2D image */

    FrameBuffer_clear(f,BLACK);
    FrameBuffer_solidbox(f,50,50,250,250,BLUE);
    FrameBuffer_drawstring(f,105,150,WHITE,BLUE,"HELLO WORLD",HORIZONTAL);
    FrameBuffer_writeGIF(f,cm,"plot.gif");

}
