# ------------------------------------------------------------------------------------
# 3-Dimensional image base class
#
# This class defines parameters and methods for dealing with 3D images.  Is fairly
# similar to the Image2D class, but even more complicated (yikes).
#
#
#    self.xmin                         = xmin   (minimum x coordinate)
#    self.ymin                         = ymin   (minimum y coordinate)
#    self.zmin                         = zmin   (minimum z coordinate)
#    self.xmax                         = xmax   (maximum x coordinate)
#    self.ymax                         = ymax   (maximum y coordinate)
#    self.zmax                         = zmax   (maximum z coordinate)
#    self.min                          = minimum "color" value
#    self.max                          = maximum "color" value
# These parameters define where the following region is inside the view region.
# They are given in pixels.  For example, self.frame_left = 50 means that
# the actual data will be plotted 50 pixels from the left boundary.
#
#    self.frame_left
#    self.frame_right
#    self.frame_top
#    self.frame_bottom
#    self.frame_color
#    self.frame_width
#
# These parameters define properties of text on the graph
#    self.title
#    self.title_color
#    self.xaxis_label
#    self.xaxis_label_color
#    self.yaxis_label
#    self.yaxis_label_color
#    self.zaxis_label
#    self.zaxis_label_color
#
# These parameters define properties of  tick-marks on the graph
#    self.xtick_spacing
#    self.xtick_length
#    self.ytick_spacing
#    self.ytick_length
#    self.ztick_spacing
#    self.ztick_length
#    self.xtick_user            (User defined tick mark locations)
#    self.ytick_user
#    self.ztick_user
#
# These properties define various things about the axis
#
#    self.axis_color
#    self.axis_origin           (Where do tick marks start?)
#    self.xaxis_scale           (LINEAR,LOG)
#    self.yaxis_scale   
#    self.zaxis_scale
#    self.xaxis_precision 
#    self.yaxis_precision
#    self.zaxis_precision
#
# These properties describe the colorbar
#
#    self.colorbar_width        
#    self.colorbar_orientation
#
# Status variables indicating various other things
#    self.draw_axis
#    self.draw_frame
#    self.draw_labels
#    self.draw_ranges
#    self.draw_colorbar
#
# ... and more parameters can be added later
#
# Methods :  The following operations can be performed on 2D plots
#
#  self.plot(x,y,z,color)                     : Plot a point
#  self.line(x1,y1,z1,x2,y2,z2,color)         : Make a line
#  self.perspective(fovy,zfar,znear)          : Set perspective transformation
#  self.lookat(z)                             : Sets how far away the viewer is
#  self.autoperspective(fovy)                 : Automatically figure out near and far clip planes
#  self.solidtriangle(x1,y1,z1,...,x3,y3,z3,color)  : Draw a filled triangle
#  self.triangle(x1,y1,z1,...,x3,y3,z3,color) : Draw an outline triangle
#  self.quad(x1,y1,z1,...,x4,y4,z4,color)     : Draw a quadralateral
#  self.solidquad(x1,y1,z1,...,x4,y4,z4,color): Draw a solid quadralateral
#  self.solidsphere(x,y,z,radius,color)       : Draw a solid sphere
#  self.outlinesphere(x,y,z,radius,color)     : Draw an outline sphere
#  self.rotl(deg)                             : Rotate left
#  self.rotr(deg)                             : Rotate right
#  self.rotd(deg)                             : Rotate down
#  self.rotu(deg)                             : Rotate up
#  self.rotc(deg)                             : Rotate around center
#  self.rotx(deg)                             : Rotate around x axis
#  self.roty(deg)                             : Rotate around y axis
#  self.rotz(deg)                             : Rotate around z axis
#  self.zoom(s)                               : Zoom in on an image
#  self.left(s)                               : Move left
#  self.right(s)                              : Move right
#  self.up(s)                                 : Move up
#  self.down(s)                               : Move down
#  self.region(xmin,ymin,xmax,ymax,zmin,zmax) : set the viewing region
#
# General purpose, used before plotting
#  self.clear()
#  self.setplotview()
#  self.setrange()                            : Sets the plotting range
#
# ---------------------------------------------------------------------------

from image import *
from gifplot import *

class Image3D(Plot3D,Image):

	# Create a new 3D Image	

	def __init__(self,xmin,ymin,zmin,xmax,ymax,zmax):
		init_framebuffer()
		Plot3D.__init__(self,Image.Default_framebuffer,xmin,ymin,zmin,xmax,ymax,zmax)
		Image.__init__(self)                        # Construct a new image

		# Default scaling parameters (for creating the colorbar)

		self.min  = 0                
		self.max  = 1

		# default values for view frame (in pixels)

                self.frame_left = 40
		self.frame_right = 40
		self.frame_top = 20
		self.frame_bottom = 60
		self.frame_color  = self.fgcolor
		self.frame_width  = 4

		# default values for text and labels

                self.title             = "Untitled " + str(self.imageno)
		self.title_color       = self.fgcolor
		self.xaxis_label       = ""
		self.xaxis_label_color = self.fgcolor
		self.yaxis_label       = ""
		self.yaxis_label_color = self.fgcolor
		self.zaxis_label       = ""
		self.zaxis_label_color = self.fgcolor

		# default values for tickmarks

                self.xtick_spacing     = (xmax - xmin)/10.0
		self.xtick_length      = 3
		self.ytick_spacing     = (ymax - ymin)/10.0
		self.ytick_length       = 3
		self.ztick_spacing     = (zmax - zmin)/10.0
		self.ztick_length      = 3
		self.xtick_user        = []
		self.ytick_user        = []
		self.ztick_user        = []

		# default values for axis

		self.axis_color        = self.fgcolor
		self.axis_origin       = (0,0)
		self.xaxis_scale       = LINEAR
		self.yaxis_scale       = LINEAR
		self.zaxis_scale       = LINEAR
		self.xaxis_precision   = 7
		self.yaxis_precision   = 7
		self.zaxis_precision   = 7

		# default values for colorbar

		self.colorbar_width    = 7
		self.colorbar_orientation = HORIZONTAL
		
		# default values for bounding box

		self.box_color         = CYAN
		
		# various status variables

                self.draw_axis         = 1
		self.draw_frame        = 1
		self.draw_labels       = 1
		self.draw_ranges       = 1
		self.draw_box          = 1
		self.draw_colorbar     = 1

		# These variables set the physical location of the 2D plotting frame

		self.vxmin = 0
		self.vymin = 0
		self.vxmax = self.frame.width
		self.vymax = self.frame.height

	# set the plotting region

	def setplotview(self):
		x1 = self.vxmin + self.frame_left
		x2 = self.vxmax - self.frame_right
		y1 = self.vymin + self.frame_bottom
		y2 = self.vymax - self.frame_top
		self.frame.setclip(x1,y1,x2,y2)
		self.setview(x1,y1,x2,y2)

	# start a new plot.  Clears framebuffer, draws frame, etc...

	def newplot(self):
		self.setview(self.vxmin,self.vymin,self.vxmax,self.vymax)
		self.clear(self.bgcolor)
		self.drawframe()
		self.drawcolorbar()
		self.drawtext()
		self.drawboundingbox()
		self.setplotview()
		self.start()

	# Draw a bounding box around the image

	def drawboundingbox(self):
		if self.draw_box == 1:
			self.setplotview()
			self.line(self.xmin,self.ymin,self.zmin,self.xmax,self.ymin,self.zmin,self.box_color)
			self.line(self.xmax,self.ymin,self.zmin,self.xmax,self.ymax,self.zmin,self.box_color)
			self.line(self.xmax,self.ymax,self.zmin,self.xmin,self.ymax,self.zmin,self.box_color)
			self.line(self.xmin,self.ymax,self.zmin,self.xmin,self.ymin,self.zmin,self.box_color)
			self.line(self.xmin,self.ymin,self.zmin,self.xmin,self.ymin,self.zmax,self.box_color)
			self.line(self.xmax,self.ymin,self.zmin,self.xmax,self.ymin,self.zmax,self.box_color)
			self.line(self.xmax,self.ymax,self.zmin,self.xmax,self.ymax,self.zmax,self.box_color)
			self.line(self.xmin,self.ymax,self.zmin,self.xmin,self.ymax,self.zmax,self.box_color)
			self.line(self.xmin,self.ymin,self.zmax,self.xmax,self.ymin,self.zmax,self.box_color)
			self.line(self.xmax,self.ymin,self.zmax,self.xmax,self.ymax,self.zmax,self.box_color)
			self.line(self.xmax,self.ymax,self.zmax,self.xmin,self.ymax,self.zmax,self.box_color)
			self.line(self.xmin,self.ymax,self.zmax,self.xmin,self.ymin,self.zmax,self.box_color)

	# Draw a frame around the image.  Includes image manipulation tick marks

	def drawframe(self):
		if self.draw_frame == 1:
			self.frame.setclip(self.vxmin,self.vymin,self.vxmax,self.vymax)
			x1 = self.vxmin + self.frame_left - self.frame_width
			x2 = self.vxmax - self.frame_right + self.frame_width
			y1 = self.vymin + self.frame_bottom - self.frame_width
			y2 = self.vymax - self.frame_top + self.frame_width
			self.frame.box(x1,y1,x2,y2,self.frame_color)
			dx = (x2 - x1)/10.0
			dy = (y2 - y1)/10.0
			for i in range(0,11):
				self.frame.solidbox(x1+i*dx,y1,x1+i*dx+1,y1+self.frame_width,self.frame_color)
				self.frame.solidbox(x1+i*dx,y2,x1+i*dx+1,y2-self.frame_width,self.frame_color)
				self.frame.solidbox(x1,y1+i*dy,x1+self.frame_width,y1+i*dy+1,self.frame_color)
				self.frame.solidbox(x2,y1+i*dy,x2-self.frame_width,y1+i*dy+1,self.frame_color)


	# Draw a colorbar on the image.

	def drawcolorbar(self):
		self.frame.setclip(self.vxmin,self.vymin,self.vxmax,self.vymax)
		if self.colorbar_orientation == HORIZONTAL:
			x1 = self.vxmin+self.frame_left
			y1 = self.vymin+self.frame_bottom-self.frame_width - 2
			x2 = self.vxmax-self.frame_right
			y2 = y1 - self.colorbar_width
			self.frame.interpbox(x1,y1,x2,y2,16,16,255,255)

			# Draw colorbar minimum and maximum values

			self.frame.drawstring(x1,y2-11,self.fgcolor,self.bgcolor,str(self.min),HORIZONTAL)
			self.frame.drawstring(x2-8*len(str(self.max)),y2-11,self.fgcolor,self.bgcolor,str(self.max),HORIZONTAL)
		elif self.colorbar_orientation == VERTICAL:
			x1 = self.vxmin+self.frame_left-self.frame_width-2
			y1 = self.vymin+self.frame_bottom
			x2 = x1-self.colorbar_width
			y2 = self.vymax-self.frame_top
			self.frame.interpbox(x1,y1,x2,y2,16,255,16,255)

			# Draw colorbar minimum and maximum values

			self.frame.drawstring(x2-2,y1,self.fgcolor,self.bgcolor,str(self.min),VERTICAL)
			self.frame.drawstring(x2-2,y2-8*len(str(self.max)),self.fgcolor,self.bgcolor,str(self.max),VERTICAL)

	# Draw text annotation on the image

	def drawtext(self):
		self.frame.setclip(self.vxmin,self.vymin,self.vxmax,self.vymax)
		xc = (self.vxmin+self.frame_left + self.vxmax-self.frame_right)/2
		yc = self.vymin+self.frame_bottom-self.frame_width- 13
		if (self.draw_colorbar == 1) and (self.colorbar_orientation == HORIZONTAL):
			yc = yc - self.colorbar_width
		self.frame.drawstring(xc-4*len(self.title),yc,self.fgcolor,self.bgcolor,self.title,HORIZONTAL)

	# Change to another framebuffer		
	def setframe(self,framebuffer):
		self.frame = framebuffer
		framebuffer.thisown = 0
		

	# More needs to be implemented here (maybe)



