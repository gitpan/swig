from image import *

class PlotFunc(Image):
	def __init__(self,func,xmin,ymin,xmax,ymax,width=500,height=500):
		Image.__init__(self,width,height,xmin,ymin,xmax,ymax)
		self.func = func
		self.npoints = 100
		self.color = WHITE
	def draw(self):
		self.clear(0)
		lastx = self.xmin
		lasty = self.func(lastx)
		dx = 1.0*(self.xmax-self.xmin)/self.npoints
		x = lastx+dx
		for i in range(0,self.npoints):
			y = self.func(x)
			self.line(lastx,lasty,x,y,self.color)
			lastx = x
			lasty = y
			x = x + dx

		self.axis(WHITE)
		
# Make a few function plots

import math

p1 = PlotFunc(math.sin,-6.3,-1.2,6.3,1.2)
p1.show("plot1.gif")

p2 = PlotFunc(lambda x: 0.5*math.sin(x)+0.75*math.sin(2*x)-0.6*math.sin(3*x),-10,-2,10,2)
p2.show("plot2.gif")

del p1
del p2

	
