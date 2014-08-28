; (included from th05_main.asm, don't assemble directly)

; ===========================================================================

; Segment type:	Pure code
seg003		segment	byte public 'CODE' use16
		assume cs:seg003
		;org 8
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================


sub_15288	proc near
					; sub_17C04+25Ep
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
					; sub_15288+20j
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
					; sub_1607D+1A8p ...
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
					; sub_1535A:loc_153B6p	...
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
					; sub_152F2+23j
		inc	word_221C2
		stc
		retn
sub_152F2	endp


; =============== S U B	R O U T	I N E =======================================


sub_1531F	proc near
					; sub_1535A+44p ...
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

; ---------------------------------------------------------------------------
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
					; sub_1535A+5Fj ...
		mov	byte ptr [si], 2
		mov	al, 1
		jmp	loc_1575C
; ---------------------------------------------------------------------------

loc_15390:
					; DATA XREF: seg003:04E3o
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
					; DATA XREF: seg003:04E5o
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
					; DATA XREF: seg003:04E7o
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
					; DATA XREF: seg003:04EBo
		inc	dl

loc_153E2:
					; DATA XREF: seg003:04E9o
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
					; DATA XREF: seg003:04EFo
		inc	dl

loc_15422:
					; DATA XREF: seg003:04EDo
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
					; sub_1535A+E5j
		push	ax
		call	sub_152F2
		pop	ax
		jb	loc_15388
		mov	dl, [si+1Bh]
		add	[si+1Ah], dl
		jmp	loc_15748
; ---------------------------------------------------------------------------

loc_15459:
					; DATA XREF: seg003:04F1o
		or	cl, cl
		jnz	short loc_1547D
		mov	eax, [si+2]
		mov	[si+6],	eax
		jmp	short loc_1547D
; ---------------------------------------------------------------------------

loc_15467:
					; DATA XREF: seg003:04F3o
		or	cl, cl
		jnz	short loc_15470
		mov	word ptr [si+0Ah], 0

loc_15470:
		mov	ax, word_2CDFE
		mov	[si+0Ch], ax
		call	sub_152F2
		jb	loc_15388

loc_1547D:
					; sub_1535A+10Bj
		mov	ah, es:[di+1]
		mov	al, 2
		jmp	loc_15748
; ---------------------------------------------------------------------------

loc_15486:
					; DATA XREF: seg003:04F5o
		inc	dl

loc_15488:
					; DATA XREF: seg003:04F7o
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
		movsx	edx, word ptr [bx+4AEh]
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
					; DATA XREF: seg003:04F9o
		mov	ax, es:[di+1]
		mov	[si+1Ah], al
		mov	[si+16h], ah
		call	sub_15330
		mov	al, 3
		jmp	loc_15740
; ---------------------------------------------------------------------------
		db 0
		db 64h,	1Ah, 0EBh, 3, 0, 64h, 16h, 0E8h, 1Dh, 0FEh, 0B0h
		db 2, 0E9h, 39h, 2, 0E8h, 0CCh,	2, 88h,	44h, 1Ah, 0B0h
		db 1, 0E9h, 2Eh, 2, 0B2h, 2, 0EBh, 2, 0FEh, 0C2h, 89h
		db 16h,	80h, 35h, 0E8h,	26h, 0FEh, 8Bh,	44h, 2,	1, 6, 1Ch
		db 56h,	8Bh, 44h, 4, 1,	6, 1Eh,	56h, 6,	0FFh, 16h, 64h
		db 49h,	8Bh, 1Eh, 80h, 35h, 3, 0DBh, 0FFh, 97h,	0BCh, 8
		db 7, 0B0h, 1, 0E9h, 0FEh, 1, 0C6h, 44h, 23h, 0, 88h, 64h
; ---------------------------------------------------------------------------

loc_15548:
		sub	byte_24F6B, ah
		add	cl, [bx+si+2E44h]
		mov	[si+34h], ah
		mov	ax, es:[di+4]
		mov	[si+35h], al
		mov	[si+29h], ah
		mov	al, 6
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	[si+28h], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------
		mov	eax, es:[di+1]
		mov	[si+2Ah], eax
		mov	al, 5
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	[si+34h], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------
		db 0, 64h, 34h,	0EBh, 1Dh, 0E8h, 54h, 2, 88h, 44h, 34h
		db 0B0h, 1, 0E9h, 0B6h,	1, 88h,	64h, 29h, 0EBh,	0Dh, 88h
		db 64h,	35h, 0EBh, 8, 0, 64h, 35h, 0EBh, 3, 88h, 64h, 2Eh
; ---------------------------------------------------------------------------

loc_1559C:
					; sub_1535A+21Ej ...
		mov	al, 2
		jmp	loc_15740
; ---------------------------------------------------------------------------
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
					; sub_1535A+26Bj ...
		cmp	byte_25FEB, 0
		jnz	short loc_155E9
		mov	dl, 0FFh

loc_155E9:
		mov	[si+27h], dl
		jmp	short loc_1559C
; ---------------------------------------------------------------------------
		inc	dl
		mov	[si+23h], dl
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	[si+30h], ah
		mov	al, es:[di+2]
		mov	[si+31h], al

loc_15600:
		mov	al, 3
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	[si+32h], ah
		mov	al, es:[di+2]
		mov	[si+33h], al
		jmp	short loc_15600
; ---------------------------------------------------------------------------
		mov	[si+2Fh], ah
		jmp	short loc_1559C
; ---------------------------------------------------------------------------
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
		jmp	loc_1559C
; ---------------------------------------------------------------------------

loc_15633:
					; DATA XREF: seg003:04E1o
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
		mov	byte ptr [si+1Fh], 11h
		jmp	loc_15740
; ---------------------------------------------------------------------------
		or	byte ptr [si+1Fh], 1
		jmp	loc_15740
; ---------------------------------------------------------------------------
		or	byte ptr [si+1Fh], 10h
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	[si+1Ch], ah
		mov	al, es:[di+2]
		mov	[si+1Dh], al
		mov	al, 3
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	al, ah
		mov	ah, 0
		push	ax
		call	sub_14CEE

loc_15681:
		mov	al, 2
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	[si+17h], ah
		jmp	short loc_15681
; ---------------------------------------------------------------------------
		mov	[si+22h], dl

loc_1568E:
					; sub_1535A+347j
		mov	[si+23h], dl
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	byte ptr [si+22h], 1
		cmp	byte_25FEB, 3
		jnz	short loc_1568E
		inc	dl
		jmp	short loc_1568E
; ---------------------------------------------------------------------------
		inc	dl
		mov	[si+24h], dl
		jmp	loc_15740
; ---------------------------------------------------------------------------
		mov	eax, [si+2]
		mov	[si+6],	eax
		mov	eax, es:[di+1]
		mov	[si+2],	eax
		jmp	short loc_156D4
; ---------------------------------------------------------------------------
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
		db 0, 64h, 17h,	0B0h, 2, 0EBh, 5Fh, 88h, 64h, 1Ah, 26h
		db 8Ah,	45h, 2,	88h, 44h, 16h, 0E8h, 31h, 0FCh,	0B0h, 3
		db 0EBh, 4Eh, 88h, 64h,	1Ah, 26h, 8Ah, 45h, 2, 88h, 44h
		db 16h,	80h, 7Ch, 25h, 0, 75h, 0E9h, 0B0h, 80h,	2Ah, 0C4h
		db 88h,	44h, 1Ah, 0EBh,	0E0h, 88h, 64h,	16h, 0E8h, 0Eh
		db 0FCh, 0B0h, 2, 0EBh,	2Bh, 8Ah, 44h, 19h, 26h, 3Ah, 45h
		db 2, 72h, 8, 0C6h, 44h, 19h, 0, 0B0h, 3, 0EBh,	1Ah, 0FEh
		db 44h,	19h, 8Ah, 0C4h,	0B4h, 0, 29h, 44h, 14h,	0E9h, 31h
		db 0FCh, 0B0h, 3, 3Ah, 64h, 36h, 74h, 6, 26h, 2, 45h, 2
		db 74h,	0
; ---------------------------------------------------------------------------

loc_15740:
					; sub_1535A+205j ...
		mov	ah, 0
		add	[si+14h], ax
		jmp	loc_15364
; ---------------------------------------------------------------------------

loc_15748:
					; sub_1535A+67j ...
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
					; sub_1535A+33j
		pop	di
		pop	si
		retn
sub_1535A	endp

; ---------------------------------------------------------------------------
off_1575F	dw offset loc_15388	; DATA XREF: sub_1535A+29r
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
		db 77h,	2, 7Ch,	2, 87h,	2, 98h,	2, 0C2h, 2, 0E2h, 2, 0E7h
		db 2, 0F5h, 2, 0FAh, 2,	0FFh, 2, 0Ah, 3, 0Fh, 3, 14h, 3
		db 19h,	3, 21h,	3, 6Eh,	3, 70h,	3, 0FAh, 2, 76h, 3, 85h
		db 3, 0DAh, 3, 0E1h, 3,	0D3h, 3, 0E8h, 3, 0F7h,	3, 6, 4
		db 0Bh,	4, 14h,	4, 25h,	4, 23h,	4, 2Bh,	4, 3Eh,	4, 5Ah
		db 4, 61h, 4, 72h, 4, 8Bh, 4, 95h, 4, 95h, 4, 0B3h, 4
		db 0A9h, 4, 36h, 1, 92h, 2, 91h, 3, 96h, 2, 96h, 3, 90h

; =============== S U B	R O U T	I N E =======================================


sub_157D6	proc near
					; sub_18017+67p ...
		mov	bx, word_24062
		mov	ax, [bx+3582h]
		inc	byte ptr word_24062
		retn
sub_157D6	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_157E4	proc near
					; sub_16BD9+26p ...
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
					; sub_16E29+8p	...
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
					; sub_15814+4Cj
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
					; sub_15814+53j
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
					; sub_173AC+5Bp ...
		mov	bl, byte_24065
		inc	byte_24065
		cmp	bl, 4Fh	; 'O'
		jb	short loc_15880
		mov	byte_24065, 0

loc_15880:
		xor	bh, bh
		add	bx, 0C8h ; 'È'
		jmp	short loc_1589C
sub_1586E	endp


; =============== S U B	R O U T	I N E =======================================


sub_15888	proc near
					; sub_17C04+345p
		mov	bl, byte_24064
		mov	bh, 0
		inc	byte_24064
		cmp	bl, 0C7h ; 'Ç'
		jb	short loc_1589C
		mov	byte_24064, 0

loc_1589C:
					; sub_15888+Dj
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
		push	large 0C00018h
		call	sub_1597C
		pop	bp
		retf
sub_158CC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_158E2	proc near
					; sub_1591A+43p ...

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
					; sub_12842+83P ...

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
					; seg003:2F29p	...

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
					; sub_17687+54p ...
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
		mov	al, 0C0h ; 'À'
		out	7Ch, al
		retn
; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15A24	proc near
					; sub_1535A+2CFp ...

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
		call	sub_1F3A
		add	al, [bp+arg_0]
		pop	bp
		retn	6
sub_15A24	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_15A42	proc near
					; sub_174C7+Bp	...
		shr	al, 1
		mov	cl, al
		mul	byte_25FEC
		shr	ax, 5
		add	al, cl
		cmp	al, 80h	; '€'
		jbe	short loc_15A55
		mov	al, 80h	; '€'

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
					; sub_16AB0+64p ...
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
					; sub_1B0A4+7Dp ...
		mov	byte_25346, 1
		call	sub_15A5C
		mov	byte_25346, 0
		retn
sub_15A8E	endp


; =============== S U B	R O U T	I N E =======================================


sub_15A9C	proc near
					; seg003:loc_1BE4Ep ...
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
		mov	bl, byte_26000
		xor	bh, bh
		cmp	bx, 0Fh
		mov	di, 1
		ja	loc_15BF8
		xor	di, di
		add	bx, bx
		mov	ax, cs:[bx+996h]
		mov	bl, byte ptr dword_26002
		mov	bh, byte ptr dword_26002+2
		or	bl, bl
		jnz	short loc_15ADD
		inc	bl

loc_15ADD:
		jmp	ax
; ---------------------------------------------------------------------------
		inc	di
		jmp	loc_15BE2
; ---------------------------------------------------------------------------
		inc	di
		jmp	loc_15BF8
; ---------------------------------------------------------------------------
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
		mov	al, bl
		dec	al
		cmp	al, ch
		ja	short loc_15B21
		inc	di

loc_15B21:
					; sub_15AAA+74j
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
					; sub_15AAA+B8j
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
					; sub_15AAA+9Aj ...
		cmp	byte_26000, 2
		jz	loc_15BF8
		cmp	byte_26000, 8
		jz	loc_15BF8
		jmp	short loc_15BE2
; ---------------------------------------------------------------------------
		mov	al, bl
		dec	al
		cmp	al, ch
		ja	short loc_15B83
		inc	di

loc_15B83:
					; sub_15AAA+6Aj ...
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
		mov	si, word_24062
		mov	al, [si+3582h]
		inc	byte ptr word_24062
		and	al, 1Fh
		add	cl, al
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
		mov	al, byte ptr dword_26002+3
		mul	ch
		add	cl, al
		mov	al, bh
		dec	al
		cmp	al, ch
		jle	short loc_15BDA
		cmp	cl, 0A0h ; ' '
		jb	short loc_15BDB

loc_15BDA:
		inc	di

loc_15BDB:
		cmp	byte_26000, 6
		jz	short loc_15BF8

loc_15BE2:
					; sub_15AAA+CEj ...
		mov	byte ptr word_25349+1, cl
		push	word ptr dword_25FFC
		push	word ptr dword_25FFC+2
		push	si
		call	sub_15A24
		mov	cl, byte ptr word_25349+1
		mov	si, ax

loc_15BF8:
					; sub_15AAA+3Aj ...
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
		db 63h,	8, 5Fh,	8, 98h,	8, 98h,	8, 0FAh, 8, 0FAh, 8, 46h
		db 9, 46h, 9, 67h, 8, 67h, 8, 67h, 8, 67h, 8, 2Dh, 9, 1Dh
		db 9, 63h, 8, 5Fh, 8

; =============== S U B	R O U T	I N E =======================================


sub_15C36	proc near
		cmp	byte_2C979, 0
		jz	short loc_15C47
		cmp	byte_2C979, 11h
		jnb	short loc_15C47

loc_15C44:
					; sub_15C36+20j ...
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
		add	ax, 40h	; '@'
		cmp	ax, 80h	; '€'
		ja	short loc_15C81
		sub	dx, word ptr dword_2CEA0+2
		add	dx, 40h	; '@'
		cmp	dx, 80h	; '€'
		ja	short loc_15C81
		mov	byte_2CEC1, 1

loc_15C81:
					; sub_15C36+44j
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
					; sub_15A70+10p
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
		mov	byte ptr word_25FFA, 0FEh ; 'þ'

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
		mov	di, 0B4h ; '´'
		jmp	short loc_15D03
; ---------------------------------------------------------------------------

loc_15CFD:
		mov	si, 8FA6h
		mov	di, 0DCh ; 'Ü'

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
		cmp	byte ptr word_26006+1, 40h ; '@'
		jb	short loc_15D2F
		cmp	byte_2C979, 0
		jz	short loc_15D38

loc_15D2F:
		test	byte ptr word_25FFA, 10h
		jnz	short loc_15D38
		xor	al, al

loc_15D38:
		mov	cs:byte_15D55, dl
		mov	cs:byte_15D68, al
		mov	byte_25348, 0
		jmp	short $+2

loc_15D48:
		cmp	byte ptr [si], 0
		jnz	loc_15DD7
		mov	byte ptr [si], 1
; ---------------------------------------------------------------------------
		db 0C6h, 44h, 12h
byte_15D55	db 7Bh			; DATA XREF: seg003:loc_15D38w
		db 66h,	0A1h, 1Ch, 56h,	66h, 89h, 44h, 2, 80h, 3Eh, 0E0h
		db 17h,	0, 75h,	13h, 0C6h, 44h,	13h
byte_15D68	db 7Bh			; DATA XREF: seg003:0ABDw
; ---------------------------------------------------------------------------
		mov	byte ptr [si+16h], 20h ; ' '
		mov	al, 48h	; 'H'
		sub	al, byte ptr word_26006+1
		mov	[si+17h], al
		jmp	short loc_15D95
; ---------------------------------------------------------------------------
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

; ---------------------------------------------------------------------------
		movzx	bx, byte_26000
		cmp	bl, 2
		jb	short locret_15E1C
		cmp	bl, 0Dh
		ja	short locret_15E1C
		sub	bl, 2
		mov	cx, 0B9Eh
		jmp	short loc_15E44
; ---------------------------------------------------------------------------
		cmp	al, 3
		jb	short locret_15E1C
		sub	byte ptr dword_26002, 2
		retn
; ---------------------------------------------------------------------------
		shr	dh, 2
		sub	byte ptr dword_26002+3,	dh
		cmp	ah, 2
		jb	short locret_15E1C
		dec	byte ptr dword_26002+2
		retn
; ---------------------------------------------------------------------------
		shr	byte ptr dword_26002, 1

locret_15E1C:
		retn
; ---------------------------------------------------------------------------
		nop
		jge	short loc_15E2B
		cbw
		or	ax, [bx+7D0Bh]
		or	bx, [bx+si-67F5h]
		or	cx, [bx]

loc_15E2B:
		mov	dh, 1Eh
		and	[bp-80h], dl
		sti
		add	[bp+1Fh], si
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
		add	byte_26000, 6
		mov	word ptr dword_26002+2,	602h
		retn
; ---------------------------------------------------------------------------
		shr	dh, 1
		add	byte ptr dword_26002+3,	dh
		retn
; ---------------------------------------------------------------------------
		shr	al, 2
		cmp	al, 6
		jbe	short loc_15E6F
		mov	al, 6

loc_15E6F:
		add	byte ptr dword_26002, al

locret_15E73:
		retn
; ---------------------------------------------------------------------------
		shr	al, 1
		jmp	short loc_15E6F
; ---------------------------------------------------------------------------
		db 0E6h, 0Bh, 0DFh, 0Bh, 0DFh, 0Bh, 0E6h, 0Bh, 0F4h, 0Bh
		db 0Fh,	0B6h, 1Eh, 20h,	56h, 80h, 0FBh,	0Dh, 77h, 32h
		db 0B9h, 40h, 0Ch, 0EBh, 0B3h, 80h, 6, 20h, 56h, 2, 0C7h
		db 6, 22h, 56h,	3, 6, 0C3h, 0D0h, 0EEh,	0, 36h,	25h, 56h
		db 0FEh, 6, 24h, 56h, 0C3h, 80h, 6, 22h, 56h, 2, 0C3h
		db 32h,	0E4h, 0B2h, 3, 0F6h, 0F2h, 3Ch,	0Ch, 76h, 2, 0B0h
		db 0Ch,	0, 6, 22h, 56h,	0C3h, 90h, 11h,	0Ch, 28h, 0Ch
		db 2Eh,	0Ch, 1Dh, 0Ch, 28h, 0Ch, 2Eh, 0Ch, 3Ah,	0Ch, 0A0h
		db 20h,	56h, 24h, 0FEh,	3Ch, 6,	75h, 1Bh, 0A0h,	0Ch, 56h
		db 3Ch,	26h, 72h, 5, 0FEh, 6, 24h, 56h,	0C3h, 3Ch, 18h
		db 77h,	0Bh, 80h, 3Eh, 24h, 56h, 2, 72h, 4, 0FEh, 0Eh
		db 24h,	56h, 0C3h, 90h,	0E8h, 0D7h, 0FFh, 0E8h,	0ECh, 0FEh
		db 0C3h, 90h, 0E8h, 0CFh, 0FFh,	0C3h, 0E8h, 0CBh, 0FFh
		db 0E8h, 24h, 0FFh, 0C3h, 90h, 0E8h, 0C3h, 0FFh, 0E8h
		db 74h,	0FFh, 0C3h, 90h, 0C8h, 4, 2 dup(0), 56h, 57h, 0C4h
		db 1Eh,	6Ah, 35h, 26h, 8Bh, 7Fh, 1, 26h, 8Bh, 47h, 3, 89h
		db 46h,	0FCh, 0BEh, 96h, 92h, 0C7h, 46h, 0FEh, 2 dup(0)
		db 0E9h, 0D0h, 0, 80h, 3Ch, 0, 0Fh, 85h, 0C3h, 0, 0C6h
		db 4, 3, 0C6h, 44h, 1, 0, 0C6h,	44h, 18h, 0, 0C6h, 44h
		db 19h,	0, 0C7h, 44h, 14h, 2 dup(0), 0C4h, 1Eh,	6Ah, 35h
		db 26h,	8Ah, 7,	0B4h, 0, 3, 0C0h, 8Bh, 0D8h, 8Bh, 87h
		db 2Ah,	35h, 89h, 44h, 12h, 81h, 0FFh, 70h, 3Eh, 75h, 8
		db 68h,	0, 18h,	0E8h, 8Fh, 0F8h, 8Bh, 0F8h, 89h, 7Ch, 2
		db 81h,	0FFh, 0, 0Ch, 7Dh, 4, 0B0h, 1, 0EBh, 2,	0B0h, 0
		db 88h,	44h, 25h, 81h, 7Eh, 0FCh, 70h, 3Eh, 75h, 9, 68h
		db 0, 17h, 0E8h, 6Eh, 0F8h, 89h, 46h, 0FCh, 8Bh, 46h, 0FCh
		db 89h,	44h, 4,	0C4h, 1Eh, 6Ah,	35h, 26h, 8Ah, 47h, 5
		db 88h,	44h, 20h, 26h, 8Ah, 47h, 6, 88h, 44h, 36h, 0C6h
		db 44h,	21h, 0,	80h, 3Eh, 0Bh, 56h, 3, 75h, 5, 0B8h, 1
		db 0, 0EBh, 2, 33h, 0C0h, 88h, 44h, 23h, 0C6h, 44h, 1Fh
		db 0, 0C6h, 44h, 1Ch, 1, 0C6h, 44h, 1Dh, 4, 0C6h, 44h
		db 1Eh,	0, 0C6h, 44h, 22h, 0, 0C6h, 44h, 24h, 0, 0E8h
		db 0FFh, 0F7h, 88h, 44h, 26h, 0C6h, 44h, 27h, 80h, 0C6h
		db 44h,	2Eh, 0Fh, 0C6h,	44h, 28h, 0, 0C6h, 44h,	35h, 2Ah
		db 0C7h, 44h, 2Ah, 2 dup(0), 0C7h, 44h,	2Ch, 2 dup(0)
		db 0C6h, 44h, 29h, 0, 0EBh, 0Eh, 0FFh, 46h, 0FEh, 83h
		db 0C6h, 40h, 83h, 7Eh,	0FEh, 20h, 0Fh,	8Ch, 28h, 0FFh
		db 5Fh,	5Eh, 0C9h, 0C3h, 0C8h, 2, 2 dup(0), 90h, 0Eh, 0E8h
		db 0Dh,	13h, 0C4h, 1Eh,	6Ah, 35h, 26h, 8Bh, 7, 3Bh, 6
		db 0, 56h, 75h,	41h, 83h, 6, 6Ah, 35h, 2, 0C4h,	1Eh, 6Ah
		db 35h,	26h, 8Ah, 7, 88h, 46h, 2 dup(0FFh), 6, 6Ah, 35h
		db 80h,	3Eh, 0ACh, 0BFh, 0, 75h, 3, 0E8h, 0D1h,	0FEh, 83h
		db 6, 6Ah, 35h,	8, 0FEh, 4Eh, 0FFh, 80h, 7Eh, 0FFh, 0
		db 77h,	0E8h, 0C4h, 1Eh, 6Ah, 35h, 26h,	83h, 3Fh, 0, 75h
		db 0Ch,	0C7h, 6, 48h, 0BFh
		dw seg seg001
; ---------------------------------------------------------------------------
		mov	word ptr dword_2C926, 1242h
		leave
		retf

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
		mov	word_2CED8, 0C0h ; 'À'
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
		cmp	byte ptr [si], 80h ; '€'
		jnb	loc_16221
		call	sub_1535A
		cmp	byte ptr [si+24h], 0
		jz	short loc_160F2
		mov	ax, [si+2]
		sub	ax, word ptr dword_2CEA0
		add	ax, 0C0h ; 'À'
		cmp	ax, 180h
		jnb	short loc_160F2
		mov	ax, [si+4]
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 0C0h ; 'À'
		cmp	ax, 180h
		jnb	short loc_160F2
		mov	byte_2CEC1, 1
		jmp	short loc_16161
; ---------------------------------------------------------------------------

loc_160F2:
					; sub_1607D+5Dj ...
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
					; sub_1607D+D8j
		mov	byte ptr [si], 80h ; '€'
		mov	byte ptr [si+1Ch], 1
		mov	byte ptr [si+22h], 0
		mov	byte ptr [si+24h], 0
		mov	word ptr [si+0Ah], 0
		mov	word ptr [si+0Ch], 0
		cmp	byte ptr [si+20h], 0FEh	; 'þ'
		jz	short loc_1618C
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	word ptr [si+20h]
		call	sub_16D84

loc_1618C:
		push	3
		call	sub_14CEE
		movzx	eax, word ptr [si+10h]
		add	dword_2CE1A, eax
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	large 400007h
		nop
		push	cs
		call	near ptr sub_1591A
		inc	word_221C2
		inc	word_221C4
		jmp	loc_1624D
; ---------------------------------------------------------------------------

loc_161B9:
		mov	byte ptr [si+21h], 1
		jmp	short loc_161C6
; ---------------------------------------------------------------------------

loc_161BF:
		push	0Ah
		call	sub_14CEE

loc_161C6:
					; sub_1607D+81j ...
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
		call	word_25344
		call	sub_15A5C

loc_1621C:
					; sub_1607D+158j ...
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
					; sub_1607D+39j ...
		inc	di
		add	si, 40h	; '@'

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
		mov	dl, 90h	; ''
		sub	dl, al
		mov	[bp+var_2], dl

loc_16279:
		mov	al, byte_25FEA
		shl	al, 4
		mov	dl, [bp+var_2]
		sub	dl, al
		mov	[bp+var_2], dl
		cmp	[bp+var_2], 90h	; ''
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
		cmp	byte_2CEC3, 80h	; '€'
		jnb	short loc_162B9
		inc	byte_2CEC3
		call	sub_1059D

loc_162B9:
					; sub_1607D+22Aj ...
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

loc_16316:				; DATA XREF: seg003:off_16344o
		mov	byte ptr [si+0Fh], 20h ; ' '
		jmp	short loc_16338
; ---------------------------------------------------------------------------

loc_1631C:
					; DATA XREF: seg003:10C6o
		mov	byte ptr [si+0Fh], 0E0h	; 'à'
		jmp	short loc_16338
; ---------------------------------------------------------------------------

loc_16322:
					; DATA XREF: seg003:10C8o
		mov	word ptr [si+0Ah], 0D0h	; 'Ð'
		mov	word ptr [si+0Ch], 70h ; 'p'
		jmp	short loc_16338
; ---------------------------------------------------------------------------

loc_1632E:
					; DATA XREF: seg003:10CAo
		mov	word ptr [si+0Ah], 70h ; 'p'
		mov	word ptr [si+0Ch], 0D0h	; 'Ð'

loc_16338:
					; sub_162CC+4Ej ...
		push	0Fh
		call	sub_14CEE
		pop	si
		pop	bp
		retn	2
sub_162CC	endp

; ---------------------------------------------------------------------------
off_16344	dw offset loc_16316	; DATA XREF: sub_162CC+45r
		dw offset loc_1631C
		dw offset loc_16322
		dw offset loc_1632E
		dw offset loc_15748
		dw 0
		mov	ax, word_26335+1
		mov	[bp-2],	ax
		mov	ax, word_26338
		mov	[bp-4],	ax
		mov	eax, dword_2634E
		mov	dword ptr word_26335+1,	eax
		push	word ptr [bp+4]
		call	sub_162CC
		mov	ax, [bp-2]
		mov	word_26335+1, ax
		mov	ax, [bp-4]
		mov	word_26338, ax
		leave
		retn	2

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1637A	proc near
					; sub_1FBBE+38p
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
		mov	word ptr [si+0Ah], 0C0h	; 'À'
		mov	word ptr [si+0Ch], 0C0h	; 'À'
		mov	byte ptr [si+0Fh], 0
		push	0Ch
		call	sub_14CEE
		pop	si
		pop	bp
		retn
sub_1637A	endp

; ---------------------------------------------------------------------------
		enter	4, 0
		mov	ax, word_26335+1
		mov	[bp-2],	ax
		mov	ax, word_26338
		mov	[bp-4],	ax
		mov	eax, dword_2634E
		mov	dword ptr word_26335+1,	eax
		call	sub_1637A
		mov	ax, [bp-2]
		mov	word_26335+1, ax
		mov	ax, [bp-4]
		mov	word_26338, ax
		leave
		retn

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_163DF	proc near
					; sub_16438+89p ...

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
		mov	ax, 41h	; 'A'
		jmp	short loc_1641B
; ---------------------------------------------------------------------------

loc_16418:
		mov	ax, 81h	; ''

loc_1641B:
		mov	[bp+var_2], ax
		push	6
		push	[bp+arg_8]
		push	ds
		mov	bx, [bp+arg_6]
		add	bx, bx
		push	word ptr [bx+1896h]
		push	ax
		call	sub_2598
		pop	si
		leave
		retn	0Ah
sub_163DF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16438	proc near
					; sub_1673E+222p

arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		cmp	byte ptr word_2634A+1, 0
		jnz	short loc_1644D
		push	large 140000h
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
		push	large 120001h
		push	3
		jmp	short loc_16484
; ---------------------------------------------------------------------------

loc_16472:
		push	large 120002h
		push	5
		jmp	short loc_16484
; ---------------------------------------------------------------------------

loc_1647C:
		push	large 120003h
		push	7

loc_16484:
					; sub_16438+42j
		push	large [bp+arg_0]
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
		push	large 130004h
		push	8
		jmp	short loc_164BD
; ---------------------------------------------------------------------------

loc_164AB:
		push	large 130005h
		push	6
		jmp	short loc_164BD
; ---------------------------------------------------------------------------

loc_164B5:
		push	large 130006h
		push	4

loc_164BD:
					; sub_16438+7Bj
		push	large [bp+arg_0]
		call	sub_163DF

loc_164C4:
		mov	al, byte_25FEB
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	short loc_16504
		add	bx, bx
		jmp	cs:off_16508[bx]

loc_164D7:				; DATA XREF: seg003:off_16508o
		push	large 140007h
		push	5
		jmp	short loc_164FD
; ---------------------------------------------------------------------------

loc_164E1:
					; DATA XREF: seg003:128Ao
		push	large 140008h
		push	0Ah
		jmp	short loc_164FD
; ---------------------------------------------------------------------------

loc_164EB:
					; DATA XREF: seg003:128Co
		push	large 140009h
		push	0Ch
		jmp	short loc_164FD
; ---------------------------------------------------------------------------

loc_164F5:
					; DATA XREF: seg003:128Eo
		push	large 14000Ah
		push	0Eh

loc_164FD:
					; sub_16438+A7j ...
		push	large [bp+arg_0]
		call	sub_163DF

loc_16504:
		pop	bp
		retn	4
sub_16438	endp

; ---------------------------------------------------------------------------
off_16508	dw offset loc_164D7	; DATA XREF: sub_16438+9Ar
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
					; sub_16510+36j
		xor	ax, ax

loc_1654F:
		mov	[bp+var_6], al
		les	bx, dword_23EF0
		mov	al, es:[bx+1Ch]
		mov	byte_22275, al
		mov	PaletteTone, 3Ch	; '<'
		call	far ptr	palette_show
		push	large 140004h
		push	ds
		push	offset unk_222A0
		push	0E1h ; 'á'
		call	sub_1DBE
		push	large 60008h
		push	ds
		push	BONUS_STAGE
		push	0E1h ; 'á'
		call	sub_2598
		push	large 6000Ah
		push	ds
		push	BONUS_DREAM
		push	0E1h ; 'á'
		call	sub_2598
		push	large 6000Ch
		push	ds
		push	GRAZEX50
		push	0E1h ; 'á'
		call	sub_2598
		push	large 6000Eh
		push	ds
		push	POINT_ITEMS
		push	0E1h ; 'á'
		call	sub_2598
		cmp	[bp+var_5], 0
		jz	short loc_165DF
		push	large 60010h
		push	ds
		push	BONUS_NOMISS
		push	0A1h ; '¡'
		call	sub_2598

loc_165DF:
		cmp	[bp+var_6], 0
		jz	short loc_165F8
		push	large 60011h
		push	ds
		push	BONUS_NOBOMB
		push	0A1h ; '¡'
		call	sub_2598

loc_165F8:
		push	large 60015h
		push	ds
		push	BONUS_TOTAL
		push	0E1h ; 'á'
		call	sub_2598
		mov	al, byte_25FEA
		mov	ah, 0
		imul	ax, 64h
		add	ax, 64h	; 'd'
		mov	si, ax
		movzx	eax, si
		mov	[bp+var_4], eax
		push	large 220008h
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E
		mov	al, byte_2CEC3
		mov	ah, 0
		imul	ax, 0Ah
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	large 22000Ah
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E
		mov	ax, word_2C97A
		imul	ax, 5
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	large 22000Ch
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E
		mov	si, word_2CEC6
		movzx	eax, si
		imul	eax, [bp+var_4]
		mov	[bp+var_4], eax
		push	large 28000Eh
		push	si
		push	0E1h ; 'á'
		nop
		push	cs
		call	near ptr sub_1F9F4
		mov	al, byte_25FEA
		mov	ah, 0
		imul	ax, 1388h
		add	ax, 2710h
		mov	si, ax
		cmp	[bp+var_5], 0
		jz	short loc_166B2
		movzx	eax, si
		add	[bp+var_4], eax
		push	large 220010h
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E

loc_166B2:
		cmp	[bp+var_6], 0
		jz	short loc_166CD
		movzx	eax, si
		add	[bp+var_4], eax
		push	large 220011h
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E

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
					; sub_16510+1D7j
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
					; sub_16510+202j
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_16438
		push	large 220015h
		push	large [bp+var_4]
		nop
		push	cs
		call	near ptr sub_1FA0E
		mov	eax, [bp+var_4]
		add	dword_2CE1A, eax
		pop	si
		leave
		retn
sub_16510	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1673E	proc near
					; sub_1FBBE:loc_1FCD1p

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
					; sub_1673E+36j
		xor	ax, ax

loc_1677D:
		mov	[bp+var_A], al
		les	bx, dword_23EF0
		mov	al, es:[bx+1Ch]
		mov	byte_22275, al
		mov	PaletteTone, 3Ch	; '<'
		call	far ptr	palette_show
		mov	byte_226C4, 0Ah
		push	large 130004h
		push	ds
		push	offset a_Abcd	; "\\]^_`abcd"
		push	0E1h ; 'á'
		call	sub_1DBE
		push	large 60006h
		push	ds
		push	ALL_CLEAR
		push	0E1h ; 'á'
		call	sub_2598
		push	large 60008h
		push	ds
		push	BONUS_DREAM
		push	0E1h ; 'á'
		call	sub_2598
		push	large 6000Ah
		push	ds
		push	GRAZEX50
		push	0E1h ; 'á'
		call	sub_2598
		push	large 6000Ch
		push	ds
		push	PLAYER_REM
		push	0E1h ; 'á'
		call	sub_2598
		push	large 6000Eh
		push	ds
		push	POINT_ITEMS
		push	0E1h ; 'á'
		call	sub_2598
		cmp	[bp+var_9], 0
		jz	short loc_16825
		push	large 60010h
		push	ds
		push	BONUS_NOMISS
		push	0A1h ; '¡'
		call	sub_2598

loc_16825:
		cmp	[bp+var_A], 0
		jz	short loc_1683E
		push	large 60011h
		push	ds
		push	BONUS_NOBOMB
		push	0A1h ; '¡'
		call	sub_2598

loc_1683E:
		push	large 60012h
		push	ds
		push	POINT_TOTAL
		push	0A1h ; '¡'
		call	sub_2598
		push	large 60015h
		push	ds
		push	BONUS_TOTAL
		push	0E1h ; 'á'
		call	sub_2598
		mov	si, 3E8h
		movzx	eax, si
		mov	[bp+var_4], eax
		push	large 220006h
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E
		mov	al, byte_2CEC3
		mov	ah, 0
		imul	ax, 0Ah
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	large 220008h
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E
		mov	ax, word_2C97A
		imul	ax, 5
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	large 22000Ah
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E
		mov	al, byte_25350
		mov	ah, 0
		imul	ax, 3E8h
		add	ax, 0FC18h
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	large 22000Ch
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E
		mov	si, word_2CEC6
		movzx	eax, si
		imul	eax, [bp+var_4]
		mov	[bp+var_4], eax
		push	large 28000Eh
		push	si
		push	0E1h ; 'á'
		nop
		push	cs
		call	near ptr sub_1F9F4
		mov	[bp+var_8], 0C350h
		cmp	[bp+var_9], 0
		jz	short loc_1691E
		mov	eax, [bp+var_8]
		add	[bp+var_4], eax
		push	large 220010h
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E

loc_1691E:
		cmp	[bp+var_A], 0
		jz	short loc_16939
		mov	eax, [bp+var_8]
		add	[bp+var_4], eax
		push	large 220011h
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E

loc_16939:
		movzx	eax, word_22648
		imul	eax, 0FAh
		mov	[bp+var_8], eax
		add	[bp+var_4], eax
		push	large 220012h
		push	eax
		nop
		push	cs
		call	near ptr sub_1FA0E
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_16438
		push	large 220015h
		push	large [bp+var_4]
		nop
		push	cs
		call	near ptr sub_1FA0E
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
					; seg003:34BEp	...
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
					; sub_1833B+17p ...

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
		cmp	byte ptr word_25FFA, 0FEh ; 'þ'
		jnb	short loc_16B0F
		call	sub_15A5C
		jmp	short loc_16B17
; ---------------------------------------------------------------------------

loc_16B0F:
		mov	byte ptr word_25FFA, 0
		call	sub_15A70

loc_16B17:
					; sub_16AB0+19j ...
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
					; sub_16B24+10j ...
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
		add	ax, 0C0h ; 'À'
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
					; seg003:3546p	...

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		or	si, si
		jnz	short loc_16C35
		cmp	word_26335+1, 900h
		jge	short loc_16BF5
		push	60h ; '`'
		call	sub_157FA
		sub	al, 30h	; '0'
		jmp	short loc_16C09
; ---------------------------------------------------------------------------

loc_16BF5:
		cmp	word_26335+1, 0F00h
		jle	short loc_16C06
		push	60h ; '`'
		call	sub_157E4
		add	al, 30h	; '0'
		jmp	short loc_16C09
; ---------------------------------------------------------------------------

loc_16C06:
		call	sub_157D6

loc_16C09:
					; sub_16BD9+2Bj
		mov	byte ptr word_2634A, al
		cmp	byte_2C974, 1
		jnz	short loc_16C1A
		cmp	byte ptr word_2634A, 80h ; '€'
		jb	short loc_16C28

loc_16C1A:
		cmp	byte_2C974, 2
		jnz	short loc_16C30
		cmp	byte ptr word_2634A, 80h ; '€'
		jb	short loc_16C30

loc_16C28:
		mov	al, byte ptr word_2634A
		neg	al
		mov	byte ptr word_2634A, al

loc_16C30:
					; sub_16BD9+4Dj
		mov	byte_2C974, 0

loc_16C35:
		or	si, si
		jl	loc_16CC5
		push	595Eh
		push	word_2634A
		mov	ax, si
		add	ax, ax
		mov	dx, 40h	; '@'
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
					; sub_16BD9+B3j
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
					; sub_16BD9+E0j
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
		call	sub_23C6
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
					; sub_17C04+37Fp ...

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
					; sub_16D84+16j
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
		mov	bx, 40h	; '@'
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
					; sub_16D84+94j
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
					; sub_16E29+37j
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
		mov	word_2CE8A, 6FDAh
		push	7
		call	sub_14CEE

loc_16F52:
					; sub_16F05+24j
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

loc_16F76:				; DATA XREF: seg003:off_171BAo
		cmp	byte_2CEBE, 80h	; '€'
		jnb	short loc_16FAA
		cmp	byte_2CEBE, 7Fh	; ''
		jnz	short loc_16F9B
		mov	byte_2CE87, 3
		mov	word_2CE8A, 6FDAh
		cmp	byte_2C979, 14h
		jnb	short loc_16F9B
		mov	byte_2C979, 14h

loc_16F9B:
					; sub_16F54+40j
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
		cmp	byte_2CEC3, 80h	; '€'
		jnb	short loc_16FD1
		inc	byte_2CEC3

loc_16FD1:
					; sub_16F54+70j ...
		mov	bx, word_22642
		add	bx, bx
		mov	si, [bx+1BFCh]
		call	sub_1059D
		jmp	loc_17174
; ---------------------------------------------------------------------------

loc_16FE3:
					; DATA XREF: seg003:1F3Co
		cmp	byte_2CEC3, 80h	; '€'
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
		cmp	byte_2CEC3, 80h	; '€'
		jbe	short loc_1703E
		mov	byte_2CEC3, 80h	; '€'

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
					; DATA XREF: seg003:1F3Eo
		cmp	byte_2CEC3, 80h	; '€'
		jb	short loc_1708F
		mov	si, 3200h
		mov	[bp+var_3], 1
		jmp	short loc_17097
; ---------------------------------------------------------------------------

loc_1708F:
		mov	si, 1
		mov	byte_2CEC3, 80h	; '€'

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
					; DATA XREF: seg003:1F40o
		cmp	byte_2CEBE, 80h	; '€'
		jnb	short loc_170F2
		mov	al, byte_2CEBE
		add	al, 0Ah
		mov	byte_2CEBE, al
		cmp	byte_2CEBE, 80h	; '€'
		jb	short loc_170E7
		mov	byte_2CEBE, 80h	; '€'
		mov	byte_2CE87, 3
		mov	word_2CE8A, 6FDAh
		cmp	byte_2C979, 14h
		jnb	short loc_170E7
		mov	byte_2C979, 14h

loc_170E7:
					; sub_16F54+18Cj
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
					; DATA XREF: seg003:1F42o
		inc	byte_25351
		mov	si, 64h	; 'd'
		call	sub_104BB
		jmp	short loc_17174
; ---------------------------------------------------------------------------

loc_1712C:
					; DATA XREF: seg003:1F44o
		push	3
		call	sub_E720
		inc	byte_25350
		call	sub_10407
		push	7
		call	sub_14CEE
		mov	byte_2CE87, 1
		mov	word_2CE8A, 6FDAh
		jmp	short loc_17171
; ---------------------------------------------------------------------------

loc_17150:
					; DATA XREF: seg003:1F46o
		cmp	byte_2C979, 14h
		jnb	short loc_1715C
		mov	byte_2C979, 14h

loc_1715C:
		mov	byte_2CE87, 3
		mov	word_2CE8A, 6FDAh
		mov	byte_2CEBE, 80h	; '€'
		call	sub_E4FC

loc_17171:
		mov	si, 64h	; 'd'

loc_17174:
					; sub_16F54+53j ...
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
		add	al, 0E0h ; 'à'
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
off_171BA	dw offset loc_16F76	; DATA XREF: sub_16F54+1Dr
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
		cmp	byte_2CEC3, 80h	; '€'
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
					; sub_171C8+22j ...
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
		call	sub_1F3A
		mov	[bp+var_1], al
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [bp+var_1]
		push	0A0h ; ' '
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
					; sub_1720E+5Aj
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
					; sub_1720E+7Aj
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
		push	0Bh
		call	sub_14CEE
		mov	byte ptr [si], 2
		jmp	short loc_172E8
; ---------------------------------------------------------------------------

loc_172E5:
					; sub_1720E+B5j ...
		inc	word ptr [si+0Ch]

loc_172E8:
					; sub_1720E+1Dj ...
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
					; sub_17486+3Cp
		push	bp
		mov	bp, sp
		mov	word_2C98E, 1240h
		mov	word_2C994, 1240h
		mov	word ptr dword_2C990+2,	seg seg001
		mov	word ptr dword_2C990, 1242h
		mov	word_2632E, 0
		pop	bp
		retf
sub_172FF	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		mov	ax, word_2632C
		cmp	ax, word_25FE0
		jnz	short loc_17352
		mov	word_2C98E, 2222h
		mov	ax, word_2C99A
		mov	word_2C994, ax
		mov	eax, dword_2C996
		mov	dword_2C990, eax
		mov	byte_26331, 0
		mov	word_26332, 0
		mov	byte_2C98C, 1

loc_17352:
		pop	bp
		retf

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
		mov	si, 80h	; '€'
		jmp	short loc_17389
; ---------------------------------------------------------------------------

loc_1736E:
		movsx	eax, di
		shl	eax, 7
		movsx	ebx, [bp+arg_0]
		cdq
		idiv	ebx
		mov	si, ax
		cmp	si, 80h	; '€'
		jge	short loc_17389
		inc	si

loc_17389:
					; sub_17354+18j ...
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
					; sub_173AC+48j
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
					; sub_17416+49j
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
					; seg003:loc_18B91p ...
		push	bp
		mov	bp, sp
		cmp	byte_26331, 0FEh ; 'þ'
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
		push	cs
		call	near ptr sub_172FF

loc_174C5:
					; sub_17486+32j
		pop	bp
		retn
sub_17486	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_174C7	proc near
					; sub_18EBD+77p ...

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
		push	80h ; '€'
		mov	al, byte_26312
		mov	ah, 0
		push	ax
		call	sub_14E6C
		push	5
		call	sub_14CEE
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
		push	5
		call	sub_14CEE

loc_1759F:
		pop	si
		pop	bp
		retn	2
sub_17548	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_175A4	proc near
					; sub_18590+39p ...

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
		push	5
		call	sub_14CEE

loc_175F9:
		pop	si
		pop	bp
		retn	2
sub_175A4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_175FE	proc near
					; sub_18590+64p ...

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
		push	6
		call	sub_14CEE

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
					; sub_17627+50j
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
					; sub_17687+22j
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
					; seg003:92AAp	...

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
		add	ax, 60h	; '`'
		cmp	ax, 0C0h ; 'À'
		ja	short loc_17790
		mov	bx, [bp+var_4]
		shl	bx, 2
		mov	ax, [bx+di+4]
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 60h	; '`'
		cmp	ax, 0C0h ; 'À'
		ja	short loc_17790
		mov	byte_2CEC1, 1

loc_17790:
					; sub_17726+63j
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
					; sub_17726+96j ...
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
		add	ax, 80h	; '€'
		cmp	ax, 100h
		ja	short loc_177FB
		add	dx, 80h	; '€'
		cmp	dx, 100h
		ja	short loc_177FB
		mov	byte_2CEC1, 1

loc_177FB:
					; sub_17726+CEj
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
		cmp	[bp+var_5], 80h	; '€'
		jb	short loc_1786E
		cmp	[bp+var_5], 0FEh ; 'þ'
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
					; sub_17726+15Cj
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
					; sub_17726+ACj
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
					; sub_17939+18j ...
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
					; sub_179F9+30p ...

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
					; sub_17973+26j ...
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
					; sub_17A31+149p ...

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		inc	byte ptr [si+16h]
		mov	al, 80h	; '€'
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

loc_17A4E:				; DATA XREF: seg003:off_17BF0o
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
		call	sub_1F3A
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
					; DATA XREF: seg003:2972o
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
					; DATA XREF: seg003:2974o
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
					; DATA XREF: seg003:2976o
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
		add	al, 0FEh ; 'þ'
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
					; sub_17A31+8Ej
		mov	byte ptr [si+13h], 2

loc_17B32:
					; sub_17A31+8Cj
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
					; DATA XREF: seg003:2978o
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
					; DATA XREF: seg003:297Ao
		cmp	word ptr [si+4], 0
		jle	short loc_17BA3
		cmp	word ptr [si+4], 1700h
		jl	loc_17BEB
		jmp	short loc_17BA3
; ---------------------------------------------------------------------------

loc_17B6C:
					; DATA XREF: seg003:297Co
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
					; DATA XREF: seg003:297Eo
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
					; sub_17A31+139j ...
		push	si
		call	sub_179F9
		jmp	short loc_17BEB
; ---------------------------------------------------------------------------

loc_17BA9:
					; DATA XREF: seg003:2980o
		cmp	byte_25FE2, 0
		jz	short loc_17BEB
		mov	al, byte_2C976
		mov	ah, 0
		add	[si+0Ch], ax
		jmp	short loc_17BEB
; ---------------------------------------------------------------------------

loc_17BBA:
					; DATA XREF: seg003:2982o
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
					; sub_17A31+6Fj ...
		pop	si
		pop	bp
		retn	2
sub_17A31	endp

; ---------------------------------------------------------------------------
off_17BF0	dw offset loc_17A4E	; DATA XREF: sub_17A31+18r
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
		cmp	di, 0DCh ; 'Ü'
		jge	short loc_17C5F
		mov	ax, 0A0h ; ' '
		jmp	short loc_17C62
; ---------------------------------------------------------------------------

loc_17C5F:
		mov	ax, 9Ch	; 'œ'

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
					; sub_17C04+6Dj ...
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
					; sub_17C04+EAj
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
					; sub_17C04+11Dj ...
		mov	byte ptr [si], 2
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17D36:
		mov	byte ptr [si+12h], 2
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17D3D:
		cmp	di, 0DCh ; 'Ü'
		jl	loc_17E74
		mov	bx, word_2CDF8
		add	bx, bx
		mov	[bx-3D50h], si
		inc	word_2CDF8
		jmp	loc_17E74
; ---------------------------------------------------------------------------

loc_17D56:
					; sub_17C04+B4j
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
					; sub_17C04+162j
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
					; sub_17C04+1AEj ...
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
		add	ax, 40h	; '@'
		cmp	ax, 80h	; '€'
		ja	short loc_17E41
		add	dx, 40h	; '@'
		cmp	dx, 80h	; '€'
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
		push	large 200002h
		nop
		push	cs
		call	near ptr sub_1591A
		mov	byte ptr [si+12h], 1
		cmp	word_2C97A, 3E7h
		jnb	short loc_17E41
		inc	word_2C97A
		call	sub_1060E
		movzx	eax, word_2C97C
		add	dword_2CE1A, eax

loc_17E41:
					; sub_17C04+1E5j ...
		cmp	di, 0DCh ; 'Ü'
		jl	short loc_17E74
		mov	ax, [si+2]
		sar	ax, 4
		add	ax, 1Ch
		mov	bx, word_2C97E
		shl	bx, 2
		mov	[bx-703Ah], ax
		mov	ax, [si+4]
		add	ax, 0C0h ; 'À'
		push	ax
		call	sub_15288
		mov	bx, word_2C97E
		shl	bx, 2
		mov	[bx-7038h], ax
		inc	word_2C97E

loc_17E74:
					; sub_17C04+39j ...
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
		add	al, 98h	; '˜'
		mov	[bp+var_9], al
		mov	[bp+var_4], 1
		mov	[bp+var_6], 1
		cmp	byte_25FEB, 4
		jnz	short loc_17EE9
		mov	ax, 640h
		jmp	short loc_17EFA
; ---------------------------------------------------------------------------

loc_17EE9:
		push	large 3C00500h
		push	large 5000500h
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
					; sub_17C04+368j ...
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
		mov	word_2CE8A, 6FDAh

loc_17FA8:
		inc	byte_2C978
		cmp	[bp+var_9], 4Ch	; 'L'
		jb	short loc_17FB7
		mov	byte_2C978, 0

loc_17FB7:
					; sub_17C04+2A1j ...
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
		add	al, 0FEh ; 'þ'
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
		cmp	word_2632E, 0C8h ; 'È'
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
		call	word_25344
		call	sub_15A70
		mov	byte_26000, 0
		mov	byte ptr word_25FFA, 2
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		call	word_25344
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

; ---------------------------------------------------------------------------
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

loc_180E3:				; DATA XREF: seg003:off_181DDo
		cmp	word_26332, 100h
		jl	loc_181C4
		inc	byte_26331
		mov	word_26332, 0
		mov	byte_26330, 0CCh ; 'Ì'
		jmp	loc_181C4
; ---------------------------------------------------------------------------

loc_180FF:
					; DATA XREF: seg003:2F5Fo ...
		push	large 0C000C0h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 40h	; '@'
		jl	loc_181C4
		inc	byte_26331
		mov	word_26332, 0
		mov	word_26328, 0
		mov	byte ptr word_2634A, 0E0h ; 'à'
		jmp	loc_181C4
; ---------------------------------------------------------------------------

loc_1812B:
					; DATA XREF: seg003:2F63o
		call	sub_18017
		push	large 1800180h
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
		mov	byte_26331, 0FEh ; 'þ'
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	large 800030h
		call	sub_1597C
		push	0Ch
		call	sub_14CEE
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
; ---------------------------------------------------------------------------
		db 0
off_181DD	dw offset loc_180E3	; DATA XREF: seg003:2E5Er
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
		push	large 90008h
		call	sub_16A6B
		cmp	word_26346, 1
		jnz	short loc_18239
		push	8
		call	sub_14CEE
		mov	byte_2D085, 80h	; '€'
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
		call	word_2CE24

loc_18239:
		pop	bp
		retn
sub_181E5	endp

; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 0F6h ; 'ö'
		mov	byte_2D085, al

loc_18274:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C
		mov	al, byte_2D084
		add	al, 0Ah
		mov	byte_2D084, al

loc_182AF:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C
		push	0Fh
		call	sub_14CEE

loc_182EB:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		mov	word ptr dword_26002+2,	608h
		mov	byte ptr word_26006+1, 10h
		call	word_25344
		call	sub_15A5C
		mov	al, byte_2D083
		add	al, 0F8h ; 'ø'
		mov	byte_2D083, al
		push	0Fh
		call	sub_14CEE

loc_18339:
		pop	bp
		retn

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
		push	large 90008h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_183F3
		push	8
		call	sub_14CEE
		mov	byte_26344, 0BCh ; '¼'
		mov	byte_2D085, 38h	; '8'
		mov	byte_2D084, 48h	; 'H'
		mov	byte_2D083, 18h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1837B:
		cmp	word_26346, 40h	; '@'
		jl	short loc_183C4
		cmp	word_26346, 60h	; '`'
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
		cmp	word_26346, 80h	; '€'
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
		cmp	word_26346, 0A0h ; ' '
		jge	short loc_183C8
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_183C8

loc_183C4:
					; sub_1833B+5Bj ...
		inc	byte_26344

loc_183C8:
					; sub_1833B+70j ...
		cmp	byte_26344, 0C0h ; 'À'
		jb	short loc_183D4
		mov	byte_26344, 0BCh ; '¼'

loc_183D4:
		call	word_2CE24
		mov	al, byte_2D07F
		mov	ah, 0
		cmp	ax, word_26346
		jg	short loc_183F3
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	byte_26344, 0B4h ; '´'

loc_183F3:
					; sub_1833B+A6j
		pop	bp
		retn
sub_1833B	endp

; ---------------------------------------------------------------------------
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
		add	al, 40h	; '@'
		mov	byte ptr word_26006, al
		mov	word ptr dword_26002, 303h
		mov	byte_26001, 0Ah
		push	1Fh
		call	sub_157E4
		add	al, 10h
		mov	byte ptr word_26006+1, al
		call	word_25344
		call	sub_15A70
		mov	byte ptr word_25FFA, 3
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 0
		mov	ax, word_26346
		add	ax, ax
		push	ax
		call	sub_157FA
		sub	al, byte ptr word_26346
		add	al, 40h	; '@'
		mov	byte ptr word_26006, al
		push	1Fh
		call	sub_157E4
		add	al, 18h
		mov	byte ptr word_26006+1, al
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE

loc_1847B:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE

loc_184BA:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE
		mov	al, byte_2D085
		add	al, 6
		mov	byte_2D085, al
		mov	al, byte_2D083
		add	al, 4
		mov	byte_2D083, al

loc_18524:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE
		mov	al, byte_2D084
		add	al, 0FAh ; 'ú'
		mov	byte_2D084, al
		mov	al, byte_2D083
		add	al, 4
		mov	byte_2D083, al

loc_1858E:
		pop	bp
		retn

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18590	proc near
		push	bp
		mov	bp, sp
		cmp	word_26346, 1
		jnz	short loc_1859F
		mov	byte_26344, 0BCh ; '¼'

loc_1859F:
		cmp	word_26346, 20h	; ' '
		jnz	short loc_185DD
		mov	eax, dword ptr word_26335+1
		mov	dword_2630A, eax
		mov	byte_26312, 0E0h ; 'à'
		mov	byte_26309, 8
		mov	byte_26313, 8
		push	0
		call	sub_175A4
		mov	byte_26312, 0A0h ; ' '
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
		cmp	word_26346, 40h	; '@'
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
		cmp	byte_2602A, 80h	; '€'
		jz	short loc_1863B
		cmp	byte_2602A, 60h	; '`'
		jz	short loc_1863B
		cmp	byte_2602A, 58h	; 'X'
		jz	short loc_1863B
		cmp	byte_2602A, 50h	; 'P'
		jnz	short loc_1863F

loc_1863B:
					; sub_18590+9Bj ...
		inc	byte_2D083

loc_1863F:
					; sub_18590+7Dj ...
		cmp	byte_25FE5, 0
		jnz	short loc_1869C
		mov	byte ptr word_25FFA, 10h
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	byte_26000, 2
		mov	byte_26001, 0Ah
		push	large 1050106h
		push	large 1070108h
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
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_186B4
		cmp	byte_2D084, 8
		jnb	short loc_186B4
		inc	byte_2D084

loc_186B4:
					; sub_18590+117j ...
		pop	bp
		retn
sub_18590	endp

; ---------------------------------------------------------------------------
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

loc_186EF:				; DATA XREF: seg003:off_188FBo
		cmp	word_26346, 1
		jnz	short loc_18702
		mov	word_26342, 122Ah
		mov	word_2634C, 9F6h

loc_18702:
		call	sub_1FB07
		cmp	word_26346, 0E0h ; 'à'
		jl	short loc_1874E
		cmp	word_26346, 0E0h ; 'à'
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
		cmp	word_26346, 0E0h ; 'à'
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
		push	0Dh
		call	sub_14CEE

loc_1877A:
		mov	word_23F5A, 227Ch
		jmp	loc_188EE
; ---------------------------------------------------------------------------

loc_18783:
					; DATA XREF: seg003:367Do
		call	sub_1FB07
		cmp	word_26346, 20h	; ' '
		jl	loc_188EE
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	byte ptr word_2634A+1, 0
		mov	byte_2D080, 0FFh
		mov	byte_2D07F, 40h	; '@'
		jmp	short loc_1877A
; ---------------------------------------------------------------------------

loc_187AF:
					; DATA XREF: seg003:367Fo
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
		mov	ax, [bx+1D76h]
		mov	word_2CE24, ax
		jmp	short loc_18819
; ---------------------------------------------------------------------------

loc_18800:
		call	sub_181E5
		cmp	word_26346, 0
		jnz	short loc_18819
		cmp	byte_2D07F, 0Ch
		jbe	short loc_18819
		mov	al, byte_2D07F
		add	al, 0F4h ; 'ô'
		mov	byte_2D07F, al

loc_18819:
		call	sub_1FADD
		or	al, al
		jz	loc_188EE
		push	5
		call	sub_17416

loc_18827:
		push	large 101C2h
		call	sub_1FB6E
		mov	byte_2D07F, 50h	; 'P'
		jmp	loc_188EE
; ---------------------------------------------------------------------------

loc_18838:
					; DATA XREF: seg003:3681o
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
		mov	ax, [bx+1D7Eh]
		mov	word_2CE24, ax
		jmp	short loc_1889D
; ---------------------------------------------------------------------------

loc_18884:
		call	sub_1833B
		cmp	word_26346, 0
		jnz	short loc_1889D
		cmp	byte_2D07F, 0B4h ; '´'
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
		push	large 20000h
		call	sub_1FB6E
		jmp	short loc_188EE
; ---------------------------------------------------------------------------

loc_188B4:
					; DATA XREF: seg003:3683o
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
		mov	byte_26345, 0FDh ; 'ý'
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
; ---------------------------------------------------------------------------
		db 0
off_188FB	dw offset loc_186EF	; DATA XREF: seg003:346Ar
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
		add	al, 0FEh ; 'þ'

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
					; sub_18905+65j ...
		mov	al, byte ptr word_26335
		add	al, 0FEh ; 'þ'
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
		call	word_25344
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
					; sub_18987+5Aj
		mov	byte ptr word_26006+1, 18h
		call	sub_157D6
		mov	byte ptr word_26006, al
		call	word_25344
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
		call	word_25344
		call	sub_15A5C

loc_18A2D:
		pop	bp
		retn
sub_189FC	endp

; ---------------------------------------------------------------------------
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
		push	large 1800180h
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
		push	large 1800180h
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
		mov	byte_26330, 0CEh ; 'Î'
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	large 400020h
		call	sub_1597C
		push	0Fh
		call	sub_14CEE
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	large 0C000400h
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
		push	large 1800180h
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
		mov	byte_26331, 0FEh ; 'þ'
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	large 800030h
		call	sub_1597C
		push	0Ch
		call	sub_14CEE
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
		mov	byte_26344, 0B8h ; '¸'
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	large 90008h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	short loc_18C8E
		push	8
		call	sub_14CEE
		jmp	short loc_18C8E
; ---------------------------------------------------------------------------

loc_18C68:
		cmp	word_26346, 20h	; ' '
		jnz	short loc_18C7A
		mov	byte_26344, 0BCh ; '¼'
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
					; sub_18C32+2Bj ...
		mov	al, 0
		pop	bp
		retn	2
sub_18C32	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18C94	proc near
		push	bp
		mov	bp, sp
		push	40h ; '@'
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
		mov	byte ptr word_26006, 60h ; '`'

loc_18CED:
		call	word_25344
		push	0Fh
		call	sub_14CEE
		cmp	byte_2D080, 24h	; '$'
		jnb	short loc_18D07
		mov	al, byte_2D080
		add	al, 4
		mov	byte_2D080, al

loc_18D07:
					; sub_18C94+69j
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_18D52
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		call	sub_15A5C
		cmp	byte_2D085, 0
		jz	short loc_18D30
		mov	al, byte ptr word_26006
		add	al, 87h	; '‡'
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
		mov	byte_26344, 0B4h ; '´'

loc_18D52:
		pop	bp
		retn
sub_18C94	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18D54	proc near
		push	bp
		mov	bp, sp
		push	60h ; '`'
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
		push	large 50A050Ch
		push	large 60C060Eh
		call	sub_E758
		mov	word ptr dword_26002+2,	ax
		mov	byte ptr word_26006, 0C0h ; 'À'
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
		add	al, 0F8h ; 'ø'
		jmp	short loc_18DC1
; ---------------------------------------------------------------------------

loc_18DBC:
		mov	al, byte ptr word_26006
		add	al, 8

loc_18DC1:
		mov	byte ptr word_26006, al
		push	0Fh
		call	sub_14CEE
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18DCD:
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte_26344, 0B4h ; '´'

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
		call	word_25344
		mov	byte ptr word_26006+1, 30h ; '0'
		mov	ax, word_26346
		mov	bx, 40h	; '@'
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
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, 40h	; '@'
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, [bp+var_1]
		mov	byte ptr word_26006, al
		mov	al, byte ptr word_26006+1
		add	al, 0FBh ; 'û'
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
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, 0C0h ; 'À'
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, [bp+var_1]
		mov	byte ptr word_26006, al
		mov	al, byte ptr word_26006+1
		add	al, 0FBh ; 'û'
		mov	byte ptr word_26006+1, al
		mov	al, byte ptr word_26006
		add	al, 8
		mov	byte ptr word_26006, al
		inc	si

loc_18EB5:
		cmp	si, 8
		jl	short loc_18E73

loc_18EBA:
					; sub_18DDF+89j
		pop	si
		leave
		retn
sub_18DDF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18EBD	proc near
		push	bp
		mov	bp, sp
		push	80h ; '€'
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
		mov	byte_26312, 0F0h ; 'ð'
		mov	word_26318, 1Eh
		mov	word_26314, 68h	; 'h'
		push	1
		call	sub_157E4
		mov	byte_2D085, al

loc_18F04:
		cmp	byte_26312, 0F0h ; 'ð'
		jnb	short loc_18F12
		cmp	byte_26312, 80h	; '€'
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
		mov	al, 80h	; '€'
		sub	al, byte_26312
		mov	byte_26312, al
		call	sub_174C7
		mov	al, 80h	; '€'
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
		mov	byte_26344, 0B4h ; '´'

loc_18F5A:
					; sub_18EBD+60j
		pop	bp
		retn
sub_18EBD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18F5C	proc near
		push	bp
		mov	bp, sp
		push	40h ; '@'
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
		mov	byte_2C977, 0E0h ; 'à'

loc_18FC0:
		call	word_25344
		push	0Fh
		call	sub_14CEE
		call	sub_15A70
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18FD0:
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte_26344, 0B4h ; '´'
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
		call	word_25344
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_19029
		mov	byte ptr word_26006, 1Fh
		jmp	short loc_1902E
; ---------------------------------------------------------------------------

loc_19029:
		mov	byte ptr word_26006, 0E1h ; 'á'

loc_1902E:
		call	sub_15A70
		push	3
		call	sub_14CEE

loc_19038:
		pop	bp
		retn
sub_18FE2	endp

; ---------------------------------------------------------------------------
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

loc_19073:				; DATA XREF: seg003:off_19270o
		cmp	word_26346, 1
		jnz	short loc_19097
		mov	word_26342, 1130h
		mov	word_2634C, 0BB8h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8

loc_19097:
		call	sub_1FB07
		cmp	word_26346, 80h	; '€'
		jl	loc_19263
		inc	byte_26345
		mov	word_26346, 0
		push	0Dh
		call	sub_14CEE
		mov	word_23F5A, 22E4h
		jmp	loc_19263
; ---------------------------------------------------------------------------

loc_190BE:
					; DATA XREF: seg003:3FF2o
		call	sub_1FB07
		cmp	word_26346, 40h	; '@'
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
					; DATA XREF: seg003:3FF4o
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
		push	large 100060h
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
		push	large 1076Ch
		jmp	loc_191FD
; ---------------------------------------------------------------------------

loc_19149:
					; DATA XREF: seg003:3FF6o
		call	sub_1FADD
		cmp	word_26346, 40h	; '@'
		jl	loc_19263
		jmp	loc_1920C
; ---------------------------------------------------------------------------

loc_19158:
					; DATA XREF: seg003:3FF8o
		call	sub_18DDF
		push	large 0E0080h
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
		push	large 201F4h
		call	sub_1FB6E
		mov	byte_2D084, 0
		mov	byte_2D080, 14h
		jmp	loc_19263
; ---------------------------------------------------------------------------

loc_1919D:
					; DATA XREF: seg003:3FFAo
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
		push	large 300030h
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
		push	large 10000h

loc_191FD:
		call	sub_1FB6E
		jmp	short loc_19263
; ---------------------------------------------------------------------------

loc_19202:
					; DATA XREF: seg003:3FFCo
		call	sub_1FADD
		cmp	word_26346, 40h	; '@'
		jl	short loc_19263

loc_1920C:
		mov	word_26346, 0
		inc	byte_26345
		mov	byte_26344, 0BCh ; '¼'
		jmp	short loc_19263
; ---------------------------------------------------------------------------

loc_1921D:
					; DATA XREF: seg003:3FFEo
		call	sub_18FE2
		push	large 80080h
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
		mov	byte_26345, 0FDh ; 'ý'
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
; ---------------------------------------------------------------------------
		db 0
off_19270	dw offset loc_19073	; DATA XREF: seg003:3DEEr
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
					; sub_193BE+9Ap ...
		push	bp
		mov	bp, sp
		test	byte ptr word_26332, 3
		jnz	short loc_192F1
		cmp	byte_2D085, 0
		jnz	short loc_192D1
		inc	byte_26330
		cmp	byte_26330, 0DCh ; 'Ü'
		jb	short loc_192F1
		mov	byte_26330, 0DBh ; 'Û'
		add	word ptr dword_26320+2,	0C0h ; 'À'
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
					; sub_19280+43j
		inc	byte_2D085
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_192D1:
		dec	byte_26330
		cmp	byte_26330, 0D4h ; 'Ô'
		jnb	short loc_192F1
		mov	byte_26330, 0D0h ; 'Ð'
		mov	byte_2D085, 0
		mov	word_26332, 0
		mov	byte_2D084, 0

loc_192F1:
					; sub_19280+1Aj ...
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
		push	large 0B000Ah
		call	sub_16A6B
		cmp	word_26332, 1
		jnz	short loc_19319
		push	8
		call	sub_14CEE
		mov	byte_26330, 0D2h ; 'Ò'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19319:
		cmp	word_26332, 10h
		jnz	short loc_19325
		mov	byte_26330, 0D3h ; 'Ó'

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
		mov	byte ptr word_26006, 40h ; '@'

loc_1935F:
					; sub_19327+89j
		call	word_25344
		call	sub_15A5C
		push	0Fh
		call	sub_14CEE
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_26324+2,	ax
		sub	word ptr dword_26320+2,	40h ; '@'
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
		cmp	word_26332, 40h	; '@'
		jnz	short loc_193B2
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	dword_26002, 8040A07h
		jmp	short loc_1935F
; ---------------------------------------------------------------------------

loc_193B2:
		cmp	word_26332, 60h	; '`'
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
		push	large 1010402h
		push	large 3030404h

loc_19412:
		call	sub_E758
		mov	word ptr dword_26002, ax
		mov	word ptr dword_26002+2,	808h

loc_19420:
		call	sub_15A5C
		push	0Fh
		call	sub_14CEE
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_26324+2,	ax
		sub	word ptr dword_26320+2,	40h ; '@'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19437:
		cmp	word_26332, 40h	; '@'
		jnz	short loc_19451
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		push	large 1010503h
		push	large 5040405h
		jmp	short loc_19412
; ---------------------------------------------------------------------------

loc_19451:
		cmp	word_26332, 60h	; '`'
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
		mov	byte ptr word_26006, 40h ; '@'

loc_19496:
					; sub_1945D+7Dj
		call	word_25344
		call	sub_15A5C
		push	0Fh
		call	sub_14CEE
		mov	ax, word ptr dword_26320+2
		mov	word ptr dword_26324+2,	ax
		sub	word ptr dword_26320+2,	40h ; '@'
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
		cmp	word_26332, 40h	; '@'
		jnz	short loc_194DC
		mov	byte ptr dword_26002, 10h
		mov	byte ptr dword_26002+1,	8
		jmp	short loc_19496
; ---------------------------------------------------------------------------

loc_194DC:
		cmp	word_26332, 60h	; '`'
		jl	short loc_194E6
		call	sub_19280

loc_194E6:
		pop	bp
		retn
sub_1945D	endp

; ---------------------------------------------------------------------------
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
		push	large 1800180h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 0C0h ; 'À'
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

loc_19569:				; DATA XREF: seg003:off_1962Co
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
					; DATA XREF: seg003:43AEo
		call	sub_19327
		jmp	short loc_195A1
; ---------------------------------------------------------------------------

loc_19599:
					; DATA XREF: seg003:43B0o
		call	sub_193BE
		jmp	short loc_195A1
; ---------------------------------------------------------------------------

loc_1959E:
					; DATA XREF: seg003:43B2o
		call	sub_1945D

loc_195A1:
		cmp	byte_26330, 0D4h ; 'Ô'
		jnb	short loc_195BC
		push	large 1800180h
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
		mov	byte_26331, 0FEh ; 'þ'
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	large 800030h
		call	sub_1597C
		push	0Ch
		call	sub_14CEE
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
; ---------------------------------------------------------------------------
		db 0
off_1962C	dw offset loc_19569	; DATA XREF: seg003:42E4r
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
		add	al, 0FEh ; 'þ'
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
		mov	word ptr [si+12h], 0C0h	; 'À'
		jmp	short loc_197DC
; ---------------------------------------------------------------------------

loc_19773:
		mov	word ptr [si+12h], 0BEh	; '¾'
		cmp	[bp+var_2], 0
		jnz	short loc_19785
		push	si
		call	word_2CE2A
		jmp	short loc_1978A
; ---------------------------------------------------------------------------

loc_19785:
		push	si
		call	word_2CE2C

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
		mov	ax, [bx+1D88h]
		mov	word_2CE2A, ax
		jmp	short loc_197D2
; ---------------------------------------------------------------------------

loc_197C2:
		push	3
		call	sub_157E4
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+1D88h]
		mov	word_2CE2C, ax

loc_197D2:
		mov	word ptr [si+0Eh], 0
		jmp	short loc_197DC
; ---------------------------------------------------------------------------

loc_197D9:
		inc	word ptr [si+0Eh]

loc_197DC:
					; sub_196D3+104j
		mov	ax, [si+2]
		sub	ax, word ptr dword_2CEA0
		add	ax, 0C0h ; 'À'
		cmp	ax, 180h
		jnb	short loc_197FF
		mov	ax, [si+4]
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 0C0h ; 'À'
		cmp	ax, 180h
		jnb	short loc_197FF
		mov	byte_2CEC1, 1

loc_197FF:
					; sub_196D3+125j
		cmp	byte_2D07F, 3
		jz	short loc_1984A
		mov	eax, [si+2]
		mov	dword_2CED2, eax
		call	sub_126B3
		mov	[si+16h], ax
		cmp	word ptr [si+16h], 0
		jz	short loc_19823
		push	4
		call	sub_14CEE

loc_19823:
		mov	ax, [si+16h]
		sub	[si+14h], ax
		cmp	word ptr [si+14h], 0
		jge	short loc_198A5
		inc	byte ptr [si]
		mov	word ptr [si+12h], 4
		mov	word ptr [si+16h], 0
		push	0Ch
		call	sub_14CEE
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
		mov	word ptr [si+12h], 0C0h	; 'À'
		cmp	[bp+var_2], 0
		jnz	short loc_19897
		mov	word_2CE2A, 4863h
		jmp	short loc_1989D
; ---------------------------------------------------------------------------

loc_19897:
		mov	word_2CE2C, 4863h

loc_1989D:
		sub	word_26342, 12Ch

loc_198A3:
					; sub_196D3+193j
		inc	byte ptr [si]

loc_198A5:
					; sub_196D3+15Aj ...
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

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+4]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_198CF
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_198CF:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19921
		cmp	word ptr [si+0Eh], 40h ; '@'
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
		call	word_25344
		call	sub_15A5C
		mov	word ptr [si+12h], 0C2h	; 'Â'
		jmp	short loc_19921
; ---------------------------------------------------------------------------

loc_19912:
		cmp	word ptr [si+0Eh], 60h ; '`'
		jb	short loc_19921
		mov	word ptr [si+12h], 0BEh	; '¾'
		mov	al, 1
		jmp	short loc_19923
; ---------------------------------------------------------------------------

loc_19921:
		mov	al, 0

loc_19923:
		pop	si
		pop	bp
		retn	2
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+4]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_19940
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_19940:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19993
		mov	word ptr [si+12h], 0C2h	; 'Â'
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
		call	word_25344
		call	sub_15A5C
		jmp	short loc_19993
; ---------------------------------------------------------------------------

loc_19984:
		cmp	word ptr [si+0Eh], 60h ; '`'
		jb	short loc_19993
		mov	word ptr [si+12h], 0BEh	; '¾'
		mov	al, 1
		jmp	short loc_19995
; ---------------------------------------------------------------------------

loc_19993:
		mov	al, 0

loc_19995:
		pop	si
		pop	bp
		retn	2
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+4]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_199B2
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_199B2:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19A08
		mov	word ptr [si+12h], 0C2h	; 'Â'
		cmp	word ptr [si+0Eh], 40h ; '@'
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
		call	word_25344
		call	sub_15A5C
		jmp	short loc_19A08
; ---------------------------------------------------------------------------

loc_199F9:
		cmp	word ptr [si+0Eh], 60h ; '`'
		jb	short loc_19A08
		mov	word ptr [si+12h], 0BEh	; '¾'
		mov	al, 1
		jmp	short loc_19A0A
; ---------------------------------------------------------------------------

loc_19A08:
		mov	al, 0

loc_19A0A:
		pop	si
		pop	bp
		retn	2
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+4]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_19A27
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_19A27:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19A7D
		mov	word ptr [si+12h], 0C2h	; 'Â'
		cmp	word ptr [si+0Eh], 40h ; '@'
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
		call	word_25344
		call	sub_15A5C
		jmp	short loc_19A7D
; ---------------------------------------------------------------------------

loc_19A6E:
		cmp	word ptr [si+0Eh], 60h ; '`'
		jb	short loc_19A7D
		mov	word ptr [si+12h], 0BEh	; '¾'
		mov	al, 1
		jmp	short loc_19A7F
; ---------------------------------------------------------------------------

loc_19A7D:
		mov	al, 0

loc_19A7F:
		pop	si
		pop	bp
		retn	2
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+4]
		cmp	word ptr [si+0Eh], 10h
		jnz	short loc_19A9C
		push	word ptr [si+2]
		push	word ptr [si+4]
		call	sub_ECD2

loc_19A9C:
		cmp	word ptr [si+0Eh], 20h ; ' '
		jb	short loc_19ADC
		mov	word ptr [si+12h], 0C2h	; 'Â'
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
		call	word_25344
		call	sub_15A5C

loc_19ADC:
		mov	al, 0
		pop	si
		pop	bp
		retn	2
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+4]
		cmp	word ptr [si+0Eh], 60h ; '`'
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
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		mov	al, 0
		pop	bp
		retn	2

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19B04	proc near
					; seg003:loc_1A101p
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 40h	; '@'
		jge	short loc_19B2F
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h ; '¸'
		cmp	word_26346, 28h	; '('
		jnz	short loc_19B9B
		push	8
		jmp	short loc_19B96
; ---------------------------------------------------------------------------

loc_19B2F:
		cmp	word_26346, 40h	; '@'
		jnz	short loc_19B9B
		mov	byte ptr word_25FFA, 2
		mov	byte_26000, 0Dh
		mov	byte ptr dword_26002, 2
		call	word_25344
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
		mov	byte_26344, 0B6h ; '¶'
		push	0Fh

loc_19B96:
		call	sub_14CEE

loc_19B9B:
					; sub_19B04+30j
		pop	si
		pop	bp
		retn
sub_19B04	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		call	sub_19B04
		cmp	word_26346, 60h	; '`'
		jnz	short loc_19BB6
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19BB6:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
		jge	short loc_19BE2
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h ; '¸'
		cmp	word_26346, 28h	; '('
		jnz	short loc_19C32
		push	8
		jmp	short loc_19C19
; ---------------------------------------------------------------------------

loc_19BE2:
		cmp	word_26346, 40h	; '@'
		jnz	short loc_19C20
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 0Bh
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	dword_26002, 804081Ch
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_26006, 0
		call	word_25344
		call	sub_15A5C
		mov	byte_26344, 0B4h ; '´'
		push	0Fh

loc_19C19:
		call	sub_14CEE
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19C20:
		cmp	word_26346, 60h	; '`'
		jnz	short loc_19C32
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19C32:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
		jge	short loc_19C5E
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h ; '¸'
		cmp	word_26346, 28h	; '('
		jnz	short loc_19CAE
		push	8
		jmp	short loc_19C95
; ---------------------------------------------------------------------------

loc_19C5E:
		cmp	word_26346, 40h	; '@'
		jnz	short loc_19C9C
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 9
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	dword_26002, 7050807h
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_26006, 0
		call	word_25344
		call	sub_15A5C
		mov	byte_26344, 0B4h ; '´'
		push	0Fh

loc_19C95:
		call	sub_14CEE
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19C9C:
		cmp	word_26346, 60h	; '`'
		jnz	short loc_19CAE
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19CAE:
		pop	bp
		retn

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
		mov	ax, 40h	; '@'
		mov	word_2BC9A, ax
		mov	word_2BC80, ax
		mov	byte_2D07E, 0C4h ; 'Ä'
		add	word_2CE30, 20h	; ' '
		leave
		retn
; ---------------------------------------------------------------------------

loc_19CFC:
		cmp	word_2CE2E, 20h	; ' '
		jb	locret_19E10
		cmp	word_2CE2E, 40h	; '@'
		jnb	short loc_19D22
		mov	byte_2D07F, 2
		mov	ax, 40h	; '@'
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
		cmp	word_2CE2E, 40h	; '@'
		jnz	short loc_19D37
		push	8
		call	sub_14CEE

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
		call	word_25344
		mov	word_2CED6, 380h
		mov	word_2CED8, 80h	; '€'
		mov	eax, dword ptr word_2BC71+1
		mov	dword_2CED2, eax
		add	word ptr dword_2CED2, 400h
		call	sub_12842
		mov	[bp+var_2], ax
		cmp	[bp+var_2], 0
		jz	short loc_19D9D
		push	9
		call	sub_14CEE

loc_19D9D:
		mov	ax, word ptr dword_2CEA0
		sub	ax, word_2BC71+1
		cmp	ax, 800h
		jnb	short loc_19DBD
		mov	ax, word_2BC74
		sub	ax, word ptr dword_2CEA0+2
		add	ax, 40h	; '@'
		cmp	ax, 80h	; '€'
		jnb	short loc_19DBD
		mov	byte_2CEC1, 1

loc_19DBD:
					; sub_19CB0+106j
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
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE

locret_19E10:
					; sub_19CB0+1Aj ...
		leave
		retn
sub_19CB0	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
		jge	short loc_19E43
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h ; '¸'
		cmp	word_26346, 28h	; '('
		jnz	loc_19ED8
		push	8
		call	sub_14CEE
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19E43:
		cmp	word_26346, 40h	; '@'
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
		call	sub_1F3A
		mov	byte_26312, al
		call	sub_174C7
		mov	al, byte_26312
		add	al, 10h
		mov	byte_26312, al
		call	sub_174C7
		mov	al, byte_26312
		add	al, 0E0h ; 'à'
		mov	byte_26312, al
		call	sub_174C7
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 0Dh
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	word ptr dword_26002, 814h
		mov	byte ptr word_26006+1, 18h
		mov	byte ptr word_26006, 0
		call	word_25344
		call	sub_15A5C
		mov	byte_26344, 0B4h ; '´'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_19EC6:
		cmp	word_26346, 60h	; '`'
		jnz	short loc_19ED8
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19ED8:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
		jge	short loc_19F0E
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h ; '¸'
		mov	byte_2D085, 8
		cmp	word_26346, 28h	; '('
		jnz	short loc_19F73
		push	8
		call	sub_14CEE
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
		call	word_25344
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
		mov	byte_26344, 0B4h ; '´'
		push	0Fh
		call	sub_14CEE

loc_19F61:
		cmp	word_26346, 60h	; '`'
		jnz	short loc_19F73
		mov	word_26346, 0
		mov	byte_26349, 0

loc_19F73:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
		jge	short loc_19FA9
		mov	ax, word_26346
		add	ax, 0FFD8h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_26344, 0B8h ; '¸'
		mov	byte_2D085, 0
		cmp	word_26346, 28h	; '('
		jnz	short loc_1A003
		push	8
		call	sub_14CEE
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
		call	word_25344
		mov	al, byte_2D085
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 2
		mov	byte_2D085, al
		mov	byte_26344, 0B4h ; '´'
		push	3
		call	sub_14CEE

loc_19FF1:
		cmp	word_26346, 60h	; '`'
		jnz	short loc_1A003
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1A003:
		pop	bp
		retn

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A005	proc near
		push	bp
		mov	bp, sp
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 2
		mov	byte ptr word_26006, 40h ; '@'
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A042
		mov	byte ptr word_26006+1, 20h ; ' '
		mov	word ptr dword_26002, 0A0Dh
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE

loc_1A042:
		pop	bp
		retn
sub_1A005	endp

; ---------------------------------------------------------------------------
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

loc_1A089:				; DATA XREF: seg003:off_1A3D1o
		cmp	word_26346, 1
		jnz	short loc_1A0AD
		mov	word_26342, 2580h
		mov	word_2634C, 1CE8h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8

loc_1A0AD:
		call	sub_1FB07
		cmp	word_26346, 80h	; '€'
		jl	loc_1A3B2
		inc	byte_26345
		mov	word_26346, 0
		push	0Dh
		call	sub_14CEE
		mov	word_23F5A, 2370h
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A0D4:
					; DATA XREF: seg003:5153o
		call	sub_1FB07
		cmp	word_26346, 40h	; '@'
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
					; DATA XREF: seg003:5155o
		call	sub_19B04
		call	sub_1FADD
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1A15A
		mov	si, 0B290h
		mov	byte ptr [si], 1
		mov	word ptr [si+12h], 0BEh	; '¾'
		mov	word ptr [si+10h], 1000h
		mov	byte ptr [si+1], 60h ; '`'
		mov	word ptr [si+14h], 1F4h
		mov	word ptr [si+2], 0C190h
		add	si, 1Ah
		mov	byte ptr [si], 1
		mov	word ptr [si+12h], 0BEh	; '¾'
		mov	word ptr [si+10h], 1000h
		mov	byte ptr [si+1], 20h ; ' '
		mov	word ptr [si+14h], 1F4h
		mov	word ptr [si+2], 0C190h
		mov	word_2CE2A, 4637h
		mov	word_2CE2C, 4637h
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A15A:
		cmp	word_26346, 80h	; '€'
		jle	loc_1A3B2
		call	sub_19634
		cmp	word_2BC80, 0
		jnz	loc_1A3B2
		inc	byte_26345
		mov	byte_26349, 0
		mov	word_26346, 0
		mov	byte ptr word_2634A+1, 0
		mov	byte_2D07D, 0
		mov	word_2CE30, 0A0h ; ' '
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A192:
					; DATA XREF: seg003:5157o ...
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
		mov	ax, [bx+1D90h]
		mov	word_2CE32, ax
		jmp	short loc_1A1E7
; ---------------------------------------------------------------------------

loc_1A1E3:
		call	word_2CE32

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
					; DATA XREF: seg003:5159o ...
		mov	word ptr dword_2BC76, 800h
		mov	word ptr dword_2BC76+2,	800h
		mov	word ptr dword_2BC90, 1000h
		mov	word ptr dword_2BC90+2,	800h
		mov	word_2BC84, 1F4h
		mov	word_2BC9E, 1F4h
		mov	ax, 487Bh
		mov	word_2CE2C, ax
		mov	word_2CE2A, ax
		push	large 0C000400h
		call	sub_16CCC
		or	al, al
		jz	loc_1A359
		jmp	loc_1A34F
; ---------------------------------------------------------------------------

loc_1A284:
					; DATA XREF: seg003:515Bo ...
		mov	word ptr dword_2BC76, 800h
		mov	word ptr dword_2BC76+2,	800h
		mov	word ptr dword_2BC90, 1000h
		mov	word ptr dword_2BC90+2,	800h
		mov	word_2BC84, 1F4h
		mov	word_2BC9E, 1F4h
		mov	ax, 487Bh
		mov	word_2CE2C, ax
		mov	word_2CE2A, ax
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
		mov	word_2CE2A, 46A8h
		mov	word_2CE2C, 46A8h
		jmp	loc_1A3B2
; ---------------------------------------------------------------------------

loc_1A315:
					; DATA XREF: seg003:516Bo
		mov	word ptr dword_2BC76, 400h
		mov	word ptr dword_2BC76+2,	800h
		mov	word ptr dword_2BC90, 1400h
		mov	word ptr dword_2BC90+2,	800h
		mov	word_2BC84, 1F4h
		mov	word_2BC9E, 1F4h
		mov	ax, 4804h
		mov	word_2CE2C, ax
		mov	word_2CE2A, ax
		push	large 0C000400h
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
					; DATA XREF: seg003:516Do
		mov	word ptr dword_2BC76, 400h
		mov	word ptr dword_2BC76+2,	800h
		mov	word ptr dword_2BC90, 1400h
		mov	word ptr dword_2BC90+2,	800h
		mov	ax, 4804h
		mov	word_2CE2C, ax
		mov	word_2CE2A, ax
		call	sub_1A005
		cmp	word_26346, 3E8h
		jge	short loc_1A396
		call	sub_1FADD
		or	al, al
		jz	short loc_1A3B2
		mov	byte ptr word_2634A+1, 1

loc_1A396:
		mov	word_26346, 0
		mov	byte_26345, 0FDh ; 'ý'
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
		cmp	byte_26345, 0FEh ; 'þ'
		jnb	short loc_1A3CD
		call	sub_196D3

loc_1A3CD:
		pop	si
		pop	bp
		retf
; ---------------------------------------------------------------------------
		db 0
off_1A3D1	dw offset loc_1A089	; DATA XREF: seg003:4E04r
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
		push	[bp+arg_0]
		call	sub_14CEE

loc_1A41F:
		mov	byte_2297E, 0
		mov	ax, si
		pop	si
		pop	bp
		retn	6
sub_1A3EF	endp

; ---------------------------------------------------------------------------
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
		push	large 1800180h
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
		push	60h ; '`'
		call	sub_157FA
		sub	al, 30h	; '0'
		jmp	short loc_1A490
; ---------------------------------------------------------------------------

loc_1A47E:
		cmp	word ptr [si], 0F00h
		jle	short loc_1A48D
		push	60h ; '`'
		call	sub_157E4
		add	al, 30h	; '0'
		jmp	short loc_1A490
; ---------------------------------------------------------------------------

loc_1A48D:
		call	sub_157D6

loc_1A490:
					; sub_1A45E+2Dj
		mov	[si+14h], al
		cmp	byte ptr [di], 1
		jnz	short loc_1A49E
		cmp	byte ptr [si+14h], 80h ; '€'
		jb	short loc_1A4A9

loc_1A49E:
		cmp	byte ptr [di], 2
		jnz	short loc_1A4B1
		cmp	byte ptr [si+14h], 80h ; '€'
		jb	short loc_1A4B1

loc_1A4A9:
		mov	al, [si+14h]
		neg	al
		mov	[si+14h], al

loc_1A4B1:
					; sub_1A45E+49j
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
		mov	byte ptr [si+0Eh], 0B6h	; '¶'
		jmp	short loc_1A4EA
; ---------------------------------------------------------------------------

loc_1A4E6:
		mov	byte ptr [si+0Eh], 0B5h	; 'µ'

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
					; sub_1A45E+A2j
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
					; sub_1A45E+BCj
		cmp	[bp+arg_2], 30h	; '0'
		jl	short loc_1A52E
		mov	byte ptr [si+0Eh], 0B4h	; '´'
		mov	al, 1
		jmp	short loc_1A530
; ---------------------------------------------------------------------------

loc_1A52E:
					; sub_1A45E+C6j
		mov	al, 0

loc_1A530:
		pop	di
		pop	si
		pop	bp
		retn	6
sub_1A45E	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+4]
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
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jge	short loc_1A58D
		mov	eax, dword ptr word_26335+1
		mov	dword_2A722, eax
		mov	ax, word_26346
		add	ax, 0FFE8h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_26344, 0B7h ; '·'
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1A5B1
		push	8
		call	sub_14CEE
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A58D:
		call	word_2CE36
		or	al, al
		jnz	short loc_1A59C
		mov	byte_26344, 0B8h ; '¸'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A59C:
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	byte_26344, 0B4h ; '´'
		mov	byte_2635C, 0B4h ; '´'

loc_1A5B1:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jge	short loc_1A5DC
		mov	eax, dword_2634E
		mov	dword_2A722, eax
		mov	ax, word_26346
		add	ax, 0FFE8h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_2635C, 0B7h ; '·'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A5DC:
		call	word_2CE38
		or	al, al
		jnz	short loc_1A5E9
		mov	byte_2635C, 0B8h ; '¸'

loc_1A5E9:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE

loc_1A641:
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1A64D
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A64D:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A9C
		push	3
		call	sub_14CEE

loc_1A69C:
		cmp	word_26346, 60h	; '`'
		jnz	short loc_1A6A7
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A6A7:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1A6BA
		mov	byte_2D085, 0F0h ; 'ð'

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
		call	word_25344
		call	sub_15A8E
		push	3
		call	sub_14CEE

loc_1A709:
		cmp	word_26346, 0A0h ; ' '
		jnz	short loc_1A715
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A715:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		mov	byte ptr word_26006, 40h ; '@'
		mov	byte ptr word_25FFA+1, 2Eh ; '.'
		mov	ax, word_26335+1
		mov	word ptr dword_25FFC, ax
		mov	ax, word_26338
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002, 0C08h
		mov	byte ptr word_26006+1, 40h ; '@'
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE

loc_1A765:
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1A771
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A771:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	sub_1F3A
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
		cmp	word_26346, 90h	; ''
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
		call	sub_1F3A
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
		cmp	word_26346, 0A0h ; ' '
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
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1A843
		mov	byte_2D085, 20h	; ' '
		mov	byte_2D082, 0FCh ; 'ü'

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
		call	word_25344
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
		push	3
		call	sub_14CEE

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
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A70

loc_1A91D:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C

loc_1A966:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C

loc_1A9AF:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		mov	byte ptr word_26006, 40h ; '@'
		mov	byte ptr word_25FFA+1, 32h ; '2'
		mov	ax, word ptr dword_2634E
		mov	word ptr dword_25FFC, ax
		mov	ax, word ptr dword_2634E+2
		add	ax, 0FF80h
		mov	word ptr dword_25FFC+2,	ax
		mov	word ptr dword_26002, 0C08h
		mov	byte ptr word_26006+1, 40h ; '@'
		call	word_25344
		call	sub_15A5C
		push	3
		call	sub_14CEE

loc_1A9FF:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C

loc_1AA48:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
		call	sub_15A5C

loc_1AA97:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344
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
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	word_26346, 30h	; '0'
		jz	short loc_1AB31
		cmp	word_26346, 60h	; '`'
		jnz	short loc_1AB72

loc_1AB31:
		mov	eax, dword_2634E
		mov	dword ptr word_2BC71+1,	eax
		mov	word_2BC82, 0Bh
		mov	byte_2BC88, 20h	; ' '
		mov	ax, word_26335+1
		cmp	ax, word ptr dword_2634E
		jl	short loc_1AB53
		mov	byte ptr [bp-1], 40h ; '@'
		jmp	short loc_1AB57
; ---------------------------------------------------------------------------

loc_1AB53:
		mov	byte ptr [bp-1], 0C0h ;	'À'

loc_1AB57:
		push	word_2BC71+1
		push	word_2BC74
		push	word ptr [bp-1]
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_17687
		push	0Fh
		call	sub_14CEE

loc_1AB72:
		mov	al, 0
		leave
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	word_26346, 30h	; '0'
		jz	short loc_1AB88
		cmp	word_26346, 60h	; '`'
		jnz	short loc_1ABC9

loc_1AB88:
		mov	eax, dword ptr word_26335+1
		mov	dword ptr word_2BC71+1,	eax
		mov	word_2BC82, 9
		mov	byte_2BC88, 20h	; ' '
		mov	ax, word_26335+1
		cmp	ax, word ptr dword_2634E
		jge	short loc_1ABAA
		mov	byte ptr [bp-1], 40h ; '@'
		jmp	short loc_1ABAE
; ---------------------------------------------------------------------------

loc_1ABAA:
		mov	byte ptr [bp-1], 0C0h ;	'À'

loc_1ABAE:
		push	word_2BC71+1
		push	word_2BC74
		push	word ptr [bp-1]
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_17687
		push	0Fh
		call	sub_14CEE

loc_1ABC9:
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1ABD6
		mov	ax, 1
		jmp	short locret_1ABD8
; ---------------------------------------------------------------------------

loc_1ABD6:
		xor	ax, ax

locret_1ABD8:
		leave
		retn
; ---------------------------------------------------------------------------
		db 0C8h, 4, 2 dup(0), 56h, 0A1h, 58h, 59h, 3Bh,	6, 70h
		db 59h,	7Eh, 6,	66h, 0A1h, 56h,	59h, 0EBh, 4, 66h, 0A1h
		db 6Eh,	59h, 66h, 0A3h,	42h, 0BFh, 0FFh, 6, 66h, 59h, 0A0h
		db 65h,	59h, 0B4h, 0, 89h, 46h,	0FCh, 0B9h, 6, 0, 0BBh
		db 3Ch,	5Dh, 2Eh, 8Bh, 7, 3Bh, 46h, 0FCh, 74h, 8, 83h
		db 0C3h, 2, 0E2h, 0F3h,	0E9h, 8Fh, 3, 2Eh, 0FFh, 67h, 0Ch
; ---------------------------------------------------------------------------

loc_1AC1C:				; DATA XREF: seg003:5D48o
		cmp	word_26346, 1
		jnz	short loc_1AC5E
		mov	word_26342, 1194h
		mov	word_2634C, 0
		mov	word_2635A, 1194h
		mov	word_26364, 0
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	si, 0D4h ; 'Ô'
		jmp	short loc_1AC58
; ---------------------------------------------------------------------------

loc_1AC51:
		push	si
		call	sub_35A2
		inc	si

loc_1AC58:
		cmp	si, 0E4h ; 'ä'
		jl	short loc_1AC51

loc_1AC5E:
		call	sub_1FB07
		push	large 1800180h
		push	0Ah
		call	sub_1A3EF
		cmp	word_26346, 80h	; '€'
		jl	loc_1AFA7	; default
		inc	byte_26345
		mov	word_26346, 0
		push	0Dh
		call	sub_14CEE
		mov	word_23F5A, 23FCh
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1AC90:				; DATA XREF: seg003:5D48o
		call	sub_1FB07
		push	large 1800180h
		push	0Ah
		call	sub_1A3EF
		cmp	word_26346, 40h	; '@'
		jl	loc_1AFA7	; default
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	word_2CE36, 536Bh
		mov	word_2CE38, 5649h
		mov	word_2D06C, 5169h
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------
aAiy	db 0A0h, 069h, 059h, 0B4h, 0
		db 0Bh,	0C0h, 74h, 0Ah,	3Dh, 1,	0, 0Fh,	84h, 0E9h, 0, 0E9h
		db 0ECh, 0, 80h, 3Eh, 6Bh, 59h,	9, 74h,	7, 80h,	3Eh, 6Bh
		db 59h,	0Eh, 75h, 2Fh, 0A1h, 66h, 59h, 5, 0C0h,	0FFh, 89h
		db 46h,	0FEh, 83h, 3Eh,	66h, 59h, 10h, 75h, 28h, 80h, 3Eh
		db 99h,	0BFh, 14h, 73h,	5, 0C6h, 6, 99h, 0BFh, 14h, 6Ah
		db 0Fh,	9Ah, 2Eh, 2
		dw seg seg002
		db 6Ah,	1, 0E8h, 0B3h, 0B5h, 6Ah, 2, 0E8h, 2Eh,	0B6h, 0EBh
		db 9, 0A1h, 66h, 59h, 5, 0F0h, 0FFh, 89h, 46h, 0FEh, 0FFh
		db 76h,	0FEh, 0E8h, 7, 0F8h, 0Ah, 0C0h,	0Fh, 84h, 9Ah
		db 0, 0C7h, 6, 66h, 59h, 2 dup(0), 0FEh, 6, 69h, 59h, 0FEh
		db 6, 6Bh, 59h,	80h, 3Eh, 6Bh, 59h, 0Ah, 73h, 25h, 0A0h
		db 6Bh,	59h, 0B4h, 0, 25h, 3, 0, 3, 0C0h, 8Bh, 0D8h, 8Bh
		db 87h,	0A8h, 1Dh, 0A3h, 56h, 0C4h, 0A0h, 6Bh, 59h, 0B4h
		db 0, 25h, 3, 0, 3, 0C0h, 8Bh, 0D8h, 8Bh, 87h, 0C0h, 1Dh
		db 0EBh, 49h, 80h, 3Eh,	6Bh, 59h, 0Fh, 73h, 18h, 0C7h
		db 6, 56h, 0C4h, 0F5h, 54h, 0A0h, 6Bh, 59h, 0B4h, 0, 25h
		db 3, 0, 3, 0C0h, 8Bh, 0D8h, 8Bh, 87h, 0C8h, 1Dh, 0EBh
		db 2Ah,	80h, 3Eh, 6Bh, 59h, 24h, 73h, 28h, 0A0h, 6Bh, 59h
		db 0B4h, 0, 25h, 3, 0, 3, 0C0h,	8Bh, 0D8h, 8Bh,	87h, 0B0h
		db 1Dh,	0A3h, 56h, 0C4h, 0A0h, 6Bh, 59h, 0B4h, 0, 25h
		db 3, 0, 3, 0C0h, 8Bh, 0D8h, 8Bh, 87h, 0D0h, 1Dh, 0A3h
		db 58h,	0C4h, 0EBh, 12h, 0C6h, 6, 6Bh, 59h, 0, 0C7h, 46h
		db 0FEh, 1, 0, 0EBh, 63h, 0E8h,	8Ah, 0F7h, 0E8h, 0E4h
		db 0F7h, 0A1h, 62h, 59h, 3, 6, 7Ah, 59h, 3Dh, 7Ch, 15h
		db 7Dh,	19h, 80h, 3Eh, 6Bh, 59h, 9, 73h, 12h, 0C6h, 6
		db 69h,	59h, 0,	0C7h, 6, 66h, 59h, 2 dup(0), 0C6h, 6, 6Bh
		db 59h,	9, 0EBh, 23h, 0A1h, 62h, 59h, 3, 6, 7Ah, 59h, 3Dh
		db 0CAh, 8, 7Dh, 17h, 80h, 3Eh,	6Bh, 59h, 0Eh, 73h, 10h
		db 0C6h, 6, 69h, 59h, 0, 0C7h, 6, 66h, 59h, 2 dup(0), 0C6h
		db 6, 6Bh, 59h,	0Eh, 0E8h, 11h,	0F6h, 0B4h, 0, 89h, 46h
		db 0FEh, 83h, 7Eh, 0FEh, 0, 0Fh, 84h, 80h, 1, 0C6h, 6
		db 6Bh,	59h, 1,	8Ah, 46h, 0FEh,	4, 0FFh, 0A2h, 83h, 59h
		db 0C6h, 6, 65h, 59h, 0FDh, 0C7h, 6, 66h, 59h, 2 dup(0)
		db 80h,	3Eh, 28h, 56h, 0, 0Fh, 84h, 5Fh, 1, 6Ah, 0, 0E8h
		db 0DAh, 0C7h, 0EBh, 1Ah
byte_1AE4F	db 83h,	3Eh, 66h, 59h, 10h, 75h, 16h, 80h, 3Eh,	83h, 59h
					; DATA XREF: seg003:5D48o
		db 0, 75h, 7, 6Ah, 4, 0E8h, 6Ah, 0B4h, 0EBh, 5,	6Ah, 4
		db 0E8h, 0E3h, 0B4h, 0E9h, 3Bh,	1, 83h,	3Eh, 66h, 59h
		db 20h,	0Fh, 85h, 32h, 1, 80h, 3Eh, 83h, 59h, 0, 75h, 0Fh
		db 0E8h, 0FBh, 0B4h, 0C6h, 6, 64h, 59h,	4, 0C6h, 6, 7Ch
		db 59h,	0B4h, 0EBh, 0Dh, 0E8h, 28h, 0B5h, 0C6h,	6, 7Ch
		db 59h,	4, 0C6h, 6, 64h, 59h, 0B4h, 0FEh, 6, 65h, 59h
		db 0A0h, 6Bh, 59h, 0A2h, 98h, 0BFh, 0C7h, 6, 66h, 59h
		db 2 dup(0), 6Ah, 0Ch, 9Ah, 2Eh, 2
		dw seg seg002
; ---------------------------------------------------------------------------
		mov	byte_2CEBC, 0FFh
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1AEB7:				; DATA XREF: seg003:5D48o
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
		mov	word_23F5A, 0DD8h
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
		cmp	word_26346, 40h	; '@'
		jl	loc_1AFA7	; default
		inc	byte_26345
		mov	word_26346, 0
		jmp	loc_1AFA7	; default
; ---------------------------------------------------------------------------

loc_1AF24:				; DATA XREF: seg003:5D48o
		mov	PaletteTone, 3Ch	; '<' ; jumptable 0001AC18 case 255
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
		mov	word ptr dword_2D066+2,	seg seg003
		mov	word ptr dword_2D066, 6772h
		jmp	short loc_1AF85
; ---------------------------------------------------------------------------

loc_1AF66:
		push	ds
		push	offset a_dm08_tx2 ; "_DM08.TX2"
		call	sub_ED87
		mov	word ptr dword_2CE9A+2,	ds
		mov	word ptr dword_2CE9A, offset aTH05_11
		mov	word ptr dword_2D066+2,	seg seg003
		mov	word ptr dword_2D066, 7298h

loc_1AF85:
		call	sub_F2B4
		mov	word_2CE88, 6EABh
		mov	byte_26345, 0
		mov	word_26346, 0
		mov	word_2D06A, 6102h
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
; ---------------------------------------------------------------------------
		db 0
		dw	0,     1,     2,  0FDh ; value table for switch	statement
		dw   0FEh,  0FFh
		dw offset loc_1AC1C	; jump table for switch	statement
		dw offset loc_1AC90
		dw offset aAiy
		dw offset byte_1AE4F
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
		push	0Dh
		call	sub_14CEE
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
		mov	ax, 40h	; '@'
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
					; sub_1AFD4+58j ...
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
		push	8
		call	sub_14CEE
		mov	byte ptr word_25FFA, 2
		mov	byte_26000, 0Dh
		mov	byte ptr dword_26002, 7
		call	word_25344
		mov	byte_26330, 0D4h ; 'Ô'

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
		push	0Fh
		call	sub_14CEE

loc_1B139:
					; sub_1B0A4+36j ...
		cmp	word_26332, 60h	; '`'
		jl	short loc_1B150
		mov	byte_26330, 0D0h ; 'Ð'
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
		push	8
		call	sub_14CEE
		mov	byte_26000, 4
		mov	byte ptr dword_26002, 10h
		call	word_25344
		mov	byte_26330, 0D4h ; 'Ô'
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
		push	3
		call	sub_14CEE

loc_1B1CC:
					; sub_1B153+35j ...
		cmp	word_26332, 60h	; '`'
		jl	short loc_1B1E3
		mov	byte_26330, 0D0h ; 'Ð'
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
		push	8
		call	sub_14CEE
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 9
		mov	byte ptr word_26006, 20h ; ' '
		mov	dword_26002, 4040803h
		mov	byte ptr word_26006+1, 10h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		call	word_25344
		mov	byte_26330, 0D4h ; 'Ô'

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
		add	al, 0F8h ; 'ø'
		mov	byte ptr word_26006, al
		push	0Fh
		call	sub_14CEE

loc_1B256:
					; sub_1B1E5+48j ...
		cmp	word_26332, 60h	; '`'
		jl	short loc_1B26D
		mov	byte_26330, 0D0h ; 'Ð'
		mov	word_26332, 0
		mov	byte_2D084, 0

loc_1B26D:
		pop	bp
		retn
sub_1B1E5	endp

; ---------------------------------------------------------------------------
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
		push	large 1800180h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 0C0h ; 'À'
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

loc_1B2F7:				; DATA XREF: seg003:off_1B3BAo
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
					; DATA XREF: seg003:613Co
		call	sub_1B0A4
		jmp	short loc_1B32F
; ---------------------------------------------------------------------------

loc_1B327:
					; DATA XREF: seg003:613Eo
		call	sub_1B153
		jmp	short loc_1B32F
; ---------------------------------------------------------------------------

loc_1B32C:
					; DATA XREF: seg003:6140o
		call	sub_1B1E5

loc_1B32F:
		cmp	byte_2D085, 0
		jz	short loc_1B34A
		push	large 1800180h
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
		mov	byte_26331, 0FEh ; 'þ'
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	large 800030h
		call	sub_1597C
		push	0Ch
		call	sub_14CEE
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
; ---------------------------------------------------------------------------
		db 0
off_1B3BA	dw offset loc_1B2F7	; DATA XREF: seg003:6072r
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
		cmp	ax, 40h	; '@'
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
		cmp	di, 40h	; '@'
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
					; seg003:loc_1C805p

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		mov	word_2CED6, 80h	; '€'
		mov	word_2CED8, 80h	; '€'
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
					; sub_1B446+34j ...
		jmp	loc_1B545
; ---------------------------------------------------------------------------

loc_1B48B:
		cmp	byte ptr [si], 2
		jz	loc_1B535
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		add	ax, 80h	; '€'
		cmp	ax, 100h
		ja	short loc_1B4B1
		add	dx, 80h	; '€'
		cmp	dx, 100h
		ja	short loc_1B4B1
		mov	byte_2CEC1, 1

loc_1B4B1:
					; sub_1B446+64j
		mov	eax, [si+2]
		mov	dword_2CED2, eax
		call	sub_126B3
		mov	[bp+var_2], ax
		or	ax, ax
		jz	loc_1B548
		cmp	word ptr [si+12h], 0D4h	; 'Ô'
		jz	short loc_1B4D2
		push	0Ah
		jmp	short loc_1B52E
; ---------------------------------------------------------------------------

loc_1B4D2:
		mov	word ptr [si+16h], 1
		mov	ax, [bp+var_2]
		sub	[si+14h], ax
		push	4
		call	sub_14CEE
		cmp	word ptr [si+14h], 0
		jge	short loc_1B548
		inc	byte ptr [si]
		mov	word ptr [si+0Eh], 0
		mov	word ptr [si+12h], 0E0h	; 'à'
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
					; sub_1B446+D9j
		push	3

loc_1B52E:
		call	sub_14CEE
		jmp	short loc_1B548
; ---------------------------------------------------------------------------

loc_1B535:
		test	byte ptr [si+0Eh], 3
		jnz	short loc_1B548
		inc	word ptr [si+12h]
		cmp	word ptr [si+12h], 0E4h	; 'ä'
		jl	short loc_1B548

loc_1B545:
		mov	byte ptr [si], 0

loc_1B548:
					; sub_1B446+7Dj ...
		inc	di
		add	si, 1Ah

loc_1B54C:
		cmp	di, 40h	; '@'
		jl	loc_1B461
		pop	di
		pop	si
		leave
		retn
sub_1B446	endp

; ---------------------------------------------------------------------------
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
		mov	byte_26344, 0D0h ; 'Ð'
		call	word_25344
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
		push	3
		call	sub_14CEE

loc_1B5E2:
		cmp	word_26346, 0A0h ; ' '
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
		cmp	word_26346, 40h	; '@'
		jl	short loc_1B624
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1B624:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 8
		jnz	short loc_1B64D
		mov	byte ptr word_26006, 80h ; '€'
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 2
		mov	byte_26344, 0D0h ; 'Ð'
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
		call	word_25344
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 6
		mov	byte ptr word_26006, al
		push	3
		call	sub_14CEE

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
		cmp	word_26346, 40h	; '@'
		jl	short loc_1B6C0
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1B6C0:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 8
		jnz	short loc_1B6ED
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 4
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr dword_26002, 18h
		call	word_25344
		mov	byte_26344, 0D0h ; 'Ð'
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
		push	0Fh
		call	sub_14CEE

loc_1B71B:
		cmp	word_26346, 0A0h ; ' '
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
		cmp	word_26346, 40h	; '@'
		jl	short loc_1B750
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	dx, 0FFE0h
		push	dx
		call	sub_16BD9

loc_1B750:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1B799
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 3
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	word ptr dword_26002, 0C05h
		mov	byte ptr word_26006, 0
		call	word_25344
		mov	byte_26344, 0D0h ; 'Ð'
		mov	byte_2BC88, 40h	; '@'
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
		add	al, 0F4h ; 'ô'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0F4h ; 'ô'
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
		push	0Fh
		call	sub_14CEE

loc_1B7F9:
		cmp	word_26346, 0A0h ; ' '
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
		cmp	word_26346, 40h	; '@'
		jl	short loc_1B82E
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	dx, 0FFE0h
		push	dx
		call	sub_16BD9

loc_1B82E:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1B858
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	large 90008h
		call	sub_16A6B
		mov	byte_26344, 0D0h ; 'Ð'
		mov	byte_2BC88, 20h	; ' '
		jmp	short loc_1B8C4
; ---------------------------------------------------------------------------

loc_1B858:
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1B866
		push	0Fh
		call	sub_14CEE

loc_1B866:
		mov	ax, word_26346
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1B8A6
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 40h	; '@'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 40h	; '@'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 40h	; '@'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 40h	; '@'
		mov	byte ptr word_2BC71, al
		mov	al, byte_2D083
		add	byte ptr word_2BC71, al

loc_1B8A6:
		cmp	word_26346, 40h	; '@'
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
; ---------------------------------------------------------------------------
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
		call	word_25344
		mov	byte_26344, 0D0h ; 'Ð'
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
		push	0Fh
		call	sub_14CEE

loc_1B927:
		cmp	word_26346, 40h	; '@'
		jnz	short loc_1B958
		mov	al, byte_2D084
		neg	al
		mov	byte_2D084, al
		cmp	byte_2D084, 7Fh	; ''
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
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	dx, 0FFE7h
		push	dx
		call	sub_16BD9

loc_1B96F:
		mov	al, 0
		pop	bp
		retn

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
		mov	byte_26344, 0D0h ; 'Ð'
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
		cmp	word_26346, 80h	; '€'
		jl	short loc_1B9EE
		cmp	word_26346, 140h
		jge	short loc_1B9E1
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	dx, 0FFE0h
		jmp	short loc_1B9EA
; ---------------------------------------------------------------------------

loc_1B9E1:
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx

loc_1B9EA:
		push	dx
		call	sub_16BD9

loc_1B9EE:
					; sub_1B973+3Ej ...
		mov	al, 0
		pop	bp
		retn
sub_1B973	endp

; ---------------------------------------------------------------------------
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

loc_1BA22:				; DATA XREF: seg003:off_1BD18o
		cmp	word_26346, 1
		jnz	short loc_1BA63
		mov	word_26342, 1EDCh
		mov	word_2634C, 11F8h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0C4h ; 'Ä'
		mov	word_2C96E, 0C6h ; 'Æ'
		mov	word_2C970, 0C5h ; 'Å'
		mov	word_2C972, 0C4h ; 'Ä'
		mov	word_2BC82, 0D8h ; 'Ø'

loc_1BA63:
		call	sub_1FB07
		cmp	word_26346, 40h	; '@'
		jl	loc_1BD09
		inc	byte_26345
		mov	word_26346, 0
		push	0Dh
		call	sub_14CEE
		mov	word_23F5A, 23FCh
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BA89:
					; DATA XREF: seg003:6A9Ao
		call	sub_1FB07
		cmp	word_26346, 40h	; '@'
		jl	loc_1BD09
		mov	byte_26344, 0CCh ; 'Ì'
		inc	byte_26345
		mov	word_26346, 0
		mov	word_2D06C, 60A2h
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BAAD:
					; DATA XREF: seg003:6A9Co
		call	sub_1FB07
		push	large 0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1BD09
		mov	byte_26344, 0CCh ; 'Ì'
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
		mov	word_2CE42, 62D7h
		mov	word_2C96E, 0CEh ; 'Î'
		mov	word_2C970, 0CDh ; 'Í'
		mov	word_2C972, 0CCh ; 'Ì'
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BB14:
					; DATA XREF: seg003:6A9Eo
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
		mov	ax, [bx+1E26h]
		mov	word_2CE42, ax
		jmp	short loc_1BB6D
; ---------------------------------------------------------------------------

loc_1BB69:
		call	word_2CE42

loc_1BB6D:
		call	sub_1FADD
		or	al, al
		jz	loc_1BD09
		push	0Ah
		call	sub_17416

loc_1BB7B:
		push	large 10C80h
		jmp	loc_1BC4E
; ---------------------------------------------------------------------------

loc_1BB84:
					; DATA XREF: seg003:6AA0o
		call	sub_1FADD
		push	large 0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1BD09
		inc	byte_26345
		mov	word_26346, 0
		mov	word_2CE42, 6444h
		mov	byte_26349, 1
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BBAE:
					; DATA XREF: seg003:6AA2o
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
		mov	ax, [bx+1E2Ah]
		mov	word_2CE42, ax
		jmp	short loc_1BBFA
; ---------------------------------------------------------------------------

loc_1BBF6:
		call	word_2CE42

loc_1BBFA:
		call	sub_1FADD
		or	al, al
		jz	loc_1BD09
		push	0Ah
		call	sub_17416

loc_1BC08:
		push	large 204B0h
		jmp	short loc_1BC4E
; ---------------------------------------------------------------------------

loc_1BC10:
					; DATA XREF: seg003:6AA4o
		call	sub_1FADD
		push	large 0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1BD09
		inc	byte_26345
		mov	word_26346, 0
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BC2F:
					; DATA XREF: seg003:6AA6o
		call	sub_1B973
		cmp	word_26346, 7D0h
		jge	short loc_1BC48
		call	sub_1FADD
		or	al, al
		jz	loc_1BD09
		push	0Ah
		call	sub_17416

loc_1BC48:
		push	large 30000h

loc_1BC4E:
		call	sub_1FB6E
		jmp	loc_1BD09
; ---------------------------------------------------------------------------

loc_1BC54:
					; DATA XREF: seg003:6AA8o
		call	sub_1FADD
		push	large 0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1BD09
		inc	byte_26345
		mov	word_26346, 0
		mov	word_2CE42, 65B2h
		mov	byte_26349, 1
		mov	byte_2D084, 8
		mov	byte_2D085, 10h
		mov	byte_2D083, 0F8h ; 'ø'
		jmp	short loc_1BD09
; ---------------------------------------------------------------------------

loc_1BC8C:
					; DATA XREF: seg003:6AAAo
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
		mov	ax, [bx+1E2Eh]
		mov	word_2CE42, ax
		jmp	short loc_1BCDB
; ---------------------------------------------------------------------------

loc_1BCD7:
		call	word_2CE42

loc_1BCDB:
		call	sub_1FADD
		or	al, al
		jz	short loc_1BD09
		mov	byte ptr word_2634A+1, 1

loc_1BCE7:
		push	4
		call	sub_162CC
		mov	word_26346, 0
		mov	byte_26345, 0FDh ; 'ý'
		call	sub_1B3C2
		mov	word_2D06C, 1240h
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
; ---------------------------------------------------------------------------
off_1BD18	dw offset loc_1BA22	; DATA XREF: seg003:679Dr
		dw offset loc_1BA89
		dw offset loc_1BAAD
		dw offset loc_1BB14
		dw offset loc_1BB84
		dw offset loc_1BBAE
		dw offset loc_1BC10
		dw offset loc_1BC2F
		dw offset loc_1BC54
		dw offset loc_1BC8C
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1BD57
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 2
		mov	byte ptr word_25FFA+1, 2Eh ; '.'
		mov	byte ptr dword_26002, 2
		mov	byte ptr word_26006, 40h ; '@'
		mov	byte_26344, 0C0h ; 'À'
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
		push	3
		call	sub_14CEE

loc_1BD99:
		cmp	word_26346, 0A0h ; ' '
		jnz	short loc_1BDB0
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		jmp	short loc_1BDCD
; ---------------------------------------------------------------------------

loc_1BDB0:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1BDCB
		cmp	word_26346, 40h	; '@'
		jl	short loc_1BDCB
		mov	ax, word_26346
		mov	bx, 40h	; '@'
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
; ---------------------------------------------------------------------------
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
		mov	byte_26344, 0C0h ; 'À'
		mov	byte_2D085, 60h	; '`'
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
		mov	byte_2C977, 0C0h ; 'À'
		jmp	short loc_1BE4E
; ---------------------------------------------------------------------------

loc_1BE40:
		mov	al, 80h	; '€'
		sub	al, byte_2D085
		mov	byte ptr word_26006, al
		mov	byte_2C977, 40h	; '@'

loc_1BE4E:
		call	sub_15A9C
		mov	al, byte_2D085
		add	al, 9
		mov	byte_2D085, al
		push	3
		call	sub_14CEE

loc_1BE60:
		cmp	word_26346, 0C0h ; 'À'
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
		cmp	word_26346, 40h	; '@'
		jl	short loc_1BE92
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1BE92:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		call	word_25344

loc_1BED4:
		cmp	si, 80h	; '€'
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
; ---------------------------------------------------------------------------
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
		call	word_25344

loc_1BF31:
		cmp	si, 80h	; '€'
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
; ---------------------------------------------------------------------------
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
		mov	byte ptr word_2BC71, 80h ; '€'
		mov	word_2BC84, 18h
		mov	word_2BC80, 1
		mov	word_2BC82, 0D4h ; 'Ô'
		mov	byte ptr word_25FFA, 12h
		mov	byte_26000, 0Ch
		mov	byte ptr word_25FFA+1, 0
		mov	byte ptr dword_26002, 4
		mov	byte ptr word_26006+1, 20h ; ' '
		call	word_25344

loc_1BF9C:
		cmp	si, 80h	; '€'
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
		add	al, 0F0h ; 'ð'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0F0h ; 'ð'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 4
		mov	byte ptr word_2BC71, al

loc_1BFD7:
		pop	si
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1C004
		mov	byte_26344, 0C0h ; 'À'
		mov	byte_2BC88, 30h	; '0'
		mov	word_2BC84, 18h
		mov	word_2BC80, 1
		mov	word_2BC82, 0D4h ; 'Ô'
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
		mov	byte ptr word_26006, 40h ; '@'
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
		push	3
		call	sub_14CEE
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
		add	al, 0E0h ; 'à'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD
		mov	al, byte ptr word_2BC71
		add	al, 0E0h ; 'à'
		mov	byte ptr word_2BC71, al
		call	sub_1B3DD

loc_1C0AD:
		cmp	word_26346, 0E0h ; 'à'
		jnz	short loc_1C0C4
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		jmp	short loc_1C0E1
; ---------------------------------------------------------------------------

loc_1C0C4:
		cmp	byte ptr word_2634A+1, 2
		jb	short loc_1C0DF
		cmp	word_26346, 40h	; '@'
		jl	short loc_1C0DF
		mov	ax, word_26346
		mov	bx, 40h	; '@'
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
; ---------------------------------------------------------------------------
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
		mov	byte_26344, 0C0h ; 'À'
		mov	byte_2C977, 0B6h ; '¶'
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
		mov	byte ptr word_26006, 80h ; '€'
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
		push	3
		call	sub_14CEE

loc_1C15E:
		cmp	word_26346, 0C0h ; 'À'
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
		cmp	word_26346, 40h	; '@'
		jl	short loc_1C190
		mov	ax, word_26346
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9

loc_1C190:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1C1C1
		mov	byte_26344, 0C0h ; 'À'
		mov	byte_2BC88, 1Ch
		mov	word_2BC84, 6
		mov	word_2BC80, 1
		mov	byte ptr word_2BC71, 80h ; '€'
		mov	word_2BC82, 0D4h ; 'Ô'
		jmp	short loc_1C239
; ---------------------------------------------------------------------------

loc_1C1C1:
		cmp	word_26346, 20h	; ' '
		jle	short loc_1C239
		cmp	word_26346, 80h	; '€'
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
		push	3
		call	sub_14CEE
		jmp	short loc_1C239
; ---------------------------------------------------------------------------

loc_1C20F:
		mov	al, byte_2D081
		neg	al
		mov	byte_2D081, al
		cmp	byte_2D081, 7Fh	; ''
		jnb	short loc_1C225
		mov	byte_2D080, 0
		jmp	short loc_1C22A
; ---------------------------------------------------------------------------

loc_1C225:
		mov	byte_2D080, 80h	; '€'

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
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	word_26346, 10h
		jnz	short loc_1C2AB
		mov	byte_26344, 0C0h ; 'À'
		push	0Fh
		call	sub_157E4
		add	ax, 10h
		mov	[bp-2],	ax
		mov	word_26318, 20h	; ' '
		mov	word_2631A, 5Ah	; 'Z'
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	dl, 40h	; '@'
		sub	dl, [bp-2]
		sub	dl, al
		mov	byte_26312, dl
		push	0
		call	sub_17548
		mov	al, byte_26312
		add	al, [bp-2]
		mov	byte_26312, al
		push	1
		call	sub_17548
		mov	al, byte_26312
		add	al, [bp-2]
		mov	byte_26312, al
		push	2
		call	sub_17548
		mov	al, byte_26312
		add	al, [bp-2]
		mov	byte_26312, al
		push	3
		call	sub_17548
		mov	byte_2D083, 0F8h ; 'ø'
		jmp	loc_1C347
; ---------------------------------------------------------------------------

loc_1C2AB:
		cmp	word_26346, 20h	; ' '
		jle	loc_1C347
		cmp	word_26346, 80h	; '€'
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
		mov	al, 80h	; '€'
		sub	al, byte_2D083
		mov	byte ptr word_26006, al
		call	sub_15A70
		mov	al, byte_2D083
		add	al, 8
		mov	byte_2D083, al
		cmp	byte_2D083, 30h	; '0'
		jbe	short loc_1C316
		mov	byte_2D083, 0F8h ; 'ø'

loc_1C316:
		push	3
		call	sub_14CEE

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
		mov	word_2CE44, 6C16h
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
		cmp	[bp+var_2], 0A0h ; ' '
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
		cmp	[bp+var_2], 0D4h ; 'Ô'
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
		cmp	[bp+var_2], 0B4h ; '´'
		jnz	short loc_1C426
		mov	al, byte_2D085
		neg	al
		mov	byte_2D085, al

loc_1C426:
					; sub_1C34B+CAj ...
		cmp	[bp+var_2], 70h	; 'p'
		jg	short loc_1C445
		mov	al, byte_25FE2
		mov	ah, 0
		add	word_2CE3E, ax
		cmp	word_2CE3E, 80h	; '€'
		jle	short loc_1C483
		mov	word_2CE3E, 80h	; '€'
		jmp	short loc_1C483
; ---------------------------------------------------------------------------

loc_1C445:
		cmp	[bp+var_2], 0C0h ; 'À'
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
		cmp	[bp+var_2], 0D4h ; 'Ô'
		jle	short loc_1C483
		push	1Fh
		call	sub_157E4
		or	ax, ax
		jnz	short loc_1C483
		mov	ax, 0FFh
		sub	ax, [bp+var_2]
		add	word_26346, ax

loc_1C483:
					; sub_1C34B+F8j ...
		cmp	[bp+var_2], 0
		jnz	short loc_1C4A3
		mov	al, byte_2D080
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		add	dx, dx
		mov	bx, dx
		mov	ax, [bx+1E38h]
		mov	word_2CE44, ax
		inc	byte_2D080

loc_1C4A3:
		cmp	word_26346, 120h
		jl	short loc_1C4C7
		call	word_2CE44
		cmp	word_26346, 220h
		jl	short loc_1C4C7
		cmp	[bp+var_2], 60h	; '`'
		jg	short loc_1C4C7
		mov	ax, [bp+var_2]
		add	ax, 0FFE0h
		push	ax
		call	sub_16BD9

loc_1C4C7:
					; sub_1C34B+16Aj ...
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
					; sub_1C34B+6Aj ...
		mov	al, 0
		pop	si
		leave
		retn
sub_1C34B	endp

; ---------------------------------------------------------------------------
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

loc_1C54D:				; DATA XREF: seg003:off_1C816o
		cmp	word_26346, 1
		jnz	short loc_1C58E
		mov	word_26342, 1E78h
		mov	word_2634C, 16A8h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0B4h ; '´'
		mov	word_2C96E, 0B6h ; '¶'
		mov	word_2C970, 0B5h ; 'µ'
		mov	word_2C972, 0B4h ; '´'
		mov	word_2BC82, 0D4h ; 'Ô'

loc_1C58E:
		call	sub_1FB07
		cmp	word_26346, 40h	; '@'
		jl	loc_1C805
		inc	byte_26345
		mov	word_26346, 0
		push	0Dh
		call	sub_14CEE
		mov	word_23F5A, 23FCh
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C5B4:
					; DATA XREF: seg003:7598o
		call	sub_1FB07
		cmp	word_26346, 40h	; '@'
		jl	loc_1C805
		mov	byte_26344, 0CCh ; 'Ì'
		inc	byte_26345
		mov	word_26346, 0
		mov	word_2D06C, 60A2h
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C5D8:
					; DATA XREF: seg003:759Ao
		call	sub_1FB07
		push	large 0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1C805
		mov	byte_26344, 0BCh ; '¼'
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		push	4
		call	sub_162CC
		push	word_26335+1
		push	word_26338
		call	sub_EC86
		mov	word_2CE42, 6AACh
		mov	word_2C96E, 0BEh ; '¾'
		mov	word_2C970, 0BDh ; '½'
		mov	word_2C972, 0BCh ; '¼'
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C630:
					; DATA XREF: seg003:759Co
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
		mov	ax, [bx+1E46h]
		mov	word_2CE42, ax
		jmp	short loc_1C67C
; ---------------------------------------------------------------------------

loc_1C678:
		call	word_2CE42

loc_1C67C:
		call	sub_1FADD
		or	al, al
		jz	loc_1C805
		push	0Ah
		call	sub_17416

loc_1C68A:
		push	large 10AF0h
		jmp	loc_1C755
; ---------------------------------------------------------------------------

loc_1C693:
					; DATA XREF: seg003:759Eo
		call	sub_1FADD
		push	large 0C000800h
		call	sub_16CCC
		or	al, al
		jz	loc_1C805
		inc	byte_26345
		mov	word_26346, 0
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C6B2:
					; DATA XREF: seg003:75A0o
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
		push	large 304B0h
		jmp	short loc_1C755
; ---------------------------------------------------------------------------

loc_1C6E1:
					; DATA XREF: seg003:75A2o
		call	sub_1FADD
		push	large 0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1C805
		jmp	short loc_1C76D
; ---------------------------------------------------------------------------

loc_1C6F5:
					; DATA XREF: seg003:75A4o
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
		mov	ax, [bx+1E3Eh]
		mov	word_2CE42, ax
		jmp	short loc_1C741
; ---------------------------------------------------------------------------

loc_1C73D:
		call	word_2CE42

loc_1C741:
		call	sub_1FADD
		or	al, al
		jz	loc_1C805
		push	0Ah
		call	sub_17416

loc_1C74F:
		push	large 10000h

loc_1C755:
		call	sub_1FB6E
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C75B:
					; DATA XREF: seg003:75A6o
		call	sub_1FADD
		push	large 0C000600h
		call	sub_16CCC
		or	al, al
		jz	loc_1C805

loc_1C76D:
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_2D080, 80h	; '€'
		mov	byte_2D081, 0FCh ; 'ü'
		jmp	loc_1C805
; ---------------------------------------------------------------------------

loc_1C784:
					; DATA XREF: seg003:75A8o
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
		mov	ax, [bx+1E42h]
		mov	word_2CE42, ax
		jmp	short loc_1C7D7
; ---------------------------------------------------------------------------

loc_1C7D3:
		call	word_2CE42

loc_1C7D7:
		call	sub_1FADD
		or	al, al
		jz	short loc_1C805
		mov	byte ptr word_2634A+1, 1

loc_1C7E3:
		push	4
		call	sub_162CC
		mov	word_26346, 0
		mov	byte_26345, 0FDh ; 'ý'
		call	sub_1B3C2
		mov	word_2D06C, 1240h
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
; ---------------------------------------------------------------------------
		db 0
off_1C816	dw offset loc_1C54D	; DATA XREF: seg003:72C8r
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
		push	0C1h ; 'Á'
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
		cmp	di, 40h	; '@'
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
					; sub_1C8A3+1Fj
		cmp	word ptr [si+0Eh], 0
		jbe	short loc_1C920
		dec	word ptr [si+0Eh]
		cmp	word ptr [si+0Eh], 0
		jnz	short loc_1C8F2
		push	0C1h ; 'Á'
		push	word ptr [si+1]
		call	sub_159E6
		mov	ah, 0
		mov	[si+12h], ax
		push	3
		call	sub_14CEE
		jmp	short loc_1C920
; ---------------------------------------------------------------------------

loc_1C8F2:
		test	di, 1
		jz	short loc_1C90C
		add	word ptr [si+12h], 2
		cmp	word ptr [si+12h], 0E1h	; 'á'
		jl	loc_1C9AF
		sub	word ptr [si+12h], 20h ; ' '
		jmp	loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C90C:
		sub	word ptr [si+12h], 2
		cmp	word ptr [si+12h], 0C1h	; 'Á'
		jge	loc_1C9AF
		add	word ptr [si+12h], 20h ; ' '
		jmp	loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C920:
					; sub_1C8A3+4Dj
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
					; sub_1C8A3+8Cj ...
		jmp	short loc_1C9AC
; ---------------------------------------------------------------------------

loc_1C93F:
		cmp	byte ptr [si], 2
		jz	short loc_1C969
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		add	ax, 70h	; 'p'
		cmp	ax, 0E0h ; 'à'
		ja	short loc_1C967
		add	dx, 70h	; 'p'
		cmp	dx, 0E0h ; 'à'
		ja	short loc_1C967
		mov	byte_2CEC1, 1
		mov	byte ptr [si], 2
		jmp	short loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C967:
					; sub_1C8A3+B8j
		jmp	short loc_1C9AF
; ---------------------------------------------------------------------------

loc_1C969:
		cmp	word ptr [si+12h], 0E1h	; 'á'
		jge	short loc_1C992
		mov	word ptr [si+12h], 0E1h	; 'á'
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
		cmp	word ptr [si+12h], 0E5h	; 'å'
		jl	short loc_1C9AF

loc_1C9AC:
		mov	byte ptr [si], 0

loc_1C9AF:
					; sub_1C8A3+5Ej ...
		inc	di
		add	si, 1Ah

loc_1C9B3:
		cmp	di, 40h	; '@'
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
		mov	byte_26344, 0BCh ; '¼'

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
		mov	byte_26344, 0B4h ; '´'
		mov	al, 1
		leave
		retn	4
; ---------------------------------------------------------------------------

loc_1CA3C:
		mov	al, 0
		leave
		retn	4
sub_1C9BE	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 10h
		jnz	short loc_1CA6B
		mov	byte_26344, 0B8h ; '¸'
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
		mov	al, 80h	; '€'
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
		mov	al, 80h	; '€'
		sub	al, byte ptr word_2BC71
		mov	byte ptr word_2BC71, al

loc_1CABB:
		mov	al, byte ptr word_2BC71
		add	al, 0FAh ; 'ú'
		mov	byte ptr word_2BC71, al
		cmp	byte ptr word_2BC71, 0Ch
		ja	short loc_1CAD5
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1CAD5:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jge	short loc_1CB23
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	large 70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	short loc_1CB6F
		mov	byte_26344, 0B8h ; '¸'
		mov	byte ptr word_25FFA, 13h
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte_26000, 4
		mov	byte ptr word_26006+1, 3Ch ; '<'
		mov	byte ptr dword_26002, 10h
		call	word_25344
		push	8
		call	sub_14CEE
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
		push	3
		call	sub_14CEE

loc_1CB5D:
		cmp	word_26346, 50h	; 'P'
		jnz	short loc_1CB6F
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1CB6F:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		push	si
		cmp	word_26346, 20h	; ' '
		jge	short loc_1CBD2
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	large 70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_1CCD0
		mov	byte_26344, 0B8h ; '¸'
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	byte_26000, 0
		mov	byte ptr word_26006+1, 60h ; '`'
		call	word_25344
		push	8
		call	sub_14CEE
		mov	word_2BC7E, 20h	; ' '
		mov	byte_2BC88, 4Ch	; 'L'
		mov	byte_2D083, 0
		mov	byte_2D082, 20h	; ' '
		jmp	loc_1CCD0
; ---------------------------------------------------------------------------

loc_1CBD2:
		mov	ax, word_26346
		mov	bx, 40h	; '@'
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
		push	3
		call	sub_14CEE

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
		mov	[bp-1],	al
		push	600h
		call	sub_157FA
		mov	word_2BC74, ax
		push	1600h
		call	sub_157FA
		add	ax, 100h
		mov	word_2BC71+1, ax
		push	ax
		push	word_2BC74
		push	word ptr [bp-1]
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
		push	large 100008h
		push	large 40004h
		call	sub_E758
		mov	byte_2D076, al
		push	large 280030h
		push	large 340034h
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
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 10h
		jge	short loc_1CD26
		mov	ax, word_26346
		dec	ax
		push	ax
		push	large 70006h
		call	sub_16A6B
		cmp	word_26346, 4
		jnz	loc_1CE0B
		mov	byte_26344, 0B8h ; '¸'
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 2
		mov	byte_26001, 0Ah
		mov	byte ptr word_26006+1, 38h ; '8'
		mov	word ptr dword_26002, 205h
		push	8
		call	sub_14CEE
		mov	byte_2D085, 60h	; '`'
		mov	byte_2D084, 40h	; '@'
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
		add	al, 80h	; '€'
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	al, byte ptr word_26006
		add	al, 80h	; '€'
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
		add	al, 80h	; '€'
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	al, byte ptr word_26006
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		call	sub_15A70
		mov	al, byte_2D085
		neg	al
		mov	byte_2D085, al
		add	al, 0F8h ; 'ø'
		mov	byte_2D085, al
		mov	al, byte_2D084
		add	al, 0FAh ; 'ú'
		mov	byte_2D084, al
		push	3
		call	sub_14CEE

loc_1CDF8:
		cmp	word_26346, 100h
		jnz	short loc_1CE0B
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1CE0B:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 10h
		jge	short loc_1CE63
		mov	ax, word_26346
		dec	ax
		push	ax
		push	large 70006h
		call	sub_16A6B
		cmp	word_26346, 4
		jnz	loc_1CED7
		mov	byte_26344, 0B8h ; '¸'
		mov	byte ptr word_25FFA, 10h
		mov	byte_26000, 3
		mov	byte ptr word_26006+1, 38h ; '8'
		mov	byte ptr dword_26002+1,	14h
		mov	byte ptr word_26006, 0
		mov	byte ptr word_25FFA+1, 44h ; 'D'
		call	word_25344
		push	8
		call	sub_14CEE
		mov	byte_2D085, 80h	; '€'
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
		mov	al, 80h	; '€'
		sub	al, byte_2D085
		mov	ah, 0
		push	ax
		call	sub_14E6C
		mov	byte ptr dword_26002, 4
		call	sub_15A5C
		mov	al, byte_2D085
		add	al, 8
		mov	byte_2D085, al
		push	3
		call	sub_14CEE

loc_1CEC4:
		cmp	word_26346, 0C0h ; 'À'
		jnz	short loc_1CED7
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1CED7:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		push	si
		push	di
		cmp	word_26346, 20h	; ' '
		jge	short loc_1CF57
		mov	ax, word_26346
		add	ax, 0FFF0h
		push	ax
		push	large 70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_1D081
		mov	byte_26344, 0B8h ; '¸'
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	byte_26000, 0
		mov	byte ptr word_26006+1, 60h ; '`'
		call	word_25344
		push	8
		call	sub_14CEE
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
		mov	bx, 40h	; '@'
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
		push	3
		call	sub_14CEE

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
		mov	[bp-1],	al
		push	600h
		call	sub_157FA
		mov	word_2BC74, ax
		push	1600h
		call	sub_157FA
		add	ax, 100h
		mov	word_2BC71+1, ax
		push	ax
		push	word_2BC74
		push	word ptr [bp-1]
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
		push	large 22001Ch
		push	large 140014h
		call	sub_E758
		mov	byte_2D077, al
		push	large 280030h
		push	large 340030h
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
		push	large 70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_1D1C4
		mov	byte_26344, 0B8h ; '¸'
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 34h ; '4'
		mov	byte_26000, 2
		mov	byte ptr dword_26002, 5
		push	large 180010h
		push	large 0C000Ah
		call	sub_E758
		mov	byte ptr dword_26002+1,	al
		mov	byte ptr word_26006+1, 80h ; '€'
		push	8
		call	sub_14CEE
		mov	word_2BC7E, 20h	; ' '
		mov	byte_2BC88, 40h	; '@'
		push	200h
		call	sub_157FA
		mov	word ptr dword_2634E+2,	ax
		push	large 28001Eh
		push	large 180010h
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
		add	al, 80h	; '€'
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
		cmp	byte ptr word_26006+1, 60h ; '`'
		jbe	short loc_1D1B9
		mov	byte ptr word_26006+1, 8
		push	0Fh
		call	sub_14CEE
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
					; sub_1D085+A4j ...
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
		push	large 70006h
		call	sub_16A6B
		cmp	word_26346, 10h
		jnz	loc_1D269
		mov	byte_26344, 0B8h ; '¸'
		mov	byte ptr word_25FFA, 10h
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	byte_26000, 4
		mov	byte ptr dword_26002, 12h
		mov	byte_26001, 2
		mov	byte ptr word_26006+1, 26h ; '&'
		call	word_25344
		push	8
		call	sub_14CEE
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
		mov	byte_2C977, 40h	; '@'
		mov	al, 80h	; '€'
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		jmp	short loc_1D257
; ---------------------------------------------------------------------------

loc_1D252:
		mov	byte_2C977, 0C0h ; 'À'

loc_1D257:
		call	sub_15A9C
		inc	byte_2D084
		inc	byte_2D085
		push	3
		call	sub_14CEE

loc_1D269:
					; sub_1D1C6+6Dj
		pop	bp
		retn
sub_1D1C6	endp

; ---------------------------------------------------------------------------
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

loc_1D29C:				; DATA XREF: seg003:off_1D524o
		cmp	word_26346, 1
		jnz	short loc_1D2EF
		mov	word_26342, 206Ch
		mov	word_2634C, 1D4Ch
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0B4h ; '´'
		mov	word_2633E, 40h	; '@'
		mov	si, 0C1h ; 'Á'
		jmp	short loc_1D2D7
; ---------------------------------------------------------------------------

loc_1D2D0:
		push	si
		call	sub_35A2
		inc	si

loc_1D2D7:
		cmp	si, 0E5h ; 'å'
		jl	short loc_1D2D0
		mov	word_2C96E, 0B4h ; '´'
		mov	word_2C970, 0B4h ; '´'
		mov	word_2C972, 0B4h ; '´'

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
		push	0Ah
		call	sub_14CEE

loc_1D320:
		cmp	word_26346, 40h	; '@'
		jge	short loc_1D32D
		call	sub_1FB07
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D32D:
		mov	byte_26344, 0BCh ; '¼'
		add	word_26335+1, 20h ; ' '
		cmp	word_26335+1, 0C00h
		jl	loc_1D513
		mov	byte_26344, 0B4h ; '´'
		inc	byte_26345
		mov	word_26346, 0
		push	0Dh
		call	sub_14CEE
		mov	word_23F5A, 248Eh
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D360:
					; DATA XREF: seg003:82A6o
		call	sub_1FB07
		cmp	word_26346, 40h	; '@'
		jl	loc_1D513
		inc	byte_26345
		mov	word_26346, 0
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	word_2CE46, 77C2h
		mov	word_2D06C, 6180h
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D38F:
					; DATA XREF: seg003:82A8o ...
		mov	al, byte_26349
		mov	ah, 0
		or	ax, ax
		jz	short loc_1D39F
		cmp	ax, 1
		jz	short loc_1D3EF
		jmp	short loc_1D3F3
; ---------------------------------------------------------------------------

loc_1D39F:
		push	large 200040h
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
		mov	ax, [bx+1E4Ah]
		jmp	short loc_1D3EA
; ---------------------------------------------------------------------------

loc_1D3DA:
		mov	al, byte ptr word_2634A+1
		mov	ah, 0
		and	ax, 1
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+1E52h]

loc_1D3EA:
		mov	word_2CE46, ax
		jmp	short loc_1D3F3
; ---------------------------------------------------------------------------

loc_1D3EF:
		call	word_2CE46

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
		push	large 1644h
		jmp	loc_1D4B7
; ---------------------------------------------------------------------------

loc_1D41A:
		push	large 30A8Ch
		jmp	loc_1D4B7
; ---------------------------------------------------------------------------

loc_1D423:
					; DATA XREF: seg003:82AAo ...
		call	sub_1FADD
		push	large 0C000400h
		call	sub_16CCC
		or	al, al
		jz	loc_1D513
		inc	byte_26345
		mov	word_26346, 0
		cmp	byte_26345, 4
		jnz	short loc_1D44F
		mov	word_2CE46, 78F1h
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D44F:
		mov	word_2CE46, 7C59h
		jmp	loc_1D513
; ---------------------------------------------------------------------------

loc_1D458:
					; DATA XREF: seg003:82ACo ...
		call	word_2CE46
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
		push	large 11194h
		call	sub_1FB6E
		mov	word_2CE46, 7A53h
		jmp	short loc_1D493
; ---------------------------------------------------------------------------

loc_1D48A:
		push	large 104B0h
		call	sub_1FB6E

loc_1D493:
		mov	byte_26349, 1
		jmp	short loc_1D513
; ---------------------------------------------------------------------------

loc_1D49A:
					; DATA XREF: seg003:82B4o
		call	sub_1D085
		cmp	word_26346, 7D0h
		jge	short loc_1D4B1
		call	sub_1FADD
		or	al, al
		jz	short loc_1D513
		push	0Ah
		call	sub_17416

loc_1D4B1:
		push	large 10000h

loc_1D4B7:
		call	sub_1FB6E
		jmp	short loc_1D513
; ---------------------------------------------------------------------------

loc_1D4BC:
					; DATA XREF: seg003:82B6o
		call	sub_1FADD
		push	large 0C000600h
		call	sub_16CCC
		or	al, al
		jz	short loc_1D513
		inc	byte_26345
		mov	word_26346, 0
		mov	byte ptr word_2634A+1, 0
		jmp	short loc_1D513
; ---------------------------------------------------------------------------

loc_1D4DD:
					; DATA XREF: seg003:82B8o
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
		mov	byte_26345, 0FDh ; 'ý'
		mov	word_2D06C, 1240h
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
; ---------------------------------------------------------------------------
		db 0
off_1D524	dw offset loc_1D29C	; DATA XREF: seg003:8017r
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
					; sub_1DB7B+87p ...

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
		cmp	di, 40h	; '@'
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
					; sub_1D58B+4Cj ...
		jmp	short loc_1D655
; ---------------------------------------------------------------------------

loc_1D5E7:
		cmp	byte ptr [si], 3
		jz	short loc_1D612
		sub	ax, word ptr dword_2CEA0
		sub	dx, word ptr dword_2CEA0+2
		add	ax, 80h	; '€'
		cmp	ax, 100h
		ja	short loc_1D610
		add	dx, 80h	; '€'
		cmp	dx, 100h
		ja	short loc_1D610
		mov	byte_2CEC1, 1
		mov	byte ptr [si], 3
		jmp	short loc_1D658
; ---------------------------------------------------------------------------

loc_1D610:
					; sub_1D58B+79j
		jmp	short loc_1D658
; ---------------------------------------------------------------------------

loc_1D612:
		cmp	word ptr [si+12h], 0CCh	; 'Ì'
		jge	short loc_1D63B
		mov	word ptr [si+12h], 0CCh	; 'Ì'
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
		cmp	word ptr [si+12h], 0D0h	; 'Ð'
		jl	short loc_1D658

loc_1D655:
		mov	byte ptr [si], 0

loc_1D658:
					; sub_1D58B+23j ...
		inc	di
		add	si, 1Ah

loc_1D65C:
		cmp	di, 40h	; '@'
		jl	loc_1D599
		pop	di
		pop	si
		pop	bp
		retn
sub_1D58B	endp

; ---------------------------------------------------------------------------
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
		mov	al, 0FEh ; 'þ'

loc_1D6A4:
		mov	byte_2D085, al
		call	word_25344
		push	0Fh
		call	sub_14CEE

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
; ---------------------------------------------------------------------------
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
		push	large 10000Ch
		push	large 80004h
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
		mov	byte ptr word_26006+1, 40h ; '@'
		mov	al, byte ptr word_26006
		add	al, 8
		mov	byte ptr word_26006, al
		call	sub_15A5C
		push	3
		call	sub_14CEE

loc_1D766:
		cmp	word_26346, 60h	; '`'
		jnz	short loc_1D772
		mov	ax, 1
		jmp	short loc_1D774
; ---------------------------------------------------------------------------

loc_1D772:
		xor	ax, ax

loc_1D774:
		pop	bp
		retn

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
		push	large 70006h
		call	sub_16A6B
		cmp	word_26346, 2
		jnz	short loc_1D7DA
		mov	byte_26344, 0B5h ; 'µ'
		mov	byte ptr word_25FFA, 13h
		mov	byte ptr word_25FFA+1, 30h ; '0'
		mov	byte_26000, 4
		mov	byte ptr word_26006+1, 3Ch ; '<'
		mov	byte ptr dword_26002, 10h
		call	word_25344
		push	8
		call	sub_14CEE
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1D7C2:
		call	word_2CE48
		or	al, al
		jz	short loc_1D7DA
		mov	byte_26344, 0B4h ; '´'
		mov	word_26346, 0
		mov	byte_26349, 0

loc_1D7DA:
					; sub_1D776+52j
		pop	bp
		retn
sub_1D776	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1D805
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_26006+1, 1Ch
		mov	byte_26000, 0Dh
		mov	byte ptr dword_26002, 3
		call	word_25344
		push	0Fh
		call	sub_14CEE

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
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1D877
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 2Ch ; ','
		mov	byte_26000, 9
		mov	byte ptr word_26006, 0
		mov	word ptr dword_26002, 402h
		push	large 0C050C06h
		push	large 0D060D07h
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
		push	0Fh
		call	sub_14CEE

loc_1D88E:
		mov	ax, word_26346
		add	ax, 0FFC0h
		push	ax
		call	sub_16BD9
		pop	bp
		retn

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
		mov	byte_26312, 40h	; '@'
		push	2
		call	sub_175A4
		mov	byte_26312, 40h	; '@'
		push	3
		call	sub_175A4
		mov	byte_26312, 38h	; '8'
		push	4
		call	sub_175A4
		mov	byte_26312, 30h	; '0'
		push	5
		call	sub_175A4
		push	8
		call	sub_14CEE
		mov	byte_26344, 0B5h ; 'µ'
		mov	byte_2D085, 0
		mov	byte_2D084, 64h	; 'd'

loc_1D8F7:
		cmp	word_26346, 10h
		jle	loc_1DA17
		cmp	byte_26042, 80h	; '€'
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
		call	word_25344
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
		push	60h ; '`'
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
		mov	byte_26344, 0B8h ; '¸'
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
		push	0Fh
		call	sub_14CEE
		mov	word_2CE06, 8
		jmp	short loc_1DA13
; ---------------------------------------------------------------------------

loc_1D9D5:
		cmp	byte_25FE2, 0
		jz	short loc_1D9E4
		mov	PaletteTone, 96h	; '–'
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
					; sub_1D89A+15Aj
		inc	byte_2D085

loc_1DA17:
					; sub_1D89A+72j ...
		mov	al, 0

loc_1DA19:
		pop	si
		pop	bp
		retn
sub_1D89A	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 80h	; '€'
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
		mov	byte ptr word_2BC71, 40h ; '@'
		push	1Fh
		call	sub_157E4
		add	al, 30h	; '0'
		mov	byte_2BC88, al
		mov	word_2BC82, 0C8h ; 'È'
		call	sub_1D53A
		push	3
		call	sub_14CEE

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
		push	large 10000Ch
		push	large 0A0008h
		call	sub_E758
		mov	byte ptr dword_26002+1,	al
		mov	byte ptr word_26006, 0
		mov	byte ptr word_26006+1, 30h ; '0'
		call	word_25344
		call	sub_15A5C

loc_1DAD0:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 80h	; '€'
		jl	loc_1DB78
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1DB10
		push	large 800030h
		push	large 200018h
		call	sub_E758
		mov	byte_2D084, al
		push	large 200028h
		push	large 300038h
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
		mov	byte_2BC88, 40h	; '@'
		push	3
		call	sub_157FA
		shl	al, 6
		mov	byte ptr word_2BC71, al
		call	sub_17687
		push	3
		call	sub_14CEE

loc_1DB78:
		pop	si
		pop	bp
		retn

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DB7B	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 0A0h ; ' '
		jge	short loc_1DB8C
		mov	al, 0
		jmp	loc_1DC2C
; ---------------------------------------------------------------------------

loc_1DB8C:
		cmp	word_26346, 0C0h ; 'À'
		jge	short loc_1DBB8
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1DBA3
		push	8
		call	sub_14CEE

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
		cmp	word_26346, 0C0h ; 'À'
		jnz	short loc_1DC1D
		mov	word_2BC82, 0C9h ; 'É'
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
		push	40h ; '@'
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
		mov	byte_26344, 0C0h ; 'À'
		push	0Fh
		call	sub_14CEE
		mov	word_2CE06, 8

loc_1DC1D:
					; sub_1DB7B+3Bj ...
		cmp	word_26346, 0C8h ; 'È'
		jnz	short loc_1DC2A
		mov	ax, 1
		jmp	short loc_1DC2C
; ---------------------------------------------------------------------------

loc_1DC2A:
		xor	ax, ax

loc_1DC2C:
					; sub_1DB7B+ADj
		pop	si
		pop	bp
		retn
sub_1DB7B	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 80h	; '€'
		jle	loc_1DCFD
		cmp	word_26346, 81h	; ''
		jnz	short loc_1DC59
		push	large 600020h
		push	large 1C0018h
		call	sub_E758
		mov	byte_2D085, al

loc_1DC59:
		mov	ax, word_26346
		mov	bx, 80h	; '€'
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
		mov	byte_2BC88, 40h	; '@'
		mov	word_2BC82, 0C9h ; 'É'
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
		cmp	si, 40h	; '@'
		jge	short loc_1DCD4
		mov	ax, si
		imul	ax, 3
		mov	byte ptr word_26006, al
		jmp	short loc_1DCE1
; ---------------------------------------------------------------------------

loc_1DCD4:
		mov	ax, si
		imul	ax, 3
		mov	dl, 40h	; '@'
		sub	dl, al
		mov	byte ptr word_26006, dl

loc_1DCE1:
		call	sub_15A70
		mov	al, 80h	; '€'
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		add	word ptr dword_25FFC, 1000h
		call	sub_15A70
		push	0Fh
		call	sub_14CEE

loc_1DCFD:
		pop	si
		pop	bp
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	word_26346, 0C0h ; 'À'
		jl	locret_1E020
		mov	ax, word_26346
		add	ax, 0FF40h
		mov	[bp-2],	ax
		cmp	word_26342, 15E0h
		jle	short loc_1DD27
		cmp	word_26346, 708h
		jl	short loc_1DD72

loc_1DD27:
		cmp	word_22852, 0
		jnz	short loc_1DD72
		mov	byte_26313, 6
		mov	byte_26312, 40h	; '@'
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
		cmp	word ptr [bp-2], 0
		jnz	short loc_1DDC3
		mov	byte_2D084, 20h	; ' '
		mov	byte_2D085, 0
		push	large 400028h
		push	large 20001Ch
		call	sub_E758
		mov	byte_2D083, al
		mov	byte_2D082, 0
		mov	byte_2D081, 0
		mov	byte_2D080, 0
		mov	byte_2D07E, 40h	; '@'
		mov	byte_2D07F, 40h	; '@'
		mov	byte_2D07D, 0

loc_1DDC3:
		mov	byte ptr word_25FFA, 12h
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		mov	byte_26000, 2
		cmp	byte_2D085, 40h	; '@'
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
		mov	al, 80h	; '€'
		sub	al, byte_2D084
		mov	byte ptr word_26006, al
		call	sub_15A8E
		sub	word ptr dword_25FFC, 400h
		mov	al, 80h	; '€'
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
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		add	word ptr dword_25FFC, 0C00h
		call	sub_15A8E
		sub	word ptr dword_25FFC, 400h
		mov	al, byte_2D084
		add	al, 80h	; '€'
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
		add	al, 0FEh ; 'þ'
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
		cmp	byte_2D085, 40h	; '@'
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
		mov	word_2BC82, 0C9h ; 'É'
		call	sub_1D53A

loc_1DF41:
		push	3
		call	sub_14CEE

loc_1DF48:
		cmp	word_22852, 0
		jz	locret_1E020
		cmp	word_22852, 40h	; '@'
		jl	short loc_1DF73
		cmp	word_22852, 40h	; '@'
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
		mov	al, 80h	; '€'
		sub	al, byte_2602A
		mov	byte_26042, al
		mov	al, 80h	; '€'
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
		push	large 340014h
		push	large 10000Ch
		call	sub_E758
		mov	byte_2D083, al
		push	0
		call	sub_162CC

locret_1E020:
		leave
		retn

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E022	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26346, 80h	; '€'
		jl	loc_1E15A
		cmp	word_26346, 80h	; '€'
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
		mov	word_2BC82, 0C8h ; 'È'
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
		add	al, 80h	; '€'
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
		add	al, 88h	; 'ˆ'
		mov	byte ptr word_2BC71, al
		push	3
		call	sub_14CEE

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
		cmp	si, 80h	; '€'
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
		add	al, 0FEh ; 'þ'
		mov	byte_2D085, al

loc_1E0F8:
					; sub_1E022+AAj
		cmp	word_26346, 200h
		jl	short loc_1E13D
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E13D
		cmp	si, 80h	; '€'
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
					; sub_1E022+DCj ...
		cmp	word_26346, 2D0h
		jl	short loc_1E15A
		mov	ax, word_26346
		add	ax, 0FD30h
		mov	bx, 80h	; '€'
		cwd
		idiv	bx
		mov	si, dx
		lea	ax, [si-60h]
		push	ax
		call	sub_16BD9

loc_1E15A:
					; sub_1E022+121j
		pop	si
		pop	bp
		retn
sub_1E022	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E15D	proc near
					; seg003:loc_1E431p
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
					; sub_1E15D+20j ...
		mov	ax, word_26340
		add	word_26338, ax

loc_1E195:
		pop	bp
		retn
sub_1E15D	endp

; ---------------------------------------------------------------------------
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

loc_1E1CD:				; DATA XREF: seg003:off_1E53Co
		cmp	word_26346, 1
		jnz	short loc_1E220
		mov	word_26342, 5910h
		mov	word_2634C, 5078h
		mov	word_2A72A, 400h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0B4h ; '´'
		mov	word_26340, 0
		mov	word_2C96E, 0B7h ; '·'
		mov	word_2C970, 0B6h ; '¶'
		mov	word_2C972, 0B4h ; '´'
		mov	si, 0C8h ; 'È'
		jmp	short loc_1E21A
; ---------------------------------------------------------------------------

loc_1E213:
		push	si
		call	sub_35A2
		inc	si

loc_1E21A:
		cmp	si, 0D0h ; 'Ð'
		jl	short loc_1E213

loc_1E220:
		call	sub_1FB07
		cmp	word_26346, 0C0h ; 'À'
		jl	loc_1E527
		mov	word_26346, 0
		inc	byte_26345
		push	0Dh
		call	sub_14CEE
		mov	word_23F5A, 2C76h
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E247:
					; DATA XREF: seg003:92BEo
		call	sub_1FB07
		cmp	word_26346, 20h	; ' '
		jnz	short loc_1E265
		mov	Palettes, 0
		mov	Palettes+1, 0
		mov	Palettes+2, 0
		mov	byte_25FE9, 1

loc_1E265:
		cmp	word_26346, 40h	; '@'
		jl	loc_1E527
		inc	byte_26345
		mov	byte_26349, 1
		mov	word_26346, 0
		mov	word_2CE48, 83E7h
		jmp	loc_1E36F
; ---------------------------------------------------------------------------

loc_1E286:
					; DATA XREF: seg003:92C0o ...
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
		mov	ax, [bx+1E6Ah]
		mov	word_2CE48, ax
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
		push	large 147E0h
		call	sub_1FB6E
		mov	byte_26349, 1
		mov	word_2CE48, 855Ch
		jmp	loc_1E481
; ---------------------------------------------------------------------------

loc_1E308:
		push	large 13908h
		call	sub_1FB6E
		jmp	loc_1E481
; ---------------------------------------------------------------------------

loc_1E314:
					; DATA XREF: seg003:92C4o
		call	sub_1FADD
		push	large 0C000500h
		call	sub_16CCC
		or	al, al
		jz	loc_1E527
		inc	byte_26345
		mov	word_26346, 0
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E333:
					; DATA XREF: seg003:92C6o
		call	sub_1FADD
		call	sub_1D89A
		or	al, al
		jz	loc_1E527
		inc	byte_26345
		mov	word_26346, 0
		mov	word_26340, 0
		mov	word_2D06C, 6263h
		push	large 3200230h
		push	large 2D00320h
		call	sub_E752
		mov	word_2D088, ax
		mov	word_2CE4A, 879Ch

loc_1E36F:
		mov	byte_2D080, 0
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E377:
					; DATA XREF: seg003:92C8o ...
		cmp	Palettes+2, 80h	; '€'
		jnb	short loc_1E38E
		cmp	byte_25FE5, 0
		jnz	short loc_1E389
		inc	Palettes+2

loc_1E389:
		mov	byte_25FE9, 1

loc_1E38E:
		call	sub_1E15D
		call	word_2CE4A
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
		push	large 22D50h
		call	sub_1FB6E
		mov	word_2CE4A, 8852h
		jmp	loc_1E47B
; ---------------------------------------------------------------------------

loc_1E3C4:
		push	large 32198h
		call	sub_1FB6E
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E3D0:
					; DATA XREF: seg003:92CCo
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
		mov	word_2CE4A, 89AFh
		jmp	loc_1E36F
; ---------------------------------------------------------------------------

loc_1E406:
					; DATA XREF: seg003:92CEo ...
		cmp	Palettes+2, 0
		jbe	short loc_1E41A
		cmp	byte_25FE4, 0
		jnz	short loc_1E42C
		dec	Palettes+2
		jmp	short loc_1E42C
; ---------------------------------------------------------------------------

loc_1E41A:
		cmp	Palettes, 80h	; '€'
		jnb	short loc_1E431
		cmp	byte_25FE5, 0
		jnz	short loc_1E42C
		inc	Palettes

loc_1E42C:
		mov	byte_25FE9, 1

loc_1E431:
		call	sub_1E15D
		call	word_2CE4A
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
		push	large 20AF0h
		call	sub_1FB6E
		mov	word_2CE4A, 8A80h

loc_1E47B:
		mov	word_26346, 0

loc_1E481:
		inc	byte_2D080
		jmp	loc_1E527
; ---------------------------------------------------------------------------

loc_1E488:
		push	large 30000h
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
					; DATA XREF: seg003:92D2o
		call	sub_1FADD
		mov	ax, word_26346
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E4C5
		mov	PaletteTone, 96h	; '–'
		jmp	short loc_1E4CB
; ---------------------------------------------------------------------------

loc_1E4C5:
		mov	PaletteTone, 64h	; 'd'

loc_1E4CB:
		mov	byte_25FE9, 1
		cmp	word_26346, 10h
		jle	short loc_1E527
		inc	byte_26345
		mov	byte_26344, 0B4h ; '´'
		mov	word_2D088, 180h
		mov	Palettes, 60h	; '`'
		mov	Palettes+2, 0
		push	0Dh
		call	sub_14CEE
		jmp	short loc_1E527
; ---------------------------------------------------------------------------

loc_1E4F9:
					; DATA XREF: seg003:92D4o
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
		mov	byte_26345, 0FDh ; 'ý'
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
; ---------------------------------------------------------------------------
		db 0
off_1E53C	dw offset loc_1E1CD	; DATA XREF: seg003:8F48r
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
		mov	byte_26330, 0DDh ; 'Ý'
		jmp	loc_1E5F5
; ---------------------------------------------------------------------------

loc_1E570:
		cmp	si, 1Eh
		jge	short loc_1E5C6
		or	si, si
		jnz	short loc_1E580
		push	8
		call	sub_14CEE

loc_1E580:
		mov	ax, 2
		imul	si
		mov	si, ax
		push	5948h
		push	word_26335
		mov	ax, 40h	; '@'
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
		mov	al, 0DEh ; 'Þ'
		jmp	short loc_1E5C1
; ---------------------------------------------------------------------------

loc_1E5BF:
		mov	al, 0DFh ; 'ß'

loc_1E5C1:
		mov	byte_26330, al
		jmp	short loc_1E5F5
; ---------------------------------------------------------------------------

loc_1E5C6:
		cmp	si, 28h	; '('
		jge	short loc_1E5EA
		cmp	si, 1Eh
		jnz	short loc_1E5D7
		push	0Fh
		call	sub_14CEE

loc_1E5D7:
		mov	eax, dword_26320
		mov	dword_26324, eax
		mov	byte_26330, 0DDh ; 'Ý'
		call	off_2285A
		jmp	short loc_1E5F5
; ---------------------------------------------------------------------------

loc_1E5EA:
		mov	byte_26330, 0DCh ; 'Ü'
		call	off_2285A
		jmp	short loc_1E5F7
; ---------------------------------------------------------------------------

loc_1E5F5:
					; sub_1E556+17j ...
		mov	al, 0

loc_1E5F7:
		pop	si
		pop	bp
		retn	2
sub_1E556	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E5FC	proc near
					; sub_1E556+99p
					; DATA XREF: ...
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

; ---------------------------------------------------------------------------
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
		cmp	word_26332, 80h	; '€'
		jl	short loc_1E66B
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E66B:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		cmp	word_26332, 80h	; '€'
		jl	short loc_1E6A2
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E6A2:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		mov	byte ptr word_26006, 80h ; '€'
		mov	byte_2C977, 0C8h ; 'È'
		call	sub_15A70
		mov	byte ptr word_26006, 0
		mov	byte_2C977, 38h	; '8'
		call	sub_15A70
		push	3
		call	sub_14CEE

loc_1E6FE:
		cmp	word_26332, 80h	; '€'
		jl	short loc_1E70A
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E70A:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		push	large 1800180h
		push	0Ah
		call	sub_1FA9D
		mov	byte ptr word_26335, 40h ; '@'
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
		push	0Fh
		call	sub_14CEE
		inc	byte_2D082

loc_1E7AF:
		mov	byte_2D085, 1
		mov	word_26332, 0
		mov	al, byte_2D084
		mov	ah, 0
		and	ax, 7
		mov	bx, ax
		mov	al, [bx+1E88h]
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
		mov	ax, [bx+1E7Ch]
		mov	off_2285A, ax

loc_1E7F2:
		push	large 1800180h
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
		mov	byte_26331, 0FEh ; 'þ'
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	large 800030h
		call	sub_1597C
		push	0Ch
		call	sub_14CEE
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
					; sub_1E8B0+19j
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
					; seg003:loc_1F4BAp ...
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		add	ax, 0FFD0h
		push	ax
		push	large 60007h
		call	sub_16A6B
		cmp	word_26346, 30h	; '0'
		jnz	short loc_1E900
		mov	byte_26344, 0B5h ; 'µ'
		push	8
		call	sub_14CEE

loc_1E900:
		cmp	word_26346, 40h	; '@'
		jl	short loc_1E91E
		call	word_2CE66
		or	al, al
		jz	short loc_1E91E
		mov	word_26346, 0
		mov	byte_26349, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E91E:
					; sub_1E8DA+33j
		mov	al, 0
		pop	bp
		retn
sub_1E8DA	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		mov	byte ptr word_25FFA, 10h
		push	1Fh
		call	sub_157E4
		add	al, 28h	; '('
		mov	byte ptr word_26006+1, al
		push	7Fh ; ''
		call	sub_157E4
		and	al, 0F8h
		sub	al, 40h	; '@'
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
		push	3
		call	sub_14CEE

loc_1E967:
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1E974
		mov	ax, 1
		jmp	short loc_1E976
; ---------------------------------------------------------------------------

loc_1E974:
		xor	ax, ax

loc_1E976:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
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
		mov	byte ptr word_26006+1, 40h ; '@'
		cmp	byte_2D085, 0
		jz	short loc_1E9B0
		mov	al, byte ptr word_26006
		add	al, 2
		jmp	short loc_1E9B5
; ---------------------------------------------------------------------------

loc_1E9B0:
		mov	al, byte ptr word_26006
		add	al, 0FEh ; 'þ'

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
		push	3
		call	sub_14CEE

loc_1E9F9:
		mov	ax, word_26346
		add	ax, 0FF9Ch
		push	ax
		call	sub_16BD9
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1EA10
		mov	ax, 1
		jmp	short loc_1EA12
; ---------------------------------------------------------------------------

loc_1EA10:
		xor	ax, ax

loc_1EA12:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
		jnz	short loc_1EA2E
		mov	byte_2D084, 40h	; '@'
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
		add	al, 0FDh ; 'ý'
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
		cmp	byte_2D084, 40h	; '@'
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
		mov	byte ptr word_26006+1, 60h ; '`'
		mov	byte ptr word_25FFA+1, 54h ; 'T'
		call	sub_15A5C

loc_1EB0C:
		mov	ax, word_26346
		mov	bx, 80h	; '€'
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
		push	0Dh
		call	sub_14CEE

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
; ---------------------------------------------------------------------------
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
		push	7Fh ; ''
		call	sub_157E4
		add	al, 80h	; '€'
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
		push	3
		call	sub_14CEE
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
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1EBFD
		mov	ax, 1
		jmp	short loc_1EBFF
; ---------------------------------------------------------------------------

loc_1EBFD:
		xor	ax, ax

loc_1EBFF:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
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
		add	al, 0FDh ; 'ý'

loc_1EC3E:
		mov	byte ptr word_26006, al
		mov	byte_26000, 4
		mov	word ptr dword_26002, 816h
		mov	byte ptr word_25FFA+1, 34h ; '4'
		call	sub_15A5C
		push	3
		call	sub_14CEE

loc_1EC5B:
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1EC68
		mov	ax, 1
		jmp	short loc_1EC6A
; ---------------------------------------------------------------------------

loc_1EC68:
		xor	ax, ax

loc_1EC6A:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
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
		mov	bx, 80h	; '€'
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
		push	3
		call	sub_14CEE

loc_1ECD0:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		cmp	word_26346, 90h	; ''
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
		mov	byte ptr word_26006+1, 40h ; '@'
		mov	word ptr dword_26002, 0A20h
		call	sub_15A5C
		jmp	short loc_1ED67
; ---------------------------------------------------------------------------

loc_1ED46:
		cmp	di, 8
		jnz	short loc_1ED67
		push	word ptr dword_2630A
		push	word ptr dword_2630A+2
		push	0D0h ; 'Ð'
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
		cmp	word_26346, 0D0h ; 'Ð'
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
; ---------------------------------------------------------------------------
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
		mov	byte ptr word_26006+1, 40h ; '@'
		mov	word ptr dword_26002, 907h
		mov	byte ptr word_25FFA+1, 44h ; 'D'
		push	300h
		call	sub_157FA
		sub	ax, 180h
		add	ax, word ptr dword_25FFC
		mov	word ptr dword_25FFC, ax
		mov	byte ptr word_26006, 0
		call	sub_15A70
		push	3
		call	sub_14CEE

loc_1EE14:
		mov	ax, word_26346
		add	ax, 0FF9Ch
		push	ax
		call	sub_16BD9
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1EE2B
		mov	ax, 1
		jmp	short loc_1EE2D
; ---------------------------------------------------------------------------

loc_1EE2B:
		xor	ax, ax

loc_1EE2D:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26346, 40h	; '@'
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
		cmp	byte_26312, 80h	; '€'
		jb	short loc_1EE9E
		mov	byte_2D085, 1
		jmp	short loc_1EE9E
; ---------------------------------------------------------------------------

loc_1EE83:
		cmp	byte_2D085, 1
		jnz	short loc_1EEA1
		mov	al, byte_26312
		add	al, 0F8h ; 'ø'
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
		mov	byte ptr word_26006+1, 40h ; '@'
		mov	word ptr dword_26002, 0A20h
		mov	byte ptr word_25FFA+1, 44h ; 'D'
		call	sub_15A5C

loc_1EEED:
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EF6F
		mov	word_2BC82, 0Bh
		mov	byte_2BC88, 30h	; '0'
		mov	ax, word_26346
		mov	bx, 80h	; '€'
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
		push	0E0h ; 'à'

loc_1EF5F:
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_17687
		push	0Fh
		call	sub_14CEE

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
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EFCF
		mov	word_2BC82, 0Bh
		mov	byte_2BC88, 40h	; '@'
		mov	ax, word_26346
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EFB4
		push	word_2BC71+1
		push	word_2BC74
		push	40h ; '@'
		jmp	short loc_1EFBF
; ---------------------------------------------------------------------------

loc_1EFB4:
		push	word_2BC71+1
		push	word_2BC74
		push	0C0h ; 'À'

loc_1EFBF:
		call	sub_15A24
		mov	byte ptr word_2BC71, al
		call	sub_17687
		push	0Fh
		call	sub_14CEE

loc_1EFCF:
		mov	ax, word_26346
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		push	dx
		call	sub_16BD9
		cmp	word_26346, 80h	; '€'
		jnz	short loc_1EFE9
		mov	ax, 1
		jmp	short loc_1EFEB
; ---------------------------------------------------------------------------

loc_1EFE9:
		xor	ax, ax

loc_1EFEB:
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		add	word ptr dword_25FFC+2,	680h
		mov	ax, word_22872
		mov	word ptr dword_25FFC, ax
		mov	word ptr dword_2A722, ax
		cmp	word_26346, 40h	; '@'
		jnz	short loc_1F045
		mov	byte ptr word_2BC71, 0C4h ; 'Ä'
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
		push	8
		call	sub_14CEE

loc_1F045:
		cmp	word_26346, 80h	; '€'
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
		mov	byte_2A72F, 0FEh ; 'þ'

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
		mov	byte_2A72F, 0FEh ; 'þ'

loc_1F0CD:
		call	sub_16A03

loc_1F0D0:
		mov	al, 80h	; '€'
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		call	sub_15A8E
		mov	al, 80h	; '€'
		sub	al, byte ptr word_26006
		mov	byte ptr word_26006, al
		call	sub_15A8E
		push	3
		call	sub_14CEE
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

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F13B	proc near
		push	bp
		mov	bp, sp
		mov	ax, word_26346
		add	ax, 0FFC0h
		push	ax
		push	large 60007h
		call	sub_16A6B
		cmp	word_26346, 40h	; '@'
		jnz	short loc_1F182
		mov	byte_26344, 0B5h ; 'µ'
		push	8
		call	sub_14CEE
		mov	byte ptr word_25FFA+1, 74h ; 't'
		mov	byte_26000, 2
		call	sub_157D6
		mov	byte ptr word_26006, al
		mov	word ptr dword_26002, 1505h
		mov	byte_2D085, 0
		mov	word_2633E, 0

loc_1F182:
		cmp	word_26346, 80h	; '€'
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
		add	al, 80h	; '€'
		mov	byte ptr word_26006, al
		call	sub_15A5C
		mov	al, byte ptr word_26006
		add	al, 87h	; '‡'
		mov	byte ptr word_26006, al
		push	9
		call	sub_14CEE

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
					; sub_1F23B+15j
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

; ---------------------------------------------------------------------------
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
					; DATA XREF: ...
		cmp	word_26346, 1
		jnz	short loc_1F333
		mov	word_26342, 6784h
		mov	word_2634C, 5CF8h
		mov	word_2A72A, 800h
		mov	byte_2A72F, 2
		mov	word_2A72C, 8
		mov	byte_26344, 0B4h ; '´'
		mov	word_2C96E, 0BAh ; 'º'
		mov	word_2C970, 0B8h ; '¸'
		mov	word_2C972, 0B4h ; '´'
		mov	byte_2CE56, 0
		mov	word_22582, 400h
		mov	word_22584, 1400h
		mov	word_22586, 300h
		mov	word_22588, 600h
		mov	si, 0CCh ; 'Ì'
		jmp	short loc_1F32D
; ---------------------------------------------------------------------------

loc_1F326:
		push	si
		call	sub_35A2
		inc	si

loc_1F32D:
		cmp	si, 0DCh ; 'Ü'
		jl	short loc_1F326

loc_1F333:
		call	sub_1FB07
		cmp	word_26346, 0C0h ; 'À'
		jl	loc_1F666
		mov	word_26346, 0
		inc	byte_26345
		push	0Dh
		call	sub_14CEE
		mov	Palettes, 0
		mov	Palettes+1, 0
		mov	Palettes+2, 0
		mov	byte_25FE9, 1
		mov	word_2CE64, 0C4h ; 'Ä'
		mov	word_23F5A, 2ECBh
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F374:
		call	sub_1FB07
		cmp	word_26346, 40h	; '@'
		jl	loc_1F666
		inc	byte_26345
		mov	byte_26349, 1
		mov	byte ptr word_2634A+1, 0
		mov	word_26346, 0
		mov	word_2D06C, 6885h
		mov	byte_2D085, 0
		mov	word_2CE66, 96A2h
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
		mov	ax, [bx+1E94h]
		mov	word_2CE66, ax
		cmp	byte ptr word_2634A+1, 20h ; ' '
		jb	short loc_1F403
		jmp	short loc_1F412
; ---------------------------------------------------------------------------

loc_1F400:
		call	sub_1E8DA

loc_1F403:
		push	cs
		call	near ptr sub_1F21A
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
					; DATA XREF: seg003:off_1F681o
		push	large 5208h
		call	sub_1F23B
		mov	word_2CE66, 9794h
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F439:
					; DATA XREF: ...
		push	large 13AFCh
		call	sub_1F23B
		mov	word_2CE66, 99ECh
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F44B:
					; DATA XREF: ...
		push	large 22580h
		call	sub_1F23B
		mov	word_2CE66, 9BAFh
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F45D:
					; DATA XREF: ...
		push	large 30D48h
		call	sub_1F23B
		mov	word_2CE66, 9D6Dh
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F46F:
		cmp	Palettes, 60h	; '`'
		jnb	short loc_1F483
		mov	al, Palettes
		add	al, 2
		mov	Palettes, al
		mov	byte_25FE9, 1

loc_1F483:
		push	large 0C000400h
		call	sub_16CCC
		or	al, al
		jz	short loc_1F49F
		mov	word_26346, 0
		inc	byte_26345
		mov	byte_26349, 1

loc_1F49F:
		push	cs
		call	near ptr sub_1F21A
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F4A6:
		cmp	Palettes, 60h	; '`'
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
		push	cs
		call	near ptr sub_1F21A
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

loc_1F4E7:				; DATA XREF: seg003:off_1F679o
		push	large 146B4h
		call	sub_1F23B
		mov	word_2CE66, 98D2h
		jmp	short loc_1F523
; ---------------------------------------------------------------------------

loc_1F4F8:
					; DATA XREF: seg003:A3FBo
		push	large 23138h
		call	sub_1F23B
		mov	word_2CE66, 9A54h
		jmp	short loc_1F523
; ---------------------------------------------------------------------------

loc_1F509:
					; DATA XREF: seg003:A3FDo
		push	large 31A90h
		call	sub_1F23B
		mov	word_2CE66, 9C71h
		jmp	short loc_1F523
; ---------------------------------------------------------------------------

loc_1F51A:
					; DATA XREF: seg003:A3FFo
		push	large 40000h
		call	sub_1F23B

loc_1F523:
		mov	word_2CC8E, 9
		mov	word_2CE64, 0C8h ; 'È'
		inc	byte_2D07F
		jmp	loc_1F666
; ---------------------------------------------------------------------------

loc_1F536:
		cmp	Palettes+2, 60h	; '`'
		jnb	short loc_1F552
		mov	al, Palettes+2
		add	al, 2
		mov	Palettes+2, al
		mov	al, Palettes
		add	al, 0FEh ; 'þ'
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
		cmp	Palettes+1, 40h	; '@'
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
		cmp	Palettes, 80h	; '€'
		jb	short loc_1F626
		mov	byte_2D080, 2
		jmp	short loc_1F626
; ---------------------------------------------------------------------------

loc_1F606:
		mov	al, Palettes
		add	al, 0FEh ; 'þ'
		mov	Palettes, al
		dec	Palettes+1
		mov	al, Palettes+2
		add	al, 0FEh ; 'þ'
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
		push	cs
		call	near ptr sub_1F21A
		or	ax, ax
		jz	short loc_1F666
		mov	byte ptr word_2634A+1, 1

loc_1F643:
		push	4
		call	sub_162CC
		mov	word_26346, 0
		mov	byte_26345, 0FDh ; 'ý'
		mov	word_2D06C, 1240h
		mov	byte_226C0, 0
		jmp	short loc_1F666
; ---------------------------------------------------------------------------

loc_1F660:
		push	0C8h ; 'È'
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
; ---------------------------------------------------------------------------
off_1F679	dw offset loc_1F4E7	; DATA XREF: seg003:A262r
		dw offset loc_1F4F8
		dw offset loc_1F509
		dw offset loc_1F51A
off_1F681	dw offset loc_1F427	; DATA XREF: seg003:A1A2r
		dw offset loc_1F439
		dw offset loc_1F44B
		dw offset loc_1F45D
off_1F689	dw offset loc_1F2C9	; DATA XREF: seg003:A044r
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
		push	large 30002h
		call	sub_16A6B
		cmp	word_26332, 10h
		jnz	short loc_1F719
		push	8
		call	sub_14CEE

loc_1F719:
		cmp	word_26332, 14h
		jz	short loc_1F72E
		cmp	word_26332, 18h
		jz	short loc_1F72E
		cmp	word_26332, 1Ch
		jnz	short loc_1F732

loc_1F72E:
					; sub_1F6F1+34j
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
		cmp	byte_26330, 0DBh ; 'Û'
		jnb	short loc_1F75C
		mov	ax, word_26332
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F75C
		inc	byte_26330

loc_1F75C:
					; sub_1F6F1+65j
		call	word_2CE68
		or	al, al
		jz	short loc_1F774
		mov	word_26332, 0
		mov	byte_2D084, 0
		mov	byte_26330, 0D4h ; 'Ô'

loc_1F774:
		pop	bp
		retn
sub_1F6F1	endp

; ---------------------------------------------------------------------------
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
		push	3
		call	sub_14CEE

loc_1F7AA:
		cmp	word_26332, 60h	; '`'
		jl	short loc_1F7B6
		mov	ax, 1
		jmp	short loc_1F7B8
; ---------------------------------------------------------------------------

loc_1F7B6:
		xor	ax, ax

loc_1F7B8:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		push	3
		call	sub_14CEE

loc_1F813:
		cmp	word_26332, 60h	; '`'
		jl	short loc_1F81F
		mov	ax, 1
		jmp	short loc_1F821
; ---------------------------------------------------------------------------

loc_1F81F:
		xor	ax, ax

loc_1F821:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		push	0Fh
		call	sub_14CEE

loc_1F86B:
		cmp	word_26332, 40h	; '@'
		jl	short loc_1F877
		mov	ax, 1
		jmp	short loc_1F879
; ---------------------------------------------------------------------------

loc_1F877:
		xor	ax, ax

loc_1F879:
		pop	bp
		retn
; ---------------------------------------------------------------------------
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
		push	large 1800180h
		push	0Ah
		call	sub_1FA9D
		cmp	word_26332, 0C0h ; 'À'
		jl	loc_1F9A1
		inc	byte_26331
		mov	word_26332, 0
		mov	byte ptr word_26335, 0
		mov	byte_2D085, 0
		mov	byte_2D084, 1
		mov	byte_2D083, 0
		mov	word_2632A, 0
		mov	word_2CE68, 0A4F6h
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
		mov	ax, [bx+1EA4h]
		mov	word_2CE68, ax
		inc	byte_2D084
		cmp	byte_2D083, 10h
		jb	short loc_1F936
		jmp	short loc_1F968
; ---------------------------------------------------------------------------

loc_1F933:
		call	sub_1F6F1

loc_1F936:
		push	large 1800180h
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
		mov	byte_26331, 0FEh ; 'þ'
		mov	byte_26330, 4
		mov	word_26332, 0
		push	word ptr dword_26320
		push	word ptr dword_26320+2
		push	large 800030h
		call	sub_1597C
		push	0Ch
		call	sub_14CEE
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
					; sub_1F9BA+20j
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
					; sub_10574+22P ...

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
					; sub_16510+11Ap ...

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		push	di
		mov	edx, [bp+arg_0]
		mov	di, 1FC6h
		mov	ax, 0E1h ; 'á'
		mov	byte ptr dword_229AA+3,	0A0h ; ' '
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
		add	al, 0A0h ; ' '
		jmp	short loc_1FA47
; ---------------------------------------------------------------------------

loc_1FA45:
		mov	al, 2

loc_1FA47:
		stosb
		add	bx, 4
		dec	cl
		jnz	short loc_1FA34
		add	dl, 0A0h ; ' '
		mov	[di], dl
		call	sub_1DBE
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
		push	[bp+arg_0]
		call	sub_14CEE

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
		push	[bp+arg_0]
		call	sub_14CEE

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
					; seg003:loc_1889Dp ...
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
					; seg003:loc_18783p ...
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
					; sub_1F23B+21p ...

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		cmp	byte_2CEBE, 80h	; '€'
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
					; sub_1FB6E+15j
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
		cmp	byte_26345, 0FDh ; 'ý'
		jnz	short loc_1FC23
		cmp	word_26346, 1
		jnz	short loc_1FBE1
		mov	byte_26348, 0
		push	0
		call	sub_162CC
		push	0Dh
		call	sub_14CEE

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
		cmp	byte_26345, 0FEh ; 'þ'
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
		mov	word_23F5A, 0DD8h
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
		mov	word_2D06A, 1240h
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
					; sub_1FBBE+160j
		mov	word_2CE88, 6BA1h
		push	20Ah
		call	sub_14F68
		jmp	short loc_1FD51
; ---------------------------------------------------------------------------

loc_1FD35:
		cmp	word_26346, 1E8h
		jnz	short loc_1FD51
		les	bx, dword_23EF0
		inc	byte ptr es:[bx+13h]
		mov	byte_25FE8, 2
		push	1
		call	sub_1510E

loc_1FD51:
					; sub_1FBBE+62j ...
		mov	word ptr dword_2C922, 0C190h
		mov	word ptr dword_2C922+2,	0C190h

loc_1FD5D:
					; sub_1FBBE+BBj ...
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
					; sub_1FD62+22j
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

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; string::string(string	const &)
@string@$bctr$qmx6string proc far
					; xmsg::xmsg(xmsg &)+56P ...

var_1E		= word ptr -1Eh
arg_0		= dword	ptr  6
arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A749h
		call	___InitExceptBlocks
		mov	ax, word ptr [bp+arg_0]
		or	ax, word ptr [bp+arg_0+2]
		jnz	short loc_1FDBC
		mov	ax, 4
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jz	short loc_1FDD6

loc_1FDBC:
		les	bx, [bp+arg_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		les	bx, [bp+arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		les	bx, es:[bx]
		inc	word ptr es:[bx]

loc_1FDD6:
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		push	[bp+var_1E]
		call	___ExitExceptBlocks
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@$bctr$qmx6string endp

; ---------------------------------------------------------------------------
byte_1FDFC	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah
					; DATA XREF: seg000:A741o
		db 0Dh dup(0), 2, 0, 2,	0, 4Fh,	0A7h
		dw seg seg000
		db 5, 0, 3Eh, 0, 78h, 61h, 2 dup(6Ch), 6Fh, 63h, 2 dup(0)
		db 0BEh, 0
		dw seg seg004
		dw 0
		db 3, 0Dh dup(0), 4, 0,	3, 0, 26h, 0, 2	dup(0FFh), 3, 0
		db 2Ch,	0, 30h,	0Dh dup(0), 1, 0, 1, 0,	56h, 6Eh
		dw seg seg000
		db 5, 0, 34h, 0, 78h, 6Dh, 73h,	67h, 0Eh dup(0)

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; int __cdecl __far string__string(__int32, char *s)
@string@$bctr$qnxc proc	far
					; string::assert_element(uint)+5Ap ...

var_22		= word ptr -22h
var_16		= word ptr -16h
var_4		= dword	ptr -4
arg_0		= dword	ptr  6
src		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 22h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A7BBh
		call	___InitExceptBlocks
		mov	ax, word ptr [bp+arg_0]
		or	ax, word ptr [bp+arg_0+2]
		jnz	short loc_1FEA5
		mov	ax, 4
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jz	short loc_1FF19

loc_1FEA5:
		mov	ax, 0Ch
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+var_4+2], dx
		mov	word ptr [bp+var_4], ax
		or	ax, dx
		jz	short loc_1FF09
		mov	[bp+var_16], 0Eh
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, word ptr [bp+src]
		or	ax, word ptr [bp+src+2]
		jz	short loc_1FEDB
		push	word ptr [bp+src+2]
		push	word ptr [bp+src] ; s
		call	_strlen
		pop	cx
		pop	cx
		jmp	short loc_1FEDD
; ---------------------------------------------------------------------------

loc_1FEDB:
		xor	ax, ax

loc_1FEDD:
		push	ax		; n
		push	word ptr [bp+src+2]
		push	word ptr [bp+src] ; src
		push	word ptr [bp+var_4+2]
		push	word ptr [bp+var_4] ; __int32
		nop
		push	cs
		call	near ptr @TStringRef@$bctr$qnxcuit1uiui	; TStringRef::TStringRef(char *,uint,char *,uint,uint)
		add	sp, 12h
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	[bp+var_16], 6

loc_1FF09:
		mov	dx, word ptr [bp+var_4+2]
		mov	ax, word ptr [bp+var_4]
		les	bx, [bp+arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax

loc_1FF19:
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		push	[bp+var_22]
		call	___ExitExceptBlocks
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@$bctr$qnxc endp

; ---------------------------------------------------------------------------
		db 4, 0, 90h, 20h, 0Ah,	0, 9Eh,	2
		dw seg seg004
aTstringref	db 'TStringRef *',0
byte_1FF56	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h
					; DATA XREF: seg000:A7A5o
		db 0Dh dup(0), 2, 0, 2,	0, 0D1h, 0A7h
		dw seg seg000
		db 5, 0, 4Ah, 0
aStringLengther	db 'string::lengtherror',0
		dd byte_1FFE6
		db 2 dup(0), 3,	0Dh dup(0)
byte_1FFA4	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah
					; DATA XREF: seg000:A7A1o
		db 0Dh dup(0), 2, 0, 2,	0, 1Eh,	0A8h
		dw seg seg000
		db 5, 0, 3Eh, 0, 78h, 61h, 2 dup(6Ch), 6Fh, 63h, 2 dup(0)
		db 66h,	2
		dw seg seg004
		dw 0
		db 3, 0Dh dup(0)
byte_1FFE6	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h
					; DATA XREF: seg004:0210o
		db 0Dh dup(0), 1, 0, 1,	0, 56h,	6Eh
		dw seg seg000
		db 5, 0, 34h, 0, 78h, 6Dh, 73h,	67h, 0Eh dup(0), 0Ch, 0
		db 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 32h, 0, 3Eh, 0Dh dup(0)
		db 1, 0, 1, 0, 0B5h, 6
		dw seg seg004
		db 5, 0, 42h, 0, 54h, 53h, 74h,	72h, 69h, 6Eh, 67h, 52h
		db 65h,	66h, 2 dup(0), 0E4h, 2
		dw seg seg004
		db 2 dup(0), 3,	0Dh dup(0), 2, 0, 3, 0,	1Ah, 0,	2 dup(0FFh)
		db 1, 0, 26h, 0, 2Ah, 0Dh dup(0), 54h, 52h, 65h, 66h, 65h
		db 72h,	65h, 6Eh, 63h, 65h, 0Ah	dup(0)

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; int __cdecl __far string___string(void (*driver)(void), char)
@string@$bdtr$qv proc far
					; xmsg::~xmsg(void)+3FP ...

var_1E		= word ptr -1Eh
driver		= dword	ptr  6
arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A874h
		call	___InitExceptBlocks
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	ax, word ptr [bp+driver]
		or	ax, word ptr [bp+driver+2]
		jz	short loc_2010A
		les	bx, [bp+driver]
		les	bx, es:[bx]
		dec	word ptr es:[bx]
		mov	ax, es:[bx]
		or	ax, ax
		jnz	short loc_200F7
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	ax, 3
		push	ax		; char
		les	bx, [bp+driver]
		push	word ptr es:[bx+2]
		push	word ptr es:[bx] ; driver
		nop
		push	cs
		call	near ptr sub_20435
		add	sp, 6

loc_200F7:
		test	[bp+arg_4], 1
		jz	short loc_2010A
		push	word ptr [bp+driver+2]
		push	word ptr [bp+driver] ; driver
		call	@$bdele$qnv
		pop	cx
		pop	cx

loc_2010A:
					; string::~string(void)+69j
		push	[bp+var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@$bdtr$qv endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; string::assert_element(unsigned int)const
@string@assert_element$xqui proc far

var_28		= word ptr -28h
var_26		= word ptr -26h
var_1A		= word ptr -1Ah
src		= byte ptr -8
driver		= byte ptr -4
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 28h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A8A8h
		call	___InitExceptBlocks
		mov	ax, [bp+arg_4]
		mov	[bp+var_28], ax
		les	bx, [bp+arg_0]
		les	bx, es:[bx]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+var_28]
		jbe	short loc_20145
		mov	ax, 1
		jmp	short loc_20147
; ---------------------------------------------------------------------------

loc_20145:
		xor	ax, ax

loc_20147:
		or	ax, ax
		jnz	short loc_201C8
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, 5
		push	ax		; int
		mov	ax, seg	seg000
		push	ax		; int
		mov	ax, 0A99Ah
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		mov	[bp+var_1A], 6
		push	ds
		mov	ax, 2586h
		push	ax		; s
		push	ss
		lea	ax, [bp+driver]
		push	ax		; __int32
		nop
		push	cs
		call	near ptr @string@$bctr$qnxc ; string::string(char *)
		add	sp, 8
		lea	ax, [bp+driver]
		push	ss
		push	ax
		push	ss
		lea	ax, [bp+src]
		push	ax
		call	@xmsg@$bctr$qmx6string ; xmsg::xmsg(string &)
		add	sp, 8
		mov	[bp+var_1A], 0Eh
		mov	ax, 2
		push	ax		; char
		push	ss
		lea	ax, [bp+driver]
		push	ax		; driver
		push	cs
		call	near ptr @string@$bdtr$qv ; string::~string(void)
		add	sp, 6
		mov	[bp+var_1A], 6
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		lea	ax, [bp+src]
		push	ss
		push	ax		; src
		push	cs		; int
		mov	ax, 0C07h
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

loc_201C8:
		push	[bp+var_26]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@assert_element$xqui endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; string::assert_index(unsigned	int)const
@string@assert_index$xqui proc far

var_28		= word ptr -28h
var_26		= word ptr -26h
var_1A		= word ptr -1Ah
src		= byte ptr -8
driver		= byte ptr -4
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 28h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A8ECh
		call	___InitExceptBlocks
		mov	ax, [bp+arg_4]
		mov	[bp+var_28], ax
		les	bx, [bp+arg_0]
		les	bx, es:[bx]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+var_28]
		jb	short loc_20203
		mov	ax, 1
		jmp	short loc_20205
; ---------------------------------------------------------------------------

loc_20203:
		xor	ax, ax

loc_20205:
		or	ax, ax
		jnz	short loc_20286
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, 5
		push	ax		; int
		mov	ax, seg	seg000
		push	ax		; int
		mov	ax, 0A99Ah
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		mov	[bp+var_1A], 6
		push	ds
		mov	ax, 25A4h
		push	ax		; s
		push	ss
		lea	ax, [bp+driver]
		push	ax		; __int32
		nop
		push	cs
		call	near ptr @string@$bctr$qnxc ; string::string(char *)
		add	sp, 8
		lea	ax, [bp+driver]
		push	ss
		push	ax
		push	ss
		lea	ax, [bp+src]
		push	ax
		call	@xmsg@$bctr$qmx6string ; xmsg::xmsg(string &)
		add	sp, 8
		mov	[bp+var_1A], 0Eh
		mov	ax, 2
		push	ax		; char
		push	ss
		lea	ax, [bp+driver]
		push	ax		; driver
		push	cs
		call	near ptr @string@$bdtr$qv ; string::~string(void)
		add	sp, 6
		mov	[bp+var_1A], 6
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		lea	ax, [bp+src]
		push	ss
		push	ax		; src
		push	cs		; int
		mov	ax, 0C07h
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

loc_20286:
		push	[bp+var_26]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@string@assert_index$xqui endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; TSubString::assert_element(unsigned int)const
@TSubString@assert_element$xqui	proc far

var_28		= word ptr -28h
var_26		= word ptr -26h
var_1A		= word ptr -1Ah
src		= byte ptr -8
driver		= byte ptr -4
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 28h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A930h
		call	___InitExceptBlocks
		mov	ax, [bp+arg_4]
		mov	[bp+var_28], ax
		les	bx, [bp+arg_0]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+var_28]
		jbe	short loc_202BE
		mov	ax, 1
		jmp	short loc_202C0
; ---------------------------------------------------------------------------

loc_202BE:
		xor	ax, ax

loc_202C0:
		or	ax, ax
		jnz	short loc_20341
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, 5
		push	ax		; int
		mov	ax, seg	seg000
		push	ax		; int
		mov	ax, 0A99Ah
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		mov	[bp+var_1A], 6
		push	ds
		mov	ax, 25C2h
		push	ax		; s
		push	ss
		lea	ax, [bp+driver]
		push	ax		; __int32
		nop
		push	cs
		call	near ptr @string@$bctr$qnxc ; string::string(char *)
		add	sp, 8
		lea	ax, [bp+driver]
		push	ss
		push	ax
		push	ss
		lea	ax, [bp+src]
		push	ax
		call	@xmsg@$bctr$qmx6string ; xmsg::xmsg(string &)
		add	sp, 8
		mov	[bp+var_1A], 0Eh
		mov	ax, 2
		push	ax		; char
		push	ss
		lea	ax, [bp+driver]
		push	ax		; driver
		push	cs
		call	near ptr @string@$bdtr$qv ; string::~string(void)
		add	sp, 6
		mov	[bp+var_1A], 6
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		lea	ax, [bp+src]
		push	ss
		push	ax		; src
		push	cs		; int
		mov	ax, 0C07h
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

loc_20341:
		push	[bp+var_26]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
@TSubString@assert_element$xqui	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; int __cdecl __far TStringRef__TStringRef(__int32, void *src, size_t n, int, int, int,	int)
@TStringRef@$bctr$qnxcuit1uiui proc far

arg_0		= dword	ptr  6
src		= dword	ptr  0Ah
n		= word ptr  0Eh
arg_A		= word ptr  10h
arg_C		= word ptr  12h
arg_E		= word ptr  14h
arg_10		= word ptr  16h

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word ptr [bp+arg_0]
		or	ax, word ptr [bp+arg_0+2]
		jnz	short loc_20373
		mov	ax, 0Ch
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jnz	short loc_20373
		jmp	loc_20419
; ---------------------------------------------------------------------------

loc_20373:
					; TStringRef::TStringRef(char *,uint,char *,uint,uint)+1Fj
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 1
		mov	word ptr es:[bx+0Ah], 0
		mov	ax, [bp+n]
		add	ax, [bp+arg_E]
		mov	es:[bx+6], ax
		mov	ax, es:[bx+6]
		add	ax, [bp+arg_10]
		push	ax
		nop
		push	cs
		call	near ptr sub_205CD
		pop	cx
		les	bx, [bp+arg_0]
		mov	es:[bx+8], ax
		mov	ax, es:[bx+8]
		inc	ax
		push	ax
		call	_malloc
		pop	cx
		les	bx, [bp+arg_0]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short loc_203CD
		push	ds
		mov	ax, 22DCh
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

loc_203CD:
		push	[bp+n]		; n
		push	word ptr [bp+src+2]
		push	word ptr [bp+src] ; src
		les	bx, [bp+arg_0]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2] ; dest
		call	_memcpy
		push	[bp+arg_E]	; n
		push	[bp+arg_C]
		push	[bp+arg_A]	; src
		les	bx, [bp+arg_0]
		mov	ax, es:[bx+2]
		add	ax, [bp+n]
		push	word ptr es:[bx+4]
		push	ax		; dest
		call	_memcpy
		add	sp, 14h
		les	bx, [bp+arg_0]
		les	bx, es:[bx+2]
		mov	ax, [bp+n]
		add	ax, [bp+arg_E]
		add	bx, ax
		mov	byte ptr es:[bx], 0

loc_20419:
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		add	word ptr es:[bx], 1
		adc	word ptr es:[bx+2], 0
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		pop	di
		pop	si
		pop	bp
		retf
@TStringRef@$bctr$qnxcuit1uiui endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; int __cdecl __far sub_20435(void (*driver)(void), char)
sub_20435	proc far

var_1E		= word ptr -1Eh
driver		= dword	ptr  6
arg_4		= byte ptr  0Ah

		push	bp
		mov	bp, sp

; TStringRef::~TStringRef(void)
@TStringRef@$bdtr$qv:
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A94Ah
		call	___InitExceptBlocks
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	ax, word ptr [bp+driver]
		or	ax, word ptr [bp+driver+2]
		jz	short loc_20487
		les	bx, [bp+driver]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	_farfree
		pop	cx
		pop	cx
		test	[bp+arg_4], 1
		jz	short loc_20487
		push	word ptr [bp+driver+2]
		push	word ptr [bp+driver] ; driver
		call	@$bdele$qnv
		pop	cx
		pop	cx

loc_20487:
					; sub_20435+43j
		push	[bp+var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
sub_20435	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; TStringRef::reserve(unsigned int)
@TStringRef@reserve$qui:
		sub	sp, 20h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A95Ch
		call	___InitExceptBlocks
		les	bx, [bp+6]
		or	word ptr es:[bx+0Ah], 1
		mov	ax, [bp+0Ah]
		inc	ax
		push	ax
		nop
		push	cs
		call	near ptr sub_205CD
		pop	cx
		mov	[bp-20h], ax
		les	bx, [bp+6]
		mov	ax, es:[bx+8]
		sub	ax, [bp-20h]
		cmp	ax, word_22F64
		jbe	short loc_204F5
		mov	ax, [bp-20h]
		inc	ax
		push	ax
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	_realloc
		add	sp, 6
		les	bx, [bp+6]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, [bp-20h]
		mov	es:[bx+8], ax

loc_204F5:
		push	word ptr [bp-1Eh]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; TStringRef::check_freeboard(void)
@TStringRef@check_freeboard$qv:
		sub	sp, 20h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A966h
		call	___InitExceptBlocks
		les	bx, [bp+6]
		push	word ptr es:[bx+6]
		nop
		push	cs
		call	near ptr sub_205CD
		pop	cx
		mov	[bp-20h], ax
		les	bx, [bp+6]
		mov	ax, es:[bx+8]
		sub	ax, [bp-20h]
		cmp	ax, word_22F64
		jbe	short loc_2055D
		mov	ax, [bp-20h]
		inc	ax
		push	ax
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	_realloc
		add	sp, 6
		les	bx, [bp+6]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, [bp-20h]
		mov	es:[bx+8], ax

loc_2055D:
		push	word ptr [bp-1Eh]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

sub_2056B	proc far

var_1E		= word ptr -1Eh
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp

; TStringRef::grow_to(unsigned int)
@TStringRef@grow_to$qui:
		sub	sp, 1Eh
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A978h
		call	___InitExceptBlocks
		les	bx, [bp+arg_0]
		mov	ax, [bp+arg_4]
		mov	es:[bx+8], ax
		mov	ax, es:[bx+8]
		inc	ax
		push	ax
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	_realloc
		add	sp, 6
		les	bx, [bp+arg_0]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short loc_205BF
		push	ds
		mov	ax, 22DCh
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

loc_205BF:
		push	[bp+var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
sub_2056B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

sub_205CD	proc far
					; seg004:0737p	...

var_20		= word ptr -20h
var_1E		= word ptr -1Eh
arg_0		= word ptr  6

		push	bp
		mov	bp, sp

; TStringRef::round_capacity(unsigned int)
@TStringRef@round_capacity$qui:
		sub	sp, 20h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A982h
		call	___InitExceptBlocks
		mov	ax, word_22F60
		mov	[bp+var_20], ax
		mov	cx, word_22F62
		mov	ax, [bp+arg_0]
		sub	ax, [bp+var_20]
		add	ax, cx
		dec	ax
		xor	dx, dx
		div	cx
		imul	cx
		add	ax, [bp+var_20]
		push	ax
		push	[bp+var_1E]
		call	___ExitExceptBlocks
		pop	ax
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
sub_205CD	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; TStringRef::splice(unsigned int, unsigned int, char const *, unsigned	int)
@TStringRef@splice$quiuinxcui:
		sub	sp, 26h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A994h
		call	___InitExceptBlocks
		les	bx, [bp+6]
		mov	ax, es:[bx+6]
		add	ax, [bp+12h]
		sub	ax, [bp+0Ch]
		mov	[bp-24h], ax
		push	ax
		push	cs
		call	near ptr sub_205CD
		pop	cx
		mov	[bp-26h], ax
		les	bx, [bp+6]
		mov	ax, es:[bx+8]
		cmp	ax, [bp-26h]
		jnb	short loc_20654
		push	word ptr [bp-26h]
		push	word ptr [bp+8]
		push	bx
		push	cs
		call	near ptr sub_2056B
		add	sp, 6
		jmp	short loc_206C3
; ---------------------------------------------------------------------------

loc_20654:
		les	bx, [bp+6]
		mov	ax, es:[bx+8]
		sub	ax, [bp-26h]
		cmp	ax, word_22F64
		jbe	short loc_206C3
		test	byte ptr es:[bx+0Ah], 1
		jnz	short loc_206C3
		mov	ax, [bp-26h]
		inc	ax
		push	ax
		call	_malloc
		pop	cx
		mov	[bp-20h], dx
		mov	[bp-22h], ax
		les	bx, [bp+6]
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short loc_20695
		push	ds
		mov	ax, 22DCh
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

loc_20695:
		cmp	word ptr [bp+0Ah], 0
		jz	short loc_206B7
		push	word ptr [bp+0Ah]
		les	bx, [bp+6]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		push	word ptr [bp-20h]
		push	word ptr [bp-22h]
		call	_memcpy
		add	sp, 0Ah

loc_206B7:
		les	bx, [bp+6]
		mov	ax, [bp-26h]
		mov	es:[bx+8], ax
		jmp	short loc_206D4
; ---------------------------------------------------------------------------

loc_206C3:
		les	bx, [bp+6]
		mov	dx, es:[bx+4]
		mov	ax, es:[bx+2]
		mov	[bp-20h], dx
		mov	[bp-22h], ax

loc_206D4:
		les	bx, [bp+6]
		mov	dx, es:[bx+4]
		mov	ax, es:[bx+2]
		cmp	dx, [bp-20h]
		jnz	short loc_206F1
		cmp	ax, [bp-22h]
		jnz	short loc_206F1
		mov	ax, [bp+12h]
		cmp	ax, [bp+0Ch]
		jz	short loc_20723

loc_206F1:
		les	bx, [bp+6]
		mov	ax, es:[bx+6]
		sub	ax, [bp+0Ah]
		sub	ax, [bp+0Ch]
		push	ax
		mov	ax, es:[bx+2]
		add	ax, [bp+0Ah]
		add	ax, [bp+0Ch]
		push	word ptr es:[bx+4]
		push	ax
		mov	ax, [bp-22h]
		add	ax, [bp+0Ah]
		add	ax, [bp+12h]
		push	word ptr [bp-20h]
		push	ax
		call	_memmove
		add	sp, 0Ah

loc_20723:
		cmp	word ptr [bp+12h], 0
		jz	short loc_20767
		mov	ax, [bp+0Eh]
		or	ax, [bp+10h]
		jz	short loc_2074E
		push	word ptr [bp+12h]
		push	word ptr [bp+10h]
		push	word ptr [bp+0Eh]
		mov	ax, [bp-22h]
		add	ax, [bp+0Ah]
		push	word ptr [bp-20h]
		push	ax
		call	_memmove
		add	sp, 0Ah
		jmp	short loc_20767
; ---------------------------------------------------------------------------

loc_2074E:
		push	word ptr [bp+12h]
		mov	ax, 20h	; ' '
		push	ax
		mov	ax, [bp-22h]
		add	ax, [bp+0Ah]
		push	word ptr [bp-20h]
		push	ax
		call	_memset
		add	sp, 8

loc_20767:
		les	bx, [bp+6]
		mov	ax, [bp-24h]
		mov	es:[bx+6], ax
		push	es
		les	ax, [bp-22h]
		mov	dx, es
		pop	es
		add	ax, es:[bx+6]
		mov	bx, ax
		mov	es, dx
		mov	byte ptr es:[bx], 0
		les	bx, [bp+6]
		mov	dx, es:[bx+4]
		mov	ax, es:[bx+2]
		cmp	dx, [bp-20h]
		jnz	short loc_20799
		cmp	ax, [bp-22h]
		jz	short loc_207BC

loc_20799:
		les	bx, [bp+6]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	_farfree
		pop	cx
		pop	cx
		les	bx, [bp+6]
		mov	dx, [bp-20h]
		mov	ax, [bp-22h]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax

loc_207BC:
		push	word ptr [bp-1Eh]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; string::set_case_sensitive(int)
@string@set_case_sensitive$qi:
		sub	sp, 2
		push	si
		push	di
		mov	ax, word_22F5A
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_22F5A, ax
		mov	ax, [bp-2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; string::set_paranoid_check(int)
@string@set_paranoid_check$qi:
		sub	sp, 2
		push	si
		push	di
		mov	ax, word_22F5C
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_22F5C, ax
		mov	ax, [bp-2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; string::skip_whitespace(int)
@string@skip_whitespace$qi:
		sub	sp, 2
		push	si
		push	di
		mov	ax, word_22F5E
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_22F5E, ax
		mov	ax, [bp-2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; string::initial_capacity(unsigned int)
@string@initial_capacity$qui:
		sub	sp, 2
		push	si
		push	di
		mov	ax, word_22F60
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_22F60, ax
		mov	ax, [bp-2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; string::resize_increment(unsigned int)
@string@resize_increment$qui:
		sub	sp, 2
		push	si
		push	di
		mov	ax, word_22F62
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_22F62, ax
		cmp	word_22F62, 0
		jnz	short loc_2085F
		mov	word_22F62, 1

loc_2085F:
		mov	ax, [bp-2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; string::max_waste(unsigned int)
@string@max_waste$qui:
		sub	sp, 2
		push	si
		push	di
		mov	ax, word_22F64
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_22F64, ax
		mov	ax, [bp-2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
byte_20885	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h
					; DATA XREF: seg000:A970o seg000:A98Co
		db 0Dh dup(0), 2, 0, 2,	0, 0CFh, 0A9h
		dw seg seg000
		db 5, 0, 4Ah, 0
aStringLength_0	db 'string::lengtherror',0
		dd byte_20915
		db 2 dup(0), 3,	0Dh dup(0), 6, 0, 3, 0,	26h, 0,	2 dup(0FFh)
		db 7, 0, 2Eh, 0, 3Ah, 0Dh dup(0), 2, 0,	2, 0, 1Ch, 0AAh
		dw seg seg000
		db 5, 0, 3Eh, 0, 78h, 61h, 2 dup(6Ch), 6Fh, 63h, 2 dup(0)
		db 95h,	0Bh
		dw seg seg004
		db 2 dup(0), 3,	0Dh dup(0)
byte_20915	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h
					; DATA XREF: seg004:0B3Fo
		db 0Dh dup(0), 1, 0, 1,	0, 56h,	6Eh
		dw seg seg000
		db 5, 0, 34h, 0, 78h, 6Dh, 73h,	67h, 0Eh dup(0), 4, 0
		db 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Eh, 0, 32h, 0Dh dup(0)
		db 1, 0, 1, 0, 12h, 3
		dw seg seg004
		db 5, 0, 36h, 0, 73h, 74h, 72h,	69h, 6Eh, 67h, 0Eh dup(0)
byte_20987	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h
					; DATA XREF: seg000:A954o
		db 0Dh dup(0), 2, 0, 2,	0, 69h,	0AAh
		dw seg seg000
		db 5, 0, 4Ah, 0
aStringOutofran	db 'string::outofrange',0
		db 0, 95h, 0Bh
		dw seg seg004
		db 2 dup(0), 3,	18h dup(0)
seg004		ends
