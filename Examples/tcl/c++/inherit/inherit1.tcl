catch {load ./inherit.so inherit}
catch {load inherit.dll inherit}

Point1 p1
p1 configure -x 1.0
puts [p1 mag]

Point2 p2
p2 configure -x 1.0 -y 2.0
puts [p2 mag]

Point3 p3
p3 configure -x 1.0 -y 2.0 -z 3.0
puts [p3 mag]

puts [Point1_mag [p1 cget -this]]
puts [Point1_mag [p2 cget -this]]
puts [Point1_mag [p3 cget -this]]

