use amember;

package amember;

# Create a person

$p = new_Person();

# Set they're name

$p->{name} = "Dave";
$p->{address} = "Salt Lake City";

# Now, see what we got

print "Name : ", $p->{name}, "\n";
print "Address : ", $p->{address},"\n";

# Now try to set a longer address

$p->{address} = "Department of Computer Science, University of Utah, Salt Lake City, UT 84112";

print "Name : ", $p->{name}, "\n";
print "Address : ", $p->{address},"\n";

# The address field should now be chopped off at 31 characters.


