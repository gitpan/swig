# Plot a 3D function
use gifplot;
package gifplot;

# Make a big ball

sub ball {
    my ($p3,$dtheta,$dphi,$r) = @_;
    my $drtheta = $dtheta*3.14159/180.0;
    my $drphi = $dphi*3.14159/180.0;
    my $theta = 0;
    while ($theta < 360) {
	my $phi = -90.0;
	my $rtheta = $theta*3.14159/180.0;
	while ($phi < 90) {
	    my $rphi = $phi*3.14159/180.0;
	    my $x1 = $r*cos($rtheta)*cos($rphi);
	    my $y1 = $r*sin($rtheta)*cos($rphi);
	    my $x2 = $r*cos($rtheta+$drtheta)*cos($rphi);
	    my $y2 = $r*sin($rtheta+$drtheta)*cos($rphi);
	    my $x3 = $r*cos($rtheta+$drtheta)*cos($rphi+$drphi);
	    my $y3 = $r*sin($rtheta+$drtheta)*cos($rphi+$drphi);
	    my $x4 = $r*cos($rtheta)*cos($rphi+$drphi);
	    my $y4 = $r*sin($rtheta)*cos($rphi+$drphi);
	    my $z1 = $r*sin($rphi);
	    my $z2 = $r*sin($rphi+$drphi);
	    my $c = int ((($z1+$r)/(2*$r))*128 + 64);
	    $p3->solidquad($x1,$y1,$z1,$x2,$y2,$z1,$x3,$y3,$z2,$x4,$y4,$z2,$c);
	    $p3->quad($x1,$y1,$z1,$x2,$y2,$z1,$x3,$y3,$z2,$x4,$y4,$z2,$BLACK);
	    $phi = $phi+$dphi;
	}
	$theta = $theta + $dtheta;
    }
}

$f = new FrameBuffer(500,500);
$cm = new ColorMap("cmap");
$p3 = new Plot3D($f,-10,-10,-10,10,10,10);
$p3->lookat(40);
$p3->autoperspective(40);
$p3->clear($BLACK);
$p3->rotu(60);
$p3->rotr(30);
$p3->rotd(10);
$p3->start();
ball($p3,10,10,10);

$f->writeGIF($cm,"ball.gif");

print "Image written to 'ball.gif'\n";


