catch {load opengl.dll opengl}

proc triangle { } {
global GL_TRIANGLES GL_COLOR_BUFFER_BIT
glClearColor 0 0 0 0
glClear $GL_COLOR_BUFFER_BIT
glColor3f 1.0 0.5 0.5
glBegin $GL_TRIANGLES
glVertex3f 0 0 0
glVertex3f 100 0 0
glVertex3f 50 50 0
glEnd
glColor3f 0.5 1.0 0.5
glBegin $GL_TRIANGLES
glVertex3f 0 0 0
glVertex3f 0 100 0
glVertex3f 50 50 50
glEnd
glColor3f 0.5 0.5 1.0
glBegin $GL_TRIANGLES
glVertex3f 0 0 0
glVertex3f 0 0 100
glVertex3f 50 50 50
glEnd
glColor3f 0.25 0.25 0.5
glBegin $GL_TRIANGLES
glVertex3f 0 100 100
glVertex3f 0 25 0
glVertex3f 50 50 50
glEnd

}

