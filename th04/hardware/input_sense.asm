; TH05 insists on only updating the affected byte, so...
if GAME eq 4
	OR_INPUT_LOW macro value
		or	_key_det, value
	endm
	OR_INPUT_HIGH macro value
		or	_key_det, value
	endm
else
	OR_INPUT_LOW macro value
		or	_key_det.lo, low value
	endm
	OR_INPUT_HIGH macro value
		or	_key_det.hi, high value
	endm
endif

; Resets, updates, and (for TH05) returns the global input state.
;
; TH04: void input_reset_sense();
; TH05:  int input_reset_sense();
_input_reset_sense	label proc
	xor	ax, ax
	mov	_key_det, ax
	mov	js_stat, ax

; Updates the global input state with the current keyboard and joystick state,
; and (for TH05) returns the new one.
;
; TH04: void input_sense();
; TH05:  int input_sense();
_input_sense	proc far
	xor	ax, ax
	mov	es, ax
	mov	ah, byte ptr es:[531h]
	test	ah, 4
	jz	short @@down?
	OR_INPUT_LOW	INPUT_UP

@@down?:
	test	ah, 20h
	jz	short @@left?
	OR_INPUT_LOW	INPUT_DOWN

@@left?:
	test	ah, 8
	jz	short @@right?
	OR_INPUT_LOW	INPUT_LEFT

@@right?:
	test	ah, 10h
	jz	short @@num6?
	OR_INPUT_LOW	INPUT_RIGHT

@@num6?:
	mov	ah, byte ptr es:[533h]
	test	ah, 1
	jz	short @@num1?
	OR_INPUT_LOW	INPUT_RIGHT

@@num1?:
	test	ah, 4
	jz	short @@num2?
	OR_INPUT_HIGH	INPUT_DOWN_LEFT

@@num2?:
	test	ah, 8
	jz	short @@num3?
	OR_INPUT_LOW	INPUT_DOWN

@@num3?:
	test	ah, 10h
	jz	short @@num4?
	OR_INPUT_HIGH	INPUT_DOWN_RIGHT

@@num4?:
	mov	ah, byte ptr es:[532h]
	test	ah, 40h
	jz	short @@num7?
	OR_INPUT_LOW	INPUT_LEFT

@@num7?:
	test	ah, 4
	jz	short @@num8?
	OR_INPUT_HIGH	INPUT_UP_LEFT

@@num8?:
	test	ah, 8
	jz	short @@num9?
	OR_INPUT_LOW	INPUT_UP

@@num9?:
	test	ah, 10h
	jz	short @@z?
	OR_INPUT_HIGH	INPUT_UP_RIGHT

@@z?:
	mov	ah, byte ptr es:[52Fh]
	test	ah, 2
	jz	short @@x?
	OR_INPUT_LOW	INPUT_SHOT

@@x?:
	test	ah, 4
	jz	short @@q?
	OR_INPUT_LOW	INPUT_BOMB

@@q?:
	mov	ah, byte ptr es:[52Ch]
	test	ah, 1
	jz	short @@esc?
	OR_INPUT_HIGH	INPUT_Q

@@esc?:
	mov	ah, byte ptr es:[52Ah]
	test	ah, 1
	jz	short @@return?
	OR_INPUT_HIGH	INPUT_CANCEL

@@return?:
	mov	ah, byte ptr es:[52Dh]
	test	ah, 10h
	jz	short @@space?
	OR_INPUT_HIGH	INPUT_OK

@@space?:
	mov	ah, byte ptr es:[530h]
	test	ah, 10h
	jz	short @@shift?
	OR_INPUT_LOW	INPUT_SHOT

@@shift?:
	mov	ah, 2
	int	18h
	and	al, 1
	mov	_shiftkey, al
	cmp	js_bexist, 0
	jz	short @@ret
	call	js_sense
	or	_key_det, ax

@@ret:
if GAME eq 5
	mov	ax, _key_det
endif
	retf
_input_sense	endp
	even
