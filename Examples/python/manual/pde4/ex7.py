# An example using our set/get functions

from pde import *

# Set up an initial condition

def initcond(h):
	h.set_temp(0.0)
	nx = h.grid.xpoints
	for i in range(0,nx):
		h.grid[i][0] = 1.0

# Set up a problem and run it

h = Heat2d(50,50)
initcond(h)
fileno = 1

for i in range(0,25):
	h.solve(100)
	h.dump("Dat"+str(fileno))
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
