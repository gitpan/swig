# graph : simple interactive graph editor
#
# This file shows how one might access C data structures
# from Tcl when using SWIG.
#
# This example is roughly adopted from the graph example
# on pg.  213-215 of "Tcl and the Tk ToolKit" by Ousterhout
#

# Uncomment for Tcl7.5

catch { load ./graph.so Graph }
catch { load graph.dll Graph }

init_graph                        ;# Initialize the graph program

canvas .c -width 600 -height 600
pack .c
set firstNode ""
set nodeList {}
set ltype 1
set short_node 0

# proc mkNode
# Makes a new node.    This creates both a Tk widget and a C
# data structure by calling out to the C function new_node
#
# To keep track of our C data structure, we keep an array
# nodeP() containing pointers.
#
 
proc mkNode {x y} {
    global nodeX nodeY nodeP nodeMap nodeList edgeFirst edgeSecond
    set new [.c create oval [expr $x-15] [expr $y-15] \
		 [expr $x+15] [expr $y+15] -outline black \
		 -fill white -tags node]
    set newnode [new_node]     ;# Make a new C Node
    set nnum [GetNum $newnode] ;# Get our node's assigned number
    set id [.c create text [expr $x-4] [expr $y+10] -text $nnum -anchor sw -tags nodeid]

    set nodeX($new) $x
    set nodeY($new) $y
    set nodeP($new) $newnode   ;# Make array of node pointers
    set nodeMap($newnode) $new ;# Make a mapping from node pointers to Tk
#                               # widgets for later use.
    set edgeFirst($new) {}
    set edgeSecond($new) {}
    lappend nodeList $new     ; # we also just keep a list of the nodes
#                               # created for making things easier
}

# proc mkArrow 
# This makes an arrow between two nodes.  Have to play
# some trig tricks to get the arrow to go outside of the
# node "oval"
#

proc mkArrow {first second} {
    global nodeX nodeY 
    set x1 $nodeX($first)
    set x2 $nodeX($second)
    set y1 $nodeY($first)
    set y2 $nodeY($second)
    set dx [expr {$x2 - $x1}]
    set dy [expr {$y2 - $y1}]
    set theta [expr {atan2($dy,$dx)}]
    if {$dx < 0} {
	set x2 [expr {$x2 - 15*cos($theta)}]
	set y2 [expr {$y2 - 15*sin($theta)}]
	set x1 [expr {$x1 + 15*cos($theta)}]
	set y1 [expr {$y1 + 15*sin($theta)}]
    } {
	set theta [expr {3.14159 + $theta}]
	set x2 [expr {$x2 +15*cos($theta)}]
	set y2 [expr {$y2 +15*sin($theta)}]
	set x1 [expr {$x1 -15*cos($theta)}]
	set y1 [expr {$y1 -15*sin($theta)}]
    }
    set edge [.c create line $x1 $y1 $x2 $y2 -arrow last -arrowshape {16 20 6} -tags arc]
    .c lower $edge
    return $edge
}

# proc mkEdge
# Makes a directed edge between two nodes.   Aside from making
# an arrow in Tk, we must look up the Node pointer for each
# object and make a call to AddLink() to make a logical link
# between nodes.  By setting the new variable to 0, this function
# will only make the Tk arrow (and not call the C function)
#
 
proc mkEdge {first second new} {
    global nodeP edgeFirst edgeSecond

    set edge [mkArrow $first $second]      ;# Make an arrow
    lappend edgeFirst($first) $edge
    lappend edgeSecond($second) $edge
    if {$new == 1} {
	AddLink $nodeP($first) $nodeP($second) ;# Make a link in our C code
    }
} 

# This function destroys all existing egdes on the canvas, and recreates
# them from the internal C representation of the graph.  This is needed 
# whenever the C code might have added/delete a whole bunch of edges.

proc mkEdges {} {
    global nodeX nodeY nodeP nodeMap nodeList edgeFirst edgeSecond
    unset edgeFirst 
    unset edgeSecond 
    .c delete arc
    foreach node $nodeList {
	set edgeFirst($node) {}
	set edgeSecond($node) {}
    }
    foreach node $nodeList {        ;# Go through all of the nodes
	set v $nodeP($node)         ;# Get the node pointer for this node
	set v1 [GetAdj $v]          ;# Get it's adjacency list
	while {$v1 != "NULL"} {          
	    set v2 [GetNode $v1]    ;# Get node pointer
	    set w $nodeMap($v2)     ;# Get widget
	    mkEdge $node $w 0       ;# Make an edge between nodes
	    set v1 [GetNext $v1]    ;# Get next node
	}
    }
}

# Clears out everything

proc clear {} {
    global nodeX nodeY nodeP nodeMap nodeList edgeFirst edgeSecond
    unset nodeX
    unset nodeY
    unset nodeP
    unset nodeMap
    unset nodeList
    unset edgeFirst
    unset edgeSecond
    init_graph
    .c delete node
    .c delete nodeid
    .c delete arc
}

# Button 1 makes a new node

bind .c <Button-1> {mkNode %x %y}

# Flip nodes black when mouse is over them

.c bind node <Any-Enter> {
    if {($firstNode != "")} {
	.c itemconfigure current -fill red
    } else {
	.c itemconfigure current -fill black
    }
}

# Flip them back to white when leaving

.c bind node <Any-Leave> {
    .c itemconfigure current -fill white
    .c delete newarc
}

# Button 2 adds a edge between nodes
# First button press selects the starting node
# Second button press selects the ending node

.c bind node <Button-2> { 
    if {($firstNode == "")} {
	set firstNode [.c find closest %x %y]
    } else {
	set curNode [.c find closest %x %y]
	if {($firstNode != "") && ($curNode != "") && ($firstNode != $curNode)} {
	mkEdge $firstNode $curNode 1
	}
	set firstNode ""
    }
}

# Button - 3 initiates some sort of search.  For example, it will
# show all of the connected components or perhaps the shortest path

.c bind node <ButtonPress-3> {
    set cnode [.c find closest %x %y]
    switch $ltype {
	1 {
	    Connected $nodeP($cnode)
	    foreach node $nodeList {
		set v [GetVisit $nodeP($node)]
		if {$v == 1} {
		    .c itemconfigure $node -fill red
		}
	    }
	}
	2 { 
	    set n1 ""
	    foreach node $nodeList {
		set v $nodeP($node)
		set n [GetNum $v]
		if {$n == $short_node} {
		    set n1 $v
 		}
	    }
	    if {$n1 != ""} {
		set n2 $nodeP($cnode)
		if {($n1 != "NULL") && ($n2 != "NULL")} {
		    set slist [FindShort $n2 $n1]
		}
# Now walk down returned list and highlight the shortest path
		set l $slist
		while {$l != "NULL"} {
		    set v [GetNode $l]
		    set w $nodeMap($v)
		    .c itemconfigure $w -fill red
		    set l [GetNext $l]
		    if {$l != "NULL"} {
			set v1 [GetNode $l]
			set w1 $nodeMap($v1)
			foreach edge $edgeFirst($w) {
			    set s [lsearch $edgeSecond($w1) $edge]
			    if {$s >= 0} {
				.c itemconfigure $edge -fill red
				.c raise $edge
			    }
			}
		    }
		}
		if {$slist != "NULL"} {
		    FreeAdjList $slist    ;# Clean up after ourselves
		}
	    }
	}
    }
}

# When button 3 is released, flip everything back to white

.c bind node <ButtonRelease-3> {
    foreach node $nodeList {
	.c itemconfigure $node -fill white
	foreach edge $edgeSecond($node) {
	    .c itemconfigure $edge -fill black
	}
	foreach edge $edgeFirst($node) {
	    .c lower $edge
	    .c itemconfigure $edge -fill black
	}
    }
}

# make some buttons and directions

button .add -text "More Edges" -command { Closure_Step; mkEdges }
button .quit -text "Quit" -command {exit 0}
button .clear -text "Clear" -command {clear}
radiobutton .connect -text "Connectivity" -variable ltype -value 1 -anchor w
radiobutton .short -text "Shortest path" -variable ltype -value 2 -anchor w
label .to -text "to node : "
entry .entry -width 5 -relief sunken -bd 2 -textvariable short_node
pack .add .clear .quit .connect .short .to .entry -side left 

proc instr {w} {
    toplevel $w -class Dialog
    wm title $w "Instructions"
    wm iconname $w Dialog
    frame $w.top -relief raised -bd 1
    pack $w.top -side top -fill both
    message $w.top.msg -width 4i -text "\
Instructions :\n\n\
Left button makes a node\n\
Middle button makes an edge\n\
Right button shows connectivity/shortest path" 
    pack $w.top.msg -side right -expand 1 -fill both
    focus $w

}

focus .c
instr .d
