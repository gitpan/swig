catch {load ./inherit.so inherit}
catch {load inherit.dll inherit}

set p1 [new_Point1]
Point1_x_set $p1 1.0
puts [Point1_mag $p1]

set p2 [new_Point2]
Point2_x_set $p2 1.0
Point2_y_set $p2 2.0
puts [Point2_mag $p2]

set p3 [new_Point3]
Point3_x_set $p3 1.0
Point3_y_set $p3 2.0
Point3_z_set $p3 3.0
puts [Point3_mag $p3]

puts [Point1_mag $p1]
puts [Point1_mag $p2]
puts [Point1_mag $p3]


