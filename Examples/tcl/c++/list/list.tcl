catch {load ./list.so List}
catch {load list.dll List}

List l
for {set i 0} {$i < 1000} {incr i 1} {
    l insert [expr {[rand] % 2000}]
}

for {set i 0} {$i < 10} {incr i 1} {
    set j [expr {[rand] % 2000}]
    set f [l search $j]
    if {$f == 1} {
	puts "$j ... found"
    } {
	puts "$j ... not found"
    }
}

for {set i 0} {$i < 10000} {incr i 1} {
    set j [expr {[rand] % 2000}]
    l remove $j
}

List_print [l cget -this]

puts "Count=  [l cget -length]"





