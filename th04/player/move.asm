; move_ret_t pascal near player_move(int input);
public PLAYER_MOVE
player_move	proc near
@@input_local	= word ptr -2
@@input      	= word ptr  4

	enter	2, 0
	mov	dl, MOVE_VALID
	mov	ax, [bp+@@input]
	mov	[bp+@@input_local], ax
	mov	cx, @@num_cases
	mov	bx, offset @@switch_table

@@case_lookup:
	mov	ax, cs:[bx]
	cmp	ax, [bp+@@input_local]
	jz	short @@switch
	add	bx, 2
	loop	@@case_lookup
	jmp	short @@default
; ---------------------------------------------------------------------------

@@switch:
	jmp	word ptr cs:[bx+@@case_to_target] ; switch jump

@@standing_still:
	mov	dl, MOVE_NOINPUT
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@left:
	mov	player_pos.velocity.x, -playchar_speed_aligned
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@down_left:
	mov	player_pos.velocity.x, -playchar_speed_diagonal
	mov	player_pos.velocity.y, playchar_speed_diagonal
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@down:
	mov	player_pos.velocity.y, playchar_speed_aligned
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@down_right:
	mov	player_pos.velocity.x, playchar_speed_diagonal
	mov	player_pos.velocity.y, playchar_speed_diagonal
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@right:
	mov	player_pos.velocity.x, playchar_speed_aligned
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@up_right:
	mov	player_pos.velocity.x, playchar_speed_diagonal
	jmp	short @@up_left_y
; ---------------------------------------------------------------------------

@@up:
	mov	player_pos.velocity.y, -playchar_speed_aligned
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@up_left:
	mov	player_pos.velocity.x, -playchar_speed_diagonal

@@up_left_y:
	mov	player_pos.velocity.y, -playchar_speed_diagonal
	jmp	short @@ret
; ---------------------------------------------------------------------------

@@default:
	mov	dl, MOVE_INVALID

@@ret:
	mov	al, dl
	leave
	retn	2

; ---------------------------------------------------------------------------
	db    0
@@switch_table	label word
	; value table for switch statement
	dw	INPUT_NONE
	dw	INPUT_UP
	dw	INPUT_DOWN
	dw	INPUT_LEFT
	dw	INPUT_UP or INPUT_LEFT
	dw 	INPUT_DOWN or INPUT_LEFT
	dw	INPUT_RIGHT
	dw	INPUT_UP or INPUT_RIGHT
	dw  INPUT_DOWN or INPUT_RIGHT
	dw	INPUT_UP_LEFT
	dw	INPUT_UP_RIGHT
	dw	INPUT_DOWN_LEFT
	dw 	INPUT_DOWN_RIGHT
@@case_to_target = $ - @@switch_table
@@num_cases = @@case_to_target shr 1
	; jump table for switch statement
	dw offset @@standing_still
	dw offset @@up
	dw offset @@down
	dw offset @@left
	dw offset @@up_left
	dw offset @@down_left
	dw offset @@right
	dw offset @@up_right
	dw offset @@down_right
	dw offset @@up_left
	dw offset @@up_right
	dw offset @@down_left
	dw offset @@down_right
player_move	endp
