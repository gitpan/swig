catch { load ./vector.so vector}
catch {load vector.dll vector }

set v [Vector]
$v configure -x 3.4 -y -2.0 -z 9.8
Vector_print $v
set w [Vector]
Vector_add $v $v $w
Vector_print $w
