# Load up the modules (if available)

puts {
If you have built everything correctly, this script should
generate no errors.
}

catch { load ./base.so base }
catch { load ./foo.so foo }
catch { load ./bar.so bar }

# The following should run without any type errors

set b [new_Bar]

Bar_bar_method $b
Base_base_method $b

set f [new_Foo]

Foo_foo_method $f
Base_base_method $f

