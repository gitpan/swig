proc display {c f cmap} {
    p3 clear 0
    make_plot [p3 cget -this] 40
    $f writeGIF [$cmap cget -this] "image.gif"
    catch { image delete myimage }
    set i [image create photo myimage -file image.gif ]
    $c create image 0 0 -image $i -anchor nw -tags image
}

set cmap [ColorMap -args cm15]
set f [FrameBuffer -args 400 400]

Plot3D p3 $f -10 -10 -10 10 10 10
p3 lookat 20
p3 autoperspective 40

frame .t 
frame .b

label .t.l -text "Test"
canvas .b.c -width 500 -height 500
pack .t.l

frame .b.buttons
button .b.buttons.clear -text "Clear" -command {$f clear 0}
button .b.buttons.display -text "Display" -command {.b.c delete tag image; display .b.c $f $cmap}
button .b.buttons.rotr -text "Right" -command {p3 rotr 30; display .b.c $f $cmap}
button .b.buttons.rotl -text "Left" -command {p3 rotl 30; display .b.c $f $cmap}
button .b.buttons.rotd -text "Down" -command {p3 rotd 30; display .b.c $f $cmap}
button .b.buttons.rotu -text "Up" -command {p3 rotu 30; display .b.c $f $cmap}
button .b.buttons.zoomi -text "Zoom in" -command {p3 zoom 150; display .b.c $f $cmap}
button .b.buttons.zoomo -text "Zoom out" -command {p3 zoom 66; display .b.c $f $cmap}
button .b.buttons.quit -text "Quit" -command {exit}

pack .b.buttons.clear .b.buttons.display .b.buttons.rotr .b.buttons.rotl .b.buttons.rotd .b.buttons.rotu .b.buttons.zoomi .b.buttons.zoomo .b.buttons.quit -side top -fill x
pack .b.buttons .b.c -side left -fill y

pack .t .b
display .b.c $f $cmap

