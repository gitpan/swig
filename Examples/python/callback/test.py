# Test our C callback module

from callback import *

# -----------------------------------------------------
# Create a new widget and access a C callback function
# -----------------------------------------------------

# Create a new widget
w = new_widget()

# Attach a callback function written in C
widget_add_callback(w,FOO,"_0_void_p");

# Try using our callback function
widget_op(w,4.0)

# -----------------------------------------------------
# Create a new widget and attach a Python callback function
# -----------------------------------------------------

def callback(a):
	print "Python callback function. Received : ",a

v = new_widget()

# Attach callback function
pywidget_add_callback(v,callback)

# Try calling our new function
widget_op(v,4.0)

# -----------------------------------------------------
# Now hammer on things a bit more
# -----------------------------------------------------

def print_array(a,nitems):
	for i in range(0,nitems):
		print "a[",i,"] = ", double_get(a,i)
	
def poly(a):
	return 0.0025*a*a - 0.5*a + 4

t = new_widget()

pywidget_add_callback(t,poly)

# Create a C double array of 20 elements
a = double_array(20)

print "Using a Python function as a C callback"

# Call a C function for filling the array
fill_array(t,a,20)

# Print it out
print_array(a,20)

# Now attach an anonymous function

pywidget_add_callback(t,lambda x: 2*x)

print "Using a Python anonymous function as a C callback"
fill_array(t,a,20)
print_array(a,20)

# Now try to pass a class member in as a callback function

class Foo:
	def __init__(self, nitems, func):
		self.widget = new_widget()
		self.data = double_array(nitems)
		self.nitems = nitems
		self.func = func
	def __del__(self):
		double_destroy(self.data)
	def callback(self,value):
		return self.func(value)
	def fill(self):
		pywidget_add_callback(self.widget,self.callback)
		for i in range(0,self.nitems):
			fill_array(self.widget,self.data,self.nitems)
	def output(self):
		for i in range(0,self.nitems):
			print "data[",i,"] = ", double_get(self.data,i)				


f = Foo(50,poly)
f.fill()
f.output()

				
		


