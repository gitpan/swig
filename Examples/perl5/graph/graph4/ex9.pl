# Read a file with cities into a graph
# Uses shadow classes

use graph;
package graph;

%Cities;              # Hash table mapping cities to nodes
%Nodes;               # Mapping of Node indicies to cities
%Locations;           # Mapping of city names to locations

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
    close CITIES;
}


sub read_locations {
    my $filename = shift;
    open(LOCATIONS,$filename);
    while (<LOCATIONS>) {
	chop;
	my @a = split(/, +/);
	my $loc;
	# Check to see if this is a city I know about
	if (exists $Cities{$a[0]}) {
	    # Create a new location
	    $loc = new Location($a[0]);
	    my @coords = split(' ',$a[1]);
	    %$loc = (lat_degrees => $coords[0],
		     lat_minutes => $coords[1],
		     lat_seconds => $coords[2],
		     lat_direction => $coords[3],
		     long_degrees => $coords[4],
		     long_minutes => $coords[5],
		     long_seconds => $coords[6],
		     long_direction => $coords[7]);
	    my $v = $Cities{$a[0]}->{v};
	    $Locations{$v} = $loc;
	}
    }
    close LOCATIONS;
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
    my $im = shift;
    
    # Lookup nodes from names
    if ((!exists $Cities{$start}) || (!exists $Cities{$dest})) {
	return;
    }

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
	my $last = $node1;
	foreach $c (@path) {
	    $node2 = $Cities{$c};
	    if ((exists $Locations{$last->{v}}) && (exists $Locations{$node2->{v}})) {
		my $loc1 = $Locations{$last->{v}};
		my $loc2 = $Locations{$node2->{v}};
		plot_cities($im,$loc1,$loc2,$red);
	    }
	    $last = $node2;
	}
    } else {
	print "    You can't get there from here\n";
    }
}

read_cities("cities");
read_locations("locations");

$im = gdImageCreate(500,500);
$white = gdImageColorAllocate($im,255,255,255);
$black = gdImageColorAllocate($im,0,0,0);
$red = gdImageColorAllocate($im,255,0,0);

$xmin = -130;
$xmax = -90;
$ymin = 30;
$ymax = 50;

# Make a plot of the entire graph


@loc = each %Cities;
while (@loc) {
    my $city = $loc[0];
    my $node = $Cities{$city};
    if (exists $Locations{$node->{v}}) {
	my $loc1 = $Locations{$node->{v}};
	plot_cities($im,$loc1,$loc1,$black);
    }
    @loc = each %Cities;
}

find_route("Denver","Seattle",$im);
dump_gif($im,"test.gif");

print "Output written to 'test.gif'\n";
