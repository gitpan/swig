# Generic Image Class
#
# Built on top of the 'gd-1.2' library by Thomas Boutell
#

import gd

BLACK = 0
WHITE = 1
RED   = 2
GREEN = 3
BLUE  = 4

class Image:
	def __init__(self,width,height,xmin=0.0,ymin=0.0,xmax=1.0,ymax=1.0):
		self.im = gd.gdImageCreate(width,height)
		self.xmin   = xmin
		self.ymin   = ymin
		self.xmax   = xmax
		self.ymax   = ymax
		self.width  = width
		self.height = height
		self.dx     = 1.0*(xmax-xmin)
		self.dy     = 1.0*(ymax-ymin)
		self.xtick  = self.dx/10.0
		self.ytick  = self.dy/10.0
		self.ticklen= 3
		self.name   = "image.gif"
		gd.gdImageColorAllocate(self.im,0,0,0)        # Black
		gd.gdImageColorAllocate(self.im,255,255,255)  # White
		gd.gdImageColorAllocate(self.im,255,0,0)      # Red
		gd.gdImageColorAllocate(self.im,0,255,0)      # Green
		gd.gdImageColorAllocate(self.im,0,0,255)      # Blue

	def __del__(self):
		print "Deleting"
		gd.gdImageDestroy(self.im)
	
	# Dump out this image to a file

	def write(self,name="NONE"):
		if name == "NONE":
			name = self.name
		f = gd.fopen(name,"w")
		gd.gdImageGif(self.im,f)
		gd.fclose(f)
		self.name = name
	
	# Virtual method that the user classes define

	def draw(self):
		print "No drawing method specified."

	# A combination of write and draw

	def show(self,filename="NONE"):
		self.draw()
		self.write(filename)

	# Load up a colormap from an array of tuples

	def colormap(self, cmap):
		for i in range(0,255):
			gd.gdImageColorDeallocate(self.im,i)
		for c in cmap:
			gd.gdImageColorAllocate(self.im,c[0],c[1],c[2])

	# Change viewing region

	def region(self,xmin,ymin,xmax,ymax):
		self.xmin = xmin
		self.ymin = ymin
		self.xmax = xmax
		self.ymax = ymax
		self.dx     = 1.0*(xmax-xmin)
		self.dy     = 1.0*(ymax-ymin)

	# Transforms a point into screen coordinates

	def transform(self,x,y):
		npt = []
		ix = (x-self.xmin)/self.dx*self.width + 0.5
		iy = (self.ymax-y)/self.dy*self.height + 0.5
		return (ix,iy)

	# A few graphics primitives

	def clear(self,color):
		gd.gdImageFilledRectangle(self.im,0,0,self.width,self.height,color)

	def plot(self,x,y,color):
		ix,iy = self.transform(x,y)
		gd.gdImageSetPixel(self.im,ix,iy,color)

	def line(self,x1,y1,x2,y2,color):
		ix1,iy1 = self.transform(x1,y1)
		ix2,iy2 = self.transform(x2,y2)
		gd.gdImageLine(self.im,ix1,iy1,ix2,iy2,color)

	def box(self,x1,y1,x2,y2,color):
		ix1,iy1 = self.transform(x1,y1)
		ix2,iy2 = self.transform(x2,y2)
		gd.gdImageRectangle(self.im,ix1,iy1,ix2,iy2,color)

	def solidbox(self,x1,y1,x2,y2,color):
		ix1,iy1 = self.transform(x1,y1)
		ix2,iy2 = self.transform(x2,y2)
		gd.gdImageFilledRectangle(self.im,ix1,iy1,ix2,iy2,color)
	
	def arc(self,cx,cy,w,h,s,e,color):
		ix,iy = self.transform(cx,cy)
		iw = (x - self.xmin)/self.dx * self.width
		ih = (y - self.ymin)/self.dy * self.height
		gd.gdImageArc(self.im,ix,iy,iw,ih,s,e,color)

	def fill(self,x,y,color):
		ix,iy = self.transform(x,y)
		gd.gdImageFill(self,ix,iy,color)

	def axis(self,color):
		self.line(self.xmin,0,self.xmax,0,color)
		self.line(0,self.ymin,0,self.ymax,color)
		x = -self.xtick*(int(-self.xmin/self.xtick)+1)
		while x <= self.xmax:
			ix,iy = self.transform(x,0)
			gd.gdImageLine(self.im,ix,iy-self.ticklen,ix,iy+self.ticklen,color)
			x = x + self.xtick
		y = -self.ytick*(int(-self.ymin/self.ytick)+1)
		while y <= self.ymax:
			ix,iy = self.transform(0,y)
			gd.gdImageLine(self.im,ix-self.ticklen,iy,ix+self.ticklen,iy,color)
			y = y + self.ytick

	# scalex(s).  Scales the x-axis.  s is given as a scaling factor

	def scalex(self,s):
		xc = self.xmin + self.dx/2.0
		dx = self.dx*s
		xmin = xc - dx/2.0
		xmax = xc + dx/2.0
		self.region(xmin,self.ymin,xmax,self.ymax)

	# scaley(s).  Scales the y-axis.  s is given as a percent with s = 100 meaning no effect

	def scaley(self,s):
		yc = self.ymin + self.dy/2.0
		dy = self.dy*s
		ymin = yc - dy/2.0
		ymax = yc + dy/2.0
		self.region(self.xmin,ymin,self.xmax,ymax)

	# Zooms a current image.  s is given as a percent with s = 100 meaning no effect

	def zoom(self,s):
		s = 100.0/s
		self.scalex(s)
		self.scaley(s)

	# Move image left.  s is given in range 0,100. 100 moves a full screen left

	def left(self,s):
		dx = self.dx*s/100.0
		xmin = self.xmin + dx
		xmax = self.xmax + dx
		self.region(xmin,self.ymin,xmax,self.ymax)

	# Move image right.  s is given in range 0,100. 100 moves a full screen right

	def right(self,s):
		self.left(-s)

	# Move image down.  s is given in range 0,100. 100 moves a full screen down

	def down(self,s):
		dy = self.dy*s/100.0
		ymin = self.ymin + dy
		ymax = self.ymax + dy
		self.region(self.xmin,ymin,self.xmax,ymax)

	# Move image up.  s is given in range 0,100. 100 moves a full screen up

	def up(self,s):
		self.down(-s)

	# Center image

	def center(self,x,y):
		self.right(50-x)
		self.up(50-y)
	
