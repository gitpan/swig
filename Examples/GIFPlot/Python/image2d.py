# ---------------------------------------------------------------------------
# 2-Dimensional Image base class
#
# This class provides basic support for 2D images.   Functions to clear the
# frame buffer, create images, and do other things are provided.   User
# must provide the draw() and function.
#
# This class has a bunch of parameters for controlling the look of 2D plots.
#
#    self.xmin                         = xmin   (minimum x coordinate)
#    self.ymin                         = ymin   (minimum y coordinate)
#    self.xmax                         = xmax   (maximum x coordinate)
#    self.ymax                         = ymax   (maximum y coordinate)
#
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
#
# These parameters define properties of  tick-marks on the graph
#    self.xtick_spacing
#    self.xtick_length
#    self.ytick_spacing
#    self.ytick_length
#    self.xtick_user            (User defined tick mark locations)
#    self.ytick_user
#
# These properties define various things about the axis
#
#    self.axis_mode             (ORIGIN,FRAME)
#    self.axis_color
#    self.axis_origin           (Where do tick marks start?)
#    self.xaxis_scale           (LINEAR,LOG)
#    self.yaxis_scale   
#    self.xaxis_precision 
#    self.yaxis_precision
#
# Status variables indicating various other things
#    self.draw_axis
#    self.draw_frame
#    self.draw_labels
#    self.draw_ranges
#
# ... and more parameters can be added later
#
# Methods :  The following operations can be performed on 2D plots
#
#  self.plot(x,y,color)                       : Plot a point
#  self.line(x1,y1,x2,y2,color)               : Make a line
#  self.box(x1,y1,x2,y2,color)                : Make a box
#  self.solidbox(x1,y1,x2,y2,color)           : Make a solid box
#  self.circle(x,y,radius,color)              : Plot a circle
#  self.solidcircle(x,y,radius,color)         : Make a solid circle
#  self.drawsymbol(symbol,x,y,color)          : Draw a pix map
#  self.zoom(s)                               : Zoom in on an image
#  self.left(s)                               : Move left
#  self.right(s)                              : Move right
#  self.up(s)                                 : Move up
#  self.down(s)                               : Move down
#  self.scalex(s)                             : scale X axis
#  self.scaley(s)                             : scale Y axis
#  self.region(xmin,ymin,xmax,ymax)           : set the viewing region
#
# General purpose, used before plotting
#  self.clear()
#  self.setplotview()
#  self.setrange()                            : Sets the plotting range
#
# ---------------------------------------------------------------------------

from image import *
import gifplot

ORIGIN     = 1
FRAME      = 2
SQUARE     = gifplot.SQUARE
CROSS      = gifplot.CROSS
TRIANGLE   = gifplot.TRIANGLE

class Image2D(Plot2D,Image):
	# Create a new 2D Image	
	def __init__(self,xmin,ymin,xmax,ymax):
		init_framebuffer()
		Plot2D.__init__(self,Image.Default_framebuffer,xmin,ymin,xmax,ymax)
		Image.__init__(self)            
		self.bgcolor  = BLACK
		self.fgcolor  = WHITE

		# Default values for 2D plots follow.   Note : changing these changes them
		# for all 2D plots.  

		# default values for view frame (in pixels)

                self.frame_left = 60
		self.frame_right = 15
		self.frame_top = 15
		self.frame_bottom = 50
		self.frame_color  = self.fgcolor
		self.frame_width  = 1

		# default values for text and labels

                self.title             = "Untitled " + str(self.imageno)
		self.title_color       = self.fgcolor
		self.xaxis_label       = ""
		self.xaxis_label_color = self.fgcolor
		self.yaxis_label       = ""
		self.yaxis_label_color = self.fgcolor

		# default values for tickmarks

                self.xtick_spacing     = (xmax - xmin)/10.0
		self.xtick_length      = 3
		self.ytick_spacing     = (ymax - ymin)/10.0
		self.ytick_length       = 3
		self.xtick_user        = []
		self.ytick_user        = []

		# default values for axis

                self.axis_mode         = ORIGIN
		self.axis_color        = self.fgcolor
		self.axis_origin       = (0,0)
		self.xaxis_scale       = LINEAR
		self.yaxis_scale       = LINEAR
		self.xaxis_precision   = 10
		self.yaxis_precision   = 7

		# various status variables

                self.draw_axis         = 1
		self.draw_frame        = 1
		self.draw_labels       = 1
		self.draw_ranges       = 1
		self.draw_ticks        = 1
	
		# These variables set the physical location of the 2D plotting frame

		self.vxmin = 0
		self.vymin = 0
		self.vxmax = self.frame.width
		self.vymax = self.frame.height

	# Set plotting region

	def setplotview(self):
		x1 = self.vxmin + self.frame_left
		x2 = self.vxmax - self.frame_right
		y1 = self.vymin + self.frame_bottom
		y2 = self.vymax - self.frame_top
		self.setview(x1,y1,x2,y2)

	# Draw the frame around the image		

	def drawframe(self):
		if self.draw_frame == 1:
			self.frame.setclip(self.vxmin,self.vymin,self.vxmax,self.vymax)
			x1 = self.vxmin + self.frame_left
			x2 = self.vxmax - self.frame_right
			y1 = self.vymin + self.frame_bottom
			y2 = self.vymax - self.frame_top
			self.frame.box(x1,y1,x2,y2,self.frame_color)

	# Draw the axis on the image

	def drawaxis(self):
		if self.draw_axis == 1:
			self.setplotview()
			if self.axis_mode == ORIGIN:
				# Draw axis from origin
				self.xaxis(self.axis_origin[0],self.axis_origin[1],\
                                          self.xtick_spacing, self.xtick_length,self.fgcolor)
				self.yaxis(self.axis_origin[0],self.axis_origin[1],\
					   self.ytick_spacing, self.ytick_length,self.fgcolor)
			elif self.axis_mode == FRAME:
				# Draw axis as part of bounding box
				self.xaxis(self.axis_origin[0],self.ymin,\
					   self.xtick_spacing,self.xtick_length,self.fgcolor)
				self.xaxis(self.axis_origin[0],self.ymax,\
					   self.xtick_spacing,self.xtick_length,self.fgcolor)
				self.yaxis(self.xmin,self.axis_origin[1],\
					   self.ytick_spacing,self.ytick_length,self.fgcolor)
				self.yaxis(self.xmax,self.axis_origin[1],\
					   self.ytick_spacing,self.ytick_length,self.fgcolor)

	# Put annotation (ie. labels) on the graph
	def drawtext(self):
		vxmin = self.vxmin
		vymin = self.vymin
		vxmax = self.vxmax
		vymax = self.vymax
		self.frame.setclip(vxmin,vymin,vxmax,vymax)
		
		sxmin = str(self.xmin)
		symin = str(self.ymin)
		sxmax = str(self.xmax)
		symax = str(self.ymax)
		sxmin = sxmin[0:self.xaxis_precision]
		symin = symin[0:self.yaxis_precision]
		sxmax = sxmax[0:self.xaxis_precision]
		symax = symax[0:self.yaxis_precision]
		# Put ranges on the plot
		if self.draw_ranges == 1:
			self.frame.drawstring(vxmin+self.frame_left,vymin+self.frame_bottom-12,\
					      self.fgcolor,self.bgcolor,sxmin,HORIZONTAL)
			self.frame.drawstring(vxmax-8*len(sxmax)-self.frame_right,\
					      vymin+self.frame_bottom-12,self.fgcolor,\
					      self.bgcolor,sxmax,HORIZONTAL)
			self.frame.drawstring(vxmin+self.frame_left-8*len(symin),\
					      vymin+self.frame_bottom,self.fgcolor,\
					      self.bgcolor,symin,HORIZONTAL)
			self.frame.drawstring(vxmin+self.frame_left-8*len(symax),\
					      vymax-self.frame_top-10,self.fgcolor,\
					      self.bgcolor,symax,HORIZONTAL)

		# Put title on the plot

		xc = (vxmin + self.frame_left + vxmax - self.frame_right)/2
		self.frame.drawstring(xc-4*len(self.title),vymax-self.frame_top+2,\
				      self.fgcolor,self.bgcolor,self.title,HORIZONTAL)

		# Draw axis labels

		if self.draw_labels == 1:
			self.frame.drawstring(xc-4*len(self.xaxis_label),vymin+self.frame_bottom-12,\
					      self.fgcolor,self.bgcolor,self.xaxis_label,HORIZONTAL)
			yc = (vymin + self.frame_bottom + vymax - self.frame_top)/2
			self.frame.drawstring(vxmin+self.frame_left-9,yc - 4*len(self.yaxis_label),\
					      self.fgcolor,self.bgcolor,self.yaxis_label,VERTICAL)


	# start a new plot. Clears the framebuffer, draws frame, text, titles, etc...

	def newplot(self):
		self.setview(self.vxmin,self.vymin,self.vxmax,self.vymax)
		self.clear(self.bgcolor)
		self.drawframe()
		self.drawaxis()
		self.drawtext()
		self.setplotview()
		self.start()

	# Image manipulation methods.   Do things like zoom, translate, etc....

	# scalex(s).  Scales the x-axis.  s is given as a scaling factor

	def scalex(self,s):
		dx = self.xmax - self.xmin
		xc = self.xmin + dx/2.0
		dx = dx*s
		self.xmin = xc - dx/2.0
		self.xmax = xc + dx/2.0
		self.setrange(self.xmin,self.ymin,self.xmax,self.ymax)

	# scaley(s).  Scales the y-axis.  s is given as a percent with s = 100 meaning no effect

	def scaley(self,s):
		dy = self.ymax - self.ymin
		yc = self.ymin + dy/2.0
		dy = dy*s
		self.ymin = yc - dy/2.0
		self.ymax = yc + dy/2.0
		self.setrange(self.xmin,self.ymin,self.xmax,self.ymax)

	# Zooms a current image.  s is given as a percent with s = 100 meaning no effect

	def zoom(self,s):
		s = 100.0/s
		self.scalex(s)
		self.scaley(s)

	# Move image left.  s is given in range 0,100. 100 moves a full screen left

	def left(self,s):
		dx = self.xmax -self.xmin
		dx = dx*s/100.0
		self.xmin = self.xmin + dx
		self.xmax = self.xmax + dx
		self.setrange(self.xmin,self.ymin,self.xmax,self.ymax)

	# Move image right.  s is given in range 0,100. 100 moves a full screen right

	def right(self,s):
		dx = self.xmax -self.xmin
		dx = dx*s/100.0
		self.xmin = self.xmin - dx
		self.xmax = self.xmax - dx
		self.setrange(self.xmin,self.ymin,self.xmax,self.ymax)

	# Move image down.  s is given in range 0,100. 100 moves a full screen down

	def down(self,s):
		dy = self.ymax -self.ymin
		dy = dy*s/100.0
		self.ymin = self.ymin + dy
		self.ymax = self.ymax + dy
		self.setrange(self.xmin,self.ymin,self.xmax,self.ymax)

	# Move image up.  s is given in range 0,100. 100 moves a full screen up

	def up(self,s):
		dy = self.ymax -self.ymin
		dy = dy*s/100.0
		self.ymin = self.ymin - dy
		self.ymax = self.ymax - dy
		self.setrange(self.xmin,self.ymin,self.xmax,self.ymax)

	def plotarray(self,data,xmin,xmax,color,symbol):
		if len(data) == 0: return
		dx = 1.0*(xmax- xmin)/len(data)
		x1 = xmin
		y1 = data[0]
		i = 0
		npoints = len(data)
		# Plot the first point
		if symbol != None:
			self.drawpixmap(symbol, x1,y1,color,self.bgcolor)
		i = i + 1
		while i < npoints:
			x2 = x1 + dx
			y2 = data[i]
			self.line(x1,y1,x2,y2,color)
			if symbol != None:
				self.drawpixmap(symbol,x2,y2,color,self.bgcolor)
			x1 = x2
			y1 = y2
			i = i + 1
	
	def plotbar(self,data,xmin,xmax,color):
		if len(data) == 0: return
		dx = 1.0*(xmax- xmin)/len(data)
		x1 = xmin
		i = 0
		npoints = len(data)
		while i < npoints:
			self.solidbox(x1-0.5*dx,0,x1+0.5*dx,data[i],color)
			x1 = x1 + dx
			i = i + 1

	def plotxy(self,xdata,ydata,color,symbol):
		if len(xdata) == 0: return
		if len(xdata) != len(ydata) : return
		x1 = xdata[0]
		y1 = ydata[0]
		i = 0
		npoints = len(xdata)
		# Plot the first point
		if symbol != None:
			self.drawpixmap(symbol,x1,y1,color,self.bgcolor)
		i = i + 1
		while i < npoints:
			x2 = xdata[i]
			y2 = ydata[i]
			self.line(x1,y1,x2,y2,color)
			if symbol != None:
				self.drawpixmap(symbol,x2,y2,color,self.bgcolor)
			x1 = x2
			y1 = y2
			i = i + 1


