; superimpose & master library module
;
; Description:
;	パターンの任意拡大表示
;
; Functions/Procedures:
;	void super_zoom( int x, int y, int num, int zoom ) ;
;
; Parameters:
;	
;
; Returns:
;	
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	PC-9801
;
; Requiring Resources:
;	CPU: 8086
;
; Notes:
;	
;
; Compiler/Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Author:
;	Kazumi(奥田  仁)
;	恋塚(恋塚昭彦)
;
; Revision History:
;
;$Id: superzom.asm 0.02 92/06/10 19:31:57 Kazumi Rel $
;
;	93/ 3/16 Initial: master.lib <- super.lib 0.22b
;

func SUPER_ZOOM		; super_zoom() {
	push	BP
	mov	BP,SP
	push	SI
	push	DI

	@@x	= (RETSIZE+4)*2
	@@y	= (RETSIZE+3)*2
	@@num	= (RETSIZE+2)*2
	@@zoom	= (RETSIZE+1)*2

	mov	SI,[BP+@@x]
	mov	WORD PTR CS:[superzom_x1],SI
	mov	DI,[BP+@@y]
	mov	AX,[BP+@@zoom]
	mov	WORD PTR CS:[superzom_next_x],AX
	mov	WORD PTR CS:[superzom_next_y],AX
	dec	AX
	mov	CS:superzom_x2,AX
	mov	CS:superzom_y2,AX
	mov	BX,[BP+@@num]
	shl	BX,1		;integer size & near pointer
	mov	CX,super_patsize[BX]	;pattern size (1-8)
	mov	BYTE PTR CS:[superzom_x_count],CH
	mov	ES,super_patdata[BX]
	mov	AX,CX
	xor	AH,AH
	mul	CH
	mov	BP,AX
	mov	CS:SUPERZOM_PLANE1,AX
	mov	CS:SUPERZOM_PLANE2,AX
	mov	CS:SUPERZOM_PLANE3,AX
	shl	AX,1
	add	AX,BP		;AX * 3
	dec	AX
	mov	WORD PTR CS:[SUPERZOM_BACK],AX
	jmp	$+2
@@next_byte:
	mov	AH,8		;byte(8 bits)
	mov	BH,ES:[BP]
	add	BP,1111h
	org	$-2
SUPERZOM_PLANE1	dw	?
	mov	BL,ES:[BP]
	add	BP,1111h
	org	$-2
SUPERZOM_PLANE2	dw	?
	mov	DH,ES:[BP]
	add	BP,1111h
	org	$-2
SUPERZOM_PLANE3	dw	?
	mov	DL,ES:[BP]

@@next_bit:
	xor	AL,AL
	shl	DL,1
	rcl	AL,1
	shl	DH,1
	rcl	AL,1
	shl	BL,1
	rcl	AL,1
	shl	BH,1
	rcl	AL,1
	or	AL,AL
	jnz	short @@no_skip
	add	SI,1111h
superzom_next_x		EQU	$-2
	jmp	short @@skip
	EVEN
@@no_skip:
	push	AX
	push	BX
	push	CX
	push	DX
	push	ES

	push	SI	; x1
	push	DI	; y1
	mov	BX,1111h
	org	$-2
superzom_x2	dw	?
	add	SI,BX
	push	SI	; x2
	mov	BX,1111h
	org	$-2
superzom_y2	dw	?
	add	BX,DI
	push	BX	; y2
	mov	BX,0c0h	; RMW, all plane
	push	BX
	xor	AH,AH
	push	AX	; color
	_call	GRCG_SETCOLOR
	_call	GRCG_BOXFILL
	inc	SI

	pop	ES
	pop	DX
	pop	CX
	pop	BX
	pop	AX
@@skip:
	dec	AH
	jnz	short @@next_bit
	sub	BP,1111h
SUPERZOM_BACK		EQU	$-2
	dec	CH
	jnz	@@next_byte
	mov	CH,11h
superzom_x_count		EQU	$-1
	mov	SI,1111h
superzom_x1		EQU	$-2
	add	DI,1111h
superzom_next_y		EQU	$-2
	dec	CL
	jnz	@@next_byte

	_call	GRCG_OFF

	pop	DI
	pop	SI
	pop	BP
	ret	8
endfunc			; }
