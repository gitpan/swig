from image import *
import string

class PlotMesh(Image):
	def __init__(self,filename,xmin,ymin,xmax,ymax,width=500,height=500):
		Image.__init__(self,width,height,xmin,ymin,xmax,ymax)

	# Now read in a mesh file in pieces

		pts = []

	# Read in data points
		atoi = string.atoi
		atof = string.atof
		f = open(filename+".pts","r")
		npoints = atoi(f.readline())
		for i in range(0,npoints):
			l = string.split(f.readline())
			pts.append((atof(l[0]),atof(l[1])))
	
	# Read in mesh data

		f.close()
		f = open(filename+".tris","r")
		ntris = string.atoi(f.readline())
		tris = [ ]
		for i in range(0,ntris):
			l = string.split(f.readline())
			tris.append((atoi(l[0])-1,atoi(l[1])-1,atoi(l[2])-1,atoi(l[3])))
		
		f.close()

	# Set up local attributes

		self.pts = pts
		self.npoints = npoints
		self.tris = tris
		self.ntris = ntris

	# Draw mesh

	def draw(self):
		self.clear(0);
		i = 0
		while i < self.ntris:
			tri = self.tris[i]
			pt1 = self.pts[tri[0]]
			pt2 = self.pts[tri[1]]
			pt3 = self.pts[tri[2]]
			
			# Now draw the mesh

			self.triangle(pt1[0],pt1[1],pt2[0],pt2[1],pt3[0],pt3[1],tri[3]);
			i = i + 1

	# Draw a triangle

	def triangle(self,x1,y1,x2,y2,x3,y3,color):
		self.line(x1,y1,x2,y2,color)
		self.line(x2,y2,x3,y3,color)
		self.line(x3,y3,x1,y1,color)

mesh = PlotMesh("mesh",5,0,35,25)
mesh.show()


