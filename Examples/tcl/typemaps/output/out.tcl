# Tcl script showing some output arguments

catch {load ./output.so output }
catch {load ./output.dll output }

# Try a variety of functions

set a [add 4 7]
puts "4 + 7 = $a"
set b [sub 4 7]
puts "4 - 7 = $b"
set c [mul 4 7]
puts "4 * 7 = $c"
set d [fdiv 4 7]
puts "4 / 7 = $d"
set e [neg 4]
puts "neg(4) = $e"

