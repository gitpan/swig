# A frame, scrollbar, and text
frame .eval
set _t [text .eval.t -width 40 -height 15 -yscrollcommand {.eval.s set}]
scrollbar .eval.s -command {.eval.t yview}
pack .eval.s -side left -fill y
pack .eval.t -side right -fill both -expand true
pack .eval -fill both -expand true

# Insert the prompt and initialize the limit mark
.eval.t insert insert "Tcl eval log\n"
set prompt "tcl> "
.eval.t insert insert $prompt
.eval.t mark set limit insert
.eval.t mark gravity limit left
focus .eval.t

# Keybindings that limit input and eval things
bind .eval.t <Return> { _Eval .eval.t ; break }
bind .eval.t <Any-Key> {
	if [%W compare insert < limit] {
		%W mark set insert end
	}
}
bindtags .eval.t {.eval.t Text all}

proc _Eval { t } {
	global prompt
	set command [$t get limit end]
	if [info complete $command] {
		$t insert insert \n
		set err [catch {uplevel #0 $command} result]
		if {[string length $result] > 0} {
		    $t insert insert $result\n
		}
		$t insert insert $prompt
		$t see insert
		$t mark set limit insert
		return
	} else {
		$t insert insert \n
	}
}
proc puts {args} {
    if {[string match -nonewline* $args]} {
	set args [lrange $args 1 end]
	set nonewline 1
    }
    .eval.t insert end [lindex $args end]	;# Ignore file specifier
    if ![info exists nonewline] {
	.eval.t insert end \n
    }
}
