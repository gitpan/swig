# Plot a 3D function
from image3d import *
import math

MESH = 0
SOLID = 1
SMOOTH = 2

class PlotFunc3D(Image3D):
	def __init__(self,func,xmin,ymin,zmin,xmax,ymax,zmax,nx=40,ny=40):
		Image3D.__init__(self,xmin,ymin,zmin,xmax,ymax,zmax)
		self.lookat(2*max([xmax-xmin,ymax-ymin,zmax-zmin]))
		self.autoperspective(40)
		self.func = func
		self.nxpoints = nx
		self.nypoints = ny
		self.mode = MESH

	# Draw a few primitives

	def drawmesh(self):
		self.min = self.zmin
		self.max = self.zmax
		self.newplot()
		dx = 1.0*(self.xmax-self.xmin)/self.nxpoints
		dy = 1.0*(self.ymax-self.ymin)/self.nypoints
		cscale = 240.0/(self.zmax-self.zmin)
		zmin = self.zmin
		x = self.xmin
		for i in xrange(0,self.nxpoints):
			y = self.ymin
			for j in xrange(0,self.nypoints):
				z1 = self.func(x,y)
				z2 = self.func(x+dx,y)
				z3 = self.func(x+dx,y+dy)
				z4 = self.func(x,y+dy)
				c1 = cscale*(z1-zmin)
				c2 = cscale*(z2-zmin)
				c3 = cscale*(z3-zmin)
				c4 = cscale*(z4-zmin)
				c = (c1+c2+c3+c4)/4
				if (c < 0) : c = 0
				if c > 239 : c = 239
				self.quad(x,y,z1,x+dx,y,z2,x+dx,y+dy,z3,x,y+dy,z4,c+16)
				y = y + dy		
			x = x + dx

	def drawsolid(self):
		self.min = self.zmin
		self.max = self.zmax
		self.newplot()
		dx = 1.0*(self.xmax-self.xmin)/self.nxpoints
		dy = 1.0*(self.ymax-self.ymin)/self.nypoints
		cscale = 240.0/(self.zmax-self.zmin)
		zmin = self.zmin
		x = self.xmin
		for i in xrange(0,self.nxpoints):
			y = self.ymin
			for j in xrange(0,self.nypoints):
				z1 = self.func(x,y)
				z2 = self.func(x+dx,y)
				z3 = self.func(x+dx,y+dy)
				z4 = self.func(x,y+dy)
				c1 = cscale*(z1-zmin)
				c2 = cscale*(z2-zmin)
				c3 = cscale*(z3-zmin)
				c4 = cscale*(z4-zmin)
				c = (c1+c2+c3+c4)/4
				if (c < 0) : c = 0
				if c > 239 : c = 239
				self.solidquad(x,y,z1,x+dx,y,z2,x+dx,y+dy,z3,x,y+dy,z4,c+16)
				y = y + dy		
			x = x + dx


	def drawsmooth(self):
		self.min = self.zmin
		self.max = self.zmax
		self.newplot()
		dx = 1.0*(self.xmax-self.xmin)/self.nxpoints
		dy = 1.0*(self.ymax-self.ymin)/self.nypoints
		cscale = 240.0/(self.zmax-self.zmin)
		zmin = self.zmin
		x = self.xmin
		for i in xrange(0,self.nxpoints):
			y = self.ymin
			for j in xrange(0,self.nypoints):
				z1 = self.func(x,y)
				z2 = self.func(x+dx,y)
				z3 = self.func(x+dx,y+dy)
				z4 = self.func(x,y+dy)
				c1 = cscale*(z1-zmin)
				c2 = cscale*(z2-zmin)
				c3 = cscale*(z3-zmin)
				c4 = cscale*(z4-zmin)
				if c1 < 0 : c1 = 0
				if c1 > 239 : c1 = 239
				if c2 < 0 : c2 = 0
				if c2 > 239 : c2 = 239
				if c3 < 0 : c3 = 0
				if c3 > 239 : c3 = 239
				if c4 < 0 : c4 = 0
				if c4 > 239 : c4 = 239

				self.interpquad(x,y,z1,c1+16,x+dx,y,z2,c2+16,
						x+dx,y+dy,z3,c3+16,x,y+dy,z4,c4+16)
				y = y + dy		
			x = x + dx


	def draw(self):
		self.newplot()
		if self.mode == MESH:
			self.drawmesh()
		elif self.mode == SOLID:
			self.drawsolid()
		elif self.mode == SMOOTH:
			self.drawsmooth()

		

p = PlotFunc3D(lambda x,y: math.sin(x)*math.cos(y),-5,-5,-2,5,5,2)
p.filename = "plot3d.gif"
p.rotu(60)
p.rotr(30)
p.rotd(10)
p.show()

p.filename = "plot3d_solid.gif"
p.mode = SOLID
p.show()

p.filename = "plot3d_smooth.gif"
p.mode = SMOOTH
p.show()
