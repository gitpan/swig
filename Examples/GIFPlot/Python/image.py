# =================================================================================
# image.py
#
# A generic image base class.   Defines a variety of global parameters and
# other stuff related to framebuffers.
# ================================================================================

from gifplot import *

# --------------------------------------------------------------------------------
# Default values (in case the user doesn't supply them
# --------------------------------------------------------------------------------

GRAPHICS_SIZE                = 500
GRAPHICS_COLORMAP            = "cmap"

# --------------------------------------------------------------------------
# Image base class
#
# All displays are consider to be "images" derived from this base class.
# The following member data and operations are available.
#
# self.frame       : Framebuffer being used by this image
# self.colormap    : Colormap being used with the image
# self.vxmin       : Plotting region for this image
# self.vymin                   "
# self.vxmax                   "
# self.vymax                   "
# self.bgcolor     : Default background color
# self.fgcolor     : Default foreground color
#
# All images must support the following methods (images may of course use the
# definitions in the base class).
#
# self.show()      : Show the current image
# self.draw()      : Method for drawing the entire image on the frame buffer
# self.output()    : Dump the current framebuffer out regardless of what state its in
# self.setview()   : Method for setting the viewing region of this image
#
# The following methods are also encouraged for all images
#
# self.zoom()      : Zoom in on the image
# self.left()      : translate left
# self.right()     : translate right
# self.up()        : translate up
# self.down()      : translate down
# self.rotr()      : rotate right (3D only)
# self.rotl()      : rotate left (3D only)
# self.rotd()      : rotate down (3D only)
# self.rotu()      : rotate up (3D only)
# self.rotc()      : rotate around the center point (3D only)
# self.rotx()      : rotate around the x axis (3D only)
# self.roty()      : rotate around the y axis (3D only)
# self.rotz()      : rotate around the z axis (3D only)
# self.center()    : Set center point
#
# -------------------------------------------------------------------------- 
	
class Image:
	Current             = None         # The currently active image
	Default_framebuffer = None         # Default framebuffer
	Default_colormap    = None         # Default colormap
	ImageNo             = 0            # Current Image Number
	bgcolor	            = BLACK
	fgcolor             = WHITE

	def __init__(self):
		init_framebuffer()
		if Image.Default_colormap == None:
			colormap(GRAPHICS_COLORMAP)
		self.frame = Image.Default_framebuffer
		self.filename = "img"+str(Image.ImageNo)+".gif"
		self.imageno  = 0                         
		Image.ImageNo = Image.ImageNo + 1
		self.colormap = Image.Default_colormap    
		self.stamp = ""
		self.fgcolor = Image.fgcolor
		self.bgcolor = Image.bgcolor
		self.vxmin   = 0
		self.vymin   = 0
		self.vxmax   = self.frame.width
		self.vymax   = self.frame.height

	# Generate the image and dump it to the current output device

	def show(self):
		if self.frame == None:
			print "Error. No frame buffer assigned to this image"
			return
		self.frame.noclip()
		self.frame.clear(self.bgcolor)
		self.frame.setclip(self.vxmin,self.vymin,self.vxmax,self.vymax)
		self.draw()
		self.output()

	# Dump this image out over a socket or to a file
	
	def output(self):
		global Graphics_current, Graphics_buffer, Graphics_buffer_size

		# Put a stamp on the image

		self.frame.noclip()	
		self.frame.drawstring(1,1,self.fgcolor,self.bgcolor,self.stamp,HORIZONTAL)

		# Make a GIF image

		print "Writing " + self.filename
		self.frame.writeGIF(self.colormap,self.filename)
		Image.Current = self
		
        def draw(self):
		print "No drawing method specified for image " + self.filename

	# Set the viewport for this image

	def viewport(self,vx,vy,wx,wy):
		self.vxmin = vx
		self.vymin = vy
		self.vxmax = wx
		self.vymax = wy
		self.frame.setclip(vx,vy,wx,wy)

	# Image manipulation methods

        def zoom(self,s):
		print("zoom() unavailable in current image")
        def left(self,s):
		print("left() unavailable in current image")
        def right(self,s):
		print("right() unavailable in current image")
        def up(self,s):
		print("up() unavailable in current image")
        def down(self,s):
		print("down() unavailable in current image")
        def rotr(self,s):
		print("rotr() unavailable in current image")
        def rotl(self,s):
		print("rotl() unavailable in current image")
        def rotu(self,s):
		print("rotu() unavailable in current image")
        def rotd(self,s):
		print("rotd() unavailable in current image")
        def rotc(self,s):
		print("rotc() unavailable in current image")
        def rotx(self,s):
		print("rotx() unavailable in current image")
        def roty(self,s):
		print("roty() unavailable in current image")
        def rotz(self,s):
		print("rotz() unavailable in current image")
        def center(self,x,y):
		print("center() unavailable in current image")

# ---------------------------------------------------------------------------
# Image manipulation shortcuts
#
# Whenever an image is created or manipulated, 'image' gets set to
# that image.   These commands operate on the last image used.
# ---------------------------------------------------------------------------

def show(*args):
	if len(args) == 0:
		Image.Current.show()
	else :
		for img in args:
			img.show()

def zoom(s):
	Image.Current.zoom(s)
	Image.Current.show()

def left(s):
	Image.Current.left(s)
	Image.Current.show()

def right(s):
	Image.Current.right(s)
	Image.Current.show()

def up(s):
	Image.Current.up(s)
	Image.Current.show()

def center(x,y):
	Image.Current.center(x,y)
	Image.Current.show()

def down(s):
	Image.Current.down(s)
	Image.Current.show()

def rotr(deg):
	Image.Current.rotr(deg)
	Image.Current.show()

def rotl(deg):
	Image.Current.rotl(deg)
	Image.Current.show()

def rotd(deg):
	Image.Current.rotd(deg)
	Image.Current.show()

def rotu(deg):
	Image.Current.rotu(deg)
	Image.Current.show()

def rotc(deg):
	Image.Current.rotc(deg)
	Image.Current.show()

def rotx(deg):
	Image.Current.rotx(deg)
	Image.Current.show()

def roty(deg):
	Image.Current.roty(deg)
	Image.Current.show()

def rotz(deg):
	Image.Current.rotz(deg)
	Image.Current.show()


# ---------------------------------------------------------------------------
# These functions should be used to change the default values for new images
#
# ---------------------------------------------------------------------------

def set_default_framebuffer(f):
	Image.Default_framebuffer = f

def colormap(filename):
	c = ColorMap(filename)
	Image.Default_colormap = c

def init_framebuffer():
	if Image.Default_framebuffer == None:
		Image.Default_framebuffer = FrameBuffer(GRAPHICS_SIZE,GRAPHICS_SIZE)

