#
# Tcl script for testing [incr Tcl] builds

puts [example::get_time]
set tcl_precision 17
puts "My Variable = ${@scope ::example My_variable}"
for {set i 0} {$i < 14} {incr i 1} {
    set n [example::fact $i];
    puts "$i factorial is $n"
}

namespace example {
for {set i 1} {$i < 250} {incr i 1} {
    for {set j 1} {$j < 250} {incr j 1} {
	set n [example::mod $i $j]
	set My_variable [expr {$My_variable + $n}]
    }
}
}

puts "My_variable = ${@scope ::example My_variable}"

