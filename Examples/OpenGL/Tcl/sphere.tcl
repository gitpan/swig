catch {load opengl.dll opengl}

source glaux.tcl
auxInitDisplayMode [expr {$AUX_SINGLE | $AUX_RGBA | $AUX_DEPTH}]
auxInitPosition 0 0 500 500
auxInitWindow "Lit-Sphere"

# set up material properties

set mat_specular [newfv4 1.0 1.0 1.0 1.0]
set mat_shininess [newfv4 50.0 0 0 0]
set light_position [newfv4 1.0 1.0 1.0 0.0]

glMaterialfv GL_FRONT GL_SPECULAR $mat_specular
glMaterialfv GL_FRONT GL_SHININESS $mat_shininess
glLightfv GL_LIGHT0 GL_POSITION $light_position
glEnable GL_LIGHTING
glEnable GL_LIGHT0
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

set object {auxSolidSphere 0.5}
redraw



