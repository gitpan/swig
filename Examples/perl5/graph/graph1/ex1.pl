# Perl code to use our graph code

use graph;
package graph;

$n0 = new_Node();
$n1 = new_Node();
$n2 = new_Node();

Node_addedge($n0,$n1,0);        #  0 -> 1
Node_addedge($n0,$n2,0);        #  0 -> 2
Node_addedge($n1,$n2,0);        #  1 -> 2
Node_addedge($n2,$n0,0);        #  2 -> 0

# A procedure to print out a node and its adjacency list

sub print_node {
    my $node = shift;
    print "Node : ", Node_v_get($node), ", Adj : ";
    my $adj = Node_adj_get($node);
    while (defined($adj)) {
	my $anode = Edge_node_get($adj);
	my $v = Node_v_get($anode);
	print "$v ";
	$adj = Edge_next_get($adj);
    }
    print "\n";
}

# Print out node information

print_node($n0);
print_node($n1);
print_node($n2);




