
catch { load ./vector.so vector }
catch {load vector.dll vector }

set v [new_Vector]
Vector_x_set $v 3.4
Vector_y_set $v -2.0
Vector_z_set $v 9.8
Vector_print $v
set w [new_Vector]
Vector_add $v $v $w
Vector_print $w

