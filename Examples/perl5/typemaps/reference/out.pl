use output;
package output;

$result = 3;
add(3,4.5,\$result);
print "$result\n";
mul(0.1,79,\$result);
print "$result\n";
$result = 9;
neg(\$result);
print "$result\n";

$a = 0;
$b = 0;
factor(32,\$a,\$b);
print "$a,$b\n";

