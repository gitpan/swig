# Use of list class with shadow classes

from list import *     

l = List()
l.insert("Guido")
l.insert("John")
l.insert("Larry")
if l.search("Guido") == 0:
	print "Guido not in the list"

a = l.get(1)
print a

l.output()
del l

