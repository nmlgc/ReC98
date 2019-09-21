	.186
	locals

include libs/master.lib/macros.inc
include th04/math/motion.inc
include th04/hardware/input.inc

extrn player_pos:motion_t
extrn _playchar_speed_aligned:word
extrn _playchar_speed_diagonal:word

; ----------------------------------------------------------------------------

main_01_TEXT	segment	word public 'CODE' use16
	assume cs:main_01_TEXT

; move_ret_t pascal near player_move(int input);
public PLAYER_MOVE
player_move	proc near
@@input	= word ptr ss:[bx+2]

@@diagonal_x equ ax
@@diagonal_y equ cx
@@aligned equ dx

	mov	bx, sp
	mov	bx, @@input
	cmp	bl, INPUT_RIGHT or INPUT_DOWN
	ja	short @@invalid
	mov	@@diagonal_y, _playchar_speed_diagonal
	mov	@@diagonal_x, @@diagonal_y
	mov	@@aligned, _playchar_speed_aligned
	and	bh, low INPUT_MOVEMENT
	jz	short @@switch
	or	bl, bl
	jnz	short @@invalid
	shr	bx, 8
	cmp	bl, 8
	ja	short @@invalid
	add	bl, 11

@@switch:
	add	bx, bx
	jmp	word ptr cs:@@switch_table[bx]

@@up:
	neg	@@aligned

@@down:
	mov	player_pos.velocity.y, @@aligned
	jmp	short @@moved
; ---------------------------------------------------------------------------

@@left:
	neg	@@aligned

@@right:
	mov	player_pos.velocity.x, @@aligned
	jmp	short @@moved
; ---------------------------------------------------------------------------

@@up_right:
	neg	@@diagonal_y
	jmp	short @@down_right
; ---------------------------------------------------------------------------

@@up_left:
	neg	@@diagonal_y

@@down_left:
	neg	@@diagonal_x

@@down_right:
	mov	player_pos.velocity.x, @@diagonal_x
	mov	player_pos.velocity.y, @@diagonal_y
	jmp	short @@moved
; ---------------------------------------------------------------------------

@@standing_still:
	mov	al, MOVE_NOINPUT
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@invalid:
	xor	al, al
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@moved:
	mov	al, MOVE_VALID

@@ret:
	retn	2

; ---------------------------------------------------------------------------
@@switch_table	label word
	dw @@standing_still
	dw @@up
	dw @@down
	dw @@invalid
	dw @@left
	dw @@up_left
	dw @@down_left
	dw @@invalid
	dw @@right
	dw @@up_right
	dw @@down_right
	dw @@invalid
	dw @@up_left
	dw @@up_right
	dw @@invalid
	dw @@down_left
	dw @@invalid
	dw @@invalid
	dw @@invalid
	dw @@down_right
player_move	endp
main_01_TEXT	ends

	end
