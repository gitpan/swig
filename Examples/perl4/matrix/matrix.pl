#!matrix
# Perl4 script file for testing out matrix operations.

sub zero {
    local($M) = @_;
    local($i) = 0;
    local($j) = 0;
    for ($i = 0; $i < 4; $i++) {
	for ($j = 0; $j < 4; $j++) {
	    &set_m($M,$i,$j,0.0);
	}
    }
}

sub identity {
    local($M) = @_;
    local($i) = 0;
    local($j) = 0;
    &zero($M);
    for ($i = 0; $i < 4; $i++) {
	for ($j = 0; $j < 4; $j++) {
	    &set_m($M,$i,$i,1.0);
	}
    }
}

# Rotate around x axis

sub rotx {
    local($M,$r) = @_;
    local($temp) = &new_matrix();
    local($rd) = $r*3.14159/180.0;
    &zero($temp);
    &set_m($temp,0,0,1.0);
    &set_m($temp,1,1,cos($rd));
    &set_m($temp,1,2,-sin($rd));
    &set_m($temp,2,1, sin($rd));
    &set_m($temp,2,2, cos($rd));
    &set_m($temp,3,3,1.0);
    &mat_mult($M,$temp,$M);
    &destroy_matrix($temp);
}

# Rotate around y axis

sub roty {
    local($M,$r) = @_;
    local($temp) = &new_matrix();
    local($rd) = $r*3.14159/180.0;
    &zero($temp);
    &set_m($temp,1,1,1.0);
    &set_m($temp,0,0, cos($rd));
    &set_m($temp,0,2, sin($rd));
    &set_m($temp,2,0, -sin($rd));
    &set_m($temp,2,2, cos($rd));
    &set_m($temp,3,3,1.0);
    &mat_mult($M,$temp,$M);
    &destroy_matrix($temp);
}

# Rotate around z axis

sub rotz {
    local($M,$r) = @_;
    local($temp) = &new_matrix();
    local($rd) = $r*3.14159/180.0;
    &zero($temp);
    &set_m($temp,0,0,cos($rd));
    &set_m($temp,0,1,-sin($rd));
    &set_m($temp,1,0,sin($rd));
    &set_m($temp,1,1,cos($rd));
    &set_m($temp,2,2,1.0);
    &set_m($temp,3,3, 1.0);
    &mat_mult($M,$temp,$M);
    &destroy_matrix($temp);
}

sub scale {
    local($M,$s) = @_;
    local($temp) = &new_matrix();
    local($i) = 0;
    &zero($temp);
    for ($i = 0; $i < 4; $i++) {
	&set_m($temp,$i,$i,$s);
    }
    &mat_mult($M,$temp,$M);
    &destroy_matrix($temp);
}

sub randmat {
    local($M) = @_;
    local($i) = 0;
    local($j) = 0;
    for ($i = 0; $i < 4; $i++) {
	for ($j = 0; $j < 4; $j++) {
	    &set_m($M,$i,$j,&drand48());
	}
    }
}

# Now we'll hammer on things a little bit just to make
# sure everything works.

print "Testing matrix program...\n";

$M1=&new_matrix();
&identity($M1);
&print_matrix($M1);
print "Rotate x 45 degrees\n";
&rotx($M1,45);
&print_matrix($M1);
print "Rotate y 30 degrees\n";
&roty($M1,30);
&print_matrix($M1);
print "Rotate z 15 degrees\n";
&rotz($M1,15);
&print_matrix($M1);
print "Scale 0.5\n";
&scale($M1,0.5);
&print_matrix($M1);

# Create a vector

$v= &createv(1,2,3,4);
print "Created vector (1,2,3,4)\n";
$t = &createv(0,0,0,0);

# Rotating ...
print "Rotating...\n";
for ($i = 0; $i < 360; $i++) {
    &rotx($M1,1);
    &rotz($M1,-0.5);
    &transform($M1,$v,$t);
}

&printv($t);

print "\nCreating 2000 matrices\n";

@M_list = ();
for ($i = 0; $i < 2000; $i++) {
    $M = &new_matrix();
    &randmat($M);
    push(@M_list,$M);
}

print "Adding them together (in Perl)\n";
&zero($M1);
foreach $m (@M_list) {
    for ($i = 0; $i < 4; $i++) {
	for ($j = 0; $j < 4; $j++) {
	    &set_m($M1,$i,$j, &get_m($m,$i,$j) + &get_m($M1,$i,$j));
	}
    }
}

&print_matrix($M1);

print "Doing 2000 multiplications (mostly in C)\n";
$M=&new_matrix();
&randmat($M);
foreach $m (@M_list) {
    &mat_mult($M1,$m,$M1);
}

print "Cleaning up\n";
foreach $m (@M_list) {
    &destroy_matrix($m);
}




