# Our new constant processor allows us to access constants
# without using $ or global declarations

catch {load ./constant.so constant}
catch {load ./constant.dll constant}

proc constants {l} {
    foreach i $l {
	print_const $i
    }
}

# This function will fail
proc fails {} {
    print_const $GL_COLOR_BUFFER_BIT
}

# This function will work (but is a pain)
proc works {} {
    global GL_COLOR_BUFFER_BIT
    print_const $GL_COLOR_BUFFER_BIT
}

# Version using our new "int" type
proc better { } {
    print_const GL_COLOR_BUFFER_BIT
}
    
print_const GL_DEPTH_BUFFER_BIT
print_const GL_STENCIL_VALUE_MASK

# Dump a bunch of constants out

constants { GL_MAX_CONVOLUTION_HEIGHT_EXT 
GL_POST_CONVOLUTION_RED_SCALE_EXT   
GL_POST_CONVOLUTION_GREEN_SCALE_EXT 
GL_POST_CONVOLUTION_BLUE_SCALE_EXT  
GL_POST_CONVOLUTION_ALPHA_SCALE_EXT 
GL_POST_CONVOLUTION_RED_BIAS_EXT    
GL_POST_CONVOLUTION_GREEN_BIAS_EXT  
GL_POST_CONVOLUTION_BLUE_BIAS_EXT   
GL_POST_CONVOLUTION_ALPHA_BIAS_EXT  }

# Can still pass numeric arguments in

print_const 7

# Can still use variables

puts [expr {$GL_COLOR_BUFFER_BIT | $GL_DEPTH_BUFFER_BIT}]
