
use ignore;
print "\nShould get 2, 3, -1\n";
ignore::omit_last(2,3);

print "\nShould get -1, 3, 4\n";
ignore::omit_first(3,4);

print "\nShould get 1, 4, -1, 5\n";
ignore::omit_opt(1);

$f = new Foo;

print "\nShould get 10, 11, -1\n";
$f->omit_last(10,11);

print "\nShould get -1, 11, 12\n";
$f->omit_first(11,12);

print "\nShould get 10, 4, -1, 5\n";
$f->omit_opt(10);
