from image2d import *
import string

class PlotMesh(Image2D):
	def __init__(self,filename,xmin,ymin,xmax,ymax):
		Image2D.__init__(self,xmin,ymin,xmax,ymax)

	# Now read in a mesh file in pieces

		pts = []

	# Read in data points
		atoi = string.atoi
		atof = string.atof
		f = open(filename+".pts","r")
		l = string.split(f.readline())
		npoints = atoi(l[0])
		for i in range(0,npoints):
			l = string.split(f.readline())
			pts.append((atof(l[0]),atof(l[1])))
	
	# Read in mesh data

		f.close()
		f = open(filename+".tris","r")
		l = string.split(f.readline())
		ntris = atoi(l[0])
		tris = [ ]
		for i in range(0,ntris):
			l = string.split(f.readline())
			tris.append((atoi(l[0])-1,atoi(l[1])-1,atoi(l[2])-1,atoi(l[3])))
		
		f.close()
					
	# Read in solution data

		f = open(filename+".out","r")
		soln = [ ]
		for i in range(0,npoints):
			l = string.split(f.readline())
			soln.append(atof(l[0]))

		self.pts = pts
		self.npoints = npoints
		self.tris = tris
		self.ntris = ntris
		self.soln = soln
		self.draw_soln = 0

	def draw(self):
		self.axis_origin = (self.xmin,self.ymin)
		self.xtick_spacing = (self.xmax - self.xmin)/10.0
		self.ytick_spacing = (self.ymax - self.ymin)/10.0
		self.newplot()
		if self.draw_soln == 0:
			i = 0
			while i < self.ntris:
				tri = self.tris[i]
				pt1 = self.pts[tri[0]]
				pt2 = self.pts[tri[1]]
				pt3 = self.pts[tri[2]]
			
				# Now draw the mesh

				self.solidtriangle(pt1[0],pt1[1],pt2[0],pt2[1],pt3[0],pt3[1],gifplot.WHITE+tri[3])
				self.triangle(pt1[0],pt1[1],pt2[0],pt2[1],pt3[0],pt3[1],gifplot.BLACK)
				i = i + 1
		else:
			cmin = min(self.soln)
			cmax = max(self.soln)
			dc   = cmax - cmin
			i = 0
			while i < self.ntris:
				tri = self.tris[i]
				pt1 = self.pts[tri[0]]
				pt2 = self.pts[tri[1]]
				pt3 = self.pts[tri[2]]
				c1 = (self.soln[tri[0]] - cmin)*239/dc + 16
				c2 = (self.soln[tri[1]] - cmin)*239/dc + 16
				c3 = (self.soln[tri[2]] - cmin)*239/dc + 16			

				# Now draw the mesh

				self.interptriangle(pt1[0],pt1[1],c1,pt2[0],pt2[1],c2,pt3[0],pt3[1],c3);
				i = i + 1

		self.drawaxis()

class Dual(PlotMesh):
	def __init__(self,filename,xmin,ymin,xmax,ymax):
		PlotMesh.__init__(self,filename,xmin,ymin,xmax,ymax)
		self.title1 = "Mesh"
		self.title2 = "Solution"
	def draw(self):
		width = self.frame.width
		height = self.frame.height
		self.viewport(0,0,width,height/2 - 2)
		self.draw_soln = 0
		self.title = self.title1
		PlotMesh.draw(self)
		self.viewport(0,height/2 + 2, width, height)
		self.draw_soln = 1
		self.title = self.title2
		PlotMesh.draw(self)

mesh = PlotMesh("../Data/mesh",5,0,35,25)
mesh.title = "Mesh"
mesh.xaxis_label = 'X'
mesh.yaxis_label = 'Y'
mesh.filename = "mesh.gif"
mesh.show()

mesh.filename = "soln.gif"
mesh.title = "Solution"
mesh.draw_soln = 1	
mesh.spawned_viewer = 0
mesh.show()

both = Dual("../Data/mesh",-10,0,50,25)
both.filename = "both.gif"
both.xaxis_label = 'X'
both.yaxis_label = 'Y'
both.zoom(200)
both.down(55)
both.zoom(300)
both.show()


