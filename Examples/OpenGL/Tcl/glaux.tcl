# Extract some constants

proc redraw {} {
    global object
    glClear GL_COLOR_BUFFER_BIT
    glClear GL_DEPTH_BUFFER_BIT
    eval $object
    glFlush
}

button .rx -text "Rotate x" -command {glRotatef 15 1 0 0; redraw}
button .ry -text "Rotate y" -command {glRotatef 15 0 1 0; redraw}
button .rz -text "Rotate z" -command {glRotatef 15 0 0 1; redraw}
button .quit -text "Quit" -command {exit 0}
pack .rx .ry .rz .quit -fill x


