#!./python
# (c) Copyright 1993, Silicon Graphics, Inc.
# ALL RIGHTS RESERVED 
# Permission to use, copy, modify, and distribute this software for 
# any purpose and without fee is hereby granted, provided that the above
# copyright notice appear in all copies and that both the copyright notice
# and this permission notice appear in supporting documentation, and that 
# the name of Silicon Graphics, Inc. not be used in advertising
# or publicity pertaining to distribution of the software without specific,
# written prior permission. 
#
# THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
# AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
# INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
# FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
# GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
# SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
# KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
# LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
# THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
# ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
# POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
# 
# US Government Users Restricted Rights 
# Use, duplication, or disclosure by the Government is subject to
# restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
# (c)(1)(ii) of the Rights in Technical Data and Computer Software
# clause at DFARS 252.227-7013 and/or in similar or successor
# clauses in the FAR or the DOD or NASA FAR Supplement.
# Unpublished-- rights reserved under the copyright laws of the
# United States.  Contractor/manufacturer is Silicon Graphics,
# Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
#
# OpenGL(TM) is a trademark of Silicon Graphics, Inc.
#/
#
# material.c
# This program demonstrates the use of the GL lighting model.
# Several objects are drawn using different material characteristics.
# A single light source illuminates the objects.
#/

from opengl import *
import time

#  Initialize z-buffer, projection matrix, light source, 
#  and lighting model.  Do not specify a material property here.
#

def myinit():
     ambient = newfv4( 0.0, 0.0, 0.0, 1.0 )
     diffuse = newfv4( 1.0, 1.0, 1.0, 1.0 )
     specular = newfv4( 1.0, 1.0, 1.0, 1.0 )
     position = newfv4( 0.0, 3.0, 2.0, 0.0 )
     lmodel_ambient = newfv4( 0.4, 0.4, 0.4, 1.0 )
     local_view = newfv4( 0.0,0,0,0 )
     glEnable(GL_DEPTH_TEST);
     glDepthFunc(GL_LESS);
     glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
     glLightfv(GL_LIGHT0, GL_POSITION, position);
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
     glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glClearColor(0.0, 0.1, 0.1, 0.0);

#  Draw twelve spheres in 3 rows with 4 columns.  
#  The spheres in the first row have materials with no ambient reflection.
#  The second row has materials with significant ambient reflection.
#  The third row has materials with colored ambient reflection.
#
#  The first column has materials with blue, diffuse reflection only.
#  The second column has blue diffuse reflection, as well as specular
#  reflection with a low shininess exponent.
#  The third column has blue diffuse reflection, as well as specular
#  reflection with a high shininess exponent (a more concentrated highlight).
#  The fourth column has materials which also include an emissive component.
#
#  glTranslatef() is used to move spheres to their appropriate locations.
#

def display():
     no_mat = newfv4( 0.0, 0.0, 0.0, 1.0 )
     mat_ambient = newfv4( 0.7, 0.7, 0.7, 1.0 )
     mat_ambient_color = newfv4( 0.8, 0.8, 0.2, 1.0 )
     mat_diffuse = newfv4( 0.1, 0.5, 0.8, 1.0 )
     mat_specular = newfv4( 1.0, 1.0, 1.0, 1.0 )
     no_shininess = newfv4( 0.0,0,0,0 )
     low_shininess = newfv4( 5.0,0,0,0 )
     high_shininess = newfv4( 100.0,0,0,0 )
     mat_emission = newfv4(0.3, 0.2, 0.2, 0.0)
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#  draw sphere in first row, first column
#  diffuse reflection only; no ambient or specular  
#
     glPushMatrix();
     glTranslatef (-3.75, 3.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
     glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in first row, second column
#  diffuse and specular reflection; low shininess; no ambient
#/
     glPushMatrix();
     glTranslatef (-1.25, 3.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in first row, third column
#  diffuse and specular reflection; high shininess; no ambient
#/
     glPushMatrix();
     glTranslatef (1.25, 3.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in first row, fourth column
#  diffuse reflection; emission; no ambient or specular reflection
#/
     glPushMatrix();
     glTranslatef (3.75, 3.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
     glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in second row, first column
#  ambient and diffuse reflection; no specular  
#/
     glPushMatrix();
     glTranslatef (-3.75, 0.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
     glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in second row, second column
#  ambient, diffuse and specular reflection; low shininess
#/
     glPushMatrix();
     glTranslatef (-1.25, 0.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in second row, third column
#  ambient, diffuse and specular reflection; high shininess
#/
     glPushMatrix();
     glTranslatef (1.25, 0.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in second row, fourth column
#  ambient and diffuse reflection; emission; no specular
#/
     glPushMatrix();
     glTranslatef (3.75, 0.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
     glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in third row, first column
#  colored ambient and diffuse reflection; no specular  
#/
     glPushMatrix();
     glTranslatef (-3.75, -3.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
     glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in third row, second column
#  colored ambient, diffuse and specular reflection; low shininess
#/
     glPushMatrix();
     glTranslatef (-1.25, -3.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in third row, third column
#  colored ambient, diffuse and specular reflection; high shininess
#/
     glPushMatrix();
     glTranslatef (1.25, -3.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
     auxSolidSphere(1.0);
     glPopMatrix();
#  draw sphere in third row, fourth column
#  colored ambient and diffuse reflection; emission; no specular
#/
     glPushMatrix();
     glTranslatef (3.75, -3.0, 0.0);
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
     glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
     auxSolidSphere(1.0);
     glPopMatrix();
     glFlush();

def myReshape(w, h):
     glViewport(0, 0, w, h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     if (w <= (h * 2)) :
	glOrtho (-6.0, 6.0, -3.0*(h*2)/w, 3.0*(h*2)/w, -10.0, 10.0);
     else :
        glOrtho (-6.0*w/(h*2), 6.0*w/(h*2), -3.0, 3.0, -10.0, 10.0);
     glMatrixMode(GL_MODELVIEW);


auxInitDisplayMode (AUX_SINGLE | AUX_RGB | AUX_DEPTH);
auxInitPosition (0, 0, 600, 450);
auxInitWindow ("materials");
myinit();
myReshape(600,450);
display();
time.sleep(15)