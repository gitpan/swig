# An example using our set/get functions

from pde import *
from image import *
import string

# Image class

class HeatImg(Image):
	def __init__(self,h,width=300,height=300):
		Image.__init__(self,width,height,0.0,0.0,1.0,1.0)
		self.h = h
		# Create a bunch of colors (Greyscale)
		cmap = []
		for i in range(0,255):
			cmap.append((i,i,i))
		self.colormap(cmap)
		self.cmin = 0.0
		self.cmax = 1.0
		self.imgno = 1
	def draw(self):
		self.clear(0)
		dx = 1.0/(self.h.grid.xpoints-2)
		dy = 1.0/(self.h.grid.ypoints-2)
		i = 1
		x = 0.0
		while i < self.h.grid.xpoints:
			j = 1;
			y = 0.0
			while j < self.h.grid.ypoints:
				c = int((self.h.grid[i][j]-self.cmin)/(self.cmax-self.cmin)*255)
				self.solidbox(x,y+dy,x+dx,y,c)
				j = j + 1
				y = y + dy
			i = i + 1
			x = x + dx
		self.name = "image"+string.zfill(self.imgno,4)+".gif"
		self.imgno = self.imgno+1

# Set up an initial condition

def initcond(h):
	h.set_temp(0.0)
	nx = h.grid.xpoints
	for i in range(0,nx):
		h.grid[i][0] = 1.0

# Set up a problem and run it

h = Heat2d(50,50)

# Make an image

img = HeatImg(h)

initcond(h)
fileno = 1

for i in range(0,25):
	h.solve(100)
	h.dump("Dat"+str(fileno))
	img.show()
	print "time = ", h.time
	fileno = fileno+1


# Calculate average temperature over the region

sum = 0.0
for i in range(0,h.grid.xpoints):
	for j in range(0,h.grid.ypoints):
		sum = sum + h.grid[i][j]

avg = sum/(h.grid.xpoints*h.grid.ypoints)

print "Avg temperature = ",avg

del h
del img


