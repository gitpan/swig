use darray;
$a = new DoubleArray(50);
for ($i = 0; $i < 50; $i++) {
    $a->setitem($i,0.25*$i);
}

# Print out the array

for ($i = 0; $i < 50; $i++) {
    print $a->getitem($i),"\n";
}

# Now generate an exception

print "This should gracefully generate an exception...\n";

$a->setitem(1000000,3.1459);

