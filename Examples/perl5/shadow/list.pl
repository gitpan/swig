#
# Perl5 shadow class example
# This file shows some of the ways in which shadow classes can be used.
# 
# This file probably isn't going to make much sense without looking
# the file shadow.i
#

# Load our module

use shadow;               

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






    

