# Plot a 3D function
use gifplot;
package gifplot;

sub func {
    my ($x,$y) = @_;
    return sin($x)*cos($y);
}

sub plotmesh {
    my ($p3,$nx,$ny) = @_;
    my $min = $p3->{zmin};
    my $max = $p3->{zmax};
    my $dx = ($p3->{xmax}-$p3->{xmin})/$nx;
    my $dy = ($p3->{ymax}-$p3->{ymin})/$ny;
    my $cscale = 240.0/($max-$min);
    my $x = $p3->{xmin};
    for ($i = 0; $i < $nx; $i++) {
	my $y = $p3->{ymin};
	for ($j = 0; $j < $ny; $j++) {
	    my $z1 = func($x,$y);
	    my $z2 = func($x+$dx,$y);
	    my $z3 = func($x+$dx,$y+$dy);
	    my $z4 = func($x,$y+$dy);
	    my $c1 = $cscale*($z1-$min);
	    my $c2 = $cscale*($z2-$min);
	    my $c3 = $cscale*($z3-$min);
	    my $c4 = $cscale*($z4-$min);
	    my $c = int (($c1+$c2+$c3+$c4)/4.0);
	    if ($c < 0) { $c = 0; }
	    if ($c > 239) { $c = 239; }
	    $c = $c + 16;
	    $p3->solidquad($x,$y,$z1,$x+$dx,$y,$z2,$x+$dx,$y+$dy,$z3,$x,$y+$dy,$z4,$c);
	    $y = $y + $dy;
	}
	$x = $x + $dx;
    }
}

$f = new FrameBuffer(500,500);
$cm = new ColorMap("cmap");
$p3 = new Plot3D($f,-5,-5,-2,5,5,2);
$p3->lookat(20);
$p3->autoperspective(40);
$p3->clear($BLACK);
$p3->rotu(60);
$p3->rotr(30);
$p3->rotd(10);
$p3->start();
plotmesh($p3,50,50);

$f->writeGIF($cm,"plot3d.gif");

print "Image written to 'plot3d.gif'\n";

