#
# Perl5 shadow class example
# This file shows some of the ways in which shadow classes can be used.
# 
# This file probably isn't going to make much sense without looking
# the file shadow.i
#

# Load our module

use shadow;               

# A Perl function to print out a vector.

sub printv {
    my $v = shift;
    print "[",$v->{x},",",$v->{y},",",$v->{z},"]\n";
}

# Create a new Vector using a normal C function.  Note that stand-alone
# C functions are created in the top-level package

$v = shadow::new_Vector(2,5,-7);

# Print it out

printv($v);

# Change a few values in the vector

$v->{y} = -10;
printv($v);

# Change all of the values in the vector

%$v = ( x=>-4, y=>7, z=>13.5 );
printv($v);

# Attach the printv function we created as a new Vector method

*Vector::print = *printv;     

# Print out a vector using our new method 

$v->print();

# Now let's create a particle

$p = new Particle();

# None of the values are initialized so let's create some

%{$p->{r}} = ( x => 1.5, y => 0.0, z => 3.25);
%{$p->{v}} = ( x => 0, y=> 0, z=>0);
%{$p->{f}} = %{$p->{v}};
$p->{type} = 1;

# Print out a few values.  Note how we can use our new print function on the
# vector members.

print "Particle\n";
print "    r = ";
$p->{r}->print();
print "    v = ";
$p->{v}->print();
print "    type = ", $p->{type},"\n";

# Now, make another particle

$p2 = Particle->new();      # An alternative way to construct

%$p2 = %$p;                 # Copy everything in p to p2

$p2->{r}->{x} = 2.5;

print "Particle2\n";
print "    r = ";
$p2->{r}->print();
print "    v = ";
$p2->{v}->print();
print "    type = ", $p2->{type},"\n";

# Now make a bond from our two particles.  Note that the new Bond function was
# declared separately

$b = shadow::new_Bond($p,$p2);

# A function for finding distance between two particles in a bond

sub bond_dist {
    my $b = shift;
    my $p1 = $b->{p1};
    my $p2 = $b->{p2};
    my $dx = $p1->{r}->{x} - $p2->{r}->{x};
    my $dy = $p1->{r}->{y} - $p2->{r}->{y};    
    my $dz = $p1->{r}->{z} - $p2->{r}->{z};
    my $r = sqrt($dx*$dx + $dy*$dy +$dz*$dz);
    return $r;
}

print "Distance = ", bond_dist($b), "\n";


# Now start twiddling with C++ classes

$l = new List;

# Insert some values into it

$l->insert("Dave");
$l->insert("Mike");
$l->insert("Kathy");
$l->insert("Bob");

# Search the list

if ($l->search("Bill")) {
    print "Bill is in the list.\n";
} else {
    print "Bill is not in the list.\n";
}

# print out the list

$l->print_list();

# Destroy the list

$l->DESTROY();

# Create a list using the alternate constructor

$l2 = List->new_List_max(100);
$l2->insert("Mary");
$l2->insert("John");
shadow::print_list($l2);

# Now try out some inheritance stuff

$c = new Circle(3);
$s = new Square(10);

print "Circle area = ", $c->area(),"\n";
print "Square area = ", $s->area(),"\n";

# Call a function in the base class

$c->set_center(2,7);
$c->print_center();

# Now access a C++ global variable we wrapped

print "a_circle : area = ",$shadow::a_circle->area(),"\n";
$shadow::part->{r}->{x} = 3.5;
print $shadow::part->{r}->{x},"\n";

print $shadow::a_circle,"\n";

