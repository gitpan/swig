use db;

open(FILE,"/etc/passwd");
while (<FILE>) {
    @fields = split(":");
  db::add_user([$fields[0],$fields[2],$fields[3],$fields[4],$fields[5]]);
}
close FILE;

db::sort_users();

sub print_user {
    print "$_[0] $_[1] $_[2] $_[3] $_[4]\n";
}

print "\nLooking for root\n";
print_user(@{db::lookup_user("root")});

print "\nLooking for beazley\n";
print_user(@{db::lookup_user("beazley")});

# print out all users

print "\nAll users\n";
for ($i = 0; $i < db::num_users(); $i++) {
    print_user(@{db::get_user($i)});
}


