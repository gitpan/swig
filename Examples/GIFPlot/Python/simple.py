# Simple GIFPlot example in Python

from gifplot import *

f = FrameBuffer(300,300)
cm = ColorMap("cmap")

f.clear(BLACK)
f.drawstring(50,50, WHITE,BLACK, "Hello world", HORIZONTAL)
f.solidbox(200,200,220,240,BLUE)
f.line(0,290,293,50,RED)
f.circle(100,100,10,YELLOW)

f.writeGIF(cm,"plot.gif")

print "Image written to 'plot.gif'"

