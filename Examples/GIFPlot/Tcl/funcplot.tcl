# A Simple Tcl example that plots a 2D function

load ./gifplot.sl

source plot2d.tcl

set f [FrameBuffer -args 400 400]
set c [ColorMap -args "cmap"]
set p2 [Plot2D -args $f -6.3 -2 6.3 2]

# Now make a plot of a sin function

newplot $p2 1.57 0.25 "sin(x)" X Y
plotfunc $p2 "sin(x)" 100 $YELLOW $TRIANGLE

$f writeGIF $c "plot.gif" 

puts "Image writte to 'plot.gif'"

