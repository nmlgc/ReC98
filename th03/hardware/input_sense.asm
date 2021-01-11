include pc98kbd.inc

; The key state is checked twice, 614.4 µs apart, to ignore the momentary "key
; released" events sent by PC-98 keyboards at the typematic rate if a key is
; held down. This ensures that the game consistently sees that specific input
; being pressed. See the HOLDKEY example in the Research/ subdirectory for
; more explanation and sample code showing off this effect.

public _input_reset_sense_key_held
_input_reset_sense_key_held	proc far
	xor	ax, ax
	mov	_input_mp_p1, ax
	mov	_input_mp_p2, ax
	mov	_input_sp, ax
	mov	js_stat, ax
	jmp	short $+2
	mov	bl, 2
	xor	ax, ax
	mov	es, ax

@@up?:
	mov	ah, byte ptr es:[KEYGROUP_7]
	test	ah, 4
	jz	short @@down?
	or	_input_sp, INPUT_UP

@@down?:
	test	ah, 20h
	jz	short @@left?
	or	_input_sp, INPUT_DOWN

@@left?:
	test	ah, 8
	jz	short @@right?
	or	_input_mp_p2, INPUT_SHOT
	or	_input_sp, INPUT_LEFT

@@right?:
	test	ah, 10h
	jz	short @@num6?
	or	_input_mp_p2, INPUT_BOMB
	or	_input_sp, INPUT_RIGHT

@@num6?:
	mov	ah, byte ptr es:[KEYGROUP_9]
	test	ah, 1
	jz	short @@num1?
	or	_input_mp_p2, INPUT_RIGHT
	or	_input_sp, INPUT_RIGHT

@@num1?:
	test	ah, 4
	jz	short @@num2?
	or	_input_mp_p2, INPUT_DOWN_LEFT
	or	_input_sp, INPUT_DOWN_LEFT

@@num2?:
	test	ah, 8
	jz	short @@num3?
	or	_input_mp_p2, INPUT_DOWN
	or	_input_sp, INPUT_DOWN

@@num3?:
	test	ah, 10h
	jz	short @@num4?
	or	_input_mp_p2, INPUT_DOWN_RIGHT
	or	_input_sp, INPUT_DOWN_RIGHT

@@num4?:
	mov	ah, byte ptr es:[KEYGROUP_8]
	test	ah, 40h
	jz	short @@num7?
	or	_input_mp_p2, INPUT_LEFT
	or	_input_sp, INPUT_LEFT

@@num7?:
	test	ah, 4
	jz	short @@num8?
	or	_input_mp_p2, INPUT_UP_LEFT
	or	_input_sp, INPUT_UP_LEFT

@@num8?:
	test	ah, 8
	jz	short @@num9?
	or	_input_mp_p2, INPUT_UP
	or	_input_sp, INPUT_UP

@@num9?:
	test	ah, 10h
	jz	short @@z?
	or	_input_mp_p2, INPUT_UP_RIGHT
	or	_input_sp, INPUT_UP_RIGHT

@@z?:
	mov	ah, byte ptr es:[KEYGROUP_5]
	test	ah, 2
	jz	short @@x?
	or	_input_mp_p1, INPUT_SHOT
	or	_input_sp, INPUT_SHOT

@@x?:
	test	ah, 4
	jz	short @@v?
	or	_input_mp_p1, INPUT_BOMB
	or	_input_sp, INPUT_BOMB

@@v?:
	test	ah, 10h
	jz	short @@b?
	or	_input_mp_p1, INPUT_DOWN_LEFT

@@b?:
	test	ah, 20h
	jz	short @@n?
	or	_input_mp_p1, INPUT_DOWN

@@n?:
	test	ah, 40h
	jz	short @@f?
	or	_input_mp_p1, INPUT_DOWN_RIGHT

@@f?:
	mov	ah, byte ptr es:[KEYGROUP_4]
	test	ah, 1
	jz	short @@h?
	or	_input_mp_p1, INPUT_LEFT

@@h?:
	test	ah, 4
	jz	short @@r?
	or	_input_mp_p1, INPUT_RIGHT

@@r?:
	mov	ah, byte ptr es:[KEYGROUP_2]
	test	ah, 8
	jz	short @@t?
	or	_input_mp_p1, INPUT_UP_LEFT

@@t?:
	test	ah, 10h
	jz	short @@y?
	or	_input_mp_p1, INPUT_UP

@@y?:
	test	ah, 20h
	jz	short @@q?
	or	_input_mp_p1, INPUT_UP_RIGHT

@@q?:
	test	ah, 1
	jz	short @@esc?
	or	_input_sp, INPUT_Q

@@esc?:
	mov	ah, byte ptr es:[KEYGROUP_0]
	test	ah, 1
	jz	short @@return?
	or	_input_sp, INPUT_CANCEL

@@return?:
	mov	ah, byte ptr es:[KEYGROUP_3]
	test	ah, 10h
	jz	short @@space?
	or	_input_sp, INPUT_OK

@@space?:
	mov	ah, byte ptr es:[KEYGROUP_6]
	test	ah, 10h
	jz	short @@wait?
	or	_input_sp, INPUT_SHOT

@@wait?:
	dec	bl
	jz	short @@ret
	mov	cx, 1024

@@wait:
	out	5Fh, al
	loop	@@wait
	jmp	@@up?

@@ret:
	retf
_input_reset_sense_key_held	endp
