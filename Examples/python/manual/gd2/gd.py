# This file was created automatically by SWIG.
import gdc
class gdImagePtr :
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def __setattr__(self,name,value):
        if name == "pixels" :
            gdc.gdImage_pixels_set(self.this,value)
            return
        if name == "sx" :
            gdc.gdImage_sx_set(self.this,value)
            return
        if name == "sy" :
            gdc.gdImage_sy_set(self.this,value)
            return
        if name == "colorsTotal" :
            gdc.gdImage_colorsTotal_set(self.this,value)
            return
        if name == "red" :
            gdc.gdImage_red_set(self.this,value)
            return
        if name == "green" :
            gdc.gdImage_green_set(self.this,value)
            return
        if name == "blue" :
            gdc.gdImage_blue_set(self.this,value)
            return
        if name == "open" :
            gdc.gdImage_open_set(self.this,value)
            return
        if name == "transparent" :
            gdc.gdImage_transparent_set(self.this,value)
            return
        if name == "polyInts" :
            gdc.gdImage_polyInts_set(self.this,value)
            return
        if name == "polyAllocated" :
            gdc.gdImage_polyAllocated_set(self.this,value)
            return
        if name == "brush" :
            gdc.gdImage_brush_set(self.this,value)
            return
        if name == "tile" :
            gdc.gdImage_tile_set(self.this,value)
            return
        if name == "brushColorMap" :
            gdc.gdImage_brushColorMap_set(self.this,value)
            return
        if name == "tileColorMap" :
            gdc.gdImage_tileColorMap_set(self.this,value)
            return
        if name == "styleLength" :
            gdc.gdImage_styleLength_set(self.this,value)
            return
        if name == "stylePos" :
            gdc.gdImage_stylePos_set(self.this,value)
            return
        if name == "style" :
            gdc.gdImage_style_set(self.this,value)
            return
        if name == "interlace" :
            gdc.gdImage_interlace_set(self.this,value)
            return
        self.__dict__[name] = value
    def __getattr__(self,name):
        if name == "pixels" : 
            return gdc.gdImage_pixels_get(self.this)
        if name == "sx" : 
            return gdc.gdImage_sx_get(self.this)
        if name == "sy" : 
            return gdc.gdImage_sy_get(self.this)
        if name == "colorsTotal" : 
            return gdc.gdImage_colorsTotal_get(self.this)
        if name == "red" : 
            return gdc.gdImage_red_get(self.this)
        if name == "green" : 
            return gdc.gdImage_green_get(self.this)
        if name == "blue" : 
            return gdc.gdImage_blue_get(self.this)
        if name == "open" : 
            return gdc.gdImage_open_get(self.this)
        if name == "transparent" : 
            return gdc.gdImage_transparent_get(self.this)
        if name == "polyInts" : 
            return gdc.gdImage_polyInts_get(self.this)
        if name == "polyAllocated" : 
            return gdc.gdImage_polyAllocated_get(self.this)
        if name == "brush" : 
            return gdc.gdImage_brush_get(self.this)
        if name == "tile" : 
            return gdc.gdImage_tile_get(self.this)
        if name == "brushColorMap" : 
            return gdc.gdImage_brushColorMap_get(self.this)
        if name == "tileColorMap" : 
            return gdc.gdImage_tileColorMap_get(self.this)
        if name == "styleLength" : 
            return gdc.gdImage_styleLength_get(self.this)
        if name == "stylePos" : 
            return gdc.gdImage_stylePos_get(self.this)
        if name == "style" : 
            return gdc.gdImage_style_get(self.this)
        if name == "interlace" : 
            return gdc.gdImage_interlace_get(self.this)
        raise AttributeError,name
    def __repr__(self):
        return "<C gdImage instance>"
class gdImage(gdImagePtr):
    def __init__(self,this):
        self.this = this




class gdFontPtr :
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def __setattr__(self,name,value):
        if name == "nchars" :
            gdc.gdFont_nchars_set(self.this,value)
            return
        if name == "offset" :
            gdc.gdFont_offset_set(self.this,value)
            return
        if name == "w" :
            gdc.gdFont_w_set(self.this,value)
            return
        if name == "h" :
            gdc.gdFont_h_set(self.this,value)
            return
        if name == "data" :
            gdc.gdFont_data_set(self.this,value)
            return
        self.__dict__[name] = value
    def __getattr__(self,name):
        if name == "nchars" : 
            return gdc.gdFont_nchars_get(self.this)
        if name == "offset" : 
            return gdc.gdFont_offset_get(self.this)
        if name == "w" : 
            return gdc.gdFont_w_get(self.this)
        if name == "h" : 
            return gdc.gdFont_h_get(self.this)
        if name == "data" : 
            return gdc.gdFont_data_get(self.this)
        raise AttributeError,name
    def __repr__(self):
        return "<C gdFont instance>"
class gdFont(gdFontPtr):
    def __init__(self,this):
        self.this = this




class gdPointPtr :
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def __del__(self):
        if self.thisown == 1 :
            gdc.delete_gdPoint(self.this)
    def __getitem__(self,arg0):
        val = gdc.gdPoint___getitem__(self.this,arg0)
        val = gdPointPtr(val)
        return val
    def __setattr__(self,name,value):
        if name == "x" :
            gdc.gdPoint_x_set(self.this,value)
            return
        if name == "y" :
            gdc.gdPoint_y_set(self.this,value)
            return
        self.__dict__[name] = value
    def __getattr__(self,name):
        if name == "x" : 
            return gdc.gdPoint_x_get(self.this)
        if name == "y" : 
            return gdc.gdPoint_y_get(self.this)
        raise AttributeError,name
    def __repr__(self):
        return "<C gdPoint instance>"
class gdPoint(gdPointPtr):
    def __init__(self,arg0) :
        self.this = gdc.new_gdPoint(arg0)
        self.thisown = 1






#-------------- FUNCTION WRAPPERS ------------------

def gdImageCreate(arg0,arg1):
    val = gdc.gdImageCreate(arg0,arg1)
    val = gdImagePtr(val)
    return val

def gdImageCreateFromGif(arg0):
    val = gdc.gdImageCreateFromGif(arg0)
    val = gdImagePtr(val)
    return val

def gdImageCreateFromGd(arg0):
    val = gdc.gdImageCreateFromGd(arg0)
    val = gdImagePtr(val)
    return val

def gdImageCreateFromXbm(arg0):
    val = gdc.gdImageCreateFromXbm(arg0)
    val = gdImagePtr(val)
    return val

def gdImageDestroy(arg0):
    val = gdc.gdImageDestroy(arg0.this)
    return val

def gdImageSetPixel(arg0,arg1,arg2,arg3):
    val = gdc.gdImageSetPixel(arg0.this,arg1,arg2,arg3)
    return val

def gdImageGetPixel(arg0,arg1,arg2):
    val = gdc.gdImageGetPixel(arg0.this,arg1,arg2)
    return val

def gdImageLine(arg0,arg1,arg2,arg3,arg4,arg5):
    val = gdc.gdImageLine(arg0.this,arg1,arg2,arg3,arg4,arg5)
    return val

def gdImageDashedLine(arg0,arg1,arg2,arg3,arg4,arg5):
    val = gdc.gdImageDashedLine(arg0.this,arg1,arg2,arg3,arg4,arg5)
    return val

def gdImageRectangle(arg0,arg1,arg2,arg3,arg4,arg5):
    val = gdc.gdImageRectangle(arg0.this,arg1,arg2,arg3,arg4,arg5)
    return val

def gdImageFilledRectangle(arg0,arg1,arg2,arg3,arg4,arg5):
    val = gdc.gdImageFilledRectangle(arg0.this,arg1,arg2,arg3,arg4,arg5)
    return val

def gdImageBoundsSafe(arg0,arg1,arg2):
    val = gdc.gdImageBoundsSafe(arg0.this,arg1,arg2)
    return val

def gdImageChar(arg0,arg1,arg2,arg3,arg4,arg5):
    val = gdc.gdImageChar(arg0.this,arg1.this,arg2,arg3,arg4,arg5)
    return val

def gdImageCharUp(arg0,arg1,arg2,arg3,arg4,arg5):
    val = gdc.gdImageCharUp(arg0.this,arg1.this,arg2,arg3,arg4,arg5)
    return val

def gdImageString(arg0,arg1,arg2,arg3,arg4,arg5):
    val = gdc.gdImageString(arg0.this,arg1.this,arg2,arg3,arg4,arg5)
    return val

def gdImageStringUp(arg0,arg1,arg2,arg3,arg4,arg5):
    val = gdc.gdImageStringUp(arg0.this,arg1.this,arg2,arg3,arg4,arg5)
    return val

def gdImagePolygon(arg0,arg1,arg2,arg3):
    val = gdc.gdImagePolygon(arg0.this,arg1.this,arg2,arg3)
    return val

def gdImageFilledPolygon(arg0,arg1,arg2,arg3):
    val = gdc.gdImageFilledPolygon(arg0.this,arg1.this,arg2,arg3)
    return val

def gdImageColorAllocate(arg0,arg1,arg2,arg3):
    val = gdc.gdImageColorAllocate(arg0.this,arg1,arg2,arg3)
    return val

def gdImageColorClosest(arg0,arg1,arg2,arg3):
    val = gdc.gdImageColorClosest(arg0.this,arg1,arg2,arg3)
    return val

def gdImageColorExact(arg0,arg1,arg2,arg3):
    val = gdc.gdImageColorExact(arg0.this,arg1,arg2,arg3)
    return val

def gdImageColorDeallocate(arg0,arg1):
    val = gdc.gdImageColorDeallocate(arg0.this,arg1)
    return val

def gdImageColorTransparent(arg0,arg1):
    val = gdc.gdImageColorTransparent(arg0.this,arg1)
    return val

def gdImageGif(arg0,arg1):
    val = gdc.gdImageGif(arg0.this,arg1)
    return val

def gdImageGd(arg0,arg1):
    val = gdc.gdImageGd(arg0.this,arg1)
    return val

def gdImageArc(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7):
    val = gdc.gdImageArc(arg0.this,arg1,arg2,arg3,arg4,arg5,arg6,arg7)
    return val

def gdImageFillToBorder(arg0,arg1,arg2,arg3,arg4):
    val = gdc.gdImageFillToBorder(arg0.this,arg1,arg2,arg3,arg4)
    return val

def gdImageFill(arg0,arg1,arg2,arg3):
    val = gdc.gdImageFill(arg0.this,arg1,arg2,arg3)
    return val

def gdImageCopy(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7):
    val = gdc.gdImageCopy(arg0.this,arg1.this,arg2,arg3,arg4,arg5,arg6,arg7)
    return val

def gdImageCopyResized(arg0,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9):
    val = gdc.gdImageCopyResized(arg0.this,arg1.this,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9)
    return val

def gdImageSetBrush(arg0,arg1):
    val = gdc.gdImageSetBrush(arg0.this,arg1.this)
    return val

def gdImageSetTile(arg0,arg1):
    val = gdc.gdImageSetTile(arg0.this,arg1.this)
    return val

def gdImageSetStyle(arg0,arg1,arg2):
    val = gdc.gdImageSetStyle(arg0.this,arg1,arg2)
    return val

def gdImageInterlace(arg0,arg1):
    val = gdc.gdImageInterlace(arg0.this,arg1)
    return val

fopen = gdc.fopen

fclose = gdc.fclose



#-------------- VARIABLE WRAPPERS ------------------

GD_H = gdc.GD_H
gdMaxColors = gdc.gdMaxColors
gdDashSize = gdc.gdDashSize
gdStyled = gdc.gdStyled
gdBrushed = gdc.gdBrushed
gdStyledBrushed = gdc.gdStyledBrushed
gdTiled = gdc.gdTiled
gdTransparent = gdc.gdTransparent
