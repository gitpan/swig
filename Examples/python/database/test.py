from db import *
import string

# Read in the passwd file and create a database

f = open("/etc/passwd","r")
l = f.readline()
while l:
	fields = string.split(string.strip(l),':')
	login = fields[0]
	uid = string.atoi(fields[2])
	gid = string.atoi(fields[3])
	name = fields[4]
	home = fields[5]
	add_user((login,uid,gid,name,home))
	l = f.readline()
f.close()

# Sort the users
sort_users()

# Find a few users

print "Looking for root"
print lookup_user("root")
print "Looking for beazley"
print lookup_user("beazley")

# print out all users
print "All users"
for i in range(0,num_users()):
	print get_user(i)

