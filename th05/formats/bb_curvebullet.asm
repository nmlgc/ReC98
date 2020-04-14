; void pascal near bb_curvebullet_load(void);
public BB_CURVEBULLET_LOAD
bb_curvebullet_load	proc near
	mov	ax, 3D00h
	mov	dx, offset aLs00_bb
	int	21h		; DOS -	2+ - OPEN DISK FILE WITH HANDLE
				; DS:DX	-> ASCIZ filename
				; AL = access mode
				; 0 - read
	mov	bx, ax
	mov	ah, 3Fh
	mov	dx, offset _bb_curvebullet
	mov	cx, BB_SIZE
	int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
				; BX = file handle, CX = number	of bytes to read
				; DS:DX	-> buffer
	mov	ah, 3Eh
	int	21h		; DOS -	2+ - CLOSE A FILE WITH HANDLE
				; BX = file handle
	retn
bb_curvebullet_load	endp
	nop


; Adapted from z_super_roll_put_tiny_32x32().
public @curvebullet_put
@curvebullet_put	proc near

; Parameters
@@left equ ax
@@top equ dx
@@sprite equ bx

; Locals
@@PATTERN_HEIGHT = CURVEBULLET_H
@@first_mask equ dl
@@first_bit equ cl
@@rows_left equ ch

	push	si
	push	di
	shl	@@sprite, 7
	mov	si, @@sprite
	add	si, offset _bb_curvebullet
	mov	di, @@top
	shl	di, 2
	add	di, @@top
	shl	di, 4
	mov	@@first_bit, al
	and	@@first_bit, 7
	shr	@@left, 3
	add	di, @@left
	mov	@@first_mask, 0FFh
	shr	@@first_mask, @@first_bit
	test	di, 1
	jnz	short @@ODD

	even
@@EVEN:
	mov	@@rows_left, @@PATTERN_HEIGHT
	cmp	di, (RES_Y - @@PATTERN_HEIGHT + 1) * ROW_SIZE
	jb	short @@EVEN_YLOOP2

@@EVEN_YLOOP1:
	call	@@put32_even
	cmp	di, PLANE_SIZE
	jb	short @@EVEN_YLOOP1
	sub	di, PLANE_SIZE

	even
@@EVEN_YLOOP2:
	call	@@put32_even
	jnz	short @@EVEN_YLOOP2
	jmp	short @@ret

	even
@@ODD:
	mov	@@rows_left, @@PATTERN_HEIGHT
	cmp	di, (RES_Y - @@PATTERN_HEIGHT + 1) * ROW_SIZE
	jb	short @@ODD_YLOOP2

@@ODD_YLOOP1:
	call	@@put32_odd
	cmp	di, PLANE_SIZE
	jb	short @@ODD_YLOOP1
	sub	di, PLANE_SIZE

	even
@@ODD_YLOOP2:
	call	@@put32_odd
	jnz	short @@ODD_YLOOP2

@@ret:
	pop	di
	pop	si
	retn
; ============================================================================

; These are the same 32-dot put functions used in z_super_roll_put_tiny(),
; only without the optimization for not writing empty rows to VRAM. They take:
; • const dots32_t* row_dots<ds:si>
; • dots32_t* vram_offset<es:di>
; • uint3_t first_bit<cl>
; • uint8_t& rows_left<ch>
; • dots8_t first_mask<dl>
; [rows_left] is decremented at the end. ZF then indicates whether this was
; the last row.

@@words equ bh
@@carry_dots_cur equ bl
@@carry_dots_next equ dh

@@put32_even:	; if X is even
	xor	@@carry_dots_cur, @@carry_dots_cur
	mov	@@words, 2
	lodsd

@@EVEN_WORD_LOOP:
	ror	ax, @@first_bit
	mov	@@carry_dots_next, al
	and	al, @@first_mask
	xor	@@carry_dots_next, al
	or	al, @@carry_dots_cur
	mov	@@carry_dots_cur, @@carry_dots_next
	stosw
	shr	eax, (8 * word)
	dec	@@words
	jnz	short @@EVEN_WORD_LOOP
	mov	es:[di], @@carry_dots_cur
	add	di, (ROW_SIZE - dword)
	dec	@@rows_left
	retn
; ----------------------------------------------------------------------------

@@put32_odd:	; if X is odd
	mov	@@words, 2
	lodsd
	ror	al, @@first_bit
	mov	@@carry_dots_cur, al
	and	al, @@first_mask
	stosb
	xor	@@carry_dots_cur, al
	shr	eax, (8 * byte)

@@ODD_WORD_LOOP:
	ror	ax, @@first_bit
	mov	@@carry_dots_next, al
	and	al, @@first_mask
	xor	@@carry_dots_next, al
	or	al, @@carry_dots_cur
	mov	@@carry_dots_cur, @@carry_dots_next
	stosw
	shr	eax, (8 * word)
	dec	@@words
	jnz	short @@ODD_WORD_LOOP
	add	di, (ROW_SIZE - (dword + 1))
	dec	@@rows_left
	retn
@curvebullet_put	endp
