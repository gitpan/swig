use nested;
package nested;

# Create a new nested object

$n = new_value(0);

# Print out some values

$n->{u}->{intval} = 4;
print "n.dataType = ",$n->{dataType}, "\n";
print "n.u.intval = ",$n->{u}->{intval},"\n";
print "n.u.doubleval = ",$n->{u}->{doubleval},"\n";
print "n.u.ptrvalue = ",$n->{u}->{ptrvalue},"\n";
print "n.u.longval = ",$n->{u}->{longval},"\n";

# Now go one more level

$n->{u}->{v}->{v} = $n->{u}->{ptrvalue};   # Set a value

print "n.u.v.i = ",$n->{u}->{v}->{i},"\n";
print "n.u.v.f = ",$n->{u}->{v}->{f},"\n";
print "n.u.v.v = ",$n->{u}->{v}->{v},"\n";

# Use our set method on name
$n->{u}->{v}->{name} =  "PERL";
print "n.u.v.name = ",$n->{u}->{v}->{name},"\n";

