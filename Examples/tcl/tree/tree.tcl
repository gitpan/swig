#!tree
# This file builds binary search trees in Tcl and C
# It can be used to compare the performance of
# C, Tcl, associative arrays etc...
#

catch {load ./tree.so tree}
catch {load ./tree.dll tree}

set tree_head [new_node "" head]
set tree_z    [new_node __end__ ""]
set_right $tree_head $tree_z
set_left $tree_z $tree_z
set_right $tree_z $tree_z

# Insert an item into the tree

proc insert_tree_tcl {key value} {
    global tree_head tree_z tree_size
    set p $tree_head
    set x [get_right $tree_head]
    while {$x != $tree_z} {
	set p $x
	if {$key < [get_key $x]} {set x [get_left $x]} {set x [get_right $x]}
    }
    set x [new_node $key $value]
    if {$key < [get_key $p]} {set_left $p $x} {set_right $p $x}
    set_left $x $tree_z
    set_right $x $tree_z
    set tree_size [expr $tree_size + 1]
}

proc search_tree_tcl {key} {
    global tree_head tree_z
    set found key
    set x [get_right $tree_head]
    while {$x != $tree_z} {
	if {[get_key $x] == $key} {set found [get_value $x]; return $found} 
	   {
	       if {$key < [get_key $x]} {
		   set x [get_left $x]
	       }{
		   set x [get_right $x]
	       }
	   }
    }
    return $key
}

set nlist {}

# Build tree structure in C (for the most part)
proc build_data {nitems} {
    global tree_head tree_z nlist data
    for {set i 0} {$i < $nitems} {incr i 1} {
	set r [rand]
	insert_tree _$r _$r $tree_head $tree_z
	set data(_$r) _$r
	lappend nlist _$r
    }
}

# Build tree structure in Tcl

proc build_data_tcl {nitems} {
    global tree_head tree_z nlist data
    for {set i 0} {$i < $nitems} {incr i 1} {
	set r [rand]
	insert_tree_tcl _$r _$r 
	set data(_$r) _$r
	lappend nlist _$r
    }
}

# Now do a bunch of lookups, using both associative
# arrays and trees.

puts "Building a binary search tree..."
puts "Inserting 10000 items using Tcl..."
set t1 [time {
    build_data_tcl 10000
} 1]

puts $t1
puts "Inserting 10000 items using Tcl and C..."
set t2 [time {
    build_data 10000
} 1]
puts $t2

set nlookup 20000
puts "Doing $nlookup lookups on Tcl associative arrays"

set t [time {
for {set i 0} {$i < $nlookup} {incr i 1} {
    set r [rand]
    catch { set g $data(_$r)}
}
} 1]

puts $t

puts "Doing $nlookup lookups on trees (in Tcl)"
set t1 [time {
for {set i 0} {$i < $nlookup} {incr i 1} {
    set r [rand]
    catch { set g [search_tree_tcl _$r]}
}
} 1]

puts $t1

puts "Doing $nlookup lookups on trees (in Tcl and C)"
set t2 [time {
for {set i 0} {$i < $nlookup} {incr i 1} {
    set r [rand]
    catch { set g [search_tree _$r $tree_head $tree_z]}
}
} 1]

puts $t2



