# Some simple Tcl functions for making 2D plots 

proc plotfunc {p2 func npoints color symbol} {

    # Substitute the variable 'x' in func to be a Tcl variable
    regsub -all x $func \$x myfunc
    puts $myfunc
    set xmin [$p2 cget -xmin]
    set xmax [$p2 cget -xmax]
    set dx [expr {1.0*($xmax-$xmin)/$npoints}]
    set x $xmin
    puts $dx
    set y [eval "expr {$myfunc}"]
    set lastx $x
    set lasty $y
    if {$symbol != "NULL"} {
	$p2 drawpixmap $symbol $x $y $color 0
    }
    for {set i 0} { $i < $npoints } {incr i 1} {
        set x [expr {$x + $dx}]
	set y [eval "expr {$myfunc}"]
	$p2 line $lastx $lasty $x $y $color
	if {$symbol != "NULL"} {
	    $p2 drawpixmap $symbol $x $y $color 0
	}
	set lastx $x
	set lasty $y
    }
}

proc newplot {p2 xtick ytick title xaxis_label yaxis_label} {
    set frame [$p2 cget -frame]
    $frame clear 0
    set width [$frame cget -width]
    set height [$frame cget -height]
    
    $frame noclip

    # Draw a bounding box around the image
    
    $frame box 50 50 [expr {$width-15}] [expr {$height-15}] 1

    # Draw graph title

    set l [string length $title]
    set sx [expr {(($width-50)/2) - 4*$l + 45}]
    $frame drawstring $sx [expr {$height-12}] 1 0 $title 1
    
    # Draw axis labels

    set l [string length $xaxis_label]
    set sx [expr {(($width-50)/2) - 4*$l + 45}]
    $frame drawstring $sx 38 1 0 $xaxis_label 1

    set l [string length $yaxis_label]
    set sy [expr {(($height-50)/2) - 4*$l + 45}]
    $frame drawstring 47 $sy 1 0 $yaxis_label 2

    # Draw plotting range
    
    set xmin [$p2 cget -xmin]
    set xmax [$p2 cget -xmax]
    
    $frame drawstring 50 38 1 0 $xmin 1
    set l [string length $xmax]
    set sx [expr {($width-15)-8*$l}]
    $frame drawstring $sx 38 1 0 $xmax 1

    set ymin [$p2 cget -ymin]
    set ymax [$p2 cget -ymax]
    $frame drawstring 47 50 1 0 $ymin 2
    set l [string length $ymax]
    set sy [expr {($height-15)-8*$l}]
    $frame drawstring 47 $sy 1 0 $ymax 2
    
    # Set clipping region for 2D plot

    $p2 setview 51 51 [expr {$width-15}] [expr {$height-15}]

    # Draw the axis
    $p2 xaxis 0 0 $xtick 3 1
    $p2 yaxis 0 0 $ytick 3 1
    $p2 start
}

# Take some screen coordinates and set global min and max values 

proc set_zoom {p2 mxmin mymin mxmax mymax x1 y1 x2 y2} {
    global xmin ymin xmax ymax

    set frame [$p2 cget -frame]
    set width [$frame cget -width]
    set height [$frame cget -height]

    if {$x1 < 50} {set x1 50}
    if {$x1 > ($width-15)} {set x1 [expr {$width-15}]}
    if {$x2 < 50} {set x2 50}
    if {$x2 > ($width-15)} {set x2 [expr {$width-15}]}
    if {$x1 < $x2} {set ixmin $x1; set ixmax $x2} {set ixmin $x2; set ixmax $x1}

    if {$y1 < 15} {set y1 15}
    if {$y1 > ($height-50)} {set y1 [expr {$height-50}]}
    if {$y2 < 15} {set y2 15}
    if {$y2 > ($height-50)} {set y2 [expr {$height-50}]}
    if {$y1 < $y2} {set iymin $y1; set iymax $y2} {set iymin $y2; set iymax $y1}

    # Now determine new min and max values based on screen location

    set xmin [expr {$mxmin + ($mxmax-$mxmin)*($ixmin-50)/($width-65)}]
    set xmax [expr {$mxmin + ($mxmax-$mxmin)*($ixmax-50)/($width-65)}]
    set ymin [expr {$mymin + ($mymax-$mymin)*(($height-65)-($iymax-15))/($height-65)}]
    set ymax [expr {$mymin + ($mymax-$mymin)*(($height-65)-($iymin-15))/($height-65)}]

    catch {make_plot}
}

