#
# Tcl script for testing simple example

# Try to load as a dynamic module.  If not, we'll just assume
# that it was statically linked in.

catch { load ./example.so example}
catch { load ./example.dll example}

set tcl_precision 17
puts "Calculating some factorials"
for {set i 0} {$i < 14} {incr i 1} {
    set n [fact $i];
    puts "$i factorial is $n"
}

puts "Now generate an error by executing fact -1"
fact -1
