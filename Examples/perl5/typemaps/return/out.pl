# Tcl script showing some output arguments
use retval;
package retval;
$a = double_array(1);

# Power function with a status value
# Note : Returning two values so we need to use arrays

@r = mypow(2,3);
print "pow(2,3) = @r\n";
@r = mypow(-1,3);
print "pow(-1,3) = @r\n";

# Some output functions

@r = multout(7,13);
print "multout(7,13) = @r\n";
@r = multout1(7,13,$a);
print "multout1(7,13) = @r\n";
@r = multout2(7,13,$a,$a);
print "multout2(7,13) = @r\n";


# Test for memory leaks, monitor with top or ps -u
#
#for ($i = 0; $i < 1000000; $i++) {
#    @r = multout(7,13);
#}

