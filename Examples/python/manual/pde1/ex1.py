# A fairly uninteresting example

from pde import *

h = new_Heat2d(50,50)

Heat2d_set_temp(h,1.0)
print "Dt = ", Heat2d_dt_get(h)

# Solve something

for i in range(0,25):	
	Heat2d_solve(h,100)
	print "time = ", Heat2d_time_get(h)


