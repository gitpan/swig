#!./perl5
# This file builds binary search trees in Perl and C
# It can be used to compare the performance of
# C, Perl, associative arrays etc...
#
use Tree;
package Tree;

$tree_head = new_node("", "head");
$tree_z = new_node("__end__", "");
set_right($tree_head,$tree_z);
set_left($tree_z,$tree_z);
set_right($tree_z,$tree_z);

# Insert an item into the tree

sub insert_tree_perl {
    local($key,$value) = @_;
    $p= $tree_head;
    $x= get_right($tree_head);
    while ($$x != $$tree_z) {
	$p=$x;
	if ($key lt get_key($x)) {
	    $x = get_left($x);
	} else {
	    $x = get_right($x);
	}
    }
    $x = new_node($key,$value);
    if ($key lt get_key($p)) {
	set_left($p,$x);
    } else {
	set_right($p,$x);
    }
    set_left($x, $tree_z);
    set_right($x, $tree_z);
    $tree_size = $tree_size+1;
}

sub search_tree_perl {
    local($key) = @_;
    $found = $key;
    $x = get_right($tree_head);
    while ($$x != $$tree_z) {
	if (get_key($x) eq $key) {
	    $found = get_value($x);
	    return;
	} else {
	    if ($key lt get_key($x)) {
		   $x = get_left($x);
	       }{
		   $x = get_right($x);
	       }
	}
    }
    $key;
}

# Build tree structure in C (for the most part)

sub build_data {
    local($nitems) = @_;
    for ($i = 0; $i < $nitems; $i++) {
	$r = rand();
	insert_tree("_$r", "_$r", $tree_head, $tree_z);
#	set data(_$r) _$r
    }
}

# Build tree structure in Perl

sub build_data_perl {
    local($nitems) = @_;
    for ($i = 0; $i < $nitems; $i++) {
	$r = rand();
	insert_tree_perl("_$r","_$r"); 
#	set data(_$r) _$r
    }
}

# Now do a bunch of lookups, 

print "Building a binary search tree...\n";
print "Inserting 10000 items using Perl...\n";

timer_clear(0);
timer_start(0);
build_data_perl(10000);
timer_stop(0);
print timer_elapsed(0), " seconds.\n";

print "Inserting 10000 items using Perl and C...\n";
timer_clear(1);
timer_start(1);
build_data(10000);
timer_stop(1);
print timer_elapsed(1), " seconds.\n";
print "Speedup = ", timer_elapsed(0)/timer_elapsed(1), "\n";

$nlookup = 20000;
print "Doing $nlookup lookups on trees (in Perl)\n";

timer_clear(0);
timer_start(0);
for ($i = 0; $i < $nlookup; $i++) {
    $r=rand();
    $g=search_tree_perl("_$r");
}
timer_stop(0);
print timer_elapsed(0), " seconds.\n";


print "Doing $nlookup lookups on trees (in Perl and C)\n";

timer_clear(1);
timer_start(1);
for ($i = 0; $i < $nlookup; $i++) {
    $r = rand();
    $g = search_tree("_$r",$tree_head,$tree_z);
}

timer_stop(1);
print timer_elapsed(1), " seconds.\n";
print "Speedup = ", timer_elapsed(0)/timer_elapsed(1), "\n";





