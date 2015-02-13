; (included from th05_main.asm, don't assemble directly)

; ===========================================================================

; Segment type:	Pure code
seg003		segment	byte public 'CODE' use16
		assume cs:seg003
		;org 8
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================


sub_15288	proc near
		mov	bx, sp
		mov	ax, ss:[bx+2]
		sar	ax, 4
		cmp	byte_2CE00, 0
		jz	short loc_1529C
		add	ax, word_2CDFC

loc_1529C:
		cmp	ax, 190h
		jl	short loc_152A6
		sub	ax, 190h
		jmp	short locret_152AD
; ---------------------------------------------------------------------------

loc_152A6:
		or	ax, ax
		jge	short locret_152AD
		add	ax, 190h

locret_152AD:
		retn	2
sub_15288	endp

; ---------------------------------------------------------------------------
		mov	bx, sp
		mov	ax, ss:[bx+2]
		sar	ax, 4
		add	ax, word_2CDFC
		cmp	ax, 190h
		jl	short loc_152C7
		sub	ax, 190h
		jmp	short locret_152CE
; ---------------------------------------------------------------------------

loc_152C7:
		or	ax, ax
		jge	short locret_152CE
		add	ax, 190h

locret_152CE:
		retn	2
; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_152D2	proc near
		mov	bx, sp
		mov	bx, ss:[bx+2]
		mov	ax, [bx]
		mov	[bx+4],	ax
		add	ax, [bx+8]
		mov	[bx], ax
		add	bx, 2
		mov	dx, [bx]
		mov	[bx+4],	dx
		add	dx, [bx+8]
		mov	[bx], dx
		retn	2
sub_152D2	endp


; =============== S U B	R O U T	I N E =======================================


sub_152F2	proc near
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		test	byte ptr [si+1Fh], 1
		jz	short loc_15307
		add	ax, 100h
		cmp	ax, 1A00h
		jnb	short loc_15319

loc_15307:
		test	byte ptr [si+1Fh], 10h
		jz	short loc_15317
		add	dx, 100h
		cmp	dx, 1900h
		jnb	short loc_15319

loc_15317:
		clc
		retn
; ---------------------------------------------------------------------------

loc_15319:
		inc	word_221C2
		stc
		retn
sub_152F2	endp


; =============== S U B	R O U T	I N E =======================================


sub_1531F	proc near
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+1Ah]
		xor	ah, ah
		mov	al, [si+16h]
		push	ax
		call	sub_158E2
		retn
sub_1531F	endp


; =============== S U B	R O U T	I N E =======================================


sub_15330	proc near
		push	es
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	word ptr [si+1Ah]
		call	sub_15A24
		mov	[si+1Ah], al
		pop	es
		call	sub_1531F
		retn
sub_15330	endp


; =============== S U B	R O U T	I N E =======================================


sub_15345	proc near
		push	si
		push	di
		mov	cx, 7
		add	si, 28h	; '('
		push	es
		push	ds
		pop	es
		assume es:dseg
		mov	di, 561Ah
		rep movsw
		pop	es
		assume es:nothing
		pop	di
		pop	si
		retn
sub_15345	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_1535A	proc near
		push	si
		push	di
		mov	si, word_2C92A
		mov	es, word_21290

loc_15364:
		mov	di, [si+12h]
		add	di, [si+14h]
		mov	bl, es:[di]
		mov	bh, 0
		cmp	bx, 3Ah	; ':'
		ja	loc_1575C
		mov	cl, [si+18h]
		mov	al, 1
		mov	ah, es:[di+1]
		xor	dx, dx
		add	bx, bx
		jmp	cs:off_1575F[bx]

loc_15388:
		mov	byte ptr [si], 2
		mov	al, 1
		jmp	loc_1575C
; ---------------------------------------------------------------------------

loc_15390:
		or	cl, cl
		jnz	short loc_153A1
		mov	ax, es:[di+1]
		mov	[si+16h], ah
		mov	[si+1Ah], al
		call	sub_1531F

loc_153A1:
		call	sub_152F2
		jb	short loc_15388
		mov	ah, es:[di+3]
		mov	al, 4
		jmp	loc_15748
; ---------------------------------------------------------------------------

loc_153AF:
		or	cl, cl
		jnz	short loc_153B6
		call	sub_1531F

loc_153B6:
		call	sub_152F2
		jb	short loc_15388
		mov	ah, es:[di+1]
		mov	al, 2
		jmp	loc_15748
; ---------------------------------------------------------------------------

loc_153C4:
		or	cl, cl
		jnz	short loc_153D2
		mov	al, es:[di+1]
		mov	[si+16h], al
		call	sub_1531F

loc_153D2:
		call	sub_152F2
		jb	short loc_15388
		mov	ah, es:[di+2]
		mov	al, 3
		jmp	loc_15748
; ---------------------------------------------------------------------------

loc_153E0:
		inc	dl

loc_153E2:
		or	cl, cl
		jnz	short loc_153F7
		mov	ax, es:[di+1]
		mov	[si+16h], ah
		mov	[si+1Ah], al
		mov	al, es:[di+3]
		mov	[si+1Bh], al

loc_153F7:
		push	dx
		call	sub_1531F
		pop	dx
		or	dl, dl
		jz	short loc_15418
		mov	al, es:[di+4]
		cbw
		add	[si+0Ah], ax
		mov	al, es:[di+5]
		cbw
		add	[si+0Ch], ax
		mov	ah, es:[di+6]
		mov	al, 7
		jmp	short loc_1541E
; ---------------------------------------------------------------------------

loc_15418:
		mov	ah, es:[di+4]
		mov	al, 5

loc_1541E:
		jmp	short loc_15447
; ---------------------------------------------------------------------------

loc_15420:
		inc	dl

loc_15422:
		call	sub_1531F
		or	dl, dl
		jz	short loc_15441
		mov	al, es:[di+1]
		cbw
		add	[si+0Ah], ax
		mov	al, es:[di+2]
		cbw
		add	[si+0Ch], ax
		mov	ah, es:[di+3]
		mov	al, 4
		jmp	short loc_15447
; ---------------------------------------------------------------------------

loc_15441:
		mov	ah, es:[di+1]
		mov	al, 2

loc_15447:
		push	ax
		call	sub_152F2
		pop	ax
		jb	loc_15388
		mov	dl, [si+1Bh]
		add	[si+1Ah], dl
		jmp	loc_15748
; ---------------------------------------------------------------------------

loc_15459:
		or	cl, cl
		jnz	short loc_1547D
		mov	eax, [si+2]
		mov	[si+6],	eax
		jmp	short loc_1547D
; ---------------------------------------------------------------------------

loc_15467:
		or	cl, cl
		jnz	short loc_15470
		mov	word ptr [si+0Ah], 0

loc_15470:
		mov	ax, word_2CDFE
		mov	[si+0Ch], ax
		call	sub_152F2
		jb	loc_15388

loc_1547D:
		mov	ah, es:[di+1]
		mov	al, 2
		jmp	loc_15748
; ---------------------------------------------------------------------------

loc_15486:
		inc	dl

loc_15488:
		or	cl, cl
		jnz	short loc_15497
		mov	byte ptr [si+1Ah], 0
		mov	al, es:[di+2]
		mov	[si+1Bh], al

loc_15497:
		mov	cl, dl
		movzx	eax, byte ptr es:[di+1]
		mov	bl, [si+1Ah]
		mov	bh, 0
		add	bx, bx
		movsx	edx, _CosTable8[bx]
		imul	eax, edx
		sar	eax, 8
		mov	[si+0Ah], ax
		mov	al, es:[di+3]
		cbw
		mov	[si+0Ch], ax
		or	cl, cl
		jnz	short loc_154CF
		mov	dx, [si+0Ah]
		mov	ax, [si+0Ch]
		mov	[si+0Ah], ax
		mov	[si+0Ch], dx

loc_154CF:
		call	sub_152F2
		jb	loc_15388
		mov	al, [si+1Bh]
		add	[si+1Ah], al
		mov	ah, es:[di+4]
		mov	al, 5
		jmp	loc_15748
; ---------------------------------------------------------------------------

loc_154E5:
		mov	ax, es:[di+1]
		mov	[si+1Ah], al
		mov	[si+16h], ah
		call	sub_15330
		mov	al, 3
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_154F7:
		add	[si+1Ah], ah
		jmp	short loc_154FF
; ---------------------------------------------------------------------------

loc_154FC:
		add	[si+16h], ah

loc_154FF:
		call	sub_1531F
		mov	al, 2
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15507:
		call	sub_157D6
		mov	[si+1Ah], al
		mov	al, 1
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15512:
		mov	dl, 2
		jmp	short loc_15518
; ---------------------------------------------------------------------------

loc_15516:
		inc	dl

loc_15518:
		mov	word_23F60, dx
		call	sub_15345
		mov	ax, [si+2]
		add	word ptr dword_25FFC, ax
		mov	ax, [si+4]
		add	word ptr dword_25FFC+2,	ax
		push	es
		call	fp_25344
		mov	bx, word_23F60
		add	bx, bx
		call	off_2129C[bx]
		pop	es
		mov	al, 1
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15542:
		mov	byte ptr [si+23h], 0
		mov	[si+28h], ah
		mov	ax, es:[di+2]
		mov	[si+2Eh], al
		mov	[si+34h], ah
		mov	ax, es:[di+4]
		mov	[si+35h], al
		mov	[si+29h], ah
		mov	al, 6
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15562:
		mov	[si+28h], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------

loc_15567:
		mov	eax, es:[di+1]
		mov	[si+2Ah], eax
		mov	al, 5
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15575:
		mov	[si+34h], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------

loc_1557A:
		add	[si+34h], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------

loc_1557F:
		call	sub_157D6
		mov	[si+34h], al
		mov	al, 1
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_1558A:
		mov	[si+29h], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------

loc_1558F:
		mov	[si+35h], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------

loc_15594:
		add	[si+35h], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------

loc_15599:
		mov	[si+2Eh], ah

loc_1559C:
		mov	al, 2
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_155A1:
		mov	al, ah
		xor	ah, ah
		mov	dl, byte_25FEC
		cmp	dl, 20h	; ' '
		jbe	short loc_155C7
		sub	dl, 20h	; ' '
		mul	dl
		shr	ax, 6
		xor	dh, dh
		mov	dl, es:[di+1]
		sub	dx, ax
		cmp	dl, 10h
		jnb	short loc_155E0
		mov	dl, 10h
		jmp	short loc_155E0
; ---------------------------------------------------------------------------

loc_155C7:
		mov	cl, 20h	; ' '
		sub	cl, dl
		mul	cl
		shr	ax, 6
		xor	dh, dh
		mov	dl, es:[di+1]
		add	dx, ax
		cmp	dx, 100h
		jb	short loc_155E0
		mov	dl, 0FFh

loc_155E0:
		cmp	byte_25FEB, 0
		jnz	short loc_155E9
		mov	dl, 0FFh

loc_155E9:
		mov	[si+27h], dl
		jmp	short loc_1559C
; ---------------------------------------------------------------------------

loc_155EE:
		inc	dl

loc_155F0:
		mov	[si+23h], dl
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_155F6:
		mov	[si+30h], ah
		mov	al, es:[di+2]
		mov	[si+31h], al

loc_15600:
		mov	al, 3
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15605:
		mov	[si+32h], ah
		mov	al, es:[di+2]

loc_1560C:
		mov	[si+33h], al

loc_1560F:
		jmp	short loc_15600
; ---------------------------------------------------------------------------

loc_15611:
		mov	[si+2Fh], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------

loc_15616:
		push	es
		mov	ax, [si+2]
		add	ax, [si+2Ah]
		push	ax
		mov	ax, [si+4]
		add	ax, [si+2Ch]
		push	ax
		push	word ptr es:[di+1]
		call	sub_15A24
		mov	[si+34h], al
		pop	es

loc_15630:
		jmp	loc_1559C
; ---------------------------------------------------------------------------

loc_15633:
		inc	dl
		mov	[si], dl
		mov	[si+17h], ah
		mov	ax, es:[di+2]
		mov	[si+0Eh], ax
		mov	ax, es:[di+4]
		mov	[si+10h], ax
		mov	[si+22h], dl
		mov	[si+24h], dl
		mov	al, 6
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15653:
		mov	byte ptr [si+1Fh], 11h
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_1565A:
		or	byte ptr [si+1Fh], 1
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15661:
		or	byte ptr [si+1Fh], 10h
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15668:
		mov	[si+1Ch], ah
		mov	al, es:[di+2]
		mov	[si+1Dh], al
		mov	al, 3
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15677:
		mov	al, ah
		mov	ah, 0
		call	snd_se_play pascal, ax

loc_15681:
		mov	al, 2
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15686:
		mov	[si+17h], ah
		jmp	short loc_15681
; ---------------------------------------------------------------------------

loc_1568B:
		mov	[si+22h], dl

loc_1568E:
		mov	[si+23h], dl
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_15694:
		mov	byte ptr [si+22h], 1
		cmp	byte_25FEB, 3
		jnz	short loc_1568E
		inc	dl
		jmp	short loc_1568E
; ---------------------------------------------------------------------------

loc_156A3:
		inc	dl

loc_156A5:
		mov	[si+24h], dl
		jmp	loc_15740
; ---------------------------------------------------------------------------

loc_156AB:
		mov	eax, [si+2]
		mov	[si+6],	eax
		mov	eax, es:[di+1]
		mov	[si+2],	eax
		jmp	short loc_156D4
; ---------------------------------------------------------------------------

loc_156BE:
		mov	eax, [si+2]
		mov	[si+6],	eax
		mov	ax, es:[di+1]
		add	[si+2],	ax
		mov	ax, es:[di+3]
		add	[si+4],	ax

loc_156D4:
		mov	ah, 0
		mov	al, 5
		jmp	short loc_15748
; ---------------------------------------------------------------------------

loc_156DA:
		add	[si+17h], ah
		mov	al, 2
		jmp	short loc_15740
; ---------------------------------------------------------------------------

loc_156E1:
		mov	[si+1Ah], ah
		mov	al, es:[di+2]
		mov	[si+16h], al

loc_156EB:
		call	sub_1531F
		mov	al, 3
		jmp	short loc_15740
; ---------------------------------------------------------------------------

loc_156F2:
		mov	[si+1Ah], ah
		mov	al, es:[di+2]
		mov	[si+16h], al
		cmp	byte ptr [si+25h], 0
		jnz	short loc_156EB
		mov	al, 80h	; '€'
		sub	al, ah
		mov	[si+1Ah], al
		jmp	short loc_156EB
; ---------------------------------------------------------------------------

loc_1570B:
		mov	[si+16h], ah
		call	sub_1531F
		mov	al, 2
		jmp	short loc_15740
; ---------------------------------------------------------------------------

loc_15715:
		mov	al, [si+19h]
		cmp	al, es:[di+2]
		jb	short loc_15726
		mov	byte ptr [si+19h], 0
		mov	al, 3
		jmp	short loc_15740
; ---------------------------------------------------------------------------

loc_15726:
		inc	byte ptr [si+19h]

loc_15729:
		mov	al, ah
		mov	ah, 0

loc_1572D:
		sub	[si+14h], ax
		jmp	loc_15364
; ---------------------------------------------------------------------------

loc_15733:
		mov	al, 3
		cmp	ah, [si+36h]
		jz	short loc_15740
		add	al, es:[di+2]
		jz	short $+2

loc_15740:
		mov	ah, 0
		add	[si+14h], ax
		jmp	loc_15364
; ---------------------------------------------------------------------------

loc_15748:
		cmp	ah, [si+18h]
		ja	short loc_15757
		mov	ah, 0
		mov	[si+18h], ah
		add	[si+14h], ax
		jmp	short loc_1575A
; ---------------------------------------------------------------------------

loc_15757:
		inc	byte ptr [si+18h]

loc_1575A:
		xor	ax, ax

loc_1575C:
		pop	di
		pop	si
		retn
sub_1535A	endp

; ---------------------------------------------------------------------------
off_1575F	dw offset loc_15388
		dw offset loc_15633
		dw offset loc_15390
		dw offset loc_153AF
		dw offset loc_153C4
		dw offset loc_153E2
		dw offset loc_153E0
		dw offset loc_15422
		dw offset loc_15420
		dw offset loc_15459
		dw offset loc_15467
		dw offset loc_15486
		dw offset loc_15488
		dw offset loc_154E5
		dw offset loc_154F7
		dw offset loc_154FC
		dw offset loc_15507
		dw offset loc_15518
		dw offset loc_15542
		dw offset loc_15562
		dw offset loc_15567
		dw offset loc_15575
		dw offset loc_1557A
		dw offset loc_1557F
		dw offset loc_1558A
		dw offset loc_1558F
		dw offset loc_15594
		dw offset loc_15599
		dw offset loc_155A1
		dw offset loc_155EE
		dw offset loc_155F0
		dw offset loc_1557A
		dw offset loc_155F6
		dw offset loc_15605
		dw offset loc_1565A
		dw offset loc_15661
		dw offset loc_15653
		dw offset loc_15668
		dw offset loc_15677
		dw offset loc_15686
		dw offset loc_1568B
		dw offset loc_15694
		dw offset loc_156A5
		dw offset loc_156A3
		dw offset loc_156AB
		dw offset loc_156BE
		dw offset loc_156DA
		dw offset loc_156E1
		dw offset loc_156F2
		dw offset loc_1570B
		dw offset loc_15715
		dw offset loc_15715
		dw offset loc_15733
		dw offset loc_15729
		dw offset loc_153B6
		dw offset loc_15512
		dw offset loc_15611
		dw offset loc_15516
		dw offset loc_15616
; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_157D6	proc near
		mov	bx, word_24062
		mov	ax, [bx+3582h]
		inc	byte ptr word_24062
		retn
sub_157D6	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_157E4	proc near
		mov	bx, word_24062
		mov	ax, [bx+3582h]
		inc	byte ptr word_24062
		mov	bx, sp
		and	ax, ss:[bx+2]
		retn	2
sub_157E4	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_157FA	proc near
		mov	bx, word_24062
		mov	ax, [bx+3582h]
		inc	byte ptr word_24062
		xor	dx, dx
		mov	bx, sp
		div	word ptr ss:[bx+2]
		mov	ax, dx
		retn	2
sub_157FA	endp

; ---------------------------------------------------------------------------
		db 0

; =============== S U B	R O U T	I N E =======================================


sub_15814	proc near
		push	si
		push	di
		mov	si, ax
		mov	bx, dx
		sar	ax, 3
		shl	dx, 6
		add	ax, dx
		shr	dx, 2
		add	ax, dx
		mov	di, ax
		and	si, 7
		mov	ax, si
		shl	si, 4
		add	si, 8C2h
		mov	cx, 8
		cmp	bx, 188h
		ja	short loc_15842
		xor	dx, dx
		jmp	short loc_1584B
; ---------------------------------------------------------------------------

loc_15842:
		mov	dx, cx
		mov	cx, 190h
		sub	cx, bx
		sub	dx, cx

loc_1584B:
		or	ax, ax
		jz	short loc_15862
		nop

loc_15850:
		movsw
		add	di, 4Eh	; 'N'
		loop	loc_15850

loc_15856:
		or	dx, dx
		jz	short loc_1586B
		sub	di, 7D00h
		xchg	cx, dx
		jmp	short loc_15850
; ---------------------------------------------------------------------------

loc_15862:
		movsb
		add	di, 4Fh	; 'O'
		inc	si
		loop	loc_15862
		jmp	short loc_15856
; ---------------------------------------------------------------------------

loc_1586B:
		pop	di
		pop	si
		retn
sub_15814	endp


; =============== S U B	R O U T	I N E =======================================


sub_1586E	proc near
		mov	bl, byte_24065
		inc	byte_24065
		cmp	bl, 4Fh	; 'O'
		jb	short loc_15880
		mov	byte_24065, 0

loc_15880:
		xor	bh, bh
		add	bx, 0C8h
		jmp	short loc_1589C
sub_1586E	endp


; =============== S U B	R O U T	I N E =======================================


sub_15888	proc near
		mov	bl, byte_24064
		mov	bh, 0
		inc	byte_24064
		cmp	bl, 0C7h
		jb	short loc_1589C
		mov	byte_24064, 0

loc_1589C:
		shl	bx, 4
		add	bx, 9DA0h
		mov	word ptr [bx], 1
		push	bp
		mov	bp, sp
		mov	ax, [bp+8]
		mov	[bx+2],	ax
		mov	ax, [bp+6]
		mov	[bx+4],	ax
		push	si
		mov	si, bx
		lea	ax, [bx+0Eh]
		push	ax
		push	word ptr [bp+4]
		call	sub_1F9BA
		mov	[si+8],	ax
		pop	si
		pop	bp
		retn	6
sub_15888	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_158CC	proc far
		push	bp
		mov	bp, sp
		push	word ptr dword_2CEA0
		push	word ptr dword_2CEA0+2
		push	0C00018h
		call	sub_1597C
		pop	bp
		retf
sub_158CC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_158E2	proc near

arg_0		= word ptr  4
arg_2		= byte ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		movsx	edx, [bp+arg_0]
		mov	bl, [bp+arg_2]
		mov	bh, 0
		add	bx, bx
		movsx	eax, word ptr [bx+4AEh]
		movsx	ecx, word ptr [bx+42Eh]
		imul	eax, edx
		sar	eax, 8
		imul	edx, ecx
		sar	edx, 8
		mov	bx, [bp+arg_4]
		mov	[bx], ax
		mov	[bx+2],	dx
		pop	bp
		retn	6
sub_158E2	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1591A	proc far

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		cmp	[bp+arg_6], 1800h
		ja	short loc_15978
		cmp	[bp+arg_4], 1700h
		ja	short loc_15978
		push	si
		push	di
		mov	di, [bp+arg_0]

loc_15930:
		mov	si, word_252DC
		add	si, 5986h
		cmp	byte ptr [si], 0
		jnz	short loc_15960
		mov	word ptr [si], 1
		mov	ax, [bp+arg_6]
		mov	[si+2],	ax
		mov	ax, [bp+arg_4]
		mov	[si+4],	ax
		push	1Fh
		call	sub_157E4
		add	ax, [bp+arg_2]
		lea	bx, [si+0Ah]
		push	bx
		push	word ptr [si+0Eh]
		push	ax
		call	sub_158E2

loc_15960:
		add	word_252DC, 10h
		cmp	word_252DC, 400h
		jb	short loc_15973
		mov	word_252DC, 0

loc_15973:
		dec	di
		jnz	short loc_15930
		pop	di
		pop	si

loc_15978:
		pop	bp
		retf	8
sub_1591A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1597C	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah

		push	bp
		mov	bp, sp
		cmp	[bp+arg_6], 1800h
		ja	short loc_159E1
		cmp	[bp+arg_4], 1700h
		ja	short loc_159E1
		push	si
		push	di
		mov	di, [bp+arg_0]
		shl	di, 8

loc_15995:
		mov	si, word_252DC
		add	si, 5986h
		cmp	byte ptr [si], 0
		jnz	short loc_159C6
		mov	word ptr [si], 1
		mov	ax, [bp+arg_6]
		mov	[si+2],	ax
		mov	ax, [bp+arg_4]
		mov	[si+4],	ax
		lea	ax, [si+0Ah]
		push	ax
		xor	dx, dx
		mov	ax, di
		div	[bp+arg_0]
		xor	ah, ah
		push	ax
		push	[bp+arg_2]
		call	sub_158E2

loc_159C6:
		add	word_252DC, 10h
		cmp	word_252DC, 400h
		jb	short loc_159D9
		mov	word_252DC, 0

loc_159D9:
		sub	di, 100h
		jnz	short loc_15995
		pop	di
		pop	si

loc_159E1:
		pop	bp
		retn	8
sub_1597C	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_159E6	proc near
		mov	bx, sp
		mov	al, ss:[bx+2]
		mov	bx, ss:[bx+4]
		add	al, 3
		cmp	bx, 54h	; 'T'
		jnb	short loc_159F9
		and	al, 7Fh

loc_159F9:
		xor	ah, ah
		shr	al, 3
		add	ax, bx
		retn	4
sub_159E6	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_15A04	proc near
		cli
		mov	dx, 7Eh	; '~'
		shr	ah, 1
		sbb	al, al
		out	dx, al
		shr	ah, 1
		sbb	al, al
		out	dx, al
		shr	ah, 1
		sbb	al, al
		out	dx, al
		shr	ah, 1
		sbb	al, al
		out	dx, al
		sti
		retn
sub_15A04	endp

; ---------------------------------------------------------------------------
		mov	al, 0C0h
		out	7Ch, al
		retn
; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15A24	proc near

arg_0		= byte ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		mov	ax, word ptr dword_2CEA0+2
		sub	ax, [bp+arg_2]
		push	ax
		mov	ax, word ptr dword_2CEA0
		sub	ax, [bp+arg_4]
		push	ax
		call	iatan2
		add	al, [bp+arg_0]
		pop	bp
		retn	6
sub_15A24	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_15A42	proc near
		shr	al, 1
		mov	cl, al
		mul	byte_25FEC
		shr	ax, 5
		add	al, cl
		cmp	al, 80h
		jbe	short loc_15A55
		mov	al, 80h

loc_15A55:
		cmp	al, 8
		jnb	short locret_15A5B
		mov	al, 8

locret_15A5B:
		retn
sub_15A42	endp


; =============== S U B	R O U T	I N E =======================================


sub_15A5C	proc near
		cmp	byte_2C978, 0
		jnz	short locret_15A6E
		push	word_26006
		call	loc_15C94
		pop	word_26006

locret_15A6E:
		retn
sub_15A5C	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_15A70	proc near
		cmp	byte_2C978, 0
		jnz	short locret_15A8C
		mov	byte_221C0, 1
		push	word_26006
		call	loc_15C94
		pop	word_26006
		mov	byte_221C0, 0

locret_15A8C:
		retn
sub_15A70	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_15A8E	proc near
		mov	byte_25346, 1
		call	sub_15A5C
		mov	byte_25346, 0
		retn
sub_15A8E	endp


; =============== S U B	R O U T	I N E =======================================


sub_15A9C	proc near
		mov	byte_25346, 1
		call	sub_15A70
		mov	byte_25346, 0
		retn
sub_15A9C	endp


; =============== S U B	R O U T	I N E =======================================


sub_15AAA	proc near
		push	si
		push	di
		xor	si, si
		mov	ch, byte_25348
		mov	cl, byte ptr word_26006+1

loc_15AB6:
		mov	bl, byte_26000
		xor	bh, bh
		cmp	bx, 0Fh
		mov	di, 1
		ja	loc_15BF8
		xor	di, di
		add	bx, bx
		mov	ax, cs:off_15C16[bx]
		mov	bl, byte ptr dword_26002
		mov	bh, byte ptr dword_26002+2
		or	bl, bl
		jnz	short loc_15ADD
		inc	bl

loc_15ADD:
		jmp	ax
; ---------------------------------------------------------------------------

loc_15ADF:
		inc	di
		jmp	loc_15BE2
; ---------------------------------------------------------------------------

loc_15AE3:
		inc	di
		jmp	loc_15BF8
; ---------------------------------------------------------------------------

loc_15AE7:
		xor	ah, ah
		mov	al, ch
		div	bl
		mov	dl, byte ptr dword_26002+3
		mul	dl
		add	cl, al
		mov	al, bl
		mul	bh
		dec	al
		cmp	al, ch
		ja	short loc_15B00
		inc	di

loc_15B00:
		xor	ah, ah
		mov	al, ch
		div	bl
		mov	ch, ah
		cmp	byte_26000, 0Ah
		jz	short loc_15B83
		cmp	byte_26000, 0Bh
		jz	short loc_15B83
		jmp	short loc_15B21
; ---------------------------------------------------------------------------

loc_15B18:
		mov	al, bl
		dec	al
		cmp	al, ch
		ja	short loc_15B21
		inc	di

loc_15B21:
		xor	ah, ah
		test	bl, 1
		jz	short loc_15B4F
		or	ch, ch
		jnz	short loc_15B33
		mov	byte_25347, 0
		jmp	short loc_15B66
; ---------------------------------------------------------------------------

loc_15B33:
		test	ch, 1
		jz	short loc_15B46

loc_15B38:
		mov	al, byte ptr dword_26002+1
		add	byte_25347, al
		mov	al, byte_25347
		mov	si, ax
		jmp	short loc_15B66
; ---------------------------------------------------------------------------

loc_15B46:
		mov	al, byte_25347
		neg	al
		mov	si, ax
		jmp	short loc_15B66
; ---------------------------------------------------------------------------

loc_15B4F:
		or	ch, ch
		jnz	short loc_15B5F
		mov	al, byte ptr dword_26002+1
		shr	al, 1
		mov	byte_25347, al
		mov	si, ax
		jmp	short loc_15B66
; ---------------------------------------------------------------------------

loc_15B5F:
		test	ch, 1
		jnz	short loc_15B46
		jmp	short loc_15B38
; ---------------------------------------------------------------------------

loc_15B66:
		cmp	byte_26000, 2
		jz	loc_15BF8
		cmp	byte_26000, 8
		jz	loc_15BF8
		jmp	short loc_15BE2
; ---------------------------------------------------------------------------

loc_15B7A:
		mov	al, bl
		dec	al
		cmp	al, ch
		ja	short loc_15B83
		inc	di

loc_15B83:
		xor	al, al
		mov	ah, ch
		div	bl
		xor	ah, ah
		mov	si, ax
		cmp	byte_26000, 4
		jz	short loc_15BF8
		cmp	byte_26000, 0Ah
		jz	short loc_15BF8
		jmp	short loc_15BE2
; ---------------------------------------------------------------------------

loc_15B9D:
		mov	si, word_24062
		mov	al, [si+3582h]
		inc	byte ptr word_24062
		and	al, 1Fh
		add	cl, al

loc_15BAD:
		inc	ch
		cmp	ch, bl
		jb	short loc_15BB4
		inc	di

loc_15BB4:
		mov	si, word_24062
		mov	si, [si+3582h]
		and	si, 0FFh
		inc	byte ptr word_24062
		jmp	short loc_15BF8
; ---------------------------------------------------------------------------

loc_15BC6:
		mov	al, byte ptr dword_26002+3
		mul	ch
		add	cl, al
		mov	al, bh
		dec	al
		cmp	al, ch
		jle	short loc_15BDA
		cmp	cl, 0A0h
		jb	short loc_15BDB

loc_15BDA:
		inc	di

loc_15BDB:
		cmp	byte_26000, 6
		jz	short loc_15BF8

loc_15BE2:
		mov	byte ptr word_25349+1, cl
		push	word ptr dword_25FFC
		push	word ptr dword_25FFC+2
		push	si
		call	sub_15A24
		mov	cl, byte ptr word_25349+1
		mov	si, ax

loc_15BF8:
		push	496Bh
		mov	ax, si
		add	al, byte ptr word_26006
		push	ax
		mov	byte ptr word_25349, al
		mov	byte ptr word_25349+1, cl
		mov	al, cl
		mov	ah, 0
		push	ax
		call	sub_158E2
		mov	ax, di
		pop	di
		pop	si
		retn
sub_15AAA	endp

; ---------------------------------------------------------------------------
off_15C16	dw offset loc_15AE3
		dw offset loc_15ADF
		dw offset loc_15B18
		dw offset loc_15B18
		dw offset loc_15B7A
		dw offset loc_15B7A
		dw offset loc_15BC6
		dw offset loc_15BC6
		dw offset loc_15AE7
		dw offset loc_15AE7
		dw offset loc_15AE7
		dw offset loc_15AE7
		dw offset loc_15BAD
		dw offset loc_15B9D
		dw offset loc_15AE3
		dw offset loc_15ADF

; =============== S U B	R O U T	I N E =======================================


sub_15C36	proc near
		cmp	byte_2C979, 0
		jz	short loc_15C47
		cmp	byte_2C979, 11h
		jnb	short loc_15C47

loc_15C44:
		mov	al, 1
		retn
; ---------------------------------------------------------------------------

loc_15C47:
		mov	ax, word ptr dword_25FFC
		mov	dx, word ptr dword_25FFC+2
		cmp	ax, 0FF80h
		jle	short loc_15C44
		cmp	ax, 1880h
		jge	short loc_15C44
		cmp	dx, 0FF80h
		jle	short loc_15C44
		cmp	dx, 1780h
		jge	short loc_15C44
		sub	ax, word ptr dword_2CEA0
		add	ax, 40h
		cmp	ax, 80h
		ja	short loc_15C81
		sub	dx, word ptr dword_2CEA0+2
		add	dx, 40h
		cmp	dx, 80h
		ja	short loc_15C81
		mov	byte_2CEC1, 1

loc_15C81:
		cmp	byte_25346, 0
		jnz	short loc_15C91
		mov	al, byte ptr word_26006+1
		call	sub_15A42
		mov	byte ptr word_26006+1, al

loc_15C91:
		mov	al, 0
		retn
sub_15C36	endp

; ---------------------------------------------------------------------------

loc_15C94:
		cmp	byte ptr word_25FFA, 11h
		jz	short loc_15CA2
		cmp	byte ptr word_25FFA, 1
		jnz	short loc_15CE5

loc_15CA2:
		mov	eax, dword_25FFC
		mov	dword_2A722, eax
		mov	dword_2A726, 0
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	byte_2A72E, 9
		mov	word_2A72C, 8
		push	word_25FFA
		dec	byte ptr word_25FFA
		cmp	byte_221C0, 0
		jz	short loc_15CDD
		mov	byte ptr word_25FFA, 0FEh

loc_15CDD:
		call	sub_16999
		pop	word_25FFA

locret_15CE4:
		retn
; ---------------------------------------------------------------------------

loc_15CE5:
		call	sub_15C36
		or	al, al
		jnz	short locret_15CE4
		push	si
		push	di
		cmp	byte ptr word_25FFA+1, 0
		jnz	short loc_15CFD
		mov	si, 7426h
		mov	di, 0B4h
		jmp	short loc_15D03
; ---------------------------------------------------------------------------

loc_15CFD:
		mov	si, 8FA6h
		mov	di, 0DCh

loc_15D03:
		mov	dl, 0
		mov	al, byte ptr word_25FFA
		and	al, 0Fh
		cmp	al, 3
		jz	short loc_15D16
		cmp	al, 2
		jnz	short loc_15D18
		mov	dl, 4
		jmp	short loc_15D18
; ---------------------------------------------------------------------------

loc_15D16:
		mov	dl, 3

loc_15D18:
		cmp	byte_221C0, 0
		jnz	short loc_15D38
		mov	al, 2
		cmp	byte ptr word_26006+1, 40h
		jb	short loc_15D2F
		cmp	byte_2C979, 0
		jz	short loc_15D38

loc_15D2F:
		test	byte ptr word_25FFA, 10h
		jnz	short loc_15D38
		xor	al, al

loc_15D38:
		mov	byte ptr cs:loc_15D52+3, dl
		mov	byte ptr cs:loc_15D65+3, al
		mov	byte_25348, 0
		jmp	short $+2

loc_15D48:
		cmp	byte ptr [si], 0
		jnz	loc_15DD7
		mov	byte ptr [si], 1

loc_15D52:
		mov	byte ptr [si+12h], 7Bh
		mov	eax, dword_25FFC
		mov	[si+2],	eax
		cmp	byte_221C0, 0
		jnz	short loc_15D78

loc_15D65:
		mov	byte ptr [si+13h], 7Bh
		mov	byte ptr [si+16h], 20h ; ' '
		mov	al, 48h	; 'H'
		sub	al, byte ptr word_26006+1
		mov	[si+17h], al
		jmp	short loc_15D95
; ---------------------------------------------------------------------------

loc_15D78:
		mov	[si+1Ah], eax
		mov	byte ptr [si+13h], 1
		mov	word ptr [si+1Eh], 0
		mov	byte ptr [si+16h], 0
		mov	al, byte_2C977
		mov	[si+17h], al
		mov	al, byte_26001
		mov	[si+14h], al

loc_15D95:
		mov	byte ptr [si+1], 0
		mov	al, byte_26000
		mov	[si+0Eh], al
		call	sub_15AAA
		mov	cl, al
		mov	al, byte ptr word_25FFA+1
		mov	ah, 0
		cmp	al, 34h	; '4'
		jb	short loc_15DB5
		push	ax
		push	word_25349
		call	sub_159E6

loc_15DB5:
		mov	[si+18h], ax
		mov	eax, dword_2534B
		mov	[si+0Ah], eax
		mov	al, byte ptr word_25349
		mov	[si+11h], al
		mov	al, byte ptr word_25349+1
		mov	[si+15h], al
		mov	[si+10h], al
		or	cl, cl
		jnz	short loc_15DDF
		inc	byte_25348

loc_15DD7:
		sub	si, 20h	; ' '
		dec	di
		jnz	loc_15D48

loc_15DDF:
		pop	di
		pop	si
		retn

; =============== S U B	R O U T	I N E =======================================


sub_15DE2	proc far
		call	sub_15A5C
		retf
sub_15DE2	endp


; =============== S U B	R O U T	I N E =======================================


sub_15DE6	proc near
		movzx	bx, byte_26000
		cmp	bl, 2
		jb	short locret_15E1C
		cmp	bl, 0Dh
		ja	short locret_15E1C
		sub	bl, 2
		mov	cx, 0B9Eh
		jmp	short loc_15E44
; ---------------------------------------------------------------------------

loc_15DFD:
		cmp	al, 3
		jb	short locret_15E1C
		sub	byte ptr dword_26002, 2
		retn
; ---------------------------------------------------------------------------

loc_15E07:
		shr	dh, 2
		sub	byte ptr dword_26002+3,	dh
		cmp	ah, 2
		jb	short locret_15E1C
		dec	byte ptr dword_26002+2
		retn
; ---------------------------------------------------------------------------

loc_15E18:
		shr	byte ptr dword_26002, 1

locret_15E1C:
		retn
sub_15DE6	endp

; ---------------------------------------------------------------------------
		nop
; ---------------------------------------------------------------------------
off_15E1E	dw offset loc_15DFD
		dw offset loc_15E18
		dw offset loc_15E07
		dw offset loc_15DFD
		dw offset loc_15E18
		dw offset loc_15E18

; =============== S U B	R O U T	I N E =======================================


sub_15E2A	proc near
		movzx	bx, byte_26000
		cmp	bl, 1
		jbe	short loc_15E53
		cmp	bl, 4
		jb	short locret_15E73
		cmp	bl, 0Dh
		ja	short locret_15E73
		sub	bl, 4
		mov	cx, 0BF8h

loc_15E44:
		mov	ax, word ptr dword_26002
		mov	dx, word ptr dword_26002+2
		and	bl, 0FEh
		add	bx, cx
		jmp	word ptr cs:[bx]
; ---------------------------------------------------------------------------

loc_15E53:
		add	byte_26000, 6
		mov	word ptr dword_26002+2,	602h
		retn
; ---------------------------------------------------------------------------

loc_15E5F:
		shr	dh, 1
		add	byte ptr dword_26002+3,	dh
		retn
; ---------------------------------------------------------------------------

loc_15E66:
		shr	al, 2
		cmp	al, 6
		jbe	short loc_15E6F
		mov	al, 6

loc_15E6F:
		add	byte ptr dword_26002, al

locret_15E73:
		retn
; ---------------------------------------------------------------------------

loc_15E74:
		shr	al, 1
		jmp	short loc_15E6F
sub_15E2A	endp

; ---------------------------------------------------------------------------
off_15E78	dw offset loc_15E66
		dw offset loc_15E5F
		dw offset loc_15E5F
		dw offset loc_15E66
		dw offset loc_15E74

; =============== S U B	R O U T	I N E =======================================


sub_15E82	proc near
		movzx	bx, byte_26000
		cmp	bl, 0Dh
		ja	short locret_15EBE
		mov	cx, 0C40h
		jmp	short loc_15E44
; ---------------------------------------------------------------------------

loc_15E91:
		add	byte_26000, 2
		mov	word ptr dword_26002, 603h
		retn
; ---------------------------------------------------------------------------

loc_15E9D:
		shr	dh, 1
		add	byte ptr dword_26002+3,	dh
		inc	byte ptr dword_26002+2
		retn
; ---------------------------------------------------------------------------

loc_15EA8:
		add	byte ptr dword_26002, 2
		retn
; ---------------------------------------------------------------------------

loc_15EAE:
		xor	ah, ah
		mov	dl, 3
		div	dl
		cmp	al, 0Ch
		jbe	short loc_15EBA
		mov	al, 0Ch

loc_15EBA:
		add	byte ptr dword_26002, al

locret_15EBE:
		retn
sub_15E82	endp

; ---------------------------------------------------------------------------
		nop
; ---------------------------------------------------------------------------
		dw offset loc_15E91
		dw offset loc_15EA8
		dw offset loc_15EAE
		dw offset loc_15E9D
		dw offset loc_15EA8
		dw offset loc_15EAE
		dw offset loc_15EBA

; =============== S U B	R O U T	I N E =======================================


sub_15ECE	proc near
		mov	al, byte_26000
		and	al, 0FEh
		cmp	al, 6
		jnz	short locret_15EF2
		mov	al, byte_25FEC
		cmp	al, 26h	; '&'
		jb	short loc_15EE3
		inc	byte ptr dword_26002+2
		retn
; ---------------------------------------------------------------------------

loc_15EE3:
		cmp	al, 18h
		ja	short locret_15EF2
		cmp	byte ptr dword_26002+2,	2
		jb	short locret_15EF2
		dec	byte ptr dword_26002+2

locret_15EF2:
		retn
sub_15ECE	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_15EF4	proc near
		call	sub_15ECE
		call	sub_15DE6
		retn
sub_15EF4	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_15EFC	proc near
		call	sub_15ECE
		retn
sub_15EFC	endp


; =============== S U B	R O U T	I N E =======================================


sub_15F00	proc near
		call	sub_15ECE
		call	sub_15E2A
		retn
sub_15F00	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_15F08	proc near
		call	sub_15ECE
		call	sub_15E82
		retn
sub_15F08	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15F10	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		les	bx, dword_23F4A
		mov	di, es:[bx+1]
		mov	ax, es:[bx+3]
		mov	[bp+var_4], ax
		mov	si, 9296h
		mov	[bp+var_2], 0
		jmp	loc_16000
; ---------------------------------------------------------------------------

loc_15F30:
		cmp	byte ptr [si], 0
		jnz	loc_15FFA
		mov	byte ptr [si], 3
		mov	byte ptr [si+1], 0
		mov	byte ptr [si+18h], 0
		mov	byte ptr [si+19h], 0
		mov	word ptr [si+14h], 0
		les	bx, dword_23F4A
		mov	al, es:[bx]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+352Ah]
		mov	[si+12h], ax
		cmp	di, 3E70h
		jnz	short loc_15F6D
		push	1800h
		call	sub_157FA
		mov	di, ax

loc_15F6D:
		mov	[si+2],	di
		cmp	di, 0C00h
		jge	short loc_15F7A
		mov	al, 1
		jmp	short loc_15F7C
; ---------------------------------------------------------------------------

loc_15F7A:
		mov	al, 0

loc_15F7C:
		mov	[si+25h], al
		cmp	[bp+var_4], 3E70h
		jnz	short loc_15F8F
		push	1700h
		call	sub_157FA
		mov	[bp+var_4], ax

loc_15F8F:
		mov	ax, [bp+var_4]
		mov	[si+4],	ax
		les	bx, dword_23F4A
		mov	al, es:[bx+5]
		mov	[si+20h], al
		mov	al, es:[bx+6]
		mov	[si+36h], al
		mov	byte ptr [si+21h], 0
		cmp	byte_25FEB, 3
		jnz	short loc_15FB7
		mov	ax, 1
		jmp	short loc_15FB9
; ---------------------------------------------------------------------------

loc_15FB7:
		xor	ax, ax

loc_15FB9:
		mov	[si+23h], al
		mov	byte ptr [si+1Fh], 0
		mov	byte ptr [si+1Ch], 1
		mov	byte ptr [si+1Dh], 4
		mov	byte ptr [si+1Eh], 0
		mov	byte ptr [si+22h], 0
		mov	byte ptr [si+24h], 0
		call	sub_157D6
		mov	[si+26h], al
		mov	byte ptr [si+27h], 80h
		mov	byte ptr [si+2Eh], 0Fh
		mov	byte ptr [si+28h], 0
		mov	byte ptr [si+35h], 2Ah ; '*'
		mov	word ptr [si+2Ah], 0
		mov	word ptr [si+2Ch], 0
		mov	byte ptr [si+29h], 0
		jmp	short loc_16008
; ---------------------------------------------------------------------------

loc_15FFA:
		inc	[bp+var_2]
		add	si, 40h	; '@'

loc_16000:
		cmp	[bp+var_2], 20h	; ' '
		jl	loc_15F30

loc_16008:
		pop	di
		pop	si
		leave
		retn
sub_15F10	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1600C	proc far

var_1		= byte ptr -1

		enter	2, 0
		nop
		push	cs
		call	near ptr sub_17322
		les	bx, dword_23F4A
		mov	ax, es:[bx]
		cmp	ax, word_25FE0
		jnz	short locret_16063
		add	word ptr dword_23F4A, 2
		les	bx, dword_23F4A
		mov	al, es:[bx]
		mov	[bp+var_1], al
		inc	word ptr dword_23F4A

loc_16035:
		cmp	byte_2C98C, 0
		jnz	short loc_1603F
		call	sub_15F10

loc_1603F:
		add	word ptr dword_23F4A, 8
		dec	[bp+var_1]
		cmp	[bp+var_1], 0
		ja	short loc_16035
		les	bx, dword_23F4A
		cmp	word ptr es:[bx], 0
		jnz	short locret_16063
		setfarfp	farfp_2C926, nullsub_1

locret_16063:
		leave
		retf
sub_1600C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16065	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, 7
		mov	si, [bp+arg_0]
		mov	di, 561Ah
		push	ds
		pop	es
		assume es:dseg
		rep movsw
		pop	di
		pop	si
		pop	bp
		retn	2
sub_16065	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1607D	proc far

var_2		= byte ptr -2
var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		mov	word ptr dword_2C922, 0C190h
		mov	word ptr dword_2C922+2,	0C190h
		mov	word_2CED6, 100h
		mov	word_2CED8, 0C0h
		mov	[bp+var_2], 0
		mov	si, 9296h
		xor	di, di
		jmp	loc_16251
; ---------------------------------------------------------------------------

loc_160A7:
		cmp	byte ptr [si], 0
		jz	loc_1624D
		cmp	byte ptr [si], 2
		jnz	short loc_160B9
		mov	byte ptr [si], 0
		jmp	loc_1624D
; ---------------------------------------------------------------------------

loc_160B9:
		mov	word_2C92A, si
		cmp	byte ptr [si], 80h
		jnb	loc_16221
		call	sub_1535A
		cmp	byte ptr [si+24h], 0
		jz	short loc_160F2
		mov	ax, [si+2]
		sub	ax, word ptr dword_2CEA0
		add	ax, 0C0h
		cmp	ax, 180h
		jnb	short loc_160F2
		mov	ax, [si+4]
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 0C0h
		cmp	ax, 180h
		jnb	short loc_160F2
		mov	byte_2CEC1, 1
		jmp	short loc_16161
; ---------------------------------------------------------------------------

loc_160F2:
		cmp	byte ptr [si+22h], 0
		jz	loc_161C6
		cmp	word ptr [si+0Eh], 0FFFFh
		jz	loc_161C6
		mov	ax, [si+2]
		add	ax, 100h
		cmp	ax, 1A00h
		jnb	loc_161C6
		mov	ax, [si+4]
		add	ax, 100h
		cmp	ax, 1800h
		jnb	loc_161C6
		inc	[bp+var_2]
		mov	ax, [si+4]
		cmp	ax, word ptr dword_2C922+2
		jle	short loc_16134
		mov	ax, [si+2]
		mov	word ptr dword_2C922, ax
		mov	ax, [si+4]
		mov	word ptr dword_2C922+2,	ax

loc_16134:
		mov	eax, [si+2]
		mov	dword_2CED2, eax
		call	sub_126B3
		mov	[bp+var_1], al
		cmp	[bp+var_1], 0
		jz	short loc_161C6
		cmp	word ptr [si+0Eh], 0FFFEh
		jz	short loc_161BF
		mov	ah, 0
		cmp	ax, [si+0Eh]
		jge	short loc_16161
		mov	al, [bp+var_1]
		mov	ah, 0
		sub	[si+0Eh], ax
		jmp	short loc_161B9
; ---------------------------------------------------------------------------

loc_16161:
		mov	byte ptr [si], 80h
		mov	byte ptr [si+1Ch], 1
		mov	byte ptr [si+22h], 0
		mov	byte ptr [si+24h], 0
		mov	word ptr [si+0Ah], 0
		mov	word ptr [si+0Ch], 0
		cmp	byte ptr [si+20h], 0FEh
		jz	short loc_1618C
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	word ptr [si+20h]
		call	sub_16D84

loc_1618C:
		call	snd_se_play pascal, 3
		movzx	eax, word ptr [si+10h]
		add	dword_2CE1A, eax
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	400007h
		nopcall	sub_1591A
		inc	word_221C2
		inc	word_221C4
		jmp	loc_1624D
; ---------------------------------------------------------------------------

loc_161B9:
		mov	byte ptr [si+21h], 1
		jmp	short loc_161C6
; ---------------------------------------------------------------------------

loc_161BF:
		call	snd_se_play pascal, 10

loc_161C6:
		cmp	byte ptr [si+23h], 0
		jz	short loc_1621C
		inc	byte ptr [si+26h]
		mov	al, [si+26h]
		cmp	al, [si+27h]
		jb	short loc_1621C
		cmp	word ptr [si+4], 1300h
		jge	short loc_1621C
		mov	ax, [si+2]
		sub	ax, word ptr dword_2CEA0
		add	ax, 300h
		cmp	ax, 600h
		jnb	short loc_161FC
		mov	ax, [si+4]
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 300h
		cmp	ax, 600h
		jb	short loc_1621C

loc_161FC:
		mov	byte ptr [si+26h], 0
		lea	ax, [si+28h]
		push	ax
		call	sub_16065
		mov	ax, [si+2]
		add	word ptr dword_25FFC, ax
		mov	ax, [si+4]
		add	word ptr dword_25FFC+2,	ax
		call	fp_25344
		call	sub_15A5C

loc_1621C:
		inc	byte ptr [si+1]
		jmp	short loc_1624D
; ---------------------------------------------------------------------------

loc_16221:
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		mov	al, [si]
		inc	al
		mov	[si], al
		mov	[bp+var_1], al
		mov	ah, 0
		add	ax, 0FF80h
		mov	bx, 4
		cwd
		idiv	bx
		add	al, 4
		mov	[bp+var_1], al
		mov	[si+17h], al
		cmp	[bp+var_1], 0Ch
		jb	short loc_1624D
		mov	byte ptr [si], 2

loc_1624D:
		inc	di
		add	si, 40h

loc_16251:
		cmp	di, 20h	; ' '
		jl	loc_160A7
		cmp	word ptr dword_2C922, 0C190h
		jz	short loc_162B9
		cmp	[bp+var_2], 8
		jb	short loc_1626C
		mov	[bp+var_2], 50h	; 'P'
		jmp	short loc_16279
; ---------------------------------------------------------------------------

loc_1626C:
		mov	al, [bp+var_2]
		shl	al, 3
		mov	dl, 90h
		sub	dl, al
		mov	[bp+var_2], dl

loc_16279:
		mov	al, byte_25FEA
		shl	al, 4
		mov	dl, [bp+var_2]
		sub	dl, al
		mov	[bp+var_2], dl
		cmp	[bp+var_2], 90h
		ja	short loc_16293
		cmp	[bp+var_2], 4
		jnb	short loc_16297

loc_16293:
		mov	[bp+var_2], 4

loc_16297:
		mov	al, [bp+var_2]
		mov	ah, 0
		push	ax
		mov	ax, word_25FE0
		xor	dx, dx
		pop	bx
		div	bx
		or	dx, dx
		jnz	short loc_162B9
		cmp	byte_2CEC3, 80h
		jnb	short loc_162B9
		inc	byte_2CEC3
		call	sub_1059D

loc_162B9:
		pop	di
		pop	si
		leave
		retf
sub_1607D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_162BD	proc far
		push	bp
		mov	bp, sp
		mov	byte_2C93C, 0
		mov	byte_2C94C, 0
		pop	bp
		retf
sub_162BD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_162CC	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, 0BF5Ch
		cmp	byte ptr [si], 0
		jz	short loc_162DB
		add	si, 10h

loc_162DB:
		mov	byte ptr [si], 1
		mov	byte ptr [si+1], 0
		mov	ax, word_26335+1
		mov	[si+2],	ax
		mov	ax, word_26338
		mov	[si+4],	ax
		mov	word ptr [si+6], 8
		mov	word ptr [si+8], 8
		mov	word ptr [si+0Ah], 0B0h	; '°'
		mov	word ptr [si+0Ch], 0B0h	; '°'
		mov	byte ptr [si+0Fh], 0
		mov	bx, [bp+arg_0]
		dec	bx
		cmp	bx, 3
		ja	short loc_16338
		add	bx, bx
		jmp	cs:off_16344[bx]

loc_16316:
		mov	byte ptr [si+0Fh], 20h ; ' '
		jmp	short loc_16338
; ---------------------------------------------------------------------------

loc_1631C:
		mov	byte ptr [si+0Fh], 0E0h
		jmp	short loc_16338
; ---------------------------------------------------------------------------

loc_16322:
		mov	word ptr [si+0Ah], 0D0h
		mov	word ptr [si+0Ch], 70h ; 'p'
		jmp	short loc_16338
; ---------------------------------------------------------------------------

loc_1632E:
		mov	word ptr [si+0Ah], 70h ; 'p'
		mov	word ptr [si+0Ch], 0D0h

loc_16338:
		call	snd_se_play pascal, 15
		pop	si
		pop	bp
		retn	2
sub_162CC	endp

; ---------------------------------------------------------------------------
off_16344	dw offset loc_16316
		dw offset loc_1631C
		dw offset loc_16322
		dw offset loc_1632E

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1634C	proc near

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	4, 0
		mov	ax, word_26335+1
		mov	[bp+var_2], ax
		mov	ax, word_26338
		mov	[bp+var_4], ax
		mov	eax, dword_2634E
		mov	dword ptr word_26335+1,	eax
		push	[bp+arg_0]
		call	sub_162CC
		mov	ax, [bp+var_2]
		mov	word_26335+1, ax
		mov	ax, [bp+var_4]
		mov	word_26338, ax
		leave
		retn	2
sub_1634C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1637A	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	si, 0BF7Ch
		mov	byte ptr [si], 1
		mov	byte ptr [si+1], 0
		mov	ax, word_26335+1
		mov	[si+2],	ax
		mov	ax, word_26338
		mov	[si+4],	ax
		mov	word ptr [si+6], 8
		mov	word ptr [si+8], 8
		mov	word ptr [si+0Ah], 0C0h
		mov	word ptr [si+0Ch], 0C0h
		mov	byte ptr [si+0Fh], 0
		call	snd_se_play pascal, 12
		pop	si
		pop	bp
		retn
sub_1637A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_163B6	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		mov	ax, word_26335+1
		mov	[bp+var_2], ax
		mov	ax, word_26338
		mov	[bp+var_4], ax
		mov	eax, dword_2634E
		mov	dword ptr word_26335+1,	eax
		call	sub_1637A
		mov	ax, [bp+var_2]
		mov	word_26335+1, ax
		mov	ax, [bp+var_4]
		mov	word_26338, ax
		leave
		retn
sub_163B6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_163DF	proc near

var_2		= word ptr -2
arg_0		= dword	ptr  4
arg_4		= word ptr  8
arg_6		= word ptr  0Ah
arg_8		= word ptr  0Ch

		enter	2, 0
		push	si
		mov	si, [bp+arg_4]
		movsx	eax, si
		les	bx, [bp+arg_0]
		assume es:nothing
		imul	eax, es:[bx]
		mov	es:[bx], eax
		mov	eax, es:[bx]
		mov	ebx, 0Ah
		xor	edx, edx
		div	ebx
		mov	bx, word ptr [bp+arg_0]
		mov	es:[bx], eax
		cmp	si, 0Ah
		jge	short loc_16418
		mov	ax, TX_RED
		jmp	short loc_1641B
; ---------------------------------------------------------------------------

loc_16418:
		mov	ax, TX_GREEN

loc_1641B:
		mov	[bp+var_2], ax
		push	6
		push	[bp+arg_8]
		push	ds
		mov	bx, [bp+arg_6]
		add	bx, bx
		push	word ptr [bx+1896h]
		push	ax
		call	text_putsa
		pop	si
		leave
		retn	0Ah
sub_163DF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16438	proc near

arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		cmp	byte ptr word_2634A+1, 0
		jnz	short loc_1644D
		push	140000h
		push	0
		jmp	loc_164FD
; ---------------------------------------------------------------------------

loc_1644D:
		les	bx, dword_23EF0
		mov	al, es:[bx+0Dh]
		mov	ah, 0
		cmp	ax, 4
		jz	short loc_1647C
		cmp	ax, 5
		jz	short loc_16472
		cmp	ax, 6
		jz	short loc_16468
		jmp	short loc_1648B
; ---------------------------------------------------------------------------

loc_16468:
		push	120001h
		push	3
		jmp	short loc_16484
; ---------------------------------------------------------------------------

loc_16472:
		push	120002h
		push	5
		jmp	short loc_16484
; ---------------------------------------------------------------------------

loc_1647C:
		push	120003h
		push	7

loc_16484:
		pushd	[bp+arg_0]
		call	sub_163DF

loc_1648B:
		mov	al, byte_2CE0A
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_164A1
		cmp	ax, 2
		jz	short loc_164AB
		cmp	ax, 3
		jz	short loc_164B5
		jmp	short loc_164C4
; ---------------------------------------------------------------------------

loc_164A1:
		push	130004h
		push	8
		jmp	short loc_164BD
; ---------------------------------------------------------------------------

loc_164AB:
		push	130005h
		push	6
		jmp	short loc_164BD
; ---------------------------------------------------------------------------

loc_164B5:
		push	130006h
		push	4

loc_164BD:
		pushd	[bp+arg_0]
		call	sub_163DF

loc_164C4:
		mov	al, byte_25FEB
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	short loc_16504
		add	bx, bx
		jmp	cs:off_16508[bx]

loc_164D7:
		push	140007h
		push	5
		jmp	short loc_164FD
; ---------------------------------------------------------------------------

loc_164E1:
		push	140008h
		push	0Ah
		jmp	short loc_164FD
; ---------------------------------------------------------------------------

loc_164EB:
		push	140009h
		push	0Ch
		jmp	short loc_164FD
; ---------------------------------------------------------------------------

loc_164F5:
		push	14000Ah
		push	0Eh

loc_164FD:
		pushd	[bp+arg_0]
		call	sub_163DF

loc_16504:
		pop	bp
		retn	4
sub_16438	endp

; ---------------------------------------------------------------------------
off_16508	dw offset loc_164D7
		dw offset loc_164E1
		dw offset loc_164EB
		dw offset loc_164F5

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16510	proc near

var_6		= byte ptr -6
var_5		= byte ptr -5
var_4		= dword	ptr -4

		enter	6, 0
		push	si
		les	bx, dword_23EF0
		mov	al, es:[bx+1Bh]
		cmp	al, byte_22274
		jnz	short loc_16528
		mov	ax, 1
		jmp	short loc_1652A
; ---------------------------------------------------------------------------

loc_16528:
		xor	ax, ax

loc_1652A:
		mov	[bp+var_5], al
		les	bx, dword_23EF0
		mov	al, es:[bx+1Bh]
		mov	byte_22274, al
		mov	al, es:[bx+1Ch]
		cmp	al, byte_22275
		jnz	short loc_1654D
		cmp	[bp+var_5], 0
		jz	short loc_1654D
		mov	ax, 1
		jmp	short loc_1654F
; ---------------------------------------------------------------------------

loc_1654D:
		xor	ax, ax

loc_1654F:
		mov	[bp+var_6], al
		les	bx, dword_23EF0
		mov	al, es:[bx+1Ch]
		mov	byte_22275, al
		mov	PaletteTone, 3Ch	; '<'
		call	far ptr	palette_show
		call	gaiji_putsa pascal, (20 shl 16) + 4, ds, offset gpCLEAR_BONUS, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 8, ds, BONUS_STAGE, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 10, ds, BONUS_DREAM, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 12, ds, GRAZEX50, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 14, ds, POINT_ITEMS, TX_WHITE
		cmp	[bp+var_5], 0
		jz	short loc_165DF
		call	text_putsa pascal, (6 shl 16) + 16, ds, BONUS_NOMISS, TX_CYAN

loc_165DF:
		cmp	[bp+var_6], 0
		jz	short loc_165F8
		call	text_putsa pascal, (6 shl 16) + 17, ds, BONUS_NOBOMB, TX_CYAN

loc_165F8:
		call	text_putsa pascal, (6 shl 16) + 21, ds, BONUS_TOTAL, TX_WHITE
		mov	al, byte_25FEA
		mov	ah, 0
		imul	ax, 64h
		add	ax, 64h	; 'd'
		mov	si, ax
		movzx	eax, si
		mov	[bp+var_4], eax
		push	220008h
		push	eax
		nopcall	sub_1FA0E
		mov	al, byte_2CEC3
		mov	ah, 0
		imul	ax, 0Ah
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	22000Ah
		push	eax
		nopcall	sub_1FA0E
		mov	ax, word_2C97A
		imul	ax, 5
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	22000Ch
		push	eax
		nopcall	sub_1FA0E
		mov	si, word_2CEC6
		movzx	eax, si
		imul	eax, [bp+var_4]
		mov	[bp+var_4], eax
		push	28000Eh
		push	si
		push	0E1h
		nopcall	sub_1F9F4
		mov	al, byte_25FEA
		mov	ah, 0
		imul	ax, 1388h
		add	ax, 2710h
		mov	si, ax
		cmp	[bp+var_5], 0
		jz	short loc_166B2
		movzx	eax, si
		add	[bp+var_4], eax
		push	220010h
		push	eax
		nopcall	sub_1FA0E

loc_166B2:
		cmp	[bp+var_6], 0
		jz	short loc_166CD
		movzx	eax, si
		add	[bp+var_4], eax
		push	220011h
		push	eax
		nopcall	sub_1FA0E

loc_166CD:
		cmp	[bp+var_4], 124F80h
		jb	short loc_166DB
		push	4
		jmp	short loc_166F5
; ---------------------------------------------------------------------------

loc_166DB:
		cmp	[bp+var_4], 0C3500h
		jb	short loc_166E9
		push	2
		jmp	short loc_166F5
; ---------------------------------------------------------------------------

loc_166E9:
		cmp	[bp+var_4], 7A120h
		jb	short loc_166FC
		push	1

loc_166F5:
		call	sub_E720
		jmp	short loc_1671B
; ---------------------------------------------------------------------------

loc_166FC:
		cmp	[bp+var_4], 186A0h
		ja	short loc_1670A
		push	2
		jmp	short loc_16716
; ---------------------------------------------------------------------------

loc_1670A:
		cmp	[bp+var_4], 30D40h
		ja	short loc_1671B
		push	1

loc_16716:
		call	sub_E73A

loc_1671B:
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_16438
		push	220015h
		pushd	[bp+var_4]
		nopcall	sub_1FA0E
		mov	eax, [bp+var_4]
		add	dword_2CE1A, eax
		pop	si
		leave
		retn
sub_16510	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1673E	proc near

var_A		= byte ptr -0Ah
var_9		= byte ptr -9
var_8		= dword	ptr -8
var_4		= dword	ptr -4

		enter	0Ah, 0
		push	si
		les	bx, dword_23EF0
		mov	al, es:[bx+1Bh]
		cmp	al, byte_22274
		jnz	short loc_16756
		mov	ax, 1
		jmp	short loc_16758
; ---------------------------------------------------------------------------

loc_16756:
		xor	ax, ax

loc_16758:
		mov	[bp+var_9], al
		les	bx, dword_23EF0
		mov	al, es:[bx+1Bh]
		mov	byte_22274, al
		mov	al, es:[bx+1Ch]
		cmp	al, byte_22275
		jnz	short loc_1677B
		cmp	[bp+var_9], 0
		jz	short loc_1677B
		mov	ax, 1
		jmp	short loc_1677D
; ---------------------------------------------------------------------------

loc_1677B:
		xor	ax, ax

loc_1677D:
		mov	[bp+var_A], al
		les	bx, dword_23EF0
		mov	al, es:[bx+1Ch]
		mov	byte_22275, al
		mov	PaletteTone, 3Ch	; '<'
		call	far ptr	palette_show
		mov	byte_226C4, 0Ah
		call	gaiji_putsa pascal, (19 shl 16) + 4, ds, offset gpCONGRATULATION, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 6, ds, ALL_CLEAR, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 8, ds, BONUS_DREAM, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 10, ds, GRAZEX50, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 12, ds, PLAYER_REM, TX_WHITE
		call	text_putsa pascal, (6 shl 16) + 14, ds, POINT_ITEMS, TX_WHITE
		cmp	[bp+var_9], 0
		jz	short loc_16825
		call	text_putsa pascal, (6 shl 16) + 16, ds, BONUS_NOMISS, TX_CYAN

loc_16825:
		cmp	[bp+var_A], 0
		jz	short loc_1683E
		call	text_putsa pascal, (6 shl 16) + 17, ds, BONUS_NOBOMB, TX_CYAN

loc_1683E:
		call	text_putsa pascal, (6 shl 16) + 18, ds, POINT_TOTAL, TX_CYAN
		call	text_putsa pascal, (6 shl 16) + 21, ds, BONUS_TOTAL, TX_WHITE
		mov	si, 3E8h
		movzx	eax, si
		mov	[bp+var_4], eax
		push	220006h
		push	eax
		nopcall	sub_1FA0E
		mov	al, byte_2CEC3
		mov	ah, 0
		imul	ax, 0Ah
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	220008h
		push	eax
		nopcall	sub_1FA0E
		mov	ax, word_2C97A
		imul	ax, 5
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	22000Ah
		push	eax
		nopcall	sub_1FA0E
		mov	al, byte_25350
		mov	ah, 0
		imul	ax, 3E8h
		add	ax, 0FC18h
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	22000Ch
		push	eax
		nopcall	sub_1FA0E
		mov	si, word_2CEC6
		movzx	eax, si
		imul	eax, [bp+var_4]
		mov	[bp+var_4], eax
		push	28000Eh
		push	si
		push	0E1h
		nopcall	sub_1F9F4
		mov	[bp+var_8], 0C350h
		cmp	[bp+var_9], 0
		jz	short loc_1691E
		mov	eax, [bp+var_8]
		add	[bp+var_4], eax
		push	220010h
		push	eax
		nopcall	sub_1FA0E

loc_1691E:
		cmp	[bp+var_A], 0
		jz	short loc_16939
		mov	eax, [bp+var_8]
		add	[bp+var_4], eax
		push	220011h
		push	eax
		nopcall	sub_1FA0E

loc_16939:
		movzx	eax, word_22648
		imul	eax, 0FAh
		mov	[bp+var_8], eax
		add	[bp+var_4], eax
		push	220012h
		push	eax
		nopcall	sub_1FA0E
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_16438
		push	220015h
		pushd	[bp+var_4]
		nopcall	sub_1FA0E
		mov	eax, [bp+var_4]
		add	dword_2CE1A, eax
		pop	si
		leave
		retn
sub_1673E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1697E	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, 7
		push	ds
		pop	es
		assume es:dseg
		mov	si, 561Ah
		mov	di, [bp+arg_0]
		add	di, 18h
		rep movsw
		pop	di
		pop	si
		pop	bp
		retn	2
sub_1697E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16999	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 9A96h
		xor	di, di
		jmp	short loc_169FA
; ---------------------------------------------------------------------------

loc_169A5:
		cmp	byte ptr [si], 0
		jnz	short loc_169F6
		mov	byte ptr [si], 1
		push	si
		call	sub_1697E
		mov	ax, word ptr dword_2A722
		mov	[si+2],	ax
		mov	ax, word ptr dword_2A722+2
		mov	[si+4],	ax
		mov	ax, word_2A72A
		mov	[si+0Eh], ax
		mov	[si+14h], ax
		mov	ax, word ptr dword_2A726
		mov	[si+0Ah], ax
		mov	ax, word ptr dword_2A726+2
		mov	[si+0Ch], ax
		mov	byte ptr [si+12h], 0
		mov	al, byte_2A72F
		mov	[si+13h], al
		mov	al, byte_2A72E
		mov	[si+1],	al
		mov	ax, word_2A72C
		mov	[si+10h], ax
		mov	ax, word_2A72A
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		mov	[si+16h], ax
		jmp	short loc_169FF
; ---------------------------------------------------------------------------

loc_169F6:
		inc	di
		add	si, 26h	; '&'

loc_169FA:
		cmp	di, 8
		jl	short loc_169A5

loc_169FF:
		pop	di
		pop	si
		pop	bp
		retn
sub_16999	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16A03	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	si, 9A96h
		xor	cx, cx
		jmp	short loc_16A63
; ---------------------------------------------------------------------------

loc_16A0E:
		cmp	byte ptr [si], 0
		jnz	short loc_16A5F
		mov	byte ptr [si], 1
		mov	byte ptr [si+18h], 0FFh
		mov	ax, word ptr dword_2A722
		mov	[si+2],	ax
		mov	ax, word ptr dword_2A722+2
		mov	[si+4],	ax
		mov	ax, word_2A72A
		mov	[si+0Eh], ax
		mov	[si+14h], ax
		mov	ax, word ptr dword_2A726
		mov	[si+0Ah], ax
		mov	ax, word ptr dword_2A726+2
		mov	[si+0Ch], ax
		mov	byte ptr [si+12h], 0
		mov	al, byte_2A72F
		mov	[si+13h], al
		mov	al, byte_2A72E
		mov	[si+1],	al
		mov	ax, word_2A72C
		mov	[si+10h], ax
		mov	ax, word_2A72A
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		mov	[si+16h], ax
		jmp	short loc_16A68
; ---------------------------------------------------------------------------

loc_16A5F:
		inc	cx
		add	si, 26h	; '&'

loc_16A63:
		cmp	cx, 8
		jl	short loc_16A0E

loc_16A68:
		pop	si
		pop	bp
		retn
sub_16A03	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16A6B	proc near

arg_0		= byte ptr  4
arg_2		= byte ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		mov	ax, [bp+arg_4]
		or	ax, ax
		jz	short loc_16A83
		cmp	ax, 2
		jz	short loc_16A88
		cmp	ax, 4
		jz	short loc_16A8E
		pop	bp
		retn	6
; ---------------------------------------------------------------------------

loc_16A83:
		mov	al, [bp+arg_2]
		jmp	short loc_16A8B
; ---------------------------------------------------------------------------

loc_16A88:
		mov	al, [bp+arg_0]

loc_16A8B:
		mov	byte_2A72E, al

loc_16A8E:
		call	sub_16A03
		pop	bp
		retn	6
sub_16A6B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16A95	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, 7
		push	ds
		pop	es
		mov	di, 561Ah
		mov	si, [bp+arg_0]
		add	si, 18h
		rep movsw
		pop	di
		pop	si
		pop	bp
		retn	2
sub_16A95	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16AB0	proc far
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 9A96h
		xor	di, di
		jmp	short loc_16B1B
; ---------------------------------------------------------------------------

loc_16ABC:
		cmp	byte ptr [si], 0
		jz	short loc_16B17
		cmp	byte ptr [si], 2
		jb	short loc_16ACB
		mov	byte ptr [si], 0
		jmp	short loc_16B17
; ---------------------------------------------------------------------------

loc_16ACB:
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		mov	ax, [si+0Eh]
		mov	[si+14h], ax
		mov	ax, [si+16h]
		sub	[si+0Eh], ax
		mov	al, [si+13h]
		add	[si+12h], al
		cmp	word ptr [si+0Eh], 20h ; ' '
		jge	short loc_16B17
		mov	byte ptr [si], 2
		cmp	byte ptr [si+18h], 0FFh
		jz	short loc_16B17
		push	si
		call	sub_16A95
		mov	ax, [si+2]
		mov	word ptr dword_25FFC, ax
		mov	ax, [si+4]
		mov	word ptr dword_25FFC+2,	ax
		cmp	byte ptr word_25FFA, 0FEh
		jnb	short loc_16B0F
		call	sub_15A5C
		jmp	short loc_16B17
; ---------------------------------------------------------------------------

loc_16B0F:
		mov	byte ptr word_25FFA, 0
		call	sub_15A70

loc_16B17:
		inc	di
		add	si, 26h	; '&'

loc_16B1B:
		cmp	di, 8
		jl	short loc_16ABC
		pop	di
		pop	si
		pop	bp
		retf
sub_16AB0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16B24	proc near
		push	bp
		mov	bp, sp
		cmp	word ptr dword_252DE, 0FFC0h
		jle	short loc_16B4A
		cmp	word ptr dword_252DE, 1840h
		jge	short loc_16B4A
		cmp	word ptr dword_252DE+2,	0FFC0h
		jle	short loc_16B4A
		cmp	word ptr dword_252DE+2,	1740h
		jge	short loc_16B4A
		mov	ax, 1
		jmp	short loc_16B4C
; ---------------------------------------------------------------------------

loc_16B4A:
		xor	ax, ax

loc_16B4C:
		pop	bp
		retn
sub_16B24	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16B4E	proc far

var_4		= byte ptr -4
var_3		= byte ptr -3
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		mov	ax, 0A800h
		mov	es, ax
		assume es:nothing
		mov	[bp+var_4], 0FFh
		mov	si, 9A96h
		mov	[bp+var_2], 0
		jmp	short loc_16BCF
; ---------------------------------------------------------------------------

loc_16B67:
		cmp	byte ptr [si], 1
		jnz	short loc_16BC9
		mov	al, [si+1]
		cmp	al, [bp+var_4]
		jz	short loc_16B7D
		mov	[bp+var_4], al
		mov	ah, [bp+var_4]
		call	sub_15A04

loc_16B7D:
		xor	di, di
		jmp	short loc_16BC4
; ---------------------------------------------------------------------------

loc_16B81:
		mov	ax, di
		shl	ax, 8
		cwd
		idiv	word ptr [si+10h]
		add	al, [si+12h]
		mov	[bp+var_3], al
		push	48FEh
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	word ptr [si+0Eh]
		mov	ah, 0
		push	ax
		call	sub_14E6C
		call	sub_16B24
		or	al, al
		jz	short loc_16BC3
		mov	ax, word ptr dword_252DE+2
		add	ax, 0C0h
		push	ax
		call	sub_15288
		mov	dx, ax
		mov	ax, word ptr dword_252DE
		sar	ax, 4
		add	ax, 1Ch
		call	sub_15814

loc_16BC3:
		inc	di

loc_16BC4:
		cmp	[si+10h], di
		jg	short loc_16B81

loc_16BC9:
		inc	[bp+var_2]
		add	si, 26h	; '&'

loc_16BCF:
		cmp	[bp+var_2], 8
		jl	short loc_16B67
		pop	di
		pop	si
		leave
		retf
sub_16B4E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16BD9	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		or	si, si
		jnz	short loc_16C35
		cmp	word_26335+1, 900h
		jge	short loc_16BF5
		push	60h
		call	sub_157FA
		sub	al, 30h	; '0'
		jmp	short loc_16C09
; ---------------------------------------------------------------------------

loc_16BF5:
		cmp	word_26335+1, 0F00h
		jle	short loc_16C06
		push	60h
		call	sub_157E4
		add	al, 30h	; '0'
		jmp	short loc_16C09
; ---------------------------------------------------------------------------

loc_16C06:
		call	sub_157D6

loc_16C09:
		mov	byte ptr word_2634A, al
		cmp	byte_2C974, 1
		jnz	short loc_16C1A
		cmp	byte ptr word_2634A, 80h
		jb	short loc_16C28

loc_16C1A:
		cmp	byte_2C974, 2
		jnz	short loc_16C30
		cmp	byte ptr word_2634A, 80h
		jb	short loc_16C30

loc_16C28:
		mov	al, byte ptr word_2634A
		neg	al
		mov	byte ptr word_2634A, al

loc_16C30:
		mov	byte_2C974, 0

loc_16C35:
		or	si, si
		jl	loc_16CC5
		push	595Eh
		push	word_2634A
		mov	ax, si
		add	ax, ax
		mov	dx, 40h
		sub	dx, ax
		push	dx
		call	sub_158E2
		mov	ax, word_2633E
		add	word_26335+1, ax
		mov	ax, word_26340
		add	word_26338, ax
		cmp	word_2633E, 0
		jge	short loc_16C69
		mov	al, byte ptr word_2C96E
		jmp	short loc_16C6C
; ---------------------------------------------------------------------------

loc_16C69:
		mov	al, byte ptr word_2C970

loc_16C6C:
		mov	byte_26344, al
		mov	ax, word_26338
		cmp	ax, word_22586
		jge	short loc_16C85
		mov	ax, word_22586
		mov	word_26338, ax
		mov	byte_2C974, 2
		jmp	short loc_16C99
; ---------------------------------------------------------------------------

loc_16C85:
		mov	ax, word_26338
		cmp	ax, word_22588
		jle	short loc_16C99
		mov	ax, word_22588
		mov	word_26338, ax
		mov	byte_2C974, 1

loc_16C99:
		mov	ax, word_26335+1
		cmp	ax, word_22582
		jge	short loc_16CA7
		mov	ax, word_22582
		jmp	short loc_16CB3
; ---------------------------------------------------------------------------

loc_16CA7:
		mov	ax, word_26335+1
		cmp	ax, word_22584
		jle	short loc_16CB6
		mov	ax, word_22584

loc_16CB3:
		mov	word_26335+1, ax

loc_16CB6:
		cmp	si, 1Ch
		jl	short loc_16CC5
		mov	al, byte ptr word_2C972
		mov	byte_26344, al
		mov	al, 1
		jmp	short loc_16CC7
; ---------------------------------------------------------------------------

loc_16CC5:
		mov	al, 0

loc_16CC7:
		pop	si
		pop	bp
		retn	2
sub_16BD9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16CCC	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	di, [bp+arg_2]
		xor	si, si
		mov	ax, di
		sub	ax, word_26335+1
		mov	cx, ax
		mov	bx, 10h
		cwd
		idiv	bx
		or	ax, ax
		jz	short loc_16CEC
		mov	ax, cx
		jmp	short loc_16CFA
; ---------------------------------------------------------------------------

loc_16CEC:
		mov	ax, cx
		mov	bx, 4
		cwd
		idiv	bx
		or	ax, ax
		jz	short loc_16D03
		mov	ax, cx

loc_16CFA:
		cwd
		idiv	bx
		add	word_26335+1, ax
		jmp	short loc_16D08
; ---------------------------------------------------------------------------

loc_16D03:
		mov	word_26335+1, di
		inc	si

loc_16D08:
		or	cx, cx
		jge	short loc_16D11
		mov	al, byte ptr word_2C96E
		jmp	short loc_16D14
; ---------------------------------------------------------------------------

loc_16D11:
		mov	al, byte ptr word_2C970

loc_16D14:
		mov	byte_26344, al
		mov	ax, [bp+arg_0]
		sub	ax, word_26338
		mov	cx, ax
		mov	bx, 10h
		cwd
		idiv	bx
		or	ax, ax
		jz	short loc_16D31
		mov	ax, cx
		cwd
		idiv	bx
		jmp	short loc_16D43
; ---------------------------------------------------------------------------

loc_16D31:
		mov	ax, cx
		cwd
		sub	ax, dx
		sar	ax, 1
		or	ax, ax
		jz	short loc_16D49
		mov	ax, cx
		cwd
		sub	ax, dx
		sar	ax, 1

loc_16D43:
		add	word_26338, ax
		jmp	short loc_16D50
; ---------------------------------------------------------------------------

loc_16D49:
		mov	ax, [bp+arg_0]
		mov	word_26338, ax
		inc	si

loc_16D50:
		cmp	si, 2
		jz	short loc_16D59
		mov	al, 0
		jmp	short loc_16D61
; ---------------------------------------------------------------------------

loc_16D59:
		mov	al, byte ptr word_2C972
		mov	byte_26344, al
		mov	al, 1

loc_16D61:
		pop	di
		pop	si
		pop	bp
		retn	4
sub_16CCC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16D67	proc far
		push	bp
		mov	bp, sp
		call	IRand
		and	al, 0Fh
		mov	byte_2C98A, al
		call	sub_178D7
		mov	byte_2264E, 0
		mov	word_2C986, 0
		pop	bp
		retf
sub_16D67	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16D84	proc near

arg_0		= byte ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	byte_2264E, 0
		jz	short loc_16DA0
		cmp	[bp+arg_0], 3
		jb	short loc_16D9C
		cmp	[bp+arg_0], 0FFh
		jnz	short loc_16DA0

loc_16D9C:
		mov	[bp+arg_0], 0

loc_16DA0:
		cmp	[bp+arg_0], 0FFh
		jnz	short loc_16DCA
		inc	byte_2C98A
		test	byte_2C98A, 1
		jnz	short loc_16E23
		mov	al, byte_2C98A
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	bx, 40h
		cwd
		idiv	bx
		mov	bx, dx
		mov	al, [bx+1BACh]
		mov	[bp+arg_0], al

loc_16DCA:
		mov	si, 0AF20h
		xor	di, di
		jmp	short loc_16E1E
; ---------------------------------------------------------------------------

loc_16DD1:
		cmp	byte ptr [si], 0
		jnz	short loc_16E1A
		mov	byte ptr [si], 1
		mov	byte ptr [si+0Fh], 0
		mov	ax, [bp+arg_4]
		mov	[si+2],	ax
		mov	ax, [bp+arg_2]
		mov	[si+4],	ax
		mov	word ptr [si+0Ah], 0
		mov	word ptr [si+0Ch], 0FFD0h
		mov	al, [bp+arg_0]
		mov	[si+0Eh], al
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+1BEEh]
		mov	[si+10h], ax
		push	[bp+arg_4]
		push	[bp+arg_2]
		call	sub_178F1
		mov	word ptr [si+12h], 0
		inc	word_22644
		jmp	short loc_16E23
; ---------------------------------------------------------------------------

loc_16E1A:
		inc	di
		add	si, 14h

loc_16E1E:
		cmp	di, 28h	; '('
		jl	short loc_16DD1

loc_16E23:
		pop	di
		pop	si
		pop	bp
		retn	6
sub_16D84	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16E29	proc far

var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	0Ah, 0
		push	si
		push	di
		push	5
		call	sub_157FA
		mov	[bp+var_6], ax

loc_16E37:
		push	5
		call	sub_157FA
		mov	[bp+var_A], ax
		cmp	ax, [bp+var_6]
		jz	short loc_16E37
		cmp	word ptr dword_2CEA0, 800h
		jge	short loc_16E53
		mov	[bp+var_4], 0
		jmp	short loc_16E67
; ---------------------------------------------------------------------------

loc_16E53:
		cmp	word ptr dword_2CEA0, 1000h
		jg	short loc_16E62
		mov	[bp+var_4], 1
		jmp	short loc_16E67
; ---------------------------------------------------------------------------

loc_16E62:
		mov	[bp+var_4], 2

loc_16E67:
		xor	di, di
		mov	si, 0AF20h
		mov	[bp+var_2], 0
		jmp	loc_16EF9
; ---------------------------------------------------------------------------

loc_16E74:
		cmp	byte ptr [si], 0
		jnz	short loc_16EF3
		mov	byte ptr [si], 1
		mov	byte ptr [si+0Fh], 0
		mov	ax, word ptr dword_2CEA0
		mov	[si+2],	ax
		mov	ax, word ptr dword_2CEA0+2
		mov	[si+4],	ax
		mov	bx, [bp+var_4]
		imul	bx, 14h
		mov	ax, di
		add	ax, ax
		add	bx, ax
		mov	ax, [bx+1C70h]
		mov	[si+0Ch], ax
		mov	bx, [bp+var_4]
		imul	bx, 14h
		mov	ax, di
		add	ax, ax
		add	bx, ax
		mov	ax, [bx+1C7Ah]
		mov	[si+0Ah], ax
		mov	word ptr [si+12h], 0
		cmp	[bp+var_6], di
		jz	short loc_16EC6
		push	1
		call	sub_157E4
		mov	[bp+var_8], ax
		jmp	short loc_16ECB
; ---------------------------------------------------------------------------

loc_16EC6:
		mov	[bp+var_8], 3

loc_16ECB:
		cmp	byte_25350, 1
		jnz	short loc_16ED7
		mov	[bp+var_8], 6

loc_16ED7:
		mov	al, byte ptr [bp+var_8]
		mov	[si+0Eh], al
		mov	bx, [bp+var_8]
		add	bx, bx
		mov	ax, [bx+1BEEh]
		mov	[si+10h], ax
		inc	di
		inc	word_22644
		cmp	di, 5
		jge	short loc_16F01

loc_16EF3:
		inc	[bp+var_2]
		add	si, 14h

loc_16EF9:
		cmp	[bp+var_2], 28h	; '('
		jl	loc_16E74

loc_16F01:
		pop	di
		pop	si
		leave
		retf
sub_16E29	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16F05	proc near
		push	bp
		mov	bp, sp
		mov	al, byte_226C4
		mov	ah, 0
		imul	ax, 64h
		add	ax, 64h	; 'd'
		cmp	ax, word_22648
		ja	short loc_16F52
		push	4
		call	sub_E720
		inc	byte_226C4
		cmp	byte_25350, 63h	; 'c'
		jnb	short loc_16F52
		inc	byte_25350
		cmp	byte_2C979, 14h
		jnb	short loc_16F3B
		mov	byte_2C979, 14h

loc_16F3B:
		call	sub_10407
		mov	byte_2CE87, 1
		mov	fp_2CE8A, offset sub_11DEA
		call	snd_se_play pascal, 7

loc_16F52:
		pop	bp
		retn
sub_16F05	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16F54	proc near

var_3		= byte ptr -3
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	4, 0
		push	si
		push	di
		mov	di, [bp+arg_0]
		mov	[bp+var_3], 0
		mov	al, [di+0Eh]
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 6
		ja	loc_17174
		add	bx, bx
		jmp	cs:off_171BA[bx]

loc_16F76:
		cmp	byte_2CEBE, 80h
		jnb	short loc_16FAA
		cmp	byte_2CEBE, 7Fh
		jnz	short loc_16F9B
		mov	byte_2CE87, 3
		mov	fp_2CE8A, offset sub_11DEA
		cmp	byte_2C979, 14h
		jnb	short loc_16F9B
		mov	byte_2C979, 14h

loc_16F9B:
		inc	byte_2CEBE
		call	sub_E4FC
		mov	si, 1
		jmp	loc_17174
; ---------------------------------------------------------------------------

loc_16FAA:
		inc	word_22642
		cmp	word_22642, 2Ah	; '*'
		jb	short loc_16FD1
		mov	word_22642, 2Ah	; '*'
		mov	[bp+var_3], 1
		cmp	byte_2264E, 0
		jnz	short loc_16FD1
		cmp	byte_2CEC3, 80h
		jnb	short loc_16FD1
		inc	byte_2CEC3

loc_16FD1:
		mov	bx, word_22642
		add	bx, bx
		mov	si, [bx+1BFCh]
		call	sub_1059D
		jmp	loc_17174
; ---------------------------------------------------------------------------

loc_16FE3:
		cmp	byte_2CEC3, 80h
		jnb	short loc_17003
		mov	al, byte_2CEC3
		mov	ah, 0
		imul	ax, 18h
		mov	dx, [di+4]
		sub	dx, ax
		add	dx, 0FC80h
		mov	[bp+var_2], dx
		mov	si, 1400h
		jmp	short loc_1700C
; ---------------------------------------------------------------------------

loc_17003:
		mov	[bp+var_2], 0
		mov	si, word_2C988

loc_1700C:
		cmp	[bp+var_2], 0
		jg	short loc_1704D
		inc	byte_225CC
		cmp	byte_2264E, 0
		jnz	short loc_17043
		mov	ax, [di+4]
		mov	bx, 400h
		cwd
		idiv	bx
		mov	dl, 6
		sub	dl, al
		add	dl, byte_2CEC3
		mov	byte_2CEC3, dl
		cmp	byte_2CEC3, 80h
		jbe	short loc_1703E
		mov	byte_2CEC3, 80h

loc_1703E:
		call	sub_1059D

loc_17043:
		inc	word_2264C
		mov	[bp+var_3], 1
		jmp	short loc_1705C
; ---------------------------------------------------------------------------

loc_1704D:
		mov	ax, [bp+var_2]
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	dx, 0AF0h
		sub	dx, ax
		mov	si, dx

loc_1705C:
		inc	byte_225CC
		inc	word_22648
		inc	word_2264A
		cmp	word_2CEC6, 3E7h
		jnb	short loc_17074
		inc	word_2CEC6

loc_17074:
		call	sub_16F05
		call	sub_10574
		jmp	loc_17174
; ---------------------------------------------------------------------------

loc_1707F:
		cmp	byte_2CEC3, 80h
		jb	short loc_1708F
		mov	si, 3200h
		mov	[bp+var_3], 1
		jmp	short loc_17097
; ---------------------------------------------------------------------------

loc_1708F:
		mov	si, 1
		mov	byte_2CEC3, 80h

loc_17097:
		call	sub_1059D
		mov	al, byte_225CC
		add	al, 2
		mov	byte_225CC, al
		cmp	byte_2264E, 0
		jz	loc_17174
		add	al, 2
		mov	byte_225CC, al
		jmp	loc_17174
; ---------------------------------------------------------------------------

loc_170B5:
		cmp	byte_2CEBE, 80h
		jnb	short loc_170F2
		mov	al, byte_2CEBE
		add	al, 0Ah
		mov	byte_2CEBE, al
		cmp	byte_2CEBE, 80h
		jb	short loc_170E7
		mov	byte_2CEBE, 80h
		mov	byte_2CE87, 3
		mov	fp_2CE8A, offset sub_11DEA
		cmp	byte_2C979, 14h
		jnb	short loc_170E7
		mov	byte_2C979, 14h

loc_170E7:
		call	sub_E4FC
		mov	si, 1
		jmp	loc_17174
; ---------------------------------------------------------------------------

loc_170F2:
		add	word_22642, 5
		mov	bx, word_22642
		add	bx, bx
		mov	si, [bx+1BFCh]
		cmp	word_22642, 2Ah	; '*'
		jbe	short loc_1710E
		mov	word_22642, 2Ah	; '*'

loc_1710E:
		cmp	word_22642, 2Ah	; '*'
		jnz	short loc_17174
		mov	si, 0A00h
		mov	[bp+var_3], 1
		jmp	short loc_17174
; ---------------------------------------------------------------------------

loc_1711E:
		inc	byte_25351
		mov	si, 64h	; 'd'
		call	sub_104BB
		jmp	short loc_17174
; ---------------------------------------------------------------------------

loc_1712C:
		push	3
		call	sub_E720
		inc	byte_25350
		call	sub_10407
		call	snd_se_play pascal, 7
		mov	byte_2CE87, 1
		mov	fp_2CE8A, offset sub_11DEA
		jmp	short loc_17171
; ---------------------------------------------------------------------------

loc_17150:
		cmp	byte_2C979, 14h
		jnb	short loc_1715C
		mov	byte_2C979, 14h

loc_1715C:
		mov	byte_2CE87, 3
		mov	fp_2CE8A, offset sub_11DEA
		mov	byte_2CEBE, 80h
		call	sub_E4FC

loc_17171:
		mov	si, 64h	; 'd'

loc_17174:
		movzx	eax, si
		add	dword_2CE1A, eax
		cmp	[bp+var_3], 0
		jnz	short loc_1718F
		push	word ptr [di+2]
		push	word ptr [di+4]
		push	si
		call	sub_15888
		jmp	short loc_17199
; ---------------------------------------------------------------------------

loc_1718F:
		push	word ptr [di+2]
		push	word ptr [di+4]
		push	si
		call	sub_1586E

loc_17199:
		cmp	byte_225CC, 20h	; ' '
		jb	short loc_171AF
		mov	al, byte_225CC
		add	al, 0E0h
		mov	byte_225CC, al
		push	1
		call	sub_E720

loc_171AF:
		inc	word_22646
		pop	di
		pop	si
		leave
		retn	2
sub_16F54	endp

; ---------------------------------------------------------------------------
		db 0
off_171BA	dw offset loc_16F76
		dw offset loc_16FE3
		dw offset loc_1707F
		dw offset loc_170B5
		dw offset loc_1711E
		dw offset loc_1712C
		dw offset loc_17150

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_171C8	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		mov	al, [si+0Eh]
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_171E5
		cmp	ax, 4
		jz	short loc_171F9
		cmp	ax, 5
		jz	short loc_171FD
		jmp	short loc_17204
; ---------------------------------------------------------------------------

loc_171E5:
		cmp	byte_2CEC3, 1
		jbe	short loc_17204
		cmp	byte_2CEC3, 80h
		jnb	short loc_17204
		dec	byte_2CEC3
		jmp	short loc_17204
; ---------------------------------------------------------------------------

loc_171F9:
		push	2
		jmp	short loc_171FF
; ---------------------------------------------------------------------------

loc_171FD:
		push	4

loc_171FF:
		call	sub_E73A

loc_17204:
		call	sub_1059D
		pop	si
		pop	bp
		retn	2
sub_171C8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1720E	proc far

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		mov	si, 0AF20h
		xor	di, di
		jmp	loc_172EC
; ---------------------------------------------------------------------------

loc_1721C:
		cmp	byte ptr [si], 0
		jz	loc_172E8
		cmp	byte ptr [si], 2
		jnz	short loc_1722E
		mov	byte ptr [si], 0
		jmp	loc_172E8
; ---------------------------------------------------------------------------

loc_1722E:
		cmp	byte_2264E, 0
		jz	short loc_17264
		mov	byte_21762, 1
		mov	word ptr [si+12h], 1
		mov	ax, word ptr dword_2CEA0+2
		sub	ax, [si+4]
		push	ax
		mov	ax, word ptr dword_2CEA0
		sub	ax, [si+2]
		push	ax
		call	iatan2
		mov	[bp+var_1], al
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [bp+var_1]
		push	0A0h
		call	sub_158E2
		jmp	short loc_17279
; ---------------------------------------------------------------------------

loc_17264:
		cmp	word ptr [si+12h], 0
		jz	short loc_17279
		mov	word ptr [si+0Ah], 0
		mov	word ptr [si+0Ch], 0
		mov	word ptr [si+12h], 0

loc_17279:
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		cmp	ax, 0FF80h
		jle	short loc_17290
		cmp	ax, 1880h
		jge	short loc_17290
		cmp	dx, 1780h
		jl	short loc_17299

loc_17290:
		mov	byte ptr [si], 2
		push	si
		call	sub_171C8
		jmp	short loc_172E8
; ---------------------------------------------------------------------------

loc_17299:
		cmp	dx, 0FF80h
		jge	short loc_172A3
		mov	word ptr [si+4], 0FF80h

loc_172A3:
		cmp	word ptr [si+0Ch], 0
		jl	short loc_172AE
		mov	word ptr [si+0Ah], 0

loc_172AE:
		cmp	byte_2CEC2, 0
		jnz	short loc_172E5
		mov	bx, word ptr dword_2CEA0
		add	bx, 180h
		sub	bx, ax
		cmp	bx, 300h
		ja	short loc_172E5
		mov	bx, word ptr dword_2CEA0+2
		add	bx, 180h
		sub	bx, dx
		cmp	bx, 260h
		ja	short loc_172E5
		push	si
		call	sub_16F54
		call	snd_se_play pascal, 11
		mov	byte ptr [si], 2
		jmp	short loc_172E8
; ---------------------------------------------------------------------------

loc_172E5:
		inc	word ptr [si+0Ch]

loc_172E8:
		inc	di
		add	si, 14h

loc_172EC:
		cmp	di, 28h	; '('
		jl	loc_1721C
		call	sub_17939
		mov	byte_21762, 0
		pop	di
		pop	si
		leave
		retf
sub_1720E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_172FF	proc far
		push	bp
		mov	bp, sp
		mov	fp_2C98E, offset nullsub_2
		mov	fp_2C994, offset nullsub_2
		setfarfp	farfp_2C990, nullsub_1
		mov	word_2632E, 0
		pop	bp
		retf
sub_172FF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17322	proc far
		push	bp
		mov	bp, sp
		mov	ax, word_2632C
		cmp	ax, word_25FE0
		jnz	short loc_17352
		mov	fp_2C98E, offset sub_D032
		mov	ax, fp_2C99A
		mov	fp_2C994, ax
		mov	eax, farfp_2C996
		mov	farfp_2C990, eax
		mov	byte_26331, 0
		mov	word_26332, 0
		mov	byte_2C98C, 1

loc_17352:
		pop	bp
		retf
sub_17322	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17354	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	di, [bp+arg_2]
		or	di, di
		jg	short loc_17364
		xor	si, si
		jmp	short loc_17389
; ---------------------------------------------------------------------------

loc_17364:
		cmp	di, [bp+arg_0]
		jl	short loc_1736E
		mov	si, 80h
		jmp	short loc_17389
; ---------------------------------------------------------------------------

loc_1736E:
		movsx	eax, di
		shl	eax, 7
		movsx	ebx, [bp+arg_0]
		cdq
		idiv	ebx
		mov	si, ax
		cmp	si, 80h
		jge	short loc_17389
		inc	si

loc_17389:
		cmp	word_2268C, si
		jge	short loc_17393
		inc	word_2268C

loc_17393:
		cmp	word_2268C, si
		jle	short loc_1739D
		mov	word_2268C, si

loc_1739D:
		push	word_2268C
		call	sub_1065B
		pop	di
		pop	si
		pop	bp
		retn	4
sub_17354	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_173AC	proc near

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	4, 0
		push	si
		push	di
		mov	ax, [bp+arg_0]
		imul	ax, 500h
		movzx	eax, ax
		add	dword_2CE1A, eax
		mov	byte_21762, 0
		mov	ax, word ptr dword_26320
		add	ax, 0FC00h
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_26320+2
		add	ax, 0FC00h
		mov	[bp+var_4], ax
		xor	di, di
		jmp	short loc_1740B
; ---------------------------------------------------------------------------

loc_173DD:
		push	800h
		call	sub_157FA
		add	ax, [bp+var_2]
		mov	si, ax
		or	si, si
		jge	short loc_173F0
		xor	si, si
		jmp	short loc_173F9
; ---------------------------------------------------------------------------

loc_173F0:
		cmp	si, 1800h
		jle	short loc_173F9
		mov	si, 1800h

loc_173F9:
		push	si
		push	800h
		call	sub_157FA
		add	ax, [bp+var_4]
		push	ax
		push	500h
		call	sub_1586E
		inc	di

loc_1740B:
		cmp	di, [bp+arg_0]
		jb	short loc_173DD
		pop	di
		pop	si
		leave
		retn	2
sub_173AC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17416	proc near

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	4, 0
		push	si
		push	di
		movzx	eax, [bp+arg_0]
		imul	eax, 3E8h
		add	dword_2CE1A, eax
		mov	byte_21762, 0
		mov	ax, word_26335+1
		add	ax, 0FC00h
		mov	[bp+var_2], ax
		mov	ax, word_26338
		add	ax, 0FC00h
		mov	[bp+var_4], ax
		xor	di, di
		jmp	short loc_17476
; ---------------------------------------------------------------------------

loc_17448:
		push	800h
		call	sub_157FA
		add	ax, [bp+var_2]
		mov	si, ax
		or	si, si
		jge	short loc_1745B
		xor	si, si
		jmp	short loc_17464
; ---------------------------------------------------------------------------

loc_1745B:
		cmp	si, 1800h
		jle	short loc_17464
		mov	si, 1800h

loc_17464:
		push	si
		push	800h
		call	sub_157FA
		add	ax, [bp+var_4]
		push	ax
		push	3E8h
		call	sub_1586E
		inc	di

loc_17476:
		cmp	di, [bp+arg_0]
		jb	short loc_17448
		mov	byte_229BA, 0
		pop	di
		pop	si
		leave
		retn	2
sub_17416	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17486	proc near
		push	bp
		mov	bp, sp
		cmp	byte_26331, 0FEh
		jnz	short loc_174C1
		cmp	word_26332, 1
		jnz	short loc_174A2
		mov	word_2CE06, 0Ah
		mov	byte_2C98C, 0

loc_174A2:
		mov	ax, word_26332
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_174C5
		inc	byte_26330
		cmp	byte_26330, 0Ch
		jb	short loc_174C5
		mov	byte_26331, 0FFh
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_174C1:
		call	sub_172FF

loc_174C5:
		pop	bp
		retn
sub_17486	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_174C7	proc near

var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	al, byte ptr word_26314
		call	sub_15A42
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	si, 5628h
		xor	di, di
		jmp	short loc_1753F
; ---------------------------------------------------------------------------

loc_174E1:
		cmp	byte ptr [si], 0
		jnz	short loc_1753B
		mov	byte ptr [si], 1
		mov	word ptr [si+6], 100h
		mov	word ptr [si+8], 100h
		mov	word ptr [si+0Eh], 0
		mov	ax, word_26318
		mov	[si+10h], ax
		mov	al, byte_26309
		mov	[si+1],	al
		mov	ax, [bp+var_2]
		mov	[si+0Ch], ax
		mov	byte ptr [si+14h], 6
		mov	byte ptr [si+0Bh], 6
		mov	al, byte_26312
		mov	[si+0Ah], al
		lea	ax, [si+2]
		push	ax
		push	word ptr dword_2630A
		push	word ptr dword_2630A+2
		push	80h
		mov	al, byte_26312
		mov	ah, 0
		push	ax
		call	sub_14E6C
		call	snd_se_play pascal, 5
		jmp	short loc_17544
; ---------------------------------------------------------------------------

loc_1753B:
		inc	di
		add	si, 18h

loc_1753F:
		cmp	di, 20h	; ' '
		jl	short loc_174E1

loc_17544:
		pop	di
		pop	si
		leave
		retn
sub_174C7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17548	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	ax, [bp+arg_0]
		imul	ax, 18h
		add	ax, 5628h
		mov	si, ax
		cmp	byte ptr [si], 0
		jnz	short loc_1759F
		mov	byte ptr [si], 2
		mov	eax, dword_2630A
		mov	[si+2],	eax
		mov	word ptr [si+6], 100h
		mov	word ptr [si+8], 2260h
		mov	word ptr [si+0Eh], 0
		mov	ax, word_26318
		mov	[si+10h], ax
		mov	ax, word_2631A
		mov	[si+12h], ax
		mov	al, byte_26309
		mov	[si+1],	al
		mov	al, byte_26313
		mov	[si+14h], al
		mov	byte ptr [si+0Bh], 1
		mov	al, byte_26312
		mov	[si+0Ah], al
		call	snd_se_play pascal, 5

loc_1759F:
		pop	si
		pop	bp
		retn	2
sub_17548	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_175A4	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	ax, [bp+arg_0]
		imul	ax, 18h
		add	ax, 5628h
		mov	si, ax
		cmp	byte ptr [si], 0
		jnz	short loc_175F9
		mov	byte ptr [si], 2
		mov	eax, dword_2630A
		mov	[si+2],	eax
		mov	word ptr [si+6], 100h
		mov	word ptr [si+8], 2260h
		mov	word ptr [si+0Eh], 0
		mov	word ptr [si+10h], 0FFFFh
		mov	word ptr [si+12h], 0FFFFh
		mov	al, byte_26309
		mov	[si+1],	al
		mov	byte ptr [si+0Bh], 1
		mov	al, byte_26313
		mov	[si+14h], al
		mov	al, byte_26312
		mov	[si+0Ah], al
		call	snd_se_play pascal, 5

loc_175F9:
		pop	si
		pop	bp
		retn	2
sub_175A4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_175FE	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		mov	bx, si
		imul	bx, 18h
		cmp	byte ptr [bx+5628h], 2
		jnz	short loc_17622
		mov	bx, si
		imul	bx, 18h
		mov	byte ptr [bx+5628h], 3
		call	snd_se_play pascal, 6

loc_17622:
		pop	si
		pop	bp
		retn	2
sub_175FE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17627	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		mov	ax, [bp+arg_0]
		mov	bx, ax
		imul	bx, 18h
		cmp	byte ptr [bx+5628h], 4
		jnz	short loc_17647
		mov	bx, ax
		imul	bx, 18h
		mov	byte ptr [bx+5628h], 5
		pop	bp
		retn	2
; ---------------------------------------------------------------------------

loc_17647:
		mov	bx, ax
		imul	bx, 18h
		cmp	byte ptr [bx+5628h], 1
		jnz	short loc_17661
		mov	bx, ax
		imul	bx, 18h
		mov	byte ptr [bx+5628h], 7
		pop	bp
		retn	2
; ---------------------------------------------------------------------------

loc_17661:
		mov	bx, ax
		imul	bx, 18h
		cmp	byte ptr [bx+5628h], 5
		jz	short loc_17683
		mov	bx, ax
		imul	bx, 18h
		cmp	byte ptr [bx+5628h], 7
		jz	short loc_17683
		mov	bx, ax
		imul	bx, 18h
		mov	byte ptr [bx+5628h], 0

loc_17683:
		pop	bp
		retn	2
sub_17627	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17687	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		mov	si, 0B2AAh
		mov	[bp+var_4], 0BFC2h
		mov	[bp+var_2], 1
		jmp	short loc_1771A
; ---------------------------------------------------------------------------

loc_1769E:
		cmp	byte ptr [si], 0
		jnz	short loc_17710
		mov	bx, [bp+var_4]
		cmp	byte ptr [bx], 0
		jnz	short loc_17710
		mov	bx, [bp+var_4]
		mov	byte ptr [bx], 1
		mov	al, byte ptr word_2BC71
		mov	[si+1],	al
		mov	al, byte_2BC88
		mov	[si+18h], al
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+1]
		mov	al, [si+18h]
		mov	ah, 0
		push	ax
		call	sub_158E2
		mov	bx, [bp+var_4]
		mov	al, byte ptr word_2BC82
		mov	[bx+1],	al
		push	0
		push	word ptr [si+1]
		call	sub_159E6
		mov	ah, 0
		mov	[si+12h], ax
		mov	eax, dword ptr word_2BC71+1
		mov	[si+2],	eax
		xor	di, di
		jmp	short loc_17709
; ---------------------------------------------------------------------------

loc_176EF:
		mov	bx, di
		shl	bx, 2
		add	bx, [bp+var_4]
		mov	eax, dword ptr word_2BC71+1
		mov	[bx+2],	eax
		mov	al, [si+12h]
		mov	bx, [bp+var_4]
		mov	[bx+di+42h], al
		inc	di

loc_17709:
		cmp	di, 10h
		jl	short loc_176EF
		jmp	short loc_17722
; ---------------------------------------------------------------------------

loc_17710:
		inc	[bp+var_2]
		add	si, 1Ah
		add	[bp+var_4], 52h	; 'R'

loc_1771A:
		cmp	[bp+var_2], 8
		jl	loc_1769E

loc_17722:
		pop	di
		pop	si
		leave
		retn
sub_17687	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17726	proc near

var_6		= byte ptr -6
var_5		= byte ptr -5
var_4		= word ptr -4
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		mov	si, 0B2AAh
		mov	di, 0BFC2h
		mov	[bp+var_2], 1
		jmp	loc_178CB
; ---------------------------------------------------------------------------

loc_1773C:
		cmp	byte ptr [di], 0
		jz	loc_178C2
		inc	word ptr [si+0Eh]
		mov	[bp+var_4], 0Fh
		jmp	short loc_1779C
; ---------------------------------------------------------------------------

loc_1774D:
		mov	bx, [bp+var_4]
		shl	bx, 2
		mov	eax, [bx+di-2]
		mov	bx, [bp+var_4]
		shl	bx, 2
		mov	[bx+di+2], eax
		mov	bx, [bp+var_4]
		shl	bx, 2
		mov	ax, [bx+di+2]
		sub	ax, word ptr dword_2CEA0
		add	ax, 60h
		cmp	ax, 0C0h
		ja	short loc_17790
		mov	bx, [bp+var_4]
		shl	bx, 2
		mov	ax, [bx+di+4]
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 60h
		cmp	ax, 0C0h
		ja	short loc_17790
		mov	byte_2CEC1, 1

loc_17790:
		mov	bx, [bp+var_4]
		mov	al, [bx+di+41h]
		mov	[bx+di+42h], al
		dec	[bp+var_4]

loc_1779C:
		cmp	[bp+var_4], 0
		jg	short loc_1774D
		mov	eax, [si+2]
		mov	[di+2],	eax
		mov	al, [si+12h]
		mov	[di+42h], al
		cmp	word ptr [di+3Eh], 0FF00h
		jle	short loc_177CC
		cmp	word ptr [di+3Eh], 1900h
		jge	short loc_177CC
		cmp	word ptr [di+40h], 0FF00h
		jle	short loc_177CC
		cmp	word ptr [di+40h], 1800h
		jl	short loc_177D5

loc_177CC:
		mov	byte ptr [di], 0
		mov	byte ptr [si], 0
		jmp	loc_178C2
; ---------------------------------------------------------------------------

loc_177D5:
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		add	ax, 80h
		cmp	ax, 100h
		ja	short loc_177FB
		add	dx, 80h
		cmp	dx, 100h
		ja	short loc_177FB
		mov	byte_2CEC1, 1

loc_177FB:
		cmp	byte ptr [di], 1
		jnz	short loc_17811
		dec	byte ptr [si+18h]
		cmp	byte ptr [si+18h], 4
		ja	short loc_1780B
		inc	byte ptr [di]

loc_1780B:
		mov	[bp+var_6], 10h
		jmp	short loc_17825
; ---------------------------------------------------------------------------

loc_17811:
		mov	al, [si+18h]
		add	al, byte_25FE2
		inc	al
		mov	[si+18h], al
		mov	al, [si+18h]
		add	al, 20h	; ' '
		mov	[bp+var_6], al

loc_17825:
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	0
		call	sub_15A24
		mov	dl, [si+1]
		sub	dl, al
		mov	[bp+var_5], dl
		cmp	[bp+var_5], 80h
		jb	short loc_1786E
		cmp	[bp+var_5], 0FEh
		jnb	short loc_17874
		mov	al, [bp+var_5]
		mov	ah, 0
		push	ax
		mov	ax, 100h
		pop	dx
		sub	ax, dx
		mov	dl, [bp+var_6]
		mov	dh, 0
		push	dx
		cwd
		pop	bx
		idiv	bx
		mov	[bp+var_5], al
		cmp	al, [bp+var_6]
		jnb	short loc_17866
		mov	[bp+var_5], 1

loc_17866:
		mov	al, [bp+var_5]
		add	[si+1],	al
		jmp	short loc_178A5
; ---------------------------------------------------------------------------

loc_1786E:
		cmp	[bp+var_5], 2
		ja	short loc_17884

loc_17874:
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	0
		call	sub_15A24
		mov	[si+1],	al
		jmp	short loc_178A5
; ---------------------------------------------------------------------------

loc_17884:
		mov	al, [bp+var_5]
		mov	ah, 0
		mov	dl, [bp+var_6]
		mov	dh, 0
		push	dx
		cwd
		pop	bx
		idiv	bx
		mov	[bp+var_5], al
		cmp	al, [bp+var_6]
		jnb	short loc_1789F
		mov	[bp+var_5], 1

loc_1789F:
		mov	al, [bp+var_5]
		sub	[si+1],	al

loc_178A5:
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+1]
		mov	al, [si+18h]
		mov	ah, 0
		push	ax
		call	sub_158E2
		push	0
		push	word ptr [si+1]
		call	sub_159E6
		mov	ah, 0
		mov	[si+12h], ax

loc_178C2:
		inc	[bp+var_2]
		add	si, 1Ah
		add	di, 52h	; 'R'

loc_178CB:
		cmp	[bp+var_2], 8
		jl	loc_1773C
		pop	di
		pop	si
		leave
		retn
sub_17726	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_178D7	proc near
		push	bp
		mov	bp, sp
		push	di
		mov	cx, 28h	; '('
		mov	ax, ds
		mov	es, ax
		assume es:dseg
		xor	ax, ax
		mov	di, 0C252h
		rep stosw
		mov	byte_2CC8C, 0
		pop	di
		pop	bp
		retn
sub_178D7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_178F1	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	al, byte_2CC8C
		mov	ah, 0
		imul	ax, 0Ah
		add	ax, 0C252h
		mov	si, ax
		inc	byte_2CC8C
		cmp	byte_2CC8C, 8
		jb	short loc_17912
		mov	byte_2CC8C, 0

loc_17912:
		cmp	byte ptr [si], 0
		jnz	short loc_17934
		mov	byte ptr [si], 1
		mov	ax, [bp+arg_2]
		mov	[si+2],	ax
		mov	ax, [bp+arg_0]
		mov	[si+4],	ax
		mov	word ptr [si+6], 20h ; ' '
		mov	byte ptr [si+1], 10h
		mov	word ptr [si+8], 20h ; ' '

loc_17934:
		pop	si
		pop	bp
		retn	4
sub_178F1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17939	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	si, 0C252h
		xor	dx, dx
		jmp	short loc_1796B
; ---------------------------------------------------------------------------

loc_17944:
		cmp	byte ptr [si], 0
		jz	short loc_17967
		cmp	byte ptr [si], 2
		jnz	short loc_17953
		mov	byte ptr [si], 0
		jmp	short loc_17967
; ---------------------------------------------------------------------------

loc_17953:
		mov	ax, [si+6]
		mov	[si+8],	ax
		add	word ptr [si+6], 20h ; ' '
		cmp	word ptr [si+6], 200h
		jl	short loc_17967
		mov	byte ptr [si], 2

loc_17967:
		inc	dx
		add	si, 0Ah

loc_1796B:
		cmp	dx, 8
		jl	short loc_17944
		pop	si
		pop	bp
		retn
sub_17939	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17973	proc near

var_1		= byte ptr -1
arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		mov	si, [bp+arg_0]
		cmp	word ptr [si+18h], 34h ; '4'
		jl	short loc_179BC
		cmp	word ptr [si+18h], 44h ; 'D'
		jge	short loc_1798F
		mov	[bp+var_1], 34h	; '4'
		jmp	short loc_179AB
; ---------------------------------------------------------------------------

loc_1798F:
		cmp	word ptr [si+18h], 54h ; 'T'
		jge	short loc_1799B
		mov	[bp+var_1], 44h	; 'D'
		jmp	short loc_179AB
; ---------------------------------------------------------------------------

loc_1799B:
		cmp	word ptr [si+18h], 74h ; 't'
		jge	short loc_179A7
		mov	[bp+var_1], 54h	; 'T'
		jmp	short loc_179AB
; ---------------------------------------------------------------------------

loc_179A7:
		mov	[bp+var_1], 74h	; 't'

loc_179AB:
		mov	al, [bp+var_1]
		mov	ah, 0
		push	ax
		push	word ptr [si+11h]
		call	sub_159E6
		mov	ah, 0
		mov	[si+18h], ax

loc_179BC:
		pop	si
		leave
		retn	2
sub_17973	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_179C1	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		inc	byte ptr [si+16h]
		mov	al, 80h
		sub	al, [si+11h]
		mov	[si+11h], al
		mov	al, [si+16h]
		cmp	al, byte_2C976
		jb	short loc_179E0
		mov	byte ptr [si+13h], 2

loc_179E0:
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_158E2
		push	si
		call	sub_17973
		pop	si
		pop	bp
		retn	2
sub_179C1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_179F9	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		inc	byte ptr [si+16h]
		mov	al, [si+11h]
		neg	al
		mov	[si+11h], al
		mov	al, [si+16h]
		cmp	al, byte_2C976
		jb	short loc_17A18
		mov	byte ptr [si+13h], 2

loc_17A18:
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_158E2
		push	si
		call	sub_17973
		pop	si
		pop	bp
		retn	2
sub_179F9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17A31	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		mov	al, [si+14h]
		mov	ah, 0
		dec	ax
		mov	bx, ax
		cmp	bx, 9
		ja	loc_17BEB
		add	bx, bx
		jmp	cs:off_17BF0[bx]

loc_17A4E:
		cmp	byte ptr [si+10h], 0
		jz	short loc_17A56
		jmp	short loc_17A8D
; ---------------------------------------------------------------------------

loc_17A56:
		inc	byte ptr [si+16h]
		mov	ax, word ptr dword_2CEA0+2
		sub	ax, [si+4]
		push	ax
		mov	ax, word ptr dword_2CEA0
		sub	ax, [si+2]
		push	ax
		call	iatan2
		mov	[si+11h], al
		push	si
		call	sub_17973
		mov	al, [si+15h]
		mov	[si+10h], al
		mov	al, [si+16h]
		cmp	al, byte_2C976
		jb	loc_17B32
		jmp	loc_17B2E
; ---------------------------------------------------------------------------

loc_17A87:
		cmp	byte ptr [si+10h], 0
		jz	short loc_17AA3

loc_17A8D:
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_158E2
		dec	byte ptr [si+10h]
		jmp	loc_17BEB
; ---------------------------------------------------------------------------

loc_17AA3:
		inc	byte ptr [si+16h]
		mov	al, [si+17h]
		add	[si+11h], al
		push	si
		call	sub_17973
		mov	al, [si+15h]
		mov	[si+10h], al
		mov	al, [si+16h]
		cmp	al, byte_2C976
		jb	short loc_17B32
		jmp	short loc_17B2E
; ---------------------------------------------------------------------------

loc_17AC1:
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_158E2
		mov	al, byte_2C976
		add	[si+10h], al
		jmp	loc_17BEB
; ---------------------------------------------------------------------------

loc_17ADA:
		cmp	byte ptr [si+10h], 0
		jz	short loc_17B22
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_158E2
		cmp	byte ptr [si+10h], 1
		jbe	short loc_17B00
		mov	al, [si+10h]
		add	al, 0FEh
		mov	[si+10h], al
		jmp	short loc_17B04
; ---------------------------------------------------------------------------

loc_17B00:
		mov	byte ptr [si+10h], 0

loc_17B04:
		cmp	byte ptr [si+10h], 20h ; ' '
		jnb	loc_17BEB
		mov	al, [si+17h]
		sub	al, [si+11h]
		cbw
		mov	bx, 4
		cwd
		idiv	bx
		add	al, [si+11h]
		mov	[si+11h], al
		jmp	loc_17BEB
; ---------------------------------------------------------------------------

loc_17B22:
		mov	al, [si+17h]
		mov	[si+11h], al
		mov	al, [si+15h]
		mov	[si+10h], al

loc_17B2E:
		mov	byte ptr [si+13h], 2

loc_17B32:
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_158E2
		jmp	loc_17BEB
; ---------------------------------------------------------------------------

loc_17B45:
		cmp	word ptr [si+2], 0
		jle	short loc_17B54
		cmp	word ptr [si+2], 1800h
		jl	loc_17BEB

loc_17B54:
		push	si
		call	sub_179C1
		jmp	loc_17BEB
; ---------------------------------------------------------------------------

loc_17B5B:
		cmp	word ptr [si+4], 0
		jle	short loc_17BA3
		cmp	word ptr [si+4], 1700h
		jl	loc_17BEB
		jmp	short loc_17BA3
; ---------------------------------------------------------------------------

loc_17B6C:
		cmp	word ptr [si+2], 0
		jle	short loc_17B79
		cmp	word ptr [si+2], 1800h
		jl	short loc_17B7D

loc_17B79:
		push	si
		call	sub_179C1

loc_17B7D:
		cmp	word ptr [si+4], 0
		jle	short loc_17BA3
		cmp	word ptr [si+4], 1700h
		jl	short loc_17BEB
		jmp	short loc_17BA3
; ---------------------------------------------------------------------------

loc_17B8C:
		cmp	word ptr [si+2], 0
		jle	short loc_17B99
		cmp	word ptr [si+2], 1800h
		jl	short loc_17B9D

loc_17B99:
		push	si
		call	sub_179C1

loc_17B9D:
		cmp	word ptr [si+4], 0
		jg	short loc_17BEB

loc_17BA3:
		push	si
		call	sub_179F9
		jmp	short loc_17BEB
; ---------------------------------------------------------------------------

loc_17BA9:
		cmp	byte_25FE2, 0
		jz	short loc_17BEB
		mov	al, byte_2C976
		mov	ah, 0
		add	[si+0Ch], ax
		jmp	short loc_17BEB
; ---------------------------------------------------------------------------

loc_17BBA:
		mov	al, [si+10h]
		mov	ah, 0
		add	[si+1Eh], ax
		push	48FEh
		push	word ptr [si+1Ah]
		push	word ptr [si+1Ch]
		push	word ptr [si+1Eh]
		mov	al, [si+11h]
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	ax, word ptr dword_252DE
		sub	ax, [si+2]
		mov	[si+0Ah], ax
		mov	ax, word ptr dword_252DE+2
		sub	ax, [si+4]
		mov	[si+0Ch], ax

loc_17BEB:
		pop	si
		pop	bp
		retn	2
sub_17A31	endp

; ---------------------------------------------------------------------------
off_17BF0	dw offset loc_17A4E
		dw offset loc_17A87
		dw offset loc_17AC1
		dw offset loc_17ADA
		dw offset loc_17B45
		dw offset loc_17B5B
		dw offset loc_17B6C
		dw offset loc_17B8C
		dw offset loc_17BA9
		dw offset loc_17BBA

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17C04	proc far

var_9		= byte ptr -9
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 0Ah
		push	si
		push	di
		mov	[bp+var_2], 0
		mov	word_2CDF8, 0
		mov	word_2C97E, 0
		mov	si, 8FA6h
		cmp	byte_2C978, 0
		jnz	loc_17EC3
		xor	di, di
		jmp	loc_17E78
; ---------------------------------------------------------------------------

loc_17C2E:
		cmp	byte ptr [si], 0
		jz	loc_17E74
		cmp	byte ptr [si], 2
		jnz	short loc_17C40
		mov	byte ptr [si], 0
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17C40:
		inc	[bp+var_2]
		cmp	byte_2C979, 0
		jz	short loc_17CA3
		cmp	byte ptr [si+13h], 4
		jnb	short loc_17C7B
		mov	byte ptr [si+13h], 4
		cmp	di, 0DCh
		jge	short loc_17C5F
		mov	ax, 0A0h
		jmp	short loc_17C62
; ---------------------------------------------------------------------------

loc_17C5F:
		mov	ax, 9Ch

loc_17C62:
		mov	[si+18h], ax
		cmp	byte ptr [si+1], 0
		jz	short loc_17C73
		add	dword_2CE1A, 64h ; 'd'
		jmp	short loc_17CA3
; ---------------------------------------------------------------------------

loc_17C73:
		add	dword_2CE1A, 0Ah
		jmp	short loc_17CA3
; ---------------------------------------------------------------------------

loc_17C7B:
		inc	byte ptr [si+13h]
		cmp	byte ptr [si+13h], 14h
		jb	short loc_17C91
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		mov	byte ptr [si], 2
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17C91:
		mov	al, [si+13h]
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_17CA3
		inc	word ptr [si+18h]

loc_17CA3:
		inc	byte ptr [si+1]
		cmp	byte ptr [si+12h], 2
		jb	loc_17D56
		cmp	byte ptr [si+12h], 2
		jnz	short loc_17CBB
		mov	byte ptr [si+12h], 0
		jmp	loc_17D56
; ---------------------------------------------------------------------------

loc_17CBB:
		cmp	byte ptr [si+12h], 3
		jnz	short loc_17CE1
		mov	eax, [si+2]
		mov	[si+6],	eax
		mov	ax, [si+0Ah]
		shl	ax, 3
		sub	[si+2],	ax
		mov	ax, [si+0Ch]
		shl	ax, 3
		sub	[si+4],	ax
		mov	byte ptr [si+12h], 4
		jmp	short loc_17D0D
; ---------------------------------------------------------------------------

loc_17CE1:
		cmp	byte ptr [si+12h], 4
		jnz	short loc_17CF0
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		jmp	short loc_17D0D
; ---------------------------------------------------------------------------

loc_17CF0:
		mov	eax, [si+2]
		mov	[si+6],	eax
		mov	ax, [si+0Ah]
		mov	bx, 3
		cwd
		idiv	bx
		add	[si+2],	ax
		mov	ax, [si+0Ch]
		cwd
		idiv	bx
		add	[si+4],	ax

loc_17D0D:
		inc	byte ptr [si+12h]
		cmp	byte ptr [si+12h], 14h
		jb	short loc_17D3D
		cmp	word ptr [si+4], 0FF80h
		jl	short loc_17D30
		cmp	word ptr [si+4], 1780h
		jge	short loc_17D30
		cmp	word ptr [si+2], 0FF80h
		jl	short loc_17D30
		cmp	word ptr [si+2], 1880h
		jl	short loc_17D36

loc_17D30:
		mov	byte ptr [si], 2
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17D36:
		mov	byte ptr [si+12h], 2
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17D3D:
		cmp	di, 0DCh
		jl	loc_17E74
		mov	bx, word_2CDF8
		add	bx, bx
		mov	[bx-3D50h], si
		inc	word_2CDF8
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17D56:
		cmp	byte ptr [si+13h], 1
		jnz	short loc_17D62
		push	si
		call	sub_17A31
		jmp	short loc_17DA3
; ---------------------------------------------------------------------------

loc_17D62:
		cmp	byte ptr [si+13h], 0
		jnz	short loc_17DA3
		dec	byte ptr [si+16h]
		mov	al, [si+16h]
		mov	ah, 0
		mov	dl, [si+17h]
		mov	dh, 0
		imul	dx
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		add	al, [si+15h]
		mov	[si+10h], al
		cmp	byte ptr [si+16h], 0
		jnz	short loc_17D93
		mov	al, [si+15h]
		mov	[si+10h], al
		mov	byte ptr [si+13h], 2

loc_17D93:
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_158E2

loc_17DA3:
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		cmp	ax, 0FF80h
		jle	short loc_17DBF
		cmp	ax, 1880h
		jge	short loc_17DBF
		cmp	dx, 0FF80h
		jle	short loc_17DBF
		cmp	dx, 1780h
		jl	short loc_17DC5

loc_17DBF:
		mov	byte ptr [si], 2
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17DC5:
		cmp	byte_2C979, 0
		jnz	loc_17E74
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		cmp	byte_2CEBC, 0
		jnz	short loc_17E41
		cmp	byte ptr [si+12h], 0
		jz	short loc_17DFE
		add	ax, 40h
		cmp	ax, 80h
		ja	short loc_17E41
		add	dx, 40h
		cmp	dx, 80h
		ja	short loc_17E41
		mov	byte ptr [si], 2
		mov	byte_2CEC1, 1
		jmp	short loc_17E74
; ---------------------------------------------------------------------------

loc_17DFE:
		add	ax, 100h
		cmp	ax, 240h
		ja	short loc_17E41
		add	dx, 160h
		cmp	dx, 2C0h
		ja	short loc_17E41
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	200002h
		nopcall	sub_1591A
		mov	byte ptr [si+12h], 1
		cmp	word_2C97A, 3E7h
		jnb	short loc_17E41
		inc	word_2C97A
		call	sub_1060E
		movzx	eax, word_2C97C
		add	dword_2CE1A, eax

loc_17E41:
		cmp	di, 0DCh
		jl	short loc_17E74
		mov	ax, [si+2]
		sar	ax, 4
		add	ax, 1Ch
		mov	bx, word_2C97E
		shl	bx, 2
		mov	[bx-703Ah], ax
		mov	ax, [si+4]
		add	ax, 0C0h
		push	ax
		call	sub_15288
		mov	bx, word_2C97E
		shl	bx, 2
		mov	[bx-7038h], ax
		inc	word_2C97E

loc_17E74:
		inc	di
		sub	si, 20h	; ' '

loc_17E78:
		cmp	di, 190h
		jl	loc_17C2E
		cmp	byte_25FF2, 0
		jnz	loc_17FB7
		mov	byte_25FF8, 0
		mov	di, 2Ah	; '*'
		mov	al, byte_25FEB
		mov	ah, 0
		shl	ax, 3
		add	di, ax
		cmp	[bp+var_2], di
		jl	short loc_17EAB
		cmp	byte_25FE2, 0
		jnz	loc_17FB7
		jmp	short loc_17EB5
; ---------------------------------------------------------------------------

loc_17EAB:
		lea	ax, [di+20h]
		cmp	ax, [bp+var_2]
		jg	loc_17FB7

loc_17EB5:
		mov	word_25FE6, 2
		mov	byte_25FF8, 1
		jmp	loc_17FB7
; ---------------------------------------------------------------------------

loc_17EC3:
		mov	al, byte_2C978
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		add	al, 98h
		mov	[bp+var_9], al
		mov	[bp+var_4], 1
		mov	[bp+var_6], 1
		cmp	byte_25FEB, 4
		jnz	short loc_17EE9
		mov	ax, 640h
		jmp	short loc_17EFA
; ---------------------------------------------------------------------------

loc_17EE9:
		push	3C00500h
		push	5000500h
		call	sub_E758

loc_17EFA:
		mov	[bp+var_8], ax
		mov	dword_2CE8E, 0
		xor	di, di
		jmp	loc_17F8D
; ---------------------------------------------------------------------------

loc_17F0B:
		cmp	byte ptr [si], 1
		jnz	short loc_17F89
		mov	word ptr [si+0Ah], 0
		mov	word ptr [si+0Ch], 0
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		cmp	[bp+var_9], 4Ch	; 'L'
		jnb	short loc_17F31
		mov	al, [bp+var_9]
		mov	ah, 0
		mov	[si+18h], ax
		jmp	short loc_17F86
; ---------------------------------------------------------------------------

loc_17F31:
		movzx	eax, [bp+var_4]
		add	dword_2CE8E, eax
		add	dword_2CE1A, eax
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	[bp+var_4]
		call	sub_15888
		mov	ax, [bp+var_6]
		add	[bp+var_4], ax
		add	[bp+var_6], 3
		mov	ax, [bp+var_4]
		cmp	ax, [bp+var_8]
		jbe	short loc_17F64
		mov	ax, [bp+var_8]
		mov	[bp+var_4], ax

loc_17F64:
		mov	byte ptr [si], 2
		cmp	byte_226C0, 0
		jz	short loc_17F86
		mov	ax, [bp+var_2]
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_17F86
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	1
		call	sub_16D84

loc_17F86:
		inc	[bp+var_2]

loc_17F89:
		inc	di
		sub	si, 20h	; ' '

loc_17F8D:
		cmp	di, 190h
		jl	loc_17F0B
		cmp	dword_2CE8E, 0
		jz	short loc_17FA8
		mov	byte_2CE87, 2
		mov	fp_2CE8A, offset sub_11DEA

loc_17FA8:
		inc	byte_2C978
		cmp	[bp+var_9], 4Ch	; 'L'
		jb	short loc_17FB7
		mov	byte_2C978, 0

loc_17FB7:
		cmp	byte_2C979, 0
		jz	short loc_17FC2
		dec	byte_2C979

loc_17FC2:
		pop	di
		pop	si
		leave
		retf
sub_17C04	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17FC6	proc near
		push	bp
		mov	bp, sp
		mov	ax, word ptr dword_26320
		mov	word ptr dword_26324, ax
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_26324+2,	ax
		push	0C00h
		push	word_26328
		mov	al, byte ptr word_26335
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4AEh]
		call	sub_14E50
		mov	word ptr dword_26320, ax
		push	600h
		push	word_26328
		mov	al, byte ptr word_26335
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+42Eh]
		call	sub_14E50
		mov	word ptr dword_26320+2,	ax
		mov	al, byte ptr word_26335
		add	al, 0FEh
		mov	byte ptr word_26335, al
		pop	bp
		retn
sub_17FC6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18017	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	si, 10h
		cmp	word_2632E, 0C8h
		jg	short loc_18029
		mov	si, 0Ch

loc_18029:
		mov	ax, word_26332
		cwd
		idiv	si
		or	dx, dx
		jnz	loc_180BC
		mov	byte ptr word_25FFA, 0
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte_26000, 2
		mov	byte_26001, 0Ah
		mov	word ptr dword_26002, 204h
		mov	al, byte ptr word_2634A
		mov	byte ptr word_26006, al
		add	al, 14h
		mov	byte ptr word_2634A, al
		call	fp_25344
		call	sub_15A70
		mov	byte_26000, 0
		mov	byte ptr word_25FFA, 2
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		call	fp_25344
		call	sub_157D6
		mov	byte ptr word_26006, al
		push	word ptr dword_26320
		push	200h
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4AEh]
		call	sub_14E50
		mov	word ptr dword_25FFC, ax
		push	word ptr dword_26320+2
		push	200h
		mov	al, byte ptr word_26006
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+42Eh]
		call	sub_14E50
		mov	word ptr dword_25FFC+2,	ax
		call	sub_15A5C

loc_180BC:
		pop	si
		pop	bp
		retn
sub_18017	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_180BF	proc far
		push	bp
		mov	bp, sp
		mov	eax, dword_26320
		mov	dword_25FFC, eax
		inc	word_26332
		mov	al, byte_26331
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	loc_181B5
		add	bx, bx
		jmp	cs:off_181DD[bx]

loc_180E3:
		cmp	word_26332, 100h
		jl	loc_181C4
		inc	byte_26331
		mov	word_26332, 0
		mov	byte_26330, 0CCh
		jmp	loc_181C4
; ---------------------------------------------------------------------------

loc_180FF:
		push	0C000C0h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 40h
		jl	loc_181C4
		inc	byte_26331
		mov	word_26332, 0
		mov	word_26328, 0
		mov	byte ptr word_2634A, 0E0h
		jmp	loc_181C4
; ---------------------------------------------------------------------------

loc_1812B:
		call	sub_18017
		push	1800180h
		push	4
		call	sub_1FA9D
		mov	byte_26334, al
		mov	ah, 0
		sub	word_2632E, ax
		mov	ax, 3E8h
		sub	ax, word_2632E
		cwde
		shl	eax, 6
		shl	eax, 4
		mov	ebx, 3E8h
		xor	edx, edx
		div	ebx
		mov	word_26328, ax
		call	sub_17FC6
		cmp	word_26332, 5DCh
		jge	short loc_1818B
		cmp	word_2632E, 0
		jg	short loc_181C4
		mov	byte_2C978, 1
		push	5
		call	sub_173AC
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	3
		call	sub_16D84

loc_1818B:
		mov	byte_26331, 0FEh
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	800030h
		call	sub_1597C
		call	snd_se_play pascal, 12
		jmp	short loc_181C4
; ---------------------------------------------------------------------------

loc_181B5:
		call	sub_17486
		push	word_2632E
		push	3E8h
		call	sub_17354
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_181C4:
		push	word_2632E
		push	3E8h
		call	sub_17354
		mov	ax, word ptr dword_26320
		mov	word ptr dword_2C922, ax
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_2C922+2,	ax
		pop	bp
		retf
sub_180BF	endp

; ---------------------------------------------------------------------------
		db 0
off_181DD	dw offset loc_180E3
		dw offset loc_180FF
		dw offset loc_180FF
		dw offset loc_1812B

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_181E5	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 10h
		jge	short loc_1821C
		mov	ax, word_26346
		dec	ax
		push	ax
		push	90008h
		call	sub_16A6B
		cmp	word_26346, 1
		jnz	short loc_18239
		call	snd_se_play pascal, 8
		mov	byte_2D085, 80h
		mov	byte_2D084, 0
		mov	byte_2D083, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1821C:
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		call	sub_16BD9
		or	al, al
		jz	short loc_18235
		mov	word_26346, 0
		mov	byte_26349, 0

loc_18235:
		call	fp_2CE24

loc_18239:
		pop	bp
		retn
sub_181E5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1823B	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18274
		mov	byte ptr word_25FFA, 2
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 0
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	byte ptr word_26006+1, 18h
		call	fp_25344
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 0F6h
		mov	byte_2D085, al

loc_18274:
		pop	bp
		retn
sub_1823B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18276	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_182AF
		mov	byte ptr word_25FFA, 2
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 0
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		mov	byte ptr word_26006+1, 18h
		call	fp_25344
		call	sub_15A5C
		mov	al, byte_2D084
		add	al, 0Ah
		mov	byte_2D084, al

loc_182AF:
		pop	bp
		retn
sub_18276	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_182B1	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_182EB
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte_26000, 9
		mov	byte ptr word_26006, 0
		mov	dword_26002, 7051005h
		mov	byte ptr word_26006+1, 10h
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 15

loc_182EB:
		pop	bp
		retn
sub_182B1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_182ED	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18339
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte_26000, 6
		mov	al, byte ptr word_2634A
		add	al, byte_2D083
		add	al, 80h
		mov	byte ptr word_26006, al
		mov	word ptr dword_26002+2,	608h
		mov	byte ptr word_26006+1, 10h
		call	fp_25344
		call	sub_15A5C
		mov	al, byte_2D083
		add	al, 0F8h
		mov	byte_2D083, al
		call	snd_se_play pascal, 15

loc_18339:
		pop	bp
		retn
sub_182ED	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1833B	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1837B
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	90008h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_183F3
		call	snd_se_play pascal, 8
		mov	byte_26344, 0BCh
		mov	byte_2D085, 38h	; '8'
		mov	byte_2D084, 48h	; 'H'
		mov	byte_2D083, 18h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1837B:
		cmp	word_26346, 40h
		jl	short loc_183C4
		cmp	word_26346, 60h
		jge	short loc_18398
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_183C8
		jmp	short loc_183C4
; ---------------------------------------------------------------------------

loc_18398:
		cmp	word_26346, 80h
		jge	short loc_183AF
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_183C8
		jmp	short loc_183C4
; ---------------------------------------------------------------------------

loc_183AF:
		cmp	word_26346, 0A0h
		jge	short loc_183C8
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_183C8

loc_183C4:
		inc	byte_26344

loc_183C8:
		cmp	byte_26344, 0C0h
		jb	short loc_183D4
		mov	byte_26344, 0BCh

loc_183D4:
		call	fp_2CE24
		mov	al, byte_2D07F
		mov	ah, 0
		cmp	ax, word_26346
		jg	short loc_183F3
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	byte_26344, 0B4h

loc_183F3:
		pop	bp
		retn
sub_1833B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_183F5	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1847B
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 0
		mov	byte_26000, 2
		mov	ax, word_26346
		add	ax, ax
		push	ax
		call	sub_157FA
		sub	al, byte ptr word_26346
		add	al, 40h
		mov	byte ptr word_26006, al
		mov	word ptr dword_26002, 303h
		mov	byte_26001, 0Ah
		push	1Fh
		call	sub_157E4
		add	al, 10h
		mov	byte ptr word_26006+1, al
		call	fp_25344
		call	sub_15A70
		mov	byte ptr word_25FFA, 3
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 0
		mov	ax, word_26346
		add	ax, ax
		push	ax
		call	sub_157FA
		sub	al, byte ptr word_26346
		add	al, 40h
		mov	byte ptr word_26006, al
		push	1Fh
		call	sub_157E4
		add	al, 18h
		mov	byte ptr word_26006+1, al
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1847B:
		pop	bp
		retn
sub_183F5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1847D	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_184BA
		mov	byte ptr word_25FFA, 2
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte_26000, 4
		call	sub_157D6
		mov	byte ptr word_26006, al
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte ptr dword_26002, 0Ch
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_184BA:
		pop	bp
		retn
sub_1847D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_184BC	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18524
		mov	byte ptr word_25FFA, 0
		mov	byte_26000, 4
		mov	byte ptr dword_26002, 3
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	al, byte_2D083
		mov	byte ptr word_26006+1, al
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18506
		mov	al, byte ptr word_26006+1
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	byte ptr word_26006+1, al

loc_18506:
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3
		mov	al, byte_2D085
		add	al, 6
		mov	byte_2D085, al
		mov	al, byte_2D083
		add	al, 4
		mov	byte_2D083, al

loc_18524:
		pop	bp
		retn
sub_184BC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18526	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1858E
		mov	byte ptr word_25FFA, 0
		mov	byte_26000, 4
		mov	byte ptr dword_26002, 3
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		mov	al, byte_2D083
		mov	byte ptr word_26006+1, al
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18570
		mov	al, byte ptr word_26006+1
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	byte ptr word_26006+1, al

loc_18570:
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3
		mov	al, byte_2D084
		add	al, 0FAh
		mov	byte_2D084, al
		mov	al, byte_2D083
		add	al, 4
		mov	byte_2D083, al

loc_1858E:
		pop	bp
		retn
sub_18526	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18590	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 1
		jnz	short loc_1859F
		mov	byte_26344, 0BCh

loc_1859F:
		cmp	word_26346, 20h	; ' '
		jnz	short loc_185DD
		mov	eax, dword ptr word_26335+1
		mov	dword_2630A, eax
		mov	byte_26312, 0E0h
		mov	byte_26309, 8
		mov	byte_26313, 8
		push	0
		call	sub_175A4
		mov	byte_26312, 0A0h
		push	1
		call	sub_175A4
		mov	byte_2D085, 0
		mov	byte_2D084, 1
		mov	byte_2D083, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_185DD:
		cmp	word_26346, 20h	; ' '
		jle	loc_186B4
		cmp	word_26346, 40h
		jnz	short loc_185F7
		push	0
		call	sub_175FE
		push	1
		call	sub_175FE

loc_185F7:
		mov	al, byte_2D083
		mov	ah, 0
		push	ax
		mov	ax, word_26346
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_1863F
		cmp	byte_2602A, 4Ah	; 'J'
		jbe	short loc_1863F
		mov	al, byte_26012
		inc	al
		mov	byte_26012, al
		mov	al, byte_2602A
		add	al, 0FFh
		mov	byte_2602A, al
		cmp	byte_2602A, 80h
		jz	short loc_1863B
		cmp	byte_2602A, 60h
		jz	short loc_1863B
		cmp	byte_2602A, 58h	; 'X'
		jz	short loc_1863B
		cmp	byte_2602A, 50h	; 'P'
		jnz	short loc_1863F

loc_1863B:
		inc	byte_2D083

loc_1863F:
		cmp	byte_25FE5, 0
		jnz	short loc_1869C
		mov	byte ptr word_25FFA, 10h
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	byte_26000, 2
		mov	byte_26001, 0Ah
		push	1050106h
		push	1070108h
		call	sub_E758
		mov	word ptr dword_26002, ax
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte ptr word_25FFA+1, 0
		call	sub_15A70
		mov	byte_26000, 0Dh
		mov	byte ptr word_26006+1, 10h
		mov	al, byte_2D084
		mov	byte ptr dword_26002, al
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 0Eh
		mov	byte_2D085, al

loc_1869C:
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_186B4
		cmp	byte_2D084, 8
		jnb	short loc_186B4
		inc	byte_2D084

loc_186B4:
		pop	bp
		retn
sub_18590	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_186B6	proc far
		push	bp
		mov	bp, sp
		mov	ax, word_26335+1
		mov	word ptr dword_2C922, ax
		mov	ax, word_26338
		mov	word ptr dword_2C922+2,	ax
		inc	word_26346
		mov	byte ptr word_25FFA, 0
		mov	eax, dword ptr word_26335+1
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		mov	al, byte_26345
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 4
		ja	loc_188E9
		add	bx, bx
		jmp	cs:off_188FB[bx]

loc_186EF:
		cmp	word_26346, 1
		jnz	short loc_18702
		mov	word_26342, 122Ah
		mov	word_2634C, 9F6h

loc_18702:
		call	sub_1FB07
		cmp	word_26346, 0E0h
		jl	short loc_1874E
		cmp	word_26346, 0E0h
		jnz	short loc_18737
		mov	ax, word_26335+1
		mov	word ptr dword_2A722, ax
		mov	ax, word_26338
		mov	word ptr dword_2A722+2,	ax
		mov	word_2A72A, 1400h
		mov	word_2A72C, 20h	; ' '
		mov	byte_2A72F, 3
		mov	byte_2A72E, 9

loc_18737:
		test	byte ptr word_26346, 7
		jnz	short loc_18741
		call	sub_16A03

loc_18741:
		cmp	word_26346, 0E0h
		jnz	short loc_1874E
		mov	byte_2A72E, 8

loc_1874E:
		cmp	word_26346, 100h
		jl	loc_188EE
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		inc	byte_26345
		mov	word_26346, 0
		call	snd_se_play pascal, 13

loc_1877A:
		mov	fp_23F5A, offset sub_D08C
		jmp	loc_188EE
; ---------------------------------------------------------------------------

loc_18783:
		call	sub_1FB07
		cmp	word_26346, 20h	; ' '
		jl	loc_188EE
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	byte ptr word_2634A+1, 0
		mov	byte_2D080, 0FFh
		mov	byte_2D07F, 40h
		jmp	short loc_1877A
; ---------------------------------------------------------------------------

loc_187AF:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_187BA
		jmp	short loc_18800
; ---------------------------------------------------------------------------

loc_187BA:
		mov	al, byte_2D07F
		mov	ah, 0
		mov	dx, word_26346
		sub	dx, ax
		push	dx
		call	sub_16BD9
		or	al, al
		jz	short loc_18819
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 20h ; ' '
		jnb	short loc_18827

loc_187DE:
		push	4
		call	sub_157FA
		inc	al
		mov	byte_26349, al
		cmp	al, byte_2D080
		jz	short loc_187DE
		mov	byte_2D080, al
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22758[bx-2]
		mov	fp_2CE24, ax
		jmp	short loc_18819
; ---------------------------------------------------------------------------

loc_18800:
		call	sub_181E5
		cmp	word_26346, 0
		jnz	short loc_18819
		cmp	byte_2D07F, 0Ch
		jbe	short loc_18819
		mov	al, byte_2D07F
		add	al, 0F4h
		mov	byte_2D07F, al

loc_18819:
		call	sub_1FADD
		or	al, al
		jz	loc_188EE
		push	5
		call	sub_17416

loc_18827:
		push	101C2h
		call	sub_1FB6E
		mov	byte_2D07F, 50h	; 'P'
		jmp	loc_188EE
; ---------------------------------------------------------------------------

loc_18838:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_18843
		jmp	short loc_18884
; ---------------------------------------------------------------------------

loc_18843:
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		call	sub_16BD9
		or	al, al
		jz	short loc_1889D
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 18h
		jnb	short loc_188A9

loc_18862:
		push	4
		call	sub_157FA
		inc	al
		mov	byte_26349, al
		cmp	al, byte_2D080
		jz	short loc_18862
		mov	byte_2D080, al
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, off_2275E[bx]
		mov	fp_2CE24, ax
		jmp	short loc_1889D
; ---------------------------------------------------------------------------

loc_18884:
		call	sub_1833B
		cmp	word_26346, 0
		jnz	short loc_1889D
		cmp	byte_2D07F, 0B4h
		jnb	short loc_1889D
		mov	al, byte_2D07F
		add	al, 18h
		mov	byte_2D07F, al

loc_1889D:
		call	sub_1FADD
		or	al, al
		jz	short loc_188EE
		push	5
		call	sub_17416

loc_188A9:
		push	20000h
		call	sub_1FB6E
		jmp	short loc_188EE
; ---------------------------------------------------------------------------

loc_188B4:
		call	sub_18590
		cmp	word_26346, 514h
		jl	short loc_188C6
		mov	byte ptr word_2634A+1, 0
		jmp	short loc_188D2
; ---------------------------------------------------------------------------

loc_188C6:
		call	sub_1FADD
		or	al, al
		jz	short loc_188EE
		mov	byte ptr word_2634A+1, 1

loc_188D2:
		push	0
		call	sub_17627
		push	1
		call	sub_17627
		mov	word_26346, 0
		mov	byte_26345, 0FDh
		jmp	short loc_188EE
; ---------------------------------------------------------------------------

loc_188E9:
		push	0Ah
		call	sub_1FBBE

loc_188EE:
		push	word_26342
		push	122Ah
		call	sub_17354
		pop	bp
		retf
sub_186B6	endp

; ---------------------------------------------------------------------------
		db 0
off_188FB	dw offset loc_186EF
		dw offset loc_18783
		dw offset loc_187AF
		dw offset loc_18838
		dw offset loc_188B4

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18905	proc near
		push	bp
		mov	bp, sp
		mov	eax, dword_26320
		mov	dword_26324, eax
		push	5940h
		push	word_2CE26
		push	word_2CE28
		push	word_26328
		mov	al, byte ptr word_26335
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	al, byte_2D084
		cbw
		add	word_2CE26, ax
		cmp	word_2CE26, 800h
		jge	short loc_18941
		mov	al, byte_2D084
		add	al, 2
		jmp	short loc_1894E
; ---------------------------------------------------------------------------

loc_18941:
		cmp	word_2CE26, 1000h
		jle	short loc_18951
		mov	al, byte_2D084
		add	al, 0FEh

loc_1894E:
		mov	byte_2D084, al

loc_18951:
		cmp	byte_2D085, 0
		jnz	short loc_1896C
		add	word_26328, 10h
		cmp	word_26328, 400h
		jle	short loc_1897D
		mov	byte_2D085, 1
		jmp	short loc_1897D
; ---------------------------------------------------------------------------

loc_1896C:
		sub	word_26328, 10h
		cmp	word_26328, 10h
		jg	short loc_1897D
		mov	byte_2D085, 0

loc_1897D:
		mov	al, byte ptr word_26335
		add	al, 0FEh
		mov	byte ptr word_26335, al
		pop	bp
		retn
sub_18905	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18987	proc near
		push	bp
		mov	bp, sp
		cmp	byte_25FE5, 0
		jnz	short loc_189FA
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte_26000, 6
		mov	word ptr dword_26002+2,	803h
		mov	byte ptr word_26006+1, 18h
		call	sub_157D6
		mov	byte ptr word_26006, al
		call	fp_25344
		call	sub_15A5C
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 0
		mov	byte_26000, 0Dh
		mov	byte ptr dword_26002, 3
		cmp	word_2632E, 258h
		jg	short loc_189DB
		mov	byte ptr dword_26002, 6
		jmp	short loc_189E8
; ---------------------------------------------------------------------------

loc_189DB:
		cmp	word_2632E, 320h
		jg	short loc_189E8
		mov	byte ptr dword_26002, 4

loc_189E8:
		mov	byte ptr word_26006+1, 18h
		call	sub_157D6
		mov	byte ptr word_26006, al
		call	fp_25344
		call	sub_15A5C

loc_189FA:
		pop	bp
		retn
sub_18987	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_189FC	proc near
		push	bp
		mov	bp, sp
		cmp	byte_25FE3, 0
		jnz	short loc_18A2D
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 6
		mov	word ptr dword_26002+2,	0F03h
		mov	byte ptr word_26006+1, 18h
		call	sub_157D6
		mov	byte ptr word_26006, al
		call	fp_25344
		call	sub_15A5C

loc_18A2D:
		pop	bp
		retn
sub_189FC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18A2F	proc far
		push	bp
		mov	bp, sp
		mov	eax, dword_26320
		mov	dword_25FFC, eax
		inc	word_26332
		mov	al, byte_26331
		mov	ah, 0
		or	ax, ax
		jz	short loc_18A56
		cmp	ax, 1
		jz	short loc_18A9F
		cmp	ax, 2
		jz	loc_18B24
		jmp	loc_18B91
; ---------------------------------------------------------------------------

loc_18A56:
		push	5940h
		call	sub_152D2
		push	1800180h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 100h
		jl	loc_18BA0
		inc	byte_26331
		mov	word_26332, 0
		mov	byte ptr word_26335, 0
		mov	byte_2D085, 0
		mov	byte_2D084, 20h	; ' '
		mov	word_26328, 0
		mov	word_2CE26, 0C00h
		mov	ax, word ptr dword_26320+2
		mov	word_2CE28, ax
		jmp	loc_18BA0
; ---------------------------------------------------------------------------

loc_18A9F:
		call	sub_18987
		call	sub_18905
		push	1800180h
		push	4
		call	sub_1FA9D
		mov	byte_26334, al
		mov	ah, 0
		sub	word_2632E, ax
		cmp	word_26332, 3E8h
		jge	short loc_18ADC
		cmp	word_2632E, 190h
		jg	loc_18BA0
		push	5
		call	sub_173AC
		cmp	byte_2C979, 14h
		jnb	short loc_18ADC
		mov	byte_2C979, 14h

loc_18ADC:
		inc	byte_26331
		mov	byte_26330, 0CEh
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	400020h
		call	sub_1597C
		call	snd_se_play pascal, 15
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	0C000400h
		push	0
		push	ds
		push	offset word_26328
		push	ds
		push	offset word_2632A
		push	1
		call	sub_14B0A
		jmp	short loc_18BA0
; ---------------------------------------------------------------------------

loc_18B24:
		call	sub_189FC
		push	5940h
		call	sub_152D2
		push	1800180h
		push	4
		call	sub_1FA9D
		mov	byte_26334, al
		mov	ah, 0
		sub	word_2632E, ax
		cmp	word_26332, 320h
		jge	short loc_18B67
		cmp	word_2632E, 0
		jg	short loc_18BA0
		mov	byte_2C978, 1
		push	0Fh
		call	sub_173AC
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	4
		call	sub_16D84

loc_18B67:
		mov	byte_26331, 0FEh
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	800030h
		call	sub_1597C
		call	snd_se_play pascal, 12
		jmp	short loc_18BA0
; ---------------------------------------------------------------------------

loc_18B91:
		call	sub_17486
		push	word_2632E
		push	578h
		call	sub_17354
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_18BA0:
		push	word_2632E
		push	578h
		call	sub_17354
		mov	ax, word ptr dword_26320
		mov	word ptr dword_2C922, ax
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_2C922+2,	ax
		pop	bp
		retf
sub_18A2F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18BB8	proc near

var_1		= byte ptr -1
arg_0		= word ptr  4
arg_2		= word ptr  6

		enter	2, 0
		cmp	word_26346, 1
		jnz	short loc_18BDC
		call	sub_157D6
		mov	[bp+var_1], al
		push	ds
		push	offset word_2633E
		push	ds
		push	offset word_26340
		push	word ptr [bp+var_1]
		push	[bp+arg_2]
		call	sub_14AC4

loc_18BDC:
		mov	ax, word_2633E
		add	word_26335+1, ax
		mov	ax, word_26340
		add	word_26338, ax
		cmp	word_26335+1, 300h
		jle	short loc_18BFA
		cmp	word_26335+1, 1500h
		jl	short loc_18C04

loc_18BFA:
		mov	ax, 0FFFFh
		imul	word_2633E
		mov	word_2633E, ax

loc_18C04:
		cmp	word_26338, 300h
		jle	short loc_18C14
		cmp	word_26338, 600h
		jl	short loc_18C1E

loc_18C14:
		mov	ax, 0FFFFh
		imul	word_26340
		mov	word_26340, ax

loc_18C1E:
		mov	ax, word_26346
		cmp	ax, [bp+arg_0]
		jl	short loc_18C2C
		mov	al, 1
		leave
		retn	4
; ---------------------------------------------------------------------------

loc_18C2C:
		mov	al, 0
		leave
		retn	4
sub_18BB8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18C32	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		cmp	word_26346, 10h
		jl	short loc_18C8E
		cmp	word_26346, 20h	; ' '
		jge	short loc_18C68
		mov	byte_26344, 0B8h
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	90008h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	short loc_18C8E
		call	snd_se_play pascal, 8
		jmp	short loc_18C8E
; ---------------------------------------------------------------------------

loc_18C68:
		cmp	word_26346, 20h	; ' '
		jnz	short loc_18C7A
		mov	byte_26344, 0BCh
		mov	al, 1
		pop	bp
		retn	2
; ---------------------------------------------------------------------------

loc_18C7A:
		mov	ax, word_26346
		cmp	ax, [bp+arg_0]
		jge	short loc_18C88
		mov	al, 2
		pop	bp
		retn	2
; ---------------------------------------------------------------------------

loc_18C88:
		mov	al, 3
		pop	bp
		retn	2
; ---------------------------------------------------------------------------

loc_18C8E:
		mov	al, 0
		pop	bp
		retn	2
sub_18C32	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18C94	proc near
		push	bp
		mov	bp, sp
		push	40h
		call	sub_18C32
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_18CB1
		cmp	ax, 2
		jz	short loc_18D07
		cmp	ax, 3
		jz	loc_18D42
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18CB1:
		mov	byte ptr word_25FFA, 0
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 2
		mov	al, byte_2D080
		mov	byte ptr word_26006+1, al
		mov	word ptr dword_26002, 605h
		mov	byte_26001, 0Ah
		mov	al, 1
		sub	al, byte_2D085
		mov	byte_2D085, al
		cmp	byte_2D085, 0
		jz	short loc_18CE8
		mov	byte ptr word_26006, 20h ; ' '
		jmp	short loc_18CED
; ---------------------------------------------------------------------------

loc_18CE8:
		mov	byte ptr word_26006, 60h

loc_18CED:
		call	fp_25344
		call	snd_se_play pascal, 15
		cmp	byte_2D080, 24h	; '$'
		jnb	short loc_18D07
		mov	al, byte_2D080
		add	al, 4
		mov	byte_2D080, al

loc_18D07:
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18D52
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A5C
		cmp	byte_2D085, 0
		jz	short loc_18D30
		mov	al, byte ptr word_26006
		add	al, 87h
		jmp	short loc_18D35
; ---------------------------------------------------------------------------

loc_18D30:
		mov	al, byte ptr word_26006
		add	al, 79h	; 'y'

loc_18D35:
		mov	byte ptr word_26006, al
		mov	al, byte ptr word_26006+1
		add	al, 4
		mov	byte ptr word_26006+1, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18D42:
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte_26344, 0B4h

loc_18D52:
		pop	bp
		retn
sub_18C94	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18D54	proc near
		push	bp
		mov	bp, sp
		push	60h
		call	sub_18C32
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_18D6F
		cmp	ax, 2
		jz	short loc_18D9E
		cmp	ax, 3
		jz	short loc_18DCD
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18D6F:
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	byte_26000, 6
		mov	byte ptr word_26006+1, 20h ; ' '
		push	50A050Ch
		push	60C060Eh
		call	sub_E758
		mov	word ptr dword_26002+2,	ax
		mov	byte ptr word_26006, 0C0h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18D9E:
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18DDD
		call	sub_15A5C
		cmp	byte_2D085, 0
		jz	short loc_18DBC
		mov	al, byte ptr word_26006
		add	al, 0F8h
		jmp	short loc_18DC1
; ---------------------------------------------------------------------------

loc_18DBC:
		mov	al, byte ptr word_26006
		add	al, 8

loc_18DC1:
		mov	byte ptr word_26006, al
		call	snd_se_play pascal, 15
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18DCD:
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte_26344, 0B4h

loc_18DDD:
		pop	bp
		retn
sub_18D54	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18DDF	proc near

var_1		= byte ptr -1

		enter	2, 0
		push	si
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_18EBA
		mov	byte ptr word_25FFA, 3
		mov	byte_26000, 0
		mov	byte ptr word_25FFA+1, 0
		call	fp_25344
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18E6A
		mov	byte ptr word_26006, 24h ; '$'
		xor	si, si
		jmp	short loc_18E63
; ---------------------------------------------------------------------------

loc_18E21:
		mov	al, byte ptr word_26006
		mov	[bp+var_1], al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, 40h
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, [bp+var_1]
		mov	byte ptr word_26006, al
		mov	al, byte ptr word_26006+1
		add	al, 0FBh
		mov	byte ptr word_26006+1, al
		mov	al, byte ptr word_26006
		add	al, 8
		mov	byte ptr word_26006, al
		inc	si

loc_18E63:
		cmp	si, 8
		jl	short loc_18E21
		jmp	short loc_18EBA
; ---------------------------------------------------------------------------

loc_18E6A:
		mov	byte ptr word_26006, 64h ; 'd'
		xor	si, si
		jmp	short loc_18EB5
; ---------------------------------------------------------------------------

loc_18E73:
		mov	al, byte ptr word_26006
		mov	[bp+var_1], al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, 0C0h
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, [bp+var_1]
		mov	byte ptr word_26006, al
		mov	al, byte ptr word_26006+1
		add	al, 0FBh
		mov	byte ptr word_26006+1, al
		mov	al, byte ptr word_26006
		add	al, 8
		mov	byte ptr word_26006, al
		inc	si

loc_18EB5:
		cmp	si, 8
		jl	short loc_18E73

loc_18EBA:
		pop	si
		leave
		retn
sub_18DDF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18EBD	proc near
		push	bp
		mov	bp, sp
		push	80h
		call	sub_18C32
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_18ED9
		cmp	ax, 2
		jz	short loc_18F04
		cmp	ax, 3
		jz	short loc_18F4A
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18ED9:
		mov	eax, dword ptr word_26335+1
		mov	dword_2630A, eax
		mov	byte_26313, 6
		mov	byte_26309, 8
		mov	byte_26312, 0F0h
		mov	word_26318, 1Eh
		mov	word_26314, 68h	; 'h'
		push	1
		call	sub_157E4
		mov	byte_2D085, al

loc_18F04:
		cmp	byte_26312, 0F0h
		jnb	short loc_18F12
		cmp	byte_26312, 80h
		ja	short loc_18F5A

loc_18F12:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18F5A
		cmp	byte_2D085, 0
		jz	short loc_18F2B
		call	sub_174C7
		jmp	short loc_18F40
; ---------------------------------------------------------------------------

loc_18F2B:
		mov	al, 80h
		sub	al, byte_26312
		mov	byte_26312, al
		call	sub_174C7
		mov	al, 80h
		sub	al, byte_26312
		mov	byte_26312, al

loc_18F40:
		mov	al, byte_26312
		add	al, 0Ah
		mov	byte_26312, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18F4A:
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte_26344, 0B4h

loc_18F5A:
		pop	bp
		retn
sub_18EBD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18F5C	proc near
		push	bp
		mov	bp, sp
		push	40h
		call	sub_18C32
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_18F72
		cmp	ax, 3
		jz	short loc_18FD0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18F72:
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	byte_26000, 0Bh
		mov	al, byte_2D080
		mov	byte ptr word_26006+1, al
		cmp	byte_2D080, 20h	; ' '
		jnb	short loc_18F93
		add	al, 4
		mov	byte_2D080, al

loc_18F93:
		mov	dword_26002, 9050818h
		mov	byte ptr word_26006, 0
		mov	byte_26001, 2
		mov	byte_2C976, 1
		push	1
		call	sub_157E4
		or	ax, ax
		jz	short loc_18FBB
		mov	byte_2C977, 20h	; ' '
		jmp	short loc_18FC0
; ---------------------------------------------------------------------------

loc_18FBB:
		mov	byte_2C977, 0E0h

loc_18FC0:
		call	fp_25344
		call	snd_se_play pascal, 15
		call	sub_15A70
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18FD0:
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte_26344, 0B4h
		pop	bp
		retn
sub_18F5C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18FE2	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_19038
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 3
		mov	byte ptr word_25FFA+1, 0
		mov	byte_26001, 0Ah
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	word ptr dword_26002, 220h
		call	fp_25344
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_19029
		mov	byte ptr word_26006, 1Fh
		jmp	short loc_1902E
; ---------------------------------------------------------------------------

loc_19029:
		mov	byte ptr word_26006, 0E1h

loc_1902E:
		call	sub_15A70
		call	snd_se_play pascal, 3

loc_19038:
		pop	bp
		retn
sub_18FE2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1903A	proc far
		push	bp
		mov	bp, sp
		mov	ax, word_26335+1
		mov	word ptr dword_2C922, ax
		mov	ax, word_26338
		mov	word ptr dword_2C922+2,	ax
		inc	word_26346
		mov	byte ptr word_25FFA, 0
		mov	eax, dword ptr word_26335+1
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		mov	al, byte_26345
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 7
		ja	loc_1925E
		add	bx, bx
		jmp	cs:off_19270[bx]

loc_19073:
		cmp	word_26346, 1
		jnz	short loc_19097
		mov	word_26342, 1130h
		mov	word_2634C, 0BB8h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8

loc_19097:
		call	sub_1FB07
		cmp	word_26346, 80h
		jl	loc_19263
		inc	byte_26345
		mov	word_26346, 0
		call	snd_se_play pascal, 13
		mov	fp_23F5A, offset sub_D0F4
		jmp	loc_19263
; ---------------------------------------------------------------------------

loc_190BE:
		call	sub_1FB07
		cmp	word_26346, 40h
		jl	loc_19263
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	byte_2D080, 18h
		mov	byte_2D085, 0
		jmp	loc_19263
; ---------------------------------------------------------------------------

loc_190EB:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_19100
		cmp	ax, 1
		jz	short loc_1912A
		cmp	ax, 2
		jz	short loc_1912F
		jmp	short loc_19132
; ---------------------------------------------------------------------------

loc_19100:
		push	100060h
		call	sub_18BB8
		or	al, al
		jz	short loc_19132
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		mov	al, byte ptr word_2634A+1
		and	al, 1
		inc	al
		mov	byte_26349, al
		cmp	byte ptr word_2634A+1, 14h
		jb	short loc_19132
		jmp	short loc_19140
; ---------------------------------------------------------------------------

loc_1912A:
		call	sub_18C94
		jmp	short loc_19132
; ---------------------------------------------------------------------------

loc_1912F:
		call	sub_18D54

loc_19132:
		call	sub_1FADD
		or	al, al
		jz	loc_19263
		push	0Ah
		call	sub_17416

loc_19140:
		push	1076Ch
		jmp	loc_191FD
; ---------------------------------------------------------------------------

loc_19149:
		call	sub_1FADD
		cmp	word_26346, 40h
		jl	loc_19263
		jmp	loc_1920C
; ---------------------------------------------------------------------------

loc_19158:
		call	sub_18DDF
		push	0E0080h
		call	sub_18BB8
		or	al, al
		jz	short loc_19179
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 14h
		jnb	short loc_19187

loc_19179:
		call	sub_1FADD
		or	al, al
		jz	loc_19263
		push	0Ah
		call	sub_17416

loc_19187:
		push	201F4h
		call	sub_1FB6E
		mov	byte_2D084, 0
		mov	byte_2D080, 14h
		jmp	loc_19263
; ---------------------------------------------------------------------------

loc_1919D:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_191B2
		cmp	ax, 1
		jz	short loc_191E3
		cmp	ax, 2
		jz	short loc_191E8
		jmp	short loc_191EB
; ---------------------------------------------------------------------------

loc_191B2:
		push	300030h
		call	sub_18BB8
		or	al, al
		jz	short loc_191EB
		mov	al, byte_2D084
		inc	al
		mov	byte_26349, al
		mov	al, 1
		sub	al, byte_2D084
		mov	byte_2D084, al
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 14h
		jb	short loc_191EB
		jmp	short loc_191F7
; ---------------------------------------------------------------------------

loc_191E3:
		call	sub_18EBD
		jmp	short loc_191EB
; ---------------------------------------------------------------------------

loc_191E8:
		call	sub_18F5C

loc_191EB:
		call	sub_1FADD
		or	al, al
		jz	short loc_19263
		push	0Ah
		call	sub_17416

loc_191F7:
		push	10000h

loc_191FD:
		call	sub_1FB6E
		jmp	short loc_19263
; ---------------------------------------------------------------------------

loc_19202:
		call	sub_1FADD
		cmp	word_26346, 40h
		jl	short loc_19263

loc_1920C:
		mov	word_26346, 0
		inc	byte_26345
		mov	byte_26344, 0BCh
		jmp	short loc_19263
; ---------------------------------------------------------------------------

loc_1921D:
		call	sub_18FE2
		push	80080h
		call	sub_18BB8
		or	al, al
		jz	short loc_19245
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 0Ah
		jb	short loc_19245
		mov	byte ptr word_2634A+1, 0
		jmp	short loc_19251
; ---------------------------------------------------------------------------

loc_19245:
		call	sub_1FADD
		or	al, al
		jz	short loc_19263
		mov	byte ptr word_2634A+1, 1

loc_19251:
		mov	word_26346, 0
		mov	byte_26345, 0FDh
		jmp	short loc_19263
; ---------------------------------------------------------------------------

loc_1925E:
		push	0Ah
		call	sub_1FBBE

loc_19263:
		push	word_26342
		push	1130h
		call	sub_17354
		pop	bp
		retf
sub_1903A	endp

; ---------------------------------------------------------------------------
		db 0
off_19270	dw offset loc_19073
		dw offset loc_190BE
		dw offset loc_190EB
		dw offset loc_19149
		dw offset loc_19158
		dw offset loc_1919D
		dw offset loc_19202
		dw offset loc_1921D

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19280	proc near
		push	bp
		mov	bp, sp
		test	byte ptr word_26332, 3
		jnz	short loc_192F1
		cmp	byte_2D085, 0
		jnz	short loc_192D1
		inc	byte_26330
		cmp	byte_26330, 0DCh
		jb	short loc_192F1
		mov	byte_26330, 0DBh
		add	word ptr dword_26320+2,	0C0h
		mov	ax, word ptr dword_2CEA0
		mov	word ptr dword_26320, ax
		cmp	word ptr dword_26320, 400h
		jge	short loc_192BD
		mov	word ptr dword_26320, 400h
		jmp	short loc_192CB
; ---------------------------------------------------------------------------

loc_192BD:
		cmp	word ptr dword_26320, 1400h
		jle	short loc_192CB
		mov	word ptr dword_26320, 1400h

loc_192CB:
		inc	byte_2D085
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_192D1:
		dec	byte_26330
		cmp	byte_26330, 0D4h
		jnb	short loc_192F1
		mov	byte_26330, 0D0h
		mov	byte_2D085, 0
		mov	word_26332, 0
		mov	byte_2D084, 0

loc_192F1:
		pop	bp
		retn
sub_19280	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_192F3	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26332
		dec	ax
		push	ax
		push	0B000Ah
		call	sub_16A6B
		cmp	word_26332, 1
		jnz	short loc_19319
		call	snd_se_play pascal, 8
		mov	byte_26330, 0D2h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19319:
		cmp	word_26332, 10h
		jnz	short loc_19325
		mov	byte_26330, 0D3h

loc_19325:
		pop	bp
		retn
sub_192F3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19327	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 20h	; ' '
		jge	short loc_19336
		call	sub_192F3
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19336:
		cmp	word_26332, 20h	; ' '
		jnz	short loc_1937A
		mov	byte ptr word_25FFA, 2
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte ptr word_26006+1, 18h
		mov	byte_26000, 8
		mov	dword_26002, 8041003h
		mov	byte ptr word_26006, 40h

loc_1935F:
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 15
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_26324+2,	ax
		sub	word ptr dword_26320+2,	40h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1937A:
		cmp	word_26332, 30h	; '0'
		jnz	short loc_19396
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	dword_26002, 8040504h
		jmp	short loc_1935F
; ---------------------------------------------------------------------------

loc_19396:
		cmp	word_26332, 40h
		jnz	short loc_193B2
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	dword_26002, 8040A07h
		jmp	short loc_1935F
; ---------------------------------------------------------------------------

loc_193B2:
		cmp	word_26332, 60h
		jl	short loc_193BC
		call	sub_19280

loc_193BC:
		pop	bp
		retn
sub_19327	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_193BE	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 20h	; ' '
		jge	short loc_193CD
		call	sub_192F3
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_193CD:
		cmp	word_26332, 20h	; ' '
		jnz	short loc_193F5
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte ptr word_26006+1, 18h
		mov	byte_26000, 7
		mov	word ptr dword_26002+2,	808h
		mov	byte ptr word_26006, 0
		jmp	short loc_19420
; ---------------------------------------------------------------------------

loc_193F5:
		cmp	word_26332, 30h	; '0'
		jnz	short loc_19437
		mov	byte_26000, 9
		mov	byte ptr word_25FFA+1, 30h ; '0'
		push	1010402h
		push	3030404h

loc_19412:
		call	sub_E758
		mov	word ptr dword_26002, ax
		mov	word ptr dword_26002+2,	808h

loc_19420:
		call	sub_15A5C
		call	snd_se_play pascal, 15
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_26324+2,	ax
		sub	word ptr dword_26320+2,	40h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19437:
		cmp	word_26332, 40h
		jnz	short loc_19451
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		push	1010503h
		push	5040405h
		jmp	short loc_19412
; ---------------------------------------------------------------------------

loc_19451:
		cmp	word_26332, 60h
		jl	short loc_1945B
		call	sub_19280

loc_1945B:
		pop	bp
		retn
sub_193BE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1945D	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 20h	; ' '
		jge	short loc_1946C
		call	sub_192F3
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1946C:
		cmp	word_26332, 20h	; ' '
		jnz	short loc_194B1
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 34h ; '4'
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	byte_26000, 2
		mov	byte ptr dword_26002, 10h
		mov	byte ptr dword_26002+1,	8
		mov	byte ptr word_26006, 40h

loc_19496:
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 15
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_26324+2,	ax
		sub	word ptr dword_26320+2,	40h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_194B1:
		cmp	word_26332, 30h	; '0'
		jnz	short loc_194C9
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	byte ptr dword_26002, 15h
		mov	byte ptr dword_26002+1,	4
		jmp	short loc_19496
; ---------------------------------------------------------------------------

loc_194C9:
		cmp	word_26332, 40h
		jnz	short loc_194DC
		mov	byte ptr dword_26002, 10h
		mov	byte ptr dword_26002+1,	8
		jmp	short loc_19496
; ---------------------------------------------------------------------------

loc_194DC:
		cmp	word_26332, 60h
		jl	short loc_194E6
		call	sub_19280

loc_194E6:
		pop	bp
		retn
sub_1945D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_194E8	proc far
		push	bp
		mov	bp, sp
		mov	eax, dword_26320
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		inc	word_26332
		mov	al, byte_26331
		mov	ah, 0
		or	ax, ax
		jz	short loc_1950C
		cmp	ax, 1
		jz	short loc_1954E
		jmp	loc_19604
; ---------------------------------------------------------------------------

loc_1950C:
		push	5940h
		call	sub_152D2
		push	1800180h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 0C0h
		jl	loc_19613
		inc	byte_26331
		mov	word_26332, 0
		mov	byte ptr word_26335, 0
		mov	byte_2D085, 0
		mov	byte_2D084, 1
		mov	byte_2D083, 1
		mov	word_26328, 0
		jmp	loc_19613
; ---------------------------------------------------------------------------

loc_1954E:
		mov	eax, dword_26320
		mov	dword_26324, eax
		mov	al, byte_2D084
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	short loc_195A1
		add	bx, bx
		jmp	cs:off_1962C[bx]

loc_19569:
		cmp	word_26332, 20h	; ' '
		jl	short loc_195A1
		mov	al, byte_2D083
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		inc	dl
		mov	byte_2D084, dl
		inc	byte_2D083
		mov	word_26332, 0
		cmp	byte_2D083, 0Dh
		jb	short loc_195A1
		jmp	short loc_195DA
; ---------------------------------------------------------------------------

loc_19594:
		call	sub_19327
		jmp	short loc_195A1
; ---------------------------------------------------------------------------

loc_19599:
		call	sub_193BE
		jmp	short loc_195A1
; ---------------------------------------------------------------------------

loc_1959E:
		call	sub_1945D

loc_195A1:
		cmp	byte_26330, 0D4h
		jnb	short loc_195BC
		push	1800180h
		push	4
		call	sub_1FA9D
		mov	byte_26334, al
		mov	ah, 0
		sub	word_2632E, ax

loc_195BC:
		cmp	word_2632E, 0
		jg	short loc_19613
		mov	byte_2C978, 1
		push	0Fh
		call	sub_173AC
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	5
		call	sub_16D84

loc_195DA:
		mov	byte_26331, 0FEh
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	800030h
		call	sub_1597C
		call	snd_se_play pascal, 12
		jmp	short loc_19613
; ---------------------------------------------------------------------------

loc_19604:
		call	sub_17486
		push	word_2632E
		push	578h
		call	sub_17354
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_19613:
		push	word_2632E
		push	578h
		call	sub_17354
		mov	ax, word ptr dword_26320
		mov	word ptr dword_2C922, ax
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_2C922+2,	ax
		pop	bp
		retf
sub_194E8	endp

; ---------------------------------------------------------------------------
		db 0
off_1962C	dw offset loc_19569
		dw offset loc_19594
		dw offset loc_19599
		dw offset loc_1959E

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19634	proc near
		push	bp
		mov	bp, sp
		push	600h
		push	word_2BC80
		mov	al, byte ptr word_2BC71
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4AEh]
		call	sub_14E50
		mov	word_2BC71+1, ax
		push	600h
		push	word_2BC80
		mov	al, byte ptr word_2BC71
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+42Eh]
		call	sub_14E50
		mov	word_2BC74, ax
		mov	al, byte ptr word_2BC71
		add	al, 0FEh
		mov	byte ptr word_2BC71, al
		sub	word_2BC80, 20h	; ' '
		push	1200h
		push	word_2BC9A
		mov	al, byte_2BC8B
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4AEh]
		call	sub_14E50
		mov	word ptr dword_2BC8C, ax
		push	600h
		push	word_2BC9A
		mov	al, byte_2BC8B
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+42Eh]
		call	sub_14E50
		mov	word ptr dword_2BC8C+2,	ax
		mov	al, byte_2BC8B
		add	al, 2
		mov	byte_2BC8B, al
		sub	word_2BC9A, 20h	; ' '
		mov	eax, dword ptr word_2BC71+1
		mov	dword_2BC76, eax
		mov	eax, dword_2BC8C
		mov	dword_2BC90, eax
		pop	bp
		retn
sub_19634	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_196D3	proc near

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		mov	word_2CED6, 140h
		mov	word_2CED8, 140h
		mov	si, 0B290h
		mov	[bp+var_2], 0
		jmp	loc_198AB
; ---------------------------------------------------------------------------

loc_196F0:
		cmp	byte ptr [si], 0
		jz	loc_198A5
		cmp	byte ptr [si], 1
		jnz	loc_19851
		mov	eax, [si+2]
		cmp	eax, [si+6]
		jz	short loc_19773
		mov	ax, [si+6]
		sub	ax, [si+2]
		mov	di, ax
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	ax, ax
		jz	short loc_1971E
		mov	ax, di
		jmp	short loc_1972C
; ---------------------------------------------------------------------------

loc_1971E:
		mov	ax, di
		mov	bx, 4
		cwd
		idiv	bx
		or	ax, ax
		jz	short loc_19734
		mov	ax, di

loc_1972C:
		cwd
		idiv	bx
		add	[si+2],	ax
		jmp	short loc_1973A
; ---------------------------------------------------------------------------

loc_19734:
		mov	ax, [si+6]
		mov	[si+2],	ax

loc_1973A:
		mov	ax, [si+8]
		sub	ax, [si+4]
		mov	di, ax
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	ax, ax
		jz	short loc_19750
		mov	ax, di
		jmp	short loc_1975E
; ---------------------------------------------------------------------------

loc_19750:
		mov	ax, di
		mov	bx, 4
		cwd
		idiv	bx
		or	ax, ax
		jz	short loc_19766
		mov	ax, di

loc_1975E:
		cwd
		idiv	bx
		add	[si+4],	ax
		jmp	short loc_1976C
; ---------------------------------------------------------------------------

loc_19766:
		mov	ax, [si+8]
		mov	[si+4],	ax

loc_1976C:
		mov	word ptr [si+12h], 0C0h
		jmp	short loc_197DC
; ---------------------------------------------------------------------------

loc_19773:
		mov	word ptr [si+12h], 0BEh
		cmp	[bp+var_2], 0
		jnz	short loc_19785
		push	si
		call	fp_2CE2A
		jmp	short loc_1978A
; ---------------------------------------------------------------------------

loc_19785:
		push	si
		call	fp_2CE2C

loc_1978A:
		mov	ah, 0
		mov	di, ax
		or	di, di
		jz	short loc_197D9
		push	1400h
		call	sub_157FA
		add	ax, 200h
		mov	[si+6],	ax
		push	0A00h
		call	sub_157FA
		add	ax, 100h
		mov	[si+8],	ax
		cmp	[bp+var_2], 0
		jnz	short loc_197C2
		push	3
		call	sub_157E4
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22768[bx]
		mov	fp_2CE2A, ax
		jmp	short loc_197D2
; ---------------------------------------------------------------------------

loc_197C2:
		push	3
		call	sub_157E4
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22768[bx]
		mov	fp_2CE2C, ax

loc_197D2:
		mov	word ptr [si+0Eh], 0
		jmp	short loc_197DC
; ---------------------------------------------------------------------------

loc_197D9:
		inc	word ptr [si+0Eh]

loc_197DC:
		mov	ax, [si+2]
		sub	ax, word ptr dword_2CEA0
		add	ax, 0C0h
		cmp	ax, 180h
		jnb	short loc_197FF
		mov	ax, [si+4]
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 0C0h
		cmp	ax, 180h
		jnb	short loc_197FF
		mov	byte_2CEC1, 1

loc_197FF:
		cmp	byte_2D07F, 3
		jz	short loc_1984A
		mov	eax, [si+2]
		mov	dword_2CED2, eax
		call	sub_126B3
		mov	[si+16h], ax
		cmp	word ptr [si+16h], 0
		jz	short loc_19823
		call	snd_se_play pascal, 4

loc_19823:
		mov	ax, [si+16h]
		sub	[si+14h], ax
		cmp	word ptr [si+14h], 0
		jge	short loc_198A5
		inc	byte ptr [si]
		mov	word ptr [si+12h], 4
		mov	word ptr [si+16h], 0
		call	snd_se_play pascal, 12
		add	dword_2CE1A, 64h ; 'd'
		jmp	short loc_198A5
; ---------------------------------------------------------------------------

loc_1984A:
		mov	word ptr [si+16h], 0
		jmp	short loc_198A5
; ---------------------------------------------------------------------------

loc_19851:
		mov	al, [si]
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_198A3
		inc	word ptr [si+12h]
		cmp	word ptr [si+12h], 0Ch
		jl	short loc_198A3
		mov	byte ptr [si], 0
		mov	word ptr [si+2], 0C00h
		mov	word ptr [si+4], 0F000h
		mov	word ptr [si+6], 0C00h
		mov	word ptr [si+8], 0FF00h
		mov	word ptr [si+14h], 1F4h
		mov	word ptr [si+12h], 0C0h
		cmp	[bp+var_2], 0
		jnz	short loc_19897
		mov	fp_2CE2A, offset sub_19AE3
		jmp	short loc_1989D
; ---------------------------------------------------------------------------

loc_19897:
		mov	fp_2CE2C, offset sub_19AE3

loc_1989D:
		sub	word_26342, 12Ch

loc_198A3:
		inc	byte ptr [si]

loc_198A5:
		inc	[bp+var_2]
		add	si, 1Ah

loc_198AB:
		cmp	[bp+var_2], 2
		jl	loc_196F0
		pop	di
		pop	si
		leave
		retn
sub_196D3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_198B7	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_198CF
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_198CF:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19921
		cmp	word ptr [si+0Eh], 40h
		jnb	short loc_19912
		cmp	byte_25FE2, 0
		jz	short loc_19912
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte_26000, 0
		mov	eax, [si+2]
		mov	dword_25FFC, eax
		call	sub_157D6
		mov	byte ptr word_26006, al
		call	fp_25344
		call	sub_15A5C
		mov	word ptr [si+12h], 0C2h
		jmp	short loc_19921
; ---------------------------------------------------------------------------

loc_19912:
		cmp	word ptr [si+0Eh], 60h
		jb	short loc_19921
		mov	word ptr [si+12h], 0BEh
		mov	al, 1
		jmp	short loc_19923
; ---------------------------------------------------------------------------

loc_19921:
		mov	al, 0

loc_19923:
		pop	si
		pop	bp
		retn	2
sub_198B7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19928	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_19940
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_19940:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19993
		mov	word ptr [si+12h], 0C2h
		cmp	word ptr [si+0Eh], 20h ; ' '
		jnz	short loc_19984
		mov	byte ptr word_25FFA+1, 0
		mov	eax, [si+2]
		mov	dword_25FFC, eax
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_26006+1, 18h
		mov	byte_26000, 9
		mov	dword_26002, 5051203h
		mov	byte ptr word_26006, 0
		call	fp_25344
		call	sub_15A5C
		jmp	short loc_19993
; ---------------------------------------------------------------------------

loc_19984:
		cmp	word ptr [si+0Eh], 60h
		jb	short loc_19993
		mov	word ptr [si+12h], 0BEh
		mov	al, 1
		jmp	short loc_19995
; ---------------------------------------------------------------------------

loc_19993:
		mov	al, 0

loc_19995:
		pop	si
		pop	bp
		retn	2
sub_19928	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1999A	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_199B2
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_199B2:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19A08
		mov	word ptr [si+12h], 0C2h
		cmp	word ptr [si+0Eh], 40h
		jnb	short loc_199F9
		test	byte ptr [si+0Eh], 7
		jnz	short loc_199F9
		mov	byte ptr word_25FFA+1, 0
		mov	eax, [si+2]
		mov	dword_25FFC, eax
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte_26000, 3
		mov	word ptr dword_26002, 1005h
		mov	byte ptr word_26006, 0
		call	fp_25344
		call	sub_15A5C
		jmp	short loc_19A08
; ---------------------------------------------------------------------------

loc_199F9:
		cmp	word ptr [si+0Eh], 60h
		jb	short loc_19A08
		mov	word ptr [si+12h], 0BEh
		mov	al, 1
		jmp	short loc_19A0A
; ---------------------------------------------------------------------------

loc_19A08:
		mov	al, 0

loc_19A0A:
		pop	si
		pop	bp
		retn	2
sub_1999A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19A0F	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_19A27
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_19A27:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19A7D
		mov	word ptr [si+12h], 0C2h
		cmp	word ptr [si+0Eh], 40h
		jnb	short loc_19A6E
		test	byte ptr [si+0Eh], 7
		jnz	short loc_19A6E
		mov	byte ptr word_25FFA+1, 0
		mov	eax, [si+2]
		mov	dword_25FFC, eax
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte_26000, 5
		mov	word ptr dword_26002, 80Ch
		mov	byte ptr word_26006, 0
		call	fp_25344
		call	sub_15A5C
		jmp	short loc_19A7D
; ---------------------------------------------------------------------------

loc_19A6E:
		cmp	word ptr [si+0Eh], 60h
		jb	short loc_19A7D
		mov	word ptr [si+12h], 0BEh
		mov	al, 1
		jmp	short loc_19A7F
; ---------------------------------------------------------------------------

loc_19A7D:
		mov	al, 0

loc_19A7F:
		pop	si
		pop	bp
		retn	2
sub_19A0F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19A84	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_19A9C
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_19A9C:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19ADC
		mov	word ptr [si+12h], 0C2h
		test	byte ptr word_25FE0, 1Fh
		jnz	short loc_19ADC
		mov	byte ptr word_25FFA+1, 0
		mov	eax, [si+2]
		mov	dword_25FFC, eax
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_26006+1, 18h
		mov	byte_26000, 3
		mov	word ptr dword_26002, 0C07h
		mov	byte ptr word_26006, 0
		call	fp_25344
		call	sub_15A5C

loc_19ADC:
		mov	al, 0
		pop	si
		pop	bp
		retn	2
sub_19A84	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19AE3	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	word ptr [si+0Eh], 60h
		jb	short loc_19AF4
		mov	al, 1
		jmp	short loc_19AF6
; ---------------------------------------------------------------------------

loc_19AF4:
		mov	al, 0

loc_19AF6:
		pop	si
		pop	bp
		retn	2
sub_19AE3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19AFB	proc near
		push	bp
		mov	bp, sp
		mov	al, 0
		pop	bp
		retn	2
sub_19AFB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19B04	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 40h
		jge	short loc_19B2F
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h
		cmp	word_26346, 28h	; '('
		jnz	short loc_19B9B
		push	8
		jmp	short loc_19B96
; ---------------------------------------------------------------------------

loc_19B2F:
		cmp	word_26346, 40h
		jnz	short loc_19B9B
		mov	byte ptr word_25FFA, 2
		mov	byte_26000, 0Dh
		mov	byte ptr dword_26002, 2
		call	fp_25344
		xor	si, si
		jmp	short loc_19B8A
; ---------------------------------------------------------------------------

loc_19B4D:
		test	si, 1
		jz	short loc_19B57
		mov	al, 2Ch	; ','
		jmp	short loc_19B59
; ---------------------------------------------------------------------------

loc_19B57:
		mov	al, 0

loc_19B59:
		mov	byte ptr word_25FFA+1, al
		push	3Fh ; '?'
		call	sub_157E4
		add	al, 0Ch
		mov	byte ptr word_26006+1, al
		push	300h
		call	sub_157FA
		add	ax, word_26335+1
		sub	ax, 180h
		mov	word ptr dword_25FFC, ax
		push	300h
		call	sub_157FA
		add	ax, word_26338
		sub	ax, 200h
		mov	word ptr dword_25FFC+2,	ax
		call	sub_15A5C
		inc	si

loc_19B8A:
		cmp	si, 20h	; ' '
		jl	short loc_19B4D
		mov	byte_26344, 0B6h
		push	15

loc_19B96:
		call	snd_se_play

loc_19B9B:
		pop	si
		pop	bp
		retn
sub_19B04	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19B9E	proc near
		push	bp
		mov	bp, sp
		call	sub_19B04
		cmp	word_26346, 60h
		jnz	short loc_19BB6
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19BB6:
		pop	bp
		retn
sub_19B9E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19BB8	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jge	short loc_19BE2
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h
		cmp	word_26346, 28h	; '('
		jnz	short loc_19C32
		push	8
		jmp	short loc_19C19
; ---------------------------------------------------------------------------

loc_19BE2:
		cmp	word_26346, 40h
		jnz	short loc_19C20
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 0Bh
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	dword_26002, 804081Ch
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_26006, 0
		call	fp_25344
		call	sub_15A5C
		mov	byte_26344, 0B4h
		push	0Fh

loc_19C19:
		call	snd_se_play
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19C20:
		cmp	word_26346, 60h
		jnz	short loc_19C32
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19C32:
		pop	bp
		retn
sub_19BB8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19C34	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jge	short loc_19C5E
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h
		cmp	word_26346, 28h	; '('
		jnz	short loc_19CAE
		push	8
		jmp	short loc_19C95
; ---------------------------------------------------------------------------

loc_19C5E:
		cmp	word_26346, 40h
		jnz	short loc_19C9C
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 9
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	dword_26002, 7050807h
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_26006, 0
		call	fp_25344
		call	sub_15A5C
		mov	byte_26344, 0B4h
		push	15

loc_19C95:
		call	snd_se_play
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19C9C:
		cmp	word_26346, 60h
		jnz	short loc_19CAE
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19CAE:
		pop	bp
		retn
sub_19C34	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19CB0	proc near

var_2		= word ptr -2

		enter	2, 0
		mov	eax, dword ptr word_2BC71+1
		cmp	eax, dword_2BC76
		jnz	locret_19E10
		mov	eax, dword_2BC8C
		cmp	eax, dword_2BC90
		jnz	locret_19E10
		inc	word_2CE2E
		cmp	word_2CE2E, 10h
		jb	locret_19E10
		cmp	word_2CE2E, 10h
		jnz	short loc_19CFC
		mov	byte_2D07F, 1
		mov	ax, 40h
		mov	word_2BC9A, ax
		mov	word_2BC80, ax
		mov	byte_2D07E, 0C4h
		add	word_2CE30, 20h	; ' '
		leave
		retn
; ---------------------------------------------------------------------------

loc_19CFC:
		cmp	word_2CE2E, 20h	; ' '
		jb	locret_19E10
		cmp	word_2CE2E, 40h
		jnb	short loc_19D22
		mov	byte_2D07F, 2
		mov	ax, 40h
		sub	ax, word_2CE2E
		add	ax, ax
		mov	word_2BC9A, ax
		mov	word_2BC80, ax
		leave
		retn
; ---------------------------------------------------------------------------

loc_19D22:
		cmp	word_2CE2E, 50h	; 'P'
		jnb	short loc_19D56
		cmp	word_2CE2E, 40h
		jnz	short loc_19D37
		call	snd_se_play pascal, 8

loc_19D37:
		mov	byte_2D07F, 3
		cmp	word_2CE2E, 47h	; 'G'
		jz	short loc_19D4C
		cmp	word_2CE2E, 4Fh	; 'O'
		jnz	locret_19E10

loc_19D4C:
		mov	al, byte_2D07E
		add	al, 2
		mov	byte_2D07E, al
		leave
		retn
; ---------------------------------------------------------------------------

loc_19D56:
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr word_26006+1, 18h
		mov	byte_26000, 0
		call	fp_25344
		mov	word_2CED6, 380h
		mov	word_2CED8, 80h
		mov	eax, dword ptr word_2BC71+1
		mov	dword_2CED2, eax
		add	word ptr dword_2CED2, 400h
		call	sub_12842
		mov	[bp+var_2], ax
		cmp	[bp+var_2], 0
		jz	short loc_19D9D
		call	snd_se_play pascal, 9

loc_19D9D:
		mov	ax, word ptr dword_2CEA0
		sub	ax, word_2BC71+1
		cmp	ax, 800h
		jnb	short loc_19DBD
		mov	ax, word_2BC74
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 40h
		cmp	ax, 80h
		jnb	short loc_19DBD
		mov	byte_2CEC1, 1

loc_19DBD:
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_19E10
		mov	ax, word_26346
		mov	bx, 100h
		cwd
		idiv	bx
		cmp	dx, word_2CE30
		jnb	short locret_19E10
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 7
		mov	byte ptr word_26006, 0
		mov	ax, word_26335+1
		mov	word ptr dword_25FFC, ax
		mov	ax, word_26338
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002+2,	608h
		mov	byte ptr word_26006+1, 20h ; ' '
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3

locret_19E10:
		leave
		retn
sub_19CB0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19E12	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jge	short loc_19E43
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h
		cmp	word_26346, 28h	; '('
		jnz	loc_19ED8
		call	snd_se_play pascal, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19E43:
		cmp	word_26346, 40h
		jnz	short loc_19EC6
		mov	byte_26309, 6
		mov	byte_26313, 8
		mov	eax, dword_25FFC
		mov	dword_2630A, eax
		mov	word_26318, 28h	; '('
		mov	word_26314, 50h	; 'P'
		mov	ax, word ptr dword_2CEA0+2
		sub	ax, word ptr dword_2630A+2
		push	ax
		mov	ax, word ptr dword_2CEA0
		sub	ax, word ptr dword_2630A
		push	ax
		call	iatan2
		mov	byte_26312, al
		call	sub_174C7
		mov	al, byte_26312
		add	al, 10h
		mov	byte_26312, al
		call	sub_174C7
		mov	al, byte_26312
		add	al, 0E0h
		mov	byte_26312, al
		call	sub_174C7
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 0Dh
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	word ptr dword_26002, 814h
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_26006, 0
		call	fp_25344
		call	sub_15A5C
		mov	byte_26344, 0B4h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19EC6:
		cmp	word_26346, 60h
		jnz	short loc_19ED8
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19ED8:
		pop	bp
		retn
sub_19E12	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19EDA	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jge	short loc_19F0E
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h
		mov	byte_2D085, 8
		cmp	word_26346, 28h	; '('
		jnz	short loc_19F73
		call	snd_se_play pascal, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19F0E:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_19F61
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 7
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	word ptr dword_26002+2,	708h
		mov	byte ptr word_26006+1, 18h
		call	fp_25344
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		neg	al
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 5
		mov	byte_2D085, al
		mov	byte_26344, 0B4h
		call	snd_se_play pascal, 15

loc_19F61:
		cmp	word_26346, 60h
		jnz	short loc_19F73
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19F73:
		pop	bp
		retn
sub_19EDA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19F75	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jge	short loc_19FA9
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h
		mov	byte_2D085, 0
		cmp	word_26346, 28h	; '('
		jnz	short loc_1A003
		call	snd_se_play pascal, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19FA9:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_19FF1
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 4
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	word ptr dword_26002, 714h
		mov	byte ptr word_26006+1, 28h ; '('
		call	fp_25344
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 2
		mov	byte_2D085, al
		mov	byte_26344, 0B4h
		call	snd_se_play pascal, 3

loc_19FF1:
		cmp	word_26346, 60h
		jnz	short loc_1A003
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1A003:
		pop	bp
		retn
sub_19F75	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A005	proc near
		push	bp
		mov	bp, sp
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 2
		mov	byte ptr word_26006, 40h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A042
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	word ptr dword_26002, 0A0Dh
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1A042:
		pop	bp
		retn
sub_1A005	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A044	proc far
		push	bp
		mov	bp, sp
		push	si
		mov	ax, word_26335+1
		mov	word ptr dword_2C922, ax
		mov	ax, word_26338
		mov	word ptr dword_2C922+2,	ax
		inc	word_26346
		mov	byte ptr word_25FFA, 0
		mov	ax, word_26335+1
		mov	word ptr dword_25FFC, ax
		mov	ax, word_26338
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	eax, dword_25FFC
		mov	dword_2A722, eax
		mov	al, byte_26345
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 0Eh
		ja	loc_1A3AD
		add	bx, bx
		jmp	cs:off_1A3D1[bx]

loc_1A089:
		cmp	word_26346, 1
		jnz	short loc_1A0AD
		mov	word_26342, 2580h
		mov	word_2634C, 1CE8h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8

loc_1A0AD:
		call	sub_1FB07
		cmp	word_26346, 80h
		jl	loc_1A3B2
		inc	byte_26345
		mov	word_26346, 0
		call	snd_se_play pascal, 13
		mov	fp_23F5A, offset sub_D180
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A0D4:
		call	sub_1FB07
		cmp	word_26346, 40h
		jl	loc_1A3B2
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	byte_2D080, 18h
		mov	byte_2D07F, 0
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A101:
		call	sub_19B04
		call	sub_1FADD
		cmp	word_26346, 80h
		jnz	short loc_1A15A
		mov	si, 0B290h
		mov	byte ptr [si], 1
		mov	word ptr [si+12h], 0BEh
		mov	word ptr [si+10h], 1000h
		mov	byte ptr [si+1], 60h
		mov	word ptr [si+14h], 1F4h
		mov	word ptr [si+2], 0C190h
		add	si, 1Ah
		mov	byte ptr [si], 1
		mov	word ptr [si+12h], 0BEh
		mov	word ptr [si+10h], 1000h
		mov	byte ptr [si+1], 20h ; ' '
		mov	word ptr [si+14h], 1F4h
		mov	word ptr [si+2], 0C190h
		mov	fp_2CE2A, offset sub_198B7
		mov	fp_2CE2C, offset sub_198B7
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A15A:
		cmp	word_26346, 80h
		jle	loc_1A3B2
		call	sub_19634
		cmp	word_2BC80, 0
		jnz	loc_1A3B2
		inc	byte_26345
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte ptr word_2634A+1, 0
		mov	byte_2D07D, 0
		mov	word_2CE30, 0A0h
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A192:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1A1A2
		cmp	ax, 1
		jz	short loc_1A1E3
		jmp	short loc_1A1E7
; ---------------------------------------------------------------------------

loc_1A1A2:
		mov	ax, word_26346
		add	ax, 0FFF8h
		push	ax
		call	sub_16BD9
		or	al, al
		jz	short loc_1A1E7
		mov	byte_26349, 1
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 18h
		jnb	short loc_1A1F8
		push	3
		call	sub_157FA
		add	ax, ax
		mov	dl, byte_2D07D
		mov	dh, 0
		imul	dx, 6
		add	ax, dx
		mov	bx, ax
		mov	ax, off_22770[bx]
		mov	fp_2CE32, ax
		jmp	short loc_1A1E7
; ---------------------------------------------------------------------------

loc_1A1E3:
		call	fp_2CE32

loc_1A1E7:
		call	sub_1FADD
		or	al, al
		jz	loc_1A3B2
		push	7
		call	sub_17416
		call	sub_1FB19

loc_1A1F8:
		inc	byte_2D07D
		cmp	byte_2C979, 14h
		jnb	short loc_1A208
		mov	byte_2C979, 14h

loc_1A208:
		push	1
		call	sub_162CC
		inc	byte_26345
		mov	word_26346, 0
		mov	byte ptr word_2634A+1, 0
		mov	byte_26349, 0
		mov	ax, word_2634C
		mov	word_26342, ax
		cmp	byte_26345, 0Ch
		jnb	short loc_1A236
		sub	word_2634C, 898h
		jmp	short loc_1A23C
; ---------------------------------------------------------------------------

loc_1A236:
		mov	word_2634C, 0

loc_1A23C:
		mov	word_2CE2E, 0
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A245:
		mov	word ptr dword_2BC76, 800h
		mov	word ptr dword_2BC76+2,	800h
		mov	word ptr dword_2BC90, 1000h
		mov	word ptr dword_2BC90+2,	800h
		mov	word_2BC84, 1F4h
		mov	word_2BC9E, 1F4h
		mov	ax, offset sub_19AFB
		mov	fp_2CE2C, ax
		mov	fp_2CE2A, ax
		push	0C000400h
		call	sub_16CCC
		or	al, al
		jz	loc_1A359
		jmp	loc_1A34F
; ---------------------------------------------------------------------------

loc_1A284:
		mov	word ptr dword_2BC76, 800h
		mov	word ptr dword_2BC76+2,	800h
		mov	word ptr dword_2BC90, 1000h
		mov	word ptr dword_2BC90+2,	800h
		mov	word_2BC84, 1F4h
		mov	word_2BC9E, 1F4h
		mov	ax, offset sub_19AFB
		mov	fp_2CE2C, ax
		mov	fp_2CE2A, ax
		call	sub_19CB0
		call	sub_1FADD
		cmp	word_26346, 258h
		jl	loc_1A3B2
		push	5
		call	sub_17416
		push	1
		call	sub_162CC
		cmp	byte_2C979, 14h
		jnb	short loc_1A2D7
		mov	byte_2C979, 14h

loc_1A2D7:
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_2D07F, 0
		mov	word ptr dword_2BC76, 1400h
		mov	word ptr dword_2BC76+2,	600h
		mov	word ptr dword_2BC90, 400h
		mov	word ptr dword_2BC90+2,	600h
		xor	ax, ax
		mov	word_2BC98, ax
		mov	word_2BC7E, ax
		mov	fp_2CE2A, offset sub_19928
		mov	fp_2CE2C, offset sub_19928
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A315:
		mov	word ptr dword_2BC76, 400h
		mov	word ptr dword_2BC76+2,	800h
		mov	word ptr dword_2BC90, 1400h
		mov	word ptr dword_2BC90+2,	800h
		mov	word_2BC84, 1F4h
		mov	word_2BC9E, 1F4h
		mov	ax, offset sub_19A84
		mov	fp_2CE2C, ax
		mov	fp_2CE2A, ax
		push	0C000400h
		call	sub_16CCC
		or	al, al
		jz	short loc_1A359

loc_1A34F:
		mov	word_26346, 0
		inc	byte_26345

loc_1A359:
		call	sub_1FADD
		jmp	short loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A35E:
		mov	word ptr dword_2BC76, 400h
		mov	word ptr dword_2BC76+2,	800h
		mov	word ptr dword_2BC90, 1400h
		mov	word ptr dword_2BC90+2,	800h
		mov	ax, offset sub_19A84
		mov	fp_2CE2C, ax
		mov	fp_2CE2A, ax
		call	sub_1A005
		cmp	word_26346, 3E8h
		jge	short loc_1A396
		call	sub_1FADD
		or	al, al
		jz	short loc_1A3B2
		mov	byte ptr word_2634A+1, 1

loc_1A396:
		mov	word_26346, 0
		mov	byte_26345, 0FDh
		mov	byte_2BC70, 2
		mov	byte_2BC8A, 2
		jmp	short loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A3AD:
		push	0Ah
		call	sub_1FBBE

loc_1A3B2:
		push	word_26342
		push	2580h
		call	sub_17354
		cmp	byte_26345, 3
		jb	short loc_1A3CD
		cmp	byte_26345, 0FEh
		jnb	short loc_1A3CD
		call	sub_196D3

loc_1A3CD:
		pop	si
		pop	bp
		retf
sub_1A044	endp

; ---------------------------------------------------------------------------
		db 0
off_1A3D1	dw offset loc_1A089
		dw offset loc_1A0D4
		dw offset loc_1A101
		dw offset loc_1A192
		dw offset loc_1A245
		dw offset loc_1A284
		dw offset loc_1A192
		dw offset loc_1A245
		dw offset loc_1A284
		dw offset loc_1A192
		dw offset loc_1A245
		dw offset loc_1A284
		dw offset loc_1A192
		dw offset loc_1A315
		dw offset loc_1A35E

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A3EF	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		mov	byte_2297E, 1
		mov	ax, [bp+arg_4]
		mov	word_2CED6, ax
		mov	ax, [bp+arg_2]
		mov	word_2CED8, ax
		mov	eax, dword_2634E
		mov	dword_2CED2, eax
		call	sub_126B3
		mov	si, ax
		or	si, si
		jz	short loc_1A41F
		call	snd_se_play pascal, [bp+arg_0]

loc_1A41F:
		mov	byte_2297E, 0
		mov	ax, si
		pop	si
		pop	bp
		retn	6
sub_1A3EF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A42B	proc near
		push	bp
		mov	bp, sp
		call	sub_1FADD
		or	al, al
		jz	short loc_1A439
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A439:
		push	1800180h
		push	4
		call	sub_1A3EF
		mov	byte_26360, al
		mov	ah, 0
		sub	word_2635A, ax
		mov	ax, word_2635A
		cmp	ax, word_26364
		jg	short loc_1A45A
		mov	al, 2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A45A:
		mov	al, 0
		pop	bp
		retn
sub_1A42B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A45E	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_0]
		cmp	[bp+arg_2], 0
		jnz	short loc_1A4B4
		cmp	word ptr [si], 900h
		jge	short loc_1A47E
		push	60h
		call	sub_157FA
		sub	al, 30h	; '0'
		jmp	short loc_1A490
; ---------------------------------------------------------------------------

loc_1A47E:
		cmp	word ptr [si], 0F00h
		jle	short loc_1A48D
		push	60h
		call	sub_157E4
		add	al, 30h	; '0'
		jmp	short loc_1A490
; ---------------------------------------------------------------------------

loc_1A48D:
		call	sub_157D6

loc_1A490:
		mov	[si+14h], al
		cmp	byte ptr [di], 1
		jnz	short loc_1A49E
		cmp	byte ptr [si+14h], 80h
		jb	short loc_1A4A9

loc_1A49E:
		cmp	byte ptr [di], 2
		jnz	short loc_1A4B1
		cmp	byte ptr [si+14h], 80h
		jb	short loc_1A4B1

loc_1A4A9:
		mov	al, [si+14h]
		neg	al
		mov	[si+14h], al

loc_1A4B1:
		mov	byte ptr [di], 0

loc_1A4B4:
		cmp	[bp+arg_2], 0
		jl	short loc_1A52E
		lea	ax, [si+8]
		push	ax
		push	word ptr [si+14h]
		mov	ax, [bp+arg_2]
		add	ax, ax
		mov	dx, 64h	; 'd'
		sub	dx, ax
		push	dx
		call	sub_158E2
		mov	ax, [si+8]
		add	[si], ax
		mov	ax, [si+0Ah]
		add	[si+2],	ax
		cmp	word ptr [si+8], 0
		jge	short loc_1A4E6
		mov	byte ptr [si+0Eh], 0B6h
		jmp	short loc_1A4EA
; ---------------------------------------------------------------------------

loc_1A4E6:
		mov	byte ptr [si+0Eh], 0B5h

loc_1A4EA:
		cmp	word ptr [si+2], 180h
		jge	short loc_1A4FB
		mov	word ptr [si+2], 180h
		mov	byte ptr [di], 2
		jmp	short loc_1A50A
; ---------------------------------------------------------------------------

loc_1A4FB:
		cmp	word ptr [si+2], 800h
		jle	short loc_1A50A
		mov	word ptr [si+2], 800h
		mov	byte ptr [di], 1

loc_1A50A:
		cmp	word ptr [si], 200h
		jge	short loc_1A516
		mov	word ptr [si], 200h
		jmp	short loc_1A520
; ---------------------------------------------------------------------------

loc_1A516:
		cmp	word ptr [si], 1600h
		jle	short loc_1A520
		mov	word ptr [si], 1600h

loc_1A520:
		cmp	[bp+arg_2], 30h	; '0'
		jl	short loc_1A52E
		mov	byte ptr [si+0Eh], 0B4h
		mov	al, 1
		jmp	short loc_1A530
; ---------------------------------------------------------------------------

loc_1A52E:
		mov	al, 0

loc_1A530:
		pop	di
		pop	si
		pop	bp
		retn	6
sub_1A45E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A536	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		push	5956h
		push	si
		push	0C454h
		call	sub_1A45E
		push	596Eh
		push	si
		push	0C455h
		call	sub_1A45E
		pop	si
		pop	bp
		retn	2
sub_1A536	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A556	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jge	short loc_1A58D
		mov	eax, dword ptr word_26335+1
		mov	dword_2A722, eax
		mov	ax, word_26346
		add	ax, 0FFE8h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_26344, 0B7h
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1A5B1
		call	snd_se_play pascal, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A58D:
		call	fp_2CE36
		or	al, al
		jnz	short loc_1A59C
		mov	byte_26344, 0B8h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A59C:
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	byte_26344, 0B4h
		mov	byte_2635C, 0B4h

loc_1A5B1:
		pop	bp
		retn
sub_1A556	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A5B3	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jge	short loc_1A5DC
		mov	eax, dword_2634E
		mov	dword_2A722, eax
		mov	ax, word_26346
		add	ax, 0FFE8h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_2635C, 0B7h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A5DC:
		call	fp_2CE38
		or	al, al
		jnz	short loc_1A5E9
		mov	byte_2635C, 0B8h

loc_1A5E9:
		pop	bp
		retn
sub_1A5B3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A5EB	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 6
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A641
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 7
		push	3Fh ; '?'
		call	sub_157E4
		sub	al, 20h	; ' '
		mov	byte ptr word_26006, al
		mov	byte ptr word_25FFA+1, 2Fh ; '/'
		mov	ax, word_26335+1
		mov	word ptr dword_25FFC, ax
		mov	ax, word_26338
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002+2,	602h
		push	1Fh
		call	sub_157E4
		add	al, 10h
		mov	byte ptr word_26006+1, al
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1A641:
		cmp	word_26346, 80h
		jnz	short loc_1A64D
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A64D:
		mov	al, 0
		pop	bp
		retn
sub_1A5EB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A651	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1A69C
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 3
		mov	byte_26001, 1
		mov	byte ptr word_26006, 0
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	ax, word_26335+1
		mov	word ptr dword_25FFC, ax
		mov	ax, word_26338
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002, 810h
		mov	byte ptr word_26006+1, 3Ch ; '<'
		call	fp_25344
		call	sub_15A9C
		call	snd_se_play pascal, 3

loc_1A69C:
		cmp	word_26346, 60h
		jnz	short loc_1A6A7
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A6A7:
		mov	al, 0
		pop	bp
		retn
sub_1A651	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A6AB	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1A6BA
		mov	byte_2D085, 0F0h

loc_1A6BA:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A709
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 2
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		add	al, 5
		mov	byte_2D085, al
		mov	byte ptr word_25FFA+1, 0
		mov	ax, word_26335+1
		mov	word ptr dword_25FFC, ax
		mov	ax, word_26338
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002, 0A05h
		mov	byte ptr word_26006+1, 32h ; '2'
		call	fp_25344
		call	sub_15A8E
		call	snd_se_play pascal, 3

loc_1A709:
		cmp	word_26346, 0A0h
		jnz	short loc_1A715
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A715:
		mov	al, 0
		pop	bp
		retn
sub_1A6AB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A719	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A765
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 2
		mov	byte ptr word_26006, 40h
		mov	byte ptr word_25FFA+1, 2Eh ; '.'
		mov	ax, word_26335+1
		mov	word ptr dword_25FFC, ax
		mov	ax, word_26338
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002, 0C08h
		mov	byte ptr word_26006+1, 40h
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1A765:
		cmp	word_26346, 80h
		jnz	short loc_1A771
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A771:
		mov	al, 0
		pop	bp
		retn
sub_1A719	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A775	proc near

var_1		= byte ptr -1

		enter	2, 0
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1A7AF
		mov	eax, dword ptr word_26335+1
		mov	dword_2630A, eax
		mov	ax, word ptr dword_2CEA0+2
		sub	ax, word ptr dword_2630A+2
		push	ax
		mov	ax, word ptr dword_2CEA0
		sub	ax, word ptr dword_2630A
		push	ax
		call	iatan2
		mov	byte_26312, al
		mov	byte_26309, 8
		mov	byte_26313, 8
		push	0
		call	sub_175A4

loc_1A7AF:
		cmp	word_26346, 50h	; 'P'
		jnz	short loc_1A7BB
		push	0
		call	sub_175FE

loc_1A7BB:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A81A
		cmp	word_26346, 50h	; 'P'
		jl	short loc_1A7D7
		cmp	word_26346, 90h
		jl	short loc_1A7E4

loc_1A7D7:
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A81A

loc_1A7E4:
		mov	ax, word ptr dword_2CEA0+2
		sub	ax, word ptr dword_2630A+2
		push	ax
		mov	ax, word ptr dword_2CEA0
		sub	ax, word ptr dword_2630A
		push	ax
		call	iatan2
		mov	[bp-1],	al
		mov	al, byte_26012
		sub	[bp-1],	al
		cmp	byte ptr [bp-1], 0
		jle	short loc_1A80C
		inc	al
		jmp	short loc_1A817
; ---------------------------------------------------------------------------

loc_1A80C:
		cmp	byte ptr [bp-1], 0
		jge	short loc_1A81A
		mov	al, byte_26012
		add	al, 0FFh

loc_1A817:
		mov	byte_26012, al

loc_1A81A:
		cmp	word_26346, 0A0h
		jnz	short loc_1A82B
		push	0
		call	sub_17627
		mov	al, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A82B:
		mov	al, 0
		leave
		retn
sub_1A775	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A82F	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1A843
		mov	byte_2D085, 20h	; ' '
		mov	byte_2D082, 0FCh

loc_1A843:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A8B9
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 4
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	al, byte_2D082
		add	byte_2D085, al
		mov	byte ptr word_25FFA+1, 2Eh ; '.'
		mov	ax, word_26335+1
		mov	word ptr dword_25FFC, ax
		mov	ax, word_26338
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	byte ptr dword_26002, 4
		mov	byte ptr word_26006+1, 26h ; '&'
		call	fp_25344
		call	sub_15A5C
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A8B2
		push	7
		call	sub_157E4
		add	al, 10h
		mov	dl, byte_2D085
		sub	dl, al
		mov	byte_2D085, dl
		mov	al, byte_2D082
		neg	al
		mov	byte_2D082, al

loc_1A8B2:
		call	snd_se_play pascal, 3

loc_1A8B9:
		cmp	word_26346, 100h
		jnz	short loc_1A8C5
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A8C5:
		mov	al, 0
		pop	bp
		retn
sub_1A82F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A8C9	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A91D
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 3
		push	3Fh ; '?'
		call	sub_157E4
		sub	al, 20h	; ' '
		mov	byte ptr word_26006, al
		mov	byte ptr word_25FFA+1, 32h ; '2'
		mov	ax, word ptr dword_2634E
		mov	word ptr dword_25FFC, ax
		mov	ax, word ptr dword_2634E+2
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002, 507h
		mov	byte_26001, 0Ah
		push	1Fh
		call	sub_157E4
		add	al, 10h
		mov	byte ptr word_26006+1, al
		call	fp_25344
		call	sub_15A70

loc_1A91D:
		mov	al, 0
		pop	bp
		retn
sub_1A8C9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A921	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A966
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 4
		call	sub_157D6
		mov	byte ptr word_26006, al
		mov	byte ptr word_25FFA+1, 32h ; '2'
		mov	ax, word ptr dword_2634E
		mov	word ptr dword_25FFC, ax
		mov	ax, word ptr dword_2634E+2
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	byte ptr dword_26002, 20h ; ' '
		mov	byte ptr word_26006+1, 28h ; '('
		call	fp_25344
		call	sub_15A5C

loc_1A966:
		mov	al, 0
		pop	bp
		retn
sub_1A921	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A96A	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A9AF
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 7
		mov	byte ptr word_26006, 0
		mov	byte ptr word_25FFA+1, 32h ; '2'
		mov	ax, word ptr dword_2634E
		mov	word ptr dword_25FFC, ax
		mov	ax, word ptr dword_2634E+2
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002+2,	408h
		mov	byte ptr word_26006+1, 20h ; ' '
		call	fp_25344
		call	sub_15A5C

loc_1A9AF:
		mov	al, 0
		pop	bp
		retn
sub_1A96A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A9B3	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A9FF
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 2
		mov	byte ptr word_26006, 40h
		mov	byte ptr word_25FFA+1, 32h ; '2'
		mov	ax, word ptr dword_2634E
		mov	word ptr dword_25FFC, ax
		mov	ax, word ptr dword_2634E+2
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002, 0C08h
		mov	byte ptr word_26006+1, 40h
		call	fp_25344
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1A9FF:
		mov	al, 0
		pop	bp
		retn
sub_1A9B3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AA03	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1AA48
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 7
		mov	byte ptr word_26006, 0
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	ax, word ptr dword_2634E
		mov	word ptr dword_25FFC, ax
		mov	ax, word ptr dword_2634E+2
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002+2,	608h
		mov	byte ptr word_26006+1, 20h ; ' '
		call	fp_25344
		call	sub_15A5C

loc_1AA48:
		mov	al, 0
		pop	bp
		retn
sub_1AA03	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AA4C	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1AA97
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 2
		call	sub_157D6
		mov	byte ptr word_26006, al
		mov	byte ptr word_25FFA+1, 0
		mov	ax, word ptr dword_2634E
		mov	word ptr dword_25FFC, ax
		mov	ax, word ptr dword_2634E+2
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002, 202h
		push	1Fh
		call	sub_157E4
		add	al, 18h
		mov	byte ptr word_26006+1, al
		call	fp_25344
		call	sub_15A5C

loc_1AA97:
		mov	al, 0
		pop	bp
		retn
sub_1AA4C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AA9B	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1AAAF
		mov	byte_2D084, 0
		mov	byte_2D083, 4

loc_1AAAF:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1AB1B
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 4
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		mov	al, byte_2D083
		add	byte_2D084, al
		mov	byte ptr word_25FFA+1, 32h ; '2'
		mov	ax, word ptr dword_2634E
		mov	word ptr dword_25FFC, ax
		mov	ax, word ptr dword_2634E+2
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	byte ptr dword_26002, 4
		mov	byte ptr word_26006+1, 26h ; '&'
		call	fp_25344
		call	sub_15A5C
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1AB1B
		push	7
		call	sub_157E4
		add	al, byte_2D084
		add	al, 10h
		mov	byte_2D084, al
		mov	al, byte_2D083
		neg	al
		mov	byte_2D083, al

loc_1AB1B:
		mov	al, 0
		pop	bp
		retn
sub_1AA9B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AB1F	proc near

var_1		= byte ptr -1

		enter	2, 0
		cmp	word_26346, 30h	; '0'
		jz	short loc_1AB31
		cmp	word_26346, 60h
		jnz	short loc_1AB72

loc_1AB31:
		mov	eax, dword_2634E
		mov	dword ptr word_2BC71+1,	eax
		mov	word_2BC82, 0Bh
		mov	byte_2BC88, 20h	; ' '
		mov	ax, word_26335+1
		cmp	ax, word ptr dword_2634E
		jl	short loc_1AB53
		mov	[bp+var_1], 40h
		jmp	short loc_1AB57
; ---------------------------------------------------------------------------

loc_1AB53:
		mov	[bp+var_1], 0C0h

loc_1AB57:
		push	word_2BC71+1
		push	word_2BC74
		push	word ptr [bp+var_1]
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_17687
		call	snd_se_play pascal, 15

loc_1AB72:
		mov	al, 0
		leave
		retn
sub_1AB1F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AB76	proc near

var_1		= byte ptr -1

		enter	2, 0
		cmp	word_26346, 30h	; '0'
		jz	short loc_1AB88
		cmp	word_26346, 60h
		jnz	short loc_1ABC9

loc_1AB88:
		mov	eax, dword ptr word_26335+1
		mov	dword ptr word_2BC71+1,	eax
		mov	word_2BC82, 9
		mov	byte_2BC88, 20h	; ' '
		mov	ax, word_26335+1
		cmp	ax, word ptr dword_2634E
		jge	short loc_1ABAA
		mov	[bp+var_1], 40h
		jmp	short loc_1ABAE
; ---------------------------------------------------------------------------

loc_1ABAA:
		mov	[bp+var_1], 0C0h

loc_1ABAE:
		push	word_2BC71+1
		push	word_2BC74
		push	word ptr [bp+var_1]
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_17687
		call	snd_se_play pascal, 15

loc_1ABC9:
		cmp	word_26346, 80h
		jnz	short loc_1ABD6
		mov	ax, 1
		jmp	short locret_1ABD8
; ---------------------------------------------------------------------------

loc_1ABD6:
		xor	ax, ax

locret_1ABD8:
		leave
		retn
sub_1AB76	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1ABDA	proc far

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		mov	ax, word_26338
		cmp	ax, word ptr dword_2634E+2
		jle	short loc_1ABEE
		mov	eax, dword ptr word_26335+1
		jmp	short loc_1ABF2
; ---------------------------------------------------------------------------

loc_1ABEE:
		mov	eax, dword_2634E

loc_1ABF2:
		mov	dword_2C922, eax
		inc	word_26346
		mov	al, byte_26345
		mov	ah, 0
		mov	[bp+var_4], ax
		mov	cx, 6		; switch 6 cases
		mov	bx, offset word_1AFBC

loc_1AC08:
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_4]
		jz	short loc_1AC18
		add	bx, 2
		loop	loc_1AC08
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1AC18:
		jmp	word ptr cs:[bx+0Ch] ; switch jump

loc_1AC1C:
		cmp	word_26346, 1	; jumptable 0001AC18 case 0
		jnz	short loc_1AC5E
		mov	word_26342, 1194h
		mov	word_2634C, 0
		mov	word_2635A, 1194h
		mov	word_26364, 0
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	si, 0D4h
		jmp	short loc_1AC58
; ---------------------------------------------------------------------------

loc_1AC51:
		push	si
		call	super_convert_tiny
		inc	si

loc_1AC58:
		cmp	si, 0E4h
		jl	short loc_1AC51

loc_1AC5E:
		call	sub_1FB07
		push	1800180h
		push	0Ah
		call	sub_1A3EF
		cmp	word_26346, 80h
		jl	loc_1AFA7	; default
		inc	byte_26345
		mov	word_26346, 0
		call	snd_se_play pascal, 13
		mov	fp_23F5A, offset sub_D20C
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1AC90:
		call	sub_1FB07	; jumptable 0001AC18 case 1
		push	1800180h
		push	0Ah
		call	sub_1A3EF
		cmp	word_26346, 40h
		jl	loc_1AFA7	; default
		inc	byte_26345

loc_1ACAB:
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	fp_2CE36, offset sub_1A5EB
		mov	fp_2CE38, offset sub_1A8C9
		mov	fp_2D06C, offset sub_FF79
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1ACD0:
		mov	al, byte_26349	; jumptable 0001AC18 case 2
		mov	ah, 0
		or	ax, ax
		jz	short loc_1ACE3
		cmp	ax, 1
		jz	loc_1ADC9
		jmp	loc_1ADCF
; ---------------------------------------------------------------------------

loc_1ACE3:
		cmp	byte ptr word_2634A+1, 9
		jz	short loc_1ACF1
		cmp	byte ptr word_2634A+1, 0Eh
		jnz	short loc_1AD20

loc_1ACF1:
		mov	ax, word_26346
		add	ax, 0FFC0h
		mov	[bp+var_2], ax
		cmp	word_26346, 10h
		jnz	short loc_1AD29
		cmp	byte_2C979, 14h
		jnb	short loc_1AD0D
		mov	byte_2C979, 14h

loc_1AD0D:
		call	snd_se_play pascal, 15
		push	1
		call	sub_162CC
		push	2
		call	sub_1634C
		jmp	short loc_1AD29
; ---------------------------------------------------------------------------

loc_1AD20:
		mov	ax, word_26346
		add	ax, 0FFF0h
		mov	[bp+var_2], ax

loc_1AD29:
		push	[bp+var_2]
		call	sub_1A536
		or	al, al
		jz	loc_1ADCF
		mov	word_26346, 0
		inc	byte_26349
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 0Ah
		jnb	short loc_1AD6F
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 3
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22788[bx]
		mov	fp_2CE36, ax
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 3
		add	ax, ax
		mov	bx, ax
		mov	ax, off_227A0[bx]
		jmp	short loc_1ADB8
; ---------------------------------------------------------------------------

loc_1AD6F:
		cmp	byte ptr word_2634A+1, 0Fh
		jnb	short loc_1AD8E
		mov	fp_2CE36, offset sub_1A775
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 3
		add	ax, ax
		mov	bx, ax
		mov	ax, off_227A8[bx]
		jmp	short loc_1ADB8
; ---------------------------------------------------------------------------

loc_1AD8E:
		cmp	byte ptr word_2634A+1, 24h ; '$'
		jnb	short loc_1ADBD
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 3
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22790[bx]
		mov	fp_2CE36, ax
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 3
		add	ax, ax
		mov	bx, ax
		mov	ax, off_227B0[bx]

loc_1ADB8:
		mov	fp_2CE38, ax
		jmp	short loc_1ADCF
; ---------------------------------------------------------------------------

loc_1ADBD:
		mov	byte ptr word_2634A+1, 0
		mov	[bp+var_2], 1
		jmp	short loc_1AE2C
; ---------------------------------------------------------------------------

loc_1ADC9:
		call	sub_1A556
		call	sub_1A5B3

loc_1ADCF:
		mov	ax, word_26342
		add	ax, word_2635A
		cmp	ax, 157Ch
		jge	short loc_1ADF4
		cmp	byte ptr word_2634A+1, 9
		jnb	short loc_1ADF4
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte ptr word_2634A+1, 9
		jmp	short loc_1AE17
; ---------------------------------------------------------------------------

loc_1ADF4:
		mov	ax, word_26342
		add	ax, word_2635A
		cmp	ax, 8CAh
		jge	short loc_1AE17
		cmp	byte ptr word_2634A+1, 0Eh
		jnb	short loc_1AE17
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte ptr word_2634A+1, 0Eh

loc_1AE17:
		call	sub_1A42B
		mov	ah, 0
		mov	[bp+var_2], ax
		cmp	[bp+var_2], 0
		jz	loc_1AFA7	; default
		mov	byte ptr word_2634A+1, 1

loc_1AE2C:
		mov	al, byte ptr [bp+var_2]
		add	al, 0FFh
		mov	byte_26363, al
		mov	byte_26345, 0FDh
		mov	word_26346, 0
		cmp	byte_26008, 0
		jz	loc_1AFA7	; default
		push	0
		call	sub_17627
		jmp	short loc_1AE69
; ---------------------------------------------------------------------------

loc_1AE4F:
		cmp	word_26346, 10h	; jumptable 0001AC18 case 253
		jnz	short loc_1AE6C
		cmp	byte_26363, 0
		jnz	short loc_1AE64
		push	4
		call	sub_162CC
		jmp	short loc_1AE69
; ---------------------------------------------------------------------------

loc_1AE64:
		push	4
		call	sub_1634C

loc_1AE69:
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1AE6C:
		cmp	word_26346, 20h	; ' '
		jnz	loc_1AFA7	; default
		cmp	byte_26363, 0
		jnz	short loc_1AE8B
		call	sub_1637A
		mov	byte_26344, 4
		mov	byte_2635C, 0B4h
		jmp	short loc_1AE98
; ---------------------------------------------------------------------------

loc_1AE8B:
		call	sub_163B6
		mov	byte_2635C, 4
		mov	byte_26344, 0B4h

loc_1AE98:
		inc	byte_26345
		mov	al, byte ptr word_2634A+1
		mov	byte_2C978, al
		mov	word_26346, 0
		call	snd_se_play pascal, 12
		mov	byte_2CEBC, 0FFh
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1AEB7:
		cmp	word_26346, 0Ch	; jumptable 0001AC18 case 254
		jge	short loc_1AEE2
		cmp	byte_25FE2, 0
		jnz	short loc_1AECA
		mov	ax, 0FFFCh
		jmp	short loc_1AECD
; ---------------------------------------------------------------------------

loc_1AECA:
		mov	ax, 4

loc_1AECD:
		mov	word_2CE02, ax
		cmp	byte_25FE3, 1
		ja	short loc_1AEDC
		mov	ax, 0FFFCh
		jmp	short loc_1AEDF
; ---------------------------------------------------------------------------

loc_1AEDC:
		mov	ax, 4

loc_1AEDF:
		mov	word_2CE04, ax

loc_1AEE2:
		mov	fp_23F5A, offset sub_BBE8
		mov	word_25FE6, 2
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1AFA7	; default
		cmp	byte_26363, 0
		jnz	short loc_1AF0A
		inc	byte_26344
		jmp	short loc_1AF0E
; ---------------------------------------------------------------------------

loc_1AF0A:
		inc	byte_2635C

loc_1AF0E:
		cmp	word_26346, 40h
		jl	loc_1AFA7	; default
		inc	byte_26345
		mov	word_26346, 0
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1AF24:
		mov	PaletteTone, 3Ch ; '<' ; jumptable 0001AC18 case 255
		mov	byte_25FE9, 1
		cmp	word_26346, 1
		jnz	short loc_1AFA7	; default
		cmp	byte_26363, 0
		jnz	short loc_1AF66
		push	ds
		push	offset a_dm09_tx2 ; "_DM09.TX2"
		call	sub_ED87
		mov	word ptr dword_2CE9A+2,	ds
		mov	word ptr dword_2CE9A, offset aTH05_10
		mov	eax, dword_2634E
		mov	dword ptr word_26335+1,	eax
		setfarfp	farfp_2D066, sub_1B9F2
		jmp	short loc_1AF85
; ---------------------------------------------------------------------------

loc_1AF66:
		push	ds
		push	offset a_dm08_tx2 ; "_DM08.TX2"
		call	sub_ED87
		mov	word ptr dword_2CE9A+2,	ds
		mov	word ptr dword_2CE9A, offset aTH05_11
		setfarfp	farfp_2D066, sub_1C518

loc_1AF85:
		call	sub_F2B4
		mov	fp_2CE88, offset sub_11CBB
		mov	byte_26345, 0
		mov	word_26346, 0
		mov	fp_2D06A, offset sub_10F12
		mov	word_26342, 1EDCh

loc_1AFA7:
		call	sub_17726	; default
		mov	ax, word_26342
		add	ax, word_2635A
		push	ax
		push	2328h
		call	sub_17354
		pop	si
		leave
		retf
sub_1ABDA	endp
; ---------------------------------------------------------------------------
		db 0
word_1AFBC	dw	0,     1,     2,  0FDh
		dw   0FEh,  0FFh	; value	table for switch statement
		dw offset loc_1AC1C	; jump table for switch	statement
		dw offset loc_1AC90
		dw offset loc_1ACD0
		dw offset loc_1AE4F
		dw offset loc_1AEB7
		dw offset loc_1AF24

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AFD4	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26332, 10h
		jl	loc_1B09F
		mov	ax, word_26332
		add	ax, 0FFF0h
		mov	si, ax
		cmp	si, 20h	; ' '
		jge	short loc_1B039
		or	si, si
		jnz	short loc_1B004
		mov	byte_2D085, 0
		call	snd_se_play pascal, 13
		mov	ax, word ptr dword_26320
		mov	word_2CE3A, ax

loc_1B004:
		mov	ax, word_2CE3A
		mov	word ptr dword_26320, ax
		cmp	si, 14h
		jle	short loc_1B01C
		lea	ax, [si-14h]
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, 14h
		mov	si, ax

loc_1B01C:
		cmp	byte_25FE2, 0
		jz	short loc_1B02E
		mov	ax, si
		shl	ax, 5
		add	word ptr dword_26320, ax
		jmp	short loc_1B09F
; ---------------------------------------------------------------------------

loc_1B02E:
		mov	ax, si
		shl	ax, 5
		sub	word ptr dword_26320, ax
		jmp	short loc_1B09F
; ---------------------------------------------------------------------------

loc_1B039:
		cmp	si, 20h	; ' '
		jnz	short loc_1B058
		push	1000h
		call	sub_157FA
		add	ax, 400h
		mov	word_2CE3A, ax
		push	200h
		call	sub_157FA
		add	ax, 400h
		mov	word ptr dword_26320+2,	ax
		jmp	short loc_1B09F
; ---------------------------------------------------------------------------

loc_1B058:
		mov	ax, 40h
		sub	ax, si
		mov	si, ax
		cmp	si, 14h
		jle	short loc_1B071
		add	ax, 0FFECh
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, 14h
		mov	si, ax

loc_1B071:
		mov	ax, word_2CE3A
		mov	word ptr dword_26320, ax
		cmp	byte_25FE2, 0
		jz	short loc_1B089
		mov	ax, si
		shl	ax, 5
		add	word ptr dword_26320, ax
		jmp	short loc_1B092
; ---------------------------------------------------------------------------

loc_1B089:
		mov	ax, si
		shl	ax, 5
		sub	word ptr dword_26320, ax

loc_1B092:
		or	si, si
		jnz	short loc_1B09F
		mov	byte_2D085, 1
		mov	al, 1
		jmp	short loc_1B0A1
; ---------------------------------------------------------------------------

loc_1B09F:
		mov	al, 0

loc_1B0A1:
		pop	si
		pop	bp
		retn
sub_1AFD4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B0A4	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26332, 10h
		jnz	short loc_1B0CE
		call	snd_se_play pascal, 8
		mov	byte ptr word_25FFA, 2
		mov	byte_26000, 0Dh
		mov	byte ptr dword_26002, 7
		call	fp_25344
		mov	byte_26330, 0D4h

loc_1B0CE:
		cmp	word_26332, 30h	; '0'
		jl	short loc_1B139
		cmp	word_26332, 50h	; 'P'
		jg	short loc_1B139
		mov	ax, word_26332
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B139
		mov	byte ptr word_26006+1, 8
		xor	si, si
		jmp	short loc_1B12D
; ---------------------------------------------------------------------------

loc_1B0F2:
		test	si, 1
		jz	short loc_1B0FC
		mov	al, 74h	; 't'
		jmp	short loc_1B0FE
; ---------------------------------------------------------------------------

loc_1B0FC:
		mov	al, 0

loc_1B0FE:
		mov	byte ptr word_25FFA+1, al
		push	300h
		call	sub_157FA
		add	ax, word ptr dword_26320
		sub	ax, 180h
		mov	word ptr dword_25FFC, ax
		push	300h
		call	sub_157FA
		add	ax, word ptr dword_26320+2
		sub	ax, 200h
		mov	word ptr dword_25FFC+2,	ax
		call	sub_15A8E
		mov	al, byte ptr word_26006+1
		add	al, 10h
		mov	byte ptr word_26006+1, al
		inc	si

loc_1B12D:
		cmp	si, 4
		jl	short loc_1B0F2
		call	snd_se_play pascal, 15

loc_1B139:
		cmp	word_26332, 60h
		jl	short loc_1B150
		mov	byte_26330, 0D0h
		mov	word_26332, 0
		mov	byte_2D084, 0

loc_1B150:
		pop	si
		pop	bp
		retn
sub_1B0A4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B153	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 10h
		jnz	short loc_1B17C
		call	snd_se_play pascal, 8
		mov	byte_26000, 4
		mov	byte ptr dword_26002, 10h
		call	fp_25344
		mov	byte_26330, 0D4h
		mov	byte ptr word_25FFA+1, 54h ; 'T'

loc_1B17C:
		cmp	word_26332, 30h	; '0'
		jl	short loc_1B1CC
		cmp	word_26332, 50h	; 'P'
		jg	short loc_1B1CC
		mov	ax, word_26332
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B1CC
		mov	ax, word_26332
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B1B0
		mov	byte ptr word_26006+1, 38h ; '8'
		mov	byte ptr word_25FFA, 2
		jmp	short loc_1B1BA
; ---------------------------------------------------------------------------

loc_1B1B0:
		mov	byte ptr word_26006+1, 28h ; '('
		mov	byte ptr word_25FFA, 0

loc_1B1BA:
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 4
		mov	byte ptr word_26006, al
		call	snd_se_play pascal, 3

loc_1B1CC:
		cmp	word_26332, 60h
		jl	short loc_1B1E3
		mov	byte_26330, 0D0h
		mov	word_26332, 0
		mov	byte_2D084, 0

loc_1B1E3:
		pop	bp
		retn
sub_1B153	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B1E5	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 10h
		jnz	short loc_1B221
		call	snd_se_play pascal, 8
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 9
		mov	byte ptr word_26006, 20h ; ' '
		mov	dword_26002, 4040803h
		mov	byte ptr word_26006+1, 10h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		call	fp_25344
		mov	byte_26330, 0D4h

loc_1B221:
		cmp	word_26332, 30h	; '0'
		jl	short loc_1B256
		cmp	word_26332, 50h	; 'P'
		jg	short loc_1B256
		mov	ax, word_26332
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B256
		call	sub_15A5C
		mov	al, byte ptr word_26006+1
		add	al, 0Ch
		mov	byte ptr word_26006+1, al
		mov	al, byte ptr word_26006
		add	al, 0F8h
		mov	byte ptr word_26006, al
		call	snd_se_play pascal, 15

loc_1B256:
		cmp	word_26332, 60h
		jl	short loc_1B26D
		mov	byte_26330, 0D0h
		mov	word_26332, 0
		mov	byte_2D084, 0

loc_1B26D:
		pop	bp
		retn
sub_1B1E5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B26F	proc far
		push	bp
		mov	bp, sp
		mov	eax, dword_26320
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		inc	word_26332
		mov	al, byte_26331
		mov	ah, 0
		or	ax, ax
		jz	short loc_1B293
		cmp	ax, 1
		jz	short loc_1B2DC
		jmp	loc_1B392
; ---------------------------------------------------------------------------

loc_1B293:
		cmp	word_26332, 1
		jnz	short loc_1B29F
		mov	byte_2D085, 1

loc_1B29F:
		push	5940h
		call	sub_152D2
		push	1800180h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 0C0h
		jl	loc_1B3A1
		inc	byte_26331
		mov	word_26332, 0
		mov	byte ptr word_26335, 0
		mov	byte_2D084, 1
		mov	byte_2D083, 0
		mov	word_26328, 0
		jmp	loc_1B3A1
; ---------------------------------------------------------------------------

loc_1B2DC:
		mov	eax, dword_26320
		mov	dword_26324, eax
		mov	al, byte_2D084
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	short loc_1B32F
		add	bx, bx
		jmp	cs:off_1B3BA[bx]

loc_1B2F7:
		call	sub_1AFD4
		or	al, al
		jz	short loc_1B32F
		mov	word_26332, 0
		inc	byte_2D083
		mov	al, byte_2D083
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		inc	dl
		mov	byte_2D084, dl
		cmp	byte_2D083, 10h
		jb	short loc_1B32F
		jmp	short loc_1B368
; ---------------------------------------------------------------------------

loc_1B322:
		call	sub_1B0A4
		jmp	short loc_1B32F
; ---------------------------------------------------------------------------

loc_1B327:
		call	sub_1B153
		jmp	short loc_1B32F
; ---------------------------------------------------------------------------

loc_1B32C:
		call	sub_1B1E5

loc_1B32F:
		cmp	byte_2D085, 0
		jz	short loc_1B34A
		push	1800180h
		push	4
		call	sub_1FA9D
		mov	byte_26334, al
		mov	ah, 0
		sub	word_2632E, ax

loc_1B34A:
		cmp	word_2632E, 0
		jg	short loc_1B3A1
		mov	byte_2C978, 1
		push	0Fh
		call	sub_173AC
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	4
		call	sub_16D84

loc_1B368:
		mov	byte_26331, 0FEh
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	800030h
		call	sub_1597C
		call	snd_se_play pascal, 12
		jmp	short loc_1B3A1
; ---------------------------------------------------------------------------

loc_1B392:
		call	sub_17486
		push	word_2632E
		push	44Ch
		call	sub_17354
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_1B3A1:
		push	word_2632E
		push	44Ch
		call	sub_17354
		mov	ax, word ptr dword_26320
		mov	word ptr dword_2C922, ax
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_2C922+2,	ax
		pop	bp
		retf
sub_1B26F	endp

; ---------------------------------------------------------------------------
		db 0
off_1B3BA	dw offset loc_1B2F7
		dw offset loc_1B322
		dw offset loc_1B327
		dw offset loc_1B32C

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B3C2	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	si, 0B2AAh
		mov	ax, 1
		jmp	short loc_1B3D5
; ---------------------------------------------------------------------------

loc_1B3CE:
		mov	byte ptr [si], 0
		inc	ax
		add	si, 1Ah

loc_1B3D5:
		cmp	ax, 40h
		jl	short loc_1B3CE
		pop	si
		pop	bp
		retn
sub_1B3C2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B3DD	proc near

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		mov	al, byte_2BC88
		call	sub_15A42
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	si, 0B2AAh
		mov	di, 1
		jmp	short loc_1B43D
; ---------------------------------------------------------------------------

loc_1B3F6:
		cmp	byte ptr [si], 0
		jnz	short loc_1B439
		mov	byte ptr [si], 1
		mov	eax, dword ptr word_2BC71+1
		mov	[si+2],	eax
		lea	ax, [si+0Ah]
		push	ax
		push	word_2BC71
		push	[bp+var_2]
		call	sub_158E2
		mov	al, byte ptr word_2BC71
		mov	[si+1],	al
		mov	al, byte_2BC88
		mov	[si+18h], al
		mov	ax, word_2BC82
		mov	[si+12h], ax
		mov	ax, word_2BC84
		mov	[si+14h], ax
		mov	word ptr [si+16h], 0
		mov	ax, word_2BC80
		mov	[si+10h], ax
		jmp	short loc_1B442
; ---------------------------------------------------------------------------

loc_1B439:
		inc	di
		add	si, 1Ah

loc_1B43D:
		cmp	di, 40h
		jl	short loc_1B3F6

loc_1B442:
		pop	di
		pop	si
		leave
		retn
sub_1B3DD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B446	proc near

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		mov	word_2CED6, 80h
		mov	word_2CED8, 80h
		mov	si, 0B2AAh
		mov	di, 1
		jmp	loc_1B54C
; ---------------------------------------------------------------------------

loc_1B461:
		cmp	byte ptr [si], 0
		jz	loc_1B548
		inc	word ptr [si+0Eh]
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		cmp	ax, 0FF00h
		jle	short loc_1B488
		cmp	ax, 1900h
		jge	short loc_1B488
		cmp	dx, 0FF00h
		jle	short loc_1B488
		cmp	dx, 1800h
		jl	short loc_1B48B

loc_1B488:
		jmp	loc_1B545
; ---------------------------------------------------------------------------

loc_1B48B:
		cmp	byte ptr [si], 2
		jz	loc_1B535
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		add	ax, 80h
		cmp	ax, 100h
		ja	short loc_1B4B1
		add	dx, 80h
		cmp	dx, 100h
		ja	short loc_1B4B1
		mov	byte_2CEC1, 1

loc_1B4B1:
		mov	eax, [si+2]
		mov	dword_2CED2, eax
		call	sub_126B3
		mov	[bp+var_2], ax
		or	ax, ax
		jz	loc_1B548
		cmp	word ptr [si+12h], 0D4h
		jz	short loc_1B4D2
		push	10
		jmp	short loc_1B52E
; ---------------------------------------------------------------------------

loc_1B4D2:
		mov	word ptr [si+16h], 1
		mov	ax, [bp+var_2]
		sub	[si+14h], ax
		call	snd_se_play pascal, 4
		cmp	word ptr [si+14h], 0
		jge	short loc_1B548
		inc	byte ptr [si]
		mov	word ptr [si+0Eh], 0
		mov	word ptr [si+12h], 0E0h
		mov	ax, [si+0Ah]
		mov	bx, 4
		cwd
		idiv	bx
		mov	[si+0Ah], ax
		mov	ax, [si+0Ch]
		cwd
		idiv	bx
		mov	[si+0Ch], ax
		add	dword_2CE1A, 226h
		cmp	word ptr [si+10h], 0
		jz	short loc_1B52C
		cmp	word ptr [si+4], 0F00h
		jg	short loc_1B52C
		mov	eax, [si+2]
		mov	dword_25FFC, eax
		call	sub_15A5C

loc_1B52C:
		push	3

loc_1B52E:
		call	snd_se_play
		jmp	short loc_1B548
; ---------------------------------------------------------------------------

loc_1B535:
		test	byte ptr [si+0Eh], 3
		jnz	short loc_1B548
		inc	word ptr [si+12h]
		cmp	word ptr [si+12h], 0E4h
		jl	short loc_1B548

loc_1B545:
		mov	byte ptr [si], 0

loc_1B548:
		inc	di
		add	si, 1Ah

loc_1B54C:
		cmp	di, 40h
		jl	loc_1B461
		pop	di
		pop	si
		leave
		retn
sub_1B446	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B557	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1B599
		call	sub_157D6
		mov	byte_2D085, al
		mov	byte_2D084, 1
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 4
		mov	byte_26001, 0Ah
		mov	byte ptr word_25FFA+1, 32h ; '2'
		mov	al, byte_25FEB
		add	al, 5
		mov	byte ptr dword_26002, al
		mov	byte ptr word_26006+1, 36h ; '6'
		mov	byte_26344, 0D0h
		call	fp_25344
		jmp	loc_1B624
; ---------------------------------------------------------------------------

loc_1B599:
		cmp	word_26346, 30h	; '0'
		jle	loc_1B624
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B5E2
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	al, byte_2D084
		add	byte_2D085, al
		call	sub_15A70
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B5DB
		mov	al, byte_2D084
		mov	ah, 0
		imul	ax, 0Ch
		add	al, byte_2D085
		mov	byte_2D085, al

loc_1B5DB:
		call	snd_se_play pascal, 3

loc_1B5E2:
		cmp	word_26346, 0A0h
		jnz	short loc_1B5F2
		mov	al, byte_2D084
		neg	al
		mov	byte_2D084, al

loc_1B5F2:
		cmp	word_26346, 100h
		jnz	short loc_1B609
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B609:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1B624
		cmp	word_26346, 40h
		jl	short loc_1B624
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1B624:
		mov	al, 0
		pop	bp
		retn
sub_1B557	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B628	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 8
		jnz	short loc_1B64D
		mov	byte ptr word_26006, 80h
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 2
		mov	byte_26344, 0D0h
		mov	byte ptr word_25FFA+1, 30h ; '0'
		jmp	short loc_1B6C0
; ---------------------------------------------------------------------------

loc_1B64D:
		cmp	word_26346, 8
		jle	short loc_1B6C0
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B68E
		push	1Fh
		call	sub_157E4
		add	al, 8
		mov	byte ptr word_26006+1, al
		push	7
		call	sub_157E4
		mov	byte ptr dword_26002, al
		mov	byte ptr dword_26002+1,	6
		call	fp_25344
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 6
		mov	byte ptr word_26006, al
		call	snd_se_play pascal, 3

loc_1B68E:
		cmp	word_26346, 100h
		jnz	short loc_1B6A5
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B6A5:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1B6C0
		cmp	word_26346, 40h
		jl	short loc_1B6C0
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1B6C0:
		mov	al, 0
		pop	bp
		retn
sub_1B628	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B6C4	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 8
		jnz	short loc_1B6ED
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 4
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr dword_26002, 18h
		call	fp_25344
		mov	byte_26344, 0D0h
		jmp	short loc_1B750
; ---------------------------------------------------------------------------

loc_1B6ED:
		cmp	word_26346, 8
		jle	short loc_1B750
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B71B
		call	sub_157D6
		mov	byte ptr word_26006, al
		push	1Fh
		call	sub_157E4
		add	al, 20h	; ' '
		mov	byte ptr word_26006+1, al
		call	sub_15A5C
		call	snd_se_play pascal, 15

loc_1B71B:
		cmp	word_26346, 0A0h
		jnz	short loc_1B732
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B732:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1B750
		cmp	word_26346, 40h
		jl	short loc_1B750
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		add	dx, 0FFE0h
		push	dx
		call	sub_16BD9

loc_1B750:
		mov	al, 0
		pop	bp
		retn
sub_1B6C4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B754	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1B799
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 3
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	word ptr dword_26002, 0C05h
		mov	byte ptr word_26006, 0
		call	fp_25344
		mov	byte_26344, 0D0h
		mov	byte_2BC88, 40h
		jmp	loc_1B82E
; ---------------------------------------------------------------------------

loc_1B799:
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B7F9
		push	1Fh
		call	sub_157E4
		add	al, 10h
		mov	byte ptr word_26006+1, al
		call	sub_15A5C
		push	word_2BC71+1
		push	word_2BC74
		push	0
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0F4h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0F4h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 24h	; '$'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0Ch
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		call	snd_se_play pascal, 15

loc_1B7F9:
		cmp	word_26346, 0A0h
		jnz	short loc_1B810
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B810:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1B82E
		cmp	word_26346, 40h
		jl	short loc_1B82E
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		add	dx, 0FFE0h
		push	dx
		call	sub_16BD9

loc_1B82E:
		mov	al, 0
		pop	bp
		retn
sub_1B754	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B832	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1B858
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	90008h
		call	sub_16A6B
		mov	byte_26344, 0D0h
		mov	byte_2BC88, 20h	; ' '
		jmp	short loc_1B8C4
; ---------------------------------------------------------------------------

loc_1B858:
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1B866
		call	snd_se_play pascal, 15

loc_1B866:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B8A6
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 40h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 40h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 40h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 40h
		mov	byte ptr word_2BC71, al
		mov	al, byte_2D083
		add	byte ptr word_2BC71, al

loc_1B8A6:
		cmp	word_26346, 40h
		jnz	short loc_1B8C4
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, byte_2D083
		neg	al
		mov	byte_2D083, al
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B8C4:
		mov	al, 0
		pop	bp
		retn
sub_1B832	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B8C8	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 18h
		jnz	short loc_1B8FC
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 6
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	word ptr dword_26002+2,	608h
		mov	byte ptr word_26006, 10h
		mov	byte ptr word_26006+1, 20h ; ' '
		call	fp_25344
		mov	byte_26344, 0D0h
		jmp	short loc_1B96F
; ---------------------------------------------------------------------------

loc_1B8FC:
		cmp	word_26346, 18h
		jl	short loc_1B96F
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B927
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte_2D084
		add	byte_2D085, al
		call	snd_se_play pascal, 15

loc_1B927:
		cmp	word_26346, 40h
		jnz	short loc_1B958
		mov	al, byte_2D084
		neg	al
		mov	byte_2D084, al
		cmp	byte_2D084, 7Fh
		jnb	short loc_1B944
		mov	byte_2D085, 10h
		jmp	short loc_1B949
; ---------------------------------------------------------------------------

loc_1B944:
		mov	byte_2D085, 70h	; 'p'

loc_1B949:
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B958:
		cmp	byte ptr word_2634A+1, 2
		jbe	short loc_1B96F
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		add	dx, 0FFE7h
		push	dx
		call	sub_16BD9

loc_1B96F:
		mov	al, 0
		pop	bp
		retn
sub_1B8C8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B973	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 8
		jnz	short loc_1B9AC
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 0Ch
		mov	byte_26001, 3
		mov	byte_2C976, 1
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	al, byte_25FEB
		add	al, al
		add	al, 4
		mov	byte ptr dword_26002, al
		mov	byte_26344, 0D0h
		mov	byte ptr word_26006+1, 20h ; ' '
		jmp	short loc_1B9EE
; ---------------------------------------------------------------------------

loc_1B9AC:
		cmp	word_26346, 8
		jle	short loc_1B9EE
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B9C3
		call	sub_15A70

loc_1B9C3:
		cmp	word_26346, 80h
		jl	short loc_1B9EE
		cmp	word_26346, 140h
		jge	short loc_1B9E1
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		add	dx, 0FFE0h
		jmp	short loc_1B9EA
; ---------------------------------------------------------------------------

loc_1B9E1:
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx

loc_1B9EA:
		push	dx
		call	sub_16BD9

loc_1B9EE:
		mov	al, 0
		pop	bp
		retn
sub_1B973	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B9F2	proc far
		push	bp
		mov	bp, sp
		mov	eax, dword ptr word_26335+1
		mov	dword_2C922, eax
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		mov	dword ptr word_2BC71+1,	eax
		inc	word_26346
		mov	al, byte_26345
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 9
		ja	loc_1BD02
		add	bx, bx
		jmp	cs:off_1BD18[bx]

loc_1BA22:
		cmp	word_26346, 1
		jnz	short loc_1BA63
		mov	word_26342, 1EDCh
		mov	word_2634C, 11F8h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0C4h
		mov	word_2C96E, 0C6h
		mov	word_2C970, 0C5h
		mov	word_2C972, 0C4h
		mov	word_2BC82, 0D8h

loc_1BA63:
		call	sub_1FB07
		cmp	word_26346, 40h
		jl	loc_1BD09
		inc	byte_26345
		mov	word_26346, 0
		call	snd_se_play pascal, 13
		mov	fp_23F5A, offset sub_D20C
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BA89:
		call	sub_1FB07
		cmp	word_26346, 40h
		jl	loc_1BD09
		mov	byte_26344, 0CCh
		inc	byte_26345
		mov	word_26346, 0
		mov	fp_2D06C, offset sub_10EB2
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BAAD:
		call	sub_1FB07
		push	0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1BD09
		mov	byte_26344, 0CCh
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	ax, word_26335+1
		mov	word ptr dword_2634E, ax
		mov	ax, word_26338
		add	ax, 100h
		mov	word ptr dword_2634E+2,	ax
		push	word_26335+1
		push	word_26338
		call	sub_EC86
		push	4
		call	sub_162CC
		mov	fp_2CE42, offset sub_1B557
		mov	word_2C96E, 0CEh
		mov	word_2C970, 0CDh
		mov	word_2C972, 0CCh
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BB14:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1BB24
		cmp	ax, 1
		jz	short loc_1BB69
		jmp	short loc_1BB6D
; ---------------------------------------------------------------------------

loc_1BB24:
		push	word ptr dword_2634E
		push	word ptr dword_2634E+2
		call	sub_16CCC
		or	al, al
		jz	short loc_1BB6D
		mov	ax, word_26335+1
		mov	word ptr dword_2634E, ax
		mov	word ptr dword_2634E+2,	600h
		mov	word_26346, 0
		inc	byte_26349
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 0Ch
		jnb	short loc_1BB7B
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 1
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22806[bx]
		mov	fp_2CE42, ax
		jmp	short loc_1BB6D
; ---------------------------------------------------------------------------

loc_1BB69:
		call	fp_2CE42

loc_1BB6D:
		call	sub_1FADD
		or	al, al
		jz	loc_1BD09
		push	0Ah
		call	sub_17416

loc_1BB7B:
		push	10C80h
		jmp	loc_1BC4E
; ---------------------------------------------------------------------------

loc_1BB84:
		call	sub_1FADD
		push	0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1BD09
		inc	byte_26345
		mov	word_26346, 0
		mov	fp_2CE42, offset sub_1B6C4
		mov	byte_26349, 1
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BBAE:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1BBBE
		cmp	ax, 1
		jz	short loc_1BBF6
		jmp	short loc_1BBFA
; ---------------------------------------------------------------------------

loc_1BBBE:
		push	word_26335+1
		push	600h
		call	sub_16CCC
		or	al, al
		jz	short loc_1BBFA
		mov	word_26346, 0
		inc	byte_26349
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 18h
		jnb	short loc_1BC08
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 1
		add	ax, ax
		mov	bx, ax
		mov	ax, off_2280A[bx]
		mov	fp_2CE42, ax
		jmp	short loc_1BBFA
; ---------------------------------------------------------------------------

loc_1BBF6:
		call	fp_2CE42

loc_1BBFA:
		call	sub_1FADD
		or	al, al
		jz	loc_1BD09
		push	0Ah
		call	sub_17416

loc_1BC08:
		push	204B0h
		jmp	short loc_1BC4E
; ---------------------------------------------------------------------------

loc_1BC10:
		call	sub_1FADD
		push	0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1BD09
		inc	byte_26345
		mov	word_26346, 0
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BC2F:
		call	sub_1B973
		cmp	word_26346, 7D0h
		jge	short loc_1BC48
		call	sub_1FADD
		or	al, al
		jz	loc_1BD09
		push	0Ah
		call	sub_17416

loc_1BC48:
		push	30000h

loc_1BC4E:
		call	sub_1FB6E
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BC54:
		call	sub_1FADD
		push	0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1BD09
		inc	byte_26345
		mov	word_26346, 0
		mov	fp_2CE42, offset sub_1B832
		mov	byte_26349, 1
		mov	byte_2D084, 8
		mov	byte_2D085, 10h
		mov	byte_2D083, 0F8h
		jmp	short loc_1BD09
; ---------------------------------------------------------------------------

loc_1BC8C:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1BC9C
		cmp	ax, 1
		jz	short loc_1BCD7
		jmp	short loc_1BCDB
; ---------------------------------------------------------------------------

loc_1BC9C:
		cmp	word_26346, 8
		jl	short loc_1BCDB
		mov	word_26346, 0
		inc	byte_26349
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 24h ; '$'
		jb	short loc_1BCBF
		mov	byte ptr word_2634A+1, 0
		jmp	short loc_1BCE7
; ---------------------------------------------------------------------------

loc_1BCBF:
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		mov	bx, 5
		cwd
		idiv	bx
		add	dx, dx
		mov	bx, dx
		mov	ax, off_2280E[bx]
		mov	fp_2CE42, ax
		jmp	short loc_1BCDB
; ---------------------------------------------------------------------------

loc_1BCD7:
		call	fp_2CE42

loc_1BCDB:
		call	sub_1FADD
		or	al, al
		jz	short loc_1BD09
		mov	byte ptr word_2634A+1, 1

loc_1BCE7:
		push	4
		call	sub_162CC
		mov	word_26346, 0
		mov	byte_26345, 0FDh
		call	sub_1B3C2
		mov	fp_2D06C, offset nullsub_2
		jmp	short loc_1BD09
; ---------------------------------------------------------------------------

loc_1BD02:
		push	32h ; '2'
		call	sub_1FBBE
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_1BD09:
		call	sub_1B446
		push	word_26342
		push	1EDCh
		call	sub_17354
		pop	bp
		retf
sub_1B9F2	endp

; ---------------------------------------------------------------------------
off_1BD18	dw offset loc_1BA22
		dw offset loc_1BA89
		dw offset loc_1BAAD
		dw offset loc_1BB14
		dw offset loc_1BB84
		dw offset loc_1BBAE
		dw offset loc_1BC10
		dw offset loc_1BC2F
		dw offset loc_1BC54
		dw offset loc_1BC8C

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BD2C	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1BD57
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 2
		mov	byte ptr word_25FFA+1, 2Eh ; '.'
		mov	byte ptr dword_26002, 2
		mov	byte ptr word_26006, 40h
		mov	byte_26344, 0C0h
		jmp	short loc_1BDCB
; ---------------------------------------------------------------------------

loc_1BD57:
		cmp	word_26346, 20h	; ' '
		jle	short loc_1BDCB
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BD99
		mov	byte ptr dword_26002+1,	0Ch
		mov	byte ptr word_26006+1, 30h ; '0'
		xor	si, si
		jmp	short loc_1BD8D
; ---------------------------------------------------------------------------

loc_1BD79:
		call	sub_15A5C
		mov	al, byte ptr dword_26002+1
		add	al, 8
		mov	byte ptr dword_26002+1,	al
		mov	al, byte ptr word_26006+1
		add	al, 6
		mov	byte ptr word_26006+1, al
		inc	si

loc_1BD8D:
		cmp	si, 8
		jl	short loc_1BD79
		call	snd_se_play pascal, 3

loc_1BD99:
		cmp	word_26346, 0A0h
		jnz	short loc_1BDB0
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		jmp	short loc_1BDCD
; ---------------------------------------------------------------------------

loc_1BDB0:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1BDCB
		cmp	word_26346, 40h
		jl	short loc_1BDCB
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1BDCB:
		mov	al, 0

loc_1BDCD:
		pop	si
		pop	bp
		retn
sub_1BD2C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BDD0	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1BE12
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 6
		mov	byte_2C976, 1
		mov	byte_26001, 2
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	al, byte_25FEB
		add	al, 4
		mov	byte ptr dword_26002+2,	al
		mov	byte ptr dword_26002+3,	10h
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte_26344, 0C0h
		mov	byte_2D085, 60h
		jmp	loc_1BE92
; ---------------------------------------------------------------------------

loc_1BE12:
		cmp	word_26346, 20h	; ' '
		jle	short loc_1BE92
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BE60
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BE40
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	byte_2C977, 0C0h
		jmp	short loc_1BE4E
; ---------------------------------------------------------------------------

loc_1BE40:
		mov	al, 80h
		sub	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	byte_2C977, 40h

loc_1BE4E:
		call	sub_15A9C
		mov	al, byte_2D085
		add	al, 9
		mov	byte_2D085, al
		call	snd_se_play pascal, 3

loc_1BE60:
		cmp	word_26346, 0C0h
		jnz	short loc_1BE77
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1BE77:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1BE92
		cmp	word_26346, 40h
		jl	short loc_1BE92
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1BE92:
		mov	al, 0
		pop	bp
		retn
sub_1BDD0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BE96	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	ax, word_26346
		add	ax, 0FFE0h
		mov	bx, 100h
		cwd
		idiv	bx
		mov	si, dx
		or	si, si
		jnz	short loc_1BED4
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 2
		mov	byte_26001, 2
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	word ptr dword_26002, 0C03h
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	byte ptr word_26006, 0
		call	fp_25344

loc_1BED4:
		cmp	si, 80h
		jg	short loc_1BEF1
		mov	ax, si
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BEF1
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 6
		mov	byte ptr word_26006, al

loc_1BEF1:
		pop	si
		pop	bp
		retn
sub_1BE96	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BEF4	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	ax, word_26346
		add	ax, 0FFE0h
		mov	bx, 100h
		cwd
		idiv	bx
		mov	si, dx
		or	si, si
		jnz	short loc_1BF31
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 4
		mov	byte_26001, 2
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	byte ptr dword_26002, 18h
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	byte ptr word_26006, 0
		call	fp_25344

loc_1BF31:
		cmp	si, 80h
		jg	short loc_1BF4A
		mov	ax, si
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BF4A
		call	sub_15A5C
		inc	byte ptr word_26006

loc_1BF4A:
		pop	si
		pop	bp
		retn
sub_1BEF4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BF4D	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	ax, word_26346
		add	ax, 0FFE0h
		mov	bx, 100h
		cwd
		idiv	bx
		mov	si, dx
		or	si, si
		jnz	short loc_1BF9C
		mov	byte_2BC88, 30h	; '0'
		mov	byte ptr word_2BC71, 80h
		mov	word_2BC84, 18h
		mov	word_2BC80, 1
		mov	word_2BC82, 0D4h
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 0Ch
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr dword_26002, 4
		mov	byte ptr word_26006+1, 20h ; ' '
		call	fp_25344

loc_1BF9C:
		cmp	si, 80h
		jg	short loc_1BFD7
		mov	ax, si
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BFD7
		mov	al, byte ptr word_2BC71
		add	al, 10h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0F0h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0F0h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 4
		mov	byte ptr word_2BC71, al

loc_1BFD7:
		pop	si
		pop	bp
		retn
sub_1BF4D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BFDA	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1C004
		mov	byte_26344, 0C0h
		mov	byte_2BC88, 30h	; '0'
		mov	word_2BC84, 18h
		mov	word_2BC80, 1
		mov	word_2BC82, 0D4h
		jmp	loc_1C0DF
; ---------------------------------------------------------------------------

loc_1C004:
		cmp	word_26346, 20h	; ' '
		jle	loc_1C0DF
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1C0AD
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 2
		mov	byte ptr word_25FFA+1, 2Dh ; '-'
		mov	byte ptr dword_26002, 2
		mov	byte ptr word_26006, 40h
		mov	byte ptr dword_26002+1,	0Ch
		mov	byte ptr word_26006+1, 30h ; '0'
		xor	si, si
		jmp	short loc_1C057
; ---------------------------------------------------------------------------

loc_1C043:
		call	sub_15A5C
		mov	al, byte ptr dword_26002+1
		add	al, 8
		mov	byte ptr dword_26002+1,	al
		mov	al, byte ptr word_26006+1
		add	al, 6
		mov	byte ptr word_26006+1, al
		inc	si

loc_1C057:
		cmp	si, 8
		jl	short loc_1C043
		call	snd_se_play pascal, 3
		mov	byte_26000, 0Ch
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr dword_26002, 3
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C0AD
		push	word_2BC71+1
		push	word_2BC74
		push	20h ; ' '
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0E0h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0E0h
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD

loc_1C0AD:
		cmp	word_26346, 0E0h
		jnz	short loc_1C0C4
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		jmp	short loc_1C0E1
; ---------------------------------------------------------------------------

loc_1C0C4:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1C0DF
		cmp	word_26346, 40h
		jl	short loc_1C0DF
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1C0DF:
		mov	al, 0

loc_1C0E1:
		pop	si
		pop	bp
		retn
sub_1BFDA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C0E4	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1C121
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 8
		mov	byte_2C976, 1
		mov	byte_26001, 2
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	dword_26002, 8020802h
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	byte_26344, 0C0h
		mov	byte_2C977, 0B6h
		jmp	short loc_1C190
; ---------------------------------------------------------------------------

loc_1C121:
		cmp	word_26346, 20h	; ' '
		jle	short loc_1C190
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C15E
		mov	byte ptr word_26006, 80h
		call	sub_15A9C
		mov	al, byte_2C977
		neg	al
		mov	byte_2C977, al
		mov	byte ptr word_26006, 0
		call	sub_15A9C
		mov	al, byte_2C977
		neg	al
		add	al, 8
		mov	byte_2C977, al
		call	snd_se_play pascal, 3

loc_1C15E:
		cmp	word_26346, 0C0h
		jnz	short loc_1C175
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1C175:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1C190
		cmp	word_26346, 40h
		jl	short loc_1C190
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1C190:
		mov	al, 0
		pop	bp
		retn
sub_1C0E4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C194	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1C1C1
		mov	byte_26344, 0C0h
		mov	byte_2BC88, 1Ch
		mov	word_2BC84, 6
		mov	word_2BC80, 1
		mov	byte ptr word_2BC71, 80h
		mov	word_2BC82, 0D4h
		jmp	short loc_1C239
; ---------------------------------------------------------------------------

loc_1C1C1:
		cmp	word_26346, 20h	; ' '
		jle	short loc_1C239
		cmp	word_26346, 80h
		jg	short loc_1C20F
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 0Dh
		mov	byte ptr word_25FFA+1, 2Eh ; '.'
		mov	byte ptr dword_26002, 8
		mov	byte ptr word_26006+1, 18h
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C239
		mov	al, byte_2D080
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte_2D081
		add	byte_2D080, al
		call	snd_se_play pascal, 3
		jmp	short loc_1C239
; ---------------------------------------------------------------------------

loc_1C20F:
		mov	al, byte_2D081
		neg	al
		mov	byte_2D081, al
		cmp	byte_2D081, 7Fh
		jnb	short loc_1C225
		mov	byte_2D080, 0
		jmp	short loc_1C22A
; ---------------------------------------------------------------------------

loc_1C225:
		mov	byte_2D080, 80h

loc_1C22A:
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1C239:
		mov	al, 0
		pop	bp
		retn
sub_1C194	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C23D	proc near

var_2		= word ptr -2

		enter	2, 0
		cmp	word_26346, 10h
		jnz	short loc_1C2AB
		mov	byte_26344, 0C0h
		push	0Fh
		call	sub_157E4
		add	ax, 10h
		mov	[bp+var_2], ax
		mov	word_26318, 20h	; ' '
		mov	word_2631A, 5Ah	; 'Z'
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	dl, 40h
		sub	dl, byte ptr [bp+var_2]
		sub	dl, al
		mov	byte_26312, dl
		push	0
		call	sub_17548
		mov	al, byte_26312
		add	al, byte ptr [bp+var_2]
		mov	byte_26312, al
		push	1
		call	sub_17548
		mov	al, byte_26312
		add	al, byte ptr [bp+var_2]
		mov	byte_26312, al
		push	2
		call	sub_17548
		mov	al, byte_26312
		add	al, byte ptr [bp+var_2]
		mov	byte_26312, al
		push	3
		call	sub_17548
		mov	byte_2D083, 0F8h
		jmp	loc_1C347
; ---------------------------------------------------------------------------

loc_1C2AB:
		cmp	word_26346, 20h	; ' '
		jle	loc_1C347
		cmp	word_26346, 80h
		jg	short loc_1C338
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C31D
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 6
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	word ptr dword_26002+2,	608h
		mov	byte ptr word_26006+1, 18h
		mov	byte_26001, 8
		mov	byte_2C976, 1
		mov	al, byte_2D083
		mov	byte ptr word_26006, al
		call	sub_15A70
		mov	al, 80h
		sub	al, byte_2D083
		mov	byte ptr word_26006, al
		call	sub_15A70
		mov	al, byte_2D083
		add	al, 8
		mov	byte_2D083, al
		cmp	byte_2D083, 30h	; '0'
		jbe	short loc_1C316
		mov	byte_2D083, 0F8h

loc_1C316:
		call	snd_se_play pascal, 3

loc_1C31D:
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 0Dh
		mov	byte ptr word_25FFA+1, 2Eh ; '.'
		mov	byte ptr dword_26002, 6
		mov	byte ptr word_26006+1, 18h
		jmp	short loc_1C347
; ---------------------------------------------------------------------------

loc_1C338:
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1C347:
		mov	al, 0
		leave
		retn
sub_1C23D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C34B	proc near

var_2		= word ptr -2

		enter	2, 0
		push	si
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1C3B0
		mov	byte_26309, 8
		mov	byte_26313, 8
		call	sub_157D6
		mov	[bp+var_2], ax
		mov	al, byte_25FEB
		mov	ah, 0
		add	ax, 5
		mov	word_2CE3C, ax
		xor	si, si
		jmp	short loc_1C38B
; ---------------------------------------------------------------------------

loc_1C376:
		mov	ax, si
		shl	ax, 8
		cwd
		idiv	word_2CE3C
		add	al, byte ptr [bp+var_2]
		mov	byte_26312, al
		push	si
		call	sub_175A4
		inc	si

loc_1C38B:
		cmp	si, word_2CE3C
		jl	short loc_1C376
		mov	word_2CE40, 0
		mov	word_2CE3E, 1
		mov	fp_2CE44, offset sub_1BE96
		mov	byte_2D085, 1
		mov	byte_2D080, 0
		jmp	loc_1C513
; ---------------------------------------------------------------------------

loc_1C3B0:
		cmp	word_26346, 20h	; ' '
		jle	loc_1C513
		mov	ax, word_26346
		add	ax, 0FFE0h
		mov	bx, 100h
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		xor	si, si
		jmp	short loc_1C3DB
; ---------------------------------------------------------------------------

loc_1C3CC:
		mov	bx, si
		imul	bx, 18h
		mov	eax, dword ptr word_26335+1
		mov	[bx+562Ah], eax
		inc	si

loc_1C3DB:
		cmp	si, word_2CE3C
		jl	short loc_1C3CC
		cmp	[bp+var_2], 0A0h
		jnz	short loc_1C3F9
		xor	si, si
		jmp	short loc_1C3F1
; ---------------------------------------------------------------------------

loc_1C3EC:
		push	si
		call	sub_175FE
		inc	si

loc_1C3F1:
		cmp	si, word_2CE3C
		jl	short loc_1C3EC
		jmp	short loc_1C426
; ---------------------------------------------------------------------------

loc_1C3F9:
		cmp	[bp+var_2], 0D4h
		jnz	short loc_1C417
		xor	si, si
		jmp	short loc_1C40F
; ---------------------------------------------------------------------------

loc_1C404:
		mov	bx, si
		imul	bx, 18h
		mov	byte ptr [bx+5628h], 6
		inc	si

loc_1C40F:
		cmp	si, word_2CE3C
		jl	short loc_1C404
		jmp	short loc_1C426
; ---------------------------------------------------------------------------

loc_1C417:
		cmp	[bp+var_2], 0B4h
		jnz	short loc_1C426
		mov	al, byte_2D085
		neg	al
		mov	byte_2D085, al

loc_1C426:
		cmp	[bp+var_2], 70h	; 'p'
		jg	short loc_1C445
		mov	al, byte_25FE2
		mov	ah, 0
		add	word_2CE3E, ax
		cmp	word_2CE3E, 80h
		jle	short loc_1C483
		mov	word_2CE3E, 80h
		jmp	short loc_1C483
; ---------------------------------------------------------------------------

loc_1C445:
		cmp	[bp+var_2], 0C0h
		jg	short loc_1C460
		sub	word_2CE3E, 2
		cmp	word_2CE3E, 0
		jge	short loc_1C483
		mov	word_2CE3E, 0
		jmp	short loc_1C483
; ---------------------------------------------------------------------------

loc_1C460:
		mov	al, byte_25FE2
		mov	ah, 0
		add	word_2CE3E, ax
		cmp	[bp+var_2], 0D4h
		jle	short loc_1C483
		push	1Fh
		call	sub_157E4
		or	ax, ax
		jnz	short loc_1C483
		mov	ax, 0FFh
		sub	ax, [bp+var_2]
		add	word_26346, ax

loc_1C483:
		cmp	[bp+var_2], 0
		jnz	short loc_1C4A3
		mov	al, byte_2D080
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		add	dx, dx
		mov	bx, dx
		mov	ax, off_22818[bx]
		mov	fp_2CE44, ax
		inc	byte_2D080

loc_1C4A3:
		cmp	word_26346, 120h
		jl	short loc_1C4C7
		call	fp_2CE44
		cmp	word_26346, 220h
		jl	short loc_1C4C7
		cmp	[bp+var_2], 60h
		jg	short loc_1C4C7
		mov	ax, [bp+var_2]
		add	ax, 0FFE0h
		push	ax
		call	sub_16BD9

loc_1C4C7:
		mov	ax, word_2CE3E
		add	word_2CE40, ax
		cmp	word_2CE40, 10h
		jl	short loc_1C513
		mov	ax, word_2CE40
		mov	bx, 10h
		cwd
		idiv	bx
		mov	dl, byte_2D085
		mov	dh, 0
		imul	dx
		mov	[bp+var_2], ax
		mov	ax, word_2CE40
		cwd
		idiv	bx
		mov	word_2CE40, dx
		xor	si, si
		jmp	short loc_1C50D
; ---------------------------------------------------------------------------

loc_1C4F7:
		mov	bx, si
		imul	bx, 18h
		mov	al, [bx+5632h]
		add	al, byte ptr [bp+var_2]
		mov	bx, si
		imul	bx, 18h
		mov	[bx+5632h], al
		inc	si

loc_1C50D:
		cmp	si, word_2CE3C
		jl	short loc_1C4F7

loc_1C513:
		mov	al, 0
		pop	si
		leave
		retn
sub_1C34B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C518	proc far
		push	bp
		mov	bp, sp
		push	si
		mov	eax, dword ptr word_26335+1
		mov	dword_2C922, eax
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		mov	dword_2630A, eax
		mov	dword ptr word_2BC71+1,	eax
		inc	word_26346
		mov	al, byte_26345
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 9
		ja	loc_1C7FE
		add	bx, bx
		jmp	cs:off_1C816[bx]

loc_1C54D:
		cmp	word_26346, 1
		jnz	short loc_1C58E
		mov	word_26342, 1E78h
		mov	word_2634C, 16A8h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0B4h
		mov	word_2C96E, 0B6h
		mov	word_2C970, 0B5h
		mov	word_2C972, 0B4h
		mov	word_2BC82, 0D4h

loc_1C58E:
		call	sub_1FB07
		cmp	word_26346, 40h
		jl	loc_1C805
		inc	byte_26345
		mov	word_26346, 0
		call	snd_se_play pascal, 13
		mov	fp_23F5A, offset sub_D20C
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C5B4:
		call	sub_1FB07
		cmp	word_26346, 40h
		jl	loc_1C805
		mov	byte_26344, 0CCh
		inc	byte_26345
		mov	word_26346, 0
		mov	fp_2D06C, offset sub_10EB2
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C5D8:
		call	sub_1FB07
		push	0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1C805
		mov	byte_26344, 0BCh
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		push	4
		call	sub_162CC
		push	word_26335+1
		push	word_26338
		call	sub_EC86
		mov	fp_2CE42, offset sub_1BD2C
		mov	word_2C96E, 0BEh
		mov	word_2C970, 0BDh
		mov	word_2C972, 0BCh
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C630:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1C640
		cmp	ax, 1
		jz	short loc_1C678
		jmp	short loc_1C67C
; ---------------------------------------------------------------------------

loc_1C640:
		mov	ax, word_26346
		add	ax, 0FFE0h
		push	ax
		call	sub_16BD9
		or	al, al
		jz	short loc_1C67C
		mov	word_26346, 0
		inc	byte_26349
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 24h ; '$'
		jnb	short loc_1C68A
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 1
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22826[bx]
		mov	fp_2CE42, ax
		jmp	short loc_1C67C
; ---------------------------------------------------------------------------

loc_1C678:
		call	fp_2CE42

loc_1C67C:
		call	sub_1FADD
		or	al, al
		jz	loc_1C805
		push	0Ah
		call	sub_17416

loc_1C68A:
		push	10AF0h
		jmp	loc_1C755
; ---------------------------------------------------------------------------

loc_1C693:
		call	sub_1FADD
		push	0C000800h
		call	sub_16CCC
		or	al, al
		jz	loc_1C805
		inc	byte_26345
		mov	word_26346, 0
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C6B2:
		call	sub_1C34B
		cmp	word_26346, 1388h
		jge	short loc_1C6CB
		call	sub_1FADD
		or	al, al
		jz	loc_1C805
		push	0Ah
		call	sub_17416

loc_1C6CB:
		xor	si, si
		jmp	short loc_1C6D4
; ---------------------------------------------------------------------------

loc_1C6CF:
		push	si
		call	sub_17627
		inc	si

loc_1C6D4:
		cmp	si, 0Ah
		jl	short loc_1C6CF
		push	304B0h
		jmp	short loc_1C755
; ---------------------------------------------------------------------------

loc_1C6E1:
		call	sub_1FADD
		push	0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1C805
		jmp	short loc_1C76D
; ---------------------------------------------------------------------------

loc_1C6F5:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1C705
		cmp	ax, 1
		jz	short loc_1C73D
		jmp	short loc_1C741
; ---------------------------------------------------------------------------

loc_1C705:
		mov	ax, word_26346
		add	ax, 0FFE0h
		push	ax
		call	sub_16BD9
		or	al, al
		jz	short loc_1C741
		mov	word_26346, 0
		inc	byte_26349
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 24h ; '$'
		jnb	short loc_1C74F
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 1
		add	ax, ax
		mov	bx, ax
		mov	ax, off_2281E[bx]
		mov	fp_2CE42, ax
		jmp	short loc_1C741
; ---------------------------------------------------------------------------

loc_1C73D:
		call	fp_2CE42

loc_1C741:
		call	sub_1FADD
		or	al, al
		jz	loc_1C805
		push	0Ah
		call	sub_17416

loc_1C74F:
		push	10000h

loc_1C755:
		call	sub_1FB6E
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C75B:
		call	sub_1FADD
		push	0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1C805

loc_1C76D:
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_2D080, 80h
		mov	byte_2D081, 0FCh
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C784:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1C794
		cmp	ax, 1
		jz	short loc_1C7D3
		jmp	short loc_1C7D7
; ---------------------------------------------------------------------------

loc_1C794:
		mov	ax, word_26346
		add	ax, 0FFFCh
		push	ax
		call	sub_16BD9
		or	al, al
		jz	short loc_1C7D7
		mov	word_26346, 0
		inc	byte_26349
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 14h
		jb	short loc_1C7BE
		mov	byte ptr word_2634A+1, 0
		jmp	short loc_1C7E3
; ---------------------------------------------------------------------------

loc_1C7BE:
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 1
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22822[bx]
		mov	fp_2CE42, ax
		jmp	short loc_1C7D7
; ---------------------------------------------------------------------------

loc_1C7D3:
		call	fp_2CE42

loc_1C7D7:
		call	sub_1FADD
		or	al, al
		jz	short loc_1C805
		mov	byte ptr word_2634A+1, 1

loc_1C7E3:
		push	4
		call	sub_162CC
		mov	word_26346, 0
		mov	byte_26345, 0FDh
		call	sub_1B3C2
		mov	fp_2D06C, offset nullsub_2
		jmp	short loc_1C805
; ---------------------------------------------------------------------------

loc_1C7FE:
		push	46h ; 'F'
		call	sub_1FBBE
		jmp	short loc_1C812
; ---------------------------------------------------------------------------

loc_1C805:
		call	sub_1B446
		push	word_26342
		push	1E78h
		call	sub_17354

loc_1C812:
		pop	si
		pop	bp
		retf
sub_1C518	endp

; ---------------------------------------------------------------------------
		db 0
off_1C816	dw offset loc_1C54D
		dw offset loc_1C5B4
		dw offset loc_1C5D8
		dw offset loc_1C630
		dw offset loc_1C693
		dw offset loc_1C6B2
		dw offset loc_1C6E1
		dw offset loc_1C6F5
		dw offset loc_1C75B
		dw offset loc_1C784

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C82A	proc near

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		mov	al, byte_2BC88
		call	sub_15A42
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	byte_2C92C, 9
		mov	si, 0B2AAh
		mov	di, 1
		jmp	short loc_1C89A
; ---------------------------------------------------------------------------

loc_1C848:
		cmp	byte ptr [si], 0
		jnz	short loc_1C896
		mov	byte ptr [si], 1
		mov	eax, dword ptr word_2BC71+1
		mov	[si+2],	eax
		push	word_2BC71+1
		push	word_2BC74
		call	sub_ECD2
		lea	ax, [si+0Ah]
		push	ax
		push	word_2BC71
		push	[bp+var_2]
		call	sub_158E2
		mov	al, byte ptr word_2BC71
		mov	[si+1],	al
		push	0C1h
		push	word_2BC71
		call	sub_159E6
		mov	ah, 0
		mov	[si+12h], ax
		mov	al, byte ptr [bp+var_2]
		mov	[si+18h], al
		mov	ax, word_2BC7E
		mov	[si+0Eh], ax
		jmp	short loc_1C89F
; ---------------------------------------------------------------------------

loc_1C896:
		inc	di
		add	si, 1Ah

loc_1C89A:
		cmp	di, 40h
		jl	short loc_1C848

loc_1C89F:
		pop	di
		pop	si
		leave
		retn
sub_1C82A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C8A3	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 0B2AAh
		mov	di, 1
		jmp	loc_1C9B3
; ---------------------------------------------------------------------------

loc_1C8B1:
		cmp	byte ptr [si], 0
		jz	loc_1C9AF
		cmp	byte_2C979, 0
		jz	short loc_1C8CC
		cmp	byte ptr [si], 1
		jnz	short loc_1C8CC
		mov	byte ptr [si], 2
		mov	word ptr [si+0Eh], 0

loc_1C8CC:
		cmp	word ptr [si+0Eh], 0
		jbe	short loc_1C920
		dec	word ptr [si+0Eh]
		cmp	word ptr [si+0Eh], 0
		jnz	short loc_1C8F2
		push	0C1h
		push	word ptr [si+1]
		call	sub_159E6
		mov	ah, 0
		mov	[si+12h], ax
		call	snd_se_play pascal, 3
		jmp	short loc_1C920
; ---------------------------------------------------------------------------

loc_1C8F2:
		test	di, 1
		jz	short loc_1C90C
		add	word ptr [si+12h], 2
		cmp	word ptr [si+12h], 0E1h
		jl	loc_1C9AF
		sub	word ptr [si+12h], 20h ; ' '
		jmp	loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C90C:
		sub	word ptr [si+12h], 2
		cmp	word ptr [si+12h], 0C1h
		jge	loc_1C9AF
		add	word ptr [si+12h], 20h ; ' '
		jmp	loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C920:
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		cmp	ax, 0FF00h
		jle	short loc_1C93D
		cmp	ax, 1900h
		jge	short loc_1C93D
		cmp	dx, 0FF00h
		jle	short loc_1C93D
		cmp	dx, 1800h
		jl	short loc_1C93F

loc_1C93D:
		jmp	short loc_1C9AC
; ---------------------------------------------------------------------------

loc_1C93F:
		cmp	byte ptr [si], 2
		jz	short loc_1C969
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		add	ax, 70h	; 'p'
		cmp	ax, 0E0h
		ja	short loc_1C967
		add	dx, 70h	; 'p'
		cmp	dx, 0E0h
		ja	short loc_1C967
		mov	byte_2CEC1, 1
		mov	byte ptr [si], 2
		jmp	short loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C967:
		jmp	short loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C969:
		cmp	word ptr [si+12h], 0E1h
		jge	short loc_1C992
		mov	word ptr [si+12h], 0E1h
		mov	ax, [si+0Ah]
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	[si+0Ah], ax
		mov	ax, [si+0Ch]
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	[si+0Ch], ax
		mov	word ptr [si+14h], 0
		jmp	short loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C992:
		inc	word ptr [si+14h]
		mov	ax, [si+14h]
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C9AF
		inc	word ptr [si+12h]
		cmp	word ptr [si+12h], 0E5h
		jl	short loc_1C9AF

loc_1C9AC:
		mov	byte ptr [si], 0

loc_1C9AF:
		inc	di
		add	si, 1Ah

loc_1C9B3:
		cmp	di, 40h
		jl	loc_1C8B1
		pop	di
		pop	si
		pop	bp
		retn
sub_1C8A3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C9BE	proc near

var_1		= byte ptr -1
arg_0		= word ptr  4
arg_2		= word ptr  6

		enter	2, 0
		cmp	word_26346, 1
		jnz	short loc_1C9E7
		call	sub_157D6
		mov	[bp+var_1], al
		push	ds
		push	offset word_2633E
		push	ds
		push	offset word_26340
		push	word ptr [bp+var_1]
		push	[bp+arg_2]
		call	sub_14AC4
		mov	byte_26344, 0BCh

loc_1C9E7:
		mov	ax, word_2633E
		add	word_26335+1, ax
		mov	ax, word_26340
		add	word_26338, ax
		cmp	word_26335+1, 300h
		jle	short loc_1CA05
		cmp	word_26335+1, 1500h
		jl	short loc_1CA0F

loc_1CA05:
		mov	ax, 0FFFFh
		imul	word_2633E
		mov	word_2633E, ax

loc_1CA0F:
		cmp	word_26338, 300h
		jle	short loc_1CA1F
		cmp	word_26338, 800h
		jl	short loc_1CA29

loc_1CA1F:
		mov	ax, 0FFFFh
		imul	word_26340
		mov	word_26340, ax

loc_1CA29:
		mov	ax, word_26346
		cmp	ax, [bp+arg_0]
		jl	short loc_1CA3C
		mov	byte_26344, 0B4h
		mov	al, 1
		leave
		retn	4
; ---------------------------------------------------------------------------

loc_1CA3C:
		mov	al, 0
		leave
		retn	4
sub_1C9BE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CA42	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 10h
		jnz	short loc_1CA6B
		mov	byte_26344, 0B8h
		mov	word_2BC7E, 30h	; '0'
		mov	byte_2BC88, 50h	; 'P'
		mov	byte ptr word_2BC71, 70h ; 'p'
		push	1
		call	sub_157E4
		mov	byte_2D085, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1CA6B:
		cmp	word_26346, 20h	; ' '
		jle	short loc_1CAD5
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1CAD5
		cmp	byte_2D085, 0
		jz	short loc_1CA8F
		mov	al, 80h
		sub	al, byte ptr word_2BC71
		mov	byte ptr word_2BC71, al

loc_1CA8F:
		push	0B292h
		push	word_26335+1
		push	word_26338
		push	300h
		mov	al, byte ptr word_2BC71
		mov	ah, 0
		push	ax
		call	sub_14E6C
		call	sub_1C82A
		cmp	byte_2D085, 0
		jz	short loc_1CABB
		mov	al, 80h
		sub	al, byte ptr word_2BC71
		mov	byte ptr word_2BC71, al

loc_1CABB:
		mov	al, byte ptr word_2BC71
		add	al, 0FAh
		mov	byte ptr word_2BC71, al
		cmp	byte ptr word_2BC71, 0Ch
		ja	short loc_1CAD5
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1CAD5:
		pop	bp
		retn
sub_1CA42	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CAD7	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1CB23
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	short loc_1CB6F
		mov	byte_26344, 0B8h
		mov	byte ptr word_25FFA, 13h
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte_26000, 4
		mov	byte ptr word_26006+1, 3Ch ; '<'
		mov	byte ptr dword_26002, 10h
		call	fp_25344
		call	snd_se_play pascal, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1CB23:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1CB5D
		call	sub_157D6
		mov	byte ptr word_26006, al
		push	561Ch
		push	word_26335+1
		push	word_26338
		push	200h
		call	sub_157FA
		push	ax
		mov	al, byte ptr word_26006
		mov	ah, 0
		push	ax
		call	sub_14E6C
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1CB5D:
		cmp	word_26346, 50h	; 'P'
		jnz	short loc_1CB6F
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1CB6F:
		pop	bp
		retn
sub_1CAD7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CB71	proc near

var_1		= byte ptr -1

		enter	2, 0
		push	si
		cmp	word_26346, 20h	; ' '
		jge	short loc_1CBD2
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_1CCD0
		mov	byte_26344, 0B8h
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	byte_26000, 0
		mov	byte ptr word_26006+1, 60h
		call	fp_25344
		call	snd_se_play pascal, 8
		mov	word_2BC7E, 20h	; ' '
		mov	byte_2BC88, 4Ch	; 'L'
		mov	byte_2D083, 0
		mov	byte_2D082, 20h	; ' '
		jmp	loc_1CCD0
; ---------------------------------------------------------------------------

loc_1CBD2:
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		mov	si, dx
		mov	al, byte_2D082
		mov	ah, 0
		cmp	ax, si
		jle	short loc_1CC3E
		test	si, 1
		jnz	short loc_1CC3E
		sub	word ptr dword_25FFC, 200h
		sub	word ptr dword_25FFC+2,	100h
		or	si, si
		jnz	short loc_1CC1F
		push	word ptr dword_25FFC
		push	word ptr dword_25FFC+2
		push	0
		call	sub_15A24
		mov	byte_2D085, al
		mov	ax, word ptr dword_25FFC
		add	ax, 400h
		push	ax
		push	word ptr dword_25FFC+2
		push	0
		call	sub_15A24
		mov	byte_2D084, al

loc_1CC1F:
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A5C
		add	word ptr dword_25FFC, 400h
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1CC3E:
		mov	al, byte_2D076
		mov	ah, 0
		push	ax
		mov	ax, word_26346
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_1CC7F
		push	1Fh
		call	sub_157E4
		sub	al, 0Fh
		mov	[bp+var_1], al
		push	600h
		call	sub_157FA
		mov	word_2BC74, ax
		push	1600h
		call	sub_157FA
		add	ax, 100h
		mov	word_2BC71+1, ax
		push	ax
		push	word_2BC74
		push	word ptr [bp+var_1]
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_1C82A

loc_1CC7F:
		mov	ax, word_26342
		sub	ax, word_2634C
		cmp	ax, 258h
		jge	short loc_1CCD0
		cmp	byte_2D083, 0
		jnz	short loc_1CCD0
		mov	byte_2D083, 1
		push	100008h
		push	40004h
		call	sub_E758
		mov	byte_2D076, al
		push	280030h
		push	340034h
		call	sub_E758
		mov	byte_2D082, al
		push	0
		call	sub_162CC
		cmp	byte_2C979, 14h
		jnb	short loc_1CCD0
		mov	byte_2C979, 14h

loc_1CCD0:
		pop	si
		leave
		retn
sub_1CB71	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CCD3	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 10h
		jge	short loc_1CD26
		mov	ax, word_26346
		dec	ax
		push	ax
		push	70006h
		call	sub_16A6B
		cmp	word_26346, 4
		jnz	loc_1CE0B
		mov	byte_26344, 0B8h
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 2
		mov	byte_26001, 0Ah
		mov	byte ptr word_26006+1, 38h ; '8'
		mov	word ptr dword_26002, 205h
		call	snd_se_play pascal, 8
		mov	byte_2D085, 60h
		mov	byte_2D084, 40h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1CD26:
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1CDF8
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		push	561Ch
		push	word_26335+1
		push	word_26338
		push	300h
		mov	al, byte_2D085
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	al, byte_2D085
		add	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A70
		push	561Ch
		push	word_26335+1
		push	word_26338
		push	300h
		mov	al, byte_2D085
		add	al, 80h
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	al, byte ptr word_26006
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A70
		mov	byte ptr word_25FFA+1, 0
		mov	al, byte_2D085
		neg	al
		mov	byte_2D085, al
		push	561Ch
		push	word_26335+1
		push	word_26338
		push	200h
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	al, byte_2D085
		sub	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A70
		push	561Ch
		push	word_26335+1
		push	word_26338
		push	200h
		mov	al, byte_2D085
		add	al, 80h
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	al, byte ptr word_26006
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A70
		mov	al, byte_2D085
		neg	al
		mov	byte_2D085, al
		add	al, 0F8h
		mov	byte_2D085, al
		mov	al, byte_2D084
		add	al, 0FAh
		mov	byte_2D084, al
		call	snd_se_play pascal, 3

loc_1CDF8:
		cmp	word_26346, 100h
		jnz	short loc_1CE0B
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1CE0B:
		pop	bp
		retn
sub_1CCD3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CE0D	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 10h
		jge	short loc_1CE63
		mov	ax, word_26346
		dec	ax
		push	ax
		push	70006h
		call	sub_16A6B
		cmp	word_26346, 4
		jnz	loc_1CED7
		mov	byte_26344, 0B8h
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 3
		mov	byte ptr word_26006+1, 38h ; '8'
		mov	byte ptr dword_26002+1,	14h
		mov	byte ptr word_26006, 0
		mov	byte ptr word_25FFA+1, 44h ; 'D'
		call	fp_25344
		call	snd_se_play pascal, 8
		mov	byte_2D085, 80h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1CE63:
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1CEC4
		push	561Ch
		push	word_26335+1
		push	word_26338
		push	300h
		mov	al, byte_2D085
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	byte ptr dword_26002, 5
		call	sub_15A5C
		push	561Ch
		push	word_26335+1
		push	word_26338
		push	300h
		mov	al, 80h
		sub	al, byte_2D085
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	byte ptr dword_26002, 4
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 8
		mov	byte_2D085, al
		call	snd_se_play pascal, 3

loc_1CEC4:
		cmp	word_26346, 0C0h
		jnz	short loc_1CED7
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1CED7:
		pop	bp
		retn
sub_1CE0D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CED9	proc near

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		cmp	word_26346, 20h	; ' '
		jge	short loc_1CF57
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_1D081
		mov	byte_26344, 0B8h
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	byte_26000, 0
		mov	byte ptr word_26006+1, 60h
		call	fp_25344
		call	snd_se_play pascal, 8
		mov	word_26316, 18h
		mov	word_26314, 64h	; 'd'
		mov	byte_26313, 6
		mov	byte_26309, 8
		mov	word_26318, 1Ch
		mov	byte_2D083, 0
		mov	byte_2D082, 20h	; ' '
		mov	word_2BC7E, 20h	; ' '
		mov	byte_2BC88, 4Ch	; 'L'
		jmp	loc_1D081
; ---------------------------------------------------------------------------

loc_1CF57:
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		mov	di, dx
		mov	al, byte_2D082
		mov	ah, 0
		cmp	ax, di
		jle	short loc_1CFC3
		test	di, 1
		jnz	short loc_1CFC3
		sub	word ptr dword_25FFC, 200h
		sub	word ptr dword_25FFC+2,	100h
		or	di, di
		jnz	short loc_1CFA4
		push	word ptr dword_25FFC
		push	word ptr dword_25FFC+2
		push	0
		call	sub_15A24
		mov	byte_2D085, al
		mov	ax, word ptr dword_25FFC
		add	ax, 400h
		push	ax
		push	word ptr dword_25FFC+2
		push	0
		call	sub_15A24
		mov	byte_2D084, al

loc_1CFA4:
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A5C
		add	word ptr dword_25FFC, 400h
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1CFC3:
		mov	al, byte_2D077
		mov	ah, 0
		push	ax
		mov	ax, word_26346
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_1D030
		mov	word ptr dword_2630A+2,	200h
		push	1000h
		call	sub_157FA
		add	ax, 400h
		mov	word ptr dword_2630A, ax
		push	ax
		push	word ptr dword_2630A+2
		push	0
		call	sub_15A24
		mov	byte_26312, al
		call	sub_174C7
		xor	si, si
		jmp	short loc_1D02B
; ---------------------------------------------------------------------------

loc_1CFFA:
		push	1Fh
		call	sub_157E4
		sub	al, 0Fh
		mov	[bp+var_1], al
		push	600h
		call	sub_157FA
		mov	word_2BC74, ax
		push	1600h
		call	sub_157FA
		add	ax, 100h
		mov	word_2BC71+1, ax
		push	ax
		push	word_2BC74
		push	word ptr [bp+var_1]
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_1C82A
		inc	si

loc_1D02B:
		cmp	si, 2
		jl	short loc_1CFFA

loc_1D030:
		mov	ax, word_26342
		sub	ax, word_2634C
		cmp	ax, 1F4h
		jge	short loc_1D081
		cmp	byte_2D083, 0
		jnz	short loc_1D081
		mov	byte_2D083, 1
		push	22001Ch
		push	140014h
		call	sub_E758
		mov	byte_2D077, al
		push	280030h
		push	340030h
		call	sub_E758
		mov	byte_2D082, al
		push	0
		call	sub_162CC
		cmp	byte_2C979, 14h
		jnb	short loc_1D081
		mov	byte_2C979, 14h

loc_1D081:
		pop	di
		pop	si
		leave
		retn
sub_1CED9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D085	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	loc_1D117
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_1D1C4
		mov	byte_26344, 0B8h
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 34h ; '4'
		mov	byte_26000, 2
		mov	byte ptr dword_26002, 5
		push	180010h
		push	0C000Ah
		call	sub_E758
		mov	byte ptr dword_26002+1,	al
		mov	byte ptr word_26006+1, 80h
		call	snd_se_play pascal, 8
		mov	word_2BC7E, 20h	; ' '
		mov	byte_2BC88, 40h
		push	200h
		call	sub_157FA
		mov	word ptr dword_2634E+2,	ax
		push	28001Eh
		push	180010h
		call	sub_E758
		mov	byte_2D085, al
		mov	byte_2D084, 0

loc_1D110:
		mov	byte_2D083, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1D117:
		cmp	byte_2D083, 0
		jnz	short loc_1D17C
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1D1C4
		mov	al, byte_2D084
		mov	byte ptr word_2BC71, al
		cmp	byte_2D084, 0
		jnz	short loc_1D142
		mov	word_2BC71+1, 100h
		jmp	short loc_1D148
; ---------------------------------------------------------------------------

loc_1D142:
		mov	word_2BC71+1, 1700h

loc_1D148:
		mov	ax, word ptr dword_2634E+2
		mov	word_2BC74, ax
		call	sub_1C82A
		mov	al, byte_2D085
		mov	ah, 0
		shl	ax, 4
		add	word ptr dword_2634E+2,	ax
		mov	al, byte_2D084
		add	al, 80h
		mov	byte_2D084, al
		cmp	word ptr dword_2634E+2,	1780h
		jl	short loc_1D1C4
		push	200h
		call	sub_157FA
		mov	word ptr dword_2634E+2,	ax
		inc	byte_2D083
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1D17C:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1D1C4
		cmp	byte ptr word_26006+1, 60h
		jbe	short loc_1D1B9
		mov	byte ptr word_26006+1, 8
		call	snd_se_play pascal, 15
		inc	byte_2D083
		cmp	byte_2D083, 5
		ja	loc_1D110
		push	word ptr dword_25FFC
		push	word ptr dword_25FFC+2
		push	0
		call	sub_15A24
		mov	byte ptr word_26006, al

loc_1D1B9:
		mov	al, byte ptr word_26006+1
		add	al, 8
		mov	byte ptr word_26006+1, al
		call	sub_15A5C

loc_1D1C4:
		pop	bp
		retn
sub_1D085	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D1C6	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1D228
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_1D269
		mov	byte_26344, 0B8h
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	byte_26000, 4
		mov	byte ptr dword_26002, 12h
		mov	byte_26001, 2
		mov	byte ptr word_26006+1, 26h ; '&'
		call	fp_25344
		call	snd_se_play pascal, 8
		mov	byte_2D085, 0
		mov	byte_2C976, 2
		mov	byte_2D084, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1D228:
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1D269
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		test	byte_2D085, 1
		jz	short loc_1D252
		mov	byte_2C977, 40h
		mov	al, 80h
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		jmp	short loc_1D257
; ---------------------------------------------------------------------------

loc_1D252:
		mov	byte_2C977, 0C0h

loc_1D257:
		call	sub_15A9C
		inc	byte_2D084
		inc	byte_2D085
		call	snd_se_play pascal, 3

loc_1D269:
		pop	bp
		retn
sub_1D1C6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D26B	proc far
		push	bp
		mov	bp, sp
		push	si
		mov	eax, dword ptr word_26335+1
		mov	dword_2C922, eax
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		mov	dword ptr word_2BC71+1,	eax
		inc	word_26346
		mov	al, byte_26345
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 0Ah
		ja	loc_1D50C
		add	bx, bx
		jmp	cs:off_1D524[bx]

loc_1D29C:
		cmp	word_26346, 1
		jnz	short loc_1D2EF
		mov	word_26342, 206Ch
		mov	word_2634C, 1D4Ch
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0B4h
		mov	word_2633E, 40h
		mov	si, 0C1h
		jmp	short loc_1D2D7
; ---------------------------------------------------------------------------

loc_1D2D0:
		push	si
		call	super_convert_tiny
		inc	si

loc_1D2D7:
		cmp	si, 0E5h
		jl	short loc_1D2D0
		mov	word_2C96E, 0B4h
		mov	word_2C970, 0B4h
		mov	word_2C972, 0B4h

loc_1D2EF:
		cmp	word ptr dword_2634E+2,	0FE00h
		jl	short loc_1D320
		sub	word ptr dword_2634E+2,	10h
		mov	word_2CED6, 180h
		mov	word_2CED8, 180h
		mov	eax, dword_2634E
		mov	dword_2CED2, eax
		call	sub_126B3
		or	ax, ax
		jz	short loc_1D320
		call	snd_se_play pascal, 10

loc_1D320:
		cmp	word_26346, 40h
		jge	short loc_1D32D
		call	sub_1FB07
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D32D:
		mov	byte_26344, 0BCh
		add	word_26335+1, 20h ; ' '
		cmp	word_26335+1, 0C00h
		jl	loc_1D513
		mov	byte_26344, 0B4h
		inc	byte_26345
		mov	word_26346, 0
		call	snd_se_play pascal, 13
		mov	fp_23F5A, offset sub_D29E
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D360:
		call	sub_1FB07
		cmp	word_26346, 40h
		jl	loc_1D513
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	fp_2CE46, offset sub_1CA42
		mov	fp_2D06C, offset sub_10F90
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D38F:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1D39F
		cmp	ax, 1
		jz	short loc_1D3EF
		jmp	short loc_1D3F3
; ---------------------------------------------------------------------------

loc_1D39F:
		push	200040h
		call	sub_1C9BE
		or	al, al
		jz	short loc_1D3F3
		mov	word_26346, 0
		inc	byte_26349
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 14h
		jnb	short loc_1D40A
		cmp	byte_26345, 2
		jnz	short loc_1D3DA
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 1
		add	ax, ax
		mov	bx, ax
		mov	ax, off_2282A[bx]
		jmp	short loc_1D3EA
; ---------------------------------------------------------------------------

loc_1D3DA:
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 1
		add	ax, ax
		mov	bx, ax
		mov	ax, off_22832[bx]

loc_1D3EA:
		mov	fp_2CE46, ax
		jmp	short loc_1D3F3
; ---------------------------------------------------------------------------

loc_1D3EF:
		call	fp_2CE46

loc_1D3F3:
		cmp	byte_26349, 0
		jz	loc_1D513
		call	sub_1FADD
		or	al, al
		jz	loc_1D513
		push	0Ah
		call	sub_17416

loc_1D40A:
		cmp	byte_26345, 2
		jnz	short loc_1D41A
		pushd	1644h
		jmp	loc_1D4B7
; ---------------------------------------------------------------------------

loc_1D41A:
		push	30A8Ch
		jmp	loc_1D4B7
; ---------------------------------------------------------------------------

loc_1D423:
		call	sub_1FADD
		push	0C000400h
		call	sub_16CCC
		or	al, al
		jz	loc_1D513
		inc	byte_26345
		mov	word_26346, 0
		cmp	byte_26345, 4
		jnz	short loc_1D44F
		mov	fp_2CE46, offset sub_1CB71
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D44F:
		mov	fp_2CE46, offset sub_1CED9
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D458:
		call	fp_2CE46
		cmp	word_26346, 7D0h
		jge	short loc_1D472
		call	sub_1FADD
		or	al, al
		jz	loc_1D513
		push	0Ah
		call	sub_17416

loc_1D472:
		cmp	byte_26345, 4
		jnz	short loc_1D48A
		push	11194h
		call	sub_1FB6E
		mov	fp_2CE46, offset sub_1CCD3
		jmp	short loc_1D493
; ---------------------------------------------------------------------------

loc_1D48A:
		push	104B0h
		call	sub_1FB6E

loc_1D493:
		mov	byte_26349, 1
		jmp	short loc_1D513
; ---------------------------------------------------------------------------

loc_1D49A:
		call	sub_1D085
		cmp	word_26346, 7D0h
		jge	short loc_1D4B1
		call	sub_1FADD
		or	al, al
		jz	short loc_1D513
		push	0Ah
		call	sub_17416

loc_1D4B1:
		push	10000h

loc_1D4B7:
		call	sub_1FB6E
		jmp	short loc_1D513
; ---------------------------------------------------------------------------

loc_1D4BC:
		call	sub_1FADD
		push	0C000600h
		call	sub_16CCC
		or	al, al
		jz	short loc_1D513
		inc	byte_26345
		mov	word_26346, 0
		mov	byte ptr word_2634A+1, 0
		jmp	short loc_1D513
; ---------------------------------------------------------------------------

loc_1D4DD:
		call	sub_1D1C6
		cmp	word_26346, 4B0h
		jge	short loc_1D4F4
		call	sub_1FADD
		or	al, al
		jz	short loc_1D513
		mov	byte ptr word_2634A+1, 1

loc_1D4F4:
		push	4
		call	sub_162CC
		mov	word_26346, 0
		mov	byte_26345, 0FDh
		mov	fp_2D06C, offset nullsub_2
		jmp	short loc_1D513
; ---------------------------------------------------------------------------

loc_1D50C:
		push	41h ; 'A'
		call	sub_1FBBE
		jmp	short loc_1D520
; ---------------------------------------------------------------------------

loc_1D513:
		call	sub_1C8A3
		push	word_26342
		push	206Ch
		call	sub_17354

loc_1D520:
		pop	si
		pop	bp
		retf
sub_1D26B	endp

; ---------------------------------------------------------------------------
		db 0
off_1D524	dw offset loc_1D29C
		dw offset loc_1D360
		dw offset loc_1D38F
		dw offset loc_1D423
		dw offset loc_1D458
		dw offset loc_1D38F
		dw offset loc_1D423
		dw offset loc_1D458
		dw offset loc_1D49A
		dw offset loc_1D4BC
		dw offset loc_1D4DD

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D53A	proc near

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		mov	al, byte_2BC88
		call	sub_15A42
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	si, 0B2AAh
		mov	di, 1
		jmp	short loc_1D582
; ---------------------------------------------------------------------------

loc_1D553:
		cmp	byte ptr [si], 0
		jnz	short loc_1D57E
		mov	byte ptr [si], 1
		mov	eax, dword ptr word_2BC71+1
		mov	[si+2],	eax
		lea	ax, [si+0Ah]
		push	ax
		push	word_2BC71
		push	[bp+var_2]
		call	sub_158E2
		mov	ax, word_2BC82
		mov	[si+12h], ax
		mov	word ptr [si+10h], 300h
		jmp	short loc_1D587
; ---------------------------------------------------------------------------

loc_1D57E:
		inc	di
		add	si, 1Ah

loc_1D582:
		cmp	di, 40h
		jl	short loc_1D553

loc_1D587:
		pop	di
		pop	si
		leave
		retn
sub_1D53A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D58B	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 0B2AAh
		mov	di, 1
		jmp	loc_1D65C
; ---------------------------------------------------------------------------

loc_1D599:
		cmp	byte ptr [si], 0
		jz	loc_1D658
		cmp	byte ptr [si], 1
		jnz	short loc_1D5B4
		sub	word ptr [si+10h], 20h ; ' '
		cmp	word ptr [si+10h], 100h
		jge	loc_1D658
		inc	byte ptr [si]

loc_1D5B4:
		cmp	byte_2C979, 0
		jnz	short loc_1D5C2
		cmp	byte_2C978, 0
		jz	short loc_1D5C5

loc_1D5C2:
		mov	byte ptr [si], 3

loc_1D5C5:
		inc	word ptr [si+0Eh]
		lea	ax, [si+2]
		push	ax
		call	sub_152D2
		cmp	ax, 0FF00h
		jle	short loc_1D5E5
		cmp	ax, 1900h
		jge	short loc_1D5E5
		cmp	dx, 0FF00h
		jle	short loc_1D5E5
		cmp	dx, 1800h
		jl	short loc_1D5E7

loc_1D5E5:
		jmp	short loc_1D655
; ---------------------------------------------------------------------------

loc_1D5E7:
		cmp	byte ptr [si], 3
		jz	short loc_1D612
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		add	ax, 80h
		cmp	ax, 100h
		ja	short loc_1D610
		add	dx, 80h
		cmp	dx, 100h
		ja	short loc_1D610
		mov	byte_2CEC1, 1
		mov	byte ptr [si], 3
		jmp	short loc_1D658
; ---------------------------------------------------------------------------

loc_1D610:
		jmp	short loc_1D658
; ---------------------------------------------------------------------------

loc_1D612:
		cmp	word ptr [si+12h], 0CCh
		jge	short loc_1D63B
		mov	word ptr [si+12h], 0CCh
		mov	ax, [si+0Ah]
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	[si+0Ah], ax
		mov	ax, [si+0Ch]
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	[si+0Ch], ax
		mov	word ptr [si+14h], 0
		jmp	short loc_1D658
; ---------------------------------------------------------------------------

loc_1D63B:
		inc	word ptr [si+14h]
		mov	ax, [si+14h]
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1D658
		inc	word ptr [si+12h]
		cmp	word ptr [si+12h], 0D0h
		jl	short loc_1D658

loc_1D655:
		mov	byte ptr [si], 0

loc_1D658:
		inc	di
		add	si, 1Ah

loc_1D65C:
		cmp	di, 40h
		jl	loc_1D599
		pop	di
		pop	si
		pop	bp
		retn
sub_1D58B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D667	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1D6B2
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 2Dh ; '-'
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte_26000, 4
		mov	byte_26001, 0Ah
		call	sub_157D6
		mov	byte ptr word_26006, al
		mov	byte ptr dword_26002, 10h
		push	1
		call	sub_157E4
		or	ax, ax
		jz	short loc_1D6A2
		mov	al, 2
		jmp	short loc_1D6A4
; ---------------------------------------------------------------------------

loc_1D6A2:
		mov	al, 0FEh

loc_1D6A4:
		mov	byte_2D085, al
		call	fp_25344
		call	snd_se_play pascal, 15

loc_1D6B2:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1D6D1
		call	sub_15A70
		mov	al, byte ptr word_26006+1
		add	al, 8
		mov	byte ptr word_26006+1, al
		mov	al, byte_2D085
		add	byte ptr word_26006, al

loc_1D6D1:
		cmp	word_26346, 3Ch	; '<'
		jnz	short loc_1D6DD
		mov	ax, 1
		jmp	short loc_1D6DF
; ---------------------------------------------------------------------------

loc_1D6DD:
		xor	ax, ax

loc_1D6DF:
		pop	bp
		retn
sub_1D667	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D6E1	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1D719
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 4
		call	sub_157D6
		mov	byte ptr word_26006, al
		mov	byte ptr dword_26002, 10h
		push	10000Ch
		push	80004h
		call	sub_E758
		mov	byte_2D085, al

loc_1D719:
		mov	al, byte_2D085
		mov	ah, 0
		push	ax
		mov	ax, word_26346
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_1D766
		push	561Ch
		push	word_26335+1
		push	word_26338
		push	200h
		call	sub_157FA
		push	ax
		mov	al, byte ptr word_26006
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	byte ptr word_26006+1, 20h ; ' '
		call	sub_15A5C
		mov	byte ptr word_26006+1, 40h
		mov	al, byte ptr word_26006
		add	al, 8
		mov	byte ptr word_26006, al
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1D766:
		cmp	word_26346, 60h
		jnz	short loc_1D772
		mov	ax, 1
		jmp	short loc_1D774
; ---------------------------------------------------------------------------

loc_1D772:
		xor	ax, ax

loc_1D774:
		pop	bp
		retn
sub_1D6E1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D776	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1D7C2
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	70006h
		call	sub_16A6B
		cmp	word_26346, 2
		jnz	short loc_1D7DA
		mov	byte_26344, 0B5h
		mov	byte ptr word_25FFA, 13h
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte_26000, 4
		mov	byte ptr word_26006+1, 3Ch ; '<'
		mov	byte ptr dword_26002, 10h
		call	fp_25344
		call	snd_se_play pascal, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1D7C2:
		call	fp_2CE48
		or	al, al
		jz	short loc_1D7DA
		mov	byte_26344, 0B4h
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1D7DA:
		pop	bp
		retn
sub_1D776	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D7DC	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1D805
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_26006+1, 1Ch
		mov	byte_26000, 0Dh
		mov	byte ptr dword_26002, 3
		call	fp_25344
		call	snd_se_play pascal, 15

loc_1D805:
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1D82E
		mov	byte ptr word_25FFA+1, 34h ; '4'
		sub	word ptr dword_25FFC, 100h
		call	sub_15A5C
		mov	byte ptr word_25FFA+1, 74h ; 't'
		add	word ptr dword_25FFC, 200h
		call	sub_15A5C

loc_1D82E:
		mov	ax, word_26346
		add	ax, 0FFC0h
		push	ax
		call	sub_16BD9
		pop	bp
		retn
sub_1D7DC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D83A	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1D877
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 9
		mov	byte ptr word_26006, 0
		mov	word ptr dword_26002, 402h
		push	0C050C06h
		push	0D060D07h
		call	sub_E758
		mov	word ptr dword_26002+2,	ax
		mov	byte ptr word_26006+1, 20h ; ' '

loc_1D877:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1D88E
		call	sub_15A5C
		call	snd_se_play pascal, 15

loc_1D88E:
		mov	ax, word_26346
		add	ax, 0FFC0h
		push	ax
		call	sub_16BD9
		pop	bp
		retn
sub_1D83A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D89A	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 10h
		jnz	short loc_1D8F7
		mov	byte_26312, 50h	; 'P'
		push	0
		call	sub_175A4
		mov	byte_26312, 48h	; 'H'
		push	1
		call	sub_175A4
		mov	byte_26312, 40h
		push	2
		call	sub_175A4
		mov	byte_26312, 40h
		push	3
		call	sub_175A4
		mov	byte_26312, 38h	; '8'
		push	4
		call	sub_175A4
		mov	byte_26312, 30h	; '0'
		push	5
		call	sub_175A4
		call	snd_se_play pascal, 8
		mov	byte_26344, 0B5h
		mov	byte_2D085, 0
		mov	byte_2D084, 64h	; 'd'

loc_1D8F7:
		cmp	word_26346, 10h
		jle	loc_1DA17
		cmp	byte_26042, 80h
		jnb	short loc_1D954
		cmp	byte_25FE2, 0
		jz	loc_1DA17
		mov	al, byte_26012
		inc	al
		mov	byte_26012, al
		mov	al, byte_2602A
		inc	al
		mov	byte_2602A, al
		mov	al, byte_26042
		inc	al
		mov	byte_26042, al
		mov	al, byte_2605A
		add	al, 0FFh
		mov	byte_2605A, al
		mov	al, byte_26072
		add	al, 0FFh
		mov	byte_26072, al
		mov	al, byte_2608A
		add	al, 0FFh
		mov	byte_2608A, al
		mov	al, byte_2D084
		mov	ah, 0
		mov	PaletteTone, ax
		mov	byte_25FE9, 1
		inc	byte_2D084
		jmp	loc_1DA17
; ---------------------------------------------------------------------------

loc_1D954:
		cmp	byte_2D085, 0
		jnz	short loc_1D9D5
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 0
		call	fp_25344
		xor	si, si
		jmp	short loc_1D9AE
; ---------------------------------------------------------------------------

loc_1D972:
		push	1000h
		call	sub_157FA
		add	ax, word_26335+1
		sub	ax, 800h
		mov	word ptr dword_25FFC, ax
		push	400h
		call	sub_157FA
		mov	dx, word_26338
		sub	dx, ax
		add	dx, 100h
		mov	word ptr dword_25FFC+2,	dx
		push	60h
		call	sub_157FA
		add	al, 10h
		mov	byte ptr word_26006, al
		push	3Fh ; '?'
		call	sub_157E4
		add	al, 18h
		mov	byte ptr word_26006+1, al
		call	sub_15A5C
		inc	si

loc_1D9AE:
		cmp	si, 32h	; '2'
		jl	short loc_1D972
		mov	byte_26344, 0B8h
		xor	si, si
		jmp	short loc_1D9C1
; ---------------------------------------------------------------------------

loc_1D9BC:
		push	si
		call	sub_175FE
		inc	si

loc_1D9C1:
		cmp	si, 6
		jl	short loc_1D9BC
		call	snd_se_play pascal, 15
		mov	word_2CE06, 8
		jmp	short loc_1DA13
; ---------------------------------------------------------------------------

loc_1D9D5:
		cmp	byte_25FE2, 0
		jz	short loc_1D9E4
		mov	PaletteTone, 96h
		jmp	short loc_1D9EA
; ---------------------------------------------------------------------------

loc_1D9E4:
		mov	PaletteTone, 64h	; 'd'

loc_1D9EA:
		mov	byte_25FE9, 1
		cmp	byte_2D085, 8
		jb	short loc_1DA13
		mov	PaletteTone, 64h	; 'd'
		mov	byte_25FE9, 1
		xor	si, si
		jmp	short loc_1DA0A
; ---------------------------------------------------------------------------

loc_1DA05:
		push	si
		call	sub_17627
		inc	si

loc_1DA0A:
		cmp	si, 6
		jl	short loc_1DA05
		mov	al, 1
		jmp	short loc_1DA19
; ---------------------------------------------------------------------------

loc_1DA13:
		inc	byte_2D085

loc_1DA17:
		mov	al, 0

loc_1DA19:
		pop	si
		pop	bp
		retn
sub_1D89A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DA1C	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 80h
		jle	loc_1DAD0
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DA6A
		push	1800h
		call	sub_157FA
		mov	word_2BC71+1, ax
		push	400h
		call	sub_157FA
		add	ax, 200h
		mov	word_2BC74, ax
		mov	byte ptr word_2BC71, 40h
		push	1Fh
		call	sub_157E4
		add	al, 30h	; '0'
		mov	byte_2BC88, al
		mov	word_2BC82, 0C8h
		call	sub_1D53A
		call	snd_se_play pascal, 3

loc_1DA6A:
		mov	ax, word_26346
		mov	bx, 18h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DAD0
		push	1000h
		call	sub_157FA
		add	ax, word_26335+1
		sub	ax, 800h
		mov	word ptr dword_25FFC, ax
		push	400h
		call	sub_157FA
		mov	dx, word_26338
		sub	dx, ax
		mov	word ptr dword_25FFC+2,	dx
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 3
		mov	byte ptr dword_26002, 5
		push	10000Ch
		push	0A0008h
		call	sub_E758
		mov	byte ptr dword_26002+1,	al
		mov	byte ptr word_26006, 0
		mov	byte ptr word_26006+1, 30h ; '0'
		call	fp_25344
		call	sub_15A5C

loc_1DAD0:
		pop	bp
		retn
sub_1DA1C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DAD2	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 80h
		jl	loc_1DB78
		cmp	word_26346, 80h
		jnz	short loc_1DB10
		push	800030h
		push	200018h
		call	sub_E758
		mov	byte_2D084, al
		push	200028h
		push	300038h
		call	sub_E758
		mov	byte_2D085, al

loc_1DB10:
		mov	al, byte_2D084
		mov	ah, 0
		push	ax
		mov	ax, word_26346
		cwd
		pop	bx
		idiv	bx
		mov	si, dx
		test	si, 7
		jnz	short loc_1DB78
		mov	byte ptr word_25FFA+1, 2Dh ; '-'
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 2
		push	1Fh
		call	sub_157E4
		add	al, 30h	; '0'
		mov	byte ptr word_26006+1, al
		mov	word ptr dword_26002, 806h
		mov	byte ptr word_26006, 68h ; 'h'
		call	sub_15A5C
		mov	byte ptr word_26006, 18h
		call	sub_15A5C
		or	si, si
		jnz	short loc_1DB78
		mov	word_2BC82, 0Bh
		mov	byte_2BC88, 40h
		push	3
		call	sub_157FA
		shl	al, 6
		mov	byte ptr word_2BC71, al
		call	sub_17687
		call	snd_se_play pascal, 3

loc_1DB78:
		pop	si
		pop	bp
		retn
sub_1DAD2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DB7B	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 0A0h
		jge	short loc_1DB8C
		mov	al, 0
		jmp	loc_1DC2C
; ---------------------------------------------------------------------------

loc_1DB8C:
		cmp	word_26346, 0C0h
		jge	short loc_1DBB8
		cmp	word_26346, 80h
		jnz	short loc_1DBA3
		call	snd_se_play pascal, 8

loc_1DBA3:
		test	byte ptr word_26346, 1
		jz	short loc_1DBB1
		add	word_26338, 20h	; ' '
		jmp	short loc_1DC1D
; ---------------------------------------------------------------------------

loc_1DBB1:
		sub	word_26338, 20h	; ' '
		jmp	short loc_1DC1D
; ---------------------------------------------------------------------------

loc_1DBB8:
		cmp	word_26346, 0C0h
		jnz	short loc_1DC1D
		mov	word_2BC82, 0C9h
		xor	si, si
		jmp	short loc_1DC06
; ---------------------------------------------------------------------------

loc_1DBCA:
		push	1000h
		call	sub_157FA
		add	ax, word_26335+1
		sub	ax, 800h
		mov	word_2BC71+1, ax
		push	400h
		call	sub_157FA
		mov	dx, word_26338
		sub	dx, ax
		add	dx, 100h
		mov	word_2BC74, dx
		push	40h
		call	sub_157FA
		add	al, 20h	; ' '
		mov	byte ptr word_2BC71, al
		push	3Fh ; '?'
		call	sub_157E4
		add	al, 20h	; ' '
		mov	byte_2BC88, al
		call	sub_1D53A
		inc	si

loc_1DC06:
		cmp	si, 10h
		jl	short loc_1DBCA
		mov	byte_26344, 0C0h
		call	snd_se_play pascal, 15
		mov	word_2CE06, 8

loc_1DC1D:
		cmp	word_26346, 0C8h
		jnz	short loc_1DC2A
		mov	ax, 1
		jmp	short loc_1DC2C
; ---------------------------------------------------------------------------

loc_1DC2A:
		xor	ax, ax

loc_1DC2C:
		pop	si
		pop	bp
		retn
sub_1DB7B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DC2F	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 80h
		jle	loc_1DCFD
		cmp	word_26346, 81h
		jnz	short loc_1DC59
		push	600020h
		push	1C0018h
		call	sub_E758
		mov	byte_2D085, al

loc_1DC59:
		mov	ax, word_26346
		mov	bx, 80h
		cwd
		idiv	bx
		mov	si, dx
		mov	al, byte_2D085
		mov	ah, 0
		push	ax
		mov	ax, word_26346
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_1DC93
		push	word_2BC71+1
		push	word_2BC74
		push	0
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		mov	byte_2BC88, 40h
		mov	word_2BC82, 0C9h
		call	sub_1D53A

loc_1DC93:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DCFD
		sub	word ptr dword_25FFC, 800h
		mov	byte_26000, 2
		mov	byte_26001, 0Ah
		mov	word ptr dword_26002, 203h
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_26006+1, 28h ; '('
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		cmp	si, 40h
		jge	short loc_1DCD4
		mov	ax, si
		imul	ax, 3
		mov	byte ptr word_26006, al
		jmp	short loc_1DCE1
; ---------------------------------------------------------------------------

loc_1DCD4:
		mov	ax, si
		imul	ax, 3
		mov	dl, 40h
		sub	dl, al
		mov	byte ptr word_26006, dl

loc_1DCE1:
		call	sub_15A70
		mov	al, 80h
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		add	word ptr dword_25FFC, 1000h
		call	sub_15A70
		call	snd_se_play pascal, 15

loc_1DCFD:
		pop	si
		pop	bp
		retn
sub_1DC2F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DD00	proc near

var_2		= word ptr -2

		enter	2, 0
		cmp	word_26346, 0C0h
		jl	locret_1E020
		mov	ax, word_26346
		add	ax, 0FF40h
		mov	[bp+var_2], ax
		cmp	word_26342, 15E0h
		jle	short loc_1DD27
		cmp	word_26346, 708h
		jl	short loc_1DD72

loc_1DD27:
		cmp	word_22852, 0
		jnz	short loc_1DD72
		mov	byte_26313, 6
		mov	byte_26312, 40h
		mov	byte_26309, 0Eh
		add	word ptr dword_2630A, 600h
		push	0
		call	sub_175A4
		sub	word ptr dword_2630A, 400h
		push	1
		call	sub_175A4
		sub	word ptr dword_2630A, 400h
		push	2
		call	sub_175A4
		sub	word ptr dword_2630A, 400h
		push	3
		call	sub_175A4
		inc	word_22852
		push	0
		call	sub_162CC

loc_1DD72:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1DF48
		cmp	[bp+var_2], 0
		jnz	short loc_1DDC3
		mov	byte_2D084, 20h	; ' '
		mov	byte_2D085, 0
		push	400028h
		push	20001Ch
		call	sub_E758
		mov	byte_2D083, al
		mov	byte_2D082, 0
		mov	byte_2D081, 0
		mov	byte_2D080, 0
		mov	byte_2D07E, 40h
		mov	byte_2D07F, 40h
		mov	byte_2D07D, 0

loc_1DDC3:
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	byte_26000, 2
		cmp	byte_2D085, 40h
		jnz	short loc_1DDE4
		cmp	byte_2D082, 0
		jnz	short loc_1DDE4
		inc	byte_2D082

loc_1DDE4:
		cmp	byte_2D082, 0
		jnz	short loc_1DDF2
		mov	byte ptr dword_26002, 1
		jmp	short loc_1DDF7
; ---------------------------------------------------------------------------

loc_1DDF2:
		mov	byte ptr dword_26002, 3

loc_1DDF7:
		mov	byte ptr dword_26002+1,	30h ; '0'
		mov	byte ptr word_26006+1, 70h ; 'p'
		add	word ptr dword_25FFC, 600h
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A8E
		sub	word ptr dword_25FFC, 400h
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A8E
		sub	word ptr dword_25FFC, 400h
		mov	al, 80h
		sub	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A8E
		sub	word ptr dword_25FFC, 400h
		mov	al, 80h
		sub	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A8E
		cmp	byte_2D082, 0
		jnz	short loc_1DE5D
		mov	al, byte_2D085
		add	al, 4
		mov	byte_2D085, al
		mov	al, byte_2D084
		add	al, 2
		mov	byte_2D084, al
		jmp	loc_1DEEA
; ---------------------------------------------------------------------------

loc_1DE5D:
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr word_25FFA, 10h
		mov	word ptr dword_26002, 3003h
		mov	al, byte_2D085
		add	al, 80h
		mov	byte ptr word_26006, al
		add	word ptr dword_25FFC, 0C00h
		call	sub_15A8E
		sub	word ptr dword_25FFC, 400h
		mov	al, byte_2D084
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A8E
		sub	word ptr dword_25FFC, 400h
		mov	al, 0
		sub	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A8E
		sub	word ptr dword_25FFC, 400h
		mov	al, 0
		sub	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A8E
		cmp	byte_2D081, 0
		jnz	short loc_1DED3
		mov	al, byte_2D085
		add	al, 0FEh
		mov	byte_2D085, al
		dec	byte_2D084
		cmp	byte_2D085, 30h	; '0'
		jnz	short loc_1DEEA
		inc	byte_2D081
		jmp	short loc_1DEEA
; ---------------------------------------------------------------------------

loc_1DED3:
		mov	al, byte_2D085
		add	al, 2
		mov	byte_2D085, al
		inc	byte_2D084
		cmp	byte_2D085, 40h
		jnz	short loc_1DEEA
		dec	byte_2D081

loc_1DEEA:
		cmp	byte_2D082, 0
		jz	short loc_1DF41
		mov	al, byte_2D083
		mov	ah, 0
		push	ax
		mov	ax, word_26346
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_1DF41
		push	1000h
		call	sub_157FA
		add	ax, word_26335+1
		sub	ax, 800h
		mov	word_2BC71+1, ax
		push	400h
		call	sub_157FA
		mov	dx, word_26338
		sub	dx, ax
		add	dx, 100h
		mov	word_2BC74, dx
		push	word_2BC71+1
		push	dx
		push	0
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		mov	byte_2BC88, 3Ch	; '<'
		mov	word_2BC82, 0C9h
		call	sub_1D53A

loc_1DF41:
		call	snd_se_play pascal, 3

loc_1DF48:
		cmp	word_22852, 0
		jz	locret_1E020
		cmp	word_22852, 40h
		jl	short loc_1DF73
		cmp	word_22852, 40h
		jnz	short loc_1DF79
		push	0
		call	sub_175FE
		push	1
		call	sub_175FE
		push	2
		call	sub_175FE
		push	3
		call	sub_175FE

loc_1DF73:
		inc	word_22852
		leave
		retn
; ---------------------------------------------------------------------------

loc_1DF79:
		cmp	byte_2D080, 0
		jnz	short loc_1DF8F
		cmp	byte_2D085, 30h	; '0'
		jnz	locret_1E020
		inc	byte_2D080
		leave
		retn
; ---------------------------------------------------------------------------

loc_1DF8F:
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	locret_1E020
		mov	al, byte_2D07F
		mov	byte_26012, al
		mov	al, byte_2D07E
		mov	byte_2602A, al
		mov	al, 80h
		sub	al, byte_2602A
		mov	byte_26042, al
		mov	al, 80h
		sub	al, byte_26012
		mov	byte_2605A, al
		cmp	byte_2D07D, 0
		jnz	short loc_1DFD8
		inc	byte_2D07F
		dec	byte_2D07E
		cmp	byte_2D07E, 38h	; '8'
		jnz	short loc_1DFEB
		inc	byte_2D07D
		jmp	short loc_1DFEB
; ---------------------------------------------------------------------------

loc_1DFD8:
		dec	byte_2D07F
		inc	byte_2D07E
		cmp	byte_2D07E, 41h	; 'A'
		jnz	short loc_1DFEB
		dec	byte_2D07D

loc_1DFEB:
		cmp	word_26342, 0ED8h
		jle	short loc_1DFFB
		cmp	word_26346, 9C4h
		jl	short locret_1E020

loc_1DFFB:
		mov	ax, word_22852
		inc	word_22852
		cmp	ax, 41h	; 'A'
		jnz	short locret_1E020
		push	340014h
		push	10000Ch
		call	sub_E758
		mov	byte_2D083, al
		push	0
		call	sub_162CC

locret_1E020:
		leave
		retn
sub_1DD00	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E022	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 80h
		jl	loc_1E15A
		cmp	word_26346, 80h
		jnz	short loc_1E047
		mov	byte ptr word_2BC71, 0
		mov	byte_2D085, 0
		mov	byte_2D084, 0

loc_1E047:
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E0A6
		mov	word_2BC82, 0C8h
		push	0B292h
		push	word_26335+1
		push	word_26338
		push	400h
		mov	al, byte ptr word_2BC71
		mov	ah, 0
		push	ax
		call	sub_14E6C
		call	sub_1D53A
		mov	al, byte ptr word_2BC71
		add	al, 80h
		mov	byte ptr word_2BC71, al
		push	0B292h
		push	word_26335+1
		push	word_26338
		push	400h
		mov	ah, 0
		push	ax
		call	sub_14E6C
		call	sub_1D53A
		mov	al, byte ptr word_2BC71
		add	al, 88h
		mov	byte ptr word_2BC71, al
		call	snd_se_play pascal, 3

loc_1E0A6:
		cmp	word_26346, 100h
		jl	loc_1E13D
		mov	ax, word_26346
		mov	bx, 100h
		cwd
		idiv	bx
		mov	si, dx
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E0F8
		cmp	si, 80h
		jge	short loc_1E0F8
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 4
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte ptr dword_26002, 0Ch
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 0FEh
		mov	byte_2D085, al

loc_1E0F8:
		cmp	word_26346, 200h
		jl	short loc_1E13D
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E13D
		cmp	si, 80h
		jl	short loc_1E13D
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 4
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte ptr dword_26002, 0Ch
		call	sub_15A5C
		mov	al, byte_2D084
		add	al, 4
		mov	byte_2D084, al

loc_1E13D:
		cmp	word_26346, 2D0h
		jl	short loc_1E15A
		mov	ax, word_26346
		add	ax, 0FD30h
		mov	bx, 80h
		cwd
		idiv	bx
		mov	si, dx
		lea	ax, [si-60h]
		push	ax
		call	sub_16BD9

loc_1E15A:
		pop	si
		pop	bp
		retn
sub_1E022	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E15D	proc near
		push	bp
		mov	bp, sp
		cmp	byte_25FE3, 0
		jnz	short loc_1E195
		cmp	byte_22854, 0
		jnz	short loc_1E17F
		inc	word_26340
		cmp	word_26340, 10h
		jl	short loc_1E18E
		inc	byte_22854
		jmp	short loc_1E18E
; ---------------------------------------------------------------------------

loc_1E17F:
		dec	word_26340
		cmp	word_26340, 0FFF0h
		jg	short loc_1E18E
		dec	byte_22854

loc_1E18E:
		mov	ax, word_26340
		add	word_26338, ax

loc_1E195:
		pop	bp
		retn
sub_1E15D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E197	proc far
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	eax, dword ptr word_26335+1
		mov	dword_2C922, eax
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		mov	dword_2630A, eax
		mov	dword ptr word_2BC71+1,	eax
		inc	word_26346
		mov	al, byte_26345
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 0Ch
		ja	loc_1E522
		add	bx, bx
		jmp	cs:off_1E53C[bx]

loc_1E1CD:
		cmp	word_26346, 1
		jnz	short loc_1E220
		mov	word_26342, 5910h
		mov	word_2634C, 5078h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0B4h
		mov	word_26340, 0
		mov	word_2C96E, 0B7h
		mov	word_2C970, 0B6h
		mov	word_2C972, 0B4h
		mov	si, 0C8h
		jmp	short loc_1E21A
; ---------------------------------------------------------------------------

loc_1E213:
		push	si
		call	super_convert_tiny
		inc	si

loc_1E21A:
		cmp	si, 0D0h
		jl	short loc_1E213

loc_1E220:
		call	sub_1FB07
		cmp	word_26346, 0C0h
		jl	loc_1E527
		mov	word_26346, 0
		inc	byte_26345
		call	snd_se_play pascal, 13
		mov	fp_23F5A, offset sub_DA86
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E247:
		call	sub_1FB07
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1E265
		mov	Palettes, 0
		mov	Palettes+1, 0
		mov	Palettes+2, 0
		mov	byte_25FE9, 1

loc_1E265:
		cmp	word_26346, 40h
		jl	loc_1E527
		inc	byte_26345
		mov	byte_26349, 1
		mov	word_26346, 0
		mov	fp_2CE48, offset sub_1D667
		jmp	loc_1E36F
; ---------------------------------------------------------------------------

loc_1E286:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1E296
		cmp	ax, 1
		jz	short loc_1E2D9
		jmp	short loc_1E2DC
; ---------------------------------------------------------------------------

loc_1E296:
		mov	ax, word_26346
		add	ax, 0FFE0h
		push	ax
		call	sub_16BD9
		or	al, al
		jz	short loc_1E2DC
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		inc	byte_26349
		mov	al, byte_2D080
		mov	ah, 0
		shl	ax, 2
		mov	dl, byte ptr word_2634A+1
		mov	dh, 0
		and	dx, 1
		add	dx, dx
		add	ax, dx
		mov	bx, ax
		mov	ax, off_2284A[bx]
		mov	fp_2CE48, ax
		cmp	byte ptr word_2634A+1, 10h
		jb	short loc_1E2DC
		jmp	short loc_1E2EA
; ---------------------------------------------------------------------------

loc_1E2D9:
		call	sub_1D776

loc_1E2DC:
		call	sub_1FADD
		or	al, al
		jz	loc_1E527
		push	0Ah
		call	sub_17416

loc_1E2EA:
		cmp	byte_2D080, 0
		jnz	short loc_1E308
		push	147E0h
		call	sub_1FB6E
		mov	byte_26349, 1
		mov	fp_2CE48, offset sub_1D7DC
		jmp	loc_1E481
; ---------------------------------------------------------------------------

loc_1E308:
		push	13908h
		call	sub_1FB6E
		jmp	loc_1E481
; ---------------------------------------------------------------------------

loc_1E314:
		call	sub_1FADD
		push	0C000500h
		call	sub_16CCC
		or	al, al
		jz	loc_1E527
		inc	byte_26345
		mov	word_26346, 0
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E333:
		call	sub_1FADD
		call	sub_1D89A
		or	al, al
		jz	loc_1E527
		inc	byte_26345
		mov	word_26346, 0
		mov	word_26340, 0
		mov	fp_2D06C, offset sub_11073
		push	3200230h
		push	2D00320h
		call	sub_E752
		mov	word_2D088, ax
		mov	fp_2CE4A, offset sub_1DA1C

loc_1E36F:
		mov	byte_2D080, 0
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E377:
		cmp	Palettes+2, 80h
		jnb	short loc_1E38E
		cmp	byte_25FE5, 0
		jnz	short loc_1E389
		inc	Palettes+2

loc_1E389:
		mov	byte_25FE9, 1

loc_1E38E:
		call	sub_1E15D
		call	fp_2CE4A
		cmp	word_26346, 0BB8h
		jge	short loc_1E3AB
		call	sub_1FADD
		or	al, al
		jz	loc_1E527
		push	19h
		call	sub_17416

loc_1E3AB:
		cmp	byte_2D080, 0
		jnz	short loc_1E3C4
		push	22D50h
		call	sub_1FB6E
		mov	fp_2CE4A, offset sub_1DAD2
		jmp	loc_1E47B
; ---------------------------------------------------------------------------

loc_1E3C4:
		push	32198h
		call	sub_1FB6E
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E3D0:
		cmp	Palettes+2, 0
		jbe	short loc_1E3E7
		cmp	byte_25FE4, 0
		jnz	short loc_1E3E2
		dec	Palettes+2

loc_1E3E2:
		mov	byte_25FE9, 1

loc_1E3E7:
		call	sub_1FADD
		call	sub_1DB7B
		or	al, al
		jz	loc_1E527
		inc	byte_26345
		mov	word_26346, 0
		mov	fp_2CE4A, offset sub_1DC2F
		jmp	loc_1E36F
; ---------------------------------------------------------------------------

loc_1E406:
		cmp	Palettes+2, 0
		jbe	short loc_1E41A
		cmp	byte_25FE4, 0
		jnz	short loc_1E42C
		dec	Palettes+2
		jmp	short loc_1E42C
; ---------------------------------------------------------------------------

loc_1E41A:
		cmp	Palettes, 80h
		jnb	short loc_1E431
		cmp	byte_25FE5, 0
		jnz	short loc_1E42C
		inc	Palettes

loc_1E42C:
		mov	byte_25FE9, 1

loc_1E431:
		call	sub_1E15D
		call	fp_2CE4A
		cmp	word_26346, 0BB8h
		jge	short loc_1E465
		call	sub_1FADD
		mov	ah, 0
		mov	di, ax
		cmp	byte_2429A, 0
		jz	short loc_1E45A
		mov	al, byte_26348
		mov	ah, 0
		dec	ax
		add	word_26342, ax
		xor	di, di

loc_1E45A:
		or	di, di
		jz	loc_1E527
		push	19h
		call	sub_17416

loc_1E465:
		cmp	byte_2D080, 0
		jnz	short loc_1E488
		push	20AF0h
		call	sub_1FB6E
		mov	fp_2CE4A, offset sub_1DD00

loc_1E47B:
		mov	word_26346, 0

loc_1E481:
		inc	byte_2D080
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E488:
		push	30000h
		call	sub_1FB6E
		mov	word_2CE06, 10h
		push	0
		call	sub_17627
		push	1
		call	sub_17627
		push	2
		call	sub_17627
		push	3
		call	sub_17627
		jmp	short loc_1E527
; ---------------------------------------------------------------------------

loc_1E4AD:
		call	sub_1FADD
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E4C5
		mov	PaletteTone, 96h
		jmp	short loc_1E4CB
; ---------------------------------------------------------------------------

loc_1E4C5:
		mov	PaletteTone, 64h	; 'd'

loc_1E4CB:
		mov	byte_25FE9, 1
		cmp	word_26346, 10h
		jle	short loc_1E527
		inc	byte_26345
		mov	byte_26344, 0B4h
		mov	word_2D088, 180h
		mov	Palettes, 60h
		mov	Palettes+2, 0
		call	snd_se_play pascal, 13
		jmp	short loc_1E527
; ---------------------------------------------------------------------------

loc_1E4F9:
		call	sub_1E022
		cmp	word_26346, 0BB8h
		jge	short loc_1E510
		call	sub_1FADD
		or	al, al
		jz	short loc_1E527
		mov	byte ptr word_2634A+1, 1

loc_1E510:
		push	4
		call	sub_162CC
		mov	word_26346, 0
		mov	byte_26345, 0FDh
		jmp	short loc_1E527
; ---------------------------------------------------------------------------

loc_1E522:
		push	41h ; 'A'
		call	sub_1FBBE

loc_1E527:
		call	sub_1D58B
		call	sub_17726
		push	word_26342
		push	5910h
		call	sub_17354
		pop	di
		pop	si
		pop	bp
		retf
sub_1E197	endp

; ---------------------------------------------------------------------------
		db 0
off_1E53C	dw offset loc_1E1CD
		dw offset loc_1E247
		dw offset loc_1E286
		dw offset loc_1E286
		dw offset loc_1E314
		dw offset loc_1E333
		dw offset loc_1E377
		dw offset loc_1E377
		dw offset loc_1E3D0
		dw offset loc_1E406
		dw offset loc_1E406
		dw offset loc_1E4AD
		dw offset loc_1E4F9

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E556	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	si, 0FFF8h
		jl	loc_1E5F5
		or	si, si
		jge	short loc_1E570
		mov	byte_26330, 0DDh
		jmp	loc_1E5F5
; ---------------------------------------------------------------------------

loc_1E570:
		cmp	si, 1Eh
		jge	short loc_1E5C6
		or	si, si
		jnz	short loc_1E580
		call	snd_se_play pascal, 8

loc_1E580:
		mov	ax, 2
		imul	si
		mov	si, ax
		push	5948h
		push	word_26335
		mov	ax, 40h
		sub	ax, si
		push	ax
		call	sub_158E2
		push	5940h
		call	sub_152D2
		cmp	si, 10h
		jge	short loc_1E5A7
		mov	ax, 1
		jmp	short loc_1E5A9
; ---------------------------------------------------------------------------

loc_1E5A7:
		xor	ax, ax

loc_1E5A9:
		push	ax
		cmp	si, 30h	; '0'
		jle	short loc_1E5B4
		mov	ax, 1
		jmp	short loc_1E5B6
; ---------------------------------------------------------------------------

loc_1E5B4:
		xor	ax, ax

loc_1E5B6:
		pop	dx
		or	dx, ax
		jz	short loc_1E5BF
		mov	al, 0DEh
		jmp	short loc_1E5C1
; ---------------------------------------------------------------------------

loc_1E5BF:
		mov	al, 0DFh

loc_1E5C1:
		mov	byte_26330, al
		jmp	short loc_1E5F5
; ---------------------------------------------------------------------------

loc_1E5C6:
		cmp	si, 28h	; '('
		jge	short loc_1E5EA
		cmp	si, 1Eh
		jnz	short loc_1E5D7
		call	snd_se_play pascal, 15

loc_1E5D7:
		mov	eax, dword_26320
		mov	dword_26324, eax
		mov	byte_26330, 0DDh
		call	off_2285A
		jmp	short loc_1E5F5
; ---------------------------------------------------------------------------

loc_1E5EA:
		mov	byte_26330, 0DCh
		call	off_2285A
		jmp	short loc_1E5F7
; ---------------------------------------------------------------------------

loc_1E5F5:
		mov	al, 0

loc_1E5F7:
		pop	si
		pop	bp
		retn	2
sub_1E556	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E5FC	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 70h	; 'p'
		jl	short loc_1E60A
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E60A:
		mov	al, 0
		pop	bp
		retn
sub_1E5FC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E60E	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 5Eh	; '^'
		jnz	short loc_1E62A
		push	1
		call	sub_157E4
		or	ax, ax
		jz	short loc_1E625
		mov	al, 1
		jmp	short loc_1E627
; ---------------------------------------------------------------------------

loc_1E625:
		mov	al, 0FFh

loc_1E627:
		mov	byte_2D083, al

loc_1E62A:
		cmp	word_26332, 72h	; 'r'
		jg	short loc_1E65F
		mov	byte ptr word_25FFA, 10h
		mov	byte_2C976, 2
		mov	byte_26001, 3
		mov	word ptr dword_26002, 1012h
		mov	byte_26000, 4
		mov	byte ptr word_26006+1, 8
		mov	byte ptr word_25FFA+1, 2Fh ; '/'
		mov	al, byte_2D083
		add	byte ptr word_26006, al
		call	sub_15A70

loc_1E65F:
		cmp	word_26332, 80h
		jl	short loc_1E66B
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E66B:
		mov	al, 0
		pop	bp
		retn
sub_1E60E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E66F	proc near
		push	bp
		mov	bp, sp
		cmp	byte_25352, 0
		jz	short loc_1E696
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 0Dh
		mov	byte ptr word_26006+1, 10h
		mov	word ptr dword_26002, 0A0Ch
		mov	byte ptr word_25FFA+1, 0
		call	sub_15A5C

loc_1E696:
		cmp	word_26332, 80h
		jl	short loc_1E6A2
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E6A2:
		mov	al, 0
		pop	bp
		retn
sub_1E66F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E6A6	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26332
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E6FE
		mov	byte ptr word_25FFA, 13h
		mov	byte_2C976, 1
		mov	byte_26001, 2
		mov	byte_26000, 8
		mov	dword_26002, 10040805h
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_25FFA+1, 2Fh ; '/'
		mov	byte ptr word_26006, 80h
		mov	byte_2C977, 0C8h
		call	sub_15A70
		mov	byte ptr word_26006, 0
		mov	byte_2C977, 38h	; '8'
		call	sub_15A70
		call	snd_se_play pascal, 3

loc_1E6FE:
		cmp	word_26332, 80h
		jl	short loc_1E70A
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E70A:
		mov	al, 0
		pop	bp
		retn
sub_1E6A6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E70E	proc far
		push	bp
		mov	bp, sp
		mov	eax, dword_26320
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		inc	word_26332
		mov	al, byte_26331
		mov	ah, 0
		or	ax, ax
		jz	short loc_1E732
		cmp	ax, 1
		jz	short loc_1E776
		jmp	loc_1E855
; ---------------------------------------------------------------------------

loc_1E732:
		push	1800180h
		push	0Ah
		call	sub_1FA9D
		mov	byte ptr word_26335, 40h
		push	word_26332
		call	sub_1E556
		or	al, al
		jz	loc_1E864
		inc	byte_26331
		mov	word_26332, 0
		mov	byte ptr word_26335, 0
		mov	byte_2D085, 0
		mov	byte_2D084, 0
		mov	byte_2D082, 0
		mov	off_2285A, 938Eh
		jmp	loc_1E864
; ---------------------------------------------------------------------------

loc_1E776:
		mov	ax, word_26332
		add	ax, 0FFC0h
		push	ax
		call	sub_1E556
		or	al, al
		jz	short loc_1E7F2
		cmp	byte_2D082, 0
		jnz	short loc_1E7AF
		cmp	word_2632E, 3E8h
		jge	short loc_1E7AF
		push	0Ah
		call	sub_173AC
		cmp	byte_2C979, 14h
		jnb	short loc_1E7A4
		mov	byte_2C979, 14h

loc_1E7A4:
		call	snd_se_play pascal, 15
		inc	byte_2D082

loc_1E7AF:
		mov	byte_2D085, 1
		mov	word_26332, 0
		mov	al, byte_2D084
		mov	ah, 0
		and	ax, 7
		mov	bx, ax
		mov	al, byte_22868[bx]
		mov	byte ptr word_26335, al
		inc	byte_2D084
		mov	al, byte_2D082
		mov	ah, 0
		shl	ax, 2
		mov	dl, byte_2D084
		mov	dh, 0
		mov	bx, 2
		push	ax
		mov	ax, dx
		cwd
		idiv	bx
		add	dx, dx
		pop	bx
		add	bx, dx
		mov	ax, off_2285C[bx]
		mov	off_2285A, ax

loc_1E7F2:
		push	1800180h
		push	4
		call	sub_1FA9D
		mov	byte_26334, al
		mov	ah, 0
		sub	word_2632E, ax
		cmp	byte_2D084, 14h
		jnb	short loc_1E82B
		cmp	word_2632E, 0
		jg	short loc_1E864
		mov	byte_2C978, 1
		push	1Eh
		call	sub_173AC
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	5
		call	sub_16D84

loc_1E82B:
		mov	byte_26331, 0FEh
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	800030h
		call	sub_1597C
		call	snd_se_play pascal, 12
		jmp	short loc_1E864
; ---------------------------------------------------------------------------

loc_1E855:
		call	sub_17486
		push	word_2632E
		push	0BB8h
		call	sub_17354
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_1E864:
		push	word_2632E
		push	0BB8h
		call	sub_17354
		mov	ax, word ptr dword_26320
		mov	word ptr dword_2C922, ax
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_2C922+2,	ax
		pop	bp
		retf
sub_1E70E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E87C	proc near

arg_0		= byte ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, 0C478h
		xor	dx, dx
		jmp	short loc_1E8A6
; ---------------------------------------------------------------------------

loc_1E887:
		cmp	byte ptr [si], 0
		jnz	short loc_1E8A2
		mov	byte ptr [si], 1
		mov	al, [bp+arg_0]
		mov	[si+1],	al
		mov	word ptr [si+2], 10h
		mov	ax, [bp+arg_2]
		mov	[si+4],	ax
		jmp	short loc_1E8AB
; ---------------------------------------------------------------------------

loc_1E8A2:
		inc	dx
		add	si, 6

loc_1E8A6:
		cmp	dx, 2
		jl	short loc_1E887

loc_1E8AB:
		pop	si
		pop	bp
		retn	4
sub_1E87C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E8B0	proc near
		push	bp
		mov	bp, sp
		push	si
		mov	si, 0C478h
		xor	ax, ax
		jmp	short loc_1E8D2
; ---------------------------------------------------------------------------

loc_1E8BB:
		cmp	byte ptr [si], 0
		jz	short loc_1E8CE
		add	word ptr [si+2], 4
		cmp	word ptr [si+2], 260h
		jl	short loc_1E8CE
		mov	byte ptr [si], 0

loc_1E8CE:
		inc	ax
		add	si, 6

loc_1E8D2:
		cmp	ax, 2
		jl	short loc_1E8BB
		pop	si
		pop	bp
		retn
sub_1E8B0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E8DA	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		add	ax, 0FFD0h
		push	ax
		push	60007h
		call	sub_16A6B
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1E900
		mov	byte_26344, 0B5h
		call	snd_se_play pascal, 8

loc_1E900:
		cmp	word_26346, 40h
		jl	short loc_1E91E
		call	fp_2CE66
		or	al, al
		jz	short loc_1E91E
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E91E:
		mov	al, 0
		pop	bp
		retn
sub_1E8DA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E922	proc near
		push	bp
		mov	bp, sp
		mov	byte ptr word_25FFA, 10h
		push	1Fh
		call	sub_157E4
		add	al, 28h	; '('
		mov	byte ptr word_26006+1, al
		push	7Fh
		call	sub_157E4
		and	al, 0F8h
		sub	al, 40h
		mov	byte ptr word_26006, al
		mov	byte_26000, 3
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	word ptr dword_26002, 0C05h
		call	sub_15A5C
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E967
		call	snd_se_play pascal, 3

loc_1E967:
		cmp	word_26346, 80h
		jnz	short loc_1E974
		mov	ax, 1
		jmp	short loc_1E976
; ---------------------------------------------------------------------------

loc_1E974:
		xor	ax, ax

loc_1E976:
		pop	bp
		retn
sub_1E922	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E978	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jnz	short loc_1E98B
		mov	al, 1
		sub	al, byte_2D085
		mov	byte_2D085, al

loc_1E98B:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E9F9
		mov	byte ptr word_25FFA, 13h
		mov	byte ptr word_26006+1, 40h
		cmp	byte_2D085, 0
		jz	short loc_1E9B0
		mov	al, byte ptr word_26006
		add	al, 2
		jmp	short loc_1E9B5
; ---------------------------------------------------------------------------

loc_1E9B0:
		mov	al, byte ptr word_26006
		add	al, 0FEh

loc_1E9B5:
		mov	byte ptr word_26006, al
		mov	byte_26000, 4
		mov	byte_26001, 1
		mov	byte_2C976, 1
		mov	word ptr dword_26002, 0A0Ch
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E9E4
		call	sub_15A5C
		jmp	short loc_1E9F2
; ---------------------------------------------------------------------------

loc_1E9E4:
		mov	word ptr dword_26002, 0A08h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		call	sub_15A70

loc_1E9F2:
		call	snd_se_play pascal, 3

loc_1E9F9:
		mov	ax, word_26346
		add	ax, 0FF9Ch
		push	ax
		call	sub_16BD9
		cmp	word_26346, 80h
		jnz	short loc_1EA10
		mov	ax, 1
		jmp	short loc_1EA12
; ---------------------------------------------------------------------------

loc_1EA10:
		xor	ax, ax

loc_1EA12:
		pop	bp
		retn
sub_1E978	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EA14	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jnz	short loc_1EA2E
		mov	byte_2D084, 40h
		mov	byte_2D083, 0
		mov	word_2CC8E, 7

loc_1EA2E:
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1EB0C
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1EAE3
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 0
		mov	byte_26000, 3
		mov	word ptr dword_26002, 605h
		mov	byte ptr word_26006+1, 50h ; 'P'
		mov	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		neg	al
		mov	byte ptr word_26006, al
		call	sub_15A5C
		cmp	byte_2D083, 0
		jnz	short loc_1EA96
		mov	al, byte_2D084
		add	al, 0FDh
		mov	byte_2D084, al
		cmp	byte_2D084, 14h
		ja	short loc_1EAA9
		inc	byte_2D083
		jmp	short loc_1EAA9
; ---------------------------------------------------------------------------

loc_1EA96:
		mov	al, byte_2D084
		add	al, 3
		mov	byte_2D084, al
		cmp	byte_2D084, 40h
		jb	short loc_1EAA9
		dec	byte_2D083

loc_1EAA9:
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EAE3
		push	600h
		call	sub_157FA
		add	ax, word ptr dword_25FFC
		sub	ax, 300h
		mov	word_2CE52, ax
		push	400h
		call	sub_157FA
		add	ax, word ptr dword_25FFC+2
		sub	ax, 200h
		mov	word_2CE54, ax
		push	word_2CE52
		push	ax
		push	0
		call	sub_15A24
		mov	byte_2D085, al

loc_1EAE3:
		mov	ax, word_2CE52
		mov	word ptr dword_25FFC, ax
		mov	ax, word_2CE54
		mov	word ptr dword_25FFC+2,	ax
		mov	byte ptr word_25FFA, 12h
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	byte_26000, 0
		mov	byte ptr word_26006+1, 60h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		call	sub_15A5C

loc_1EB0C:
		mov	ax, word_26346
		mov	bx, 80h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EB39
		push	bx
		mov	ax, word_26346
		mov	bx, 100h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EB2C
		mov	ax, 1
		jmp	short loc_1EB2E
; ---------------------------------------------------------------------------

loc_1EB2C:
		xor	ax, ax

loc_1EB2E:
		push	ax
		call	sub_1E87C
		call	snd_se_play pascal, 13

loc_1EB39:
		cmp	word_26346, 100h
		jl	short loc_1EB4E
		mov	ax, word_26346
		and	ax, 7Fh
		add	ax, 0FFA0h
		push	ax
		call	sub_16BD9

loc_1EB4E:
		mov	al, 0
		pop	bp
		retn
sub_1EA14	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EB52	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1EBF0
		mov	byte ptr word_25FFA, 10h
		push	1Fh
		call	sub_157E4
		add	al, 0Ch
		mov	byte ptr word_26006+1, al
		push	7Fh
		call	sub_157E4
		add	al, 80h
		mov	byte ptr word_26006, al
		mov	byte_26000, 2
		mov	byte_26001, 9
		mov	byte_2C976, 1
		mov	byte ptr word_25FFA+1, 2Eh ; '.'
		mov	word ptr dword_26002, 0C03h
		call	sub_15A70
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EBF0
		call	snd_se_play pascal, 3
		mov	byte ptr word_25FFA, 12h
		push	600h
		call	sub_157FA
		sub	ax, 300h
		add	ax, word ptr dword_25FFC
		mov	word ptr dword_25FFC, ax
		push	400h
		call	sub_157FA
		sub	ax, 200h
		add	ax, word ptr dword_25FFC+2
		mov	word ptr dword_25FFC+2,	ax
		mov	byte ptr word_25FFA+1, 0
		mov	byte_26000, 7
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	word ptr dword_26002+2,	604h
		mov	byte ptr word_26006, 0
		call	sub_15A5C

loc_1EBF0:
		cmp	word_26346, 80h
		jnz	short loc_1EBFD
		mov	ax, 1
		jmp	short loc_1EBFF
; ---------------------------------------------------------------------------

loc_1EBFD:
		xor	ax, ax

loc_1EBFF:
		pop	bp
		retn
sub_1EB52	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EC01	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jnz	short loc_1EC14
		mov	al, 1
		sub	al, byte_2D085
		mov	byte_2D085, al

loc_1EC14:
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EC5B
		mov	byte ptr word_25FFA, 13h
		mov	byte ptr word_26006+1, 58h ; 'X'
		cmp	byte_2D085, 0
		jz	short loc_1EC39
		mov	al, byte ptr word_26006
		add	al, 3
		jmp	short loc_1EC3E
; ---------------------------------------------------------------------------

loc_1EC39:
		mov	al, byte ptr word_26006
		add	al, 0FDh

loc_1EC3E:
		mov	byte ptr word_26006, al
		mov	byte_26000, 4
		mov	word ptr dword_26002, 816h
		mov	byte ptr word_25FFA+1, 34h ; '4'
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1EC5B:
		cmp	word_26346, 80h
		jnz	short loc_1EC68
		mov	ax, 1
		jmp	short loc_1EC6A
; ---------------------------------------------------------------------------

loc_1EC68:
		xor	ax, ax

loc_1EC6A:
		pop	bp
		retn
sub_1EC01	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EC6C	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jnz	short loc_1EC7B
		mov	byte ptr dword_26002, 8

loc_1EC7B:
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1ECD0
		mov	byte ptr word_25FFA+1, 34h ; '4'
		mov	byte ptr word_25FFA, 13h
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte_26000, 4
		mov	byte_26001, 8
		mov	ax, word_26346
		mov	bx, 80h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1ECB9
		cmp	byte ptr dword_26002, 0Eh
		jnb	short loc_1ECB9
		inc	byte ptr dword_26002

loc_1ECB9:
		mov	byte_2C976, 1
		mov	al, byte ptr word_26006
		add	al, 2
		mov	byte ptr word_26006, al
		call	sub_15A70
		call	snd_se_play pascal, 3

loc_1ECD0:
		mov	al, 0
		pop	bp
		retn
sub_1EC6C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1ECD4	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		mov	di, dx
		mov	byte_26309, 3
		mov	byte_26313, 8
		mov	word_26318, 2Fh	; '/'
		mov	word_2631A, 50h	; 'P'
		cmp	word_26346, 90h
		jge	short loc_1ED67
		or	di, di
		jnz	short loc_1ED46
		push	word ptr dword_2630A
		push	word ptr dword_2630A+2
		push	30h ; '0'
		call	sub_15A24
		mov	byte_26312, al
		mov	ax, word_22870
		inc	word_22870
		push	ax
		call	sub_17548
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 44h ; 'D'
		mov	byte_26000, 4
		call	sub_157D6
		mov	byte ptr word_26006, al
		mov	byte ptr word_26006+1, 40h
		mov	word ptr dword_26002, 0A20h
		call	sub_15A5C
		jmp	short loc_1ED67
; ---------------------------------------------------------------------------

loc_1ED46:
		cmp	di, 8
		jnz	short loc_1ED67
		push	word ptr dword_2630A
		push	word ptr dword_2630A+2
		push	0D0h
		call	sub_15A24
		mov	byte_26312, al
		mov	ax, word_22870
		inc	word_22870
		push	ax
		call	sub_17548

loc_1ED67:
		and	word_22870, 0Fh
		xor	si, si
		jmp	short loc_1EDA4
; ---------------------------------------------------------------------------

loc_1ED70:
		mov	bx, si
		imul	bx, 18h
		cmp	byte ptr [bx+5628h], 2
		jnz	short loc_1EDA3
		test	si, 1
		jz	short loc_1ED8F
		mov	bx, si
		imul	bx, 18h
		mov	al, [bx+5632h]
		inc	al
		jmp	short loc_1ED9A
; ---------------------------------------------------------------------------

loc_1ED8F:
		mov	bx, si
		imul	bx, 18h
		mov	al, [bx+5632h]
		add	al, 0FFh

loc_1ED9A:
		mov	bx, si
		imul	bx, 18h
		mov	[bx+5632h], al

loc_1EDA3:
		inc	si

loc_1EDA4:
		cmp	si, 10h
		jl	short loc_1ED70
		cmp	word_26346, 0D0h
		jnz	short loc_1EDBB
		mov	word_22870, 0
		mov	al, 1
		jmp	short loc_1EDBD
; ---------------------------------------------------------------------------

loc_1EDBB:
		mov	al, 0

loc_1EDBD:
		pop	di
		pop	si
		pop	bp
		retn
sub_1ECD4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EDC1	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EE14
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 3
		mov	byte_26001, 3
		mov	byte_2C976, 2
		mov	byte ptr word_26006+1, 40h
		mov	word ptr dword_26002, 907h
		mov	byte ptr word_25FFA+1, 44h ; 'D'
		push	300h
		call	sub_157FA
		sub	ax, 180h
		add	ax, word ptr dword_25FFC
		mov	word ptr dword_25FFC, ax
		mov	byte ptr word_26006, 0
		call	sub_15A70
		call	snd_se_play pascal, 3

loc_1EE14:
		mov	ax, word_26346
		add	ax, 0FF9Ch
		push	ax
		call	sub_16BD9
		cmp	word_26346, 80h
		jnz	short loc_1EE2B
		mov	ax, 1
		jmp	short loc_1EE2D
; ---------------------------------------------------------------------------

loc_1EE2B:
		xor	ax, ax

loc_1EE2D:
		pop	bp
		retn
sub_1EDC1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EE2F	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h
		jnz	short loc_1EE59
		mov	byte_26309, 2
		mov	byte_26313, 6
		mov	byte_26312, 0
		mov	word_26318, 1Eh
		mov	word_26314, 58h	; 'X'
		mov	byte_2D085, 0

loc_1EE59:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EEA1
		cmp	byte_2D085, 0
		jnz	short loc_1EE83
		mov	al, byte_26312
		add	al, 8
		mov	byte_26312, al
		cmp	byte_26312, 80h
		jb	short loc_1EE9E
		mov	byte_2D085, 1
		jmp	short loc_1EE9E
; ---------------------------------------------------------------------------

loc_1EE83:
		cmp	byte_2D085, 1
		jnz	short loc_1EEA1
		mov	al, byte_26312
		add	al, 0F8h
		mov	byte_26312, al
		cmp	byte_26312, 0
		jnz	short loc_1EE9E
		mov	byte_2D085, 0

loc_1EE9E:
		call	sub_174C7

loc_1EEA1:
		cmp	word_26346, 100h
		jl	short loc_1EEED
		mov	ax, word_26346
		and	ax, 3Fh
		add	ax, 0FFE0h
		push	ax
		call	sub_16BD9
		cmp	word_26346, 200h
		jl	short loc_1EEED
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EEED
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 5
		mov	byte ptr word_26006, 0
		mov	byte ptr word_26006+1, 40h
		mov	word ptr dword_26002, 0A20h
		mov	byte ptr word_25FFA+1, 44h ; 'D'
		call	sub_15A5C

loc_1EEED:
		mov	al, 0
		pop	bp
		retn
sub_1EE2F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EEF1	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EF6F
		mov	byte ptr word_26006+1, 38h ; '8'
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 3
		mov	byte ptr word_25FFA+1, 2Fh ; '/'
		mov	byte ptr word_26006, 0
		mov	word ptr dword_26002, 0F09h
		call	sub_15A5C
		mov	ax, word_26346
		mov	bx, 40h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EF6F
		mov	word_2BC82, 0Bh
		mov	byte_2BC88, 30h	; '0'
		mov	ax, word_26346
		mov	bx, 80h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EF54
		push	word_2BC71+1
		push	word_2BC74
		push	20h ; ' '
		jmp	short loc_1EF5F
; ---------------------------------------------------------------------------

loc_1EF54:
		push	word_2BC71+1
		push	word_2BC74
		push	0E0h

loc_1EF5F:
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_17687
		call	snd_se_play pascal, 15

loc_1EF6F:
		cmp	word_26346, 100h
		jnz	short loc_1EF7C
		mov	ax, 1
		jmp	short loc_1EF7E
; ---------------------------------------------------------------------------

loc_1EF7C:
		xor	ax, ax

loc_1EF7E:
		pop	bp
		retn
sub_1EEF1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EF80	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EFCF
		mov	word_2BC82, 0Bh
		mov	byte_2BC88, 40h
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EFB4
		push	word_2BC71+1
		push	word_2BC74
		push	40h
		jmp	short loc_1EFBF
; ---------------------------------------------------------------------------

loc_1EFB4:
		push	word_2BC71+1
		push	word_2BC74
		push	0C0h

loc_1EFBF:
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_17687
		call	snd_se_play pascal, 15

loc_1EFCF:
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9
		cmp	word_26346, 80h
		jnz	short loc_1EFE9
		mov	ax, 1
		jmp	short loc_1EFEB
; ---------------------------------------------------------------------------

loc_1EFE9:
		xor	ax, ax

loc_1EFEB:
		pop	bp
		retn
sub_1EF80	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EFED	proc near
		push	bp
		mov	bp, sp
		add	word ptr dword_25FFC+2,	680h
		mov	ax, word_22872
		mov	word ptr dword_25FFC, ax
		mov	word ptr dword_2A722, ax
		cmp	word_26346, 40h
		jnz	short loc_1F045
		mov	byte ptr word_2BC71, 0C4h
		mov	byte ptr word_26006, 20h ; ' '
		mov	byte_2BC88, 50h	; 'P'
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 2
		mov	word ptr dword_26002, 803h
		mov	byte ptr word_25FFA+1, 2Fh ; '/'
		mov	byte_2D085, 0
		mov	byte_2D084, 0
		mov	byte_2D083, 0
		call	snd_se_play pascal, 8

loc_1F045:
		cmp	word_26346, 80h
		jge	short loc_1F08C
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1F137
		mov	byte_2A72E, 0Eh
		mov	ax, word ptr dword_25FFC+2
		mov	word ptr dword_2A722+2,	ax
		mov	word_2A72A, 1000h
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F081
		mov	byte_2A72F, 2
		jmp	short loc_1F086
; ---------------------------------------------------------------------------

loc_1F081:
		mov	byte_2A72F, 0FEh

loc_1F086:
		call	sub_16A03
		jmp	loc_1F137
; ---------------------------------------------------------------------------

loc_1F08C:
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1F137
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F0D0
		mov	ax, word ptr dword_25FFC+2
		mov	word ptr dword_2A722+2,	ax
		mov	word_2A72A, 800h
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F0C8
		mov	byte_2A72F, 2
		jmp	short loc_1F0CD
; ---------------------------------------------------------------------------

loc_1F0C8:
		mov	byte_2A72F, 0FEh

loc_1F0CD:
		call	sub_16A03

loc_1F0D0:
		mov	al, 80h
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		call	sub_15A8E
		mov	al, 80h
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		call	sub_15A8E
		call	snd_se_play pascal, 3
		mov	al, byte_2D085
		sub	byte ptr word_26006, al
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F137
		mov	al, byte_2D084
		add	byte_2D085, al
		cmp	byte_2D083, 0
		jnz	short loc_1F122
		inc	byte_2D084
		cmp	byte_2D084, 10h
		jb	short loc_1F137
		inc	byte_2D083
		jmp	short loc_1F137
; ---------------------------------------------------------------------------

loc_1F122:
		dec	byte_2D084
		cmp	byte_2D084, 0
		jnz	short loc_1F137
		mov	ax, word ptr dword_2CEA0
		mov	word_22872, ax
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1F137:
		mov	al, 0
		pop	bp
		retn
sub_1EFED	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F13B	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		add	ax, 0FFC0h
		push	ax
		push	60007h
		call	sub_16A6B
		cmp	word_26346, 40h
		jnz	short loc_1F182
		mov	byte_26344, 0B5h
		call	snd_se_play pascal, 8
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	byte_26000, 2
		call	sub_157D6
		mov	byte ptr word_26006, al
		mov	word ptr dword_26002, 1505h
		mov	byte_2D085, 0
		mov	word_2633E, 0

loc_1F182:
		cmp	word_26346, 80h
		jl	loc_1F218
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F1D4
		mov	ax, 0D48h
		sub	ax, word_26342
		cwde
		shl	eax, 6
		mov	ebx, 0D48h
		xor	edx, edx
		div	ebx
		add	al, 28h	; '('
		mov	byte ptr word_26006+1, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 87h
		mov	byte ptr word_26006, al
		call	snd_se_play pascal, 9

loc_1F1D4:
		push	0C00h
		push	word_2633E
		mov	al, byte_2D085
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+42Eh]
		call	sub_14E50
		mov	word_26335+1, ax
		mov	al, byte_2D085
		add	al, 2
		mov	byte_2D085, al
		mov	ax, 0D48h
		sub	ax, word_26342
		cwde
		shl	eax, 6
		shl	eax, 4
		mov	ebx, 0D48h
		xor	edx, edx
		div	ebx
		mov	word_2633E, ax

loc_1F218:
		pop	bp
		retn
sub_1F13B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F21A	proc far
		push	bp
		mov	bp, sp
		cmp	byte_2429A, 0
		jz	short loc_1F229
		mov	byte_2CE56, 27h	; '''

loc_1F229:
		cmp	byte_2CE56, 0
		jnz	short loc_1F237
		call	sub_1FADD
		mov	ah, 0
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_1F237:
		xor	ax, ax
		pop	bp
		retf
sub_1F21A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F23B	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_2]
		cmp	si, 0FFFFh
		jz	short loc_1F25F
		push	si
		call	sub_162CC
		cmp	byte_229BA, 0
		jnz	short loc_1F25F
		mov	byte_226C0, 1
		mov	byte_2C978, 1
		call	sub_1FB19

loc_1F25F:
		mov	byte_229BA, 1
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	byte ptr word_2634A+1, 0
		mov	ax, word_2634C
		mov	word_26342, ax
		mov	ax, [bp+arg_0]
		mov	word_2634C, ax
		pop	si
		pop	bp
		retn	4
sub_1F23B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F289	proc far
		push	bp
		mov	bp, sp
		push	si
		cmp	byte_2CE56, 0
		jz	short loc_1F298
		dec	byte_2CE56

loc_1F298:
		mov	eax, dword ptr word_26335+1
		mov	dword_2C922, eax
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		mov	dword_2630A, eax
		mov	dword ptr word_2BC71+1,	eax
		inc	word_26346
		mov	al, byte_26345
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 11h
		ja	loc_1F660
		add	bx, bx
		jmp	cs:off_1F689[bx]

loc_1F2C9:
		cmp	word_26346, 1
		jnz	short loc_1F333
		mov	word_26342, 6784h
		mov	word_2634C, 5CF8h
		mov	word_2A72A, 800h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0B4h
		mov	word_2C96E, 0BAh
		mov	word_2C970, 0B8h
		mov	word_2C972, 0B4h
		mov	byte_2CE56, 0
		mov	word_22582, 400h
		mov	word_22584, 1400h
		mov	word_22586, 300h
		mov	word_22588, 600h
		mov	si, 0CCh
		jmp	short loc_1F32D
; ---------------------------------------------------------------------------

loc_1F326:
		push	si
		call	super_convert_tiny
		inc	si

loc_1F32D:
		cmp	si, 0DCh
		jl	short loc_1F326

loc_1F333:
		call	sub_1FB07
		cmp	word_26346, 0C0h
		jl	loc_1F666
		mov	word_26346, 0
		inc	byte_26345
		call	snd_se_play pascal, 13
		mov	Palettes, 0
		mov	Palettes+1, 0
		mov	Palettes+2, 0
		mov	byte_25FE9, 1
		mov	word_2CE64, 0C4h
		mov	fp_23F5A, offset sub_DCDB
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F374:
		call	sub_1FB07
		cmp	word_26346, 40h
		jl	loc_1F666
		inc	byte_26345
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	word_26346, 0
		mov	fp_2D06C, offset sub_11695
		mov	byte_2D085, 0
		mov	fp_2CE66, offset sub_1E922
		mov	byte_2D07F, 0
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F3AD:
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1F3BD
		cmp	ax, 1
		jz	short loc_1F400
		jmp	short loc_1F403
; ---------------------------------------------------------------------------

loc_1F3BD:
		mov	ax, word_26346
		add	ax, 0FFE0h
		push	ax
		call	sub_16BD9
		or	al, al
		jz	short loc_1F403
		mov	word_26346, 0
		inc	byte ptr word_2634A+1
		inc	byte_26349
		mov	al, byte_2D07F
		mov	ah, 0
		shl	ax, 2
		mov	dl, byte ptr word_2634A+1
		mov	dh, 0
		and	dx, 1
		add	dx, dx
		add	ax, dx
		mov	bx, ax
		mov	ax, off_22874[bx]
		mov	fp_2CE66, ax
		cmp	byte ptr word_2634A+1, 20h ; ' '
		jb	short loc_1F403
		jmp	short loc_1F412
; ---------------------------------------------------------------------------

loc_1F400:
		call	sub_1E8DA

loc_1F403:
		call	sub_1F21A
		or	ax, ax
		jz	loc_1F666
		push	14h
		call	sub_17416

loc_1F412:
		mov	al, byte_2D07F
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	loc_1F666
		add	bx, bx
		jmp	cs:off_1F681[bx]

loc_1F427:
		pushd	5208h
		call	sub_1F23B
		mov	fp_2CE66, offset sub_1EA14
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F439:
		push	13AFCh
		call	sub_1F23B
		mov	fp_2CE66, offset sub_1EC6C
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F44B:
		push	22580h
		call	sub_1F23B
		mov	fp_2CE66, offset sub_1EE2F
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F45D:
		push	30D48h
		call	sub_1F23B
		mov	fp_2CE66, offset sub_1EFED
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F46F:
		cmp	Palettes, 60h
		jnb	short loc_1F483
		mov	al, Palettes
		add	al, 2
		mov	Palettes, al
		mov	byte_25FE9, 1

loc_1F483:
		push	0C000400h
		call	sub_16CCC
		or	al, al
		jz	short loc_1F49F
		mov	word_26346, 0
		inc	byte_26345
		mov	byte_26349, 1

loc_1F49F:
		call	sub_1F21A
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F4A6:
		cmp	Palettes, 60h
		jnb	short loc_1F4BA
		mov	al, Palettes
		add	al, 2
		mov	Palettes, al
		mov	byte_25FE9, 1

loc_1F4BA:
		call	sub_1E8DA
		cmp	word_26346, 0FA0h
		jg	short loc_1F4D4

loc_1F4C5:
		call	sub_1F21A
		or	ax, ax
		jz	loc_1F666
		push	14h
		call	sub_17416

loc_1F4D4:
		mov	al, byte_2D07F
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	short loc_1F523
		add	bx, bx
		jmp	cs:off_1F679[bx]

loc_1F4E7:
		push	146B4h
		call	sub_1F23B
		mov	fp_2CE66, offset sub_1EB52
		jmp	short loc_1F523
; ---------------------------------------------------------------------------

loc_1F4F8:
		push	23138h
		call	sub_1F23B
		mov	fp_2CE66, offset sub_1ECD4
		jmp	short loc_1F523
; ---------------------------------------------------------------------------

loc_1F509:
		push	31A90h
		call	sub_1F23B
		mov	fp_2CE66, offset sub_1EEF1
		jmp	short loc_1F523
; ---------------------------------------------------------------------------

loc_1F51A:
		push	40000h
		call	sub_1F23B

loc_1F523:
		mov	word_2CC8E, 9
		mov	word_2CE64, 0C8h
		inc	byte_2D07F
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F536:
		cmp	Palettes+2, 60h
		jnb	short loc_1F552
		mov	al, Palettes+2
		add	al, 2
		mov	Palettes+2, al
		mov	al, Palettes
		add	al, 0FEh
		mov	Palettes, al
		mov	byte_25FE9, 1

loc_1F552:
		cmp	byte_26345, 5
		jnz	loc_1F3AD
		jmp	loc_1F483
; ---------------------------------------------------------------------------

loc_1F55E:
		cmp	Palettes, 30h	; '0'
		jnb	short loc_1F572
		inc	Palettes
		dec	Palettes+2
		mov	byte_25FE9, 1

loc_1F572:
		cmp	byte_26345, 9
		jnz	loc_1F3AD
		jmp	loc_1F483
; ---------------------------------------------------------------------------

loc_1F57E:
		cmp	Palettes+1, 40h
		jnb	short loc_1F5A4
		cmp	Palettes, 0
		jbe	short loc_1F590
		dec	Palettes

loc_1F590:
		inc	Palettes+1
		cmp	Palettes+2, 0
		jbe	short loc_1F59F
		dec	Palettes+2

loc_1F59F:
		mov	byte_25FE9, 1

loc_1F5A4:
		cmp	byte_26345, 0Dh
		jnz	loc_1F3AD
		jmp	loc_1F483
; ---------------------------------------------------------------------------

loc_1F5B0:
		call	sub_1E8DA
		or	al, al
		jz	loc_1F4C5
		inc	byte ptr word_2634A+1
		cmp	byte ptr word_2634A+1, 8
		jbe	loc_1F4C5
		jmp	loc_1F4D4
; ---------------------------------------------------------------------------

loc_1F5C9:
		cmp	byte_2D080, 0
		jnz	short loc_1F5DD
		cmp	Palettes+1, 0
		jbe	short loc_1F621
		dec	Palettes+1
		jmp	short loc_1F626
; ---------------------------------------------------------------------------

loc_1F5DD:
		cmp	byte_2D080, 1
		jnz	short loc_1F606
		mov	al, Palettes
		add	al, 2
		mov	Palettes, al
		inc	Palettes+1
		mov	al, Palettes+2
		add	al, 2
		mov	Palettes+2, al
		cmp	Palettes, 80h
		jb	short loc_1F626
		mov	byte_2D080, 2
		jmp	short loc_1F626
; ---------------------------------------------------------------------------

loc_1F606:
		mov	al, Palettes
		add	al, 0FEh
		mov	Palettes, al
		dec	Palettes+1
		mov	al, Palettes+2
		add	al, 0FEh
		mov	Palettes+2, al
		cmp	Palettes, 0
		jnz	short loc_1F626

loc_1F621:
		mov	byte_2D080, 1

loc_1F626:
		mov	byte_25FE9, 1
		call	sub_1F13B
		cmp	word_26346, 1388h
		jg	short loc_1F643
		call	sub_1F21A
		or	ax, ax
		jz	short loc_1F666
		mov	byte ptr word_2634A+1, 1

loc_1F643:
		push	4
		call	sub_162CC
		mov	word_26346, 0
		mov	byte_26345, 0FDh
		mov	fp_2D06C, offset nullsub_2
		mov	byte_226C0, 0
		jmp	short loc_1F666
; ---------------------------------------------------------------------------

loc_1F660:
		push	0C8h
		call	sub_1FBBE

loc_1F666:
		call	sub_17726
		call	sub_1E8B0
		push	word_26342
		push	6784h
		call	sub_17354
		pop	si
		pop	bp
		retf
sub_1F289	endp

; ---------------------------------------------------------------------------
off_1F679	dw offset loc_1F4E7
		dw offset loc_1F4F8
		dw offset loc_1F509
		dw offset loc_1F51A
off_1F681	dw offset loc_1F427
		dw offset loc_1F439
		dw offset loc_1F44B
		dw offset loc_1F45D
off_1F689	dw offset loc_1F2C9
		dw offset loc_1F374
		dw offset loc_1F3AD
		dw offset loc_1F46F
		dw offset loc_1F4A6
		dw offset loc_1F536
		dw offset loc_1F536
		dw offset loc_1F483
		dw offset loc_1F4BA
		dw offset loc_1F55E
		dw offset loc_1F55E
		dw offset loc_1F483
		dw offset loc_1F4BA
		dw offset loc_1F57E
		dw offset loc_1F57E
		dw offset loc_1F483
		dw offset loc_1F5B0
		dw offset loc_1F5C9

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F6AD	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 1
		jnz	short loc_1F6DC
		cmp	byte_2D085, 0
		jz	short loc_1F6C5
		cmp	byte_2D085, 3
		jnz	short loc_1F6CD

loc_1F6C5:
		mov	word_26328, 0FFE0h
		jmp	short loc_1F6D3
; ---------------------------------------------------------------------------

loc_1F6CD:
		mov	word_26328, 20h	; ' '

loc_1F6D3:
		inc	byte_2D085
		and	byte_2D085, 3

loc_1F6DC:
		push	5940h
		call	sub_152D2
		cmp	word_26332, 20h	; ' '
		jl	short loc_1F6ED
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1F6ED:
		mov	al, 0
		pop	bp
		retn
sub_1F6AD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F6F1	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 20h	; ' '
		jge	short loc_1F744
		mov	ax, word_26332
		add	ax, 0FFF0h
		push	ax
		push	30002h
		call	sub_16A6B
		cmp	word_26332, 10h
		jnz	short loc_1F719
		call	snd_se_play pascal, 8

loc_1F719:
		cmp	word_26332, 14h
		jz	short loc_1F72E
		cmp	word_26332, 18h
		jz	short loc_1F72E
		cmp	word_26332, 1Ch
		jnz	short loc_1F732

loc_1F72E:
		inc	byte_26330

loc_1F732:
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	0
		call	sub_15A24
		mov	byte ptr word_26006, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1F744:
		cmp	byte_26330, 0DBh
		jnb	short loc_1F75C
		mov	ax, word_26332
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F75C
		inc	byte_26330

loc_1F75C:
		call	fp_2CE68
		or	al, al
		jz	short loc_1F774
		mov	word_26332, 0
		mov	byte_2D084, 0
		mov	byte_26330, 0D4h

loc_1F774:
		pop	bp
		retn
sub_1F6F1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F776	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26332
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F7AA
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	byte ptr word_26006+1, 58h ; 'X'
		mov	byte_26000, 2
		mov	word ptr dword_26002, 70Dh
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1F7AA:
		cmp	word_26332, 60h
		jl	short loc_1F7B6
		mov	ax, 1
		jmp	short loc_1F7B8
; ---------------------------------------------------------------------------

loc_1F7B6:
		xor	ax, ax

loc_1F7B8:
		pop	bp
		retn
sub_1F776	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F7BA	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26332
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F813
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 44h ; 'D'
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	byte_26000, 4
		mov	byte ptr dword_26002, 10h
		push	400h
		call	sub_157FA
		sub	ax, 200h
		add	ax, word ptr dword_25FFC
		mov	word ptr dword_25FFC, ax
		push	400h
		call	sub_157FA
		sub	ax, 200h
		add	ax, word ptr dword_25FFC+2
		mov	word ptr dword_25FFC+2,	ax
		call	sub_157D6
		mov	byte ptr word_26006, al
		call	sub_15A5C
		call	snd_se_play pascal, 3

loc_1F813:
		cmp	word_26332, 60h
		jl	short loc_1F81F
		mov	ax, 1
		jmp	short loc_1F821
; ---------------------------------------------------------------------------

loc_1F81F:
		xor	ax, ax

loc_1F821:
		pop	bp
		retn
sub_1F7BA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F823	proc near
		push	bp
		mov	bp, sp
		cmp	word_26332, 20h	; ' '
		jnz	short loc_1F86B
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 0
		mov	byte_26000, 9
		mov	byte ptr word_26006, 0
		mov	dword_26002, 6050A05h
		mov	byte ptr word_26006+1, 20h ; ' '
		call	sub_15A5C
		mov	byte_26000, 0Bh
		mov	byte ptr dword_26002+3,	4
		mov	byte ptr dword_26002, 20h ; ' '
		call	sub_15A5C
		call	snd_se_play pascal, 15

loc_1F86B:
		cmp	word_26332, 40h
		jl	short loc_1F877
		mov	ax, 1
		jmp	short loc_1F879
; ---------------------------------------------------------------------------

loc_1F877:
		xor	ax, ax

loc_1F879:
		pop	bp
		retn
sub_1F823	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F87B	proc far
		push	bp
		mov	bp, sp
		mov	eax, dword_26320
		mov	dword_25FFC, eax
		mov	dword_2A722, eax
		inc	word_26332
		mov	al, byte_26331
		mov	ah, 0
		or	ax, ax
		jz	short loc_1F89F
		cmp	ax, 1
		jz	short loc_1F8E7
		jmp	loc_1F992
; ---------------------------------------------------------------------------

loc_1F89F:
		push	5940h
		call	sub_152D2
		push	1800180h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 0C0h
		jl	loc_1F9A1
		inc	byte_26331
		mov	word_26332, 0
		mov	byte ptr word_26335, 0
		mov	byte_2D085, 0
		mov	byte_2D084, 1
		mov	byte_2D083, 0
		mov	word_2632A, 0
		mov	fp_2CE68, offset sub_1F776
		jmp	loc_1F9A1
; ---------------------------------------------------------------------------

loc_1F8E7:
		mov	eax, dword_26320
		mov	dword_26324, eax
		mov	al, byte_2D084
		mov	ah, 0
		or	ax, ax
		jz	short loc_1F8FF
		cmp	ax, 1
		jz	short loc_1F933
		jmp	short loc_1F936
; ---------------------------------------------------------------------------

loc_1F8FF:
		call	sub_1F6AD
		or	al, al
		jz	short loc_1F936
		mov	word_26332, 0
		inc	byte_2D083
		mov	al, byte_2D083
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		add	dx, dx
		mov	bx, dx
		mov	ax, off_22884[bx]
		mov	fp_2CE68, ax
		inc	byte_2D084
		cmp	byte_2D083, 10h
		jb	short loc_1F936
		jmp	short loc_1F968
; ---------------------------------------------------------------------------

loc_1F933:
		call	sub_1F6F1

loc_1F936:
		push	1800180h
		push	4
		call	sub_1FA9D
		mov	byte_26334, al
		mov	ah, 0
		sub	word_2632E, ax
		cmp	word_2632E, 0
		jg	short loc_1F9A1
		mov	byte_2C978, 1
		push	1Eh
		call	sub_173AC
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	5
		call	sub_16D84

loc_1F968:
		mov	byte_26331, 0FEh
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	800030h
		call	sub_1597C
		call	snd_se_play pascal, 12
		jmp	short loc_1F9A1
; ---------------------------------------------------------------------------

loc_1F992:
		call	sub_17486
		push	word_2632E
		push	60Eh
		call	sub_17354
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_1F9A1:
		push	word_2632E
		push	60Eh
		call	sub_17354
		mov	ax, word ptr dword_26320
		mov	word ptr dword_2C922, ax
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_2C922+2,	ax
		pop	bp
		retf
sub_1F87B	endp

; ---------------------------------------------------------------------------
		db 0

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F9BA	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		mov	dx, [bp+arg_0]
		mov	bx, [bp+arg_2]
		push	si
		xor	bp, bp
		mov	si, 1FBCh
		mov	cx, 4

loc_1F9CC:
		mov	ax, dx
		xor	dx, dx
		div	word ptr [si]
		mov	[bx], al
		or	al, al
		jz	short loc_1F9DE
		or	bp, bp
		jnz	short loc_1F9DE
		mov	bp, cx

loc_1F9DE:
		dec	bx
		add	si, 2
		loop	loc_1F9CC
		mov	[bx], dl
		add	bp, 2
		shl	bp, 3
		mov	ax, bp
		pop	si
		pop	bp
		retn	4
sub_1F9BA	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F9F4	proc far

arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	di
		; Hack?!? What is this I don't even
		db 08dh
		db 03eh
		db 0c9h
		db 01fh
		movzx	edx, [bp+arg_4]
		db 08dh
		db 01eh
		db 0a8h
		db 01fh
		mov	ax, [bp+arg_2]
		mov	cx, 4
		jmp	short loc_1FA27
sub_1F9F4	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FA0E	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		push	di
		mov	edx, [bp+arg_0]
		mov	di, 1FC6h
		mov	ax, TX_WHITE
		mov	byte ptr dword_229AA+3,	0A0h
		mov	bx, 1FA0h
		mov	cx, 6

loc_1FA27:
		push	[bp+arg_6]
		push	[bp+arg_4]
		push	ds
		push	di
		push	ax
		mov	ax, ds
		mov	es, ax

loc_1FA34:
		mov	eax, edx
		xor	edx, edx
		div	dword ptr [bx]
		or	ch, al
		jz	short loc_1FA45
		add	al, 0A0h
		jmp	short loc_1FA47
; ---------------------------------------------------------------------------

loc_1FA45:
		mov	al, 2

loc_1FA47:
		stosb
		add	bx, 4
		dec	cl
		jnz	short loc_1FA34
		add	dl, 0A0h
		mov	[di], dl
		call	gaiji_putsa
		pop	di
		pop	bp
		retf	8
sub_1FA0E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FA5E	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		mov	byte_2297E, 1
		mov	ax, [bp+arg_4]
		mov	word_2CED6, ax
		mov	ax, [bp+arg_2]
		mov	word_2CED8, ax
		mov	eax, dword ptr word_26335+1
		mov	dword_2CED2, eax
		call	sub_126B3
		mov	si, ax
		or	si, si
		jz	short loc_1FA8E
		call	snd_se_play pascal, [bp+arg_0]

loc_1FA8E:
		mov	byte_2297E, 0
		call	sub_1FD62
		mov	ax, si
		pop	si
		pop	bp
		retn	6
sub_1FA5E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FA9D	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		mov	byte_2297E, 1
		mov	ax, [bp+arg_4]
		mov	word_2CED6, ax
		mov	ax, [bp+arg_2]
		mov	word_2CED8, ax
		mov	ax, word ptr dword_26320
		mov	word ptr dword_2CED2, ax
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_2CED2+2,	ax
		call	sub_126B3
		mov	si, ax
		or	si, si
		jz	short loc_1FAD1
		call	snd_se_play pascal, [bp+arg_0]

loc_1FAD1:
		mov	byte_2297E, 0
		mov	ax, si
		pop	si
		pop	bp
		retn	6
sub_1FA9D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FADD	proc near
		push	bp
		mov	bp, sp
		push	word_2D088
		push	word_2D08A
		push	4
		call	sub_1FA5E
		mov	byte_26348, al
		mov	ah, 0
		sub	word_26342, ax
		mov	ax, word_26342
		cmp	ax, word_2634C
		jg	short loc_1FB03
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FB03:
		mov	al, 0
		pop	bp
		retn
sub_1FADD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FB07	proc near
		push	bp
		mov	bp, sp
		push	word_2D088
		push	word_2D08A
		push	0Ah
		call	sub_1FA5E
		pop	bp
		retn
sub_1FB07	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FB19	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		cmp	byte_2CEBE, 80h
		jnb	short loc_1FB2A
		xor	di, di
		jmp	short loc_1FB2D
; ---------------------------------------------------------------------------

loc_1FB2A:
		mov	di, 1

loc_1FB2D:
		mov	ax, word_26335+1
		add	ax, 0FC00h
		mov	[bp+var_2], ax
		mov	ax, word_26338
		add	ax, 0FC00h
		mov	[bp+var_4], ax
		xor	si, si
		jmp	short loc_1FB65
; ---------------------------------------------------------------------------

loc_1FB43:
		push	800h
		call	sub_157FA
		add	ax, [bp+var_2]
		push	ax
		push	800h
		call	sub_157FA
		add	ax, [bp+var_4]
		push	ax
		mov	bx, di
		imul	bx, 5
		mov	al, [bx+si+1FD0h]
		push	ax
		call	sub_16D84
		inc	si

loc_1FB65:
		cmp	si, 5
		jl	short loc_1FB43
		pop	di
		pop	si
		leave
		retn
sub_1FB19	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FB6E	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_2]
		cmp	si, 0FFFFh
		jz	short loc_1FB94
		push	si
		call	sub_162CC
		cmp	byte_229BA, 0
		jnz	short loc_1FB94
		cmp	byte_2C979, 14h
		jnb	short loc_1FB91
		mov	byte_2C979, 14h

loc_1FB91:
		call	sub_1FB19

loc_1FB94:
		mov	byte_229BA, 1
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	byte ptr word_2634A+1, 0
		mov	ax, word_2634C
		mov	word_26342, ax
		mov	ax, [bp+arg_0]
		mov	word_2634C, ax
		pop	si
		pop	bp
		retn	4
sub_1FB6E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FBBE	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		cmp	byte_26345, 0FDh
		jnz	short loc_1FC23
		cmp	word_26346, 1
		jnz	short loc_1FBE1
		mov	byte_26348, 0
		push	0
		call	sub_162CC
		call	snd_se_play pascal, 13

loc_1FBE1:
		cmp	word_26346, 10h
		jnz	short loc_1FBED
		push	4
		call	sub_162CC

loc_1FBED:
		cmp	word_26346, 20h	; ' '
		jnz	loc_1FD51
		call	sub_1637A
		inc	byte_26345
		mov	al, byte ptr word_2634A+1
		mov	byte_2C978, al
		cmp	byte ptr word_2634A+1, 0
		jz	short loc_1FC10
		push	[bp+arg_0]
		call	sub_17416

loc_1FC10:
		mov	byte_26344, 4
		mov	word_26346, 0
		mov	byte_2CEBC, 0FFh
		jmp	loc_1FD51
; ---------------------------------------------------------------------------

loc_1FC23:
		cmp	byte_26345, 0FEh
		jnz	short loc_1FC95
		cmp	word_26346, 0Ch
		jge	short loc_1FC55
		cmp	byte_25FE2, 0
		jnz	short loc_1FC3D
		mov	ax, 0FFFCh
		jmp	short loc_1FC40
; ---------------------------------------------------------------------------

loc_1FC3D:
		mov	ax, 4

loc_1FC40:
		mov	word_2CE02, ax
		cmp	byte_25FE3, 1
		ja	short loc_1FC4F
		mov	ax, 0FFFCh
		jmp	short loc_1FC52
; ---------------------------------------------------------------------------

loc_1FC4F:
		mov	ax, 4

loc_1FC52:
		mov	word_2CE04, ax

loc_1FC55:
		mov	fp_23F5A, offset sub_BBE8
		mov	word_25FE6, 2
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1FD5D
		inc	byte_26344
		cmp	byte_26344, 0Ch
		jb	loc_1FD5D
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_2C96C, 1
		mov	fp_2D06A, offset nullsub_2
		jmp	loc_1FD5D
; ---------------------------------------------------------------------------

loc_1FC95:
		mov	PaletteTone, 3Ch	; '<'
		mov	byte_25FE9, 1
		cmp	word_26346, 1
		jnz	short loc_1FCD6
		les	bx, dword_23EF0
		assume es:nothing
		mov	ax, word_2C97A
		add	es:[bx+3Ah], ax
		cmp	byte_25FEA, 5
		jz	short loc_1FCD1
		call	sub_F2B4
		cmp	byte_25FEA, 6
		jz	short loc_1FCCB
		call	sub_16510
		jmp	loc_1FD51
; ---------------------------------------------------------------------------

loc_1FCCB:
		call	sub_1673E
		jmp	loc_1FD51
; ---------------------------------------------------------------------------

loc_1FCD1:
		call	sub_1673E
		jmp	short loc_1FD51
; ---------------------------------------------------------------------------

loc_1FCD6:
		cmp	word_26346, 1A0h
		jnz	short loc_1FD35
		call	sub_14AB1
		cmp	byte_25FEA, 6
		jnb	short loc_1FD0B
		xor	si, si
		jmp	short loc_1FD06
; ---------------------------------------------------------------------------

loc_1FCEE:
		mov	al, [si-3BD6h]
		mov	dl, byte_25FEA
		mov	dh, 0
		shl	dx, 3
		les	bx, dword_23EF0
		add	bx, dx
		mov	es:[bx+si+4Ch],	al
		inc	si

loc_1FD06:
		cmp	si, 8
		jl	short loc_1FCEE

loc_1FD0B:
		cmp	byte_25FEA, 5
		jnz	short loc_1FD19
		call	sub_E448
		jmp	short loc_1FD25
; ---------------------------------------------------------------------------

loc_1FD19:
		cmp	byte_25FEA, 6
		jnz	short loc_1FD25
		call	sub_E480

loc_1FD25:
		mov	fp_2CE88, offset sub_119B1
		kajacall	KAJA_SONG_FADE, 10
		jmp	short loc_1FD51
; ---------------------------------------------------------------------------

loc_1FD35:
		cmp	word_26346, 1E8h
		jnz	short loc_1FD51
		les	bx, dword_23EF0
		inc	byte ptr es:[bx+13h]
		mov	byte_25FE8, 2
		push	1
		call	frame_delay

loc_1FD51:
		mov	word ptr dword_2C922, 0C190h
		mov	word ptr dword_2C922+2,	0C190h

loc_1FD5D:
		pop	si
		pop	bp
		retn	2
sub_1FBBE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FD62	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26335+1
		mov	dx, word_26338
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		add	dx, 100h
		cmp	dx, 200h
		ja	short loc_1FD8B
		add	ax, 100h
		cmp	ax, 200h
		ja	short loc_1FD8B
		mov	byte_2CEC1, 1

loc_1FD8B:
		pop	bp
		retn
sub_1FD62	endp

seg003		ends

; ===========================================================================

; Segment type:	Pure code
seg004		segment	byte public 'CODE' use16
		assume cs:seg004
		;org 0Dh
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

include libs/BorlandC/ctor2[textc].asm
include libs/BorlandC/ctor3[textc].asm
include libs/BorlandC/strings[textc].asm
		dd 0, 0
		dw 0
		db 0
seg004		ends
