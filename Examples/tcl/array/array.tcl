# A mildly amusing array example that turns C pointers into Tcl "objects"

catch { load ./array.so }
catch { load ./array.dll }

proc Array {type size} {
    set ptr [new_$type $size]
    set code {
	set method [lindex $args 0] 
	set parms [concat $ptr [lrange $args 1 end]] 
	switch $method { 
	    get {return [eval "get_$type $parms"]} 
	    set {return [eval "set_$type $parms"]} 
	    delete {eval "delete_$type $ptr; rename $ptr {}"}
	}
    }
    uplevel "proc $ptr args {set ptr $ptr; set type $type;$code}"
    return $ptr
}

proc ClearArray {array size value} {
    for {set i 0} {$i < $size} {incr i 1} {
	$array set $i $value
    }
}

