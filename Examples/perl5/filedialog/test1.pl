use FileSelect;
package FileSelect;

local(%my_filter) = ( "C/C++ Files (*.c;*.cpp)" => "*.c;*.cpp",
                      "H Files (*.h;*.hpp)"     => "*.h;*.hpp" );

$res = FileSelection("Select Source File",
                     "",
                     "d:\\dev50\\cf\\include\\",
		   				\%my_filter);
if($res eq "") {
	print "You did not select a file\n";
} else {
	print "You selected $res\n";
}

