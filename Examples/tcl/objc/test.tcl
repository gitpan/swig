catch {load ./list.so list}

# Create an Objective-C list

set Users [new_List]

set f [open /etc/passwd]

set r [gets $f]
while {$r != ""} {
    set fields [split $r :]
    set u [new_User "[lindex $fields 4]" "[lindex $fields 2]" "[lindex $fields 5]"]
    List_append $Users $u
    set r [gets $f]
}

close $f

for {set i 0} {$i < [List_len $Users]} {incr i 1 } {
    puts [User_str [ptrcast [List_get $Users $i] "User *"]] 
}


