# Make a plot from a web-server log

from image2d import *
from image3d import *
import string
import regex

class HitsPerDay(Image2D):
	def __init__(self,filename):
		Image2D.__init__(self,0,0,32,1)

	# Now read in a mesh file in pieces

		hits = [0]*32

	# Read in data points
		f = open(filename,"r")
		l = f.readline()
		while l:
			try:
				d = string.split(l)[3]
				fields = string.split(d[1:],"/")
				day = string.atoi(fields[0])
				hits[day] = hits[day] + 1
			except:
				pass
			l = f.readline()			
		f.close()
		self.hits = hits
		self.color = BLUE
		self.ymax = max(self.hits)
		self.xtick_spacing = 1.0
		self.ytick_spacing = self.ymax / 10.0
		self.xaxis_label = "Day"
		self.yaxis_label = "Total hits"

	def draw(self):
		self.newplot()
		self.plotbar(self.hits,0,31,self.color)
		self.plotarray(self.hits,0,31,WHITE,CROSS)
		self.drawaxis()


class HitsByHour(Image2D):
	def __init__(self,filename):
		Image2D.__init__(self,0,0,24,1)

	# Now read in a mesh file in pieces

		hits = [0]*24

	# Read in data points
		f = open(filename,"r")
		l = f.readline()
		while l:
			try:
				d = string.split(l)[3]
				fields = string.split(d[1:],"/")
				t = string.split(fields[2][5:],":")
				hour = string.atoi(t[0])
				hits[hour] = hits[hour]+1
			except:
				pass
			l = f.readline()			
		f.close()
		self.hits = hits
		self.color = BLUE
		self.ymax = max(self.hits)
		self.ytick_spacing = self.ymax / 10.0
		self.xtick_spacing = 1.0
		self.xaxis_label = "Hour"
		self.yaxis_label = "Total hits"
	def draw(self):
		self.newplot()
		self.plotbar(self.hits,0,24,self.color)
		self.plotarray(self.hits,0,24,WHITE,CROSS)
		self.drawaxis()

class HitsPerHour(Image3D):
	def __init__(self,filename):

	# Now read in a mesh file in pieces
		hits = []
		for i in range(0,31):
			hits.append([0]*24)

	# Read in data points
		f = open(filename,"r")
		l = f.readline()
		while l:
			try:
				d = string.split(l)[3]
				fields = string.split(d[1:],"/")
				day = string.atoi(fields[0])
				t = string.split(fields[2][5:],":")
				hour = string.atoi(t[0])
				hits[day][hour] = hits[day][hour]+1
			except:
				pass
			l = f.readline()			
		f.close()
		Image3D.__init__(self,0,0,0,31,24,10.0)
		self.max = max(map(max,hits))
		self.min = 0
		self.hits = hits
		self.title = "Hits per hour"
		self.draw_box = 0
		self.lookat(50)
		self.autoperspective(40)
	def draw(self):
		self.newplot()
		zscale = 239.0/self.max
		zscale2 = 10.0/self.max
		for i in xrange(0,30):
			for j in xrange(0,23):
				z1 = self.hits[i][j]
				z2 = self.hits[i+1][j]
				z3 = self.hits[i+1][j+1]
				z4 = self.hits[i][j+1]
				c1 = z1*zscale+16
				c2 = z2*zscale+16
				c3 = z3*zscale+16
				c4 = z4*zscale+16
				self.interpquad(i,j,z1*zscale2,c1,i+1,j,z2*zscale2,c2,
						i+1,j+1,z3*zscale2,c3,i,j+1,z4*zscale2,c4)


l = HitsPerDay("../Data/logs.9604")
l.title = "Hits per Day (April 1996)"
l.filename = "hits_day.gif"
l.show()

t = HitsByHour("../Data/logs.9604")
t.title = "Hits by hour (April 1996)"
t.filename = "hits_time.gif"
t.show()

p = HitsPerHour("../Data/logs.9604")
p.title = "Hits per hour (April 1996)"
p.filename = "hits_hour.gif"
p.rotu(50)
p.rotr(20)
p.right(5)
p.up(15)
p.zoom(120)
p.show()