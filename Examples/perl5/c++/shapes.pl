use shapes;

# Create a circle

$c = shapes::new_Circle(4);

# Create a square

$s = shapes::new_Square(9.5);

# Now print out area and perimeter using base class

print "Circle area      = ", &shapes::Shape_area($c), "\n";
print "Circle perimeter = ", &shapes::Shape_perimeter($c), "\n\n";
print "Square area      = ", &shapes::Shape_area($s), "\n";
print "Square perimeter = ", &shapes::Shape_perimeter($s), "\n\n";

# Try a function in the base class

&shapes::Shape_print_center($c);
&shapes::Circle_print_center($c);







