# Check out our multiple inheritance script

catch { load ./inherit.so inherit }
catch {load inherit.dll inherit}

set d [new_D]

# Get data members
set x [A_x_get $d]
set y [B_y_get $d]
set z [D_z_get $d]
set a [C_a_get $d]
set b [C_b_get $d]
set ptr [C_ptr_get $d]

puts " x = $x  (should be 1.0)"
puts " y = $y  (should be 2.0)"
puts " z = $z  (should be 3.0)"
puts " a = $a  (should be 7)"
puts " b = $b  (should be 2.81828)"
puts " ptr = $ptr (should be _4d2_void_p)"

puts "Trying some member functions."
A_foo $d
B_bar $d
D_grok $d
puts "Looks okay."


