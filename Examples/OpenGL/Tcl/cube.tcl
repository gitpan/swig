proc square {} {
    glClear GL_COLOR_BUFFER_BIT
    glBegin GL_POLYGON
    glColor3f 0 1.0 0
    glVertex3f -0.5 -0.5 0
    glVertex3f -0.5 0.5 0
    glColor3f 0 0 1.0
    glVertex3f 0.5 0.5 0
    glVertex3f 0.5 -0.5 0
    glEnd
    glFlush
}

proc cube { } {
    glClear GL_COLOR_BUFFER_BIT
    glClear GL_DEPTH_BUFFER_BIT
    glBegin GL_QUADS
    glColor3f 0 1.0 0
    glVertex3f -0.5 -0.5 -0.5
    glVertex3f -0.5 0.5 -0.5
    glVertex3f 0.5 0.5 -0.5
    glVertex3f 0.5 -0.5 -0.5
    glColor3f 0 0 1.0
    glVertex3f -0.5 -0.5 0.5
    glVertex3f -0.5 0.5 0.5
    glVertex3f 0.5 0.5 0.5
    glVertex3f 0.5 -0.5 0.5
    glColor3f 1 1 0
    glVertex3f -0.5 -0.5 -0.5
    glVertex3f -0.5 0.5 -0.5
    glVertex3f -0.5 0.5 0.5
    glVertex3f -0.5 -0.5 0.5
    glColor3f 1 0 0
    glVertex3f 0.5 -0.5 -0.5
    glVertex3f 0.5 0.5 -0.5
    glVertex3f 0.5 0.5 0.5
    glVertex3f 0.5 -0.5 0.5
    glColor3f 1 1 1
    glVertex3f -0.5 -0.5 -0.5
    glVertex3f 0.5 -0.5 -0.5
    glVertex3f 0.5 -0.5 0.5
    glVertex3f -0.5 -0.5 0.5
    glColor3f 0 1 1
    glVertex3f -0.5 0.5 -0.5
    glVertex3f 0.5 0.5 -0.5
    glVertex3f 0.5 0.5 0.5
    glVertex3f -0.5 0.5 0.5
    glEnd
    glFlush
}






