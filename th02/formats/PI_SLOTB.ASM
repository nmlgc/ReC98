; Global PI file slots.

; void far *pi_slot_buffers[6]
public _pi_slot_buffers
_pi_slot_buffers	dd 6 dup(?)
; PiHeader pi_slot_headers[6]
public _pi_slot_headers
_pi_slot_headers	PiHeader 6 dup(<?>)
