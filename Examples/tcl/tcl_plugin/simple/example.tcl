#!/usr/local/bin/tclsh7.5
#
# Tcl script for testing simple example

load ./example.so example

puts [get_time]
set tcl_precision 17
puts "My Variable = $My_variable"
for {set i 0} {$i < 14} {incr i 1} {
    set n [fact $i];
    puts "$i factorial is $n"
}

for {set i 1} {$i < 250} {incr i 1} {
    for {set j 1} {$j < 250} {incr j 1} {
	set n [mod $i $j]
	set My_variable [expr {$My_variable + $n}]
    }
}

puts "My_variable = $My_variable"

