catch { load ./example.so example}
catch { load ./example.dll example}

puts "Note : error message is part of the SWIG example (don't panic)"

print_error 15
print_error 15 "This is an error"

set_range 500 500
set_range 500 500 -10 10
set_range 400 400 -7.554 23.72 -2.5 12.5








