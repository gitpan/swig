# Create and manipulate a variety of arrays

source array.tcl

# Create a double array

set d [ Array double 100 ]

# Clear it

ClearArray $d 100 0.0

# Fill it with values

for {set i 0} {$i < 100} {incr i 1} {
    $d set $i [expr {sin($i)}]
}

# Print out the values

for {set i 0} {$i < 100} {incr i 1} {
    puts [$d get $i]
}

# ---- Now do exactly the same thing with integers -----

# Create an int array

set a [ Array int 100]

# Clear it

ClearArray $a 100 0

# Fill it with values

for {set i 0} {$i < 100} {incr i 1} {
    $a set $i [expr {2*$i}]
}

# Print out the values

for {set i 0} {$i < 100} {incr i 1} {
    puts [$a get $i]
}




