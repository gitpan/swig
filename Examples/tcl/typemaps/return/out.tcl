# Tcl script showing some output arguments

catch {load ./return.so return }
catch {load ./return.dll return }

set a [double_array 1]

# Power function with a status value

set r [mypow 2 3 ""]
puts "pow(2,3) = $r"
set r [mypow -1 3 ""]
puts "pow(-1,3) = $r"

# Some output functions

set r [multout 7 13 "" ""]
puts "multout 7 13 = $r"
set r [multout1 7 13 "" $a]
puts "multout1 7 13 = $r"
set r [multout2 7 13 $a $a]
puts "multout2 7 13 = $r"
