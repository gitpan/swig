from image3d import *
import math

class Scene(Image3D):
	def __init__(self):
		Image3D.__init__(self,-5,-5,-5,5,5,5)
		self.title = "Scene"
		self.lookat(20)
		self.autoperspective(40)

	# Draw a few primitives

	def draw(self):
		self.newplot()
		self.solidquad(0,0,0,0,2,0,2,2,0,2,0,0,BLUE)
		self.solidquad(0,0,2,0,2,2,2,2,2,2,0,2,WHITE)
		self.solidquad(0,0,0,0,2,0,0,2,2,0,0,2,RED)
		self.solidquad(2,0,0,2,2,0,2,2,2,2,0,2,CYAN)
		self.solidquad(0,0,0,0,0,2,2,0,2,2,0,0,YELLOW)
		self.solidquad(0,2,0,0,2,2,2,2,2,2,2,0,GREEN)
		self.solidtriangle(-5,-5,-5,5,3,5,-5,-5,5,BLUE)
	        z = 0.0
		dz = 0.1
		for j in range(0,50):
			dx = 0.1
			lastx = -5.0
			lasty = math.sin(lastx)
			x = lastx
			for i in range(0,100):
				x = x + dx
				y = math.sin(x)
				self.quad(lastx,lasty,lasty+z,x,y,y+z,
					       x,y,y+z-dz,lastx,lasty,lasty+z-dz,4*j)
				lastx = x
				lasty = y
			z = z + dz
		

			
s = Scene()
s.rotr(30)
s.rotd(20)
s.zoom(160)
s.show()
