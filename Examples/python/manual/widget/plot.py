# Now use our plotting widget

import posix
from plotwidget import *
from math import *

def func1(x):
	return 0.5*sin(x)+0.25*sin(2*x)+0.125*cos(4*x)

print "Making plot1.gif..."
# Make a widget and set callback
w = PlotWidget(500,500,-10,-2,10,2)
w.set_pymethod(func1)
w.plot()
f = open("plot1.gif","w")
w.save(f)
f.close()

# Comment this line out if you don't have xv
posix.system("xv plot1.gif &")

# Make another plot

print "Making plot2.gif..."
w1 = PlotWidget(500,500,-4,-1,4,16)
w1.set_pymethod(lambda x: x*x)
w1.plot()
f = open("plot2.gif","w")
w1.save(f)
f.close()

posix.system("xv plot2.gif &")

# Make yet another plot

print "Making plot3.gif..."
w2 = PlotWidget(500,500,-7,-1.5,7,1.5)
w2.set_pymethod(sin)
w2.plot()
f = open("plot3.gif","w")
w2.save(f)
f.close()

posix.system("xv plot3.gif &")
