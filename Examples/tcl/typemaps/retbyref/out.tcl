# Tcl script showing some output arguments

catch {load ./return.so return }
catch {load ./return.dll return }

set a [double_array 1]

# Power function with a status value

set status [mypow 2 3 r];          # Result is placed in r
puts "pow(2,3) = $r"
set status [mypow -1 3 s];         # Result is placed in s
puts "pow(-1,3) = $s"

# Some output functions

multout 7 13 x y
puts "multout 7 13 = $x $y"
multout1 7 13 x $a
puts "multout1 7 13 = $x"
set r [multout2 7 13 $a $a]
puts "multout2 7 13 = $r"

