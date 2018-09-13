; The key state is checked twice, 614.4 µs apart, to ignore the momentary "key
; released" events sent by PC-98 keyboards at the typematic rate if a key is
; held down. This ensures that the game consistently sees that specific input
; being pressed. See the HOLDKEY example in the Research/ subdirectory for
; more explanation and sample code showing off this effect.
;
; int input_reset_sense_held();
_input_reset_sense_held	proc far
	call	_input_reset_sense
	mov	cx, 1024

@@wait:
	out	5Fh, al
	loop	@@wait
	call	_input_sense
	retf
_input_reset_sense_held	endp
