# Pointer example

catch { load ./example.so example}
catch { load ./example.dll example}    ;# Windows

# Allocate some memory
puts "Allocating memory..."
set a [malloc 20000]
puts $a
puts "Freeing memory..."
free $a
puts "Done.\n"

puts "Generating NULL pointer..."
set a "NULL"
puts $a
puts "This will generate an error"
puts "Freeing memory..."
free $a
