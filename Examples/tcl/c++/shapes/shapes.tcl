catch { load ./shapes.so shapes }
catch {load shapes.dll shapes}

Circle c 4
Square s 10
puts [c area]
puts [s area]
c set_center 4 -5
puts [c perimeter]
puts [s perimeter]

s identify
c identify

