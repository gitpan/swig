# This python file shows how we can access some array members

from arraymember import *

# Create a new array

a = Arrays()

# Change the name

a.name = 'Monty'

# Print it out

print a.name

# Try changing the name to something too big

a.name = 'A really long name that is too big to fit in our struct'

# Name should be unchanged

print a.name

# Now set a whole bunch of values

for i in range(0,100):
	a.numbers_set(i,i)

# Print them out

for i in range(0,100):
	print a.numbers_get(i)

