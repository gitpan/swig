# ------------------------------------------------------------------
# Simple Mathematical Function Plotter
#
# Plots mathematical functions and makes GIF images.
# Primarily intended to be an interesting example, not a full
# fledged package.
# ------------------------------------------------------------------

load ./gifplot.sl
source plot2d.tcl
source display.tcl

# Create a framebuffer and plot

set f [FrameBuffer -args 400 400]
set cmap [ColorMap -args "cmap"]
set p2 [Plot2D -args $f -6.3 -2 6.3 2]
set xmin -6.3
set xmax 6.3
set ymin -2.0
set ymax 2.0
set xtick 3.1415926
set ytick 0.5
set title Plot
set xaxis_label X
set yaxis_label Y
set symbol NULL
set npoints 100
set color $YELLOW
set func "sin(x)"
set imageno 0
set filename plot0.gif
set autoinc 1

# Make a plot from the above parms

proc make_plot {} {
    global p2 xtick ytick title xaxis_label yaxis_label color symbol func npoints filename cmap
    global xmin ymin xmax ymax imageno autoinc

    $p2 setrange $xmin $ymin $xmax $ymax
    newplot $p2 $xtick $ytick $title $xaxis_label $yaxis_label
    plotfunc $p2 $func $npoints $color $symbol
    [$p2 cget -frame] writeGIF $cmap $filename
    display_image $filename $p2 set_zoom
    if {$autoinc == 1} {
	incr imageno 1
	set filename plot$imageno.gif
    }
}

# Create a few frames

frame .title -relief groove -borderwidth 1
label .title.name -text "GIF Function Plotter (2D)" 
button .title.quit -text "Quit" -command "exit"
button .title.about -text "About" -command "about"
pack .title.name -side left
pack .title.quit .title.about -side right

frame .func -relief groove -borderwidth 1
frame .func.f
label .func.f.flabel -text "Function" -width 12
entry .func.f.func -textvar func -width 45
pack .func.f.flabel .func.f.func -side left

frame .func.xrange
label .func.xrange.xrlabel -text "X range" -width 12
entry .func.xrange.xmin -textvar xmin -width 8
label .func.xrange.xtolabel -text "to"
entry .func.xrange.xmax -textvar xmax -width 8
pack  .func.xrange.xrlabel .func.xrange.xmin .func.xrange.xtolabel .func.xrange.xmax -side left

label .func.xrange.xtickl -text "Tickmarks "
entry .func.xrange.xtick -textvar xtick -width 10
pack .func.xrange.xtick .func.xrange.xtickl -side right

frame .func.yrange
label .func.yrange.yrlabel -text "Y range" -width 12
entry .func.yrange.ymin -textvar ymin -width 8
label .func.yrange.ytolabel -text "to"
entry .func.yrange.ymax -textvar ymax -width 8
pack  .func.yrange.yrlabel .func.yrange.ymin .func.yrange.ytolabel .func.yrange.ymax -side left

label .func.yrange.ytickl -text "Tickmarks "
entry .func.yrange.ytick -textvar ytick -width 10
pack .func.yrange.ytick .func.yrange.ytickl -side right

frame .func.npoints 
label .func.npoints.label -text "N Points " -width 12
entry .func.npoints.npoints -textvar npoints -width 8
pack .func.npoints.label .func.npoints.npoints -side left

pack .func.f .func.xrange .func.yrange .func.npoints -side top -fill x

frame .appear -relief groove -borderwidth 1

# Appearance (labels )

frame .appear.text 
frame .appear.text.title 
label .appear.text.title.label -text "Title" -width 12 
entry .appear.text.title.title -textvar title -width 20
pack .appear.text.title.label .appear.text.title.title -side left

frame .appear.text.xlabel
label .appear.text.xlabel.label -text "X Axis Label" -width 12
entry .appear.text.xlabel.title -textvar xaxis_label -width 20
pack .appear.text.xlabel.label .appear.text.xlabel.title -side left

frame .appear.text.ylabel
label .appear.text.ylabel.label -text "Y Axis Label" -width 12
entry .appear.text.ylabel.title -textvar yaxis_label -width 20
pack .appear.text.ylabel.label .appear.text.ylabel.title -side left

pack .appear.text.title .appear.text.xlabel .appear.text.ylabel -side top -fill x

# Appearance (symbols)

frame .appear.symbol
label .appear.symbol.label -text "Symbol"
radiobutton .appear.symbol.none -text "None" -value NULL -variable symbol -anchor w
radiobutton .appear.symbol.square -text "Square" -value $SQUARE -variable symbol -anchor w
radiobutton .appear.symbol.triangle -text "Triangle" -value $TRIANGLE -variable symbol -anchor w
radiobutton .appear.symbol.cross -text "Cross" -value $CROSS -variable symbol -anchor w
pack .appear.symbol.label .appear.symbol.none .appear.symbol.square .appear.symbol.triangle .appear.symbol.cross -side top -fill x

pack .appear.text .appear.symbol -side left -fill x -anchor n

# Filename dialog

frame .save -relief groove -borderwidth 1

frame .save.file
label .save.file.label -text "Save as" -width 12
entry .save.file.filename -textvar filename -width 20
pack .save.file.label .save.file.filename -side left
checkbutton .save.file.auto -text "Auto increment" -variable autoinc -anchor w
pack .save.file.auto -side left
pack .save.file -side top -fill x
button .save.go -text "Plot" -command "make_plot"
pack .save.go -side right

bind .save.file.filename <Return> {make_plot}

pack .title .func .appear .save -side top -fill both

proc about { } {
    toplevel .about -width 350

    message .about.m -text "\
GIF Function Plotter\n\n\
Copyright (c) 1997\n\
Dave Beazley\n\
University of Utah\n\n\
Creates simple 2D plots in the form of GIF files.  Simply enter \
a mathematical expression in 'x' and press 'Plot' to make an image.  Images \
can be zoomed by clicking in the displayed image and dragging.\n\n\
Disclaimer : This is not intended to be a full-fledged plotting package.\n" -justify left


button .about.okay -text "Ok" -command {destroy .about}

pack .about.m .about.okay -side top
focus .about.okay
}





    
