use fileout;

# Open up a Perl file
open(COUNT,">count.out");
print COUNT "Count from 1 to 100\n";

# Now call into a C function, but pass the Perl COUNT filehandle
# (which semi-magically shows up as a C FILE *).

fileout::print_count(COUNT,100);
close(COUNT);

print "Output written to 'count.out'\n";

