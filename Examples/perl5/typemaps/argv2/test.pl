use argv;
@a = ("Dave", "Mike", "John", "Mary");
print @a,"\n";
argv::print_args(\@a);

print argv::get_args(),"\n";


