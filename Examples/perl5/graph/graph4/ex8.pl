# Read a file with cities into a graph
# Uses shadow classes

use graph;
package graph;

%Cities;              # Hash table mapping cities to nodes
%Nodes;               # Mapping of Node indicies to cities
%Locations;           # Mapping of Node numbers to locations

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
    
read_cities("cities");
read_locations("locations");

$im = gdImageCreate(500,500);
$white = gdImageColorAllocate($im,255,255,255);
$black = gdImageColorAllocate($im,0,0,0);

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
	my $e = $node->{adj};
	while (defined($e)) {
   	      if (exists $Locations{$e->{node}->{v}}) {
		  my $loc2 = $Locations{$e->{node}->{v}};
		  plot_cities($im,$loc1,$loc2,$black);
	      }
	      $e = $e->{next};
	  }
    }
    @loc = each %Cities;
}

dump_gif($im,"test.gif");
print "Output written to 'test.gif'\n";

