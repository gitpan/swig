use FileSelect;
package FileSelect;

$res = FileSelection("Open Perl File",
                     "*.pl",
                     "z:\\joshaugh\\temp");
if($res eq "") {
	print "You did not select a file\n";
} else {
	print "You selected $res\n";
}

local(%my_filter) = ( "C Files (*.c)" => "*.c",
							 "H Files (*.h)" => "*.h" );

$res = FileSelection("Select Header Files",
                     "*.h",
                     "d:\\dev50\\cf\\include\\",
		   				\%my_filter,
                     $OFN_LONGNAMES | $OFN_ALLOWMULTISELECT);
if($res eq "") {
	print "You did not select a file\n";
} else {
	print "You selected $res\n";
}


