catch { load ./example.so example}
catch { load ./example.dll example}    ;# Windows

puts "Default SWIG Constants"
printi $FOO
printd $PI4
prints $STR

puts "\nHash table"
printi FOO
printd PI4
prints STR
