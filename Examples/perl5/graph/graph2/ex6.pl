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

%visit = ();

sub breadth_search {
    my $node1 = shift;
    my $node2 = shift;
    my @queue;
    %visit = ();

    # Put starting node into queue

    push @queue, $node1;
    $visit{Node_v_get($node1)} = Node_v_get($node1);

    while (@queue) {
	my $n = shift @queue;
	my $nv = Node_v_get($n);
	if ($$n == $$node2) {
	    return 1;
	}

	# Put children onto the queue
	my $e = Node_adj_get($n);
	while (defined($e)) {
	    my $m = Edge_node_get($e);
	    my $v = Node_v_get($m);
	    if (!exists $visit{$v}) {
		push @queue, $m;
		$visit{$v} = $nv;
	    }
	    $e = Edge_next_get($e);
	}
    }
    return 0;
}


sub find_route {
    my $start = shift;
    my $dest = shift;

    # Lookup nodes from names
    if ((!exists $Cities{$start}) || (!exists $Cities{$dest})) {
	return;
    }

    print "$start --> $dest :\n";

    my $node1 = $Cities{$start};
    my $node2 = $Cities{$dest};

    my $found = breadth_search($node1,$node2);
    my @path;
    if ($found) {
	my $v = Node_v_get($node2);
	delete $visit{Node_v_get($node1)};
	while (exists($visit{$v})) {
	    unshift @path,$Nodes{$v};
	    $v = $visit{$v};
	}
	unshift @path,$start;
	foreach $c (@path) {
	    print "    $c\n";
	}
    } else {
	print "    You can't get there from here\n";
    }
}
    
read_cities("cities");

find_route("Salt Lake City","Denver");
find_route("Albuquerque","Boise");
find_route("Tuscon","Santa Fe");


