from list import *
import string

# Create a list

Users = new_List()

# Read in the passwd file and create a database

f = open("/etc/passwd","r")
l = f.readline()
while l:
	fields = string.split(string.strip(l),':')
	uid = string.atoi(fields[2])
	name = fields[4]
	home = fields[5]
	
	List_append(Users, new_User(name,uid,home));
	l = f.readline()
f.close()


# Now print all of the users out

for i in range(0,List_len(Users)):
	a = ptrcast(List_get(Users,i),"User *")
	print User_str(a)


	