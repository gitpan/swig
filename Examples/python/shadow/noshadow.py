# Use of list class without shadow classes

from listc import *          # Note : low-level module is 'listc' when
                             # shadow classes have been generated

l = new_List()
List_insert(l,"Guido")
List_insert(l,"John")
List_insert(l,"Larry")
if (List_search(l,"Guido") == 0):
	print "Guido not in the list"

a = List_get(l,1)
print a

List_output(l)

