use argv;
@a = ("Dave", "Mike", "John", "Mary");
print @a,"\n";
argv::print_args(\@a);

$b = argv::get_args();       # This returns a reference to an array

print @$b,"\n";

$f = new Foo;
$f->output(\@a);



