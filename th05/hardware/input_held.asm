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
