# Test some out some of our math functions

catch { load ./example.so example}
catch { load ./example.dll example}    ;# Windows

puts [exp -2.5]
puts [log 2]
puts [inv 0.25]
puts [sqrt 0]

# Now generate an exception

puts "This will generate an error."

puts [log 0]
