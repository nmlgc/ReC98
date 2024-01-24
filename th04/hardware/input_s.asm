	.386
	.model use16 large SHARED
	locals

include pc98kbd.inc
include twobyte.inc
include th04/hardware/input.inc

	extrn _key_det:word
	extrn _shiftkey:byte
	extrn js_stat:word
	extrn js_bexist:word

	extrn JS_SENSE:proc

	.code SHARED

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

public _input_reset_sense
_input_reset_sense label proc
	xor	ax, ax
	mov	_key_det, ax
	mov	js_stat, ax

public _input_sense
_input_sense proc far
	xor	ax, ax
	mov	es, ax
	mov	ah, byte ptr es:[KEYGROUP_7]
	test	ah, K7_ARROW_UP
	jz	short @@down?
	OR_INPUT_LOW	INPUT_UP

@@down?:
	test	ah, K7_ARROW_DOWN
	jz	short @@left?
	OR_INPUT_LOW	INPUT_DOWN

@@left?:
	test	ah, K7_ARROW_LEFT
	jz	short @@right?
	OR_INPUT_LOW	INPUT_LEFT

@@right?:
	test	ah, K7_ARROW_RIGHT
	jz	short @@num6?
	OR_INPUT_LOW	INPUT_RIGHT

@@num6?:
	mov	ah, byte ptr es:[KEYGROUP_9]
	test	ah, K9_NUM_6
	jz	short @@num1?
	OR_INPUT_LOW	INPUT_RIGHT

@@num1?:
	test	ah, K9_NUM_1
	jz	short @@num2?
	OR_INPUT_HIGH	INPUT_DOWN_LEFT

@@num2?:
	test	ah, K9_NUM_2
	jz	short @@num3?
	OR_INPUT_LOW	INPUT_DOWN

@@num3?:
	test	ah, K9_NUM_3
	jz	short @@num4?
	OR_INPUT_HIGH	INPUT_DOWN_RIGHT

@@num4?:
	mov	ah, byte ptr es:[KEYGROUP_8]
	test	ah, K8_NUM_4
	jz	short @@num7?
	OR_INPUT_LOW	INPUT_LEFT

@@num7?:
	test	ah, K8_NUM_7
	jz	short @@num8?
	OR_INPUT_HIGH	INPUT_UP_LEFT

@@num8?:
	test	ah, K8_NUM_8
	jz	short @@num9?
	OR_INPUT_LOW	INPUT_UP

@@num9?:
	test	ah, K8_NUM_9
	jz	short @@z?
	OR_INPUT_HIGH	INPUT_UP_RIGHT

@@z?:
	mov	ah, byte ptr es:[KEYGROUP_5]
	test	ah, K5_Z
	jz	short @@x?
	OR_INPUT_LOW	INPUT_SHOT

@@x?:
	test	ah, K5_X
	jz	short @@q?
	OR_INPUT_LOW	INPUT_BOMB

@@q?:
	mov	ah, byte ptr es:[KEYGROUP_2]
	test	ah, K2_Q
	jz	short @@esc?
	OR_INPUT_HIGH	INPUT_Q

@@esc?:
	mov	ah, byte ptr es:[KEYGROUP_0]
	test	ah, K0_ESC
	jz	short @@return?
	OR_INPUT_HIGH	INPUT_CANCEL

@@return?:
	mov	ah, byte ptr es:[KEYGROUP_3]
	test	ah, K3_RETURN
	jz	short @@space?
	OR_INPUT_HIGH	INPUT_OK

@@space?:
	mov	ah, byte ptr es:[KEYGROUP_6]
	test	ah, K6_SPACE
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
_input_sense endp
	even

	end
