# Read a file with cities into a graph

use graph;
package graph;

%Cities = ();              # Hash table mapping cities to nodes
%Nodes = ();               # Mapping of Node indicies to cities

sub read_cities {
    my $filename = shift;
    open(CITIES,$filename);
    while (<CITIES>) {
	chop;
	my @a = split(/, +/);
	my $node1;
	my $node2;
	# Check to see if a given city is already a node
	if (!exists $Cities{$a[0]}) {
	    $node1 = new_Node();
	    $Cities{$a[0]} = $node1;
	    my $node_num = Node_v_get($node1);
	    $Nodes{$node_num} = $a[0];
	} else {
	    $node1 = $Cities{$a[0]};
	}
	if (!exists $Cities{$a[1]}) {
	    $node2 = new_Node();
	    $Cities{$a[1]} = $node2;
	    my $node_num = Node_v_get($node2);
	    $Nodes{$node_num} = $a[1];
	} else {
	    $node2 = $Cities{$a[1]};
	}
	# Add edges
	Node_addedge($node1,$node2,$a[2]);
	Node_addedge($node2,$node1,$a[2]);
    }
}

sub is_route {
    my $start = shift;
    my $dest = shift;

    # Lookup nodes from names

    my $node1 = $Cities{$start};
    my $node2 = $Cities{$dest};
    print "$start --> $dest :";
    my $found = Node_search($node1,Node_v_get($node2));
    if ($found) {
	print "Looks good.\n";
    } else {
	print "You can't get there from here\n";
    }
}
    
read_cities("cities");

is_route("Denver","Portland");
is_route("Albuquerque","Boise");



