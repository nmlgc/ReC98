	.386
	.model use16 large
	locals

include libs/master.lib/master.inc

	.code

; Just another dumb micro-optimized variation of vector2(), making full use of
; 32-bit registers. Since Turbo C++ 4.0J's inline assembler doesn't support
; them, this function is impossible to decompile without spelling out the
; entire thing in machine code.
; MODDERS: Just replace with one of the other variants.
public VECTOR2_NEAR
vector2_near proc near
	; (PASCAL calling convention, parameter list needs to be reversed here)
	arg @@length:word, @@angle:byte, @@ret:word

	push	bp
	mov	bp, sp
	movsx	edx, @@length
	mov	bl, @@angle
	mov	bh, 0
	add	bx, bx
	movsx	eax, _CosTable8[bx]
	movsx	ecx, _SinTable8[bx]
	imul	eax, edx
	sar	eax, 8
	imul	edx, ecx
	sar	edx, 8
	mov	bx, @@ret
	mov	[bx], ax
	mov	[bx+2],	dx
	pop	bp
	retn	6
vector2_near endp
	even

	end
