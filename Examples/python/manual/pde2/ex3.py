# An example using our set/get functions

from pde import *

# Set up an initial condition

def initcond(h):
	h.set_temp(0.0)
	nx = h.grid.xpoints
	for i in range(0,nx):
		Grid2d_set(h.grid,i,0,1.0)

# Dump out to a file

def dump(h,filename):
	f = open(filename,"w")
	nx = h.grid.xpoints
	ny = h.grid.ypoints
	for i in range(0,nx):
		for j in range(0,ny):
			f.write(str(Grid2d_get(h.grid,i,j))+"\n")
	f.close()

# Set up a problem and run it

h = Heat2d(50,50)
initcond(h)
fileno = 1

for i in range(0,25):
	h.solve(100)
	dump(h,"Dat"+str(fileno))
	print "time = ", h.time
	fileno = fileno+1

del h


