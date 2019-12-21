SETUP_LINE_H = 16
SETUP_CHOICE_X = 48
SETUP_CHOICE_Y = 136
SETUP_HELP_X = 208
SETUP_HELP_Y = 136

public SETUP_BGM_CHOICE_PUT
setup_bgm_choice_put	proc near

@@str	= dword	ptr -4
@@col	= word ptr  4
@@mode	= word ptr  6

	enter	4, 0
	push	si
	mov	si, SETUP_CHOICE_Y
	mov	ax, [bp+@@mode]
	or	ax, ax
	jz	short @@none
	cmp	ax, SND_BGM_FM26
	jz	short @@fm26
	cmp	ax, SND_BGM_FM86
	jnz	short @@put
	mov	word ptr [bp+@@str+2], ds
	mov	word ptr [bp+@@str], offset aSETUP_BGM_OPTION1
	jmp	short @@put
; ---------------------------------------------------------------------------

@@fm26:
	mov	word ptr [bp+@@str+2], ds
	mov	word ptr [bp+@@str], offset aSETUP_BGM_OPTION2
	add	si, SETUP_LINE_H * 1
	jmp	short @@put
; ---------------------------------------------------------------------------

@@none:
	mov	word ptr [bp+@@str+2], ds
	mov	word ptr [bp+@@str], offset aSETUP_BGM_OPTION3
	add	si, SETUP_LINE_H * 2

@@put:
	call	graph_putsa_fx pascal, SETUP_CHOICE_X, si, [bp+@@col], large [bp+@@str]
	pop	si
	leave
	retn	4
setup_bgm_choice_put	endp


public SETUP_SE_CHOICE_PUT
setup_se_choice_put	proc near

@@str		= dword	ptr -4
@@col		= word ptr  4
@@mode		= word ptr  6

	enter	4, 0
	push	si
	mov	si, SETUP_CHOICE_Y
	mov	ax, [bp+@@mode]
	or	ax, ax
	jz	short @@none
	cmp	ax, SND_SE_FM
	jz	short @@fm
	cmp	ax, SND_SE_BEEP
	jz	short @@beep
	jmp	short @@put
; ---------------------------------------------------------------------------

@@fm:
	mov	word ptr [bp+@@str+2], ds
	mov	word ptr [bp+@@str], offset aSETUP_SE_OPTION1
	jmp	short @@put
; ---------------------------------------------------------------------------

@@beep:
	mov	word ptr [bp+@@str+2], ds
	mov	word ptr [bp+@@str], offset aSETUP_SE_OPTION2
	add	si, SETUP_LINE_H * 1
	jmp	short @@put
; ---------------------------------------------------------------------------

@@none:
	mov	word ptr [bp+@@str+2], ds
	mov	word ptr [bp+@@str], offset aSETUP_SE_OPTION3
	add	si, SETUP_LINE_H * 2

@@put:
	call	graph_putsa_fx pascal, SETUP_CHOICE_X, si, [bp+@@col], large [bp+@@str]
	pop	si
	leave
	retn	4
setup_se_choice_put	endp


public SETUP_BGM_HELP_PUT
setup_bgm_help_put	proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, SETUP_HELP_Y
	xor	si, si
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@put_line:
	push	SETUP_HELP_X
	push	di
	push	15
	mov	bx, si
	shl	bx, 2
	pushd	SETUP_BGM_HELP[bx]
	call	graph_putsa_fx
	inc	si
	add	di, SETUP_LINE_H

@@more?:
	cmp	si, 9
	jl	short @@put_line
	pop	di
	pop	si
	pop	bp
	retn
setup_bgm_help_put	endp


public SETUP_SE_HELP_PUT
setup_se_help_put	proc near
	push	bp
	mov	bp, sp
	push	si
	push	di
	mov	di, SETUP_HELP_Y
	xor	si, si
	jmp	short @@more?
; ---------------------------------------------------------------------------

@@put_line:
	push	SETUP_HELP_X
	push	di
	push	15
	mov	bx, si
	shl	bx, 2
	pushd	SETUP_SE_HELP[bx]
	call	graph_putsa_fx
	inc	si
	add	di, SETUP_LINE_H

@@more?:
	cmp	si, 9
	jl	short @@put_line
	pop	di
	pop	si
	pop	bp
	retn
setup_se_help_put	endp
