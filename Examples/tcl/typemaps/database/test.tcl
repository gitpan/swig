catch {load ./db.so db}

set f [open /etc/passwd]

set r [gets $f]
while {$r != ""} {
    set fields [split $r :]
    add_user [list "[lindex $fields 0]" "[lindex $fields 2]" "[lindex $fields 3]" "[lindex $fields 4]" "[lindex $fields 5]"]
    set r [gets $f]
}

close $f

sort_users

puts "\nLooking for root";
puts [lookup_user root]

puts "\nLooking for beazley";
puts [lookup_user beazley]

# print out all users

puts "\nAll users";
for {set i 0} {$i < [num_users]} {incr i 1} {
    puts [get_user $i]
}


