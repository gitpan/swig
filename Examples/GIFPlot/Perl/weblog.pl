# Plot web-hits
use gifplot;
package gifplot;

sub webhits {
    my ($p3,$file) = @_;
    my @hits;
    for ($i = 0; $i < 32; $i++) {
	$hits[$i] = [];
	for ($j = 0; $j < 24; $j++) {
	    $hits[$i][$j] = 0;
	}
    }
    open(FILE,$file);
    while (<FILE>) {
	my @fields = split(/\s+/, $_);
	next if ($fields[8] != 200);
	my @datetime = split(/\[|\/|:/, $fields[3]);
	my $day = $datetime[1];
	my $time = $datetime[4];
	$hits[$day][$time]++;
    }
    my $max = 0;
    for ($i = 0; $i < 32; $i++) {
	for ($j = 0; $j < 24; $j++) {
	    if ($hits[$i][$j] > $max) { $max = $hits[$i][$j]; }
	}
    }
    my $zscale = 239.0/$max;
    my $zscale2 = 10.0/$max;
    for ($i = 0; $i < 32; $i++) {
	for ($j = 0; $j < 24; $j++) {
	    my $z1 = $hits[$i][$j];
	    my $z2 = $hits[$i+1][$j];
	    my $z3 = $hits[$i+1][$j+1];
	    my $z4 = $hits[$i][$j+1];
	    my $c1 = int ($z1*$zscale + 16);
	    my $c2 = int ($z2*$zscale + 16);
	    my $c3 = int ($z3*$zscale + 16);
	    my $c4 = int ($z4*$zscale + 16);
	    $p3->interpquad($i,$j,$z1*$zscale2,$c1,$i+1,$j,$z2*$zscale2,$c2,
                            $i+1,$j+1,$z3*$zscale2,$c3, $i,$j+1,$z4*$zscale2, $c4);
	}
    }
}

$f = new FrameBuffer(500,500);
$cm = new ColorMap("cmap");
$p3 = new Plot3D($f,0,0,0,32,24,10);
$p3->lookat(40);
$p3->autoperspective(40);
$p3->clear($BLACK);
$p3->rotu(60);
$p3->rotr(30);
$p3->rotd(10);
$p3->zoom(80);
$p3->up(20);
$p3->right(3);
$p3->start();
webhits($p3,"../Data/logs.9604");

$f->writeGIF($cm,"hits.gif");

print "Image written to 'hits.gif'\n";
