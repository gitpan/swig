load ./gifplot.sl
source plot2d.tcl

set f [FrameBuffer -args 500 500]
set c [ColorMap -args cmap]
set p2 [Plot2D -args [$f cget -this] -6 -2 6 2]

