; (included from th04_main.asm, don't assemble directly)

; ===========================================================================

; Segment type:	Pure code
seg003		segment	byte public 'CODE' use16
		assume cs:seg003
		;org 0Ch
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13A9C	proc near		; CODE XREF: sub_13AB7+15p

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
		pop	es
		assume es:dseg
		mov	si, 53A2h
		mov	di, [bp+arg_0]
		add	di, 14h

loc_13AAC:				; CODE XREF: sub_1F3AB:loc_1F539j
		mov	cx, 9		; jumptable 0001F539 case 65360
		rep movsw
		pop	di
		pop	si
		pop	bp
		retn	2
sub_13A9C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13AB7	proc near		; CODE XREF: sub_1D294+3Bp
					; sub_1FC46+D8p
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 9292h
		xor	di, di
		jmp	short loc_13B18
; ---------------------------------------------------------------------------

loc_13AC3:				; CODE XREF: sub_13AB7+64j
		cmp	byte ptr [si], 0
		jnz	short loc_13B14
		mov	byte ptr [si], 1
		push	si
		call	sub_13A9C
		mov	ax, word ptr dword_2A8C6
		mov	[si+2],	ax
		mov	ax, word ptr dword_2A8C6+2
		mov	[si+4],	ax
		mov	ax, word_2A8CE
		mov	[si+0Eh], ax
		mov	[si+26h], ax
		mov	ax, word ptr dword_2A8CA
		mov	[si+0Ah], ax
		mov	ax, word ptr dword_2A8CA+2
		mov	[si+0Ch], ax
		mov	byte ptr [si+12h], 0
		mov	al, byte_2A8D3
		mov	[si+13h], al
		mov	al, byte_2A8D2
		mov	[si+1],	al
		mov	ax, word_2A8D0
		mov	[si+10h], ax
		mov	ax, word_2A8CE
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		mov	[si+28h], ax
		jmp	short loc_13B1D
; ---------------------------------------------------------------------------

loc_13B14:				; CODE XREF: sub_13AB7+Fj
		inc	di
		add	si, 2Ah	; '*'

loc_13B18:				; CODE XREF: sub_13AB7+Aj
		cmp	di, 10h
		jl	short loc_13AC3

loc_13B1D:				; CODE XREF: sub_13AB7+5Bj
		pop	di
		pop	si
		pop	bp
		retn
sub_13AB7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13B21	proc near		; CODE XREF: sub_13B89:loc_13BACp
					; sub_161D7:loc_1621Cp	...
		push	bp
		mov	bp, sp
		push	si
		mov	si, 9292h
		xor	cx, cx
sub_13B21	endp ; sp-analysis failed

		jmp	short loc_13B81
; ---------------------------------------------------------------------------

loc_13B2C:				; CODE XREF: seg003:00F4j
		cmp	byte ptr [si], 0
		jnz	short loc_13B7D
		mov	byte ptr [si], 1
		mov	byte ptr [si+14h], 0
		mov	ax, word ptr dword_2A8C6
		mov	[si+2],	ax
		mov	ax, word ptr dword_2A8C6+2
		mov	[si+4],	ax
		mov	ax, word_2A8CE
		mov	[si+0Eh], ax
		mov	[si+26h], ax
		mov	ax, word ptr dword_2A8CA
		mov	[si+0Ah], ax
		mov	ax, word ptr dword_2A8CA+2
		mov	[si+0Ch], ax
		mov	byte ptr [si+12h], 0
		mov	al, byte_2A8D3
		mov	[si+13h], al
		mov	al, byte_2A8D2
		mov	[si+1],	al
		mov	ax, word_2A8D0
		mov	[si+10h], ax
		mov	ax, word_2A8CE
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		mov	[si+28h], ax
		jmp	short loc_13B86
; ---------------------------------------------------------------------------

loc_13B7D:				; CODE XREF: seg003:009Fj
		inc	cx
		add	si, 2Ah	; '*'

loc_13B81:				; CODE XREF: seg003:009Aj
		cmp	cx, 10h
		jl	short loc_13B2C

loc_13B86:				; CODE XREF: seg003:00EBj
		pop	si
		pop	bp
		retn

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13B89	proc near		; CODE XREF: sub_14CFD+DAp
					; sub_195E4+11p

arg_0		= byte ptr  4
arg_2		= byte ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		mov	ax, [bp+arg_4]
		or	ax, ax
		jz	short loc_13BA1
		cmp	ax, 2
		jz	short loc_13BA6
		cmp	ax, 4
		jz	short loc_13BAC
		pop	bp
		retn	6
; ---------------------------------------------------------------------------

loc_13BA1:				; CODE XREF: sub_13B89+8j
		mov	al, [bp+arg_2]
		jmp	short loc_13BA9
; ---------------------------------------------------------------------------

loc_13BA6:				; CODE XREF: sub_13B89+Dj
		mov	al, [bp+arg_0]

loc_13BA9:				; CODE XREF: sub_13B89+1Bj
		mov	byte_2A8D2, al

loc_13BAC:				; CODE XREF: sub_13B89+12j
		call	sub_13B21
		pop	bp
		retn	6
sub_13B89	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13BB3	proc near		; CODE XREF: sub_13BCE+44p

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
		pop	es
		mov	di, 53A2h
		mov	si, [bp+arg_0]
		add	si, 14h
		mov	cx, 9
		rep movsw
		pop	di
		pop	si
		pop	bp
		retn	2
sub_13BB3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13BCE	proc far		; CODE XREF: sub_AB88+76P
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 9292h
		xor	di, di
		jmp	short loc_13C29
; ---------------------------------------------------------------------------

loc_13BDA:				; CODE XREF: sub_13BCE+5Ej
		cmp	byte ptr [si], 0
		jz	short loc_13C25
		cmp	byte ptr [si], 2
		jb	short loc_13BE9
		mov	byte ptr [si], 0
		jmp	short loc_13C25
; ---------------------------------------------------------------------------

loc_13BE9:				; CODE XREF: sub_13BCE+14j
		lea	ax, [si+2]
		push	ax
		call	sub_13D32
		mov	ax, [si+0Eh]
		mov	[si+26h], ax
		mov	ax, [si+28h]
		sub	[si+0Eh], ax
		mov	al, [si+13h]
		add	[si+12h], al
		cmp	word ptr [si+0Eh], 20h ; ' '
		jge	short loc_13C25
		mov	byte ptr [si], 2
		cmp	byte ptr [si+14h], 0
		jz	short loc_13C25
		push	si
		call	sub_13BB3
		mov	ax, [si+2]
		mov	word ptr dword_266E4, ax
		mov	ax, [si+4]
		mov	word ptr dword_266E4+2,	ax
		call	word_2D000

loc_13C25:				; CODE XREF: sub_13BCE+Fj
					; sub_13BCE+19j ...
		inc	di
		add	si, 2Ah	; '*'

loc_13C29:				; CODE XREF: sub_13BCE+Aj
		cmp	di, 10h
		jl	short loc_13BDA
		pop	di
		pop	si
		pop	bp
		retf
sub_13BCE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13C32	proc near		; CODE XREF: sub_13C5C+56p
		push	bp
		mov	bp, sp
		cmp	word_266DA, 0FFC0h
		jle	short loc_13C58
		cmp	word_266DA, 1840h
		jge	short loc_13C58
		cmp	word_266DC, 0FFC0h
		jle	short loc_13C58
		cmp	word_266DC, 1740h
		jge	short loc_13C58
		mov	ax, 1
		jmp	short loc_13C5A
; ---------------------------------------------------------------------------

loc_13C58:				; CODE XREF: sub_13C32+8j
					; sub_13C32+10j ...
		xor	ax, ax

loc_13C5A:				; CODE XREF: sub_13C32+24j
		pop	bp
		retn
sub_13C32	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13C5C	proc far		; CODE XREF: sub_AB88+96P

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
		mov	si, 9292h
		mov	[bp+var_2], 0
		jmp	short loc_13CDD
; ---------------------------------------------------------------------------

loc_13C75:				; CODE XREF: sub_13C5C+85j
		cmp	byte ptr [si], 1
		jnz	short loc_13CD7
		mov	al, [si+1]
		cmp	al, [bp+var_4]
		jz	short loc_13C8B
		mov	[bp+var_4], al
		mov	ah, [bp+var_4]
		call	sub_13EF6

loc_13C8B:				; CODE XREF: sub_13C5C+24j
		xor	di, di
		jmp	short loc_13CD2
; ---------------------------------------------------------------------------

loc_13C8F:				; CODE XREF: sub_13C5C+79j
		mov	ax, di
		shl	ax, 8
		cwd
		idiv	word ptr [si+10h]
		add	al, [si+12h]
		mov	[bp+var_3], al
		push	539Ah
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	word ptr [si+0Eh]
		mov	ah, 0
		push	ax
		call	sub_1333C
		call	sub_13C32
		or	al, al
		jz	short loc_13CD1
		mov	ax, word_266DC
		add	ax, 0C0h ; 'À'
		push	ax
		call	sub_13CE8
		mov	dx, ax
		mov	ax, word_266DA
		sar	ax, 4
		add	ax, 1Ch
		call	sub_14A98

loc_13CD1:				; CODE XREF: sub_13C5C+5Bj
		inc	di

loc_13CD2:				; CODE XREF: sub_13C5C+31j
					; sub_1C2E5:loc_1C46Fj
					; DATA XREF: ...
		cmp	[si+10h], di
		jg	short loc_13C8F

loc_13CD7:				; CODE XREF: sub_13C5C+1Cj
		inc	[bp+var_2]
		add	si, 2Ah	; '*'

loc_13CDD:				; CODE XREF: sub_13C5C+17j
		cmp	[bp+var_2], 10h
		jl	short loc_13C75
		pop	di
		pop	si
		leave
		retf
sub_13C5C	endp

; ---------------------------------------------------------------------------
		db    0

; =============== S U B	R O U T	I N E =======================================


sub_13CE8	proc near		; CODE XREF: sub_13C5C+64p
					; sub_14017+E7p ...
		mov	bx, sp
		mov	ax, ss:[bx+2]
		sar	ax, 4
		cmp	byte_255BC, 0
		jz	short loc_13CFC
		add	ax, word_255B8

loc_13CFC:				; CODE XREF: sub_13CE8+Ej
		cmp	ax, 190h
		jl	short loc_13D06
		sub	ax, 190h
		jmp	short locret_13D0D
; ---------------------------------------------------------------------------

loc_13D06:				; CODE XREF: sub_13CE8+17j
		or	ax, ax
		jge	short locret_13D0D
		add	ax, 190h

locret_13D0D:				; CODE XREF: sub_13CE8+1Cj
					; sub_13CE8+20j
		retn	2
sub_13CE8	endp


; =============== S U B	R O U T	I N E =======================================


sub_13D10	proc near		; CODE XREF: sub_152B4+16Cp
		mov	bx, sp
		mov	ax, ss:[bx+2]
		sar	ax, 4
		add	ax, word_255B8
		cmp	ax, 190h
		jl	short loc_13D27
		sub	ax, 190h
		jmp	short locret_13D2E
; ---------------------------------------------------------------------------

loc_13D27:				; CODE XREF: sub_13D10+10j
		or	ax, ax
		jge	short locret_13D2E
		add	ax, 190h

locret_13D2E:				; CODE XREF: sub_13D10+15j
					; sub_13D10+19j
		retn	2
sub_13D10	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_13D32	proc near		; CODE XREF: sub_13BCE+1Fp
					; sub_14017+16p ...
		mov	bx, sp
		mov	bx, ss:[bx+2]
		mov	ax, [bx]
		mov	[bx+4],	ax
		add	ax, [bx+8]
		mov	[bx], ax
		add	bx, 2
		mov	dx, [bx]
		mov	[bx+4],	dx	; CODE XREF: sub_1CCB8:loc_1CCD9j
		add	dx, [bx+8]
		mov	[bx], dx
		retn	2
sub_13D32	endp


; =============== S U B	R O U T	I N E =======================================


sub_13D52	proc near		; CODE XREF: seg003:0921p seg003:099Fp ...
		mov	bx, word_2520C
		mov	ax, [bx+3DCCh]	; CODE XREF: sub_1CD6E:loc_1CD8Fj
		inc	byte ptr word_2520C
		retn
sub_13D52	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_13D60	proc near		; CODE XREF: sub_13E2A+35p
					; sub_147DB+2Fp ...
		mov	bx, word_2520C
		mov	ax, [bx+3DCCh]
		inc	byte ptr word_2520C
		mov	bx, sp
		and	ax, ss:[bx+2]
		retn	2
sub_13D60	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_13D76	proc near		; CODE XREF: sub_14F78+43p
					; sub_14F78+4Dp ...
		mov	bx, word_2520C
		mov	ax, [bx+3DCCh]
		inc	byte ptr word_2520C
		xor	dx, dx
		mov	bx, sp
		div	word ptr ss:[bx+2]
		mov	ax, dx
		retn	2
sub_13D76	endp

; ---------------------------------------------------------------------------
		db    0

; =============== S U B	R O U T	I N E =======================================


sub_13D90	proc near		; CODE XREF: sub_19F6E+5Bp
					; sub_19FD8+5Bp ...
		mov	bl, byte_2520F
		inc	byte_2520F
		cmp	bl, 0C7h ; 'Ç'
		jb	short loc_13DA2
		mov	byte_2520F, 0

loc_13DA2:				; CODE XREF: sub_13D90+Bj
		xor	bh, bh
		add	bx, 0C8h ; 'È'
		jmp	short loc_13DBE
sub_13D90	endp


; =============== S U B	R O U T	I N E =======================================


sub_13DAA	proc near		; CODE XREF: sub_1C8C8+307p
					; sub_1DBAE+20Cp
		mov	bl, byte_2520E
		mov	bh, 0
		inc	byte_2520E
		cmp	bl, 0C7h ; 'Ç'
		jb	short loc_13DBE
		mov	byte_2520E, 0

loc_13DBE:				; CODE XREF: sub_13D90+18j
					; sub_13DAA+Dj
		shl	bx, 4
		add	bx, 9634h
		mov	word ptr [bx], 1
		push	bp
		mov	bp, sp
		mov	ax, [bp+8]
		mov	[bx+2],	ax
		mov	ax, [bp+6]
		mov	[bx+4],	ax
		mov	word ptr [bx+0Ch], 0
		mov	al, byte_21CC8
		mov	[bx+0Eh], al
		lea	ax, [bx+0Bh]
		push	ax
		push	word ptr [bp+4]
		call	sub_189EE
		pop	bp
		retn	6
sub_13DAA	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13DF2	proc near		; CODE XREF: sub_13E2A+43p
					; sub_13E8C+47p ...

arg_0		= word ptr  4
arg_2		= byte ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		movsx	edx, [bp+arg_0]
		mov	bl, [bp+arg_2]
		mov	bh, 0
		add	bx, bx
		movsx	eax, word ptr [bx+566h]
		movsx	ecx, word ptr [bx+4E6h]
		imul	eax, edx
		sar	eax, 8
		imul	edx, ecx
		sar	edx, 8
		mov	bx, [bp+arg_4]
		mov	[bx], ax
		mov	[bx+2],	dx
		pop	bp
		retn	6
sub_13DF2	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13E2A	proc far		; CODE XREF: sub_105B9+9FP
					; sub_105B9+116P ...

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		cmp	[bp+arg_6], 1800h
		ja	short loc_13E88
		cmp	[bp+arg_4], 1700h
		ja	short loc_13E88
		push	si
		push	di
		mov	di, [bp+arg_0]

loc_13E40:				; CODE XREF: sub_13E2A+5Aj
		mov	si, word_25534
		add	si, 53E2h
		cmp	byte ptr [si], 0
		jnz	short loc_13E70
		mov	word ptr [si], 1
		mov	ax, [bp+arg_6]
		mov	[si+2],	ax
		mov	ax, [bp+arg_4]
		mov	[si+4],	ax
		push	1Fh
		call	sub_13D60
		add	ax, [bp+arg_2]
		lea	bx, [si+0Ah]
		push	bx
		push	word ptr [si+0Eh]
		push	ax
		call	sub_13DF2

loc_13E70:				; CODE XREF: sub_13E2A+21j
		add	word_25534, 10h
		cmp	word_25534, 600h

loc_13E7B:				; CODE XREF: sub_1CCB8:loc_1CCD9j
		jb	short loc_13E83	; jumptable 0001CCD9 case 65534
		mov	word_25534, 0

loc_13E83:				; CODE XREF: sub_13E2A:loc_13E7Bj
		dec	di
		jnz	short loc_13E40
		pop	di
		pop	si

loc_13E88:				; CODE XREF: sub_13E2A+8j sub_13E2A+Fj
		pop	bp
		retf	8
sub_13E2A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13E8C	proc near		; CODE XREF: sub_14017+FBp
					; sub_14017+179p ...

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah

		push	bp
		mov	bp, sp
		cmp	[bp+arg_6], 1800h
		ja	short loc_13EF1
		cmp	[bp+arg_4], 1700h
		ja	short loc_13EF1
		push	si
		push	di
		mov	di, [bp+arg_0]
		shl	di, 8

loc_13EA5:				; CODE XREF: sub_13E8C+61j
		mov	si, word_25534
		add	si, 53E2h
		cmp	byte ptr [si], 0
		jnz	short loc_13ED6
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
		call	sub_13DF2

loc_13ED6:				; CODE XREF: sub_13E8C+24j
		add	word_25534, 10h
		cmp	word_25534, 600h
		jb	short loc_13EE9
		mov	word_25534, 0

loc_13EE9:				; CODE XREF: sub_13E8C+55j
		sub	di, 100h
		jnz	short loc_13EA5
		pop	di
		pop	si

loc_13EF1:				; CODE XREF: sub_13E8C+8j sub_13E8C+Fj
		pop	bp
		retn	8
sub_13E8C	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_13EF6	proc near		; CODE XREF: sub_13C5C+2Cp
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
sub_13EF6	endp


; =============== S U B	R O U T	I N E =======================================


sub_13F10	proc near
		mov	al, 0C0h ; 'À'
		out	7Ch, al
		retn
sub_13F10	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13F16	proc near		; CODE XREF: sub_1DA1B+Dp
		push	bp
		mov	bp, sp
		push	di
		mov	cx, 28h	; '('
		mov	ax, ds
		mov	es, ax
		assume es:dseg
		xor	ax, ax
		mov	di, 41F6h
		rep stosw
		mov	byte_25590, 0
		pop	di
		pop	bp
		retn
sub_13F16	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13F30	proc near		; CODE XREF: sub_1DA38+79p

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	al, byte_25590
		mov	ah, 0
		imul	ax, 0Ah
		add	ax, 41F6h
		mov	si, ax
		inc	byte_25590
		cmp	byte_25590, 8
		jb	short loc_13F51
		mov	byte_25590, 0

loc_13F51:				; CODE XREF: sub_13F30+1Aj
		cmp	byte ptr [si], 0
		jnz	short loc_13F73
		mov	byte ptr [si], 1
		mov	ax, [bp+arg_2]
		mov	[si+2],	ax
		mov	ax, [bp+arg_0]
		mov	[si+4],	ax
		mov	word ptr [si+6], 20h ; ' '
		mov	byte ptr [si+1], 10h
		mov	word ptr [si+8], 20h ; ' '

loc_13F73:				; CODE XREF: sub_13F30+24j
		pop	si
		pop	bp
		retn	4
sub_13F30	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13F78	proc near		; CODE XREF: sub_1DE5D+F8p
		push	bp
		mov	bp, sp
		push	si
		mov	si, 41F6h
		xor	dx, dx
		jmp	short loc_13FAA
; ---------------------------------------------------------------------------

loc_13F83:				; CODE XREF: sub_13F78+35j
		cmp	byte ptr [si], 0
		jz	short loc_13FA6
		cmp	byte ptr [si], 2
		jnz	short loc_13F92
		mov	byte ptr [si], 0
		jmp	short loc_13FA6
; ---------------------------------------------------------------------------

loc_13F92:				; CODE XREF: sub_13F78+13j
		mov	ax, [si+6]
		mov	[si+8],	ax
		add	word ptr [si+6], 20h ; ' '
		cmp	word ptr [si+6], 200h
		jl	short loc_13FA6
		mov	byte ptr [si], 2

loc_13FA6:				; CODE XREF: sub_13F78+Ej
					; sub_13F78+18j ...
		inc	dx
		add	si, 0Ah

loc_13FAA:				; CODE XREF: sub_13F78+9j
		cmp	dx, 8
		jl	short loc_13F83
		pop	si
		pop	bp
		retn
sub_13F78	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_13FB2	proc near		; CODE XREF: sub_14017+26Fp
		push	bp
		mov	bp, sp
		push	si
		cmp	word ptr dword_266F4+2,	1000h
		jge	short loc_14014
		mov	si, word_26706
		cmp	si, 1
		jnz	short loc_13FCC
		mov	byte_25594, 1

loc_13FCC:				; CODE XREF: sub_13FB2+13j
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_14014
		mov	byte_266E2, 2
		mov	byte_266E3, 4Ch	; 'L'
		mov	al, byte_25594
		mov	byte_266ED, al
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EC, 0
		mov	byte_266F2, 0FFh
		call	word_2D004
		call	word_2D002
		mov	al, 80h	; '€'
		sub	al, byte_25594	; CODE XREF: sub_1BDB4:loc_1BDDEj
		mov	byte_266ED, al
		call	word_2D002
		mov	al, byte_25594
		add	al, 0Ch
		mov	byte_25594, al

loc_14014:				; CODE XREF: sub_13FB2+Aj
					; sub_13FB2+24j
		pop	si
		pop	bp
		retn
sub_13FB2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14017	proc far
		push	bp
		mov	bp, sp
		push	si
		cmp	byte_26705, 0
		jnz	loc_1411F
		mov	word_266FE, 0FFF0h
		push	53B4h
		call	sub_13D32
		mov	ax, word ptr dword_266F4
		add	ax, 0FF00h
		push	ax
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FF00h
		push	ax
		push	4B4Ah
		call	sub_B682
		push	word ptr dword_266F4
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FF00h
		push	ax
		push	504Ah
		call	sub_B682
		mov	ax, word ptr dword_266F4
		add	ax, 0FF00h
		push	ax
		push	word ptr dword_266F4+2
		push	1E4Ch
		call	sub_B682
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	234Ch
		call	sub_B682
		inc	word_26706
		cmp	word_26706, 120h
		jl	loc_142E4
		mov	byte_26705, 1
		mov	word_26706, 0
		mov	word_266FE, 2
		mov	ax, word ptr dword_266F4
		add	ax, 0FF00h
		push	ax
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FF00h
		push	ax
		push	554Ah
		call	sub_B682
		push	word ptr dword_266F4
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FF00h
		push	ax
		push	5A4Ah
		call	sub_B682
		mov	ax, word ptr dword_266F4
		add	ax, 0FF00h
		push	ax
		push	word ptr dword_266F4+2
		push	284Ch
		call	sub_B682
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	2D4Ch
		call	sub_B682
		mov	byte_26704, 88h	; 'ˆ'
		sub	word ptr dword_266F4+2,	40h ; '@'
		mov	al, byte_255B6
		mov	ah, 0
		add	word ptr dword_266F4+2,	ax
		push	word ptr dword_266F4+2
		call	sub_13CE8
		mov	word_25596, ax
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	large 300020h
		call	sub_13E8C
		push	9

loc_14117:				; CODE XREF: sub_14017+213j
					; sub_14017+288j
		call	sub_138B2
		jmp	loc_142E4
; ---------------------------------------------------------------------------

loc_1411F:				; CODE XREF: sub_14017+9j
		cmp	byte_26705, 1
		jnz	loc_141BF
		push	53B4h
		call	sub_13D32
		mov	ax, word ptr dword_266F4
		mov	word_25982, ax
		mov	ax, word ptr dword_266F4+2
		mov	word_25984, ax
		inc	word_26706
		cmp	byte_26704, 8Bh	; '‹'
		jnb	short loc_14158
		mov	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1419A
		inc	byte_26704
		jmp	short loc_1419A	; CODE XREF: sub_1CD6E:loc_1CD8Fj
; ---------------------------------------------------------------------------

loc_14158:				; CODE XREF: sub_14017+12Cj
		cmp	word_26706, 60h	; '`'
		jl	short loc_1419A
		mov	byte_26705, 2
		mov	word_26706, 0
		mov	byte_26704, 8Ch	; 'Œ'
		sub	word ptr dword_266F4+2,	100h
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FF00h
		push	ax
		call	sub_13CE8
		mov	word_25596, ax
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	large 300020h
		call	sub_13E8C
		push	9
		call	sub_138B2

loc_1419A:				; CODE XREF: sub_14017+139j
					; sub_14017+13Fj ...
		mov	word_257E2, 100h
		mov	word_257E4, 0C0h ; 'À'
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_257DE, ax
		mov	ax, word ptr dword_266F4+2
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		or	ax, ax
		jz	loc_142E4
		jmp	short loc_14228
; ---------------------------------------------------------------------------

loc_141BF:				; CODE XREF: sub_14017+10Dj
		cmp	byte_26705, 2
		jnz	short loc_1422D
		push	53B4h
		call	sub_13D32
		mov	ax, word ptr dword_266F4
		mov	word_25982, ax
		mov	ax, word ptr dword_266F4+2
		mov	word_25984, ax
		inc	word_26706
		cmp	byte_26704, 92h	; '’'
		jnb	short loc_141FA
		mov	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_14205
		mov	al, byte_26704
		add	al, 2
		mov	byte_26704, al
		jmp	short loc_14205
; ---------------------------------------------------------------------------

loc_141FA:				; CODE XREF: sub_14017+1CAj
		mov	byte_26705, 3
		mov	word_26706, 0

loc_14205:				; CODE XREF: sub_14017+1D7j
					; sub_14017+1E1j
		mov	word_257E2, 180h
		mov	word_257E4, 100h
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_257DE, ax
		mov	ax, word ptr dword_266F4+2
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		or	ax, ax
		jz	loc_142E4

loc_14228:				; CODE XREF: sub_14017+1A6j
		push	0Ah
		jmp	loc_14117
; ---------------------------------------------------------------------------

loc_1422D:				; CODE XREF: sub_14017+1ADj
		cmp	byte_26705, 3
		jnz	loc_142E1
		push	53B4h
		call	sub_13D32
		cmp	byte_255B7, 2
		ja	short loc_142AC
		mov	ax, word ptr dword_266F4
		mov	word_25982, ax
		mov	ax, word ptr dword_266F4+2
		mov	word_25984, ax
		inc	word_26706
		mov	word_257E2, 180h
		mov	word_257E4, 100h
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_257DE, ax
		mov	ax, word ptr dword_266F4+2
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		mov	si, ax
		mov	byte_266E2, 1
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FFF0h
		mov	word ptr dword_266E4+2,	ax
		call	sub_13FB2
		or	si, si
		jz	short loc_142E4
		sub	word_26702, si
		cmp	word_26702, 0
		jle	short loc_142A2
		mov	byte_26708, 1
		push	4
		jmp	loc_14117
; ---------------------------------------------------------------------------

loc_142A2:				; CODE XREF: sub_14017+27Fj
		mov	byte_2CFF9, 1
		push	5
		call	sub_19F6E

loc_142AC:				; CODE XREF: sub_14017+22Aj
		mov	byte_26705, 0FEh ; 'þ'
		mov	byte_26704, 4
		mov	word_26706, 0
		mov	word_266FE, 0
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	large 800030h
		call	sub_13E8C
		push	0Ch
		call	sub_138B2
		mov	byte_255B7, 4
		jmp	short loc_142E4
; ---------------------------------------------------------------------------

loc_142E1:				; CODE XREF: sub_14017+21Bj
		call	sub_1A047

loc_142E4:				; CODE XREF: sub_14017+6Fj
					; sub_14017+105j ...
		push	word_26702
		push	26Ch
		call	sub_19F16
		pop	si
		pop	bp
		retf
sub_14017	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26706, 2
		jnz	short loc_14339
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266F4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266F4
		push	ax
		call	sub_1DA8
		mov	byte_26709, al
		mov	byte_266E2, 2
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		mov	byte_266EE, 28h	; '('
		mov	byte_266ED, 0
		call	word_2D004
		call	word_2D000

loc_14339:				; CODE XREF: seg003:0869j
		mov	ax, word_26706
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1436F
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 2
		mov	byte_266F0, 0Ch
		mov	byte_266EE, 34h	; '4'
		mov	al, byte_26709
		mov	byte_266ED, al
		call	word_2D004
		call	word_2D000
		push	3
		call	sub_138B2

loc_1436F:				; CODE XREF: seg003:08B4j
		cmp	word_26706, 20h	; ' '
		jl	short loc_14381
		mov	byte_25598, 0FFh
		mov	word_26706, 0

loc_14381:				; CODE XREF: seg003:08E4j
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26706, 20h	; ' '
		jl	short loc_143C5
		mov	byte_25598, 0FFh
		mov	word_26706, 0
		mov	byte_266E2, 5
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		mov	byte_266EE, 28h	; '('
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D004
		call	sub_1CFA2
		push	9
		call	sub_138B2

loc_143C5:				; CODE XREF: seg003:08FBj
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26706, 1
		jnz	short loc_143D6
		mov	byte_26709, 80h	; '€'

loc_143D6:				; CODE XREF: seg003:093Fj
		mov	ax, word_26706
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_14411
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 2
		mov	byte_266F0, 12h
		mov	byte_266EE, 2Eh	; '.'
		mov	al, byte_26709
		mov	byte_266ED, al
		add	al, 0F8h ; 'ø'
		mov	byte_26709, al
		call	word_2D004
		call	word_2D000
		push	3
		call	sub_138B2

loc_14411:				; CODE XREF: seg003:0951j
		cmp	word_26706, 20h	; ' '
		jl	short loc_14423
		mov	byte_25598, 0FFh
		mov	word_26706, 0

loc_14423:				; CODE XREF: seg003:0986j
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		cmp	word_26706, 1
		jnz	short loc_14435
		call	sub_13D52
		mov	byte_26709, al

loc_14435:				; CODE XREF: seg003:099Dj
		mov	ax, word_26706
		mov	bx, 6
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_14477
		mov	byte_266E2, 2
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EE, 20h	; ' '
		mov	al, byte_26709
		mov	byte_266ED, al
		mov	byte_266EF, 18h
		call	word_2D004
		call	sub_1CFA2
		push	9
		call	sub_138B2
		mov	al, byte_26709
		add	al, 6
		mov	byte_26709, al

loc_14477:				; CODE XREF: seg003:09B0j
		cmp	word_26706, 20h	; ' '
		jl	short loc_14489
		mov	byte_25598, 0FFh
		mov	word_26706, 0

loc_14489:				; CODE XREF: seg003:09ECj
		pop	bp
		retn
; ---------------------------------------------------------------------------
		db 0C8h, 4, 2 dup(0), 56h, 0A1h, 0B4h, 53h, 0A3h, 42h
		db 46h,	0A1h, 0B6h, 53h, 0A3h, 44h, 46h, 80h, 3Eh, 0C5h
		db 53h,	0, 75h,	4Eh, 68h, 0B4h,	53h, 0E8h, 89h,	0F8h, 0FFh
		db 6, 0C6h, 53h, 66h, 68h, 80h,	1, 80h,	1, 6Ah,	0Ah, 0E8h
		db 60h,	0A1h, 8Bh, 0F0h, 83h, 3Eh, 0C6h, 53h, 14h, 0Fh
		db 8Ch,	0CAh, 1, 0FEh, 6, 0C5h,	53h, 0C7h, 6, 0C6h, 53h
		db 2 dup(0), 0C7h, 6, 0BCh, 53h, 2 dup(0), 0C7h, 6, 0BEh
		db 53h,	2 dup(0), 6Ah, 3, 0E8h,	82h, 0F8h, 0A2h, 58h, 42h
		db 6Ah,	1, 0E8h, 7Ah, 0F8h, 0A2h, 59h, 42h, 0C6h, 6, 5Ah
		db 42h,	0, 0E9h, 9Ch, 1, 80h, 3Eh, 0C5h, 53h, 1, 0Fh, 85h
		db 90h,	1, 68h,	0B4h, 53h, 0E8h, 32h, 0F8h, 0FFh, 6, 0C6h
		db 53h,	0C6h, 6, 0A2h, 53h, 1, 0A1h, 0B4h, 53h,	0A3h, 0A4h
		db 53h,	0A1h, 0B6h, 53h, 5, 0, 0FFh, 0A3h, 0A6h, 53h, 0A0h
		db 58h,	42h, 0B4h, 0, 89h, 46h,	0FCh, 0B9h, 5, 0, 0BBh
		db 0Bh,	0Ch, 2Eh, 8Bh, 7, 3Bh, 46h, 0FCh, 74h, 8, 83h
		db 0C3h, 2, 0E2h, 0F3h,	0E9h, 0B4h, 0, 2Eh, 0FFh, 67h
		db 0Ah,	0E8h, 0B4h, 0FDh, 0E9h,	0AAh, 0, 0E8h, 40h, 0FEh
		db 0E9h, 0A4h, 0, 0E8h,	7Eh, 0FEh, 0E9h, 9Eh, 0, 0E8h
		db 0D6h, 0FEh, 0E9h, 98h, 0, 80h, 3Eh, 5Ah, 42h, 0Bh, 77h
		db 4Ch,	0A1h, 0B4h, 53h, 0A3h, 86h, 95h, 0A1h, 0B6h, 53h
		db 0A3h, 88h, 95h, 0A1h, 0C6h, 53h, 5, 0C0h, 0FFh, 50h
		db 66h,	68h, 9,	0, 0Fh,	0, 0E8h, 14h, 0F6h, 0A1h, 0C6h
		db 53h,	3Dh, 40h, 0, 74h, 7, 3Dh, 44h, 0, 74h, 10h, 0EBh
		db 21h,	0C7h, 6, 0BCh, 53h, 2 dup(0), 0C7h, 6, 0BEh, 53h
		db 2 dup(0), 0EBh, 13h,	0C7h, 6, 0C6h, 53h, 2 dup(0), 0A0h
		db 5Ah,	42h, 24h, 3, 0A2h, 58h,	42h, 0C6h, 6, 0C4h, 53h
		db 0, 83h, 3Eh,	0C6h, 53h, 1, 75h, 3Eh,	0A0h, 5Ah, 42h
		db 0B4h, 0, 8Bh, 0D8h, 8Ah, 87h, 90h, 17h, 88h,	46h, 0FFh
		db 80h,	3Eh, 59h, 42h, 0, 74h, 8, 0B0h,	80h, 2Ah, 46h
		db 0FFh, 88h, 46h, 0FFh, 1Eh, 68h, 0BCh, 53h, 1Eh, 68h
		db 0BEh, 53h, 0FFh, 76h, 0FFh, 6Ah, 20h, 9Ah, 37h, 0
		dw seg seg002
		db 0FEh, 6, 5Ah, 42h, 0C6h, 6, 0C4h, 53h, 1, 0C7h, 6, 90h
		db 95h,	8, 0, 81h, 3Eh,	0B6h, 53h, 0, 17h, 7Dh,	0Fh, 83h
		db 3Eh,	0B4h, 53h, 0, 7Eh, 8, 81h, 3Eh,	0B4h, 53h, 0, 18h
		db 7Ch,	5, 0C6h, 6, 0C5h, 53h, 3, 66h, 68h, 80h, 1, 80h
		db 1, 6Ah, 4, 0E8h, 7, 0A0h, 8Bh, 0F0h,	0Bh, 0F6h, 74h
		db 76h,	29h, 36h, 0C2h,	53h, 83h, 3Eh, 0C2h, 53h, 0, 7Eh
		db 7, 0C6h, 6, 0C8h, 53h, 1, 0EBh, 64h,	0C6h, 6, 0C8h
		db 53h,	1, 0A1h, 0B6h, 53h, 5, 0, 0FFh,	50h, 0E8h, 0D8h
		db 0F6h, 8Bh, 0F0h, 0C6h, 6, 0B9h, 0BCh, 1, 0A0h, 5Ah
		db 42h,	0B4h, 0, 0BAh, 14h, 0, 2Bh, 0D0h, 52h, 0E8h, 21h
		db 59h,	0C6h, 6, 0C5h, 53h, 0FEh, 0C6h,	6, 0C4h, 53h, 4
		db 0C7h, 6, 0C6h, 53h, 2 dup(0), 0C7h, 6, 0BCh,	53h, 2 dup(0)
		db 0FFh, 36h, 0B4h, 53h, 0FFh, 36h, 0B6h, 53h, 66h, 68h
		db 30h,	0, 60h,	0, 0E8h, 18h, 0F8h, 6Ah, 0Ch, 9Ah, 0D2h
		db 7
		dw seg seg002
		db 0FFh, 36h, 0B4h, 53h, 0FFh, 36h, 0B6h, 53h, 6Ah, 5
		db 0E8h, 0B0h, 93h, 0EBh, 3, 0E8h
; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_1F903

loc_1468B:				; CODE XREF: sub_1F903:loc_1F922j
		mov	dx, 0FF59h	; jumptable 0001F922 case 46147
		db	36h
		retn	6853h
; END OF FUNCTION CHUNK	FOR sub_1F903
; ---------------------------------------------------------------------------
		db 52h,	3, 0E8h, 7Fh, 58h, 5Eh,	0C9h, 0CBh, 3 dup(0), 1
		db 0, 2, 0, 3, 0, 0FFh,	0, 0AAh, 0Ah, 0B0h, 0Ah, 0B6h
		db 0Ah,	0BCh, 0Ah, 0C2h, 0Ah

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_146AF	proc near		; CODE XREF: seg003:loc_14975p
					; seg003:loc_149A3p ...
		push	bp
		mov	bp, sp
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_266F8, ax
		mov	ax, word ptr dword_266F4+2
		mov	word ptr dword_266F8+2,	ax
		push	0C00h
		push	word_26702
		mov	al, byte_26709
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+566h]
		call	sub_13320
		mov	word ptr dword_266F4, ax
		push	600h
		push	word_26702
		mov	al, byte_26709
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4E6h]
		call	sub_13320
		mov	word ptr dword_266F4+2,	ax
		mov	al, byte_26709
		add	al, 0FEh ; 'þ'
		mov	byte_26709, al
		pop	bp
		retn
sub_146AF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14700	proc near		; CODE XREF: seg003:loc_14A0Ap
					; seg003:loc_14A31p ...
		push	bp
		mov	bp, sp
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_266F8, ax
		mov	ax, word ptr dword_266F4+2
		mov	word ptr dword_266F8+2,	ax
		cmp	word_26706, 1
		jnz	short loc_14721
		mov	word_266FC, 10h
		mov	byte_26709, 0

loc_14721:				; CODE XREF: sub_14700+14j
		mov	ax, word_266FC
		add	word ptr dword_266F4, ax
		cmp	byte_26705, 5
		ja	short loc_14749
		cmp	word ptr dword_266F4, 100h
		jle	short loc_1473F
		cmp	word ptr dword_266F4, 1700h
		jl	short loc_14749

loc_1473F:				; CODE XREF: sub_14700+35j
		mov	ax, 0FFFFh
		imul	word_266FC
		mov	word_266FC, ax

loc_14749:				; CODE XREF: sub_14700+2Dj
					; sub_14700+3Dj
		push	600h
		push	word_26702
		mov	al, byte_26709
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4E6h]
		call	sub_13320
		mov	word ptr dword_266F4+2,	ax
		mov	al, byte_26709
		add	al, 2
		mov	byte_26709, al
		pop	bp
		retn
sub_14700	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1476F	proc near		; CODE XREF: sub_1CCB8-8325p
					; seg003:0F31p
		push	bp
		mov	bp, sp
		cmp	byte_266CF, 0
		jnz	short loc_14796
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266EE, 30h	; '0'
		call	word_2D004
		call	word_2D000

loc_14796:				; CODE XREF: sub_1476F+8j
		pop	bp
		retn
sub_1476F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14798	proc near		; CODE XREF: seg003:0F5Ep
		push	bp
		mov	bp, sp
		cmp	byte_266CF, 0
		jnz	short loc_147D9
		mov	byte_266E2, 5
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		call	sub_13D52
		mov	byte_266ED, al
		mov	ax, word_26706
		mov	bx, 4
		cwd
		idiv	bx
		add	al, 0Ah
		mov	byte_266EE, al
		call	word_2D004
		call	word_2D000
		push	3
		call	sub_138B2

loc_147D9:				; CODE XREF: sub_14798+8j
		pop	bp
		retn
sub_14798	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_147DB	proc near		; CODE XREF: seg003:0F7Dp
		push	bp
		mov	bp, sp
		cmp	byte_266CF, 0
		jnz	short loc_14826
		mov	byte_266E2, 2
		mov	byte_266F2, 87h	; '‡'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 5
		mov	byte_266F0, 0Ch
		mov	byte_266E3, 3Bh	; ';'
		mov	byte_266EE, 20h	; ' '
		push	0Fh
		call	sub_13D60
		add	al, 0B8h ; '¸'
		mov	byte_266ED, al
		call	word_2D004
		mov	byte_2CFF7, 2
		call	word_2D002
		push	9
		call	sub_138B2

loc_14826:				; CODE XREF: sub_147DB+8j
		pop	bp
		retn
sub_147DB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14828	proc near		; CODE XREF: seg003:0FACp
		push	bp
		mov	bp, sp
		cmp	byte_266CF, 0
		jnz	short loc_1486C
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266EE, 20h	; ' '
		call	word_2D004
		call	word_2D000
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 10h
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266EE, 30h	; '0'
		call	word_2D004
		call	word_2D000

loc_1486C:				; CODE XREF: sub_14828+8j
		pop	bp
		retn
sub_14828	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1486E	proc near		; CODE XREF: seg003:0FC0p

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_26706
		mov	[bp+var_2], ax
		mov	cx, 15h		; switch 21 cases
		mov	bx, offset word_148F8

loc_1487E:				; CODE XREF: sub_1486E+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1488D
		add	bx, 2
		loop	loc_1487E
		jmp	short locret_148F5 ; default
; ---------------------------------------------------------------------------

loc_1488D:				; CODE XREF: sub_1486E+16j
		jmp	word ptr cs:[bx+2Ah] ; switch jump

loc_14891:				; DATA XREF: seg003:0E92o
		push	9		; jumptable 0001488D cases 250,258,266,274
		call	sub_138B2
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	2
		jmp	short loc_148F2
; ---------------------------------------------------------------------------

loc_148A4:				; CODE XREF: sub_1486E:loc_1488Dj
					; DATA XREF: seg003:0E92o
		push	3		; jumptable 0001488D cases 290,298,306,314,390,398,406,414,490,498,506,514
		call	sub_138B2
		mov	byte_266EC, 2Eh	; '.'
		mov	byte_266EF, 5
		mov	byte_266F0, 6
		mov	byte_266ED, 0
		mov	byte_266EE, 40h	; '@'
		call	word_2D004
		call	word_2D000
		leave
		retn
; ---------------------------------------------------------------------------

loc_148CE:				; CODE XREF: sub_1486E:loc_1488Dj
					; DATA XREF: seg003:0E92o
		push	9		; jumptable 0001488D cases 350,358,366,374

loc_148D0:				; CODE XREF: sub_1F3AB:loc_1F539j
		call	sub_138B2
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	3
		jmp	short loc_148F2
; ---------------------------------------------------------------------------

loc_148E1:				; CODE XREF: sub_1486E:loc_1488Dj
					; DATA XREF: seg003:0E92o
		push	9		; jumptable 0001488D case 450
		call	sub_138B2
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	5

loc_148F2:				; CODE XREF: sub_1486E+34j
					; sub_1486E+71j
		call	sub_1DA38

locret_148F5:				; CODE XREF: sub_1486E+1Dj
		leave			; default
		retn
sub_1486E	endp

; ---------------------------------------------------------------------------
		db    0
word_148F8	dw   0FAh,  102h,  10Ah,  112h ; DATA XREF: sub_1486E+Do
		dw   122h,  12Ah,  132h,  13Ah ; value table for switch	statement
		dw   15Eh,  166h,  16Eh,  176h
		dw   186h,  18Eh,  196h,  19Eh
		dw   1C2h,  1EAh,  1F2h,  1FAh
		dw   202h
		dw offset loc_14891	; jump table for switch	statement
		dw offset loc_14891
		dw offset loc_14891
		dw offset loc_14891
		dw offset loc_148A4
		dw offset loc_148A4
		dw offset loc_148A4
		dw offset loc_148A4
		dw offset loc_148CE
		dw offset loc_148CE
		dw offset loc_148CE
		dw offset loc_148CE
		dw offset loc_148A4
		dw offset loc_148A4
		dw offset loc_148A4
		dw offset loc_148A4
		dw offset loc_148E1
		dw offset loc_148A4
		dw offset loc_148A4
		dw offset loc_148A4
		dw offset loc_148A4
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_266F4+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266E2, 1
		mov	al, byte_26705
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 6
		ja	loc_14A87
		add	bx, bx
		jmp	cs:off_14A8A[bx]

loc_14975:				; DATA XREF: seg003:off_14A8Ao
		call	sub_146AF
		inc	word_26706
		cmp	word_26702, 80h	; '€'
		jle	short loc_14989
		sub	word_26702, 20h	; ' '

loc_14989:				; CODE XREF: seg003:0EF2j
		cmp	word_26706, 80h	; '€'
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_1498F:				; CODE XREF: sub_1CCB8:loc_1CCD9j
		jl	loc_14A87	; jumptable 0001CCD9 case 17022
		call	sub_1476F
		cmp	word_26706, 140h
		jl	loc_14A87
		jmp	loc_14A29
; END OF FUNCTION CHUNK	FOR sub_1CCB8
; ---------------------------------------------------------------------------

loc_149A3:				; CODE XREF: seg003:0EE0j
					; DATA XREF: seg003:0FFCo
		call	sub_146AF
		inc	word_26706
		cmp	word_26702, 380h
		jge	short loc_149B7
		add	word_26702, 8

loc_149B7:				; CODE XREF: seg003:0F20j
		cmp	word_26706, 80h	; '€'
		jl	loc_14A87
		call	sub_1476F
		cmp	word_26706, 140h
		jl	loc_14A87
		jmp	short loc_14A29
; ---------------------------------------------------------------------------

loc_149D0:				; CODE XREF: seg003:0EE0j
					; DATA XREF: seg003:0FFEo
		call	sub_146AF
		inc	word_26706
		cmp	word_26702, 80h	; '€'
		jle	short loc_149E4
		sub	word_26702, 20h	; ' '

loc_149E4:				; CODE XREF: seg003:0F4Dj
		cmp	word_26706, 80h	; '€'
		jl	loc_14A87
		call	sub_14798
		cmp	word_26706, 140h
		jl	loc_14A87
		jmp	short loc_14A29
; ---------------------------------------------------------------------------

loc_149FD:				; CODE XREF: seg003:0EE0j
					; DATA XREF: seg003:1000o
		cmp	word_26706, 80h	; '€'
		jge	short loc_14A0A
		call	sub_146AF
		jmp	short loc_14A1D
; ---------------------------------------------------------------------------

loc_14A0A:				; CODE XREF: seg003:0F73j
		call	sub_14700
		call	sub_147DB
		cmp	word_26702, 300h
		jge	short loc_14A1D
		add	word_26702, 8

loc_14A1D:				; CODE XREF: seg003:0F78j seg003:0F86j
		inc	word_26706
		cmp	word_26706, 280h
		jl	short loc_14A87
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_14A29:				; CODE XREF: sub_1CCB8-8318j
					; seg003:0F3Ej	...
		mov	word_26706, 0
		jmp	short loc_14A65
; END OF FUNCTION CHUNK	FOR sub_1CCB8
; ---------------------------------------------------------------------------

loc_14A31:				; CODE XREF: seg003:0EE0j
					; DATA XREF: seg003:1002o
		call	sub_14700
		cmp	word_26706, 0A0h ; ' '
		jl	short loc_14A3F
		call	sub_14828

loc_14A3F:				; CODE XREF: seg003:0FAAj
		inc	word_26706
		cmp	word_26706, 1B8h
		jl	short loc_14A87
		jmp	short loc_14A5F
; ---------------------------------------------------------------------------

loc_14A4D:				; CODE XREF: seg003:0EE0j
					; DATA XREF: seg003:off_14A94o
		call	sub_14700
		call	sub_1486E
		inc	word_26706
		cmp	word_26706, 208h
		jl	short loc_14A87

loc_14A5F:				; CODE XREF: seg003:0FBBj
		mov	word_26706, 2
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_14A65:				; CODE XREF: sub_1CCB8-8289j
		inc	byte_26705
		pop	bp
		retf
; END OF FUNCTION CHUNK	FOR sub_1CCB8
; ---------------------------------------------------------------------------

loc_14A6B:				; CODE XREF: seg003:0EE0j
					; DATA XREF: seg003:1006o
		call	sub_14700
		inc	word_26706
		cmp	word ptr dword_266F4, 0FF00h
		jle	short loc_14A82
		cmp	word ptr dword_266F4, 1900h
		jl	short loc_14A87

loc_14A82:				; CODE XREF: seg003:0FE8j
		nop
		push	cs
		call	near ptr sub_19EBC
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_14A87:				; CODE XREF: seg003:0EDAj
					; sub_1CCB8:loc_1498Fj	...
		pop	bp
		retf
; END OF FUNCTION CHUNK	FOR sub_1CCB8
; ---------------------------------------------------------------------------
		db    0
off_14A8A	dw offset loc_14975	; DATA XREF: seg003:0EE0r
		dw offset loc_149A3
		dw offset loc_149D0
		dw offset loc_149FD
		dw offset loc_14A31
off_14A94	dw offset loc_14A4D	; CODE XREF: sub_1C2E5:loc_1C46Fj
					; DATA XREF: sub_C696+1Ao
		dw offset loc_14A6B

; =============== S U B	R O U T	I N E =======================================


sub_14A98	proc near		; CODE XREF: sub_13C5C+72p
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
		add	si, 179Ch
		mov	cx, 8
		cmp	bx, 188h
		ja	short loc_14AC6
		xor	dx, dx
		jmp	short loc_14ACF
; ---------------------------------------------------------------------------

loc_14AC6:				; CODE XREF: sub_14A98+28j
		mov	dx, cx
		mov	cx, 190h
		sub	cx, bx
		sub	dx, cx

loc_14ACF:				; CODE XREF: sub_14A98+2Cj
		or	ax, ax
		jz	short loc_14AE6
		nop

loc_14AD4:				; CODE XREF: sub_14A98+40j
					; sub_14A98+4Cj
		movsw
		add	di, 4Eh	; 'N'
		loop	loc_14AD4

loc_14ADA:				; CODE XREF: sub_14A98+55j
		or	dx, dx
		jz	short loc_14AEF
		sub	di, 7D00h
		xchg	cx, dx
		jmp	short loc_14AD4
; ---------------------------------------------------------------------------

loc_14AE6:				; CODE XREF: sub_14A98+39j
					; sub_14A98+53j
		movsb
		add	di, 4Fh	; 'O'
		inc	si
		loop	loc_14AE6
		jmp	short loc_14ADA
; ---------------------------------------------------------------------------

loc_14AEF:				; CODE XREF: sub_14A98+44j
		pop	di
		pop	si
		retn
sub_14A98	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14AF2	proc near		; CODE XREF: sub_14CFD:loc_14DA6p
		push	bp
		mov	bp, sp
		push	si
		mov	si, word_26706
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_14B63
		push	3
		call	sub_138B2
		mov	al, byte_255B3
		shl	al, 5
		add	al, 20h	; ' '
		mov	byte_266ED, al
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		test	al, 1
		jz	short loc_14B47
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 0
		mov	byte_266EE, 2Ah	; '*'
		call	word_2D004
		call	word_2D000
		mov	byte_266F0, 0Fh
		jmp	short loc_14B4C
; ---------------------------------------------------------------------------

loc_14B47:				; CODE XREF: sub_14AF2+30j
					; sub_1C2E5:loc_1C46Fj
					; DATA XREF: ...
		mov	byte_266F0, 0Ah

loc_14B4C:				; CODE XREF: sub_14AF2+53j
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 6
		mov	byte_266EE, 24h	; '$'
		call	word_2D004
		call	word_2D000

loc_14B63:				; CODE XREF: sub_14AF2+12j
		cmp	si, 40h	; '@'
		jl	short loc_14B73
		mov	word_26706, 0
		mov	byte_255B2, 0FFh

loc_14B73:				; CODE XREF: sub_14AF2+74j
		pop	si
		pop	bp
		retn
sub_14AF2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14B76	proc near		; CODE XREF: sub_14CFD:loc_14DACp
		push	bp
		mov	bp, sp
		push	si
		mov	si, word_26706
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_14BBA
		push	3
		call	sub_138B2
		mov	al, byte_255B3
		shl	al, 5
		add	al, 20h	; ' '
		mov	byte_266ED, al
		mov	ax, si
		cwd
		sub	ax, dx
		sar	ax, 1
		add	al, 20h	; ' '
		mov	byte_266EE, al
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		call	word_2D004
		call	word_2D000

loc_14BBA:				; CODE XREF: sub_14B76+12j
		cmp	si, 20h	; ' '
		jl	short loc_14BCA
		mov	word_26706, 0
		mov	byte_255B2, 0FFh

loc_14BCA:				; CODE XREF: sub_14B76+47j
		pop	si
		pop	bp
		retn
sub_14B76	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14BCD	proc near		; CODE XREF: sub_14CFD:loc_14DB2p
		push	bp
		mov	bp, sp
		push	si
		mov	si, word_26706
		mov	ax, si
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_14C32
		push	3
		call	sub_138B2
		mov	byte_266EE, 40h	; '@'
		mov	byte_266EC, 0
		mov	al, byte_255B3
		shl	al, 5
		add	al, 8
		mov	byte_266ED, al
		call	word_2D004
		call	word_2D000
		mov	al, byte_255B3
		shl	al, 5
		add	al, 10h
		mov	byte_266ED, al
		call	word_2D000
		mov	al, byte_255B3
		shl	al, 5
		add	al, 38h	; '8'
		mov	byte_266ED, al
		call	word_2D000
		mov	al, byte_255B3
		shl	al, 5
		add	al, 30h	; '0'
		mov	byte_266ED, al
		call	word_2D000

loc_14C32:				; CODE XREF: sub_14BCD+12j
		cmp	si, 20h	; ' '
		jl	short loc_14C42
		mov	word_26706, 0
		mov	byte_255B2, 0FFh

loc_14C42:				; CODE XREF: sub_14BCD+68j
		pop	si
		pop	bp
		retn
sub_14BCD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14C45	proc near		; CODE XREF: sub_14CFD:loc_14DB8p
		push	bp
		mov	bp, sp
		push	si
		mov	ax, word_26706
		dec	ax
		mov	si, ax
		or	si, si
		jnz	short loc_14C6B
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266F4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266F4
		push	ax
		call	sub_1DA8
		mov	byte_26709, al

loc_14C6B:				; CODE XREF: sub_14C45+Cj
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_14CCC
		push	3
		call	sub_138B2
		mov	byte_266EE, 28h	; '('
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 5
		mov	byte_266F0, 10h
		mov	al, byte_26709
		mov	byte_266ED, al
		call	word_2D004
		call	word_2D000
		mov	byte_266EE, 0Ah
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266F4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266F4
		push	ax
		call	sub_1DA8
		mov	byte_266ED, al
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EC, 0
		mov	byte_266F2, 0FFh

loc_14CCC:				; CODE XREF: sub_14C45+30j
		mov	ax, si
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cmp	dx, 18h
		jl	short loc_14CEA
		mov	byte_266E2, 4
		mov	al, byte_266EE
		add	al, 0Ah
		mov	byte_266EE, al
		call	word_2D002

loc_14CEA:				; CODE XREF: sub_14C45+92j
		cmp	si, 40h	; '@'
		jl	short loc_14CFA
		mov	word_26706, 0
		mov	byte_255B2, 0FFh

loc_14CFA:				; CODE XREF: sub_14C45+A8j
		pop	si
		pop	bp
		retn
sub_14C45	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14CFD	proc far

var_2		= word ptr -2

		enter	2, 0
		push	si
		mov	ax, word ptr dword_266F4
		mov	word_25982, ax
		mov	ax, word ptr dword_266F4+2
		mov	word_25984, ax
		cmp	byte_26705, 0
		jnz	short loc_14D5D
		push	53B4h
		call	sub_13D32
		inc	word_26706
		push	large 1800180h
		push	0Ah
		call	sub_1E618
		mov	si, ax
		cmp	word_26706, 60h	; '`'
		jl	loc_14F57
		inc	byte_26705
		mov	word_26706, 0
		mov	word_266FC, 0
		mov	word_266FE, 0
		mov	byte_255B2, 0
		mov	byte_255B3, 1
		mov	byte_255B4, 0
		jmp	loc_14F57
; ---------------------------------------------------------------------------

loc_14D5D:				; CODE XREF: sub_14CFD+16j
		cmp	byte_26705, 1
		jnz	loc_14F16
		push	53B4h
		call	sub_13D32
		inc	word_26706
		mov	byte_266E2, 1
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FF00h
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_255B2
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	cx, 5		; switch 5 cases
		mov	bx, offset word_14F64

loc_14D92:				; CODE XREF: sub_14CFD+A0j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_14DA2
		add	bx, 2
		loop	loc_14D92
		jmp	loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14DA2:				; CODE XREF: sub_14CFD+9Bj
		jmp	word ptr cs:[bx+0Ah] ; switch jump

loc_14DA6:				; DATA XREF: seg003:14DEo
		call	sub_14AF2	; jumptable 00014DA2 case 0
		jmp	loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14DAC:				; CODE XREF: sub_14CFD:loc_14DA2j
					; DATA XREF: seg003:14DEo
		call	sub_14B76	; jumptable 00014DA2 case 1
		jmp	loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14DB2:				; CODE XREF: sub_14CFD:loc_14DA2j
					; DATA XREF: seg003:14DEo
		call	sub_14BCD	; jumptable 00014DA2 case 2
		jmp	loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14DB8:				; CODE XREF: sub_14CFD:loc_14DA2j
					; DATA XREF: seg003:14DEo
		call	sub_14C45	; jumptable 00014DA2 case 3
		jmp	loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14DBE:				; CODE XREF: sub_14CFD:loc_14DA2j
					; DATA XREF: seg003:14DEo
		mov	ax, word ptr dword_266F4 ; jumptable 00014DA2 case 255
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_266F4+2
		mov	word ptr dword_2A8C6+2,	ax
		mov	ax, word_26706
		add	ax, 0FFD0h
		push	ax
		push	large 0F0007h
		call	sub_13B89
		mov	ax, word_26706
		cmp	ax, 1
		jz	short loc_14E20
		cmp	ax, 30h	; '0'
		jz	short loc_14DEF
		cmp	ax, 34h	; '4'
		jz	short loc_14DF8
		jmp	loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14DEF:				; CODE XREF: sub_14CFD+E8j
		mov	word_266FC, 0
		jmp	loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14DF8:				; CODE XREF: sub_14CFD+EDj
		mov	word_26706, 0
		cmp	byte_255B3, 1
		jnz	short loc_14E0A
		mov	byte_26704, 0

loc_14E0A:				; CODE XREF: sub_14CFD+106j
		inc	byte_255B4
		mov	al, byte_255B4
		and	al, 3
		mov	byte_255B2, al
		cmp	byte_255B4, 10h
		jbe	short loc_14E8E	; default
		jmp	loc_14EE0
; ---------------------------------------------------------------------------

loc_14E20:				; CODE XREF: sub_14CFD+E3j
		mov	word_2A8D0, 8
		mov	word_2A8CE, 600h
		cmp	byte_255B3, 1
		jnz	short loc_14E5E
		call	sub_13D52
		test	al, 1
		jz	short loc_14E4C
		mov	byte_26704, 1
		mov	byte_255B3, 0
		mov	word_266FC, 0FFD0h
		jmp	short loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14E4C:				; CODE XREF: sub_14CFD+13Bj
		mov	byte_26704, 2
		mov	byte_255B3, 2
		mov	word_266FC, 30h	; '0'
		jmp	short loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14E5E:				; CODE XREF: sub_14CFD+134j
		cmp	byte_255B3, 0
		jnz	short loc_14E77
		mov	byte_255B3, 1
		mov	word_266FC, 30h	; '0'
		mov	byte_26704, 2
		jmp	short loc_14E8E	; default
; ---------------------------------------------------------------------------

loc_14E77:				; CODE XREF: sub_14CFD+166j
		cmp	byte_255B3, 2
		jnz	short loc_14E8E	; default
		mov	byte_255B3, 1
		mov	word_266FC, 0FFD0h
		mov	byte_26704, 1

loc_14E8E:				; CODE XREF: sub_14CFD+A2j
					; sub_14CFD+ACj ...
		push	large 1800180h	; default
		push	0Ah
		call	sub_1E618
		mov	si, ax
		or	si, si
		jz	loc_14F57
		sub	word_26702, si
		cmp	word_26702, 0
		jle	short loc_14EB5
		mov	byte_26708, 1
		push	4
		jmp	short loc_14F0F
; ---------------------------------------------------------------------------

loc_14EB5:				; CODE XREF: sub_14CFD+1ADj
		mov	byte_26708, 1
		mov	byte_2CFF9, 1
		mov	al, byte_255B4
		mov	ah, 0
		mov	dx, 12h
		sub	dx, ax
		push	dx
		call	sub_19F6E
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	4
		call	sub_1DA38
		mov	word_255C2, 0Ch

loc_14EE0:				; CODE XREF: sub_14CFD+120j
		mov	byte_26705, 2
		mov	byte_26704, 0
		mov	word_26706, 0
		mov	word_266FC, 0
		mov	word_266FE, 0FFF0h
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	large 800030h
		call	sub_13E8C
		push	0Ch

loc_14F0F:				; CODE XREF: sub_14CFD+1B6j
		call	sub_138B2
		jmp	short loc_14F57
; ---------------------------------------------------------------------------

loc_14F16:				; CODE XREF: sub_14CFD+65j
		cmp	byte_26705, 2
		jnz	short loc_14F52
		push	53B4h
		call	sub_13D32
		inc	word_26706
		cmp	word ptr dword_266F4+2,	0
		jg	short loc_14F38
		inc	byte_26705
		mov	word_26702, 0

loc_14F38:				; CODE XREF: sub_14CFD+22Fj
		cmp	byte_266CF, 0
		jnz	short loc_14F57
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	large 800010h
		call	sub_13E8C
		jmp	short loc_14F57
; ---------------------------------------------------------------------------

loc_14F52:				; CODE XREF: sub_14CFD+21Ej
		nop
		push	cs
		call	near ptr sub_19EBC

loc_14F57:				; CODE XREF: sub_14CFD+34j
					; sub_14CFD+5Dj ...
		push	word_26702
		push	2EEh
		call	sub_19F16
		pop	si
		leave
		retf
sub_14CFD	endp

; ---------------------------------------------------------------------------
word_14F64	dw	0,     1,     2,     3 ; DATA XREF: sub_14CFD+92o
		dw   0FFh		; value	table for switch statement
		dw offset loc_14DA6	; jump table for switch	statement
		dw offset loc_14DAC
		dw offset loc_14DB2
		dw offset loc_14DB8
		dw offset loc_14DBE

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_14F78	proc near		; CODE XREF: sub_152B4:loc_1535Cp
		push	bp
		mov	bp, sp
		cmp	word_26706, 18h
		jg	short loc_14F9B
		mov	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		mov	byte_26704, al
		cmp	word_26706, 18h
		jnz	loc_15025
		push	6
		jmp	short loc_14FF9
; ---------------------------------------------------------------------------

loc_14F9B:				; CODE XREF: sub_14F78+8j
		cmp	word_26706, 80h	; '€'
		jge	short loc_15000
		test	byte ptr word_26706, 3
		jnz	short loc_15025
		mov	byte_266EC, 2Eh	; '.'
		mov	byte_266EF, 2
		mov	byte_266F0, 6
		push	18h
		call	sub_13D76
		add	al, 20h	; ' '
		mov	byte_266EE, al
		push	60h ; '`'
		call	sub_13D76
		sub	al, 30h	; '0'
		mov	byte_266ED, al
		call	word_2D004
		call	word_2D000
		mov	byte_266E2, 2
		mov	byte_266E3, 3Ah	; ':'
		push	18h
		call	sub_13D76
		add	al, 20h	; ' '
		mov	byte_266EE, al
		push	60h ; '`'
		call	sub_13D76
		sub	al, 30h	; '0'
		mov	byte_266ED, al
		call	word_2D000
		push	3

loc_14FF9:				; CODE XREF: sub_14F78+21j
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_15000:				; CODE XREF: sub_14F78+29j
		cmp	word_26706, 98h	; '˜'
		jge	short loc_1501A
		mov	ax, 9Fh	; 'Ÿ'
		sub	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		mov	byte_26704, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1501A:				; CODE XREF: sub_14F78+8Ej
		mov	word_26706, 0
		mov	byte_255C6, 0FFh

loc_15025:				; CODE XREF: sub_14F78+1Bj
					; sub_14F78+30j
		pop	bp
		retn
sub_14F78	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15027	proc near		; CODE XREF: sub_152B4:loc_15366p

var_1		= byte ptr -1

		enter	2, 0
		cmp	word_26706, 18h
		jg	short loc_15068
		mov	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		mov	byte_26704, al
		cmp	word_26706, 18h
		jnz	locret_1511B
		push	6
		call	sub_138B2
		cmp	word ptr dword_266F4, 0C00h
		jge	short loc_1505D
		mov	byte_266ED, 36h	; '6'
		jmp	short loc_15062
; ---------------------------------------------------------------------------

loc_1505D:				; CODE XREF: sub_15027+2Dj
		mov	byte_266ED, 56h	; 'V'

loc_15062:				; CODE XREF: sub_15027+34j
		inc	byte_22B9E
		leave
		retn
; ---------------------------------------------------------------------------

loc_15068:				; CODE XREF: sub_15027+9j
		cmp	word_26706, 88h	; 'ˆ'
		jg	loc_150F6
		mov	ax, word_26706
		add	ax, 0FFE7h
		test	al, 0Fh
		jnz	locret_1511B
		mov	byte_266EC, 2Fh	; '/'
		test	byte_22B9E, 1
		jz	short loc_150A1
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266F4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266F4
		push	ax
		call	sub_1DA8
		jmp	short loc_150A6
; ---------------------------------------------------------------------------

loc_150A1:				; CODE XREF: sub_15027+61j
		mov	al, byte_266ED
		add	al, 0F8h ; 'ø'

loc_150A6:				; CODE XREF: sub_15027+78j
		mov	byte_266ED, al
		mov	al, byte_266ED
		mov	[bp+var_1], al
		push	3
		call	sub_138B2
		mov	byte_266E2, 2
		mov	byte_266E3, 3Ah	; ':'
		call	word_2D004
		mov	byte_266EE, 10h
		mov	byte_266EF, 0Ch
		mov	byte_266F0, 7
		call	sub_1CFA2
		cmp	word ptr dword_266F4, 0C00h
		jle	short loc_150E2
		mov	al, 0A0h ; ' '
		jmp	short loc_150E4
; ---------------------------------------------------------------------------

loc_150E2:				; CODE XREF: sub_15027+B5j
		mov	al, 60h	; '`'

loc_150E4:				; CODE XREF: sub_15027+B9j
		sub	al, byte_266ED
		mov	byte_266ED, al
		call	sub_1CFA2
		mov	al, [bp+var_1]
		mov	byte_266ED, al
		leave
		retn
; ---------------------------------------------------------------------------

loc_150F6:				; CODE XREF: sub_15027+47j
		cmp	word_26706, 0A0h ; ' '
		jge	short loc_15110
		mov	ax, 0A5h ; '¥'
		sub	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		mov	byte_26704, al
		leave
		retn
; ---------------------------------------------------------------------------

loc_15110:				; CODE XREF: sub_15027+D5j
		mov	word_26706, 0
		mov	byte_255C6, 0FFh

locret_1511B:				; CODE XREF: sub_15027+1Cj
					; sub_15027+53j
		leave
		retn
sub_15027	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1511D	proc near		; CODE XREF: sub_152B4:loc_15361p
		push	bp
		mov	bp, sp
		push	si
		cmp	word_26706, 18h
		jg	short loc_15142
		mov	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		mov	byte_26704, al
		cmp	word_26706, 18h
		jnz	loc_151FF
		push	6
		jmp	loc_151D3
; ---------------------------------------------------------------------------

loc_15142:				; CODE XREF: sub_1511D+9j
		cmp	word_26706, 78h	; 'x'
		jg	loc_151DA
		test	byte ptr word_26706, 7
		jnz	short loc_1517E
		mov	byte_266EC, 2Eh	; '.'
		push	3
		call	sub_13D60
		add	al, al
		inc	al
		mov	byte_266EF, al
		push	7
		call	sub_13D60
		add	al, 0Ah
		mov	byte_266F0, al
		mov	byte_266EE, 32h	; '2'
		mov	byte_266ED, 0
		call	word_2D004
		call	sub_1CFA2

loc_1517E:				; CODE XREF: sub_1511D+33j
		mov	ax, word_26706
		add	ax, 0FFE7h
		and	ax, 1Fh
		mov	si, ax
		or	si, si
		jnz	short loc_151A5
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266F4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266F4
		push	ax
		call	sub_1DA8
		mov	byte_26709, al

loc_151A5:				; CODE XREF: sub_1511D+6Ej
		test	si, 3
		jnz	short loc_151FF
		mov	byte_266E2, 2
		mov	byte_266EC, 0
		mov	byte_266E3, 5Ch	; '\'
		mov	ax, si
		imul	ax, 3
		add	al, 28h	; '('
		mov	byte_266EE, al
		mov	al, byte_26709
		mov	byte_266ED, al
		call	word_2D004
		call	sub_1CFA2
		push	3

loc_151D3:				; CODE XREF: sub_1511D+22j
		call	sub_138B2
		jmp	short loc_151FF
; ---------------------------------------------------------------------------

loc_151DA:				; CODE XREF: sub_1511D+2Aj
		cmp	word_26706, 90h	; ''
		jge	short loc_151F4
		mov	ax, 97h	; '—'
		sub	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		mov	byte_26704, al
		jmp	short loc_151FF
; ---------------------------------------------------------------------------

loc_151F4:				; CODE XREF: sub_1511D+C3j
		mov	word_26706, 0
		mov	byte_255C6, 0FFh

loc_151FF:				; CODE XREF: sub_1511D+1Cj
					; sub_1511D+8Cj ...
		pop	si
		pop	bp
		retn
sub_1511D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15202	proc near		; CODE XREF: sub_152B4:loc_1536Bp
		push	bp
		mov	bp, sp
		cmp	word_26706, 18h
		jg	short loc_1522F
		mov	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		mov	byte_26704, al
		cmp	word_26706, 18h
		jnz	loc_152B2
		push	6
		call	sub_138B2
		mov	byte_266ED, 0E0h ; 'à'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1522F:				; CODE XREF: sub_15202+8j
		cmp	word_26706, 80h	; '€'
		jge	short loc_1528D
		test	byte ptr word_26706, 2
		jnz	short loc_152B2
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 3
		mov	byte_266F0, 6
		mov	byte_266EE, 3Ch	; '<'
		cmp	word ptr dword_266F4, 0C00h
		jge	short loc_15263
		mov	al, 80h	; '€'
		sub	al, byte_266ED
		mov	byte_266ED, al

loc_15263:				; CODE XREF: sub_15202+56j
		call	word_2D004
		call	word_2D000
		cmp	word ptr dword_266F4, 0C00h
		jge	short loc_1527C
		mov	al, 80h	; '€'
		sub	al, byte_266ED
		mov	byte_266ED, al

loc_1527C:				; CODE XREF: sub_15202+6Fj
		push	3
		call	sub_138B2
		mov	al, byte_266ED
		add	al, 6
		mov	byte_266ED, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1528D:				; CODE XREF: sub_15202+33j
		cmp	word_26706, 98h	; '˜'
		jge	short loc_152A7
		mov	ax, 9Fh	; 'Ÿ'
		sub	ax, word_26706
		mov	bx, 8
		cwd
		idiv	bx
		mov	byte_26704, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_152A7:				; CODE XREF: sub_15202+91j
		mov	word_26706, 0
		mov	byte_255C6, 0FFh

loc_152B2:				; CODE XREF: sub_15202+1Bj
					; sub_15202+3Aj
		pop	bp
		retn
sub_15202	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_152B4	proc far

var_2		= word ptr -2

		enter	2, 0
		push	si
		mov	ax, word ptr dword_266F4
		mov	word_25982, ax
		mov	ax, word ptr dword_266F4+2
		mov	word_25984, ax
		cmp	byte_26705, 0
		jnz	short loc_15314
		push	53B4h
		call	sub_13D32
		inc	word_26706
		push	large 1800180h
		push	0Ah
		call	sub_1E618
		mov	si, ax
		cmp	word_26706, 30h	; '0'
		jl	loc_1552D
		inc	byte_26705
		mov	word_26706, 0
		mov	word_266FC, 0
		mov	word_266FE, 0
		mov	byte_255C8, 0
		mov	byte_255C6, 0
		mov	byte_255C7, 0
		jmp	loc_1552D
; ---------------------------------------------------------------------------

loc_15314:				; CODE XREF: sub_152B4+16j
		cmp	byte_26705, 1
		jnz	loc_15490
		push	53B4h
		call	sub_13D32
		inc	word_26706
		mov	byte_266E2, 1
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FF00h
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_255C6
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	cx, 5		; switch 5 cases
		mov	bx, offset word_1553B

loc_15349:				; CODE XREF: sub_152B4+A0j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_15358
		add	bx, 2
		loop	loc_15349
		jmp	short loc_153D2	; default
; ---------------------------------------------------------------------------

loc_15358:				; CODE XREF: sub_152B4+9Bj
		jmp	word ptr cs:[bx+0Ah] ; switch jump

loc_1535C:				; DATA XREF: seg003:1AB5o
		call	sub_14F78	; jumptable 00015358 case 0
		jmp	short loc_153D2	; default
; ---------------------------------------------------------------------------

loc_15361:				; CODE XREF: sub_152B4:loc_15358j
					; DATA XREF: seg003:1AB5o
		call	sub_1511D	; jumptable 00015358 case 1
		jmp	short loc_153D2	; default
; ---------------------------------------------------------------------------

loc_15366:				; CODE XREF: sub_152B4:loc_15358j
					; DATA XREF: seg003:1AB5o
		call	sub_15027	; jumptable 00015358 case 2
		jmp	short loc_153D2	; default
; ---------------------------------------------------------------------------

loc_1536B:				; CODE XREF: sub_152B4:loc_15358j
					; DATA XREF: seg003:1AB5o
		call	sub_15202	; jumptable 00015358 case 3
		jmp	short loc_153D2	; default
; ---------------------------------------------------------------------------

loc_15370:				; CODE XREF: sub_152B4:loc_15358j
					; DATA XREF: seg003:1AB5o
		cmp	word_26706, 1	; jumptable 00015358 case 255
		jnz	short loc_1538C
		cmp	word ptr dword_266F4, 0B40h
		jl	short loc_15384
		mov	ax, 0FFC0h
		jmp	short loc_15387
; ---------------------------------------------------------------------------

loc_15384:				; CODE XREF: sub_152B4+C9j
		mov	ax, 40h	; '@'

loc_15387:				; CODE XREF: sub_152B4+CEj
		mov	word_266FC, ax
		jmp	short loc_153D2	; default
; ---------------------------------------------------------------------------

loc_1538C:				; CODE XREF: sub_152B4+C1j
		cmp	byte_255C7, 8
		jnb	short loc_153BD
		cmp	word ptr dword_266F4, 300h
		jle	short loc_153A3

loc_1539B:				; CODE XREF: sub_1EA4B:loc_1EA6Bj
		cmp	word ptr dword_266F4, 1500h
		jl	short loc_153D2	; default

loc_153A3:				; CODE XREF: sub_152B4+E5j
		mov	word_266FC, 0
		mov	word_26706, 0
		inc	byte_255C7
		mov	al, byte_255C7
		and	al, 3
		mov	byte_255C6, al
		jmp	short loc_153D2	; default
; ---------------------------------------------------------------------------

loc_153BD:				; CODE XREF: sub_152B4+DDj
		cmp	word ptr dword_266F4, 0FE00h
		jle	short loc_153CD
		cmp	word ptr dword_266F4, 1A00h
		jl	short loc_153D2	; default

loc_153CD:				; CODE XREF: sub_152B4+10Fj
		mov	byte_26705, 3

loc_153D2:				; CODE XREF: sub_152B4+A2j
					; sub_152B4+ABj ...
		cmp	word ptr dword_266F4+2,	1700h ;	default
		jge	short loc_153E9
		cmp	word ptr dword_266F4, 0
		jle	short loc_153E9
		cmp	word ptr dword_266F4, 1800h
		jl	short loc_153EE

loc_153E9:				; CODE XREF: sub_152B4+124j
					; sub_152B4+12Bj
		mov	byte_26705, 0FFh

loc_153EE:				; CODE XREF: sub_152B4+133j
		push	large 1800180h
		push	4
		call	sub_1E618
		mov	si, ax
		or	si, si
		jz	loc_1552D
		sub	word_26702, si
		cmp	word_26702, 0
		jle	short loc_15414
		mov	byte_26708, 1
		jmp	loc_1552D
; ---------------------------------------------------------------------------

loc_15414:				; CODE XREF: sub_152B4+156j
		mov	byte_26708, 1
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FF00h
		push	ax
		call	sub_13D10
		mov	si, ax
		mov	byte_2CFF9, 1
		mov	al, byte_255C7
		mov	ah, 0
		mov	dx, 1Eh
		sub	dx, ax
		push	dx
		call	sub_19F6E
		mov	word_255C2, 0Ch
		mov	byte_26705, 0FEh ; 'þ'
		mov	byte_26704, 4
		mov	word_26706, 0
		mov	word_266FC, 0
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	large 600030h
		call	sub_13E8C
		push	0Ch
		call	sub_138B2
		cmp	word_26700, 0AF0h
		jnz	short loc_15480
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	4
		jmp	short loc_1548A
; ---------------------------------------------------------------------------

loc_15480:				; CODE XREF: sub_152B4+1BEj
		push	word ptr dword_266F4
		push	word ptr dword_266F4+2
		push	5

loc_1548A:				; CODE XREF: sub_152B4+1CAj
		call	sub_1DA38
		jmp	loc_1552D
; ---------------------------------------------------------------------------

loc_15490:				; CODE XREF: sub_152B4+65j
		cmp	byte_26705, 0FEh ; 'þ'
		jnz	short loc_154D1
		mov	word_266FC, 0
		mov	word_266FE, 0
		push	53B4h
		call	sub_13D32
		inc	word_26706
		mov	ax, word_26706
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1552D
		inc	byte_26704
		cmp	byte_26704, 0Ch
		jb	short loc_1552D
		inc	byte_26705
		mov	word_26702, 0
		jmp	short loc_1552D
; ---------------------------------------------------------------------------

loc_154D1:				; CODE XREF: sub_152B4+1E1j
		nop
		push	cs
		call	near ptr sub_19EBC
		cmp	word_26700, 0AF0h
		jnz	short loc_1552D
		mov	word_26700, 15E0h
		mov	word ptr dword_259FC+2,	seg seg003
		mov	word ptr dword_259FC, 1824h
		mov	word_25A00, 2316h
		mov	word ptr dword_266F4, 0F00h
		mov	word ptr dword_266F4+2,	0FE00h
		mov	word ptr dword_266F8, 0F00h
		mov	word ptr dword_266F8+2,	0FE00h
		mov	word_266FC, 0FFC0h
		mov	word_266FE, 20h	; ' '
		mov	word_26702, 4B0h
		mov	byte_26704, 0
		mov	word_26706, 0
		jmp	short loc_15537
; ---------------------------------------------------------------------------

loc_1552D:				; CODE XREF: sub_152B4+34j
					; sub_152B4+5Dj ...
		push	word_26702
		push	4B0h
		call	sub_19F16

loc_15537:				; CODE XREF: sub_152B4+277j
		pop	si
		leave
		retf
sub_152B4	endp

; ---------------------------------------------------------------------------
		db 0
word_1553B	dw	0,     1,     2,     3 ; DATA XREF: sub_152B4+92o
		dw   0FFh		; value	table for switch statement
		dw offset loc_1535C	; jump table for switch	statement
		dw offset loc_15361
		dw offset loc_15366
		dw offset loc_1536B
		dw offset loc_15370

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1554F	proc near		; CODE XREF: sub_155DD:loc_15620p
					; sub_155DD:loc_15640p	...

var_2		= word ptr -2

		enter	2, 0
		push	si
		mov	ax, word_2598A
		mov	[bp+var_2], ax
		add	ax, 2
		push	ax
		call	sub_13D32
		mov	si, [bp+var_2]
		cmp	byte ptr [si+20h], 0
		jz	short loc_15572
		add	ax, 100h
		cmp	ax, 1A00h
		jnb	short loc_15586

loc_15572:				; CODE XREF: sub_1554F+19j
		cmp	byte ptr [si+21h], 0
		jz	short loc_15582
		add	dx, 100h
		cmp	dx, 1900h
		jnb	short loc_15586

loc_15582:				; CODE XREF: sub_1554F+27j
		mov	al, 0
		jmp	short loc_1558F
; ---------------------------------------------------------------------------

loc_15586:				; CODE XREF: sub_1554F+21j
					; sub_1554F+31j
		inc	word_22E9E
		mov	byte ptr [si], 2
		mov	al, 1

loc_1558F:				; CODE XREF: sub_1554F+35j
		pop	si
		leave
		retn
sub_1554F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15592	proc near		; CODE XREF: sub_155DD+40p
					; sub_155DD+60p ...
		push	bp
		mov	bp, sp
		push	si
		mov	si, word_2598A
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+1Eh]
		push	word ptr [si+1Ch]
		call	sub_13DF2
		pop	si
		pop	bp
		retn
sub_15592	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_155AA	proc near		; CODE XREF: sub_155DD+1EAp
		push	bp
		mov	bp, sp
		push	si
		mov	si, word_2598A
		push	es
		mov	ax, word ptr dword_2598E+2
		sub	ax, [si+4]
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, [si+2]
		push	ax
		call	sub_1DA8
		add	al, [si+1Eh]
		mov	[si+1Eh], al
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+1Eh]
		push	word ptr [si+1Ch]
		call	sub_13DF2
		pop	es
		assume es:nothing
		pop	si
		pop	bp
		retn
sub_155AA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_155DD	proc near		; CODE XREF: sub_17E59+43p

var_4		= word ptr -4
var_2		= byte ptr -2
var_1		= byte ptr -1

		enter	4, 0
		push	si
		push	di
		mov	si, word_2598A
		mov	es, word_21C58

loc_155EB:				; CODE XREF: sub_155DD+52Ej
					; sub_155DD+53Aj
		mov	di, [si+16h]
		add	di, [si+18h]

loc_155F1:				; CODE XREF: sub_155DD+569j
		mov	al, es:[di]
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 8Fh	; ''
		ja	loc_15B1A
		add	bx, bx
		jmp	cs:off_15B4D[bx]

loc_15607:				; DATA XREF: seg003:20BFo
		cmp	byte ptr [si+1Ah], 0
		jnz	short loc_15620
		mov	al, es:[di+2]
		mov	ah, 0
		mov	[si+1Ch], ax
		mov	al, es:[di+1]
		mov	[si+1Eh], al
		call	sub_15592

loc_15620:				; CODE XREF: sub_155DD+2Ej
		call	sub_1554F
		or	al, al
		jnz	loc_159A4
		mov	al, es:[di+3]
		mov	[bp+var_1], al
		mov	[bp+var_2], 4
		jmp	loc_15B1A
; ---------------------------------------------------------------------------

loc_15637:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20C1o
		cmp	byte ptr [si+1Ah], 0
		jnz	short loc_15640
		call	sub_15592

loc_15640:				; CODE XREF: sub_155DD+5Ej
		call	sub_1554F
		or	al, al
		jnz	loc_159A4
		jmp	loc_1573B
; ---------------------------------------------------------------------------

loc_1564C:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20C3o
		cmp	byte ptr [si+1Ah], 0
		jnz	short loc_1565E
		mov	al, es:[di+1]
		mov	ah, 0
		mov	[si+1Ch], ax
		call	sub_15592

loc_1565E:				; CODE XREF: sub_155DD+73j
		call	sub_1554F
		or	al, al
		jnz	loc_159A4
		mov	al, es:[di+2]
		mov	[bp+var_1], al
		mov	[bp+var_2], 3
		jmp	loc_15B1A
; ---------------------------------------------------------------------------

loc_15675:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20C5o ...
		cmp	byte ptr [si+1Ah], 0
		jnz	short loc_15692
		mov	al, es:[di+1]
		mov	[si+1Eh], al
		mov	al, es:[di+3]
		mov	[si+1Fh], al
		mov	al, es:[di+2]
		mov	ah, 0
		mov	[si+1Ch], ax

loc_15692:				; CODE XREF: sub_155DD+9Cj
		call	sub_15592
		cmp	byte ptr es:[di], 5
		jnz	short loc_156B8
		mov	al, es:[di+4]
		cbw
		add	[si+0Ah], ax
		mov	al, es:[di+5]
		cbw
		add	[si+0Ch], ax
		mov	al, es:[di+6]
		mov	[bp+var_1], al
		mov	[bp+var_2], 7
		jmp	short loc_156C3
; ---------------------------------------------------------------------------

loc_156B8:				; CODE XREF: sub_155DD+BCj
		mov	al, es:[di+4]
		mov	[bp+var_1], al
		mov	[bp+var_2], 5

loc_156C3:				; CODE XREF: sub_155DD+D9j
		call	sub_1554F
		or	al, al
		jnz	loc_159A4
		jmp	short loc_15708
; ---------------------------------------------------------------------------

loc_156CE:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20D7o ...
		call	sub_15592
		cmp	byte ptr es:[di], 0Eh
		jnz	short loc_156F4
		mov	al, es:[di+1]
		cbw
		add	[si+0Ah], ax
		mov	al, es:[di+2]
		cbw
		add	[si+0Ch], ax
		mov	al, es:[di+3]
		mov	[bp+var_1], al
		mov	[bp+var_2], 4
		jmp	short loc_156FF
; ---------------------------------------------------------------------------

loc_156F4:				; CODE XREF: sub_155DD+F8j
		mov	al, es:[di+1]
		mov	[bp+var_1], al
		mov	[bp+var_2], 2

loc_156FF:				; CODE XREF: sub_155DD+115j
		call	sub_1554F
		or	al, al
		jnz	loc_159A4

loc_15708:				; CODE XREF: sub_155DD+EFj
		mov	al, [si+1Fh]
		add	[si+1Eh], al
		jmp	loc_15B1A
; ---------------------------------------------------------------------------

loc_15711:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20C9o
		cmp	byte ptr [si+1Ah], 0
		jnz	short loc_1573B
		mov	eax, [si+2]
		mov	[si+6],	eax
		jmp	short loc_1573B
; ---------------------------------------------------------------------------

loc_15721:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20D3o
		cmp	byte ptr [si+1Ah], 0
		jnz	short loc_1572C
		mov	word ptr [si+0Ah], 0

loc_1572C:				; CODE XREF: sub_155DD+148j
		mov	ax, word_255BA
		mov	[si+0Ch], ax
		call	sub_1554F
		or	al, al
		jnz	loc_159A4

loc_1573B:				; CODE XREF: sub_155DD+6Cj
					; sub_155DD+138j ...
		mov	al, es:[di+1]
		mov	[bp+var_1], al
		mov	[bp+var_2], 2
		jmp	loc_15B1A
; ---------------------------------------------------------------------------

loc_15749:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20CBo ...
		cmp	byte ptr [si+1Ah], 0
		jnz	short loc_1575A
		mov	byte ptr [si+1Eh], 0
		mov	al, es:[di+2]
		mov	[si+1Fh], al

loc_1575A:				; CODE XREF: sub_155DD+170j
		movzx	eax, byte ptr es:[di+1]
		mov	dl, [si+1Eh]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+566h]
		imul	eax, edx
		sar	eax, 8
		mov	[si+0Ah], ax
		mov	al, es:[di+3]
		cbw
		mov	[si+0Ch], ax
		cmp	byte ptr es:[di], 8
		jnz	short loc_1579A
		mov	ax, [si+0Ah]
		mov	[bp+var_4], ax
		mov	ax, [si+0Ch]
		mov	[si+0Ah], ax
		mov	ax, [bp+var_4]
		mov	[si+0Ch], ax

loc_1579A:				; CODE XREF: sub_155DD+1A9j
		call	sub_1554F
		or	al, al
		jnz	loc_159A4
		mov	al, [si+1Fh]
		add	[si+1Eh], al
		mov	al, es:[di+4]
		mov	[bp+var_1], al
		mov	[bp+var_2], 5
		jmp	loc_15B1A
; ---------------------------------------------------------------------------

loc_157B7:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20CFo
		mov	al, es:[di+1]
		mov	[si+1Eh], al
		mov	al, es:[di+2]
		mov	ah, 0
		mov	[si+1Ch], ax
		call	sub_155AA
		jmp	loc_15A9D
; ---------------------------------------------------------------------------

loc_157CD:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20D1o
		mov	al, es:[di+1]
		add	[si+1Eh], al
		jmp	loc_15ACD
; ---------------------------------------------------------------------------

loc_157D7:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20D5o
		mov	al, es:[di+1]
		cbw
		add	[si+1Ch], ax
		jmp	loc_15ACD
; ---------------------------------------------------------------------------

loc_157E2:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20DFo
		call	sub_13D52
		mov	[si+1Eh], al
		jmp	loc_158BE
; ---------------------------------------------------------------------------

loc_157EB:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20FDo
		mov	al, [si+2Ch]
		mov	byte_266E2, al
		mov	al, [si+2Dh]
		mov	byte_266E3, al
		mov	ax, [si+2Eh]
		add	ax, [si+2]
		mov	word ptr dword_266E4, ax
		mov	ax, [si+30h]
		add	ax, [si+4]
		mov	word ptr dword_266E4+2,	ax
		mov	al, [si+36h]
		mov	byte_266EC, al
		mov	al, [si+37h]
		mov	byte_266ED, al
		mov	al, [si+38h]
		mov	byte_266EE, al
		mov	al, [si+39h]
		mov	byte_266EF, al
		mov	al, [si+3Ah]
		mov	byte_266F0, al
		push	es
		call	word_2D004
		call	word_2D000
		pop	es
		jmp	loc_158BE
; ---------------------------------------------------------------------------

loc_15834:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20FFo
		mov	byte ptr [si+29h], 0
		mov	al, es:[di+1]
		mov	[si+2Ch], al
		mov	ax, es:[di+2]
		mov	[si+2Eh], ax
		mov	ax, es:[di+4]
		mov	[si+30h], ax
		mov	al, es:[di+6]
		mov	[si+36h], al
		mov	al, es:[di+7]
		mov	[si+37h], al
		mov	al, es:[di+8]
		mov	[si+38h], al
		mov	al, es:[di+9]
		mov	[si+2Dh], al
		mov	al, es:[di+0Ah]
		mov	[si+39h], al
		mov	[bp+var_2], 0Bh
		jmp	loc_15B37
; ---------------------------------------------------------------------------

loc_15877:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2101o
		mov	al, es:[di+1]
		mov	[si+2Ch], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_15881:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2103o
		cmp	byte ptr [si+1Ah], 0
		jnz	short loc_1588F
		mov	eax, [si+2]
		mov	[si+6],	eax

loc_1588F:				; CODE XREF: sub_155DD+2A8j
		mov	ax, es:[di+1]
		mov	[si+2Eh], ax
		mov	ax, es:[di+3]
		mov	[si+30h], ax
		mov	[bp+var_2], 5
		jmp	loc_15B37
; ---------------------------------------------------------------------------

loc_158A4:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2105o
		mov	al, es:[di+1]
		mov	[si+37h], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_158AE:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2107o
		mov	al, es:[di+1]
		add	[si+37h], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_158B8:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2117o
		call	sub_13D52
		mov	[si+37h], al

loc_158BE:				; CODE XREF: sub_155DD+20Bj
					; sub_155DD+254j ...
		mov	[bp+var_2], 1
		jmp	loc_15B37
; ---------------------------------------------------------------------------

loc_158C5:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2111o
		mov	al, es:[di+1]
		mov	[si+2Dh], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_158CF:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:210Fo
		mov	al, es:[di+1]
		mov	[si+39h], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_158D9:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2109o
		mov	al, es:[di+1]
		mov	[si+38h], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_158E3:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:210Bo
		mov	al, es:[di+1]
		add	[si+38h], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_158ED:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:210Do
		mov	al, es:[di+1]
		mov	[si+36h], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_158F7:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2115o
		mov	al, es:[di+1]
		mov	ah, 0
		mov	[bp+var_4], ax
		cmp	byte_266D5, 10h
		jbe	short loc_1593A
		mov	al, byte_266D5
		mov	ah, 0
		add	ax, 0FFF0h
		imul	[bp+var_4]
		mov	[bp+var_4], ax
		mov	bx, 20h	; ' '
		mov	ax, [bp+var_4]
		cwd
		idiv	bx
		mov	[bp+var_4], ax
		mov	al, es:[di+1]
		mov	ah, 0
		sub	ax, [bp+var_4]
		mov	[bp+var_4], ax
		cmp	[bp+var_4], 10h
		jge	short loc_15977
		mov	[bp+var_4], 10h
		jmp	short loc_15977
; ---------------------------------------------------------------------------

loc_1593A:				; CODE XREF: sub_155DD+328j
		cmp	byte_266D5, 10h
		jnb	short loc_15977
		mov	al, byte_266D5
		mov	ah, 0
		push	ax
		mov	ax, 10h
		pop	dx
		sub	ax, dx
		imul	[bp+var_4]
		mov	[bp+var_4], ax
		mov	bx, 20h	; ' '
		mov	ax, [bp+var_4]
		cwd
		idiv	bx
		mov	[bp+var_4], ax
		mov	al, es:[di+1]
		mov	ah, 0
		add	ax, [bp+var_4]
		mov	[bp+var_4], ax
		cmp	[bp+var_4], 100h
		jl	short loc_15977
		mov	[bp+var_4], 0FFh

loc_15977:				; CODE XREF: sub_155DD+354j
					; sub_155DD+35Bj ...
		cmp	byte_25688, 0
		jnz	short loc_15983
		mov	[bp+var_4], 0FFh

loc_15983:				; CODE XREF: sub_155DD+39Fj
		mov	al, byte ptr [bp+var_4]
		mov	[si+3Fh], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_1598C:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2113o
		mov	byte ptr [si+29h], 1
		jmp	loc_158BE
; ---------------------------------------------------------------------------

loc_15993:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:2119o
		mov	byte ptr [si+29h], 0
		jmp	loc_158BE
; ---------------------------------------------------------------------------

loc_1599A:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:211Do
		mov	al, es:[di+1]
		mov	[si+3Ah], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_159A4:				; CODE XREF: sub_155DD+25j
					; sub_155DD+48j ...
		mov	byte ptr [si], 2
		mov	al, 1
		jmp	loc_15B49
; ---------------------------------------------------------------------------

loc_159AC:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20DDo
		mov	byte ptr [si], 1
		mov	al, es:[di+1]
		mov	[si+0Eh], al
		mov	ax, es:[di+2]
		mov	[si+10h], ax
		mov	ax, es:[di+4]
		mov	[si+14h], ax
		mov	byte ptr [si+28h], 1
		mov	byte ptr [si+2Ah], 1
		mov	[bp+var_2], 6
		jmp	loc_15B37
; ---------------------------------------------------------------------------

loc_159D3:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21C1o
		mov	byte ptr [si+20h], 1
		jmp	loc_158BE
; ---------------------------------------------------------------------------

loc_159DA:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21C5o
		mov	byte ptr [si+20h], 1

loc_159DE:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21C3o
		mov	byte ptr [si+21h], 1
		jmp	loc_158BE
; ---------------------------------------------------------------------------

loc_159E5:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21C7o
		mov	al, es:[di+1]
		mov	[si+25h], al
		mov	al, es:[di+2]
		mov	[si+26h], al
		jmp	loc_15A9D
; ---------------------------------------------------------------------------

loc_159F6:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21C9o
		mov	al, es:[di+1]
		mov	ah, 0
		push	ax
		call	sub_138B2
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_15A05:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21CBo
		mov	al, es:[di+1]
		mov	[si+0Eh], al
		jmp	loc_15AE4
; ---------------------------------------------------------------------------

loc_15A0F:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21CDo
		mov	byte ptr [si+28h], 0
		mov	[bp+var_2], 1
		mov	byte ptr [si+29h], 0
		jmp	loc_15B37
; ---------------------------------------------------------------------------

loc_15A1E:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21CFo
		mov	byte ptr [si+28h], 1
		mov	[bp+var_2], 1
		cmp	byte_25688, 3
		jnz	short loc_15A32
		mov	ax, 1
		jmp	short loc_15A34
; ---------------------------------------------------------------------------

loc_15A32:				; CODE XREF: sub_155DD+44Ej
		xor	ax, ax

loc_15A34:				; CODE XREF: sub_155DD+453j
		mov	[si+29h], al
		jmp	loc_15B37
; ---------------------------------------------------------------------------

loc_15A3A:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21D5o
		mov	byte ptr [si+2Ah], 0
		jmp	loc_158BE
; ---------------------------------------------------------------------------

loc_15A41:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21D7o
		mov	byte ptr [si+2Ah], 1
		jmp	loc_158BE
; ---------------------------------------------------------------------------

loc_15A48:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21D1o
		mov	eax, [si+2]
		mov	[si+6],	eax
		mov	ax, es:[di+1]
		mov	[si+2],	ax
		mov	ax, es:[di+3]
		mov	[si+4],	ax
		jmp	short loc_15A76
; ---------------------------------------------------------------------------

loc_15A60:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21D3o
		mov	eax, [si+2]
		mov	[si+6],	eax
		mov	ax, es:[di+1]
		add	[si+2],	ax
		mov	ax, es:[di+3]
		add	[si+4],	ax

loc_15A76:				; CODE XREF: sub_155DD+481j
		mov	[bp+var_2], 5
		mov	[bp+var_1], 0
		jmp	loc_15B1A
; ---------------------------------------------------------------------------

loc_15A81:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21D9o
		mov	al, es:[di+1]
		add	[si+0Eh], al
		jmp	short loc_15AE4
; ---------------------------------------------------------------------------

loc_15A8A:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20E1o
		mov	al, es:[di+1]
		mov	[si+1Eh], al
		mov	al, es:[di+2]

loc_15A95:				; CODE XREF: sub_1C2E5:loc_1C46Fj
					; DATA XREF: sub_C696+1Ao
		mov	ah, 0		; jumptable 0001C46F case 60
		mov	[si+1Ch], ax

loc_15A9A:				; CODE XREF: sub_155DD+4DBj
					; sub_155DD+4E5j
		call	sub_15592

loc_15A9D:				; CODE XREF: sub_155DD+1EDj
					; sub_155DD+416j ...
		mov	[bp+var_2], 3
		jmp	loc_15B37
; ---------------------------------------------------------------------------

loc_15AA4:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20E3o
		mov	al, es:[di+1]
		mov	[si+1Eh], al
		mov	al, es:[di+2]
		mov	ah, 0
		mov	[si+1Ch], ax
		cmp	byte ptr [si+2Bh], 0
		jnz	short loc_15A9A
		mov	al, 80h	; '€'
		sub	al, [si+1Eh]
		mov	[si+1Eh], al
		jmp	short loc_15A9A
; ---------------------------------------------------------------------------

loc_15AC4:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:20E5o
		mov	al, es:[di+1]
		mov	ah, 0
		mov	[si+1Ch], ax

loc_15ACD:				; CODE XREF: sub_155DD+1F7j
					; sub_155DD+202j
		call	sub_15592
		jmp	short loc_15AE4
; ---------------------------------------------------------------------------

loc_15AD2:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21DBo
		push	word ptr [si+2]
		push	word ptr [si+4]
		mov	al, es:[di+1]
		mov	ah, 0
		push	ax
		call	sub_B682

loc_15AE4:				; CODE XREF: sub_155DD+2A1j
					; sub_155DD+2CEj ...
		mov	[bp+var_2], 2
		jmp	short loc_15B37
; ---------------------------------------------------------------------------

loc_15AEA:				; CODE XREF: sub_155DD+25j
					; DATA XREF: seg003:21BDo ...
		mov	al, [si+1Bh]
		cmp	al, es:[di+2]
		jb	short loc_15AF9
		mov	byte ptr [si+1Bh], 0
		jmp	short loc_15A9D
; ---------------------------------------------------------------------------

loc_15AF9:				; CODE XREF: sub_155DD+514j
		inc	byte ptr [si+1Bh]
		cmp	byte ptr es:[di], 80h ;	'€'
		jnz	short loc_15B0E
		mov	al, es:[di+1]
		mov	ah, 0
		mov	[si+18h], ax
		jmp	loc_155EB
; ---------------------------------------------------------------------------

loc_15B0E:				; CODE XREF: sub_155DD+523j
		mov	al, es:[di+1]
		mov	ah, 0
		sub	[si+18h], ax
		jmp	loc_155EB
; ---------------------------------------------------------------------------

loc_15B1A:				; CODE XREF: sub_155DD+1Fj
					; sub_155DD+25j ...
		mov	al, [si+1Ah]
		cmp	al, [bp+var_1]
		jb	short loc_15B30
		mov	byte ptr [si+1Ah], 0
		mov	al, [bp+var_2]
		mov	ah, 0
		add	[si+18h], ax
		jmp	short loc_15B33
; ---------------------------------------------------------------------------

loc_15B30:				; CODE XREF: sub_155DD+543j
		inc	byte ptr [si+1Ah]

loc_15B33:				; CODE XREF: sub_155DD+551j
		mov	al, 0
		jmp	short loc_15B49
; ---------------------------------------------------------------------------

loc_15B37:				; CODE XREF: sub_155DD+297j
					; sub_155DD+2C4j ...
		mov	al, [bp+var_2]
		mov	ah, 0
		add	[si+18h], ax
		mov	al, [bp+var_2]
		mov	ah, 0
		add	di, ax
		jmp	loc_155F1
; ---------------------------------------------------------------------------

loc_15B49:				; CODE XREF: sub_155DD+3CCj
					; sub_155DD+558j
		pop	di
		pop	si
		leave
		retn
sub_155DD	endp

; ---------------------------------------------------------------------------
off_15B4D	dw offset loc_159A4	; DATA XREF: sub_155DD+25r
		dw offset loc_15607
		dw offset loc_15637
		dw offset loc_1564C
		dw offset loc_15675
		dw offset loc_15675
		dw offset loc_15711
		dw offset loc_15749
		dw offset loc_15749
		dw offset loc_157B7
		dw offset loc_157CD
		dw offset loc_15721
		dw offset loc_157D7
		dw offset loc_156CE
		dw offset loc_156CE
		dw offset loc_15B1A
		dw offset loc_159AC
		dw offset loc_157E2
		dw offset loc_15A8A
		dw offset loc_15AA4
		dw offset loc_15AC4
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_157EB
		dw offset loc_15834
		dw offset loc_15877
		dw offset loc_15881
		dw offset loc_158A4
		dw offset loc_158AE
		dw offset loc_158D9
		dw offset loc_158E3
		dw offset loc_158ED
		dw offset loc_158CF
		dw offset loc_158C5
		dw offset loc_1598C
		dw offset loc_158F7
		dw offset loc_158B8
		dw offset loc_15993
		dw offset loc_15B1A
		dw offset loc_1599A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15B1A
		dw offset loc_15AEA
		dw offset loc_15AEA
		dw offset loc_159D3
		dw offset loc_159DE
		dw offset loc_159DA
		dw offset loc_159E5
		dw offset loc_159F6
		dw offset loc_15A05
		dw offset loc_15A0F
		dw offset loc_15A1E
		dw offset loc_15A48
		dw offset loc_15A60
		dw offset loc_15A3A
		dw offset loc_15A41
		dw offset loc_15A81
		dw offset loc_15AD2

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15C6D	proc far		; CODE XREF: sub_1DF61+3Dp
		push	bp
		mov	bp, sp
		mov	byte_255D8, 0
		mov	byte_255E8, 0
		pop	bp
		retf
sub_15C6D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15C7C	proc near		; CODE XREF: sub_16610+140p
					; sub_16610+1ADp ...

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, 4298h
		cmp	byte ptr [si], 0
		jz	short loc_15C8B
		add	si, 10h

loc_15C8B:				; CODE XREF: sub_15C7C+Aj
		mov	byte ptr [si], 1
		mov	byte ptr [si+1], 0
		mov	ax, word ptr dword_2670A
		mov	[si+2],	ax
		mov	ax, word ptr dword_2670A+2
		mov	[si+4],	ax
		mov	word ptr [si+6], 8
		mov	word ptr [si+8], 8
		mov	word ptr [si+0Ah], 0B0h	; '°'
		mov	word ptr [si+0Ch], 0B0h	; '°'
		mov	byte ptr [si+0Fh], 0
		mov	bx, [bp+arg_0]
		dec	bx
		cmp	bx, 3
		ja	short loc_15CE8
		add	bx, bx
		jmp	cs:off_15CF4[bx]

loc_15CC6:				; DATA XREF: seg003:off_15CF4o
		mov	byte ptr [si+0Fh], 20h ; ' '
		jmp	short loc_15CE8
; ---------------------------------------------------------------------------

loc_15CCC:				; CODE XREF: sub_15C7C+45j
					; DATA XREF: seg003:2266o
		mov	byte ptr [si+0Fh], 0E0h	; 'à'
		jmp	short loc_15CE8
; ---------------------------------------------------------------------------

loc_15CD2:				; CODE XREF: sub_15C7C+45j
					; DATA XREF: seg003:2268o
		mov	word ptr [si+0Ah], 0D0h	; 'Ð'
		mov	word ptr [si+0Ch], 70h ; 'p'
		jmp	short loc_15CE8
; ---------------------------------------------------------------------------

loc_15CDE:				; CODE XREF: sub_15C7C+45j
					; DATA XREF: seg003:226Ao
		mov	word ptr [si+0Ah], 70h ; 'p'
		mov	word ptr [si+0Ch], 0D0h	; 'Ð'

loc_15CE8:				; CODE XREF: sub_15C7C+41j
					; sub_15C7C+4Ej ...
		push	0Fh
		call	sub_138B2
		pop	si
		pop	bp
		retn	2
sub_15C7C	endp

; ---------------------------------------------------------------------------
off_15CF4	dw offset loc_15CC6	; DATA XREF: sub_15C7C+45r
		dw offset loc_15CCC
		dw offset loc_15CD2
		dw offset loc_15CDE

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15CFC	proc near		; CODE XREF: sub_16610+35Cp
					; sub_179F4+269p ...

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, 42B8h
		mov	byte ptr [si], 1
		mov	byte ptr [si+1], 0
		mov	ax, word ptr dword_2670A
		mov	[si+2],	ax
		mov	ax, word ptr dword_2670A+2
		mov	[si+4],	ax
		mov	word ptr [si+6], 8
		mov	word ptr [si+8], 8
		mov	word ptr [si+0Ah], 0B0h	; '°'
		mov	word ptr [si+0Ch], 0B0h	; '°'
		mov	byte ptr [si+0Fh], 0
		mov	bx, [bp+arg_0]
		dec	bx
		cmp	bx, 3
		ja	short loc_15D60
		add	bx, bx
		jmp	cs:off_15D6C[bx]

loc_15D3E:				; DATA XREF: seg003:off_15D6Co
		mov	byte ptr [si+0Fh], 20h ; ' '
		jmp	short loc_15D60
; ---------------------------------------------------------------------------

loc_15D44:				; CODE XREF: sub_15CFC+3Dj
					; DATA XREF: seg003:22DEo
		mov	byte ptr [si+0Fh], 0E0h	; 'à'
		jmp	short loc_15D60
; ---------------------------------------------------------------------------

loc_15D4A:				; CODE XREF: sub_15CFC+3Dj
					; DATA XREF: seg003:22E0o
		mov	word ptr [si+0Ah], 0D0h	; 'Ð'
		mov	word ptr [si+0Ch], 70h ; 'p'
		jmp	short loc_15D60
; ---------------------------------------------------------------------------

loc_15D56:				; CODE XREF: sub_15CFC+3Dj
					; DATA XREF: seg003:22E2o
		mov	word ptr [si+0Ah], 70h ; 'p'
		mov	word ptr [si+0Ch], 0D0h	; 'Ð'

loc_15D60:				; CODE XREF: sub_15CFC+39j
					; sub_15CFC+46j ...
		push	0Fh
		call	sub_138B2
		pop	si
		pop	bp
		retn	2
sub_15CFC	endp

; ---------------------------------------------------------------------------
off_15D6C	dw offset loc_15D3E	; DATA XREF: sub_15CFC+3Dr
		dw offset loc_15D44
		dw offset loc_15D4A
		dw offset loc_15D56

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15D74	proc far		; CODE XREF: sub_B1D0+B6P
		push	bp
		mov	bp, sp
		push	si
		mov	si, 42F0h
		xor	ax, ax
		jmp	short loc_15D86
; ---------------------------------------------------------------------------

loc_15D7F:				; CODE XREF: sub_15D74+15j
		mov	byte ptr [si], 0
		inc	ax
		add	si, 18h

loc_15D86:				; CODE XREF: sub_15D74+9j
		cmp	ax, 2
		jl	short loc_15D7F
		mov	word_25622, 0
		mov	byte_25618, 1
		mov	word_2562C, 1
		mov	word_2562E, 1
		pop	si
		pop	bp
		retf
sub_15D74	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15DA5	proc near		; CODE XREF: sub_15DBD+12p

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, 0Ch
		push	ds
		pop	es
		assume es:dseg
		mov	si, 42D8h
		mov	di, [bp+arg_0]
		rep movsw
		pop	di
		pop	si
		pop	bp
		retn	2
sub_15DA5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15DBD	proc near		; CODE XREF: sub_16389+ABp
					; sub_1AE8F+102p ...
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 42F0h
		xor	di, di
		jmp	short loc_15DDF
; ---------------------------------------------------------------------------

loc_15DC9:				; CODE XREF: sub_15DBD+25j
		cmp	byte ptr [si], 0
		jnz	short loc_15DDB
		push	si
		call	sub_15DA5
		push	5
		call	sub_138B2
		jmp	short loc_15DE4
; ---------------------------------------------------------------------------

loc_15DDB:				; CODE XREF: sub_15DBD+Fj
		inc	di
		add	si, 18h

loc_15DDF:				; CODE XREF: sub_15DBD+Aj
		cmp	di, 2
		jl	short loc_15DC9

loc_15DE4:				; CODE XREF: sub_15DBD+1Cj
		pop	di
		pop	si
		pop	bp
		retn
sub_15DBD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15DE8	proc near		; CODE XREF: sub_16610+3B4p
					; sub_1CCB8-13C2p ...

var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
		mov	si, 42F0h
		mov	[bp+var_2], 0
		jmp	loc_15EC2
; ---------------------------------------------------------------------------

loc_15DFB:				; CODE XREF: sub_15DE8+DEj
		cmp	byte ptr [si], 0
		jz	loc_15EBC
		cmp	byte ptr [si], 1
		jnz	short loc_15E1F
		mov	ax, [si+0Ah]
		cmp	ax, [si+0Ch]
		jl	short loc_15E6B
		inc	byte ptr [si]
		mov	word ptr [si+0Ah], 0
		push	6
		call	sub_138B2
		jmp	short loc_15E6B
; ---------------------------------------------------------------------------

loc_15E1F:				; CODE XREF: sub_15DE8+1Dj
		cmp	byte ptr [si], 2
		jnz	short loc_15E41
		mov	ax, [si+16h]
		add	[si+14h], ax
		mov	ax, [si+14h]
		cmp	ax, [si+12h]
		jl	short loc_15E6B
		inc	byte ptr [si]
		mov	word ptr [si+0Ah], 0
		mov	ax, [si+12h]
		mov	[si+14h], ax
		jmp	short loc_15E6B
; ---------------------------------------------------------------------------

loc_15E41:				; CODE XREF: sub_15DE8+3Aj
		cmp	byte ptr [si], 3
		jnz	short loc_15E57
		mov	ax, [si+0Ah]
		cmp	ax, [si+0Eh]
		jl	short loc_15E6B
		inc	byte ptr [si]
		mov	word ptr [si+0Ah], 0
		jmp	short loc_15E6B
; ---------------------------------------------------------------------------

loc_15E57:				; CODE XREF: sub_15DE8+5Cj
		cmp	byte ptr [si], 4
		jnz	short loc_15E6B
		mov	ax, [si+16h]
		sub	[si+14h], ax
		cmp	word ptr [si+14h], 1
		jg	short loc_15E6B
		mov	byte ptr [si], 0

loc_15E6B:				; CODE XREF: sub_15DE8+25j
					; sub_15DE8+35j ...
		inc	word ptr [si+0Ah]
		cmp	byte ptr [si], 1
		jbe	short loc_15EBC
		mov	ax, [si+14h]
		shl	ax, 3
		mov	di, ax
		mov	ax, [si+4]
		add	ax, di
		cmp	ax, word ptr dword_2598E+2
		jg	short loc_15EBC
		mov	ax, [si+14h]
		shl	ax, 2
		mov	di, ax
		cmp	di, 100h
		jl	short loc_15E97
		mov	di, 100h

loc_15E97:				; CODE XREF: sub_15DE8+AAj
		mov	ax, [si+14h]
		shl	ax, 4
		sub	ax, di
		mov	di, ax
		mov	ax, [si+2]
		sub	ax, di
		cmp	ax, word ptr dword_2598E
		jg	short loc_15EBC
		mov	ax, [si+2]
		add	ax, di
		cmp	ax, word ptr dword_2598E
		jl	short loc_15EBC
		mov	byte_259A9, 1

loc_15EBC:				; CODE XREF: sub_15DE8+16j
					; sub_15DE8+89j ...
		inc	[bp+var_2]
		add	si, 18h

loc_15EC2:				; CODE XREF: sub_15DE8+10j
		cmp	[bp+var_2], 2
		jl	loc_15DFB
		pop	di
		pop	si
		leave
		retn
sub_15DE8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15ECE	proc near		; CODE XREF: sub_16610+110p
					; sub_16610+163p ...

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	byte_25667, 0
		jnz	short loc_15EEA
		mov	byte_25667, 1
		mov	byte_2671C, 0
		add	word ptr dword_2670A+2,	100h

loc_15EEA:				; CODE XREF: sub_15ECE+Aj
		cmp	byte_25667, 1
		jnz	short loc_15F46
		cmp	word_2671A, 20h	; ' '
		jl	loc_15F8F
		mov	word_2671A, 0
		mov	byte_25667, 2
		cmp	[bp+arg_0], 0
		jnz	short loc_15F23
		push	1000h
		call	sub_13D76
		add	ax, 400h
		mov	si, ax
		push	400h
		call	sub_13D76
		add	ax, 400h
		mov	di, ax
		jmp	short loc_15F29
; ---------------------------------------------------------------------------

loc_15F23:				; CODE XREF: sub_15ECE+3Bj
		mov	si, 0C00h
		mov	di, 500h

loc_15F29:				; CODE XREF: sub_15ECE+53j
		mov	ax, si
		sub	ax, word ptr dword_2670A
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		mov	word_26712, ax
		mov	ax, di
		sub	ax, word ptr dword_2670A+2
		cwd
		idiv	bx
		mov	word_26714, ax
		jmp	short loc_15F8F
; ---------------------------------------------------------------------------

loc_15F46:				; CODE XREF: sub_15ECE+21j
		cmp	byte_25667, 2
		jnz	short loc_15F67
		push	53CAh
		call	sub_13D32
		cmp	word_2671A, 40h	; '@'
		jl	short loc_15F8F
		mov	word_2671A, 0
		mov	byte_25667, 3
		jmp	short loc_15F8F
; ---------------------------------------------------------------------------

loc_15F67:				; CODE XREF: sub_15ECE+7Dj
		cmp	byte_25667, 3
		jnz	short loc_15F8F
		cmp	word_2671A, 8
		jl	short loc_15F8F
		mov	word_2671A, 0
		mov	byte_25667, 0
		mov	byte_2671D, 0FEh ; 'þ'
		sub	word ptr dword_2670A+2,	100h
		mov	al, 1
		jmp	short loc_15F91
; ---------------------------------------------------------------------------

loc_15F8F:				; CODE XREF: sub_15ECE+28j
					; sub_15ECE+76j ...
		mov	al, 0

loc_15F91:				; CODE XREF: sub_15ECE+BFj
		pop	di
		pop	si
		pop	bp
		retn	2
sub_15ECE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_15F97	proc near		; CODE XREF: sub_16610:loc_166F9p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 1
		jnz	short loc_15FCF
		mov	ax, word ptr dword_2670A
		add	ax, 0FE00h
		mov	word_25662, ax
		mov	byte_266E2, 2
		mov	byte_266E3, 3Bh	; ';'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 0Bh
		mov	byte_266F0, 5
		mov	byte_266EE, 28h	; '('
		call	word_2D004
		jmp	loc_1607E
; ---------------------------------------------------------------------------

loc_15FCF:				; CODE XREF: sub_15F97+8j
		cmp	word_2671A, 0Fh
		jnz	short loc_15FDE
		mov	byte_266ED, 0
		jmp	loc_1607E
; ---------------------------------------------------------------------------

loc_15FDE:				; CODE XREF: sub_15F97+3Dj
		cmp	word_2671A, 1Fh
		jnz	short loc_15FF3
		add	word_25662, 400h
		mov	byte_266ED, 80h	; '€'
		jmp	loc_1607E
; ---------------------------------------------------------------------------

loc_15FF3:				; CODE XREF: sub_15F97+4Cj
		cmp	word_2671A, 2Fh	; '/'
		jnz	short loc_16007
		sub	word_25662, 400h
		mov	byte_266ED, 10h
		jmp	short loc_1607E
; ---------------------------------------------------------------------------

loc_16007:				; CODE XREF: sub_15F97+61j
		cmp	word_2671A, 3Fh	; '?'
		jnz	short loc_1601B
		add	word_25662, 400h
		mov	byte_266ED, 70h	; 'p'
		jmp	short loc_1607E
; ---------------------------------------------------------------------------

loc_1601B:				; CODE XREF: sub_15F97+75j
		cmp	word_2671A, 4Fh	; 'O'
		jnz	short loc_1602F
		sub	word_25662, 400h
		mov	byte_266ED, 20h	; ' '
		jmp	short loc_1607E
; ---------------------------------------------------------------------------

loc_1602F:				; CODE XREF: sub_15F97+89j
		cmp	word_2671A, 5Fh	; '_'
		jnz	short loc_16043
		add	word_25662, 400h
		mov	byte_266ED, 60h	; '`'
		jmp	short loc_1607E
; ---------------------------------------------------------------------------

loc_16043:				; CODE XREF: sub_15F97+9Dj
		cmp	word_2671A, 6Fh	; 'o'
		jnz	short loc_16057
		sub	word_25662, 400h
		mov	byte_266ED, 30h	; '0'
		jmp	short loc_1607E
; ---------------------------------------------------------------------------

loc_16057:				; CODE XREF: sub_15F97+B1j
		cmp	word_2671A, 7Fh	; ''
		jnz	short loc_1606B
		add	word_25662, 400h
		mov	byte_266ED, 50h	; 'P'
		jmp	short loc_1607E
; ---------------------------------------------------------------------------

loc_1606B:				; CODE XREF: sub_15F97+C5j
		cmp	word_2671A, 8Ch	; 'Œ'
		jnz	short loc_1607E
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_1607E:				; CODE XREF: sub_15F97+35j
					; sub_15F97+44j ...
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		cmp	dx, 0Fh
		jnz	short loc_160A3
		mov	ax, word_25662
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		call	word_2D000
		push	3
		call	sub_138B2

loc_160A3:				; CODE XREF: sub_15F97+F3j
		pop	bp
		retn
sub_15F97	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_160A5	proc near		; CODE XREF: sub_16610:loc_166FEp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 1
		jnz	short loc_160DC
		mov	byte_266ED, 0
		mov	byte_266E2, 4
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EC, 26h	; '&'
		mov	al, byte_25688
		inc	al
		mov	byte_266EF, al
		mov	byte_266EE, 40h	; '@'
		mov	byte_25664, 1
		mov	byte_25665, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_160DC:				; CODE XREF: sub_160A5+8j
		cmp	word_2671A, 80h	; '€'
		jge	short loc_160F4
		cmp	byte_25665, 10h
		jb	loc_1617E
		mov	al, byte_266ED
		add	al, 7
		jmp	short loc_16164
; ---------------------------------------------------------------------------

loc_160F4:				; CODE XREF: sub_160A5+3Dj
		cmp	word_2671A, 80h	; '€'
		jnz	short loc_16150
		mov	byte_266E2, 2
		mov	byte_266E3, 3Bh	; ';'
		mov	byte_266ED, 80h	; '€'
		mov	byte_266EE, 10h
		mov	byte_266F2, 82h	; '‚'
		mov	byte_2CFF7, 1
		mov	byte_266EF, 20h	; ' '
		call	word_2D004
		call	sub_1CFB5
		mov	byte_266E2, 4
		mov	byte_266EE, 40h	; '@'
		mov	al, byte_25688
		inc	al
		mov	byte_266EF, al
		mov	byte_25664, 1
		mov	byte_25665, 0
		push	9
		call	sub_138B2
		mov	byte_266E3, 4Ch	; 'L'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_16150:				; CODE XREF: sub_160A5+55j
		cmp	word_2671A, 100h
		jge	short loc_16187
		cmp	byte_25665, 10h
		jb	short loc_1617E
		mov	al, byte_266ED
		add	al, 0F9h ; 'ù'

loc_16164:				; CODE XREF: sub_160A5+4Dj
		mov	byte_266ED, al
		call	word_2D000
		push	3
		call	sub_138B2
		inc	byte_25664
		mov	al, byte_25665
		add	al, 0F0h ; 'ð'
		mov	byte_25665, al

loc_1617E:				; CODE XREF: sub_160A5+44j
					; sub_160A5+B8j
		mov	al, byte_25664
		add	byte_25665, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_16187:				; CODE XREF: sub_160A5+B1j
		cmp	word_2671A, 100h
		jnz	short loc_161C2
		mov	byte_266E2, 2
		mov	byte_266E3, 3Bh	; ';'
		mov	byte_266ED, 0
		mov	byte_266EE, 10h
		mov	byte_266F2, 82h	; '‚'
		mov	byte_2CFF7, 1
		mov	byte_266EF, 20h	; ' '
		call	word_2D004
		call	sub_1CFB5
		push	9
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_161C2:				; CODE XREF: sub_160A5+E8j
		cmp	word_2671A, 120h
		jnz	short loc_161D5
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_161D5:				; CODE XREF: sub_160A5+123j
		pop	bp
		retn
sub_160A5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_161D7	proc near		; CODE XREF: sub_16610:loc_16793p

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_16293

loc_161E7:				; CODE XREF: sub_161D7+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_161F6
		add	bx, 2
		loop	loc_161E7
		jmp	short loc_1626B	; default
; ---------------------------------------------------------------------------

loc_161F6:				; CODE XREF: sub_161D7+16j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_161FA:				; DATA XREF: seg003:280Bo
		mov	ax, word ptr dword_266E4 ; jumptable 000161F6 case 1
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_266E4+2
		mov	word ptr dword_2A8C6+2,	ax
		mov	word_2A8D0, 20h	; ' '
		mov	byte_2A8D2, 0Bh
		mov	word_2A8CE, 1000h
		mov	byte_2A8D3, 3

loc_1621C:				; CODE XREF: sub_161D7:loc_161F6j
					; sub_161D7+4Fj
					; DATA XREF: ...
		call	sub_13B21	; jumptable 000161F6 case 5
		jmp	short loc_1626B	; default
; ---------------------------------------------------------------------------

loc_16221:				; CODE XREF: sub_161D7:loc_161F6j
					; DATA XREF: seg003:280Bo
		mov	byte_2A8D2, 0Ah	; jumptable 000161F6 case 3
		jmp	short loc_1621C	; jumptable 000161F6 case 5
; ---------------------------------------------------------------------------

loc_16228:				; CODE XREF: sub_161D7:loc_161F6j
					; DATA XREF: seg003:280Bo
		push	word ptr dword_266E4 ; jumptable 000161F6 case 17
		push	word ptr dword_266E4+2
		call	sub_C696
		mov	byte_25592, 0Fh
		mov	byte_266E2, 2
		mov	byte_266EE, 10h
		mov	byte_266F2, 87h	; '‡'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 7
		mov	byte_266F0, 8
		mov	byte_266E3, 3Bh	; ';'
		mov	byte_266EE, 20h	; ' '
		call	word_2D004
		mov	byte_2CFF7, 1

loc_1626B:				; CODE XREF: sub_161D7+1Dj
					; sub_161D7+48j
		cmp	word_2671A, 20h	; ' ' ; default
		jl	short locret_16290
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_16290
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D002
		push	9
		call	sub_138B2

locret_16290:				; CODE XREF: sub_161D7+99j
					; sub_161D7+A6j
		leave
		retn
sub_161D7	endp

; ---------------------------------------------------------------------------
		db 0
word_16293	dw	1,     3,     5,   11h ; DATA XREF: sub_161D7+Do
					; value	table for switch statement
		dw offset loc_161FA	; jump table for switch	statement
		dw offset loc_16221
		dw offset loc_1621C
		dw offset loc_16228

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_162A3	proc near		; CODE XREF: sub_16610:loc_16814p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 1
		jnz	short loc_162D7
		mov	byte_266E2, 2
		mov	byte_266E3, 3Bh	; ';'
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266F0, 6
		mov	byte_266EE, 10h
		mov	byte_266F2, 82h	; '‚'
		mov	byte_266EF, 8
		mov	byte_2CFF7, 1
		jmp	short loc_162EA
; ---------------------------------------------------------------------------

loc_162D7:				; CODE XREF: sub_162A3+8j
		cmp	word_2671A, 0AAh ; 'ª'
		jnz	short loc_162EA
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_162EA:				; CODE XREF: sub_162A3+32j
					; sub_162A3+3Aj
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		cmp	dx, 0Fh
		jnz	short loc_1630B
		call	word_2D002
		mov	al, byte_266EF
		add	al, 3
		mov	byte_266EF, al
		push	3
		call	sub_138B2

loc_1630B:				; CODE XREF: sub_162A3+53j
		pop	bp
		retn
sub_162A3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1630D	proc near		; CODE XREF: sub_16610:loc_16819p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 1
		jnz	short loc_16353
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266E4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266E4
		push	ax
		call	sub_1DA8
		mov	byte_266ED, al

loc_1632F:				; CODE XREF: sub_1EA4B:loc_1EA6Bj
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 5
		mov	byte_266F0, 42h	; 'B'
		mov	byte_266EE, 50h	; 'P'
		call	word_2D004
		jmp	short loc_16366
; ---------------------------------------------------------------------------

loc_16353:				; CODE XREF: sub_1630D+8j
		cmp	word_2671A, 80h	; '€'
		jnz	short loc_16366
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_16366:				; CODE XREF: sub_1630D+44j
					; sub_1630D+4Cj
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 7
		jnz	short loc_16387
		mov	al, byte_266F0
		add	al, 0FCh ; 'ü'
		mov	byte_266F0, al
		call	word_2D000
		push	3
		call	sub_138B2

loc_16387:				; CODE XREF: sub_1630D+65j
		pop	bp
		retn
sub_1630D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16389	proc near		; CODE XREF: sub_16610:loc_168A8p

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 14h		; switch 20 cases
		mov	bx, offset word_164ED

loc_16399:				; CODE XREF: sub_16389+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_163A9
		add	bx, 2
		loop	loc_16399
		jmp	loc_16437	; default
; ---------------------------------------------------------------------------

loc_163A9:				; CODE XREF: sub_16389+16j
		jmp	word ptr cs:[bx+28h] ; switch jump

loc_163AD:				; DATA XREF: seg003:2A85o
		mov	byte_2A8D3, 3	; jumptable 000163A9 case 16
		jmp	loc_16437	; default
; ---------------------------------------------------------------------------

loc_163B5:				; CODE XREF: sub_16389:loc_163A9j
					; DATA XREF: seg003:2A85o
		mov	byte_266ED, 0	; jumptable 000163A9 case 48
		push	8
		call	sub_138B2
		mov	byte_25666, 64h	; 'd'

loc_163C6:				; CODE XREF: sub_16389:loc_163A9j
					; DATA XREF: seg003:2A85o
		mov	byte_25592, 0Fh	; jumptable 000163A9 cases 56,64,72,80
		push	word ptr dword_266E4
		push	word ptr dword_266E4+2
		call	sub_C696

loc_163D8:				; CODE XREF: sub_16389:loc_163A9j
					; DATA XREF: seg003:2A85o
		mov	al, byte_2A8D3	; jumptable 000163A9 case 40
		neg	al
		mov	byte_2A8D3, al
		mov	ax, word ptr dword_266E4
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_266E4+2
		mov	word ptr dword_2A8C6+2,	ax
		mov	word_2A8D0, 8
		mov	byte_2A8D2, 9
		mov	word_2A8CE, 1000h

loc_163FD:				; CODE XREF: sub_16389:loc_163A9j
					; sub_16389+7Ej
					; DATA XREF: ...
		call	sub_13B21	; jumptable 000163A9 cases 44,52,60,68,76,84
		jmp	short loc_16437	; default
; ---------------------------------------------------------------------------

loc_16402:				; CODE XREF: sub_16389:loc_163A9j
					; DATA XREF: seg003:2A85o
		mov	byte_2A8D2, 8	; jumptable 000163A9 cases 42,50,58,66,74,82
		jmp	short loc_163FD	; jumptable 000163A9 cases 44,52,60,68,76,84
; ---------------------------------------------------------------------------

loc_16409:				; CODE XREF: sub_16389:loc_163A9j
					; DATA XREF: seg003:2A85o
		mov	ax, word ptr dword_266E4 ; jumptable 000163A9 case 96
		mov	word_2561A, ax
		mov	ax, word ptr dword_266E4+2
		mov	word_2561C, ax
		mov	al, byte_2D01E
		mov	ah, 0
		mov	word_2562A, ax
		mov	word_2562E, 6
		mov	word_25624, 20h	; ' '
		mov	word_25626, 90h	; ''
		mov	byte_25628, 8
		call	sub_15DBD

loc_16437:				; CODE XREF: sub_16389+1Dj
					; sub_16389+29j ...
		cmp	word_2671A, 80h	; '€' ; default
		jl	locret_164EB
		cmp	word_2671A, 0A0h ; ' '
		jg	short loc_16453
		mov	al, byte_25666
		add	al, 2
		mov	byte_25666, al
		jmp	short loc_16469
; ---------------------------------------------------------------------------

loc_16453:				; CODE XREF: sub_16389+BEj
		cmp	byte_25666, 64h	; 'd'
		jbe	short loc_16476
		mov	al, byte ptr word_2671A
		and	al, 1
		mov	dl, byte_25666
		sub	dl, al
		mov	byte_25666, dl

loc_16469:				; CODE XREF: sub_16389+C8j
		mov	al, byte_25666
		mov	ah, 0
		mov	word_216E4, ax
		mov	byte_266D3, 1

loc_16476:				; CODE XREF: sub_16389+CFj
		cmp	word_2671A, 80h	; '€'
		jl	short locret_164EB
		mov	ax, word_2671A
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_164BB
		mov	byte_266E2, 2
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EE, 48h	; 'H'
		call	word_2D004
		call	word_2D000
		mov	al, byte_266ED
		add	al, 2
		mov	byte_266ED, al
		push	9
		call	sub_138B2

loc_164BB:				; CODE XREF: sub_16389+100j
		cmp	word_2671A, 0C0h ; 'À'
		jl	short locret_164EB
		cmp	byte_266CC, 0
		jz	short locret_164EB
		mov	byte_266E2, 2
		mov	byte_266EC, 1Bh
		mov	byte_266E3, 37h	; '7'
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EF, 2
		call	word_2D004
		call	word_2D000

locret_164EB:				; CODE XREF: sub_16389+B4j
					; sub_16389+F3j ...
		leave
		retn
sub_16389	endp

; ---------------------------------------------------------------------------
word_164ED	dw    10h,   28h,   2Ah,   2Ch ; DATA XREF: sub_16389+Do
		dw    30h,   32h,   34h,   38h ; value table for switch	statement
		dw    3Ah,   3Ch,   40h,   42h
		dw    44h,   48h,   4Ah,   4Ch
		dw    50h,   52h,   54h,   60h
		dw offset loc_163AD	; jump table for switch	statement
		dw offset loc_163D8
		dw offset loc_16402
		dw offset loc_163FD
		dw offset loc_163B5
		dw offset loc_16402
		dw offset loc_163FD
		dw offset loc_163C6
		dw offset loc_16402
		dw offset loc_163FD
		dw offset loc_163C6
		dw offset loc_16402
		dw offset loc_163FD
		dw offset loc_163C6
		dw offset loc_16402
		dw offset loc_163FD
		dw offset loc_163C6
		dw offset loc_16402
		dw offset loc_163FD
		dw offset loc_16409

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1653D	proc near		; CODE XREF: sub_16610:loc_1691Ap
		push	bp
		mov	bp, sp
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_1656A
		push	word ptr dword_266E4
		push	word ptr dword_266E4+2
		call	sub_C696
		mov	byte_25592, 0Fh
		mov	byte_2671E, 10h
		mov	byte_2D02D, 10h
		mov	byte_266F2, 0FFh
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1656A:				; CODE XREF: sub_1653D+8j
		cmp	word_2671A, 40h	; '@'
		jl	loc_1660E
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1660E
		mov	byte_266E2, 4
		mov	byte_266EF, 5
		mov	byte_266F0, 1
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EE, 28h	; '('
		call	word_2D004
		add	word ptr dword_266E4, 200h
		mov	al, byte_2671E
		mov	byte_266ED, al
		call	word_2D002
		sub	word ptr dword_266E4, 400h
		mov	al, 80h	; '€'
		sub	al, byte_2671E
		mov	byte_266ED, al
		call	word_2D002
		mov	al, byte_2671E
		add	al, 0F0h ; 'ð'
		mov	byte_2671E, al
		mov	byte_266E2, 1
		mov	byte_266EF, 3
		mov	byte_266EE, 18h
		call	word_2D004
		mov	al, byte_2D02D
		mov	byte_266ED, al
		call	word_2D002
		add	word ptr dword_266E4, 400h
		mov	al, 80h	; '€'
		sub	al, byte_2D02D
		mov	byte_266ED, al
		call	word_2D002
		mov	al, byte_2D02D
		add	al, 9
		mov	byte_2D02D, al
		push	3
		call	sub_138B2

loc_1660E:				; CODE XREF: sub_1653D+32j
					; sub_1653D+41j
		pop	bp
		retn
sub_1653D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16610	proc far

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 100h
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_26719
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 12h
		ja	loc_169B3
		add	bx, bx
		jmp	cs:off_169F4[bx]

loc_16638:				; DATA XREF: seg003:off_169F4o
		cmp	word_2671A, 0
		jnz	short loc_16651
		mov	word ptr dword_25986+2,	seg seg001
		mov	word ptr dword_25986, 11C0h
		mov	word_26700, 0

loc_16651:				; CODE XREF: sub_16610+2Dj
		call	sub_1E67C
		cmp	word_2671A, 80h	; '€'
		jle	loc_169B8
		inc	byte_26719
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	byte_25667, 0
		mov	byte_2CDCA, 0Fh
		mov	word_255AC, 7874h
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_16682:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F66o
		call	sub_1E67C
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_166A0
		mov	byte_23DC2, 40h	; '@'
		mov	byte_23DC3, 40h	; '@'
		mov	byte_23DC4, 40h	; '@'
		mov	byte_266D3, 1

loc_166A0:				; CODE XREF: sub_16610+7Aj
		cmp	word_2671A, 40h	; '@'
		jl	loc_169B8
		inc	byte_26719
		mov	word_26712, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		mov	word_26716, 2328h
		mov	word_26720, 1EDCh
		mov	word_2671A, 0
		sub	word ptr dword_2670A+2,	100h
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_166D8:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F68o ...
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_169E4

loc_166E6:				; CODE XREF: sub_16610+E1j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_166F5
		add	bx, 2
		loop	loc_166E6
		jmp	short loc_16723	; default
; ---------------------------------------------------------------------------

loc_166F5:				; CODE XREF: sub_16610+DCj
		jmp	word ptr cs:[bx+8] ; switch jump

loc_166F9:				; DATA XREF: seg003:2F5Co
		call	sub_15F97	; jumptable 000166F5 case 0
		jmp	short loc_16723	; default
; ---------------------------------------------------------------------------

loc_166FE:				; CODE XREF: sub_16610:loc_166F5j
					; DATA XREF: seg003:2F5Co
		call	sub_160A5	; jumptable 000166F5 case 1
		jmp	short loc_16723	; default
; ---------------------------------------------------------------------------

loc_16703:				; CODE XREF: sub_16610:loc_166F5j
					; DATA XREF: seg003:2F5Co
		mov	word_2671A, 0	; jumptable 000166F5 case 254
		inc	byte_2671F
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 2
		cwd
		idiv	bx
		mov	byte_2671D, dl
		jmp	short loc_16723	; default
; ---------------------------------------------------------------------------

loc_1671E:				; CODE XREF: sub_16610:loc_166F5j
					; DATA XREF: seg003:2F5Co
		push	0		; jumptable 000166F5 case 255
		call	sub_15ECE

loc_16723:				; CODE XREF: sub_16610+E3j
					; sub_16610+ECj ...
		cmp	byte_25667, 0	; default
		jnz	short loc_16766
		cmp	byte_2671F, 4
		jnb	short loc_16742
		call	sub_1E64E
		or	al, al
		jz	loc_169B8
		push	0Fh
		call	sub_19FD8
		call	sub_1E692

loc_16742:				; CODE XREF: sub_16610+11Fj
		cmp	byte_2CFFA, 14h
		jnb	short loc_1674E
		mov	byte_2CFFA, 14h

loc_1674E:				; CODE XREF: sub_16610+137j
		push	0
		call	sub_15C7C
		inc	byte_26719
		mov	ax, word_26720
		mov	word_26716, ax
		sub	word_26720, 320h
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_16766:				; CODE XREF: sub_16610+118j
		inc	word_2671A
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_1676D:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F6Ao ...
		inc	word_2671A
		push	1
		call	sub_15ECE
		or	al, al
		jz	loc_169B8
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_16793:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F6Co ...
		call	sub_161D7
		cmp	word_2671A, 1F4h
		jge	short loc_167AF
		call	sub_1E64E
		or	al, al
		jz	loc_169B8
		push	0Fh
		call	sub_19FD8
		call	sub_1E692

loc_167AF:				; CODE XREF: sub_16610+18Cj
		cmp	byte_2CFFA, 14h
		jnb	short loc_167BB
		mov	byte_2CFFA, 14h

loc_167BB:				; CODE XREF: sub_16610+1A4j
		push	1
		call	sub_15C7C
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		mov	ax, word_26720
		mov	word_26716, ax
		cmp	byte_26719, 0Ah
		jnb	short loc_167EA
		sub	word_26720, 44Ch
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_167EA:				; CODE XREF: sub_16610+1CFj
		sub	word_26720, 4B0h
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_167F3:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F7Ao ...
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp+var_4], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_169D4

loc_16801:				; CODE XREF: sub_16610+1FCj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_4]
		jz	short loc_16810
		add	bx, 2
		loop	loc_16801
		jmp	short loc_1683E	; default
; ---------------------------------------------------------------------------

loc_16810:				; CODE XREF: sub_16610+1F7j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_16814:				; DATA XREF: seg003:2F4Co
		call	sub_162A3	; jumptable 00016810 case 0
		jmp	short loc_1683E	; default
; ---------------------------------------------------------------------------

loc_16819:				; CODE XREF: sub_16610:loc_16810j
					; DATA XREF: seg003:2F4Co
		call	sub_1630D	; jumptable 00016810 case 1
		jmp	short loc_1683E	; default
; ---------------------------------------------------------------------------

loc_1681E:				; CODE XREF: sub_16610:loc_16810j
					; DATA XREF: seg003:2F4Co
		mov	word_2671A, 0	; jumptable 00016810 case 254
		inc	byte_2671F
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 2
		cwd
		idiv	bx
		mov	byte_2671D, dl
		jmp	short loc_1683E	; default
; ---------------------------------------------------------------------------

loc_16839:				; CODE XREF: sub_16610:loc_16810j
					; DATA XREF: seg003:2F4Co
		push	0		; jumptable 00016810 case 255
		call	sub_15ECE

loc_1683E:				; CODE XREF: sub_16610+1FEj
					; sub_16610+207j ...
		cmp	byte_25667, 0	; default
		jnz	short loc_1687B
		cmp	byte_2671F, 4
		jnb	short loc_1685D
		call	sub_1E64E
		or	al, al
		jz	loc_169B8
		push	0Fh
		call	sub_19FD8
		call	sub_1E692

loc_1685D:				; CODE XREF: sub_16610+23Aj
		cmp	byte_2CFFA, 14h
		jnb	short loc_16869
		mov	byte_2CFFA, 14h

loc_16869:				; CODE XREF: sub_16610+252j
		push	0
		call	sub_15C7C
		inc	byte_26719
		mov	ax, word_26720
		mov	word_26716, ax
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_1687B:				; CODE XREF: sub_16610+233j
		inc	word_2671A
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_16882:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F7Co ...
		inc	word_2671A
		push	1
		call	sub_15ECE
		or	al, al
		jz	loc_169B8
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_168A8:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F7Eo ...
		call	sub_16389
		call	sub_1E67C
		cmp	word_2671A, 120h
		jl	loc_169B8
		push	4
		call	sub_15C7C
		cmp	byte_2CFFA, 14h
		jnb	short loc_168C9
		mov	byte_2CFFA, 14h

loc_168C9:				; CODE XREF: sub_16610+2B2j
		inc	byte_26719
		mov	ax, word_26720
		mov	word_26716, ax
		cmp	byte_26719, 11h
		jnz	short loc_168F6
		mov	word_26720, 0
		mov	byte_23DC2, 80h	; '€'
		mov	byte_23DC3, 40h	; '@'
		mov	byte_23DC4, 40h	; '@'
		mov	byte_266D3, 1
		jmp	short loc_168FC
; ---------------------------------------------------------------------------

loc_168F6:				; CODE XREF: sub_16610+2C8j
		sub	word_26720, 4B0h

loc_168FC:				; CODE XREF: sub_16610+2E4j
		mov	word_2671A, 0
		mov	byte_2671F, 0

loc_16907:				; CODE XREF: sub_16610+341j
		mov	byte_2671D, 0
		mov	word_216E4, 64h	; 'd'
		mov	byte_266D3, 1
		jmp	loc_169B8
; ---------------------------------------------------------------------------

loc_1691A:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F86o
		call	sub_1653D
		call	sub_1E64E
		or	al, al
		jnz	short loc_1692E
		cmp	word_2671A, 3E8h
		jl	loc_169B8

loc_1692E:				; CODE XREF: sub_16610+312j
		push	1
		call	sub_15C7C
		inc	byte_26719
		cmp	word_2671A, 3E8h
		jge	short loc_16946
		mov	byte_2671F, 1
		jmp	short loc_1694B
; ---------------------------------------------------------------------------

loc_16946:				; CODE XREF: sub_16610+32Dj
		mov	byte_2671F, 0

loc_1694B:				; CODE XREF: sub_16610+334j
		mov	word_2671A, 0
		jmp	short loc_16907
; ---------------------------------------------------------------------------

loc_16953:				; CODE XREF: sub_16610+23j
					; DATA XREF: seg003:2F88o
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_16963
		push	4
		call	sub_15C7C

loc_16963:				; CODE XREF: sub_16610+34Cj
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_169B8
		push	2
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_16986
		push	3Ch ; '<'
		call	sub_19FD8

loc_16986:				; CODE XREF: sub_16610+36Fj
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_23DC2, 0
		mov	byte_23DC3, 0
		mov	byte_23DC4, 0
		mov	byte_266D3, 1
		mov	byte_259A2, 0FFh
		jmp	short loc_169B8
; ---------------------------------------------------------------------------

loc_169B3:				; CODE XREF: sub_16610+1Dj
		call	sub_1E743
		leave
		retf
; ---------------------------------------------------------------------------

loc_169B8:				; CODE XREF: sub_16610+4Aj
					; sub_16610+6Fj ...
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax
		call	sub_15DE8
		push	word_26716
		push	2328h
		call	sub_19F16
		leave
		retf
sub_16610	endp

; ---------------------------------------------------------------------------
		db 0
word_169D4	dw	0,     1,  0FEh,  0FFh ; DATA XREF: sub_16610+1EEo
					; value	table for switch statement
		dw offset loc_16814	; jump table for switch	statement
		dw offset loc_16819
		dw offset loc_1681E
		dw offset loc_16839
word_169E4	dw	0,     1,  0FEh,  0FFh ; DATA XREF: sub_16610+D3o
					; value	table for switch statement
		dw offset loc_166F9	; jump table for switch	statement
		dw offset loc_166FE
		dw offset loc_16703
		dw offset loc_1671E
off_169F4	dw offset loc_16638	; DATA XREF: sub_16610+23r
		dw offset loc_16682
		dw offset loc_166D8
		dw offset loc_1676D
		dw offset loc_16793
		dw offset loc_166D8
		dw offset loc_1676D
		dw offset loc_16793
		dw offset loc_166D8
		dw offset loc_1676D
		dw offset loc_16793
		dw offset loc_167F3
		dw offset loc_16882
		dw offset loc_168A8
		dw offset loc_167F3
		dw offset loc_16882
		dw offset loc_168A8
		dw offset loc_1691A
		dw offset loc_16953

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16A1A	proc near		; CODE XREF: sub_16DFF+4p sub_16E9D+4p ...
		push	bp
		mov	bp, sp
		cmp	byte_2671D, 1
		jb	short loc_16A71
		cmp	byte_2671D, 6
		ja	short loc_16A71
		mov	ax, word_2671A
		cmp	ax, 20h	; ' '
		jz	short loc_16A3F
		cmp	ax, 22h	; '"'
		jz	short loc_16A69
		cmp	ax, 24h	; '$'
		jz	short loc_16A6E
		jmp	short loc_16A71
; ---------------------------------------------------------------------------

loc_16A3F:				; CODE XREF: sub_16A1A+17j
		mov	ax, word ptr dword_2670A
		add	ax, 0FEC0h
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF80h
		mov	word ptr dword_2A8C6+2,	ax
		mov	word_2A8D0, 10h
		mov	byte_2A8D3, 0FEh ; 'þ'
		mov	byte_2A8D2, 3
		mov	word_2A8CE, 1000h
		jmp	short loc_16A6E
; ---------------------------------------------------------------------------

loc_16A69:				; CODE XREF: sub_16A1A+1Cj
		mov	byte_2A8D2, 2

loc_16A6E:				; CODE XREF: sub_16A1A+21j
					; sub_16A1A+4Dj
		call	sub_13B21

loc_16A71:				; CODE XREF: sub_16A1A+8j sub_16A1A+Fj ...
		cmp	word_2671A, 10h
		jnz	short loc_16A86
		mov	byte_26718, 82h	; '‚'
		push	8
		call	sub_138B2
		jmp	short loc_16ADA
; ---------------------------------------------------------------------------

loc_16A86:				; CODE XREF: sub_16A1A+5Cj
		cmp	word_2671A, 1Eh
		jnz	short loc_16AA2
		mov	ax, word ptr dword_2670A
		add	ax, 0FEC0h
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF80h
		push	ax
		call	sub_C696
		jmp	short loc_16ADA
; ---------------------------------------------------------------------------

loc_16AA2:				; CODE XREF: sub_16A1A+71j
		cmp	word_2671A, 2Ch	; ','
		jl	short loc_16AC3
		cmp	word_2671A, 40h	; '@'
		jge	short loc_16AC3
		mov	ax, word_2671A
		add	ax, 0FFE0h
		mov	bx, 4
		cwd
		idiv	bx
		add	al, 80h	; '€'
		mov	byte_26718, al
		jmp	short loc_16ADA
; ---------------------------------------------------------------------------

loc_16AC3:				; CODE XREF: sub_16A1A+8Dj
					; sub_16A1A+94j
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_16ADA
		mov	byte_26718, 82h	; '‚'
		push	0Fh
		call	sub_138B2
		mov	al, 2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_16ADA:				; CODE XREF: sub_16A1A+6Aj
					; sub_16A1A+86j ...
		cmp	word_2671A, 40h	; '@'
		jge	short loc_16AE5
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_16AE5:				; CODE XREF: sub_16A1A+C5j
		mov	al, 1
		pop	bp
		retn
sub_16A1A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16AE9	proc near		; CODE XREF: sub_179F4:loc_17B1Ep

var_1		= byte ptr -1

		enter	2, 0
		mov	ax, word_2671A
		and	ax, 1Fh
		cmp	ax, 1
		jnz	loc_16B7D
		cmp	word ptr dword_2670A, 700h
		jg	short loc_16B0A
		mov	word_26712, 20h	; ' '
		jmp	short loc_16B2E
; ---------------------------------------------------------------------------

loc_16B0A:				; CODE XREF: sub_16AE9+17j
		cmp	word ptr dword_2670A, 1100h
		jl	short loc_16B1A
		mov	word_26712, 0FFE0h
		jmp	short loc_16B2E
; ---------------------------------------------------------------------------

loc_16B1A:				; CODE XREF: sub_16AE9+27j
		push	1
		call	sub_13D60
		or	ax, ax
		jz	short loc_16B28
		mov	ax, 10h
		jmp	short loc_16B2B
; ---------------------------------------------------------------------------

loc_16B28:				; CODE XREF: sub_16AE9+38j
		mov	ax, 0FFF0h

loc_16B2B:				; CODE XREF: sub_16AE9+3Dj
		mov	word_26712, ax

loc_16B2E:				; CODE XREF: sub_16AE9+1Fj
					; sub_16AE9+2Fj
		cmp	word ptr dword_2670A+2,	500h
		jg	short loc_16B3E
		mov	word_26714, 10h
		jmp	short loc_16B7D
; ---------------------------------------------------------------------------

loc_16B3E:				; CODE XREF: sub_16AE9+4Bj
		cmp	word ptr dword_2670A+2,	900h
		jl	short loc_16B4E
		mov	word_26714, 0FFF0h
		jmp	short loc_16B7D
; ---------------------------------------------------------------------------

loc_16B4E:				; CODE XREF: sub_16AE9+5Bj
		push	3

loc_16B50:				; CODE XREF: sub_1EA4B:loc_1EA6Bj
		call	sub_13D60	; jumptable 0001EA6B case 7819
		mov	[bp+var_1], al
		cmp	[bp+var_1], 0
		jnz	short loc_16B61
		mov	ax, 10h
		jmp	short loc_16B7A
; ---------------------------------------------------------------------------

loc_16B61:				; CODE XREF: sub_16AE9+71j
		cmp	[bp+var_1], 1
		jnz	short loc_16B6C
		mov	ax, 0FFF0h
		jmp	short loc_16B7A
; ---------------------------------------------------------------------------

loc_16B6C:				; CODE XREF: sub_16AE9+7Cj
		cmp	[bp+var_1], 2
		jnz	short loc_16B77
		mov	ax, 18h
		jmp	short loc_16B7A
; ---------------------------------------------------------------------------

loc_16B77:				; CODE XREF: sub_16AE9+87j
		mov	ax, 0FFE8h

loc_16B7A:				; CODE XREF: sub_16AE9+76j
					; sub_16AE9+81j ...
		mov	word_26714, ax

loc_16B7D:				; CODE XREF: sub_16AE9+Dj
					; sub_16AE9+53j ...
		push	53CAh
		call	sub_13D32
		leave
		retn
sub_16AE9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16B85	proc near		; CODE XREF: sub_16F61+70p
					; sub_17079+94p ...

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	byte_2D02B, 0
		jnz	short loc_16BC5
		mov	ax, si
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, 0FFFAh
		push	ax
		mov	ax, 0C00h
		sub	ax, word ptr dword_2670A
		cwd
		pop	bx
		idiv	bx
		mov	word_26712, ax
		mov	ax, si
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, 0FFFAh
		push	ax
		mov	ax, 700h
		sub	ax, word ptr dword_2670A+2
		cwd
		pop	bx
		idiv	bx
		mov	word_26714, ax

loc_16BC5:				; CODE XREF: sub_16B85+Cj
		inc	byte_2D02B
		mov	al, byte_2D02B
		mov	ah, 0
		lea	dx, [si-0Ch]
		cmp	ax, dx
		jl	short loc_16BEB
		mov	ax, word_26712
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	word_26712, ax
		mov	ax, word_26714
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	word_26714, ax

loc_16BEB:				; CODE XREF: sub_16B85+4Ej
		mov	al, byte_2D02B
		mov	ah, 0
		cmp	ax, si
		jl	short loc_16BF8
		mov	al, 1
		jmp	short loc_16C00
; ---------------------------------------------------------------------------

loc_16BF8:				; CODE XREF: sub_16B85+6Dj
		push	53CAh
		call	sub_13D32
		mov	al, 0

loc_16C00:				; CODE XREF: sub_16B85+71j
		pop	si
		pop	bp
		retn	2
sub_16B85	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16C05	proc near		; CODE XREF: sub_16E9D:loc_16EF1p

var_A		= byte ptr -0Ah
var_1		= byte ptr -1

		enter	0Ah, 0
		push	si
		push	di
		lea	ax, [bp+var_A]
		push	ss
		push	ax
		push	ds
		push	offset unk_22D9E
		mov	cx, 8
		call	SCOPY@
		call	sub_13D52
		mov	[bp+var_1], al
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_16C61
; ---------------------------------------------------------------------------

loc_16C29:				; CODE XREF: sub_16C05+5Fj
		mov	byte ptr [si], 1
		mov	al, byte_25671
		mov	[si+19h], al
		mov	al, [bp+var_1]
		mov	[si+1],	al
		add	al, 40h	; '@'
		mov	[bp+var_1], al
		lea	ax, [di+88h]
		mov	[si+6],	ax
		mov	word ptr [si+10h], 0
		mov	bx, di
		add	bx, bx
		lea	ax, [bp+var_A]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	[si+14h], ax
		mov	word ptr [si+12h], 20h ; ' '
		inc	di
		add	si, 1Ah

loc_16C61:				; CODE XREF: sub_16C05+22j
		cmp	di, 4
		jl	short loc_16C29
		pop	di
		pop	si
		leave
		retn
sub_16C05	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16C6A	proc near		; CODE XREF: sub_179F4+2BCp

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		mov	byte_25672, 0
		mov	si, 0B204h
		mov	[bp+var_2], 0
		jmp	loc_16DCB
; ---------------------------------------------------------------------------

loc_16C80:				; CODE XREF: sub_16C6A+165j
		cmp	byte ptr [si], 0
		jz	loc_16DC5
		cmp	byte ptr [si], 80h ; '€'
		jb	short loc_16CB4
		mov	al, [si]
		inc	al
		mov	[si], al
		mov	ah, 0
		mov	di, ax
		add	ax, 0FF80h
		mov	bx, 4
		cwd
		idiv	bx
		add	ax, 4
		mov	di, ax
		mov	[si+6],	di
		cmp	di, 0Ch
		jl	loc_16DC5
		mov	byte ptr [si], 0
		jmp	loc_16DC5
; ---------------------------------------------------------------------------

loc_16CB4:				; CODE XREF: sub_16C6A+20j
		mov	al, [si+19h]
		add	[si+1],	al
		mov	ax, [si+12h]
		add	[si+10h], ax
		lea	ax, [si+2]
		push	ax
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		push	word ptr [si+10h]
		mov	al, [si+1]
		mov	ah, 0
		push	ax
		call	sub_1333C
		cmp	byte ptr [si], 1
		jnz	short loc_16CEF
		cmp	word ptr [si+10h], 400h
		jl	short loc_16CFC
		inc	byte ptr [si]
		mov	word ptr [si+12h], 0
		jmp	short loc_16CFC
; ---------------------------------------------------------------------------

loc_16CEF:				; CODE XREF: sub_16C6A+73j
		cmp	byte ptr [si], 2
		jnz	short loc_16CFC
		cmp	word ptr [si+10h], 40h ; '@'
		jl	short loc_16CFC
		inc	byte ptr [si]

loc_16CFC:				; CODE XREF: sub_16C6A+7Aj
					; sub_16C6A+83j ...
		mov	word_257E2, 0C0h ; 'À'
		mov	word_257E4, 0C0h ; 'À'
		mov	ax, [si+2]
		mov	word ptr dword_257DE, ax
		mov	ax, [si+4]
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		mov	[si+16h], ax
		mov	ax, [si+16h]
		sub	[si+14h], ax
		cmp	word ptr [si+14h], 0
		jg	short loc_16D53
		mov	word ptr [si+6], 4
		mov	byte ptr [si], 80h ; '€'
		push	3
		call	sub_138B2
		add	dword_2569A, 1400h
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	large 400008h
		nop
		push	cs
		call	near ptr sub_13E2A
		jmp	short loc_16DC5
; ---------------------------------------------------------------------------

loc_16D53:				; CODE XREF: sub_16C6A+BCj
		mov	ax, [si+2]
		add	ax, 0FF40h
		mov	di, ax
		mov	ax, [si+4]
		add	ax, 0FF40h
		mov	[bp+var_4], ax
		mov	ax, word ptr dword_2598E
		sub	ax, di
		cmp	ax, 180h
		jnb	short loc_16D7E
		mov	ax, word ptr dword_2598E+2
		sub	ax, [bp+var_4]
		cmp	ax, 180h
		jnb	short loc_16D7E
		mov	byte_259A9, 1

loc_16D7E:				; CODE XREF: sub_16C6A+102j
					; sub_16C6A+10Dj
		mov	ax, [si+4]
		cmp	ax, word_25984
		jge	short loc_16D93
		mov	ax, [si+2]
		mov	word_25982, ax
		mov	ax, [si+4]
		mov	word_25984, ax

loc_16D93:				; CODE XREF: sub_16C6A+11Bj
		mov	ax, [si+2]
		sar	ax, 4
		add	ax, 20h	; ' '
		mov	dl, byte_25672
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+4338h], ax
		mov	ax, [si+4]
		sar	ax, 4
		add	ax, 10h
		mov	dl, byte_25672
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+4340h], ax
		inc	byte_25672

loc_16DC5:				; CODE XREF: sub_16C6A+19j
					; sub_16C6A+40j ...
		inc	[bp+var_2]
		add	si, 1Ah

loc_16DCB:				; CODE XREF: sub_16C6A+13j
		cmp	[bp+var_2], 4
		jl	loc_16C80
		pop	di
		pop	si
		leave
		retn
sub_16C6A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16DD7	proc near		; CODE XREF: sub_16F61+5Ap
					; sub_17079+7Ep ...
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_16DF6
; ---------------------------------------------------------------------------

loc_16DE3:				; CODE XREF: sub_16DD7+22j
		cmp	byte ptr [si], 0
		jz	short loc_16DF2
		cmp	byte ptr [si], 80h ; '€'
		jnb	short loc_16DF2
		push	si
		call	word_25676

loc_16DF2:				; CODE XREF: sub_16DD7+Fj
					; sub_16DD7+14j
		inc	di
		add	si, 1Ah

loc_16DF6:				; CODE XREF: sub_16DD7+Aj
		cmp	di, 4
		jl	short loc_16DE3
		pop	di
		pop	si
		pop	bp
		retn
sub_16DD7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16DFF	proc near		; CODE XREF: sub_179F4:loc_17B13p

var_1		= byte ptr -1

		enter	2, 0
		call	sub_16A1A
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_16E2E
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266ED, 80h	; '€'
		mov	byte_266F0, 8
		call	word_2D004
		leave
		retn
; ---------------------------------------------------------------------------

loc_16E2E:				; CODE XREF: sub_16DFF+Ej
		cmp	[bp+var_1], 1
		jnz	short locret_16E9B
		mov	ax, word_2671A
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_16E84
		push	3
		call	sub_13D60
		inc	al
		mov	byte_266EF, al
		push	1Fh
		call	sub_13D60
		add	al, 20h	; ' '
		mov	byte_266EE, al
		mov	al, byte_266ED
		add	al, 0F8h ; 'ø'
		mov	byte_266ED, al
		sub	word ptr dword_266E4, 60h ; '`'
		call	word_2D000
		push	3
		call	sub_13D60
		inc	al
		mov	byte_266EF, al
		push	1Fh
		call	sub_13D60
		add	al, 20h	; ' '
		mov	byte_266EE, al
		add	word ptr dword_266E4, 0C0h ; 'À'
		call	word_2D000

loc_16E84:				; CODE XREF: sub_16DFF+40j
		cmp	byte_266ED, 0
		jnz	short locret_16E9B
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

locret_16E9B:				; CODE XREF: sub_16DFF+33j
					; sub_16DFF+8Aj
		leave
		retn
sub_16DFF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16E9D	proc near		; CODE XREF: sub_179F4:loc_17AE3p

var_2		= word ptr -2

		enter	2, 0
		call	sub_16A1A
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 5		; switch 5 cases
		mov	bx, offset word_16F10

loc_16EB0:				; CODE XREF: sub_16E9D+1Ej
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_16EBF
		add	bx, 2
		loop	loc_16EB0
		jmp	short locret_16F0E ; default
; ---------------------------------------------------------------------------

loc_16EBF:				; CODE XREF: sub_16E9D+19j
		jmp	word ptr cs:[bx+0Ah] ; switch jump

loc_16EC3:				; DATA XREF: seg003:348Ao
		mov	ax, word ptr dword_2670A ; jumptable 00016EBF case 32
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_2A8C6+2,	ax
		mov	word_2A8D0, 20h	; ' '
		mov	byte_2A8D3, 0FEh ; 'þ'
		mov	byte_2A8D2, 9
		mov	word_2A8CE, 1000h

loc_16EE5:				; CODE XREF: sub_16E9D:loc_16EBFj
					; sub_16E9D+52j
					; DATA XREF: ...
		call	sub_13B21	; jumptable 00016EBF case 36
		leave
		retn
; ---------------------------------------------------------------------------

loc_16EEA:				; CODE XREF: sub_16E9D:loc_16EBFj
					; DATA XREF: seg003:348Ao
		mov	byte_2A8D2, 8	; jumptable 00016EBF case 34
		jmp	short loc_16EE5	; jumptable 00016EBF case 36
; ---------------------------------------------------------------------------

loc_16EF1:				; CODE XREF: sub_16E9D:loc_16EBFj
					; DATA XREF: seg003:348Ao
		call	sub_16C05	; jumptable 00016EBF case 64
		mov	al, byte_25671
		neg	al
		mov	byte_25671, al
		leave
		retn
; ---------------------------------------------------------------------------

loc_16EFE:				; CODE XREF: sub_16E9D:loc_16EBFj
					; DATA XREF: seg003:348Ao
		mov	word_2671A, 0	; jumptable 00016EBF case 96
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

locret_16F0E:				; CODE XREF: sub_16E9D+20j
		leave			; default
		retn
sub_16E9D	endp

; ---------------------------------------------------------------------------
word_16F10	dw    20h,   22h,   24h,   40h ; DATA XREF: sub_16E9D+10o
		dw    60h		; value	table for switch statement
		dw offset loc_16EC3	; jump table for switch	statement
		dw offset loc_16EEA
		dw offset loc_16EE5
		dw offset loc_16EF1
		dw offset loc_16EFE
; ---------------------------------------------------------------------------
		enter	2, 0
		push	si
		mov	si, [bp+4]
		cmp	byte_25672, 2
		ja	short loc_16F38
		mov	byte_266EF, 5

loc_16F38:				; CODE XREF: seg003:34A1j
		cmp	byte ptr [si+19h], 0
		jl	short loc_16F42
		mov	al, 0C0h ; 'À'
		jmp	short loc_16F44
; ---------------------------------------------------------------------------

loc_16F42:				; CODE XREF: seg003:34ACj
		mov	al, 40h	; '@'

loc_16F44:				; CODE XREF: seg003:34B0j
		mov	[bp-1],	al
		mov	al, [si+1]
		add	al, [bp-1]
		mov	byte_266ED, al
		mov	eax, [si+2]
		mov	dword_266E4, eax
		call	word_2D000
		pop	si
		leave
		retn	2

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_16F61	proc near		; CODE XREF: sub_179F4:loc_17AE9p

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		call	sub_16A1A
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_16F9F
		mov	byte_266E2, 1
		mov	byte_266EE, 38h	; '8'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 3
		mov	byte_266F0, 8
		call	word_2D004
		mov	word_25676, 3494h
		mov	al, byte ptr word_2671A
		mov	byte_2D02D, al
		jmp	loc_1705D
; ---------------------------------------------------------------------------

loc_16F9F:				; CODE XREF: sub_16F61+10j
		cmp	[bp+var_1], 1
		jnz	loc_1705D
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1702D
		cmp	byte_25672, 0
		jz	short loc_16FC6
		call	sub_16DD7
		mov	al, byte ptr word_2671A
		mov	byte_2D02D, al
		jmp	short loc_17026
; ---------------------------------------------------------------------------

loc_16FC6:				; CODE XREF: sub_16F61+58j
		mov	al, byte_2D02D
		mov	ah, 0
		mov	dx, 0A0h ; ' '
		sub	dx, ax
		push	dx
		call	sub_16B85
		mov	byte_266E2, 2
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EE, 34h	; '4'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 3
		mov	byte_266F0, 6
		mov	al, byte_266ED
		add	al, 6
		mov	byte_266ED, al
		call	word_2D004
		call	word_2D000
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	word_2D000
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	word_2D000
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	word_2D000

loc_17026:				; CODE XREF: sub_16F61+63j
		push	9
		call	sub_138B2

loc_1702D:				; CODE XREF: sub_16F61+51j
		cmp	word_2671A, 0A0h ; ' '
		jl	short loc_1705D
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_17048
; ---------------------------------------------------------------------------

loc_1703C:				; CODE XREF: sub_16F61+EAj
		mov	al, [si+19h]
		neg	al
		mov	[si+19h], al
		inc	di
		add	si, 1Ah

loc_17048:				; CODE XREF: sub_16F61+D9j
		cmp	di, 4
		jl	short loc_1703C
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

loc_1705D:				; CODE XREF: sub_16F61+3Bj
					; sub_16F61+42j ...
		pop	di
		pop	si
		leave
		retn
sub_16F61	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+4]
		mov	eax, [si+2]
		mov	dword_266E4, eax
		call	word_2D000
		pop	si
		pop	bp
		retn	2

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17079	proc near		; CODE XREF: sub_179F4:loc_17AEFp

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		call	sub_16A1A
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_170C3
		mov	byte_266E2, 1
		mov	byte_266EE, 10h
		mov	byte_266EC, 0
		call	word_2D004
		mov	word_25676, 35D1h
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_170B5
; ---------------------------------------------------------------------------

loc_170AB:				; CODE XREF: sub_17079+3Fj
		mov	al, [si+19h]
		add	[si+19h], al
		inc	di
		add	si, 1Ah

loc_170B5:				; CODE XREF: sub_17079+30j
		cmp	di, 4
		jl	short loc_170AB
		mov	al, byte ptr word_2671A
		mov	byte_2D02D, al
		jmp	loc_17179
; ---------------------------------------------------------------------------

loc_170C3:				; CODE XREF: sub_17079+10j
		cmp	[bp+var_1], 1
		jnz	loc_17179
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_17145
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8
		mov	byte_266ED, al
		cmp	byte_25672, 0
		jz	short loc_17102
		call	sub_16DD7
		mov	al, byte ptr word_2671A
		mov	byte_2D02D, al
		jmp	short loc_17136
; ---------------------------------------------------------------------------

loc_17102:				; CODE XREF: sub_17079+7Cj
		mov	al, byte_2D02D
		mov	ah, 0
		mov	dx, 0A0h ; ' '
		sub	dx, ax
		push	dx
		call	sub_16B85
		mov	byte_266E2, 2
		mov	byte_266E3, 38h	; '8'
		mov	byte_266EC, 2Eh	; '.'
		mov	byte_266EF, 3
		mov	byte_266F0, 0Ch
		mov	byte_266ED, 0
		call	word_2D004
		call	word_2D000

loc_17136:				; CODE XREF: sub_17079+87j
		mov	al, byte_266EE
		add	al, 4
		mov	byte_266EE, al
		push	9
		call	sub_138B2

loc_17145:				; CODE XREF: sub_17079+5Dj
		cmp	word_2671A, 0A0h ; ' '
		jl	short loc_17179
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_17164
; ---------------------------------------------------------------------------

loc_17154:				; CODE XREF: sub_17079+EEj
		mov	al, [si+19h]
		cbw
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	[si+19h], al
		inc	di
		add	si, 1Ah

loc_17164:				; CODE XREF: sub_17079+D9j
		cmp	di, 4
		jl	short loc_17154
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

loc_17179:				; CODE XREF: sub_17079+47j
					; sub_17079+4Ej ...
		pop	di
		pop	si
		leave
		retn
sub_17079	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1717D	proc near		; CODE XREF: sub_179F4:loc_17AF5p

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		call	sub_16A1A
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_171A2
		mov	byte_266E2, 1
		mov	word_25676, 3494h
		mov	byte_2D02D, 0
		jmp	loc_17331
; ---------------------------------------------------------------------------

loc_171A2:				; CODE XREF: sub_1717D+10j
		cmp	[bp+var_1], 1
		jnz	loc_17331
		cmp	byte_25672, 0
		jz	loc_1726E
		cmp	word_2671A, 0C0h ; 'À'
		jg	short loc_171D2
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_171CA
; ---------------------------------------------------------------------------

loc_171C2:				; CODE XREF: sub_1717D+50j
		add	word ptr [si+10h], 18h
		inc	di
		add	si, 1Ah

loc_171CA:				; CODE XREF: sub_1717D+43j
		cmp	di, 4
		jl	short loc_171C2
		jmp	loc_17331
; ---------------------------------------------------------------------------

loc_171D2:				; CODE XREF: sub_1717D+3Cj
		cmp	word_2671A, 100h
		jg	short loc_17232
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_17331
		mov	ax, word_2671A
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1720D
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 10h
		call	word_2D004
		call	word_2D000

loc_1720D:				; CODE XREF: sub_1717D+77j
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 3
		mov	byte_266F0, 6
		call	word_2D004
		mov	byte_266EE, 40h	; '@'
		push	9
		call	sub_138B2
		call	sub_16DD7
		jmp	loc_17331
; ---------------------------------------------------------------------------

loc_17232:				; CODE XREF: sub_1717D+5Bj
		cmp	word_2671A, 180h
		jg	short loc_17251
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_17249
; ---------------------------------------------------------------------------

loc_17241:				; CODE XREF: sub_1717D+CFj
		sub	word ptr [si+10h], 18h
		inc	di
		add	si, 1Ah

loc_17249:				; CODE XREF: sub_1717D+C2j
		cmp	di, 4
		jl	short loc_17241
		jmp	loc_17331
; ---------------------------------------------------------------------------

loc_17251:				; CODE XREF: sub_1717D+BBj
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_17266
; ---------------------------------------------------------------------------

loc_17258:				; CODE XREF: sub_1717D+ECj
		mov	al, [si+19h]
		neg	al
		mov	[si+19h], al
		add	di, 2
		add	si, 34h	; '4'

loc_17266:				; CODE XREF: sub_1717D+D9j
		cmp	di, 4
		jl	short loc_17258
		jmp	loc_17318
; ---------------------------------------------------------------------------

loc_1726E:				; CODE XREF: sub_1717D+32j
		push	60h ; '`'
		call	sub_16B85
		cmp	byte_2D02D, 0
		jnz	short loc_1729F
		mov	byte_2D02D, 1
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266ED, 80h	; '€'
		mov	byte_266F0, 8
		push	0Fh
		call	sub_138B2

loc_1729F:				; CODE XREF: sub_1717D+FBj
		mov	ax, word_2671A
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_17331
		push	3
		call	sub_13D60
		inc	al
		mov	byte_266EF, al
		push	1Fh
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		test	byte_2D02D, 1
		jz	short loc_172D0
		mov	al, byte_266ED
		add	al, 0F8h ; 'ø'
		jmp	short loc_172D5
; ---------------------------------------------------------------------------

loc_172D0:				; CODE XREF: sub_1717D+14Aj
		mov	al, byte_266ED
		add	al, 8

loc_172D5:				; CODE XREF: sub_1717D+151j
		mov	byte_266ED, al
		sub	word ptr dword_266E4, 60h ; '`'
		call	word_2D000
		push	3
		call	sub_13D60
		inc	al
		mov	byte_266EF, al
		push	1Fh
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		add	word ptr dword_266E4, 0C0h ; 'À'
		call	word_2D000
		cmp	byte_266ED, 0
		jz	short loc_1730D
		cmp	byte_266ED, 80h	; '€'
		jb	short loc_17331

loc_1730D:				; CODE XREF: sub_1717D+187j
		inc	byte_2D02D
		cmp	byte_2D02D, 4
		jb	short loc_1732A

loc_17318:				; CODE XREF: sub_1717D+EEj
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''
		jmp	short loc_17331
; ---------------------------------------------------------------------------

loc_1732A:				; CODE XREF: sub_1717D+199j
		push	0Fh
		call	sub_138B2

loc_17331:				; CODE XREF: sub_1717D+22j
					; sub_1717D+29j ...
		pop	di
		pop	si
		leave
		retn
sub_1717D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17335	proc near		; CODE XREF: sub_179F4:loc_17AFBp

var_3		= byte ptr -3
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		call	sub_16A1A
		mov	[bp+var_3], al
		cmp	[bp+var_3], 2
		jnz	short loc_1736D
		mov	byte_266E2, 5
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EE, 32h	; '2'
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266ED, 0
		call	word_2D004
		mov	word_25676, 35D1h
		jmp	loc_1748D
; ---------------------------------------------------------------------------

loc_1736D:				; CODE XREF: sub_17335+10j
		cmp	[bp+var_3], 1
		jnz	loc_1748D
		cmp	byte_25672, 0
		jz	short loc_173D3
		mov	ax, word_2671A
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_173AC
		mov	al, byte_25672
		add	al, al
		mov	dl, 18h
		sub	dl, al
		mov	byte_266EF, dl
		cmp	byte_25674, 2
		jnz	short loc_173A2
		mov	byte_266EF, 1Ch

loc_173A2:				; CODE XREF: sub_17335+66j
		call	sub_16DD7
		push	9
		call	sub_138B2

loc_173AC:				; CODE XREF: sub_17335+52j
		cmp	word_2671A, 0A0h ; ' '
		jl	loc_1748D
		mov	di, 0B204h
		xor	si, si
		jmp	short loc_173CB
; ---------------------------------------------------------------------------

loc_173BD:				; CODE XREF: sub_17335+99j
		mov	al, [di+19h]
		neg	al
		mov	[di+19h], al
		add	si, 2
		add	di, 34h	; '4'

loc_173CB:				; CODE XREF: sub_17335+86j
		cmp	si, 4
		jl	short loc_173BD
		jmp	loc_1747D
; ---------------------------------------------------------------------------

loc_173D3:				; CODE XREF: sub_17335+45j
		push	40h ; '@'
		call	sub_16B85
		or	al, al
		jnz	loc_1747D
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1748D
		mov	byte_266E2, 4
		mov	byte_266E3, 3Dh	; '='
		mov	byte_266EC, 1
		mov	byte_266F2, 0FFh
		call	word_2D004
		xor	si, si
		jmp	short loc_1746F
; ---------------------------------------------------------------------------

loc_17409:				; CODE XREF: sub_17335+13Dj
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FCC0h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FD80h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		push	60h ; '`'
		call	sub_13D76
		add	ax, 10h
		mov	[bp+var_2], ax
		mov	al, byte ptr [bp+var_2]
		mov	byte_266EE, al
		cmp	[bp+var_2], 40h	; '@'
		jl	short loc_1744D
		mov	byte_266ED, 0
		jmp	short loc_1746A
; ---------------------------------------------------------------------------

loc_1744D:				; CODE XREF: sub_17335+10Fj
		mov	ax, 40h	; '@'
		sub	ax, [bp+var_2]
		mov	[bp+var_2], ax
		push	ax
		call	sub_13D76
		push	ax
		mov	ax, [bp+var_2]
		cwd
		sub	ax, dx
		sar	ax, 1
		pop	dx
		sub	dl, al
		mov	byte_266ED, dl

loc_1746A:				; CODE XREF: sub_17335+116j
		call	word_2D002
		inc	si

loc_1746F:				; CODE XREF: sub_17335+D2j
		cmp	si, 20h	; ' '
		jl	short loc_17409
		push	0Fh
		call	sub_138B2
		jmp	short loc_1748D
; ---------------------------------------------------------------------------

loc_1747D:				; CODE XREF: sub_17335+9Bj
					; sub_17335+A5j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

loc_1748D:				; CODE XREF: sub_17335+35j
					; sub_17335+3Cj ...
		pop	di
		pop	si
		leave
		retn
sub_17335	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17491	proc near		; CODE XREF: sub_179F4:loc_17B01p

var_1		= byte ptr -1

		enter	2, 0
		push	si
		call	sub_16A1A
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_174CD
		mov	byte_266E2, 2
		mov	byte_266E3, 38h	; '8'
		mov	byte_266EE, 5Ch	; '\'
		mov	byte_266EC, 0
		mov	byte_266F2, 83h	; 'ƒ'
		call	word_2D004
		mov	word_25676, 35D1h
		mov	byte_2D02D, 0
		jmp	loc_1769B
; ---------------------------------------------------------------------------

loc_174CD:				; CODE XREF: sub_17491+Fj
		cmp	[bp+var_1], 1
		jnz	loc_1769B
		cmp	byte_25672, 0
		jz	loc_17615
		cmp	word_2671A, 60h	; '`'
		jg	short loc_17515
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_17683
		mov	byte_2CFF8, 40h	; '@'
		mov	byte_266ED, 10h
		xor	si, si
		jmp	short loc_1750E
; ---------------------------------------------------------------------------

loc_17502:				; CODE XREF: sub_17491+80j
		call	sub_1CFB5
		mov	al, byte_266ED
		add	al, 20h	; ' '
		mov	byte_266ED, al
		inc	si

loc_1750E:				; CODE XREF: sub_17491+6Fj
		cmp	si, 4
		jl	short loc_17502
		jmp	short loc_17560
; ---------------------------------------------------------------------------

loc_17515:				; CODE XREF: sub_17491+52j
		cmp	word_2671A, 80h	; '€'
		jg	short loc_1756A
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_17683
		mov	byte_2CFF8, 30h	; '0'
		mov	byte_266ED, 90h	; ''
		call	sub_1CFB5
		mov	byte_2CFF8, 50h	; 'P'
		mov	byte_266ED, 0B0h ; '°'
		call	sub_1CFB5
		mov	byte_2CFF8, 30h	; '0'
		mov	byte_266ED, 0D0h ; 'Ð'
		call	sub_1CFB5
		mov	byte_2CFF8, 50h	; 'P'
		mov	byte_266ED, 0F0h ; 'ð'
		call	sub_1CFB5

loc_17560:				; CODE XREF: sub_17491+82j
					; sub_17491+10Fj ...
		push	3
		call	sub_138B2
		jmp	loc_17683
; ---------------------------------------------------------------------------

loc_1756A:				; CODE XREF: sub_17491+8Aj
		cmp	word_2671A, 0A0h ; ' '
		jg	short loc_175A2
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_17683
		mov	byte_2CFF8, 70h	; 'p'
		mov	byte_266ED, 10h
		xor	si, si
		jmp	short loc_1759B
; ---------------------------------------------------------------------------

loc_1758F:				; CODE XREF: sub_17491+10Dj
		call	sub_1CFB5
		mov	al, byte_266ED
		add	al, 20h	; ' '
		mov	byte_266ED, al
		inc	si

loc_1759B:				; CODE XREF: sub_17491+FCj
		cmp	si, 4
		jl	short loc_1758F
		jmp	short loc_17560
; ---------------------------------------------------------------------------

loc_175A2:				; CODE XREF: sub_17491+DFj
		cmp	word_2671A, 0C0h ; 'À'
		jg	short loc_175DA
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_17683
		mov	byte_2CFF8, 10h
		mov	byte_266ED, 10h
		xor	si, si
		jmp	short loc_175D3
; ---------------------------------------------------------------------------

loc_175C7:				; CODE XREF: sub_17491+145j
		call	sub_1CFB5
		mov	al, byte_266ED
		add	al, 20h	; ' '
		mov	byte_266ED, al
		inc	si

loc_175D3:				; CODE XREF: sub_17491+134j
		cmp	si, 4
		jl	short loc_175C7
		jmp	short loc_17560
; ---------------------------------------------------------------------------

loc_175DA:				; CODE XREF: sub_17491+117j
		cmp	word_2671A, 0E0h ; 'à'
		jg	loc_17683
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_17683
		mov	byte_2CFF8, 40h	; '@'
		mov	byte_266ED, 10h
		xor	si, si
		jmp	short loc_1760D
; ---------------------------------------------------------------------------

loc_17601:				; CODE XREF: sub_17491+17Fj
		call	sub_1CFB5
		mov	al, byte_266ED
		add	al, 20h	; ' '
		mov	byte_266ED, al
		inc	si

loc_1760D:				; CODE XREF: sub_17491+16Ej
		cmp	si, 4
		jl	short loc_17601
		jmp	loc_17560
; ---------------------------------------------------------------------------

loc_17615:				; CODE XREF: sub_17491+49j
		push	80h ; '€'
		call	sub_16B85
		cmp	byte_2D02D, 0
		jnz	short loc_17634
		push	1Fh
		call	sub_13D60
		mov	dl, 80h	; '€'
		sub	dl, al
		mov	byte_266ED, dl
		mov	byte_2D02D, 1

loc_17634:				; CODE XREF: sub_17491+18Fj
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_17675
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 2Fh	; '/'
		mov	byte_266EF, 10h
		mov	byte_266F0, 5
		mov	byte_266EE, 10h
		call	word_2D004
		call	sub_1CFA2
		mov	al, byte_266ED
		add	al, 0F8h ; 'ø'
		mov	byte_266ED, al
		push	0Fh
		call	sub_138B2

loc_17675:				; CODE XREF: sub_17491+1AEj
		cmp	byte_266ED, 80h	; '€'
		jbe	short loc_17683
		cmp	byte_266ED, 0E0h ; 'à'
		jbe	short loc_1768B

loc_17683:				; CODE XREF: sub_17491+5Fj
					; sub_17491+97j ...
		cmp	word_2671A, 100h
		jl	short loc_1769B

loc_1768B:				; CODE XREF: sub_17491+1F0j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

loc_1769B:				; CODE XREF: sub_17491+39j
					; sub_17491+40j ...
		pop	si
		leave
		retn
sub_17491	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1769E	proc near		; CODE XREF: sub_179F4:loc_17B07p

var_1		= byte ptr -1

		enter	2, 0
		call	sub_16A1A
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_176D9
		mov	byte_266E2, 2
		mov	byte_266E3, 38h	; '8'
		mov	byte_266EC, 0
		mov	byte_266F2, 0FFh
		mov	byte_266ED, 0C0h ; 'À'
		mov	byte_266EE, 60h	; '`'
		mov	word_25676, 35D1h
		mov	byte_2D02D, 0
		leave
		retn
; ---------------------------------------------------------------------------

loc_176D9:				; CODE XREF: sub_1769E+Ej
		cmp	[bp+var_1], 1
		jnz	locret_17811
		cmp	byte_25672, 0
		jz	loc_1779E
		cmp	word_2671A, 80h	; '€'
		jg	short loc_17707
		cmp	byte_266CD, 0
		jnz	locret_17811
		call	sub_16DD7
		push	9
		call	sub_138B2
		leave
		retn
; ---------------------------------------------------------------------------

loc_17707:				; CODE XREF: sub_1769E+52j
		cmp	word_2671A, 0C0h ; 'À'
		jg	loc_17794
		cmp	byte_266CD, 0
		jnz	locret_17811
		mov	word ptr dword_266E4, 0
		push	0C00h
		call	sub_13D76
		mov	word ptr dword_266E4+2,	ax
		push	1Fh
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		push	1Fh
		call	sub_13D60
		mov	dl, 30h	; '0'
		sub	dl, al
		mov	byte_266ED, dl
		call	word_2D002
		mov	word ptr dword_266E4, 1800h
		push	0C00h
		call	sub_13D76
		mov	word ptr dword_266E4+2,	ax
		push	1Fh
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		push	1Fh
		call	sub_13D60
		add	al, 50h	; 'P'
		mov	byte_266ED, al
		call	word_2D002
		push	1800h
		call	sub_13D76
		mov	word ptr dword_266E4, ax
		mov	word ptr dword_266E4+2,	0
		push	1Fh
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		push	1Fh
		call	sub_13D60
		add	al, 30h	; '0'
		mov	byte_266ED, al
		call	word_2D002
		leave
		retn
; ---------------------------------------------------------------------------

loc_17794:				; CODE XREF: sub_1769E+6Fj
		cmp	word_2671A, 100h
		jl	short locret_17811
		jmp	short loc_17801
; ---------------------------------------------------------------------------

loc_1779E:				; CODE XREF: sub_1769E+48j
		push	0A0h ; ' '
		call	sub_16B85
		cmp	byte_2D02D, 0
		jnz	short loc_177B8
		push	1Fh
		call	sub_13D60
		mov	byte_266ED, al
		mov	byte_2D02D, 1

loc_177B8:				; CODE XREF: sub_1769E+10Bj
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_177F9
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 2Fh	; '/'
		mov	byte_266EF, 10h
		mov	byte_266F0, 5
		mov	byte_266EE, 10h
		call	word_2D004
		call	sub_1CFA2
		mov	al, byte_266ED
		add	al, 8
		mov	byte_266ED, al
		push	0Fh
		call	sub_138B2

loc_177F9:				; CODE XREF: sub_1769E+125j
		cmp	word_2671A, 0C0h ; 'À'
		jl	short locret_17811

loc_17801:				; CODE XREF: sub_1769E+FEj
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

locret_17811:				; CODE XREF: sub_1769E+3Fj
					; sub_1769E+59j ...
		leave
		retn
sub_1769E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17813	proc near		; CODE XREF: sub_179F4:loc_17B19p

var_1		= byte ptr -1

		enter	2, 0
		call	sub_16A1A
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_1784F
		mov	byte_266E2, 1
		mov	byte_266EF, 20h	; ' '
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EE, 38h	; '8'
		call	word_2D004
		push	1
		call	sub_13D60
		or	ax, ax
		jnz	short loc_17848
		mov	al, 1
		jmp	short loc_1784A
; ---------------------------------------------------------------------------

loc_17848:				; CODE XREF: sub_17813+2Fj
		mov	al, 0FFh

loc_1784A:				; CODE XREF: sub_17813+33j
		mov	byte_2D02D, al
		leave
		retn
; ---------------------------------------------------------------------------

loc_1784F:				; CODE XREF: sub_17813+Ej
		cmp	[bp+var_1], 1
		jnz	short locret_1788C
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_17874
		call	word_2D000
		mov	al, byte_2D02D
		add	byte_266ED, al
		push	9
		call	sub_138B2

loc_17874:				; CODE XREF: sub_17813+4Dj
		cmp	word_2671A, 80h	; '€'
		jl	short locret_1788C
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

locret_1788C:				; CODE XREF: sub_17813+40j
					; sub_17813+67j
		leave
		retn
sub_17813	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1788E	proc far		; CODE XREF: sub_179F4:loc_17B0Dp

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		call	sub_16A1A
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_178AD
		mov	byte_2D02C, 20h	; ' '
		push	1
		call	sub_13D60
		mov	byte_2D02D, al

loc_178AD:				; CODE XREF: sub_1788E+10j
		call	sub_16A1A
		cmp	al, 1
		jnz	loc_179B8
		cmp	byte_25672, 0
		jz	loc_1795F
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1793D
		mov	word_25676, 35D1h
		mov	byte_266E2, 1
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EC, 0
		mov	al, byte ptr word_266CA
		shl	al, 3
		mov	byte_266ED, al
		cmp	byte_2D02D, 0
		jz	short loc_178F6
		neg	al
		mov	byte_266ED, al

loc_178F6:				; CODE XREF: sub_1788E+61j
		call	word_2D004
		call	sub_16DD7
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_17936
		mov	word_25676, 3494h
		mov	byte_266E2, 4	; CODE XREF: sub_1CCB8:loc_1CCD9j
					; sub_1CD6E:loc_1CD8Fj
		mov	byte_266E3, 39h	; '9'
		mov	al, byte_2D02C
		mov	byte_266EE, al
		add	al, 2
		mov	byte_2D02C, al
		mov	byte_266EC, 0
		mov	byte_266ED, 0
		call	word_2D004
		call	sub_16DD7

loc_17936:				; CODE XREF: sub_1788E+7Aj
		push	9
		call	sub_138B2

loc_1793D:				; CODE XREF: sub_1788E+3Cj
		cmp	word_2671A, 0A0h ; ' '
		jl	short loc_179B8
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_17958
; ---------------------------------------------------------------------------

loc_1794C:				; CODE XREF: sub_1788E+CDj
		mov	al, [si+19h]
		neg	al
		mov	[si+19h], al
		inc	di
		add	si, 1Ah

loc_17958:				; CODE XREF: sub_1788E+BCj
		cmp	di, 4
		jl	short loc_1794C
		jmp	short loc_179A8
; ---------------------------------------------------------------------------

loc_1795F:				; CODE XREF: sub_1788E+2Dj
		push	48h ; 'H'
		call	sub_16B85
		or	al, al
		jnz	short loc_179A8
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_179B8
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 30h	; '0'
		mov	byte_266EF, 10h
		mov	byte_266F0, 5
		mov	byte_266ED, 0
		mov	byte_266EE, 10h
		call	word_2D004
		call	sub_1CFA2
		push	0Fh
		call	sub_138B2
		jmp	short loc_179B8
sub_1788E	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_179A8:				; CODE XREF: sub_1788E+CFj
					; sub_1788E+D8j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	byte_26718, 81h	; ''

loc_179B8:				; CODE XREF: sub_1788E+24j
					; sub_1788E+B5j ...
		pop	di
		pop	si
		leave
		retn
; END OF FUNCTION CHUNK	FOR sub_1CCB8

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_179BC	proc near		; CODE XREF: sub_179F4:loc_17B98p
		push	bp
		mov	bp, sp
		inc	word_2671A
		push	large 1800180h
		push	4
		call	sub_1E5D8
		mov	byte_2671C, al
		mov	ah, 0
		mov	dl, byte_25672
		mov	dh, 0
		inc	dx
		push	dx
		cwd
		pop	bx
		idiv	bx
		sub	word_26716, ax
		mov	ax, word_26716
		cmp	ax, word_26720
		jg	short loc_179F0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_179F0:				; CODE XREF: sub_179BC+2Ej
		mov	al, 0
		pop	bp
		retn
sub_179BC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_179F4	proc far

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		mov	ax, word ptr dword_2670A
		add	ax, 0FEC0h
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF80h
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_26719
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	loc_17C9F
		add	bx, bx
		jmp	cs:off_17CEB[bx]

loc_17A1F:				; DATA XREF: seg003:off_17CEBo
		cmp	word_2671A, 0
		jnz	short loc_17A31
		mov	word_26716, 1770h
		mov	byte_25671, 2

loc_17A31:				; CODE XREF: sub_179F4+30j
		call	sub_1E67C
		cmp	word_2671A, 60h	; '`'
		jle	loc_17CA4
		inc	byte_26719
		mov	byte_23DC2, 0
		mov	byte_23DC3, 0
		mov	byte_23DC4, 7
		mov	byte_266D3, 1
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	word_255AC, 77E7h
		mov	byte_2CDCA, 0Fh
		mov	byte_25670, 0
		jmp	loc_17CA4
; ---------------------------------------------------------------------------

loc_17A75:				; CODE XREF: sub_179F4+26j
					; DATA XREF: seg003:425Do
		inc	word_2671A
		call	sub_1E67C
		cmp	word_2671A, 80h	; '€'
		jl	loc_17CA4
		inc	byte_26719
		mov	word_26712, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0Ah
		mov	word_2671A, 0
		mov	byte_26718, 81h	; ''
		mov	byte_25673, 1
		mov	byte_25674, 0
		mov	byte_2566E, 0Ah
		mov	byte_2566F, 0
		mov	byte_2D02B, 0
		jmp	loc_17CA4
; ---------------------------------------------------------------------------

loc_17AC1:				; CODE XREF: sub_179F4+26j
					; DATA XREF: seg003:425Fo
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp+var_4], ax
		mov	cx, 0Bh		; switch 11 cases
		mov	bx, offset word_17CBF

loc_17ACF:				; CODE XREF: sub_179F4+E6j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_4]
		jz	short loc_17ADF
		add	bx, 2
		loop	loc_17ACF
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17ADF:				; CODE XREF: sub_179F4+E1j
		jmp	word ptr cs:[bx+16h] ; switch jump

loc_17AE3:				; DATA XREF: seg003:4245o
		call	sub_16E9D	; jumptable 00017ADF case 0
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17AE9:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_16F61	; jumptable 00017ADF case 1
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17AEF:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_17079	; jumptable 00017ADF case 2
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17AF5:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_1717D	; jumptable 00017ADF case 3
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17AFB:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_17335	; jumptable 00017ADF case 4
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17B01:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_17491	; jumptable 00017ADF case 5
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17B07:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_1769E	; jumptable 00017ADF case 6
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17B0D:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	near ptr sub_1788E ; jumptable 00017ADF	case 7
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17B13:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_16DFF	; jumptable 00017ADF case 10
		jmp	loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17B19:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_17813	; jumptable 00017ADF case 11
		jmp	short loc_17B98	; default
; ---------------------------------------------------------------------------

loc_17B1E:				; CODE XREF: sub_179F4:loc_17ADFj
					; DATA XREF: seg003:4245o
		call	sub_16AE9	; jumptable 00017ADF case 255
		cmp	word_2671A, 40h	; '@'
		jl	short loc_17B98	; default
		inc	byte_2671F
		mov	byte_2D02B, 0
		cmp	byte_2566F, 0
		jnz	short loc_17B62
		cmp	byte_25672, 0
		jnz	short loc_17B62
		inc	byte_25673
		cmp	byte_25673, 2
		jb	short loc_17B56
		mov	byte_2671D, 0
		mov	byte_25673, 0
		jmp	short loc_17B84
; ---------------------------------------------------------------------------

loc_17B56:				; CODE XREF: sub_179F4+154j
		push	1
		call	sub_13D60
		add	al, 0Ah
		mov	byte_2671D, al
		jmp	short loc_17B84
; ---------------------------------------------------------------------------

loc_17B62:				; CODE XREF: sub_179F4+142j
					; sub_179F4+149j ...
		push	7
		call	sub_13D76
		inc	ax
		mov	[bp+var_2], ax
		mov	al, byte_2566E
		mov	ah, 0
		cmp	ax, [bp+var_2]
		jz	short loc_17B62
		mov	al, byte ptr [bp+var_2]
		mov	byte_2671D, al
		mov	byte_2566E, al
		mov	al, byte_25672
		mov	byte_2566F, al

loc_17B84:				; CODE XREF: sub_179F4+160j
					; sub_179F4+16Cj
		mov	word_2671A, 0
		cmp	byte_2671F, 34h	; '4'
		jb	short loc_17B98	; default
		mov	byte_2671F, 0
		jmp	short loc_17BA4
; ---------------------------------------------------------------------------

loc_17B98:				; CODE XREF: sub_179F4+E8j
					; sub_179F4+F2j ...
		call	sub_179BC	; default
		or	al, al
		jz	short loc_17BB3
		mov	byte_2671F, 1

loc_17BA4:				; CODE XREF: sub_179F4+1A2j
		push	3
		call	sub_15C7C
		inc	byte_26719
		mov	word_2671A, 0

loc_17BB3:				; CODE XREF: sub_179F4+1A9j
		cmp	byte_266CD, 0
		jnz	short loc_17BF0
		cmp	byte_25670, 0
		jnz	short loc_17BD7
		mov	al, byte_23DC4
		add	al, 2
		mov	byte_23DC4, al
		cmp	byte_23DC4, 0C0h ; 'À'
		jb	short loc_17BEB
		mov	byte_25670, 1
		jmp	short loc_17BEB
; ---------------------------------------------------------------------------

loc_17BD7:				; CODE XREF: sub_179F4+1CBj
		mov	al, byte_23DC4
		add	al, 0FEh ; 'þ'
		mov	byte_23DC4, al
		cmp	byte_23DC4, 26h	; '&'
		ja	short loc_17BEB
		mov	byte_25670, 0

loc_17BEB:				; CODE XREF: sub_179F4+1DAj
					; sub_179F4+1E1j ...
		mov	byte_266D3, 1

loc_17BF0:				; CODE XREF: sub_179F4+1C4j
		cmp	word_26716, 1194h
		jg	short loc_17BFF
		cmp	byte_25674, 0
		jz	short loc_17C21

loc_17BFF:				; CODE XREF: sub_179F4+202j
		cmp	word_26716, 9C4h
		jg	short loc_17C0E
		cmp	byte_25674, 1
		jz	short loc_17C21

loc_17C0E:				; CODE XREF: sub_179F4+211j
		cmp	word_26716, 3E8h
		jg	loc_17CA4
		cmp	byte_25674, 2
		jnz	loc_17CA4

loc_17C21:				; CODE XREF: sub_179F4+209j
					; sub_179F4+218j
		call	sub_1E692
		cmp	byte_2CFFA, 14h
		jnb	short loc_17C30
		mov	byte_2CFFA, 14h

loc_17C30:				; CODE XREF: sub_179F4+235j
		push	0Ah
		call	sub_19FD8
		mov	al, byte_25674
		mov	ah, 0
		push	ax
		call	sub_15C7C
		inc	byte_25674
		jmp	short loc_17CA4
; ---------------------------------------------------------------------------

loc_17C44:				; CODE XREF: sub_179F4+26j
					; DATA XREF: seg003:4261o
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_17C54
		push	4
		call	sub_15C7C

loc_17C54:				; CODE XREF: sub_179F4+259j
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_17CA4
		push	2
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_17C77
		push	28h ; '('
		call	sub_19FD8

loc_17C77:				; CODE XREF: sub_179F4+27Cj
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_23DC2, 0
		mov	byte_23DC4, 0
		mov	byte_266D3, 1
		mov	byte_259A2, 0FFh
		jmp	short loc_17CA4
; ---------------------------------------------------------------------------

loc_17C9F:				; CODE XREF: sub_179F4+20j
		call	sub_1E743
		leave
		retf
; ---------------------------------------------------------------------------

loc_17CA4:				; CODE XREF: sub_179F4+45j
					; sub_179F4+7Ej ...
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax
		call	sub_16C6A
		push	word_26716
		push	1770h
		call	sub_19F16
		leave
		retf
sub_179F4	endp ; sp-analysis failed

; ---------------------------------------------------------------------------
word_17CBF	dw	0,     1,     2,     3 ; DATA XREF: sub_179F4+D8o
		dw	4,     5,     6,     7 ; value table for switch	statement
		dw    0Ah,   0Bh,  0FFh
		dw offset loc_17AE3	; jump table for switch	statement
		dw offset loc_17AE9
		dw offset loc_17AEF
		dw offset loc_17AF5
		dw offset loc_17AFB
		dw offset loc_17B01
		dw offset loc_17B07
		dw offset loc_17B0D
		dw offset loc_17B13
		dw offset loc_17B19
		dw offset loc_17B1E
off_17CEB	dw offset loc_17A1F	; DATA XREF: sub_179F4+26r
		dw offset loc_17A75
		dw offset loc_17AC1
		dw offset loc_17C44

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17CF3	proc near		; CODE XREF: seg003:4385p

var_2		= word ptr -2
arg_4		= word ptr  8

; FUNCTION CHUNK AT 4277 SIZE 00000007 BYTES
; FUNCTION CHUNK AT 432D SIZE 0000000E BYTES

		enter	2, 0
		push	si
		push	di
		mov	di, [bp+arg_4]
		mov	si, 8A92h
		mov	[bp+var_2], 0
		jmp	loc_17DC3
sub_17CF3	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_17CF3

loc_17D07:				; CODE XREF: sub_17CF3+D4j
		cmp	byte ptr [si], 0
		jnz	loc_17DBD
; END OF FUNCTION CHUNK	FOR sub_17CF3
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_17D0E:				; CODE XREF: sub_1CCB8:loc_1CCD9j
					; sub_1CCB8:loc_1CCD9j	...
		mov	byte ptr [si], 3 ; jumptable 0001CCD9 case 30465
		mov	byte ptr [si+1Ah], 0 ; CODE XREF: sub_1CCB8:loc_1CCD9j
		mov	byte ptr [si+1Bh], 0
		mov	byte ptr [si+1], 0
		mov	word ptr [si+18h], 0
		mov	bx, word ptr [bp+0ah]
		add	bx, bx
		mov	ax, [bx+3D7Ah]
		mov	[si+16h], ax
		cmp	di, 3E70h
		jnz	short loc_17D3C
		push	1800h
		call	sub_13D76
		mov	di, ax

loc_17D3C:				; CODE XREF: sub_1CCB8-4F86j
		cmp	word ptr [bp+06h], 3E70h
		jnz	short loc_17D4C
		push	1700h
		call	sub_13D76
		mov	word ptr [bp+06h], ax

loc_17D4C:				; CODE XREF: sub_1CCB8-4F77j
		mov	[si+2],	di
		mov	ax, word ptr [bp+06h]
		mov	[si+4],	ax
		mov	al, [bp+4]
		mov	[si+23h], al
		mov	byte ptr [si+24h], 0
		cmp	byte_25688, 3
		jnz	short loc_17D6B
		mov	ax, 1
		jmp	short loc_17D6D
; ---------------------------------------------------------------------------

loc_17D6B:				; CODE XREF: sub_1CCB8-4F54j
		xor	ax, ax

loc_17D6D:				; CODE XREF: sub_1CCB8-4F4Fj
		mov	[si+29h], al
		mov	byte ptr [si+20h], 0
		mov	byte ptr [si+21h], 0
		mov	byte ptr [si+25h], 1
		mov	byte ptr [si+26h], 4
		mov	byte ptr [si+27h], 0
		mov	byte ptr [si+28h], 0
		mov	byte ptr [si+2Ah], 0
		cmp	di, 0C00h
		jge	short loc_17D96
		mov	al, 1
		jmp	short loc_17D98
; ---------------------------------------------------------------------------

loc_17D96:				; CODE XREF: sub_1CCB8-4F28j
		mov	al, 0

loc_17D98:				; CODE XREF: sub_1CCB8-4F24j
		mov	[si+2Bh], al
		call	sub_13D52
		mov	[si+3Eh], al
		mov	byte ptr [si+3Fh], 80h ; '€'
		mov	byte ptr [si+36h], 41h ; 'A'
		mov	byte ptr [si+2Ch], 1
		mov	byte ptr [si+38h], 2Ah ; '*'
		mov	word ptr [si+2Eh], 0
		mov	word ptr [si+30h], 0
		jmp	short loc_17DCB
; END OF FUNCTION CHUNK	FOR sub_1CCB8
; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_17CF3

loc_17DBD:				; CODE XREF: sub_17CF3+17j
		inc	[bp+var_2]
		add	si, 40h	; '@'

loc_17DC3:				; CODE XREF: sub_17CF3+11j
		cmp	[bp+var_2], 20h	; ' '
		jl	loc_17D07
; END OF FUNCTION CHUNK	FOR sub_17CF3
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_17DCB:				; CODE XREF: sub_1CCB8-4EFDj
		pop	di
		pop	si
		leave
		retn	8
; END OF FUNCTION CHUNK	FOR sub_1CCB8
; ---------------------------------------------------------------------------
		enter	2, 0
		les	bx, dword_250FA
		assume es:nothing
		mov	ax, es:[bx]
		cmp	ax, word_266CA
		jnz	short locret_17E3C
		add	word ptr dword_250FA, 2
		les	bx, dword_250FA
		mov	al, es:[bx]
		mov	[bp-1],	al
		inc	word ptr dword_250FA

loc_17DF5:				; CODE XREF: seg003:4394j
		cmp	byte_259F2, 0
		jnz	short loc_17E18
		les	bx, dword_250FA
		mov	al, es:[bx]
		mov	ah, 0
		push	ax
		push	word ptr es:[bx+1]
		push	word ptr es:[bx+3]
		mov	al, es:[bx+5]
		mov	ah, 0
		push	ax
		call	sub_17CF3

loc_17E18:				; CODE XREF: seg003:436Aj
		add	word ptr dword_250FA, 8
		dec	byte ptr [bp-1]
		cmp	byte ptr [bp-1], 0
		ja	short loc_17DF5
		les	bx, dword_250FA
		cmp	word ptr es:[bx], 0
		jnz	short locret_17E3C
		mov	word ptr dword_25986+2,	seg seg001
		mov	word ptr dword_25986, 11C0h

locret_17E3C:				; CODE XREF: seg003:4350j seg003:439Ej
		leave
		retf

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17E3E	proc near		; CODE XREF: sub_17E59+17Dp

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, 9
		mov	si, [bp+arg_0]
		add	si, 2Ch	; ','
		mov	di, 53A2h
		push	ds
		pop	es
		assume es:dseg
		rep movsw
		pop	di
		pop	si
		pop	bp
		retn	2
sub_17E3E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_17E59	proc far		; CODE XREF: sub_AB88+64P

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		mov	word_25982, 0C190h
		mov	word_25984, 0C190h
		mov	word_257E2, 100h
		mov	word_257E4, 0C0h ; 'À'
		mov	si, 8A92h
		xor	di, di
		jmp	loc_18024
; ---------------------------------------------------------------------------

loc_17E7F:				; CODE XREF: sub_17E59+1CEj
		cmp	byte ptr [si], 0
		jz	loc_18020
		cmp	byte ptr [si], 2
		jnz	short loc_17E91
		mov	byte ptr [si], 0
		jmp	loc_18020
; ---------------------------------------------------------------------------

loc_17E91:				; CODE XREF: sub_17E59+30j
		mov	word_2598A, si
		cmp	byte ptr [si], 80h ; '€'
		jnb	loc_17FF4
		call	sub_155DD
		cmp	byte ptr [si+2Ah], 0
		jz	short loc_17ECA
		mov	ax, [si+2]
		sub	ax, word ptr dword_2598E
		add	ax, 0C0h ; 'À'
		cmp	ax, 180h
		jnb	short loc_17ECA
		mov	ax, [si+4]
		sub	ax, word ptr dword_2598E+2
		add	ax, 0C0h ; 'À'
		cmp	ax, 180h
		jnb	short loc_17ECA
		mov	byte_259A9, 1
		jmp	short loc_17F3C
; ---------------------------------------------------------------------------

loc_17ECA:				; CODE XREF: sub_17E59+4Aj
					; sub_17E59+59j ...
		cmp	byte ptr [si+28h], 0
		jz	loc_17F9B
		cmp	word ptr [si+10h], 0FFFFh
		jz	loc_17F9B
		mov	ax, [si+2]
		add	ax, 100h
		cmp	ax, 1A00h
		jnb	loc_17F9B
		mov	ax, [si+4]
		add	ax, 100h
		cmp	ax, 1800h
		jnb	loc_17F9B
		mov	ax, [si+4]
		cmp	ax, word_25984
		jle	short loc_17F0F
		cmp	ax, word ptr dword_2598E+2
		jg	short loc_17F0F
		mov	ax, [si+2]
		mov	word_25982, ax
		mov	ax, [si+4]
		mov	word_25984, ax

loc_17F0F:				; CODE XREF: sub_17E59+A2j
					; sub_17E59+A8j
		mov	eax, [si+2]
		mov	dword_257DE, eax
		call	sub_105B9
		mov	[bp+var_1], al
		cmp	[bp+var_1], 0
		jz	short loc_17F9B
		cmp	word ptr [si+10h], 0FFFEh
		jz	short loc_17F94
		mov	ah, 0
		cmp	ax, [si+10h]
		jge	short loc_17F3C
		mov	al, [bp+var_1]
		mov	ah, 0
		sub	[si+10h], ax
		jmp	short loc_17F8E
; ---------------------------------------------------------------------------

loc_17F3C:				; CODE XREF: sub_17E59+6Fj
					; sub_17E59+D7j
		mov	byte ptr [si], 80h ; '€'
		mov	byte ptr [si+25h], 1
		mov	byte ptr [si+28h], 0
		mov	byte ptr [si+2Ah], 0
		mov	word ptr [si+0Ah], 0
		mov	word ptr [si+0Ch], 0
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	word ptr [si+23h]
		call	sub_1DA38
		push	3
		call	sub_138B2
		movzx	eax, word ptr [si+14h]
		add	dword_2569A, eax
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	large 400008h
		nop
		push	cs
		call	near ptr sub_13E2A
		inc	word_22E9E
		inc	word_22EA0
		jmp	loc_18020
; ---------------------------------------------------------------------------

loc_17F8E:				; CODE XREF: sub_17E59+E1j
		mov	byte ptr [si+24h], 1
		jmp	short loc_17F9B
; ---------------------------------------------------------------------------

loc_17F94:				; CODE XREF: sub_17E59+D0j
		push	0Ah
		call	sub_138B2

loc_17F9B:				; CODE XREF: sub_17E59+75j
					; sub_17E59+7Dj ...
		cmp	byte ptr [si+29h], 0
		jz	short loc_17FEF
		inc	byte ptr [si+3Eh]
		mov	al, [si+3Eh]
		cmp	al, [si+3Fh]
		jb	short loc_17FEF
		cmp	word ptr [si+4], 1300h
		jge	short loc_17FEF
		mov	ax, [si+2]
		sub	ax, word ptr dword_2598E
		add	ax, 300h
		cmp	ax, 600h
		jnb	short loc_17FD1
		mov	ax, [si+4]
		sub	ax, word ptr dword_2598E+2
		add	ax, 300h
		cmp	ax, 600h
		jb	short loc_17FEF

loc_17FD1:				; CODE XREF: sub_17E59+167j
		mov	byte ptr [si+3Eh], 0
		push	si
		call	sub_17E3E
		mov	ax, [si+2]
		add	word ptr dword_266E4, ax
		mov	ax, [si+4]
		add	word ptr dword_266E4+2,	ax
		call	word_2D004
		call	word_2D000

loc_17FEF:				; CODE XREF: sub_17E59+146j
					; sub_17E59+151j ...
		inc	byte ptr [si+1]
		jmp	short loc_18020
; ---------------------------------------------------------------------------

loc_17FF4:				; CODE XREF: sub_17E59+3Fj
		lea	ax, [si+2]
		push	ax
		call	sub_13D32
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
		mov	[si+0Eh], al
		cmp	[bp+var_1], 0Ch
		jb	short loc_18020
		mov	byte ptr [si], 2

loc_18020:				; CODE XREF: sub_17E59+29j
					; sub_17E59+35j ...
		inc	di
		add	si, 40h	; '@'

loc_18024:				; CODE XREF: sub_17E59+23j
		cmp	di, 20h	; ' '
		jl	loc_17E7F
		pop	di
		pop	si
		leave
		retf
sub_17E59	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1802F	proc near		; CODE XREF: sub_18044:loc_1808Bp
		push	bp
		mov	bp, sp
		mov	byte_2A8D3, 0FEh ; 'þ'
		call	sub_13B21
		mov	byte_2A8D3, 2
		call	sub_13B21
		pop	bp
		retn
sub_1802F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18044	proc near		; CODE XREF: sub_180BB+9p sub_1812A+9p ...

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_2671A
		add	ax, word_231F2
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_180AB

loc_18058:				; CODE XREF: sub_18044+1Fj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_18067
		add	bx, 2
		loop	loc_18058
		jmp	short locret_180A9 ; default
; ---------------------------------------------------------------------------

loc_18067:				; CODE XREF: sub_18044+1Aj
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1806B:				; DATA XREF: seg003:4623o
		mov	word_2A8CE, 1400h ; jumptable 00018067 case 32
		mov	ax, word_259EC
		add	ax, 0FF60h
		mov	word ptr dword_2A8C6+2,	ax
		mov	ax, word_259EA
		mov	word ptr dword_2A8C6, ax
		mov	word_2A8D0, 10h
		mov	byte_2A8D2, 0Eh

loc_1808B:				; CODE XREF: sub_18044:loc_18067j
					; sub_18044+51j
					; DATA XREF: ...
		call	sub_1802F	; jumptable 00018067 case 36
		leave
		retn
; ---------------------------------------------------------------------------

loc_18090:				; CODE XREF: sub_18044:loc_18067j
					; DATA XREF: seg003:4623o
		mov	byte_2A8D2, 7	; jumptable 00018067 case 34
		jmp	short loc_1808B	; jumptable 00018067 case 36
; ---------------------------------------------------------------------------

loc_18097:				; CODE XREF: sub_18044:loc_18067j
					; DATA XREF: seg003:4623o
		push	word ptr dword_2A8C6 ; jumptable 00018067 case 48
		push	word ptr dword_2A8C6+2
		call	sub_C696
		mov	byte_25592, 0Fh

locret_180A9:				; CODE XREF: sub_18044+21j
		leave			; default
		retn
sub_18044	endp

; ---------------------------------------------------------------------------
word_180AB	dw    20h,   22h,   24h,   30h ; DATA XREF: sub_18044+11o
					; value	table for switch statement
		dw offset loc_1806B	; jump table for switch	statement
		dw offset loc_18090
		dw offset loc_1808B
		dw offset loc_18097

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_180BB	proc near
		push	bp
		mov	bp, sp
		mov	word_231F2, 10h
		call	sub_18044
		cmp	word_2671A, 10h
		jl	short loc_18126
		cmp	word_2671A, 10h
		jz	short loc_180FF
		cmp	byte_26718, 18h
		jb	short loc_18126
		cmp	word_2671A, 30h	; '0'
		jge	short loc_18106
		cmp	word_2671A, 18h
		jnz	short loc_180F1
		push	8
		call	sub_138B2

loc_180F1:				; CODE XREF: sub_180BB+2Dj
		cmp	byte_266CC, 0
		jz	short loc_180FF
		mov	byte_26718, 82h	; '‚'
		jmp	short loc_18126
; ---------------------------------------------------------------------------

loc_180FF:				; CODE XREF: sub_180BB+18j
					; sub_180BB+3Bj
		mov	byte_26718, 81h	; ''
		jmp	short loc_18126
; ---------------------------------------------------------------------------

loc_18106:				; CODE XREF: sub_180BB+26j
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_18116
		mov	byte_26718, 80h	; '€'
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18116:				; CODE XREF: sub_180BB+50j
					; sub_1C2E5:loc_1C46Fj
					; DATA XREF: ...
		cmp	word_2671A, 80h	; '€'
		jge	short loc_18122
		mov	al, 2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18122:				; CODE XREF: sub_180BB+61j
		mov	al, 3
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18126:				; CODE XREF: sub_180BB+11j
					; sub_180BB+1Fj ...
		mov	al, 0
		pop	bp
		retn
sub_180BB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1812A	proc near
		push	bp
		mov	bp, sp
		mov	word_231F2, 0
		call	sub_18044
		mov	bx, word_2671A
		sub	bx, 10h
		cmp	bx, 20h	; ' '
		ja	short loc_18184
		add	bx, bx
		jmp	cs:off_181DC[bx]

loc_18149:				; DATA XREF: seg003:4770o
		mov	byte_26718, 0
		mov	ax, word_259EA
		mov	word ptr dword_2670A, ax
		mov	ax, word_259EC
		mov	word ptr dword_2670A+2,	ax
		jmp	short loc_18184
; ---------------------------------------------------------------------------

loc_1815C:				; CODE XREF: sub_1812A+1Aj
					; DATA XREF: seg003:476Co ...
		mov	byte_26718, 87h	; '‡'
		jmp	short loc_18184
; ---------------------------------------------------------------------------

loc_18163:				; CODE XREF: sub_1812A+1Aj
					; DATA XREF: seg003:4768o ...
		mov	byte_26718, 86h	; '†'
		jmp	short loc_18184
; ---------------------------------------------------------------------------

loc_1816A:				; CODE XREF: sub_1812A+1Aj
					; DATA XREF: seg003:4764o ...
		mov	byte_26718, 85h	; '…'
		jmp	short loc_18184
; ---------------------------------------------------------------------------

loc_18171:				; CODE XREF: sub_1812A+1Aj
					; DATA XREF: seg003:4760o ...
		mov	byte_26718, 84h	; '„'
		jmp	short loc_18184
; ---------------------------------------------------------------------------

loc_18178:				; CODE XREF: sub_1812A+1Aj
					; DATA XREF: seg003:475Co ...
		mov	byte_26718, 83h	; 'ƒ'
		jmp	short loc_18184
; ---------------------------------------------------------------------------

loc_1817F:				; CODE XREF: sub_1812A+1Aj
					; DATA XREF: seg003:off_181DCo	...
		mov	byte_26718, 81h	; ''

loc_18184:				; CODE XREF: sub_1812A+16j
					; sub_1812A+1Aj ...
		cmp	word_2671A, 30h	; '0'
		jge	short loc_1818D
		jmp	short loc_181D7
; ---------------------------------------------------------------------------

loc_1818D:				; CODE XREF: sub_1812A+5Fj
		cmp	word_2671A, 40h	; '@'
		jge	short loc_181B7
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_181A2
		push	8
		call	sub_138B2

loc_181A2:				; CODE XREF: sub_1812A+6Fj
		cmp	byte_266CC, 0
		jz	short loc_181B0
		mov	byte_26718, 82h	; '‚'
		jmp	short loc_181D7
; ---------------------------------------------------------------------------

loc_181B0:				; CODE XREF: sub_1812A+7Dj
		mov	byte_26718, 81h	; ''
		jmp	short loc_181D7
; ---------------------------------------------------------------------------

loc_181B7:				; CODE XREF: sub_1812A+68j
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_181C7
		mov	byte_26718, 80h	; '€'
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_181C7:				; CODE XREF: sub_1812A+92j
		cmp	word_2671A, 90h	; ''
		jge	short loc_181D3
		mov	al, 2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_181D3:				; CODE XREF: sub_1812A+A3j
		mov	al, 3
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_181D7:				; CODE XREF: sub_1812A+61j
					; sub_1812A+84j ...
		mov	al, 0
		pop	bp
		retn
sub_1812A	endp

; ---------------------------------------------------------------------------
		db 0
off_181DC	dw offset loc_1817F	; DATA XREF: sub_1812A+1Ar
		dw offset loc_18184
		dw offset loc_18184
		dw offset loc_18184
		dw offset loc_18184
		dw offset loc_18184
		dw offset loc_18184
		dw offset loc_18184
		dw offset loc_18178
		dw offset loc_18184
		dw offset loc_18171
		dw offset loc_18184
		dw offset loc_1816A
		dw offset loc_18184
		dw offset loc_18163
		dw offset loc_18184
		dw offset loc_1815C
		dw offset loc_18184
		dw offset loc_18149
		dw offset loc_18184
		dw offset loc_18184
		dw offset loc_18184
		dw offset loc_1815C
		dw offset loc_18184
		dw offset loc_18163
		dw offset loc_18184
		dw offset loc_1816A
		dw offset loc_18184
		dw offset loc_18171
		dw offset loc_18184
		dw offset loc_18178
		dw offset loc_18184
		dw offset loc_1817F

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1821E	proc near
		push	bp
		mov	bp, sp
		mov	word_231F2, 0FFB0h
		call	sub_18044
		mov	bx, word_2671A
		sub	bx, 10h
		cmp	bx, 20h	; ' '
		ja	short loc_18278
		add	bx, bx
		jmp	cs:off_182D2[bx]

loc_1823D:				; DATA XREF: seg003:4866o
		mov	byte_26718, 0
		mov	ax, word_259EA
		mov	word ptr dword_2670A, ax
		mov	ax, word_259EC
		mov	word ptr dword_2670A+2,	ax
		jmp	short loc_18278
; ---------------------------------------------------------------------------

loc_18250:				; CODE XREF: sub_1821E+1Aj
					; DATA XREF: seg003:4862o ...
		mov	byte_26718, 87h	; '‡'
		jmp	short loc_18278
; ---------------------------------------------------------------------------

loc_18257:				; CODE XREF: sub_1821E+1Aj
					; DATA XREF: seg003:485Eo ...
		mov	byte_26718, 86h	; '†'
		jmp	short loc_18278
; ---------------------------------------------------------------------------

loc_1825E:				; CODE XREF: sub_1821E+1Aj
					; DATA XREF: seg003:485Ao ...
		mov	byte_26718, 85h	; '…'
		jmp	short loc_18278
; ---------------------------------------------------------------------------

loc_18265:				; CODE XREF: sub_1821E+1Aj
					; DATA XREF: seg003:4856o ...
		mov	byte_26718, 84h	; '„'
		jmp	short loc_18278
; ---------------------------------------------------------------------------

loc_1826C:				; CODE XREF: sub_1821E+1Aj
					; DATA XREF: seg003:4852o ...
		mov	byte_26718, 83h	; 'ƒ'
		jmp	short loc_18278
; ---------------------------------------------------------------------------

loc_18273:				; CODE XREF: sub_1821E+1Aj
					; DATA XREF: seg003:off_182D2o	...
		mov	byte_26718, 81h	; ''

loc_18278:				; CODE XREF: sub_1821E+16j
					; sub_1821E+1Aj ...
		cmp	word_2671A, 30h	; '0'
		jge	short loc_18281
		jmp	short loc_182CD
; ---------------------------------------------------------------------------

loc_18281:				; CODE XREF: sub_1821E+5Fj
		cmp	word_2671A, 80h	; '€'
		jge	short loc_182AC
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_18297
		push	8
		call	sub_138B2

loc_18297:				; CODE XREF: sub_1821E+70j
		cmp	byte_266CC, 0
		jz	short loc_182A5
		mov	byte_26718, 82h	; '‚'
		jmp	short loc_182CD
; ---------------------------------------------------------------------------

loc_182A5:				; CODE XREF: sub_1821E+7Ej
		mov	byte_26718, 81h	; ''
		jmp	short loc_182CD
; ---------------------------------------------------------------------------

loc_182AC:				; CODE XREF: sub_1821E+69j
		cmp	word_2671A, 80h	; '€'
		jnz	short loc_182BD
		mov	byte_26718, 80h	; '€'
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_182BD:				; CODE XREF: sub_1821E+94j
		cmp	word_2671A, 0C0h ; 'À'
		jge	short loc_182C9
		mov	al, 2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_182C9:				; CODE XREF: sub_1821E+A5j
		mov	al, 3
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_182CD:				; CODE XREF: sub_1821E+61j
					; sub_1821E+85j ...
		mov	al, 0
		pop	bp
		retn
sub_1821E	endp

; ---------------------------------------------------------------------------
		db 0
off_182D2	dw offset loc_18273	; DATA XREF: sub_1821E+1Ar
		dw offset loc_18278
		dw offset loc_18278
		dw offset loc_18278
		dw offset loc_18278
		dw offset loc_18278
		dw offset loc_18278
		dw offset loc_18278
		dw offset loc_1826C
		dw offset loc_18278
		dw offset loc_18265
		dw offset loc_18278
		dw offset loc_1825E
		dw offset loc_18278
		dw offset loc_18257
		dw offset loc_18278
		dw offset loc_18250
		dw offset loc_18278
		dw offset loc_1823D
		dw offset loc_18278
		dw offset loc_18278
		dw offset loc_18278
		dw offset loc_18250
		dw offset loc_18278
		dw offset loc_18257
		dw offset loc_18278
		dw offset loc_1825E
		dw offset loc_18278
		dw offset loc_18265
		dw offset loc_18278
		dw offset loc_1826C
		dw offset loc_18278
		dw offset loc_18273

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18314	proc near		; CODE XREF: sub_186EB:loc_187F2p
		push	bp
		mov	bp, sp
		call	word_259E8
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_1832E
		cmp	ax, 2
		jz	short loc_1834D
		cmp	ax, 3
		jz	short loc_1837D
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1832E:				; CODE XREF: sub_18314+Cj
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 8
		mov	byte_266EE, 20h	; ' '
		call	sub_13D52
		mov	byte_266ED, al
		push	1
		call	sub_13D60
		mov	byte_2D02D, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1834D:				; CODE XREF: sub_18314+11j
		cmp	byte_266CD, 0
		jnz	short loc_18388
		call	word_2D000
		mov	al, byte_266EE
		add	al, 3
		mov	byte_266EE, al
		cmp	byte_2D02D, 0
		jz	short loc_1836B
		mov	al, 4
		jmp	short loc_1836D
; ---------------------------------------------------------------------------

loc_1836B:				; CODE XREF: sub_18314+51j
		mov	al, 0FCh ; 'ü'

loc_1836D:				; CODE XREF: sub_18314+55j
		add	al, byte_266ED
		mov	byte_266ED, al
		push	3
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1837D:				; CODE XREF: sub_18314+16j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_18388:				; CODE XREF: sub_18314+3Ej
		pop	bp
		retn
sub_18314	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1838A	proc near		; CODE XREF: sub_186EB:loc_187F7p

var_2		= word ptr -2

		enter	2, 0
		call	word_259E8
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_183A7
		cmp	ax, 2
		jz	short loc_18409
		cmp	ax, 3
		jz	loc_18451
		leave
		retn
; ---------------------------------------------------------------------------

loc_183A7:				; CODE XREF: sub_1838A+Dj
		push	0Fh
		call	sub_138B2
		mov	byte_266E2, 2
		mov	byte_266E3, 3Bh	; ';'
		mov	byte_266ED, 0
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		mov	byte_266F2, 81h	; ''
		mov	byte_266EE, 28h	; '('
		mov	byte_2CFF7, 2
		mov	byte_2CFF8, 0E0h ; 'à'
		call	word_2D004
		call	sub_1CFB5
		mov	byte_2CFF8, 20h	; ' '
		call	sub_1CFB5
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8
		mov	byte_266ED, al
		mov	byte_266F0, 42h	; 'B'
		leave
		retn
; ---------------------------------------------------------------------------

loc_18409:				; CODE XREF: sub_1838A+12j
		mov	ax, word_2671A
		and	ax, 7
		mov	[bp+var_2], ax
		or	ax, ax
		jnz	short loc_1841E
		mov	al, byte_266F0
		add	al, 0F8h ; 'ø'
		mov	byte_266F0, al

loc_1841E:				; CODE XREF: sub_1838A+8Aj
		mov	byte_266E2, 2
		mov	byte_266E3, 4Ch	; 'L'
		mov	ax, [bp+var_2]
		imul	ax, 0Ch
		add	al, 20h	; ' '
		mov	byte_266EE, al
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 2
		call	word_2D000
		cmp	byte_266CD, 0
		jnz	short locret_1845C
		push	3
		call	sub_138B2
		leave
		retn
; ---------------------------------------------------------------------------

loc_18451:				; CODE XREF: sub_1838A+17j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

locret_1845C:				; CODE XREF: sub_1838A+BCj
		leave
		retn
sub_1838A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1845E	proc near		; CODE XREF: sub_186EB:loc_187EDp
		push	bp
		mov	bp, sp
		call	word_259E8
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_18473
		cmp	ax, 2
		jz	short loc_1849F
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18473:				; CODE XREF: sub_1845E+Cj
		mov	byte_266E2, 5
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 28h	; '('
		mov	byte_266EE, 10h
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D000
		push	0Fh
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1849F:				; CODE XREF: sub_1845E+11j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		pop	bp
		retn
sub_1845E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_184AC	proc near		; CODE XREF: sub_186EB:loc_187E8p
		push	bp
		mov	bp, sp
		call	word_259E8
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_184C8
		cmp	ax, 2
		jz	short loc_184D9
		cmp	ax, 3
		jz	loc_18549
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_184C8:				; CODE XREF: sub_184AC+Cj
		mov	byte_266F2, 81h	; ''
		mov	byte_266EC, 0
		mov	byte_2CFF7, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_184D9:				; CODE XREF: sub_184AC+11j
		cmp	byte_266CC, 0
		jz	short loc_18554
		mov	byte_266E2, 2
		mov	byte_266E3, 3Ah	; ':'
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	200h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE60h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266ED, 0
		mov	byte_2CFF8, 40h	; '@'
		call	word_2D002
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		mov	byte_266ED, 80h	; '€'
		mov	byte_2CFF8, 0C0h ; 'À'
		call	word_2D002
		push	9
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18549:				; CODE XREF: sub_184AC+16j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_18554:				; CODE XREF: sub_184AC+32j
		pop	bp
		retn
sub_184AC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18556	proc near		; CODE XREF: sub_186EB+1D5p
		push	bp
		mov	bp, sp
		call	word_259E8
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_18570
		cmp	ax, 2
		jz	short loc_18580
		cmp	ax, 3
		jz	short loc_185D7
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18570:				; CODE XREF: sub_18556+Cj
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		call	word_2D004
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18580:				; CODE XREF: sub_18556+11j
		cmp	byte_266CE, 0
		jnz	short loc_185E2
		push	1
		call	sub_13D60
		mov	byte_266E2, al
		mov	byte_266E3, 39h	; '9'
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	200h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE60h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D000
		push	3
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_185D7:				; CODE XREF: sub_18556+16j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_185E2:				; CODE XREF: sub_18556+2Fj
		pop	bp
		retn
sub_18556	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_185E4	proc near		; CODE XREF: sub_186EB:loc_188F6p
		push	bp
		mov	bp, sp
		cmp	byte_266CE, 0
		jnz	short loc_18653
		mov	al, byte_2671E
		mov	byte_266ED, al
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 10h
		mov	ax, word_2671A
		mov	bx, 100h
		cwd
		idiv	bx
		add	al, 20h	; ' '
		mov	byte_266EE, al
		call	word_2D000
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266E2, 2
		mov	al, byte_266ED
		neg	al
		add	al, al
		mov	byte_266ED, al
		mov	byte_266EF, 4
		mov	al, byte_266EE
		add	al, 10h
		mov	byte_266EE, al
		call	word_2D000
		mov	ax, word_2671A
		mov	bx, 400h
		cwd
		idiv	bx
		cmp	dx, 200h
		jge	short loc_1864B
		mov	al, byte_2671E
		add	al, 3
		jmp	short loc_18650
; ---------------------------------------------------------------------------

loc_1864B:				; CODE XREF: sub_185E4+5Ej
		mov	al, byte_2671E
		add	al, 0FDh ; 'ý'

loc_18650:				; CODE XREF: sub_185E4+65j
		mov	byte_2671E, al

loc_18653:				; CODE XREF: sub_185E4+8j
		pop	bp
		retn
sub_185E4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18655	proc near		; CODE XREF: sub_186EB+180p
					; sub_186EB+216p
		push	bp
		mov	bp, sp
		cmp	byte_266CE, 0
		jnz	short loc_18682
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266E2, 2
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266EE, 70h	; 'p'
		call	word_2D000

loc_18682:				; CODE XREF: sub_18655+8j
		pop	bp
		retn
sub_18655	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18684	proc near		; CODE XREF: sub_186EB+1A7p

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		call	sub_1E692
		push	[bp+arg_2]
		call	sub_15C7C
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671D, 0
		mov	byte_2671F, 0
		mov	ax, word_26720
		mov	word_26716, ax
		mov	ax, [bp+arg_0]
		mov	word_26720, ax
		mov	byte_259EE, 0
		pop	bp
		retn	4
sub_18684	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_186B9	proc near		; CODE XREF: sub_186EB:loc_1876Bp
					; sub_186EB:loc_18797p	...
		push	bp
		mov	bp, sp
		cmp	byte_259EF, 0
		jz	short loc_186D0
		push	large 3000300h
		push	0Ah
		call	sub_1E5D8
		jmp	short loc_186E3
; ---------------------------------------------------------------------------

loc_186D0:				; CODE XREF: sub_186B9+8j
		cmp	byte_26718, 82h	; '‚'
		ja	short loc_186E3
		cmp	byte_26718, 0
		jz	short loc_186E3
		call	sub_1E64E
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_186E3:				; CODE XREF: sub_186B9+15j
					; sub_186B9+1Cj ...
		inc	word_2671A
		mov	al, 0
		pop	bp
		retn
sub_186B9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_186EB	proc far

var_4		= word ptr -4
var_1		= byte ptr -1

		enter	4, 0
		cmp	byte_256A8, 0
		jz	short loc_186FB
		mov	byte_259EF, 20h	; ' '

loc_186FB:				; CODE XREF: sub_186EB+9j
		cmp	byte_259EF, 0
		jz	short loc_18706
		dec	byte_259EF

loc_18706:				; CODE XREF: sub_186EB+15j
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266E2, 1
		mov	al, byte_26719
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 7
		ja	loc_1899C
		add	bx, bx
		jmp	cs:off_189DE[bx]

loc_1872F:				; DATA XREF: seg003:off_189DEo
		cmp	word_2671A, 0
		jnz	short loc_1876B
		mov	word ptr dword_25986+2,	seg seg001
		mov	word ptr dword_25986, 11C0h
		mov	word_26700, 0
		mov	word_259E8, 462Bh
		mov	byte_259EF, 0
		mov	word_26716, 24B8h
		mov	word_26720, 0E74h
		mov	ax, word ptr dword_2670A
		mov	word_259EA, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_259EC, ax

loc_1876B:				; CODE XREF: sub_186EB+49j
		call	sub_186B9
		cmp	word_2671A, 80h	; '€'
		jle	loc_189A1
		inc	byte_26719
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	byte_2CDCA, 0Fh
		mov	word_255AC, 7E89h
		jmp	loc_189A1
; ---------------------------------------------------------------------------

loc_18797:				; CODE XREF: sub_186EB+3Fj
					; DATA XREF: seg003:4F50o
		call	sub_186B9
		cmp	word_2671A, 40h	; '@'
		jl	loc_189A1
		inc	byte_26719
		mov	byte_2671D, 0
		mov	byte_2671F, 2
		mov	word_2671A, 0
		mov	word_26712, 0
		mov	byte_259EE, 0
		jmp	loc_189A1
; ---------------------------------------------------------------------------

loc_187C5:				; CODE XREF: sub_186EB+3Fj
					; DATA XREF: seg003:4F52o
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp+var_4], ax
		mov	cx, 9		; switch 9 cases
		mov	bx, offset word_189BA

loc_187D3:				; CODE XREF: sub_186EB+F3j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_4]
		jz	short loc_187E2
		add	bx, 2
		loop	loc_187D3
		jmp	short loc_18856	; default
; ---------------------------------------------------------------------------

loc_187E2:				; CODE XREF: sub_186EB+EEj
		jmp	word ptr cs:[bx+12h] ; switch jump
; ---------------------------------------------------------------------------
		jmp	short loc_187F2	; jumptable 000187E2 cases 0,6
; ---------------------------------------------------------------------------

loc_187E8:				; CODE XREF: sub_186EB:loc_187E2j
					; DATA XREF: seg003:4F3Co
		call	sub_184AC	; jumptable 000187E2 case 3
		jmp	short loc_18856	; default
; ---------------------------------------------------------------------------

loc_187ED:				; CODE XREF: sub_186EB:loc_187E2j
					; DATA XREF: seg003:4F3Co
		call	sub_1845E	; jumptable 000187E2 cases 1,4,5
		jmp	short loc_18856	; default
; ---------------------------------------------------------------------------

loc_187F2:				; CODE XREF: sub_186EB:loc_187E2j
					; sub_186EB+FBj
					; DATA XREF: ...
		call	sub_18314	; jumptable 000187E2 cases 0,6
		jmp	short loc_18856	; default
; ---------------------------------------------------------------------------

loc_187F7:				; CODE XREF: sub_186EB:loc_187E2j
					; DATA XREF: seg003:4F3Co
		call	sub_1838A	; jumptable 000187E2 cases 2,7
		jmp	short loc_18856	; default
; ---------------------------------------------------------------------------

loc_187FC:				; CODE XREF: sub_186EB:loc_187E2j
					; DATA XREF: seg003:4F3Co
		cmp	word_2671A, 10h	; jumptable 000187E2 case 255
		jle	short loc_18856	; default
		push	3
		call	sub_13D60
		or	ax, ax
		jnz	short loc_18814
		mov	word_259E8, 462Bh
		jmp	short loc_18844
; ---------------------------------------------------------------------------

loc_18814:				; CODE XREF: sub_186EB+11Fj
		mov	word_259E8, 469Ah

loc_1881A:				; CODE XREF: sub_186EB+13Dj
		push	5
		call	sub_13D76
		mov	[bp+var_1], al
		mov	al, byte_2671F
		cmp	al, [bp+var_1]
		jz	short loc_1881A
		mov	al, [bp+var_1]
		mov	byte_2671F, al
		mov	ah, 0
		shl	ax, 6
		shl	ax, 4
		add	ax, 400h
		mov	word_259EA, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_259EC, ax

loc_18844:				; CODE XREF: sub_186EB+127j
		mov	word_2671A, 0
		inc	byte_259EE
		mov	al, byte_259EE
		and	al, 7
		mov	byte_2671D, al

loc_18856:				; CODE XREF: sub_186EB+F5j
					; sub_186EB+100j ...
		cmp	byte_259EE, 20h	; ' ' ; default
		jb	short loc_1886E
		cmp	byte_2671D, 0FFh
		jz	short loc_1886E
		cmp	word_2671A, 18h
		jle	short loc_1886E
		call	sub_18655

loc_1886E:				; CODE XREF: sub_186EB+170j
					; sub_186EB+177j ...
		cmp	byte_259EE, 24h	; '$'
		jnb	short loc_18883
		call	sub_186B9
		or	al, al
		jz	loc_189A1
		push	64h ; 'd'
		call	sub_19FD8

loc_18883:				; CODE XREF: sub_186EB+188j
		cmp	byte_2CFFA, 14h
		jnb	short loc_1888F
		mov	byte_2CFFA, 14h

loc_1888F:				; CODE XREF: sub_186EB+19Dj
		push	large 0
		call	sub_18684
		mov	word_259EA, 0C00h
		jmp	loc_189A1
; ---------------------------------------------------------------------------

loc_1889E:				; CODE XREF: sub_186EB+3Fj
					; DATA XREF: seg003:4F54o
		call	sub_186B9
		cmp	word_2671A, 40h	; '@'
		jl	loc_189A1
		inc	byte_26719
		mov	word_259E8, 478Eh

loc_188B4:				; CODE XREF: sub_186EB+209j
		mov	word_2671A, 0
		jmp	loc_189A1
; ---------------------------------------------------------------------------

loc_188BD:				; CODE XREF: sub_186EB+3Fj
					; DATA XREF: seg003:4F56o
		call	sub_186B9
		call	sub_18556
		cmp	word_2671A, 0
		jnz	loc_189A1
		push	3
		call	sub_15C7C
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_26718, 81h	; ''
		jmp	loc_189A1
; ---------------------------------------------------------------------------

loc_188E3:				; CODE XREF: sub_186EB+3Fj
					; DATA XREF: seg003:4F58o
		call	sub_186B9
		cmp	word_2671A, 80h	; '€'
		jl	loc_189A1
		inc	byte_26719
		jmp	short loc_188B4
; ---------------------------------------------------------------------------

loc_188F6:				; CODE XREF: sub_186EB+3Fj
					; DATA XREF: seg003:4F5Ao
		call	sub_185E4
		cmp	word_2671A, 0BB8h
		jl	short loc_18904
		call	sub_18655

loc_18904:				; CODE XREF: sub_186EB+214j
		call	sub_186B9
		or	al, al
		jnz	short loc_18915
		cmp	word_2671A, 0FA0h
		jl	loc_189A1

loc_18915:				; CODE XREF: sub_186EB+21Ej
		push	1
		call	sub_15C7C
		inc	byte_26719
		cmp	word_2671A, 0FA0h
		jge	short loc_1892D
		mov	byte_2671F, 1
		jmp	short loc_18932
; ---------------------------------------------------------------------------

loc_1892D:				; CODE XREF: sub_186EB+239j
		mov	byte_2671F, 0

loc_18932:				; CODE XREF: sub_186EB+240j
		mov	word_2671A, 0
		mov	byte_2671D, 0
		mov	word_216E4, 64h	; 'd'
		mov	byte_266D3, 1
		jmp	short loc_189A1
; ---------------------------------------------------------------------------

loc_1894A:				; CODE XREF: sub_186EB+3Fj
					; DATA XREF: seg003:4F5Co
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_1895A
		push	4
		call	sub_15C7C

loc_1895A:				; CODE XREF: sub_186EB+268j
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_189A1
		push	2
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_1897E
		push	0C8h ; 'È'
		call	sub_19FD8

loc_1897E:				; CODE XREF: sub_186EB+28Bj
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_266D3, 1
		mov	byte_259A2, 0FFh
		jmp	short loc_189A1
; ---------------------------------------------------------------------------

loc_1899C:				; CODE XREF: sub_186EB+39j
		call	sub_1E743
		leave
		retf
; ---------------------------------------------------------------------------

loc_189A1:				; CODE XREF: sub_186EB+89j
					; sub_186EB+A9j ...
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax
		push	word_26716
		push	24B8h
		call	sub_19F16
		leave
		retf
sub_186EB	endp

; ---------------------------------------------------------------------------
		db 0
word_189BA	dw	0,     1,     2,     3 ; DATA XREF: sub_186EB+E5o
		dw	4,     5,     6,     7 ; value table for switch	statement
		dw   0FFh
		dw offset loc_187F2	; jump table for switch	statement
		dw offset loc_187ED
		dw offset loc_187F7
		dw offset loc_187E8
		dw offset loc_187ED
		dw offset loc_187ED
		dw offset loc_187F2
		dw offset loc_187F7
		dw offset loc_187FC
off_189DE	dw offset loc_1872F	; DATA XREF: sub_186EB+3Fr
		dw offset loc_18797
		dw offset loc_187C5
		dw offset loc_1889E
		dw offset loc_188BD
		dw offset loc_188E3
		dw offset loc_188F6
		dw offset loc_1894A

; =============== S U B	R O U T	I N E =======================================


sub_189EE	proc near		; CODE XREF: sub_13DAA+40p
		mov	bx, sp
		mov	dx, ss:[bx+2]
		mov	bx, ss:[bx+4]
		push	si
		mov	si, 1EB6h
		mov	cx, 3

loc_189FF:				; CODE XREF: sub_189EE+1Dj
		mov	ax, dx
		xor	dx, dx
		div	word ptr [si]
		mov	[bx], al
		dec	bx
		add	si, 2
		loop	loc_189FF
		mov	[bx], dl
		pop	si
		retn	4
sub_189EE	endp

; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18A14	proc near		; CODE XREF: sub_18BE6+53p
					; sub_18C76+51p ...

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_18A6E
; ---------------------------------------------------------------------------

loc_18A20:				; CODE XREF: sub_18A14+5Dj
		cmp	byte ptr [si], 0
		jnz	short loc_18A6A
		mov	byte ptr [si], 1
		mov	ax, word ptr dword_2670A
		add	ax, [bp+arg_2]
		mov	[si+2],	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		mov	[si+4],	ax
		mov	ax, word ptr dword_2670A
		add	ax, [bp+arg_2]
		mov	[si+6],	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		mov	[si+8],	ax
		push	ds
		lea	ax, [si+0Ah]
		push	ax
		push	ds
		lea	ax, [si+0Ch]
		push	ax
		push	[bp+arg_0]
		push	100h
		call	sub_13117
		push	5
		call	sub_138B2
		jmp	short loc_18A73
; ---------------------------------------------------------------------------

loc_18A6A:				; CODE XREF: sub_18A14+Fj
		inc	di
		add	si, 1Ah

loc_18A6E:				; CODE XREF: sub_18A14+Aj
		cmp	di, 6
		jl	short loc_18A20

loc_18A73:				; CODE XREF: sub_18A14+54j
		pop	di
		pop	si
		pop	bp
		retn	4
sub_18A14	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18A79	proc near		; CODE XREF: sub_18BE6+7Cp
					; sub_18C76+7Ap ...

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		mov	si, 0B204h
		xor	di, di
		mov	[bp+var_2], 0
		jmp	loc_18B51
; ---------------------------------------------------------------------------

loc_18A8C:				; CODE XREF: sub_18A79+DBj
		cmp	byte ptr [si], 0
		jnz	short loc_18A94
		inc	[bp+var_2]

loc_18A94:				; CODE XREF: sub_18A79+16j
		cmp	byte ptr [si], 1
		jnz	loc_18B1D
		cmp	word ptr [si+2], 1800h
		jge	short loc_18AC4
		cmp	word ptr [si+4], 1700h
		jge	short loc_18AC4
		cmp	word ptr [si+2], 0
		jle	short loc_18AC4
		cmp	word ptr [si+4], 0
		jle	short loc_18AC4
		mov	ax, [si+0Ah]
		add	[si+2],	ax
		mov	ax, [si+0Ch]
		add	[si+4],	ax
		jmp	loc_18B4D
; ---------------------------------------------------------------------------

loc_18AC4:				; CODE XREF: sub_18A79+27j
					; sub_18A79+2Ej ...
		mov	ax, [si+2]
		sub	ax, [si+0Ah]
		mov	word ptr dword_266E4, ax
		mov	ax, [si+4]
		sub	ax, [si+0Ch]
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266F2, 82h	; '‚'
		mov	byte_2CFF7, 1
		mov	[bp+var_4], 0
		mov	byte_266EE, 20h	; ' '
		jmp	short loc_18AFA
; ---------------------------------------------------------------------------

loc_18AEC:				; CODE XREF: sub_18A79+85j
		call	sub_1CFA2
		inc	[bp+var_4]
		mov	al, byte_266EE
		add	al, 6
		mov	byte_266EE, al

loc_18AFA:				; CODE XREF: sub_18A79+71j
		cmp	[bp+var_4], 3
		jl	short loc_18AEC
		inc	byte ptr [si]
		push	6
		call	sub_138B2
		mov	byte_25592, 9
		push	word ptr dword_266E4
		push	word ptr dword_266E4+2
		call	sub_C64A
		jmp	short loc_18B4D
; ---------------------------------------------------------------------------

loc_18B1D:				; CODE XREF: sub_18A79+1Ej
		cmp	byte ptr [si], 2
		jnz	short loc_18B4D
		cmp	word ptr [si+6], 1800h
		jge	short loc_18B4A
		cmp	word ptr [si+8], 1700h
		jge	short loc_18B4A
		cmp	word ptr [si+6], 0
		jle	short loc_18B4A
		cmp	word ptr [si+8], 0
		jle	short loc_18B4A
		mov	ax, [si+0Ah]
		add	[si+6],	ax
		mov	ax, [si+0Ch]
		add	[si+8],	ax
		jmp	short loc_18B4D
; ---------------------------------------------------------------------------

loc_18B4A:				; CODE XREF: sub_18A79+AEj
					; sub_18A79+B5j ...
		mov	byte ptr [si], 0

loc_18B4D:				; CODE XREF: sub_18A79+48j
					; sub_18A79+A2j ...
		inc	di
		add	si, 1Ah

loc_18B51:				; CODE XREF: sub_18A79+10j
		cmp	di, 6
		jl	loc_18A8C
		cmp	[bp+var_2], 6
		jnz	short loc_18B62
		mov	al, 1
		jmp	short loc_18B64
; ---------------------------------------------------------------------------

loc_18B62:				; CODE XREF: sub_18A79+E3j
		mov	al, 0

loc_18B64:				; CODE XREF: sub_18A79+E7j
		pop	di
		pop	si
		leave
		retn
sub_18A79	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18B68	proc near		; CODE XREF: seg003:loc_19279p
					; seg003:loc_19387p
		push	bp
		mov	bp, sp
		push	large 0C000400h
		mov	al, byte_2671E
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+566h]
		call	sub_13320
		mov	word ptr dword_2670A, ax
		push	large 5B00140h
		mov	al, byte_2671E
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4E6h]
		call	sub_13320
		mov	word ptr dword_2670A+2,	ax
		inc	byte_2671E
		pop	bp
		retn
sub_18B68	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18BA7	proc near		; CODE XREF: sub_18DB6+3p
		push	bp
		mov	bp, sp
		push	large 0C000400h
		mov	al, byte_2671E
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+566h]
		call	sub_13320
		mov	word ptr dword_2670A, ax
		push	large 5B00140h
		mov	al, byte_2671E
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4E6h]
		call	sub_13320
		mov	word ptr dword_2670A+2,	ax
		dec	byte_2671E
		pop	bp
		retn
sub_18BA7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18BE6	proc near		; CODE XREF: seg003:loc_192FCp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 10h
		jnz	short loc_18BF7
		mov	byte_26718, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18BF7:				; CODE XREF: sub_18BE6+8j
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_18C1F
		mov	ax, word ptr dword_2670A
		add	ax, 0FF40h
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		push	ax
		call	sub_C696
		mov	byte_25592, 0Fh
		push	8
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18C1F:				; CODE XREF: sub_18BE6+16j
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_18C3E
		mov	byte_26718, 0
		push	large 0FF40000Fh
		call	sub_13D60
		mov	dl, 18h
		sub	dl, al
		push	dx
		call	sub_18A14
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18C3E:				; CODE XREF: sub_18BE6+3Ej
		cmp	word_2671A, 40h	; '@'
		jle	short loc_18C74
		mov	byte_266E2, 2
		mov	byte_266E3, 37h	; '7'
		mov	byte_266ED, 0
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 10h
		call	word_2D004
		call	sub_18A79
		or	al, al
		jz	short loc_18C74
		mov	word_2671A, 0
		mov	byte_2671D, 0

loc_18C74:				; CODE XREF: sub_18BE6+5Dj
					; sub_18BE6+81j
		pop	bp
		retn
sub_18BE6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18C76	proc near		; CODE XREF: seg003:loc_19301p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 10h
		jnz	short loc_18C87
		mov	byte_26718, 9
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18C87:				; CODE XREF: sub_18C76+8j
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_18CAF
		mov	ax, word ptr dword_2670A
		add	ax, 0C0h ; 'À'
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		push	ax
		call	sub_C696
		mov	byte_25592, 0Fh
		push	8
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18CAF:				; CODE XREF: sub_18C76+16j
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_18CCC
		mov	byte_26718, 0
		push	large 0C0000Fh
		call	sub_13D60
		add	al, 68h	; 'h'
		push	ax
		call	sub_18A14
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18CCC:				; CODE XREF: sub_18C76+3Ej
		cmp	word_2671A, 40h	; '@'
		jle	short loc_18D02
		mov	byte_266E2, 2
		mov	byte_266E3, 37h	; '7'
		mov	byte_266ED, 0
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 10h
		call	word_2D004
		call	sub_18A79
		or	al, al
		jz	short loc_18D02
		mov	word_2671A, 0
		mov	byte_2671D, 0

loc_18D02:				; CODE XREF: sub_18C76+5Bj
					; sub_18C76+7Fj
		pop	bp
		retn
sub_18C76	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18D04	proc near		; CODE XREF: seg003:loc_19306p

var_1		= byte ptr -1

		enter	2, 0
		cmp	word_2671A, 10h
		jnz	short loc_18D16
		mov	byte_26718, 0Ah
		leave
		retn
; ---------------------------------------------------------------------------

loc_18D16:				; CODE XREF: sub_18D04+9j
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_18D51
		mov	ax, word ptr dword_2670A
		add	ax, 0C0h ; 'À'
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		push	ax
		call	sub_C696
		mov	ax, word ptr dword_2670A
		add	ax, 0FF40h
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		push	ax
		call	sub_C696
		mov	byte_25592, 0Fh
		push	8
		call	sub_138B2
		leave
		retn
; ---------------------------------------------------------------------------

loc_18D51:				; CODE XREF: sub_18D04+17j
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_18D7E
		mov	byte_26718, 0
		push	0Fh
		call	sub_13D60
		add	al, 68h	; 'h'
		mov	[bp+var_1], al
		push	0C0h ; 'À'
		push	word ptr [bp+var_1]
		call	sub_18A14
		push	0FF40h
		mov	al, 80h	; '€'
		sub	al, [bp+var_1]
		push	ax
		call	sub_18A14
		leave
		retn
; ---------------------------------------------------------------------------

loc_18D7E:				; CODE XREF: sub_18D04+52j
		cmp	word_2671A, 40h	; '@'
		jle	short locret_18DB4
		mov	byte_266E2, 2
		mov	byte_266E3, 37h	; '7'
		mov	byte_266ED, 0
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 8
		call	word_2D004
		call	sub_18A79
		or	al, al
		jz	short locret_18DB4
		mov	word_2671A, 0
		mov	byte_2671D, 0

locret_18DB4:				; CODE XREF: sub_18D04+7Fj
					; sub_18D04+A3j
		leave
		retn
sub_18D04	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18DB6	proc near		; CODE XREF: seg003:loc_19350p
		push	bp
		mov	bp, sp
		call	sub_18BA7
		cmp	byte_2671E, 80h	; '€'
		jbe	short loc_18DCA
		mov	byte_26718, 4
		jmp	short loc_18DCF
; ---------------------------------------------------------------------------

loc_18DCA:				; CODE XREF: sub_18DB6+Bj
		mov	byte_26718, 6

loc_18DCF:				; CODE XREF: sub_18DB6+12j
		mov	ax, word_266CA
		mov	bx, 39h	; '9'
		xor	dx, dx
		div	bx
		or	dx, dx
		jnz	short loc_18E41
		mov	byte_266E2, 2
		mov	byte_266E3, 37h	; '7'
		mov	eax, dword_2670A
		mov	dword_266E4, eax
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 10h
		mov	byte_266F2, 81h	; ''
		mov	byte_266EE, 30h	; '0'
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_2CFF7, 1
		test	byte_259F0, 1
		jz	short loc_18E19
		mov	al, 40h	; '@'
		jmp	short loc_18E1B
; ---------------------------------------------------------------------------

loc_18E19:				; CODE XREF: sub_18DB6+5Dj
		mov	al, 0C0h ; 'À'

loc_18E1B:				; CODE XREF: sub_18DB6+61j
		mov	byte_2CFF8, al
		call	word_2D004
		call	word_2D002
		mov	al, byte_2CFF8
		add	al, 80h	; '€'
		mov	byte_2CFF8, al
		mov	byte_266EE, 20h	; ' '
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D002
		inc	byte_259F0

loc_18E41:				; CODE XREF: sub_18DB6+25j
		pop	bp
		retn
sub_18DB6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18E43	proc near		; CODE XREF: seg003:loc_1940Ap
		push	bp
		mov	bp, sp
sub_18E43	endp ; sp-analysis failed

; START	OF FUNCTION CHUNK FOR sub_1CD6E

loc_18E46:				; CODE XREF: sub_1CD6E:loc_1CD8Fj
		cmp	word_2671A, 10h	; jumptable 0001CD8F case 17022
		jnz	short loc_18E54
		mov	byte_26718, 8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18E54:				; CODE XREF: sub_1CD6E-3F23j
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_18E7C
		mov	ax, word ptr dword_2670A
		add	ax, 0FF40h
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		push	ax
		call	sub_C696
		mov	byte_25592, 0Fh
		push	8
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18E7C:				; CODE XREF: sub_1CD6E-3F15j
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_18E92
		mov	byte_26718, 0
		push	0FF40h
		push	18h
		call	sub_18A14
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18E92:				; CODE XREF: sub_1CD6E-3EEDj
		cmp	word_2671A, 40h	; '@'
		jle	short loc_18EE5
		cmp	word_2671A, 50h	; 'P'
		jnz	short loc_18EA7
		push	0FF40h
		push	10h
		jmp	short loc_18EB3
; ---------------------------------------------------------------------------

loc_18EA7:				; CODE XREF: sub_1CD6E-3ED0j
		cmp	word_2671A, 60h	; '`'
		jnz	short loc_18EB6
		push	0FF40h
		push	8

loc_18EB3:				; CODE XREF: sub_1CD6E-3EC9j
		call	sub_18A14

loc_18EB6:				; CODE XREF: sub_1CD6E-3EC2j
		mov	byte_266E2, 2
		mov	byte_266E3, 37h	; '7'
		mov	byte_266ED, 0
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 0Ch
		call	word_2D004
		call	sub_18A79
		or	al, al
		jz	short loc_18EE5
		mov	word_2671A, 0
		mov	byte_2671D, 0

loc_18EE5:				; CODE XREF: sub_1CD6E-3ED7j
					; sub_1CD6E-3E96j
		pop	bp
		retn
; END OF FUNCTION CHUNK	FOR sub_1CD6E

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18EE7	proc near		; CODE XREF: seg003:loc_1940Fp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 10h
		jnz	short loc_18EF8
		mov	byte_26718, 9
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18EF8:				; CODE XREF: sub_18EE7+8j
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_18F20
		mov	ax, word ptr dword_2670A
		add	ax, 0C0h ; 'À'
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		push	ax
		call	sub_C696
		mov	byte_25592, 0Fh
		push	8
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18F20:				; CODE XREF: sub_18EE7+16j
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_18F36
		mov	byte_26718, 0
		push	0C0h ; 'À'
		push	68h ; 'h'
		call	sub_18A14
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18F36:				; CODE XREF: sub_18EE7+3Ej
		cmp	word_2671A, 40h	; '@'
		jle	short loc_18F89
		cmp	word_2671A, 50h	; 'P'
		jnz	short loc_18F4B
		push	0C0h ; 'À'
		push	70h ; 'p'
		jmp	short loc_18F57
; ---------------------------------------------------------------------------

loc_18F4B:				; CODE XREF: sub_18EE7+5Bj
		cmp	word_2671A, 60h	; '`'
		jnz	short loc_18F5A
		push	0C0h ; 'À'
		push	78h ; 'x'

loc_18F57:				; CODE XREF: sub_18EE7+62j
		call	sub_18A14

loc_18F5A:				; CODE XREF: sub_18EE7+69j
		mov	byte_266E2, 2
		mov	byte_266E3, 37h	; '7'
		mov	byte_266ED, 0
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 0Ch
		call	word_2D004
		call	sub_18A79
		or	al, al
		jz	short loc_18F89
		mov	word_2671A, 0
		mov	byte_2671D, 0

loc_18F89:				; CODE XREF: sub_18EE7+54j
					; sub_18EE7+95j
		pop	bp
		retn
sub_18EE7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_18F8B	proc near		; CODE XREF: seg003:loc_19414p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 10h
		jnz	short loc_18F9C
		mov	byte_26718, 0Ah
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18F9C:				; CODE XREF: sub_18F8B+8j
		cmp	word_2671A, 30h	; '0'
		jnz	short loc_18FD7
		mov	ax, word ptr dword_2670A
		add	ax, 0FF40h
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		push	ax
		call	sub_C696
		mov	ax, word ptr dword_2670A
		add	ax, 0C0h ; 'À'
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		push	ax
		call	sub_C696
		mov	byte_25592, 0Fh
		push	8
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18FD7:				; CODE XREF: sub_18F8B+16j
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_18FF5
		mov	byte_26718, 0
		push	0FF40h
		push	18h
		call	sub_18A14
		push	0C0h ; 'À'
		push	68h ; 'h'
		call	sub_18A14
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_18FF5:				; CODE XREF: sub_18F8B+51j
		cmp	word_2671A, 40h	; '@'
		jle	short loc_19058
		cmp	word_2671A, 50h	; 'P'
		jnz	short loc_19012
		push	0FF40h
		push	10h
		call	sub_18A14
		push	0C0h ; 'À'
		push	70h ; 'p'
		jmp	short loc_19026
; ---------------------------------------------------------------------------

loc_19012:				; CODE XREF: sub_18F8B+76j
		cmp	word_2671A, 60h	; '`'
		jnz	short loc_19029
		push	0FF40h
		push	8
		call	sub_18A14
		push	0C0h ; 'À'
		push	78h ; 'x'

loc_19026:				; CODE XREF: sub_18F8B+85j
		call	sub_18A14

loc_19029:				; CODE XREF: sub_18F8B+8Cj
		mov	byte_266E2, 2
		mov	byte_266E3, 37h	; '7'
		mov	byte_266ED, 0
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 6
		call	word_2D004
		call	sub_18A79
		or	al, al
		jz	short loc_19058
		mov	word_2671A, 0
		mov	byte_2671D, 0

loc_19058:				; CODE XREF: sub_18F8B+6Fj
					; sub_18F8B+C0j
		pop	bp
		retn
sub_18F8B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1905A	proc near		; CODE XREF: seg003:loc_194BEp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 10h
		jl	loc_1915B
		cmp	word_2671A, 10h
		jnz	short loc_1908E
		push	0Fh
		call	sub_13D60
		mov	dl, 0E0h ; 'à'
		sub	dl, al
		mov	byte_2D02D, dl
		push	0Fh
		call	sub_13D60
		add	al, 0A0h ; ' '
		mov	byte_2D02C, al
		mov	byte_2D02B, 0
		mov	byte_266E3, 4Ch	; 'L'

loc_1908E:				; CODE XREF: sub_1905A+11j
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_190DE
		mov	byte_266EE, 10h
		mov	al, byte_2D02D
		add	al, 10h
		mov	byte_2D02D, al
		mov	al, byte_2D02C
		add	al, 0F0h ; 'ð'
		mov	byte_2D02C, al
		inc	byte_2D02B
		cmp	byte_2D02B, 0Ah
		jbe	short loc_190D7
		push	0Fh
		call	sub_13D60
		mov	dl, 0E0h ; 'à'
		sub	dl, al
		mov	byte_2D02D, dl
		push	0Fh
		call	sub_13D60
		add	al, 0A0h ; ' '
		mov	byte_2D02C, al
		mov	byte_2D02B, 0

loc_190D7:				; CODE XREF: sub_1905A+5Fj
		push	0Fh
		call	sub_138B2

loc_190DE:				; CODE XREF: sub_1905A+3Fj
		mov	byte_266E2, 4
		mov	byte_266EC, 0
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF60h
		mov	word ptr dword_266E4+2,	ax
		mov	ax, word ptr dword_2670A
		add	ax, 0C0h ; 'À'
		mov	word ptr dword_266E4, ax
		mov	al, byte_2D02D
		mov	byte_266ED, al
		call	sub_1CFA2
		sub	word ptr dword_266E4, 180h
		mov	al, byte_2D02C
		mov	byte_266ED, al
		call	sub_1CFA2
		mov	al, byte_266EE
		add	al, 0Ah
		mov	byte_266EE, al
		mov	al, byte_2D01E
		mov	ah, 0
		push	ax
		mov	ax, word_2671A
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_1915B
		mov	byte_266EC, 2Eh	; '.'
		mov	byte_266EF, 5
		mov	byte_266F0, 9
		mov	byte_266ED, 0
		mov	byte_266E2, 1
		push	0Fh
		call	sub_13D60
		add	al, 20h	; ' '
		mov	byte_266EE, al
		mov	byte_266F2, 0FFh
		call	word_2D004
		call	word_2D002

loc_1915B:				; CODE XREF: sub_1905A+8j
					; sub_1905A+CFj
		pop	bp
		retn
sub_1905A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1915D	proc far

; FUNCTION CHUNK AT 5B14 SIZE 00000005 BYTES

		enter	2, 0
		push	si
		push	di
		mov	al, byte_26719
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 6
		ja	loc_195A4
		add	bx, bx
		jmp	word ptr cs:[bx+5B46h]
sub_1915D	endp


; =============== S U B	R O U T	I N E =======================================


sub_19178	proc far
		cmp	word_2671A, 0
		jnz	short loc_191DC
		mov	word_26716, 12C0h
		mov	word_26720, 12C0h
		mov	byte_23DC2, 60h	; '`'
		mov	byte_23DC3, 0
		mov	byte_23DC4, 0
		mov	byte_266D3, 1
		mov	word ptr [bp-2], 0B204h
		xor	si, si
		jmp	short loc_191B3
; ---------------------------------------------------------------------------

loc_191A8:				; CODE XREF: sub_19178+3Ej
		mov	bx, [bp-2]
		mov	byte ptr [bx], 0
		inc	si
		add	word ptr [bp-2], 1Ah

loc_191B3:				; CODE XREF: sub_19178+2Ej
		cmp	si, 6
		jl	short loc_191A8
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_2A8C6+2,	ax
		mov	word_2A8D0, 20h	; ' '
		mov	word_2A8CE, 1400h
		mov	byte_2A8D3, 0FDh ; 'ý'
		mov	byte_2A8D2, 0Fh
		jmp	short loc_19235
; ---------------------------------------------------------------------------

loc_191DC:				; CODE XREF: sub_19178+5j
		cmp	word_2671A, 120h
		jl	short loc_19226
		cmp	word_2671A, 128h ; CODE	XREF: sub_1CD6E:loc_1CD8Fj
		jnz	short loc_191F1
		mov	byte_2A8D2, 9

loc_191F1:				; CODE XREF: sub_19178+72j
		test	byte ptr word_2671A, 7
		jnz	short loc_191FB
		call	sub_13B21

loc_191FB:				; CODE XREF: sub_19178+7Ej
		cmp	word_2671A, 140h
		jl	short loc_19235
		inc	byte_26719
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	byte_259F1, 0
		mov	word_255AC, 76FBh
		mov	byte_2CDCA, 0
		jmp	short loc_19235
; ---------------------------------------------------------------------------

loc_19226:				; CODE XREF: sub_19178+6Aj
		cmp	word_2671A, 80h	; '€'
		jnz	short loc_19235
		push	8
		call	sub_138B2
sub_19178	endp ; sp-analysis failed

; START	OF FUNCTION CHUNK FOR sub_1CD6E

loc_19235:				; CODE XREF: sub_19178+62j
					; sub_19178+89j ...
		call	sub_1E67C
		jmp	loc_195A9
; END OF FUNCTION CHUNK	FOR sub_1CD6E
; ---------------------------------------------------------------------------
		call	sub_1E67C
		cmp	word_2671A, 20h	; ' '
		jl	loc_195A9
		push	large 0FFFF0CE4h
		call	sub_1E6F3
		mov	byte_2671D, 3
		mov	byte_2671E, 0C0h ; 'À'
		push	6
		call	sub_138B2
		jmp	loc_195A9
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 4
		ja	loc_19309
		add	bx, bx
		jmp	cs:off_195CC[bx]

loc_19279:				; CODE XREF: seg003:58F2j
					; DATA XREF: seg003:off_195CCo
		call	sub_18B68
		cmp	word_2671A, 60h	; '`'
		jl	loc_19309
		mov	word_2671A, 0
		push	3
		call	sub_13D60
		inc	al
		mov	byte_2671D, al
		inc	byte_2671F
		cmp	byte_2671F, 0Ah
		ja	short loc_19317
		mov	byte_266E2, 1
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266E3, 37h	; '7'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 16h
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D004
		mov	byte_266EE, 10h
		mov	al, byte_2671F
		mov	ah, 0
		mov	di, ax
		cmp	di, 5
		jle	short loc_192DE
		mov	di, 5

loc_192DE:				; CODE XREF: seg003:5849j
		xor	si, si
		jmp	short loc_192F6
; ---------------------------------------------------------------------------

loc_192E2:				; CODE XREF: seg003:5868j
		call	sub_1CFA2
		inc	si
		mov	al, byte_266EE
		add	al, 8
		mov	byte_266EE, al
		mov	al, byte_266ED
		add	al, 0FDh ; 'ý'
		mov	byte_266ED, al

loc_192F6:				; CODE XREF: seg003:5850j
		cmp	si, di
		jl	short loc_192E2
		jmp	short loc_19309
; ---------------------------------------------------------------------------

loc_192FC:				; CODE XREF: seg003:57E4j seg003:58F2j
					; DATA XREF: ...
		call	sub_18BE6
		jmp	short loc_19309
; ---------------------------------------------------------------------------

loc_19301:				; CODE XREF: seg003:57E4j seg003:58F2j
					; DATA XREF: ...
		call	sub_18C76
		jmp	short loc_19309
; ---------------------------------------------------------------------------

loc_19306:				; CODE XREF: seg003:57E4j seg003:58F2j
					; DATA XREF: ...
		call	sub_18D04

loc_19309:				; CODE XREF: seg003:57DEj seg003:57F1j ...
		call	sub_1E64E
		or	al, al
		jz	loc_195A9
		push	0Ah
		call	sub_19FD8

loc_19317:				; CODE XREF: seg003:580Ej
		push	large 10802h
		call	sub_1E6F3
		mov	byte_2CFF8, 40h	; '@'
		jmp	loc_195A9
; ---------------------------------------------------------------------------
		call	sub_18A79
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_1933B
		cmp	ax, 1
		jz	short loc_19350
		jmp	short loc_19353
; ---------------------------------------------------------------------------

loc_1933B:				; CODE XREF: seg003:58A2j
		cmp	word_2671A, 80h	; '€'
		jl	short loc_19353
		mov	word_2671A, 0
		mov	byte_2671D, 1
		jmp	short loc_19353
; ---------------------------------------------------------------------------

loc_19350:				; CODE XREF: seg003:58A7j
		call	sub_18DB6

loc_19353:				; CODE XREF: seg003:58A9j seg003:58B1j ...
		cmp	word_2671A, 7D0h
		jg	short loc_19369
		call	sub_1E64E
		or	al, al
		jz	loc_195A9
		push	0Ah
		call	sub_19FD8

loc_19369:				; CODE XREF: seg003:58C9j
		push	large 20226h
		jmp	loc_1942B
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	loc_19417
		add	bx, bx
		jmp	cs:off_195C4[bx]

loc_19387:				; DATA XREF: seg003:off_195C4o
		call	sub_18B68
		cmp	word_2671A, 60h	; '`'
		jl	loc_19417
		mov	word_2671A, 0
		push	3
		call	sub_13D76
		inc	al
		mov	byte_2671D, al
		inc	byte_2671F
		cmp	byte_2671F, 0Ah
		ja	short loc_19425
		mov	byte_266E2, 1
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266E3, 37h	; '7'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 16h
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D004
		mov	byte_266EE, 10h
		mov	al, byte_2671F
		mov	ah, 0
		mov	di, ax
		cmp	di, 5
		jle	short loc_193EC
		mov	di, 5

loc_193EC:				; CODE XREF: seg003:5957j
		xor	si, si
		jmp	short loc_19404
; ---------------------------------------------------------------------------

loc_193F0:				; CODE XREF: seg003:5976j
		call	sub_1CFA2
		inc	si
		mov	al, byte_266EE
		add	al, 8
		mov	byte_266EE, al
		mov	al, byte_266ED
		add	al, 3
		mov	byte_266ED, al

loc_19404:				; CODE XREF: seg003:595Ej
		cmp	si, di
		jl	short loc_193F0
		jmp	short loc_19417
; ---------------------------------------------------------------------------

loc_1940A:				; CODE XREF: seg003:58F2j
					; DATA XREF: seg003:5B36o
		call	sub_18E43
		jmp	short loc_19417
; ---------------------------------------------------------------------------

loc_1940F:				; CODE XREF: seg003:58F2j
					; DATA XREF: seg003:5B38o
		call	sub_18EE7
		jmp	short loc_19417
; ---------------------------------------------------------------------------

loc_19414:				; CODE XREF: seg003:58F2j
					; DATA XREF: seg003:5B3Ao
		call	sub_18F8B

loc_19417:				; CODE XREF: seg003:58ECj seg003:58FFj ...
		call	sub_1E64E
		or	al, al
		jz	loc_195A9
		push	0Ah
		call	sub_19FD8

loc_19425:				; CODE XREF: seg003:591Cj
		push	large 30000h

loc_1942B:				; CODE XREF: seg003:58DFj
		call	sub_1E6F3
		jmp	loc_195A9
; ---------------------------------------------------------------------------
		call	sub_18A79
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_19444
		cmp	ax, 1
		jz	short loc_194BE
		jmp	short loc_194C1
; ---------------------------------------------------------------------------

loc_19444:				; CODE XREF: seg003:59ABj
		cmp	word_2671A, 90h	; ''
		jnz	short loc_1945E
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		call	sub_C696
		mov	byte_25592, 0Fh

loc_1945E:				; CODE XREF: seg003:59BAj
		cmp	word_2671A, 40h	; '@'
		jle	short loc_1947A
		mov	word_2671A, 0
		mov	byte_2671D, 1
		mov	byte_26718, 0Ch
		mov	byte_2671E, 80h	; '€'

loc_1947A:				; CODE XREF: seg003:59D3j
		cmp	word ptr dword_2670A, 0BF0h
		jge	short loc_1948A
		mov	word_26712, 18h
		jmp	short loc_19498
; ---------------------------------------------------------------------------

loc_1948A:				; CODE XREF: seg003:59F0j
		cmp	word ptr dword_2670A, 0C10h
		jle	short loc_19498
		mov	word_26712, 0FFE8h

loc_19498:				; CODE XREF: seg003:59F8j seg003:5A00j
		cmp	word ptr dword_2670A+2,	4F0h
		jge	short loc_194A8
		mov	word_26714, 0Ch
		jmp	short loc_194B6
; ---------------------------------------------------------------------------

loc_194A8:				; CODE XREF: seg003:5A0Ej
		cmp	word ptr dword_2670A+2,	510h
		jle	short loc_194B6
		mov	word_26714, 0FFF4h

loc_194B6:				; CODE XREF: seg003:5A16j seg003:5A1Ej
		push	53CAh
		call	sub_13D32
		jmp	short loc_194C1
; ---------------------------------------------------------------------------

loc_194BE:				; CODE XREF: seg003:59B0j
		call	sub_1905A

loc_194C1:				; CODE XREF: seg003:59B2j seg003:5A2Cj
		call	sub_1E64E
		or	al, al
		jnz	short loc_194D2
		cmp	word_2671A, 2BCh
		jl	loc_195A9

loc_194D2:				; CODE XREF: seg003:5A36j
		inc	byte_26719
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		push	large 800030h
		call	sub_13E8C
		push	4
		call	sub_15C7C
		cmp	word_2671A, 258h
		jge	short loc_194FB
		mov	byte_2671F, 1
		jmp	short loc_19500
; ---------------------------------------------------------------------------

loc_194FB:				; CODE XREF: seg003:5A62j
		mov	byte_2671F, 0

loc_19500:				; CODE XREF: seg003:5A69j
		mov	word_2671A, 0
		jmp	loc_195A9
; ---------------------------------------------------------------------------
		call	sub_18A79
		cmp	word ptr dword_2670A, 0BF0h
		jge	short loc_1951C
		mov	word_26712, 18h
		jmp	short loc_1952A
; ---------------------------------------------------------------------------

loc_1951C:				; CODE XREF: seg003:5A82j
		cmp	word ptr dword_2670A, 0C10h
		jle	short loc_1952A
		mov	word_26712, 0FFE8h

loc_1952A:				; CODE XREF: seg003:5A8Aj seg003:5A92j
		cmp	word ptr dword_2670A+2,	4F0h
		jge	short loc_1953A
		mov	word_26714, 0Ch
		jmp	short loc_19548
; ---------------------------------------------------------------------------

loc_1953A:				; CODE XREF: seg003:5AA0j
		cmp	word ptr dword_2670A+2,	510h
		jle	short loc_19548
		mov	word_26714, 0FFF4h

loc_19548:				; CODE XREF: seg003:5AA8j seg003:5AB0j
		push	53CAh
		call	sub_13D32
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_1955E
		push	4
		call	sub_15C7C

loc_1955E:				; CODE XREF: seg003:5AC7j
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_195A9
		push	0
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_19581
		push	14h
		call	sub_19FD8

loc_19581:				; CODE XREF: seg003:5AEAj
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_23DC2, 0
		mov	byte_266D3, 1
		mov	byte_259A2, 0FFh
		jmp	short loc_195A9
; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_1915D

loc_195A4:				; CODE XREF: sub_1915D+10j
		call	sub_1E743
		jmp	short loc_195BF
; END OF FUNCTION CHUNK	FOR sub_1915D
; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_1CD6E

loc_195A9:				; CODE XREF: sub_1CD6E-3B36j
					; seg003:57B3j	...
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax
		push	word_26716
		push	12C0h
		call	sub_19F16

loc_195BF:				; CODE XREF: sub_1915D+44Aj
		pop	di
		pop	si
		leave
		retf
; END OF FUNCTION CHUNK	FOR sub_1CD6E
; ---------------------------------------------------------------------------
		db 0
off_195C4	dw offset loc_19387	; DATA XREF: seg003:58F2r
		dw offset loc_1940A
		dw offset loc_1940F
		dw offset loc_19414
off_195CC	dw offset loc_19279	; DATA XREF: seg003:57E4r
		dw offset loc_192FC
		dw offset loc_19301
		dw offset loc_19306
		dw offset loc_19306
		db 0E8h, 56h, 0ABh, 57h, 0D4h, 57h, 98h, 58h, 0E2h, 58h
		db 0A1h, 59h, 79h, 5Ah

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_195E4	proc near		; CODE XREF: sub_19686+3p sub_19720+3p ...

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		mov	ax, word_2671A
		add	ax, 0FFBAh
		push	ax
		push	large 70006h
		call	sub_13B89
		cmp	word_2671A, 10h
		jl	short loc_19678
		cmp	word_2671A, 10h
		jnz	short loc_19647
		push	1400h
		call	sub_13D76
		add	ax, 200h
		mov	[bp+var_2], ax
		push	600h
		call	sub_13D76
		add	ax, 400h
		mov	[bp+var_4], ax
		mov	ax, [bp+var_2]
		sub	ax, word ptr dword_2670A
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		mov	word_26712, ax
		mov	ax, [bp+var_4]
		sub	ax, word ptr dword_2670A+2
		cwd
		idiv	bx
		mov	word_26714, ax
		mov	word_2A8CE, 600h
		mov	word_2A8D0, 8

loc_19647:				; CODE XREF: sub_195E4+20j
		cmp	word_2671A, 46h	; 'F'
		jge	short loc_19656
		push	53CAh
		call	sub_13D32
		jmp	short loc_19682
; ---------------------------------------------------------------------------

loc_19656:				; CODE XREF: sub_195E4+68j
		cmp	word_2671A, 46h	; 'F'
		jnz	short loc_19671
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		call	sub_C696
		mov	byte_25592, 0Fh
		jmp	short loc_19682
; ---------------------------------------------------------------------------

loc_19671:				; CODE XREF: sub_195E4+77j
		cmp	word_2671A, 56h	; 'V'
		jge	short loc_1967D

loc_19678:				; CODE XREF: sub_195E4+19j
		mov	ax, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1967D:				; CODE XREF: sub_195E4+92j
		mov	ax, 2
		leave
		retn
; ---------------------------------------------------------------------------

loc_19682:				; CODE XREF: sub_195E4+70j
					; sub_195E4+8Bj
		xor	ax, ax
		leave
		retn
sub_195E4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19686	proc near		; CODE XREF: sub_19AA3:loc_19C4Fp
		push	bp
		mov	bp, sp
		call	sub_195E4
		cmp	ax, 2
		jnz	loc_1971E
		cmp	word_2671A, 56h	; 'V'
		jnz	short loc_196C2
		push	1
		call	sub_13D60
		mov	byte_2671F, al
		cmp	byte_2671F, 0
		jnz	short loc_196AD
		mov	al, 0
		jmp	short loc_196AF
; ---------------------------------------------------------------------------

loc_196AD:				; CODE XREF: sub_19686+21j
		mov	al, 80h	; '€'

loc_196AF:				; CODE XREF: sub_19686+25j
		mov	byte_2671E, al
		cmp	byte_2671F, 0
		jnz	short loc_196BD
		mov	al, 0Bh
		jmp	short loc_196BF
; ---------------------------------------------------------------------------

loc_196BD:				; CODE XREF: sub_19686+31j
		mov	al, 0F5h ; 'õ'

loc_196BF:				; CODE XREF: sub_19686+35j
		mov	byte_2671F, al

loc_196C2:				; CODE XREF: sub_19686+12j
		cmp	byte_266CC, 0
		jnz	short loc_19712
		mov	byte_266E2, 1
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 2
		mov	al, byte_2671E
		mov	byte_266ED, al
		mov	byte_266EE, 1Eh
		call	word_2D000
		mov	al, byte_266ED
		add	al, 5
		mov	byte_266ED, al
		mov	byte_266EE, 14h
		call	word_2D000
		mov	al, byte_2671F
		add	byte_2671E, al
		push	9
		call	sub_138B2

loc_19712:				; CODE XREF: sub_19686+41j
		cmp	word_2671A, 76h	; 'v'
		jl	short loc_1971E
		mov	byte_2671D, 0

loc_1971E:				; CODE XREF: sub_19686+9j
					; sub_19686+91j
		pop	bp
		retn
sub_19686	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19720	proc near		; CODE XREF: sub_19AA3:loc_19C54p
		push	bp
		mov	bp, sp
		call	sub_195E4
		cmp	ax, 2
		jnz	loc_197B9
		cmp	word_2671A, 56h	; 'V'
		jnz	short loc_19751
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8
		mov	byte_2671E, al
		mov	byte_266EE, 10h

loc_19751:				; CODE XREF: sub_19720+12j
		cmp	byte_266CD, 0
		jnz	short loc_197AD
		mov	byte_266E2, 4
		mov	byte_266E3, 34h	; '4'
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 3
		mov	byte_266F0, 0Ch
		mov	byte_266F2, 0FFh
		mov	al, byte_2671E
		add	al, 0E0h ; 'à'
		mov	byte_266ED, al
		call	word_2D004
		call	word_2D002
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	word_2D002
		push	3
		call	sub_138B2
		mov	al, byte_266EE
		add	al, 6
		mov	byte_266EE, al

loc_197AD:				; CODE XREF: sub_19720+36j
		cmp	word_2671A, 76h	; 'v'
		jl	short loc_197B9
		mov	byte_2671D, 0

loc_197B9:				; CODE XREF: sub_19720+9j
					; sub_19720+92j
		pop	bp
		retn
sub_19720	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_197BB	proc near		; CODE XREF: sub_19AA3:loc_19C59p
		push	bp
		mov	bp, sp
		call	sub_195E4
		cmp	ax, 2
		jnz	short loc_19812
		cmp	byte_266CE, 0
		jnz	short loc_19806
		mov	byte_266E2, 2
		mov	byte_266E3, 34h	; '4'
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 10h
		mov	byte_266EE, 20h	; ' '
		mov	byte_266ED, 0
		call	word_2D004
		call	word_2D000
		push	9
		call	sub_138B2

loc_19806:				; CODE XREF: sub_197BB+10j
		cmp	word_2671A, 76h	; 'v'
		jl	short loc_19812
		mov	byte_2671D, 0

loc_19812:				; CODE XREF: sub_197BB+9j
					; sub_197BB+50j
		pop	bp
		retn
sub_197BB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19814	proc near		; CODE XREF: sub_19AA3:loc_19C5Ep
		push	bp
		mov	bp, sp
		call	sub_195E4
		cmp	ax, 2
		jnz	short loc_19876
		cmp	byte_266CE, 0
		jnz	short loc_1986A
		mov	byte_266E2, 1
		mov	ax, word ptr dword_2670A
		add	ax, 0FE00h
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 8
		mov	byte_266EE, 1Eh
		mov	al, byte_266ED
		add	al, 8
		mov	byte_266ED, al
		call	word_2D004
		call	word_2D000
		add	word ptr dword_266E4, 400h
		call	word_2D000
		push	9
		call	sub_138B2

loc_1986A:				; CODE XREF: sub_19814+10j
		cmp	word_2671A, 76h	; 'v'
		jl	short loc_19876
		mov	byte_2671D, 0

loc_19876:				; CODE XREF: sub_19814+9j
					; sub_19814+5Bj
		pop	bp
		retn
sub_19814	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19878	proc near		; CODE XREF: sub_19AA3:loc_19CAFp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 1
		jnz	short loc_1989A
		cmp	word ptr dword_2670A, 0C00h
		jge	short loc_1988F
		mov	ax, 10h
		jmp	short loc_19892
; ---------------------------------------------------------------------------

loc_1988F:				; CODE XREF: sub_19878+10j
		mov	ax, 0FFF0h

loc_19892:				; CODE XREF: sub_19878+15j
		mov	word_26712, ax
		mov	byte_2671E, 0

loc_1989A:				; CODE XREF: sub_19878+8j
		push	large 10h
		mov	al, byte_2671E
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4E6h]
		call	sub_13320
		mov	word_26714, ax
		cmp	word ptr dword_2670A+2,	600h
		jl	short loc_198C0
		mov	word_26714, 0FFF0h

loc_198C0:				; CODE XREF: sub_19878+40j
		cmp	word ptr dword_2670A+2,	300h
		jg	short loc_198CE
		mov	word_26714, 10h

loc_198CE:				; CODE XREF: sub_19878+4Ej
		mov	al, byte_2671E
		add	al, 2
		mov	byte_2671E, al
		push	53CAh
		call	sub_13D32
		cmp	ax, 200h
		jbe	short loc_198E6
		cmp	ax, 1600h
		jb	short loc_198F0

loc_198E6:				; CODE XREF: sub_19878+67j
		mov	ax, 0FFFFh
		imul	word_26712
		mov	word_26712, ax

loc_198F0:				; CODE XREF: sub_19878+6Cj
		cmp	byte_266CD, 0
		jnz	loc_19989
		cmp	byte_25688, 0
		jnz	short loc_19909
		cmp	byte_266CE, 0
		jz	loc_19989

loc_19909:				; CODE XREF: sub_19878+86j
		mov	byte_266E3, 34h	; '4'
		mov	ax, word ptr dword_2670A
		add	ax, 0FE00h
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 1Bh
		mov	byte_266EF, 1
		cmp	word_26716, 2BCh
		jg	short loc_19942
		cmp	byte_25688, 3
		jnb	short loc_1993D
		mov	byte_266EF, 2
		jmp	short loc_19942
; ---------------------------------------------------------------------------

loc_1993D:				; CODE XREF: sub_19878+BCj
		mov	byte_266EF, 4

loc_19942:				; CODE XREF: sub_19878+B5j
					; sub_19878+C3j
		mov	byte_266EE, 20h	; ' '
		push	1
		call	sub_13D60
		or	ax, ax
		jnz	short loc_19954
		mov	al, 1
		jmp	short loc_19956
; ---------------------------------------------------------------------------

loc_19954:				; CODE XREF: sub_19878+D6j
		mov	al, 4

loc_19956:				; CODE XREF: sub_19878+DAj
		mov	byte_266E2, al
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D004
		call	word_2D000
		add	word ptr dword_266E4, 400h
		push	1
		call	sub_13D60
		or	ax, ax
		jnz	short loc_1997A
		mov	al, 1
		jmp	short loc_1997C
; ---------------------------------------------------------------------------

loc_1997A:				; CODE XREF: sub_19878+FCj
		mov	al, 4

loc_1997C:				; CODE XREF: sub_19878+100j
		mov	byte_266E2, al
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D000

loc_19989:				; CODE XREF: sub_19878+7Dj
					; sub_19878+8Dj
		pop	bp
		retn
sub_19878	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1998B	proc near		; CODE XREF: sub_19AA3:loc_19D9Bp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 60h	; '`'
		jz	short loc_199AD
		cmp	word_2671A, 0A0h ; ' '
		jz	short loc_199AD
		cmp	word_2671A, 0E0h ; 'à'
		jz	short loc_199AD
		cmp	word_2671A, 120h
		jnz	short loc_199BC

loc_199AD:				; CODE XREF: sub_1998B+8j
					; sub_1998B+10j ...
		mov	ax, word ptr dword_266E4
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_266E4+2
		mov	word ptr dword_2A8C6+2,	ax
		call	sub_13B21

loc_199BC:				; CODE XREF: sub_1998B+20j
		cmp	word_2671A, 70h	; 'p'
		jz	short loc_199DB
		cmp	word_2671A, 0A0h ; ' '
		jz	short loc_199DB
		cmp	word_2671A, 0F0h ; 'ð'
		jz	short loc_199DB
		cmp	word_2671A, 130h
		jnz	short loc_199ED

loc_199DB:				; CODE XREF: sub_1998B+36j
					; sub_1998B+3Ej ...
		push	word ptr dword_266E4
		push	word ptr dword_266E4+2
		call	sub_C696
		mov	byte_25592, 0Fh

loc_199ED:				; CODE XREF: sub_1998B+4Ej
		cmp	byte_266CD, 0
		jnz	loc_19AA1
		mov	byte_266E2, 1
		mov	byte_266EC, 0
		mov	al, byte_2671E
		add	al, 0F9h ; 'ù'
		mov	byte_2671E, al
		mov	byte_266EE, 20h	; ' '
		mov	byte_266ED, al
		call	word_2D004
		call	sub_1CFA2
		cmp	word_2671A, 80h	; '€'
		jl	loc_19AA1
		cmp	word_2671A, 0C0h ; 'À'
		jl	short loc_19A4F
		cmp	word_2671A, 100h
		jl	short loc_19A44
		cmp	word_2671A, 140h
		jge	short loc_19A56
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	sub_1CFA2

loc_19A44:				; CODE XREF: sub_1998B+A4j
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	sub_1CFA2

loc_19A4F:				; CODE XREF: sub_1998B+9Cj
		mov	al, byte_266ED
		add	al, 40h	; '@'
		jmp	short loc_19A9B
; ---------------------------------------------------------------------------

loc_19A56:				; CODE XREF: sub_1998B+ACj
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	sub_1CFA2
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	sub_1CFA2
		mov	al, byte_266ED
		add	al, 40h	; '@'
		mov	byte_266ED, al
		call	sub_1CFA2
		mov	al, byte_266EE
		add	al, 10h
		mov	byte_266EE, al
		mov	byte_266E2, 2
		mov	byte_266E3, 34h	; '4'
		mov	al, byte_266ED
		neg	al
		add	al, 0E0h ; 'à'
		mov	byte_266ED, al
		call	sub_1CFA2
		mov	al, byte_266ED
		add	al, 80h	; '€'

loc_19A9B:				; CODE XREF: sub_1998B+C9j
		mov	byte_266ED, al
		call	sub_1CFA2

loc_19AA1:				; CODE XREF: sub_1998B+67j
					; sub_1998B+92j
		pop	bp
		retn
sub_1998B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19AA3	proc far
		push	bp
		mov	bp, sp
		push	si
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_2A8C6+2,	ax
		mov	al, byte_26719
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 5
		ja	loc_19E88
		add	bx, bx
		jmp	cs:off_19EB0[bx]

loc_19AC8:				; CODE XREF: sub_19AA3+17Bj
					; DATA XREF: seg003:off_19EB0o
		cmp	word_2671A, 0
		jnz	short loc_19AEF
		mov	word_26716, 0BEAh
		mov	word_26720, 79Eh
		mov	byte_23DC2, 0
		mov	byte_23DC3, 0
		mov	byte_23DC4, 60h	; '`'
		mov	byte_266D3, 1

loc_19AEF:				; CODE XREF: sub_19AA3+2Aj
		inc	word_2671A
		cmp	word_2671A, 0C0h ; 'À'
		jnz	short loc_19B35
		mov	al, byte_26718
		add	al, 2
		mov	byte_26718, al
		push	8
		call	sub_138B2
		mov	ax, word ptr dword_2670A
		add	ax, 80h	; '€'
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FD80h
		mov	word ptr dword_2A8C6+2,	ax
		mov	word_2A8CE, 1400h
		mov	word_2A8D0, 20h	; ' '
		mov	byte_2A8D3, 3
		mov	byte_2A8D2, 7
		jmp	loc_19C02
; ---------------------------------------------------------------------------

loc_19B35:				; CODE XREF: sub_19AA3+56j
		cmp	word_2671A, 140h
		jle	loc_19C02
		cmp	word_2671A, 150h
		jnz	short loc_19B4C
		mov	byte_2A8D2, 6

loc_19B4C:				; CODE XREF: sub_19AA3+A2j
		test	byte ptr word_2671A, 7
		jnz	short loc_19B56
		call	sub_13B21

loc_19B56:				; CODE XREF: sub_19AA3+AEj
		cmp	word_2671A, 160h
		jl	loc_19C02
		inc	byte_26719
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	byte_2D02D, 0
		mov	byte_2D02C, 0FFh
		mov	word_255AC, 768Eh
		mov	byte_2CDCA, 0
		jmp	short loc_19C02
; ---------------------------------------------------------------------------

loc_19B88:				; CODE XREF: sub_19AA3+20j
					; sub_19AA3+17Bj
					; DATA XREF: ...
		inc	word_2671A
		cmp	word_2671A, 20h	; ' '
		jl	short loc_19C02
		mov	word_2A8CE, 400h
		mov	byte_2A8D3, 2
		mov	word_2A8D0, 8
		mov	byte_26719, 2
		mov	word_2671A, 0
		mov	byte_2671D, 0
		mov	al, byte_26718
		add	al, 2
		mov	byte_26718, al
		mov	byte_266E2, 1
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 10h
		mov	byte_266EE, 40h	; '@'
		mov	byte_266ED, 0
		call	word_2D004
		xor	si, si
		jmp	short loc_19BF6
; ---------------------------------------------------------------------------

loc_19BE9:				; CODE XREF: sub_19AA3+156j
		call	word_2D000
		mov	al, byte_266EE
		add	al, 0F0h ; 'ð'
		mov	byte_266EE, al
		inc	si

loc_19BF6:				; CODE XREF: sub_19AA3+144j
		cmp	si, 3
		jl	short loc_19BE9
		push	6
		call	sub_138B2

loc_19C02:				; CODE XREF: sub_19AA3+8Fj
					; sub_19AA3+98j ...
		push	large 1000100h
		push	0Ah
		call	sub_1E5D8
		jmp	loc_19E8D
; ---------------------------------------------------------------------------

loc_19C10:				; CODE XREF: sub_19AA3+20j
					; sub_19AA3+17Bj
					; DATA XREF: ...
		mov	al, byte_2671D
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 4
		ja	short loc_19C61
		add	bx, bx
		jmp	cs:off_19EA6[bx]

loc_19C23:				; DATA XREF: seg003:off_19EA6o
		mov	word_2671A, 0

loc_19C29:				; CODE XREF: sub_19AA3+197j
		push	3
		call	sub_13D60
		inc	al
		mov	byte_2671D, al
		mov	al, byte_2D02C
		cmp	al, byte_2671D
		jz	short loc_19C29
		mov	al, byte_2671D
		mov	byte_2D02C, al
		inc	byte_2D02D
		cmp	byte_2D02D, 10h
		jb	short loc_19C61
		jmp	short loc_19C6F
; ---------------------------------------------------------------------------

loc_19C4F:				; CODE XREF: sub_19AA3+17Bj
					; DATA XREF: seg003:6418o
		call	sub_19686
		jmp	short loc_19C61
; ---------------------------------------------------------------------------

loc_19C54:				; CODE XREF: sub_19AA3+17Bj
					; DATA XREF: seg003:641Ao
		call	sub_19720
		jmp	short loc_19C61
; ---------------------------------------------------------------------------

loc_19C59:				; CODE XREF: sub_19AA3+17Bj
					; DATA XREF: seg003:641Co
		call	sub_197BB
		jmp	short loc_19C61
; ---------------------------------------------------------------------------

loc_19C5E:				; CODE XREF: sub_19AA3+17Bj
					; DATA XREF: seg003:641Eo
		call	sub_19814

loc_19C61:				; CODE XREF: sub_19AA3+177j
					; sub_19AA3+1A8j ...
		call	sub_1E64E
		or	al, al
		jz	loc_19E8D
		push	5
		call	sub_19FD8

loc_19C6F:				; CODE XREF: sub_19AA3+1AAj
		push	large 101C2h
		call	sub_1E6F3
		mov	byte_23DC2, 70h	; 'p'
		mov	byte_23DC4, 70h	; 'p'
		mov	byte_266D3, 1
		jmp	loc_19E8D
; ---------------------------------------------------------------------------

loc_19C8A:				; CODE XREF: sub_19AA3+20j
					; sub_19AA3+17Bj
					; DATA XREF: ...
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_19C9A
		cmp	ax, 1
		jz	short loc_19CAF
		jmp	short loc_19CB2
; ---------------------------------------------------------------------------

loc_19C9A:				; CODE XREF: sub_19AA3+1EEj
		cmp	word_2671A, 80h	; '€'
		jle	short loc_19CB2
		mov	word_2671A, 0
		mov	byte_2671D, 1
		jmp	short loc_19CB2
; ---------------------------------------------------------------------------

loc_19CAF:				; CODE XREF: sub_19AA3+1F3j
		call	sub_19878

loc_19CB2:				; CODE XREF: sub_19AA3+1F5j
					; sub_19AA3+1FDj ...
		cmp	word_2671A, 5DCh
		jg	short loc_19CC8
		call	sub_1E64E
		or	al, al
		jz	loc_19E8D
		push	5
		call	sub_19FD8

loc_19CC8:				; CODE XREF: sub_19AA3+215j
		push	large 10000h
		call	sub_1E6F3
		mov	al, byte_26718
		add	al, 4
		mov	byte_26718, al
		mov	byte_23DC2, 90h	; ''
		mov	byte_23DC4, 20h	; ' '
		mov	byte_266D3, 1
		mov	byte_2A8D2, 9
		jmp	loc_19E8D
; ---------------------------------------------------------------------------

loc_19CF0:				; CODE XREF: sub_19AA3+20j
					; sub_19AA3+17Bj
					; DATA XREF: ...
		mov	ax, word ptr dword_2670A
		add	ax, 80h	; '€'
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF00h
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_19D15
		cmp	ax, 1
		jz	loc_19D9B
		jmp	loc_19D9E
; ---------------------------------------------------------------------------

loc_19D15:				; CODE XREF: sub_19AA3+266j
		cmp	word_2671A, 60h	; '`'
		jnz	short loc_19D2B
		mov	ax, word ptr dword_266E4
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_266E4+2
		mov	word ptr dword_2A8C6+2,	ax
		call	sub_13B21

loc_19D2B:				; CODE XREF: sub_19AA3+277j
		cmp	word_2671A, 70h	; 'p'
		jnz	short loc_19D44
		push	word ptr dword_266E4
		push	word ptr dword_266E4+2
		call	sub_C696
		mov	byte_25592, 0Fh

loc_19D44:				; CODE XREF: sub_19AA3+28Dj
		cmp	word_2671A, 80h	; '€'
		jle	short loc_19D57
		mov	word_2671A, 0
		mov	byte_2671D, 1

loc_19D57:				; CODE XREF: sub_19AA3+2A7j
		cmp	word ptr dword_2670A, 0BF0h
		jge	short loc_19D67
		mov	word_26712, 18h
		jmp	short loc_19D75
; ---------------------------------------------------------------------------

loc_19D67:				; CODE XREF: sub_19AA3+2BAj
		cmp	word ptr dword_2670A, 0C10h
		jle	short loc_19D75
		mov	word_26712, 0FFE8h

loc_19D75:				; CODE XREF: sub_19AA3+2C2j
					; sub_19AA3+2CAj
		cmp	word ptr dword_2670A+2,	4F0h
		jge	short loc_19D85
		mov	word_26714, 0Ch
		jmp	short loc_19D93
; ---------------------------------------------------------------------------

loc_19D85:				; CODE XREF: sub_19AA3+2D8j
		cmp	word ptr dword_2670A+2,	510h
		jle	short loc_19D93
		mov	word_26714, 0FFF4h

loc_19D93:				; CODE XREF: sub_19AA3+2E0j
					; sub_19AA3+2E8j
		push	53CAh
		call	sub_13D32
		jmp	short loc_19D9E
; ---------------------------------------------------------------------------

loc_19D9B:				; CODE XREF: sub_19AA3+26Bj
		call	sub_1998B

loc_19D9E:				; CODE XREF: sub_19AA3+26Fj
					; sub_19AA3+2F6j
		cmp	word_2671A, 258h
		jg	short loc_19DAF
		call	sub_1E64E
		or	al, al
		jz	loc_19E8D

loc_19DAF:				; CODE XREF: sub_19AA3+301j
		cmp	word_2671A, 258h
		jg	short loc_19DBE
		mov	byte_2671F, 1
		jmp	short loc_19DC3
; ---------------------------------------------------------------------------

loc_19DBE:				; CODE XREF: sub_19AA3+312j
		mov	byte_2671F, 0

loc_19DC3:				; CODE XREF: sub_19AA3+319j
		push	3
		call	sub_15C7C
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671D, 0
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		push	large 800030h
		call	sub_13E8C
		jmp	loc_19E8D
; ---------------------------------------------------------------------------

loc_19DEB:				; CODE XREF: sub_19AA3+20j
					; sub_19AA3+17Bj
					; DATA XREF: ...
		cmp	word ptr dword_2670A, 0BF0h
		jge	short loc_19DFB
		mov	word_26712, 18h
		jmp	short loc_19E09
; ---------------------------------------------------------------------------

loc_19DFB:				; CODE XREF: sub_19AA3+34Ej
		cmp	word ptr dword_2670A, 0C10h
		jle	short loc_19E09
		mov	word_26712, 0FFE8h

loc_19E09:				; CODE XREF: sub_19AA3+356j
					; sub_19AA3+35Ej
		cmp	word ptr dword_2670A+2,	4F0h
		jge	short loc_19E19
		mov	word_26714, 0Ch
		jmp	short loc_19E27
; ---------------------------------------------------------------------------

loc_19E19:				; CODE XREF: sub_19AA3+36Cj
		cmp	word ptr dword_2670A+2,	510h
		jle	short loc_19E27
		mov	word_26714, 0FFF4h

loc_19E27:				; CODE XREF: sub_19AA3+374j
					; sub_19AA3+37Cj
		push	53CAh
		call	sub_13D32
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_19E3D
		push	4
		call	sub_15C7C

loc_19E3D:				; CODE XREF: sub_19AA3+393j
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_19E8D
		push	0
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_19E60
		push	0Ah
		call	sub_19FD8

loc_19E60:				; CODE XREF: sub_19AA3+3B6j
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_23DC2, 0
		mov	byte_23DC4, 0
		mov	byte_266D3, 1
		mov	byte_259A2, 0FFh
		jmp	short loc_19E8D
; ---------------------------------------------------------------------------

loc_19E88:				; CODE XREF: sub_19AA3+1Aj
		call	sub_1E743
		jmp	short loc_19EA3
; ---------------------------------------------------------------------------

loc_19E8D:				; CODE XREF: sub_19AA3+16Aj
					; sub_19AA3+1C3j ...
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax
		push	word_26716
		push	0BEAh
		call	sub_19F16

loc_19EA3:				; CODE XREF: sub_19AA3+3E8j
		pop	si
		pop	bp
		retf
sub_19AA3	endp

; ---------------------------------------------------------------------------
off_19EA6	dw offset loc_19C23	; DATA XREF: sub_19AA3+17Br
		dw offset loc_19C4F
		dw offset loc_19C54
		dw offset loc_19C59
		dw offset loc_19C5E
off_19EB0	dw offset loc_19AC8	; DATA XREF: sub_19AA3+20r
		dw offset loc_19B88
		dw offset loc_19C10
		dw offset loc_19C8A
		dw offset loc_19CF0
		dw offset loc_19DEB

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19EBC	proc far		; CODE XREF: sub_AED0+B1P seg003:0FF4p ...
		push	bp
		mov	bp, sp
		mov	word_259F4, 11BEh
		mov	word_259FA, 11BEh
		mov	word ptr dword_259F6+2,	seg seg001
		mov	word ptr dword_259F6, 11C0h
		mov	byte_259F2, 0
		mov	word_26702, 0
		pop	bp
		retf
sub_19EBC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19EE4	proc far		; CODE XREF: sub_AB88+36P
		push	bp
		mov	bp, sp
		mov	ax, word_26700
		cmp	ax, word_266CA
		jnz	short loc_19F14
		mov	word_259F4, 7634h
		mov	ax, word_25A00
		mov	word_259FA, ax
		mov	eax, dword_259FC
		mov	dword_259F6, eax
		mov	byte_26705, 0
		mov	word_26706, 0
		mov	byte_259F2, 1

loc_19F14:				; CODE XREF: sub_19EE4+Aj
		pop	bp
		retf
sub_19EE4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19F16	proc near		; CODE XREF: sub_14017+2D4p
					; sub_14CFD+261p ...

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	di, [bp+arg_2]
		or	di, di
		jg	short loc_19F26
		xor	si, si
		jmp	short loc_19F4B
; ---------------------------------------------------------------------------

loc_19F26:				; CODE XREF: sub_19F16+Aj
		cmp	di, [bp+arg_0]
		jl	short loc_19F30
		mov	si, 80h	; '€'
		jmp	short loc_19F4B
; ---------------------------------------------------------------------------

loc_19F30:				; CODE XREF: sub_19F16+13j
		movsx	eax, di
		shl	eax, 7
		movsx	ebx, [bp+arg_0]
		cdq
		idiv	ebx
		mov	si, ax
		cmp	si, 80h	; '€'
		jge	short loc_19F4B
		inc	si

loc_19F4B:				; CODE XREF: sub_19F16+Ej
					; sub_19F16+18j ...
		cmp	word_23210, si
		jge	short loc_19F55
		inc	word_23210

loc_19F55:				; CODE XREF: sub_19F16+39j
		cmp	word_23210, si
		jle	short loc_19F5F
		mov	word_23210, si

loc_19F5F:				; CODE XREF: sub_19F16+43j
		push	word_23210
		call	sub_F0DD
		pop	di
		pop	si
		pop	bp
		retn	4
sub_19F16	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19F6E	proc near		; CODE XREF: sub_14017+292p
					; sub_14CFD+1CDp ...

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	4, 0
		push	si
		push	di
		mov	ax, [bp+arg_0]
		imul	ax, 500h
		movzx	eax, ax
		add	dword_2569A, eax
		mov	byte_21CC8, 0
		mov	ax, word ptr dword_266F4
		add	ax, 0FC00h
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_266F4+2
		add	ax, 0FC00h
		mov	[bp+var_4], ax
		xor	di, di
		jmp	short loc_19FCD
; ---------------------------------------------------------------------------

loc_19F9F:				; CODE XREF: sub_19F6E+62j
		push	800h
		call	sub_13D76
		add	ax, [bp+var_2]
		mov	si, ax
		or	si, si
		jge	short loc_19FB2
		xor	si, si
		jmp	short loc_19FBB
; ---------------------------------------------------------------------------

loc_19FB2:				; CODE XREF: sub_19F6E+3Ej
		cmp	si, 1800h
		jle	short loc_19FBB
		mov	si, 1800h

loc_19FBB:				; CODE XREF: sub_19F6E+42j
					; sub_19F6E+48j
		push	si
		push	800h
		call	sub_13D76
		add	ax, [bp+var_4]
		push	ax
		push	500h
		call	sub_13D90
		inc	di

loc_19FCD:				; CODE XREF: sub_19F6E+2Fj
		cmp	di, [bp+arg_0]
		jb	short loc_19F9F
		pop	di
		pop	si
		leave
		retn	2
sub_19F6E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_19FD8	proc near		; CODE XREF: sub_16610+12Cp
					; sub_16610+199p ...

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	4, 0
		push	si
		push	di
		mov	ax, [bp+arg_0]
		imul	ax, 500h
		movzx	eax, ax
		add	dword_2569A, eax
		mov	byte_21CC8, 0
		mov	ax, word ptr dword_2670A
		add	ax, 0FC00h
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FC00h
		mov	[bp+var_4], ax
		xor	di, di
		jmp	short loc_1A037
; ---------------------------------------------------------------------------

loc_1A009:				; CODE XREF: sub_19FD8+62j
		push	800h
		call	sub_13D76
		add	ax, [bp+var_2]
		mov	si, ax
		or	si, si
		jge	short loc_1A01C
		xor	si, si
		jmp	short loc_1A025
; ---------------------------------------------------------------------------

loc_1A01C:				; CODE XREF: sub_19FD8+3Ej
		cmp	si, 1800h
		jle	short loc_1A025
		mov	si, 1800h

loc_1A025:				; CODE XREF: sub_19FD8+42j
					; sub_19FD8+48j
		push	si
		push	800h
		call	sub_13D76
		add	ax, [bp+var_4]
		push	ax
		push	500h
		call	sub_13D90
		inc	di

loc_1A037:				; CODE XREF: sub_19FD8+2Fj
		cmp	di, [bp+arg_0]
		jb	short loc_1A009
		mov	byte_2372D, 0
		pop	di
		pop	si
		leave
		retn	2
sub_19FD8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A047	proc near		; CODE XREF: sub_14017:loc_142E1p
		push	bp
		mov	bp, sp
		cmp	byte_26705, 0FEh ; 'þ'
		jnz	short loc_1A081
		cmp	word_26706, 0
		jnz	short loc_1A05E
		mov	word_255C2, 0Ch

loc_1A05E:				; CODE XREF: sub_1A047+Fj
		inc	word_26706
		mov	ax, word_26706
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1A085
		inc	byte_26704
		cmp	byte_26704, 0Ch
		jb	short loc_1A085
		mov	byte_26705, 0FFh
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A081:				; CODE XREF: sub_1A047+8j
		push	cs
		call	near ptr sub_19EBC

loc_1A085:				; CODE XREF: sub_1A047+26j
					; sub_1A047+31j
		pop	bp
		retn
sub_1A047	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A087	proc near		; CODE XREF: sub_1B22B+28p
					; sub_1B22B+31p

arg_0		= byte ptr  4
arg_2		= byte ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, 0B204h
		xor	dx, dx
		jmp	short loc_1A0C7
; ---------------------------------------------------------------------------

loc_1A092:				; CODE XREF: sub_1A087+43j
		cmp	byte ptr [si], 0
		jnz	short loc_1A0C3
		mov	byte ptr [si], 1
		mov	word ptr [si+16h], 0
		mov	word ptr [si+0Eh], 0
		mov	al, [bp+arg_2]
		mov	[si+1],	al
		mov	al, [bp+arg_0]
		mov	[si+18h], al
		mov	word ptr [si+14h], 64h ; 'd'
		mov	ax, word ptr dword_2670A
		mov	[si+2],	ax
		mov	ax, word ptr dword_2670A+2
		mov	[si+4],	ax
		jmp	short loc_1A0CC
; ---------------------------------------------------------------------------

loc_1A0C3:				; CODE XREF: sub_1A087+Ej
		inc	dx
		add	si, 1Ah

loc_1A0C7:				; CODE XREF: sub_1A087+9j
		cmp	dx, 20h	; ' '
		jl	short loc_1A092

loc_1A0CC:				; CODE XREF: sub_1A087+3Aj
		pop	si
		pop	bp
		retn	4
sub_1A087	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A0D1	proc near		; CODE XREF: sub_1AD6F+67p
		push	bp
		mov	bp, sp
		push	si
		mov	si, 0B52Ah
		mov	byte ptr [si], 1
		mov	word ptr [si+0Eh], 0
		mov	byte ptr [si+18h], 8
		mov	ax, word ptr dword_2598E
		sar	ax, 4
		add	ax, 20h	; ' '
		mov	[si+2],	ax
		mov	ax, word ptr dword_2598E+2
		sar	ax, 4
		add	ax, 10h
		mov	[si+4],	ax
		mov	word ptr [si+10h], 8
		mov	word ptr [si+12h], 50h ; 'P'
		push	8
		call	sub_138B2
		pop	si
		pop	bp
		retn
sub_1A0D1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A110	proc near		; CODE XREF: sub_1CCB8-13BFp

var_6		= byte ptr -6
var_5		= byte ptr -5
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		push	si
		push	di
		mov	word_257E2, 0C0h ; 'À'
		mov	word_257E4, 0C0h ; 'À'
		mov	si, 0B204h
		xor	di, di
		jmp	loc_1A235
; ---------------------------------------------------------------------------

loc_1A12A:				; CODE XREF: sub_1A110+128j
		cmp	byte ptr [si], 1
		jnz	loc_1A231
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+1]
		mov	al, [si+18h]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		mov	ax, [si+0Ah]
		add	[si+2],	ax
		mov	ax, [si+0Ch]
		add	[si+4],	ax
		cmp	word ptr [si+2], 0FF00h
		jle	short loc_1A169
		cmp	word ptr [si+2], 1900h
		jge	short loc_1A169
		cmp	word ptr [si+4], 1800h
		jge	short loc_1A169
		cmp	word ptr [si+4], 0FF00h
		jg	short loc_1A16C

loc_1A169:				; CODE XREF: sub_1A110+42j
					; sub_1A110+49j ...
		mov	byte ptr [si], 0

loc_1A16C:				; CODE XREF: sub_1A110+57j
		mov	ax, [si+2]
		add	ax, 0FF40h
		mov	[bp+var_2], ax
		mov	ax, [si+4]
		add	ax, 0FF40h
		mov	[bp+var_4], ax
		mov	ax, word ptr dword_2598E
		sub	ax, [bp+var_2]
		cmp	ax, 180h
		jnb	short loc_1A199
		mov	ax, word ptr dword_2598E+2
		sub	ax, [bp+var_4]
		cmp	ax, 180h
		jnb	short loc_1A199
		mov	byte_259A9, 1

loc_1A199:				; CODE XREF: sub_1A110+77j
					; sub_1A110+82j
		cmp	word ptr [si+0Eh], 38h ; '8'
		jnb	short loc_1A1CF
		mov	ax, word ptr dword_2598E+2
		sub	ax, [si+4]
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, [si+2]
		push	ax
		call	sub_1DA8
		mov	[bp+var_5], al
		mov	al, [si+1]
		sub	[bp+var_5], al
		cmp	[bp+var_5], 80h	; '€'
		jnb	short loc_1A1C6
		inc	byte ptr [si+1]
		jmp	short loc_1A1CF
; ---------------------------------------------------------------------------

loc_1A1C6:				; CODE XREF: sub_1A110+AFj
		cmp	[bp+var_5], 80h	; '€'
		jb	short loc_1A1CF
		dec	byte ptr [si+1]

loc_1A1CF:				; CODE XREF: sub_1A110+8Dj
					; sub_1A110+B4j ...
		mov	ax, [si+2]
		mov	word ptr dword_257DE, ax
		mov	ax, [si+4]
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		mov	[si+16h], ax
		or	ax, ax
		jz	short loc_1A1EE
		push	4
		call	sub_138B2

loc_1A1EE:				; CODE XREF: sub_1A110+D5j
		mov	ax, [si+16h]
		sub	[si+14h], ax
		cmp	word ptr [si+14h], 0
		jg	short loc_1A22E
		push	3
		call	sub_138B2
		add	dword_2569A, 0BB8h
		mov	byte ptr [si], 10h
		mov	word ptr [si+0Eh], 0
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	large 400008h
		nop
		push	cs
		call	near ptr sub_13E2A
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	3
		call	sub_1DA38

loc_1A22E:				; CODE XREF: sub_1A110+E8j
		inc	word ptr [si+0Eh]

loc_1A231:				; CODE XREF: sub_1A110+1Dj
		inc	di
		add	si, 1Ah

loc_1A235:				; CODE XREF: sub_1A110+17j
		cmp	di, 1Fh
		jl	loc_1A12A
		mov	al, [si]
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_1A24D
		cmp	ax, 2
		jz	short loc_1A261
		jmp	loc_1A3BF
; ---------------------------------------------------------------------------

loc_1A24D:				; CODE XREF: sub_1A110+133j
		cmp	word ptr [si+10h], 80h ; '€'
		jg	short loc_1A25B
		add	word ptr [si+10h], 8
		jmp	loc_1A3BF
; ---------------------------------------------------------------------------

loc_1A25B:				; CODE XREF: sub_1A110+142j
		mov	byte ptr [si], 2
		jmp	loc_1A3BF
; ---------------------------------------------------------------------------

loc_1A261:				; CODE XREF: sub_1A110+138j
		cmp	word ptr [si+0Eh], 8
		jnb	short loc_1A26E
		sub	word ptr [si+12h], 8
		jmp	loc_1A3BC
; ---------------------------------------------------------------------------

loc_1A26E:				; CODE XREF: sub_1A110+155j
		cmp	word ptr [si+0Eh], 8
		jnz	short loc_1A27B
		mov	byte ptr [si+18h], 9
		jmp	loc_1A3BC
; ---------------------------------------------------------------------------

loc_1A27B:				; CODE XREF: sub_1A110+162j
		cmp	word ptr [si+0Eh], 10h
		jnb	short loc_1A288
		sub	word ptr [si+12h], 2
		jmp	loc_1A3BC
; ---------------------------------------------------------------------------

loc_1A288:				; CODE XREF: sub_1A110+16Fj
		cmp	word ptr [si+0Eh], 0A0h	; ' '
		jnb	loc_1A3A8
		mov	ax, [si+0Eh]
		and	ax, 1Fh
		cmp	ax, 10h
		jnb	short loc_1A2A1
		inc	word ptr [si+12h]
		jmp	short loc_1A2A4
; ---------------------------------------------------------------------------

loc_1A2A1:				; CODE XREF: sub_1A110+18Aj
		dec	word ptr [si+12h]

loc_1A2A4:				; CODE XREF: sub_1A110+18Fj
		cmp	byte_266CC, 0
		jz	short loc_1A2B1
		mov	byte ptr [si+18h], 0Fh
		jmp	short loc_1A2B5
; ---------------------------------------------------------------------------

loc_1A2B1:				; CODE XREF: sub_1A110+199j
		mov	byte ptr [si+18h], 9

loc_1A2B5:				; CODE XREF: sub_1A110+19Fj
		cmp	word ptr [si+0Eh], 68h ; 'h'
		ja	short loc_1A2BE
		dec	word ptr [si+10h]

loc_1A2BE:				; CODE XREF: sub_1A110+1A9j
		test	byte ptr [si+0Eh], 0Fh
		jnz	loc_1A3BC
		mov	[bp+var_6], 0C0h ; 'À'
		test	byte ptr [si+0Eh], 1Fh
		jnz	short loc_1A309
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 200h
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266E2, 2
		mov	byte_266E3, 3Ch	; '<'
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 20h	; ' '
		mov	byte_266EE, 10h
		mov	byte_266ED, 0
		call	word_2D004
		call	word_2D000
		mov	[bp+var_6], 40h	; '@'

loc_1A309:				; CODE XREF: sub_1A110+1BEj
		mov	byte_266E2, 1
		mov	byte_266F0, 0Ch
		mov	ax, word_266CA
		mov	bx, 5
		xor	dx, dx
		div	bx
		mov	[bp+var_5], al
		mov	ax, [si+10h]
		add	ax, 4
		mov	[bp+var_2], ax
		xor	di, di
		jmp	short loc_1A39A
; ---------------------------------------------------------------------------

loc_1A32D:				; CODE XREF: sub_1A110+28Dj
		mov	al, [bp+var_5]
		add	al, [bp+var_6]
		mov	byte_266ED, al
		push	53A4h
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	[bp+var_2]
		mov	al, [bp+var_5]
		mov	ah, 0
		push	ax
		call	sub_1333C
		sub	word ptr dword_266E4, 20h ; ' '
		sub	word ptr dword_266E4+2,	10h
		mov	ax, 10h
		imul	word ptr dword_266E4
		mov	word ptr dword_266E4, ax
		mov	ax, 10h
		imul	word ptr dword_266E4+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 2Fh	; '/'
		mov	byte_266EF, 8
		mov	byte_266EE, 10h
		call	word_2D000
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 4
		mov	byte_266EE, 30h	; '0'
		call	word_2D000
		inc	di
		mov	al, [bp+var_5]
		add	al, 20h	; ' '
		mov	[bp+var_5], al

loc_1A39A:				; CODE XREF: sub_1A110+21Bj
		cmp	di, 8
		jl	short loc_1A32D
		push	3
		call	sub_138B2
		jmp	short loc_1A3BC
; ---------------------------------------------------------------------------

loc_1A3A8:				; CODE XREF: sub_1A110+17Dj
		cmp	word ptr [si+0Eh], 0B0h	; '°'
		jnb	short loc_1A3B9
		add	word ptr [si+12h], 10h
		sub	word ptr [si+10h], 2
		jmp	short loc_1A3BC
; ---------------------------------------------------------------------------

loc_1A3B9:				; CODE XREF: sub_1A110+29Dj
		mov	byte ptr [si], 0

loc_1A3BC:				; CODE XREF: sub_1A110+15Bj
					; sub_1A110+168j ...
		inc	word ptr [si+0Eh]

loc_1A3BF:				; CODE XREF: sub_1A110+13Aj
					; sub_1A110+148j ...
		pop	di
		pop	si
		leave
		retn
sub_1A110	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A3C3	proc near		; CODE XREF: seg003:loc_1B563p
		push	bp
		mov	bp, sp
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 6
		cwd
		idiv	bx
		cmp	dx, 5
		jge	short loc_1A42E
		mov	ax, word_2671A
		cmp	ax, 1
		jz	short loc_1A3E5
		cmp	ax, 70h	; 'p'
		jz	short loc_1A40E
		jmp	short loc_1A41C
; ---------------------------------------------------------------------------

loc_1A3E5:				; CODE XREF: sub_1A3C3+19j
		push	53D2h
		mov	al, byte_25A07
		mov	ah, 0
		imul	ax, 5
		mov	dl, byte_2671F
		mov	dh, 0
		mov	bx, 6
		push	ax
		mov	ax, dx
		cwd
		idiv	bx
		pop	bx
		add	bx, dx
		mov	al, [bx+1ED4h]
		push	ax
		push	8
		call	sub_13DF2
		jmp	short loc_1A41C
; ---------------------------------------------------------------------------

loc_1A40E:				; CODE XREF: sub_1A3C3+1Ej
		mov	word_2671A, 0
		inc	byte_2671F
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A41C:				; CODE XREF: sub_1A3C3+20j
					; sub_1A3C3+49j
		mov	ax, word_26712
		add	word ptr dword_2670A, ax
		mov	ax, word_26714
		add	word ptr dword_2670A+2,	ax
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A42E:				; CODE XREF: sub_1A3C3+11j
		push	large 0C000500h
		call	sub_1A439
		pop	bp
		retn
sub_1A3C3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A439	proc near		; CODE XREF: sub_1A3C3+71p
					; seg003:7B20p	...

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_2]
		mov	di, [bp+arg_0]
		cmp	word_2671A, 40h	; '@'
		jge	short loc_1A457
		cmp	byte_25A06, 0
		jz	short loc_1A461
		call	sub_1A7BC
		jmp	short loc_1A461
; ---------------------------------------------------------------------------

loc_1A457:				; CODE XREF: sub_1A439+10j
		cmp	byte_25A06, 0
		jnz	short loc_1A461
		call	sub_1A831

loc_1A461:				; CODE XREF: sub_1A439+17j
					; sub_1A439+1Cj ...
		mov	ax, word_2671A
		cmp	ax, 40h	; '@'
		jz	short loc_1A470
		cmp	ax, 80h	; '€'
		jz	short loc_1A492
		jmp	short loc_1A4A0
; ---------------------------------------------------------------------------

loc_1A470:				; CODE XREF: sub_1A439+2Ej
		mov	word ptr dword_2670A, si
		mov	word ptr dword_2670A+2,	di
		cmp	byte_25A1B, 0
		jz	short loc_1A4A0
		mov	byte_25A1B, 2
		mov	ax, 1800h
		sub	ax, si
		mov	word_25A0C, ax
		mov	word_25A0E, di
		jmp	short loc_1A4A0
; ---------------------------------------------------------------------------

loc_1A492:				; CODE XREF: sub_1A439+33j
		mov	word_2671A, 0
		inc	byte_2671F
		mov	al, 1
		jmp	short loc_1A4A2
; ---------------------------------------------------------------------------

loc_1A4A0:				; CODE XREF: sub_1A439+35j
					; sub_1A439+44j ...
		mov	al, 0

loc_1A4A2:				; CODE XREF: sub_1A439+65j
		pop	di
		pop	si
		pop	bp
		retn	4
sub_1A439	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A4A8	proc near		; CODE XREF: seg003:7BC9p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 1
		jnz	short loc_1A4BD
		mov	word_26712, 20h	; ' '
		mov	byte_2671E, 0

loc_1A4BD:				; CODE XREF: sub_1A4A8+8j
		mov	ax, word_26712
		add	word ptr dword_2670A, ax
		cmp	word ptr dword_2670A, 300h
		jle	short loc_1A4D4
		cmp	word ptr dword_2670A, 1500h
		jl	short loc_1A4DE

loc_1A4D4:				; CODE XREF: sub_1A4A8+22j
		mov	ax, 0FFFFh
		imul	word_26712
		mov	word_26712, ax

loc_1A4DE:				; CODE XREF: sub_1A4A8+2Aj
		push	large 5000300h
		mov	al, byte_2671E
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4E6h]
		call	sub_13320
		mov	word ptr dword_2670A+2,	ax
		mov	al, byte_2671E
		add	al, 2
		mov	byte_2671E, al
		pop	bp
		retn
sub_1A4A8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A503	proc near		; CODE XREF: seg003:7C07p
					; sub_1CCB8:loc_1B790p
		push	bp
		mov	bp, sp
		cmp	byte_25A06, 0
		jnz	short loc_1A512
		call	sub_1A831
		jmp	short loc_1A539
; ---------------------------------------------------------------------------

loc_1A512:				; CODE XREF: sub_1A503+8j
		mov	byte_25A08, 0
		cmp	word ptr dword_2670A, 0C00h
		jge	short loc_1A526
		add	word ptr dword_2670A, 10h
		jmp	short loc_1A539
; ---------------------------------------------------------------------------

loc_1A526:				; CODE XREF: sub_1A503+1Aj
		cmp	word ptr dword_2670A, 0C10h
		jl	short loc_1A535
		sub	word ptr dword_2670A, 10h
		jmp	short loc_1A539
; ---------------------------------------------------------------------------

loc_1A535:				; CODE XREF: sub_1A503+29j
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A539:				; CODE XREF: sub_1A503+Dj
					; sub_1A503+21j ...
		mov	al, 0
		pop	bp
		retn
sub_1A503	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A53D	proc near		; CODE XREF: sub_1AB5D+Ap
					; sub_1AD6F+11p ...

var_2		= word ptr -2

		enter	2, 0
		mov	byte_25A06, 1
		inc	word_25A0A
		mov	ax, word_25A0A
		mov	[bp+var_2], ax
		mov	cx, 5		; switch 5 cases
		mov	bx, offset word_1A598

loc_1A556:				; CODE XREF: sub_1A53D+24j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A565
		add	bx, 2
		loop	loc_1A556
		jmp	short loc_1A594	; default
; ---------------------------------------------------------------------------

loc_1A565:				; CODE XREF: sub_1A53D+1Fj
		jmp	word ptr cs:[bx+0Ah] ; switch jump

loc_1A569:				; DATA XREF: seg003:6B12o
		mov	byte_26718, 80h	; '€' ; jumptable 0001A565 case 1
		jmp	short loc_1A594	; default
; ---------------------------------------------------------------------------

loc_1A570:				; CODE XREF: sub_1A53D:loc_1A565j
					; DATA XREF: seg003:6B12o
		mov	byte_26718, 82h	; '‚' ; jumptable 0001A565 case 7
		jmp	short loc_1A594	; default
; ---------------------------------------------------------------------------

loc_1A577:				; CODE XREF: sub_1A53D:loc_1A565j
					; DATA XREF: seg003:6B12o
		mov	byte_26718, 84h	; '„' ; jumptable 0001A565 case 13
		jmp	short loc_1A594	; default
; ---------------------------------------------------------------------------

loc_1A57E:				; CODE XREF: sub_1A53D:loc_1A565j
					; DATA XREF: seg003:6B12o
		mov	byte_26718, 86h	; '†' ; jumptable 0001A565 case 19
		jmp	short loc_1A594	; default
; ---------------------------------------------------------------------------

loc_1A585:				; CODE XREF: sub_1A53D:loc_1A565j
					; DATA XREF: seg003:6B12o
		mov	word_25A0A, 0	; jumptable 0001A565 case 25
		mov	byte_25A06, 2

loc_1A590:				; CODE XREF: sub_1EA4B:loc_1EA6Bj
		mov	al, 1		; jumptable 0001EA6B case 13291
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A594:				; CODE XREF: sub_1A53D+26j
					; sub_1A53D+31j ...
		mov	al, 0		; default
		leave
		retn
sub_1A53D	endp

; ---------------------------------------------------------------------------
word_1A598	dw	1,     7,   0Dh,   13h ; DATA XREF: sub_1A53D+16o
		dw    19h		; value	table for switch statement
		dw offset loc_1A569	; jump table for switch	statement
		dw offset loc_1A570
		dw offset loc_1A577
		dw offset loc_1A57E
		dw offset loc_1A585

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A5AC	proc near		; CODE XREF: sub_1ACCC+Ap
					; sub_1AD6F:loc_1ADBAp	...

var_2		= word ptr -2

		enter	2, 0
		mov	byte_25A06, 2
		inc	word_25A0A
		mov	ax, word_25A0A
		mov	[bp+var_2], ax
		mov	cx, 5		; switch 5 cases
		mov	bx, offset word_1A608

loc_1A5C5:				; CODE XREF: sub_1A5AC+24j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A5D4
		add	bx, 2
		loop	loc_1A5C5
		jmp	short loc_1A603	; default
; ---------------------------------------------------------------------------

loc_1A5D4:				; CODE XREF: sub_1A5AC+1Fj
		jmp	word ptr cs:[bx+0Ah] ; switch jump

loc_1A5D8:				; DATA XREF: seg003:6B82o
		mov	byte_26718, 86h	; '†' ; jumptable 0001A5D4 case 1
		jmp	short loc_1A603	; default
; ---------------------------------------------------------------------------

loc_1A5DF:				; CODE XREF: sub_1A5AC:loc_1A5D4j
					; DATA XREF: seg003:6B82o
		mov	byte_26718, 84h	; '„' ; jumptable 0001A5D4 case 7
		jmp	short loc_1A603	; default
; ---------------------------------------------------------------------------

loc_1A5E6:				; CODE XREF: sub_1A5AC:loc_1A5D4j
					; DATA XREF: seg003:6B82o
		mov	byte_26718, 82h	; '‚' ; jumptable 0001A5D4 case 13
		jmp	short loc_1A603	; default
; ---------------------------------------------------------------------------

loc_1A5ED:				; CODE XREF: sub_1A5AC:loc_1A5D4j
					; DATA XREF: seg003:6B82o
		mov	byte_26718, 80h	; '€' ; jumptable 0001A5D4 case 19
		jmp	short loc_1A603	; default
; ---------------------------------------------------------------------------

loc_1A5F4:				; CODE XREF: sub_1A5AC:loc_1A5D4j
					; DATA XREF: seg003:6B82o
		mov	word_25A0A, 0	; jumptable 0001A5D4 case 25
		mov	byte_25A06, 1
		mov	al, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A603:				; CODE XREF: sub_1A5AC+26j
					; sub_1A5AC+31j ...
		mov	al, 0		; default
		leave
		retn
sub_1A5AC	endp

; ---------------------------------------------------------------------------
		db 0
word_1A608	dw	1,     7,   0Dh,   13h ; DATA XREF: sub_1A5AC+16o
		dw    19h		; value	table for switch statement
		dw offset loc_1A5D8	; jump table for switch	statement
		dw offset loc_1A5DF
		dw offset loc_1A5E6
		dw offset loc_1A5ED
		dw offset loc_1A5F4

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A61C	proc near		; CODE XREF: sub_1AD6F+1Dp
					; sub_1AE8F+1Dp ...

var_2		= word ptr -2

		enter	2, 0
		inc	word_25A0A
		mov	ax, word_25A0A
		mov	[bp+var_2], ax
		mov	cx, 5		; switch 5 cases
		mov	bx, offset word_1A672

loc_1A630:				; CODE XREF: sub_1A61C+1Fj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A63F
		add	bx, 2
		loop	loc_1A630
		jmp	short loc_1A66E	; default
; ---------------------------------------------------------------------------

loc_1A63F:				; CODE XREF: sub_1A61C+1Aj
		jmp	word ptr cs:[bx+0Ah] ; switch jump

loc_1A643:				; DATA XREF: seg003:6BECo
		mov	byte_26718, 86h	; '†' ; jumptable 0001A63F case 1
		jmp	short loc_1A66E	; default
; ---------------------------------------------------------------------------

loc_1A64A:				; CODE XREF: sub_1A61C:loc_1A63Fj
					; DATA XREF: seg003:6BECo
		mov	byte_26718, 88h	; 'ˆ' ; jumptable 0001A63F case 7
		jmp	short loc_1A66E	; default
; ---------------------------------------------------------------------------

loc_1A651:				; CODE XREF: sub_1A61C:loc_1A63Fj
					; DATA XREF: seg003:6BECo
		mov	byte_26718, 98h	; '˜' ; jumptable 0001A63F case 13
		jmp	short loc_1A66E	; default
; ---------------------------------------------------------------------------

loc_1A658:				; CODE XREF: sub_1A61C:loc_1A63Fj
					; DATA XREF: seg003:6BECo
		mov	byte_26718, 8Ah	; 'Š' ; jumptable 0001A63F case 19
		jmp	short loc_1A66E	; default
; ---------------------------------------------------------------------------

loc_1A65F:				; CODE XREF: sub_1A61C:loc_1A63Fj
					; DATA XREF: seg003:6BECo
		mov	word_25A0A, 0	; jumptable 0001A63F case 25
		mov	byte_25A06, 3
		mov	al, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A66E:				; CODE XREF: sub_1A61C+21j
					; sub_1A61C+2Cj ...
		mov	al, 0		; default
		leave
		retn
sub_1A61C	endp

; ---------------------------------------------------------------------------
word_1A672	dw	1,     7,   0Dh,   13h ; DATA XREF: sub_1A61C+11o
		dw    19h		; value	table for switch statement
		dw offset loc_1A643	; jump table for switch	statement
		dw offset loc_1A64A
		dw offset loc_1A651
		dw offset loc_1A658
		dw offset loc_1A65F

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A686	proc near		; CODE XREF: sub_1ABE5+14p

var_2		= word ptr -2

		enter	2, 0
		inc	word_25A0A
		mov	ax, word_25A0A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1A6D5

loc_1A69A:				; CODE XREF: sub_1A686+1Fj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A6A9
		add	bx, 2
		loop	loc_1A69A
		jmp	short loc_1A6D1	; default
; ---------------------------------------------------------------------------

loc_1A6A9:				; CODE XREF: sub_1A686+1Aj
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1A6AD:				; DATA XREF: seg003:6C4Do
		mov	byte_26718, 86h	; '†' ; jumptable 0001A6A9 case 1
		jmp	short loc_1A6D1	; default
; ---------------------------------------------------------------------------

loc_1A6B4:				; CODE XREF: sub_1A686:loc_1A6A9j
					; DATA XREF: seg003:6C4Do
		mov	byte_26718, 88h	; 'ˆ' ; jumptable 0001A6A9 case 7
		jmp	short loc_1A6D1	; default
; ---------------------------------------------------------------------------

loc_1A6BB:				; CODE XREF: sub_1A686:loc_1A6A9j
					; DATA XREF: seg003:6C4Do
		mov	byte_26718, 96h	; '–' ; jumptable 0001A6A9 case 13
		jmp	short loc_1A6D1	; default
; ---------------------------------------------------------------------------

loc_1A6C2:				; CODE XREF: sub_1A686:loc_1A6A9j
					; DATA XREF: seg003:6C4Do
		mov	word_25A0A, 0	; jumptable 0001A6A9 case 19
		mov	byte_25A06, 4
		mov	al, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A6D1:				; CODE XREF: sub_1A686+21j
					; sub_1A686+2Cj ...
		mov	al, 0		; default
		leave
		retn
sub_1A686	endp

; ---------------------------------------------------------------------------
word_1A6D5	dw	1,     7,   0Dh,   13h ; DATA XREF: sub_1A686+11o
					; value	table for switch statement
		dw offset loc_1A6AD	; jump table for switch	statement
		dw offset loc_1A6B4
		dw offset loc_1A6BB
		dw offset loc_1A6C2

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A6E5	proc near		; CODE XREF: sub_1ABE5+23p
					; sub_1AD6F+46p ...
		push	bp
		mov	bp, sp
		inc	word_25A0A
		mov	bx, word_25A0A
		dec	bx
		cmp	bx, 27h	; '''
		ja	short loc_1A767
		add	bx, bx
		jmp	cs:off_1A76C[bx]

loc_1A6FD:				; DATA XREF: seg003:off_1A76Co
		mov	byte_26718, 96h	; '–'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A704:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6CE2o
		mov	byte_26718, 98h	; '˜'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A70B:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6CE8o
		mov	byte_26718, 9Ah	; 'š'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A712:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6CEEo
		mov	byte_26718, 9Ch	; 'œ'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A719:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6CF4o
		mov	byte_26718, 9Eh	; 'ž'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A720:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6CFAo
		mov	byte_26718, 0A0h ; ' '
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A727:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6D00o
		mov	byte_26718, 0A2h ; '¢'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A72E:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6D06o
		mov	byte_26718, 0A4h ; '¤'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A735:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6D0Co
		mov	byte_26718, 0A6h ; '¦'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A73C:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6D12o
		mov	byte_26718, 0A8h ; '¨'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A743:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6D18o
		mov	byte_26718, 0AAh ; 'ª'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A74A:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6D1Eo
		mov	byte_26718, 0ACh ; '¬'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A751:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6D24o
		mov	byte_26718, 86h	; '†'
		jmp	short loc_1A767
; ---------------------------------------------------------------------------

loc_1A758:				; CODE XREF: sub_1A6E5+13j
					; DATA XREF: seg003:6D2Ao
		mov	word_25A0A, 0
		mov	byte_25A06, 2
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1A767:				; CODE XREF: sub_1A6E5+Fj
					; sub_1A6E5+13j ...
		mov	al, 0
		pop	bp
		retn
sub_1A6E5	endp

; ---------------------------------------------------------------------------
		db 0
off_1A76C	dw offset loc_1A6FD	; DATA XREF: sub_1A6E5+13r
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A704
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A70B
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A712
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A719
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A720
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A727
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A72E
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A735
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A73C
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A743
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A74A
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A751
		dw offset loc_1A767
		dw offset loc_1A767
		dw offset loc_1A758

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A7BC	proc near		; CODE XREF: sub_1A439+19p
					; seg003:7BAFp

var_2		= word ptr -2

		enter	2, 0
		inc	word_25A0A
		mov	ax, word_25A0A
		mov	[bp+var_2], ax
		mov	cx, 6		; switch 6 cases
		mov	bx, offset word_1A819

loc_1A7D0:				; CODE XREF: sub_1A7BC+1Fj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A7DF
		add	bx, 2
		loop	loc_1A7D0
		jmp	short loc_1A815	; default
; ---------------------------------------------------------------------------

loc_1A7DF:				; CODE XREF: sub_1A7BC+1Aj
		jmp	word ptr cs:[bx+0Ch] ; switch jump

loc_1A7E3:				; DATA XREF: seg003:6D95o
		mov	byte_26718, 0AEh ; '®' ; jumptable 0001A7DF case 1
		jmp	short loc_1A815	; default
; ---------------------------------------------------------------------------

loc_1A7EA:				; CODE XREF: sub_1A7BC:loc_1A7DFj
					; DATA XREF: seg003:6D95o
		mov	byte_26718, 0B0h ; '°' ; jumptable 0001A7DF case 8
		jmp	short loc_1A815	; default
; ---------------------------------------------------------------------------

loc_1A7F1:				; CODE XREF: sub_1A7BC:loc_1A7DFj
					; DATA XREF: seg003:6D95o
		mov	byte_26718, 0B2h ; '²' ; jumptable 0001A7DF case 15
		jmp	short loc_1A815	; default
; ---------------------------------------------------------------------------

loc_1A7F8:				; CODE XREF: sub_1A7BC:loc_1A7DFj
					; DATA XREF: seg003:6D95o
		mov	byte_26718, 0B4h ; '´' ; jumptable 0001A7DF case 22
		jmp	short loc_1A815	; default
; ---------------------------------------------------------------------------

loc_1A7FF:				; CODE XREF: sub_1A7BC:loc_1A7DFj
					; DATA XREF: seg003:6D95o
		mov	byte_26718, 0	; jumptable 0001A7DF case 29
		jmp	short loc_1A815	; default
; ---------------------------------------------------------------------------

loc_1A806:				; CODE XREF: sub_1A7BC:loc_1A7DFj
					; DATA XREF: seg003:6D95o
		mov	word_25A0A, 0	; jumptable 0001A7DF case 36
		mov	byte_25A06, 0
		mov	al, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A815:				; CODE XREF: sub_1A7BC+21j
					; sub_1A7BC+2Cj ...
		mov	al, 0		; default
		leave
		retn
sub_1A7BC	endp

; ---------------------------------------------------------------------------
word_1A819	dw	1,     8,   0Fh,   16h ; DATA XREF: sub_1A7BC+11o
		dw    1Dh,   24h	; value	table for switch statement
		dw offset loc_1A7E3	; jump table for switch	statement
		dw offset loc_1A7EA
		dw offset loc_1A7F1
		dw offset loc_1A7F8
		dw offset loc_1A7FF
		dw offset loc_1A806

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A831	proc near		; CODE XREF: sub_1A439+25p
					; sub_1A503+Ap

var_2		= word ptr -2

		enter	2, 0
		inc	word_25A0A
		mov	ax, word_25A0A
		mov	[bp+var_2], ax
		mov	cx, 6		; switch 6 cases
		mov	bx, offset word_1A88F

loc_1A845:				; CODE XREF: sub_1A831+1Fj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A854
		add	bx, 2
		loop	loc_1A845
		jmp	short loc_1A88A	; default
; ---------------------------------------------------------------------------

loc_1A854:				; CODE XREF: sub_1A831+1Aj
		jmp	word ptr cs:[bx+0Ch] ; switch jump

loc_1A858:				; DATA XREF: seg003:6E0Bo
		mov	byte_26718, 0B4h ; '´' ; jumptable 0001A854 case 1
		jmp	short loc_1A88A	; default
; ---------------------------------------------------------------------------

loc_1A85F:				; CODE XREF: sub_1A831:loc_1A854j
					; DATA XREF: seg003:6E0Bo
		mov	byte_26718, 0B2h ; '²' ; jumptable 0001A854 case 8
		jmp	short loc_1A88A	; default
; ---------------------------------------------------------------------------

loc_1A866:				; CODE XREF: sub_1A831:loc_1A854j
					; DATA XREF: seg003:6E0Bo
		mov	byte_26718, 0B0h ; '°' ; jumptable 0001A854 case 15
		jmp	short loc_1A88A	; default
; ---------------------------------------------------------------------------

loc_1A86D:				; CODE XREF: sub_1A831:loc_1A854j
					; DATA XREF: seg003:6E0Bo
		mov	byte_26718, 0AEh ; '®' ; jumptable 0001A854 case 22
		jmp	short loc_1A88A	; default
; ---------------------------------------------------------------------------

loc_1A874:				; CODE XREF: sub_1A831:loc_1A854j
					; DATA XREF: seg003:6E0Bo
		mov	byte_26718, 80h	; '€' ; jumptable 0001A854 case 29
		jmp	short loc_1A88A	; default
; ---------------------------------------------------------------------------

loc_1A87B:				; CODE XREF: sub_1A831:loc_1A854j
					; sub_1F3AB:loc_1F539j
					; DATA XREF: ...
		mov	word_25A0A, 0	; jumptable 0001A854 case 36
					; jumptable 0001F539 case 65142
		mov	byte_25A06, 1
		mov	al, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A88A:				; CODE XREF: sub_1A831+21j
					; sub_1A831+2Cj ...
		mov	al, 0		; default
		leave
		retn
sub_1A831	endp

; ---------------------------------------------------------------------------
		db 0
word_1A88F	dw	1,     8,   0Fh,   16h ; DATA XREF: sub_1A831+11o
		dw    1Dh,   24h	; value	table for switch statement
		dw offset loc_1A858	; jump table for switch	statement
		dw offset loc_1A85F
		dw offset loc_1A866
		dw offset loc_1A86D
		dw offset loc_1A874
		dw offset loc_1A87B

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A8A7	proc near		; CODE XREF: sub_1B099+11p

var_2		= word ptr -2

		enter	2, 0
		inc	word_25A0A
		mov	ax, word_25A0A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1A8F7

loc_1A8BB:				; CODE XREF: sub_1A8A7+1Fj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A8CA
		add	bx, 2
		loop	loc_1A8BB
		jmp	short loc_1A8F2	; default
; ---------------------------------------------------------------------------

loc_1A8CA:				; CODE XREF: sub_1A8A7+1Aj
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1A8CE:				; DATA XREF: seg003:6E6Fo
		mov	byte_26718, 80h	; '€' ; jumptable 0001A8CA case 1
		jmp	short loc_1A8F2	; default
; ---------------------------------------------------------------------------

loc_1A8D5:				; CODE XREF: sub_1A8A7:loc_1A8CAj
					; DATA XREF: seg003:6E6Fo
		mov	byte_26718, 8Eh	; 'Ž' ; jumptable 0001A8CA case 7
		jmp	short loc_1A8F2	; default
; ---------------------------------------------------------------------------

loc_1A8DC:				; CODE XREF: sub_1A8A7:loc_1A8CAj
					; DATA XREF: seg003:6E6Fo
		mov	byte_26718, 90h	; '' ; jumptable 0001A8CA case 13
		jmp	short loc_1A8F2	; default
; ---------------------------------------------------------------------------

loc_1A8E3:				; CODE XREF: sub_1A8A7:loc_1A8CAj
					; DATA XREF: seg003:6E6Fo
		mov	word_25A0A, 0	; jumptable 0001A8CA case 19
		mov	byte_25A06, 8
		mov	al, 1
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A8F2:				; CODE XREF: sub_1A8A7+21j
					; sub_1A8A7+2Cj ...
		mov	al, 0		; default
		leave
		retn
sub_1A8A7	endp

; ---------------------------------------------------------------------------
		db 0
word_1A8F7	dw	1,     7,   0Dh,   13h ; DATA XREF: sub_1A8A7+11o
					; value	table for switch statement
		dw offset loc_1A8CE	; jump table for switch	statement
		dw offset loc_1A8D5
		dw offset loc_1A8DC
		dw offset loc_1A8E3

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A907	proc near		; CODE XREF: sub_1AB5D:loc_1AB6Ap
					; sub_1ACCC:loc_1AD6Ap

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1A9A5

loc_1A917:				; CODE XREF: sub_1A907+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A926
		add	bx, 2
		loop	loc_1A917
		jmp	short locret_1A9A3 ; default
; ---------------------------------------------------------------------------

loc_1A926:				; CODE XREF: sub_1A907+16j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1A92A:				; DATA XREF: seg003:6F1Do
		push	8		; jumptable 0001A926 case 16
		call	sub_138B2
		mov	word_2A8CE, 1400h
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FFC0h
		mov	word ptr dword_2A8C6+2,	ax
		mov	ax, word ptr dword_2670A
		add	ax, 180h
		mov	word ptr dword_2A8C6, ax
		mov	word_2A8D0, 10h
		mov	byte_2A8D2, 9
		mov	byte_2A8D3, 0FEh ; 'þ'

loc_1A959:				; CODE XREF: sub_1A907:loc_1A926j
					; DATA XREF: seg003:6F1Do
		call	sub_13B21	; jumptable 0001A926 case 20
		sub	word ptr dword_2A8C6, 2C0h
		mov	byte_2A8D3, 2

loc_1A967:				; CODE XREF: sub_1A907+78j
		call	sub_13B21
		leave
		retn
; ---------------------------------------------------------------------------

loc_1A96C:				; CODE XREF: sub_1A907:loc_1A926j
					; DATA XREF: seg003:6F1Do
		mov	byte_2A8D2, 8	; jumptable 0001A926 case 18
		call	sub_13B21
		add	word ptr dword_2A8C6, 2C0h
		mov	byte_2A8D3, 0FEh ; 'þ'
		jmp	short loc_1A967
; ---------------------------------------------------------------------------

loc_1A981:				; CODE XREF: sub_1A907:loc_1A926j
					; DATA XREF: seg003:6F1Do
		push	word ptr dword_2A8C6 ; jumptable 0001A926 case 32
		push	word ptr dword_2A8C6+2
		call	sub_C696
		mov	ax, word ptr dword_2A8C6
		add	ax, 2C0h
		push	ax
		push	word ptr dword_2A8C6+2
		call	sub_C696
		mov	byte_25592, 0Fh

locret_1A9A3:				; CODE XREF: sub_1A907+1Dj
		leave			; default
		retn
sub_1A907	endp

; ---------------------------------------------------------------------------
word_1A9A5	dw    10h,   12h,   14h,   20h ; DATA XREF: sub_1A907+Do
					; value	table for switch statement
		dw offset loc_1A92A	; jump table for switch	statement
		dw offset loc_1A96C
		dw offset loc_1A959
		dw offset loc_1A981

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A9B5	proc near		; CODE XREF: sub_1A9CA:loc_1AA14p
					; sub_1AA45+4Ap ...
		push	bp
		mov	bp, sp
		mov	byte_2A8D3, 0FEh ; 'þ'
		call	sub_13B21
		mov	byte_2A8D3, 2
		call	sub_13B21
		pop	bp
		retn
sub_1A9B5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1A9CA	proc near		; CODE XREF: sub_1AD6F:loc_1ADCCp

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1AA35

loc_1A9DA:				; CODE XREF: sub_1A9CA+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1A9E9
		add	bx, 2
		loop	loc_1A9DA
		jmp	short locret_1AA32 ; default
; ---------------------------------------------------------------------------

loc_1A9E9:				; CODE XREF: sub_1A9CA+16j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1A9ED:				; DATA XREF: seg003:6FADo
		push	8		; jumptable 0001A9E9 case 48
		call	sub_138B2
		mov	word_2A8CE, 1400h
		mov	ax, word ptr dword_2670A+2
		add	ax, 200h
		mov	word ptr dword_2A8C6+2,	ax
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_2A8C6, ax
		mov	word_2A8D0, 8
		mov	byte_2A8D2, 9

loc_1AA14:				; CODE XREF: sub_1A9CA:loc_1A9E9j
					; sub_1A9CA+54j
					; DATA XREF: ...
		call	sub_1A9B5	; jumptable 0001A9E9 case 52
		leave
		retn
; ---------------------------------------------------------------------------

loc_1AA19:				; CODE XREF: sub_1A9CA:loc_1A9E9j
					; DATA XREF: seg003:6FADo
		mov	byte_2A8D2, 8	; jumptable 0001A9E9 case 50
		jmp	short loc_1AA14	; jumptable 0001A9E9 case 52
; ---------------------------------------------------------------------------

loc_1AA20:				; CODE XREF: sub_1A9CA:loc_1A9E9j
					; DATA XREF: seg003:6FADo
		push	word ptr dword_2A8C6 ; jumptable 0001A9E9 case 64
		push	word ptr dword_2A8C6+2
		call	sub_C696
		mov	byte_25592, 0Fh

locret_1AA32:				; CODE XREF: sub_1A9CA+1Dj
		leave			; default
		retn
sub_1A9CA	endp

; ---------------------------------------------------------------------------
		db 0
word_1AA35	dw    30h,   32h,   34h,   40h ; DATA XREF: sub_1A9CA+Do
					; value	table for switch statement
		dw offset loc_1A9ED	; jump table for switch	statement
		dw offset loc_1AA19
		dw offset loc_1AA14
		dw offset loc_1AA20

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AA45	proc near		; CODE XREF: sub_1AE8F:loc_1AF59p
					; sub_1AFA8:loc_1B094p	...

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1AAD5

loc_1AA55:				; CODE XREF: sub_1AA45+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1AA64
		add	bx, 2
		loop	loc_1AA55
		jmp	short locret_1AAD2 ; default
; ---------------------------------------------------------------------------

loc_1AA64:				; CODE XREF: sub_1AA45+16j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1AA68:				; DATA XREF: seg003:704Do
		push	8		; jumptable 0001AA64 case 32
		call	sub_138B2
		mov	word_2A8CE, 1400h
		mov	word_2A8D0, 8
		mov	byte_2A8D2, 9

loc_1AA80:				; CODE XREF: sub_1AA45:loc_1AA64j
					; sub_1AA45+66j
					; DATA XREF: ...
		mov	ax, word ptr dword_2670A+2 ; jumptable 0001AA64	case 36
		add	ax, 200h
		mov	word ptr dword_2A8C6+2,	ax
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_2A8C6, ax
		call	sub_1A9B5
		mov	ax, word_25A0E
		add	ax, 200h
		mov	word ptr dword_2A8C6+2,	ax
		mov	ax, word_25A0C
		mov	word ptr dword_2A8C6, ax
		call	sub_1A9B5
		leave
		retn
; ---------------------------------------------------------------------------

loc_1AAA6:				; CODE XREF: sub_1AA45:loc_1AA64j
					; DATA XREF: seg003:704Do
		mov	byte_2A8D2, 8	; jumptable 0001AA64 case 34
		jmp	short loc_1AA80	; jumptable 0001AA64 case 36
; ---------------------------------------------------------------------------

loc_1AAAD:				; CODE XREF: sub_1AA45:loc_1AA64j
					; DATA XREF: seg003:704Do
		push	word ptr dword_2670A ; jumptable 0001AA64 case 48
		mov	ax, word ptr dword_2670A+2
		add	ax, 200h
		push	ax
		call	sub_C696
		push	word_25A0C
		mov	ax, word_25A0E
		add	ax, 200h
		push	ax
		call	sub_C696
		mov	byte_25592, 0Fh

locret_1AAD2:				; CODE XREF: sub_1AA45+1Dj
		leave			; default
		retn
sub_1AA45	endp

; ---------------------------------------------------------------------------
		db 0
word_1AAD5	dw    20h,   22h,   24h,   30h ; DATA XREF: sub_1AA45+Do
					; value	table for switch statement
		dw offset loc_1AA68	; jump table for switch	statement
		dw offset loc_1AAA6
		dw offset loc_1AA80
		dw offset loc_1AAAD

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AAE5	proc near		; CODE XREF: sub_1B099:loc_1B125p
					; sub_1B1B1:loc_1B213p

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1AB4D

loc_1AAF5:				; CODE XREF: sub_1AAE5+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1AB04
		add	bx, 2
		loop	loc_1AAF5
		jmp	short locret_1AB4A ; default
; ---------------------------------------------------------------------------

loc_1AB04:				; CODE XREF: sub_1AAE5+16j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1AB08:				; DATA XREF: seg003:70C5o
		push	8		; jumptable 0001AB04 case 16
		call	sub_138B2
		mov	word_2A8CE, 1400h
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_2A8C6+2,	ax
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_2A8C6, ax
		mov	word_2A8D0, 10h
		mov	byte_2A8D2, 7

loc_1AB2C:				; CODE XREF: sub_1AAE5:loc_1AB04j
					; sub_1AAE5+51j
					; DATA XREF: ...
		call	sub_1A9B5	; jumptable 0001AB04 case 20
		leave
		retn
; ---------------------------------------------------------------------------

loc_1AB31:				; CODE XREF: sub_1AAE5:loc_1AB04j
					; DATA XREF: seg003:70C5o
		mov	byte_2A8D2, 6	; jumptable 0001AB04 case 18
		jmp	short loc_1AB2C	; jumptable 0001AB04 case 20
; ---------------------------------------------------------------------------

loc_1AB38:				; CODE XREF: sub_1AAE5:loc_1AB04j
					; DATA XREF: seg003:70C5o
		push	word ptr dword_2A8C6 ; jumptable 0001AB04 case 32
		push	word ptr dword_2A8C6+2
		call	sub_C696
		mov	byte_25592, 0Fh

locret_1AB4A:				; CODE XREF: sub_1AAE5+1Dj
		leave			; default
		retn
sub_1AAE5	endp

; ---------------------------------------------------------------------------
		db 0
word_1AB4D	dw    10h,   12h,   14h,   20h ; DATA XREF: sub_1AAE5+Do
					; value	table for switch statement
		dw offset loc_1AB08	; jump table for switch	statement
		dw offset loc_1AB31
		dw offset loc_1AB2C
		dw offset loc_1AB38

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AB5D	proc near		; CODE XREF: seg003:loc_1B554p
		push	bp
		mov	bp, sp
		cmp	byte_25A06, 1
		jnz	short loc_1AB6A
		call	sub_1A53D

loc_1AB6A:				; CODE XREF: sub_1AB5D+8j
		call	sub_1A907
		mov	ax, word_2671A
		cmp	ax, 30h	; '0'
		jz	short loc_1AB81
		cmp	ax, 40h	; '@'
		jz	short loc_1AB86
		cmp	ax, 50h	; 'P'
		jz	short loc_1ABD8
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1AB81:				; CODE XREF: sub_1AB5D+16j
		mov	byte_266EE, 28h	; '('

loc_1AB86:				; CODE XREF: sub_1AB5D+1Bj
		mov	byte_266E2, 2
		mov	byte_266E3, 3Bh	; ';'
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FFC0h
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266ED, 0
		mov	byte_266EC, 26h	; '&'
		mov	byte_266F2, 81h	; ''
		mov	byte_266EF, 14h
		mov	byte_2CFF8, 0C0h ; 'À'
		call	word_2D004
		call	sub_1CFB5
		mov	byte_2CFF8, 40h	; '@'
		call	sub_1CFB5
		push	9
		call	sub_138B2
		mov	al, byte_266EE
		add	al, 10h
		mov	byte_266EE, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1ABD8:				; CODE XREF: sub_1AB5D+20j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		pop	bp
		retn
sub_1AB5D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1ABE5	proc near		; CODE XREF: seg003:loc_1B559p

var_1		= byte ptr -1

		enter	2, 0
		cmp	word_2671A, 30h	; '0'
		jge	short loc_1ABFF
		cmp	byte_25A06, 2
		jnz	loc_1AC96
		call	sub_1A686
		jmp	loc_1AC96
; ---------------------------------------------------------------------------

loc_1ABFF:				; CODE XREF: sub_1ABE5+9j
		cmp	byte_25A06, 4
		jnz	loc_1AC96
		call	sub_1A6E5
		cmp	word_2671A, 50h	; 'P'
		jg	loc_1AC96
		mov	byte_266E2, 1
		mov	byte_266EC, 26h	; '&'
		mov	al, byte_2D01F
		mov	byte_266EF, al
		mov	al, byte ptr word_2671A
		shl	al, 3
		mov	dl, 0
		sub	dl, al
		mov	[bp+var_1], dl
		mov	byte_266EE, 28h	; '('
		mov	al, [bp+var_1]
		mov	byte_266ED, al
		push	53A4h
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		push	220h
		mov	ah, 0
		push	ax
		call	sub_1333C
		call	word_2D000
		mov	al, 80h	; '€'
		sub	al, [bp+var_1]
		mov	[bp+var_1], al
		push	53A4h
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		push	220h
		mov	ah, 0
		push	ax
		call	sub_1333C
		mov	ax, word_2671A
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	dl, 3Ch	; '<'
		sub	dl, al
		mov	byte_266EE, dl
		call	word_2D000
		cmp	byte_266CD, 0
		jnz	short loc_1AC96
		push	9
		call	sub_138B2

loc_1AC96:				; CODE XREF: sub_1ABE5+10j
					; sub_1ABE5+17j ...
		mov	ax, word_2671A
		cmp	ax, 20h	; ' '
		jz	short loc_1ACA5
		cmp	ax, 60h	; '`'
		jz	short loc_1ACBF
		leave
		retn
; ---------------------------------------------------------------------------

loc_1ACA5:				; CODE XREF: sub_1ABE5+B7j
		mov	ax, word ptr dword_2670A
		add	ax, 0FD80h
		push	ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 280h
		push	ax
		call	sub_C696
		mov	byte_25592, 0Fh
		leave
		retn
; ---------------------------------------------------------------------------

loc_1ACBF:				; CODE XREF: sub_1ABE5+BCj
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		leave
		retn
sub_1ABE5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1ACCC	proc near		; CODE XREF: seg003:loc_1B55Ep
		push	bp
		mov	bp, sp
		cmp	byte_25A06, 2
		jnz	short loc_1ACD9
		call	sub_1A5AC

loc_1ACD9:				; CODE XREF: sub_1ACCC+8j
		cmp	word_2671A, 30h	; '0'
		jl	short loc_1AD58
		cmp	word_2671A, 50h	; 'P'
		jg	short loc_1AD58
		cmp	byte_266CD, 0
		jnz	short loc_1AD6A
		mov	al, byte_266CE
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		inc	al
		mov	byte_266E2, al
		mov	byte_266E3, 3Ch	; '<'
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FFC0h
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 1Ch
		mov	byte_266EF, 4
		mov	byte_266F2, 88h	; 'ˆ'
		push	18h
		call	sub_13D76
		add	al, 8
		mov	byte_266EE, al
		mov	ax, word ptr dword_2670A
		add	ax, 0FEC0h
		mov	word ptr dword_266E4, ax
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_2CFF7, 1
		call	word_2D004
		call	sub_1CFB5
		call	sub_13D52
		mov	byte_266ED, al
		add	word ptr dword_266E4, 2C0h
		call	sub_1CFB5
		push	9
		call	sub_138B2
		jmp	short loc_1AD6A
; ---------------------------------------------------------------------------

loc_1AD58:				; CODE XREF: sub_1ACCC+12j
					; sub_1ACCC+19j
		cmp	word_2671A, 50h	; 'P'
		jle	short loc_1AD6A
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1AD6A:				; CODE XREF: sub_1ACCC+20j
					; sub_1ACCC+8Aj ...
		call	sub_1A907
		pop	bp
		retn
sub_1ACCC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AD6F	proc near		; CODE XREF: seg003:loc_1B5DBp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 40h	; '@'
		jge	short loc_1AD91
		cmp	byte_25A06, 1
		jnz	short loc_1AD85
		call	sub_1A53D
		jmp	short loc_1ADCC
; ---------------------------------------------------------------------------

loc_1AD85:				; CODE XREF: sub_1AD6F+Fj
		cmp	byte_25A06, 2
		jnz	short loc_1ADCC
		call	sub_1A61C
		jmp	short loc_1ADCC
; ---------------------------------------------------------------------------

loc_1AD91:				; CODE XREF: sub_1AD6F+8j
		cmp	word_2671A, 40h	; '@'
		jl	short loc_1ADA6
		cmp	word_2671A, 70h	; 'p'
		jg	short loc_1ADA6
		mov	byte_26718, 8Ch	; 'Œ'
		jmp	short loc_1ADCC
; ---------------------------------------------------------------------------

loc_1ADA6:				; CODE XREF: sub_1AD6F+27j
					; sub_1AD6F+2Ej
		cmp	word_2671A, 120h
		jl	short loc_1ADCC
		cmp	byte_25A06, 2
		jz	short loc_1ADBA
		call	sub_1A6E5
		jmp	short loc_1ADCC
; ---------------------------------------------------------------------------

loc_1ADBA:				; CODE XREF: sub_1AD6F+44j
		call	sub_1A5AC
		or	al, al
		jz	short loc_1ADCC
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1ADCC:				; CODE XREF: sub_1AD6F+14j
					; sub_1AD6F+1Bj ...
		call	sub_1A9CA
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_1ADD9
		call	sub_1A0D1

loc_1ADD9:				; CODE XREF: sub_1AD6F+65j
		pop	bp
		retn
sub_1AD6F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1ADDB	proc near		; CODE XREF: seg003:7BC2p
		push	bp
		mov	bp, sp
		cmp	byte_266CF, 0
		jnz	loc_1AE8D
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		cmp	byte_26719, 6
		jnz	short loc_1AE40
		mov	byte_266E2, 2
		mov	byte_266E3, 3Ch	; '<'
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 10h
		mov	byte_266EE, 1Eh
		call	word_2D004
		call	word_2D000
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		add	al, 2
		mov	byte_266EF, al
		mov	byte_266EE, 22h	; '"'
		jmp	short loc_1AE85
; ---------------------------------------------------------------------------

loc_1AE40:				; CODE XREF: sub_1ADDB+1Dj
		mov	byte_266E2, 4
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266ED, 0
		mov	byte_266EC, 30h	; '0'
		mov	byte_266EF, 7
		mov	byte_266EE, 20h	; ' '
		mov	byte_266F0, 0Ah
		call	word_2D004
		call	sub_1CFA2
		push	0Fh
		call	sub_138B2
		mov	byte_266E2, 1
		mov	byte_266EC, 1Ch
		mov	byte_266EF, 4
		mov	byte_266EE, 18h

loc_1AE85:				; CODE XREF: sub_1ADDB+63j
		call	word_2D004
		call	word_2D000

loc_1AE8D:				; CODE XREF: sub_1ADDB+8j
		pop	bp
		retn
sub_1ADDB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AE8F	proc near		; CODE XREF: seg003:loc_1B6EDp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 40h	; '@'
		jge	short loc_1AEB7
		cmp	byte_25A06, 1
		jnz	short loc_1AEA5
		call	sub_1A53D
		jmp	short loc_1AEAF
; ---------------------------------------------------------------------------

loc_1AEA5:				; CODE XREF: sub_1AE8F+Fj
		cmp	byte_25A06, 2
		jnz	short loc_1AEAF
		call	sub_1A61C

loc_1AEAF:				; CODE XREF: sub_1AE8F+14j
					; sub_1AE8F+1Bj
		mov	byte_266EE, 10h
		jmp	loc_1AF59
; ---------------------------------------------------------------------------

loc_1AEB7:				; CODE XREF: sub_1AE8F+8j
		cmp	word_2671A, 40h	; '@'
		jl	short loc_1AF33
		cmp	word_2671A, 80h	; '€'
		jg	short loc_1AF33
		mov	byte_26718, 8Ch	; 'Œ'
		cmp	byte_266CE, 0
		jnz	loc_1AF59
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266E2, 4
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266F0, 8
		mov	byte_266EF, 3
		call	word_2D004
		mov	byte_266ED, 60h	; '`'
		call	word_2D000
		mov	byte_266ED, 20h	; ' '
		call	word_2D000
		mov	ax, word_25A0C
		mov	word ptr dword_266E4, ax
		call	word_2D000
		mov	byte_266ED, 60h	; '`'
		call	word_2D000
		mov	al, byte_266EE
		add	al, 0Ch
		mov	byte_266EE, al
		push	3
		call	sub_138B2
		jmp	short loc_1AF59
; ---------------------------------------------------------------------------

loc_1AF33:				; CODE XREF: sub_1AE8F+2Dj
					; sub_1AE8F+35j
		cmp	word_2671A, 80h	; '€'
		jl	short loc_1AF59
		cmp	byte_25A06, 2
		jz	short loc_1AF47
		call	sub_1A6E5
		jmp	short loc_1AF59
; ---------------------------------------------------------------------------

loc_1AF47:				; CODE XREF: sub_1AE8F+B1j
		call	sub_1A5AC
		or	al, al
		jz	short loc_1AF59
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1AF59:				; CODE XREF: sub_1AE8F+25j
					; sub_1AE8F+41j ...
		call	sub_1AA45
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_1AFA6
		mov	al, byte_2D01E
		mov	ah, 0
		mov	word_2562A, ax
		mov	word_2562E, 4
		mov	word_25624, 24h	; '$'
		mov	word_25626, 28h	; '('
		mov	byte_25628, 8
		mov	ax, word ptr dword_2670A
		mov	word_2561A, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 200h
		mov	word_2561C, ax
		call	sub_15DBD
		mov	ax, word_25A0C
		mov	word_2561A, ax
		mov	ax, word_25A0E
		add	ax, 280h
		mov	word_2561C, ax
		call	sub_15DBD

loc_1AFA6:				; CODE XREF: sub_1AE8F+D2j
		pop	bp
		retn
sub_1AE8F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1AFA8	proc near		; CODE XREF: seg003:loc_1B6F2p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 40h	; '@'
		jge	short loc_1AFD0
		cmp	byte_25A06, 1
		jnz	short loc_1AFBE
		call	sub_1A53D
		jmp	short loc_1AFC8
; ---------------------------------------------------------------------------

loc_1AFBE:				; CODE XREF: sub_1AFA8+Fj
		cmp	byte_25A06, 2
		jnz	short loc_1AFC8
		call	sub_1A61C

loc_1AFC8:				; CODE XREF: sub_1AFA8+14j
					; sub_1AFA8+1Bj
		mov	byte_2D02D, 2
		jmp	loc_1B094
; ---------------------------------------------------------------------------

loc_1AFD0:				; CODE XREF: sub_1AFA8+8j
		cmp	word_2671A, 40h	; '@'
		jl	loc_1B06E
		cmp	word_2671A, 80h	; '€'
		jg	loc_1B06E
		mov	byte_26718, 8Ch	; 'Œ'
		cmp	byte_266CD, 0
		jnz	loc_1B094
		mov	ax, word ptr dword_2670A+2
		add	ax, 200h
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266E2, 2
		mov	byte_266E3, 5Ch	; '\'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 5
		push	1Fh
		call	sub_13D60
		add	al, 0Ch
		mov	byte_266EE, al
		mov	byte_266F0, 10h
		mov	al, byte_2D02D
		mov	ah, 0
		add	ax, ax
		push	ax
		call	sub_13D76
		mov	dl, 40h	; '@'
		sub	dl, byte_2D02D
		add	al, dl
		mov	byte_266ED, al
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		call	word_2D000
		mov	al, byte_2D02D
		mov	ah, 0
		add	ax, ax
		push	ax
		call	sub_13D76
		mov	dl, 40h	; '@'
		sub	dl, byte_2D02D
		add	al, dl
		mov	byte_266ED, al
		mov	ax, word_25A0C
		mov	word ptr dword_266E4, ax
		call	word_2D000
		push	9

loc_1B05F:				; CODE XREF: sub_1F903:loc_1F922j
		call	sub_138B2
		mov	al, byte_2D02D
		add	al, 6
		mov	byte_2D02D, al
		jmp	short loc_1B094
; ---------------------------------------------------------------------------

loc_1B06E:				; CODE XREF: sub_1AFA8+2Dj
					; sub_1AFA8+37j
		cmp	word_2671A, 80h	; '€'
		jl	short loc_1B094
		cmp	byte_25A06, 2
		jz	short loc_1B082
		call	sub_1A6E5
		jmp	short loc_1B094
; ---------------------------------------------------------------------------

loc_1B082:				; CODE XREF: sub_1AFA8+D3j
		call	sub_1A5AC
		or	al, al
		jz	short loc_1B094
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1B094:				; CODE XREF: sub_1AFA8+25j
					; sub_1AFA8+45j ...
		call	sub_1AA45
		pop	bp
		retn
sub_1AFA8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B099	proc near		; CODE XREF: seg003:loc_1B7E2p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 30h	; '0'
		jg	short loc_1B0AF
		cmp	byte_25A06, 8
		jz	short loc_1B125
		call	sub_1A8A7
		jmp	short loc_1B125
; ---------------------------------------------------------------------------

loc_1B0AF:				; CODE XREF: sub_1B099+8j
		cmp	word_2671A, 88h	; 'ˆ'
		jge	short loc_1B0F0
		mov	al, byte_266CD
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		add	al, al
		add	al, 92h	; '’'
		mov	byte_26718, al
		cmp	byte_266CC, 0
		jz	short loc_1B0D2
		call	sub_1CFA2

loc_1B0D2:				; CODE XREF: sub_1B099+34j
		cmp	byte_266CD, 0
		jnz	short loc_1B0E0
		push	3
		call	sub_138B2

loc_1B0E0:				; CODE XREF: sub_1B099+3Ej
		cmp	word_2671A, 70h	; 'p'
		jl	short loc_1B125
		mov	al, byte_2671E
		add	byte_266ED, al
		jmp	short loc_1B125
; ---------------------------------------------------------------------------

loc_1B0F0:				; CODE XREF: sub_1B099+1Cj
		cmp	byte_25688, 2
		jb	short loc_1B120
		cmp	word_2671A, 96h	; '–'
		jge	short loc_1B120
		mov	al, byte_2671E
		sub	byte_266ED, al
		cmp	byte_266CC, 0
		jz	short loc_1B110
		call	sub_1CFA2

loc_1B110:				; CODE XREF: sub_1B099+72j
		cmp	byte_266CD, 0
		jnz	short loc_1B125
		push	3
		call	sub_138B2
		jmp	short loc_1B125
; ---------------------------------------------------------------------------

loc_1B120:				; CODE XREF: sub_1B099+5Cj
					; sub_1B099+64j
		mov	byte_26718, 92h	; '’'

loc_1B125:				; CODE XREF: sub_1B099+Fj
					; sub_1B099+14j ...
		call	sub_1AAE5
		mov	ax, word_2671A
		cmp	ax, 30h	; '0'
		jz	short loc_1B13C
		cmp	ax, 90h	; ''
		jz	short loc_1B19D
		cmp	ax, 9Ch	; 'œ'
		jz	short loc_1B1A4
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B13C:				; CODE XREF: sub_1B099+95j
		mov	ax, word ptr dword_2670A+2
		sub	ax, word ptr dword_2598E+2
		push	ax
		mov	ax, word ptr dword_2670A
		sub	ax, word ptr dword_2598E
		push	ax
		call	sub_1DA8
		add	al, 10h
		mov	byte_266ED, al
		mov	byte_266E2, 4
		mov	byte_266E3, 3Dh	; '='
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 8
		mov	byte_266EE, 90h	; ''
		cmp	byte_25688, 0
		jz	short loc_1B196
		push	1
		call	sub_13D60
		or	ax, ax
		jz	short loc_1B18F
		mov	al, 1
		jmp	short loc_1B191
; ---------------------------------------------------------------------------

loc_1B18F:				; CODE XREF: sub_1B099+F0j
		mov	al, 0FFh

loc_1B191:				; CODE XREF: sub_1B099+F4j
		mov	byte_2671E, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B196:				; CODE XREF: sub_1B099+E7j
		mov	byte_2671E, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B19D:				; CODE XREF: sub_1B099+9Aj
		cmp	byte_25688, 2
		jnb	short loc_1B1AF

loc_1B1A4:				; CODE XREF: sub_1B099+9Fj
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1B1AF:				; CODE XREF: sub_1B099+109j
		pop	bp
		retn
sub_1B099	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B1B1	proc near		; CODE XREF: seg003:loc_1B7E7p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 30h	; '0'
		jle	short loc_1B20E
		mov	al, byte_266CD
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		add	al, al
		add	al, 92h	; '’'
		mov	byte_26718, al
		cmp	byte_266CE, 0
		jnz	short loc_1B213
		push	3
		call	sub_138B2
		mov	al, byte_266ED
		add	al, 2
		mov	byte_266ED, al
		mov	byte_266EC, 26h	; '&'
		mov	byte_266E2, 2
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EE, 30h	; '0'
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		add	al, 4
		mov	byte_266EF, al
		call	word_2D004
		call	word_2D000
		jmp	short loc_1B213
; ---------------------------------------------------------------------------

loc_1B20E:				; CODE XREF: sub_1B1B1+8j
		mov	byte_26718, 92h	; '’'

loc_1B213:				; CODE XREF: sub_1B1B1+20j
					; sub_1B1B1+5Bj
		call	sub_1AAE5
		cmp	word_2671A, 90h	; ''
		jnz	short loc_1B229
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1B229:				; CODE XREF: sub_1B1B1+6Bj
		pop	bp
		retn
sub_1B1B1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B22B	proc near		; CODE XREF: seg003:loc_1B7ECp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 30h	; '0'
		jle	short loc_1B268
		mov	al, byte_266CD
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		add	al, al
		add	al, 92h	; '’'
		mov	byte_26718, al
		cmp	byte_266CE, 0
		jnz	short loc_1B26D
		call	sub_13D52
		push	ax
		push	20h ; ' '
		call	sub_1A087
		call	sub_13D52
		push	ax
		push	20h ; ' '
		call	sub_1A087
		push	3
		call	sub_138B2
		jmp	short loc_1B26D
; ---------------------------------------------------------------------------

loc_1B268:				; CODE XREF: sub_1B22B+8j
		mov	byte_26718, 92h	; '’'

loc_1B26D:				; CODE XREF: sub_1B22B+20j
					; sub_1B22B+3Bj
		cmp	word_2671A, 90h	; ''
		jnz	short loc_1B280
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1B280:				; CODE XREF: sub_1B22B+48j
		pop	bp
		retn
sub_1B22B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B282	proc near

var_1		= byte ptr -1

		enter	2, 0
		mov	al, byte ptr word_2671A
		and	al, 1Fh
		mov	[bp+var_1], al
		mov	al, byte_266CD
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		add	al, al
		add	al, 92h	; '’'
		mov	byte_26718, al
		test	[bp+var_1], 3
		jnz	short loc_1B2ED
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	al, 3
		sub	al, byte_266E2
		mov	byte_266E2, al
		mov	byte_266E3, 3Ch	; '<'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 8
		mov	al, [bp+var_1]
		add	al, 20h	; ' '
		mov	byte_266EE, al
		call	word_2D004
		mov	al, 82h	; '‚'
		sub	al, byte_266ED
		mov	byte_266ED, al
		call	sub_1CFA2
		mov	al, 80h	; '€'
		sub	al, byte_266ED
		mov	byte_266ED, al
		call	sub_1CFA2

loc_1B2ED:				; CODE XREF: sub_1B282+21j
		cmp	[bp+var_1], 0
		jnz	short locret_1B311
		mov	al, byte_266ED
		add	al, 8
		mov	byte_266ED, al
		mov	word_2A8D0, 8
		mov	byte_2A8D2, 9
		mov	al, byte_2A8D3
		neg	al
		mov	byte_2A8D3, al
		call	sub_13B21

locret_1B311:				; CODE XREF: sub_1B282+6Fj
		leave
		retn
sub_1B282	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B313	proc near		; CODE XREF: seg003:loc_1B6F7p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 40h	; '@'
		jge	short loc_1B339
		cmp	byte_25A06, 1
		jnz	short loc_1B32A
		call	sub_1A53D
		jmp	loc_1B3DD
; ---------------------------------------------------------------------------

loc_1B32A:				; CODE XREF: sub_1B313+Fj
		cmp	byte_25A06, 2
		jnz	loc_1B3DD
		call	sub_1A61C
		jmp	loc_1B3DD
; ---------------------------------------------------------------------------

loc_1B339:				; CODE XREF: sub_1B313+8j
		cmp	word_2671A, 40h	; '@'
		jl	short loc_1B3B7
		cmp	word_2671A, 0C0h ; 'À'
		jg	short loc_1B3B7
		mov	byte_26718, 8Ch	; 'Œ'
		cmp	byte_266CF, 0
		jnz	loc_1B3DD
		mov	byte_266E2, 2
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EE, 28h	; '('
		mov	byte_266F0, 0Eh
		test	byte ptr word_266CA, 1Fh
		jnz	short loc_1B382
		mov	byte_266EF, 0Ah
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266ED, 40h	; '@'
		jmp	short loc_1B391
; ---------------------------------------------------------------------------

loc_1B382:				; CODE XREF: sub_1B313+5Cj
		mov	byte_266EF, 7
		mov	byte_266EC, 2Eh	; '.'
		mov	byte_266ED, 0

loc_1B391:				; CODE XREF: sub_1B313+6Dj
		mov	ax, word ptr dword_2670A+2
		add	ax, 200h
		mov	word ptr dword_266E4+2,	ax
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		call	word_2D000
		mov	ax, word_25A0C
		mov	word ptr dword_266E4, ax
		call	word_2D000
		push	3
		call	sub_138B2
		jmp	short loc_1B3DD
; ---------------------------------------------------------------------------

loc_1B3B7:				; CODE XREF: sub_1B313+2Bj
					; sub_1B313+33j
		cmp	word_2671A, 0C0h ; 'À'
		jl	short loc_1B3DD
		cmp	byte_25A06, 2
		jz	short loc_1B3CB
		call	sub_1A6E5
		jmp	short loc_1B3DD
; ---------------------------------------------------------------------------

loc_1B3CB:				; CODE XREF: sub_1B313+B1j
		call	sub_1A5AC
		or	al, al
		jz	short loc_1B3DD
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1B3DD:				; CODE XREF: sub_1B313+14j
					; sub_1B313+1Cj ...
		call	sub_1AA45
		pop	bp
		retn
sub_1B313	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B3E2	proc near		; CODE XREF: seg003:7CAFp
		push	bp
		mov	bp, sp
		cmp	byte_25A1B, 2
		jnz	short loc_1B42B
		mov	word_257E2, 180h
		mov	word_257E4, 300h
		mov	ax, word_25A0C
		mov	word ptr dword_257DE, ax
		mov	ax, word_25A0E
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		mov	byte_25A1E, al
		or	al, al
		jz	short loc_1B417
		push	4
		call	sub_138B2

loc_1B417:				; CODE XREF: sub_1B3E2+2Cj
		mov	al, byte_25A1E
		mov	ah, 0
		sub	word_26716, ax
		cmp	word_26716, 0
		jge	short loc_1B42B
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1B42B:				; CODE XREF: sub_1B3E2+8j
					; sub_1B3E2+43j
		mov	al, 0
		pop	bp
		retn
sub_1B3E2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B42F	proc near		; CODE XREF: seg003:7B10p seg003:7B99p ...

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		cmp	byte_2CFFA, 14h
		jnb	short loc_1B43E
		mov	byte_2CFFA, 14h

loc_1B43E:				; CODE XREF: sub_1B42F+8j
		push	[bp+arg_2]
		call	sub_15C7C
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		mov	ax, word_26720
		mov	word_26716, ax
		mov	ax, [bp+arg_0]
		mov	word_26720, ax
		mov	word_25A0A, 0
		mov	byte_26718, 80h	; '€'
		mov	word_25A0A, 0
		mov	byte_25A06, 1
		pop	bp
		retn	4
sub_1B42F	endp

; ---------------------------------------------------------------------------
		db 0C8h, 6, 2 dup(0), 0A0h, 0D9h, 53h, 0B4h, 0,	8Bh, 0D8h
		db 83h,	0FBh, 11h, 0Fh,	87h, 55h, 4, 3,	0DBh, 2Eh, 0FFh
		db 0A7h, 0A8h, 7Eh, 83h, 3Eh, 0DAh, 53h, 0, 75h, 1Ch, 0C7h
		db 6, 48h, 46h
		dw seg seg001
; ---------------------------------------------------------------------------
		mov	word ptr dword_25986, 11C0h
		mov	word_26700, 0
		mov	byte_25A08, 0
		mov	byte_25A1B, 0
		call	sub_1E67C
		cmp	word_2671A, 80h	; '€'
		jle	loc_1B8EA
		inc	byte_26719
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	byte_25A02, 0
		mov	word_255AC, 7DC9h
		mov	byte_2CDCA, 0Fh
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		call	sub_1E67C
		cmp	word_2671A, 40h	; '@'
		jl	loc_1B8EA
		inc	byte_26719
		mov	word_26712, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		mov	word_26716, 33F4h
		mov	word_26720, 2968h
		mov	word_2671A, 0
		mov	word_25A0A, 0
		mov	byte_25A06, 1
		push	1
		call	sub_13D60
		mov	byte_25A07, al
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp-2],	ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1B928

loc_1B541:				; CODE XREF: seg003:7ABCj
		mov	ax, cs:[bx]
		cmp	ax, [bp-2]
		jz	short loc_1B550
		add	bx, 2
		loop	loc_1B541
		jmp	short loc_1B580	; default
; ---------------------------------------------------------------------------

loc_1B550:				; CODE XREF: seg003:7AB7j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1B554:				; DATA XREF: seg003:7EA0o
		call	sub_1AB5D	; jumptable 0001B550 case 0
		jmp	short loc_1B580	; default
; ---------------------------------------------------------------------------

loc_1B559:				; CODE XREF: seg003:loc_1B550j
					; DATA XREF: seg003:7EA0o
		call	sub_1ABE5	; jumptable 0001B550 case 1
		jmp	short loc_1B580	; default
; ---------------------------------------------------------------------------

loc_1B55E:				; CODE XREF: seg003:loc_1B550j
					; DATA XREF: seg003:7EA0o
		call	sub_1ACCC	; jumptable 0001B550 case 2
		jmp	short loc_1B580	; default
; ---------------------------------------------------------------------------

loc_1B563:				; CODE XREF: seg003:loc_1B550j
					; DATA XREF: seg003:7EA0o
		call	sub_1A3C3	; jumptable 0001B550 case 255
		or	al, al
		jz	short loc_1B580	; default
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		mov	byte_2671D, dl
		cmp	byte_2671F, 0Ah
		jnb	short loc_1B59A

loc_1B580:				; CODE XREF: seg003:7ABEj seg003:7AC7j ...
		cmp	byte_26718, 0	; default
		jz	loc_1B787
		call	sub_1E64E
		or	al, al
		jz	loc_1B8EA
		push	14h
		call	sub_19FD8
		call	sub_1E692

loc_1B59A:				; CODE XREF: seg003:7AEEj
		push	large 1DB0h
		call	sub_1B42F
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		inc	word_2671A
		push	large 0C000500h
		call	sub_1A439
		or	al, al
		jz	loc_1B8EA
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671F, 0
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_1B5DB
		cmp	ax, 0FFh
		jz	short loc_1B5E0
		jmp	short loc_1B600
; ---------------------------------------------------------------------------

loc_1B5DB:				; CODE XREF: seg003:7B42j
		call	sub_1AD6F
		jmp	short loc_1B600
; ---------------------------------------------------------------------------

loc_1B5E0:				; CODE XREF: seg003:7B47j
		push	1200h
		call	sub_13D76
		add	ax, 300h
		push	ax
		push	500h
		call	sub_1A439
		or	al, al
		jz	short loc_1B600
		mov	byte_2671D, 0
		cmp	byte_2671F, 0Ah
		jnb	short loc_1B623

loc_1B600:				; CODE XREF: seg003:7B49j seg003:7B4Ej ...
		cmp	byte_26718, 0
		jz	loc_1B787
		cmp	byte_2671D, 0FFh
		jz	loc_1B787
		call	sub_1E64E
		or	al, al
		jz	loc_1B8EA
		push	14h
		call	sub_19FD8
		call	sub_1E692

loc_1B623:				; CODE XREF: seg003:7B6Ej
		push	large 1518h
		call	sub_1B42F
		mov	byte_25A08, 1
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		inc	word_2671A
		cmp	byte_25A06, 0
		jz	short loc_1B645
		call	sub_1A7BC
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------

loc_1B645:				; CODE XREF: seg003:7BADj
		inc	byte_26719
		mov	word_2671A, 0
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		call	sub_1ADDB
		inc	word_2671A
		call	sub_1A4A8
		cmp	word_2671A, 140h
		jl	loc_1B8EA
		cmp	word ptr dword_2670A+2,	500h
		jnz	loc_1B8EA
		push	2
		call	sub_15C7C
		cmp	byte_2CFFA, 14h
		jnb	short loc_1B681
		mov	byte_2CFFA, 14h

loc_1B681:				; CODE XREF: seg003:7BEAj
		inc	byte_26719
		mov	word_2671A, 0
		mov	word_25A0A, 0
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		call	sub_1E64E
		call	sub_1A503
		or	al, al
		jz	loc_1B8EA
		inc	byte_26719
		mov	byte_2671F, 0
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0
		mov	word_25A0A, 0
		mov	byte_25A06, 2
		mov	byte_25A1B, 1
		mov	byte_25A02, 0FFh
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp-4],	ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1B918

loc_1B6DA:				; CODE XREF: seg003:7C55j
		mov	ax, cs:[bx]
		cmp	ax, [bp-4]
		jz	short loc_1B6E9
		add	bx, 2
		loop	loc_1B6DA
		jmp	short loc_1B72E	; default
; ---------------------------------------------------------------------------

loc_1B6E9:				; CODE XREF: seg003:7C50j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1B6ED:				; DATA XREF: seg003:7E90o
		call	sub_1AE8F	; jumptable 0001B6E9 case 0
		jmp	short loc_1B72E	; default
; ---------------------------------------------------------------------------

loc_1B6F2:				; CODE XREF: seg003:loc_1B6E9j
					; DATA XREF: seg003:7E90o
		call	sub_1AFA8	; jumptable 0001B6E9 case 1
		jmp	short loc_1B72E	; default
; ---------------------------------------------------------------------------

loc_1B6F7:				; CODE XREF: seg003:loc_1B6E9j
					; DATA XREF: seg003:7E90o
		call	sub_1B313	; jumptable 0001B6E9 case 2
		jmp	short loc_1B72E	; default
; ---------------------------------------------------------------------------

loc_1B6FC:				; CODE XREF: seg003:loc_1B6E9j
					; DATA XREF: seg003:7E90o
		push	900h		; jumptable 0001B6E9 case 255
		call	sub_13D76
		add	ax, 300h
		push	ax
		push	500h
		call	sub_1A439
		or	al, al
		jz	short loc_1B72E	; default

loc_1B710:				; CODE XREF: seg003:7C8Fj
		push	3
		call	sub_13D76
		mov	byte_2671D, al
		mov	al, byte_25A02
		cmp	al, byte_2671D
		jz	short loc_1B710
		mov	al, byte_2671D
		mov	byte_25A02, al
		cmp	byte_2671F, 0Ah
		jnb	short loc_1B75B

loc_1B72E:				; CODE XREF: seg003:7C57j seg003:7C60j ...
		cmp	byte_26718, 0	; default
		jz	short loc_1B787
		cmp	byte_2671D, 2
		ja	short loc_1B744
		call	sub_1E64E
		call	sub_1B3E2
		jmp	short loc_1B748
; ---------------------------------------------------------------------------

loc_1B744:				; CODE XREF: seg003:7CAAj
		inc	word_2671A

loc_1B748:				; CODE XREF: seg003:7CB2j
		mov	ax, word_26716
		cmp	ax, word_26720
		jg	loc_1B8EA
		push	14h
		call	sub_19FD8
		call	sub_1E692

loc_1B75B:				; CODE XREF: seg003:7C9Cj
		cmp	byte_26719, 8
		jnz	short loc_1B76A
		push	large 0D48h
		jmp	short loc_1B770
; ---------------------------------------------------------------------------

loc_1B76A:				; CODE XREF: seg003:7CD0j
		push	large 4B0h

loc_1B770:				; CODE XREF: seg003:7CD8j
		call	sub_1B42F
		cmp	byte_26719, 9
		jnz	short loc_1B77F
		mov	byte_25A08, 1

loc_1B77F:				; CODE XREF: seg003:7CE8j
		mov	byte_25A1B, 0
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------

loc_1B787:				; CODE XREF: seg003:7AF5j seg003:7B75j ...
		inc	word_2671A
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		db 0E8h, 0EBh
; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_1B790:				; CODE XREF: sub_1CCB8:loc_1CCD9j
		db	2Eh		; jumptable 0001CCD9 case 47109
		call	sub_1A503
		or	al, al
		jz	loc_1B8EA
		inc	byte_26719
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		mov	word_2671A, 0
		mov	word_25A0A, 0
		mov	byte_25A06, 2
		mov	byte_25A1B, 1
		jmp	loc_1B8EA
; END OF FUNCTION CHUNK	FOR sub_1CCB8
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp-6],	ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset word_1B908

loc_1B7CF:				; CODE XREF: seg003:7D4Aj
		mov	ax, cs:[bx]
		cmp	ax, [bp-6]
		jz	short loc_1B7DE
		add	bx, 2
		loop	loc_1B7CF
		jmp	short loc_1B80B	; default
; ---------------------------------------------------------------------------

loc_1B7DE:				; CODE XREF: seg003:7D45j
		jmp	word ptr cs:[bx+8] ; switch jump

loc_1B7E2:				; DATA XREF: seg003:7E80o
		call	sub_1B099	; jumptable 0001B7DE case 0
		jmp	short loc_1B80B	; default
; ---------------------------------------------------------------------------

loc_1B7E7:				; CODE XREF: seg003:loc_1B7DEj
					; DATA XREF: seg003:7E80o
		call	sub_1B1B1	; jumptable 0001B7DE case 1
		jmp	short loc_1B80B	; default
; ---------------------------------------------------------------------------

loc_1B7EC:				; CODE XREF: seg003:loc_1B7DEj
					; DATA XREF: seg003:7E80o
		call	sub_1B22B	; jumptable 0001B7DE case 2
		jmp	short loc_1B80B	; default
; ---------------------------------------------------------------------------

loc_1B7F1:				; CODE XREF: seg003:loc_1B7DEj
					; DATA XREF: seg003:7E80o
		inc	byte_2671F	; jumptable 0001B7DE case 255
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		mov	byte_2671D, dl
		cmp	byte_2671F, 12h
		jnb	short loc_1B81C

loc_1B80B:				; CODE XREF: seg003:7D4Cj seg003:7D55j ...
		call	sub_1E64E	; default
		or	al, al
		jz	loc_1B8EA
		push	14h
		call	sub_19FD8
		call	sub_1E692

loc_1B81C:				; CODE XREF: seg003:7D79j
		push	large 30000h
		call	sub_1B42F
		mov	byte_26718, 92h	; '’'
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		call	sub_1E64E
		cmp	word_2671A, 80h	; '€'
		jl	loc_1B8EA
		inc	byte_26719
		mov	byte_266E2, 1
		mov	byte_266ED, 0
		jmp	loc_1B8EA
; ---------------------------------------------------------------------------
		call	sub_1B282
		call	sub_1E64E
		or	al, al
		jnz	short loc_1B85F
		cmp	word_2671A, 9C4h
		jl	loc_1B8EA

loc_1B85F:
		push	1
		call	sub_15C7C
		inc	byte_26719
		cmp	word_2671A, 9C4h
		jge	short loc_1B877
		mov	byte_2671F, 1
		jmp	short loc_1B87C
; ---------------------------------------------------------------------------

loc_1B877:
		mov	byte_2671F, 0

loc_1B87C:
		mov	word_2671A, 0
		mov	byte_2671D, 0
		mov	word_216E4, 64h
		mov	byte_266D3, 1
		jmp	short loc_1B8EA
; ---------------------------------------------------------------------------
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_1B8A4
		push	4
		call	sub_15C7C

loc_1B8A4:				; CODE XREF: sub_1CD6E-14D1j
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_1B8EA
		push	2
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_1B8C7
		push	46h ; 'F'
		call	sub_19FD8

loc_1B8C7:				; CODE XREF: sub_1CD6E-14AEj
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_266D3, 1
		mov	byte_259A2, 0FFh
		jmp	short loc_1B8EA
; END OF FUNCTION CHUNK	FOR sub_1CD6E
; ---------------------------------------------------------------------------
		call	sub_1E743
		leave
		retf
; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_1CCB8

loc_1B8EA:				; CODE XREF: seg003:7A33j seg003:7A58j ...
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax
		call	sub_15DE8
		call	sub_1A110
		push	word_26716
		push	33F4h
		call	sub_19F16
		leave
		retf
; END OF FUNCTION CHUNK	FOR sub_1CCB8
; ---------------------------------------------------------------------------
word_1B908	dw	0,     1,     2,  0FFh ; DATA XREF: seg003:7D3Co
					; value	table for switch statement
		dw offset loc_1B7E2	; jump table for switch	statement
		dw offset loc_1B7E7
		dw offset loc_1B7EC
		dw offset loc_1B7F1
word_1B918	dw	0,     1,     2,  0FFh ; DATA XREF: seg003:7C47o
					; value	table for switch statement
		dw offset loc_1B6ED	; jump table for switch	statement
		dw offset loc_1B6F2
		dw offset loc_1B6F7
		dw offset loc_1B6FC
word_1B928	dw	0,     1,     2,  0FFh ; DATA XREF: seg003:7AAEo
					; value	table for switch statement
		dw offset loc_1B554	; jump table for switch	statement
		dw offset loc_1B559
		dw offset loc_1B55E
		dw offset loc_1B563
		db 7, 7Ah, 5Bh,	7Ah, 0A3h, 7Ah,	16h, 7Bh, 3Bh, 7Bh, 0A4h
		db 7Bh,	0C2h, 7Bh, 4, 7Ch, 3Ch,	7Ch, 0A4h, 7Bh,	0C2h, 7Bh
		db 4, 7Ch, 3Ch,	7Ch, 0FEh, 7Ch,	31h, 7Dh, 9Dh, 7Dh, 0BBh
		db 7Dh,	4, 7Eh

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B95C	proc near		; CODE XREF: sub_1C2E5+4p

var_1		= byte ptr -1

		enter	2, 0
		cmp	byte_25A27, 2
		jnz	short loc_1B96C
		mov	byte_25A27, 0

loc_1B96C:				; CODE XREF: sub_1B95C+9j
		mov	al, byte_25A26
		mov	ah, 0
		dec	ax
		mov	bx, ax
		cmp	bx, 7
		ja	loc_1BBA8
		add	bx, bx
		jmp	word ptr cs:[bx-7E64h]
; ---------------------------------------------------------------------------
		cmp	word_25A34, 40h	; '@'
		jnb	short loc_1B99B
		test	byte ptr word_25A34, 7
		jnz	short loc_1B99B
		mov	ax, word_25A34
		shr	ax, 3
		add	al, 86h	; '†'
		mov	byte_26718, al

loc_1B99B:				; CODE XREF: sub_1B95C+2Bj
					; sub_1B95C+32j
		cmp	word_25A34, 0
		jnz	short loc_1B9AC
		push	8
		call	sub_138B2
		jmp	loc_1BBA4
; ---------------------------------------------------------------------------

loc_1B9AC:				; CODE XREF: sub_1B95C+44j
		cmp	word_25A34, 38h	; '8'
		jnz	short loc_1B9CE
		push	9
		call	sub_138B2
		mov	byte_25A27, 1
		mov	ax, word ptr dword_2670A
		mov	word_25A28, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25A2A, ax
		jmp	loc_1BBA4
; ---------------------------------------------------------------------------

loc_1B9CE:				; CODE XREF: sub_1B95C+55j
		cmp	word_25A34, 40h	; '@'
		jb	loc_1BBA4
		mov	byte_26718, 8Dh	; ''
		mov	byte_25A26, 2
		cmp	word_25A34, 50h	; 'P'
		jnb	short loc_1BA49
		mov	ax, word ptr dword_2598E+2
		sub	ax, word_25A2A
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word_25A28
		push	ax
		call	sub_1DA8
		mov	[bp+var_1], al
		mov	al, byte ptr word_25A36
		sub	[bp+var_1], al
		cmp	[bp+var_1], 80h	; '€'
		jnb	short loc_1BA19
		cmp	[bp+var_1], 10h
		jb	short loc_1BA19
		mov	byte_25A38, 1
		jmp	short loc_1BA2A
; ---------------------------------------------------------------------------

loc_1BA19:				; CODE XREF: sub_1B95C+AEj
					; sub_1B95C+B4j
		cmp	[bp+var_1], 80h	; '€'
		jb	short loc_1BA33
		cmp	[bp+var_1], 0F0h ; 'ð'
		ja	short loc_1BA33
		mov	byte_25A38, 0FFh

loc_1BA2A:				; CODE XREF: sub_1B95C+BBj
		mov	al, byte_266CC
		add	byte ptr word_25A36+1, al
		jmp	short loc_1BA40
; ---------------------------------------------------------------------------

loc_1BA33:				; CODE XREF: sub_1B95C+C1j
					; sub_1B95C+C7j
		mov	al, byte ptr word_25A36+1
		inc	al
		mov	byte ptr word_25A36+1, al
		mov	byte_25A38, 0

loc_1BA40:				; CODE XREF: sub_1B95C+D5j
		mov	al, byte_25A38
		add	byte ptr word_25A36, al
		jmp	short loc_1BA50
; ---------------------------------------------------------------------------

loc_1BA49:				; CODE XREF: sub_1B95C+8Aj
		mov	al, byte_266CC
		add	byte ptr word_25A36+1, al

loc_1BA50:				; CODE XREF: sub_1B95C+EBj
		cmp	word_25A28, 400h
		jg	short loc_1BA60
		mov	byte_25A26, 3
		jmp	loc_1BBA4
; ---------------------------------------------------------------------------

loc_1BA60:				; CODE XREF: sub_1B95C+FAj
		cmp	word_25A28, 1400h
		jl	short loc_1BA70
		mov	byte_25A26, 4
		jmp	loc_1BBA4
; ---------------------------------------------------------------------------

loc_1BA70:				; CODE XREF: sub_1B95C+10Aj
		cmp	word_25A2A, 1300h
		jl	short loc_1BA80
		mov	byte_25A26, 5
		jmp	loc_1BBA4
; ---------------------------------------------------------------------------

loc_1BA80:				; CODE XREF: sub_1B95C+11Aj
		cmp	word_25A2A, 200h
		jg	loc_1BBA4
		mov	byte_25A26, 6
		jmp	loc_1BBA4
; ---------------------------------------------------------------------------
		mov	al, byte ptr word_25A36+1
		add	al, 0FCh ; 'ü'
		mov	byte ptr word_25A36+1, al
		mov	al, byte_25A38
		add	byte ptr word_25A36, al
		cmp	byte ptr word_25A36+1, 4
		ja	loc_1BBA8
		jmp	short loc_1BB0C
; ---------------------------------------------------------------------------
		mov	al, byte ptr word_25A36+1
		add	al, 0FCh ; 'ü'
		mov	byte ptr word_25A36+1, al
		mov	al, byte_25A38
		add	byte ptr word_25A36, al
		cmp	byte_25A38, 0
		jz	short loc_1BACB
		mov	al, byte_25A38
		add	byte ptr word_25A36, al
		jmp	short loc_1BACF
; ---------------------------------------------------------------------------

loc_1BACB:				; CODE XREF: sub_1B95C+164j
		inc	byte ptr word_25A36

loc_1BACF:				; CODE XREF: sub_1B95C+16Dj
		cmp	byte ptr word_25A36+1, 4
		ja	loc_1BBA8
		jmp	short loc_1BB0C
; ---------------------------------------------------------------------------
		mov	al, byte ptr word_25A36+1
		add	al, 0FCh ; 'ü'
		mov	byte ptr word_25A36+1, al
		mov	al, byte_25A38
		add	byte ptr word_25A36, al
		cmp	byte ptr word_25A36+1, 4
		ja	loc_1BBA8
		jmp	short loc_1BB0C
; ---------------------------------------------------------------------------
		mov	al, byte ptr word_25A36+1
		add	al, 0FCh ; 'ü'
		mov	byte ptr word_25A36+1, al
		mov	al, byte_25A38
		add	byte ptr word_25A36, al
		cmp	byte ptr word_25A36+1, 4
		ja	loc_1BBA8

loc_1BB0C:				; CODE XREF: sub_1B95C+14Ej
					; sub_1B95C+17Cj ...
		mov	byte_25A26, 7
		jmp	loc_1BBA8
; ---------------------------------------------------------------------------
		mov	ax, word ptr dword_2670A+2
		sub	ax, word_25A2A
		push	ax
		mov	ax, word ptr dword_2670A
		sub	ax, word_25A28
		push	ax
		call	sub_1DA8
		mov	byte ptr word_25A36, al
		mov	al, byte ptr word_25A36+1
		add	al, 8
		mov	byte ptr word_25A36+1, al
		mov	ax, word ptr dword_2670A
		add	ax, 0FF00h
		cmp	ax, word_25A28
		jge	short loc_1BBA8
		mov	ax, word ptr dword_2670A
		add	ax, 100h
		cmp	ax, word_25A28
		jle	short loc_1BBA8
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FF00h
		cmp	ax, word_25A2A
		jge	short loc_1BBA8
		mov	ax, word ptr dword_2670A+2
		add	ax, 100h
		cmp	ax, word_25A2A
		jle	short loc_1BBA8
		mov	byte_25A26, 8
		mov	byte_25A27, 2
		mov	word_25A34, 0
		jmp	short loc_1BBA8
; ---------------------------------------------------------------------------
		cmp	word_25A34, 20h	; ' '
		jnb	short loc_1BB93
		test	byte ptr word_25A34, 7
		jnz	short loc_1BB93
		mov	ax, 1Fh
		sub	ax, word_25A34
		shr	ax, 2
		add	al, 86h	; '†'
		mov	byte_26718, al

loc_1BB93:				; CODE XREF: sub_1B95C+21Fj
					; sub_1B95C+226j
		cmp	word_25A34, 20h	; ' '
		jb	short loc_1BBA4
		mov	byte_26718, 86h	; '†'
		mov	byte_25A26, 0

loc_1BBA4:				; CODE XREF: sub_1B95C+4Dj
					; sub_1B95C+6Fj ...
		inc	word_25A34

loc_1BBA8:				; CODE XREF: sub_1B95C+1Bj
					; sub_1B95C+14Aj ...
		cmp	byte_25A27, 1
		jnz	short locret_1BC2A
		push	ds
		push	offset unk_25A30
		push	ds
		push	offset word_25A32
		push	word_25A36
		mov	al, byte ptr word_25A36+1
		mov	ah, 0
		push	ax
		call	sub_13117
		mov	word_257E2, 200h
		mov	word_257E4, 200h
		mov	ax, word_25A28
		mov	word ptr dword_257DE, ax
		mov	ax, word_25A2A
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		shr	ax, 1
		mov	dx, word_25A32
		sub	dx, ax
		mov	word_25A32, dx
		push	46E8h
		call	sub_13D32
		mov	ax, word_25A28
		add	ax, 0FE80h
		cmp	ax, word ptr dword_2598E
		jge	short locret_1BC2A
		mov	ax, word_25A28
		add	ax, 180h
		cmp	ax, word ptr dword_2598E
		jle	short locret_1BC2A
		mov	ax, word_25A2A
		add	ax, 0FE80h
		cmp	ax, word ptr dword_2598E+2
		jge	short locret_1BC2A
		mov	ax, word_25A2A
		add	ax, 180h
		cmp	ax, word ptr dword_2598E+2
		jle	short locret_1BC2A
		mov	byte_259A9, 1

locret_1BC2A:				; CODE XREF: sub_1B95C+251j
					; sub_1B95C+2A3j ...
		leave
		retn
sub_1B95C	endp

; ---------------------------------------------------------------------------
		db 0F2h, 7Eh, 51h, 7Fh,	2, 80h,	1Ch, 80h, 4Ah, 80h, 64h
		db 80h,	84h, 80h, 0E6h,	80h

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BC3C	proc near		; CODE XREF: sub_1BD23+Ap
					; sub_1BD4B+11p ...
		push	bp
		mov	bp, sp
		mov	byte ptr word_25A36+1, 8
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8
		mov	byte ptr word_25A36, al
		mov	byte_25A26, 1
		mov	word_25A34, 0
		mov	byte_25A27, 0
		mov	byte_25A38, 0
		pop	bp
		retn
sub_1BC3C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BC73	proc near		; CODE XREF: sub_1BD4B+3p sub_1BF52+3p ...
		push	bp
		mov	bp, sp
		cmp	word_25A3A, 80h	; '€'
		jge	short loc_1BC8A
		add	word ptr dword_2670E, 8
		mov	byte_2671E, 60h	; '`'
		jmp	short loc_1BCE9
; ---------------------------------------------------------------------------

loc_1BC8A:				; CODE XREF: sub_1BC73+9j
		cmp	word_25A3A, 100h
		jge	short loc_1BC98
		dec	byte_2671E
		jmp	short loc_1BCE9
; ---------------------------------------------------------------------------

loc_1BC98:				; CODE XREF: sub_1BC73+1Dj
		cmp	word_25A3A, 180h
		jl	short loc_1BCCA
		cmp	word_25A3A, 200h
		jge	short loc_1BCB4
		add	word ptr dword_2670E, 8
		mov	byte_2671E, 20h	; ' '
		jmp	short loc_1BCE9
; ---------------------------------------------------------------------------

loc_1BCB4:				; CODE XREF: sub_1BC73+33j
		cmp	word_25A3A, 280h
		jge	short loc_1BCC2
		inc	byte_2671E
		jmp	short loc_1BCE9
; ---------------------------------------------------------------------------

loc_1BCC2:				; CODE XREF: sub_1BC73+47j
		cmp	word_25A3A, 300h
		jge	short loc_1BCD1

loc_1BCCA:				; CODE XREF: sub_1BC73+2Bj
		sub	word ptr dword_2670E, 8
		jmp	short loc_1BCE9
; ---------------------------------------------------------------------------

loc_1BCD1:				; CODE XREF: sub_1BC73+55j
		cmp	word_25A3A, 300h
		jl	short loc_1BCE9
		add	word ptr dword_2670E, 8
		mov	byte_2671E, 60h	; '`'
		mov	word_25A3A, 0

loc_1BCE9:				; CODE XREF: sub_1BC73+15j
					; sub_1BC73+23j ...
		push	0C00h
		push	word ptr dword_2670E
		mov	al, byte_2671E
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+566h]
		call	sub_13320
		mov	word ptr dword_2670A, ax
		push	600h
		push	word ptr dword_2670E
		mov	al, byte_2671E
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4E6h]
		call	sub_13320
		mov	word ptr dword_2670A+2,	ax
		pop	bp
		retn
sub_1BC73	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BD23	proc near		; CODE XREF: sub_1C2E5:loc_1C343p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_1BD30
		call	sub_1BC3C

loc_1BD30:				; CODE XREF: sub_1BD23+8j
		cmp	word_2671A, 20h	; ' '
		jle	short loc_1BD49
		cmp	byte_25A26, 0
		jnz	short loc_1BD49
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_1BD49:				; CODE XREF: sub_1BD23+12j
					; sub_1BD23+19j
		pop	bp
		retn
sub_1BD23	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BD4B	proc near		; CODE XREF: sub_1C2E5+18Ep
		push	bp
		mov	bp, sp
		call	sub_1BC73
		inc	word_25A3A
		cmp	word_2671A, 10h
		jnz	short loc_1BD64
		call	sub_1BC3C
		mov	byte_266ED, 0C0h ; 'À'

loc_1BD64:				; CODE XREF: sub_1BD4B+Fj
		cmp	word_2671A, 10h
		jle	short loc_1BDB2
		cmp	byte_266CF, 0
		jnz	short loc_1BDA0
		mov	byte_266E2, 2
		mov	byte_266E3, 5Ch	; '\'
		mov	byte_266EE, 30h	; '0'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 5
		mov	byte_266F0, 10h
		call	word_2D004
		call	word_2D000
		mov	al, byte_266ED
		add	al, 0F0h ; 'ð'
		mov	byte_266ED, al

loc_1BDA0:				; CODE XREF: sub_1BD4B+25j
		cmp	byte_25A26, 0
		jnz	short loc_1BDB2
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_1BDB2:				; CODE XREF: sub_1BD4B+1Ej
					; sub_1BD4B+5Aj
		pop	bp
		retn
sub_1BD4B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BDB4	proc near		; CODE XREF: sub_1BE78+3p sub_1BFAB+3p ...

var_2		= word ptr -2

		enter	2, 0
		cmp	word_2671A, 20h	; ' '
		jle	short loc_1BDC3
		mov	al, 0
		leave
		retn
; ---------------------------------------------------------------------------

loc_1BDC3:				; CODE XREF: sub_1BDB4+9j
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset byte_1BE33

loc_1BDCF:				; CODE XREF: sub_1BDB4+26j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1BDDE
		add	bx, 2
		loop	loc_1BDCF
		jmp	short loc_1BE2E	; default
; ---------------------------------------------------------------------------

loc_1BDDE:				; CODE XREF: sub_1BDB4+21j
		jmp	word ptr cs:[bx+8] ; switch jump
; ---------------------------------------------------------------------------
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_2A8C6+2,	ax
		mov	word_2A8D0, 8
		mov	word_2A8CE, 0C00h
		mov	byte_2A8D2, 0Fh

loc_1BDFF:				; CODE XREF: sub_1BDB4+74j
		mov	byte_2A8D3, 0FEh ; 'þ'
		call	sub_13B21
		mov	byte_2A8D3, 2
		call	sub_13B21
		jmp	short loc_1BE2E	; default
; ---------------------------------------------------------------------------
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		call	sub_C696
		mov	byte_25592, 0Fh
		mov	byte_2A8D2, 7
		jmp	short loc_1BDFF
; ---------------------------------------------------------------------------
		mov	al, 2
		leave
		retn
; ---------------------------------------------------------------------------

loc_1BE2E:				; CODE XREF: sub_1BDB4+28j
					; sub_1BDB4+5Bj
		mov	al, 1		; default
		leave
		retn
sub_1BDB4	endp

; ---------------------------------------------------------------------------
		db 0
byte_1BE33	db 1, 0, 8, 0, 10h, 0, 20h, 0, 52h, 83h, 93h, 83h, 81h
					; DATA XREF: sub_1BDB4+18o
		db 83h,	9Ah, 83h

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BE43	proc near		; CODE XREF: sub_1BE78+D5p
					; sub_1BFAB+94p ...
		push	bp
		mov	bp, sp
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0
		mov	byte_266ED, 0
		mov	byte_266E2, 5
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 30h	; '0'
		call	word_2D004
		call	sub_1CFA2
		pop	bp
		retn
sub_1BE43	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BE78	proc near		; CODE XREF: sub_1C2E5+194p
		push	bp
		mov	bp, sp
		call	sub_1BDB4
		mov	ah, 0
		or	ax, ax
		jz	short loc_1BEA5
		cmp	ax, 2
		jnz	loc_1BF50
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8
		add	al, 0C0h ; 'À'
		jmp	loc_1BF40
; ---------------------------------------------------------------------------

loc_1BEA5:				; CODE XREF: sub_1BE78+Aj
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BEB9
		push	9
		call	sub_138B2

loc_1BEB9:				; CODE XREF: sub_1BE78+38j
		cmp	word_2671A, 48h	; 'H'
		jge	short loc_1BEF7
		mov	ax, word_2671A
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1BF50
		mov	byte_266E2, 1
		mov	byte_266EE, 40h	; '@'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 2
		mov	byte_266F0, 0Ch
		call	word_2D004
		call	word_2D000
		mov	al, byte_266ED
		add	al, 4
		jmp	short loc_1BF40
; ---------------------------------------------------------------------------

loc_1BEF7:				; CODE XREF: sub_1BE78+46j
		cmp	word_2671A, 48h	; 'H'
		jnz	short loc_1BF05
		mov	al, byte_266ED
		add	al, 40h	; '@'
		jmp	short loc_1BF40
; ---------------------------------------------------------------------------

loc_1BF05:				; CODE XREF: sub_1BE78+84j
		cmp	word_2671A, 90h	; ''
		jge	short loc_1BF45
		mov	ax, word_2671A
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BF50
		mov	byte_266E2, 1
		mov	byte_266EE, 40h	; '@'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 2
		mov	byte_266F0, 0Ch
		call	word_2D004
		call	word_2D000
		mov	al, byte_266ED
		add	al, 0FEh ; 'þ'

loc_1BF40:				; CODE XREF: sub_1BE78+2Aj
					; sub_1BE78+7Dj ...
		mov	byte_266ED, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1BF45:				; CODE XREF: sub_1BE78+93j
		cmp	word_2671A, 90h	; ''
		jl	short loc_1BF50
		call	sub_1BE43

loc_1BF50:				; CODE XREF: sub_1BE78+Fj
					; sub_1BE78+53j ...
		pop	bp
		retn
sub_1BE78	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BF52	proc near		; CODE XREF: sub_1C2E5+19Ap
		push	bp
		mov	bp, sp
		call	sub_1BC73
		inc	word_25A3A
		cmp	word_2671A, 10h
		jnz	short loc_1BF66
		call	sub_1BC3C

loc_1BF66:				; CODE XREF: sub_1BF52+Fj
		cmp	word_2671A, 10h
		jle	short loc_1BFA9
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BF97
		mov	byte_266ED, 0
		mov	byte_266E2, 1
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 8
		call	word_2D000

loc_1BF97:				; CODE XREF: sub_1BF52+26j
		cmp	byte_25A26, 0
		jnz	short loc_1BFA9
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_1BFA9:				; CODE XREF: sub_1BF52+19j
					; sub_1BF52+4Aj
		pop	bp
		retn
sub_1BF52	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BFAB	proc near		; CODE XREF: sub_1C2E5+1A0p
		push	bp
		mov	bp, sp
		call	sub_1BDB4
		mov	ah, 0
		or	ax, ax
		jz	short loc_1BFD7
		cmp	ax, 2
		jnz	loc_1C042
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8
		add	al, 0C0h ; 'À'
		jmp	short loc_1C033
; ---------------------------------------------------------------------------

loc_1BFD7:				; CODE XREF: sub_1BFAB+Aj
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BFEB
		push	9
		call	sub_138B2

loc_1BFEB:				; CODE XREF: sub_1BFAB+37j
		cmp	word_2671A, 50h	; 'P'
		jge	short loc_1C038
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C042
		mov	byte_266E2, 4
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		add	al, 2Ch	; ','
		mov	byte_266EE, al
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 4
		mov	byte_266F0, 0Ch
		mov	byte_266E3, 34h	; '4'
		call	word_2D004
		call	word_2D000
		mov	al, byte_266ED
		add	al, 0Bh

loc_1C033:				; CODE XREF: sub_1BFAB+2Aj
		mov	byte_266ED, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1C038:				; CODE XREF: sub_1BFAB+45j
		cmp	word_2671A, 50h	; 'P'
		jl	short loc_1C042
		call	sub_1BE43

loc_1C042:				; CODE XREF: sub_1BFAB+Fj
					; sub_1BFAB+52j ...
		pop	bp
		retn
sub_1BFAB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C044	proc near		; CODE XREF: sub_1C2E5+1A6p
		push	bp
		mov	bp, sp
		call	sub_1BC73
		inc	word_25A3A
		call	sub_1BC73
		inc	word_25A3A
		cmp	word_2671A, 10h
		jnz	short loc_1C07C
		call	sub_1BC3C
		mov	byte_266ED, 40h	; '@'
		mov	byte_266E2, 4
		mov	byte_266EE, 40h	; '@'
		mov	byte_266EC, 1
		mov	byte_266E3, 37h	; '7'
		call	word_2D004

loc_1C07C:				; CODE XREF: sub_1C044+16j
		cmp	word_2671A, 10h
		jle	short loc_1C0BD
		cmp	byte_266CE, 0
		jnz	short loc_1C0AB
		call	word_2D000
		mov	al, byte_266ED
		neg	al
		mov	byte_266ED, al
		call	word_2D000
		mov	al, byte_266ED
		neg	al
		add	al, 0FDh ; 'ý'
		mov	byte_266ED, al
		push	3
		call	sub_138B2

loc_1C0AB:				; CODE XREF: sub_1C044+44j
		cmp	byte_25A26, 0
		jnz	short loc_1C0BD
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_1C0BD:				; CODE XREF: sub_1C044+3Dj
					; sub_1C044+6Cj
		pop	bp
		retn
sub_1C044	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C0BF	proc near		; CODE XREF: sub_1C2E5+1ACp
		push	bp
		mov	bp, sp
		call	sub_1BDB4
		mov	ah, 0
		or	ax, ax
		jz	short loc_1C0EB
		cmp	ax, 2
		jnz	loc_1C162
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8

loc_1C0E7:				; CODE XREF: sub_1C0BF+97j
		add	al, 40h	; '@'
		jmp	short loc_1C147
; ---------------------------------------------------------------------------

loc_1C0EB:				; CODE XREF: sub_1C0BF+Aj
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C0FF
		push	9
		call	sub_138B2

loc_1C0FF:				; CODE XREF: sub_1C0BF+37j
		cmp	word_2671A, 50h	; 'P'
		jge	short loc_1C14C
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C162
		mov	byte_266E2, 4
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		add	al, 2Ch	; ','
		mov	byte_266EE, al
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 4
		mov	byte_266F0, 0Ch
		mov	byte_266E3, 34h	; '4'
		call	word_2D004
		call	word_2D000
		mov	al, byte_266ED
		add	al, 0F5h ; 'õ'

loc_1C147:				; CODE XREF: sub_1C0BF+2Aj
		mov	byte_266ED, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1C14C:				; CODE XREF: sub_1C0BF+45j
		cmp	word_2671A, 50h	; 'P'
		jnz	short loc_1C158
		mov	al, byte_266ED
		jmp	short loc_1C0E7
; ---------------------------------------------------------------------------

loc_1C158:				; CODE XREF: sub_1C0BF+92j
		cmp	word_2671A, 50h	; 'P'
		jl	short loc_1C162
		call	sub_1BE43

loc_1C162:				; CODE XREF: sub_1C0BF+Fj
					; sub_1C0BF+52j ...
		pop	bp
		retn
sub_1C0BF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C164	proc near		; CODE XREF: sub_1C2E5+1B2p
		push	bp
		mov	bp, sp
		call	sub_1BC73
		inc	word_25A3A
		call	sub_1BC73
		inc	word_25A3A
		cmp	word_2671A, 10h
		jnz	short loc_1C19C
		call	sub_1BC3C
		mov	byte_266ED, 0
		mov	byte_266E2, 1
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 10h
		call	word_2D004

loc_1C19C:				; CODE XREF: sub_1C164+16j
		cmp	word_2671A, 10h
		jle	short loc_1C1CD
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C1BB
		call	word_2D000
		push	3
		call	sub_138B2

loc_1C1BB:				; CODE XREF: sub_1C164+4Aj
		cmp	byte_25A26, 0
		jnz	short loc_1C1CD
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_1C1CD:				; CODE XREF: sub_1C164+3Dj
					; sub_1C164+5Cj
		pop	bp
		retn
sub_1C164	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C1CF	proc near		; CODE XREF: sub_1C2E5+1B8p

; FUNCTION CHUNK AT 87B5 SIZE 0000000C BYTES

		push	bp
		mov	bp, sp
		call	sub_1BDB4
		mov	ah, 0
		or	ax, ax
		jz	short loc_1C245
		cmp	ax, 2
		jnz	short loc_1C24F
		mov	byte_266E2, 1
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 10h
		call	sub_13D52
		mov	byte_266ED, al
		sub	word ptr dword_266E4, 200h
		call	word_2D004
		call	word_2D000
		call	sub_13D52
		mov	byte_266ED, al
		add	word ptr dword_266E4, 400h
		call	word_2D000
		call	sub_13D52
sub_1C1CF	endp ; sp-analysis failed

; START	OF FUNCTION CHUNK FOR sub_1EA4B

loc_1C21B:				; CODE XREF: sub_1EA4B:loc_1EA6Bj
		mov	byte_266ED, al
		sub	word ptr dword_266E4, 200h
; END OF FUNCTION CHUNK	FOR sub_1EA4B
		sub	word ptr dword_266E4+2,	200h
		call	word_2D000
		call	sub_13D52
		mov	byte_266ED, al
		add	word ptr dword_266E4+2,	400h
		call	word_2D000
		push	9
		call	sub_138B2
; START	OF FUNCTION CHUNK FOR sub_1C1CF

loc_1C245:				; CODE XREF: sub_1C1CF+Aj
		cmp	word_2671A, 50h	; 'P'
		jl	short loc_1C24F
		call	sub_1BE43

loc_1C24F:				; CODE XREF: sub_1C1CF+Fj
					; sub_1C1CF+7Bj
		pop	bp
		retn
; END OF FUNCTION CHUNK	FOR sub_1C1CF

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C251	proc near		; CODE XREF: sub_1C2E5+1BEp
		push	bp
		mov	bp, sp
		call	sub_1BC73
		inc	word_25A3A
		call	sub_1BC73
		inc	word_25A3A
		cmp	word_2671A, 10h
		jnz	short loc_1C26C
		call	sub_1BC3C

loc_1C26C:				; CODE XREF: sub_1C251+16j
		cmp	word_2671A, 10h
		jle	short loc_1C2E3
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C2AD
		mov	byte_266E2, 2
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EE, 38h	; '8'
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 10h
		mov	byte_266ED, 0
		call	word_2D004
		call	word_2D000
		push	3
		call	sub_138B2

loc_1C2AD:				; CODE XREF: sub_1C251+2Dj
		cmp	word_26716, 0C8h ; 'È'
		jg	short loc_1C2D1
		mov	byte_266E2, 1
		mov	byte_266EE, 20h	; ' '
		mov	byte_266EC, 1Bh
		mov	byte_266EF, 2
		call	word_2D004
		call	word_2D000

loc_1C2D1:				; CODE XREF: sub_1C251+62j
		cmp	byte_25A26, 0
		jnz	short loc_1C2E3
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0

loc_1C2E3:				; CODE XREF: sub_1C251+20j
					; sub_1C251+85j
		pop	bp
		retn
sub_1C251	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C2E5	proc far

var_2		= word ptr -2

; FUNCTION CHUNK AT 8BEA SIZE 00000018 BYTES

		enter	2, 0
		call	sub_1B95C
		mov	al, byte_26719
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 4
		ja	loc_1C675
		add	bx, bx
		jmp	word ptr cs:[bx-73CCh]
; ---------------------------------------------------------------------------
		mov	byte_25A27, 0
		mov	byte_25A26, 0
		inc	byte_26719
		mov	byte_2671D, 0
		mov	byte_23DC4, 80h	; '€'
		mov	byte_266D3, 1
		mov	word_26716, 1770h
		mov	word_26720, 1770h
		jmp	loc_1C67A
; ---------------------------------------------------------------------------
		push	53CAh
		call	sub_13D32
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_1C343
		cmp	ax, 0FFh
		jz	short loc_1C348
		jmp	short loc_1C39E
; ---------------------------------------------------------------------------

loc_1C343:				; CODE XREF: sub_1C2E5+55j
		call	sub_1BD23
		jmp	short loc_1C39E
; ---------------------------------------------------------------------------

loc_1C348:				; CODE XREF: sub_1C2E5+5Aj
		cmp	word_2671A, 40h	; '@'
		jg	short loc_1C37B
		cmp	byte_2671F, 0
		jz	short loc_1C35D
		cmp	byte_2671F, 3
		jnz	short loc_1C365

loc_1C35D:				; CODE XREF: sub_1C2E5+6Fj
		mov	word_26712, 0FFF0h
		jmp	short loc_1C39E
; ---------------------------------------------------------------------------

loc_1C365:				; CODE XREF: sub_1C2E5+76j
		cmp	byte_2671F, 1
		jz	short loc_1C373
		cmp	byte_2671F, 2
		jnz	short loc_1C39E

loc_1C373:				; CODE XREF: sub_1C2E5+85j
		mov	word_26712, 10h
		jmp	short loc_1C39E
; ---------------------------------------------------------------------------

loc_1C37B:				; CODE XREF: sub_1C2E5+68j
		cmp	byte_2671F, 3
		jnb	short loc_1C388
		inc	byte_2671F
		jmp	short loc_1C38D
; ---------------------------------------------------------------------------

loc_1C388:				; CODE XREF: sub_1C2E5+9Bj
		mov	byte_2671F, 0

loc_1C38D:				; CODE XREF: sub_1C2E5+A1j
					; sub_1C2E5:loc_1C46Fj
					; DATA XREF: ...
		mov	byte_2671D, 0
		mov	word_2671A, 0
		mov	word_26712, 0

loc_1C39E:				; CODE XREF: sub_1C2E5+5Cj
					; sub_1C2E5+61j ...
		inc	word_2671A
		call	sub_1E67C
		cmp	word_266CA, 2418h
		jb	loc_1C67A
		inc	byte_26719
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	word_26714, 8
		mov	word_255AC, 777Fh
		mov	byte_2CDCA, 0
		jmp	loc_1C67A
; ---------------------------------------------------------------------------
		push	53CAh
		call	sub_13D32
		cmp	word ptr dword_2670A, 0C00h
		jge	short loc_1C3EA
		mov	word_26712, 20h	; ' '
		jmp	short loc_1C400
; ---------------------------------------------------------------------------

loc_1C3EA:				; CODE XREF: sub_1C2E5+FBj
		cmp	word ptr dword_2670A, 0C10h
		jl	short loc_1C3FA
		mov	word_26712, 0FFE0h
		jmp	short loc_1C400
; ---------------------------------------------------------------------------

loc_1C3FA:				; CODE XREF: sub_1C2E5+10Bj
		mov	word_26712, 0

loc_1C400:				; CODE XREF: sub_1C2E5+103j
					; sub_1C2E5+113j
		call	sub_1E67C
		cmp	word_2671A, 20h	; ' '
		jl	loc_1C67A
		mov	word_26712, 0
		mov	byte_23DC4, 0
		mov	byte_266D3, 1
		mov	word_25A3A, 0
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670A+2,	600h
		mov	word ptr dword_2670E, 0
		push	large 0FFFF0000h
		call	sub_1E6F3
		mov	byte_25A24, 0
		jmp	loc_1C67A
; ---------------------------------------------------------------------------
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	cx, 0Ah		; switch 10 cases
		mov	bx, offset unk_1C69C

loc_1C45F:				; CODE XREF: sub_1C2E5+185j
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1C46F
		add	bx, 2
		loop	loc_1C45F
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------

loc_1C46F:				; CODE XREF: sub_1C2E5+180j
		jmp	word ptr cs:[bx+14h] ; switch jump
; ---------------------------------------------------------------------------
		call	sub_1BD4B
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		call	sub_1BE78
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		call	sub_1BF52
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		call	sub_1BFAB
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		call	sub_1C044
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		call	sub_1C0BF
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		call	sub_1C164
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		call	sub_1C1CF
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		call	sub_1C251
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------
		cmp	word_2671A, 20h	; ' '
		jge	short loc_1C4BA
		call	sub_1BC73
		inc	word_25A3A
		jmp	loc_1C585	; default
; ---------------------------------------------------------------------------

loc_1C4BA:				; CODE XREF: sub_1C2E5+1C9j
		inc	byte_2671F
		mov	al, byte_25A24
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 4
		ja	loc_1C57F
		add	bx, bx
		jmp	word ptr cs:[bx-73FEh]
; ---------------------------------------------------------------------------
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 2
		cwd
		idiv	bx
		mov	byte_2671D, dl
		cmp	byte_2671F, 8
		jb	loc_1C57F

loc_1C4EB:				; CODE XREF: sub_1C2E5+242j
					; sub_1C2E5+25Dj ...
		mov	al, byte_25A24
		mov	ah, 0
		push	ax
		call	sub_15C7C
		mov	byte_2671D, 0FFh
		inc	byte_25A24
		mov	al, byte_25A24
		mov	ah, 0
		imul	ax, 5DCh
		mov	dx, 1770h
		sub	dx, ax
		mov	word_26716, dx
		jmp	short loc_1C57F
; ---------------------------------------------------------------------------
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		mov	byte_2671D, dl
		cmp	byte_2671F, 10h
		jb	short loc_1C57F
		jmp	short loc_1C4EB
; ---------------------------------------------------------------------------
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		add	dl, 2
		mov	byte_2671D, dl
		cmp	byte_2671F, 18h
		jb	short loc_1C57F
		jmp	short loc_1C4EB
; ---------------------------------------------------------------------------
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		add	dl, 4
		mov	byte_2671D, dl
		cmp	byte_2671F, 20h	; ' '
		jb	short loc_1C57F
		jmp	short loc_1C4EB
; ---------------------------------------------------------------------------
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		add	dl, 5
		mov	byte_2671D, dl
		cmp	byte_2671F, 28h	; '('
		jb	short loc_1C57F
		mov	byte_2671F, 0
		jmp	short loc_1C591
; ---------------------------------------------------------------------------

loc_1C57F:				; CODE XREF: sub_1C2E5+1E3j
					; sub_1C2E5+202j ...
		mov	word_2671A, 0

loc_1C585:				; CODE XREF: sub_1C2E5+187j
					; sub_1C2E5+191j ...
		call	sub_1E64E	; default
		or	al, al
		jz	short loc_1C5B1
		mov	byte_2671F, 1

loc_1C591:				; CODE XREF: sub_1C2E5+298j
		inc	byte_26719
		push	word ptr dword_2670A
		push	word ptr dword_2670A+2
		push	large 800030h
		call	sub_13E8C
		push	4
		call	sub_15C7C
		mov	word_2671A, 0

loc_1C5B1:				; CODE XREF: sub_1C2E5+2A5j
		cmp	byte_25A24, 0
		jnz	short loc_1C5C0
		cmp	word_26716, 125Ch
		jle	short loc_1C5F1

loc_1C5C0:				; CODE XREF: sub_1C2E5+2D1j
		cmp	byte_25A24, 1
		jnz	short loc_1C5CF
		cmp	word_26716, 0CE4h
		jle	short loc_1C5F1

loc_1C5CF:				; CODE XREF: sub_1C2E5+2E0j
		cmp	byte_25A24, 2
		jnz	short loc_1C5DE
		cmp	word_26716, 834h
		jle	short loc_1C5F1

loc_1C5DE:				; CODE XREF: sub_1C2E5+2EFj
		cmp	byte_25A24, 3
		jnz	loc_1C67A
		cmp	word_26716, 2BCh
		jg	loc_1C67A

loc_1C5F1:				; CODE XREF: sub_1C2E5+2D9j
					; sub_1C2E5+2E8j ...
		call	sub_1E692
		cmp	byte_2CFFA, 14h
		jnb	short loc_1C600
		mov	byte_2CFFA, 14h

loc_1C600:				; CODE XREF: sub_1C2E5+314j
		push	0Ah
		call	sub_19FD8
		mov	al, byte_25A24
		mov	ah, 0
		push	ax
		call	sub_15C7C
		mov	byte_2671D, 0FFh
		mov	word_2671A, 0
		inc	byte_25A24
		jmp	short loc_1C67A
; ---------------------------------------------------------------------------
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_1C62F
		push	4
		call	sub_15C7C

loc_1C62F:				; CODE XREF: sub_1C2E5+343j
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_1C67A
		push	3
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_1C652
		push	28h ; '('
		call	sub_19FD8

loc_1C652:				; CODE XREF: sub_1C2E5+366j
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_259A2, 0FFh
		mov	byte_25A26, 0
		mov	byte_25A27, 0
		jmp	short loc_1C67A
; ---------------------------------------------------------------------------

loc_1C675:				; CODE XREF: sub_1C2E5+11j
		call	sub_1E743
		leave
		retf
sub_1C2E5	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_1C2E5

loc_1C67A:				; CODE XREF: sub_1C2E5+45j
					; sub_1C2E5+C6j ...
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax
		push	word_26716
		push	1770h
		call	sub_19F16
		leave
		retf
; END OF FUNCTION CHUNK	FOR sub_1C2E5
; ---------------------------------------------------------------------------
		db  43h	; C
		db  8Ah	; Š
		db  81h	; 
		db  8Ah	; Š
		db  99h	; ™
		db  8Ah	; Š
		db 0B4h	; ´
		db  8Ah	; Š
		db 0CFh	; Ï
		db  8Ah	; Š
unk_1C69C	db    0			; DATA XREF: sub_1C2E5+177o
		db    0
		db    1
		db    0
		db    2
		db    0
		db    3
		db    0
		db    4
		db    0
		db    5
		db    0
		db    6
		db    0
		db    7
		db    0
		db    8
		db    0
		db 0FFh
		db    0
		db 0E3h	; ã
		db  89h	; ‰
		db 0E9h	; é
		db  89h	; ‰
		db 0EFh	; ï
		db  89h	; ‰
		db 0F5h	; õ
		db  89h	; ‰
		db 0FBh	; û
		db  89h	; ‰
		db    1
		db  8Ah	; Š
		db    7
		db  8Ah	; Š
		db  0Dh
		db  8Ah	; Š
		db  13h
		db  8Ah	; Š
		db  19h
		db  8Ah	; Š
		db  71h	; q
		db  88h	; ˆ
		db  9Dh	; 
		db  88h	; ˆ
		db  44h	; D
		db  89h	; ‰
		db 0B5h	; µ
		db  89h	; ‰
		db  8Fh	; 
		db  8Bh	; ‹

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C6CE	proc near		; CODE XREF: sub_1C736+11Bp
					; sub_1C736+13Dp ...

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
		cmp	al, byte_2CFF7
		jb	short loc_1C6ED
		mov	byte ptr [si+13h], 2

loc_1C6ED:				; CODE XREF: sub_1C6CE+19j
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		pop	si
		pop	bp
		retn	2
sub_1C6CE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C702	proc near		; CODE XREF: sub_1C736+167p

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
		cmp	al, byte_2CFF7
		jb	short loc_1C721
		mov	byte ptr [si+13h], 2

loc_1C721:				; CODE XREF: sub_1C702+19j
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		pop	si
		pop	bp
		retn	2
sub_1C702	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C736	proc near		; CODE XREF: sub_1C8C8+119p

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		mov	al, [si+14h]
		mov	ah, 0
		sub	ax, 80h	; '€'
		mov	bx, ax
		cmp	bx, 8
		ja	loc_1C8B1
		add	bx, bx
		jmp	cs:off_1C8B6[bx]

loc_1C755:				; DATA XREF: seg003:off_1C8B6o
		cmp	byte ptr [si+10h], 0
		jz	short loc_1C75D
		jmp	short loc_1C790
; ---------------------------------------------------------------------------

loc_1C75D:				; CODE XREF: sub_1C736+23j
		inc	byte ptr [si+16h]
		mov	ax, word ptr dword_2598E+2
		sub	ax, [si+4]
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, [si+2]
		push	ax
		call	sub_1DA8
		mov	[si+11h], al
		mov	al, [si+15h]
		mov	[si+10h], al
		mov	al, [si+16h]
		cmp	al, byte_2CFF7
		jb	loc_1C831
		jmp	loc_1C82D
; ---------------------------------------------------------------------------

loc_1C78A:				; CODE XREF: sub_1C736+1Aj
					; DATA XREF: seg003:8E28o
		cmp	byte ptr [si+10h], 0
		jz	short loc_1C7A6

loc_1C790:				; CODE XREF: sub_1C736+25j
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		dec	byte ptr [si+10h]
		jmp	loc_1C8B1
; ---------------------------------------------------------------------------

loc_1C7A6:				; CODE XREF: sub_1C736+58j
		inc	byte ptr [si+16h]
		mov	al, [si+17h]
		add	[si+11h], al
		mov	al, [si+15h]
		mov	[si+10h], al
		mov	al, [si+16h]
		cmp	al, byte_2CFF7
		jb	short loc_1C831
		jmp	short loc_1C82D
; ---------------------------------------------------------------------------

loc_1C7C0:				; CODE XREF: sub_1C736+1Aj
					; DATA XREF: seg003:8E2Ao
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		mov	al, byte_2CFF7
		add	[si+10h], al
		jmp	loc_1C8B1
; ---------------------------------------------------------------------------

loc_1C7D9:				; CODE XREF: sub_1C736+1Aj
					; DATA XREF: seg003:8E2Co
		cmp	byte ptr [si+10h], 0
		jz	short loc_1C821
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		cmp	byte ptr [si+10h], 1
		jbe	short loc_1C7FF
		mov	al, [si+10h]
		add	al, 0FEh ; 'þ'
		mov	[si+10h], al
		jmp	short loc_1C803
; ---------------------------------------------------------------------------

loc_1C7FF:				; CODE XREF: sub_1C736+BDj
		mov	byte ptr [si+10h], 0

loc_1C803:				; CODE XREF: sub_1C736+C7j
		cmp	byte ptr [si+10h], 20h ; ' '
		jnb	loc_1C8B1
		mov	al, [si+17h]
		sub	al, [si+11h]
		cbw
		mov	bx, 4
		cwd
		idiv	bx
		add	al, [si+11h]
		mov	[si+11h], al
		jmp	loc_1C8B1
; ---------------------------------------------------------------------------

loc_1C821:				; CODE XREF: sub_1C736+A7j
		mov	al, [si+17h]
		mov	[si+11h], al
		mov	al, [si+15h]
		mov	[si+10h], al

loc_1C82D:				; CODE XREF: sub_1C736+51j
					; sub_1C736+88j
		mov	byte ptr [si+13h], 2

loc_1C831:				; CODE XREF: sub_1C736+4Dj
					; sub_1C736+86j
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		jmp	short loc_1C8B1
; ---------------------------------------------------------------------------

loc_1C843:				; CODE XREF: sub_1C736+1Aj
					; DATA XREF: seg003:8E2Eo
		cmp	word ptr [si+2], 0
		jle	short loc_1C850
		cmp	word ptr [si+2], 1800h
		jl	short loc_1C8B1

loc_1C850:				; CODE XREF: sub_1C736+111j
		push	si
		call	sub_1C6CE
		jmp	short loc_1C8B1
; ---------------------------------------------------------------------------

loc_1C856:				; CODE XREF: sub_1C736+1Aj
					; DATA XREF: seg003:8E30o
		cmp	word ptr [si+4], 0
		jle	short loc_1C89C
		cmp	word ptr [si+4], 1700h
		jl	short loc_1C8B1
		jmp	short loc_1C89C
; ---------------------------------------------------------------------------

loc_1C865:				; CODE XREF: sub_1C736+1Aj
					; DATA XREF: seg003:8E32o
		cmp	word ptr [si+2], 0
		jle	short loc_1C872
		cmp	word ptr [si+2], 1800h
		jl	short loc_1C876

loc_1C872:				; CODE XREF: sub_1C736+133j
		push	si
		call	sub_1C6CE

loc_1C876:				; CODE XREF: sub_1C736+13Aj
		cmp	word ptr [si+4], 0
		jle	short loc_1C89C
		cmp	word ptr [si+4], 1700h
		jl	short loc_1C8B1
		jmp	short loc_1C89C
; ---------------------------------------------------------------------------

loc_1C885:				; CODE XREF: sub_1C736+1Aj
					; DATA XREF: seg003:8E34o
		cmp	word ptr [si+2], 0
		jle	short loc_1C892
		cmp	word ptr [si+2], 1800h
		jl	short loc_1C896

loc_1C892:				; CODE XREF: sub_1C736+153j
		push	si
		call	sub_1C6CE

loc_1C896:				; CODE XREF: sub_1C736+15Aj
		cmp	word ptr [si+4], 0
		jg	short loc_1C8B1

loc_1C89C:				; CODE XREF: sub_1C736+124j
					; sub_1C736+12Dj ...
		push	si
		call	sub_1C702
		jmp	short loc_1C8B1
; ---------------------------------------------------------------------------

loc_1C8A2:				; CODE XREF: sub_1C736+1Aj
					; DATA XREF: seg003:8E36o
		cmp	byte_266CC, 0
		jz	short loc_1C8B1
		mov	al, byte_2CFF7
		mov	ah, 0
		add	[si+0Ch], ax

loc_1C8B1:				; CODE XREF: sub_1C736+14j
					; sub_1C736+6Dj ...
		pop	si
		pop	bp
		retn	2
sub_1C736	endp

; ---------------------------------------------------------------------------
off_1C8B6	dw offset loc_1C755	; DATA XREF: sub_1C736+1Ar
		dw offset loc_1C78A
		dw offset loc_1C7C0
		dw offset loc_1C7D9
		dw offset loc_1C843
		dw offset loc_1C856
		dw offset loc_1C865
		dw offset loc_1C885
		dw offset loc_1C8A2

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1C8C8	proc far		; CODE XREF: sub_AB88+5FP

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
		mov	word_2D006, 0
		mov	si, 86B8h
		cmp	byte_2CFF9, 0
		jnz	loc_1CB44
		xor	di, di
		jmp	loc_1CAFC
; ---------------------------------------------------------------------------

loc_1C8EC:				; CODE XREF: sub_1C8C8+238j
		cmp	byte ptr [si], 0
		jz	loc_1CAF8
		cmp	byte ptr [si], 2
		jnz	short loc_1C8FE
		mov	byte ptr [si], 0
		jmp	loc_1CAF8
; ---------------------------------------------------------------------------

loc_1C8FE:				; CODE XREF: sub_1C8C8+2Ej
		inc	[bp+var_2]
		cmp	byte_2CFFA, 0
		jz	short loc_1C961
		cmp	byte ptr [si+13h], 4
		jnb	short loc_1C939
		mov	byte ptr [si+13h], 4
		cmp	di, 0C8h ; 'È'
		jge	short loc_1C91D
		mov	ax, 70h	; 'p'
		jmp	short loc_1C920
; ---------------------------------------------------------------------------

loc_1C91D:				; CODE XREF: sub_1C8C8+4Ej
		mov	ax, 6Ch	; 'l'

loc_1C920:				; CODE XREF: sub_1C8C8+53j
		mov	[si+18h], ax
		cmp	byte ptr [si+1], 0
		jz	short loc_1C931
		add	dword_2569A, 64h ; 'd'
		jmp	short loc_1C961
; ---------------------------------------------------------------------------

loc_1C931:				; CODE XREF: sub_1C8C8+5Fj
		add	dword_2569A, 0Ah
		jmp	short loc_1C961
; ---------------------------------------------------------------------------

loc_1C939:				; CODE XREF: sub_1C8C8+44j
		inc	byte ptr [si+13h]
		cmp	byte ptr [si+13h], 14h
		jb	short loc_1C94F
		lea	ax, [si+2]
		push	ax
		call	sub_13D32
		mov	byte ptr [si], 2
		jmp	loc_1CAF8
; ---------------------------------------------------------------------------

loc_1C94F:				; CODE XREF: sub_1C8C8+78j
		mov	al, [si+13h]
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C961
		inc	word ptr [si+18h]

loc_1C961:				; CODE XREF: sub_1C8C8+3Ej
					; sub_1C8C8+67j ...
		inc	byte ptr [si+1]
		cmp	byte ptr [si+12h], 2
		jb	short loc_1C9DA
		cmp	byte ptr [si+12h], 2
		jnz	short loc_1C976
		mov	byte ptr [si+12h], 0
		jmp	short loc_1C9DA
; ---------------------------------------------------------------------------

loc_1C976:				; CODE XREF: sub_1C8C8+A6j
		cmp	byte ptr [si+12h], 3
		jnz	short loc_1C99C
		mov	eax, [si+2]
		mov	[si+6],	eax
		mov	ax, [si+0Ah]
		shl	ax, 3
		sub	[si+2],	ax
		mov	ax, [si+0Ch]
		shl	ax, 3
		sub	[si+4],	ax
		mov	byte ptr [si+12h], 4
		jmp	short loc_1C9C8
; ---------------------------------------------------------------------------

loc_1C99C:				; CODE XREF: sub_1C8C8+B2j
		cmp	byte ptr [si+12h], 4
		jnz	short loc_1C9AB
		lea	ax, [si+2]
		push	ax
		call	sub_13D32
		jmp	short loc_1C9C8
; ---------------------------------------------------------------------------

loc_1C9AB:				; CODE XREF: sub_1C8C8+D8j
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

loc_1C9C8:				; CODE XREF: sub_1C8C8+D2j
					; sub_1C8C8+E1j
		inc	byte ptr [si+12h]
		cmp	byte ptr [si+12h], 14h
		jb	loc_1CAF8
		mov	byte ptr [si+12h], 2
		jmp	loc_1CAF8
; ---------------------------------------------------------------------------

loc_1C9DA:				; CODE XREF: sub_1C8C8+A0j
					; sub_1C8C8+ACj
		cmp	byte ptr [si+13h], 1
		jnz	short loc_1C9E6
		push	si
		call	sub_1C736
		jmp	short loc_1CA27
; ---------------------------------------------------------------------------

loc_1C9E6:				; CODE XREF: sub_1C8C8+116j
		cmp	byte ptr [si+13h], 0
		jnz	short loc_1CA27
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
		jnz	short loc_1CA17
		mov	al, [si+15h]
		mov	[si+10h], al
		mov	byte ptr [si+13h], 2

loc_1CA17:				; CODE XREF: sub_1C8C8+143j
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+11h]
		mov	al, [si+10h]
		mov	ah, 0
		push	ax
		call	sub_13DF2

loc_1CA27:				; CODE XREF: sub_1C8C8+11Cj
					; sub_1C8C8+122j
		lea	ax, [si+2]
		push	ax
		call	sub_13D32
		cmp	ax, 0FF80h
		jle	short loc_1CA43
		cmp	ax, 1880h
		jge	short loc_1CA43
		cmp	dx, 0FF80h
		jle	short loc_1CA43
		cmp	dx, 1780h
		jl	short loc_1CA49

loc_1CA43:				; CODE XREF: sub_1C8C8+169j
					; sub_1C8C8+16Ej ...
		mov	byte ptr [si], 2
		jmp	loc_1CAF8
; ---------------------------------------------------------------------------

loc_1CA49:				; CODE XREF: sub_1C8C8+179j
		cmp	byte_2CFFA, 0
		jnz	loc_1CAF8
		sub	ax, word ptr dword_2598E
		sub	dx, word ptr dword_2598E+2
		cmp	byte_259A2, 0
		jnz	short loc_1CAC5
		cmp	byte ptr [si+12h], 0
		jz	short loc_1CA82
		add	ax, 40h	; '@'
		cmp	ax, 80h	; '€'
		ja	short loc_1CAC5
		add	dx, 40h	; '@'
		cmp	dx, 80h	; '€'
		ja	short loc_1CAC5
		mov	byte ptr [si], 2
		mov	byte_259A9, 1
		jmp	short loc_1CAF8
; ---------------------------------------------------------------------------

loc_1CA82:				; CODE XREF: sub_1C8C8+19Dj
		add	ax, 100h
		cmp	ax, 240h
		ja	short loc_1CAC5
		add	dx, 160h
		cmp	dx, 2C0h
		ja	short loc_1CAC5
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	large 200002h
		nop
		push	cs
		call	near ptr sub_13E2A
		mov	byte ptr [si+12h], 1
		cmp	word_2CFFC, 3E7h
		jnb	short loc_1CAC5
		inc	word_2CFFC
		call	sub_F091
		movzx	eax, word_2CFFE
		add	dword_2569A, eax

loc_1CAC5:				; CODE XREF: sub_1C8C8+197j
					; sub_1C8C8+1A5j ...
		cmp	di, 0C8h ; 'È'
		jl	short loc_1CAF8
		mov	ax, [si+2]
		sar	ax, 4
		add	ax, 1Ch
		mov	bx, word_2D006
		shl	bx, 2
		mov	[bx-792Eh], ax
		mov	ax, [si+4]
		add	ax, 0C0h ; 'À'
		push	ax
		call	sub_13CE8
		mov	bx, word_2D006
		shl	bx, 2
		mov	[bx-792Ch], ax
		inc	word_2D006

loc_1CAF8:				; CODE XREF: sub_1C8C8+27j
					; sub_1C8C8+33j ...
		inc	di
		sub	si, 1Ah

loc_1CAFC:				; CODE XREF: sub_1C8C8+21j
		cmp	di, 1B8h
		jl	loc_1C8EC
		cmp	byte_266E0, 0
		jnz	loc_1CC19
		mov	di, 18h
		mov	al, byte_266D5
		mov	ah, 0
		add	di, ax
		mov	al, byte_25688
		mov	ah, 0
		shl	ax, 3
		add	di, ax
		cmp	[bp+var_2], di
		jl	short loc_1CB31
		cmp	byte_266CC, 0
		jnz	loc_1CC19
		jmp	short loc_1CB3B
; ---------------------------------------------------------------------------

loc_1CB31:				; CODE XREF: sub_1C8C8+25Cj
		lea	ax, [di+18h]
		cmp	ax, [bp+var_2]
		jg	loc_1CC19

loc_1CB3B:				; CODE XREF: sub_1C8C8+267j
		mov	word_266D0, 2
		jmp	loc_1CC19
; ---------------------------------------------------------------------------

loc_1CB44:				; CODE XREF: sub_1C8C8+1Bj
		mov	al, byte_2CFF9
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		add	al, 48h	; 'H'
		mov	[bp+var_9], al
		mov	[bp+var_4], 1
		mov	[bp+var_6], 1
		mov	al, byte_25688
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 4
		ja	short loc_1CB84
		add	bx, bx
		jmp	cs:off_1CC29[bx]

loc_1CB71:				; DATA XREF: seg003:off_1CC29o
		mov	[bp+var_8], 3E8h
		jmp	short loc_1CB84
; ---------------------------------------------------------------------------

loc_1CB78:				; CODE XREF: sub_1C8C8+2A4j
					; DATA XREF: seg003:919Bo ...
		mov	[bp+var_8], 640h
		jmp	short loc_1CB84
; ---------------------------------------------------------------------------

loc_1CB7F:				; CODE XREF: sub_1C8C8+2A4j
					; DATA XREF: seg003:91A1o
		mov	[bp+var_8], 7D0h

loc_1CB84:				; CODE XREF: sub_1C8C8+2A0j
					; sub_1C8C8+2AEj ...
		mov	dword_259E2, 0
		xor	di, di
		jmp	short loc_1CBF1
; ---------------------------------------------------------------------------

loc_1CB91:				; CODE XREF: sub_1C8C8+32Dj
		cmp	byte ptr [si], 1
		jnz	short loc_1CBED
		mov	word ptr [si+0Ah], 0
		mov	word ptr [si+0Ch], 0
		lea	ax, [si+2]
		push	ax
		call	sub_13D32
		cmp	[bp+var_9], 4Ch	; 'L'
		jnb	short loc_1CBB7
		mov	al, [bp+var_9]
		mov	ah, 0
		mov	[si+18h], ax
		jmp	short loc_1CBED
; ---------------------------------------------------------------------------

loc_1CBB7:				; CODE XREF: sub_1C8C8+2E3j
		movzx	eax, [bp+var_4]
		add	dword_259E2, eax
		add	dword_2569A, eax
		push	word ptr [si+2]
		push	word ptr [si+4]
		push	[bp+var_4]
		call	sub_13DAA
		mov	ax, [bp+var_6]
		add	[bp+var_4], ax
		add	[bp+var_6], 3
		mov	ax, [bp+var_4]
		cmp	ax, [bp+var_8]
		jbe	short loc_1CBEA
		mov	ax, [bp+var_8]
		mov	[bp+var_4], ax

loc_1CBEA:				; CODE XREF: sub_1C8C8+31Aj
		mov	byte ptr [si], 2

loc_1CBED:				; CODE XREF: sub_1C8C8+2CCj
					; sub_1C8C8+2EDj
		inc	di
		sub	si, 1Ah

loc_1CBF1:				; CODE XREF: sub_1C8C8+2C7j
		cmp	di, 1B8h
		jl	short loc_1CB91
		cmp	dword_259E2, 0
		jz	short loc_1CC0A
		mov	byte_259DB, 2
		mov	word_259DE, 67E8h

loc_1CC0A:				; CODE XREF: sub_1C8C8+335j
		inc	byte_2CFF9
		cmp	[bp+var_9], 4Ch	; 'L'
		jb	short loc_1CC19
		mov	byte_2CFF9, 0

loc_1CC19:				; CODE XREF: sub_1C8C8+241j
					; sub_1C8C8+263j ...
		cmp	byte_2CFFA, 0
		jz	short loc_1CC24
		dec	byte_2CFFA

loc_1CC24:				; CODE XREF: sub_1C8C8+356j
		pop	di
		pop	si
		leave
		retf
sub_1C8C8	endp

; ---------------------------------------------------------------------------
		db 0
off_1CC29	dw offset loc_1CB71	; DATA XREF: sub_1C8C8+2A4r
		dw offset loc_1CB78
		dw offset loc_1CB78
		dw offset loc_1CB78
		dw offset loc_1CB7F

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CC33	proc near		; CODE XREF: seg003:943Bp
		push	bp
		mov	bp, sp
		mov	al, byte_266EC
		mov	ah, 0
		sub	ax, 1Bh
		mov	bx, ax
		cmp	bx, 15h
		ja	short loc_1CC89
		add	bx, bx
		jmp	cs:off_1CC8C[bx]

loc_1CC4C:				; DATA XREF: seg003:9224o seg003:9226o
		mov	al, byte_266F0
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		mov	dl, byte_266F0
		sub	dl, al
		mov	byte_266F0, dl
		cmp	byte_266EF, 2
		jb	short loc_1CC89
		dec	byte_266EF
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1CC6E:				; CODE XREF: sub_1CC33+14j
					; DATA XREF: seg003:9220o ...
		cmp	byte_266EF, 3
		jb	short loc_1CC89
		mov	al, byte_266EF
		add	al, 0FEh ; 'þ'
		jmp	short loc_1CC86
; ---------------------------------------------------------------------------

loc_1CC7C:				; CODE XREF: sub_1CC33+14j
					; DATA XREF: seg003:off_1CC8Co	...
		mov	al, byte_266EF
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1

loc_1CC86:				; CODE XREF: sub_1CC33+47j
		mov	byte_266EF, al

loc_1CC89:				; CODE XREF: sub_1CC33+10j
					; sub_1CC33+14j ...
		pop	bp
		retn
sub_1CC33	endp

; ---------------------------------------------------------------------------
		db 0
off_1CC8C	dw offset loc_1CC7C	; DATA XREF: sub_1CC33+14r
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC7C
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC89
		dw offset loc_1CC7C
		dw offset loc_1CC6E
		dw offset loc_1CC6E
		dw offset loc_1CC4C
		dw offset loc_1CC4C

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CCB8	proc far		; CODE XREF: seg003:944Ep

var_2		= word ptr -2
arg_0		= word ptr  6
arg_4		= word ptr  0Ah

; FUNCTION CHUNK AT 0EFF SIZE 00000014 BYTES
; FUNCTION CHUNK AT 0F99 SIZE 00000008 BYTES
; FUNCTION CHUNK AT 0FD5 SIZE 00000006 BYTES
; FUNCTION CHUNK AT 0FF7 SIZE 00000002 BYTES
; FUNCTION CHUNK AT 3F18 SIZE 00000014 BYTES
; FUNCTION CHUNK AT 427E SIZE 000000AF BYTES
; FUNCTION CHUNK AT 433B SIZE 00000006 BYTES
; FUNCTION CHUNK AT 7D00 SIZE 00000031 BYTES
; FUNCTION CHUNK AT 7E5A SIZE 0000001E BYTES

		enter	2, 0
		mov	al, byte_266EC
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	cx, 0Ah		; switch 10 cases
		mov	bx, offset byte_1CD46

loc_1CCCA:				; CODE XREF: sub_1CCB8+1Dj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1CCD9
		add	bx, 2
		loop	loc_1CCCA
		jmp	short locret_1CD43 ; default
; ---------------------------------------------------------------------------

loc_1CCD9:				; CODE XREF: sub_1CCB8+18j
		jmp	word ptr cs:[bx+14h] ; switch jump
; ---------------------------------------------------------------------------
		mov	byte_266EC, 30h	; '0'
		jmp	short loc_1CCE9
; ---------------------------------------------------------------------------
		mov	byte_266EC, 2Fh	; '/'

loc_1CCE9:				; CODE XREF: sub_1CCB8+2Aj
		mov	byte_266EF, 2
		mov	byte_266F0, 6
		leave
		retn
; ---------------------------------------------------------------------------
		mov	al, byte_266F0
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		add	al, byte_266F0
		mov	byte_266F0, al
		leave
		retn
; ---------------------------------------------------------------------------
		mov	al, byte_266EF
		add	al, 2
		jmp	short loc_1CD40
; ---------------------------------------------------------------------------
		mov	al, byte_266EF
		mov	ah, 0
		imul	ax, 3
		mov	byte_266EF, al
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	byte_266EF, al
		cmp	byte_266EF, 30h	; '0'
		jbe	short locret_1CD43 ; default
		mov	byte_266EF, 30h	; '0'
		leave
		retn
; ---------------------------------------------------------------------------
		mov	al, byte_266EF
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		add	al, byte_266EF

loc_1CD40:				; CODE XREF: sub_1CCB8+55j
		mov	byte_266EF, al

locret_1CD43:				; CODE XREF: sub_1CCB8+1Fj
					; sub_1CCB8+71j
		leave			; default
		retn
sub_1CCB8	endp ; sp-analysis failed

; ---------------------------------------------------------------------------
		db 0
byte_1CD46	db 2 dup(0), 1,	0, 1Bh,	0, 1Ch,	0, 26h,	0, 2Ch,	0, 2Dh
					; DATA XREF: sub_1CCB8+Fo
		db 0, 2Eh, 0, 2Fh, 0, 30h, 0, 54h, 92h,	4Dh, 92h, 0A2h
		db 92h,	0A2h, 92h, 7Fh,	92h, 7Fh, 92h, 78h, 92h, 78h, 92h
		db 65h,	92h, 65h, 92h

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CD6E	proc far		; CODE XREF: seg003:9459p

var_2		= word ptr -2
arg_24		= dword	ptr  28h

; FUNCTION CHUNK AT 53B6 SIZE 000000A1 BYTES
; FUNCTION CHUNK AT 57A5 SIZE 00000006 BYTES
; FUNCTION CHUNK AT 5B19 SIZE 0000001A BYTES
; FUNCTION CHUNK AT 7E00 SIZE 00000055 BYTES

		enter	2, 0
		mov	al, byte_266EC
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	cx, 0Ah		; switch 10 cases
		mov	bx, offset byte_1CDEA

loc_1CD80:				; CODE XREF: sub_1CD6E+1Dj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1CD8F
		add	bx, 2
		loop	loc_1CD80
		jmp	short locret_1CDE7 ; default
; ---------------------------------------------------------------------------

loc_1CD8F:				; CODE XREF: sub_1CD6E+18j
		jmp	word ptr cs:[bx+14h] ; switch jump
; ---------------------------------------------------------------------------
		mov	byte_266EC, 2Eh	; '.'
		jmp	short loc_1CD9F
; ---------------------------------------------------------------------------
		mov	byte_266EC, 2Dh	; '-'

loc_1CD9F:				; CODE XREF: sub_1CD6E+2Aj
		mov	byte_266EF, 3
		mov	byte_266F0, 6
		leave
		retn
; ---------------------------------------------------------------------------
		mov	al, byte_266F0
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		add	al, byte_266F0
		mov	byte_266F0, al
		inc	byte_266EF
		leave
		retn
; ---------------------------------------------------------------------------
		mov	al, byte_266EF
		add	al, 4
		jmp	short loc_1CDE4
; ---------------------------------------------------------------------------
		mov	al, byte_266EF
		add	al, al
		mov	byte_266EF, al
		cmp	byte_266EF, 30h	; '0'
		jbe	short locret_1CDE7 ; default
		mov	byte_266EF, 30h	; '0'
		leave
		retn
; ---------------------------------------------------------------------------
		mov	al, byte_266EF
		add	al, al

loc_1CDE4:				; CODE XREF: sub_1CD6E+59j
		mov	byte_266EF, al

locret_1CDE7:				; CODE XREF: sub_1CD6E+1Fj
					; sub_1CD6E+68j
		leave			; default
		retn
sub_1CD6E	endp ; sp-analysis failed

; ---------------------------------------------------------------------------
		db 0
byte_1CDEA	db 2 dup(0), 1,	0, 1Bh,	0, 1Ch,	0, 26h,	0, 2Ch,	0, 2Dh
					; DATA XREF: sub_1CD6E+Fo
		db 0, 2Eh, 0, 2Fh, 0, 30h, 0, 0Ah, 93h,	3, 93h,	4Fh, 93h
		db 4Fh,	93h, 39h, 93h, 39h, 93h, 32h, 93h, 32h,	93h, 1Bh
		db 93h,	1Bh, 93h

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CE12	proc near		; CODE XREF: seg003:9438p seg003:9443p ...
		push	bp
		mov	bp, sp
		mov	al, byte_266EC
		mov	ah, 0
		sub	ax, 26h	; '&'
		mov	bx, ax
		cmp	bx, 0Ah
		ja	loc_1CEAD
		add	bx, bx
		jmp	cs:off_1CEAF[bx]

loc_1CE2D:				; DATA XREF: seg003:9431o seg003:9433o
		cmp	byte_266D5, 18h
		jb	short loc_1CE3A
		inc	byte_266EF
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1CE3A:				; CODE XREF: sub_1CE12+20j
		cmp	byte_266D5, 6
		ja	short loc_1CEAD
		cmp	byte_266EF, 2
		jb	short loc_1CEAD
		dec	byte_266EF
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1CE4E:				; CODE XREF: sub_1CE12+16j
					; DATA XREF: seg003:942Do ...
		cmp	byte_266D5, 18h
		jb	short loc_1CE57
		jmp	short loc_1CE81
; ---------------------------------------------------------------------------

loc_1CE57:				; CODE XREF: sub_1CE12+41j
		cmp	byte_266D5, 6
		ja	short loc_1CEAD
		cmp	byte_266EF, 3
		jb	short loc_1CEAD
		mov	al, byte_266EF
		add	al, 0FEh ; 'þ'
		jmp	short loc_1CEAA
; ---------------------------------------------------------------------------

loc_1CE6C:				; CODE XREF: sub_1CE12+16j
					; DATA XREF: seg003:off_1CEAFo	...
		cmp	byte_266D5, 18h
		jb	short loc_1CE7A
		mov	al, byte_266EF
		add	al, 4
		jmp	short loc_1CEAA
; ---------------------------------------------------------------------------

loc_1CE7A:				; CODE XREF: sub_1CE12+5Fj
		cmp	byte_266D5, 14h
		jb	short loc_1CE88

loc_1CE81:				; CODE XREF: sub_1CE12+43j
		mov	al, byte_266EF
		add	al, 2
		jmp	short loc_1CEAA
; ---------------------------------------------------------------------------

loc_1CE88:				; CODE XREF: sub_1CE12+6Dj
		cmp	byte_266EF, 5
		jb	short loc_1CEAD
		cmp	byte_266D5, 0Ah
		ja	short loc_1CE9E
		mov	al, byte_266EF
		add	al, 0FEh ; 'þ'
		mov	byte_266EF, al

loc_1CE9E:				; CODE XREF: sub_1CE12+82j
		cmp	byte_266D5, 4
		ja	short loc_1CEAD
		mov	al, byte_266EF
		add	al, 0FCh ; 'ü'

loc_1CEAA:				; CODE XREF: sub_1CE12+58j
					; sub_1CE12+66j ...
		mov	byte_266EF, al

loc_1CEAD:				; CODE XREF: sub_1CE12+10j
					; sub_1CE12+16j ...
		pop	bp
		retn
sub_1CE12	endp

; ---------------------------------------------------------------------------
off_1CEAF	dw offset loc_1CE6C	; DATA XREF: sub_1CE12+16r
		dw offset loc_1CEAD
		dw offset loc_1CEAD
		dw offset loc_1CEAD
		dw offset loc_1CEAD
		dw offset loc_1CEAD
		dw offset loc_1CE6C
		dw offset loc_1CE4E
		dw offset loc_1CE4E
		dw offset loc_1CE2D
		dw offset loc_1CE2D
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		call	sub_1CE12
		call	sub_1CC33
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		call	sub_1CE12
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		call	sub_1CE12
		call	near ptr sub_1CCB8
		pop	bp
		retn
; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp
		call	sub_1CE12
		call	near ptr sub_1CD6E
		pop	bp
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	byte_2CFF9, 0
		jnz	short locret_1CF14
		mov	al, byte_266EF
		mov	[bp-2],	al
		mov	al, byte_266EE
		mov	[bp-1],	al
		call	sub_1D294
		mov	al, [bp-2]
		mov	byte_266EF, al
		mov	al, [bp-1]
		mov	byte_266EE, al

locret_1CF14:				; CODE XREF: seg003:9467j
		leave
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	byte_2CFF9, 0
		jnz	short locret_1CF30
		mov	al, byte_266EE
		mov	[bp-1],	al
		call	sub_1D294
		mov	al, [bp-1]
		mov	byte_266EE, al

locret_1CF30:				; CODE XREF: seg003:948Fj
		leave
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	byte_2CFF9, 0
		jnz	short locret_1CF4C
		mov	al, byte_266EE
		mov	[bp-1],	al
		call	sub_1D294
		mov	al, [bp-1]
		mov	byte_266EE, al

locret_1CF4C:				; CODE XREF: seg003:94ABj
		leave
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	byte_2CFF9, 0
		jnz	short locret_1CF68
		mov	al, byte_266EE
		mov	[bp-1],	al
		call	sub_1D3BF
		mov	al, [bp-1]
		mov	byte_266EE, al

locret_1CF68:				; CODE XREF: seg003:94C7j
		leave
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	byte_2CFF9, 0
		jnz	short locret_1CF84
		mov	al, byte_266EE
		mov	[bp-1],	al
		call	sub_1D3BF
		mov	al, [bp-1]
		mov	byte_266EE, al

locret_1CF84:				; CODE XREF: seg003:94E3j
		leave
		retn
; ---------------------------------------------------------------------------
		enter	2, 0
		cmp	byte_2CFF9, 0
		jnz	short locret_1CFA0
		mov	al, byte_266EE
		mov	[bp-1],	al
		call	sub_1D3BF
		mov	al, [bp-1]
		mov	byte_266EE, al

locret_1CFA0:				; CODE XREF: seg003:94FFj
		leave
		retn

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CFA2	proc near		; CODE XREF: seg003:092Bp seg003:09D5p ...
		push	bp
		mov	bp, sp
		mov	byte_23278, 1
		call	word_2D000
		mov	byte_23278, 0
		pop	bp
		retn
sub_1CFA2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CFB5	proc near		; CODE XREF: sub_160A5+7Ep
					; sub_160A5+111p ...
		push	bp
		mov	bp, sp
		mov	byte_23278, 1
		call	word_2D002
		mov	byte_23278, 0
		pop	bp
		retn
sub_1CFB5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1CFC8	proc near		; CODE XREF: sub_1D294+E4p
					; sub_1D3BF+88p

var_4		= byte ptr -4
var_3		= byte ptr -3
var_2		= word ptr -2
arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		mov	si, [bp+arg_0]
		mov	[bp+var_2], 0
		mov	[bp+var_4], 0
		mov	al, byte_266EE
		mov	[bp+var_3], al
		mov	al, byte_266EC
		mov	ah, 0
		cmp	ax, 2Ch	; ','
		jz	loc_1D0EB
		jg	short loc_1D027
		cmp	ax, 1Bh
		jz	loc_1D119
		jg	short loc_1D00F
		or	ax, ax
		jz	loc_1D112
		cmp	ax, 1
		jz	loc_1D15E
		cmp	ax, 1Ah
		jz	loc_1D10C
		jmp	loc_1D18D
; ---------------------------------------------------------------------------

loc_1D00F:				; CODE XREF: sub_1CFC8+2Ej
		cmp	ax, 1Ch
		jz	loc_1D12B
		cmp	ax, 1Dh
		jz	loc_1D148
		cmp	ax, 26h	; '&'
		jz	loc_1D0CA
		jmp	loc_1D18D
; ---------------------------------------------------------------------------

loc_1D027:				; CODE XREF: sub_1CFC8+25j
		cmp	ax, 30h	; '0'
		jz	loc_1D164
		jg	short loc_1D044
		cmp	ax, 2Dh	; '-'
		jz	short loc_1D055
		cmp	ax, 2Eh	; '.'
		jz	short loc_1D055
		cmp	ax, 2Fh	; '/'
		jz	loc_1D164
		jmp	loc_1D18D
; ---------------------------------------------------------------------------

loc_1D044:				; CODE XREF: sub_1CFC8+66j
		cmp	ax, 40h	; '@'
		jz	loc_1D112
		cmp	ax, 41h	; 'A'
		jz	loc_1D15E
		jmp	loc_1D18D
; ---------------------------------------------------------------------------

loc_1D055:				; CODE XREF: sub_1CFC8+6Bj
					; sub_1CFC8+70j
		test	byte_266EF, 1
		jz	short loc_1D088
		or	si, si
		jnz	short loc_1D06C
		mov	byte_2CFF6, 0
		mov	[bp+var_2], 0
		jmp	short loc_1D0B0
; ---------------------------------------------------------------------------

loc_1D06C:				; CODE XREF: sub_1CFC8+96j
		test	si, 1
		jz	short loc_1D0A8
		mov	al, byte_266F0
		add	byte_2CFF6, al

loc_1D079:				; CODE XREF: sub_1CFC8+D7j
		mov	al, byte_2CFF6
		mov	ah, 0
		mov	dx, 100h
		sub	dx, ax
		mov	[bp+var_2], dx
		jmp	short loc_1D0B0
; ---------------------------------------------------------------------------

loc_1D088:				; CODE XREF: sub_1CFC8+92j
		or	si, si
		jnz	short loc_1D09B
		mov	al, byte_266F0
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	byte_2CFF6, al
		jmp	short loc_1D0A8
; ---------------------------------------------------------------------------

loc_1D09B:				; CODE XREF: sub_1CFC8+C2j
		test	si, 1
		jnz	short loc_1D079
		mov	al, byte_266F0
		add	byte_2CFF6, al

loc_1D0A8:				; CODE XREF: sub_1CFC8+A8j
					; sub_1CFC8+D1j
		mov	al, byte_2CFF6
		mov	ah, 0
		mov	[bp+var_2], ax

loc_1D0B0:				; CODE XREF: sub_1CFC8+A2j
					; sub_1CFC8+BEj
		mov	al, byte_266EF
		mov	ah, 0
		dec	ax
		cmp	ax, si
		jg	short loc_1D0BE
		mov	[bp+var_4], 1

loc_1D0BE:				; CODE XREF: sub_1CFC8+F0j
		cmp	byte_266EC, 2Dh	; '-'
		jnz	loc_1D18D
		jmp	loc_1D1A5
; ---------------------------------------------------------------------------

loc_1D0CA:				; CODE XREF: sub_1CFC8+58j
		mov	ax, si
		shl	ax, 8
		mov	dl, byte_266EF
		mov	dh, 0
		push	dx
		cwd
		pop	bx
		idiv	bx
		mov	[bp+var_2], ax
		mov	al, byte_266EF
		mov	ah, 0
		dec	ax
		cmp	ax, si
		jg	loc_1D1A5
		jmp	short loc_1D112
; ---------------------------------------------------------------------------

loc_1D0EB:				; CODE XREF: sub_1CFC8+21j
		mov	ax, si
		shl	ax, 8
		mov	dl, byte_266EF
		mov	dh, 0
		push	dx
		cwd
		pop	bx
		idiv	bx
		mov	[bp+var_2], ax
		mov	al, byte_266EF
		mov	ah, 0
		dec	ax
		cmp	ax, si
		jg	loc_1D18D
		jmp	short loc_1D15E
; ---------------------------------------------------------------------------

loc_1D10C:				; CODE XREF: sub_1CFC8+40j
		call	sub_13D52
		mov	[bp+var_2], ax

loc_1D112:				; CODE XREF: sub_1CFC8+32j
					; sub_1CFC8+7Fj ...
		mov	[bp+var_4], 1
		jmp	loc_1D1A5
; ---------------------------------------------------------------------------

loc_1D119:				; CODE XREF: sub_1CFC8+2Aj
		call	sub_13D52
		mov	[bp+var_2], ax
		mov	al, byte_266EF
		mov	ah, 0
		dec	ax
		cmp	ax, si
		jg	short loc_1D1A5
		jmp	short loc_1D112
; ---------------------------------------------------------------------------

loc_1D12B:				; CODE XREF: sub_1CFC8+4Aj
		call	sub_13D52
		mov	[bp+var_2], ax
		push	1Fh
		call	sub_13D60
		add	al, [bp+var_3]
		mov	[bp+var_3], al
		mov	al, byte_266EF
		mov	ah, 0
		dec	ax
		cmp	ax, si
		jg	short loc_1D1A5
		jmp	short loc_1D112
; ---------------------------------------------------------------------------

loc_1D148:				; CODE XREF: sub_1CFC8+51j
		push	1Fh
		call	sub_13D60
		mov	[bp+var_2], ax
		sub	[bp+var_2], 10h
		mov	al, byte_266EF
		mov	ah, 0
		dec	ax
		cmp	ax, si
		jg	short loc_1D18D

loc_1D15E:				; CODE XREF: sub_1CFC8+39j
					; sub_1CFC8+86j ...
		mov	[bp+var_4], 1
		jmp	short loc_1D18D
; ---------------------------------------------------------------------------

loc_1D164:				; CODE XREF: sub_1CFC8+62j
					; sub_1CFC8+75j
		mov	al, byte_266F0
		mov	ah, 0
		imul	si
		add	al, [bp+var_3]
		mov	[bp+var_3], al
		mov	al, byte_266EF
		mov	ah, 0
		dec	ax
		cmp	ax, si
		jle	short loc_1D182
		cmp	byte_266EE, 0A0h ; ' '
		jb	short loc_1D186

loc_1D182:				; CODE XREF: sub_1CFC8+1B1j
		mov	[bp+var_4], 1

loc_1D186:				; CODE XREF: sub_1CFC8+1B8j
		cmp	byte_266EC, 2Fh	; '/'
		jz	short loc_1D1A5

loc_1D18D:				; CODE XREF: sub_1CFC8+44j
					; sub_1CFC8+5Cj ...
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266E4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266E4
		push	ax
		call	sub_1DA8
		add	[bp+var_2], ax

loc_1D1A5:				; CODE XREF: sub_1CFC8+FFj
					; sub_1CFC8+11Dj ...
		push	53A8h
		mov	al, byte ptr [bp+var_2]
		add	al, byte_266ED
		push	ax
		mov	al, [bp+var_3]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		mov	al, byte ptr [bp+var_2]
		add	al, byte_266ED
		mov	byte ptr word_2D008, al
		mov	al, [bp+var_4]
		mov	ah, 0
		pop	si
		leave
		retn	2
sub_1CFC8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D1CD	proc near		; CODE XREF: sub_1D230+5Dp
		push	bp
		mov	bp, sp
		mov	al, byte_266EE
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	byte_266EE, al
		mov	ah, 0
		mov	cx, ax
		mov	al, byte_266D5
		mov	ah, 0
		imul	cx
		mov	cx, ax
		mov	bx, 10h
		mov	ax, cx
		cwd
		idiv	bx
		mov	cx, ax
		mov	al, byte_266EE
		add	al, cl
		mov	byte_266EE, al
		cmp	byte_266EE, 80h	; '€'
		jbe	short loc_1D20A
		mov	byte_266EE, 80h	; '€'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1D20A:				; CODE XREF: sub_1D1CD+34j
		cmp	byte_266EE, 8
		jnb	short loc_1D216
		mov	byte_266EE, 8

loc_1D216:				; CODE XREF: sub_1D1CD+42j
		pop	bp
		retn
sub_1D1CD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D218	proc near		; CODE XREF: sub_1D294+F5p
					; sub_1D3BF+99p

arg_0		= byte ptr  4

		push	bp
		mov	bp, sp
		mov	al, [bp+arg_0]
		mov	ah, 0
		add	ax, 3
		and	ax, 7Fh
		mov	bx, 8
		cwd
		idiv	bx
		pop	bp
		retn	2
sub_1D218	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D230	proc near		; CODE XREF: sub_1D294:loc_1D2D5p
					; sub_1D3BF+8p
		push	bp
		mov	bp, sp
		cmp	byte_2CFFA, 0
		jbe	short loc_1D241
		cmp	byte_2CFFA, 11h
		jbe	short loc_1D282

loc_1D241:				; CODE XREF: sub_1D230+8j
		cmp	word ptr dword_266E4, 0FF80h
		jle	short loc_1D282
		cmp	word ptr dword_266E4, 1880h
		jge	short loc_1D282
		cmp	word ptr dword_266E4+2,	0FF80h
		jle	short loc_1D282
		cmp	word ptr dword_266E4+2,	1780h
		jge	short loc_1D282
		mov	ax, word ptr dword_266E4
		sub	ax, word ptr dword_2598E
		add	ax, 40h	; '@'
		cmp	ax, 80h	; '€'
		ja	short loc_1D286
		mov	ax, word ptr dword_266E4+2
		sub	ax, word ptr dword_2598E+2
		add	ax, 40h	; '@'
		cmp	ax, 80h	; '€'
		ja	short loc_1D286
		mov	byte_259A9, 1

loc_1D282:				; CODE XREF: sub_1D230+Fj
					; sub_1D230+16j ...
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1D286:				; CODE XREF: sub_1D230+3Cj
					; sub_1D230+4Bj
		cmp	byte_23278, 0
		jnz	short loc_1D290
		call	sub_1D1CD

loc_1D290:				; CODE XREF: sub_1D230+5Bj
		mov	al, 0
		pop	bp
		retn
sub_1D230	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D294	proc near		; CODE XREF: seg003:9475p seg003:9497p ...

var_5		= byte ptr -5
var_4		= byte ptr -4
var_3		= byte ptr -3
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 6
		push	si
		push	di
		cmp	byte_266E2, 3
		jnz	short loc_1D2D5
		mov	eax, dword_266E4
		mov	dword_2A8C6, eax
		mov	dword_2A8CA, 0
		mov	word_2A8CE, 400h
		mov	byte_2A8D3, 2
		mov	byte_2A8D2, 9
		mov	word_2A8D0, 8
		mov	byte_266E2, 1
		call	sub_13AB7
		jmp	loc_1D3BB
; ---------------------------------------------------------------------------

loc_1D2D5:				; CODE XREF: sub_1D294+Dj
		call	sub_1D230
		or	al, al
		jnz	loc_1D3BB
		mov	[bp+var_5], 0
		mov	al, byte_266E2
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_1D2F8
		cmp	ax, 4
		jz	short loc_1D308
		cmp	ax, 5
		jz	short loc_1D302
		jmp	short loc_1D30C
; ---------------------------------------------------------------------------

loc_1D2F8:				; CODE XREF: sub_1D294+56j
		mov	si, 7268h
		mov	[bp+var_2], 0F0h ; 'ð'
		jmp	short loc_1D314
; ---------------------------------------------------------------------------

loc_1D302:				; CODE XREF: sub_1D294+60j
		mov	[bp+var_5], 3
		jmp	short loc_1D30C
; ---------------------------------------------------------------------------

loc_1D308:				; CODE XREF: sub_1D294+5Bj
		mov	[bp+var_5], 4

loc_1D30C:				; CODE XREF: sub_1D294+62j
					; sub_1D294+72j
		mov	si, 86B8h
		mov	[bp+var_2], 0C8h ; 'È'

loc_1D314:				; CODE XREF: sub_1D294+6Cj
		mov	[bp+var_3], 2
		cmp	byte_266EE, 40h	; '@'
		jb	short loc_1D326
		cmp	byte_2CFFA, 0
		jz	short loc_1D338

loc_1D326:				; CODE XREF: sub_1D294+89j
		cmp	byte_266EC, 2Fh	; '/'
		jz	short loc_1D338
		cmp	byte_266EC, 30h	; '0'
		jz	short loc_1D338
		mov	[bp+var_3], 0

loc_1D338:				; CODE XREF: sub_1D294+90j
					; sub_1D294+97j ...
		xor	di, di
		jmp	short loc_1D3B5
; ---------------------------------------------------------------------------

loc_1D33C:				; CODE XREF: sub_1D294+125j
		cmp	byte ptr [si], 0
		jnz	short loc_1D3AF
		mov	byte ptr [si], 1
		mov	al, [bp+var_3]
		mov	[si+13h], al
		mov	byte ptr [si+16h], 20h ; ' '
		mov	al, 48h	; 'H'
		sub	al, byte_266EE
		mov	[si+17h], al
		mov	byte ptr [si+1], 0
		mov	eax, dword_266E4
		mov	[si+2],	eax
		mov	al, byte_266EC
		mov	[si+0Eh], al
		mov	al, byte_266E3
		mov	ah, 0
		mov	[si+18h], ax
		mov	al, [bp+var_5]
		mov	[si+12h], al
		push	di
		call	sub_1CFC8
		mov	[bp+var_4], al
		cmp	byte_266E3, 4Ch	; 'L'
		jb	short loc_1D391
		push	word_2D008
		call	sub_1D218
		mov	ah, 0

loc_1D38E:				; CODE XREF: sub_1C2E5:loc_1C46Fj
					; DATA XREF: sub_C696+1Ao
		add	[si+18h], ax

loc_1D391:				; CODE XREF: sub_1D294+EFj
		mov	eax, dword_266E8

loc_1D395:				; CODE XREF: sub_1C2E5:loc_1C46Fj
					; DATA XREF: sub_C696+1Ao
		mov	[si+0Ah], eax
		mov	al, byte ptr word_2D008
		mov	[si+11h], al
		mov	al, byte_266EE
		mov	[si+15h], al
		mov	[si+10h], al
		cmp	[bp+var_4], 0
		jnz	short loc_1D3BB
		inc	di

loc_1D3AF:				; CODE XREF: sub_1D294+ABj
		dec	[bp+var_2]
		sub	si, 1Ah

loc_1D3B5:				; CODE XREF: sub_1D294+A6j
		cmp	[bp+var_2], 0
		jg	short loc_1D33C

loc_1D3BB:				; CODE XREF: sub_1D294+3Ej
					; sub_1D294+46j ...
		pop	di
		pop	si
		leave
		retn
sub_1D294	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D3BF	proc near		; CODE XREF: seg003:94CFp seg003:94EBp ...

var_4		= byte ptr -4
var_3		= byte ptr -3
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		call	sub_1D230
		or	al, al
		jnz	loc_1D48A
		mov	[bp+var_4], 0
		mov	al, byte_266E2
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_1D3EA
		cmp	ax, 4
		jz	short loc_1D3FA
		cmp	ax, 5
		jz	short loc_1D3F4
		jmp	short loc_1D3FE
; ---------------------------------------------------------------------------

loc_1D3EA:				; CODE XREF: sub_1D3BF+1Dj
		mov	si, 7268h
		mov	[bp+var_2], 0F0h ; 'ð'
		jmp	short loc_1D406
; ---------------------------------------------------------------------------

loc_1D3F4:				; CODE XREF: sub_1D3BF+27j
		mov	[bp+var_4], 3
		jmp	short loc_1D3FE
; ---------------------------------------------------------------------------

loc_1D3FA:				; CODE XREF: sub_1D3BF+22j
		mov	[bp+var_4], 4

loc_1D3FE:				; CODE XREF: sub_1D3BF+29j
					; sub_1D3BF+39j
		mov	si, 86B8h
		mov	[bp+var_2], 0C8h ; 'È'

loc_1D406:				; CODE XREF: sub_1D3BF+33j
		xor	di, di
		jmp	short loc_1D484
; ---------------------------------------------------------------------------

loc_1D40A:				; CODE XREF: sub_1D3BF+C9j
		cmp	byte ptr [si], 0
		jnz	short loc_1D47E
		mov	byte ptr [si], 1
		mov	byte ptr [si+13h], 1
		mov	al, byte_266F2
		mov	[si+14h], al
		mov	byte ptr [si+16h], 0
		mov	al, byte_2CFF8
		mov	[si+17h], al
		mov	byte ptr [si+1], 0
		mov	eax, dword_266E4
		mov	[si+2],	eax
		mov	al, byte_266EC
		mov	[si+0Eh], al
		mov	al, byte_266E3
		mov	ah, 0
		mov	[si+18h], ax
		mov	al, [bp+var_4]
		mov	[si+12h], al
		push	di
		call	sub_1CFC8
		mov	[bp+var_3], al
		cmp	byte_266E3, 4Ch	; 'L'
		jb	short loc_1D460
		push	word_2D008
		call	sub_1D218
		mov	ah, 0
		add	[si+18h], ax

loc_1D460:				; CODE XREF: sub_1D3BF+93j
		mov	eax, dword_266E8
		mov	[si+0Ah], eax
		mov	al, byte ptr word_2D008
		mov	[si+11h], al
		mov	al, byte_266EE
		mov	[si+15h], al
		mov	[si+10h], al
		cmp	[bp+var_3], 0
		jnz	short loc_1D48A
		inc	di

loc_1D47E:				; CODE XREF: sub_1D3BF+4Ej
		dec	[bp+var_2]
		sub	si, 1Ah

loc_1D484:				; CODE XREF: sub_1D3BF+49j
		cmp	[bp+var_2], 0
		jg	short loc_1D40A

loc_1D48A:				; CODE XREF: sub_1D3BF+Dj
					; sub_1D3BF+BCj
		pop	di
		pop	si
		leave
		retn
sub_1D3BF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D48E	proc near		; CODE XREF: sub_1D6C1+BEp
					; sub_1D6C1+D7p ...

var_12		= dword	ptr -12h
var_E		= dword	ptr -0Eh
var_A		= byte ptr -0Ah
var_4		= byte ptr -4
var_3		= byte ptr -3
var_2		= byte ptr -2
arg_0		= dword	ptr  4
arg_4		= word ptr  8

		enter	12h, 0
		push	si
		push	di
		mov	[bp+var_E], 0F4240h
		xor	si, si
		xor	di, di
		jmp	short loc_1D4EA
; ---------------------------------------------------------------------------

loc_1D4A2:				; CODE XREF: sub_1D48E+61j
		mov	eax, [bp+arg_0]
		xor	edx, edx
		div	[bp+var_E]
		mov	[bp+var_12], eax
		mov	eax, [bp+arg_0]
		xor	edx, edx
		div	[bp+var_E]
		mov	[bp+arg_0], edx
		or	di, word ptr [bp+var_12]
		or	di, di
		jz	short loc_1D4D1
		mov	al, byte ptr [bp+var_12]
		add	al, 0A0h ; ' '
		mov	[bp+si+var_A], al
		jmp	short loc_1D4D5
; ---------------------------------------------------------------------------

loc_1D4D1:				; CODE XREF: sub_1D48E+37j
		mov	[bp+si+var_A], 2

loc_1D4D5:				; CODE XREF: sub_1D48E+41j
		mov	ebx, 0Ah
		mov	eax, [bp+var_E]
		xor	edx, edx
		div	ebx
		mov	[bp+var_E], eax
		inc	si

loc_1D4EA:				; CODE XREF: sub_1D48E+12j
		cmp	[bp+var_E], 1
		ja	short loc_1D4A2
		mov	al, byte ptr [bp+arg_0]
		add	al, 0A0h ; ' '
		mov	[bp+var_4], al
		mov	[bp+var_3], 0A0h ; ' '
		mov	[bp+var_2], 0
		push	22h ; '"'
		push	[bp+arg_4]
		push	ss
		lea	ax, [bp+var_A]
		push	ax
		push	0E1h ; 'á'
		call	sub_1B50
		pop	di
		pop	si
		leave
		retn	6
sub_1D48E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D519	proc far		; CODE XREF: sub_F064+FP sub_F07A+10P	...

var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= byte ptr -6
var_2		= byte ptr -2
var_1		= byte ptr -1
arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah

		enter	0Ah, 0
		push	si
		push	di
		mov	si, 2710h
		xor	di, di
		mov	[bp+var_A], 0
		jmp	short loc_1D565
; ---------------------------------------------------------------------------

loc_1D52B:				; CODE XREF: sub_1D519+4Fj
		mov	ax, [bp+arg_0]
		xor	dx, dx
		div	si
		mov	[bp+var_8], ax
		mov	ax, [bp+arg_0]
		xor	dx, dx
		div	si
		mov	[bp+arg_0], dx
		mov	ax, [bp+var_8]
		or	[bp+var_A], ax
		cmp	[bp+var_A], 0
		jz	short loc_1D555
		mov	al, byte ptr [bp+var_8]
		add	al, 0A0h ; ' '
		mov	[bp+di+var_6], al
		jmp	short loc_1D559
; ---------------------------------------------------------------------------

loc_1D555:				; CODE XREF: sub_1D519+30j
		mov	[bp+di+var_6], 2

loc_1D559:				; CODE XREF: sub_1D519+3Aj
		mov	bx, 0Ah
		mov	ax, si
		xor	dx, dx
		div	bx
		mov	si, ax
		inc	di

loc_1D565:				; CODE XREF: sub_1D519+10j
		cmp	si, 1
		ja	short loc_1D52B
		mov	al, byte ptr [bp+arg_0]
		add	al, 0A0h ; ' '
		mov	[bp+var_2], al
		mov	[bp+var_1], 0
		push	[bp+arg_4]
		push	[bp+arg_2]
		push	ss
		lea	ax, [bp+var_6]
		push	ax
		push	0E1h ; 'á'
		call	sub_1B50
		pop	di
		pop	si
		leave
		retf	6
sub_1D519	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D58F	proc near		; CODE XREF: sub_1D5E9+50p
					; sub_1D5E9+89p ...

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
		jge	short loc_1D5C8
		mov	ax, 41h	; 'A'
		jmp	short loc_1D5CB
; ---------------------------------------------------------------------------

loc_1D5C8:				; CODE XREF: sub_1D58F+32j
		mov	ax, 81h	; ''

loc_1D5CB:				; CODE XREF: sub_1D58F+37j
		mov	[bp+var_2], ax
		push	6
		push	[bp+arg_8]
		mov	bx, [bp+arg_6]
		shl	bx, 2
		push	large dword ptr	[bx+1F3Ah]
		push	ax
		call	sub_22F6
		pop	si
		leave
		retn	0Ah
sub_1D58F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D5E9	proc near		; CODE XREF: sub_1D6C1+130p
					; sub_1D896+16Dp

arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		cmp	byte_2671F, 0
		jnz	short loc_1D5FE
		push	large 140000h
		push	0
		jmp	loc_1D6AE
; ---------------------------------------------------------------------------

loc_1D5FE:				; CODE XREF: sub_1D5E9+8j
		les	bx, dword_2CDC6
		mov	al, es:[bx+0Ch]
		mov	ah, 0
		cmp	ax, 4
		jz	short loc_1D62D
		cmp	ax, 5
		jz	short loc_1D623
		cmp	ax, 6
		jz	short loc_1D619
		jmp	short loc_1D63C
; ---------------------------------------------------------------------------

loc_1D619:				; CODE XREF: sub_1D5E9+2Cj
		push	large 120001h
		push	3
		jmp	short loc_1D635
; ---------------------------------------------------------------------------

loc_1D623:				; CODE XREF: sub_1D5E9+27j
		push	large 120002h
		push	5
		jmp	short loc_1D635
; ---------------------------------------------------------------------------

loc_1D62D:				; CODE XREF: sub_1D5E9+22j
		push	large 120003h
		push	7

loc_1D635:				; CODE XREF: sub_1D5E9+38j
					; sub_1D5E9+42j
		push	large [bp+arg_0]
		call	sub_1D58F

loc_1D63C:				; CODE XREF: sub_1D5E9+2Ej
		mov	al, byte_25689
		mov	ah, 0
		cmp	ax, 1
		jz	short loc_1D652
		cmp	ax, 2
		jz	short loc_1D65C
		cmp	ax, 3
		jz	short loc_1D666
		jmp	short loc_1D675
; ---------------------------------------------------------------------------

loc_1D652:				; CODE XREF: sub_1D5E9+5Bj
		push	large 130004h
		push	8
		jmp	short loc_1D66E
; ---------------------------------------------------------------------------

loc_1D65C:				; CODE XREF: sub_1D5E9+60j
		push	large 130005h
		push	6
		jmp	short loc_1D66E
; ---------------------------------------------------------------------------

loc_1D666:				; CODE XREF: sub_1D5E9+65j
		push	large 130006h
		push	4

loc_1D66E:				; CODE XREF: sub_1D5E9+71j
					; sub_1D5E9+7Bj
		push	large [bp+arg_0]
		call	sub_1D58F

loc_1D675:				; CODE XREF: sub_1D5E9+67j
		mov	al, byte_25688
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 3
		ja	short loc_1D6B5
		add	bx, bx
		jmp	cs:off_1D6B9[bx]

loc_1D688:				; DATA XREF: seg003:off_1D6B9o
		push	large 140007h
		push	5
		jmp	short loc_1D6AE
; ---------------------------------------------------------------------------

loc_1D692:				; CODE XREF: sub_1D5E9+9Aj
					; DATA XREF: seg003:9C2Bo
		push	large 140008h
		push	0Ah
		jmp	short loc_1D6AE
; ---------------------------------------------------------------------------

loc_1D69C:				; CODE XREF: sub_1D5E9+9Aj
					; DATA XREF: seg003:9C2Do
		push	large 140009h
		push	0Ch
		jmp	short loc_1D6AE
; ---------------------------------------------------------------------------

loc_1D6A6:				; CODE XREF: sub_1D5E9+9Aj
					; DATA XREF: seg003:9C2Fo
		push	large 14000Ah
		push	0Eh

loc_1D6AE:				; CODE XREF: sub_1D5E9+12j
					; sub_1D5E9+A7j ...
		push	large [bp+arg_0]
		call	sub_1D58F

loc_1D6B5:				; CODE XREF: sub_1D5E9+96j
		pop	bp
		retn	4
sub_1D5E9	endp

; ---------------------------------------------------------------------------
off_1D6B9	dw offset loc_1D688	; DATA XREF: sub_1D5E9+9Ar
		dw offset loc_1D692
		dw offset loc_1D69C
		dw offset loc_1D6A6

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D6C1	proc near		; CODE XREF: sub_1E743+166p

var_8		= dword	ptr -8
var_4		= dword	ptr -4

		enter	8, 0
		push	si
		mov	word_216E4, 3Ch	; '<'
		call	far ptr	loc_1F04
		push	large 140004h
		push	ds
		push	offset unk_232A6
		push	0E1h ; 'á'
		call	sub_1B50
		push	large 60007h
		push	ds
		push	offset aVrvsvVfvdb@vav ; "‚r‚s‚`‚f‚d@‚a‚‚Ž‚•‚“"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 60009h
		push	ds
		push	offset aVovnvvvdvqb@bB ; "‚o‚n‚v‚d‚q@~@@‚T‚O"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 6000Bh
		push	ds
		push	offset aVcvqvdvVlb@vav ; "‚c‚q‚d‚`‚l@‚a‚‚Ž‚•‚“"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 6000Dh
		push	ds
		push	offset aGjgxgkterfb@bB ; "ƒJƒXƒŠ’e”@~@@‚T‚O"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 60010h
		push	ds
		push	offset aVovnvhvmvsb@va ; "‚o‚n‚h‚m‚s@‚a‚‚Ž‚•‚“@@@@@@~"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 60015h
		push	ds
		push	offset aB@b@b@vsvnvsvV ; "@@@‚s‚n‚s‚`‚k"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 60016h
		push	ds
		push	offset aB@b@b@b@b@vavp ; "@@@@@‚a‚‚‚‚@‚d‚˜‚”‚…‚Ž‚„II"
		push	0C3h ; 'Ã'
		call	sub_22F6
		les	bx, dword_2CDC6
		mov	al, es:[bx+11h]
		mov	ah, 0
		imul	ax, 64h
		add	ax, 64h	; 'd'
		mov	si, ax
		movzx	eax, si
		mov	[bp+var_4], eax
		push	7
		push	eax
		call	sub_1D48E
		mov	al, byte_259A4
		mov	ah, 0
		imul	ax, 5
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	9
		push	eax
		call	sub_1D48E
		mov	si, word_2D00C
		movzx	eax, si
		add	[bp+var_4], eax
		push	0Bh
		push	eax
		call	sub_1D48E
		mov	ax, word_2CFFC
		imul	ax, 5
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	0Dh
		push	eax
		call	sub_1D48E
		mov	al, byte_259AB
		mov	ah, 0
		mov	si, ax
		movzx	eax, si
		imul	eax, [bp+var_4]
		mov	[bp+var_4], eax
		push	large 280010h
		push	si
		push	cs
		call	near ptr sub_1D519
		mov	eax, [bp+var_4]
		mov	[bp+var_8], eax
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_1D5E9
		push	15h
		push	large [bp+var_4]
		call	sub_1D48E
		mov	eax, [bp+var_4]
		add	dword_2569A, eax
		cmp	[bp+var_8], 124F80h
		jb	short loc_1D814
		push	4
		jmp	short loc_1D82E
; ---------------------------------------------------------------------------

loc_1D814:				; CODE XREF: sub_1D6C1+14Dj
		cmp	[bp+var_8], 0C3500h
		jb	short loc_1D822
		push	2
		jmp	short loc_1D82E
; ---------------------------------------------------------------------------

loc_1D822:				; CODE XREF: sub_1D6C1+15Bj
		cmp	[bp+var_8], 7A120h
		jb	short loc_1D835
		push	1

loc_1D82E:				; CODE XREF: sub_1D6C1+151j
					; sub_1D6C1+15Fj
		call	sub_C364
		jmp	short loc_1D854
; ---------------------------------------------------------------------------

loc_1D835:				; CODE XREF: sub_1D6C1+169j
		cmp	[bp+var_8], 186A0h
		ja	short loc_1D843
		push	2
		jmp	short loc_1D84F
; ---------------------------------------------------------------------------

loc_1D843:				; CODE XREF: sub_1D6C1+17Cj
		cmp	[bp+var_8], 30D40h
		ja	short loc_1D854
		push	1

loc_1D84F:				; CODE XREF: sub_1D6C1+180j
		call	sub_C37E

loc_1D854:				; CODE XREF: sub_1D6C1+172j
					; sub_1D6C1+18Aj
		les	bx, dword_2CDC6
		inc	byte ptr es:[bx+0Dh]
		call	sub_EFA1
		les	bx, dword_2CDC6
		mov	al, es:[bx+31h]
		cmp	al, byte_266D4
		ja	short loc_1D876
		push	2
		call	sub_C364

loc_1D876:				; CODE XREF: sub_1D6C1+1ACj
		les	bx, dword_2CDC6
		mov	al, es:[bx+32h]
		mov	ah, 0
		mov	dl, byte_266D4
		mov	dh, 0
		add	dx, dx
		cmp	ax, dx
		jg	short loc_1D893
		push	2
		call	sub_C364

loc_1D893:				; CODE XREF: sub_1D6C1+1C9j
		pop	si
		leave
		retn
sub_1D6C1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1D896	proc near		; CODE XREF: sub_1E743:loc_1E89Bp
					; sub_1E743:loc_1E8AEp

var_4		= dword	ptr -4

		enter	4, 0
		push	si
		mov	word_216E4, 3Ch	; '<'
		call	far ptr	loc_1F04
		mov	byte_22DA6, 0Ah
		push	large 130004h
		push	ds
		push	offset a_Abcd	; "\\]^_`abcd"
		push	0E1h ; 'á'
		call	sub_1B50
		push	large 60006h
		push	ds
		push	offset aVVkvkb@vbvmvev ; "‚`‚k‚k@‚b‚Œ‚…‚‚’@@"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 60008h
		push	ds
		push	offset aVovnvvvdvqb@_0 ; "‚o‚n‚v‚d‚q@~@@‚T‚O"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 6000Ah
		push	ds
		push	offset aVcvqvdvVlb@v_0 ; "‚c‚q‚d‚`‚l@‚a‚‚Ž‚•‚“"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 6000Ch
		push	ds
		push	offset aGjgxgkterfb@_0 ; "ƒJƒXƒŠ’e”@~@@‚T‚O"
		push	0E1h ; 'á'
		call	sub_22F6
		cmp	byte_25688, 4
		jz	short loc_1D918
		push	large 6000Eh
		push	ds
		push	offset aOcvsrlrfb@bVpv ; "Žc‚èl”@~‚P‚O‚O‚O‚O"
		jmp	short loc_1D922
; ---------------------------------------------------------------------------

loc_1D918:				; CODE XREF: sub_1D896+74j
		push	large 6000Eh
		push	ds
		push	offset aOcvsrlrfb@bVrv ; "Žc‚èl”@~‚R‚O‚O‚O‚O"

loc_1D922:				; CODE XREF: sub_1D896+80j
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 60011h
		push	ds
		push	offset aVovnvhvmvsb@_0 ; "‚o‚n‚h‚m‚s@‚a‚‚Ž‚•‚“@@@@@@~"
		push	0E1h ; 'á'
		call	sub_22F6
		push	large 60015h
		push	ds
		push	offset aB@b@b@vsvnvs_0 ; "@@@‚s‚n‚s‚`‚k"
		push	0E1h ; 'á'
		call	sub_22F6
		mov	si, 3E8h
		movzx	eax, si
		mov	[bp+var_4], eax
		push	6
		push	eax
		call	sub_1D48E
		mov	al, byte_259A4
		mov	ah, 0
		imul	ax, 5
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	8
		push	eax
		call	sub_1D48E
		mov	si, word_2D00C
		movzx	eax, si
		add	[bp+var_4], eax
		push	0Ah
		push	eax
		call	sub_1D48E
		mov	ax, word_2CFFC
		imul	ax, 5
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	0Ch
		push	eax
		call	sub_1D48E
		cmp	byte_25688, 4
		jz	short loc_1D9BD
		les	bx, dword_2CDC6
		mov	al, es:[bx+0Bh]
		mov	ah, 0
		imul	ax, 3E8h
		add	ax, 0FC18h
		jmp	short loc_1D9CE
; ---------------------------------------------------------------------------

loc_1D9BD:				; CODE XREF: sub_1D896+112j
		les	bx, dword_2CDC6
		mov	al, es:[bx+0Bh]
		mov	ah, 0
		imul	ax, 0BB8h
		add	ax, 0F448h

loc_1D9CE:				; CODE XREF: sub_1D896+125j
		mov	si, ax
		movzx	eax, si
		add	[bp+var_4], eax
		push	0Eh
		push	eax
		call	sub_1D48E
		mov	al, byte_259AB
		mov	ah, 0
		mov	si, ax
		movzx	eax, si
		imul	eax, [bp+var_4]
		mov	[bp+var_4], eax
		push	large 280011h
		push	si
		push	cs
		call	near ptr sub_1D519
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_1D5E9
		push	15h
		push	large [bp+var_4]
		call	sub_1D48E
		mov	eax, [bp+var_4]
		add	dword_2569A, eax
		pop	si
		leave
		retn
sub_1D896	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DA1B	proc far		; CODE XREF: sub_B1D0+A8P
		push	bp
		mov	bp, sp
		call	sub_2172
		and	al, 0Fh
		mov	byte_2D00E, al
		call	sub_13F16
		mov	byte_236E0, 0
		mov	word_2D00C, 0
		pop	bp
		retf
sub_1DA1B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DA38	proc near		; CODE XREF: sub_1486E:loc_148F2p
					; sub_14CFD+1DAp ...

arg_0		= byte ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	[bp+arg_0], 0FFh
		jnz	short loc_1DA6F
		inc	byte_2D00E
		mov	al, byte_2D00E
		mov	ah, 0
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DAC8
		mov	al, byte_2D00E
		mov	ah, 0
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		mov	bx, dx
		mov	al, [bx+22E0h]
		mov	[bp+arg_0], al

loc_1DA6F:				; CODE XREF: sub_1DA38+9j
		mov	si, 0AF34h
		xor	di, di
		jmp	short loc_1DAC3
; ---------------------------------------------------------------------------

loc_1DA76:				; CODE XREF: sub_1DA38+8Ej
		cmp	byte ptr [si], 0
		jnz	short loc_1DABF
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
		mov	ax, [bx+2322h]
		mov	[si+10h], ax
		push	[bp+arg_4]
		push	[bp+arg_2]
		call	sub_13F30
		mov	word ptr [si+12h], 0
		inc	word_236D8
		jmp	short loc_1DAC8
; ---------------------------------------------------------------------------

loc_1DABF:				; CODE XREF: sub_1DA38+41j
		inc	di
		add	si, 14h

loc_1DAC3:				; CODE XREF: sub_1DA38+3Cj
		cmp	di, 20h	; ' '
		jl	short loc_1DA76

loc_1DAC8:				; CODE XREF: sub_1DA38+1Cj
					; sub_1DA38+85j
		pop	di
		pop	si
		pop	bp
		retn	6
sub_1DA38	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DACE	proc far		; CODE XREF: sub_10988+32P

var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	0Ah, 0
		push	si
		push	di
		push	5
		call	sub_13D76
		mov	[bp+var_6], ax

loc_1DADC:				; CODE XREF: sub_1DACE+19j
		push	5
		call	sub_13D76
		mov	[bp+var_A], ax
		cmp	ax, [bp+var_6]
		jz	short loc_1DADC
		cmp	word ptr dword_2598E, 800h
		jge	short loc_1DAF8
		mov	[bp+var_4], 0
		jmp	short loc_1DB0C
; ---------------------------------------------------------------------------

loc_1DAF8:				; CODE XREF: sub_1DACE+21j
		cmp	word ptr dword_2598E, 1000h
		jg	short loc_1DB07
		mov	[bp+var_4], 1
		jmp	short loc_1DB0C
; ---------------------------------------------------------------------------

loc_1DB07:				; CODE XREF: sub_1DACE+30j
		mov	[bp+var_4], 2

loc_1DB0C:				; CODE XREF: sub_1DACE+28j
					; sub_1DACE+37j
		xor	di, di
		mov	si, 0AF34h
		mov	[bp+var_2], 0
		jmp	loc_1DBA2
; ---------------------------------------------------------------------------

loc_1DB19:				; CODE XREF: sub_1DACE+D8j
		cmp	byte ptr [si], 0
		jnz	short loc_1DB9C
		mov	byte ptr [si], 1
		mov	byte ptr [si+0Fh], 0
		mov	ax, word ptr dword_2598E
		mov	[si+2],	ax
		mov	ax, word ptr dword_2598E+2
		mov	[si+4],	ax
		mov	bx, [bp+var_4]
		imul	bx, 14h
		mov	ax, di
		add	ax, ax
		add	bx, ax
		mov	ax, [bx+23A2h]
		mov	[si+0Ch], ax
		mov	bx, [bp+var_4]
		imul	bx, 14h
		mov	ax, di
		add	ax, ax
		add	bx, ax
		mov	ax, [bx+23ACh]
		mov	[si+0Ah], ax
		mov	word ptr [si+12h], 0
		cmp	[bp+var_6], di
		jz	short loc_1DB6B
		push	1
		call	sub_13D60
		mov	[bp+var_8], ax
		jmp	short loc_1DB70
; ---------------------------------------------------------------------------

loc_1DB6B:				; CODE XREF: sub_1DACE+91j
		mov	[bp+var_8], 3

loc_1DB70:				; CODE XREF: sub_1DACE+9Bj
		les	bx, dword_2CDC6
		cmp	byte ptr es:[bx+0Bh], 1
		jnz	short loc_1DB80
		mov	[bp+var_8], 6

loc_1DB80:				; CODE XREF: sub_1DACE+ABj
		mov	al, byte ptr [bp+var_8]
		mov	[si+0Eh], al
		mov	bx, [bp+var_8]
		add	bx, bx
		mov	ax, [bx+2322h]
		mov	[si+10h], ax
		inc	di
		inc	word_236D8
		cmp	di, 5
		jge	short loc_1DBAA

loc_1DB9C:				; CODE XREF: sub_1DACE+4Ej
		inc	[bp+var_2]
		add	si, 14h

loc_1DBA2:				; CODE XREF: sub_1DACE+48j
		cmp	[bp+var_2], 20h	; ' '
		jl	loc_1DB19

loc_1DBAA:				; CODE XREF: sub_1DACE+CCj
		pop	di
		pop	si
		leave
		retf
sub_1DACE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DBAE	proc near		; CODE XREF: sub_1DE5D+DBp

var_1		= byte ptr -1
arg_0		= word ptr  4

		enter	2, 0
		push	si
		push	di
		mov	di, [bp+arg_0]
		mov	[bp+var_1], 0
		mov	al, [di+0Eh]
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 6
		ja	loc_1DD93
		add	bx, bx
		jmp	cs:off_1DDE9[bx]

loc_1DBD0:				; DATA XREF: seg003:off_1DDE9o
		cmp	byte_259A4, 80h	; '€'
		jnb	short loc_1DC04
		cmp	byte_259A4, 7Fh	; ''
		jnz	short loc_1DBF5
		mov	byte_259DB, 3
		mov	word_259DE, 67E8h
		cmp	byte_2CFFA, 14h
		jnb	short loc_1DBF5
		mov	byte_2CFFA, 14h

loc_1DBF5:				; CODE XREF: sub_1DBAE+2Ej
					; sub_1DBAE+40j
		inc	byte_259A4
		call	sub_11DE6
		mov	si, 1
		jmp	loc_1DD93
; ---------------------------------------------------------------------------

loc_1DC04:				; CODE XREF: sub_1DBAE+27j
		inc	word_236D6
		cmp	word_236D6, 2Ah	; '*'
		jb	short loc_1DC19
		mov	word_236D6, 2Ah	; '*'
		mov	[bp+var_1], 1

loc_1DC19:				; CODE XREF: sub_1DBAE+5Fj
		mov	bx, word_236D6
		add	bx, bx
		mov	si, [bx+2330h]
		cmp	byte_21CC8, 0
		jz	loc_1DD93
		inc	byte_23660
		jmp	loc_1DD93
; ---------------------------------------------------------------------------

loc_1DC33:				; CODE XREF: sub_1DBAE+1Dj
					; DATA XREF: seg003:A35Bo
		cmp	word ptr [di+4], 340h
		jg	short loc_1DC58
		mov	si, 1400h
		mov	al, byte_23660
		add	al, 4
		mov	byte_23660, al
		inc	word_236DE
		mov	[bp+var_1], 1
		cmp	byte_21CC8, 0
		jz	short loc_1DC7B
		add	al, 4
		jmp	short loc_1DC78
; ---------------------------------------------------------------------------

loc_1DC58:				; CODE XREF: sub_1DBAE+8Aj
		mov	ax, [di+4]
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	dx, 0CE4h
		sub	dx, ax
		mov	si, dx
		mov	al, byte_23660
		add	al, 2
		mov	byte_23660, al
		cmp	byte_21CC8, 0
		jz	short loc_1DC7B
		add	al, 2

loc_1DC78:				; CODE XREF: sub_1DBAE+A8j
		mov	byte_23660, al

loc_1DC7B:				; CODE XREF: sub_1DBAE+A4j
					; sub_1DBAE+C6j
		inc	word_236DC
		add	si, word_2D00C
		inc	byte_259AB
		call	sub_F064
		jmp	loc_1DD93
; ---------------------------------------------------------------------------

loc_1DC8F:				; CODE XREF: sub_1DBAE+1Dj
					; DATA XREF: seg003:A35Do
		cmp	byte_259B6, 6
		ja	short loc_1DC9A
		inc	byte_259B6

loc_1DC9A:				; CODE XREF: sub_1DBAE+E6j
		mov	al, byte_259B6
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+2386h]
		mov	word_2D00C, ax
		mov	si, word_2D00C
		call	sub_F07A
		mov	al, byte_23660
		add	al, 2
		mov	byte_23660, al
		cmp	byte_21CC8, 0
		jz	loc_1DD93
		add	al, 2
		mov	byte_23660, al
		jmp	loc_1DD93
; ---------------------------------------------------------------------------

loc_1DCCC:				; CODE XREF: sub_1DBAE+1Dj
					; DATA XREF: seg003:A35Fo
		cmp	byte_259A4, 80h	; '€'
		jnb	short loc_1DD09
		mov	al, byte_259A4
		add	al, 0Ah
		mov	byte_259A4, al
		cmp	byte_259A4, 80h	; '€'
		jb	short loc_1DCFE
		mov	byte_259A4, 80h	; '€'
		mov	byte_259DB, 3
		mov	word_259DE, 67E8h
		cmp	byte_2CFFA, 14h
		jnb	short loc_1DCFE
		mov	byte_2CFFA, 14h

loc_1DCFE:				; CODE XREF: sub_1DBAE+132j
					; sub_1DBAE+149j
		call	sub_11DE6
		mov	si, 1
		jmp	loc_1DD93
; ---------------------------------------------------------------------------

loc_1DD09:				; CODE XREF: sub_1DBAE+123j
		add	word_236D6, 5
		mov	bx, word_236D6
		add	bx, bx
		mov	si, [bx+2330h]
		cmp	word_236D6, 2Ah	; '*'
		jbe	short loc_1DD25
		mov	word_236D6, 2Ah	; '*'

loc_1DD25:				; CODE XREF: sub_1DBAE+16Fj
		cmp	word_236D6, 2Ah	; '*'
		jnz	short loc_1DD93
		mov	si, 0A00h
		mov	[bp+var_1], 1
		jmp	short loc_1DD93
; ---------------------------------------------------------------------------

loc_1DD35:				; CODE XREF: sub_1DBAE+1Dj
					; DATA XREF: seg003:A361o
		les	bx, dword_2CDC6
		inc	byte ptr es:[bx+0Dh]
		mov	si, 64h	; 'd'
		call	sub_EFA1
		jmp	short loc_1DD93
; ---------------------------------------------------------------------------

loc_1DD47:				; CODE XREF: sub_1DBAE+1Dj
					; DATA XREF: seg003:A363o
		push	3
		call	sub_C364
		les	bx, dword_2CDC6
		inc	byte ptr es:[bx+0Bh]
		call	sub_EEE8
		push	7
		call	sub_138B2
		mov	byte_259DB, 1
		mov	word_259DE, 67E8h
		jmp	short loc_1DD90	; jumptable 0001CCD9 case 696
; ---------------------------------------------------------------------------

loc_1DD6F:				; CODE XREF: sub_1DBAE+1Dj
					; DATA XREF: seg003:A365o
		cmp	byte_2CFFA, 14h
		jnb	short loc_1DD7B
		mov	byte_2CFFA, 14h

loc_1DD7B:				; CODE XREF: sub_1DBAE+1C6j
		mov	byte_259DB, 3
		mov	word_259DE, 67E8h
		mov	byte_259A4, 80h	; '€'
		call	sub_11DE6

loc_1DD90:				; CODE XREF: sub_1CCB8:loc_1CCD9j
					; sub_1DBAE+1BFj
		mov	si, 64h	; 'd'   ; jumptable 0001CCD9 case 696

loc_1DD93:				; CODE XREF: sub_1DBAE+17j
					; sub_1DBAE+53j ...
		cmp	byte_21CC8, 0
		jnz	short loc_1DDA0
		movzx	eax, si
		jmp	short loc_1DDA8
; ---------------------------------------------------------------------------

loc_1DDA0:				; CODE XREF: sub_1DBAE+1EAj
		mov	ax, si
		add	ax, ax
		movzx	eax, ax

loc_1DDA8:				; CODE XREF: sub_1DBAE+1F0j
		add	dword_2569A, eax
		cmp	[bp+var_1], 0
		jnz	short loc_1DDBF
		push	word ptr [di+2]
		push	word ptr [di+4]
		push	si
		call	sub_13DAA
		jmp	short loc_1DDC9
; ---------------------------------------------------------------------------

loc_1DDBF:				; CODE XREF: sub_1DBAE+203j
		push	word ptr [di+2]
		push	word ptr [di+4]
		push	si
		call	sub_13D90

loc_1DDC9:				; CODE XREF: sub_1DBAE+20Fj
		cmp	byte_23660, 20h	; ' '
		jb	short loc_1DDDF
		mov	al, byte_23660
		add	al, 0E0h ; 'à'
		mov	byte_23660, al
		push	1
		call	sub_C364

loc_1DDDF:				; CODE XREF: sub_1DBAE+220j
		inc	word_236DA
		pop	di
		pop	si
		leave
		retn	2
sub_1DBAE	endp

; ---------------------------------------------------------------------------
off_1DDE9	dw offset loc_1DBD0	; DATA XREF: sub_1DBAE+1Dr
		dw offset loc_1DC33
		dw offset loc_1DC8F
		dw offset loc_1DCCC
		dw offset loc_1DD35
		dw offset loc_1DD47
		dw offset loc_1DD6F

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DDF7	proc near		; CODE XREF: sub_1DE5D+99p

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		mov	al, [si+0Eh]
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 5
		ja	short loc_1DE36
		add	bx, bx
		jmp	cs:off_1DE51[bx]

loc_1DE11:				; DATA XREF: seg003:off_1DE51o
					; seg003:A3C7o
		inc	byte_23661
		jmp	short loc_1DE36
; ---------------------------------------------------------------------------

loc_1DE17:				; CODE XREF: sub_1DDF7+15j
					; DATA XREF: seg003:A3C3o
		mov	al, byte_23661
		add	al, 2
		mov	byte_23661, al
		jmp	short loc_1DE36
; ---------------------------------------------------------------------------

loc_1DE21:				; CODE XREF: sub_1DDF7+15j
					; DATA XREF: seg003:A3C5o
		mov	al, byte_23661
		add	al, 4
		mov	byte_23661, al
		jmp	short loc_1DE36
; ---------------------------------------------------------------------------

loc_1DE2B:				; CODE XREF: sub_1DDF7+15j
					; DATA XREF: seg003:A3C9o
		push	2
		jmp	short loc_1DE31
; ---------------------------------------------------------------------------

loc_1DE2F:				; CODE XREF: sub_1DDF7+15j
					; DATA XREF: seg003:A3CBo
		push	4

loc_1DE31:				; CODE XREF: sub_1DDF7+36j
		call	sub_C37E

loc_1DE36:				; CODE XREF: sub_1DDF7+11j
					; sub_1DDF7+1Ej ...
		cmp	byte_23661, 40h	; '@'
		jb	short loc_1DE4C
		mov	al, byte_23661
		add	al, 0D0h ; 'Ð'
		mov	byte_23661, al
		push	1
		call	sub_C37E

loc_1DE4C:				; CODE XREF: sub_1DDF7+44j
		pop	si
		pop	bp
		retn	2
sub_1DDF7	endp

; ---------------------------------------------------------------------------
off_1DE51	dw offset loc_1DE11	; DATA XREF: sub_1DDF7+15r
		dw offset loc_1DE17
		dw offset loc_1DE21
		dw offset loc_1DE11
		dw offset loc_1DE2B
		dw offset loc_1DE2F

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DE5D	proc far		; CODE XREF: sub_AB88+71P

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		mov	si, 0AF34h
		cmp	byte_236E0, 0
		jz	short loc_1DE74
		mov	byte_21CC8, 1
		jmp	short loc_1DE79
; ---------------------------------------------------------------------------

loc_1DE74:				; CODE XREF: sub_1DE5D+Ej
		mov	byte_21CC8, 0

loc_1DE79:				; CODE XREF: sub_1DE5D+15j
		xor	di, di
		jmp	loc_1DF4E
; ---------------------------------------------------------------------------

loc_1DE7E:				; CODE XREF: sub_1DE5D+F4j
		cmp	byte ptr [si], 0
		jz	loc_1DF4A
		cmp	byte ptr [si], 2
		jnz	short loc_1DE90
		mov	byte ptr [si], 0
		jmp	loc_1DF4A
; ---------------------------------------------------------------------------

loc_1DE90:				; CODE XREF: sub_1DE5D+2Bj
		cmp	byte_236E0, 0
		jz	short loc_1DEC6
		mov	byte_21CC8, 1
		mov	word ptr [si+12h], 1
		mov	ax, word ptr dword_2598E+2
		sub	ax, [si+4]
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, [si+2]
		push	ax
		call	sub_1DA8
		mov	[bp+var_1], al
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [bp+var_1]
		push	0A0h ; ' '
		call	sub_13DF2
		jmp	short loc_1DEDB
; ---------------------------------------------------------------------------

loc_1DEC6:				; CODE XREF: sub_1DE5D+38j
		cmp	word ptr [si+12h], 0
		jz	short loc_1DEDB
		mov	word ptr [si+0Ah], 0
		mov	word ptr [si+0Ch], 0
		mov	word ptr [si+12h], 0

loc_1DEDB:				; CODE XREF: sub_1DE5D+67j
					; sub_1DE5D+6Dj
		lea	ax, [si+2]
		push	ax
		call	sub_13D32
		cmp	ax, 0FF80h
		jle	short loc_1DEF2
		cmp	ax, 1880h
		jge	short loc_1DEF2
		cmp	dx, 1780h
		jl	short loc_1DEFB

loc_1DEF2:				; CODE XREF: sub_1DE5D+88j
					; sub_1DE5D+8Dj
		mov	byte ptr [si], 2
		push	si
		call	sub_1DDF7
		jmp	short loc_1DF4A
; ---------------------------------------------------------------------------

loc_1DEFB:				; CODE XREF: sub_1DE5D+93j
		cmp	dx, 0FF80h
		jge	short loc_1DF05
		mov	word ptr [si+4], 0FF80h

loc_1DF05:				; CODE XREF: sub_1DE5D+A1j
		cmp	word ptr [si+0Ch], 0
		jl	short loc_1DF10
		mov	word ptr [si+0Ah], 0

loc_1DF10:				; CODE XREF: sub_1DE5D+ACj
		cmp	byte_259AA, 0
		jnz	short loc_1DF47
		mov	bx, word ptr dword_2598E
		add	bx, 180h
		sub	bx, ax
		cmp	bx, 300h
		ja	short loc_1DF47
		mov	bx, word ptr dword_2598E+2
		add	bx, 180h
		sub	bx, dx
		cmp	bx, 260h
		ja	short loc_1DF47
		push	si
		call	sub_1DBAE
		push	0Bh
		call	sub_138B2
		mov	byte ptr [si], 2
		jmp	short loc_1DF4A
; ---------------------------------------------------------------------------

loc_1DF47:				; CODE XREF: sub_1DE5D+B8j
					; sub_1DE5D+C8j ...
		inc	word ptr [si+0Ch]

loc_1DF4A:				; CODE XREF: sub_1DE5D+24j
					; sub_1DE5D+30j ...
		inc	di
		add	si, 14h

loc_1DF4E:				; CODE XREF: sub_1DE5D+1Ej
		cmp	di, 20h	; ' '
		jl	loc_1DE7E
		call	sub_13F78
		mov	byte_21CC8, 0
		pop	di
		pop	si
		leave
		retf
sub_1DE5D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DF61	proc near		; CODE XREF: sub_1DFEF+45p
					; sub_1E0B3+4Ap ...
		push	bp
		mov	bp, sp
		mov	word ptr dword_2D010+2,	seg seg001
		mov	word ptr dword_2D010, 11C0h
		mov	word_2D014, 11BEh
		mov	byte_26719, 0
		mov	byte_2671D, 0
		mov	byte_2671F, 0
		mov	word_2671A, 0
		mov	word_26712, 0
		mov	word_26714, 0
		mov	byte_2671C, 0
		nop
		push	cs
		call	near ptr sub_15C6D
		mov	byte_2372D, 1
		pop	bp
		retn
sub_1DF61	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DFA8	proc near		; CODE XREF: sub_1DFEF+A9p
					; sub_1E0B3+AEp ...

arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		push	large [bp+arg_0]
		call	sub_F14
		push	800h
		call	sub_2578
		mov	word_2D02E, ax
		push	ax
		push	large 800h
		call	sub_E60
		call	sub_DF4
		pop	bp
		retn	4
sub_1DFA8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DFD4	proc far		; CODE XREF: sub_B29E+4P sub_E7FD+65P	...
		push	bp
		mov	bp, sp
		cmp	word_2D02E, 0
		jz	short loc_1DFED
		push	word_2D02E
		call	sub_267C
		mov	word_2D02E, 0

loc_1DFED:				; CODE XREF: sub_1DFD4+8j
		pop	bp
		retf
sub_1DFD4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DFEF	proc far		; CODE XREF: sub_AED0+15DP
		push	bp
		mov	bp, sp
		mov	word ptr dword_259FC+2,	seg seg003
		mov	word ptr dword_259FC, 587h
		mov	word_25A00, 1C88h
		mov	word_26700, 0C1Ch
		mov	word ptr dword_266F4, 0C00h
		mov	word ptr dword_266F4+2,	1700h
		mov	word ptr dword_266F8, 0C00h
		mov	word ptr dword_266F8+2,	1700h
		mov	word_266FC, 0
		mov	word_266FE, 10h
		mov	word_26702, 320h
		call	sub_1DF61
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670E, 0C00h
		mov	word ptr dword_2670A+2,	280h
		mov	word ptr dword_2670E+2,	280h
		mov	word_2D016, 768Eh
		mov	word ptr dword_2D018+2,	seg seg003
		mov	word ptr dword_2D018, 6013h
		mov	word_2D01C, 6E7Bh
		mov	byte_26718, 80h	; '€'
		mov	word_2D030, 180h
		mov	word_2D032, 100h
		mov	word_2CDCC, 42F2h
		push	ds
		push	offset aSt00_bmt ; "st00.bmt"
		call	sub_2A74
		push	10h
		push	ds
		push	offset aSt00bk_cdg ; "st00bk.cdg"
		push	0
		call	sub_13938
		push	ds
		push	offset aSt00_bb	; "st00.bb"
		call	sub_1DFA8
		mov	byte_23DC2, 0FFh
		mov	byte_23DC3, 0FFh
		mov	word_2566C, 11BEh
		mov	word_2566A, 11BEh
		pop	bp
		retf
sub_1DFEF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E0B3	proc far		; CODE XREF: sub_AED0+195P
		push	bp
		mov	bp, sp
		mov	word ptr dword_259FC+2,	seg seg003
		mov	word ptr dword_259FC, 126Dh
		mov	word_25A00, 214Ah
		mov	word_26700, 0A28h
		mov	word ptr dword_266F4, 0C00h
		mov	word ptr dword_266F4+2,	0FE00h
		mov	word ptr dword_266F8, 0C00h
		mov	word ptr dword_266F8+2,	0FE00h
		mov	word_266FC, 0
		mov	word_266FE, 10h
		mov	word_26702, 2EEh
		mov	byte_26704, 0
		call	sub_1DF61
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670E, 0C00h
		mov	word ptr dword_2670A+2,	510h
		mov	word ptr dword_2670E+2,	510h
		mov	word_2D016, 76FBh
		mov	word ptr dword_2D018+2,	seg seg003
		mov	word ptr dword_2D018, 56CDh
		mov	word_2D01C, 6CA3h
		mov	byte_26718, 0
		mov	word_2D030, 180h
		mov	word_2D032, 180h
		mov	word_2CDCC, 3F80h
		push	ds
		push	offset aSt01_bmt ; "st01.bmt"
		call	sub_2A74
		push	10h
		push	ds
		push	offset aSt01bk_cdg ; "st01bk.cdg"
		push	0
		call	sub_13938
		push	ds
		push	offset aSt01_bb	; "st01.bb"
		call	sub_1DFA8
		push	large 0FF0080h
		push	large 200008h
		call	sub_C396
		mov	byte_2D01E, al
		mov	word_2566C, 11BEh
		mov	word_2566A, 11BEh
		pop	bp
		retf
sub_1E0B3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E186	proc far		; CODE XREF: sub_AED0+1BBP
		push	bp
		mov	bp, sp
		mov	word ptr dword_259FC+2,	seg seg003
		mov	word ptr dword_259FC, 9FBh
		mov	word_25A00, 1D95h
		mov	word_26700, 640h
		mov	word ptr dword_266F4, 0C00h
		mov	word ptr dword_266F4+2,	0FE00h
		mov	word ptr dword_266F8, 0C00h
		mov	word ptr dword_266F8+2,	0FE00h
		mov	word_266FC, 0
		mov	word_266FE, 40h	; '@'
		mov	word_26702, 352h
		mov	byte_26704, 0
		call	sub_1DF61
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670E, 0C00h
		mov	word ptr dword_2670A+2,	400h
		mov	word ptr dword_2670E+2,	400h
		mov	word_2D016, 777Fh
		mov	word ptr dword_2D018+2,	seg seg003
		mov	word ptr dword_2D018, 8855h
		mov	word_2D01C, 7322h
		mov	byte_26718, 86h	; '†'
		mov	word_2D030, 180h
		mov	word_2D032, 180h
		mov	word_2CDCC, 13DCh
		push	ds
		push	offset aSt02_bmt ; "st02.bmt"
		call	sub_2A74
		push	10h
		push	ds
		push	offset aSt02bk_cdg ; "st02bk.cdg"
		push	0
		call	sub_13938
		push	ds
		push	offset aSt02_bb	; "st02.bb"
		call	sub_1DFA8
		mov	word_2566C, 11BEh
		mov	word_2566A, 11BEh
		pop	bp
		retf
sub_1E186	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E245	proc far		; CODE XREF: sub_AED0+1F0P
		push	bp
		mov	bp, sp
		mov	word ptr dword_259FC+2,	seg seg003
		mov	word ptr dword_259FC, 1824h
		mov	word_25A00, 2316h
		mov	word_26700, 0AF0h
		mov	word ptr dword_266F4, 900h
		mov	word ptr dword_266F4+2,	0FE00h
		mov	word ptr dword_266F8, 900h
		mov	word ptr dword_266F8+2,	0FE00h
		mov	word_266FC, 40h	; '@'
		mov	word_266FE, 20h	; ' '
		mov	word_26702, 4B0h
		mov	byte_26704, 0
		call	sub_1DF61
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670E, 0C00h
		mov	word ptr dword_2670A+2,	400h
		mov	word ptr dword_2670E+2,	400h
		mov	word_2D016, 77E7h
		cmp	byte_266D8, 1
		jnz	loc_1E359
		mov	word ptr dword_2D018+2,	seg seg003
		mov	word ptr dword_2D018, 0B91Bh
		mov	word_2D01C, 83A3h
		push	large 40006h
		push	large 8000Ch
		call	sub_C396
		mov	byte_2D01E, al
		push	large 10000Ch
		push	large 80006h
		call	sub_C396
		mov	byte_2D01F, al
		push	large 10002h
		push	large 30004h
		call	sub_C396
		mov	byte_2D020, al
		push	large 170017h
		push	large 180018h
		call	sub_C396
		mov	byte_2D021, al
		push	large 80009h
		push	large 9000Ah
		call	sub_C396
		mov	byte_2D022, al
		push	large 120010h
		push	large 0E000Ah
		call	sub_C396
		mov	byte_2D023, al
		push	large 60008h
		push	large 9000Ah
		call	sub_C396
		mov	byte_2D024, al
		jmp	short loc_1E371
; ---------------------------------------------------------------------------

loc_1E359:				; CODE XREF: sub_1E245+70j
		mov	word ptr dword_2D018+2,	seg seg003
		mov	word ptr dword_2D018, 3F64h
		mov	word_2D01C, 4281h
		mov	word_26716, 1770h

loc_1E371:				; CODE XREF: sub_1E245+112j
		mov	byte_26718, 80h	; '€'
		mov	word_2D030, 180h
		mov	word_2D032, 180h
		mov	word_2CDCC, 13EAh
		push	ds
		push	offset aSt03_bmt ; "st03.bmt"
		call	sub_2A74
		cmp	byte_266D8, 0
		jz	short loc_1E3A0
		push	10h
		push	ds
		push	offset aSt03bk_cdg ; "st03bk.cdg"
		jmp	short loc_1E3A6
; ---------------------------------------------------------------------------

loc_1E3A0:				; CODE XREF: sub_1E245+151j
		push	10h
		push	ds
		push	offset aSt03bk2_cdg ; "st03bk2.cdg"

loc_1E3A6:				; CODE XREF: sub_1E245+159j
		push	0
		call	sub_13938
		push	ds
		push	offset aSt03_bb	; "st03.bb"
		call	sub_1DFA8
		mov	word_2566C, 11BEh
		mov	word_2566A, 11BEh
		pop	bp
		retf
sub_1E245	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E3C2	proc far		; CODE XREF: sub_AED0+21EP
		push	bp
		mov	bp, sp
		mov	word ptr dword_259FC+2,	seg seg001
		mov	word ptr dword_259FC, 11C0h
		mov	word_25A00, 11BEh
		mov	word_26700, 0EA60h
		call	sub_1DF61
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670E, 0C00h
		mov	word ptr dword_2670A+2,	400h
		mov	word ptr dword_2670E+2,	400h
		mov	word_2D016, 7874h
		mov	word ptr dword_2D018+2,	seg seg003
		mov	word ptr dword_2D018, 2B80h
		mov	word_2D01C, 3DB3h
		mov	byte_26718, 80h	; '€'
		mov	word_2D030, 1A0h
		mov	word_2D032, 1A0h
		mov	word_2CDCC, 1508h
		push	10h
		push	ds
		push	offset aSt04bk_cdg ; "st04bk.cdg"
		push	0
		call	sub_13938
		push	ds
		push	offset aSt04_bb	; "st04.bb"
		call	sub_1DFA8
		push	11h
		push	ds
		push	offset aSt04_cdg ; "st04.cdg"
		push	0
		call	sub_13938
		mov	word_2D034, 1400h
		mov	word_2D036, 280h
		mov	word_2D038, 0BE0h
		mov	word_2566C, 40FEh
		mov	word_2566A, 4169h
		push	large 9000A0h
		push	large 0A800B4h
		call	sub_C396
		mov	byte_2D01E, al
		pop	bp
		retf
sub_1E3C2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E47C	proc far		; CODE XREF: sub_AED0+243P
		push	bp
		mov	bp, sp
		mov	word ptr dword_259FC+2,	seg seg001
		mov	word ptr dword_259FC, 11C0h
		mov	word_25A00, 11BEh
		mov	word_26700, 0EA60h
		call	sub_1DF61
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670E, 0C00h
		mov	word ptr dword_2670A+2,	500h
		mov	word ptr dword_2670E+2,	500h
		mov	word_2D016, 7DC9h
		mov	word ptr dword_2D018+2,	seg seg003
		mov	word ptr dword_2D018, 79EEh
		mov	word_2D01C, 712Ah
		mov	byte_26718, 80h	; '€'
		mov	word_2D030, 180h
		mov	word_2D032, 300h
		push	ds
		push	offset aSt05_bb	; "st05.bb"
		call	sub_1DFA8
		mov	word_2566C, 11BEh
		mov	word_2566A, 11BEh
		push	large 300040h
		push	large 500060h
		call	sub_C396
		mov	byte_2D01E, al
		push	large 10001h
		push	large 20004h
		call	sub_C396
		mov	byte_2D01F, al
		pop	bp
		retf
sub_1E47C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E518	proc far		; CODE XREF: sub_AED0+268P
		push	bp
		mov	bp, sp
		mov	word ptr dword_259FC+2,	seg seg003
		mov	word ptr dword_259FC, 0EBCh
		mov	word_25A00, 1E5Ah
		mov	word_26700, 1518h
		mov	word ptr dword_266F4, 0FF00h
		mov	word ptr dword_266F4+2,	1000h
		mov	word ptr dword_266F8, 0FF00h
		mov	word ptr dword_266F8+2,	1000h
		mov	word_266FC, 40h	; '@'
		mov	word_266FE, 0FFC0h
		mov	word_26702, 1000h
		mov	byte_26704, 0
		mov	byte_26709, 60h	; '`'
		call	sub_1DF61
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670E, 0C00h
		mov	word ptr dword_2670A+2,	500h
		mov	word ptr dword_2670E+2,	500h
		mov	word_2D016, 7E89h
		mov	word ptr dword_2D018+2,	seg seg003
		mov	word ptr dword_2D018, 4C5Bh
		mov	word_2D01C, 6AC6h
		mov	byte_26718, 80h	; '€'
		mov	word_2D030, 180h
		mov	word_2D032, 300h
		mov	word_2CDCC, 1658h
		mov	byte_2D01E, 0
		push	10h
		push	ds
		push	offset aSt06bk_cdg ; "st06bk.cdg"
		push	0
		call	sub_13938
		push	ds
		push	offset aSt06_bb	; "st06.bb"
		call	sub_1DFA8
		mov	word_2566C, 11BEh
		mov	word_2566A, 11BEh
		pop	bp
		retf
sub_1E518	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E5D8	proc near		; CODE XREF: sub_179BC+Fp
					; sub_186B9+12p ...

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		mov	byte_22E9C, 1
		mov	ax, [bp+arg_4]
		mov	word_257E2, ax
		mov	ax, [bp+arg_2]
		mov	word_257E4, ax
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_257DE, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		mov	si, ax
		or	si, si
		jz	short loc_1E60C
		push	[bp+arg_0]
		call	sub_138B2

loc_1E60C:				; CODE XREF: sub_1E5D8+2Aj
		mov	byte_22E9C, 0
		mov	ax, si
		pop	si
		pop	bp
		retn	6
sub_1E5D8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E618	proc near		; CODE XREF: sub_14CFD+2Ap
					; sub_14CFD+199p ...

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		push	bp
		mov	bp, sp
		push	si
		mov	ax, [bp+arg_4]
		mov	word_257E2, ax
		mov	ax, [bp+arg_2]
		mov	word_257E4, ax
		mov	ax, word ptr dword_266F4
		mov	word ptr dword_257DE, ax
		mov	ax, word ptr dword_266F4+2
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		mov	si, ax
		or	si, si
		jz	short loc_1E647
		push	[bp+arg_0]
		call	sub_138B2

loc_1E647:				; CODE XREF: sub_1E618+25j
		mov	ax, si
		pop	si
		pop	bp
		retn	6
sub_1E618	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E64E	proc near		; CODE XREF: sub_16610+121p
					; sub_16610+18Ep ...
		push	bp
		mov	bp, sp
		inc	word_2671A
		push	word_2D030
		push	word_2D032
		push	4
		call	sub_1E5D8
		mov	byte_2671C, al
		mov	ah, 0
		sub	word_26716, ax
		mov	ax, word_26716
		cmp	ax, word_26720
		jg	short loc_1E678
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E678:				; CODE XREF: sub_1E64E+24j
		mov	al, 0
		pop	bp
		retn
sub_1E64E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E67C	proc near		; CODE XREF: sub_16610:loc_16651p
					; sub_16610:loc_16682p	...
		push	bp
		mov	bp, sp
		inc	word_2671A
		push	word_2D030
		push	word_2D032
		push	0Ah
		call	sub_1E5D8
		pop	bp
		retn
sub_1E67C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E692	proc near		; CODE XREF: sub_16610+12Fp
					; sub_16610+19Cp ...

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		cmp	byte_259A4, 7Bh	; '{'
		ja	short loc_1E6A3
		xor	di, di
		jmp	short loc_1E6B2
; ---------------------------------------------------------------------------

loc_1E6A3:				; CODE XREF: sub_1E692+Bj
		cmp	byte_259A4, 80h	; '€'
		jnb	short loc_1E6AF
		mov	di, 1
		jmp	short loc_1E6B2
; ---------------------------------------------------------------------------

loc_1E6AF:				; CODE XREF: sub_1E692+16j
		mov	di, 2

loc_1E6B2:				; CODE XREF: sub_1E692+Fj
					; sub_1E692+1Bj
		mov	ax, word ptr dword_2670A
		add	ax, 0FC00h
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FC00h
		mov	[bp+var_4], ax
		xor	si, si
		jmp	short loc_1E6EA
; ---------------------------------------------------------------------------

loc_1E6C8:				; CODE XREF: sub_1E692+5Bj
		push	800h
		call	sub_13D76
		add	ax, [bp+var_2]
		push	ax
		push	800h
		call	sub_13D76
		add	ax, [bp+var_4]
		push	ax
		mov	bx, di
		imul	bx, 5
		mov	al, [bx+si+23DEh]
		push	ax
		call	sub_1DA38
		inc	si

loc_1E6EA:				; CODE XREF: sub_1E692+34j
		cmp	si, 5
		jl	short loc_1E6C8
		pop	di
		pop	si
		leave
		retn
sub_1E692	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E6F3	proc near		; CODE XREF: seg003:57BDp seg003:588Dp ...

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_2]
		cmp	si, 0FFFFh
		jz	short loc_1E719
		push	si
		call	sub_15C7C
		cmp	byte_2372D, 0
		jnz	short loc_1E719
		cmp	byte_2CFFA, 14h
		jnb	short loc_1E716
		mov	byte_2CFFA, 14h

loc_1E716:				; CODE XREF: sub_1E6F3+1Cj
		call	sub_1E692

loc_1E719:				; CODE XREF: sub_1E6F3+Aj
					; sub_1E6F3+15j
		mov	byte_2372D, 1
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671D, 0
		mov	byte_2671F, 0
		mov	ax, word_26720
		mov	word_26716, ax
		mov	ax, [bp+arg_0]
		mov	word_26720, ax
		pop	si
		pop	bp
		retn	4
sub_1E6F3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E743	proc near		; CODE XREF: sub_16610:loc_169B3p
					; sub_179F4:loc_17C9Fp	...
		push	bp
		mov	bp, sp
		cmp	byte_26719, 0FEh ; 'þ'
		jnz	short loc_1E7B5
		cmp	word_2671A, 0Ch
		jge	short loc_1E778
		cmp	byte_266CC, 0
		jnz	short loc_1E760
		mov	ax, 0FFFCh
		jmp	short loc_1E763
; ---------------------------------------------------------------------------

loc_1E760:				; CODE XREF: sub_1E743+16j
		mov	ax, 4

loc_1E763:				; CODE XREF: sub_1E743+1Bj
		mov	word_255BE, ax
		cmp	byte_266CD, 1
		ja	short loc_1E772
		mov	ax, 0FFFCh
		jmp	short loc_1E775
; ---------------------------------------------------------------------------

loc_1E772:				; CODE XREF: sub_1E743+28j
		mov	ax, 4

loc_1E775:				; CODE XREF: sub_1E743+2Dj
		mov	word_255C0, ax

loc_1E778:				; CODE XREF: sub_1E743+Fj
		mov	word_255AC, 20C8h
		mov	word_266D0, 2
		inc	word_2671A
		mov	ax, word_2671A
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1E915
		inc	byte_26718
		cmp	byte_26718, 0Ch
		jb	loc_1E915
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2D00A, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E7B5:				; CODE XREF: sub_1E743+8j
		mov	word_216E4, 3Ch	; '<'
		mov	byte_266D3, 1
		cmp	word_2671A, 0
		jnz	loc_1E8B3
		les	bx, dword_2CDC6
		mov	ax, word_2CFFC
		add	es:[bx+38h], ax
		cmp	byte_266D4, 5
		jz	loc_1E8AE
		cmp	byte_266D4, 4
		jnz	short loc_1E801
		cmp	byte_25689, 0
		jnz	short loc_1E7F2
		cmp	byte_25688, 0
		jnz	short loc_1E801

loc_1E7F2:				; CODE XREF: sub_1E743+A6j
		call	sub_CF01
		call	sub_D6EB
		call	sub_B7E4

loc_1E801:				; CODE XREF: sub_1E743+9Fj
					; sub_1E743+ADj
		cmp	byte_266D4, 6
		jnz	loc_1E8A4
		push	large 800100h
		call	sub_2B4E
		call	sub_D6EB
		cmp	byte_2D01E, 0
		jnz	short loc_1E89B	; CODE XREF: sub_1BDB4:loc_1BDDEj
		mov	byte_2D01E, 1
		call	sub_1DF61
		mov	word ptr dword_2670A, 0C00h
		mov	word ptr dword_2670E, 0C00h
		mov	word ptr dword_2670A+2,	600h
		mov	word ptr dword_2670E+2,	600h
		mov	word_255A8, 7E89h
		mov	word ptr dword_2D010+2,	seg seg003
		mov	word ptr dword_2D010, 0C7DAh
		mov	word_2D014, 846Fh
		mov	byte_26718, 80h	; '€'
		mov	word_2D030, 180h
		mov	word_2D032, 300h
		mov	bgm_title_id, 0Fh
		mov	word_259DC, 66A5h
		push	10h
		call	sub_13A58
		push	cs
		call	near ptr sub_1DFD4
		push	10h
		push	ds
		push	offset aSt06bk2_cdg ; "st06bk2.cdg"
		push	0
		call	sub_13938
		push	ds
		push	offset aSt06b_bb ; "st06b.bb"
		call	sub_1DFA8
		mov	byte_2D00A, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E89B:				; CODE XREF: sub_1E743+DCj
		call	sub_1D896
		inc	word_2671A
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1E8A4:				; CODE XREF: sub_1E743+C3j
		call	sub_D6EB
		call	sub_1D6C1
		jmp	short loc_1E905
; ---------------------------------------------------------------------------

loc_1E8AE:				; CODE XREF: sub_1E743+96j
		call	sub_1D896
		jmp	short loc_1E905
; ---------------------------------------------------------------------------

loc_1E8B3:				; CODE XREF: sub_1E743+82j
		cmp	word_2671A, 1A0h
		jnz	short loc_1E8E5
		cmp	byte_266D4, 5
		jnz	short loc_1E8C9
		call	sub_B7B9
		jmp	short loc_1E8D5
; ---------------------------------------------------------------------------

loc_1E8C9:				; CODE XREF: sub_1E743+17Dj
		cmp	byte_266D4, 6
		jnz	short loc_1E8D5
		call	sub_B80F

loc_1E8D5:				; CODE XREF: sub_1E743+184j
					; sub_1E743+18Bj
		mov	word_259DC, 6349h
		push	20Ah
		call	sub_133DC
		jmp	short loc_1E905
; ---------------------------------------------------------------------------

loc_1E8E5:				; CODE XREF: sub_1E743+176j
		cmp	word_2671A, 1E8h
		jnz	short loc_1E905
		les	bx, dword_2CDC6
		inc	byte ptr es:[bx+11h]
		inc	byte ptr es:[bx+13h]
		mov	byte_266D2, 2
		push	1
		call	sub_131B7

loc_1E905:				; CODE XREF: sub_1E743+169j
					; sub_1E743+16Ej ...
		inc	word_2671A
		mov	word_25982, 0C190h
		mov	word_25984, 0C190h

loc_1E915:				; CODE XREF: sub_1E743+50j
					; sub_1E743+5Dj
		pop	bp
		retn
sub_1E743	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E917	proc near		; CODE XREF: sub_1F3AB:loc_1F46Cp
					; sub_1F3AB:loc_1F737p
		push	bp
		mov	bp, sp
		push	si
		cmp	word_2671A, 1
		jnz	short loc_1E96E
		mov	byte_2D03C, 1
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E944
		mov	word_26712, 0FFC0h
		mov	word_26714, 10h
		jmp	short loc_1E96E
; ---------------------------------------------------------------------------

loc_1E944:				; CODE XREF: sub_1E917+1Dj
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_1E962
		mov	word_26712, 40h	; '@'
		mov	word_26714, 0
		jmp	short loc_1E96E
; ---------------------------------------------------------------------------

loc_1E962:				; CODE XREF: sub_1E917+3Bj
		mov	word_26712, 0FFC0h
		mov	word_26714, 0FFF0h

loc_1E96E:				; CODE XREF: sub_1E917+9j
					; sub_1E917+2Bj ...
		push	53CAh
		call	sub_13D32
		mov	si, 20h	; ' '
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_1E98A
		mov	si, 40h	; '@'

loc_1E98A:				; CODE XREF: sub_1E917+6Ej
		cmp	word_2671A, si
		jnz	short loc_1E9AE
		inc	byte_2671F
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 2
		cwd
		idiv	bx
		mov	byte_2671D, dl
		mov	word_2671A, 0
		mov	byte_2D03C, 0

loc_1E9AE:				; CODE XREF: sub_1E917+77j
		pop	si
		pop	bp
		retn
sub_1E917	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E9B1	proc near		; CODE XREF: sub_1F3AB:loc_1F600p
		push	bp
		mov	bp, sp
		push	si
		cmp	word_2671A, 1
		jnz	short loc_1EA08
		mov	byte_2D03C, 1
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E9DE
		mov	word_26712, 40h	; '@'
		mov	word_26714, 0FFF0h
		jmp	short loc_1EA08
; ---------------------------------------------------------------------------

loc_1E9DE:				; CODE XREF: sub_1E9B1+1Dj
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_1E9FC
		mov	word_26712, 0FFC0h
		mov	word_26714, 0
		jmp	short loc_1EA08
; ---------------------------------------------------------------------------

loc_1E9FC:				; CODE XREF: sub_1E9B1+3Bj
		mov	word_26712, 40h	; '@'
		mov	word_26714, 10h

loc_1EA08:				; CODE XREF: sub_1E9B1+9j
					; sub_1E9B1+2Bj ...
		push	53CAh
		call	sub_13D32
		mov	si, 20h	; ' '
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 3
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_1EA24
		mov	si, 40h	; '@'

loc_1EA24:				; CODE XREF: sub_1E9B1+6Ej
		cmp	word_2671A, si
		jnz	short loc_1EA48
		inc	byte_2671F
		mov	al, byte_2671F
		mov	ah, 0
		mov	bx, 2
		cwd
		idiv	bx
		mov	byte_2671D, dl
		mov	word_2671A, 0
		mov	byte_2D03C, 0

loc_1EA48:				; CODE XREF: sub_1E9B1+77j
		pop	si
		pop	bp
		retn
sub_1E9B1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EA4B	proc near		; CODE XREF: sub_1ED15+4p sub_1EDBC+4p ...

var_2		= word ptr -2

; FUNCTION CHUNK AT 878B SIZE 00000009 BYTES
; FUNCTION CHUNK AT B443 SIZE 000000B4 BYTES

		enter	2, 0
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 0Ah		; switch 10 cases
		mov	bx, (offset byte_1EB08+1)

loc_1EA5B:				; CODE XREF: sub_1EA4B+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1EA6B
		add	bx, 2
		loop	loc_1EA5B
		jmp	loc_1EAF9	; default
; ---------------------------------------------------------------------------

loc_1EA6B:				; CODE XREF: sub_1EA4B+16j
		jmp	word ptr cs:[bx+14h] ; switch jump
; ---------------------------------------------------------------------------
		mov	ax, word ptr dword_2670A
		add	ax, 40h	; '@'
		mov	word ptr dword_2A8C6, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FE40h
		mov	word ptr dword_2A8C6+2,	ax
		mov	word_2A8D0, 10h
		mov	word_2A8CE, 1000h
		mov	byte_2A8D2, 9
		call	sub_13B21
		mov	byte_26718, 81h	; ''
		push	8
		call	sub_138B2
		mov	byte_25592, 0Fh
		jmp	short loc_1EAF9	; default
; ---------------------------------------------------------------------------
		mov	byte_2A8D2, 8
		call	sub_13B21
		jmp	short loc_1EAF9	; default
; ---------------------------------------------------------------------------
		mov	byte_26718, 82h	; '‚'
		jmp	short loc_1EAF9	; default
; ---------------------------------------------------------------------------
		mov	byte_26718, 83h	; 'ƒ'
		jmp	short loc_1EAF9	; default
; ---------------------------------------------------------------------------
		mov	byte_26718, 84h	; '„'
		push	word ptr dword_2A8C6
		push	word ptr dword_2A8C6+2
		call	sub_C696
		jmp	short loc_1EAF9	; default
; ---------------------------------------------------------------------------
		mov	byte_26718, 85h	; '…'
		jmp	short loc_1EAF9	; default
; ---------------------------------------------------------------------------
		mov	byte_26718, 86h	; '†'
		jmp	short loc_1EAF9	; default
; ---------------------------------------------------------------------------
		mov	byte_26718, 87h	; '‡'
		jmp	short loc_1EAF9	; default
; ---------------------------------------------------------------------------
		mov	byte_26718, 81h	; ''
		push	3
		call	sub_138B2
		mov	al, 2
		leave
		retn
; ---------------------------------------------------------------------------

loc_1EAF9:				; CODE XREF: sub_1EA4B+1Dj
					; sub_1EA4B+5Bj ...
		cmp	word_2671A, 2Eh	; '.' ; default
		jge	short loc_1EB04
		mov	al, 0
		leave
		retn
; ---------------------------------------------------------------------------

loc_1EB04:				; CODE XREF: sub_1EA4B+B3j
		mov	al, 1
		leave
		retn
sub_1EA4B	endp ; sp-analysis failed

; ---------------------------------------------------------------------------
byte_1EB08	db 0, 0Eh, 0, 10h, 0, 12h, 0, 16h, 0, 1Ah, 0, 1Eh, 0, 22h
					; DATA XREF: sub_1EA4B+Do
		db 0, 26h, 0, 2Ah, 0, 2Eh, 0, 0DFh, 0AFh, 18h, 0B0h, 1Dh
		db 0B0h, 22h, 0B0h, 29h, 0B0h, 30h, 0B0h, 44h, 0B0h, 4Bh
		db 0B0h, 52h, 0B0h, 59h, 0B0h

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EB31	proc near		; CODE XREF: sub_1F111+4Bp
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_1EB83
; ---------------------------------------------------------------------------

loc_1EB3D:				; CODE XREF: sub_1EB31+55j
		cmp	byte ptr [si], 0
		jnz	short loc_1EB7F
		mov	byte ptr [si], 2
		mov	eax, dword ptr word_2D03F+1
		mov	[si+2],	eax
		mov	eax, dword_2D044
		mov	[si+6],	eax
		mov	ax, word_2D050
		mov	[si+12h], ax
		mov	al, byte_2D056
		mov	[si+18h], al
		mov	al, byte ptr word_2D03F
		mov	[si+1],	al
		mov	word ptr [si+10h], 0
		lea	ax, [si+0Ah]
		push	ax
		push	word_2D03F
		mov	al, byte_2D056
		mov	ah, 0
		push	ax
		call	sub_13DF2
		jmp	short loc_1EB88
; ---------------------------------------------------------------------------

loc_1EB7F:				; CODE XREF: sub_1EB31+Fj
		inc	di
		add	si, 1Ah

loc_1EB83:				; CODE XREF: sub_1EB31+Aj
		cmp	di, 20h	; ' '
		jl	short loc_1EB3D

loc_1EB88:				; CODE XREF: sub_1EB31+4Cj
		pop	di
		pop	si
		pop	bp
		retn
sub_1EB31	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EB8C	proc near		; CODE XREF: sub_1EE21+2Cp

arg_0		= word ptr  4
arg_2		= byte ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		xor	cx, cx
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_1EBE8
; ---------------------------------------------------------------------------

loc_1EB9A:				; CODE XREF: sub_1EB8C+5Fj
		cmp	byte ptr [si], 0
		jnz	short loc_1EBE4
		mov	byte ptr [si], 1
		mov	ax, word_2D04C
		mov	[si+0Eh], ax
		mov	eax, dword ptr word_2D03F+1
		mov	[si+2],	eax
		mov	eax, dword_2D044
		mov	[si+6],	eax
		mov	ax, word_2D050
		mov	[si+12h], ax
		mov	al, byte_2D056
		mov	[si+18h], al
		mov	ax, cx
		shl	ax, 8
		cwd
		idiv	[bp+arg_0]
		add	al, [bp+arg_2]
		mov	[si+1],	al
		mov	word ptr [si+10h], 0
		mov	al, byte_2D057
		mov	[si+19h], al
		inc	cx
		cmp	cx, [bp+arg_0]
		jge	short loc_1EBED

loc_1EBE4:				; CODE XREF: sub_1EB8C+11j
		inc	di
		add	si, 1Ah

loc_1EBE8:				; CODE XREF: sub_1EB8C+Cj
		cmp	di, 20h	; ' '
		jl	short loc_1EB9A

loc_1EBED:				; CODE XREF: sub_1EB8C+56j
		pop	di
		pop	si
		pop	bp
		retn	4
sub_1EB8C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EBF3	proc near		; CODE XREF: sub_1F3AB+506p

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	di
		mov	si, 0B204h
		xor	di, di
		jmp	loc_1ED0A
; ---------------------------------------------------------------------------

loc_1EC01:				; CODE XREF: sub_1EBF3+11Aj
		cmp	byte ptr [si], 0
		jz	loc_1ED06
		cmp	byte ptr [si], 1
		jnz	short loc_1EC86
		push	word ptr [si+6]
		push	word ptr [si+10h]
		mov	al, [si+1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+566h]
		call	sub_13320
		mov	[si+2],	ax
		push	word ptr [si+8]
		push	word ptr [si+10h]
		mov	al, [si+1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+4E6h]
		call	sub_13320
		mov	[si+4],	ax
		cmp	word ptr [si+10h], 400h
		jge	short loc_1EC4E
		add	word ptr [si+10h], 40h ; '@'

loc_1EC4E:				; CODE XREF: sub_1EBF3+55j
		dec	word ptr [si+0Eh]
		mov	al, [si+19h]
		add	[si+1],	al
		cmp	word ptr [si+0Eh], 0
		jnz	short loc_1ECBC
		cmp	byte ptr [si+19h], 0
		jl	short loc_1EC6A
		mov	al, [si+1]
		add	al, 40h	; '@'
		jmp	short loc_1EC6F
; ---------------------------------------------------------------------------

loc_1EC6A:				; CODE XREF: sub_1EBF3+6Ej
		mov	al, [si+1]
		add	al, 0C0h ; 'À'

loc_1EC6F:				; CODE XREF: sub_1EBF3+75j
		mov	[si+1],	al
		lea	ax, [si+0Ah]
		push	ax
		push	word ptr [si+1]
		mov	al, [si+18h]
		mov	ah, 0
		push	ax
		call	sub_13DF2
		inc	byte ptr [si]
		jmp	short loc_1ECBC
; ---------------------------------------------------------------------------

loc_1EC86:				; CODE XREF: sub_1EBF3+18j
		cmp	byte ptr [si], 2
		jnz	short loc_1ECBC
		inc	word ptr [si+0Eh]
		mov	ax, [si+0Ah]
		add	[si+2],	ax
		cmp	word ptr [si+2], 0
		jl	short loc_1ECA1
		cmp	word ptr [si+2], 1800h
		jle	short loc_1ECA9

loc_1ECA1:				; CODE XREF: sub_1EBF3+A5j
		mov	ax, [si+0Ah]
		neg	ax
		mov	[si+0Ah], ax

loc_1ECA9:				; CODE XREF: sub_1EBF3+ACj
		mov	ax, [si+0Ch]
		add	[si+4],	ax
		cmp	word ptr [si+4], 1700h
		jl	short loc_1ECB9
		mov	byte ptr [si], 0

loc_1ECB9:				; CODE XREF: sub_1EBF3+C1j
		inc	word ptr [si+0Ch]

loc_1ECBC:				; CODE XREF: sub_1EBF3+68j
					; sub_1EBF3+91j ...
		mov	word_257E2, 0C0h ; 'À'
		mov	word_257E4, 0C0h ; 'À'
		mov	ax, [si+2]
		mov	word ptr dword_257DE, ax
		mov	ax, [si+4]
		mov	word ptr dword_257DE+2,	ax
		call	sub_105B9
		mov	ax, [si+2]
		add	ax, 0FF40h
		mov	[bp+var_2], ax
		mov	ax, [si+4]
		add	ax, 0FF40h
		mov	[bp+var_4], ax
		mov	ax, word ptr dword_2598E
		sub	ax, [bp+var_2]
		cmp	ax, 180h
		jnb	short loc_1ED06
		mov	ax, word ptr dword_2598E+2
		sub	ax, [bp+var_4]
		cmp	ax, 180h
		jnb	short loc_1ED06
		mov	byte_259A9, 1

loc_1ED06:				; CODE XREF: sub_1EBF3+11j
					; sub_1EBF3+101j ...
		inc	di
		add	si, 1Ah

loc_1ED0A:				; CODE XREF: sub_1EBF3+Bj
		cmp	di, 20h	; ' '
		jl	loc_1EC01
		pop	di
		pop	si
		leave
		retn
sub_1EBF3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1ED15	proc near		; CODE XREF: sub_1F3AB:loc_1F462p

var_1		= byte ptr -1

		enter	2, 0
		call	sub_1EA4B
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_1ED71
		mov	byte_266E2, 2
		mov	byte_266E3, 5Ch	; '\'
		mov	byte_266EE, 60h	; '`'
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8
		mov	byte_2671E, al
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 6
		mov	al, byte_2D023
		mov	byte_266F0, al
		call	word_2D004
		cmp	word ptr dword_2598E, 0C00h
		jge	short loc_1ED6C
		mov	al, 0FEh ; 'þ'
		jmp	short loc_1ED6E
; ---------------------------------------------------------------------------

loc_1ED6C:				; CODE XREF: sub_1ED15+51j
		mov	al, 2

loc_1ED6E:				; CODE XREF: sub_1ED15+55j
		mov	byte_2D03A, al

loc_1ED71:				; CODE XREF: sub_1ED15+Ej
		cmp	[bp+var_1], 1
		jnz	short locret_1EDBA
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EDA3
		mov	al, byte_2671E
		mov	byte_266ED, al
		call	word_2D000
		push	3
		call	sub_138B2
		cmp	word_2671A, 40h	; '@'
		jl	short loc_1EDA3
		mov	al, byte_2D03A
		add	byte_2671E, al

loc_1EDA3:				; CODE XREF: sub_1ED15+6Dj
					; sub_1ED15+85j
		cmp	word_2671A, 70h	; 'p'
		jl	short locret_1EDBA
		mov	byte_26718, 80h	; '€'
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

locret_1EDBA:				; CODE XREF: sub_1ED15+60j
					; sub_1ED15+93j
		leave
		retn
sub_1ED15	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EDBC	proc near		; CODE XREF: sub_1F3AB:loc_1F467p

var_1		= byte ptr -1

		enter	2, 0
		call	sub_1EA4B
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_1EE01
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EE, 55h	; 'U'
		mov	byte_266ED, 0
		mov	byte_266F2, 80h	; '€'
		mov	al, byte_2D020
		mov	byte_2CFF7, al
		mov	byte_266EC, 2Eh	; '.'
		mov	byte_266EF, 9
		mov	byte_266F0, 6
		call	word_2D004
		call	sub_1CFB5

loc_1EE01:				; CODE XREF: sub_1EDBC+Ej
		cmp	[bp+var_1], 1
		jnz	short locret_1EE1F
		cmp	word_2671A, 80h	; '€'
		jl	short locret_1EE1F
		mov	byte_26718, 80h	; '€'
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

locret_1EE1F:				; CODE XREF: sub_1EDBC+49j
					; sub_1EDBC+51j
		leave
		retn
sub_1EDBC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EE21	proc near		; CODE XREF: sub_1F3AB+192p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_1EE57
		mov	byte_26718, 88h	; 'ˆ'
		mov	word_2D04C, 40h	; '@'
		mov	byte_2D056, 38h	; '8'
		mov	eax, dword_2670A
		mov	dword_2D044, eax
		call	sub_13D52
		push	ax
		mov	al, byte_2D01E
		mov	ah, 0
		push	ax
		call	sub_1EB8C
		push	8
		call	sub_138B2

loc_1EE57:				; CODE XREF: sub_1EE21+8j
		cmp	word_2671A, 60h	; '`'
		jl	short loc_1EE71
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	al, byte_2D057
		neg	al
		mov	byte_2D057, al

loc_1EE71:				; CODE XREF: sub_1EE21+3Bj
		pop	bp
		retn
sub_1EE21	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EE73	proc near		; CODE XREF: sub_1F3AB+197p

var_1		= byte ptr -1

		enter	2, 0
		push	si
		call	sub_1EA4B
		mov	[bp+var_1], al
		cmp	[bp+var_1], 1
		jnz	loc_1EF84
		mov	ax, word_2671A
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1EEF5
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266E2, 5
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EE, 10h
		mov	byte_266ED, 0
sub_1EE73	endp ; sp-analysis failed

; START	OF FUNCTION CHUNK FOR sub_1EA4B

loc_1EED3:				; CODE XREF: sub_1EA4B:loc_1EA6Bj
		mov	byte_266F2, 82h	; '‚' ; jumptable 0001EA6B case 65331
		mov	byte_2CFF7, 1
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 10h
		call	word_2D004
		call	sub_1CFB5
		push	3
		call	sub_138B2

loc_1EEF5:				; CODE XREF: sub_1EE73+1Ej
		mov	ax, word_2671A
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cmp	dx, 10h
		jnz	short loc_1EF6C
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266E2, 1
		mov	byte_266EE, 18h
		mov	byte_266EC, 2Fh	; '/'
		mov	byte_266EF, 4
		mov	byte_266F0, 8
		call	word_2D004
		xor	si, si
		call	sub_13D52
		jmp	short loc_1EF5D
; ---------------------------------------------------------------------------

loc_1EF53:				; CODE XREF: sub_1EA4B+518j
		call	word_2D000
		inc	si
		mov	al, byte_266ED
		add	al, 15h

loc_1EF5D:				; CODE XREF: sub_1EA4B+506j
		mov	byte_266ED, al
		cmp	si, 0Ch
		jl	short loc_1EF53
		push	3
		call	sub_138B2

loc_1EF6C:				; CODE XREF: sub_1EA4B+4B6j
		cmp	word_2671A, 120h
		jl	short loc_1EF84
		mov	byte_26718, 80h	; '€'
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1EF84:				; CODE XREF: sub_1EE73+Fj
					; sub_1EA4B+527j
		pop	si
		leave
		retn
; END OF FUNCTION CHUNK	FOR sub_1EA4B

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EF87	proc near		; CODE XREF: sub_1F3AB:loc_1F5F6p
					; sub_1F3AB:loc_1F72Dp

var_1		= byte ptr -1

		enter	2, 0
		call	sub_1EA4B
		mov	[bp+var_1], al
		cmp	[bp+var_1], 1
		jnz	locret_1F04C
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1F034
		mov	byte_266E2, 1
		mov	byte_266EE, 80h	; '€'
		push	7
		call	sub_13D60
		add	al, 0BCh ; '¼'
		mov	byte_266ED, al
		mov	byte_266EC, 2Dh	; '-'
		mov	al, byte_2D021
		mov	byte_266EF, al
		mov	al, byte_2D022
		mov	byte_266F0, al
		call	sub_1CFA2
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F034
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 30h	; '0'
		mov	al, byte_25688
		add	al, 3
		mov	byte_266EF, al
		mov	byte_266F0, 10h
		mov	byte_266E2, 4
		mov	byte_266EE, 20h	; ' '
		mov	byte_266ED, 0
		mov	byte_266E3, 3Dh	; '='
		call	word_2D000
		push	3
		call	sub_138B2

loc_1F034:				; CODE XREF: sub_1EF87+1Dj
					; sub_1EF87+54j
		cmp	word_2671A, 0C0h ; 'À'
		jl	short locret_1F04C
		mov	byte_26718, 80h	; '€'
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

locret_1F04C:				; CODE XREF: sub_1EF87+Ej
					; sub_1EF87+B3j
		leave
		retn
sub_1EF87	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F04E	proc near		; CODE XREF: sub_1F3AB:loc_1F5FBp

var_1		= byte ptr -1

		enter	2, 0
		call	sub_1EA4B
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_1F08E
		mov	byte_266E2, 1
		mov	byte_266EE, 36h	; '6'
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_2670A+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_2670A
		push	ax
		call	sub_1DA8
		mov	byte_266ED, al
		mov	byte_266EC, 1Ch
		mov	byte_266EF, 3
		call	word_2D004

loc_1F08E:				; CODE XREF: sub_1F04E+Ej
		cmp	[bp+var_1], 1
		jnz	short locret_1F10F
		cmp	word_2671A, 60h	; '`'
		jge	short loc_1F0B0
		mov	ax, word_2671A
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_1F10F
		call	word_2D000
		push	3
		jmp	short loc_1F0F8
; ---------------------------------------------------------------------------

loc_1F0B0:				; CODE XREF: sub_1F04E+4Bj
		cmp	word_2671A, 80h	; '€'
		jg	short loc_1F0FF
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_1F10F
		mov	byte_266E2, 5
		mov	byte_266E3, 39h	; '9'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266EE, 30h	; '0'
		mov	byte_266F2, 82h	; '‚'
		mov	byte_2CFF7, 1
		call	word_2D004
		call	word_2D002
		push	0Fh

loc_1F0F8:				; CODE XREF: sub_1F04E+60j
		call	sub_138B2
		leave
		retn
; ---------------------------------------------------------------------------

loc_1F0FF:				; CODE XREF: sub_1F04E+68j
		mov	byte_26718, 80h	; '€'
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

locret_1F10F:				; CODE XREF: sub_1F04E+44j
					; sub_1F04E+58j ...
		leave
		retn
sub_1F04E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F111	proc near		; CODE XREF: sub_1F3AB:loc_1F6CDp
		push	bp
		mov	bp, sp
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_1F13D
		mov	byte_26718, 88h	; 'ˆ'
		mov	byte ptr word_2D03F, 0
		mov	byte_2D056, 38h	; '8'
		mov	ax, word ptr dword_2670A
		mov	word_2D03F+1, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_2D042, ax
		push	8
		call	sub_138B2

loc_1F13D:				; CODE XREF: sub_1F111+8j
		cmp	word_2671A, 20h	; ' '
		jl	short loc_1F15F
		mov	al, byte_2D01F
		mov	ah, 0
		push	ax
		mov	ax, word_2671A
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_1F15F
		mov	al, byte_2D057
		sub	byte ptr word_2D03F, al
		call	sub_1EB31

loc_1F15F:				; CODE XREF: sub_1F111+31j
					; sub_1F111+42j
		cmp	word_2671A, 0B4h ; '´'
		jl	short loc_1F17A
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		mov	al, byte_2D057
		neg	al
		mov	byte_2D057, al

loc_1F17A:				; CODE XREF: sub_1F111+54j
		pop	bp
		retn
sub_1F111	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F17C	proc near		; CODE XREF: sub_1F3AB+463p
		push	bp
		mov	bp, sp
		push	si
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_1F1AA
		mov	byte_26718, 88h	; 'ˆ'
		mov	byte_2671E, 0
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266ED, 0C0h ; 'À'
		mov	byte_266F2, 0FFh
		mov	byte_266F0, 8

loc_1F1AA:				; CODE XREF: sub_1F17C+9j
		cmp	word_2671A, 20h	; ' '
		jl	short loc_1F227
		mov	ax, word_2671A
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F227
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266E2, 1
		mov	byte_266EE, 18h
		mov	byte_266EC, 2Fh	; '/'
		mov	byte_266EF, 4
		mov	byte_266F0, 0Ah
		call	word_2D004
		xor	si, si
		call	sub_13D52
		jmp	short loc_1F218
; ---------------------------------------------------------------------------

loc_1F20E:				; CODE XREF: sub_1F17C+A2j
		call	word_2D000
		inc	si
		mov	al, byte_266ED
		add	al, 20h	; ' '

loc_1F218:				; CODE XREF: sub_1F17C+90j
		mov	byte_266ED, al
		cmp	si, 8
		jl	short loc_1F20E
		push	3
		call	sub_138B2

loc_1F227:				; CODE XREF: sub_1F17C+33j
					; sub_1F17C+40j
		pop	si
		pop	bp
		retn
sub_1F17C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F22A	proc near		; CODE XREF: sub_1F3AB:loc_1F6D2p

var_1		= byte ptr -1

		enter	2, 0
		call	sub_1EA4B
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_1F263
		mov	byte_266E2, 4
		mov	byte_266E3, 39h	; '9'
		mov	byte_266ED, 0C0h ; 'À'
		mov	byte_266F2, 0FFh
		mov	byte_266F0, 8
		cmp	byte_237F6, 78h	; 'x'
		jz	short loc_1F25E
		mov	al, 78h	; 'x'
		jmp	short loc_1F260
; ---------------------------------------------------------------------------

loc_1F25E:				; CODE XREF: sub_1F22A+2Ej
		mov	al, 88h	; 'ˆ'

loc_1F260:				; CODE XREF: sub_1F22A+32j
		mov	byte_237F6, al

loc_1F263:				; CODE XREF: sub_1F22A+Ej
		cmp	[bp+var_1], 1
		jnz	locret_1F2F1
		mov	ax, word_2671A
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F2D9
		push	1Fh
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		mov	byte_266EC, 2Dh	; '-'
		push	3
		call	sub_13D60
		add	al, 2
		mov	byte_266EF, al
		call	word_2D004
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_237F6
		add	byte_266ED, al
		call	word_2D002
		mov	al, byte_266ED
		add	al, 80h	; '€'
		mov	byte_266ED, al
		call	word_2D002
		push	3
		call	sub_138B2

loc_1F2D9:				; CODE XREF: sub_1F22A+4Cj
		cmp	word_2671A, 0E0h ; 'à'
		jl	short locret_1F2F1
		mov	byte_26718, 80h	; '€'
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

locret_1F2F1:				; CODE XREF: sub_1F22A+3Dj
					; sub_1F22A+B5j
		leave
		retn
sub_1F22A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F2F3	proc near		; CODE XREF: sub_1F3AB:loc_1F732p

var_1		= byte ptr -1

		enter	2, 0
		push	si
		call	sub_1EA4B
		mov	[bp+var_1], al
		cmp	[bp+var_1], 2
		jnz	short loc_1F328
		mov	byte_266E2, 4
		mov	byte_266EC, 30h	; '0'
		mov	al, byte_2D024
		mov	byte_266EF, al
		mov	byte_266F0, 0Ch
		mov	byte_266F2, 0FFh
		mov	byte_266ED, 0
		mov	byte_266E3, 39h	; '9'

loc_1F328:				; CODE XREF: sub_1F2F3+Fj
		cmp	[bp+var_1], 1
		jnz	short loc_1F375
		mov	ax, word_2671A
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cmp	dx, 10h
		jnz	short loc_1F35D
		xor	si, si
		mov	byte_266ED, 20h	; ' '
		jmp	short loc_1F351
; ---------------------------------------------------------------------------

loc_1F345:				; CODE XREF: sub_1F2F3+61j
		call	sub_1CFB5
		inc	si
		mov	al, byte_266ED
		add	al, 0F0h ; 'ð'
		mov	byte_266ED, al

loc_1F351:				; CODE XREF: sub_1F2F3+50j
		cmp	si, 5
		jl	short loc_1F345
		push	0Fh
		call	sub_138B2

loc_1F35D:				; CODE XREF: sub_1F2F3+47j
		cmp	word_2671A, 80h	; '€'
		jl	short loc_1F375
		mov	byte_26718, 80h	; '€'
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1F375:				; CODE XREF: sub_1F2F3+39j
					; sub_1F2F3+70j
		pop	si
		leave
		retn
sub_1F2F3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F378	proc near		; CODE XREF: sub_1F3AB+76p
					; sub_1F3AB:loc_1F46Fp	...
		push	bp
		mov	bp, sp
		cmp	byte_237F7, 0
		jnz	short loc_1F394
		inc	byte_23DC2
		cmp	byte_23DC2, 0F0h ; 'ð'
		jb	short loc_1F3A4
		mov	byte_237F7, 1
		jmp	short loc_1F3A4
; ---------------------------------------------------------------------------

loc_1F394:				; CODE XREF: sub_1F378+8j
		dec	byte_23DC2
		cmp	byte_23DC2, 40h	; '@'
		ja	short loc_1F3A4
		mov	byte_237F7, 0

loc_1F3A4:				; CODE XREF: sub_1F378+13j
					; sub_1F378+1Aj ...
		mov	byte_266D3, 1
		pop	bp
		retn
sub_1F378	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F3AB	proc far

var_2		= word ptr -2

; FUNCTION CHUNK AT BE15 SIZE 0000001B BYTES

		enter	2, 0
		mov	ax, word ptr dword_2670A
		add	ax, 40h	; '@'
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FE40h
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_26719
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 0Ch
		ja	loc_1F8A0
		add	bx, bx
		jmp	word ptr cs:[bx-41BCh]
; ---------------------------------------------------------------------------
		cmp	word_2671A, 0
		jnz	short loc_1F3E2
		mov	byte_2D03C, 0

loc_1F3E2:				; CODE XREF: sub_1F3AB+30j
		call	sub_1E67C
		cmp	word_2671A, 60h	; '`'
		jle	loc_1F8A5
		inc	byte_26719
		mov	byte_23DC2, 80h	; '€'
		mov	byte_23DC3, 0
		mov	byte_23DC4, 0E0h ; 'à'
		mov	byte_266D3, 1
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	word_255AC, 77E7h
		mov	byte_2CDCA, 0Fh
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		call	sub_1F378
		inc	word_2671A
		call	sub_1E67C
		cmp	word_2671A, 80h	; '€'
		jl	loc_1F8A5
		mov	word_26712, 0
		mov	word_26720, 238Ch
		push	large 0FFFF1EDCh
		call	sub_1E6F3
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_1F462
		cmp	ax, 1
		jz	short loc_1F467
		cmp	ax, 0FFh
		jz	short loc_1F46C
		jmp	short loc_1F46F
; ---------------------------------------------------------------------------

loc_1F462:				; CODE XREF: sub_1F3AB+A9j
		call	sub_1ED15
		jmp	short loc_1F46F
; ---------------------------------------------------------------------------

loc_1F467:				; CODE XREF: sub_1F3AB+AEj
		call	sub_1EDBC
		jmp	short loc_1F46F
; ---------------------------------------------------------------------------

loc_1F46C:				; CODE XREF: sub_1F3AB+B3j
		call	sub_1E917

loc_1F46F:				; CODE XREF: sub_1F3AB+B5j
					; sub_1F3AB+BAj ...
		call	sub_1F378
		cmp	byte_2671F, 9
		jnb	short loc_1F487
		call	sub_1E64E
		or	al, al
		jz	loc_1F8A5
		push	0Ah
		call	sub_19FD8

loc_1F487:				; CODE XREF: sub_1F3AB+CCj
		push	large 189Ch
		jmp	loc_1F621
; ---------------------------------------------------------------------------
		cmp	word ptr dword_2670A, 0C00h
		jge	short loc_1F4A0
		mov	word_26712, 20h	; ' '
		jmp	short loc_1F4B6
; ---------------------------------------------------------------------------

loc_1F4A0:				; CODE XREF: sub_1F3AB+EBj
		cmp	word ptr dword_2670A, 0C00h
		jle	short loc_1F4B0
		mov	word_26712, 0FFE0h
		jmp	short loc_1F4B6
; ---------------------------------------------------------------------------

loc_1F4B0:				; CODE XREF: sub_1F3AB+FBj
		mov	word_26712, 0

loc_1F4B6:				; CODE XREF: sub_1F3AB+F3j
					; sub_1F3AB+103j
		cmp	word ptr dword_2670A+2,	600h
		jge	short loc_1F4C6
		mov	word_26714, 10h
		jmp	short loc_1F4DC
; ---------------------------------------------------------------------------

loc_1F4C6:				; CODE XREF: sub_1F3AB+111j
		cmp	word ptr dword_2670A+2,	600h
		jle	short loc_1F4D6
		mov	word_26714, 0FFF0h
		jmp	short loc_1F4DC
; ---------------------------------------------------------------------------

loc_1F4D6:				; CODE XREF: sub_1F3AB+121j
		mov	word_26714, 0

loc_1F4DC:				; CODE XREF: sub_1F3AB+119j
					; sub_1F3AB+129j
		push	53CAh
		call	sub_13D32
		call	sub_1F378
		call	sub_1E64E
		cmp	word_2671A, 40h	; '@'
		jl	loc_1F8A5
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		mov	byte_26718, 81h	; ''
		mov	byte_2D057, 4
		mov	byte_2D03B, 8Ch	; 'Œ'
		mov	byte_2D028, 0
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		mov	[bp+var_2], ax
		mov	cx, 5		; switch 5 cases
		mov	bx, offset byte_1F8C0

loc_1F52A:				; CODE XREF: sub_1F3AB+18Aj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1F539
		add	bx, 2
		loop	loc_1F52A
		jmp	short loc_1F579	; default
; ---------------------------------------------------------------------------

loc_1F539:				; CODE XREF: sub_1F3AB+185j
		jmp	word ptr cs:[bx+0Ah] ; switch jump
; ---------------------------------------------------------------------------
		call	sub_1EE21
		jmp	short loc_1F579	; default
; ---------------------------------------------------------------------------
		call	sub_1EE73
		jmp	short loc_1F579	; default
; ---------------------------------------------------------------------------
		inc	byte_2671F
		cmp	byte_2D028, 2
		ja	short loc_1F568
		push	1
		call	sub_13D60
		or	ax, ax
		jz	short loc_1F561
		inc	byte_2D028
		jmp	short loc_1F56D
; ---------------------------------------------------------------------------

loc_1F561:				; CODE XREF: sub_1F3AB+1AEj
		mov	byte_2D028, 3
		jmp	short loc_1F56D
; ---------------------------------------------------------------------------

loc_1F568:				; CODE XREF: sub_1F3AB+1A5j
		mov	byte_2D028, 0

loc_1F56D:				; CODE XREF: sub_1F3AB+1B4j
					; sub_1F3AB+1BBj
		mov	al, byte_2D028
		mov	byte_2671D, al
		mov	word_2671A, 0

loc_1F579:				; CODE XREF: sub_1F3AB+18Cj
					; sub_1F3AB+195j ...
		call	sub_1F378	; default
		cmp	byte_2671F, 12h
		jnb	short loc_1F591
		call	sub_1E64E
		or	al, al
		jz	loc_1F8A5
		push	0Ah
		call	sub_19FD8

loc_1F591:				; CODE XREF: sub_1F3AB+1D6j
		push	large 11194h
		call	sub_1E6F3
		mov	word_26712, 0
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		cmp	word ptr dword_2670A+2,	800h
		jge	short loc_1F5B3
		mov	word_26714, 10h
		jmp	short loc_1F5C9
; ---------------------------------------------------------------------------

loc_1F5B3:				; CODE XREF: sub_1F3AB+1FEj
		cmp	word ptr dword_2670A+2,	800h
		jle	short loc_1F5C3
		mov	word_26714, 0FFF0h
		jmp	short loc_1F5C9
; ---------------------------------------------------------------------------

loc_1F5C3:				; CODE XREF: sub_1F3AB+20Ej
		mov	word_26714, 0

loc_1F5C9:				; CODE XREF: sub_1F3AB+206j
					; sub_1F3AB+216j
		push	53CAh
		call	sub_13D32
		call	sub_1F378
		call	sub_1E64E
		cmp	word_2671A, 40h	; '@'
		jl	loc_1F8A5
		jmp	loc_1F7E1
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_1F5F6
		cmp	ax, 1
		jz	short loc_1F5FB
		cmp	ax, 0FFh
		jz	short loc_1F600
		jmp	short loc_1F603
; ---------------------------------------------------------------------------

loc_1F5F6:				; CODE XREF: sub_1F3AB+23Dj
		call	sub_1EF87
		jmp	short loc_1F603
; ---------------------------------------------------------------------------

loc_1F5FB:				; CODE XREF: sub_1F3AB+242j
		call	sub_1F04E
		jmp	short loc_1F603
; ---------------------------------------------------------------------------

loc_1F600:				; CODE XREF: sub_1F3AB+247j
		call	sub_1E9B1

loc_1F603:				; CODE XREF: sub_1F3AB+249j
					; sub_1F3AB+24Ej ...
		call	sub_1F378
		cmp	byte_2671F, 0Bh
		jnb	short loc_1F61B
		call	sub_1E64E
		or	al, al
		jz	loc_1F8A5
		push	0Ah
		call	sub_19FD8

loc_1F61B:				; CODE XREF: sub_1F3AB+260j
		push	large 20A8Ch

loc_1F621:				; CODE XREF: sub_1F3AB+E2j
		call	sub_1E6F3
		mov	byte_26718, 81h	; ''
		mov	byte_2D03C, 0
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		cmp	word ptr dword_2670A, 0C00h
		jge	short loc_1F641
		mov	word_26712, 20h	; ' '
		jmp	short loc_1F657
; ---------------------------------------------------------------------------

loc_1F641:				; CODE XREF: sub_1F3AB+28Cj
		cmp	word ptr dword_2670A, 0C00h
		jle	short loc_1F651
		mov	word_26712, 0FFE0h
		jmp	short loc_1F657
; ---------------------------------------------------------------------------

loc_1F651:				; CODE XREF: sub_1F3AB+29Cj
		mov	word_26712, 0

loc_1F657:				; CODE XREF: sub_1F3AB+294j
					; sub_1F3AB+2A4j
		cmp	word ptr dword_2670A+2,	600h
		jge	short loc_1F667
		mov	word_26714, 10h
		jmp	short loc_1F67D
; ---------------------------------------------------------------------------

loc_1F667:				; CODE XREF: sub_1F3AB+2B2j
		cmp	word ptr dword_2670A+2,	600h
		jle	short loc_1F677
		mov	word_26714, 0FFF0h
		jmp	short loc_1F67D
; ---------------------------------------------------------------------------

loc_1F677:				; CODE XREF: sub_1F3AB+2C2j
		mov	word_26714, 0

loc_1F67D:				; CODE XREF: sub_1F3AB+2BAj
					; sub_1F3AB+2CAj
		push	53CAh
		call	sub_13D32
		call	sub_1F378
		call	sub_1E64E
		cmp	word_2671A, 40h	; '@'
		jl	loc_1F8A5
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		mov	byte_26718, 81h	; ''
		mov	byte_2D057, 12h
		mov	byte_2D03B, 90h	; ''
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_1F6CD
		cmp	ax, 1
		jz	short loc_1F6D2
		cmp	ax, 0FFh
		jz	short loc_1F6D7
		jmp	short loc_1F6E9
; ---------------------------------------------------------------------------

loc_1F6CD:				; CODE XREF: sub_1F3AB+314j
		call	sub_1F111
		jmp	short loc_1F6E9
; ---------------------------------------------------------------------------

loc_1F6D2:				; CODE XREF: sub_1F3AB+319j
		call	sub_1F22A
		jmp	short loc_1F6E9
; ---------------------------------------------------------------------------

loc_1F6D7:				; CODE XREF: sub_1F3AB+31Ej
		inc	byte_2671F
		mov	al, byte_2671F
		and	al, 1
		mov	byte_2671D, al
		mov	word_2671A, 0

loc_1F6E9:				; CODE XREF: sub_1F3AB+320j
					; sub_1F3AB+325j ...
		call	sub_1F378
		cmp	byte_2671F, 0Ah
		jnb	short loc_1F701
		call	sub_1E64E
		or	al, al
		jz	loc_1F8A5
		push	0Ah
		call	sub_19FD8

loc_1F701:				; CODE XREF: sub_1F3AB+346j
		push	large 30384h
		call	sub_1E6F3
		mov	word_26712, 0
		mov	byte_2D057, 3
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_1F72D
		cmp	ax, 1
		jz	short loc_1F732
		cmp	ax, 0FFh
		jz	short loc_1F737
		jmp	short loc_1F73A
; ---------------------------------------------------------------------------

loc_1F72D:				; CODE XREF: sub_1F3AB+374j
		call	sub_1EF87
		jmp	short loc_1F73A
; ---------------------------------------------------------------------------

loc_1F732:				; CODE XREF: sub_1F3AB+379j
		call	sub_1F2F3
		jmp	short loc_1F73A
; ---------------------------------------------------------------------------

loc_1F737:				; CODE XREF: sub_1F3AB+37Ej
		call	sub_1E917

loc_1F73A:				; CODE XREF: sub_1F3AB+380j
					; sub_1F3AB+385j ...
		call	sub_1F378
		cmp	byte_2671F, 0Ch
		jnb	short loc_1F752
		call	sub_1E64E
		or	al, al
		jz	loc_1F8A5
		push	0Ah
		call	sub_19FD8

loc_1F752:				; CODE XREF: sub_1F3AB+397j
		push	large 40000h
		call	sub_1E6F3
		mov	word_26712, 0
		mov	byte_2D057, 3
		mov	byte_23DC2, 3Ch	; '<'
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		cmp	word ptr dword_2670A, 0C00h
		jge	short loc_1F77E
		mov	word_26712, 20h	; ' '
		jmp	short loc_1F794
; ---------------------------------------------------------------------------

loc_1F77E:				; CODE XREF: sub_1F3AB+3C9j
		cmp	word ptr dword_2670A, 0C00h
		jle	short loc_1F78E
		mov	word_26712, 0FFE0h
		jmp	short loc_1F794
; ---------------------------------------------------------------------------

loc_1F78E:				; CODE XREF: sub_1F3AB+3D9j
		mov	word_26712, 0

loc_1F794:				; CODE XREF: sub_1F3AB+3D1j
					; sub_1F3AB+3E1j
		cmp	word ptr dword_2670A+2,	600h
		jge	short loc_1F7A4
		mov	word_26714, 10h
		jmp	short loc_1F7BA
; ---------------------------------------------------------------------------

loc_1F7A4:				; CODE XREF: sub_1F3AB+3EFj
		cmp	word ptr dword_2670A+2,	600h
		jle	short loc_1F7B4
		mov	word_26714, 0FFF0h
		jmp	short loc_1F7BA
; ---------------------------------------------------------------------------

loc_1F7B4:				; CODE XREF: sub_1F3AB+3FFj
		mov	word_26714, 0

loc_1F7BA:				; CODE XREF: sub_1F3AB+3F7j
					; sub_1F3AB+407j
		push	53CAh
		call	sub_13D32
		mov	al, byte_23DC2
		add	al, 3
		mov	byte_23DC2, al
		mov	al, byte_23DC4
		add	al, 0FEh ; 'þ'
		mov	byte_23DC4, al
		mov	byte_266D3, 1
		call	sub_1E64E
		cmp	word_2671A, 40h	; '@'
		jl	loc_1F8A5

loc_1F7E1:				; CODE XREF: sub_1F3AB+233j
		inc	byte_26719
		mov	word_2671A, 0
		mov	byte_2671F, 0
		mov	byte_2671D, 0
		mov	byte_26718, 81h	; ''
		mov	byte_2D057, 4
		jmp	loc_1F8A5
; ---------------------------------------------------------------------------
		mov	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		mov	word ptr dword_266E4+2,	ax
		call	sub_1F17C
		call	sub_1E64E
		or	al, al
		jnz	short loc_1F822
		cmp	word_2671A, 3E8h
		jl	loc_1F8A5

loc_1F822:				; CODE XREF: sub_1F3AB+46Bj
		push	3
		call	sub_15C7C
		inc	byte_26719
		mov	byte_2671F, 0
		cmp	word_2671A, 3E8h
		jge	short loc_1F83D
		mov	byte_2671F, 1

loc_1F83D:				; CODE XREF: sub_1F3AB+48Bj
		mov	word_2671A, 0
		jmp	short loc_1F8A5
; ---------------------------------------------------------------------------
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_1F855
		push	4
		call	sub_15C7C

loc_1F855:				; CODE XREF: sub_1F3AB+4A3j
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_1F8A5
		push	2
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_1F878
		push	28h ; '('
		call	sub_19FD8

loc_1F878:				; CODE XREF: sub_1F3AB+4C6j
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_23DC2, 0
		mov	byte_23DC4, 0
		mov	byte_266D3, 1
		mov	byte_259A2, 0FFh
		jmp	short loc_1F8A5
; ---------------------------------------------------------------------------

loc_1F8A0:				; CODE XREF: sub_1F3AB+20j
		call	sub_1E743
		leave
		retf
sub_1F3AB	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_1F3AB

loc_1F8A5:				; CODE XREF: sub_1F3AB+3Fj
					; sub_1F3AB+73j ...
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax
		call	sub_1EBF3
		push	word_26716
		push	238Ch
		call	sub_19F16
		leave
		retf
; END OF FUNCTION CHUNK	FOR sub_1F3AB
; ---------------------------------------------------------------------------
byte_1F8C0	db 2 dup(0), 1,	0, 2, 0, 3, 0, 0FFh, 0,	0ADh, 0BAh, 0ADh
					; DATA XREF: sub_1F3AB+17Co
		db 0BAh, 0ADh, 0BAh, 0B2h, 0BAh, 0B7h, 0BAh, 46h, 0B9h
		db 91h,	0B9h, 0BDh, 0B9h, 0, 0BAh, 8Ch,	0BAh, 13h, 0BBh
		db 51h,	0BBh, 0A1h, 0BBh, 28h, 0BCh, 88h, 0BCh,	0DEh, 0BCh
		db 72h,	0BDh, 0B5h, 0BDh

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F8EE	proc near		; CODE XREF: sub_1F903:loc_1F949p
		push	bp
		mov	bp, sp
		mov	byte_2A8D3, 0FEh ; 'þ'
		call	sub_13B21
		mov	byte_2A8D3, 2
		call	sub_13B21
		pop	bp
		retn
sub_1F8EE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F903	proc near		; CODE XREF: sub_1FA33+3p

var_2		= word ptr -2

; FUNCTION CHUNK AT 0BFB SIZE 00000007 BYTES

		enter	2, 0
		mov	ax, word_2671A
		mov	[bp+var_2], ax
		mov	cx, 4		; switch 4 cases
		mov	bx, offset byte_1F96A

loc_1F913:				; CODE XREF: sub_1F903+1Bj
		mov	ax, cs:[bx]
		cmp	ax, [bp+var_2]
		jz	short loc_1F922
		add	bx, 2
		loop	loc_1F913
		jmp	short locret_1F967 ; default
; ---------------------------------------------------------------------------

loc_1F922:				; CODE XREF: sub_1F903+16j
		jmp	word ptr cs:[bx+8] ; switch jump
; ---------------------------------------------------------------------------
		mov	word_2A8CE, 1400h
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FD00h
		mov	word ptr dword_2A8C6+2,	ax
		mov	ax, word ptr dword_2670A
		add	ax, 0FF30h
		mov	word ptr dword_2A8C6, ax
		mov	word_2A8D0, 10h
		mov	byte_2A8D2, 0Fh

loc_1F949:				; CODE XREF: sub_1F903+50j
		call	sub_1F8EE
		leave
		retn
; ---------------------------------------------------------------------------
		mov	byte_2A8D2, 9
		jmp	short loc_1F949
; ---------------------------------------------------------------------------
		push	word ptr dword_2A8C6
		push	word ptr dword_2A8C6+2
		call	sub_C696
		mov	byte_25592, 0Fh

locret_1F967:				; CODE XREF: sub_1F903+1Dj
		leave			; default
		retn
sub_1F903	endp ; sp-analysis failed

; ---------------------------------------------------------------------------
		db 0
byte_1F96A	db 30h,	0, 32h,	0, 34h,	0, 40h,	0, 96h,	3 dup(0BEh), 0B9h
					; DATA XREF: sub_1F903+Do
		db 0BEh, 0C5h, 0BEh

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F97A	proc near		; CODE XREF: sub_2026A:loc_20370p
					; sub_2026A:loc_20417p	...
		push	bp
		mov	bp, sp
		cmp	word_2671A, 1
		jnz	short loc_1F994
		mov	ax, word_2D05A
		sub	ax, word ptr dword_2670A
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		mov	word_26712, ax

loc_1F994:				; CODE XREF: sub_1F97A+8j
		mov	ax, word_26712
		add	word ptr dword_2670A, ax
		cmp	word_2671A, 20h	; ' '
		jg	short loc_1F9A9
		mov	al, byte ptr word_237F8
		add	al, 2
		jmp	short loc_1F9AE
; ---------------------------------------------------------------------------

loc_1F9A9:				; CODE XREF: sub_1F97A+26j
		mov	al, byte ptr word_237F8
		add	al, 0FEh ; 'þ'

loc_1F9AE:				; CODE XREF: sub_1F97A+2Dj
		mov	byte ptr word_237F8, al
		cmp	word_2671A, 40h	; '@'
		jnz	short loc_1F9C1
		mov	byte ptr word_237F8, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1F9C1:				; CODE XREF: sub_1F97A+3Cj
		mov	al, 0
		pop	bp
		retn
sub_1F97A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F9C5	proc near		; CODE XREF: sub_2026A+354p
		push	bp
		mov	bp, sp
		cmp	word_2671A, 1
		jnz	short loc_1F9E2
		cmp	word ptr dword_2670A, 0C00h
		jge	short loc_1F9DC
		mov	ax, 20h	; ' '
		jmp	short loc_1F9DF
; ---------------------------------------------------------------------------

loc_1F9DC:				; CODE XREF: sub_1F9C5+10j
		mov	ax, 0FFE0h

loc_1F9DF:				; CODE XREF: sub_1F9C5+15j
		mov	word_26712, ax

loc_1F9E2:				; CODE XREF: sub_1F9C5+8j
		cmp	word_26712, 0
		jge	short loc_1F9F1
		cmp	word ptr dword_2670A, 0C10h
		jge	short loc_1FA00

loc_1F9F1:				; CODE XREF: sub_1F9C5+22j
		cmp	word_26712, 0
		jle	short loc_1FA07
		cmp	word ptr dword_2670A, 0C00h
		jg	short loc_1FA07

loc_1FA00:				; CODE XREF: sub_1F9C5+2Aj
		mov	ax, word_26712
		add	word ptr dword_2670A, ax

loc_1FA07:				; CODE XREF: sub_1F9C5+31j
					; sub_1F9C5+39j
		cmp	word_2671A, 40h	; '@'
		jg	short loc_1FA14
		inc	byte ptr word_237F8
		jmp	short loc_1FA18
; ---------------------------------------------------------------------------

loc_1FA14:				; CODE XREF: sub_1F9C5+47j
		dec	byte ptr word_237F8

loc_1FA18:				; CODE XREF: sub_1F9C5+4Dj
		cmp	word_2671A, 80h	; '€'
		jnz	short loc_1FA2F
		mov	word ptr dword_2670A, 0C00h
		mov	byte ptr word_237F8, 0
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FA2F:				; CODE XREF: sub_1F9C5+59j
		mov	al, 0
		pop	bp
		retn
sub_1F9C5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FA33	proc near		; CODE XREF: sub_1FAAA+3p sub_1FAF7+3p ...
		push	bp
		mov	bp, sp
		call	sub_1F903
		cmp	word_2671A, 8
		jl	short loc_1FA55
		cmp	word_2671A, 8
		jnz	short loc_1FA4E
		mov	byte_26718, 82h	; '‚'
		jmp	short loc_1FA55
; ---------------------------------------------------------------------------

loc_1FA4E:				; CODE XREF: sub_1FA33+12j
		cmp	byte_26718, 20h	; ' '
		jnb	short loc_1FA59

loc_1FA55:				; CODE XREF: sub_1FA33+Bj
					; sub_1FA33+19j
		mov	al, 0
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FA59:				; CODE XREF: sub_1FA33+20j
		cmp	word_2671A, 50h	; 'P'
		jge	short loc_1FA85
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_1FA6E
		push	8
		call	sub_138B2

loc_1FA6E:				; CODE XREF: sub_1FA33+32j
		cmp	byte_266CC, 0
		jz	short loc_1FA7C
		mov	byte_26718, 86h	; '†'
		jmp	short loc_1FA81
; ---------------------------------------------------------------------------

loc_1FA7C:				; CODE XREF: sub_1FA33+40j
		mov	byte_26718, 82h	; '‚'

loc_1FA81:				; CODE XREF: sub_1FA33+47j
		mov	al, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FA85:				; CODE XREF: sub_1FA33+2Bj
		cmp	word_2671A, 50h	; 'P'
		jnz	short loc_1FA95
		mov	byte_26718, 84h	; '„'
		mov	al, 2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FA95:				; CODE XREF: sub_1FA33+57j
		cmp	word_2671A, 90h	; ''
		jge	short loc_1FAA1
		mov	al, 3
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FAA1:				; CODE XREF: sub_1FA33+68j
		mov	byte_26718, 84h	; '„'
		mov	al, 4
		pop	bp
		retn
sub_1FA33	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FAAA	proc near		; CODE XREF: sub_2026A:loc_20326p
		push	bp
		mov	bp, sp
		call	sub_1FA33
		mov	ah, 0
		cmp	ax, 2
		jz	short loc_1FABE
		cmp	ax, 4
		jz	short loc_1FAEA
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FABE:				; CODE XREF: sub_1FAAA+Bj
		mov	byte_266E2, 5
		mov	byte_266E3, 3Eh	; '>'
		mov	byte_266EE, 46h	; 'F'
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 5Ah	; 'Z'
		call	sub_13D52
		mov	byte_266ED, al
		call	word_2D000
		push	9
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FAEA:				; CODE XREF: sub_1FAAA+10j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh
		pop	bp
		retn
sub_1FAAA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FAF7	proc near		; CODE XREF: sub_2026A:loc_2032Bp
		push	bp
		mov	bp, sp
		call	sub_1FA33
		mov	ah, 0
		cmp	ax, 2
		jz	short loc_1FB10
		cmp	ax, 3
		jz	short loc_1FB36
		cmp	ax, 4
		jz	short loc_1FB79
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FB10:				; CODE XREF: sub_1FAF7+Bj
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266F0, 8
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266E4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266E4
		push	ax
		call	sub_1DA8
		add	al, 0C0h ; 'À'
		mov	byte_2D02D, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FB36:				; CODE XREF: sub_1FAF7+10j
		cmp	byte_266CC, 0
		jnz	short loc_1FB84
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 8
		mov	byte_266EE, al
		push	3
		call	sub_13D60
		add	al, 5
		mov	byte_266EF, al
		mov	al, byte_2D02D
		mov	byte_266ED, al
		call	word_2D000
		mov	al, 80h	; '€'
		sub	al, byte_2D02D
		mov	byte_266ED, al
		call	word_2D000
		mov	al, byte_2D02D
		add	al, 7
		mov	byte_2D02D, al
		push	9
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FB79:				; CODE XREF: sub_1FAF7+15j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1FB84:				; CODE XREF: sub_1FAF7+44j
		pop	bp
		retn
sub_1FAF7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FB86	proc near		; CODE XREF: sub_2026A:loc_203CDp
		push	bp
		mov	bp, sp
		call	sub_1FA33
		mov	ah, 0
		cmp	ax, 2
		jz	short loc_1FBA1
		cmp	ax, 3
		jz	short loc_1FBAD
		cmp	ax, 4
		jz	loc_1FC39
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FBA1:				; CODE XREF: sub_1FB86+Bj
		mov	byte_266F2, 86h	; '†'
		mov	byte_2CFF7, 4
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FBAD:				; CODE XREF: sub_1FB86+10j
		cmp	byte_266CC, 0
		jz	loc_1FC44
		mov	byte_266EC, 0
		mov	byte_266E2, 2
		mov	byte_266E3, 3Bh	; ';'
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 2Ah	; '*'
		mov	byte_266EE, al
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	200h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266ED, 0E0h ; 'à'
		call	word_2D002
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 2Ah	; '*'
		mov	byte_266EE, al
		mov	byte_266ED, 0A0h ; ' '
		call	word_2D002
		push	9
		call	sub_138B2
		cmp	byte_266CF, 1
		jnz	short loc_1FC44
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 20h	; ' '
		mov	byte_266EE, 50h	; 'P'
		call	word_2D000
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FC39:				; CODE XREF: sub_1FB86+15j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1FC44:				; CODE XREF: sub_1FB86+2Cj
					; sub_1FB86+97j
		pop	bp
		retn
sub_1FB86	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FC46	proc near		; CODE XREF: sub_2026A:loc_203D2p
		push	bp
		mov	bp, sp
		call	sub_1FA33
		mov	ah, 0
		cmp	ax, 2
		jz	short loc_1FC61
		cmp	ax, 3
		jz	short loc_1FC68
		cmp	ax, 4
		jz	loc_1FD23
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FC61:				; CODE XREF: sub_1FC46+Bj
		mov	byte_2CFF7, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FC68:				; CODE XREF: sub_1FC46+10j
		cmp	byte_266CC, 0
		jz	short loc_1FCE0
		mov	byte_266F2, 81h	; ''
		mov	byte_266EC, 0
		mov	byte_266E2, 2
		mov	byte_266E3, 3Ah	; ':'
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		push	400h
		call	sub_13D76

loc_1FC93:				; CODE XREF: sub_1EA4B:loc_1EA6Bj
		mov	dx, word ptr dword_2670A ; jumptable 0001EA6B case 32792
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	200h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE60h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		mov	byte_266ED, 80h	; '€'
		mov	byte_2CFF8, 0C0h ; 'À'
		call	word_2D002
		mov	byte_266ED, 0
		mov	byte_2CFF8, 40h	; '@'
		call	word_2D002
		push	9
		call	sub_138B2

loc_1FCE0:				; CODE XREF: sub_1FC46+27j
		cmp	byte_266CD, 0
		jnz	short loc_1FD2E
		mov	word_2A8D0, 8
		mov	word_2A8CE, 400h
		mov	byte_2A8D2, 0Eh
		mov	byte_266E2, 1
		mov	ax, word ptr dword_266E4+2
		mov	word ptr dword_2A8C6+2,	ax
		push	1400h
		call	sub_13D76
		add	ax, 200h
		mov	word ptr dword_2A8C6, ax
		mov	byte_266EC, 2Ch	; ','
		mov	byte_266EF, 10h
		mov	byte_266EE, 40h	; '@'
		call	sub_13AB7
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FD23:				; CODE XREF: sub_1FC46+15j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1FD2E:				; CODE XREF: sub_1FC46+9Fj
		pop	bp
		retn
sub_1FC46	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FD30	proc near		; CODE XREF: sub_2026A:loc_20474p
		push	bp
		mov	bp, sp
		push	si
		call	sub_1FA33
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 4
		ja	loc_1FDF1
		add	bx, bx
		jmp	cs:off_1FDF4[bx]

loc_1FD49:				; DATA XREF: seg003:off_1FDF4o
		mov	byte_266E3, 3Eh	; '>'
		mov	byte_266EC, 2Eh	; '.'
		mov	byte_266F2, 0FFh
		mov	byte_266F0, 10h
		mov	byte_266ED, 0
		mov	byte_266EF, 2
		jmp	loc_1FDF1
; ---------------------------------------------------------------------------

loc_1FD6A:				; CODE XREF: sub_1FD30+14j
					; DATA XREF: seg003:C366o
		mov	ax, word_2671A
		and	ax, 0Fh
		cmp	ax, 8
		jnz	short loc_1FDF1
		mov	byte_266E2, 4
		xor	si, si
		mov	byte_266EE, 10h
		jmp	short loc_1FD8F
; ---------------------------------------------------------------------------

loc_1FD83:				; CODE XREF: sub_1FD30+62j
		call	sub_1CFB5
		inc	si
		mov	al, byte_266EE
		add	al, 14h
		mov	byte_266EE, al

loc_1FD8F:				; CODE XREF: sub_1FD30+51j
		cmp	si, 4
		jl	short loc_1FD83
		push	0Fh
		call	sub_138B2
		mov	al, byte_266EF
		add	al, 2
		mov	byte_266EF, al
		mov	al, byte_266F0
		add	al, 0FEh ; 'þ'
		mov	byte_266F0, al
		jmp	short loc_1FDF1
; ---------------------------------------------------------------------------

loc_1FDAD:				; CODE XREF: sub_1FD30+14j
					; DATA XREF: seg003:C368o
		mov	byte_266EC, 30h	; '0'
		mov	byte_266EF, 8
		mov	byte_266F0, 0Ah
		mov	byte_266EE, 20h	; ' '
		mov	byte_266E3, 39h	; '9'
		mov	byte_266ED, 0
		jmp	short loc_1FDF1
; ---------------------------------------------------------------------------

loc_1FDCD:				; CODE XREF: sub_1FD30+14j
					; DATA XREF: seg003:C36Ao
		test	byte ptr word_2671A, 3
		jnz	short loc_1FDF1
		mov	byte_266E2, 4
		call	word_2D000
		push	0Fh
		call	sub_138B2
		jmp	short loc_1FDF1
; ---------------------------------------------------------------------------

loc_1FDE6:				; CODE XREF: sub_1FD30+14j
					; DATA XREF: seg003:C36Co
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh ; CODE	XREF: sub_1CD6E:loc_1CD8Fj

loc_1FDF1:				; CODE XREF: sub_1FD30+Ej
					; sub_1FD30+37j ...
		pop	si
		pop	bp
		retn
sub_1FD30	endp

; ---------------------------------------------------------------------------
off_1FDF4	dw offset loc_1FD49	; DATA XREF: sub_1FD30+14r
		dw offset loc_1FD6A
		dw offset loc_1FDAD
		dw offset loc_1FDCD
		dw offset loc_1FDE6

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FDFE	proc near		; CODE XREF: sub_2026A:loc_20479p
		push	bp
		mov	bp, sp
		call	sub_1FA33
		mov	ah, 0
		cmp	ax, 2
		jz	short loc_1FE17
		cmp	ax, 3
		jz	short loc_1FE45
		cmp	ax, 4
		jz	short loc_1FE5D
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FE17:				; CODE XREF: sub_1FDFE+Bj
		mov	byte_266EE, 50h	; 'P'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 1
		mov	byte_266F0, 6
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266E4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266E4
		push	ax
		call	sub_1DA8
		mov	byte_266ED, al
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FE45:				; CODE XREF: sub_1FDFE+10j
		cmp	byte_266CD, 0
		jnz	short loc_1FE68
		call	word_2D000
		inc	byte_266EF
		push	9
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FE5D:				; CODE XREF: sub_1FDFE+15j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1FE68:				; CODE XREF: sub_1FDFE+4Cj
		pop	bp
		retn
sub_1FDFE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FE6A	proc near		; CODE XREF: sub_2026A:loc_2051Bp
		push	bp
		mov	bp, sp
		call	sub_1FA33
		mov	ah, 0
		cmp	ax, 2
		jz	short loc_1FE83
		cmp	ax, 3
		jz	short loc_1FEA3
		cmp	ax, 4
		jz	short loc_1FED2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FE83:				; CODE XREF: sub_1FE6A+Bj
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 5
		mov	byte_266F0, 0Bh
		mov	byte_266ED, 0
		mov	byte_266EE, 5Ah	; 'Z'
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FEA3:				; CODE XREF: sub_1FE6A+10j
		cmp	byte_266CC, 0
		jnz	short loc_1FEDD
		mov	byte_266E2, 2
		call	word_2D000
		mov	al, 80h	; '€'
		sub	al, byte_266ED
		mov	byte_266ED, al
		call	word_2D000
		mov	al, 78h	; 'x'
		sub	al, byte_266ED
		mov	byte_266ED, al
		push	3
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_1FED2:				; CODE XREF: sub_1FE6A+15j
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_1FEDD:				; CODE XREF: sub_1FE6A+3Ej
		pop	bp
		retn
sub_1FE6A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FEDF	proc near		; CODE XREF: sub_2026A:loc_20520p

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		cmp	word_2671A, 1
		jnz	short loc_1FF2E
		push	1
		call	sub_13D60
		mov	[bp+var_1], al
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_1FF29
; ---------------------------------------------------------------------------

loc_1FEFB:				; CODE XREF: sub_1FEDF+4Dj
		cmp	[bp+var_1], 0
		jnz	short loc_1FF0C
		mov	ax, di
		imul	ax, 180h
		add	ax, 0C0h ; 'À'
		jmp	short loc_1FF1D
; ---------------------------------------------------------------------------

loc_1FF0C:				; CODE XREF: sub_1FEDF+20j
		push	0C0h ; 'À'
		call	sub_13D76
		mov	dx, di
		imul	dx, 180h
		add	dx, 60h	; '`'
		add	ax, dx

loc_1FF1D:				; CODE XREF: sub_1FEDF+2Bj
		mov	[si+2],	ax
		mov	word ptr [si+4], 0
		inc	di
		add	si, 1Ah

loc_1FF29:				; CODE XREF: sub_1FEDF+1Aj
		cmp	di, 10h
		jl	short loc_1FEFB

loc_1FF2E:				; CODE XREF: sub_1FEDF+Bj
		call	sub_1FA33
		mov	ah, 0
		dec	ax
		mov	bx, ax
		cmp	bx, 3
		ja	loc_20044
		add	bx, bx
		jmp	cs:off_20048[bx]

loc_1FF44:				; DATA XREF: seg003:off_20048o
		mov	byte_266E2, 2
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266EF, 5
		mov	byte_266F0, 18h
		mov	byte_266ED, 0C0h ; 'À'
		mov	byte_266E3, 34h	; '4'
		mov	byte_266EE, 7Fh	; ''
		call	word_2D004
		call	word_2D000
		push	3
		call	sub_138B2
		mov	ax, word ptr dword_2598E+2
		sub	ax, word ptr dword_266E4+2
		push	ax
		mov	ax, word ptr dword_2598E
		sub	ax, word ptr dword_266E4
		push	ax
		call	sub_1DA8
		add	al, 0D0h ; 'Ð'
		mov	byte_2D02D, al
		jmp	loc_20044
; ---------------------------------------------------------------------------

loc_1FF93:				; CODE XREF: sub_1FEDF+60j
					; DATA XREF: seg003:C5BAo
		mov	ax, word ptr dword_266E4
		mov	word_2561A, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_2561C, ax
		mov	word_2562A, 40h	; '@'
		mov	word_2562E, 6
		mov	word_25624, 20h	; ' '
		mov	word_25626, 30h	; '0'
		mov	byte_25628, 8
		call	sub_15DBD
		jmp	loc_20044
; ---------------------------------------------------------------------------

loc_1FFC2:				; CODE XREF: sub_1FEDF+60j
					; DATA XREF: seg003:C5BCo
		cmp	byte_266CD, 0
		jnz	short loc_20044
		cmp	byte_266CE, 0
		jnz	short loc_1FFF8
		mov	byte_266E2, 1
		mov	al, byte_2D02D
		mov	byte_266ED, al
		mov	byte_266EC, 2Fh	; '/'
		mov	byte_266EF, 0Ch
		mov	byte_266EE, 20h	; ' '
		mov	byte_266F0, 8
		add	al, 0Ch
		mov	byte_2D02D, al
		call	word_2D000

loc_1FFF8:				; CODE XREF: sub_1FEDF+EFj
		mov	byte_266EE, 80h	; '€'
		mov	byte_266ED, 40h	; '@'
		mov	byte_266E3, 34h	; '4'
		mov	byte_266E2, 2
		mov	word ptr dword_266E4+2,	0
		mov	byte_266EC, 0
		mov	si, 0B204h
		xor	di, di
		jmp	short loc_2002B
; ---------------------------------------------------------------------------

loc_2001E:				; CODE XREF: sub_1FEDF+14Fj
		mov	ax, [si+2]
		mov	word ptr dword_266E4, ax
		call	sub_1CFA2
		inc	di
		add	si, 1Ah

loc_2002B:				; CODE XREF: sub_1FEDF+13Dj
		cmp	di, 10h
		jl	short loc_2001E
		push	3
		call	sub_138B2
		jmp	short loc_20044
; ---------------------------------------------------------------------------

loc_20039:				; CODE XREF: sub_1FEDF+60j
					; DATA XREF: seg003:C5BEo
		mov	word_2671A, 0
		mov	byte_2671D, 0FFh

loc_20044:				; CODE XREF: sub_1FEDF+5Aj
					; sub_1FEDF+B1j ...
		pop	di
		pop	si
		leave
		retn
sub_1FEDF	endp

; ---------------------------------------------------------------------------
off_20048	dw offset loc_1FF44	; DATA XREF: sub_1FEDF+60r
		dw offset loc_1FF93
		dw offset loc_1FFC2
		dw offset loc_20039

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20050	proc near		; CODE XREF: sub_2026A+36Ap
		push	bp
		mov	bp, sp
		mov	byte_26718, 80h	; '€'
		cmp	byte_266CE, 0
		jnz	short loc_200B4
		call	sub_13D52
		mov	byte_266ED, al
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	200h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE60h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 10h
		mov	byte_266E2, 2
		mov	byte_266E3, 4Ch	; 'L'
		push	3Fh ; '?'
		call	sub_13D60
		add	al, 10h
		mov	byte_266EE, al
		call	word_2D000
		push	3
		call	sub_138B2

loc_200B4:				; CODE XREF: sub_20050+Dj
		pop	bp
		retn
sub_20050	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_200B6	proc near		; CODE XREF: sub_2026A+3A7p
		push	bp
		mov	bp, sp
		cmp	byte_266CD, 0
		jnz	loc_2018E
		mov	byte_26718, 86h	; '†'
		mov	byte_266EC, 2Dh	; '-'
		mov	byte_266F0, 9
		mov	byte_266EF, 8
		mov	byte_266EE, 38h	; '8'
		mov	al, byte ptr word_266CA
		add	al, al
		mov	byte_266ED, al
		mov	ax, word_266CA
		and	ax, 1FFh
		cmp	ax, 100h
		jb	short loc_200F6
		mov	al, byte_266ED
		neg	al
		mov	byte_266ED, al

loc_200F6:				; CODE XREF: sub_200B6+36j
		call	word_2D000
		mov	al, byte_266ED
		add	al, 80h	; '€'
		mov	byte_266ED, al
		call	word_2D000
		mov	byte_266EE, 20h	; ' '
		mov	byte_266E2, 5
		mov	byte_266F0, 1
		mov	byte_266EF, 3
		mov	byte_266E3, 39h	; '9'
		push	200h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE60h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		mov	al, byte_2D02D
		mov	ah, 0
		shl	ax, 4
		add	ax, word ptr dword_2670A
		mov	word ptr dword_266E4, ax
		mov	al, byte_2D02C
		mov	byte_266ED, al
		call	word_2D000
		mov	al, byte_2D02D
		mov	ah, 0
		shl	ax, 4
		mov	dx, word ptr dword_2670A
		sub	dx, ax
		mov	word ptr dword_266E4, dx
		mov	al, byte_2D02C
		neg	al
		mov	byte_266ED, al
		call	word_2D000
		mov	al, byte_2D02D
		add	al, 10h
		mov	byte_2D02D, al
		cmp	byte_2D02D, 0B0h ; '°'
		jbe	short loc_2017D
		mov	byte_2D02D, 10h

loc_2017D:				; CODE XREF: sub_200B6+C0j
		mov	al, byte_2D02C
		add	al, 0Bh
		mov	byte_2D02C, al
		push	3
		call	sub_138B2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_2018E:				; CODE XREF: sub_200B6+8j
		mov	byte_26718, 82h	; '‚'
		pop	bp
		retn
sub_200B6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20195	proc near		; CODE XREF: sub_2026A:loc_20616p
		push	bp
		mov	bp, sp
		cmp	byte_266CC, 0
		jz	short loc_201A6
		mov	byte_26718, 86h	; '†'
		jmp	short loc_201AB
; ---------------------------------------------------------------------------

loc_201A6:				; CODE XREF: sub_20195+8j
		mov	byte_26718, 82h	; '‚'

loc_201AB:				; CODE XREF: sub_20195+Fj
		cmp	byte_266CD, 0
		jnz	short loc_20200
		push	1

loc_201B4:				; CODE XREF: sub_1F3AB:loc_1F539j
		call	sub_13D60	; jumptable 0001F539 case 36296
		mov	byte_266E2, al
		push	400h
		call	sub_13D76
		mov	dx, word ptr dword_2670A
		add	dx, 0FE00h
		add	ax, dx
		mov	word ptr dword_266E4, ax
		push	200h
		call	sub_13D76
		mov	dx, word ptr dword_2670A+2
		add	dx, 0FE60h
		add	ax, dx
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266EE, 64h	; 'd'
		call	word_2D000
		push	3
		call	sub_138B2

loc_20200:				; CODE XREF: sub_20195+1Bj
		pop	bp
		retn
sub_20195	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20202	proc near		; CODE XREF: sub_2026A:loc_202B0p
					; sub_2026A:loc_202E8p	...
		push	bp
		mov	bp, sp
		cmp	byte_259EF, 0
		jz	short loc_20220
		cmp	byte ptr word_237F8, 0
		jnz	short loc_20220
		push	large 3000300h
		push	0Ah
		call	sub_1E5D8
		jmp	short loc_20233
; ---------------------------------------------------------------------------

loc_20220:				; CODE XREF: sub_20202+8j sub_20202+Fj
		cmp	byte_26718, 0
		jz	short loc_20233
		cmp	byte ptr word_237F8, 0
		jnz	short loc_20233
		call	sub_1E64E
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_20233:				; CODE XREF: sub_20202+1Cj
					; sub_20202+23j ...
		inc	word_2671A
		mov	al, 0
		pop	bp
		retn
sub_20202	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2023B	proc near		; CODE XREF: sub_2026A+12Dp
					; sub_2026A+1D4p ...
		push	bp
		mov	bp, sp
		cmp	byte_266CE, 0
		jnz	short loc_20268
		mov	byte_266EC, 26h	; '&'
		mov	byte_266EF, 20h	; ' '
		mov	byte_266E3, 4Ch	; 'L'
		mov	byte_266E2, 2
		call	sub_13D52
		mov	byte_266ED, al
		mov	byte_266EE, 70h	; 'p'
		call	word_2D000

loc_20268:				; CODE XREF: sub_2023B+8j
		pop	bp
		retn
sub_2023B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2026A	proc far
		push	bp
		mov	bp, sp
		cmp	byte_256A8, 0
		jz	short loc_20279
		mov	byte_259EF, 20h	; ' '

loc_20279:				; CODE XREF: sub_2026A+8j
		cmp	byte_259EF, 0
		jz	short loc_20284
		dec	byte_259EF

loc_20284:				; CODE XREF: sub_2026A+14j
		mov	ax, word ptr dword_2670A
		add	ax, 0FF30h
		mov	word ptr dword_266E4, ax
		mov	ax, word ptr dword_2670A+2
		add	ax, 0FD00h
		mov	word ptr dword_266E4+2,	ax
		mov	byte_266E2, 1
		mov	al, byte_26719
		mov	ah, 0
		mov	bx, ax
		cmp	bx, 9
		ja	loc_206B1
		add	bx, bx
		jmp	cs:off_206D8[bx]

loc_202B0:				; DATA XREF: seg003:off_206D8o
		call	sub_20202
		mov	word_26716, 490Ch
		cmp	word_2671A, 80h	; '€'
		jle	loc_206B6
		mov	word_26720, 396Ch
		inc	byte_26719
		mov	word_2671A, 0
		push	0Dh
		call	sub_138B2
		mov	byte_2CDCA, 0Fh
		mov	word_255AC, 7E89h
		jmp	loc_206B6
; ---------------------------------------------------------------------------

loc_202E8:				; CODE XREF: sub_2026A+41j
					; DATA XREF: seg003:CC4Ao
		call	sub_20202
		cmp	word_2671A, 40h	; '@'
		jl	loc_206B6
		inc	byte_26719
		mov	byte_2671D, 0
		mov	byte_2671F, 0
		mov	word_2671A, 0
		mov	word_26712, 0
		jmp	loc_206B6
; ---------------------------------------------------------------------------

loc_20311:				; CODE XREF: sub_2026A+41j
					; DATA XREF: seg003:CC4Co
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_20326
		cmp	ax, 1
		jz	short loc_2032B
		cmp	ax, 0FFh
		jz	short loc_20330
		jmp	short loc_20389
; ---------------------------------------------------------------------------

loc_20326:				; CODE XREF: sub_2026A+AEj
		call	sub_1FAAA
		jmp	short loc_20389
; ---------------------------------------------------------------------------

loc_2032B:				; CODE XREF: sub_2026A+B3j
		call	sub_1FAF7
		jmp	short loc_20389
; ---------------------------------------------------------------------------

loc_20330:				; CODE XREF: sub_2026A+B8j
		cmp	word_2671A, 1
		jnz	short loc_20370
		test	byte_2671F, 1
		jz	short loc_20364
		mov	ax, word ptr dword_2598E
		mov	word_2D05A, ax
		cmp	word_2D05A, 200h
		jge	short loc_20354
		mov	word_2D05A, 200h
		jmp	short loc_20370
; ---------------------------------------------------------------------------

loc_20354:				; CODE XREF: sub_2026A+E0j
		cmp	word_2D05A, 1600h
		jle	short loc_20370
		mov	word_2D05A, 1600h
		jmp	short loc_20370
; ---------------------------------------------------------------------------

loc_20364:				; CODE XREF: sub_2026A+D2j
		push	1000h
		call	sub_13D76
		add	ax, 400h
		mov	word_2D05A, ax

loc_20370:				; CODE XREF: sub_2026A+CBj
					; sub_2026A+E8j ...
		call	sub_1F97A
		or	al, al
		jz	short loc_20389
		inc	byte_2671F
		mov	al, byte_2671F
		and	al, 1
		mov	byte_2671D, al
		mov	word_2671A, 0

loc_20389:				; CODE XREF: sub_2026A+BAj
					; sub_2026A+BFj ...
		cmp	byte_2671F, 12h
		jb	short loc_2039A
		cmp	byte_2671D, 0FFh
		jz	short loc_2039A
		call	sub_2023B

loc_2039A:				; CODE XREF: sub_2026A+124j
					; sub_2026A+12Bj
		cmp	byte_2671F, 16h
		jnb	short loc_203AF
		call	sub_20202
		or	al, al
		jz	loc_206B6
		push	64h ; 'd'
		call	sub_19FD8

loc_203AF:				; CODE XREF: sub_2026A+135j
		push	large 319Ch
		jmp	loc_205AA
; ---------------------------------------------------------------------------

loc_203B8:				; CODE XREF: sub_2026A+41j
					; DATA XREF: seg003:CC4Eo
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_203CD
		cmp	ax, 1
		jz	short loc_203D2
		cmp	ax, 0FFh
		jz	short loc_203D7
		jmp	short loc_20430
; ---------------------------------------------------------------------------

loc_203CD:				; CODE XREF: sub_2026A+155j
		call	sub_1FB86
		jmp	short loc_20430
; ---------------------------------------------------------------------------

loc_203D2:				; CODE XREF: sub_2026A+15Aj
		call	sub_1FC46
		jmp	short loc_20430
; ---------------------------------------------------------------------------

loc_203D7:				; CODE XREF: sub_2026A+15Fj
		cmp	word_2671A, 1
		jnz	short loc_20417
		test	byte_2671F, 1
		jz	short loc_2040B
		mov	ax, word ptr dword_2598E
		mov	word_2D05A, ax
		cmp	word_2D05A, 200h
		jge	short loc_203FB
		mov	word_2D05A, 200h
		jmp	short loc_20417
; ---------------------------------------------------------------------------

loc_203FB:				; CODE XREF: sub_2026A+187j
		cmp	word_2D05A, 1600h
		jle	short loc_20417
		mov	word_2D05A, 1600h
		jmp	short loc_20417
; ---------------------------------------------------------------------------

loc_2040B:				; CODE XREF: sub_2026A+179j
		push	1000h
		call	sub_13D76
		add	ax, 400h
		mov	word_2D05A, ax

loc_20417:				; CODE XREF: sub_2026A+172j
					; sub_2026A+18Fj ...
		call	sub_1F97A
		or	al, al
		jz	short loc_20430
		mov	al, byte_2671F
		and	al, 1
		mov	byte_2671D, al
		inc	byte_2671F
		mov	word_2671A, 0

loc_20430:				; CODE XREF: sub_2026A+161j
					; sub_2026A+166j ...
		cmp	byte_2671F, 12h
		jb	short loc_20441
		cmp	byte_2671D, 0FFh
		jz	short loc_20441
		call	sub_2023B

loc_20441:				; CODE XREF: sub_2026A+1CBj
					; sub_2026A+1D2j
		cmp	byte_2671F, 16h
		jnb	short loc_20456
		call	sub_20202
		or	al, al
		jz	loc_206B6
		push	64h ; 'd'
		call	sub_19FD8

loc_20456:				; CODE XREF: sub_2026A+1DCj
		push	large 322C4h
		jmp	loc_205AA
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_20474
		cmp	ax, 1
		jz	short loc_20479
		cmp	ax, 0FFh
		jz	short loc_2047E
		jmp	short loc_204D7
; ---------------------------------------------------------------------------

loc_20474:				; CODE XREF: sub_2026A+1FCj
		call	sub_1FD30
		jmp	short loc_204D7
; ---------------------------------------------------------------------------

loc_20479:				; CODE XREF: sub_2026A+201j
		call	sub_1FDFE
		jmp	short loc_204D7
; ---------------------------------------------------------------------------

loc_2047E:				; CODE XREF: sub_2026A+206j
		cmp	word_2671A, 1
		jnz	short loc_204BE
		test	byte_2671F, 1
		jz	short loc_204B2
		mov	ax, word ptr dword_2598E
		mov	word_2D05A, ax
		cmp	word_2D05A, 200h
		jge	short loc_204A2
		mov	word_2D05A, 200h
		jmp	short loc_204BE
; ---------------------------------------------------------------------------

loc_204A2:				; CODE XREF: sub_2026A+22Ej
		cmp	word_2D05A, 1600h
		jle	short loc_204BE
		mov	word_2D05A, 1600h
		jmp	short loc_204BE
; ---------------------------------------------------------------------------

loc_204B2:				; CODE XREF: sub_2026A+220j
		push	1000h
		call	sub_13D76
		add	ax, 400h
		mov	word_2D05A, ax

loc_204BE:				; CODE XREF: sub_2026A+219j
					; sub_2026A+236j ...
		call	sub_1F97A
		or	al, al
		jz	short loc_204D7
		mov	al, byte_2671F
		and	al, 1
		mov	byte_2671D, al
		inc	byte_2671F
		mov	word_2671A, 0

loc_204D7:				; CODE XREF: sub_2026A+208j
					; sub_2026A+20Dj ...
		cmp	byte_2671F, 12h
		jb	short loc_204E8
		cmp	byte_2671D, 0FFh
		jz	short loc_204E8
		call	sub_2023B

loc_204E8:				; CODE XREF: sub_2026A+272j
					; sub_2026A+279j
		cmp	byte_2671F, 16h
		jnb	short loc_204FD
		call	sub_20202
		or	al, al
		jz	loc_206B6
		push	64h ; 'd'
		call	sub_19FD8

loc_204FD:				; CODE XREF: sub_2026A+283j
		push	large 3157Ch
		jmp	loc_205AA
; ---------------------------------------------------------------------------
		mov	al, byte_2671D
		mov	ah, 0
		or	ax, ax
		jz	short loc_2051B
		cmp	ax, 1
		jz	short loc_20520
		cmp	ax, 0FFh
		jz	short loc_20525
		jmp	short loc_2057E
; ---------------------------------------------------------------------------

loc_2051B:				; CODE XREF: sub_2026A+2A3j
		call	sub_1FE6A
		jmp	short loc_2057E
; ---------------------------------------------------------------------------

loc_20520:				; CODE XREF: sub_2026A+2A8j
		call	sub_1FEDF
		jmp	short loc_2057E
; ---------------------------------------------------------------------------

loc_20525:				; CODE XREF: sub_2026A+2ADj
		cmp	word_2671A, 1
		jnz	short loc_20565
		test	byte_2671F, 1
		jz	short loc_20559
		mov	ax, word ptr dword_2598E
		mov	word_2D05A, ax
		cmp	word_2D05A, 200h
		jge	short loc_20549
		mov	word_2D05A, 200h
		jmp	short loc_20565
; ---------------------------------------------------------------------------

loc_20549:				; CODE XREF: sub_2026A+2D5j
		cmp	word_2D05A, 1600h
		jle	short loc_20565
		mov	word_2D05A, 1600h
		jmp	short loc_20565
; ---------------------------------------------------------------------------

loc_20559:				; CODE XREF: sub_2026A+2C7j
		push	1000h
		call	sub_13D76
		add	ax, 400h
		mov	word_2D05A, ax

loc_20565:				; CODE XREF: sub_2026A+2C0j
					; sub_2026A+2DDj ...
		call	sub_1F97A
		or	al, al
		jz	short loc_2057E
		mov	al, byte_2671F
		and	al, 1
		mov	byte_2671D, al
		inc	byte_2671F
		mov	word_2671A, 0

loc_2057E:				; CODE XREF: sub_2026A+2AFj
					; sub_2026A+2B4j ...
		cmp	byte_2671F, 12h
		jb	short loc_2058F
		cmp	byte_2671D, 0FFh
		jz	short loc_2058F
		call	sub_2023B

loc_2058F:				; CODE XREF: sub_2026A+319j
					; sub_2026A+320j
		cmp	byte_2671F, 16h
		jnb	short loc_205A4
		call	sub_20202
		or	al, al
		jz	loc_206B6
		push	64h ; 'd'
		call	sub_19FD8

loc_205A4:				; CODE XREF: sub_2026A+32Aj
		push	large 30BB8h

loc_205AA:				; CODE XREF: sub_2026A+14Bj
					; sub_2026A+1F2j ...
		call	sub_1E6F3
		mov	byte_2671D, 0FFh
		mov	word_2D05A, 0C00h
		jmp	loc_206B6
; ---------------------------------------------------------------------------
		call	sub_20202
		call	sub_1F9C5
		or	al, al
		jz	loc_206B6
		inc	byte_26719
		mov	word_2671A, 20h	; ' '
		jmp	loc_206B6
; ---------------------------------------------------------------------------
		call	sub_20050
		cmp	word_2671A, 5DCh
		jge	short loc_205ED
		call	sub_20202
		or	al, al
		jz	loc_206B6
		push	64h ; 'd'
		call	sub_19FD8

loc_205ED:				; CODE XREF: sub_2026A+373j
		push	large 40000h
		call	sub_1E6F3
		mov	byte_2671D, 0FFh
		mov	word_2D05A, 0C00h
		mov	byte_2D02D, 10h
		jmp	loc_206B6
; ---------------------------------------------------------------------------
		cmp	word_2671A, 0BB8h
		jg	short loc_20616
		call	sub_200B6
		jmp	short loc_20619
; ---------------------------------------------------------------------------

loc_20616:				; CODE XREF: sub_2026A+3A5j
		call	sub_20195

loc_20619:				; CODE XREF: sub_2026A+3AAj
		call	sub_20202
		or	al, al
		jnz	short loc_2062A
		cmp	word_2671A, 1388h
		jl	loc_206B6

loc_2062A:				; CODE XREF: sub_2026A+3B4j
		push	1
		call	sub_15C7C
		inc	byte_26719
		cmp	word_2671A, 1388h
		jge	short loc_20642
		mov	byte_2671F, 1
		jmp	short loc_20647
; ---------------------------------------------------------------------------

loc_20642:				; CODE XREF: sub_2026A+3CFj
		mov	byte_2671F, 0

loc_20647:				; CODE XREF: sub_2026A+3D6j
		mov	word_2671A, 0
		mov	byte_2671D, 0
		mov	word_216E4, 64h	; 'd'
		mov	byte_266D3, 1
		jmp	short loc_206B6
; ---------------------------------------------------------------------------
		inc	word_2671A
		cmp	word_2671A, 10h
		jnz	short loc_2066F
		push	4
		call	sub_15C7C

loc_2066F:				; CODE XREF: sub_2026A+3FEj
		cmp	word_2671A, 20h	; ' '
		jnz	short loc_206B6
		push	3
		call	sub_15CFC
		mov	byte_26719, 0FEh ; 'þ'
		mov	al, byte_2671F
		mov	byte_2CFF9, al
		cmp	byte_2671F, 0
		jz	short loc_20693
		push	0C8h ; 'È'
		call	sub_19FD8

loc_20693:				; CODE XREF: sub_2026A+421j
		mov	byte_26718, 4
		mov	word_2671A, 0
		push	0Ch
		call	sub_138B2
		mov	byte_266D3, 1
		mov	byte_259A2, 0FFh
		jmp	short loc_206B6
; ---------------------------------------------------------------------------

loc_206B1:				; CODE XREF: sub_2026A+3Bj
		call	sub_1E743
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_206B6:				; CODE XREF: sub_2026A+55j
					; sub_2026A+7Bj ...
		cmp	byte ptr word_237F8, 0
		jnz	short loc_206C9
		mov	ax, word ptr dword_2670A
		mov	word_25982, ax
		mov	ax, word ptr dword_2670A+2
		mov	word_25984, ax

loc_206C9:				; CODE XREF: sub_2026A+451j
		call	sub_15DE8
		push	word_26716
		push	490Ch
		call	sub_19F16
		pop	bp
		retf
sub_2026A	endp

; ---------------------------------------------------------------------------
off_206D8	dw offset loc_202B0	; DATA XREF: sub_2026A+41r
		dw offset loc_202E8
		dw offset loc_20311
		dw offset loc_203B8
seg003		ends

; ---------------------------------------------------------------------------
; ===========================================================================

; Segment type:	Pure code
seg004		segment	byte public 'CODE' use16
		assume cs:seg004
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing
		iret
; ---------------------------------------------------------------------------
		db 0C9h, 76h, 0CAh, 2Bh, 0CBh, 44h, 0CBh, 79h, 0CBh, 0CFh
		db 0CBh

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; string::string(string	const &)
@string@$bctr$qmx6string proc far	; CODE XREF: xmsg::xmsg(string &)+52P
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
		mov	bx, 0A41Dh
		call	far ptr	___InitExceptBlocks
		mov	ax, word ptr [bp+arg_0]
		or	ax, word ptr [bp+arg_0+2]
		jnz	short loc_2071B
		mov	ax, 4
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jz	short loc_20735

loc_2071B:				; CODE XREF: string::string(string &)+19j
		les	bx, [bp+arg_4]
		mov	dx, es:[bx+2]
		mov	ax, es:[bx]
		les	bx, [bp+arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax
		les	bx, es:[bx]
		inc	word ptr es:[bx]

loc_20735:				; CODE XREF: string::string(string &)+2Dj
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
byte_2075B	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah
					; DATA XREF: seg000:A415o
		db 0Dh dup(0), 2, 0, 2,	0, 23h,	0A4h
		dw seg seg000
		db 5, 0, 3Eh, 0, 78h, 61h, 2 dup(6Ch), 6Fh, 63h, 2 dup(0)
		db 0BDh, 0
		dw seg seg004
		db 2 dup(0), 3,	0Dh dup(0), 4, 0, 3, 0,	26h, 0,	2 dup(0FFh)
		db 3, 0, 2Ch, 0, 30h, 0Dh dup(0), 1, 0,	1, 0, 2Ah, 6Bh
		dw seg seg000
		db 5, 0, 34h, 0, 78h, 6Dh, 73h,	67h, 0Eh dup(0)

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; int __cdecl __far string__string(__int32, char *s)
@string@$bctr$qnxc proc	far		; CODE XREF: string::contains(char *)+25P
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
		mov	bx, 0A48Fh
		call	far ptr	___InitExceptBlocks
		mov	ax, word ptr [bp+arg_0]
		or	ax, word ptr [bp+arg_0+2]
		jnz	short loc_20804
		mov	ax, 4
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jz	short loc_20878

loc_20804:				; CODE XREF: string::string(char *)+19j
		mov	ax, 0Ch
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+var_4+2], dx
		mov	word ptr [bp+var_4], ax
		or	ax, dx
		jz	short loc_20868
		mov	[bp+var_16], 0Eh
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, word ptr [bp+src]
		or	ax, word ptr [bp+src+2]
		jz	short loc_2083A
		push	word ptr [bp+src+2]
		push	word ptr [bp+src] ; s
		call	_strlen
		pop	cx
		pop	cx
		jmp	short loc_2083C
; ---------------------------------------------------------------------------

loc_2083A:				; CODE XREF: string::string(char *)+54j
		xor	ax, ax

loc_2083C:				; CODE XREF: string::string(char *)+63j
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

loc_20868:				; CODE XREF: string::string(char *)+41j
		mov	dx, word ptr [bp+var_4+2]
		mov	ax, word ptr [bp+var_4]
		les	bx, [bp+arg_0]
		mov	es:[bx+2], dx
		mov	es:[bx], ax

loc_20878:				; CODE XREF: string::string(char *)+2Dj
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
		db 4, 0, 90h, 20h, 0Ah,	0, 9Dh,	2
		dw seg seg004
aTstringref	db 'TStringRef *',0
byte_208B5	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h
					; DATA XREF: seg000:A479o
		db 0Dh dup(0), 2, 0, 2,	0, 0A5h, 0A4h
		dw seg seg000
		db 5, 0, 4Ah, 0
aStringLengther	db 'string::lengtherror',0
		dd byte_20945
		db 2 dup(0), 3,	0Dh dup(0)
byte_20903	db 6, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 2Eh, 0, 3Ah
					; DATA XREF: seg000:A475o
		db 0Dh dup(0), 2, 0, 2,	0, 0F2h, 0A4h
		dw seg seg000
		db 5, 0, 3Eh, 0, 78h, 61h, 2 dup(6Ch), 6Fh, 63h, 2 dup(0)
		db 65h,	2
		dw seg seg004
		db 2 dup(0), 3,	0Dh dup(0)
byte_20945	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Ch, 0, 30h
					; DATA XREF: seg004:020Fo
		db 0Dh dup(0), 1, 0, 1,	0, 2Ah,	6Bh
		dw seg seg000
		db 5, 0, 34h, 0, 78h, 6Dh, 73h,	67h, 0Eh dup(0), 0Ch, 0
		db 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 32h, 0, 3Eh, 0Dh dup(0)
		db 1, 0, 1, 0, 0B4h, 6
		dw seg seg004
		db 5, 0, 42h, 0, 54h, 53h, 74h,	72h, 69h, 6Eh, 67h, 52h
		db 65h,	66h, 2 dup(0), 0E3h, 2
		dw seg seg004
		db 2 dup(0), 3,	0Dh dup(0), 2, 0, 3, 0,	1Ah, 0,	2 dup(0FFh)
		db 1, 0, 26h, 0, 2Ah, 0Dh dup(0), 54h, 52h, 65h, 66h, 65h
		db 72h,	65h, 6Eh, 63h, 65h, 0Ah	dup(0)

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

; int __cdecl __far string___string(void (*driver)(void), char)
@string@$bdtr$qv proc far		; CODE XREF: string::contains(char *)+45P
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
		mov	bx, 0A548h
		call	far ptr	___InitExceptBlocks
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	ax, word ptr [bp+driver]
		or	ax, word ptr [bp+driver+2]
		jz	short loc_20A69
		les	bx, [bp+driver]
		les	bx, es:[bx]
		dec	word ptr es:[bx]
		mov	ax, es:[bx]
		or	ax, ax
		jnz	short loc_20A56
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
		call	near ptr sub_20D94
		add	sp, 6

loc_20A56:				; CODE XREF: string::~string(void)+3Bj
		test	[bp+arg_4], 1
		jz	short loc_20A69
		push	word ptr [bp+driver+2]
		push	word ptr [bp+driver] ; driver
		call	far ptr	_registerbgidriver
		pop	cx
		pop	cx

loc_20A69:				; CODE XREF: string::~string(void)+2Bj
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
		mov	bx, 0A57Ch
		call	far ptr	___InitExceptBlocks
		mov	ax, [bp+arg_4]
		mov	[bp+var_28], ax
		les	bx, [bp+arg_0]
		les	bx, es:[bx]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+var_28]
		jbe	short loc_20AA4
		mov	ax, 1
		jmp	short loc_20AA6
; ---------------------------------------------------------------------------

loc_20AA4:				; CODE XREF: string::assert_element(uint)+26j
		xor	ax, ax

loc_20AA6:				; CODE XREF: string::assert_element(uint)+2Bj
		or	ax, ax
		jnz	short loc_20B27
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, 5
		push	ax		; int
		mov	ax, seg	seg000
		push	ax		; int
		mov	ax, 0A66Eh
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		mov	[bp+var_1A], 6
		push	ds
		mov	ax, 29A8h
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
		mov	ax, 0C06h
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

loc_20B27:				; CODE XREF: string::assert_element(uint)+31j
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
		mov	bx, 0A5C0h
		call	far ptr	___InitExceptBlocks
		mov	ax, [bp+arg_4]
		mov	[bp+var_28], ax
		les	bx, [bp+arg_0]
		les	bx, es:[bx]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+var_28]
		jb	short loc_20B62
		mov	ax, 1
		jmp	short loc_20B64
; ---------------------------------------------------------------------------

loc_20B62:				; CODE XREF: string::assert_index(uint)+26j
		xor	ax, ax

loc_20B64:				; CODE XREF: string::assert_index(uint)+2Bj
		or	ax, ax
		jnz	short loc_20BE5
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, 5
		push	ax		; int
		mov	ax, seg	seg000
		push	ax		; int
		mov	ax, 0A66Eh
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		mov	[bp+var_1A], 6
		push	ds
		mov	ax, 29C6h
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
		mov	ax, 0C06h
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

loc_20BE5:				; CODE XREF: string::assert_index(uint)+31j
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
		mov	bx, 0A604h
		call	far ptr	___InitExceptBlocks
		mov	ax, [bp+arg_4]
		mov	[bp+var_28], ax
		les	bx, [bp+arg_0]
		mov	ax, es:[bx+6]
		cmp	ax, [bp+var_28]
		jbe	short loc_20C1D
		mov	ax, 1
		jmp	short loc_20C1F
; ---------------------------------------------------------------------------

loc_20C1D:				; CODE XREF: TSubString::assert_element(uint)+23j
		xor	ax, ax

loc_20C1F:				; CODE XREF: TSubString::assert_element(uint)+28j
		or	ax, ax
		jnz	short loc_20CA0
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		push	ax		; int
		push	ax		; int
		mov	ax, 5
		push	ax		; int
		mov	ax, seg	seg000
		push	ax		; int
		mov	ax, 0A66Eh
		push	ax		; int
		xor	ax, ax
		push	ax		; int
		push	ax		; int
		mov	[bp+var_1A], 6
		push	ds
		mov	ax, 29E4h
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

loc_20C93:				; jumptable 0001EA6B case 56171
		push	cs
		mov	ax, 0C06h
		push	ax		; int
		call	@_ThrowException$qnvt1t1t1uiuiuinuc ; _ThrowException(void *,void *,void *,void	*,uint,uint,uint,uchar *)
		add	sp, 1Ah

loc_20CA0:				; CODE XREF: TSubString::assert_element(uint)+2Ej
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
@TStringRef@$bctr$qnxcuit1uiui proc far	; CODE XREF: string::string(char *)+76p

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
		jnz	short loc_20CD2
		mov	ax, 0Ch
		push	ax
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jnz	short loc_20CD2
		jmp	loc_20D78
; ---------------------------------------------------------------------------

loc_20CD2:				; CODE XREF: TStringRef::TStringRef(char *,uint,char *,uint,uint)+Bj
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
		call	near ptr sub_20F2C
		pop	cx
		les	bx, [bp+arg_0]
		mov	es:[bx+8], ax
		mov	ax, es:[bx+8]
		inc	ax
		push	ax
		call	sub_51C6
		pop	cx
		les	bx, [bp+arg_0]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short loc_20D2C
		push	ds
		mov	ax, 26FEh
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

loc_20D2C:				; CODE XREF: TStringRef::TStringRef(char *,uint,char *,uint,uint)+70j
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

loc_20D78:				; CODE XREF: TStringRef::TStringRef(char *,uint,char *,uint,uint)+21j
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

; int __cdecl __far sub_20D94(void (*driver)(void), char)
sub_20D94	proc far		; CODE XREF: string::~string(void)+5Fp

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
		mov	bx, 0A61Eh
		call	far ptr	___InitExceptBlocks
		call	@__RefDestructorCount$qv ; __RefDestructorCount(void)
		mov	bx, ax
		mov	es, dx
		sub	word ptr es:[bx], 1
		sbb	word ptr es:[bx+2], 0
		mov	ax, word ptr [bp+driver]
		or	ax, word ptr [bp+driver+2]
		jz	short loc_20DE6
		les	bx, [bp+driver]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	sub_5093
		pop	cx
		pop	cx
		test	[bp+arg_4], 1
		jz	short loc_20DE6
		push	word ptr [bp+driver+2]
		push	word ptr [bp+driver] ; driver
		call	far ptr	_registerbgidriver
		pop	cx
		pop	cx

loc_20DE6:				; CODE XREF: sub_20D94+2Bj
					; sub_20D94+43j
		push	[bp+var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
sub_20D94	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; TStringRef::reserve(unsigned int)
@TStringRef@reserve$qui:
		sub	sp, 20h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A630h
		call	far ptr	___InitExceptBlocks
		les	bx, [bp+6]
		or	word ptr es:[bx+0Ah], 1
		mov	ax, [bp+0Ah]
		inc	ax
		push	ax
		nop
		push	cs
		call	near ptr sub_20F2C
		pop	cx
		mov	[bp-20h], ax
		les	bx, [bp+6]
		mov	ax, es:[bx+8]
		sub	ax, [bp-20h]
		cmp	ax, word_23CE6
		jbe	short loc_20E54
		mov	ax, [bp-20h]
		inc	ax
		push	ax
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	sub_532D
		add	sp, 6
		les	bx, [bp+6]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, [bp-20h]
		mov	es:[bx+8], ax

loc_20E54:				; CODE XREF: seg004:074Bj
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
		mov	bx, 0A63Ah
		call	far ptr	___InitExceptBlocks
		les	bx, [bp+6]
		push	word ptr es:[bx+6]
		nop
		push	cs
		call	near ptr sub_20F2C
		pop	cx
		mov	[bp-20h], ax
		les	bx, [bp+6]
		mov	ax, es:[bx+8]
		sub	ax, [bp-20h]
		cmp	ax, word_23CE6
		jbe	short loc_20EBC
		mov	ax, [bp-20h]
		inc	ax
		push	ax
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	sub_532D
		add	sp, 6
		les	bx, [bp+6]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, [bp-20h]
		mov	es:[bx+8], ax

loc_20EBC:				; CODE XREF: seg004:07B3j
		push	word ptr [bp-1Eh]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

sub_20ECA	proc far		; CODE XREF: seg004:08CBp

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
		mov	bx, 0A64Ch
		call	far ptr	___InitExceptBlocks
		les	bx, [bp+arg_0]
		mov	ax, [bp+arg_4]
		mov	es:[bx+8], ax
		mov	ax, es:[bx+8]
		inc	ax
		push	ax
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	sub_532D
		add	sp, 6
		les	bx, [bp+arg_0]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short loc_20F1E
		push	ds
		mov	ax, 26FEh
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

loc_20F1E:				; CODE XREF: sub_20ECA+46j
		push	[bp+var_1E]
		call	___ExitExceptBlocks
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
sub_20ECA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

sub_20F2C	proc far		; CODE XREF: TStringRef::TStringRef(char *,uint,char *,uint,uint)+46p
					; seg004:0736p	...

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
		mov	bx, 0A656h
		call	far ptr	___InitExceptBlocks
		mov	ax, word_23CE2
		mov	[bp+var_20], ax
		mov	cx, word_23CE4
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
sub_20F2C	endp

; ---------------------------------------------------------------------------
		push	bp
		mov	bp, sp

; TStringRef::splice(unsigned int, unsigned int, char const *, unsigned	int)
@TStringRef@splice$quiuinxcui:
		sub	sp, 26h
		push	si
		push	di
		mov	ax, seg	seg000
		mov	bx, 0A668h
		call	far ptr	___InitExceptBlocks
		les	bx, [bp+6]
		mov	ax, es:[bx+6]
		add	ax, [bp+12h]
		sub	ax, [bp+0Ch]
		mov	[bp-24h], ax
		push	ax
		push	cs
		call	near ptr sub_20F2C
		pop	cx
		mov	[bp-26h], ax
		les	bx, [bp+6]
		mov	ax, es:[bx+8]
		cmp	ax, [bp-26h]
		jnb	short loc_20FB3
		push	word ptr [bp-26h]
		push	word ptr [bp+8]
		push	bx
		push	cs
		call	near ptr sub_20ECA
		add	sp, 6
		jmp	short loc_21022
; ---------------------------------------------------------------------------

loc_20FB3:				; CODE XREF: seg004:08C1j
		les	bx, [bp+6]
		mov	ax, es:[bx+8]
		sub	ax, [bp-26h]
		cmp	ax, word_23CE6
		jbe	short loc_21022
		test	byte ptr es:[bx+0Ah], 1
		jnz	short loc_21022
		mov	ax, [bp-26h]
		inc	ax
		push	ax
		call	sub_51C6
		pop	cx
		mov	[bp-20h], dx
		mov	[bp-22h], ax
		les	bx, [bp+6]
		mov	ax, es:[bx+2]
		or	ax, es:[bx+4]
		jnz	short loc_20FF4
		push	ds
		mov	ax, 26FEh
		push	ax
		call	@xalloc@raise$qv ; xalloc::raise(void)
		pop	cx
		pop	cx

loc_20FF4:				; CODE XREF: seg004:0906j
		cmp	word ptr [bp+0Ah], 0
		jz	short loc_21016
		push	word ptr [bp+0Ah]
		les	bx, [bp+6]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		push	word ptr [bp-20h]
		push	word ptr [bp-22h]
		call	_memcpy
		add	sp, 0Ah

loc_21016:				; CODE XREF: seg004:0918j
		les	bx, [bp+6]
		mov	ax, [bp-26h]
		mov	es:[bx+8], ax
		jmp	short loc_21033
; ---------------------------------------------------------------------------

loc_21022:				; CODE XREF: seg004:08D1j seg004:08E1j ...
		les	bx, [bp+6]
		mov	dx, es:[bx+4]
		mov	ax, es:[bx+2]
		mov	[bp-20h], dx
		mov	[bp-22h], ax

loc_21033:				; CODE XREF: seg004:0940j
		les	bx, [bp+6]
		mov	dx, es:[bx+4]
		mov	ax, es:[bx+2]
		cmp	dx, [bp-20h]
		jnz	short loc_21050
		cmp	ax, [bp-22h]
		jnz	short loc_21050
		mov	ax, [bp+12h]
		cmp	ax, [bp+0Ch]
		jz	short loc_21082

loc_21050:				; CODE XREF: seg004:0961j seg004:0966j
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

loc_21082:				; CODE XREF: seg004:096Ej
		cmp	word ptr [bp+12h], 0
		jz	short loc_210C6
		mov	ax, [bp+0Eh]
		or	ax, [bp+10h]
		jz	short loc_210AD
		push	word ptr [bp+12h]
		push	word ptr [bp+10h]
		push	word ptr [bp+0Eh]
		mov	ax, [bp-22h]
		add	ax, [bp+0Ah]
		push	word ptr [bp-20h]
		push	ax
		call	_memmove
		add	sp, 0Ah
		jmp	short loc_210C6
; ---------------------------------------------------------------------------

loc_210AD:				; CODE XREF: seg004:09AEj
		push	word ptr [bp+12h]
		mov	ax, 20h	; ' '
		push	ax
		mov	ax, [bp-22h]
		add	ax, [bp+0Ah]
		push	word ptr [bp-20h]
		push	ax
		call	_memset
		add	sp, 8

loc_210C6:				; CODE XREF: seg004:09A6j seg004:09CBj
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
		jnz	short loc_210F8
		cmp	ax, [bp-22h]
		jz	short loc_2111B

loc_210F8:				; CODE XREF: seg004:0A11j
		les	bx, [bp+6]
		push	word ptr es:[bx+4]
		push	word ptr es:[bx+2]
		call	sub_5093
		pop	cx
		pop	cx
		les	bx, [bp+6]
		mov	dx, [bp-20h]
		mov	ax, [bp-22h]
		mov	es:[bx+4], dx
		mov	es:[bx+2], ax

loc_2111B:				; CODE XREF: seg004:0A16j
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
		mov	ax, word_23CDC
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_23CDC, ax
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
		mov	ax, word_23CDE
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_23CDE, ax
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
		mov	ax, word_23CE0
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_23CE0, ax
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
		mov	ax, word_23CE2
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_23CE2, ax
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
		mov	ax, word_23CE4
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_23CE4, ax
		cmp	word_23CE4, 0
		jnz	short loc_211BE
		mov	word_23CE4, 1

loc_211BE:				; CODE XREF: seg004:0AD6j
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
		mov	ax, word_23CE6
		mov	[bp-2],	ax
		mov	ax, [bp+6]
		mov	word_23CE6, ax
		mov	ax, [bp-2]
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
; ---------------------------------------------------------------------------
byte_211E4	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h
					; DATA XREF: seg000:A644o seg000:A660o
		db 0Dh dup(0), 2, 0, 2,	0, 0A3h, 0A6h
		dw seg seg000
		db 5, 0, 4Ah, 0, 73h, 74h, 72h,	69h, 6Eh, 67h, 2 dup(3Ah)
		db 6Ch,	65h, 6Eh, 67h, 74h, 68h, 65h, 2	dup(72h)
byte_2121B	db 6Fh,	72h, 0,	94h, 0Bh
		dw seg seg004
		dw 0
		db 3, 0Dh dup(0), 6, 0,	3, 0, 26h, 0, 2	dup(0FFh), 7, 0
		db 2Eh,	0, 3Ah,	0Dh dup(0), 2, 0, 2, 0,	0F0h, 0A6h
		dw seg seg000
		db 5, 0, 3Eh, 0, 78h, 61h, 2 dup(6Ch), 6Fh, 63h, 2 dup(0)
		db 94h,	0Bh
		dw seg seg004
byte_21264	db 2 dup(0), 3,	0Dh dup(0), 4, 0, 3, 0,	26h, 0,	2 dup(0FFh)
		db 3, 0, 2Ch, 0, 30h, 0Dh dup(0), 1, 0,	1, 0, 2Ah, 6Bh
		dw seg seg000
		db 5, 0, 34h, 0, 78h, 6Dh, 73h,	67h, 0Eh dup(0), 4, 0
		db 3, 0, 26h, 0, 2 dup(0FFh), 3, 0, 2Eh, 0, 32h, 0Dh dup(0)
		db 1, 0, 1, 0, 11h, 3
		dw seg seg004
		db 5, 0, 36h, 0, 73h, 74h, 72h,	69h, 6Eh, 67h, 0Eh dup(0)
byte_212E6	db 4, 0, 3, 0, 26h, 0, 2 dup(0FFh), 7, 0, 3Ah, 0, 46h
					; DATA XREF: seg000:A628o
		db 0Dh dup(0), 2, 0, 2,	0, 3Dh,	0A7h
		dw seg seg000
		db 5, 0, 4Ah, 0
aStringOutofran	db 'string::outofrange',0
		db 0
		dd byte_21264+10h
		db 2 dup(0), 3,	19h dup(0)
seg004		ends
