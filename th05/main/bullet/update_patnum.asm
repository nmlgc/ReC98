public BULLET_UPDATE_PATNUM
bullet_update_patnum	proc near

@@patnum_base	= byte ptr -1
@@bullet     	= word ptr  4

	push	bp
	mov	bp, sp
	sub	sp, 2
	push	si
	mov	si, [bp+@@bullet]
	cmp	[si+bullet_t.BULLET_patnum], PAT_BULLET16_D_BLUE
	jl	short @@ret
	cmp	[si+bullet_t.BULLET_patnum], PAT_BULLET16_D_GREEN
	jge	short @@d_green?
	mov	[bp+@@patnum_base], PAT_BULLET16_D_BLUE
	jmp	short @@set
; ---------------------------------------------------------------------------

@@d_green?:
	cmp	[si+bullet_t.BULLET_patnum], PAT_BULLET16_V_RED
	jge	short @@v_red?
	mov	[bp+@@patnum_base], PAT_BULLET16_D_GREEN
	jmp	short @@set
; ---------------------------------------------------------------------------

@@v_red?:
	cmp	[si+bullet_t.BULLET_patnum], PAT_BULLET16_V_BLUE
	jge	short @@v_blue?
	mov	[bp+@@patnum_base], PAT_BULLET16_V_RED
	jmp	short @@set
; ---------------------------------------------------------------------------

@@v_blue?:
	mov	[bp+@@patnum_base], PAT_BULLET16_V_BLUE

@@set:
	mov	al, [bp+@@patnum_base]
	mov	ah, 0
	call	bullet_patnum_for_angle pascal, ax, word ptr [si+bullet_t.BULLET_angle]
	mov	ah, 0
	mov	[si+bullet_t.BULLET_patnum], ax

@@ret:
	pop	si
	leave
	retn	2
bullet_update_patnum	endp
