# Read a file with cities into a graph

use graph;
package graph;

%Cities;              # Hash table mapping cities to nodes
%Nodes;               # Mapping of Node indicies to cities

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

sub print_near {
    my $city = shift;
    if (exists $Cities{$city}) {
	my $node = $Cities{$city};
	print "Cities near $city : ";
	my $adj = Node_adj_get($node);
	while (defined($adj)) {
	    my $anode = Edge_node_get($adj);
	    my $v = Node_v_get($anode);
	    print $Nodes{$v},", ";
	    $adj = Edge_next_get($adj);
	}
    }
    print "\n";
}

read_cities("cities");

print_near("Denver");
print_near("Las Vegas");


