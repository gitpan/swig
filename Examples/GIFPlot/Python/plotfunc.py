# Class to plot a simple mathematical function

from image2d import *

class PlotFunc(Image2D):
	def __init__(self,func,xmin,ymin,xmax,ymax,npoints=100):
		Image2D.__init__(self,xmin,ymin,xmax,ymax)
		self.symbol = None
		self.color = YELLOW
		self.func = func
		self.npoints = npoints
	def draw(self):
		pts = []
		dx = 1.0*(self.xmax-self.xmin)/self.npoints
		x = self.xmin
		for i in xrange(0,self.npoints):
			pts.append(self.func(x))
			x = x + dx
		self.newplot()
		self.plotarray(pts,self.xmin,self.xmax,self.color,self.symbol)



# Sample code

import math

p = PlotFunc(lambda x: 0.5*math.sin(x)+0.75*math.sin(2*x)-0.6*math.sin(3*x),-10,-2,10,2,200)
p.symbol = TRIANGLE
p.xaxis_label = "X"
p.yaxis_label = "Y"
p.xtick_spacing = 3.14159265/2
p.ytick_spacing = 0.5
p.show()

