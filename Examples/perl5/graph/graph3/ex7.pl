# Read a file with cities into a graph
# Uses shadow classes

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
	    $node1 = new Node;
	    $Cities{$a[0]} = $node1;
	    $Nodes{$node1->{v}} = $a[0];
	} else {
	    $node1 = $Cities{$a[0]};
	}
	if (!exists $Cities{$a[1]}) {
	    $node2 = new Node;
	    $Cities{$a[1]} = $node2;
	    $Nodes{$node2->{v}} = $a[1];
	} else {
	    $node2 = $Cities{$a[1]};
	}
	# Add edges
	$node1->addedge($node2,$a[2]);
	$node2->addedge($node1,$a[2]);
    }
}

%visit;

sub breadth_search {
    my $node1 = shift;
    my $node2 = shift;
    my @queue;
    %visit = ();

    my $dest = $node2->{v};
    # Put starting node into queue

    push @queue, $node1;
    $visit{$node1->{v}} = $node1->{v};

    while (@queue) {
	my $n = shift @queue;
	if ($n->{v} == $node2->{v}) {
	    return 1;
	}

	# Put children onto the queue
	my $e = $n->{adj};
	while (defined($e)) {
	    if (!exists $visit{$e->{node}->{v}}) {
		push @queue, $e->{node};
		$visit{$e->{node}->{v}} = $n->{v};
	    }
	    $e = $e->{next};
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
	my $v = $node2->{v};
	delete $visit{$node1->{v}};
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
find_route("Los Angeles","San Francisco");


