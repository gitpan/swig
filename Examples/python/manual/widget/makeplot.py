# Now use our plotting widget

import posix
import sys
import string
from plotwidget import *
from math import *

line = raw_input("Enter a function of x : ")
ranges = string.split(raw_input("Enter xmin,ymin,xmax,ymax :"),",")

print "Making a plot..."

w = PlotWidget(500,500,string.atof(ranges[0]),string.atof(ranges[1]),
               string.atof(ranges[2]),string.atof(ranges[3]))


code = "def func(x): return " + line
exec(code)

w.set_pymethod(func)
w.plot()

f = open("plot.gif","w")
w.save(f)
f.close()
posix.system("xv plot.gif &")



