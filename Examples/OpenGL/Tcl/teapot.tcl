catch {load opengl.dll opengl}

source glaux.tcl
auxInitDisplayMode [expr {$AUX_SINGLE | $AUX_RGBA | $AUX_DEPTH}]
auxInitPosition 0 0 500 500
auxInitWindow "Teapot"

glDepthFunc GL_LEQUAL
glEnable GL_DEPTH_TEST

# Set up view

glClearColor 0 0 0 0
glColor3f 1.0 1.0 1.0
glMatrixMode GL_PROJECTION
glLoadIdentity
glOrtho -1 1 -1 1 -1 1
glMatrixMode GL_MODELVIEW
glLoadIdentity

# Draw it

set object {auxWireTeapot 0.5}
redraw



