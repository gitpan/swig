#!my_wish
# This file is a simple test that combines BLT and Tix together

# Generate some data points

set pi 3.141592654
for {set i -360} {$i <= 360} {incr i 5} {
    lappend x $i
    set theta [expr $i*($pi/180.0)]
    lappend sin [expr sin($theta)]
    lappend cos [expr cos($theta)]
}

proc show_sin { a } {
    global x sin
    if {$a} {
	.g1 element create elem1 -label sin(x) -fill red -color red4 \
		-xdata $x -ydata $sin -scalesymbols yes
    } { .g1 element delete elem1 }
}

proc show_cos { a } {
    global x cos
    if {$a} {
	.g1 element create elem2 -label cos(x) -fill green -color green4 \
	    -xdata $x -ydata $cos -scalesymbols yes
    } { .g1 element delete elem2 }
}

# Create a tix selection widget

tixSelect .func -allowzero true -radio false -label "Function :" -command setplot
.func add cos -text cos
.func add sin -text sin

proc setplot {value y} {
    switch $value {
	cos { show_cos $y }
	sin { show_sin $y }
    }
}

pack .func

graph .g1 -title "A Simple Graph" 
pack .g1


