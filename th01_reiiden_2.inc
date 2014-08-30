; (included from th01_reiiden.asm, don't assemble directly)

; ===========================================================================

; Segment type:	Pure code
seg028		segment	byte public 'CODE' use16
		assume cs:seg028
		;org 0Fh
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B03F	proc far

var_C8		= word ptr -0C8h
var_C6		= word ptr -0C6h
var_C4		= word ptr -0C4h
var_C2		= word ptr -0C2h
var_C0		= word ptr -0C0h
var_BE		= word ptr -0BEh
var_BC		= word ptr -0BCh
var_BA		= word ptr -0BAh
var_B8		= word ptr -0B8h
var_B6		= word ptr -0B6h
var_B4		= word ptr -0B4h
var_B2		= word ptr -0B2h
var_B0		= word ptr -0B0h
var_AE		= word ptr -0AEh
var_AC		= word ptr -0ACh
var_AA		= word ptr -0AAh
var_A8		= word ptr -0A8h
var_A6		= word ptr -0A6h
var_A4		= word ptr -0A4h
var_A2		= word ptr -0A2h
var_A0		= word ptr -0A0h
var_9E		= word ptr -9Eh
var_9C		= word ptr -9Ch
var_9A		= word ptr -9Ah
var_98		= byte ptr -98h
var_97		= byte ptr -97h
var_96		= word ptr -96h
var_94		= word ptr -94h
var_92		= word ptr -92h
var_90		= word ptr -90h
var_8E		= word ptr -8Eh
var_8C		= word ptr -8Ch
var_8A		= word ptr -8Ah
var_88		= word ptr -88h
var_86		= word ptr -86h
var_84		= word ptr -84h
var_82		= word ptr -82h
var_80		= word ptr -80h
var_7E		= word ptr -7Eh
var_7C		= word ptr -7Ch
var_7A		= word ptr -7Ah
var_78		= word ptr -78h
var_76		= word ptr -76h
var_74		= word ptr -74h
var_72		= word ptr -72h
var_70		= word ptr -70h
var_6E		= word ptr -6Eh
var_6C		= word ptr -6Ch
var_6A		= word ptr -6Ah
var_68		= word ptr -68h
var_66		= byte ptr -66h
var_65		= byte ptr -65h
var_64		= word ptr -64h
var_62		= word ptr -62h
var_60		= word ptr -60h
var_5E		= word ptr -5Eh
var_5C		= word ptr -5Ch
var_5A		= word ptr -5Ah
var_58		= word ptr -58h
var_56		= word ptr -56h
var_54		= word ptr -54h
var_52		= word ptr -52h
var_50		= word ptr -50h
var_4E		= word ptr -4Eh
var_4C		= word ptr -4Ch
var_4A		= word ptr -4Ah
var_48		= word ptr -48h
var_46		= word ptr -46h
var_44		= word ptr -44h
var_42		= word ptr -42h
var_40		= word ptr -40h
var_3E		= word ptr -3Eh
var_3C		= word ptr -3Ch
var_3A		= word ptr -3Ah
var_38		= word ptr -38h
var_36		= word ptr -36h
var_34		= byte ptr -34h
var_33		= byte ptr -33h
var_32		= word ptr -32h
var_30		= word ptr -30h
var_2E		= word ptr -2Eh
var_2C		= word ptr -2Ch
var_2A		= word ptr -2Ah
var_28		= word ptr -28h
var_26		= word ptr -26h
var_24		= word ptr -24h
var_22		= word ptr -22h
var_20		= word ptr -20h
var_1E		= word ptr -1Eh
var_1C		= word ptr -1Ch
var_1A		= word ptr -1Ah
var_18		= word ptr -18h
var_16		= word ptr -16h
var_14		= word ptr -14h
var_12		= word ptr -12h
var_10		= word ptr -10h
var_E		= word ptr -0Eh
var_C		= word ptr -0Ch
var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= byte ptr -2
var_1		= byte ptr -1

		enter	0C8h, 0
		mov	word_39854, 1
		push	0
		push	ds
		push	offset aBoss2_bos ; "boss2.bos"
		push	ds
		push	offset dword_3982A
		call	sub_1568F
		mov	word_39854, 0
		mov	ax, word ptr dword_3982A
		mov	[bp+var_32], ax
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_30], ax
		mov	ax, word_3982E
		mov	[bp+var_2E], ax
		mov	ax, word_39830
		mov	[bp+var_2C], ax
		mov	ax, word_39832
		mov	[bp+var_2A], ax
		mov	ax, word_39834
		mov	[bp+var_28], ax
		mov	ax, word_39836
		mov	[bp+var_26], ax
		mov	ax, word_39838
		mov	[bp+var_24], ax
		mov	ax, word_3983A
		mov	[bp+var_22], ax
		mov	ax, word_3983C
		mov	[bp+var_20], ax
		mov	ax, word_3983E
		mov	[bp+var_1E], ax
		mov	ax, word_39840
		mov	[bp+var_1C], ax
		mov	ax, word_39842
		mov	[bp+var_1A], ax
		mov	ax, word_39844
		mov	[bp+var_18], ax
		mov	ax, word_39846
		mov	[bp+var_16], ax
		mov	ax, word_39848
		mov	[bp+var_14], ax
		mov	ax, word_3984A
		mov	[bp+var_12], ax
		mov	ax, word_3984C
		mov	[bp+var_10], ax
		mov	ax, word_3984E
		mov	[bp+var_E], ax
		mov	ax, word_39850
		mov	[bp+var_C], ax
		mov	ax, word_39852
		mov	[bp+var_A], ax
		mov	ax, word_39854
		mov	[bp+var_8], ax
		mov	ax, word_39856
		mov	[bp+var_6], ax
		mov	ax, word_39858
		mov	[bp+var_4], ax
		mov	al, byte_3985A
		mov	[bp+var_2], al
		mov	al, byte_3985B
		mov	[bp+var_1], al
		push	ds
		push	offset unk_39866
		push	ds
		push	offset unk_39864
		push	ds
		push	offset unk_3988D
		push	ds
		push	offset unk_3987C
		push	ss
		lea	ax, [bp+var_32]
		push	ax
		call	sub_15851
		mov	ax, word ptr dword_3982A
		mov	[bp+var_64], ax
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_62], ax
		mov	ax, word_3982E
		mov	[bp+var_60], ax
		mov	ax, word_39830
		mov	[bp+var_5E], ax
		mov	ax, word_39832
		mov	[bp+var_5C], ax
		mov	ax, word_39834
		mov	[bp+var_5A], ax
		mov	ax, word_39836
		mov	[bp+var_58], ax
		mov	ax, word_39838
		mov	[bp+var_56], ax
		mov	ax, word_3983A
		mov	[bp+var_54], ax
		mov	ax, word_3983C
		mov	[bp+var_52], ax
		mov	ax, word_3983E
		mov	[bp+var_50], ax
		mov	ax, word_39840
		mov	[bp+var_4E], ax
		mov	ax, word_39842
		mov	[bp+var_4C], ax
		mov	ax, word_39844
		mov	[bp+var_4A], ax
		mov	ax, word_39846
		mov	[bp+var_48], ax
		mov	ax, word_39848
		mov	[bp+var_46], ax
		mov	ax, word_3984A
		mov	[bp+var_44], ax
		mov	ax, word_3984C
		mov	[bp+var_42], ax
		mov	ax, word_3984E
		mov	[bp+var_40], ax
		mov	ax, word_39850
		mov	[bp+var_3E], ax
		mov	ax, word_39852
		mov	[bp+var_3C], ax
		mov	ax, word_39854
		mov	[bp+var_3A], ax
		mov	ax, word_39856
		mov	[bp+var_38], ax
		mov	ax, word_39858
		mov	[bp+var_36], ax
		mov	al, byte_3985A
		mov	[bp+var_34], al
		mov	al, byte_3985B
		mov	[bp+var_33], al
		push	ds
		push	offset unk_39898
		push	ds
		push	offset unk_39896
		push	ds
		push	offset unk_398BF
		push	ds
		push	offset unk_398AE
		push	ss
		lea	ax, [bp+var_64]
		push	ax
		call	sub_15851
		add	sp, 32h
		mov	ax, word ptr dword_3982A
		mov	[bp+var_96], ax
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_94], ax
		mov	ax, word_3982E
		mov	[bp+var_92], ax
		mov	ax, word_39830
		mov	[bp+var_90], ax
		mov	ax, word_39832
		mov	[bp+var_8E], ax
		mov	ax, word_39834
		mov	[bp+var_8C], ax
		mov	ax, word_39836
		mov	[bp+var_8A], ax
		mov	ax, word_39838
		mov	[bp+var_88], ax
		mov	ax, word_3983A
		mov	[bp+var_86], ax
		mov	ax, word_3983C
		mov	[bp+var_84], ax
		mov	ax, word_3983E
		mov	[bp+var_82], ax
		mov	ax, word_39840
		mov	[bp+var_80], ax
		mov	ax, word_39842
		mov	[bp+var_7E], ax
		mov	ax, word_39844
		mov	[bp+var_7C], ax
		mov	ax, word_39846
		mov	[bp+var_7A], ax
		mov	ax, word_39848
		mov	[bp+var_78], ax
		mov	ax, word_3984A
		mov	[bp+var_76], ax
		mov	ax, word_3984C
		mov	[bp+var_74], ax
		mov	ax, word_3984E
		mov	[bp+var_72], ax
		mov	ax, word_39850
		mov	[bp+var_70], ax
		mov	ax, word_39852
		mov	[bp+var_6E], ax
		mov	ax, word_39854
		mov	[bp+var_6C], ax
		mov	ax, word_39856
		mov	[bp+var_6A], ax
		mov	ax, word_39858
		mov	[bp+var_68], ax
		mov	al, byte_3985A
		mov	[bp+var_66], al
		mov	al, byte_3985B
		mov	[bp+var_65], al
		push	ds
		push	offset unk_398CA
		push	ds
		push	offset unk_398C8
		push	ds
		push	offset unk_398F1
		push	ds
		push	offset unk_398E0
		push	ss
		lea	ax, [bp+var_96]
		push	ax
		call	sub_15851
		mov	ax, word ptr dword_3982A
		mov	[bp+var_C8], ax
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_C6], ax
		mov	ax, word_3982E
		mov	[bp+var_C4], ax
		mov	ax, word_39830
		mov	[bp+var_C2], ax
		mov	ax, word_39832
		mov	[bp+var_C0], ax
		mov	ax, word_39834
		mov	[bp+var_BE], ax
		mov	ax, word_39836
		mov	[bp+var_BC], ax
		mov	ax, word_39838
		mov	[bp+var_BA], ax
		mov	ax, word_3983A
		mov	[bp+var_B8], ax
		mov	ax, word_3983C
		mov	[bp+var_B6], ax
		mov	ax, word_3983E
		mov	[bp+var_B4], ax
		mov	ax, word_39840
		mov	[bp+var_B2], ax
		mov	ax, word_39842
		mov	[bp+var_B0], ax
		mov	ax, word_39844
		mov	[bp+var_AE], ax
		mov	ax, word_39846
		mov	[bp+var_AC], ax
		mov	ax, word_39848
		mov	[bp+var_AA], ax
		mov	ax, word_3984A
		mov	[bp+var_A8], ax
		mov	ax, word_3984C
		mov	[bp+var_A6], ax
		mov	ax, word_3984E
		mov	[bp+var_A4], ax
		mov	ax, word_39850
		mov	[bp+var_A2], ax
		mov	ax, word_39852
		mov	[bp+var_A0], ax
		mov	ax, word_39854
		mov	[bp+var_9E], ax
		mov	ax, word_39856
		mov	[bp+var_9C], ax
		mov	ax, word_39858
		mov	[bp+var_9A], ax
		mov	al, byte_3985A
		mov	[bp+var_98], al
		mov	al, byte_3985B
		mov	[bp+var_97], al
		push	ds
		push	offset unk_398FC
		push	ds
		push	offset unk_398FA
		push	ds
		push	offset unk_39923
		push	ds
		push	offset unk_39912
		push	ss
		lea	ax, [bp+var_C8]
		push	ax
		call	sub_15851
		nop
		push	cs
		call	near ptr sub_1B383
		push	ds
		push	offset aBoss3_m_ptn ; "boss3_m.ptn"
		push	2
		call	sub_10888
		mov	byte_3A1B2, 80h	; '?'
		push	ds
		push	offset unk_39EC4
		call	sub_21EFF
		add	sp, 32h
		leave
		retf
sub_1B03F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B383	proc far
		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
		push	offset aBoss2_grp_0 ; "boss2.grp"
		call	sub_10C51
		add	sp, 4
		call	sub_232A4
		mov	word_3984E, 0
		mov	word_39880, 0
		mov	word_398B2, 0
		mov	word_398E4, 0
		mov	word_39916, 0
		xor	si, si
		jmp	short loc_1B3D8
; ---------------------------------------------------------------------------

loc_1B3BB:
		xor	di, di
		jmp	short loc_1B3D2
; ---------------------------------------------------------------------------

loc_1B3BF:
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+di+6F0h]
		mov	bx, si
		imul	bx, 3
		mov	[bx+di+5414h], al
		inc	di

loc_1B3D2:
		cmp	di, 3
		jl	short loc_1B3BF
		inc	si

loc_1B3D8:
		cmp	si, 10h
		jl	short loc_1B3BB
		push	large 1300040h
		push	large 2E00000h
		push	large 300080h
		push	40h ; '@'
		push	ds
		push	offset dword_3982A
		call	sub_166D2
		push	large 1300040h
		push	large 2E00000h
		push	large 300080h
		push	200h
		push	ds
		push	offset dword_3985C
		call	sub_166D2
		add	sp, 24h
		push	large 1300040h
		push	large 2E00000h
		push	large 3000B0h
		push	0C0h ; '?'
		push	ds
		push	offset dword_3988E
		call	sub_166D2
		push	large 1300040h
		push	large 2E00000h
		push	large 3000B0h
		push	180h
		push	ds
		push	offset word_398C0
		call	sub_166D2
		add	sp, 24h
		push	large 1300040h
		push	large 2E00000h
		push	large 300040h
		push	120h
		push	ds
		push	offset word_398F2
		call	sub_166D2
		mov	word_3983E, 0Ch
		mov	word_39840, 34h	; '4'
		mov	word_39842, 0Ch
		mov	word_39844, 20h	; ' '
		mov	word_39870, 0Ch
		mov	word_39872, 34h	; '4'
		mov	word_39874, 0Ch
		mov	word_39876, 20h	; ' '
		mov	word_398A2, 0Ch
		mov	word_398A4, 34h	; '4'
		mov	word_398A6, 0Ch
		mov	word_398A8, 20h	; ' '
		mov	word_398D4, 0Ch
		mov	word_398D6, 34h	; '4'
		mov	word_398D8, 0Ch
		mov	word_398DA, 20h	; ' '
		mov	word_39906, 0Ch
		mov	word_39908, 34h	; '4'
		mov	word_3990A, 0Ch
		mov	word_3990C, 20h	; ' '
		mov	word_39852, 1
		mov	word_39884, 1
		mov	word_398B6, 1
		mov	word_398E8, 1
		mov	word_3991A, 1
		mov	word_3A6CA, 0
		mov	byte_3A6CE, 0
		mov	word_3A6C8, 10h
		mov	word_3A1E5, 0Ch
		mov	word_3A1E7, 8
		push	large 700FFh
		call	sub_22264
		add	sp, 16h
		pop	di
		pop	si
		pop	bp
		retf
sub_1B383	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B53D	proc far

var_A		= word ptr -0Ah
var_8		= qword	ptr -8
arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= dword	ptr  0Ah

		enter	0Ah, 0
		mov	ax, [bp+arg_2]
		sub	ax, [bp+arg_0]
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		; Hack (fstp [bp+var_8])
		db 0cdh
		db 039h
		db 05eh
		db 0f8h
		push	large 3
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_1594
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		; Hack (fmul [bp+var_8])
		db 0cdh
		db 038h
		db 04eh
		db 0f8h
		; Hack (fdiv flt_35B76)
		db 0cdh
		db 034h
		db 036h
		db 0d6h
		db 011h
		call	sub_2395
		les	bx, [bp+arg_4]
		mov	es:[bx], ax
		leave
		retf
sub_1B53D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B579	proc far
		push	bp
		mov	bp, sp
		push	0
		call	sub_169CB
		push	2
		call	sub_108AB
		add	sp, 4
		pop	bp
		retf
sub_1B579	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B58F	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0A0h ; '?'
		jle	loc_1B6CB
		cmp	word_3A6CA, 12Ch
		jge	short loc_1B60E
		push	large 7018Eh
		mov	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		call	sub_F236
		push	large 7018Eh
		mov	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		push	ax
		call	sub_F236
		add	sp, 10h
		mov	ax, word ptr dword_3982A
		add	ax, 4
		cmp	ax, word_36C26
		jge	short loc_1B5F1
		mov	ax, word ptr dword_3982A
		add	ax, 14h
		cmp	ax, word_36C26
		jg	short loc_1B609

loc_1B5F1:
		mov	ax, word ptr dword_3985C
		add	ax, 4
		cmp	ax, word_36C26
		jge	short loc_1B60E
		mov	ax, word ptr dword_3985C
		add	ax, 2Ch	; ','
		cmp	ax, word_36C26
		jle	short loc_1B60E

loc_1B609:
		mov	byte_34A4F, 1

loc_1B60E:
		cmp	word_3A6CA, 0B4h ; '?'
		jle	loc_1B6CB
		cmp	word_3A6CA, 140h
		jge	short loc_1B68A
		push	large 7018Eh
		mov	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		call	sub_F236
		push	large 7018Eh
		mov	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_398C0
		add	ax, 1Ch
		push	ax
		call	sub_F236
		add	sp, 10h
		mov	ax, word ptr dword_3988E
		add	ax, 4
		cmp	ax, word_36C26
		jge	short loc_1B66D
		mov	ax, word ptr dword_3988E
		add	ax, 14h
		cmp	ax, word_36C26
		jg	short loc_1B685

loc_1B66D:
		mov	ax, word_398C0
		add	ax, 4
		cmp	ax, word_36C26
		jge	short loc_1B68A
		mov	ax, word_398C0
		add	ax, 14h
		cmp	ax, word_36C26
		jle	short loc_1B68A

loc_1B685:
		mov	byte_34A4F, 1

loc_1B68A:
		cmp	word_3A6CA, 0C8h ; '?'
		jle	short loc_1B6CB
		push	large 7018Eh
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		call	sub_F236
		add	sp, 8
		mov	ax, word_398F2
		add	ax, 4
		cmp	ax, word_36C26
		jge	short loc_1B6CB
		mov	ax, word_398F2
		add	ax, 14h
		cmp	ax, word_36C26
		jle	short loc_1B6CB
		mov	byte_34A4F, 1

loc_1B6CB:
		cmp	word_34A78, 0
		jz	short loc_1B6D7
		mov	byte_34A4F, 0

loc_1B6D7:
		pop	bp
		retf
sub_1B58F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B6D9	proc far
		push	bp
		mov	bp, sp
		mov	ax, word_3A6CA
		cwd
		idiv	word_39DE4
		cmp	dx, 0Ah
		jnz	short loc_1B70E
		push	large 180015h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		push	18h
		jmp	loc_1B7D1
; ---------------------------------------------------------------------------

loc_1B70E:
		mov	ax, word_3A6CA
		cwd
		idiv	word_39DE4
		cmp	dx, 19h
		jnz	short loc_1B740
		push	large 1C0015h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		push	1Ch
		jmp	loc_1B7D1
; ---------------------------------------------------------------------------

loc_1B740:
		mov	ax, word_3A6CA
		cwd
		idiv	word_39DE4
		cmp	dx, 28h	; '('
		jnz	short loc_1B771
		push	large 200015h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		push	20h ; ' '
		jmp	short loc_1B7D1
; ---------------------------------------------------------------------------

loc_1B771:
		mov	ax, word_3A6CA
		cwd
		idiv	word_39DE4
		cmp	dx, 3Ch	; '<'
		jnz	short loc_1B7A2
		push	large 2C0015h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		push	2Ch ; ','
		jmp	short loc_1B7D1
; ---------------------------------------------------------------------------

loc_1B7A2:
		mov	ax, word_3A6CA
		cwd
		idiv	word_39DE4
		cmp	dx, 50h	; 'P'
		jnz	short loc_1B7D5
		push	large 320015h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		push	32h ; '2'

loc_1B7D1:
		push	15h
		jmp	short loc_1B808
; ---------------------------------------------------------------------------

loc_1B7D5:
		mov	ax, word_3A6CA
		cwd
		idiv	word_39DE4
		cmp	dx, 6Eh	; 'n'
		jnz	short loc_1B822
		push	large 44000Ch
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		push	large 44000Ch

loc_1B808:
		mov	ax, word ptr dword_3985C+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_1B822:
		pop	bp
		retf
sub_1B6D9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B824	proc near

var_18		= qword	ptr -18h
var_10		= qword	ptr -10h
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6

		enter	6, 0
		push	[bp+arg_2]
		push	8
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_12053
		add	sp, 0Ch
		push	0		; char
		mov	ax, [bp+var_2]
		mov	[bp+var_6], ax
		; Hack (fild [bp+var_6])
		db 0cdh
		db 03bh
		db 046h
		db 0fah
		sub	sp, 8
		; Hack (fstp [bp+var_10])
		db 0cdh
		db 039h
		db 05eh
		db 0f0h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_4]
		mov	[bp+var_6], ax
		; Hack (fild [bp+var_6])
		db 0cdh
		db 03bh
		db 046h
		db 0fah
		sub	sp, 8
		; Hack (fstp [bp+var_18])
		db 0cdh
		db 039h
		db 05eh
		db 0e8h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax		; int
		mov	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax		; int
		push	ds
		push	offset unk_39EC4 ; __int32
		call	sub_21C0D
		add	sp, 1Ah
		push	[bp+arg_0]
		push	8
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_12053
		add	sp, 0Ch
		push	0		; char
		mov	ax, [bp+var_2]
		mov	[bp+var_6], ax
		; Hack (fild [bp+var_6])
		db 0cdh
		db 03bh
		db 046h
		db 0fah
		sub	sp, 8
		; Hack (fstp [bp+var_10])
		db 0cdh
		db 039h
		db 05eh
		db 0f0h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_4]
		mov	[bp+var_6], ax
		; Hack (fild [bp+var_6])
		db 0cdh
		db 03bh
		db 046h
		db 0fah
		sub	sp, 8
		; Hack (fstp [bp+var_18])
		db 0cdh
		db 039h
		db 05eh
		db 0e8h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, word_398C2
		add	ax, 1Ch
		push	ax		; int
		mov	ax, word_398C0
		add	ax, 1Ch
		push	ax		; int
		push	ds
		push	offset unk_39EC4 ; __int32
		call	sub_21C0D
		add	sp, 1Ah
		leave
		retn	4
sub_1B824	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1B8DE	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	di, [bp+arg_0]
		push	word_39DF4
		push	word_39DEA
		push	word_39DF0
		push	word_39DE6
		call	sub_114CA
		push	word_39DF8
		push	word_39DEE
		push	word_39DF4
		push	word_39DEA
		call	sub_114CA
		push	word_39DF2
		push	word_39DE8
		push	word_39DF8
		push	word_39DEE
		call	sub_114CA
		push	word_39DF6
		push	word_39DEC
		push	word_39DF2
		push	word_39DE8
		call	sub_114CA
		push	word_39DF0
		push	word_39DE6
		push	word_39DF6
		push	word_39DEC
		call	sub_114CA
		add	sp, 28h
		xor	si, si
		jmp	short loc_1B9B1
; ---------------------------------------------------------------------------

loc_1B956:
		movsx	eax, word_39DFA
		mov	bx, si
		imul	bx, 33h
		add	bx, di
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		add	ax, word_39DFC
		mov	bx, si
		add	bx, bx
		mov	[bx+5446h], ax
		movsx	eax, word_39DFA
		mov	bx, si
		imul	bx, 33h
		add	bx, di
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		add	ax, word_39DFE
		mov	bx, si
		add	bx, bx
		mov	[bx+5450h], ax
		inc	si

loc_1B9B1:
		cmp	si, 5
		jl	short loc_1B956
		push	7
		push	word_39DF4
		push	word_39DEA
		push	word_39DF0
		push	word_39DE6
		call	sub_114E3
		push	7
		push	word_39DF8
		push	word_39DEE
		push	word_39DF4
		push	word_39DEA
		call	sub_114E3
		push	7
		push	word_39DF2
		push	word_39DE8
		push	word_39DF8
		push	word_39DEE
		call	sub_114E3
		push	7
		push	word_39DF6
		push	word_39DEC
		push	word_39DF2
		push	word_39DE8
		call	sub_114E3
		push	7
		push	word_39DF0
		push	word_39DE6
		push	word_39DF6
		push	word_39DEC
		call	sub_114E3
		add	sp, 32h
		pop	di
		pop	si
		pop	bp
		retn	2
sub_1B8DE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1BA32	proc far

var_32		= word ptr -32h
var_30		= word ptr -30h
var_2E		= word ptr -2Eh
var_2C		= word ptr -2Ch
var_2A		= word ptr -2Ah
var_28		= word ptr -28h
var_26		= word ptr -26h
var_24		= word ptr -24h
var_22		= word ptr -22h
var_20		= word ptr -20h
var_1E		= word ptr -1Eh
var_1C		= word ptr -1Ch
var_1A		= word ptr -1Ah
var_18		= word ptr -18h
var_16		= word ptr -16h
var_14		= word ptr -14h
var_12		= word ptr -12h
var_10		= word ptr -10h
var_E		= word ptr -0Eh
var_C		= word ptr -0Ch
var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	32h, 0
		push	si
		mov	ax, word_35B52
		mov	[bp+var_2], ax
		push	ds
		push	offset unk_39EC4
		call	sub_21F19
		add	sp, 4
		cmp	byte_3A6CE, 0
		jnz	loc_1BEC0
		cmp	byte ptr word_39E14+1, 0
		jnz	short loc_1BA6C
		push	word_3A6CA
		push	word_3A6C8
		call	sub_2191C
		add	sp, 4
		mov	byte ptr word_39E14+1, al

loc_1BA6C:
		inc	word_3A6CA
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3988E
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398C0
		call	sub_16733
		add	sp, 30h
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398F2
		call	sub_16733
		add	sp, 0Ch
		push	cs
		call	near ptr sub_1B58F
		mov	ax, word_3A6CA
		mov	bx, 28h	; '('
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1BAFD
		inc	byte_350BD
		inc	byte_350BE
		inc	byte_39BB9
		inc	byte_39BBA
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4

loc_1BAFD:
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1BB1F
		mov	word_3984E, 1
		mov	word_39880, 1
		mov	word_39852, 0
		mov	word_39884, 0
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BB1F:
		cmp	word_3A6CA, 78h	; 'x'
		jnz	short loc_1BB4D
		mov	word_3984E, 2
		mov	word_39880, 2
		mov	word_398B2, 1
		mov	word_398E4, 1
		mov	word_398B6, 0
		mov	word_398E8, 0
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BB4D:
		cmp	word_3A6CA, 8Ch	; '�
		jnz	short loc_1BB7C
		mov	word_3984E, 6
		mov	word_39880, 6
		mov	word_398B2, 2
		mov	word_398E4, 2
		mov	word_39916, 1
		mov	word_3991A, 0
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BB7C:
		cmp	word_3A6CA, 0A0h ; '?'
		jnz	short loc_1BBA5
		mov	word_3984E, 3
		mov	word_39880, 3
		mov	word_398B2, 6
		mov	word_398E4, 6
		mov	word_39916, 2
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BBA5:
		cmp	word_3A6CA, 0B4h ; '?'
		jnz	short loc_1BBC2
		mov	word_398B2, 3
		mov	word_398E4, 3
		mov	word_39916, 6
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BBC2:
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_1BBD3
		mov	word_39916, 3
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BBD3:
		cmp	word_3A6CA, 0F0h ; '�
		jnz	loc_1BC8C
		mov	word_3984E, 2
		mov	word_39880, 2
		mov	word_398B2, 2
		mov	word_398E4, 2
		mov	word_39916, 2
		mov	word_39852, 1
		mov	word_39884, 1
		mov	word_398B6, 1
		mov	word_398E8, 1
		mov	word_3991A, 1
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	loc_1DFFC
		push	large 36001Bh
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 36001Bh
		mov	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_398C0
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 36001Bh
		mov	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 24h
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	loc_1DFFC
		jmp	loc_1BD19
; ---------------------------------------------------------------------------

loc_1BC8C:
		cmp	word_3A6CA, 104h
		jnz	loc_1BD59
		mov	word_3984E, 1
		mov	word_39880, 1
		mov	word_398B2, 1
		mov	word_398E4, 1
		mov	word_39916, 1
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	loc_1DFFC
		push	large 36001Bh
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 36001Bh
		mov	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_398C0
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 36001Bh
		mov	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 24h

loc_1BD19:
		push	large 36001Bh
		mov	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 36001Bh
		mov	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 18h
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BD59:
		cmp	word_3A6CA, 118h
		jnz	short loc_1BD82
		mov	word_3984E, 0
		mov	word_39880, 0
		mov	word_398B2, 0
		mov	word_398E4, 0
		mov	word_39916, 0
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BD82:
		cmp	word_3A6CA, 12Ch
		jnz	short loc_1BDCD
		mov	word_3984E, 1
		mov	word_39880, 1
		push	190h
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		call	sub_F2F5
		add	sp, 8
		push	190h
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		jmp	loc_1BEB1
; ---------------------------------------------------------------------------

loc_1BDCD:
		cmp	word_3A6CA, 140h
		jnz	short loc_1BE24
		mov	word_3984E, 2
		mov	word_39880, 2
		mov	word_39852, 0
		mov	word_39884, 0
		push	190h
		mov	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		call	sub_F2F5
		add	sp, 8
		push	190h
		mov	ax, word_398C0
		add	ax, 1Ch
		push	ax
		mov	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_398C0
		jmp	loc_1BEB1
; ---------------------------------------------------------------------------

loc_1BE24:
		cmp	word_3A6CA, 14Ah
		jle	loc_1DFFC
		mov	byte_3A6CE, 1
		mov	word_35B54, 0
		mov	word_3A6CA, 0
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4
		call	sub_232A4
		mov	byte ptr word_39E14+1, 0
		mov	word_3984E, 4
		mov	word_39880, 3
		cmp	byte_34A30, 0
		jnz	short loc_1BE6D
		mov	ax, 15Eh
		jmp	short loc_1BE9A
; ---------------------------------------------------------------------------

loc_1BE6D:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_1BE7B
		mov	ax, 12Ch
		jmp	short loc_1BE9A
; ---------------------------------------------------------------------------

loc_1BE7B:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_1BE89
		mov	ax, 0C8h ; '?'
		jmp	short loc_1BE9A
; ---------------------------------------------------------------------------

loc_1BE89:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_1BE97
		mov	ax, 82h	; '�
		jmp	short loc_1BE9A
; ---------------------------------------------------------------------------

loc_1BE97:
		mov	ax, 12Ch

loc_1BE9A:
		mov	word_39DE4, ax
		push	190h
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2

loc_1BEB1:
		add	ax, 1Ch
		push	ax
		call	sub_F2F5
		add	sp, 8
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1BEC0:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 1
		jnz	loc_1C02D
		inc	word_3A6CA
		inc	word_39E04
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_16733
		add	sp, 18h
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1BF11
		mov	word_3984E, 4
		jmp	short loc_1BF30
; ---------------------------------------------------------------------------

loc_1BF11:
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1BF2A
		mov	word_3984E, 5
		jmp	short loc_1BF30
; ---------------------------------------------------------------------------

loc_1BF2A:
		mov	word_3984E, 3

loc_1BF30:
		mov	ax, word ptr dword_3985C
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1BF47
		mov	word_39880, 4
		jmp	short loc_1BF66
; ---------------------------------------------------------------------------

loc_1BF47:
		mov	ax, word ptr dword_3985C
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1BF60
		mov	word_39880, 5
		jmp	short loc_1BF66
; ---------------------------------------------------------------------------

loc_1BF60:
		mov	word_39880, 3

loc_1BF66:
		push	cs
		call	near ptr sub_1B6D9
		push	large 0
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1BF88
		cmp	word_3984E, 0
		jnz	short loc_1BFE8

loc_1BF88:
		push	ds
		push	offset dword_3985C
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1BFA0
		cmp	word_39880, 0
		jnz	short loc_1BFE8

loc_1BFA0:
		push	ds
		push	offset dword_3988E
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1BFB8
		cmp	word_398B2, 0
		jnz	short loc_1BFE8

loc_1BFB8:
		push	ds
		push	offset word_398C0
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1BFD0
		cmp	word_398E4, 0
		jnz	short loc_1BFE8

loc_1BFD0:
		push	ds
		push	offset word_398F2
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1BFED
		cmp	word_39916, 0
		jz	short loc_1BFED

loc_1BFE8:
		mov	ax, 1
		jmp	short loc_1BFEF
; ---------------------------------------------------------------------------

loc_1BFED:
		xor	ax, ax

loc_1BFEF:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_35B54
		push	ds
		push	offset word_39E04
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0Fh
		jle	short loc_1C025
		cmp	word_3A6CA, 44Ch
		jle	loc_1DFFC

loc_1C025:
		mov	byte_3A6CE, 2
		jmp	loc_1CAF9
; ---------------------------------------------------------------------------

loc_1C02D:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 2
		jnz	loc_1C0CA
		push	ds
		push	offset word_3A6CA
		push	large 20000h
		push	0Ch
		push	3
		nop
		push	cs
		call	near ptr sub_1DFFF
		add	sp, 0Ch
		cmp	word_3A6CA, 46h	; 'F'
		jl	loc_1DFFC
		mov	byte_3A6CE, 3
		mov	word_39E08, 0
		mov	byte ptr word_39E14, 0
		mov	word_3A6CA, 0
		mov	word_39E04, 0
		mov	word_39E06, 0
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4
		call	sub_232A4
		cmp	byte_34A30, 0
		jnz	short loc_1C097
		mov	ax, 8
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C097:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_1C0A6
		mov	ax, 0Ch
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C0A6:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_1C0B5
		mov	ax, 10h
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C0B5:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_1C0C4
		mov	ax, 14h
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C0C4:
		mov	ax, 0Ch
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C0CA:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 3
		jnz	loc_1C3EB
		inc	word_3A6CA
		inc	word_39E04
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3988E
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398C0
		call	sub_16733
		add	sp, 18h
		mov	ax, word ptr dword_3988E
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1C11B
		mov	word_398B2, 4
		jmp	short loc_1C13A
; ---------------------------------------------------------------------------

loc_1C11B:
		mov	ax, word ptr dword_3988E
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1C134
		mov	word_398B2, 5
		jmp	short loc_1C13A
; ---------------------------------------------------------------------------

loc_1C134:
		mov	word_398B2, 3

loc_1C13A:
		mov	ax, word_398C0
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1C151
		mov	word_398E4, 4
		jmp	short loc_1C170
; ---------------------------------------------------------------------------

loc_1C151:
		mov	ax, word_398C0
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1C16A
		mov	word_398E4, 5
		jmp	short loc_1C170
; ---------------------------------------------------------------------------

loc_1C16A:
		mov	word_398E4, 3

loc_1C170:
		cmp	word_3A6CA, 5Ah	; 'Z'
		jl	short loc_1C191
		cmp	word_39E08, 0
		jz	short loc_1C185
		cmp	word_39E08, 4
		jnz	short loc_1C191

loc_1C185:
		mov	word_398B2, 1
		mov	word_398E4, 1

loc_1C191:
		cmp	word_3A6CA, 64h	; 'd'
		jz	short loc_1C1AF
		cmp	word_39E08, 1
		jz	short loc_1C1AF
		cmp	word_39E08, 5
		jz	short loc_1C1AF
		cmp	word_39E08, 9
		jnz	loc_1C248

loc_1C1AF:
		cmp	word_39E08, 0
		jnz	short loc_1C21E
		call	IRand
		mov	bx, 3
		cwd
		idiv	bx
		shl	dx, 2
		inc	dx
		mov	word_39E08, dx
		mov	ax, word_36C26
		add	ax, 0FFF8h
		mov	word_39E0A, ax
		mov	ax, 190h
		sub	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E0A
		sub	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		call	iatan2
		mov	byte ptr word_39E16, al
		mov	ax, 190h
		sub	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E0A
		sub	ax, word_398C0
		add	ax, 1Ch
		push	ax
		call	iatan2
		mov	byte ptr word_39E16+1, al
		mov	al, byte ptr word_39E16
		add	al, 0F0h ; '�
		mov	byte ptr word_39E16, al
		mov	al, byte ptr word_39E16+1
		add	al, 10h
		mov	byte ptr word_39E16+1, al

loc_1C21E:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C236
		push	word_39E16
		push	word_39E16+1
		call	sub_1B824

loc_1C236:
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_1C248
		inc	word_39E08
		mov	word_39E06, 0

loc_1C248:
		cmp	word_39E08, 2
		jz	short loc_1C25D
		cmp	word_39E08, 6
		jz	short loc_1C25D
		cmp	word_39E08, 0Ah
		jnz	short loc_1C2A2

loc_1C25D:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	loc_1C327
		inc	word_39E06
		mov	al, byte ptr word_39E16
		add	al, 0FEh ; '?'
		mov	byte ptr word_39E16, al
		mov	al, byte ptr word_39E16+1
		add	al, 2
		mov	byte ptr word_39E16+1, al
		push	word_39E16
		push	word_39E16+1
		call	sub_1B824
		cmp	word_39E06, 0Ah
		jle	loc_1C327
		inc	word_39E08
		mov	word_39E06, 0
		jmp	loc_1C327
; ---------------------------------------------------------------------------

loc_1C2A2:
		cmp	word_39E08, 3
		jz	short loc_1C2B7
		cmp	word_39E08, 7
		jz	short loc_1C2B7
		cmp	word_39E08, 0Bh
		jnz	short loc_1C327

loc_1C2B7:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_1C327
		inc	word_39E06
		cmp	word_39E08, 3
		jnz	short loc_1C2DA
		mov	al, byte ptr word_39E16
		add	al, 4
		mov	byte ptr word_39E16, al
		jmp	short loc_1C2FF
; ---------------------------------------------------------------------------

loc_1C2DA:
		cmp	word_39E08, 7
		jnz	short loc_1C2E8
		mov	al, byte ptr word_39E16+1
		add	al, 0FCh ; '�
		jmp	short loc_1C2FC
; ---------------------------------------------------------------------------

loc_1C2E8:
		cmp	word_39E08, 0Bh
		jnz	short loc_1C2FF
		mov	al, byte ptr word_39E16
		add	al, 2
		mov	byte ptr word_39E16, al
		mov	al, byte ptr word_39E16+1
		add	al, 0FEh ; '?'

loc_1C2FC:
		mov	byte ptr word_39E16+1, al

loc_1C2FF:
		push	word_39E16
		push	word_39E16+1
		call	sub_1B824
		cmp	word_39E06, 0Ah
		jle	short loc_1C327
		mov	word_39E08, 0
		mov	word_39E06, 0
		mov	word_3A6CA, 0
		inc	byte ptr word_39E14

loc_1C327:
		push	large 0
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C345
		cmp	word_3984E, 0
		jnz	short loc_1C3A5

loc_1C345:
		push	ds
		push	offset dword_3985C
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C35D
		cmp	word_39880, 0
		jnz	short loc_1C3A5

loc_1C35D:
		push	ds
		push	offset dword_3988E
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C375
		cmp	word_398B2, 0
		jnz	short loc_1C3A5

loc_1C375:
		push	ds
		push	offset word_398C0
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C38D
		cmp	word_398E4, 0
		jnz	short loc_1C3A5

loc_1C38D:
		push	ds
		push	offset word_398F2
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C3AA
		cmp	word_39916, 0
		jz	short loc_1C3AA

loc_1C3A5:
		mov	ax, 1
		jmp	short loc_1C3AC
; ---------------------------------------------------------------------------

loc_1C3AA:
		xor	ax, ax

loc_1C3AC:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_35B54
		push	ds
		push	offset word_39E04
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0Ch
		jle	short loc_1C3E3
		mov	al, byte ptr word_39E14
		cbw
		cmp	ax, 5
		jl	loc_1DFFC

loc_1C3E3:
		mov	byte_3A6CE, 4
		jmp	loc_1CAF9
; ---------------------------------------------------------------------------

loc_1C3EB:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 4
		jnz	loc_1C493
		push	ds
		push	offset word_3A6CA
		push	large 1
		push	3
		push	0Ch
		nop
		push	cs
		call	near ptr sub_1DFFF
		add	sp, 0Ch
		cmp	word_3A6CA, 46h	; 'F'
		jl	loc_1DFFC
		mov	byte_3A6CE, 5
		mov	word_39E08, 0
		mov	byte ptr word_39E14, 0
		mov	word_3A6CA, 0
		mov	word_39E04, 0
		mov	word_39E06, 0
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4
		call	sub_232A4
		mov	ax, 190h
		sub	ax, word ptr dword_3982A+2
		mov	word_39E0C, ax
		cmp	byte_34A30, 0
		jnz	short loc_1C45B
		mov	ax, 0Ch
		jmp	short loc_1C488
; ---------------------------------------------------------------------------

loc_1C45B:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_1C469
		mov	ax, 8
		jmp	short loc_1C488
; ---------------------------------------------------------------------------

loc_1C469:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_1C477
		mov	ax, 4
		jmp	short loc_1C488
; ---------------------------------------------------------------------------

loc_1C477:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_1C485
		mov	ax, 2
		jmp	short loc_1C488
; ---------------------------------------------------------------------------

loc_1C485:
		mov	ax, 8

loc_1C488:
		mov	word_39DE4, ax
		mov	byte ptr word_39E16, 0
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1C493:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 5
		jnz	loc_1C741
		inc	word_3A6CA
		inc	word_39E04
		inc	word_39E06
		dec	byte ptr word_39E16
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_16733
		add	sp, 18h
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1C4EC
		mov	word_3984E, 4
		jmp	short loc_1C50B
; ---------------------------------------------------------------------------

loc_1C4EC:
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1C505
		mov	word_3984E, 5
		jmp	short loc_1C50B
; ---------------------------------------------------------------------------

loc_1C505:
		mov	word_3984E, 3

loc_1C50B:
		mov	ax, word ptr dword_3985C
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1C522
		mov	word_39880, 4
		jmp	short loc_1C541
; ---------------------------------------------------------------------------

loc_1C522:
		mov	ax, word ptr dword_3985C
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1C53B
		mov	word_39880, 5
		jmp	short loc_1C541
; ---------------------------------------------------------------------------

loc_1C53B:
		mov	word_39880, 3

loc_1C541:
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1C55B
		cmp	word_39E08, 0
		jnz	short loc_1C55B
		mov	word_39E06, 0
		mov	word_39E08, 1

loc_1C55B:
		cmp	word_39E08, 1
		jnz	short loc_1C5D4
		mov	ax, word_39E06
		cwd
		idiv	word_39DE4
		or	dx, dx
		jnz	short loc_1C5BA
		push	large 0
		push	large 0
		push	40h ; '@'
		mov	al, 80h	; '?'
		sub	al, byte ptr word_39E16
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	40h ; '@'
		push	word_39E16
		mov	ax, word ptr dword_3985C+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h

loc_1C5BA:
		mov	ax, word_39E06
		mov	bx, 5
		cwd
		idiv	bx
		cmp	ax, 24h	; '$'
		jl	short loc_1C5D4
		mov	word_39E08, 2
		mov	word_3A6CA, 0

loc_1C5D4:
		cmp	word_39E08, 2
		jnz	short loc_1C5F3
		cmp	word_3A6CA, 32h	; '2'
		jle	short loc_1C5F3
		mov	word_39E06, 0FFF1h
		mov	word_39E08, 3
		mov	byte ptr word_39E16, 80h ; '?'

loc_1C5F3:
		cmp	word_39E08, 3
		jnz	loc_1C67D
		mov	ax, word_39E06
		cwd
		idiv	word_39DE4
		or	dx, dx
		jnz	short loc_1C65A
		push	large 0
		push	large 400004h
		push	40h ; '@'
		mov	al, 80h	; '?'
		sub	al, byte ptr word_39E16
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 400004h
		push	40h ; '@'
		push	word_39E16
		mov	ax, word ptr dword_3985C+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h

loc_1C65A:
		mov	ax, word_39E06
		mov	bx, 5
		cwd
		idiv	bx
		cmp	ax, 14h
		jl	short loc_1C67D
		mov	word_39E08, 0
		mov	word_3A6CA, 0
		inc	byte ptr word_39E14
		mov	byte ptr word_39E16, 0

loc_1C67D:
		push	large 0
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C69B
		cmp	word_3984E, 0
		jnz	short loc_1C6FB

loc_1C69B:
		push	ds
		push	offset dword_3985C
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C6B3
		cmp	word_39880, 0
		jnz	short loc_1C6FB

loc_1C6B3:
		push	ds
		push	offset dword_3988E
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C6CB
		cmp	word_398B2, 0
		jnz	short loc_1C6FB

loc_1C6CB:
		push	ds
		push	offset word_398C0
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C6E3
		cmp	word_398E4, 0
		jnz	short loc_1C6FB

loc_1C6E3:
		push	ds
		push	offset word_398F2
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1C700
		cmp	word_39916, 0
		jz	short loc_1C700

loc_1C6FB:
		mov	ax, 1
		jmp	short loc_1C702
; ---------------------------------------------------------------------------

loc_1C700:
		xor	ax, ax

loc_1C702:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_35B54
		push	ds
		push	offset word_39E04
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0Ah
		jle	short loc_1C739
		mov	al, byte ptr word_39E14
		cbw
		cmp	ax, 4
		jle	loc_1DFFC

loc_1C739:
		mov	byte_3A6CE, 6
		jmp	loc_1CAF9
; ---------------------------------------------------------------------------

loc_1C741:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 6
		jnz	loc_1C7E4
		push	ds
		push	offset word_3A6CA
		push	large 30000h
		push	0Ch
		push	3
		nop
		push	cs
		call	near ptr sub_1DFFF
		add	sp, 0Ch
		cmp	word_3A6CA, 46h	; 'F'
		jl	loc_1DFFC
		mov	byte_3A6CE, 7
		mov	word_39E08, 0
		mov	byte ptr word_39E14, 0
		mov	word_3A6CA, 0
		mov	word_39E04, 0
		mov	word_39E06, 0
		mov	word_39E12, 0
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4
		call	sub_232A4
		cmp	byte_34A30, 0
		jnz	short loc_1C7B1
		mov	ax, 0Ah
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C7B1:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_1C7C0
		mov	ax, 10h
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C7C0:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_1C7CF
		mov	ax, 14h
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C7CF:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_1C7DE
		mov	ax, 18h
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C7DE:
		mov	ax, 10h
		jmp	loc_1D84C
; ---------------------------------------------------------------------------

loc_1C7E4:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 7
		jnz	loc_1CB08
		inc	word_3A6CA
		inc	word_39E04
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3988E
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398C0
		call	sub_16733
		add	sp, 18h
		mov	ax, word ptr dword_3988E
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1C835
		mov	word_398B2, 4
		jmp	short loc_1C854
; ---------------------------------------------------------------------------

loc_1C835:
		mov	ax, word ptr dword_3988E
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1C84E
		mov	word_398B2, 5
		jmp	short loc_1C854
; ---------------------------------------------------------------------------

loc_1C84E:
		mov	word_398B2, 3

loc_1C854:
		mov	ax, word_398C0
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1C86B
		mov	word_398E4, 4
		jmp	short loc_1C88A
; ---------------------------------------------------------------------------

loc_1C86B:
		mov	ax, word_398C0
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1C884
		mov	word_398E4, 5
		jmp	short loc_1C88A
; ---------------------------------------------------------------------------

loc_1C884:
		mov	word_398E4, 3

loc_1C88A:
		cmp	word_3A6CA, 5Ah	; 'Z'
		jl	short loc_1C8AB
		cmp	word_39E08, 0
		jz	short loc_1C89F
		cmp	word_39E08, 4
		jnz	short loc_1C8AB

loc_1C89F:
		mov	word_398B2, 1
		mov	word_398E4, 1

loc_1C8AB:
		cmp	word_3A6CA, 64h	; 'd'
		jz	short loc_1C8C2
		cmp	word_39E08, 1
		jz	short loc_1C8C2
		cmp	word_39E08, 5
		jnz	loc_1C95B

loc_1C8C2:
		cmp	word_39E08, 0
		jnz	short loc_1C931
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		shl	dx, 2
		inc	dx
		mov	word_39E08, dx
		mov	ax, word_36C26
		add	ax, 0FFF8h
		mov	word_39E0A, ax
		mov	ax, 190h
		sub	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E0A
		sub	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		call	iatan2
		mov	byte ptr word_39E16, al
		mov	ax, 190h
		sub	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E0A
		sub	ax, word_398C0
		add	ax, 1Ch
		push	ax
		call	iatan2
		mov	byte ptr word_39E16+1, al
		mov	al, byte ptr word_39E16
		add	al, 0F0h ; '�
		mov	byte ptr word_39E16, al
		mov	al, byte ptr word_39E16+1
		add	al, 10h
		mov	byte ptr word_39E16+1, al

loc_1C931:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1C949
		push	word_39E16
		push	word_39E16+1
		call	sub_1B824

loc_1C949:
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_1C95B
		inc	word_39E08
		mov	word_39E06, 0

loc_1C95B:
		cmp	word_39E08, 2
		jz	short loc_1C969
		cmp	word_39E08, 6
		jnz	short loc_1C9C3

loc_1C969:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	loc_1CA38
		inc	word_39E06
		cmp	word_39E08, 2
		jnz	short loc_1C993
		mov	al, byte ptr word_39E16
		add	al, 0FEh ; '?'
		mov	byte ptr word_39E16, al
		mov	al, byte ptr word_39E16+1
		add	al, 0FEh ; '?'
		jmp	short loc_1C9A0
; ---------------------------------------------------------------------------

loc_1C993:
		mov	al, byte ptr word_39E16
		add	al, 2
		mov	byte ptr word_39E16, al
		mov	al, byte ptr word_39E16+1
		add	al, 2

loc_1C9A0:
		mov	byte ptr word_39E16+1, al
		push	word_39E16
		push	word_39E16+1
		call	sub_1B824
		cmp	word_39E06, 0Ah
		jle	loc_1CA38
		inc	word_39E08
		mov	word_39E06, 0
		jmp	short loc_1CA38
; ---------------------------------------------------------------------------

loc_1C9C3:
		cmp	word_39E08, 3
		jz	short loc_1C9D1
		cmp	word_39E08, 7
		jnz	short loc_1CA38

loc_1C9D1:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_1CA38
		inc	word_39E06
		cmp	word_39E08, 3
		jnz	short loc_1C9F9
		mov	al, byte ptr word_39E16
		add	al, 3
		mov	byte ptr word_39E16, al
		mov	al, byte ptr word_39E16+1
		add	al, 3
		jmp	short loc_1CA0D
; ---------------------------------------------------------------------------

loc_1C9F9:
		cmp	word_39E08, 7
		jnz	short loc_1CA10
		mov	al, byte ptr word_39E16
		add	al, 0FDh ; '?'
		mov	byte ptr word_39E16, al
		mov	al, byte ptr word_39E16+1
		add	al, 0FDh ; '?'

loc_1CA0D:
		mov	byte ptr word_39E16+1, al

loc_1CA10:
		push	word_39E16
		push	word_39E16+1
		call	sub_1B824
		cmp	word_39E06, 0Ah
		jle	short loc_1CA38
		mov	word_39E08, 0
		mov	word_39E06, 0
		mov	word_3A6CA, 0
		inc	byte ptr word_39E14

loc_1CA38:
		push	large 0
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CA56
		cmp	word_3984E, 0
		jnz	short loc_1CAB6

loc_1CA56:
		push	ds
		push	offset dword_3985C
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CA6E
		cmp	word_39880, 0
		jnz	short loc_1CAB6

loc_1CA6E:
		push	ds
		push	offset dword_3988E
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CA86
		cmp	word_398B2, 0
		jnz	short loc_1CAB6

loc_1CA86:
		push	ds
		push	offset word_398C0
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CA9E
		cmp	word_398E4, 0
		jnz	short loc_1CAB6

loc_1CA9E:
		push	ds
		push	offset word_398F2
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CABB
		cmp	word_39916, 0
		jz	short loc_1CABB

loc_1CAB6:
		mov	ax, 1
		jmp	short loc_1CABD
; ---------------------------------------------------------------------------

loc_1CABB:
		xor	ax, ax

loc_1CABD:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_35B54
		push	ds
		push	offset word_39E04
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 8
		jle	short loc_1CAF4
		mov	al, byte ptr word_39E14
		cbw
		cmp	ax, 4
		jle	loc_1DFFC

loc_1CAF4:
		mov	byte_3A6CE, 8

loc_1CAF9:
		mov	word_3A6CA, 0
		mov	word_39E04, 0
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1CB08:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 8
		jnz	short loc_1CB3E
		push	ds
		push	offset word_3A6CA
		push	large 10002h
		push	10h
		push	0Ch
		nop
		push	cs
		call	near ptr sub_1DFFF
		add	sp, 0Ch
		cmp	word_3A6CA, 46h	; 'F'
		jl	loc_1DFFC
		mov	byte_3A6CE, 9
		mov	word_39E08, 0
		jmp	loc_1D071
; ---------------------------------------------------------------------------

loc_1CB3E:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 9
		jnz	loc_1D036
		inc	word_3A6CA
		inc	word_39E04
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398F2
		call	sub_16733
		add	sp, 0Ch
		cmp	word_3A6CA, 1Eh
		jl	short loc_1CB88
		cmp	word_39E08, 0
		jz	short loc_1CB82
		cmp	word_39E08, 2
		jz	short loc_1CB82
		cmp	word_39E08, 4
		jnz	short loc_1CB88

loc_1CB82:
		mov	word_39916, 1

loc_1CB88:
		cmp	word_3A6CA, 28h	; '('
		jnz	short loc_1CB96
		cmp	word_39E08, 0
		jz	short loc_1CB9F

loc_1CB96:
		cmp	word_39E08, 1
		jnz	loc_1CC8B

loc_1CB9F:
		cmp	word_39E08, 0
		jnz	short loc_1CBB2
		mov	word_39E08, 1
		mov	word_39E12, 0

loc_1CBB2:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	loc_1CF57
		cmp	word_39E06, 100h
		jg	short loc_1CBD2
		mov	word_39916, 4
		jmp	short loc_1CBE8
; ---------------------------------------------------------------------------

loc_1CBD2:
		cmp	word_39E06, 180h
		jl	short loc_1CBE2
		mov	word_39916, 5
		jmp	short loc_1CBE8
; ---------------------------------------------------------------------------

loc_1CBE2:
		mov	word_39916, 3

loc_1CBE8:
		mov	ax, word_39E06
		mov	[bp+var_4], ax
		mov	ax, word_398F4
		add	ax, 1Ch
		mov	[bp+var_6], ax
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	[bp+var_8], ax
		mov	ax, word_39E06
		add	ax, 0FFF0h
		mov	[bp+var_A], ax
		mov	ax, word_398F4
		add	ax, 1Ch
		mov	[bp+var_C], ax
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	[bp+var_E], ax
		push	190h
		push	[bp+var_A]
		push	[bp+var_C]
		push	ax
		call	sub_114CA
		push	large 0E00007h
		push	190h
		push	[bp+var_4]
		push	[bp+var_6]
		push	[bp+var_8]
		call	sub_11527
		add	sp, 14h
		cmp	word_39E06, 250h
		jl	loc_1CF52
		push	190h
		push	word_39E06
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		call	sub_114CA
		add	sp, 8
		mov	word_39E08, 2
		mov	word_3A6CA, 0
		mov	word_39E06, 0
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jle	loc_1CF52
		jmp	loc_1CD9D
; ---------------------------------------------------------------------------

loc_1CC8B:
		cmp	word_3A6CA, 28h	; '('
		jnz	short loc_1CC99
		cmp	word_39E08, 2
		jz	short loc_1CCA2

loc_1CC99:
		cmp	word_39E08, 3
		jnz	loc_1CDA6

loc_1CCA2:
		cmp	word_39E08, 2
		jnz	short loc_1CCBB
		mov	word_39E08, 3
		mov	word_39E12, 0
		mov	word_39E06, 0

loc_1CCBB:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	loc_1CF57
		cmp	word_39E06, 100h
		jg	short loc_1CCDB
		mov	word_39916, 5
		jmp	short loc_1CCF1
; ---------------------------------------------------------------------------

loc_1CCDB:
		cmp	word_39E06, 180h
		jl	short loc_1CCEB
		mov	word_39916, 4
		jmp	short loc_1CCF1
; ---------------------------------------------------------------------------

loc_1CCEB:
		mov	word_39916, 3

loc_1CCF1:
		mov	ax, 280h
		sub	ax, word_39E06
		mov	[bp+var_10], ax
		mov	ax, word_398F4
		add	ax, 1Ch
		mov	[bp+var_12], ax
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	[bp+var_14], ax
		mov	ax, 280h
		sub	ax, word_39E06
		add	ax, 10h
		mov	[bp+var_16], ax
		mov	ax, word_398F4
		add	ax, 1Ch
		mov	[bp+var_18], ax
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	[bp+var_1A], ax
		push	190h
		push	[bp+var_16]
		push	[bp+var_18]
		push	ax
		call	sub_114CA
		push	large 0E00007h
		push	190h
		push	[bp+var_10]
		push	[bp+var_12]
		push	[bp+var_14]
		call	sub_11527
		add	sp, 14h
		cmp	word_39E06, 250h
		jl	loc_1CF52
		push	190h
		mov	ax, 280h
		sub	ax, word_39E06
		push	ax
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		call	sub_114CA
		add	sp, 8
		mov	word_39E08, 4
		mov	word_3A6CA, 0
		mov	word_39E06, 0
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jle	loc_1CF52

loc_1CD9D:
		push	large 30018h
		jmp	loc_1CF38
; ---------------------------------------------------------------------------

loc_1CDA6:
		cmp	word_3A6CA, 28h	; '('
		jnz	short loc_1CDB4
		cmp	word_39E08, 4
		jz	short loc_1CDBD

loc_1CDB4:
		cmp	word_39E08, 5
		jnz	loc_1CF57

loc_1CDBD:
		cmp	word_39E08, 4
		jnz	short loc_1CDD6
		mov	word_39E08, 5
		mov	word_39E12, 0
		mov	word_39E06, 0

loc_1CDD6:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	loc_1CF57
		mov	word_39916, 6
		mov	ax, word_39E06
		mov	[bp+var_1C], ax
		mov	ax, word_398F4
		add	ax, 1Ch
		mov	[bp+var_1E], ax
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	[bp+var_20], ax
		mov	ax, word_39E06
		add	ax, 0FFF0h
		mov	[bp+var_22], ax
		mov	ax, word_398F4
		add	ax, 1Ch
		mov	[bp+var_24], ax
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	[bp+var_26], ax
		push	190h
		push	[bp+var_22]
		push	[bp+var_24]
		push	ax
		call	sub_114CA
		push	large 0E00007h
		push	190h
		push	[bp+var_1C]
		push	[bp+var_1E]
		push	[bp+var_20]
		call	sub_11527
		mov	ax, 280h
		sub	ax, word_39E06
		mov	[bp+var_28], ax
		mov	ax, word_398F4
		add	ax, 1Ch
		mov	[bp+var_2A], ax
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	[bp+var_2C], ax
		mov	ax, 280h
		sub	ax, word_39E06
		add	ax, 10h
		mov	[bp+var_2E], ax
		mov	ax, word_398F4
		add	ax, 1Ch
		mov	[bp+var_30], ax
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	[bp+var_32], ax
		push	190h
		push	[bp+var_2E]
		push	[bp+var_30]
		push	ax
		call	sub_114CA
		push	large 0E00007h
		push	190h
		push	[bp+var_28]
		push	[bp+var_2A]
		push	[bp+var_2C]
		call	sub_11527
		add	sp, 28h
		cmp	word_39E06, 120h
		jl	loc_1CF52
		push	190h
		push	word_39E06
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		call	sub_114CA
		push	190h
		mov	ax, 280h
		sub	ax, word_39E06
		push	ax
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		call	sub_114CA
		add	sp, 10h
		mov	word_39E08, 6
		mov	word_3A6CA, 0
		mov	word_39E06, 0
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_1CF29
		push	large 30018h
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_1CF29:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_1CF52
		push	large 4001Ch

loc_1CF38:
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_1CF52:
		add	word_39E06, 10h

loc_1CF57:
		push	large 0
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CF75
		cmp	word_3984E, 0
		jnz	short loc_1CFD5

loc_1CF75:
		push	ds
		push	offset dword_3985C
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CF8D
		cmp	word_39880, 0
		jnz	short loc_1CFD5

loc_1CF8D:
		push	ds
		push	offset dword_3988E
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CFA5
		cmp	word_398B2, 0
		jnz	short loc_1CFD5

loc_1CFA5:
		push	ds
		push	offset word_398C0
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CFBD
		cmp	word_398E4, 0
		jnz	short loc_1CFD5

loc_1CFBD:
		push	ds
		push	offset word_398F2
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1CFDA
		cmp	word_39916, 0
		jz	short loc_1CFDA

loc_1CFD5:
		mov	ax, 1
		jmp	short loc_1CFDC
; ---------------------------------------------------------------------------

loc_1CFDA:
		xor	ax, ax

loc_1CFDC:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_35B54
		push	ds
		push	offset word_39E04
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 2
		jle	short loc_1D011
		cmp	word_39E08, 6
		jnz	loc_1DFFC

loc_1D011:
		mov	byte_3A6CE, 0Ah
		mov	word_3A6CA, 0
		mov	word_39E04, 0
		mov	word_39E08, 1
		mov	byte ptr word_39E14, 0
		mov	word_39E10, 0
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1D036:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 0Ah
		jnz	short loc_1D08C
		push	ds
		push	offset word_3A6CA
		mov	al, byte ptr word_39E14
		cbw
		push	ax
		push	word_39E08
		push	1Fh
		push	0
		nop
		push	cs
		call	near ptr sub_1DFFF
		add	sp, 0Ch
		cmp	word_3A6CA, 46h	; 'F'
		jl	loc_1DFFC
		mov	byte_3A6CE, 0Bh
		mov	word_39E08, 0
		mov	byte ptr word_39E14, 1Fh

loc_1D071:
		mov	word_3A6CA, 0
		mov	word_39E04, 0
		mov	word_39E06, 0
		mov	word_39E12, 0
		jmp	loc_1D8C1
; ---------------------------------------------------------------------------

loc_1D08C:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 0Bh
		jnz	loc_1D852
		inc	word_3A6CA
		inc	word_39E04
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3988E
		call	sub_16733
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398C0
		call	sub_16733
		add	sp, 30h
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398F2
		call	sub_16733
		add	sp, 0Ch
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1D116
		mov	word_3984E, 4
		jmp	short loc_1D135
; ---------------------------------------------------------------------------

loc_1D116:
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1D12F
		mov	word_3984E, 5
		jmp	short loc_1D135
; ---------------------------------------------------------------------------

loc_1D12F:
		mov	word_3984E, 3

loc_1D135:
		mov	ax, word ptr dword_3985C
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1D14C
		mov	word_39880, 4
		jmp	short loc_1D16B
; ---------------------------------------------------------------------------

loc_1D14C:
		mov	ax, word ptr dword_3985C
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1D165
		mov	word_39880, 5
		jmp	short loc_1D16B
; ---------------------------------------------------------------------------

loc_1D165:
		mov	word_39880, 3

loc_1D16B:
		mov	ax, word ptr dword_3988E
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1D182
		mov	word_398B2, 4
		jmp	short loc_1D1A1
; ---------------------------------------------------------------------------

loc_1D182:
		mov	ax, word ptr dword_3988E
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1D19B
		mov	word_398B2, 5
		jmp	short loc_1D1A1
; ---------------------------------------------------------------------------

loc_1D19B:
		mov	word_398B2, 3

loc_1D1A1:
		mov	ax, word_398C0
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1D1B8
		mov	word_398E4, 4
		jmp	short loc_1D1D7
; ---------------------------------------------------------------------------

loc_1D1B8:
		mov	ax, word_398C0
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1D1D1
		mov	word_398E4, 5
		jmp	short loc_1D1D7
; ---------------------------------------------------------------------------

loc_1D1D1:
		mov	word_398E4, 3

loc_1D1D7:
		mov	ax, word_398F2
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1D1EE
		mov	word_39916, 4
		jmp	short loc_1D20D
; ---------------------------------------------------------------------------

loc_1D1EE:
		mov	ax, word_398F2
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1D207
		mov	word_39916, 5
		jmp	short loc_1D20D
; ---------------------------------------------------------------------------

loc_1D207:
		mov	word_39916, 3

loc_1D20D:
		cmp	word_3A6CA, 64h	; 'd'
		jz	short loc_1D21D
		cmp	word_39E08, 1
		jnz	loc_1D2F6

loc_1D21D:
		cmp	word_39E08, 0
		jnz	short loc_1D230
		mov	word_39E08, 1
		mov	ax, word_36C26
		mov	word_39E0A, ax

loc_1D230:
		push	7
		mov	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		call	sub_114E3
		push	7
		mov	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		call	sub_114E3
		push	7
		mov	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		push	ax
		call	sub_114E3
		push	7
		mov	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_398C0
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 1Ch
		push	ax
		call	sub_114E3
		push	7
		mov	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		mov	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_398C0
		add	ax, 1Ch
		push	ax
		call	sub_114E3
		add	sp, 32h
		cmp	word_3A6CA, 8Ch	; '�
		jnz	short loc_1D2F6
		mov	word_39E08, 2
		mov	word_39E06, 0

loc_1D2F6:
		cmp	word_39E08, 2
		jnz	loc_1D63F
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	loc_1D63F
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		add	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		call	sub_114CA
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		add	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		sub	ax, word_39E06
		push	ax
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		cwd
		idiv	bx
		add	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		call	sub_114CA
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		add	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, word_39E06
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		cwd
		idiv	bx
		add	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		sub	ax, word_39E06
		push	ax
		call	sub_114CA
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		mov	dx, word_398C0
		add	dx, 1Ch
		sub	dx, ax
		push	dx
		mov	ax, word_39E06
		cwd
		idiv	bx
		add	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, word_39E06
		add	ax, 1Ch
		push	ax
		call	sub_114CA
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		mov	dx, word_398C0
		add	dx, 1Ch
		sub	dx, ax
		push	dx
		call	sub_114CA
		add	word_39E06, 8
		push	7
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		add	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		call	sub_114E3
		add	sp, 32h
		push	7
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		add	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		sub	ax, word_39E06
		push	ax
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		cwd
		idiv	bx
		add	ax, word ptr dword_3988E
		add	ax, 1Ch
		push	ax
		call	sub_114E3
		push	7
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		add	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, word_39E06
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		cwd
		idiv	bx
		add	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		sub	ax, word_39E06
		push	ax
		call	sub_114E3
		push	7
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		mov	dx, word_398C0
		add	dx, 1Ch
		sub	dx, ax
		push	dx
		mov	ax, word_39E06
		cwd
		idiv	bx
		add	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, word_39E06
		add	ax, 1Ch
		push	ax
		call	sub_114E3
		push	7
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398F4
		add	ax, 1Ch
		push	ax
		mov	ax, word_398F2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398C2
		add	ax, 1Ch
		push	ax
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		mov	dx, word_398C0
		add	dx, 1Ch
		sub	dx, ax
		push	dx
		call	sub_114E3
		add	sp, 28h
		cmp	word_39E06, 0A0h ; '?'
		jle	loc_1D63F
		mov	ax, word_398F2
		add	ax, 1Ch
		mov	word_39DE6, ax
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398F4
		add	ax, 1Ch
		mov	word_39DF0, ax
		mov	ax, word_39E06
		mov	bx, 3
		cwd
		idiv	bx
		add	ax, word ptr dword_3988E
		add	ax, 1Ch
		mov	word_39DE8, ax
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word ptr dword_3988E+2
		add	ax, 1Ch
		mov	word_39DF2, ax
		mov	ax, word ptr dword_3985C
		add	ax, 1Ch
		sub	ax, word_39E06
		mov	word_39DEA, ax
		mov	ax, word_39E06
		cwd
		idiv	bx
		add	ax, word ptr dword_3985C+2
		add	ax, 1Ch
		mov	word_39DF4, ax
		mov	ax, word ptr dword_3982A
		add	ax, word_39E06
		add	ax, 1Ch
		mov	word_39DEC, ax
		mov	ax, word_39E06
		cwd
		idiv	bx
		add	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		mov	word_39DF6, ax
		mov	ax, word_39E06
		cwd
		idiv	bx
		mov	dx, word_398C0
		add	dx, 1Ch
		sub	dx, ax
		mov	word_39DEE, dx
		mov	ax, word_39E06
		cwd
		sub	ax, dx
		sar	ax, 1
		add	ax, word_398C2
		add	ax, 1Ch
		mov	word_39DF8, ax
		mov	word_39E08, 3

loc_1D63F:
		push	large 0
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1D65D
		cmp	word_3984E, 0
		jnz	short loc_1D6BD

loc_1D65D:
		push	ds
		push	offset dword_3985C
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1D675
		cmp	word_39880, 0
		jnz	short loc_1D6BD

loc_1D675:
		push	ds
		push	offset dword_3988E
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1D68D
		cmp	word_398B2, 0
		jnz	short loc_1D6BD

loc_1D68D:
		push	ds
		push	offset word_398C0
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1D6A5
		cmp	word_398E4, 0
		jnz	short loc_1D6BD

loc_1D6A5:
		push	ds
		push	offset word_398F2
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1D6C2
		cmp	word_39916, 0
		jz	short loc_1D6C2

loc_1D6BD:
		mov	ax, 1
		jmp	short loc_1D6C4
; ---------------------------------------------------------------------------

loc_1D6C2:
		xor	ax, ax

loc_1D6C4:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_35B54
		push	ds
		push	offset word_39E04
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	short loc_1D75D
		call	sub_12589
		push	ds
		push	offset unk_37635
		call	sub_30DEE
		add	sp, 4
		xor	si, si
		jmp	short loc_1D74B
; ---------------------------------------------------------------------------

loc_1D705:
		mov	bx, si
		imul	bx, 45h
		cmp	word ptr [bx+483Ah], 0
		jz	short loc_1D74A
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4804h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4800h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+480Ch]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4808h]
		call	sub_F2F5
		add	sp, 8
		mov	bx, si
		imul	bx, 45h
		mov	word ptr [bx+483Ah], 0
		jmp	short $+2

loc_1D74A:
		inc	si

loc_1D74B:
		cmp	si, 5
		jl	short loc_1D705
		call	sub_12A3A
		push	3
		call	sub_20754
		pop	cx

loc_1D75D:
		cmp	word_3A6C8, 0
		jle	short loc_1D76D
		cmp	word_39E08, 3
		jnz	loc_1DFFC

loc_1D76D:
		cmp	word_35B54, 0
		jnz	loc_1DFFC
		mov	byte_3A6CE, 0Ch
		mov	word_39E08, 0
		mov	byte ptr word_39E14, 1
		mov	word_3A6CA, 0
		mov	word_39E04, 0
		mov	word_39E06, 0
		mov	ax, word_39DF0
		add	ax, 40h	; '@'
		mov	word_39DFE, ax
		mov	ax, word_39DE6
		mov	word_39DFC, ax
		mov	word_39DFA, 40h	; '@'
		xor	si, si
		jmp	short loc_1D808
; ---------------------------------------------------------------------------

loc_1D7B1:
		movsx	eax, word_39DFA
		mov	bx, si
		imul	bx, 33h
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		add	ax, word_39DFC
		mov	bx, si
		add	bx, bx
		mov	[bx+5446h], ax
		movsx	eax, word_39DFA
		mov	bx, si
		imul	bx, 33h
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		add	ax, word_39DFE
		mov	bx, si
		add	bx, bx
		mov	[bx+5450h], ax
		inc	si

loc_1D808:
		cmp	si, 5
		jl	short loc_1D7B1
		mov	ax, word_39DF8
		mov	word_39DF2, ax
		cmp	byte_34A30, 0
		jnz	short loc_1D81F
		mov	ax, 18h
		jmp	short loc_1D84C
; ---------------------------------------------------------------------------

loc_1D81F:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_1D82D
		mov	ax, 0Eh
		jmp	short loc_1D84C
; ---------------------------------------------------------------------------

loc_1D82D:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_1D83B
		mov	ax, 0Ah
		jmp	short loc_1D84C
; ---------------------------------------------------------------------------

loc_1D83B:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_1D849
		mov	ax, 8
		jmp	short loc_1D84C
; ---------------------------------------------------------------------------

loc_1D849:
		mov	ax, 0Eh

loc_1D84C:
		mov	word_39DE4, ax
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1D852:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 0Ch
		jnz	short loc_1D8D5
		inc	word_39E04
		push	ds
		push	offset word_3A6CA
		push	large 1
		push	1
		push	1Eh
		nop
		push	cs
		call	near ptr sub_1DFFF
		add	sp, 0Ch
		mov	ax, word_39E04
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1D88A
		sub	word_39DFE, 3
		push	0C0h ; '?'
		call	sub_1B8DE

loc_1D88A:
		cmp	word_3A6CA, 46h	; 'F'
		jl	loc_1DFFC
		mov	byte_3A6CE, 0Dh
		mov	word_39E08, 0
		mov	byte ptr word_39E14, 1
		mov	word_3A6CA, 0
		mov	word_39E04, 0
		mov	word_39E06, 0
		mov	word_39E12, 0
		mov	word_39E0E, 0

loc_1D8C1:
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4
		call	sub_232A4
		jmp	loc_1DFFC
; ---------------------------------------------------------------------------

loc_1D8D5:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 0Dh
		jnz	loc_1DFFC
		inc	word_3A6CA
		inc	word_39E04
		inc	word_39E06
		mov	al, byte ptr word_39E14
		cbw
		and	ax, 1
		cmp	ax, 1
		jnz	short loc_1D90D
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16733
		add	sp, 0Ch

loc_1D90D:
		mov	al, byte ptr word_39E14
		cbw
		and	ax, 2
		cmp	ax, 2
		jnz	short loc_1D92E
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_16733
		add	sp, 0Ch

loc_1D92E:
		mov	al, byte ptr word_39E14
		cbw
		and	ax, 4
		cmp	ax, 4
		jnz	short loc_1D94F
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3988E
		call	sub_16733
		add	sp, 0Ch

loc_1D94F:
		mov	al, byte ptr word_39E14
		cbw
		and	ax, 8
		cmp	ax, 8
		jnz	short loc_1D970
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398C0
		call	sub_16733
		add	sp, 0Ch

loc_1D970:
		mov	al, byte ptr word_39E14
		cbw
		and	ax, 10h
		cmp	ax, 10h
		jnz	short loc_1D991
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398F2
		call	sub_16733
		add	sp, 0Ch

loc_1D991:
		cmp	word_35B54, 0
		jz	short loc_1D9BC
		cmp	word_39E0E, 0
		jnz	short loc_1D9BC
		shl	byte ptr word_39E14, 1
		mov	word_39E0E, 1
		mov	al, byte ptr word_39E14
		cbw
		cmp	ax, 20h	; ' '
		jnz	loc_1DB36
		mov	byte ptr word_39E14, 1
		jmp	loc_1DB36
; ---------------------------------------------------------------------------

loc_1D9BC:
		cmp	word_39E0E, 0
		jle	short loc_1DA05
		push	ds
		push	offset word_39E0E
		push	large 30003h
		push	word_39E14
		mov	al, byte ptr word_39E14
		cbw
		cmp	ax, 1
		jnz	short loc_1D9DE
		mov	al, 10h
		jmp	short loc_1D9E4
; ---------------------------------------------------------------------------

loc_1D9DE:
		mov	al, byte ptr word_39E14
		cbw
		sar	ax, 1

loc_1D9E4:
		push	ax
		nop
		push	cs
		call	near ptr sub_1DFFF
		add	sp, 0Ch
		cmp	word_39E0E, 46h	; 'F'
		jl	loc_1DB36
		mov	word_39E0E, 0
		mov	word_39E06, 0
		jmp	loc_1DB36
; ---------------------------------------------------------------------------

loc_1DA05:
		test	byte ptr word_39E14, 1
		jz	short loc_1DA42
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1DA23
		mov	word_3984E, 4
		jmp	short loc_1DA42
; ---------------------------------------------------------------------------

loc_1DA23:
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1DA3C
		mov	word_3984E, 5
		jmp	short loc_1DA42
; ---------------------------------------------------------------------------

loc_1DA3C:
		mov	word_3984E, 3

loc_1DA42:
		test	byte ptr word_39E14, 2
		jz	short loc_1DA7F
		mov	ax, word ptr dword_3985C
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1DA60
		mov	word_39880, 4
		jmp	short loc_1DA7F
; ---------------------------------------------------------------------------

loc_1DA60:
		mov	ax, word ptr dword_3985C
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1DA79
		mov	word_39880, 5
		jmp	short loc_1DA7F
; ---------------------------------------------------------------------------

loc_1DA79:
		mov	word_39880, 3

loc_1DA7F:
		test	byte ptr word_39E14, 4
		jz	short loc_1DABC
		mov	ax, word ptr dword_3988E
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1DA9D
		mov	word_398B2, 4
		jmp	short loc_1DABC
; ---------------------------------------------------------------------------

loc_1DA9D:
		mov	ax, word ptr dword_3988E
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1DAB6
		mov	word_398B2, 5
		jmp	short loc_1DABC
; ---------------------------------------------------------------------------

loc_1DAB6:
		mov	word_398B2, 3

loc_1DABC:
		test	byte ptr word_39E14, 8
		jz	short loc_1DAF9
		mov	ax, word_398C0
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1DADA
		mov	word_398E4, 4
		jmp	short loc_1DAF9
; ---------------------------------------------------------------------------

loc_1DADA:
		mov	ax, word_398C0
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1DAF3
		mov	word_398E4, 5
		jmp	short loc_1DAF9
; ---------------------------------------------------------------------------

loc_1DAF3:
		mov	word_398E4, 3

loc_1DAF9:
		test	byte ptr word_39E14, 10h
		jz	short loc_1DB36
		mov	ax, word_398F2
		add	ax, 20h	; ' '
		sub	ax, word_36C26
		cmp	ax, 20h	; ' '
		jle	short loc_1DB17
		mov	word_39916, 4
		jmp	short loc_1DB36
; ---------------------------------------------------------------------------

loc_1DB17:
		mov	ax, word_398F2
		add	ax, 20h	; ' '
		mov	dx, word_36C26
		sub	dx, ax
		cmp	dx, 20h	; ' '
		jle	short loc_1DB30
		mov	word_39916, 5
		jmp	short loc_1DB36
; ---------------------------------------------------------------------------

loc_1DB30:
		mov	word_39916, 3

loc_1DB36:
		cmp	word_39E08, 0
		jnz	short loc_1DBAB
		mov	ax, word_3A6CA
		cwd
		idiv	word_39DE4
		or	dx, dx
		jnz	short loc_1DBAB
		cmp	word_39E10, 6
		jz	short loc_1DBAB
		cmp	word_39E10, 9
		jz	short loc_1DBAB
		xor	si, si
		jmp	short loc_1DBA6
; ---------------------------------------------------------------------------

loc_1DB5B:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+5450h]
		sub	ax, word_39DFE
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+5446h]
		sub	ax, word_39DFC
		push	ax
		call	iatan2
		mov	byte ptr word_39E16, al
		push	large 0
		push	large 0
		push	30h ; '0'
		push	word_39E16
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5450h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5446h]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_1DBA6:
		cmp	si, 5
		jl	short loc_1DB5B

loc_1DBAB:
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1DBC5
		cmp	word_39E10, 0
		jnz	short loc_1DBC5
		mov	word_39E10, 1
		mov	word_3A6CA, 0

loc_1DBC5:
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1DBDF
		cmp	word_39E10, 7
		jnz	short loc_1DBDF
		mov	word_39E10, 8
		mov	word_3A6CA, 0

loc_1DBDF:
		cmp	word_39E10, 1
		jz	short loc_1DBF4
		cmp	word_39E10, 3
		jz	short loc_1DBF4
		cmp	word_39E10, 5
		jnz	short loc_1DC2A

loc_1DBF4:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DC18
		mov	ax, word_3A6CA
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	ax, 2
		add	word_39E12, ax
		push	word_39E12
		call	sub_1B8DE

loc_1DC18:
		cmp	word_3A6CA, 0C8h ; '?'
		jl	short loc_1DC2A
		inc	word_39E10
		mov	word_3A6CA, 0

loc_1DC2A:
		cmp	word_39E10, 2
		jz	short loc_1DC38
		cmp	word_39E10, 4
		jnz	short loc_1DC6D

loc_1DC38:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DC5C
		mov	ax, word_3A6CA
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	ax, 2
		sub	word_39E12, ax
		push	word_39E12
		call	sub_1B8DE

loc_1DC5C:
		cmp	word_3A6CA, 0C8h ; '?'
		jl	loc_1DDD4
		inc	word_39E10
		jmp	loc_1DDAD
; ---------------------------------------------------------------------------

loc_1DC6D:
		cmp	word_39E10, 6
		jnz	loc_1DD70
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DCD0
		cmp	word_39DFE, 12Ch
		jge	short loc_1DCAB
		push	bx
		push	ds
		push	offset word_39E00
		push	ds
		push	offset word_39E02
		push	190h
		push	word_36C26
		push	word_39DFE
		push	word_39DFC
		call	sub_11FF0
		add	sp, 12h

loc_1DCAB:
		mov	ax, word_3A6CA
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	ax, 2
		add	word_39E12, ax
		mov	ax, word_39E00
		add	word_39DFE, ax
		mov	ax, word_39E02
		add	word_39DFC, ax
		push	word_39E12
		call	sub_1B8DE

loc_1DCD0:
		cmp	word_39DFE, 1A4h
		jl	loc_1DDD4
		mov	word_3A6CA, 0
		mov	byte_3A6CE, 0Ah
		mov	word_39E08, 3
		mov	byte ptr word_39E14, 3
		mov	word_39E10, 7
		mov	word_39E04, 0
		mov	word_39E06, 0
		push	word_39DF4
		push	word_39DEA
		push	word_39DF0
		push	word_39DE6
		call	sub_114CA
		push	word_39DF8
		push	word_39DEE
		push	word_39DF4
		push	word_39DEA
		call	sub_114CA
		push	word_39DF2
		push	word_39DE8
		push	word_39DF8
		push	word_39DEE
		call	sub_114CA
		push	word_39DF6
		push	word_39DEC
		push	word_39DF2
		push	word_39DE8
		call	sub_114CA
		push	word_39DF0
		push	word_39DE6
		push	word_39DF6
		push	word_39DEC
		call	sub_114CA
		add	sp, 28h
		jmp	short loc_1DDD4
; ---------------------------------------------------------------------------

loc_1DD70:
		cmp	word_39E10, 8
		jnz	short loc_1DDD4
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DD9F
		inc	word_39DFA
		mov	ax, word_3A6CA
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	ax, 2
		add	word_39E12, ax
		push	word_39E12
		call	sub_1B8DE

loc_1DD9F:
		cmp	word_3A6CA, 0C8h ; '?'
		jl	short loc_1DDD4
		mov	word_39E10, 9

loc_1DDAD:
		mov	word_3A6CA, 0
		push	4
		push	ds
		push	offset word_39E00
		push	ds
		push	offset word_39E02
		push	190h
		push	word_36C26
		push	word_39DFE
		push	word_39DFC
		call	sub_11FF0
		add	sp, 12h

loc_1DDD4:
		cmp	word_39E10, 9
		jnz	loc_1DED5
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1DE37
		cmp	word_39DFE, 104h
		jge	short loc_1DE12
		push	bx
		push	ds
		push	offset word_39E00
		push	ds
		push	offset word_39E02
		push	190h
		push	word_36C26
		push	word_39DFE
		push	word_39DFC
		call	sub_11FF0
		add	sp, 12h

loc_1DE12:
		mov	ax, word_39E00
		add	word_39DFE, ax
		mov	ax, word_39E02
		add	word_39DFC, ax
		mov	ax, word_3A6CA
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		add	ax, 2
		add	word_39E12, ax
		push	word_39E12
		call	sub_1B8DE

loc_1DE37:
		cmp	word_39DFE, 1A4h
		jl	loc_1DED5
		mov	word_39E10, 0
		mov	word_3A6CA, 0
		mov	byte_3A6CE, 0Ah
		mov	word_39E08, 3
		mov	byte ptr word_39E14, 3
		mov	word_39E04, 0
		mov	word_39E06, 0
		push	word_39DF4
		push	word_39DEA
		push	word_39DF0
		push	word_39DE6
		call	sub_114CA
		push	word_39DF8
		push	word_39DEE
		push	word_39DF4
		push	word_39DEA
		call	sub_114CA
		push	word_39DF2
		push	word_39DE8
		push	word_39DF8
		push	word_39DEE
		call	sub_114CA
		push	word_39DF6
		push	word_39DEC
		push	word_39DF2
		push	word_39DE8
		call	sub_114CA
		push	word_39DF0
		push	word_39DE6
		push	word_39DF6
		push	word_39DEC
		call	sub_114CA
		add	sp, 28h

loc_1DED5:
		push	large 0
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1DEF3
		cmp	word_3984E, 0
		jnz	short loc_1DF53

loc_1DEF3:
		push	ds
		push	offset dword_3985C
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1DF0B
		cmp	word_39880, 0
		jnz	short loc_1DF53

loc_1DF0B:
		push	ds
		push	offset dword_3988E
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1DF23
		cmp	word_398B2, 0
		jnz	short loc_1DF53

loc_1DF23:
		push	ds
		push	offset word_398C0
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1DF3B
		cmp	word_398E4, 0
		jnz	short loc_1DF53

loc_1DF3B:
		push	ds
		push	offset word_398F2
		call	sub_16970
		add	sp, 4
		cmp	ax, 1
		jnz	short loc_1DF58
		cmp	word_39916, 0
		jz	short loc_1DF58

loc_1DF53:
		mov	ax, 1
		jmp	short loc_1DF5A
; ---------------------------------------------------------------------------

loc_1DF58:
		xor	ax, ax

loc_1DF5A:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_35B54
		push	ds
		push	offset word_39E04
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	short loc_1DFFC
		call	sub_12589
		push	ds
		push	offset unk_37635
		call	sub_30DEE
		push	ds
		push	offset unk_39EC4
		call	sub_21EFF
		add	sp, 8
		xor	si, si
		jmp	short loc_1DFEA
; ---------------------------------------------------------------------------

loc_1DFA4:
		mov	bx, si
		imul	bx, 45h
		cmp	word ptr [bx+483Ah], 0
		jz	short loc_1DFE9
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4804h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4800h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+480Ch]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4808h]
		call	sub_F2F5
		add	sp, 8
		mov	bx, si
		imul	bx, 45h
		mov	word ptr [bx+483Ah], 0
		jmp	short $+2

loc_1DFE9:
		inc	si

loc_1DFEA:
		cmp	si, 5
		jl	short loc_1DFA4
		call	sub_12A3A
		push	3
		call	sub_20754
		pop	cx

loc_1DFFC:
		pop	si
		leave
		retf
sub_1BA32	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1DFFF	proc far

arg_0		= byte ptr  6
arg_2		= byte ptr  8
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= dword	ptr  0Eh

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_6]
		mov	al, [bp+arg_0]
		cbw
		and	ax, 1
		cmp	ax, 1
		jz	short loc_1E022
		mov	al, [bp+arg_2]
		cbw
		and	ax, 1
		cmp	ax, 1
		jnz	short loc_1E037

loc_1E022:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16733
		add	sp, 0Ch

loc_1E037:
		mov	al, [bp+arg_0]
		cbw
		and	ax, 2
		cmp	ax, 2
		jz	short loc_1E04F
		mov	al, [bp+arg_2]
		cbw
		and	ax, 2
		cmp	ax, 2
		jnz	short loc_1E064

loc_1E04F:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_16733
		add	sp, 0Ch

loc_1E064:
		mov	al, [bp+arg_0]
		cbw
		and	ax, 4
		cmp	ax, 4
		jz	short loc_1E07C
		mov	al, [bp+arg_2]
		cbw
		and	ax, 4
		cmp	ax, 4
		jnz	short loc_1E091

loc_1E07C:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3988E
		call	sub_16733
		add	sp, 0Ch

loc_1E091:
		mov	al, [bp+arg_0]
		cbw
		and	ax, 8
		cmp	ax, 8
		jz	short loc_1E0A9
		mov	al, [bp+arg_2]
		cbw
		and	ax, 8
		cmp	ax, 8
		jnz	short loc_1E0BE

loc_1E0A9:
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398C0
		call	sub_16733
		add	sp, 0Ch

loc_1E0BE:
		mov	al, [bp+arg_0]
		cbw
		and	ax, 10h
		cmp	ax, 10h
		jz	short loc_1E0D6
		mov	al, [bp+arg_2]
		cbw
		and	ax, 10h
		cmp	ax, 10h
		jnz	short loc_1E0EB

loc_1E0D6:
		push	large 30000h
		push	large 0
		push	ds
		push	offset word_398F2
		call	sub_16733
		add	sp, 0Ch

loc_1E0EB:
		les	bx, [bp+arg_8]
		inc	word ptr es:[bx]
		mov	ax, es:[bx]
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jz	short loc_1E12D
		cmp	si, 3
		jge	short loc_1E114
		mov	al, [si+71Dh]
		cbw
		or	ax, ax
		jle	short loc_1E114
		dec	byte ptr [si+71Dh]
		dec	byte ptr [si+5219h]

loc_1E114:
		cmp	di, 3
		jge	short loc_1E121
		inc	byte ptr [di+71Dh]
		inc	byte ptr [di+5219h]

loc_1E121:
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4

loc_1E12D:
		les	bx, [bp+arg_8]
		cmp	word ptr es:[bx], 14h
		jnz	loc_1E1F1
		test	[bp+arg_0], 1
		jz	short loc_1E144
		mov	word_3984E, 2

loc_1E144:
		test	[bp+arg_0], 2
		jz	short loc_1E150
		mov	word_39880, 2

loc_1E150:
		test	[bp+arg_0], 4
		jz	short loc_1E15C
		mov	word_398B2, 2

loc_1E15C:
		test	[bp+arg_0], 8
		jz	short loc_1E168
		mov	word_398E4, 2

loc_1E168:
		test	[bp+arg_0], 10h
		jz	short loc_1E174
		mov	word_39916, 2

loc_1E174:
		test	[bp+arg_2], 1
		jz	short loc_1E180
		mov	word_3984E, 1

loc_1E180:
		test	[bp+arg_2], 2
		jz	short loc_1E18C
		mov	word_39880, 1

loc_1E18C:
		test	[bp+arg_2], 4
		jz	short loc_1E198
		mov	word_398B2, 1

loc_1E198:
		test	[bp+arg_2], 8
		jz	short loc_1E1A4
		mov	word_398E4, 1

loc_1E1A4:
		test	[bp+arg_2], 10h
		jz	short loc_1E1B0
		mov	word_39916, 1

loc_1E1B0:
		test	[bp+arg_2], 1
		jz	short loc_1E1BC
		mov	word_39852, 0

loc_1E1BC:
		test	[bp+arg_2], 2
		jz	short loc_1E1C8
		mov	word_39884, 0

loc_1E1C8:
		test	[bp+arg_2], 4
		jz	short loc_1E1D4
		mov	word_398B6, 0

loc_1E1D4:
		test	[bp+arg_2], 8
		jz	short loc_1E1E0
		mov	word_398E8, 0

loc_1E1E0:
		test	[bp+arg_2], 10h
		jz	loc_1E336
		mov	word_3991A, 0
		jmp	loc_1E336
; ---------------------------------------------------------------------------

loc_1E1F1:
		les	bx, [bp+arg_8]
		cmp	word ptr es:[bx], 28h ;	'('
		jnz	loc_1E2B5
		test	[bp+arg_0], 1
		jz	short loc_1E208
		mov	word_3984E, 1

loc_1E208:
		test	[bp+arg_0], 2
		jz	short loc_1E214
		mov	word_39880, 1

loc_1E214:
		test	[bp+arg_0], 4
		jz	short loc_1E220
		mov	word_398B2, 1

loc_1E220:
		test	[bp+arg_0], 8
		jz	short loc_1E22C
		mov	word_398E4, 1

loc_1E22C:
		test	[bp+arg_0], 10h
		jz	short loc_1E238
		mov	word_39916, 1

loc_1E238:
		test	[bp+arg_2], 1
		jz	short loc_1E244
		mov	word_3984E, 2

loc_1E244:
		test	[bp+arg_2], 2
		jz	short loc_1E250
		mov	word_39880, 2

loc_1E250:
		test	[bp+arg_2], 4
		jz	short loc_1E25C
		mov	word_398B2, 2

loc_1E25C:
		test	[bp+arg_2], 8
		jz	short loc_1E268
		mov	word_398E4, 2

loc_1E268:
		test	[bp+arg_2], 10h
		jz	short loc_1E274
		mov	word_39916, 2

loc_1E274:
		test	[bp+arg_0], 1
		jz	short loc_1E280
		mov	word_39852, 1

loc_1E280:
		test	[bp+arg_0], 2
		jz	short loc_1E28C
		mov	word_39884, 1

loc_1E28C:
		test	[bp+arg_0], 4
		jz	short loc_1E298
		mov	word_398B6, 1

loc_1E298:
		test	[bp+arg_0], 8
		jz	short loc_1E2A4
		mov	word_398E8, 1

loc_1E2A4:
		test	[bp+arg_0], 10h
		jz	loc_1E336
		mov	word_3991A, 1
		jmp	loc_1E336
; ---------------------------------------------------------------------------

loc_1E2B5:
		les	bx, [bp+arg_8]
		cmp	word ptr es:[bx], 3Ch ;	'<'
		jnz	short loc_1E336
		test	[bp+arg_0], 1
		jz	short loc_1E2CA
		mov	word_3984E, 0

loc_1E2CA:
		test	[bp+arg_0], 2
		jz	short loc_1E2D6
		mov	word_39880, 0

loc_1E2D6:
		test	[bp+arg_0], 4
		jz	short loc_1E2E2
		mov	word_398B2, 0

loc_1E2E2:
		test	[bp+arg_0], 8
		jz	short loc_1E2EE
		mov	word_398E4, 0

loc_1E2EE:
		test	[bp+arg_0], 10h
		jz	short loc_1E2FA
		mov	word_39916, 0

loc_1E2FA:
		test	[bp+arg_2], 1
		jz	short loc_1E306
		mov	word_3984E, 6

loc_1E306:
		test	[bp+arg_2], 2
		jz	short loc_1E312
		mov	word_39880, 6

loc_1E312:
		test	[bp+arg_2], 4
		jz	short loc_1E31E
		mov	word_398B2, 6

loc_1E31E:
		test	[bp+arg_2], 8
		jz	short loc_1E32A
		mov	word_398E4, 6

loc_1E32A:
		test	[bp+arg_2], 10h
		jz	short loc_1E336

loc_1E330:
		mov	word_39916, 6

loc_1E336:
		pop	di
		pop	si
		pop	bp
		retf
sub_1DFFF	endp

seg028		ends

; ===========================================================================

; Segment type:	Pure code
seg029		segment	byte public 'CODE' use16
		assume cs:seg029
		;org 0Ah
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E33A	proc far
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	word_39854, 1
		push	0
		push	ds
		push	offset aBoss3_1_bos ; "boss3_1.bos"
		push	ds
		push	offset dword_3982A
		call	sub_1568F
		mov	word_39854, 0
		mov	word_39886, 1
		push	1
		push	ds
		push	offset aBoss3_2_bos ; "boss3_2.bos"
		push	ds
		push	offset dword_3985C
		call	sub_1568F
		mov	word_39886, 0
		push	ds
		push	offset aBoss3_grp_0 ; "boss3.grp"
		call	sub_10C51
		add	sp, 18h
		xor	si, si
		jmp	short loc_1E3A2
; ---------------------------------------------------------------------------

loc_1E385:
		xor	di, di
		jmp	short loc_1E39C
; ---------------------------------------------------------------------------

loc_1E389:
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+di+6F0h]
		mov	bx, si
		imul	bx, 3
		mov	[bx+di+5414h], al
		inc	di

loc_1E39C:
		cmp	di, 3
		jl	short loc_1E389
		inc	si

loc_1E3A2:
		cmp	si, 10h
		jl	short loc_1E385
		nop
		push	cs
		call	near ptr sub_1E79B
		push	large 180002h
		call	sub_10814
		push	ds
		push	offset aBoss3_m_ptn_0 ;	"boss3_m.ptn"
		push	3
		call	sub_10888
		mov	byte_3A1B2, 0C0h ; '?'
		push	ds
		push	offset unk_39EC4
		call	sub_21EFF
		add	sp, 0Eh
		pop	di
		pop	si
		pop	bp
		retf
sub_1E33A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E3D7	proc far

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		cmp	byte_35B7A, 0
		jz	short locret_1E42F
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_1E42F
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A
		mov	[bp+var_4], ax
		mov	word ptr dword_3985C, ax
		mov	ax, [bp+var_2]
		mov	word ptr dword_3985C+2,	ax
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		mov	bx, 4
		cwd
		idiv	bx
		inc	dx
		mov	[bp+var_6], dx
		mov	ax, [bp+var_6]
		mov	word_39880, ax
		push	ax
		push	large [dword_3985C]
		push	ds
		push	offset dword_3985C
		call	sub_15F4A
		add	sp, 0Ah

locret_1E42F:
		leave
		retf
sub_1E3D7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E431	proc far

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		mov	byte_35B7A, 0
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A
		mov	[bp+var_4], ax
		mov	word ptr dword_3985C, ax
		mov	ax, [bp+var_2]
		mov	word ptr dword_3985C+2,	ax
		mov	word_39880, 0
		push	1
		call	sub_EA3E
		push	0
		push	large [dword_3985C]
		push	ds
		push	offset dword_3985C
		call	sub_1588A
		push	0
		call	sub_EA3E
		push	0
		push	large [dword_3985C]
		push	ds
		push	offset dword_3985C
		call	sub_1588A
		add	sp, 18h
		leave
		retf
sub_1E431	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E48B	proc far

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		cmp	byte_35B7A, 0
		jnz	short locret_1E4EA
		mov	byte_35B7A, 1
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A
		mov	[bp+var_4], ax
		mov	word ptr dword_3985C, ax
		mov	ax, [bp+var_2]
		mov	word ptr dword_3985C+2,	ax
		mov	word_39880, 1
		push	1
		call	sub_EA3E
		push	1
		push	large [dword_3985C]
		push	ds
		push	offset dword_3985C
		call	sub_1588A
		push	0
		call	sub_EA3E
		push	1
		push	large [dword_3985C]
		push	ds
		push	offset dword_3985C
		call	sub_1588A
		add	sp, 18h

locret_1E4EA:
		leave
		retf
sub_1E48B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E4EC	proc far
		push	bp
		mov	bp, sp
		push	1
		call	sub_EA3E
		push	word_3984E
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_1588A
		push	0
		call	sub_EA3E
		push	word_3984E
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_1588A
		add	sp, 18h
		pop	bp
		retf
sub_1E4EC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E526	proc far

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		push	si
		push	di
		mov	ax, word ptr dword_3982A
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_4], ax
		mov	[bp+var_6], 3
		push	1
		call	sub_EA3E
		pop	cx
		xor	di, di
		jmp	short loc_1E578
; ---------------------------------------------------------------------------

loc_1E549:
		xor	si, si
		jmp	short loc_1E572
; ---------------------------------------------------------------------------

loc_1E54D:
		mov	ax, [bp+var_6]
		add	ax, 80h	; '?'
		push	ax
		mov	ax, di
		shl	ax, 5
		add	ax, [bp+var_4]
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		push	ax
		call	sub_104C2
		add	sp, 6
		inc	[bp+var_6]
		inc	si

loc_1E572:
		cmp	si, 4
		jl	short loc_1E54D
		inc	di

loc_1E578:
		cmp	di, 5
		jl	short loc_1E549
		push	0
		call	sub_EA3E
		pop	cx
		pop	di
		pop	si
		leave
		retf
sub_1E526	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E589	proc far

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6

		enter	6, 0
		push	si
		push	di
		mov	di, 3
		mov	ax, word ptr dword_3982A
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_4], ax
		cmp	[bp+arg_0], 0
		jnz	short loc_1E5E1
		mov	[bp+var_6], 0
		jmp	short loc_1E5D9
; ---------------------------------------------------------------------------

loc_1E5AB:
		xor	si, si
		jmp	short loc_1E5D1
; ---------------------------------------------------------------------------

loc_1E5AF:
		lea	ax, [di+80h]
		push	ax
		mov	ax, [bp+var_6]
		shl	ax, 5
		add	ax, [bp+var_4]
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		push	ax
		call	sub_108EC
		add	sp, 6
		inc	di
		inc	si

loc_1E5D1:
		cmp	si, 4
		jl	short loc_1E5AF
		inc	[bp+var_6]

loc_1E5D9:
		cmp	[bp+var_6], 5
		jl	short loc_1E5AB
		jmp	short loc_1E655
; ---------------------------------------------------------------------------

loc_1E5E1:
		mov	di, 7
		xor	si, si
		jmp	short loc_1E628
; ---------------------------------------------------------------------------

loc_1E5E8:
		push	2
		lea	ax, [di+80h]
		push	ax
		mov	ax, [bp+var_4]
		add	ax, 30h	; '0'
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		push	ax
		call	sub_109B2
		push	3
		lea	ax, [di+80h]
		push	ax
		mov	ax, [bp+var_4]
		add	ax, 30h	; '0'
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		add	ax, 10h
		push	ax
		call	sub_109B2
		add	sp, 10h
		inc	di
		inc	si

loc_1E628:
		cmp	si, 4
		jl	short loc_1E5E8
		xor	si, si
		jmp	short loc_1E650
; ---------------------------------------------------------------------------

loc_1E631:
		lea	ax, [di+80h]
		push	ax
		mov	ax, [bp+var_4]
		add	ax, 40h	; '@'
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		push	ax
		call	sub_108EC
		add	sp, 6
		inc	di
		inc	si

loc_1E650:
		cmp	si, 4
		jl	short loc_1E631

loc_1E655:
		pop	di
		pop	si
		leave
		retf
sub_1E589	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E659	proc far

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6
arg_2		= word ptr  8

		enter	6, 0
		push	si
		push	di
		mov	di, [bp+arg_2]
		cmp	word_3A6CA, 0Ah
		jl	loc_1E735
		cmp	word_3A6CA, 0Ah
		jnz	short loc_1E691
		mov	[bp+var_4], di
		mov	ax, [bp+arg_0]
		mov	[bp+var_6], ax
		mov	word ptr dword_3982A, ax
		mov	ax, [bp+var_4]
		mov	word ptr dword_3982A+2,	ax
		push	cs
		call	near ptr sub_1E526
		lea	ax, [di+50h]
		mov	[bp+var_2], ax
		jmp	loc_1E735
; ---------------------------------------------------------------------------

loc_1E691:
		mov	al, byte_35B7B
		mov	ah, 0
		push	ax
		mov	ax, word_3A6CA
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	loc_1E735
		mov	al, byte_35B7C
		mov	ah, 0
		mov	dl, byte_35B7B
		mov	dh, 0
		push	dx
		cwd
		pop	bx
		idiv	bx
		mov	dx, word_3A6CA
		add	dx, 0FFF6h
		imul	dx
		mov	dx, 50h	; 'P'
		sub	dx, ax
		mov	[bp+var_2], dx
		cmp	[bp+var_2], 0
		jge	short loc_1E6D7
		mov	word_3A6CA, 0
		push	cs
		call	near ptr sub_1E4EC
		jmp	short loc_1E735
; ---------------------------------------------------------------------------

loc_1E6D7:
		xor	si, si
		jmp	short loc_1E718
; ---------------------------------------------------------------------------

loc_1E6DB:
		push	si
		push	word_3984E
		mov	ax, di
		add	ax, [bp+var_2]
		add	ax, si
		push	ax
		push	[bp+arg_0]
		push	ds
		push	offset dword_3982A
		call	sub_15CDD
		mov	ax, 9Fh	; '�
		sub	ax, si
		push	ax
		push	word_3984E
		lea	ax, [di+0A0h]
		sub	ax, [bp+var_2]
		sub	ax, si
		push	ax
		push	[bp+arg_0]
		push	ds
		push	offset dword_3982A
		call	sub_15CDD
		add	sp, 18h
		inc	si

loc_1E718:
		mov	al, byte_35B7C
		mov	ah, 0
		mov	dl, byte_35B7B
		mov	dh, 0
		push	dx
		cwd
		pop	bx
		idiv	bx
		mov	dx, word_3A6CA
		add	dx, 0FFF6h
		imul	dx
		cmp	ax, si
		jg	short loc_1E6DB

loc_1E735:
		pop	di
		pop	si
		leave
		retf
sub_1E659	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E739	proc far
		push	bp
		mov	bp, sp
		push	si
		cmp	word_3A6CA, 0Ah
		jl	short loc_1E798
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1E798
		mov	ax, word_3A6CA
		add	ax, 0FFF6h
		add	ax, ax
		mov	si, ax
		cmp	si, 50h	; 'P'
		jl	short loc_1E768
		mov	word_3A6CA, 0
		jmp	short loc_1E798
; ---------------------------------------------------------------------------

loc_1E768:
		push	8
		push	word_39832
		mov	ax, word ptr dword_3982A+2
		add	ax, si
		push	ax
		push	word ptr dword_3982A
		call	sub_10433
		push	8
		push	word_39832
		mov	ax, word ptr dword_3982A+2
		add	ax, 98h	; '�
		sub	ax, si
		push	ax
		push	word ptr dword_3982A
		call	sub_10433
		add	sp, 10h

loc_1E798:
		pop	si
		pop	bp
		retf
sub_1E739	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E79B	proc far
		push	bp
		mov	bp, sp
		call	sub_232A4
		mov	word_3984E, 0
		mov	word_39880, 1
		call	sub_EEF7
		push	large 1300040h
		push	large 2E00000h
		push	large 300040h
		push	100h
		push	ds
		push	offset dword_3982A
		call	sub_166D2
		mov	word_3983E, 20h	; ' '
		mov	word_39840, 60h	; '`'
		mov	word_39842, 20h	; ' '
		mov	word_39844, 80h	; '?'
		mov	word_39852, 0
		mov	word_3A6CA, 0
		mov	byte_3A6CE, 0
		mov	word_3A6C8, 0Ch
		mov	word_3A1E5, 6
		mov	word_3A1E7, 2
		push	large 700FFh
		call	sub_22264
		add	sp, 16h
		pop	bp
		retf
sub_1E79B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E81D	proc far
		push	bp
		mov	bp, sp
		push	0
		call	sub_169CB
		push	1
		call	sub_169CB
		push	2
		call	sub_108AB
		push	3
		call	sub_108AB
		add	sp, 8
		pop	bp
		retf
sub_1E81D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E841	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h

		push	bp
		mov	bp, sp
		mov	dx, [bp+arg_6]
		cmp	byte_34A30, 0
		jnz	short loc_1E853
		mov	ax, [bp+arg_4]
		jmp	short loc_1E87E
; ---------------------------------------------------------------------------

loc_1E853:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_1E860
		mov	ax, dx
		jmp	short loc_1E87E
; ---------------------------------------------------------------------------

loc_1E860:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_1E86E
		mov	ax, [bp+arg_8]
		jmp	short loc_1E87E
; ---------------------------------------------------------------------------

loc_1E86E:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_1E87C
		mov	ax, [bp+arg_A]
		jmp	short loc_1E87E
; ---------------------------------------------------------------------------

loc_1E87C:
		mov	ax, dx

loc_1E87E:
		les	bx, [bp+arg_0]
		mov	es:[bx], ax
		pop	bp
		retf
sub_1E841	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E886	proc near

arg_0		= word ptr  4
arg_2		= byte ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah
arg_8		= word ptr  0Ch
arg_A		= dword	ptr  0Eh
arg_E		= dword	ptr  12h

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_0]
		xor	cx, cx
		jmp	short loc_1E8FE
; ---------------------------------------------------------------------------

loc_1E895:
		movsx	eax, si
		mov	dl, [bp+arg_2]
		mov	dh, 0
		and	dx, 0FFh
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		add	ax, [bp+arg_8]
		mov	dx, cx
		add	dx, dx
		les	bx, [bp+arg_E]
		add	bx, dx
		mov	es:[bx], ax
		movsx	eax, si
		mov	dl, [bp+arg_2]
		mov	dh, 0
		and	dx, 0FFh
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		add	ax, [bp+arg_6]
		mov	dx, cx
		add	dx, dx
		les	bx, [bp+arg_A]
		add	bx, dx
		mov	es:[bx], ax
		mov	ax, 100h
		cwd
		idiv	di
		add	al, [bp+arg_2]
		mov	[bp+arg_2], al
		inc	cx

loc_1E8FE:
		cmp	cx, di
		jl	short loc_1E895
		pop	di
		pop	si
		pop	bp
		retn	12h
sub_1E886	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1E908	proc far

var_13		= word ptr -13h
var_10		= byte ptr -10h
var_8		= byte ptr -8

		enter	14h, 0
		push	si
		push	di
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_1EB20
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1E947
		mov	word_39E1A+1, 20h ; ' '
		mov	byte ptr word_39E1A, 0
		push	large 580050h
		push	large 480040h
		push	ds
		push	offset word_39E18
		push	cs
		call	near ptr sub_1E841
		push	8
		call	sub_125C9
		add	sp, 0Eh

loc_1E947:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1EAD2
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	di, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	[bp+var_13+1], ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_13+1]
		push	word_39E1A+1
		push	word_39E1A
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		add	sp, 0Ah
		cmp	word_3A6CA, 104h
		jge	short loc_1E9A2
		mov	al, 0Ch
		jmp	short loc_1E9A4
; ---------------------------------------------------------------------------

loc_1E9A2:
		mov	al, 0F4h ; '�

loc_1E9A4:
		add	al, byte ptr word_39E1A
		mov	byte ptr word_39E1A, al
		cmp	word_39E1A+1, 70h ; 'p'
		jge	short loc_1E9BA
		add	word_39E1A+1, 8
		jmp	loc_1EA9F
; ---------------------------------------------------------------------------

loc_1E9BA:
		cmp	word_3A6CA, 118h
		jle	short loc_1EA2D
		xor	si, si
		jmp	short loc_1EA26
; ---------------------------------------------------------------------------

loc_1E9C6:
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_10]
		add	bx, ax
		mov	ax, ss:[bx]
		sub	ax, [bp+var_13+1]
		push	ax
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		mov	ax, ss:[bx]
		sub	ax, di
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_13], al
		push	large 0
		push	large 0
		push	word_39E18
		push	[bp+var_13]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_10]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		push	word ptr ss:[bx]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	7
		call	sub_125C9
		add	sp, 16h
		inc	si

loc_1EA26:
		cmp	si, 4
		jl	short loc_1E9C6
		jmp	short loc_1EA9F
; ---------------------------------------------------------------------------

loc_1EA2D:
		xor	si, si
		jmp	short loc_1EA9A
; ---------------------------------------------------------------------------

loc_1EA31:
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_10]
		add	bx, ax
		mov	ax, 180h
		sub	ax, ss:[bx]
		push	ax
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		mov	ax, word_36C26
		add	ax, 0Ch
		sub	ax, ss:[bx]
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_13], al
		push	large 0
		push	large 0
		mov	ax, word_39E18
		cwd
		sub	ax, dx
		sar	ax, 1
		push	ax
		push	[bp+var_13]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_10]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		push	word ptr ss:[bx]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	7
		call	sub_125C9
		add	sp, 16h
		inc	si

loc_1EA9A:
		cmp	si, 4
		jl	short loc_1EA31

loc_1EA9F:
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_13+1]
		push	word_39E1A+1
		push	word_39E1A
		push	4
		call	sub_1E886
		push	large 70004h
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17BAE
		add	sp, 0Ch

loc_1EAD2:
		cmp	word_3A6CA, 168h
		jle	short loc_1EB20
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	di, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	[bp+var_13+1], ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_13+1]
		push	word_39E1A+1
		push	word_39E1A
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		add	sp, 0Ah
		mov	word_3A6CA, 0

loc_1EB20:
		pop	di
		pop	si
		leave
		retf
sub_1E908	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EB24	proc far

var_2E		= qword	ptr -2Eh
var_26		= qword	ptr -26h
var_18		= word ptr -18h
var_16		= word ptr -16h
var_14		= word ptr -14h
var_12		= word ptr -12h
var_10		= byte ptr -10h
var_8		= byte ptr -8

		enter	18h, 0
		push	si
		push	di
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_1ECEC
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1EB64
		mov	word_39E1D+1, 20h ; ' '
		mov	byte ptr word_39E1D, 0
		push	large 760070h
		push	large 680060h
		push	ds
		push	offset word_39E18
		push	cs
		call	near ptr sub_1E841
		add	sp, 0Ch
		push	8
		call	sub_125C9
		pop	cx

loc_1EB64:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1ECA1
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	si, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	di, ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	si
		push	di
		push	word_39E1D+1
		push	word_39E1D
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		add	sp, 0Ah
		mov	al, byte ptr word_39E1D
		add	al, 0F4h ; '�
		mov	byte ptr word_39E1D, al
		cmp	word_39E1D+1, 50h ; 'P'
		jge	short loc_1EBC7
		add	word_39E1D+1, 8
		jmp	loc_1EC70
; ---------------------------------------------------------------------------

loc_1EBC7:
		cmp	word_3A6CA, 0E0h ; '�
		jnz	short loc_1EBD8
		mov	ax, word_36C26
		mov	word_39E20, ax
		jmp	loc_1EC70
; ---------------------------------------------------------------------------

loc_1EBD8:
		cmp	word_3A6CA, 0F0h ; '�
		jle	loc_1EC70
		push	word_39E18
		push	ss
		lea	ax, [bp+var_16]
		push	ax
		push	ss
		lea	ax, [bp+var_14]
		push	ax
		push	180h
		mov	ax, word_39E20
		add	ax, 8
		push	ax
		push	di
		push	si
		call	sub_11FF0
		add	sp, 12h
		mov	[bp+var_12], 0
		jmp	short loc_1EC62
; ---------------------------------------------------------------------------

loc_1EC0B:
		push	0		; char
		mov	ax, [bp+var_16]
		sar	ax, 4
		mov	[bp+var_18], ax
		; Hack (fild [bp+var_18])
		db 0cdh
		db 03bh
		db 046h
		db 0e8h
		sub	sp, 8
		; Hack (fstp [bp+var_26])
		db 0cdh
		db 039h
		db 05eh
		db 0dah
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_14]
		sar	ax, 4
		mov	[bp+var_18], ax
		; Hack (fild [bp+var_18])
		db 0cdh
		db 03bh
		db 046h
		db 0e8h
		sub	sp, 8
		; Hack (fstp [bp+var_2E])
		db 0cdh
		db 039h
		db 05eh
		db 0d2h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	bx, [bp+var_12]
		add	bx, bx
		lea	ax, [bp+var_10]
		add	bx, ax
		push	word ptr ss:[bx] ; int
		mov	bx, [bp+var_12]
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		push	word ptr ss:[bx] ; int
		push	ds
		push	offset unk_39EC4 ; __int32
		call	sub_21C0D
		add	sp, 1Ah
		inc	[bp+var_12]

loc_1EC62:
		cmp	[bp+var_12], 4
		jl	short loc_1EC0B
		push	6
		call	sub_125C9
		pop	cx

loc_1EC70:
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	si
		push	di
		push	word_39E1D+1
		push	word_39E1D
		push	4
		call	sub_1E886
		push	large 70004h
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17BAE
		add	sp, 0Ch

loc_1ECA1:
		cmp	word_3A6CA, 140h
		jle	short loc_1ECEC
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	si, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	di, ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	si
		push	di
		push	word_39E1D+1
		push	word_39E1D
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		add	sp, 0Ah
		mov	word_3A6CA, 0

loc_1ECEC:
		pop	di
		pop	si
		leave
		retf
sub_1EB24	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1ECF0	proc far

var_23		= word ptr -23h
var_20		= byte ptr -20h
var_18		= byte ptr -18h
var_10		= byte ptr -10h
var_8		= byte ptr -8

		enter	24h, 0
		push	si
		push	di
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_1ED01
		push	cs
		call	near ptr sub_1E431

loc_1ED01:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_1EF81
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1ED3A
		mov	word_39E22+1, 20h ; ' '
		mov	byte ptr word_39E22, 0
		push	large 580050h
		push	large 480040h
		push	ds
		push	offset word_39E18
		push	cs
		call	near ptr sub_1E841
		push	8
		call	sub_125C9
		add	sp, 0Eh

loc_1ED3A:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1EF00
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	di, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	[bp+var_23+1], ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_23+1]
		push	word_39E22+1
		push	word_39E22
		push	4
		call	sub_1E886
		push	ss
		lea	ax, [bp+var_18]
		push	ax
		push	ss
		lea	ax, [bp+var_20]
		push	ax
		push	di
		push	[bp+var_23+1]
		push	word_39E22+1
		mov	al, 0
		sub	al, byte ptr word_39E22
		push	ax
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		push	4
		push	ss
		lea	ax, [bp+var_20]
		push	ax
		push	ss
		lea	ax, [bp+var_18]
		push	ax
		call	sub_17C2F
		add	sp, 14h
		mov	al, byte ptr word_39E22
		add	al, 0FAh ; '�
		mov	byte ptr word_39E22, al
		mov	byte_386B7, 1
		cmp	word_39E22+1, 70h ; 'p'
		jge	short loc_1EDD4
		add	word_39E22+1, 8
		jmp	loc_1EE95
; ---------------------------------------------------------------------------

loc_1EDD4:
		xor	si, si
		jmp	loc_1EE8E
; ---------------------------------------------------------------------------

loc_1EDD9:
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_10]
		add	bx, ax
		mov	ax, ss:[bx]
		sub	ax, [bp+var_23+1]
		push	ax
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		mov	ax, ss:[bx]
		sub	ax, di
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_23], al
		push	large 0
		push	large 0
		push	word_39E18
		push	[bp+var_23]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_10]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		push	word ptr ss:[bx]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_20]
		add	bx, ax
		mov	ax, ss:[bx]
		sub	ax, [bp+var_23+1]
		push	ax
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_18]
		add	bx, ax
		mov	ax, ss:[bx]
		sub	ax, di
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_23], al
		push	large 0
		push	large 0
		push	word_39E18
		push	[bp+var_23]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_20]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_18]
		add	bx, ax
		push	word ptr ss:[bx]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	7
		call	sub_125C9
		add	sp, 2Ah
		inc	si

loc_1EE8E:
		cmp	si, 4
		jl	loc_1EDD9

loc_1EE95:
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_23+1]
		push	word_39E22+1
		push	word_39E22
		push	4
		call	sub_1E886
		push	ss
		lea	ax, [bp+var_18]
		push	ax
		push	ss
		lea	ax, [bp+var_20]
		push	ax
		push	di
		push	[bp+var_23+1]
		push	word_39E22+1
		mov	al, 0
		sub	al, byte ptr word_39E22
		push	ax
		push	4
		call	sub_1E886
		push	large 70004h
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17BAE
		push	large 70004h
		push	ss
		lea	ax, [bp+var_20]
		push	ax
		push	ss
		lea	ax, [bp+var_18]
		push	ax
		call	sub_17BAE
		add	sp, 18h
		mov	byte_386B7, 0

loc_1EF00:
		cmp	word_3A6CA, 140h
		jle	short loc_1EF81
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	di, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	[bp+var_23+1], ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_23+1]
		push	word_39E22+1
		push	word_39E22
		push	4
		call	sub_1E886
		push	ss
		lea	ax, [bp+var_18]
		push	ax
		push	ss
		lea	ax, [bp+var_20]
		push	ax
		push	di
		push	[bp+var_23+1]
		push	word_39E22+1
		mov	al, 0
		sub	al, byte ptr word_39E22
		push	ax
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		push	4
		push	ss
		lea	ax, [bp+var_20]
		push	ax
		push	ss
		lea	ax, [bp+var_18]
		push	ax
		call	sub_17C2F
		add	sp, 14h
		mov	word_3A6CA, 0
		push	cs
		call	near ptr sub_1E48B

loc_1EF81:
		pop	di
		pop	si
		leave
		retf
sub_1ECF0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1EF85	proc far

var_6		= word ptr -6
var_3		= word ptr -3
arg_0		= word ptr  6

		enter	6, 0
		push	si
		cmp	[bp+arg_0], 0
		jnz	short loc_1EFB1
		mov	byte_39E25, 0FFh
		mov	byte_35B7B, 4
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	byte_39E26, dl
		mov	byte_35B7C, 10h
		jmp	loc_1F19B
; ---------------------------------------------------------------------------

loc_1EFB1:
		cmp	byte_39E25, 0FFh
		jnz	short loc_1EFE5
		push	1
		call	sub_EA3E
		push	0
		push	cs
		call	near ptr sub_1E589
		push	0
		call	sub_EA3E
		push	0
		push	cs
		call	near ptr sub_1E589
		add	sp, 8
		mov	byte_35B7A, 0
		mov	byte_39E25, 0
		mov	word_3A6CA, 1

loc_1EFE5:
		cmp	byte_39E25, 0
		jnz	short loc_1EFF8
		mov	word_39852, 1
		push	cs
		call	near ptr sub_1E739
		jmp	short loc_1F051
; ---------------------------------------------------------------------------

loc_1EFF8:
		cmp	word_3A6CA, 4
		jnz	short loc_1F030
		cmp	byte_39E26, 0
		jnz	short loc_1F011
		mov	al, byte_39E25
		mov	ah, 0
		dec	ax
		shl	ax, 7
		jmp	short loc_1F020
; ---------------------------------------------------------------------------

loc_1F011:
		mov	al, byte_39E25
		mov	ah, 0
		shl	ax, 7
		push	ax
		mov	ax, 280h
		pop	dx
		sub	ax, dx

loc_1F020:
		mov	[bp+var_6], ax
		mov	word ptr dword_3982A, ax
		mov	word ptr dword_3982A+2,	60h ; '`'
		push	cs
		call	near ptr sub_1E526

loc_1F030:
		cmp	word_3A6CA, 0Ch
		jge	short loc_1F03F
		mov	word_39852, 1
		jmp	short loc_1F045
; ---------------------------------------------------------------------------

loc_1F03F:
		mov	word_39852, 0

loc_1F045:
		push	large [dword_3982A]
		push	cs
		call	near ptr sub_1E659
		add	sp, 4

loc_1F051:
		cmp	word_3A6CA, 0
		jnz	loc_1F19B
		cmp	byte_39E25, 0
		jz	loc_1F0F8
		cmp	byte_39E25, 4
		jz	short loc_1F087
		push	1
		call	sub_EA3E
		push	0
		push	cs
		call	near ptr sub_1E589
		push	0
		call	sub_EA3E
		push	0
		push	cs
		call	near ptr sub_1E589
		add	sp, 8

loc_1F087:
		push	large 2D0028h
		push	large 23001Eh
		push	ds
		push	offset word_39E18
		push	cs
		call	near ptr sub_1E841
		push	large 0C000Ah
		push	large 80005h
		push	ss
		lea	ax, [bp+var_3+1]
		push	ax
		push	cs
		call	near ptr sub_1E841
		add	sp, 18h
		xor	si, si
		mov	byte ptr [bp+var_3], 0
		jmp	short loc_1F0F3
; ---------------------------------------------------------------------------

loc_1F0BB:
		push	large 0
		push	word_39E18
		push	6
		push	word_39E18
		push	[bp+var_3]
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si
		mov	ax, 100h
		cwd
		idiv	[bp+var_3+1]
		add	al, byte ptr [bp+var_3]
		mov	byte ptr [bp+var_3], al

loc_1F0F3:
		cmp	si, [bp+var_3+1]
		jl	short loc_1F0BB

loc_1F0F8:
		cmp	byte_39E25, 4
		jb	short loc_1F154
		push	1
		call	sub_EA3E
		push	0
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_1588A
		push	0
		call	sub_EA3E
		push	0
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_1588A
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 1Ch
		mov	byte_39E25, 0FFh
		mov	al, 1
		sub	al, byte_39E26
		mov	byte_39E26, al
		mov	byte_35B7A, 1
		mov	word_3A6CA, 0
		jmp	short loc_1F19B
; ---------------------------------------------------------------------------

loc_1F154:
		xor	si, si
		jmp	short loc_1F18C
; ---------------------------------------------------------------------------

loc_1F158:
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+6F2h]
		cbw
		add	ax, 0FFFCh
		push	ax
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+6F1h]
		cbw
		add	ax, 0FFFCh
		push	ax
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+6F0h]
		cbw
		add	ax, 0FFFCh
		push	ax
		push	si
		call	sub_EB59
		add	sp, 8
		inc	si

loc_1F18C:
		cmp	si, 10h
		jl	short loc_1F158
		inc	byte_39E25
		mov	word_3A6CA, 1

loc_1F19B:
		pop	si
		leave
		retf
sub_1EF85	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F19E	proc far

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [bp+arg_0]
		sar	ax, 3
		mov	dx, [bp+arg_2]
		shl	dx, 6
		add	ax, dx
		mov	dx, [bp+arg_2]
		shl	dx, 4
		add	ax, dx
		mov	di, ax
		push	0Ah
		call	sub_EA71
		pop	cx
		xor	si, si
		jmp	short loc_1F1EA
; ---------------------------------------------------------------------------

loc_1F1C7:
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		mov	bx, 7
		sub	bx, dx
		shl	bx, 2
		mov	eax, [bx+11DDh]
		les	bx, dword_38928
		add	bx, di
		mov	es:[bx], eax
		inc	si
		sub	di, 50h	; 'P'

loc_1F1EA:
		mov	ax, [bp+arg_4]
		add	ax, 0FFF8h
		cmp	ax, si
		jg	short loc_1F1C7
		xor	si, si
		jmp	short loc_1F21B
; ---------------------------------------------------------------------------

loc_1F1F8:
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		mov	bx, 7
		sub	bx, dx
		shl	bx, 2
		mov	eax, [bx+11FDh]
		les	bx, dword_38928
		add	bx, di
		mov	es:[bx], eax
		inc	si
		sub	di, 50h	; 'P'

loc_1F21B:
		cmp	si, 8
		jl	short loc_1F1F8
		call	sub_EB05
		pop	di
		pop	si
		pop	bp
		retf
sub_1F19E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F229	proc far
		push	bp
		mov	bp, sp
		push	si
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_1F238
		push	cs
		call	near ptr sub_1E431

loc_1F238:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_1F596
		cmp	word_3A6CA, 64h	; 'd'
		jnz	loc_1F31E
		xor	si, si
		jmp	short loc_1F263
; ---------------------------------------------------------------------------

loc_1F24E:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+5487h], 80h ; '?'
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+54A7h], 190h
		inc	si

loc_1F263:
		cmp	si, 8
		jl	short loc_1F24E
		call	IRand
		mov	bx, 30h	; '0'
		cwd
		idiv	bx
		add	dx, 10h
		mov	word_39E37, dx
		call	IRand
		mov	bx, 30h	; '0'
		cwd
		idiv	bx
		mov	ax, 260h
		sub	ax, dx
		add	ax, 10h
		mov	word_39E39, ax
		call	IRand
		mov	bx, 0E0h ; '�
		cwd
		idiv	bx
		add	dx, 40h	; '@'
		mov	word_39E3B, dx
		call	IRand
		mov	bx, 0E0h ; '�
		cwd
		idiv	bx
		add	dx, 150h
		mov	word_39E3D, dx
		call	IRand
		mov	bx, 0A0h ; '?'
		cwd
		idiv	bx
		add	dx, 80h	; '?'
		mov	word_39E3F, dx
		call	IRand
		mov	bx, 0A0h ; '?'
		cwd
		idiv	bx
		add	dx, 150h
		mov	word_39E41, dx
		call	IRand
		mov	bx, 0E0h ; '�
		cwd
		idiv	bx
		add	dx, 40h	; '@'
		mov	word_39E43, dx
		call	IRand
		mov	bx, 0E0h ; '�
		cwd
		idiv	bx
		add	dx, 150h
		mov	word_39E45, dx
		push	large 370032h
		push	large 2D0028h
		push	ds
		push	offset word_39E18
		push	cs
		call	near ptr sub_1E841
		push	8
		call	sub_125C9
		add	sp, 0Eh

loc_1F31E:
		xor	si, si
		jmp	short loc_1F381
; ---------------------------------------------------------------------------

loc_1F322:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, si
		jnz	short loc_1F380
		mov	ax, si
		imul	ax, 14h
		add	ax, 64h	; 'd'
		cmp	ax, word_3A6CA
		jge	short loc_1F380
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+5487h], 20h ; ' '
		jle	short loc_1F380
		push	0FFh
		push	0
		push	4
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5487h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5487h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+54A7h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5497h]
		call	sub_17956
		add	sp, 0Eh
		mov	bx, si
		add	bx, bx
		sub	word ptr [bx+5487h], 8

loc_1F380:
		inc	si

loc_1F381:
		cmp	si, 8
		jl	short loc_1F322
		cmp	word_3A6CA, 64h	; 'd'
		jz	short loc_1F3C4
		cmp	word_3A6CA, 78h	; 'x'
		jz	short loc_1F3C4
		cmp	word_3A6CA, 8Ch	; '�
		jz	short loc_1F3C4
		cmp	word_3A6CA, 0A0h ; '?'
		jz	short loc_1F3C4
		cmp	word_3A6CA, 0B4h ; '?'
		jz	short loc_1F3C4
		cmp	word_3A6CA, 0C8h ; '?'
		jz	short loc_1F3C4
		cmp	word_3A6CA, 0DCh ; '?'
		jz	short loc_1F3C4
		cmp	word_3A6CA, 0F0h ; '�
		jnz	short loc_1F3CC

loc_1F3C4:
		push	0Ch
		call	sub_125C9
		pop	cx

loc_1F3CC:
		cmp	word_3A6CA, 0F0h ; '�
		jnz	short loc_1F3D8
		push	cs
		call	near ptr sub_1E48B

loc_1F3D8:
		xor	si, si
		jmp	loc_1F549
; ---------------------------------------------------------------------------

loc_1F3DD:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, si
		jnz	loc_1F548
		mov	ax, si
		imul	ax, 14h
		add	ax, 64h	; 'd'
		cmp	ax, word_3A6CA
		jge	loc_1F548
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+5487h], 20h ; ' '
		jle	short loc_1F458
		push	0FFh
		push	0
		push	4
		push	7
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5487h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5487h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+54A7h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5497h]
		call	sub_1786D
		push	1
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+54A7h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5497h]
		push	large 0C80140h
		call	sub_F342
		add	sp, 1Ah
		jmp	loc_1F548
; ---------------------------------------------------------------------------

loc_1F458:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+5487h], 10h
		jle	loc_1F4F8
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+5487h], 20h ; ' '
		jnz	short loc_1F495
		push	7
		call	sub_125C9
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+54A7h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5497h]
		push	large 0C80140h
		call	sub_F2F5
		add	sp, 0Ah

loc_1F495:
		mov	bx, si
		add	bx, bx
		mov	ax, 22h	; '"'
		sub	ax, [bx+5487h]
		shl	ax, 4
		push	ax
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+54A7h]
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+5497h]
		add	ax, 0FFF0h
		push	ax
		push	cs
		call	near ptr sub_1F19E
		add	sp, 6
		cmp	word_34A78, 0
		jnz	short loc_1F4ED
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+5497h]
		add	ax, 0FFD8h
		cmp	ax, word_36C26
		jge	short loc_1F4ED
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+5497h]
		add	ax, 8
		cmp	ax, word_36C26
		jle	short loc_1F4ED
		mov	byte_34A4F, 1

loc_1F4ED:
		mov	bx, si
		add	bx, bx
		sub	word ptr [bx+5487h], 8
		jmp	short loc_1F548
; ---------------------------------------------------------------------------

loc_1F4F8:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+5487h], 0FC19h
		jz	short loc_1F548
		push	large 240017h
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 0E00020h
		push	0B0h ; '?'
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+5497h]
		add	ax, 0FFF0h
		push	ax
		call	sub_10433
		add	sp, 14h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+5487h], 0FC19h

loc_1F548:
		inc	si

loc_1F549:
		cmp	si, 8
		jl	loc_1F3DD
		cmp	word_39E27, 0FC19h
		jnz	short loc_1F596
		cmp	word_39E29, 0FC19h
		jnz	short loc_1F596
		cmp	word_39E2B, 0FC19h
		jnz	short loc_1F596
		cmp	word_39E2D, 0FC19h
		jnz	short loc_1F596
		cmp	word_39E2F, 0FC19h
		jnz	short loc_1F596
		cmp	word_39E31, 0FC19h
		jnz	short loc_1F596
		cmp	word_39E33, 0FC19h
		jnz	short loc_1F596
		cmp	word_39E35, 0FC19h
		jnz	short loc_1F596
		mov	word_3A6CA, 0

loc_1F596:
		pop	si
		pop	bp
		retf
sub_1F229	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F599	proc far

var_2E		= qword	ptr -2Eh
var_26		= qword	ptr -26h
var_18		= word ptr -18h
var_16		= word ptr -16h
var_14		= word ptr -14h
var_12		= word ptr -12h
var_10		= byte ptr -10h
var_8		= byte ptr -8

		enter	18h, 0
		push	si
		push	di
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_1F765
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1F5DE
		mov	word_39E57+1, 20h ; ' '
		mov	byte ptr word_39E57, 0
		mov	byte ptr word_39E5A, 0
		push	large 370032h
		push	large 2D0028h
		push	ds
		push	offset word_39E18
		push	cs
		call	near ptr sub_1E841
		add	sp, 0Ch
		push	8
		call	sub_125C9
		pop	cx

loc_1F5DE:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1F717
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	di, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	[bp+var_12], ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_12]
		push	word_39E57+1
		push	word_39E57
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		add	sp, 0Ah
		mov	al, byte ptr word_39E57
		add	al, 0F4h ; '�
		mov	byte ptr word_39E57, al
		cmp	word_39E57+1, 50h ; 'P'
		jge	short loc_1F644
		add	word_39E57+1, 8
		jmp	loc_1F6E4
; ---------------------------------------------------------------------------

loc_1F644:
		cmp	word_3A6CA, 0B4h ; '?'
		jle	loc_1F6E4
		mov	ax, word_3A6CA
		mov	bx, 10h
		cwd
		idiv	bx
		cmp	dx, 8
		jnz	loc_1F6E4
		push	word_39E5A
		mov	ax, word_39E18
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		push	ss
		lea	ax, [bp+var_16]
		push	ax
		push	ss
		lea	ax, [bp+var_14]
		push	ax
		call	sub_12053
		add	sp, 0Ch
		xor	si, si
		jmp	short loc_1F6CF
; ---------------------------------------------------------------------------

loc_1F682:
		push	0		; char
		mov	ax, [bp+var_16]
		mov	[bp+var_18], ax
		; Hack (fild [bp+var_18])
		db 0cdh
		db 03bh
		db 046h
		db 0e8h
		sub	sp, 8
		; Hack (fstp [bp+var_26])
		db 0cdh
		db 039h
		db 05eh
		db 0dah
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_14]
		mov	[bp+var_18], ax
		; Hack (fild [bp+var_18])
		db 0cdh
		db 03bh
		db 046h
		db 0e8h
		sub	sp, 8
		; Hack (fstp [bp+var_2E])
		db 0cdh
		db 039h
		db 05eh
		db 0d2h
		mov	bx, si
		add	bx, bx
		; Hack (wait)
		db 0cdh
		db 03dh
		lea	ax, [bp+var_10]
		add	bx, ax
		push	word ptr ss:[bx] ; int
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		push	word ptr ss:[bx] ; int
		push	ds
		push	offset unk_39EC4 ; __int32
		call	sub_21C0D
		add	sp, 1Ah
		inc	si

loc_1F6CF:
		cmp	si, 4
		jl	short loc_1F682
		push	6
		call	sub_125C9
		pop	cx
		mov	al, byte ptr word_39E5A
		add	al, 0Dh
		mov	byte ptr word_39E5A, al

loc_1F6E4:
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_12]
		push	word_39E57+1
		push	word_39E57
		push	4
		call	sub_1E886
		push	large 70004h
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17BAE
		add	sp, 0Ch

loc_1F717:
		cmp	word_3A6CA, 154h
		jle	short loc_1F765
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	di, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	[bp+var_12], ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_12]
		push	word_39E57+1
		push	word_39E57
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		add	sp, 0Ah
		mov	word_3A6CA, 0

loc_1F765:
		pop	di
		pop	si
		leave
		retf
sub_1F599	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F769	proc far

var_12		= word ptr -12h
var_10		= byte ptr -10h
var_8		= byte ptr -8

		enter	12h, 0
		push	si
		push	di
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_1F905
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1F7AD
		mov	word_39E5C, 20h	; ' '
		mov	byte ptr word_39E5A+1, 0
		mov	byte ptr word_39E5E, 80h ; '?'
		push	large 380030h
		push	large 280020h
		push	ds
		push	offset word_39E18
		push	cs
		call	near ptr sub_1E841
		push	8
		call	sub_125C9
		add	sp, 0Eh

loc_1F7AD:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_1F8B7
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	di, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	[bp+var_12], ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_12]
		push	word_39E5C
		push	word_39E5A+1
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		add	sp, 0Ah
		cmp	word_3A6CA, 10Eh
		jle	short loc_1F80B
		mov	al, byte ptr word_39E5A+1
		add	al, 0Ch
		jmp	short loc_1F810
; ---------------------------------------------------------------------------

loc_1F80B:
		mov	al, byte ptr word_39E5A+1
		add	al, 0F4h ; '�

loc_1F810:
		mov	byte ptr word_39E5A+1, al
		cmp	word_39E5C, 50h	; 'P'
		jge	short loc_1F821
		add	word_39E5C, 8
		jmp	short loc_1F884
; ---------------------------------------------------------------------------

loc_1F821:
		cmp	word_3A6CA, 0B4h ; '?'
		jle	short loc_1F884
		cmp	word_3A6CA, 10Eh
		jle	short loc_1F838
		mov	al, byte ptr word_39E5E
		add	al, 0Ch
		jmp	short loc_1F83D
; ---------------------------------------------------------------------------

loc_1F838:
		mov	al, byte ptr word_39E5E
		add	al, 0F4h ; '�

loc_1F83D:
		mov	byte ptr word_39E5E, al
		xor	si, si
		jmp	short loc_1F877
; ---------------------------------------------------------------------------

loc_1F844:
		push	large 0
		push	large 0
		push	word_39E18
		push	word_39E5E
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_10]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_8]
		add	bx, ax
		push	word ptr ss:[bx]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_1F877:
		cmp	si, 4
		jl	short loc_1F844
		push	6
		call	sub_125C9
		pop	cx

loc_1F884:
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_12]
		push	word_39E5C
		push	word_39E5A+1
		push	4
		call	sub_1E886
		push	large 70004h
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17BAE
		add	sp, 0Ch

loc_1F8B7:
		cmp	word_3A6CA, 172h
		jle	short loc_1F905
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	di, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	[bp+var_12], ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	di
		push	[bp+var_12]
		push	word_39E5C
		push	word_39E5A+1
		push	4
		call	sub_1E886
		push	4
		push	ss
		lea	ax, [bp+var_10]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_17C2F
		add	sp, 0Ah
		mov	word_3A6CA, 0

loc_1F905:
		pop	di
		pop	si
		leave
		retf
sub_1F769	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1F909	proc far

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_1F91A
		push	cs
		call	near ptr sub_1E431

loc_1F91A:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_1FA77
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_1F953
		mov	word_39E60, 20h	; ' '
		mov	byte ptr word_39E5E+1, 0
		push	large 3E003Ah
		push	large 360032h
		push	ds
		push	offset word_39E18
		push	cs
		call	near ptr sub_1E841
		push	8
		call	sub_125C9
		add	sp, 0Eh

loc_1F953:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1F9DA
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	si, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	di, ax
		push	ds
		push	offset unk_39E64
		push	ds
		push	offset unk_39E6C
		push	si
		push	ax
		push	word_39E60
		push	word_39E5E+1
		push	4
		call	sub_1E886
		push	4
		push	ds
		push	offset unk_39E6C
		push	ds
		push	offset unk_39E64
		call	sub_17C2F
		add	sp, 0Ah
		mov	al, byte ptr word_39E5E+1
		add	al, 3
		mov	byte ptr word_39E5E+1, al
		cmp	word_39E60, 50h	; 'P'
		jge	short loc_1F9AD
		add	word_39E60, 8

loc_1F9AD:
		push	ds
		push	offset unk_39E64
		push	ds
		push	offset unk_39E6C
		push	si
		push	di
		push	word_39E60
		push	word_39E5E+1
		push	4
		call	sub_1E886
		push	large 70004h
		push	ds
		push	offset unk_39E6C
		push	ds
		push	offset unk_39E64
		call	sub_17BAE
		add	sp, 0Ch

loc_1F9DA:
		cmp	word_3A6CA, 0B4h ; '?'
		jle	short loc_1FA30
		cmp	word_3A6CA, 12Ch
		jge	short loc_1FA30
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		push	bx
		push	large 140007h
		push	word_39E18
		push	190h
		mov	ax, word_36C26
		add	ax, 0Eh
		push	ax
		mov	bx, [bp+var_2]
		add	bx, bx
		push	word ptr [bx+54CCh]
		mov	bx, [bp+var_2]
		add	bx, bx
		push	word ptr [bx+54C4h]
		mov	ax, [bp+var_2]
		imul	ax, 45h
		add	ax, 4800h
		push	ds
		push	ax
		call	sub_1209D
		add	sp, 14h

loc_1FA30:
		cmp	word_3A6CA, 12Ch
		jle	short loc_1FA77
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	si, ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 50h	; 'P'
		mov	di, ax
		push	ds
		push	offset unk_39E64
		push	ds
		push	offset unk_39E6C
		push	si
		push	ax
		push	word_39E60
		push	word_39E5E+1
		push	4
		call	sub_1E886
		push	4
		push	ds
		push	offset unk_39E6C
		push	ds
		push	offset unk_39E64
		call	sub_17C2F
		add	sp, 0Ah
		mov	word_3A6CA, 0

loc_1FA77:
		pop	di
		pop	si
		leave
		retf
sub_1F909	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FA7B	proc far

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		mov	ax, word_35BBD
		mov	[bp+var_2], ax
		push	ds
		push	offset unk_39EC4
		call	sub_21F19
		push	large 70001h
		call	sub_22264
		add	sp, 8
		cmp	byte_3A6CE, 0
		jnz	short loc_1FB20
		push	0
		call	sub_EA3E
		pop	cx
		mov	word_3A6CA, 0
		mov	word_39852, 0
		xor	di, di
		mov	byte_35B7B, 1
		mov	byte_35B7C, 2
		mov	byte_35B7A, 1

loc_1FACA:
		inc	word_3A6CA
		or	di, di
		jnz	short loc_1FADF
		push	large 780100h
		push	cs
		call	near ptr sub_1E659
		add	sp, 4

loc_1FADF:
		cmp	word_3A6CA, 0
		jnz	short loc_1FAE7
		inc	di

loc_1FAE7:
		cmp	di, 1
		jz	short loc_1FAF6
		push	2
		call	sub_E364
		pop	cx
		jmp	short loc_1FACA
; ---------------------------------------------------------------------------

loc_1FAF6:
		mov	byte_3A6CE, 1
		mov	word_39E78, 0
		mov	byte_39E7A, 0
		push	ds
		push	offset unk_35090
		call	sub_C433
		add	sp, 4
		call	sub_232A4
		push	0
		push	cs
		call	near ptr sub_1EF85
		jmp	loc_1FDCE
; ---------------------------------------------------------------------------

loc_1FB20:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 1
		jnz	loc_1FC54
		cmp	byte_39E7A, 0
		jnz	short loc_1FB45
		push	word_3A6CA
		push	word_3A6C8
		call	sub_2191C
		add	sp, 4
		mov	byte_39E7A, al

loc_1FB45:
		inc	word_3A6CA
		inc	word_39E74
		push	cs
		call	near ptr sub_1E3D7
		cmp	word_39E78, 0
		jnz	short loc_1FB5E
		push	cs
		call	near ptr sub_1E908
		jmp	short loc_1FB86
; ---------------------------------------------------------------------------

loc_1FB5E:
		cmp	word_39E78, 1
		jnz	short loc_1FB6B
		push	cs
		call	near ptr sub_1EB24
		jmp	short loc_1FB86
; ---------------------------------------------------------------------------

loc_1FB6B:
		cmp	word_39E78, 2
		jnz	short loc_1FB78
		push	cs
		call	near ptr sub_1ECF0
		jmp	short loc_1FB86
; ---------------------------------------------------------------------------

loc_1FB78:
		cmp	word_39E78, 3
		jnz	short loc_1FB86
		push	1
		push	cs
		call	near ptr sub_1EF85
		pop	cx

loc_1FB86:
		cmp	word_3A6CA, 0
		jnz	short loc_1FBAC
		cmp	word_39E78, 3
		jnz	short loc_1FB98
		xor	ax, ax
		jmp	short loc_1FB9C
; ---------------------------------------------------------------------------

loc_1FB98:
		mov	ax, word_39E78
		inc	ax

loc_1FB9C:
		mov	word_39E78, ax
		cmp	word_3A6C8, 6
		jg	short loc_1FBAC
		mov	word_39E78, 63h	; 'c'

loc_1FBAC:
		push	large 300060h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 10h
		push	ax
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_39E76
		push	ds
		push	offset word_39E74
		call	sub_21A8A
		add	sp, 22h
		cmp	word_39E78, 63h	; 'c'
		jnz	loc_1FDCF
		cmp	word_39E76, 0
		jnz	loc_1FDCF
		push	1
		call	sub_EA3E
		push	0
		push	cs
		call	near ptr sub_1E589
		push	0
		call	sub_EA3E
		push	0
		push	cs
		call	near ptr sub_1E589
		add	sp, 8
		mov	byte_35B7B, 4
		mov	byte_35B7C, 8
		mov	word ptr dword_3982A, 100h
		mov	word ptr dword_3982A+2,	78h ; 'x'
		push	cs
		call	near ptr sub_1E526
		mov	byte_3A6CE, 2
		mov	word_3A6CA, 0
		mov	word_39E74, 0
		mov	word_39E78, 0
		jmp	loc_1FDCF
; ---------------------------------------------------------------------------

loc_1FC54:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 2
		jnz	short loc_1FC95
		inc	word_3A6CA
		inc	word_39E74
		push	large 780100h
		push	cs
		call	near ptr sub_1E659
		add	sp, 4
		cmp	word_3A6CA, 0
		jnz	loc_1FDCF
		mov	byte_3A6CE, 3
		mov	word_3A6CA, 0
		mov	word_39E74, 0
		mov	word_39E78, 0
		jmp	loc_1FDCF
; ---------------------------------------------------------------------------

loc_1FC95:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 3
		jnz	loc_1FDCF
		inc	word_3A6CA
		inc	word_39E74
		push	cs
		call	near ptr sub_1E3D7
		cmp	word_39E78, 0
		jnz	short loc_1FCB9
		push	cs
		call	near ptr sub_1F229
		jmp	short loc_1FCDE
; ---------------------------------------------------------------------------

loc_1FCB9:
		cmp	word_39E78, 1
		jnz	short loc_1FCC6
		push	cs
		call	near ptr sub_1F599
		jmp	short loc_1FCDE
; ---------------------------------------------------------------------------

loc_1FCC6:
		cmp	word_39E78, 2
		jnz	short loc_1FCD3
		push	cs
		call	near ptr sub_1F769
		jmp	short loc_1FCDE
; ---------------------------------------------------------------------------

loc_1FCD3:
		cmp	word_39E78, 3
		jnz	short loc_1FCDE
		push	cs
		call	near ptr sub_1F909

loc_1FCDE:
		cmp	word_3A6CA, 0
		jnz	short loc_1FCF7
		cmp	word_39E78, 3
		jnz	short loc_1FCF0
		xor	ax, ax
		jmp	short loc_1FCF4
; ---------------------------------------------------------------------------

loc_1FCF0:
		mov	ax, word_39E78
		inc	ax

loc_1FCF4:
		mov	word_39E78, ax

loc_1FCF7:
		push	large 300060h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 10h
		push	ax
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1388h
		push	2
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_39E76
		push	ds
		push	offset word_39E74
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	loc_1FDCF
		push	1
		call	sub_EA3E
		push	0
		push	cs
		call	near ptr sub_1E589
		push	0
		call	sub_EA3E
		call	sub_12589
		push	ds
		push	offset unk_37635
		call	sub_30DEE
		push	ds
		push	offset unk_39EC4
		call	sub_21EFF
		add	sp, 0Eh
		xor	si, si
		jmp	short loc_1FDBD
; ---------------------------------------------------------------------------

loc_1FD77:
		mov	bx, si
		imul	bx, 45h
		cmp	word ptr [bx+483Ah], 0
		jz	short loc_1FDBC
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4804h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4800h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+480Ch]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4808h]
		call	sub_F2F5
		add	sp, 8
		mov	bx, si
		imul	bx, 45h
		mov	word ptr [bx+483Ah], 0
		jmp	short $+2

loc_1FDBC:
		inc	si

loc_1FDBD:
		cmp	si, 5
		jl	short loc_1FD77
		call	sub_12A3A
		push	4
		call	sub_20754

loc_1FDCE:
		pop	cx

loc_1FDCF:
		pop	di
		pop	si
		leave
		retf
sub_1FA7B	endp

seg029		ends

; ===========================================================================

; Segment type:	Pure code
seg030		segment	byte public 'CODE' use16
		assume cs:seg030
		;org 3
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FDD3	proc far

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6

		enter	4, 0
		push	si
		xor	si, si
		jmp	loc_1FF7F
; ---------------------------------------------------------------------------

loc_1FDDD:
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, word_36C28
		jge	short loc_1FDFC
		mov	ax, es:[bx]
		sub	ax, word_36C28
		imul	ax, -1
		jmp	short loc_1FE0D
; ---------------------------------------------------------------------------

loc_1FDFC:
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, word_36C28

loc_1FE0D:
		mov	[bp+var_2], ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, word_36C2A
		jge	short loc_1FE2F
		mov	ax, es:[bx]
		sub	ax, word_36C2A
		imul	ax, -1
		jmp	short loc_1FE40
; ---------------------------------------------------------------------------

loc_1FE2F:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, word_36C2A

loc_1FE40:
		mov	[bp+var_4], ax
		cmp	[bp+var_2], 18h
		jnb	short loc_1FE59
		cmp	[bp+var_4], 18h
		jnb	short loc_1FE59
		les	bx, off_39E8C
		cmp	byte ptr es:[bx+si], 0
		jz	short loc_1FEAB

loc_1FE59:
		cmp	word_34A72, 1
		jnz	short loc_1FE6A
		les	bx, off_39E8C
		cmp	byte ptr es:[bx+si], 0
		jz	short loc_1FEAB

loc_1FE6A:
		cmp	byte_34A58, 1
		jnz	loc_1FF7E
		movsx	ebx, word_39E90
		mov	eax, dword_34A62
		xor	edx, edx
		div	ebx
		movzx	eax, si
		cmp	edx, eax
		jnz	loc_1FF7E
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jz	loc_1FF7E
		les	bx, off_39E8C
		cmp	byte ptr es:[bx+si], 0
		jnz	loc_1FF7E

loc_1FEAB:
		les	bx, off_39E8C
		mov	byte ptr es:[bx+si], 1
		mov	ax, word_34A84
		imul	word_34A84
		cwde
		push	eax
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_1FECC
		mov	ax, 1
		jmp	short loc_1FECE
; ---------------------------------------------------------------------------

loc_1FECC:
		xor	ax, ax

loc_1FECE:
		imul	ax, 0Fh
		add	ax, 14h
		cwde
		pop	edx
		imul	edx, eax
		mov	ax, [bp+arg_0]
		mov	bx, 5
		push	edx
		cwd
		idiv	bx
		imul	ax, 64h
		add	ax, 64h	; 'd'
		cwde
		pop	edx
		add	edx, eax
		mov	ax, si
		shl	ax, 2
		les	bx, off_39EAC
		add	bx, ax
		mov	es:[bx], edx
		cmp	dword ptr es:[bx], 6400h
		jbe	short loc_1FF15
		mov	dword ptr es:[bx], 6400h

loc_1FF15:
		mov	ax, si
		shl	ax, 2
		les	bx, off_39EAC
		add	bx, ax
		mov	eax, es:[bx]
		add	dword_34A5A, eax
		inc	word_34A84
		mov	ax, word_34A88
		cmp	ax, word_34A84
		jge	short loc_1FF3C
		mov	ax, word_34A84
		mov	word_34A88, ax

loc_1FF3C:
		call	sub_1889C
		mov	al, byte_35BEE
		inc	byte_35BEE
		mov	ah, 0
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_1FF76
		cmp	byte_35BEE, 8Ch	; '�
		jb	short loc_1FF67
		mov	byte_35BEE, 1
		cmp	byte_34A58, 0
		jz	short loc_1FF6F

loc_1FF67:
		push	si
		call	sub_18217
		jmp	short loc_1FF75
; ---------------------------------------------------------------------------

loc_1FF6F:
		push	si
		call	sub_17CA9

loc_1FF75:
		pop	cx

loc_1FF76:
		push	2
		call	sub_125C9
		pop	cx

loc_1FF7E:
		inc	si

loc_1FF7F:
		cmp	si, word_39E90
		jb	loc_1FDDD
		pop	si
		leave
		retf
sub_1FDD3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_1FF8A	proc far

var_1		= byte ptr -1
arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= dword	ptr  0Ah

		enter	2, 0
		push	si
		push	di
		mov	di, [bp+arg_2]
		mov	si, 2710h
		mov	cx, [bp+arg_0]
		mov	[bp+var_1], 0
		jmp	short loc_1FFAB
; ---------------------------------------------------------------------------

loc_1FF9F:
		mov	bx, 0Ah
		mov	ax, si
		xor	dx, dx
		div	bx
		mov	si, ax
		inc	cx

loc_1FFAB:
		cmp	cx, 5
		jb	short loc_1FF9F
		xor	cx, cx
		jmp	short loc_1FFF7
; ---------------------------------------------------------------------------

loc_1FFB4:
		mov	ax, di
		xor	dx, dx
		div	si
		or	ax, ax
		jz	short loc_1FFC2
		mov	[bp+var_1], 1

loc_1FFC2:
		cmp	[bp+var_1], 0
		jz	short loc_1FFDA
		mov	ax, di
		xor	dx, dx
		div	si
		add	al, 30h	; '0'
		les	bx, [bp+arg_4]
		add	bx, cx
		mov	es:[bx], al
		jmp	short loc_1FFE3
; ---------------------------------------------------------------------------

loc_1FFDA:
		les	bx, [bp+arg_4]
		add	bx, cx
		mov	byte ptr es:[bx], 20h ;	' '

loc_1FFE3:
		mov	ax, di
		xor	dx, dx
		div	si
		mov	di, dx
		mov	bx, 0Ah
		mov	ax, si
		xor	dx, dx
		div	bx
		mov	si, ax
		inc	cx

loc_1FFF7:
		cmp	cx, [bp+arg_0]
		jb	short loc_1FFB4
		les	bx, [bp+arg_4]
		add	bx, [bp+arg_0]
		mov	byte ptr es:[bx], 0
		pop	di
		pop	si
		leave
		retf	8
sub_1FF8A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2000C	proc far

var_3		= byte ptr -3
var_2		= word ptr -2
arg_0		= word ptr  6
arg_2		= dword	ptr  8

		enter	4, 0
		push	si
		push	di
		mov	si, [bp+arg_0]
		mov	cx, 2710h
		xor	di, di
		mov	[bp+var_3], 0
		mov	[bp+var_2], 0
		jmp	short loc_2005C
; ---------------------------------------------------------------------------

loc_20025:
		mov	ax, si
		cwd
		idiv	cx
		or	ax, ax
		jz	short loc_20032
		mov	[bp+var_3], 1

loc_20032:
		cmp	[bp+var_3], 0
		jz	short loc_20048
		mov	ax, si
		cwd
		idiv	cx
		add	al, 30h	; '0'
		les	bx, [bp+arg_2]
		add	bx, di
		mov	es:[bx], al
		inc	di

loc_20048:
		mov	ax, si
		cwd
		idiv	cx
		mov	si, dx
		mov	bx, 0Ah
		mov	ax, cx
		cwd
		idiv	bx
		mov	cx, ax
		inc	[bp+var_2]

loc_2005C:
		cmp	[bp+var_2], 5
		jl	short loc_20025
		les	bx, [bp+arg_2]
		add	bx, di
		mov	byte ptr es:[bx], 0
		pop	di
		pop	si
		leave
		retf	6
sub_2000C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20071	proc far

var_8		= byte ptr -8
var_2		= word ptr -2

		enter	8, 0
		push	si
		push	di
		xor	si, si
		jmp	loc_201B2
; ---------------------------------------------------------------------------

loc_2007C:
		mov	ax, si
		shl	ax, 2
		les	bx, off_39EAC
		add	bx, ax
		cmp	dword ptr es:[bx], 0
		jz	loc_201B1
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		cmp	word ptr es:[bx], 0Eh
		jle	loc_201B1
		cmp	word ptr es:[bx], 14h
		jle	short loc_200B2
		mov	ax, es:[bx]
		add	ax, 0FFECh
		mov	di, ax
		jmp	short loc_200B4
; ---------------------------------------------------------------------------

loc_200B2:
		xor	di, di

loc_200B4:
		mov	ax, si
		shl	ax, 2
		les	bx, off_39EAC
		add	bx, ax
		cmp	dword ptr es:[bx], 2710h
		jbe	short loc_200D0
		mov	[bp+var_2], 0FFF8h
		jmp	short loc_20101
; ---------------------------------------------------------------------------

loc_200D0:
		mov	ax, si
		shl	ax, 2
		les	bx, off_39EAC
		add	bx, ax
		cmp	dword ptr es:[bx], 3E8h
		jbe	short loc_200EC
		mov	[bp+var_2], 0
		jmp	short loc_20101
; ---------------------------------------------------------------------------

loc_200EC:
		mov	ax, si
		shl	ax, 2
		les	bx, off_39EAC
		add	bx, ax
		cmp	dword ptr es:[bx], 64h ; 'd'
		mov	[bp+var_2], 8

loc_20101:
		or	di, di
		jz	short loc_20142
		push	large 100030h
		or	di, di
		jle	short loc_20114
		lea	ax, [di-1]
		jmp	short loc_20116
; ---------------------------------------------------------------------------

loc_20114:
		xor	ax, ax

loc_20116:
		mov	dx, si
		add	dx, dx
		les	bx, off_39E88
		add	bx, dx
		mov	dx, es:[bx]
		add	dx, 8
		sub	dx, ax
		push	dx
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, [bp+var_2]
		push	ax
		call	sub_10433
		add	sp, 8

loc_20142:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		cmp	word ptr es:[bx], 1Ch
		jl	short loc_20167
		mov	ax, si
		shl	ax, 2
		les	bx, off_39EAC
		add	bx, ax
		mov	dword ptr es:[bx], 0
		jmp	short loc_201B1
; ---------------------------------------------------------------------------

loc_20167:
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		mov	ax, si
		shl	ax, 2
		les	bx, off_39EAC
		add	bx, ax
		push	word ptr es:[bx]
		push	cs
		call	near ptr sub_2000C
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	27h ; '''
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 8
		sub	ax, di
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, [bp+var_2]
		push	ax
		call	sub_FA43
		add	sp, 0Ah

loc_201B1:
		inc	si

loc_201B2:
		cmp	si, word_39E90
		jl	loc_2007C
		pop	di
		pop	si
		leave
		retf
sub_20071	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_201BE	proc far

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		xor	di, di
		push	cs
		call	near ptr sub_20071
		xor	si, si
		jmp	loc_2037C
; ---------------------------------------------------------------------------

loc_201CF:
		les	bx, off_39E8C
		mov	al, es:[bx+si]
		cbw
		cmp	ax, 1
		jnz	loc_2036D
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		cmp	word ptr es:[bx], 19h
		jge	loc_202A6
		mov	ax, es:[bx]
		mov	bx, 6
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_202A6
		push	1
		call	sub_EA3E
		pop	cx
		push	si
		les	bx, off_39E96
		mov	al, es:[bx+si]
		cbw
		imul	ax, 5
		mov	dx, si
		add	dx, dx
		les	bx, off_39E92
		add	bx, dx
		push	ax
		mov	ax, es:[bx]
		mov	bx, 6
		cwd
		idiv	bx
		pop	bx
		add	bx, ax
		mov	al, [bx+126Eh]
		mov	ah, 0
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_20496
		push	0
		call	sub_EA3E
		add	sp, 0Ah
		push	si
		les	bx, off_39E96
		mov	al, es:[bx+si]
		cbw
		imul	ax, 5
		mov	dx, si
		add	dx, dx
		les	bx, off_39E92
		add	bx, dx
		push	ax
		mov	ax, es:[bx]
		mov	bx, 6
		cwd
		idiv	bx
		pop	bx
		add	bx, ax
		mov	al, [bx+126Eh]
		mov	ah, 0
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_20496
		add	sp, 8

loc_202A6:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		inc	word ptr es:[bx]
		cmp	word ptr es:[bx], 18h
		jl	loc_2036D
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_2031C
		mov	al, byte_34A34
		cbw
		cmp	ax, 0Ah
		jge	short loc_202D4
		mov	[bp+var_2], 0Ch
		jmp	short loc_202D9
; ---------------------------------------------------------------------------

loc_202D4:
		mov	[bp+var_2], 1Dh

loc_202D9:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		cmp	word ptr es:[bx], 19h
		jnz	short loc_2031C
		push	38h ; '8'
		push	[bp+var_2]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_2031C:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		cmp	word ptr es:[bx], 1Eh
		jl	short loc_2036D
		les	bx, off_39E96
		cmp	byte ptr es:[bx+si], 0
		jnz	short loc_2034F
		les	bx, off_39E8C
		mov	byte ptr es:[bx+si], 2
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		mov	word ptr es:[bx], 0
		jmp	short loc_2036D
; ---------------------------------------------------------------------------

loc_2034F:
		les	bx, off_39E8C
		mov	byte ptr es:[bx+si], 0
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		mov	word ptr es:[bx], 0
		les	bx, off_39E96
		dec	byte ptr es:[bx+si]

loc_2036D:
		les	bx, off_39E8C
		mov	al, es:[bx+si]
		cbw
		cmp	ax, 2
		jnz	short loc_2037B
		inc	di

loc_2037B:
		inc	si

loc_2037C:
		cmp	si, word_39E90
		jl	loc_201CF
		cmp	di, word_39E90
		jnz	short loc_20395
		mov	word_34A82, 1

loc_20390:
		mov	byte_34A4F, 1

loc_20395:
		pop	di
		pop	si
		leave
		retf
sub_201BE	endp

seg030		ends

; ===========================================================================

; Segment type:	Pure code
seg031		segment	byte public 'CODE' use16
		assume cs:seg031
		;org 9
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20399	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		or	si, si
		jg	short loc_203A9
		mov	ax, 0FFF7h
		jmp	short loc_203F6
; ---------------------------------------------------------------------------

loc_203A9:
		cmp	off_39E7C, 0
		jz	short loc_203BE
		push	large [off_39E7C]
		call	_farfree
		add	sp, 4

loc_203BE:
		push	large 281h	; unitsz
		movsx	eax, si
		push	eax		; nunits
		call	_farcalloc
		add	sp, 8
		mov	word ptr off_39E7C+2, dx
		mov	word ptr off_39E7C, ax
		cmp	off_39E7C, 0
		jnz	short loc_203E6
		mov	ax, 0FFFDh
		jmp	short loc_203F6
; ---------------------------------------------------------------------------

loc_203E6:
		mov	ax, si
		imul	ax, 281h
		movzx	eax, ax
		mov	dword_39E80, eax
		xor	ax, ax

loc_203F6:
		pop	si
		pop	bp
		retf
sub_20399	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_203F9	proc far
		push	bp
		mov	bp, sp
		push	si
		xor	si, si
		jmp	short loc_20428
; ---------------------------------------------------------------------------

loc_20401:
		push	si
		push	270Fh
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		push	word ptr es:[bx]
		nop
		push	cs
		call	near ptr sub_20496
		add	sp, 8
		inc	si

loc_20428:
		cmp	si, word_39E90
		jl	short loc_20401
		xor	si, si
		jmp	short loc_2045F
; ---------------------------------------------------------------------------

loc_20432:
		mov	ax, si
		add	ax, word_39E90
		push	ax
		push	270Fh
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		nop
		push	cs
		call	near ptr sub_20496
		add	sp, 8
		inc	si

loc_2045F:
		cmp	si, word_39EAA
		jl	short loc_20432
		pop	si
		pop	bp
		retf
sub_203F9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20468	proc far
		push	bp
		mov	bp, sp
		cmp	off_39E7C, 0
		jz	short loc_20492
		push	large [off_39E7C]
		call	_farfree
		add	sp, 4
		mov	dword_39E80, 0
		mov	off_39E7C, 0

loc_20492:
		xor	ax, ax
		pop	bp
		retf
sub_20468	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20496	proc far

var_10		= dword	ptr -10h
var_C		= dword	ptr -0Ch
var_8		= dword	ptr -8
var_4		= dword	ptr -4
arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		enter	10h, 0
		push	si
		push	di
		mov	di, [bp+arg_4]
		mov	[bp+var_4], 0
		mov	ax, [bp+arg_2]
		imul	ax, 50h
		push	ax
		mov	ax, [bp+arg_0]
		mov	bx, 8
		cwd
		idiv	bx
		pop	dx
		add	dx, ax
		mov	si, dx
		cmp	di, 270Fh
		jz	short loc_204EF
		mov	ax, di
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		shl	ax, 2
		mov	bx, ax
		mov	ax, [bx+401Ah]
		mov	dx, [bx+4018h]
		push	ax
		mov	ax, di
		mov	bx, 40h	; '@'
		push	dx
		cwd
		idiv	bx
		imul	dx, 281h
		pop	ax
		add	ax, dx
		pop	dx
		mov	word ptr [bp+var_C+2], dx
		mov	word ptr [bp+var_C], ax

loc_204EF:
		mov	ax, [bp+arg_6]
		imul	ax, 281h
		mov	dx, word ptr off_39E7C+2
		mov	bx, word ptr off_39E7C
		add	bx, ax
		mov	word ptr [bp+var_10+2],	dx
		mov	word ptr [bp+var_10], bx
		cmp	di, 270Fh
		jz	loc_20622
		xor	cx, cx
		jmp	loc_20619
; ---------------------------------------------------------------------------

loc_20513:
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_C]
		add	bx, ax
		mov	eax, es:[bx+201h]
		mov	[bp+var_4], eax
		not	eax
		mov	dx, cx
		shl	dx, 2
		les	bx, [bp+var_10]
		add	bx, dx
		and	eax, es:[bx+1]
		mov	[bp+var_8], eax
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_C]
		add	bx, ax
		mov	eax, es:[bx+1]
		and	eax, [bp+var_4]
		or	eax, [bp+var_8]
		les	bx, dword_38928
		add	bx, si
		mov	es:[bx], eax
		mov	eax, [bp+var_4]
		not	eax
		mov	dx, cx
		shl	dx, 2
		les	bx, [bp+var_10]
		add	bx, dx
		and	eax, es:[bx+81h]
		mov	[bp+var_8], eax
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_C]
		add	bx, ax
		mov	eax, es:[bx+81h]
		and	eax, [bp+var_4]
		or	eax, [bp+var_8]
		les	bx, dword_3892C
		add	bx, si
		mov	es:[bx], eax
		mov	eax, [bp+var_4]
		not	eax
		mov	dx, cx
		shl	dx, 2
		les	bx, [bp+var_10]
		add	bx, dx
		and	eax, es:[bx+101h]
		mov	[bp+var_8], eax
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_C]
		add	bx, ax
		mov	eax, es:[bx+101h]
		and	eax, [bp+var_4]
		or	eax, [bp+var_8]
		les	bx, dword_38930
		add	bx, si
		mov	es:[bx], eax
		mov	eax, [bp+var_4]
		not	eax
		mov	dx, cx
		shl	dx, 2
		les	bx, [bp+var_10]
		add	bx, dx
		and	eax, es:[bx+181h]
		mov	[bp+var_8], eax
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_C]
		add	bx, ax
		mov	eax, es:[bx+181h]
		and	eax, [bp+var_4]
		or	eax, [bp+var_8]
		les	bx, dword_38934
		add	bx, si
		mov	es:[bx], eax
		add	si, 50h	; 'P'
		inc	cx

loc_20619:
		cmp	cx, 20h	; ' '
		jb	loc_20513
		jmp	short loc_20696
; ---------------------------------------------------------------------------

loc_20622:
		xor	cx, cx
		jmp	short loc_20691
; ---------------------------------------------------------------------------

loc_20626:
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_10]
		add	bx, ax
		mov	eax, es:[bx+1]
		les	bx, dword_38928
		add	bx, si
		mov	es:[bx], eax
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_10]
		add	bx, ax
		mov	eax, es:[bx+81h]
		les	bx, dword_3892C
		add	bx, si
		mov	es:[bx], eax
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_10]
		add	bx, ax
		mov	eax, es:[bx+101h]
		les	bx, dword_38930
		add	bx, si
		mov	es:[bx], eax
		mov	ax, cx
		shl	ax, 2
		les	bx, [bp+var_10]
		add	bx, ax
		mov	eax, es:[bx+181h]
		les	bx, dword_38934
		add	bx, si
		mov	es:[bx], eax
		add	si, 50h	; 'P'
		inc	cx

loc_20691:
		cmp	cx, 20h	; ' '
		jb	short loc_20626

loc_20696:
		pop	di
		pop	si
		leave
		retf
sub_20496	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2069A	proc far

var_4		= dword	ptr -4
arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah

		enter	4, 0
		push	si
		push	di
		mov	ax, [bp+arg_2]
		imul	ax, 50h
		push	ax
		mov	ax, [bp+arg_0]
		mov	bx, 8
		cwd
		idiv	bx
		pop	dx
		add	dx, ax
		mov	di, dx
		mov	ax, [bp+arg_4]
		imul	ax, 281h
		mov	dx, word ptr off_39E7C+2
		mov	bx, word ptr off_39E7C
		add	bx, ax
		mov	word ptr [bp+var_4+2], dx
		mov	word ptr [bp+var_4], bx
		push	1
		call	sub_EA3E
		pop	cx
		xor	si, si
		jmp	short loc_20743
; ---------------------------------------------------------------------------

loc_206D8:
		les	bx, dword_38928
		add	bx, di
		mov	eax, es:[bx]
		mov	dx, si
		shl	dx, 2
		les	bx, [bp+var_4]
		add	bx, dx
		mov	es:[bx+1], eax
		les	bx, dword_3892C
		add	bx, di
		mov	eax, es:[bx]
		mov	dx, si
		shl	dx, 2
		les	bx, [bp+var_4]
		add	bx, dx
		mov	es:[bx+81h], eax
		les	bx, dword_38930
		add	bx, di
		mov	eax, es:[bx]
		mov	dx, si
		shl	dx, 2
		les	bx, [bp+var_4]
		add	bx, dx
		mov	es:[bx+101h], eax
		les	bx, dword_38934
		add	bx, di
		mov	eax, es:[bx]
		mov	dx, si
		shl	dx, 2
		les	bx, [bp+var_4]
		add	bx, dx
		mov	es:[bx+181h], eax
		add	di, 50h	; 'P'
		inc	si

loc_20743:
		cmp	si, 20h	; ' '
		jl	short loc_206D8
		push	0
		call	sub_EA3E
		pop	cx
		pop	di
		pop	si
		leave
		retf
sub_2069A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20754	proc far

var_26		= byte ptr -26h
var_21		= byte ptr -21h
var_16		= byte ptr -16h
arg_0		= byte ptr  6

		enter	26h, 0
		push	si
		lea	ax, [bp+var_26]
		push	ss
		push	ax
		push	ds
		push	offset aStage_dat ; "stage .dat"
		mov	cx, 0Fh
		call	SCOPY@
		mov	al, [bp+arg_0]
		add	al, 30h	; '0'
		mov	[bp+var_21], al
		push	ss
		lea	ax, [bp+var_26]
		push	ax
		call	sub_172D6
		push	ss
		lea	ax, [bp+var_16]
		push	ax
		push	16h
		call	sub_173DC
		mov	al, [bp+arg_0]
		add	al, 30h	; '0'
		mov	byte ptr aSt_grp+2, al
		mov	al, [bp+arg_0]
		add	al, 30h	; '0'
		mov	byte ptr aSt_mdt+2, al
		xor	si, si
		jmp	short loc_207B0
; ---------------------------------------------------------------------------

loc_2079C:
		push	ds
		mov	ax, si
		imul	ax, 0FFh
		add	ax, 228Eh
		push	ax
		push	0FAh ; '�
		call	sub_173DC
		inc	si

loc_207B0:
		cmp	si, 5
		jl	short loc_2079C
		call	sub_1742C
		pop	si
		leave
		retf
sub_20754	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_207BD	proc far

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		lea	ax, [si-32h]
		mov	bx, 14h
		cwd
		idiv	bx
		shl	dx, 5
		les	bx, [bp+arg_4]
		mov	ax, es:[bx]
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		mov	es:[bx], dx
		lea	ax, [si-32h]
		mov	bx, 14h
		cwd
		idiv	bx
		shl	ax, 5
		add	ax, 40h	; '@'
		les	bx, [bp+arg_4]
		mov	dx, es:[bx]
		add	dx, dx
		les	bx, off_39E9E
		add	bx, dx
		mov	es:[bx], ax
		les	bx, [bp+arg_4]
		mov	ax, es:[bx]
		add	ax, word_39E90
		push	ax
		mov	ax, es:[bx]
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		les	bx, [bp+arg_4]
		mov	ax, es:[bx]
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		push	cs
		call	near ptr sub_2069A
		add	sp, 6
		push	[bp+arg_2]
		les	bx, [bp+arg_4]
		mov	ax, es:[bx]
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		les	bx, [bp+arg_4]
		mov	ax, es:[bx]
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6
		les	bx, [bp+arg_4]
		inc	word ptr es:[bx]
		pop	si
		pop	bp
		retf
sub_207BD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20868	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	di, [bp+arg_0]
		mov	ax, di
		mov	bx, 5
		cwd
		idiv	bx
		mov	di, dx
		cmp	di, 4
		jz	short loc_208F0
		xor	si, si
		jmp	short loc_208BD
; ---------------------------------------------------------------------------

loc_20883:
		les	bx, off_39EA2
		mov	al, es:[bx+si]
		cbw
		dec	ax
		mov	bx, ax
		cmp	bx, 14h
		ja	short loc_208BC
		add	bx, bx
		jmp	cs:off_208F4[bx]

loc_2089A:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_1031B
		add	sp, 4

loc_208BC:
		inc	si

loc_208BD:
		cmp	si, word_39EAA
		jl	short loc_20883
		xor	si, si
		jmp	short loc_208EA
; ---------------------------------------------------------------------------

loc_208C7:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_1031B
		add	sp, 4
		inc	si

loc_208EA:
		cmp	si, word_39E90
		jl	short loc_208C7

loc_208F0:
		pop	di
		pop	si
		pop	bp
		retf
sub_20868	endp

; ---------------------------------------------------------------------------
off_208F4	dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_208BC
		dw offset loc_208BC
		dw offset loc_208BC
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A
		dw offset loc_2089A

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2091E	proc far

var_7A		= byte ptr -7Ah
var_16		= word ptr -16h
var_14		= word ptr -14h
var_12		= word ptr -12h
var_10		= word ptr -10h
var_E		= word ptr -0Eh
var_C		= word ptr -0Ch
var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6

		enter	7Ah, 0
		push	si
		push	di
		mov	[bp+var_4], 0
		mov	[bp+var_E], 0
		mov	ax, [bp+arg_0]
		mov	bx, 5
		cwd
		idiv	bx
		mov	[bp+arg_0], dx
		mov	word_39EAA, 0
		mov	word_39E90, 0
		cmp	[bp+arg_0], 4
		jz	loc_20DE4
		xor	di, di
		jmp	short loc_20972
; ---------------------------------------------------------------------------

loc_20952:
		mov	si, 8
		jmp	short loc_2096D
; ---------------------------------------------------------------------------

loc_20957:
		mov	bx, [bp+arg_0]
		imul	bx, 0FFh
		mov	al, [bx+di+228Eh]
		cbw
		test	ax, si
		jz	short loc_2096B
		inc	word_39E90

loc_2096B:
		sar	si, 1

loc_2096D:
		or	si, si
		jnz	short loc_20957
		inc	di

loc_20972:
		cmp	di, 32h	; '2'
		jl	short loc_20952
		mov	di, 32h	; '2'
		jmp	short loc_2099C
; ---------------------------------------------------------------------------

loc_2097C:
		mov	bx, [bp+arg_0]
		imul	bx, 0FFh
		mov	al, [bx+di+228Eh]
		cbw
		dec	ax
		mov	bx, ax
		cmp	bx, 14h
		ja	short loc_2099B
		add	bx, bx
		jmp	cs:off_20E22[bx]

loc_20997:
		inc	word_39EAA

loc_2099B:
		inc	di

loc_2099C:
		cmp	di, 0FAh ; '�
		jl	short loc_2097C
		mov	ax, word_39E90
		add	ax, word_39EAA
		push	ax
		push	cs
		call	near ptr sub_20399
		pop	cx
		cmp	word_39E90, 0
		jle	short loc_20A27
		mov	ax, word_39E90
		add	ax, ax
		push	ax
		call	@$bnwa$qui
		pop	cx
		mov	word ptr font+2, dx
		mov	word ptr font, ax
		mov	ax, word_39E90
		add	ax, ax
		push	ax
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39E88+2, dx
		mov	word ptr off_39E88, ax
		push	word_39E90
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39E8C+2, dx
		mov	word ptr off_39E8C, ax
		mov	ax, word_39E90
		add	ax, ax
		push	ax
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39E92+2, dx
		mov	word ptr off_39E92, ax
		push	word_39E90
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39E96+2, dx
		mov	word ptr off_39E96, ax
		mov	ax, word_39E90
		shl	ax, 2
		push	ax
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39EAC+2, dx
		mov	word ptr off_39EAC, ax
		jmp	short $+2

loc_20A27:
		cmp	word_39EAA, 0
		jle	short loc_20A7A
		mov	ax, word_39EAA
		add	ax, ax
		push	ax
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39E9A+2, dx
		mov	word ptr off_39E9A, ax
		mov	ax, word_39EAA
		add	ax, ax
		push	ax
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39E9E+2, dx
		mov	word ptr off_39E9E, ax
		push	word_39EAA
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39EA2+2, dx
		mov	word ptr off_39EA2, ax
		mov	ax, word_39EAA
		add	ax, ax
		push	ax
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39EA6+2, dx
		mov	word ptr off_39EA6, ax
		jmp	short $+2

loc_20A7A:
		call	IRand
		cwd
		idiv	word_39E90
		mov	word_39EB0, dx
		xor	si, si
		jmp	short loc_20A9C
; ---------------------------------------------------------------------------

loc_20A8C:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		mov	word ptr es:[bx], 0
		inc	si

loc_20A9C:
		cmp	si, word_39EAA
		jl	short loc_20A8C
		xor	si, si
		jmp	short loc_20AB6
; ---------------------------------------------------------------------------

loc_20AA6:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E92
		add	bx, ax
		mov	word ptr es:[bx], 0
		inc	si

loc_20AB6:
		cmp	si, word_39E90
		jl	short loc_20AA6
		xor	di, di
		jmp	loc_20B79
; ---------------------------------------------------------------------------

loc_20AC1:
		mov	si, 8
		jmp	loc_20B72
; ---------------------------------------------------------------------------

loc_20AC7:
		mov	bx, si
		dec	bx
		cmp	bx, 7
		ja	short loc_20AF0
		add	bx, bx
		jmp	cs:off_20E12[bx]

loc_20AD6:
		mov	[bp+var_2], 3
		jmp	short loc_20AF0
; ---------------------------------------------------------------------------

loc_20ADD:
		mov	[bp+var_2], 2
		jmp	short loc_20AF0
; ---------------------------------------------------------------------------

loc_20AE4:
		mov	[bp+var_2], 1
		jmp	short loc_20AF0
; ---------------------------------------------------------------------------

loc_20AEB:
		mov	[bp+var_2], 0

loc_20AF0:
		mov	bx, [bp+arg_0]
		imul	bx, 0FFh
		mov	al, [bx+di+228Eh]
		cbw
		test	ax, si
		jz	short loc_20B70
		mov	ax, di
		shl	ax, 7
		mov	bx, 280h
		cwd
		idiv	bx
		mov	ax, [bp+var_2]
		shl	ax, 5
		add	dx, ax
		mov	[bp+var_10], dx
		mov	ax, di
		mov	bx, 5
		cwd
		idiv	bx
		shl	ax, 5
		add	ax, 40h	; '@'
		mov	[bp+var_12], ax
		push	[bp+var_4]
		push	ax
		push	[bp+var_10]
		push	cs
		call	near ptr sub_2069A
		add	sp, 6
		mov	ax, [bp+var_4]
		add	ax, ax
		les	bx, font
		add	bx, ax
		mov	ax, [bp+var_10]
		mov	es:[bx], ax
		mov	ax, [bp+var_4]
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		mov	ax, [bp+var_12]
		mov	es:[bx], ax
		les	bx, off_39E8C
		add	bx, [bp+var_4]
		mov	byte ptr es:[bx], 0
		les	bx, off_39E96
		add	bx, [bp+var_4]
		mov	byte ptr es:[bx], 0
		inc	[bp+var_4]

loc_20B70:
		sar	si, 1

loc_20B72:
		or	si, si
		jnz	loc_20AC7
		inc	di

loc_20B79:
		cmp	di, 32h	; '2'
		jl	loc_20AC1
		mov	[bp+var_E], 0
		mov	di, 32h	; '2'
		jmp	loc_20C8D
; ---------------------------------------------------------------------------

loc_20B8B:
		mov	bx, [bp+arg_0]
		imul	bx, 0FFh
		mov	al, [bx+di+228Eh]
		cbw
		dec	ax
		mov	bx, ax
		cmp	bx, 14h
		ja	loc_20C8C
		add	bx, bx
		jmp	cs:off_20DE8[bx]

loc_20BA8:
		push	ss
		lea	ax, [bp+var_E]
		push	ax
		push	16h
		jmp	loc_20C59
; ---------------------------------------------------------------------------

loc_20BB2:
		push	ss
		lea	ax, [bp+var_E]
		push	ax
		push	17h
		jmp	loc_20C59
; ---------------------------------------------------------------------------

loc_20BBC:
		lea	ax, [di-32h]
		mov	bx, 14h
		cwd
		idiv	bx
		shl	dx, 5
		mov	[bp+var_8], dx
		lea	ax, [di-32h]
		cwd
		idiv	bx
		shl	ax, 5
		add	ax, 40h	; '@'
		mov	[bp+var_A], ax
		mov	[bp+var_6], 0
		jmp	short loc_20C23
; ---------------------------------------------------------------------------

loc_20BE1:
		mov	ax, [bp+var_6]
		add	ax, ax
		les	bx, font
		add	bx, ax
		mov	ax, es:[bx]
		cmp	ax, [bp+var_8]
		jnz	short loc_20C20
		mov	ax, [bp+var_6]
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		mov	ax, es:[bx]
		cmp	ax, [bp+var_A]
		jnz	short loc_20C20
		mov	bx, [bp+arg_0]
		imul	bx, 0FFh
		mov	al, [bx+di+228Eh]
		add	al, 0F3h ; '�
		les	bx, off_39E96
		add	bx, [bp+var_6]
		mov	es:[bx], al
		jmp	short loc_20C8C
; ---------------------------------------------------------------------------

loc_20C20:
		inc	[bp+var_6]

loc_20C23:
		mov	ax, [bp+var_6]
		cmp	ax, word_39E90
		jl	short loc_20BE1
		jmp	short loc_20C8C
; ---------------------------------------------------------------------------

loc_20C2E:
		push	ss
		lea	ax, [bp+var_E]
		push	ax
		push	1Dh
		jmp	short loc_20C59
; ---------------------------------------------------------------------------

loc_20C37:
		push	ss
		lea	ax, [bp+var_E]
		push	ax
		push	19h
		jmp	short loc_20C59
; ---------------------------------------------------------------------------

loc_20C40:
		push	ss
		lea	ax, [bp+var_E]
		push	ax
		push	1Bh
		jmp	short loc_20C59
; ---------------------------------------------------------------------------

loc_20C49:
		push	ss
		lea	ax, [bp+var_E]
		push	ax
		push	1Ah
		jmp	short loc_20C59
; ---------------------------------------------------------------------------

loc_20C52:
		push	ss
		lea	ax, [bp+var_E]
		push	ax
		push	1Ch

loc_20C59:
		push	di
		push	cs
		call	near ptr sub_207BD
		add	sp, 8
		mov	bx, [bp+arg_0]
		imul	bx, 0FFh
		mov	al, [bx+di+228Eh]
		mov	bx, [bp+var_E]
		mov	es, word ptr off_39EA2+2
		add	bx, word ptr off_39EA2
		mov	es:[bx-1], al
		mov	ax, [bp+var_E]
		dec	ax
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		mov	word ptr es:[bx], 0

loc_20C8C:
		inc	di

loc_20C8D:
		cmp	di, 0FAh ; '�
		jl	loc_20B8B
		cmp	byte_34A49, 1
		jnz	short loc_20CE3
		xor	si, si
		jmp	short loc_20CDA
; ---------------------------------------------------------------------------

loc_20CA0:
		les	bx, off_39E96
		mov	al, es:[bx+si]
		cbw
		imul	ax, 5
		mov	bx, ax
		mov	al, [bx+126Eh]
		mov	ah, 0
		mov	[bp+var_C], ax
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6
		inc	si

loc_20CDA:
		cmp	si, word_39E90
		jl	short loc_20CA0
		jmp	loc_20DE4
; ---------------------------------------------------------------------------

loc_20CE3:
		lea	ax, [bp+var_7A]
		push	ss
		push	ax
		push	ds
		push	offset unk_35C36
		mov	cx, 64h	; 'd'
		call	SCOPY@
		mov	[bp+var_14], 0

loc_20CF9:
		mov	[bp+var_16], 0
		xor	si, si
		jmp	loc_20DAD
; ---------------------------------------------------------------------------

loc_20D03:
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_7A]
		add	bx, ax
		cmp	word ptr ss:[bx], 0FFFFh
		jnz	short loc_20D15
		inc	[bp+var_16]

loc_20D15:
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_7A]
		add	bx, ax
		cmp	word ptr ss:[bx], 0Ch
		jl	loc_20DAC
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_7A]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, 6
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_20D89
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_7A]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, 6
		cwd
		idiv	bx
		les	bx, off_39E96
		push	ax
		mov	al, es:[bx+si]
		cbw
		imul	ax, 5
		pop	bx
		add	bx, ax
		mov	al, [bx+1273h]
		mov	ah, 0
		mov	[bp+var_C], ax
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E88
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, font
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6

loc_20D89:
		mov	bx, si
		add	bx, bx
		lea	ax, [bp+var_7A]
		add	bx, ax
		inc	word ptr ss:[bx]
		mov	bx, si
		add	bx, bx
		add	bx, ax
		cmp	word ptr ss:[bx], 18h
		jle	short loc_20DAC
		mov	bx, si
		add	bx, bx
		add	bx, ax
		mov	word ptr ss:[bx], 0FFFFh

loc_20DAC:
		inc	si

loc_20DAD:
		cmp	si, word_39E90
		jl	loc_20D03
		mov	ax, [bp+var_16]
		cmp	ax, word_39E90
		jge	short loc_20DE4
		mov	ax, [bp+var_14]
		cmp	ax, word_39E90
		jge	short loc_20DD6
		mov	bx, [bp+var_14]
		add	bx, bx
		lea	ax, [bp+var_7A]
		add	bx, ax
		mov	word ptr ss:[bx], 0Ch

loc_20DD6:
		inc	[bp+var_14]
		push	1
		call	sub_E364
		pop	cx
		jmp	loc_20CF9
; ---------------------------------------------------------------------------

loc_20DE4:
		pop	di
		pop	si
		leave
		retf
sub_2091E	endp

; ---------------------------------------------------------------------------
off_20DE8	dw offset loc_20BA8
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BB2
		dw offset loc_20BBC
		dw offset loc_20BBC
		dw offset loc_20BBC
		dw offset loc_20C2E
		dw offset loc_20C37
		dw offset loc_20C40
		dw offset loc_20C49
		dw offset loc_20C52
off_20E12	dw offset loc_20AD6
		dw offset loc_20ADD
		dw offset loc_20AF0
		dw offset loc_20AE4
		dw offset loc_20AF0
		dw offset loc_20AF0
		dw offset loc_20AF0
		dw offset loc_20AEB
off_20E22	dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_2099B
		dw offset loc_2099B
		dw offset loc_2099B
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997
		dw offset loc_20997

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_20E4C	proc far

var_1A		= qword	ptr -1Ah
var_C		= word ptr -0Ch
var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6

		enter	0Ch, 0
		push	si
		push	di
		mov	di, [bp+arg_0]
		cmp	di, 1
		jnz	short loc_20E5F
		mov	byte_39EB2, 0

loc_20E5F:
		xor	si, si
		jmp	loc_212CB
; ---------------------------------------------------------------------------

loc_20E64:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, word_36C28
		mov	[bp+var_A], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		mov	[bp+var_2], ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, word_36C2A
		mov	[bp+var_C], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		mov	[bp+var_4], ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		mov	ax, word_36C28
		sub	ax, es:[bx]
		mov	[bp+var_6], ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		mov	ax, word_36C2A
		sub	ax, es:[bx]
		mov	[bp+var_8], ax
		les	bx, off_39EA2
		mov	al, es:[bx+si]
		cbw
		dec	ax
		mov	bx, ax
		cmp	bx, 14h
		ja	loc_212CA
		add	bx, bx
		jmp	cs:off_212D7[bx]

loc_20EDB:
		cmp	[bp+var_2], 18h
		jnb	loc_20F67
		cmp	[bp+var_4], 18h
		jnb	short loc_20F67
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jnz	short loc_20F67
		inc	word ptr es:[bx]
		cmp	[bp+var_8], 0
		jg	short loc_20F14
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0FFE8h
		jmp	short loc_20F24
; ---------------------------------------------------------------------------

loc_20F14:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 18h

loc_20F24:
		mov	word_36C2A, ax
		cmp	word_34A7C, 2
		jnz	short loc_20F3C
		cmp	[bp+var_6], 0
		jge	short loc_20F3C
		mov	word_34A7C, 1
		jmp	short loc_20F4F
; ---------------------------------------------------------------------------

loc_20F3C:
		cmp	word_34A7C, 1
		jnz	short loc_20F4F
		cmp	[bp+var_6], 0
		jle	short loc_20F4F
		mov	word_34A7C, 2

loc_20F4F:
		push	0		; int
		; Hack (fld flt_35C9A)
		db 0cdh
		db 035h
		db 006h
		db 0fah
		db 012h
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_C62D
		add	sp, 0Ah

loc_20F67:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jz	short loc_20F85
		inc	word ptr es:[bx]
		cmp	word ptr es:[bx], 8
		jl	short loc_20F85
		mov	word ptr es:[bx], 0

loc_20F85:
		cmp	di, 1
		jnz	loc_212CA
		jmp	loc_212BB
; ---------------------------------------------------------------------------

loc_20F8F:
		cmp	byte_34A30, 0
		jz	short loc_20FA3
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		inc	word ptr es:[bx]

loc_20FA3:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0C8h ; '?'
		jl	short loc_20FBF
		push	0
		push	si
		nop
		push	cs
		call	near ptr sub_21301
		add	sp, 4

loc_20FBF:
		cmp	di, 1
		jnz	loc_212CA
		jmp	short loc_20FFE
; ---------------------------------------------------------------------------

loc_20FC8:
		cmp	byte_34A30, 0
		jz	short loc_20FDC
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		inc	word ptr es:[bx]

loc_20FDC:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 64h ;	'd'
		jl	short loc_20FF7
		push	0
		push	si
		nop
		push	cs
		call	near ptr sub_21301
		add	sp, 4

loc_20FF7:
		cmp	di, 1
		jnz	loc_212CA

loc_20FFE:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		mov	word ptr es:[bx], 0
		push	di
		push	si
		nop
		push	cs
		call	near ptr sub_21301
		jmp	short loc_2105A
; ---------------------------------------------------------------------------

loc_21016:
		cmp	[bp+var_2], 18h
		jnb	short loc_21022
		cmp	[bp+var_4], 18h
		jb	short loc_21032

loc_21022:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jz	short loc_2103D

loc_21032:
		push	0
		push	si
		nop
		push	cs
		call	near ptr sub_21577
		add	sp, 4

loc_2103D:
		cmp	di, 1
		jnz	loc_212CA
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		mov	word ptr es:[bx], 0
		push	di
		push	si
		nop
		push	cs
		call	near ptr sub_21577

loc_2105A:
		add	sp, 4
		jmp	loc_212CA
; ---------------------------------------------------------------------------

loc_21060:
		cmp	[bp+var_2], 20h	; ' '
		jnb	short loc_210B1
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		mov	ax, word_36C2A
		sub	ax, es:[bx]
		cmp	ax, 20h	; ' '
		jg	short loc_210B1
		mov	ax, word_36C2A
		sub	ax, es:[bx]
		jle	short loc_210B1
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jnz	short loc_210B1
		inc	word ptr es:[bx]
		push	3		; int
		; Hack (fld dbl_34A94)
		db 0cdh
		db 039h
		db 006h
		db 0f4h
		db 000h
		; Hack (fchs)
		db 0cdh
		db 035h
		db 0e0h
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_C62D
		add	sp, 0Ah

loc_210B1:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jz	loc_212CA
		jmp	loc_21293
; ---------------------------------------------------------------------------

loc_210C6:
		cmp	[bp+var_2], 20h	; ' '
		jnb	short loc_21117
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		mov	ax, word_36C2A
		sub	ax, es:[bx]
		jge	short loc_21117
		mov	ax, word_36C2A
		sub	ax, es:[bx]
		cmp	ax, 0FFE0h
		jl	short loc_21117
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jnz	short loc_21117
		inc	word ptr es:[bx]
		push	3		; int
		; Hack (fld dbl_34A94)
		db 0cdh
		db 039h
		db 006h
		db 0f4h
		db 000h
		; Hack (fchs)
		db 0cdh
		db 035h
		db 0e0h
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_C62D
		add	sp, 0Ah

loc_21117:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jz	loc_212CA
		jmp	loc_21293
; ---------------------------------------------------------------------------

loc_2112C:
		cmp	[bp+var_4], 20h	; ' '
		jnb	loc_211CD
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, word_36C28
		cmp	ax, 20h	; ' '
		jg	loc_211CD
		mov	ax, es:[bx]
		sub	ax, word_36C28
		jl	short loc_211CD
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jnz	short loc_211CD
		cmp	byte_39EB2, 0
		jnz	short loc_211CD
		inc	word ptr es:[bx]
		mov	byte_39EB2, 1
		cmp	word_34A7C, 0
		jnz	short loc_21198
		push	3		; int
		; Hack (fld dbl_34A94)
		db 0cdh
		db 039h
		db 006h
		db 0f4h
		db 000h
		; Hack (fchs)
		db 0cdh
		db 035h
		db 0e0h
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_C62D
		add	sp, 0Ah
		jmp	short loc_211CD
; ---------------------------------------------------------------------------

loc_21198:
		cmp	word_34A7C, 1
		jnz	short loc_211A4
		mov	ax, 2
		jmp	short loc_211CA
; ---------------------------------------------------------------------------

loc_211A4:
		cmp	word_34A7C, 2
		jnz	short loc_211B0
		mov	ax, 1
		jmp	short loc_211CA
; ---------------------------------------------------------------------------

loc_211B0:
		cmp	word_34A7C, 3
		jnz	short loc_211BC
		mov	ax, 4
		jmp	short loc_211CA
; ---------------------------------------------------------------------------

loc_211BC:
		cmp	word_34A7C, 4
		jnz	short loc_211C8
		mov	ax, 3
		jmp	short loc_211CA
; ---------------------------------------------------------------------------

loc_211C8:
		xor	ax, ax

loc_211CA:
		mov	word_34A7C, ax

loc_211CD:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jz	loc_212CA
		jmp	loc_21293
; ---------------------------------------------------------------------------

loc_211E2:
		cmp	[bp+var_4], 20h	; ' '
		jnb	loc_21283
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, word_36C28
		jg	loc_21283
		mov	ax, es:[bx]
		sub	ax, word_36C28
		cmp	ax, 0FFE0h
		jl	short loc_21283
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jnz	short loc_21283
		cmp	byte_39EB2, 0
		jnz	short loc_21283
		inc	word ptr es:[bx]
		mov	byte_39EB2, 1
		cmp	word_34A7C, 0
		jnz	short loc_2124E
		push	3		; int
		; Hack (fld dbl_34A94)
		db 0cdh
		db 039h
		db 006h
		db 0f4h
		db 000h
		; Hack (fchs)
		db 0cdh
		db 035h
		db 0e0h
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_C62D
		add	sp, 0Ah
		jmp	short loc_21283
; ---------------------------------------------------------------------------

loc_2124E:
		cmp	word_34A7C, 1
		jnz	short loc_2125A
		mov	ax, 2
		jmp	short loc_21280
; ---------------------------------------------------------------------------

loc_2125A:
		cmp	word_34A7C, 2
		jnz	short loc_21266
		mov	ax, 1
		jmp	short loc_21280
; ---------------------------------------------------------------------------

loc_21266:
		cmp	word_34A7C, 3
		jnz	short loc_21272
		mov	ax, 4
		jmp	short loc_21280
; ---------------------------------------------------------------------------

loc_21272:
		cmp	word_34A7C, 4
		jnz	short loc_2127E
		mov	ax, 3
		jmp	short loc_21280
; ---------------------------------------------------------------------------

loc_2127E:
		xor	ax, ax

loc_21280:
		mov	word_34A7C, ax

loc_21283:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jz	short loc_212CA

loc_21293:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jz	short loc_212B6
		inc	word ptr es:[bx]
		cmp	word ptr es:[bx], 8
		jl	short loc_212B6
		mov	word ptr es:[bx], 0
		mov	byte_39EB2, 0

loc_212B6:
		cmp	di, 1
		jnz	short loc_212CA

loc_212BB:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		mov	word ptr es:[bx], 0

loc_212CA:
		inc	si

loc_212CB:
		cmp	si, word_39EAA
		jb	loc_20E64
		pop	di
		pop	si
		leave
		retf
sub_20E4C	endp

; ---------------------------------------------------------------------------
off_212D7	dw offset loc_20EDB
		dw offset loc_20F8F
		dw offset loc_20F8F
		dw offset loc_20F8F
		dw offset loc_20F8F
		dw offset loc_20F8F
		dw offset loc_20F8F
		dw offset loc_20FC8
		dw offset loc_20FC8
		dw offset loc_20FC8
		dw offset loc_20FC8
		dw offset loc_20FC8
		dw offset loc_20FC8
		dw offset loc_212CA
		dw offset loc_212CA
		dw offset loc_212CA
		dw offset loc_21016
		dw offset loc_210C6
		dw offset loc_21060
		dw offset loc_2112C
		dw offset loc_211E2

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21301	proc far

var_1		= byte ptr -1
arg_0		= word ptr  6
arg_2		= word ptr  8

		enter	2, 0
		push	si
		mov	si, [bp+arg_0]
		cmp	[bp+arg_2], 1
		jnz	short loc_21364
		cmp	off_39EB3, 0
		jz	short loc_2132D
		push	large [off_39EB3] ; font
		call	@$bdla$qnv
		add	sp, 4
		mov	off_39EB3, 0

loc_2132D:
		cmp	word_39EAA, 0
		jz	short loc_21347
		mov	ax, word_39EAA
		add	ax, ax
		push	ax
		call	@$bnwa$qui
		pop	cx
		mov	word ptr off_39EB3+2, dx
		mov	word ptr off_39EB3, ax

loc_21347:
		xor	si, si
		jmp	short loc_2135B
; ---------------------------------------------------------------------------

loc_2134B:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		mov	word ptr es:[bx], 0
		inc	si

loc_2135B:
		cmp	si, word_39EAA
		jl	short loc_2134B
		jmp	loc_2155C
; ---------------------------------------------------------------------------

loc_21364:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jnz	short loc_213DE
		push	1
		call	sub_EA3E
		pop	cx
		push	18h
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6
		push	0
		call	sub_EA3E
		pop	cx
		push	18h
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		mov	word ptr es:[bx], 1
		jmp	loc_2155C
; ---------------------------------------------------------------------------

loc_213DE:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		cmp	word ptr es:[bx], 1
		jnz	short loc_2141A
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		mov	ax, es:[bx]
		mov	bx, 0Ah
		cwd
		idiv	bx
		cmp	dx, 9
		jnz	loc_2155C
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		mov	word ptr es:[bx], 2
		jmp	loc_2155C
; ---------------------------------------------------------------------------

loc_2141A:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		cmp	word ptr es:[bx], 2
		jnz	loc_214D3
		les	bx, off_39EA2
		mov	al, es:[bx+si]
		cbw
		sub	ax, 2
		mov	bx, ax
		cmp	bx, 0Bh
		ja	short loc_21467
		add	bx, bx
		jmp	cs:off_2155F[bx]

loc_21445:
		mov	[bp+var_1], 0Ch
		jmp	short loc_21467
; ---------------------------------------------------------------------------

loc_2144B:
		mov	[bp+var_1], 1Dh
		jmp	short loc_21467
; ---------------------------------------------------------------------------

loc_21451:
		mov	[bp+var_1], 15h
		jmp	short loc_21467
; ---------------------------------------------------------------------------

loc_21457:
		mov	[bp+var_1], 17h
		jmp	short loc_21467
; ---------------------------------------------------------------------------

loc_2145D:
		mov	[bp+var_1], 19h
		jmp	short loc_21467
; ---------------------------------------------------------------------------

loc_21463:
		mov	[bp+var_1], 1Bh

loc_21467:
		push	38h ; '8'
		mov	al, [bp+var_1]
		mov	ah, 0
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		push	18h
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		mov	word ptr es:[bx], 3
		jmp	loc_2155C
; ---------------------------------------------------------------------------

loc_214D3:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		inc	word ptr es:[bx]
		cmp	word ptr es:[bx], 0Ah
		jl	short loc_2155C
		push	1
		call	sub_EA3E
		pop	cx
		push	17h
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6
		push	0
		call	sub_EA3E
		pop	cx
		push	17h
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6
		mov	ax, si
		add	ax, ax
		les	bx, off_39EB3
		add	bx, ax
		mov	word ptr es:[bx], 0
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		mov	word ptr es:[bx], 0

loc_2155C:
		pop	si
		leave
		retf
sub_21301	endp

; ---------------------------------------------------------------------------
off_2155F	dw offset loc_21445
		dw offset loc_2144B
		dw offset loc_21451
		dw offset loc_21457
		dw offset loc_2145D
		dw offset loc_21463
		dw offset loc_21445
		dw offset loc_2144B
		dw offset loc_21451
		dw offset loc_21457
		dw offset loc_2145D
		dw offset loc_21463

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21577	proc far

var_12		= qword	ptr -12h
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6
arg_2		= word ptr  8

		enter	4, 0
		push	si
		push	di
		mov	si, [bp+arg_0]
		cmp	[bp+arg_2], 1
		jnz	short loc_215B0
		mov	word_39EB7, 0
		mov	word_39EBD, 0
		cmp	word_34A86, 0
		jz	loc_21815
		push	1Dh
		push	word_39EBB
		push	word_39EB9
		call	sub_197E1
		add	sp, 6
		jmp	loc_217F2
; ---------------------------------------------------------------------------

loc_215B0:
		cmp	word_39EBD, 1
		jnz	short loc_215BF
		cmp	word_39EB7, si
		jnz	loc_21815

loc_215BF:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jz	short loc_215D2
		inc	word ptr es:[bx]

loc_215D2:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0
		jnz	short loc_21634
		mov	word_34A86, 1
		mov	word ptr es:[bx], 1
		mov	word_39EB7, si
		mov	word_39EBD, 1
		push	large 200020h
		push	word_34A90
		push	word_34A8E
		call	sub_10433
		add	sp, 8
		push	1Eh

loc_2160F:
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]

loc_21629:
		call	sub_197E1
		add	sp, 6
		jmp	loc_21815
; ---------------------------------------------------------------------------

loc_21634:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 0Ah
		jnz	short loc_21670
		push	large 200020h
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_10433
		add	sp, 8
		push	1Fh
		jmp	short loc_2160F
; ---------------------------------------------------------------------------

loc_21670:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 14h
		jnz	loc_2174D
		push	large 200020h
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_10433
		add	sp, 8
		push	1Dh
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		push	word ptr es:[bx]
		mov	ax, si
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		push	word ptr es:[bx]
		call	sub_197E1
		add	sp, 6
		xor	di, di
		mov	[bp+var_2], 0

loc_216D5:
		les	bx, off_39EA2
		mov	al, es:[bx+di]
		cbw
		cmp	ax, 11h
		jnz	short loc_216F5
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_216F5
		cmp	di, si
		jnz	short loc_2170D

loc_216F5:
		inc	di
		cmp	[bp+var_2], 0Fh
		jle	short loc_21700
		mov	di, si
		jmp	short loc_2170D
; ---------------------------------------------------------------------------

loc_21700:
		cmp	di, word_39EAA
		jl	short loc_216D5
		xor	di, di
		inc	[bp+var_2]
		jmp	short loc_216D5
; ---------------------------------------------------------------------------

loc_2170D:
		mov	ax, di
		add	ax, ax
		les	bx, off_39E9A
		add	bx, ax
		mov	ax, es:[bx]
		mov	word_39EB9, ax
		mov	ax, di
		add	ax, ax
		les	bx, off_39E9E
		add	bx, ax
		mov	ax, es:[bx]
		mov	word_39EBB, ax
		push	large 200020h
		push	ax
		push	word_39EB9
		call	sub_10433
		add	sp, 8
		push	1Fh

loc_21742:
		push	word_39EBB
		push	word_39EB9
		jmp	loc_21629
; ---------------------------------------------------------------------------

loc_2174D:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 1Eh
		jnz	short loc_21777
		push	large 200020h
		push	word_39EBB
		push	word_39EB9
		call	sub_10433
		add	sp, 8
		push	1Eh
		jmp	short loc_21742
; ---------------------------------------------------------------------------

loc_21777:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 28h ;	'('
		jnz	short loc_217FA
		push	large 200020h
		push	word_39EBB
		push	word_39EB9
		call	sub_10433
		add	sp, 8
		push	1Dh
		push	word_39EBB
		push	word_39EB9
		call	sub_197E1
		add	sp, 6
		call	IRand
		mov	bx, 5
		cwd
		idiv	bx
		mov	word_34A7C, dx
		push	3		; int
		call	IRand
		mov	bx, 13h
		cwd
		idiv	bx
		add	dx, 0FFF7h
		mov	[bp+var_4], dx
		; Hack (fild [bp+var_4])
		db 0cdh
		db 03bh
		db 046h
		db 0fch
		sub	sp, 8
		; Hack (fstp [bp+var_12])
		db 0cdh
		db 039h
		db 05eh
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_C62D
		add	sp, 0Ah
		mov	ax, word_39EB9
		mov	word_36C28, ax
		mov	ax, word_39EBB
		mov	word_36C2A, ax

loc_217F2:
		mov	word_34A86, 0
		jmp	short loc_21815
; ---------------------------------------------------------------------------

loc_217FA:
		mov	ax, si
		add	ax, ax
		les	bx, off_39EA6
		add	bx, ax
		cmp	word ptr es:[bx], 3Ch ;	'<'
		jnz	short loc_21815
		mov	word ptr es:[bx], 0
		mov	word_39EBD, 0

loc_21815:
		pop	di
		pop	si
		leave
		retf
sub_21577	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21819	proc far
		push	bp
		mov	bp, sp
		mov	word_39E90, 1
		mov	font, 0
		mov	off_39E88, 0
		mov	off_39E8C, 0
		mov	off_39E92, 0
		mov	off_39E96, 0
		mov	off_39EAC, 0
		mov	word_39EAA, 1
		mov	off_39E9A, 0
		mov	off_39E9E, 0
		mov	off_39EA2, 0
		mov	off_39EA6, 0
		pop	bp
		retf
sub_21819	endp

seg031		ends

; ===========================================================================

; Segment type:	Pure code
seg032		segment	byte public 'CODE' use16
		assume cs:seg032
		;org 4
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21884	proc far
		push	bp
		mov	bp, sp
		pop	bp
		retf
sub_21884	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21889	proc far
		push	bp
		mov	bp, sp
		mov	dx, 7Ch	; '|'
		mov	al, 0C0h ; '?'
		out	dx, al
		mov	dx, 7Eh	; '~'
		mov	al, 55h	; 'U'
		out	dx, al
		mov	al, 0FFh
		out	dx, al
		mov	al, 55h	; 'U'
		out	dx, al
		mov	al, 0AAh ; '?'
		out	dx, al
		pop	bp
		retf
sub_21889	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_218A3	proc far

var_2		= byte ptr -2
var_1		= byte ptr -1
arg_0		= word ptr  6
arg_2		= word ptr  8

		enter	2, 0
		push	si
		push	di
		mov	di, [bp+arg_2]
		mov	[bp+var_1], 0FEh ; '?'
		mov	ax, [bp+arg_0]
		add	ax, 0F10h
		mov	si, ax
		cmp	di, 2
		jnz	short loc_218C1
		push	0Ah
		jmp	short loc_218C7
; ---------------------------------------------------------------------------

loc_218C1:
		or	di, di
		jnz	short loc_218CF
		push	7

loc_218C7:
		call	sub_EA71
		pop	cx
		jmp	short loc_218D8
; ---------------------------------------------------------------------------

loc_218CF:
		cmp	di, 1
		jnz	short loc_218D8
		push	cs
		call	near ptr sub_21889

loc_218D8:
		mov	[bp+var_2], 0
		jmp	short loc_2190D
; ---------------------------------------------------------------------------

loc_218DE:
		push	1
		call	sub_EA3E
		les	bx, dword_38928
		add	bx, si
		mov	al, [bp+var_1]
		mov	es:[bx], al
		push	0
		call	sub_EA3E
		add	sp, 4
		les	bx, dword_38928
		add	bx, si
		mov	al, [bp+var_1]
		mov	es:[bx], al
		add	si, 50h	; 'P'
		inc	[bp+var_2]

loc_2190D:
		cmp	[bp+var_2], 0Fh
		jb	short loc_218DE
		call	sub_EB05
		pop	di
		pop	si
		leave
		retf
sub_218A3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2191C	proc far

var_2		= word ptr -2
arg_0		= word ptr  6
arg_2		= word ptr  8

		enter	2, 0
		push	si
		push	di
		mov	si, [bp+arg_0]
		mov	di, [bp+arg_2]
		cmp	di, 3E7h
		jnz	loc_219D1
		push	1
		call	sub_EA3E
		mov	ax, si
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	bx, 4
		cwd
		idiv	bx
		push	dx
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		add	ax, 14Eh
		push	ax
		push	30h ; '0'
		mov	ax, si
		cwd
		sub	ax, dx
		sar	ax, 1
		shl	ax, 4
		add	ax, 80h	; '?'
		push	ax
		call	sub_109B2
		push	0
		call	sub_EA3E
		mov	ax, si
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	bx, 4
		cwd
		idiv	bx
		push	dx
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		add	ax, 14Eh
		push	ax
		push	30h ; '0'
		mov	ax, si
		cwd
		sub	ax, dx
		sar	ax, 1
		shl	ax, 4
		add	ax, 80h	; '?'
		push	ax
		call	sub_109B2
		add	sp, 14h
		mov	ax, si
		mov	bx, 2
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	loc_21A84
		cmp	si, word_3A1E7
		jnb	short loc_219B7
		push	bx
		jmp	short loc_219C3
; ---------------------------------------------------------------------------

loc_219B7:
		cmp	si, word_3A1E5
		jnb	short loc_219C1
		push	1
		jmp	short loc_219C3
; ---------------------------------------------------------------------------

loc_219C1:
		push	0

loc_219C3:
		lea	ax, [si-1]
		push	ax
		push	cs
		call	near ptr sub_218A3
		add	sp, 4
		jmp	loc_21A84
; ---------------------------------------------------------------------------

loc_219D1:
		cmp	di, 0FFFFh
		jnz	short loc_21A35
		mov	[bp+var_2], 0
		jmp	short loc_21A2E
; ---------------------------------------------------------------------------

loc_219DD:
		mov	ax, [bp+var_2]
		mov	bx, 4
		cwd
		idiv	bx
		push	dx
		mov	ax, [bp+var_2]
		cwd
		idiv	bx
		add	ax, 14Eh
		push	ax
		push	30h ; '0'
		mov	ax, [bp+var_2]
		shl	ax, 4
		add	ax, 80h	; '?'
		push	ax
		call	sub_10585
		add	sp, 8
		mov	ax, [bp+var_2]
		cmp	ax, word_3A1E7
		jnb	short loc_21A12
		push	2
		jmp	short loc_21A21
; ---------------------------------------------------------------------------

loc_21A12:
		mov	ax, [bp+var_2]
		cmp	ax, word_3A1E5
		jnb	short loc_21A1F
		push	1
		jmp	short loc_21A21
; ---------------------------------------------------------------------------

loc_21A1F:
		push	0

loc_21A21:
		push	[bp+var_2]
		push	cs
		call	near ptr sub_218A3
		add	sp, 4
		inc	[bp+var_2]

loc_21A2E:
		cmp	[bp+var_2], si
		jl	short loc_219DD
		jmp	short loc_21A84
; ---------------------------------------------------------------------------

loc_21A35:
		mov	ax, di
		mov	bx, 4
		cwd
		idiv	bx
		push	dx
		mov	ax, di
		cwd
		idiv	bx
		add	ax, 14Eh
		push	ax
		push	30h ; '0'
		mov	ax, di
		shl	ax, 4
		add	ax, 80h	; '?'
		push	ax
		call	sub_10585
		add	sp, 8
		cmp	di, word_3A1E7
		jnb	short loc_21A64
		push	2
		jmp	short loc_21A70
; ---------------------------------------------------------------------------

loc_21A64:
		cmp	di, word_3A1E5
		jnb	short loc_21A6E
		push	1
		jmp	short loc_21A70
; ---------------------------------------------------------------------------

loc_21A6E:
		push	0

loc_21A70:
		push	di
		push	cs
		call	near ptr sub_218A3
		add	sp, 4
		lea	ax, [si-1]
		cmp	ax, di
		jnz	short loc_21A84
		mov	ax, 1
		jmp	short loc_21A86
; ---------------------------------------------------------------------------

loc_21A84:
		xor	ax, ax

loc_21A86:
		pop	di
		pop	si
		leave
		retf
sub_2191C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21A8A	proc far

arg_0		= dword	ptr  6
arg_4		= dword	ptr  0Ah
arg_8		= dword	ptr  0Eh
arg_C		= dword	ptr  12h
arg_10		= byte ptr  16h
arg_12		= word ptr  18h
arg_14		= dword	ptr  1Ah
arg_18		= byte ptr  1Eh
arg_1A		= word ptr  20h
arg_1C		= word ptr  22h
arg_1E		= word ptr  24h
arg_20		= word ptr  26h

		push	bp
		mov	bp, sp
		push	si
		cmp	word_34A72, 1
		jnz	short loc_21AAE
		les	bx, [bp+arg_8]
		dec	word ptr es:[bx]
		mov	word_34A72, 0
		push	3E7h
		push	word ptr es:[bx]
		push	cs
		call	near ptr sub_2191C
		add	sp, 4

loc_21AAE:
		push	[bp+arg_20]
		push	[bp+arg_1E]
		push	[bp+arg_1C]
		push	[bp+arg_1A]
		push	ds
		push	offset unk_386B8
		call	sub_2FFC1
		add	sp, 0Ch
		cmp	[bp+arg_18], 1
		jnz	short loc_21AD5
		les	bx, [bp+arg_4]
		cmp	word ptr es:[bx], 0
		jz	short loc_21AE9

loc_21AD5:
		push	large [dword_36C16]
		nop
		push	cs
		call	near ptr sub_22234
		add	sp, 4
		cmp	ax, 1
		jnz	loc_21B8A

loc_21AE9:
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 0
		xor	si, si
		jmp	short loc_21B11
; ---------------------------------------------------------------------------

loc_21AF5:
		push	large 0F000Fh
		push	0Fh
		les	bx, [bp+arg_C]
		add	bx, si
		mov	al, es:[bx]
		mov	ah, 0
		push	ax
		call	sub_EB59
		add	sp, 8
		inc	si

loc_21B11:
		mov	al, [bp+arg_10]
		mov	ah, 0
		cmp	ax, si
		jg	short loc_21AF5
		les	bx, [bp+arg_8]
		dec	word ptr es:[bx]
		les	bx, [bp+arg_4]
		mov	word ptr es:[bx], 1
		cmp	word_34A7C, 1
		jz	short loc_21B53
		cmp	word_34A7C, 3
		jz	short loc_21B53
		cmp	word_34A7C, 2
		jz	short loc_21B5B
		cmp	word_34A7C, 4
		jz	short loc_21B5B
		cmp	word_34A7C, 0
		jnz	short loc_21B61
		cmp	word_36C28, 130h
		jge	short loc_21B5B

loc_21B53:
		mov	word_34A7C, 2
		jmp	short loc_21B61
; ---------------------------------------------------------------------------

loc_21B5B:
		mov	word_34A7C, 1

loc_21B61:
		movsx	eax, [bp+arg_12]
		add	dword_34A5A, eax
		call	sub_1889C
		push	3
		call	sub_125C9
		call	[bp+arg_14]
		push	3E7h
		les	bx, [bp+arg_8]
		push	word ptr es:[bx]
		push	cs
		call	near ptr sub_2191C
		add	sp, 6

loc_21B8A:
		les	bx, [bp+arg_4]
		cmp	word ptr es:[bx], 1
		jnz	short loc_21BEC
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 28h ;	'('
		jge	short loc_21BEC
		mov	ax, es:[bx]
		mov	bx, 4
		cwd
		idiv	bx
		cmp	dx, 2
		jnz	short loc_21BD5
		xor	si, si
		jmp	short loc_21BCA
; ---------------------------------------------------------------------------

loc_21BAE:
		push	large 0F000Fh
		push	0Fh
		les	bx, [bp+arg_C]
		add	bx, si
		mov	al, es:[bx]
		mov	ah, 0
		push	ax
		call	sub_EB59
		add	sp, 8
		inc	si

loc_21BCA:
		mov	al, [bp+arg_10]
		mov	ah, 0
		cmp	ax, si
		jg	short loc_21BAE
		jmp	short loc_21C0A
; ---------------------------------------------------------------------------

loc_21BD5:
		les	bx, [bp+arg_0]
		mov	ax, es:[bx]
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_21C0A
		call	sub_232D3
		jmp	short loc_21C0A
; ---------------------------------------------------------------------------

loc_21BEC:
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 28h ;	'('
		jle	short loc_21C0A
		call	sub_232D3
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 0
		les	bx, [bp+arg_4]
		mov	word ptr es:[bx], 0

loc_21C0A:
		pop	si
		pop	bp
		retf
sub_21A8A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

; int __cdecl __far sub_21C0D(__int32, int, int, double, double, char)
sub_21C0D	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= qword	ptr  0Eh
arg_10		= qword	ptr  16h
arg_18		= byte ptr  1Eh

		push	bp
		mov	bp, sp
		push	si
		xor	si, si
		jmp	loc_21C99
; ---------------------------------------------------------------------------

loc_21C16:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+2EFh], 0
		jnz	short loc_21C98
		mov	ax, [bp+arg_4]
		shl	ax, 4
		mov	dx, si
		add	dx, dx
		les	bx, [bp+arg_0]
		add	bx, dx
		mov	es:[bx], ax
		mov	ax, [bp+arg_6]
		shl	ax, 4
		mov	es:[bx+64h], ax
		mov	word ptr es:[bx+0C8h], 0FFFFh
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 00eh
		; Hack (fmul flt_35C9E)
		db 0cdh
		db 034h
		db 00eh
		db 0feh
		db 012h
		call	sub_2395
		mov	dx, si
		add	dx, dx
		les	bx, [bp+arg_0]
		add	bx, dx
		mov	es:[bx+190h], ax
		; Hack (fld [bp+arg_10])
		db 0cdh
		db 039h
		db 046h
		db 016h
		; Hack (fmul flt_35C9E)
		db 0cdh
		db 034h
		db 00eh
		db 0feh
		db 012h
		call	sub_2395
		mov	dx, si
		add	dx, dx
		les	bx, [bp+arg_0]
		add	bx, dx
		mov	es:[bx+1F4h], ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	al, [bp+arg_18]
		mov	es:[bx+2BCh], al
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+2EFh], 1
		jmp	short loc_21CA0
; ---------------------------------------------------------------------------

loc_21C98:
		inc	si

loc_21C99:
		cmp	si, 32h	; '2'
		jl	loc_21C16

loc_21CA0:
		pop	si
		pop	bp
		retf
sub_21C0D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21CA3	proc far

var_A		= word ptr -0Ah
var_8		= qword	ptr -8
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= dword	ptr  0Ch
arg_A		= dword	ptr  10h

		enter	0Ah, 0
		push	si
		mov	si, [bp+arg_4]
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		push	word ptr es:[bx+1F4h]
		push	word ptr es:[bx+190h]
		call	iatan2
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		; Hack (fstp [bp+var_8])
		db 0cdh
		db 039h
		db 05eh
		db 0f8h
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CA2)
		db 0cdh
		db 034h
		db 01eh
		db 002h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21CE7
		xor	ax, ax
		jmp	short loc_21D37
; ---------------------------------------------------------------------------

loc_21CE7:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CA6)
		db 0cdh
		db 034h
		db 01eh
		db 006h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21D01
		mov	ax, 1
		jmp	short loc_21D37
; ---------------------------------------------------------------------------

loc_21D01:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CAA)
		db 0cdh
		db 034h
		db 01eh
		db 00ah
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21D1B
		mov	ax, 2
		jmp	short loc_21D37
; ---------------------------------------------------------------------------

loc_21D1B:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CAE)
		db 0cdh
		db 034h
		db 01eh
		db 00eh
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21D35
		mov	ax, 3
		jmp	short loc_21D37
; ---------------------------------------------------------------------------

loc_21D35:
		xor	ax, ax

loc_21D37:
		les	bx, [bp+arg_6]
		mov	es:[bx], ax
		les	bx, [bp+arg_0]
		mov	al, es:[bx+2EEh]
		mov	ah, 0
		les	bx, [bp+arg_6]
		add	es:[bx], ax
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35C9E)
		db 0cdh
		db 034h
		db 01eh
		db 0feh
		db 012h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21D67
		xor	ax, ax
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21D67:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CB2)
		db 0cdh
		db 034h
		db 01eh
		db 012h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21D82
		mov	ax, 1
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21D82:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CB6)
		db 0cdh
		db 034h
		db 01eh
		db 016h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21D9D
		mov	ax, 2
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21D9D:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CA2)
		db 0cdh
		db 034h
		db 01eh
		db 002h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21DB8
		mov	ax, 3
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21DB8:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CBA)
		db 0cdh
		db 034h
		db 01eh
		db 01ah
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21DD2
		xor	ax, ax
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21DD2:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CBE)
		db 0cdh
		db 034h
		db 01eh
		db 01eh
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21DED
		mov	ax, 1
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21DED:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CC2)
		db 0cdh
		db 034h
		db 01eh
		db 022h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21E08
		mov	ax, 2
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21E08:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CA6)
		db 0cdh
		db 034h
		db 01eh
		db 006h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21E23
		mov	ax, 3
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21E23:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CC6)
		db 0cdh
		db 034h
		db 01eh
		db 026h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21E3D
		xor	ax, ax
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21E3D:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CCA)
		db 0cdh
		db 034h
		db 01eh
		db 02ah
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21E58
		mov	ax, 1
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21E58:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CCE)
		db 0cdh
		db 034h
		db 01eh
		db 02eh
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21E73
		mov	ax, 2
		jmp	loc_21EF6
; ---------------------------------------------------------------------------

loc_21E73:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CAA)
		db 0cdh
		db 034h
		db 01eh
		db 00ah
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21E8D
		mov	ax, 3
		jmp	short loc_21EF6
; ---------------------------------------------------------------------------

loc_21E8D:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CD2)
		db 0cdh
		db 034h
		db 01eh
		db 032h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21EA6
		xor	ax, ax
		jmp	short loc_21EF6
; ---------------------------------------------------------------------------

loc_21EA6:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CD6)
		db 0cdh
		db 034h
		db 01eh
		db 036h
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21EC0
		mov	ax, 1
		jmp	short loc_21EF6
; ---------------------------------------------------------------------------

loc_21EC0:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CDA)
		db 0cdh
		db 034h
		db 01eh
		db 03ah
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21EDA
		mov	ax, 2
		jmp	short loc_21EF6
; ---------------------------------------------------------------------------

loc_21EDA:
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35CAE)
		db 0cdh
		db 034h
		db 01eh
		db 00eh
		db 013h
		; Hack (fnstsw [bp+var_A])
		db 0cdh
		db 039h
		db 07eh
		db 0f6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_A]
		sahf
		jnb	short loc_21EF4
		mov	ax, 3
		jmp	short loc_21EF6
; ---------------------------------------------------------------------------

loc_21EF4:
		xor	ax, ax

loc_21EF6:
		les	bx, [bp+arg_A]
		mov	es:[bx], ax
		pop	si
		leave
		retf
sub_21CA3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21EFF	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		xor	ax, ax
		jmp	short loc_21F12
; ---------------------------------------------------------------------------

loc_21F06:
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	byte ptr es:[bx+2EFh], 0
		inc	ax

loc_21F12:
		cmp	ax, 32h	; '2'
		jl	short loc_21F06
		pop	bp
		retf
sub_21EFF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_21F19	proc far

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= dword	ptr  6

		enter	4, 0
		push	si
		xor	si, si
		jmp	loc_220EA
; ---------------------------------------------------------------------------

loc_21F23:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+2EFh], 0
		jz	loc_220E9
		mov	ax, si
		mov	bx, 2
		cwd
		idiv	bx
		movsx	eax, dx
		mov	edx, dword_36C16
		and	edx, 1
		cmp	eax, edx
		jnz	short loc_21F7D
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		cmp	word ptr es:[bx+0C8h], 0FFFFh
		jz	short loc_21F7D
		push	large 100020h
		mov	ax, es:[bx+12Ch]
		sar	ax, 4
		push	ax
		mov	ax, es:[bx+0C8h]
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8

loc_21F7D:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+2EFh], 1
		jnz	loc_2207D
		mov	ax, si
		add	ax, ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx+190h]
		add	es:[bx], ax
		mov	ax, es:[bx+1F4h]
		add	es:[bx+64h], ax
		mov	ax, es:[bx]
		sar	ax, 4
		or	ax, ax
		jl	short loc_21FD5
		mov	ax, es:[bx]
		sar	ax, 4
		cmp	ax, 270h
		jg	short loc_21FD5
		mov	ax, es:[bx+64h]
		sar	ax, 4
		cmp	ax, 40h	; '@'
		jl	short loc_21FD5
		mov	ax, es:[bx+64h]
		sar	ax, 4
		cmp	ax, 18Fh
		jle	loc_220E9

loc_21FD5:
		les	bx, [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+2EFh], 2
		push	large 100020h
		mov	ax, si
		add	ax, ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx+12Ch]
		sar	ax, 4
		push	ax
		mov	ax, es:[bx+0C8h]
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx]
		sar	ax, 4
		or	ax, ax
		jge	short loc_22025
		mov	word ptr es:[bx+0C8h], 0
		jmp	short loc_22040
; ---------------------------------------------------------------------------

loc_22025:
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx]
		sar	ax, 4
		cmp	ax, 270h
		jle	short loc_22040
		mov	word ptr es:[bx+0C8h], 2700h

loc_22040:
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx+64h]
		sar	ax, 4
		cmp	ax, 40h	; '@'
		jge	short loc_2205F
		mov	word ptr es:[bx+12Ch], 400h
		jmp	loc_220E9
; ---------------------------------------------------------------------------

loc_2205F:
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx+64h]
		sar	ax, 4
		cmp	ax, 18Fh
		jle	short loc_220E9
		mov	word ptr es:[bx+12Ch], 1880h
		jmp	short loc_220E9
; ---------------------------------------------------------------------------

loc_2207D:
		mov	ax, si
		mov	bx, 2
		cwd
		idiv	bx
		movsx	eax, dx
		mov	edx, dword_36C16
		and	edx, 1
		cmp	eax, edx
		jnz	short loc_220A1
		les	bx, [bp+arg_0]
		add	bx, si
		inc	byte ptr es:[bx+2EFh]

loc_220A1:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+2EFh], 3
		jbe	short loc_220E9
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+2EFh], 0
		push	large 100020h
		mov	ax, si
		add	ax, ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx+12Ch]
		sar	ax, 4
		push	ax
		mov	ax, es:[bx+0C8h]
		sar	ax, 4
		push	ax
		call	sub_10433
		push	7
		call	sub_125C9
		add	sp, 0Ah

loc_220E9:
		inc	si

loc_220EA:
		cmp	si, 32h	; '2'
		jl	loc_21F23
		xor	si, si
		jmp	loc_221C2
; ---------------------------------------------------------------------------

loc_220F6:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+2EFh], 0
		jz	loc_221C1
		mov	ax, si
		mov	bx, 2
		cwd
		idiv	bx
		movsx	eax, dx
		mov	edx, dword_36C16
		and	edx, 1
		cmp	eax, edx
		jnz	loc_221C1
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+2EFh], 1
		jnz	short loc_22183
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	si
		push	large [bp+arg_0]
		push	cs
		call	near ptr sub_21CA3
		push	[bp+var_4]
		push	[bp+var_2]
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx+64h]
		sar	ax, 4
		push	ax
		mov	ax, es:[bx]
		sar	ax, 4
		push	ax
		call	sub_19BC3
		add	sp, 16h
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx]
		mov	es:[bx+0C8h], ax
		mov	ax, es:[bx+64h]
		mov	es:[bx+12Ch], ax
		jmp	short loc_221C1
; ---------------------------------------------------------------------------

loc_22183:
		les	bx, [bp+arg_0]
		add	bx, si
		mov	al, es:[bx+2EFh]
		mov	ah, 0
		add	ax, 0FFFEh
		push	ax
		mov	bx, word ptr [bp+arg_0]
		mov	al, es:[bx+2EEh]
		mov	ah, 0
		add	ax, 4
		push	ax
		mov	ax, si
		add	ax, ax
		add	bx, ax
		mov	ax, es:[bx+12Ch]
		sar	ax, 4
		push	ax
		mov	ax, es:[bx+0C8h]
		sar	ax, 4
		push	ax
		call	sub_19BC3
		add	sp, 8

loc_221C1:
		inc	si

loc_221C2:
		cmp	si, 32h	; '2'
		jl	loc_220F6
		cmp	word_34A78, 0
		jnz	short loc_22231
		xor	si, si
		jmp	short loc_2222C
; ---------------------------------------------------------------------------

loc_221D4:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+2EFh], 0
		jz	short loc_2222B
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx]
		sar	ax, 4
		mov	dx, word_36C26
		add	dx, 0FFF8h
		cmp	ax, dx
		jle	short loc_2222B
		mov	ax, es:[bx]
		sar	ax, 4
		mov	dx, word_36C26
		add	dx, 18h
		cmp	ax, dx
		jge	short loc_2222B
		mov	ax, es:[bx+64h]
		sar	ax, 4
		cmp	ax, 190h
		jge	short loc_2222B
		mov	ax, es:[bx+64h]
		sar	ax, 4
		cmp	ax, 168h
		jle	short loc_2222B
		mov	byte_34A4F, 1
		jmp	short loc_22231
; ---------------------------------------------------------------------------

loc_2222B:
		inc	si

loc_2222C:
		cmp	si, 32h	; '2'
		jl	short loc_221D4

loc_22231:
		pop	si
		leave
		retf
sub_21F19	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22234	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		cmp	word_34A80, 0
		jnz	short loc_22260
		cmp	byte_34A58, 1
		jnz	short loc_22260
		mov	eax, [bp+arg_0]
		mov	ebx, 32h ; '2'
		xor	edx, edx
		div	ebx
		cmp	edx, 0
		jnz	short loc_22260
		mov	ax, 1
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_22260:
		xor	ax, ax
		pop	bp
		retf
sub_22234	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22264	proc far

var_1		= byte ptr -1
arg_0		= word ptr  6
arg_2		= word ptr  8

		enter	2, 0
		push	si
		mov	si, [bp+arg_0]
		cmp	si, 0FFh
		jnz	short loc_2229C
		mov	[bp+var_1], 0
		jmp	short loc_22287
; ---------------------------------------------------------------------------

loc_22278:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	byte ptr [bx+598Dh], 0
		inc	[bp+var_1]

loc_22287:
		cmp	[bp+var_1], 28h	; '('
		jb	short loc_22278
		mov	word_3A1E9, 2
		mov	word_3A1EB, 0Ah
		jmp	loc_22661
; ---------------------------------------------------------------------------

loc_2229C:
		inc	byte_3A37D
		mov	al, byte_3A37D
		mov	ah, 0
		mov	dx, word_3A1E9
		imul	dx, 28h
		cmp	ax, dx
		jle	short loc_222B5
		mov	byte_3A37D, 0

loc_222B5:
		mov	al, byte_3A37D
		mov	ah, 0
		cwd
		idiv	word_3A1E9
		or	dx, dx
		jnz	loc_22538
		mov	al, byte_3A37D
		mov	ah, 0
		cwd
		idiv	word_3A1E9
		mov	[bp+var_1], al
		mov	ah, 0
		mov	bx, ax
		cmp	byte ptr [bx+598Dh], 0
		jnz	loc_22538
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	byte ptr [bx+598Dh], 1
		call	IRand
		cwd
		idiv	word_3A1EB
		inc	dl
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	[bx+59B5h], dl
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_22398
		mov	bx, si
		cmp	bx, 7
		ja	loc_22416
		add	bx, bx
		jmp	cs:off_22684[bx]

loc_22323:
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		shl	dx, 4
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	[bx+584Dh], dx
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	word ptr [bx+589Dh], 0
		jmp	loc_22416
; ---------------------------------------------------------------------------

loc_22350:
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		shl	dx, 4
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	[bx+584Dh], dx
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	word ptr [bx+589Dh], 18F0h
		jmp	loc_22416
; ---------------------------------------------------------------------------

loc_2237D:
		cmp	si, 2
		jnz	short loc_22387
		mov	ax, 27F0h
		jmp	short loc_22389
; ---------------------------------------------------------------------------

loc_22387:
		xor	ax, ax

loc_22389:
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+584Dh], ax
		jmp	short loc_223C6
; ---------------------------------------------------------------------------

loc_22398:
		mov	bx, si
		cmp	bx, 7
		ja	short loc_22416
		add	bx, bx
		jmp	cs:off_22674[bx]

loc_223A6:
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	word ptr [bx+584Dh], 27F0h
		jmp	short loc_223C6
; ---------------------------------------------------------------------------

loc_223B7:
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	word ptr [bx+584Dh], 0

loc_223C6:
		call	IRand
		mov	bx, 190h
		cwd
		idiv	bx
		shl	dx, 4
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	[bx+589Dh], dx
		jmp	short loc_22416
; ---------------------------------------------------------------------------

loc_223E3:
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		shl	dx, 4
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	[bx+584Dh], dx
		or	si, si
		jnz	short loc_22406
		xor	ax, ax
		jmp	short loc_22409
; ---------------------------------------------------------------------------

loc_22406:
		mov	ax, 18F0h

loc_22409:
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+589Dh], ax

loc_22416:
		mov	bx, si
		cmp	bx, 7
		ja	loc_22538
		add	bx, bx
		jmp	cs:off_22664[bx]

loc_22426:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		jmp	loc_224BB
; ---------------------------------------------------------------------------

loc_22436:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		imul	ax, 0Dh
		neg	ax
		jmp	loc_2250E
; ---------------------------------------------------------------------------

loc_2244B:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		neg	ax

loc_2245A:
		shl	ax, 4
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+58EDh], ax
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	word ptr [bx+593Dh], 0
		jmp	loc_22538
; ---------------------------------------------------------------------------

loc_2247C:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		imul	ax, 0Dh
		neg	ax

loc_2248E:
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+58EDh], ax
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		neg	ax
		jmp	short loc_22528
; ---------------------------------------------------------------------------

loc_224AC:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		neg	ax

loc_224BB:
		shl	ax, 4
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+593Dh], ax
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	word ptr [bx+58EDh], 0
		jmp	short loc_22538
; ---------------------------------------------------------------------------

loc_224DC:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		imul	ax, 0Dh
		jmp	short loc_2248E
; ---------------------------------------------------------------------------

loc_224EE:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		jmp	loc_2245A
; ---------------------------------------------------------------------------

loc_224FE:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0
		imul	ax, 0Dh

loc_2250E:
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+58EDh], ax
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	al, [bx+59B5h]
		mov	ah, 0

loc_22528:
		shl	ax, 3
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		mov	[bx+593Dh], ax

loc_22538:
		mov	[bp+var_1], 0
		jmp	loc_22604
; ---------------------------------------------------------------------------

loc_2253F:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		cmp	byte ptr [bx+598Dh], 0
		jz	loc_22601
		push	large 10008h
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+589Dh]
		sar	ax, 4
		push	ax
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+584Dh]
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+58EDh]
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		add	[bx+584Dh], ax
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+593Dh]
		mov	dl, [bp+var_1]
		mov	dh, 0
		add	dx, dx
		mov	bx, dx
		add	[bx+589Dh], ax
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		cmp	word ptr [bx+584Dh], 0
		jl	short loc_225F5
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		cmp	word ptr [bx+589Dh], 18F0h
		jg	short loc_225F5
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		cmp	word ptr [bx+584Dh], 27F0h
		jg	short loc_225F5
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		cmp	word ptr [bx+589Dh], 0
		jge	short loc_22601

loc_225F5:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		mov	byte ptr [bx+598Dh], 0

loc_22601:
		inc	[bp+var_1]

loc_22604:
		cmp	[bp+var_1], 28h	; '('
		jb	loc_2253F
		push	0C0h ; '?'
		push	[bp+arg_2]
		call	grcg_setcolor
		mov	[bp+var_1], 0
		jmp	short loc_22655
; ---------------------------------------------------------------------------

loc_2261D:
		mov	al, [bp+var_1]
		mov	ah, 0
		mov	bx, ax
		cmp	byte ptr [bx+598Dh], 0
		jz	short loc_22652
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+584Dh]
		sar	ax, 4
		push	ax
		mov	al, [bp+var_1]
		mov	ah, 0
		add	ax, ax
		mov	bx, ax
		mov	ax, [bx+589Dh]
		sar	ax, 4
		push	ax
		call	grcg_pset

loc_22652:
		inc	[bp+var_1]

loc_22655:
		cmp	[bp+var_1], 28h	; '('
		jb	short loc_2261D
		mov	dx, 7Ch	; '|'
		mov	al, 0
		out	dx, al

loc_22661:
		pop	si
		leave
		retf
sub_22264	endp

; ---------------------------------------------------------------------------
off_22664	dw offset loc_22426
		dw offset loc_22436
		dw offset loc_2244B
		dw offset loc_2247C
		dw offset loc_224AC
		dw offset loc_224DC
		dw offset loc_224EE
		dw offset loc_224FE
off_22674	dw offset loc_223E3
		dw offset loc_223A6
		dw offset loc_223A6
		dw offset loc_223A6
		dw offset loc_223E3
		dw offset loc_223B7
		dw offset loc_223B7
		dw offset loc_223B7
off_22684	dw offset loc_22323
		dw offset loc_22323
		dw offset loc_2237D
		dw offset loc_22350
		dw offset loc_22350
		dw offset loc_22350
seg032		ends

; ===========================================================================

; Segment type:	Pure code
seg033		segment	byte public 'CODE' use16
		assume cs:seg033
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing
		db 0FDh, 0Ah, 0A3h, 0Ah

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22694	proc far
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	word_39854, 1
		push	0
		push	ds
		push	offset aBoss1_bos ; "boss1.bos"
		push	ds
		push	offset dword_3982A
		call	sub_1568F
		mov	word_39854, 0
		mov	word_39886, 1
		push	1
		push	ds
		push	offset aBoss1_2_bos ; "boss1_2.bos"
		push	ds
		push	offset dword_3985C
		call	sub_1568F
		mov	word_39886, 0
		mov	word_398B8, 1
		push	2
		push	ds
		push	offset aBoss1_3_bos ; "boss1_3.bos"
		push	ds
		push	offset dword_3988E
		call	sub_1568F
		mov	word_398B8, 0
		push	ds
		push	offset aBoss1_grp_0 ; "boss1.grp"
		call	sub_10AA5
		add	sp, 22h
		xor	si, si
		jmp	short loc_22717
; ---------------------------------------------------------------------------

loc_226FA:
		xor	di, di
		jmp	short loc_22711
; ---------------------------------------------------------------------------

loc_226FE:
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+di+6F0h]
		mov	bx, si
		imul	bx, 3
		mov	[bx+di+5414h], al
		inc	di

loc_22711:
		cmp	di, 3
		jl	short loc_226FE
		inc	si

loc_22717:
		cmp	si, 10h
		jl	short loc_226FA
		push	ds
		push	offset unk_39DB4
		call	sub_C433
		add	sp, 4
		nop
		push	cs
		call	near ptr sub_22731
		pop	di
		pop	si
		pop	bp
		retf
sub_22694	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22731	proc far
		push	bp
		mov	bp, sp
		call	sub_232A4
		push	ds
		push	offset unk_35090
		call	sub_EB10
		push	large 1300040h
		push	large 2E00000h
		push	large 200040h
		push	280h
		push	ds
		push	offset dword_3982A
		call	sub_166D2
		mov	word_3983E, 18h
		mov	word_39840, 48h	; 'H'
		mov	word_39842, 18h
		mov	word_39844, 48h	; 'H'
		mov	word_39852, 0
		mov	word_3984E, 0
		mov	word_3A383, 8
		mov	word_3A1E5, 6
		mov	word_3A1E7, 2
		mov	byte_35CDE, 0
		push	large 700FFh
		call	sub_22264
		add	sp, 1Ah
		pop	bp
		retf
sub_22731	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_227AB	proc far
		push	bp
		mov	bp, sp
		push	0
		call	sub_169CB
		push	1
		call	sub_169CB
		push	2
		call	sub_169CB
		add	sp, 6
		pop	bp
		retf
sub_227AB	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_227C8	proc far

var_4		= word ptr -4
var_1		= byte ptr -1
arg_0		= word ptr  6
arg_2		= byte ptr  8

		enter	4, 0
		mov	ax, word_3A37F
		cwd
		idiv	[bp+arg_0]
		or	dx, dx
		jnz	short locret_22818
		mov	ax, word_3984E
		add	al, [bp+arg_2]
		mov	[bp+var_1], al
		cbw
		cmp	ax, 7
		jle	short loc_227EC
		mov	[bp+var_1], 0
		jmp	short loc_227F8
; ---------------------------------------------------------------------------

loc_227EC:
		mov	al, [bp+var_1]
		cbw
		or	ax, ax
		jge	short loc_227F8
		mov	[bp+var_1], 7

loc_227F8:
		mov	al, [bp+var_1]
		cbw
		mov	[bp+var_4], ax
		mov	word_3984E, ax
		mov	al, [bp+var_1]
		cbw
		push	ax
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_15F4A
		add	sp, 0Ah

locret_22818:
		leave
		retf
sub_227C8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2281A	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h

		push	bp
		mov	bp, sp
		mov	dx, [bp+arg_6]
		cmp	byte_34A30, 0
		jnz	short loc_2282C
		mov	ax, [bp+arg_4]
		jmp	short loc_22857
; ---------------------------------------------------------------------------

loc_2282C:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_22839
		mov	ax, dx
		jmp	short loc_22857
; ---------------------------------------------------------------------------

loc_22839:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_22847
		mov	ax, [bp+arg_8]
		jmp	short loc_22857
; ---------------------------------------------------------------------------

loc_22847:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_22855
		mov	ax, [bp+arg_A]
		jmp	short loc_22857
; ---------------------------------------------------------------------------

loc_22855:
		mov	ax, dx

loc_22857:
		les	bx, [bp+arg_0]
		mov	es:[bx], ax
		pop	bp
		retf
sub_2281A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2285F	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		cmp	word_3A37F, 32h	; '2'
		jge	short loc_22895
		mov	word_3984E, 0
		mov	ax, word_3A37F
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2290A
		push	word_3984E
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_15F4A
		add	sp, 0Ah
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_22895:
		cmp	word_3A37F, 32h	; '2'
		jnz	short loc_228A4
		push	8
		call	sub_125C9
		pop	cx

loc_228A4:
		cmp	word_3A37F, 64h	; 'd'
		jge	short loc_2290A
		mov	ax, word_3A37F
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2290A
		push	word_3984E
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_15F4A
		add	sp, 0Ah
		cmp	word_3A37F, 32h	; '2'
		jz	short loc_228FE
		cmp	word_3A37F, 3Ch	; '<'
		jz	short loc_228FE
		cmp	word_3A37F, 44h	; 'D'
		jz	short loc_228FE
		cmp	word_3A37F, 4Ah	; 'J'
		jz	short loc_228FE
		cmp	word_3A37F, 4Eh	; 'N'
		jz	short loc_228FE
		cmp	word_3A37F, 52h	; 'R'
		jz	short loc_228FE
		cmp	word_3A37F, 52h	; 'R'
		jle	short loc_2290A

loc_228FE:
		push	[bp+arg_0]
		push	1
		push	cs
		call	near ptr sub_227C8
		add	sp, 4

loc_2290A:
		pop	bp
		retf
sub_2285F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2290C	proc far

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		enter	4, 0
		push	si
		push	di
		mov	di, [bp+arg_0]
		mov	si, [bp+arg_2]
		or	si, si
		jge	short loc_2292E
		mov	ax, si
		neg	ax
		push	ax
		push	60h ; '`'
		mov	ax, word ptr dword_3982A+2
		add	ax, si
		add	ax, 60h	; '`'
		push	ax
		jmp	short loc_22939
; ---------------------------------------------------------------------------

loc_2292E:
		or	si, si
		jle	short loc_22945
		push	si
		push	60h ; '`'
		push	word ptr dword_3982A+2

loc_22939:
		push	word ptr dword_3982A
		call	sub_10433
		add	sp, 8

loc_22945:
		or	di, di
		jle	short loc_22956
		push	large 600008h
		push	large [dword_3982A]
		jmp	short loc_2296D
; ---------------------------------------------------------------------------

loc_22956:
		or	di, di
		jge	short loc_22975
		push	large 600008h
		push	word ptr dword_3982A+2
		mov	ax, word ptr dword_3982A
		add	ax, 60h	; '`'
		sub	ax, si
		push	ax

loc_2296D:
		call	sub_10433
		add	sp, 8

loc_22975:
		mov	ax, word ptr dword_3982A+2
		add	ax, si
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A
		add	ax, di
		jge	short loc_22988
		xor	ax, ax
		jmp	short loc_2298D
; ---------------------------------------------------------------------------

loc_22988:
		mov	ax, word ptr dword_3982A
		add	ax, di

loc_2298D:
		cmp	ax, 220h
		jle	short loc_22997
		mov	ax, 220h
		jmp	short loc_229A7
; ---------------------------------------------------------------------------

loc_22997:
		mov	ax, word ptr dword_3982A
		add	ax, di
		jge	short loc_229A2
		xor	ax, ax
		jmp	short loc_229A7
; ---------------------------------------------------------------------------

loc_229A2:
		mov	ax, word ptr dword_3982A
		add	ax, di

loc_229A7:
		mov	[bp+var_4], ax
		mov	word ptr dword_3982A, ax
		mov	ax, [bp+var_2]
		mov	word ptr dword_3982A+2,	ax
		mov	ax, word_3A37F
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_229CD
		push	[bp+arg_6]
		push	[bp+arg_4]
		push	cs
		call	near ptr sub_227C8
		add	sp, 4

loc_229CD:
		pop	di
		pop	si
		leave
		retf
sub_2290C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_229D1	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A37F, 0Ah
		jnz	short loc_229F4
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_229EF
		mov	al, 1
		jmp	short loc_229F1
; ---------------------------------------------------------------------------

loc_229EF:
		mov	al, 0FFh

loc_229F1:
		mov	byte ptr word_3A387+1, al

loc_229F4:
		cmp	word_3A37F, 64h	; 'd'
		jge	short loc_22A07
		mov	al, byte ptr word_3A387+1
		cbw
		push	ax
		push	cs
		call	near ptr sub_2285F
		pop	cx
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_22A07:
		cmp	word_3A37F, 64h	; 'd'
		jnz	short loc_22A37
		push	large 1E0014h
		push	large 0F000Ah
		push	ds
		push	offset word_3A385
		push	cs
		call	near ptr sub_2281A
		add	sp, 0Ch
		mov	al, byte ptr word_3A387+1
		cbw
		cmp	ax, 0FFFFh
		jnz	short loc_22A32
		mov	al, 0
		jmp	short loc_22A34
; ---------------------------------------------------------------------------

loc_22A32:
		mov	al, 80h	; '?'

loc_22A34:
		mov	byte ptr word_3A387, al

loc_22A37:
		cmp	word_3A37F, 0A0h ; '?'
		jge	short loc_22A9F
		push	1
		mov	al, byte ptr word_3A387+1
		cbw
		push	ax
		push	cs
		call	near ptr sub_227C8
		add	sp, 4
		mov	ax, 3Ch	; '<'
		cwd
		idiv	word_3A385
		push	ax
		mov	ax, word_3A37F
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_22AA5
		push	large 0
		push	large 0
		push	32h ; '2'
		push	word_3A387
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 2Ch	; ','
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		mov	al, byte ptr word_3A387+1
		cbw
		shl	ax, 7
		cwd
		idiv	word_3A385
		mov	dl, byte ptr word_3A387
		sub	dl, al
		mov	byte ptr word_3A387, dl
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_22A9F:
		mov	word_3A37F, 0

loc_22AA5:
		pop	bp
		retf
sub_229D1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22AA7	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A37F, 64h	; 'd'
		jge	short loc_22ABA
		push	1
		push	cs
		call	near ptr sub_2285F
		pop	cx
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_22ABA:
		cmp	word_3A37F, 64h	; 'd'
		jnz	short loc_22AFE
		push	large 60005h
		push	large 40004h
		push	ds
		push	offset word_3A385
		push	cs
		call	near ptr sub_2281A
		push	word_3A385
		push	ds
		push	offset word_3A38B
		push	ds
		push	offset word_3A389
		push	170h
		push	word_36C26
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		push	ax
		call	sub_11FF0
		add	sp, 1Eh

loc_22AFE:
		cmp	word_3A389, 3E7h
		jz	short loc_22B31
		push	large 10001h
		push	word_3A38B
		push	word_3A389
		push	cs
		call	near ptr sub_2290C
		add	sp, 8
		cmp	word ptr dword_3982A+2,	130h
		jle	short loc_22B60
		mov	word_3A389, 3E7h
		mov	word_3A38B, 0FFFCh
		jmp	short loc_22B60
; ---------------------------------------------------------------------------

loc_22B31:
		cmp	word_3A38B, 0FFFCh
		jnz	short loc_22B5A
		push	large 10001h
		push	word_3A38B
		push	0
		push	cs
		call	near ptr sub_2290C
		add	sp, 8
		cmp	word ptr dword_3982A+2,	60h ; '`'
		jge	short loc_22B60
		mov	word_3A38B, 0
		jmp	short loc_22B60
; ---------------------------------------------------------------------------

loc_22B5A:
		mov	word_3A37F, 0

loc_22B60:
		cmp	word_34A78, 0
		jnz	short loc_22B86
		mov	ax, word ptr dword_3982A
		cmp	ax, word_36C26
		jg	short loc_22B86
		add	ax, 40h	; '@'
		cmp	ax, word_36C26
		jl	short loc_22B86
		cmp	word ptr dword_3982A+2,	110h
		jl	short loc_22B86
		mov	byte_34A4F, 1

loc_22B86:
		pop	bp
		retf
sub_22AA7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22B88	proc far

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6
arg_2		= dword	ptr  8
arg_6		= dword	ptr  0Ch
arg_A		= dword	ptr  10h

		enter	6, 0
		push	si
		mov	si, [bp+arg_0]
		cmp	word_3A37F, 64h	; 'd'
		jge	short loc_22BA1
		push	1
		push	cs
		call	near ptr sub_2285F
		pop	cx
		jmp	loc_22CF3
; ---------------------------------------------------------------------------

loc_22BA1:
		cmp	word_3A37F, 64h	; 'd'
		jz	loc_22C9C
		cmp	word_3A37F, 69h	; 'i'
		jz	loc_22C7D
		cmp	word_3A37F, 6Eh	; 'n'
		jz	loc_22C7D
		cmp	word_3A37F, 73h	; 's'
		jnz	short loc_22BD5
		mov	ax, si
		imul	ax, 3
		push	ax
		push	large [dword_3982A]
		push	ds
		push	offset dword_3988E
		jmp	loc_22C8A
; ---------------------------------------------------------------------------

loc_22BD5:
		cmp	word_3A37F, 87h	; '�
		jnz	short loc_22C07
		mov	ax, si
		imul	ax, 3
		inc	ax
		mov	[bp+var_2], ax
		mov	word_398B2, ax
		mov	ax, si
		imul	ax, 3
		inc	ax
		push	ax
		push	large [dword_3982A]
		push	ds
		push	offset dword_3988E
		call	sub_15F4A
		add	sp, 0Ah
		call	[bp+arg_2]
		jmp	loc_22CC1
; ---------------------------------------------------------------------------

loc_22C07:
		cmp	word_3A37F, 0A0h ; '?'
		jnz	short loc_22C3E
		mov	ax, si
		imul	ax, 3
		add	ax, 2
		mov	[bp+var_4], ax
		mov	word_398B2, ax
		or	si, si
		jnz	short loc_22C25
		push	2
		jmp	short loc_22C27
; ---------------------------------------------------------------------------

loc_22C25:
		push	4

loc_22C27:
		push	large [dword_3982A]
		push	ds
		push	offset dword_3988E
		call	sub_15F4A
		add	sp, 0Ah
		call	[bp+arg_6]
		jmp	loc_22CC1
; ---------------------------------------------------------------------------

loc_22C3E:
		cmp	word_3A37F, 0B9h ; '?'
		jnz	short loc_22C6D
		mov	ax, si
		imul	ax, 3
		mov	[bp+var_6], ax
		mov	word_398B2, ax
		mov	ax, si
		imul	ax, 3
		push	ax
		push	large [dword_3982A]
		push	ds
		push	offset dword_3988E
		call	sub_15F4A
		add	sp, 0Ah
		call	[bp+arg_A]
		jmp	short loc_22CC1
; ---------------------------------------------------------------------------

loc_22C6D:
		cmp	word_3A37F, 0F0h ; '�
		jz	short loc_22C7D
		cmp	word_3A37F, 0F5h ; '�
		jnz	short loc_22C94

loc_22C7D:
		lea	ax, [si+1]
		push	ax

loc_22C81:
		push	large [dword_3982A]
		push	ds
		push	offset dword_3985C

loc_22C8A:
		call	sub_15F4A
		add	sp, 0Ah
		jmp	short loc_22CC1
; ---------------------------------------------------------------------------

loc_22C94:
		cmp	word_3A37F, 0FAh ; '�
		jnz	short loc_22CA0

loc_22C9C:
		push	0
		jmp	short loc_22C81
; ---------------------------------------------------------------------------

loc_22CA0:
		cmp	word_3A37F, 104h
		jnz	short loc_22CC1
		push	0
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_15F4A
		add	sp, 0Ah
		mov	word_3A37F, 0

loc_22CC1:
		cmp	word_3A37F, 87h	; '�
		jle	short loc_22CF3
		cmp	word_3A37F, 0F0h ; '�
		jge	short loc_22CF3
		mov	ax, word_3A37F
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_22CF3
		push	word_398B2
		push	large [dword_3982A]
		push	ds
		push	offset dword_3988E
		call	sub_15F4A
		add	sp, 0Ah

loc_22CF3:
		pop	si
		leave
		retf
sub_22B88	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22CF6	proc far

var_2		= word ptr -2

		enter	2, 0
		push	large 41003Eh
		push	large 3A0037h
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	cs
		call	near ptr sub_2281A
		push	large 0
		push	[bp+var_2]
		push	large 60010h
		push	0F0h ; '�
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 2Ch	; ','
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 20h
		push	large 0
		push	[bp+var_2]
		push	large 60010h
		push	90h ; '�
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 2Ch	; ','
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		leave
		retf
sub_22CF6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22D63	proc far

var_2		= word ptr -2

		enter	2, 0
		push	large 50004Bh
		push	large 46003Ch
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	cs
		call	near ptr sub_2281A
		push	large 0
		push	large 0
		push	[bp+var_2]
		push	30h ; '0'
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 20h
		push	large 0
		push	large 0
		push	[bp+var_2]
		push	50h ; 'P'
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 54h	; 'T'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		leave
		retf
sub_22D63	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22DC8	proc far
		push	bp
		mov	bp, sp
		push	seg seg032
		push	offset sub_21884
		push	seg seg032
		push	offset sub_21884
		push	seg seg032
		push	offset sub_21884
		push	0
		push	cs
		call	near ptr sub_22B88
		add	sp, 0Eh
		cmp	word_3A37F, 8Ch	; '�
		jle	short loc_22E07
		mov	ax, word_3A37F
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_22E07
		cmp	word_3A37F, 0DCh ; '?'
		jg	short loc_22E07
		push	cs
		call	near ptr sub_22CF6

loc_22E07:
		pop	bp
		retf
sub_22DC8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22E09	proc far
		push	bp
		mov	bp, sp
		push	seg seg032
		push	offset sub_21884
		push	seg seg032
		push	offset sub_21884
		push	seg seg032
		push	offset sub_21884
		push	0
		push	cs
		call	near ptr sub_22B88
		add	sp, 0Eh
		cmp	word_3A37F, 8Ch	; '�
		jle	short loc_22E40
		mov	ax, word_3A37F
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_22E40
		push	cs
		call	near ptr sub_22D63

loc_22E40:
		pop	bp
		retf
sub_22E09	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22E42	proc far

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	large 42003Ch
		push	large 360030h
		push	ds
		push	offset word_3A385
		push	cs
		call	near ptr sub_2281A
		add	sp, 0Ch
		xor	si, si
		jmp	short loc_22E94
; ---------------------------------------------------------------------------

loc_22E62:
		call	IRand
		and	al, 7Fh
		mov	[bp+var_1], al
		push	large 0
		push	large 0
		push	word_3A385
		push	word ptr [bp+var_1]
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 2Ch	; ','
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_22E94:
		cmp	si, 0Ah
		jl	short loc_22E62
		pop	si
		leave
		retf
sub_22E42	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22E9C	proc far

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		push	large 600050h
		push	large 400030h
		push	ds
		push	offset word_3A385
		push	cs
		call	near ptr sub_2281A
		add	sp, 0Ch
		xor	si, si
		jmp	short loc_22F02
; ---------------------------------------------------------------------------

loc_22EBC:
		call	IRand
		mov	bx, 60h	; '`'
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		call	IRand
		mov	bx, 60h	; '`'
		cwd
		idiv	bx
		mov	[bp+var_4], dx
		push	large 0
		push	word_3A385
		push	large 20000h
		push	0
		mov	ax, word ptr dword_3982A+2
		add	ax, [bp+var_4]
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_22F02:
		cmp	si, 0Ah
		jl	short loc_22EBC
		pop	si
		leave
		retf
sub_22E9C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22F0A	proc far
		push	bp
		mov	bp, sp
		push	seg seg033
		push	offset sub_22E42
		push	seg seg033
		push	offset sub_22E42
		push	seg seg033
		push	offset sub_22E42
		push	1
		push	cs
		call	near ptr sub_22B88
		add	sp, 0Eh
		pop	bp
		retf
sub_22F0A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22F2A	proc far
		push	bp
		mov	bp, sp
		push	seg seg033
		push	offset sub_22E9C
		push	seg seg033
		push	offset sub_22E9C
		push	seg seg033
		push	offset sub_22E9C
		push	1
		push	cs
		call	near ptr sub_22B88
		add	sp, 0Eh
		pop	bp
		retf
sub_22F2A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_22F4A	proc far

var_2		= byte ptr -2

		enter	2, 0
		push	si
		push	di
		mov	al, byte_35CDF
		mov	[bp+var_2], al
		cmp	byte_35CDE, 0
		jnz	loc_230BA
		mov	word ptr dword_3982A, 110h
		mov	word ptr dword_3982A+2,	60h ; '`'
		push	large 0
		push	large 5
		call	sub_EB59
		push	large 0
		push	large 9
		call	sub_EB59
		push	large 0
		push	large 0Fh
		call	sub_EB59
		add	sp, 18h
		xor	si, si
		mov	di, 12h
		mov	word_3A37F, 0
		jmp	loc_2302C
; ---------------------------------------------------------------------------

loc_22F9D:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16733
		add	sp, 0Ch
		inc	word_3A37F
		mov	ax, word_3A37F
		cwd
		idiv	di
		or	dx, dx
		jnz	short loc_22FD7
		push	large 10001h
		push	cs
		call	near ptr sub_227C8
		add	sp, 4
		sub	di, 2
		or	di, di
		jg	short loc_22FD7
		mov	di, 1

loc_22FD7:
		mov	ax, word_3A37F
		mov	bx, 14h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_23024
		xor	si, si
		jmp	short loc_23013
; ---------------------------------------------------------------------------

loc_22FE8:
		mov	al, [si+6FFh]
		cmp	al, [si+51FBh]
		jge	short loc_22FF6
		inc	byte ptr [si+6FFh]

loc_22FF6:
		mov	al, [si+70Bh]
		cmp	al, [si+5207h]
		jge	short loc_23004
		inc	byte ptr [si+70Bh]

loc_23004:
		mov	al, [si+71Dh]
		cmp	al, [si+5219h]
		jge	short loc_23012
		inc	byte ptr [si+71Dh]

loc_23012:
		inc	si

loc_23013:
		cmp	si, 3
		jl	short loc_22FE8
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4

loc_23024:
		push	1
		call	sub_E364
		pop	cx

loc_2302C:
		cmp	word_3A37F, 0C8h ; '?'
		jl	loc_22F9D
		mov	byte_35CDE, 1
		mov	word_35CE0, 0
		mov	word_35CE2, 0
		mov	word_35CE4, 0
		mov	word_3A37F, 0
		mov	word_35CE6, 0
		call	sub_232D3
		push	ds
		push	offset unk_35090
		call	sub_C433
		add	sp, 4
		call	sub_232A4
		mov	word_39852, 0
		mov	word_3A381, 0
		cmp	byte_34A30, 0
		jnz	short loc_23087
		mov	ax, 46h	; 'F'
		jmp	short loc_230B4
; ---------------------------------------------------------------------------

loc_23087:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_23095
		mov	ax, 32h	; '2'
		jmp	short loc_230B4
; ---------------------------------------------------------------------------

loc_23095:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_230A3
		mov	ax, 1Eh
		jmp	short loc_230B4
; ---------------------------------------------------------------------------

loc_230A3:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_230B1
		mov	ax, 0Ah
		jmp	short loc_230B4
; ---------------------------------------------------------------------------

loc_230B1:
		mov	ax, 32h	; '2'

loc_230B4:
		mov	word_3A385, ax
		jmp	loc_232A0
; ---------------------------------------------------------------------------

loc_230BA:
		mov	al, byte_35CDE
		cbw
		cmp	ax, 1
		jnz	loc_23198
		cmp	word_35CE6, 0
		jnz	short loc_230DF
		push	word_3A381
		push	word_3A383
		call	sub_2191C
		add	sp, 4
		mov	word_35CE6, ax

loc_230DF:
		inc	word_3A37F
		inc	word_3A381
		cmp	word_35CE0, 0
		jnz	short loc_230F4
		push	cs
		call	near ptr sub_229D1
		jmp	short loc_230FF
; ---------------------------------------------------------------------------

loc_230F4:
		cmp	word_35CE0, 1
		jnz	short loc_230FF
		push	cs
		call	near ptr sub_22AA7

loc_230FF:
		cmp	word_3A37F, 0
		jnz	short loc_23118
		cmp	word_35CE0, 1
		jnz	short loc_23111
		xor	ax, ax
		jmp	short loc_23115
; ---------------------------------------------------------------------------

loc_23111:
		mov	ax, word_35CE0
		inc	ax

loc_23115:
		mov	word_35CE0, ax

loc_23118:
		push	large 300060h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 10h
		push	ax
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	0BB8h
		push	1
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A383
		push	ds
		push	offset word_35CE4
		push	ds
		push	offset word_3A381
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A383, 6
		jg	loc_232A0
		cmp	word_35CE4, 0
		jnz	loc_232A0
		cmp	word_35CE0, 1
		jz	loc_232A0
		mov	byte_35CDE, 2
		mov	word_35CE2, 0
		mov	word_35CE0, 0
		mov	word_3A37F, 0
		mov	word_3A381, 0
		jmp	loc_232A0
; ---------------------------------------------------------------------------

loc_23198:
		mov	al, byte_35CDE
		cbw
		cmp	ax, 2
		jnz	loc_2326F
		inc	word_3A37F
		inc	word_3A381
		cmp	word_35CE0, 0
		jnz	short loc_231B8
		push	cs
		call	near ptr sub_22DC8
		jmp	short loc_231EA
; ---------------------------------------------------------------------------

loc_231B8:
		cmp	word_35CE0, 1
		jnz	short loc_231C5
		push	cs
		call	near ptr sub_22F0A
		jmp	short loc_231EA
; ---------------------------------------------------------------------------

loc_231C5:
		cmp	word_35CE0, 2
		jnz	short loc_231D2
		push	cs
		call	near ptr sub_22E09
		jmp	short loc_231EA
; ---------------------------------------------------------------------------

loc_231D2:
		cmp	word_35CE0, 3
		jnz	short loc_231DF
		push	cs
		call	near ptr sub_22F2A
		jmp	short loc_231EA
; ---------------------------------------------------------------------------

loc_231DF:
		cmp	word_35CE0, 4
		jnz	short loc_231EA
		push	cs
		call	near ptr sub_22AA7

loc_231EA:
		cmp	word_3A37F, 0
		jnz	short loc_2320E
		cmp	word_35CE0, 4
		jnz	short loc_23205
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		jmp	short loc_2320A
; ---------------------------------------------------------------------------

loc_23205:
		mov	ax, 4
		mov	dx, ax

loc_2320A:
		mov	word_35CE0, dx

loc_2320E:
		push	large 300060h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 10h
		push	ax
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	0BB8h
		push	1
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ds
		push	offset word_3A383
		push	ds
		push	offset word_35CE4
		push	ds
		push	offset word_3A381
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A383, 0
		jg	short loc_232A0
		mov	byte_35CDE, 8
		push	5
		call	sub_125C9
		pop	cx
		mov	word_3A37F, 0
		jmp	short loc_232A0
; ---------------------------------------------------------------------------

loc_2326F:
		mov	al, byte_35CDE
		cbw
		cmp	ax, 8
		jnz	short loc_232A0
		push	word_3984E
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_1588A
		call	sub_12589
		push	ds
		push	offset unk_37635
		call	sub_30DEE
		add	sp, 0Eh
		call	sub_1261B

loc_232A0:
		pop	di
		pop	si
		leave
		retf
sub_22F4A	endp

seg033		ends

; ===========================================================================

; Segment type:	Pure code
seg034		segment	byte public 'CODE' use16
		assume cs:seg034
		;org 4
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_232A4	proc far
		push	bp
		mov	bp, sp
		xor	dx, dx
		jmp	short loc_232CC
; ---------------------------------------------------------------------------

loc_232AB:
		xor	cx, cx
		jmp	short loc_232C6
; ---------------------------------------------------------------------------

loc_232AF:
		mov	bx, dx
		imul	bx, 3
		add	bx, cx
		mov	al, [bx+6F0h]
		mov	bx, dx
		imul	bx, 3
		add	bx, cx
		mov	[bx+59EEh], al
		inc	cx

loc_232C6:
		cmp	cx, 3
		jl	short loc_232AF
		inc	dx

loc_232CC:
		cmp	dx, 10h
		jl	short loc_232AB
		pop	bp
		retf
sub_232A4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_232D3	proc far
		push	bp
		mov	bp, sp
		push	ds
		push	offset unk_3A38E
		call	sub_EB10
		add	sp, 4
		pop	bp
		retf
sub_232D3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_232E4	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h

		push	bp
		mov	bp, sp
		mov	dx, [bp+arg_6]
		cmp	byte_34A30, 0
		jnz	short loc_232F6
		mov	ax, [bp+arg_4]
		jmp	short loc_23321
; ---------------------------------------------------------------------------

loc_232F6:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_23303
		mov	ax, dx
		jmp	short loc_23321
; ---------------------------------------------------------------------------

loc_23303:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_23311
		mov	ax, [bp+arg_8]
		jmp	short loc_23321
; ---------------------------------------------------------------------------

loc_23311:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_2331F
		mov	ax, [bp+arg_A]
		jmp	short loc_23321
; ---------------------------------------------------------------------------

loc_2331F:
		mov	ax, dx

loc_23321:
		les	bx, [bp+arg_0]
		mov	es:[bx], ax
		pop	bp
		retf
sub_232E4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_23329	proc far

var_64		= word ptr -64h
var_62		= word ptr -62h
var_60		= word ptr -60h
var_5E		= word ptr -5Eh
var_5C		= word ptr -5Ch
var_5A		= word ptr -5Ah
var_58		= word ptr -58h
var_56		= word ptr -56h
var_54		= word ptr -54h
var_52		= word ptr -52h
var_50		= word ptr -50h
var_4E		= word ptr -4Eh
var_4C		= word ptr -4Ch
var_4A		= word ptr -4Ah
var_48		= word ptr -48h
var_46		= word ptr -46h
var_44		= word ptr -44h
var_42		= word ptr -42h
var_40		= word ptr -40h
var_3E		= word ptr -3Eh
var_3C		= word ptr -3Ch
var_3A		= word ptr -3Ah
var_38		= word ptr -38h
var_36		= word ptr -36h
var_34		= byte ptr -34h
var_33		= byte ptr -33h
var_32		= word ptr -32h
var_30		= word ptr -30h
var_2E		= word ptr -2Eh
var_2C		= word ptr -2Ch
var_2A		= word ptr -2Ah
var_28		= word ptr -28h
var_26		= word ptr -26h
var_24		= word ptr -24h
var_22		= word ptr -22h
var_20		= word ptr -20h
var_1E		= word ptr -1Eh
var_1C		= word ptr -1Ch
var_1A		= word ptr -1Ah
var_18		= word ptr -18h
var_16		= word ptr -16h
var_14		= word ptr -14h
var_12		= word ptr -12h
var_10		= word ptr -10h
var_E		= word ptr -0Eh
var_C		= word ptr -0Ch
var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= byte ptr -2
var_1		= byte ptr -1

		enter	64h, 0
		push	si
		push	di
		mov	byte_360CC, 1
		mov	word_386B3, 7
		xor	si, si
		jmp	short loc_2335B
; ---------------------------------------------------------------------------

loc_2333E:
		xor	di, di
		jmp	short loc_23355
; ---------------------------------------------------------------------------

loc_23342:
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+di+6F0h]
		mov	bx, si
		imul	bx, 3
		mov	[bx+di+59EEh], al
		inc	di

loc_23355:
		cmp	di, 3
		jl	short loc_23342
		inc	si

loc_2335B:
		cmp	si, 10h
		jl	short loc_2333E
		xor	si, si
		jmp	short loc_2336A
; ---------------------------------------------------------------------------

loc_23364:
		mov	byte ptr [si+5A1Fh], 0
		inc	si

loc_2336A:
		cmp	si, 0Ah
		jl	short loc_23364
		mov	word_3A3F3, 1
		push	0
		push	ds
		push	offset aTamasii_bos ; "tamasii.bos"
		push	ds
		push	offset word_3A3C9
		call	sub_1568F
		mov	word_3A3F3, 0
		mov	ax, word_3A3C9
		mov	[bp+var_32], ax
		mov	ax, word_3A3CB
		mov	[bp+var_30], ax
		mov	ax, word_3A3CD
		mov	[bp+var_2E], ax
		mov	ax, word_3A3CF
		mov	[bp+var_2C], ax
		mov	ax, word_3A3D1
		mov	[bp+var_2A], ax
		mov	ax, word_3A3D3
		mov	[bp+var_28], ax
		mov	ax, word_3A3D5
		mov	[bp+var_26], ax
		mov	ax, word_3A3D7
		mov	[bp+var_24], ax
		mov	ax, word_3A3D9
		mov	[bp+var_22], ax
		mov	ax, word_3A3DB
		mov	[bp+var_20], ax
		mov	ax, word_3A3DD
		mov	[bp+var_1E], ax
		mov	ax, word_3A3DF
		mov	[bp+var_1C], ax
		mov	ax, word_3A3E1
		mov	[bp+var_1A], ax
		mov	ax, word_3A3E3
		mov	[bp+var_18], ax
		mov	ax, word_3A3E5
		mov	[bp+var_16], ax
		mov	ax, word_3A3E7
		mov	[bp+var_14], ax
		mov	ax, word_3A3E9
		mov	[bp+var_12], ax
		mov	ax, word_3A3EB
		mov	[bp+var_10], ax
		mov	ax, word_3A3ED
		mov	[bp+var_E], ax
		mov	ax, word_3A3EF
		mov	[bp+var_C], ax
		mov	ax, word_3A3F1
		mov	[bp+var_A], ax
		mov	ax, word_3A3F3
		mov	[bp+var_8], ax
		mov	ax, word_3A3F5
		mov	[bp+var_6], ax
		mov	ax, word_3A3F7
		mov	[bp+var_4], ax
		mov	al, byte_3A3F9
		mov	[bp+var_2], al
		mov	al, byte_3A3FA
		mov	[bp+var_1], al
		push	ds
		push	offset unk_3A405
		push	ds
		push	offset unk_3A403
		push	ds
		push	offset unk_3A42C
		push	ds
		push	offset unk_3A41B
		push	ss
		lea	ax, [bp+var_32]
		push	ax
		call	sub_15851
		mov	word_3A4ED, 1
		push	1
		push	ds
		push	offset aTamasii2_bos ; "tamasii2.bos"
		push	ds
		push	offset word_3A4C3
		call	sub_1568F
		mov	word_3A4ED, 0
		push	ds
		push	offset aTamayen_ptn ; "tamayen.ptn"
		push	2
		call	sub_10888
		add	sp, 2Eh
		mov	si, 1
		jmp	loc_23541
; ---------------------------------------------------------------------------

loc_2346F:
		mov	ax, word_3A4C3
		mov	[bp+var_64], ax
		mov	ax, word_3A4C5
		mov	[bp+var_62], ax
		mov	ax, word_3A4C7
		mov	[bp+var_60], ax
		mov	ax, word_3A4C9
		mov	[bp+var_5E], ax
		mov	ax, word_3A4CB
		mov	[bp+var_5C], ax
		mov	ax, word_3A4CD
		mov	[bp+var_5A], ax
		mov	ax, word_3A4CF
		mov	[bp+var_58], ax
		mov	ax, word_3A4D1
		mov	[bp+var_56], ax
		mov	ax, word_3A4D3
		mov	[bp+var_54], ax
		mov	ax, word_3A4D5
		mov	[bp+var_52], ax
		mov	ax, word_3A4D7
		mov	[bp+var_50], ax
		mov	ax, word_3A4D9
		mov	[bp+var_4E], ax
		mov	ax, word_3A4DB
		mov	[bp+var_4C], ax
		mov	ax, word_3A4DD
		mov	[bp+var_4A], ax
		mov	ax, word_3A4DF
		mov	[bp+var_48], ax
		mov	ax, word_3A4E1
		mov	[bp+var_46], ax
		mov	ax, word_3A4E3
		mov	[bp+var_44], ax
		mov	ax, word_3A4E5
		mov	[bp+var_42], ax
		mov	ax, word_3A4E7
		mov	[bp+var_40], ax
		mov	ax, word_3A4E9
		mov	[bp+var_3E], ax
		mov	ax, word_3A4EB
		mov	[bp+var_3C], ax
		mov	ax, word_3A4ED
		mov	[bp+var_3A], ax
		mov	ax, word_3A4EF
		mov	[bp+var_38], ax
		mov	ax, word_3A4F1
		mov	[bp+var_36], ax
		mov	al, byte_3A4F3
		mov	[bp+var_34], al
		mov	al, byte_3A4F4
		mov	[bp+var_33], al
		mov	ax, si
		imul	ax, 32h
		add	ax, 5B2Dh
		push	ds
		push	ax
		mov	ax, si
		imul	ax, 32h
		add	ax, 5B2Bh
		push	ds
		push	ax
		mov	ax, si
		imul	ax, 32h
		add	ax, 5B54h
		push	ds
		push	ax
		mov	ax, si
		imul	ax, 32h
		add	ax, 5B43h
		push	ds
		push	ax
		push	ss
		lea	ax, [bp+var_64]
		push	ax
		call	sub_15851
		add	sp, 14h
		inc	si

loc_23541:
		cmp	si, 0Ah
		jl	loc_2346F
		nop
		push	cs
		call	near ptr sub_2355F
		push	large 700FFh
		call	sub_22264
		add	sp, 4
		pop	di
		pop	si
		leave
		retf
sub_23329	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2355F	proc far
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	byte_3A3BE, 0
		mov	word_3A6CA, 0
		mov	word_3A6C8, 0Eh
		mov	word_3A1E5, 0Ah
		mov	word_3A1E7, 6
		push	large 1900040h
		push	large 2400020h
		push	large 320000h
		push	0
		push	ds
		push	offset word_3A3C9
		call	sub_166D2
		push	large 1900040h
		push	large 2400020h
		push	large 320000h
		push	0
		push	ds
		push	offset word_3A3FB
		call	sub_166D2
		add	sp, 24h
		xor	si, si
		jmp	short loc_235D7
; ---------------------------------------------------------------------------

loc_235C2:
		xor	di, di
		jmp	short loc_235D1
; ---------------------------------------------------------------------------

loc_235C6:
		mov	bx, si
		imul	bx, 3
		mov	byte ptr [bx+di+5414h],	0
		inc	di

loc_235D1:
		cmp	di, 3
		jl	short loc_235C6
		inc	si

loc_235D7:
		cmp	si, 10h
		jl	short loc_235C2
		pop	di
		pop	si
		pop	bp
		retf
sub_2355F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_235E0	proc far
		push	bp
		mov	bp, sp
		push	0
		call	sub_169CB
		push	1
		call	sub_169CB
		push	2
		call	sub_108AB
		add	sp, 6
		pop	bp
		retf
sub_235E0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_235FD	proc near
		push	bp
		mov	bp, sp
		cmp	word_36C28, 100h
		jle	short loc_23625
		cmp	word_36C28, 160h
		jge	short loc_23625
		cmp	word_36C2A, 84h	; '�
		jge	short loc_23625
		cmp	word_36C2A, 0B4h ; '?'
		jge	short loc_23625
		mov	ax, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_23625:
		xor	ax, ax
		pop	bp
		retn
sub_235FD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_23629	proc near

var_2		= word ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

		enter	2, 0
		push	si
		mov	si, [bp+arg_4]
		push	1
		push	[bp+arg_0]
		push	[bp+arg_2]
		push	0
		mov	ax, si
		imul	ax, 32h
		add	ax, 5A29h
		push	ds
		push	ax
		call	sub_16733
		add	sp, 0Ch
		mov	ax, word_3A6CA
		mov	bx, 0Ch
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_23689
		mov	bx, si
		imul	bx, 32h
		cmp	word ptr [bx+5A4Dh], 2
		jl	short loc_23673
		mov	bx, si
		imul	bx, 32h
		mov	word ptr [bx+5A4Dh], 0
		jmp	short loc_23689
; ---------------------------------------------------------------------------

loc_23673:
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A4Dh]
		inc	ax
		mov	[bp+var_2], ax
		mov	bx, si
		imul	bx, 32h
		mov	[bx+5A4Dh], ax

loc_23689:
		pop	si
		leave
		retn	6
sub_23629	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2368E	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		xor	si, si
		jmp	short loc_236D6
; ---------------------------------------------------------------------------

loc_23696:
		cmp	byte ptr [si+5A1Fh], 0
		jnz	short loc_236D5
		push	large 1900040h
		push	large 2400020h
		push	32h ; '2'
		push	[bp+arg_0]
		push	[bp+arg_2]
		mov	ax, si
		imul	ax, 32h
		add	ax, 5B23h
		push	ds
		push	ax
		call	sub_166D2
		add	sp, 12h
		mov	bx, si
		imul	bx, 32h
		mov	word ptr [bx+5B47h], 0
		mov	byte ptr [si+5A1Fh], 1
		jmp	short loc_236DB
; ---------------------------------------------------------------------------

loc_236D5:
		inc	si

loc_236D6:
		cmp	si, 0Ah
		jl	short loc_23696

loc_236DB:
		pop	si
		pop	bp
		retn	4
sub_2368E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_236E0	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

		push	bp
		mov	bp, sp
		mov	dx, [bp+arg_2]
		cmp	word_34A78, 1
		jz	short loc_2370F
		mov	ax, dx
		add	ax, 0FFF0h
		cmp	ax, word_36C26
		jg	short loc_2370F
		mov	ax, dx
		add	ax, [bp+arg_0]
		cmp	ax, word_36C26
		jl	short loc_2370F
		mov	byte_34A4F, 1
		mov	ax, 1
		pop	bp
		retn	4
; ---------------------------------------------------------------------------

loc_2370F:
		xor	ax, ax
		pop	bp
		retn	4
sub_236E0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_23715	proc near
		push	bp
		mov	bp, sp
		push	si
		xor	si, si
		jmp	short loc_23765
; ---------------------------------------------------------------------------

loc_2371D:
		cmp	byte ptr [si+5A1Fh], 0
		jz	short loc_23764
		mov	bx, si
		imul	bx, 32h
		cmp	word ptr [bx+5B25h], 180h
		jg	short loc_2374E
		push	large 10008h
		push	large 0
		mov	ax, si
		imul	ax, 32h
		add	ax, 5B23h
		push	ds
		push	ax
		call	sub_16733
		add	sp, 0Ch
		jmp	short loc_23764
; ---------------------------------------------------------------------------

loc_2374E:
		mov	bx, si
		imul	bx, 32h
		push	word ptr [bx+5B23h]
		push	180h
		push	ds
		mov	ax, si
		add	ax, 5A1Fh
		push	ax
		call	sub_2379B

loc_23764:
		inc	si

loc_23765:
		cmp	si, 0Ah
		jl	short loc_2371D
		pop	si
		pop	bp
		retn
sub_23715	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2376D	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_6]
		mov	di, [bp+arg_4]
		push	large 100010h
		push	di
		push	si
		call	sub_10433
		push	[bp+arg_0]
		push	[bp+arg_2]
		push	di
		push	si
		call	sub_19A62
		add	sp, 10h
		pop	di
		pop	si
		pop	bp
		retn	8
sub_2376D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2379B	proc near

arg_0		= dword	ptr  4
arg_4		= word ptr  8
arg_6		= word ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_6]
		mov	di, [bp+arg_4]
		les	bx, [bp+arg_0]
		inc	byte ptr es:[bx]
		mov	byte_35B29, 1
		mov	al, es:[bx]
		cbw
		cmp	ax, 5
		jge	short loc_237DA
		push	large 80h ; '?'
		push	di
		push	si
		call	sub_19A62
		push	si
		push	0
		call	sub_236E0
		push	7
		call	sub_125C9
		add	sp, 0Ah
		jmp	loc_23C44
; ---------------------------------------------------------------------------

loc_237DA:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 0Ah
		jge	short loc_237FF
		push	large 10080h
		push	di
		push	si
		call	sub_19A62
		add	sp, 8
		push	si
		push	0
		call	sub_236E0
		jmp	loc_23C44
; ---------------------------------------------------------------------------

loc_237FF:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 0Fh
		jge	short loc_2383B
		lea	ax, [si-10h]
		push	ax
		push	20h ; ' '
		call	sub_236E0
		push	large 10080h
		lea	ax, [di-8]
		push	ax
		push	si
		call	sub_19A62
		push	large 80h ; '?'
		push	di
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		add	sp, 10h
		push	0
		jmp	short loc_23875
; ---------------------------------------------------------------------------

loc_2383B:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 14h
		jge	short loc_23881
		lea	ax, [si-10h]
		push	ax
		push	20h ; ' '
		call	sub_236E0
		push	large 10080h
		lea	ax, [di-10h]
		push	ax
		push	si
		call	sub_19A62
		push	large 10080h
		push	di
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		add	sp, 10h
		push	1

loc_23875:
		push	80h ; '?'
		push	di
		mov	ax, si
		add	ax, 10h
		jmp	loc_23A96
; ---------------------------------------------------------------------------

loc_23881:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 19h
		jge	short loc_238E7
		lea	ax, [si-20h]
		push	ax
		push	40h ; '@'
		call	sub_236E0
		push	large 10080h
		lea	ax, [di-18h]
		push	ax
		push	si
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-8]
		push	ax
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-8]
		push	ax
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		add	sp, 18h

loc_238CF:
		push	large 80h ; '?'
		push	di
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 8
		push	0
		jmp	loc_23C36
; ---------------------------------------------------------------------------

loc_238E7:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 1Eh
		jge	short loc_2394A
		lea	ax, [si-20h]
		push	ax
		push	40h ; '@'
		call	sub_236E0
		push	large 80h ; '?'
		lea	ax, [di-20h]
		push	ax
		push	si
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-10h]
		push	ax
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-10h]
		push	ax
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		push	large 10080h
		push	di
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 20h
		push	1
		jmp	loc_23C36
; ---------------------------------------------------------------------------

loc_2394A:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 23h	; '#'
		jge	short loc_239B8
		lea	ax, [si-20h]
		push	ax
		push	40h ; '@'
		call	sub_236E0
		push	large 80h ; '?'
		lea	ax, [di-18h]
		push	ax
		push	si
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-18h]
		push	ax
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-18h]
		push	ax
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-8]
		push	ax
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 20h
		push	1

loc_239AD:
		push	80h ; '?'
		mov	ax, di
		add	ax, 0FFF8h
		jmp	loc_23A90
; ---------------------------------------------------------------------------

loc_239B8:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 28h	; '('
		jge	short loc_23A25
		lea	ax, [si-20h]
		push	ax
		push	40h ; '@'
		call	sub_236E0
		push	large 80h ; '?'
		lea	ax, [di-10h]
		push	ax
		push	si
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-20h]
		push	ax
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-20h]
		push	ax
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-10h]
		push	ax
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 20h
		push	1

loc_23A1B:
		push	80h ; '?'
		mov	ax, di
		add	ax, 0FFF0h
		jmp	short loc_23A90
; ---------------------------------------------------------------------------

loc_23A25:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 2Dh	; '-'
		jge	short loc_23AA2
		lea	ax, [si-20h]
		push	ax
		push	40h ; '@'
		call	sub_236E0
		push	large 80h ; '?'
		lea	ax, [di-8]
		push	ax
		push	si
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-18h]
		push	ax
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-18h]
		push	ax
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		push	large 10080h
		lea	ax, [di-18h]
		push	ax
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 20h
		push	1

loc_23A88:
		push	80h ; '?'
		mov	ax, di
		add	ax, 0FFE8h

loc_23A90:
		push	ax

loc_23A91:
		mov	ax, si
		add	ax, 20h	; ' '

loc_23A96:
		push	ax
		call	sub_19A62
		add	sp, 8
		jmp	loc_23C44
; ---------------------------------------------------------------------------

loc_23AA2:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 32h	; '2'
		jge	short loc_23B0D
		lea	ax, [si-20h]
		push	ax
		push	40h ; '@'
		call	sub_236E0
		push	large 80h ; '?'
		push	di
		push	si
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-10h]
		push	ax
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-10h]
		push	ax
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-20h]
		push	ax
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 20h
		push	large 80h ; '?'
		mov	ax, di
		add	ax, 0FFE0h
		jmp	short loc_23A90
; ---------------------------------------------------------------------------

loc_23B0D:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 37h	; '7'
		jge	short loc_23B70
		lea	ax, [si-20h]
		push	ax
		push	40h ; '@'
		call	sub_236E0
		push	large 30080h
		push	di
		push	si
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-8]
		push	ax
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-8]
		push	ax
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-18h]
		push	ax
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 20h
		push	0
		jmp	loc_23A88
; ---------------------------------------------------------------------------

loc_23B70:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 3Ch	; '<'
		jge	short loc_23BC0
		lea	ax, [si-20h]
		push	ax
		push	40h ; '@'
		call	sub_236E0
		push	large 80h ; '?'
		push	di
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		push	di
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-10h]
		push	ax
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 18h
		push	0
		jmp	loc_23A1B
; ---------------------------------------------------------------------------

loc_23BC0:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 41h	; 'A'
		jge	short loc_23C07
		push	large 30080h
		push	di
		lea	ax, [si-10h]
		push	ax
		call	sub_19A62
		push	large 30080h
		push	di
		lea	ax, [si+10h]
		push	ax
		call	sub_19A62
		push	large 80h ; '?'
		lea	ax, [di-8]
		push	ax
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 18h
		push	0
		jmp	loc_239AD
; ---------------------------------------------------------------------------

loc_23C07:
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 46h	; 'F'
		jl	loc_238CF
		les	bx, [bp+arg_0]
		mov	al, es:[bx]
		cbw
		cmp	ax, 4Bh	; 'K'
		jge	short loc_23C3D
		push	large 30080h
		push	di
		lea	ax, [si-20h]
		push	ax
		call	sub_19A62
		add	sp, 8
		push	3

loc_23C36:
		push	80h ; '?'
		push	di
		jmp	loc_23A91
; ---------------------------------------------------------------------------

loc_23C3D:
		les	bx, [bp+arg_0]
		mov	byte ptr es:[bx], 0

loc_23C44:
		mov	byte_35B29, 0
		pop	di
		pop	si
		pop	bp
		retn	8
sub_2379B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_23C4F	proc near

var_2		= word ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6

		enter	2, 0
		push	si
		push	di
		mov	ax, [bp+arg_2]
		imul	ax, 50h
		mov	si, ax
		cmp	[bp+arg_2], 0
		jl	loc_23D13
		cmp	[bp+arg_2], 18Fh
		jg	loc_23D13
		mov	[bp+var_2], 0
		jmp	loc_23D0B
; ---------------------------------------------------------------------------

loc_23C76:
		push	1
		call	sub_EA3E
		mov	ax, 0A800h
		mov	es, ax
		assume es:nothing
		mov	ax, es:[si]
		and	ax, [bp+arg_0]
		mov	di, ax
		push	0
		call	sub_EA3E
		mov	ax, 0A800h
		mov	es, ax
		mov	es:[si], di
		push	1
		call	sub_EA3E
		mov	ax, 0B000h
		mov	es, ax
		assume es:nothing
		mov	ax, es:[si]
		and	ax, [bp+arg_0]
		mov	di, ax
		push	0
		call	sub_EA3E
		mov	ax, 0B000h
		mov	es, ax
		mov	es:[si], di
		push	1
		call	sub_EA3E
		mov	ax, 0B800h
		mov	es, ax
		assume es:nothing
		mov	ax, es:[si]
		and	ax, [bp+arg_0]
		mov	di, ax
		push	0
		call	sub_EA3E
		mov	ax, 0B800h
		mov	es, ax
		mov	es:[si], di
		push	1
		call	sub_EA3E
		mov	ax, 0E000h
		mov	es, ax
		assume es:nothing
		mov	ax, es:[si]
		and	ax, [bp+arg_0]
		mov	di, ax
		push	0
		call	sub_EA3E
		add	sp, 10h
		mov	ax, 0E000h
		mov	es, ax
		mov	es:[si], di
		add	si, 2
		inc	[bp+var_2]

loc_23D0B:
		cmp	[bp+var_2], 28h	; '('
		jl	loc_23C76

loc_23D13:
		pop	di
		pop	si
		leave
		retn	4
sub_23C4F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_23D19	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_23E6A
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_23D63
		mov	byte_3A6B9, 0
		mov	byte_3A6BA, 0
		push	large 10002h
		push	large 30004h
		push	ds
		push	offset word_3A6B7
		push	cs
		call	near ptr sub_232E4
		push	large 32005Ah
		push	large 5A005Ah
		push	ds
		push	offset word_3A6BB
		push	cs
		call	near ptr sub_232E4
		add	sp, 18h

loc_23D63:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A6B7
		or	dx, dx
		jnz	loc_23E6A
		movsx	eax, word_3A6BB
		mov	dl, byte_3A6B9
		mov	dh, 0
		and	dx, 0FFh
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		add	ax, 140h
		mov	si, ax
		movsx	eax, word_3A6BB
		mov	dl, byte_3A6B9
		mov	dh, 0
		and	dx, 0FFh
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		add	ax, 0B4h ; '?'
		mov	di, ax
		push	large 0
		push	large 0
		push	32h ; '2'
		mov	al, byte_3A6B9
		add	al, byte_3A6BA
		push	ax
		push	di
		push	si
		push	ds
		push	offset unk_37635
		call	sub_304B8
		movsx	eax, word_3A6BB
		mov	dl, byte_3A6B9
		mov	dh, 0
		add	dx, 80h	; '?'
		and	dx, 0FFh
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		add	ax, 140h
		mov	si, ax
		movsx	eax, word_3A6BB
		mov	dl, byte_3A6B9
		mov	dh, 0
		add	dx, 80h	; '?'
		and	dx, 0FFh
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		add	ax, 0B4h ; '?'
		mov	di, ax
		push	large 0
		push	large 0
		push	32h ; '2'
		mov	al, byte_3A6B9
		add	al, byte_3A6BA
		add	al, 80h	; '?'
		push	ax
		push	di
		push	si
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		cmp	word_3A6CA, 384h
		jl	short loc_23E5E
		mov	word_3A6CA, 0

loc_23E5E:
		mov	al, byte_3A6B9
		add	al, 0F8h ; '�
		mov	byte_3A6B9, al
		inc	byte_3A6BA

loc_23E6A:
		pop	di
		pop	si
		pop	bp
		retn
sub_23D19	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_23E6E	proc near

var_7		= word ptr -7
var_4		= word ptr -4
var_2		= word ptr -2

		enter	8, 0
		push	si
		push	large 320037h
		push	large 3C0050h
		push	ss
		lea	ax, [bp+var_7+1]
		push	ax
		push	cs
		call	near ptr sub_232E4
		add	sp, 0Ch
		mov	ax, word_3A6CA
		cwd
		idiv	[bp+var_7+1]
		or	dx, dx
		jnz	short loc_23F13
		xor	si, si
		jmp	short loc_23F0E
; ---------------------------------------------------------------------------

loc_23E9A:
		mov	bx, si
		shl	bx, 5
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 4
		sar	eax, 8
		add	ax, 13Ch
		mov	[bp+var_2], ax
		mov	bx, si
		shl	bx, 5
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 4
		sar	eax, 8
		add	ax, 0E0h ; '�
		mov	[bp+var_4], ax
		push	0A4h ; '?'
		mov	ax, word_36C26
		add	ax, 0FED4h
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_7], al
		push	large 0E00138h
		push	large 200005h
		push	30h ; '0'
		push	[bp+var_7]
		push	[bp+var_4]
		push	[bp+var_2]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_23F0E:
		cmp	si, 8
		jl	short loc_23E9A

loc_23F13:
		pop	si
		leave
		retn
sub_23E6E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_23F16	proc near
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_23F62
		push	large 1900040h
		push	large 2400020h
		push	large 3200D0h
		push	130h
		push	ds
		push	offset word_3A3C9
		call	sub_166D2
		push	large 1900040h
		push	large 2400020h
		push	large 3200D0h
		push	130h
		push	ds
		push	offset word_3A3FB
		call	sub_166D2
		add	sp, 24h
		jmp	short loc_23F99
; ---------------------------------------------------------------------------

loc_23F62:
		cmp	word_3A6CA, 0C8h ; '?'
		jle	short loc_23F99
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_23F99
		push	large 0FFFCh
		push	0FFFDh
		call	sub_23629
		push	large 10004h
		push	0FFFDh
		call	sub_23629
		cmp	word_3A3CB, 60h	; '`'
		jge	short loc_23F99
		mov	ax, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_23F99:
		xor	ax, ax
		pop	bp
		retn
sub_23F16	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_23F9D	proc near

var_8		= word ptr -8
var_6		= byte ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	8, 0
		push	si
		push	large 0
		push	0
		call	sub_23629
		push	large 10000h
		push	0
		call	sub_23629
		push	large 3C0046h
		push	large 500064h
		push	ss
		lea	ax, [bp+var_6]
		push	ax
		push	cs
		call	near ptr sub_232E4
		add	sp, 0Ch
		mov	ax, word_3A6CA
		mov	bx, 50h	; 'P'
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2402E
		xor	si, si
		jmp	short loc_24029
; ---------------------------------------------------------------------------

loc_23FDE:
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A29h]
		add	ax, 0Ch
		mov	[bp+var_2], ax
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A2Bh]
		add	ax, 8
		mov	[bp+var_4], ax
		push	large 13001Bh
		push	large 170015h
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	cs
		call	near ptr sub_232E4
		push	37h ; '7'
		push	[bp+var_8]
		push	[bp+var_4]
		push	[bp+var_2]
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 18h
		inc	si

loc_24029:
		cmp	si, 2
		jl	short loc_23FDE

loc_2402E:
		cmp	word_3A6CA, 258h
		jle	short loc_2403B
		mov	ax, 2
		jmp	short loc_2403E
; ---------------------------------------------------------------------------

loc_2403B:
		mov	ax, 1

loc_2403E:
		pop	si
		leave
		retn
sub_23F9D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24041	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	word_3A6CA, 0Ah
		jge	short loc_24064
		push	large 78008Ch
		push	large 0A000C8h
		push	ds
		push	offset word_3A6B7
		push	cs
		call	near ptr sub_232E4
		add	sp, 0Ch

loc_24064:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A6B7
		or	dx, dx
		jnz	short loc_24092
		mov	ax, word_3A3C9
		add	ax, 0Ch
		push	ax
		mov	ax, word_3A3CB
		add	ax, 8
		push	ax
		call	sub_2368E
		mov	ax, word_3A3FB
		add	ax, 0Ch
		push	ax
		mov	ax, word_3A3FD
		add	ax, 8
		push	ax
		call	sub_2368E

loc_24092:
		mov	bx, word_3A6CA
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		imul	eax, 6
		sar	eax, 8
		mov	si, ax
		mov	bx, word_3A6CA
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 1
		sar	eax, 8
		mov	di, ax
		call	sub_23715
		push	0
		push	si
		push	di
		call	sub_23629
		push	1
		mov	ax, si
		neg	ax
		push	ax
		push	di
		call	sub_23629
		pop	di
		pop	si
		pop	bp
		retn
sub_24041	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_240DE	proc near
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0C8h ; '?'
		jle	short loc_2414A
		mov	ax, word_3A6CA
		mov	bx, 0C8h ; '?'
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2414A
		push	large 80014h
		push	large 0A0032h
		push	190h
		mov	ax, word_36C26
		add	ax, 3Ch	; '<'
		push	ax
		push	large 930133h
		push	ds
		push	offset unk_391A0
		call	sub_1209D
		push	large 80014h
		push	large 0A0032h
		push	190h
		mov	ax, word_36C26
		add	ax, 0FFC4h
		push	ax
		push	large 930150h
		push	ds
		push	offset unk_391E5
		call	sub_1209D
		push	6
		call	sub_125C9
		add	sp, 2Ah

loc_2414A:
		pop	bp
		retn
sub_240DE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2414C	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, word_3A6CA
		mov	bx, 0C8h ; '?'
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2419B
		push	large 28000Ch
		mov	ax, word_3A3CB
		add	ax, 0Ch
		push	ax
		mov	ax, word_3A3C9
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 28000Ch
		mov	ax, word_3A3FD
		add	ax, 0Ch
		push	ax
		mov	ax, word_3A3FB
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 18h

loc_2419B:
		mov	bx, word_3A6CA
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 2
		sar	eax, 8
		mov	si, ax
		mov	bx, word_3A6CA
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 1
		sar	eax, 8
		mov	di, ax
		call	sub_23715
		push	0
		push	si
		push	di
		call	sub_23629
		push	1
		mov	ax, si
		neg	ax
		push	ax
		push	di
		call	sub_23629
		pop	di
		pop	si
		pop	bp
		retn
sub_2414C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_241E7	proc near

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_24310
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_24219
		mov	byte ptr word_3A6BD, 20h ; ' '
		push	large 40006h
		push	large 8000Eh
		push	ds
		push	offset word_3A6B7
		push	cs
		call	near ptr sub_232E4
		add	sp, 0Ch

loc_24219:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A6B7
		or	dx, dx
		jnz	loc_24310
		xor	si, si
		jmp	loc_242EC
; ---------------------------------------------------------------------------

loc_2422C:
		mov	bx, word_3A6CA
		shl	bx, 2
		mov	ax, si
		shl	ax, 7
		add	bx, ax
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		imul	eax, 5Ah
		sar	eax, 8
		add	ax, 140h
		mov	di, ax
		mov	bx, word_3A6CA
		shl	bx, 2
		mov	ax, si
		shl	ax, 7
		add	bx, ax
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+87Ah]
		imul	eax, 5Ah
		sar	eax, 8
		add	ax, 0B4h ; '?'
		mov	[bp+var_2], ax
		push	large 0
		push	large 0
		push	24h ; '$'
		push	word_3A6BD
		push	ax
		push	di
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	24h ; '$'
		mov	al, byte ptr word_3A6BD
		add	al, 40h	; '@'
		push	ax
		push	[bp+var_2]
		push	di
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		push	large 0
		push	large 0
		push	24h ; '$'
		mov	al, byte ptr word_3A6BD
		add	al, 80h	; '?'
		push	ax
		push	[bp+var_2]
		push	di
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	24h ; '$'
		mov	al, byte ptr word_3A6BD
		add	al, 0C0h ; '?'
		push	ax
		push	[bp+var_2]
		push	di
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		add	si, 2

loc_242EC:
		cmp	si, 4
		jl	loc_2422C
		cmp	word_3A6CA, 258h
		jg	short loc_24305
		mov	al, byte ptr word_3A6BD
		add	al, 0FBh ; '�
		mov	byte ptr word_3A6BD, al
		jmp	short loc_24310
; ---------------------------------------------------------------------------

loc_24305:
		mov	word_3A6CA, 0
		mov	ax, 1
		jmp	short loc_24312
; ---------------------------------------------------------------------------

loc_24310:
		xor	ax, ax

loc_24312:
		pop	di
		pop	si
		leave
		retn
sub_241E7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24316	proc near
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0C8h ; '?'
		jle	loc_244C9
		cmp	word_3A6CA, 0FAh ; '�
		jnz	short loc_24378
		push	large 40003Ch
		push	large 380034h
		push	ds
		push	offset word_3A6B7
		push	cs
		call	near ptr sub_232E4
		push	6
		call	sub_125C9
		add	sp, 0Eh
		push	large 40014h
		push	0Ah
		push	word_3A6B7
		push	190h
		call	IRand
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		add	dx, word_36C26
		add	dx, 0FFC4h
		push	dx
		push	large 930133h
		push	ds
		push	offset unk_391A0
		jmp	loc_244AE
; ---------------------------------------------------------------------------

loc_24378:
		cmp	word_3A6CA, 118h
		jnz	short loc_243B7
		push	6
		call	sub_125C9
		pop	cx
		push	large 40014h
		push	0Ah
		push	word_3A6B7
		push	190h
		call	IRand
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		add	dx, word_36C26
		add	dx, 0FFC4h
		push	dx
		push	large 930133h
		push	ds
		push	offset unk_391E5
		jmp	loc_244AE
; ---------------------------------------------------------------------------

loc_243B7:
		cmp	word_3A6CA, 136h
		jnz	short loc_243F6
		push	6
		call	sub_125C9
		pop	cx
		push	large 40014h
		push	0Ah
		push	word_3A6B7
		push	190h
		call	IRand
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		add	dx, word_36C26
		add	dx, 0FFC4h
		push	dx
		push	large 930133h
		push	ds
		push	offset unk_3922A
		jmp	loc_244AE
; ---------------------------------------------------------------------------

loc_243F6:
		cmp	word_3A6CA, 154h
		jnz	short loc_24434
		push	6
		call	sub_125C9
		pop	cx
		push	large 40014h
		push	0Ah
		push	word_3A6B7
		push	190h
		call	IRand
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		add	dx, word_36C26
		add	dx, 0FFC4h
		push	dx
		push	large 930133h
		push	ds
		push	offset unk_3926F
		jmp	short loc_244AE
; ---------------------------------------------------------------------------

loc_24434:
		cmp	word_3A6CA, 172h
		jnz	short loc_24472
		push	6
		call	sub_125C9
		pop	cx
		push	large 40014h
		push	0Ah
		push	word_3A6B7
		push	190h
		call	IRand
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		add	dx, word_36C26
		add	dx, 0FFC4h
		push	dx
		push	large 930133h
		push	ds
		push	offset unk_392B4
		jmp	short loc_244AE
; ---------------------------------------------------------------------------

loc_24472:
		cmp	word_3A6CA, 190h
		jnz	short loc_244B6
		push	6
		call	sub_125C9
		pop	cx
		push	large 40014h
		push	0Ah
		push	word_3A6B7
		push	190h
		call	IRand
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		add	dx, word_36C26
		add	dx, 0FFC4h
		push	dx
		push	large 930133h
		push	ds
		push	offset unk_392F9

loc_244AE:
		call	sub_1209D
		add	sp, 14h

loc_244B6:
		cmp	word_3A6CA, 1F4h
		jle	short loc_244C9
		mov	word_3A6CA, 0
		mov	ax, 2
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_244C9:
		mov	ax, 1
		pop	bp
		retn
sub_24316	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_244CE	proc near
		push	bp
		mov	bp, sp
		push	si
		cmp	word_3A6CA, 64h	; 'd'
		jle	loc_24647
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_244F9
		push	large 160017h
		push	large 190023h
		push	ds
		push	offset word_3A6B7
		push	cs
		call	near ptr sub_232E4
		add	sp, 0Ch

loc_244F9:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A6B7
		or	dx, dx
		jnz	loc_24647
		xor	si, si
		jmp	loc_24640
; ---------------------------------------------------------------------------

loc_2450C:
		push	large 0
		push	large 10001h
		push	30h ; '0'
		push	0
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A2Bh]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A29h]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 10001h
		push	20h ; ' '
		push	0
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A2Bh]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A29h]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		push	large 0
		push	large 10001h
		push	10h
		push	0
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A2Bh]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A29h]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 10001h
		push	10h
		push	80h ; '?'
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A2Bh]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A29h]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		push	large 0
		push	large 10001h
		push	20h ; ' '
		push	80h ; '?'
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A2Bh]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A29h]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 10001h
		push	30h ; '0'
		push	80h ; '?'
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A2Bh]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		imul	bx, 32h
		mov	ax, [bx+5A29h]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	7
		call	sub_125C9
		add	sp, 2Ah
		inc	si

loc_24640:
		cmp	si, 2
		jl	loc_2450C

loc_24647:
		cmp	word_3A6CA, 0FAh ; '�
		jle	short loc_2465A
		mov	word_3A6CA, 0
		mov	ax, 3
		jmp	short loc_2465D
; ---------------------------------------------------------------------------

loc_2465A:
		mov	ax, 2

loc_2465D:
		pop	si
		pop	bp
		retn
sub_244CE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24660	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2471B
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_246A0
		push	large 480044h
		push	large 40003Ch
		push	ds
		push	offset word_3A6B7
		push	cs
		call	near ptr sub_232E4
		push	large 140010h
		push	large 0A0000h
		push	ds
		push	(offset	word_3A6BD+1)
		push	cs
		call	near ptr sub_232E4
		add	sp, 18h

loc_246A0:
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_24709
		mov	ax, word_3A6CA
		add	ax, 0FF9Ch
		cwd
		idiv	bx
		mov	si, ax
		call	IRand
		mov	dx, word_3A6BD+1
		add	dx, dx
		inc	dx
		push	dx
		cwd
		pop	bx
		idiv	bx
		sub	dx, word_3A6BD+1
		mov	di, dx
		push	large 80014h
		push	0Ah
		push	word_3A6B7
		push	190h
		mov	ax, si
		shl	ax, 6
		add	ax, di
		push	ax
		push	40h ; '@'
		mov	ax, si
		shl	ax, 6
		add	ax, di
		push	ax
		mov	ax, si
		imul	ax, 45h
		add	ax, 4800h
		push	ds
		push	ax
		call	sub_1209D
		push	6
		call	sub_125C9
		add	sp, 16h

loc_24709:
		cmp	word_3A6CA, 0BEh ; '?'
		jl	short loc_2471B
		mov	word_3A6CA, 0
		xor	ax, ax
		jmp	short loc_2471E
; ---------------------------------------------------------------------------

loc_2471B:
		mov	ax, 3

loc_2471E:
		pop	di
		pop	si
		pop	bp
		retn
sub_24660	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24722	proc far

var_4		= dword	ptr -4

		enter	4, 0
		push	si
		push	di
		mov	eax, dword_35D18
		mov	[bp+var_4], eax
		cmp	byte_3A3BE, 0
		jnz	loc_24B19
		mov	word_3A6CA, 0
		mov	word_3A6C2, 0
		mov	word_3A6C0, 0
		push	cs
		call	near ptr sub_232A4
		push	large 0F000Fh
		push	large 0F0002h
		call	sub_EB59
		push	large 0F000Fh
		push	large 0F0006h
		call	sub_EB59
		push	large 0F000Fh
		push	large 0F0008h
		call	sub_EB59
		push	large 0F000Fh
		push	large 0F000Bh
		call	sub_EB59
		add	sp, 20h

loc_24796:
		inc	word_3A6CA
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_24871
		cmp	word_3A6C2, 0C8h ; '?'
		jge	short loc_247C9
		push	word_3A6C2
		push	2222h
		call	sub_23C4F
		mov	ax, 18Fh
		sub	ax, word_3A6C2
		push	ax
		push	2222h
		call	sub_23C4F

loc_247C9:
		mov	ax, word_3A6CA
		add	ax, ax
		cmp	ax, 8
		jle	short loc_247F9
		cmp	word_3A6C2, 0D0h ; '?'
		jge	short loc_247F9
		mov	ax, word_3A6C2
		add	ax, 0FFF8h
		push	ax
		push	0AAAAh
		call	sub_23C4F
		mov	ax, 18Fh
		sub	ax, word_3A6C2
		add	ax, 8
		push	ax
		push	0AAAAh
		call	sub_23C4F

loc_247F9:
		mov	ax, word_3A6CA
		add	ax, ax
		cmp	ax, 10h
		jle	short loc_24829
		cmp	word_3A6C2, 0D8h ; '?'
		jge	short loc_24829
		mov	ax, word_3A6C2
		add	ax, 0FFF0h
		push	ax
		push	0EEEEh
		call	sub_23C4F
		mov	ax, 18Fh
		sub	ax, word_3A6C2
		add	ax, 10h
		push	ax
		push	0EEEEh
		call	sub_23C4F

loc_24829:
		mov	ax, word_3A6CA
		add	ax, ax
		cmp	ax, 18h
		jle	short loc_24857
		cmp	word_3A6C2, 0E0h ; '�
		jg	short loc_24857
		mov	ax, word_3A6C2
		add	ax, 0FFE8h
		push	ax
		push	0FFFFh
		call	sub_23C4F
		mov	ax, 18Fh
		sub	ax, word_3A6C2
		add	ax, 18h
		push	ax
		push	0FFFFh
		call	sub_23C4F

loc_24857:
		inc	word_3A6C2
		cmp	word_3A6C2, 0E0h ; '�
		jle	short loc_24871
		mov	word_3A6C2, 0
		mov	word_3A6CA, 0
		jmp	short loc_2489C
; ---------------------------------------------------------------------------

loc_24871:
		push	large 400170h
		push	word_36C26
		call	sub_197E1
		push	3
		push	word_36C2A
		push	word_36C28
		call	sub_197E1
		push	1
		call	sub_E364
		add	sp, 0Eh
		jmp	loc_24796
; ---------------------------------------------------------------------------

loc_2489C:
		inc	word_3A6CA
		cmp	word_3A6CA, 46h	; 'F'
		jnz	short loc_248B0
		mov	word_3A6C4, 0
		jmp	loc_24A9D
; ---------------------------------------------------------------------------

loc_248B0:
		cmp	word_3A6CA, 47h	; 'G'
		jnz	loc_24941
		mov	si, 20h	; ' '
		jmp	short loc_24938
; ---------------------------------------------------------------------------

loc_248BE:
		push	large [dword_3892C]
		movsx	eax, word_3A6C4
		push	eax
		mov	ax, si
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cwde
		pop	edx
		imul	edx, eax
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		imul	edx, eax
		sar	edx, 8
		add	dx, 0B4h ; '?'
		push	dx
		movsx	eax, word_3A6C4
		push	eax
		mov	ax, si
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cwde
		pop	edx
		imul	edx, eax
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+87Ah]
		imul	edx, eax
		sar	edx, 8
		add	dx, 130h
		push	dx
		call	sub_1156E
		add	sp, 8
		inc	si

loc_24938:
		cmp	si, 0A0h ; '?'
		jl	short loc_248BE
		jmp	loc_24A9D
; ---------------------------------------------------------------------------

loc_24941:
		cmp	word_3A6CA, 47h	; 'G'
		jle	loc_24A9D
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_24A9D
		mov	si, 20h	; ' '
		jmp	short loc_249D8
; ---------------------------------------------------------------------------

loc_2495E:
		push	large [dword_3892C]
		movsx	eax, word_3A6C4
		push	eax
		mov	ax, si
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cwde
		pop	edx
		imul	edx, eax
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		imul	edx, eax
		sar	edx, 8
		add	dx, 0B4h ; '?'
		push	dx
		movsx	eax, word_3A6C4
		push	eax
		mov	ax, si
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cwde
		pop	edx
		imul	edx, eax
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+87Ah]
		imul	edx, eax
		sar	edx, 8
		add	dx, 130h
		push	dx
		call	sub_1156E
		add	sp, 8
		inc	si

loc_249D8:
		cmp	si, 0A0h ; '?'
		jl	short loc_2495E
		add	word_3A6C4, 10h
		xor	di, di
		mov	si, 20h	; ' '
		jmp	short loc_24A66
; ---------------------------------------------------------------------------

loc_249EA:
		push	large [dword_3892C]
		movsx	eax, word_3A6C4
		push	eax
		mov	ax, si
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cwde
		pop	edx
		imul	edx, eax
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		imul	edx, eax
		sar	edx, 8
		add	dx, 0B4h ; '?'
		push	dx
		movsx	eax, word_3A6C4
		push	eax
		mov	ax, si
		mov	bx, 20h	; ' '
		cwd
		idiv	bx
		cwde
		pop	edx
		imul	edx, eax
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+87Ah]
		imul	edx, eax
		sar	edx, 8
		add	dx, 130h
		push	dx
		call	sub_1156E
		add	sp, 8
		add	di, ax
		inc	si

loc_24A66:
		cmp	si, 0A0h ; '?'
		jl	loc_249EA
		cmp	di, 80h	; '?'
		jl	short loc_24A9D
		mov	byte_3A3BE, 2
		mov	word_35D16, 0
		mov	word_3A6CA, 0
		push	cs
		call	near ptr sub_232D3
		mov	byte_3A6C6, 0
		push	ds
		push	offset unk_35090
		call	sub_C433
		add	sp, 4
		jmp	loc_24DFB
; ---------------------------------------------------------------------------

loc_24A9D:
		cmp	word_3A6CA, 47h	; 'G'
		jle	short loc_24AFF
		mov	ax, word_3A6CA
		mov	bx, 1Eh
		cwd
		idiv	bx
		or	dx, dx
		jz	short loc_24AFF
		xor	si, si
		jmp	short loc_24AEE
; ---------------------------------------------------------------------------

loc_24AB5:
		mov	al, [si+59F4h]
		cmp	al, [si+6F6h]
		jge	short loc_24AC3
		dec	byte ptr [si+6F6h]

loc_24AC3:
		mov	al, [si+5A00h]
		cmp	al, [si+702h]
		jge	short loc_24AD1
		dec	byte ptr [si+702h]

loc_24AD1:
		mov	al, [si+5A06h]
		cmp	al, [si+708h]
		jge	short loc_24ADF
		dec	byte ptr [si+708h]

loc_24ADF:
		mov	al, [si+5A0Fh]
		cmp	al, [si+711h]
		jge	short loc_24AED
		dec	byte ptr [si+711h]

loc_24AED:
		inc	si

loc_24AEE:
		cmp	si, 3
		jl	short loc_24AB5
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4

loc_24AFF:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jz	loc_2489C
		push	1
		call	sub_E364
		pop	cx
		jmp	loc_2489C
; ---------------------------------------------------------------------------

loc_24B19:
		mov	al, byte_3A3BE
		cbw
		cmp	ax, 2
		jnz	loc_24BA3
		cmp	byte_3A6C6, 0
		jnz	short loc_24B3E
		push	word_3A6CA
		push	word_3A6C8
		call	sub_2191C
		add	sp, 4
		mov	byte_3A6C6, al

loc_24B3E:
		inc	word_3A6CA
		inc	word_3A6C2
		call	sub_23D19
		push	large 0
		push	large 0
		call	sub_235FD
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1B58h
		push	4
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3A6C0
		push	ds
		push	offset word_3A6C2
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6CA, 0
		jnz	short loc_24B82
		inc	word_35D16

loc_24B82:
		cmp	word_3A6C0, 0
		jnz	loc_24DFB
		cmp	word_3A6C8, 0Ah
		jle	short loc_24B9B
		cmp	word_35D16, 6
		jl	loc_24DFB

loc_24B9B:
		mov	byte_3A3BE, 3
		jmp	loc_24CE5
; ---------------------------------------------------------------------------

loc_24BA3:
		mov	al, byte_3A3BE
		cbw
		cmp	ax, 3
		jnz	short loc_24C07
		inc	word_3A6CA
		mov	ax, word_3A6CA
		mov	bx, 14h
		cwd
		idiv	bx
		cmp	dx, 13h
		jnz	short loc_24BDA
		inc	byte_3509F
		dec	byte_350A1
		inc	byte_39B9B
		dec	byte_39B9D
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4

loc_24BDA:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_24DFB
		mov	byte_3A3BE, 4
		mov	word_3A6CA, 0
		mov	word_35D14, 0
		push	ds
		push	offset unk_39B8C
		call	sub_EB10
		add	sp, 4
		push	cs
		call	near ptr sub_232A4
		jmp	loc_24DFB
; ---------------------------------------------------------------------------

loc_24C07:
		mov	al, byte_3A3BE
		cbw
		cmp	ax, 4
		jnz	short loc_24C81
		inc	word_3A6CA
		inc	word_3A6C2
		call	sub_23E6E
		cmp	word_35D14, 0
		jnz	short loc_24C27
		call	sub_23F16
		jmp	short loc_24C2A
; ---------------------------------------------------------------------------

loc_24C27:
		call	sub_23F9D

loc_24C2A:
		mov	word_35D14, ax
		push	large 0
		push	large 0
		call	sub_235FD
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1B58h
		push	4
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3A6C0
		push	ds
		push	offset word_3A6C2
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C0, 0
		jnz	loc_24DFB
		cmp	word_35D14, 2
		jnz	loc_24DFB
		mov	byte_3A3BE, 5
		mov	word_35D14, 0
		mov	word_3A6CA, 0
		jmp	loc_24DFB
; ---------------------------------------------------------------------------

loc_24C81:
		mov	al, byte_3A3BE
		cbw
		cmp	ax, 5
		jnz	short loc_24CFA
		inc	word_3A6CA
		inc	word_3A6C2
		call	sub_24041
		call	sub_240DE
		push	large 0
		push	large 0
		call	sub_235FD
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1B58h
		push	4
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3A6C0
		push	ds
		push	offset word_3A6C2
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C0, 0
		jnz	loc_24DFB
		cmp	word_3A6C8, 6
		jle	short loc_24CE0
		cmp	word_3A6CA, 640h
		jle	loc_24DFB

loc_24CE0:
		mov	byte_3A3BE, 6

loc_24CE5:
		mov	word_3A6CA, 0
		mov	word_3A6C2, 0
		mov	word_35D16, 0
		jmp	loc_24DFB
; ---------------------------------------------------------------------------

loc_24CFA:
		mov	al, byte_3A3BE
		cbw
		cmp	ax, 6
		jnz	loc_24DFB
		inc	word_3A6CA
		inc	word_3A6C2
		call	sub_2414C
		cmp	word_35D14, 0
		jnz	short loc_24D1C
		call	sub_241E7
		jmp	short loc_24D3E
; ---------------------------------------------------------------------------

loc_24D1C:
		cmp	word_35D14, 1
		jnz	short loc_24D28
		call	sub_24316
		jmp	short loc_24D3E
; ---------------------------------------------------------------------------

loc_24D28:
		cmp	word_35D14, 2
		jnz	short loc_24D34
		call	sub_244CE
		jmp	short loc_24D3E
; ---------------------------------------------------------------------------

loc_24D34:
		cmp	word_35D14, 3
		jnz	short loc_24D41
		call	sub_24660

loc_24D3E:
		mov	word_35D14, ax

loc_24D41:
		cmp	word_3A6CA, 0
		jnz	short loc_24D4C
		inc	word_35D16

loc_24D4C:
		cmp	word_35D16, 1Dh
		jle	short loc_24D59
		mov	word_3A6C8, 1

loc_24D59:
		push	large 0
		push	large 0
		call	sub_235FD
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1B58h
		push	4
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3A6C0
		push	ds
		push	offset word_3A6C2
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	short loc_24DFB
		call	sub_12589
		push	ds
		push	offset unk_37635
		call	sub_30DEE
		add	sp, 4
		xor	si, si
		jmp	short loc_24DE9
; ---------------------------------------------------------------------------

loc_24DA3:
		mov	bx, si
		imul	bx, 45h
		cmp	word ptr [bx+483Ah], 0
		jz	short loc_24DE8
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4804h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4800h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+480Ch]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4808h]
		call	sub_F2F5
		add	sp, 8
		mov	bx, si
		imul	bx, 45h
		mov	word ptr [bx+483Ah], 0
		jmp	short $+2

loc_24DE8:
		inc	si

loc_24DE9:
		cmp	si, 4
		jl	short loc_24DA3
		call	sub_12A3A
		push	6
		call	sub_20754
		pop	cx

loc_24DFB:
		pop	di
		pop	si
		leave
		retf
sub_24722	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24DFF	proc far
		push	bp
		mov	bp, sp
		push	seg seg021
		push	offset sub_17096
		push	5
		push	large 5
		push	32h ; '2'
		push	ds
		push	offset word_3A3C9
		call	@_vector_new_$qnvuiuluie ; _vector_new_(void *,uint,ulong,uint,...)
		push	seg seg021
		push	offset sub_17096
		push	5
		push	large 0Ah
		push	32h ; '2'
		push	ds
		push	offset word_3A4C3
		call	@_vector_new_$qnvuiuluie ; _vector_new_(void *,uint,ulong,uint,...)
		add	sp, 20h
		pop	bp
		retf
sub_24DFF	endp

seg034		ends

; ===========================================================================

; Segment type:	Pure code
seg035		segment	byte public 'CODE' use16
		assume cs:seg035
		;org 3
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24E33	proc far

var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6

		enter	0Ah, 0
		push	si
		push	di
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_8], ax
		mov	ax, word ptr dword_3982A
		mov	[bp+var_A], ax
		mov	word ptr dword_3985C, ax
		mov	ax, [bp+var_8]
		mov	word ptr dword_3985C+2,	ax
		cmp	[bp+arg_0], 1
		jnz	short loc_24E5F
		mov	ax, word ptr dword_3982A
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A+2
		jmp	short loc_24E6E
; ---------------------------------------------------------------------------

loc_24E5F:
		cmp	[bp+arg_0], 2
		jnz	short loc_24E71
		mov	ax, word ptr dword_3985C
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3985C+2

loc_24E6E:
		mov	[bp+var_4], ax

loc_24E71:
		mov	[bp+var_6], 0
		push	1
		call	sub_EA3E
		pop	cx
		xor	di, di
		jmp	short loc_24EB1
; ---------------------------------------------------------------------------

loc_24E82:
		xor	si, si
		jmp	short loc_24EAB
; ---------------------------------------------------------------------------

loc_24E86:
		mov	ax, [bp+var_6]
		add	ax, 80h	; '?'
		push	ax
		mov	ax, di
		shl	ax, 5
		add	ax, [bp+var_4]
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		push	ax
		call	sub_104C2
		add	sp, 6
		inc	[bp+var_6]
		inc	si

loc_24EAB:
		cmp	si, 4
		jl	short loc_24E86
		inc	di

loc_24EB1:
		cmp	di, 3
		jl	short loc_24E82
		push	0
		call	sub_EA3E
		pop	cx
		pop	di
		pop	si
		leave
		retf
sub_24E33	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24EC2	proc far

var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6

		enter	0Ah, 0
		push	si
		push	di
		mov	[bp+var_6], 0
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_8], ax
		mov	ax, word ptr dword_3982A
		mov	[bp+var_A], ax
		mov	word ptr dword_3985C, ax
		mov	ax, [bp+var_8]
		mov	word ptr dword_3985C+2,	ax
		cmp	[bp+arg_0], 1
		jnz	short loc_24EF3
		mov	ax, word ptr dword_3982A
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A+2
		jmp	short loc_24F02
; ---------------------------------------------------------------------------

loc_24EF3:
		cmp	[bp+arg_0], 2
		jnz	short loc_24F05
		mov	ax, word ptr dword_3985C
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3985C+2

loc_24F02:
		mov	[bp+var_4], ax

loc_24F05:
		xor	di, di
		jmp	short loc_24F38
; ---------------------------------------------------------------------------

loc_24F09:
		xor	si, si
		jmp	short loc_24F32
; ---------------------------------------------------------------------------

loc_24F0D:
		mov	ax, [bp+var_6]
		add	ax, 80h	; '?'
		push	ax
		mov	ax, di
		shl	ax, 5
		add	ax, [bp+var_4]
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		push	ax
		call	sub_108EC
		add	sp, 6
		inc	[bp+var_6]
		inc	si

loc_24F32:
		cmp	si, 4
		jl	short loc_24F0D
		inc	di

loc_24F38:
		cmp	di, 3
		jl	short loc_24F09
		pop	di
		pop	si
		leave
		retf
sub_24EC2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24F41	proc far
		push	bp
		mov	bp, sp
		mov	byte_360CC, 1
		mov	word_386B3, 7
		mov	word_39854, 1
		push	0
		push	ds
		push	offset aBoss5_bos ; "boss5.bos"
		push	ds
		push	offset dword_3982A
		call	sub_1568F
		mov	word_39854, 0
		mov	word_39886, 1
		push	1
		push	ds
		push	offset aBoss5_2_bos ; "boss5_2.bos"
		push	ds
		push	offset dword_3985C
		call	sub_1568F
		mov	word_39886, 0
		mov	word_398B8, 1
		push	2
		push	ds
		push	offset aBoss5_3_bos ; "boss5_3.bos"
		push	ds
		push	offset dword_3988E
		call	sub_1568F
		mov	word_398B8, 0
		push	ds
		push	offset aBoss5_gr_grc ; "boss5_gr.grc"
		push	0
		call	sub_1744B
		push	large 0C0002h
		call	sub_10814
		push	ds
		push	offset aBoss3_m_ptn_1 ;	"boss3_m.ptn"
		push	3
		call	sub_10888
		mov	byte_3A1B2, 0C0h ; '?'
		call	sub_232A4
		nop
		push	cs
		call	near ptr sub_24FE0
		push	large 700FFh
		call	sub_22264
		add	sp, 32h
		pop	bp
		retf
sub_24F41	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_24FE0	proc far
		push	bp
		mov	bp, sp
		push	si
		push	di
		push	large 1300040h
		push	large 2E00000h
		push	large 300060h
		push	100h
		push	ds
		push	offset dword_3982A
		call	sub_166D2
		push	large 1300040h
		push	large 2E00000h
		push	large 300060h
		push	100h
		push	ds
		push	offset dword_3985C
		call	sub_166D2
		add	sp, 24h
		push	large 1300040h
		push	large 2E00000h
		push	large 300060h
		push	100h
		push	ds
		push	offset dword_3988E
		call	sub_166D2
		add	sp, 12h
		mov	word_3983E, 20h	; ' '
		mov	word_39840, 60h	; '`'
		mov	word_39842, 0Ch
		mov	word_39844, 40h	; '@'
		mov	word_398A2, 8
		mov	word_398A4, 28h	; '('
		mov	word_398A6, 8
		mov	word_398A8, 18h
		mov	byte_3A6CE, 0
		mov	word_3A6CA, 0
		mov	word_3A6C8, 0Eh
		mov	word_3A1E5, 0Ah
		mov	word_3A1E7, 6
		mov	eax, dword_36C16
		mov	random_seed, eax
		xor	si, si
		jmp	short loc_250B3
; ---------------------------------------------------------------------------

loc_2509E:
		xor	di, di
		jmp	short loc_250AD
; ---------------------------------------------------------------------------

loc_250A2:
		mov	bx, si
		imul	bx, 3
		mov	byte ptr [bx+di+5414h],	0
		inc	di

loc_250AD:
		cmp	di, 3
		jl	short loc_250A2
		inc	si

loc_250B3:
		cmp	si, 10h
		jl	short loc_2509E
		pop	di
		pop	si
		pop	bp
		retf
sub_24FE0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_250BC	proc far
		push	bp
		mov	bp, sp
		push	0
		call	sub_169CB
		push	1
		call	sub_169CB
		push	2
		call	sub_169CB
		push	0
		call	sub_17682
		push	2
		call	sub_108AB
		push	3
		call	sub_108AB
		add	sp, 0Ch
		pop	bp
		retf
sub_250BC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_250EE	proc far

var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  6
arg_2		= word ptr  8

		enter	8, 0
		push	si
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_2], ax
		mov	ax, word ptr dword_3982A
		mov	[bp+var_4], ax
		mov	word ptr dword_3985C, ax
		mov	ax, [bp+var_2]
		mov	word ptr dword_3985C+2,	ax
		cmp	word_3A6CA, 14h
		jnz	short loc_25150
		push	1
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		push	0
		call	sub_EA3E
		add	sp, 6
		mov	word_39856, 0
		mov	word_3984E, 2

loc_25132:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 0Ch
		mov	word_39852, 1
		jmp	loc_25293
; ---------------------------------------------------------------------------

loc_25150:
		cmp	word_3A6CA, 1Ch
		jnz	short loc_2516C
		push	1
		push	cs
		call	near ptr sub_24EC2
		pop	cx
		mov	word_39856, 0
		mov	word_3984E, 3
		jmp	short loc_25132
; ---------------------------------------------------------------------------

loc_2516C:
		cmp	word_3A6CA, 24h	; '$'
		jnz	short loc_2517B
		mov	word_39852, 1
		jmp	short loc_251C7
; ---------------------------------------------------------------------------

loc_2517B:
		cmp	word_3A6CA, 2Ch	; ','
		jnz	short loc_2519E
		mov	word_39852, 1
		push	large 600080h
		push	large [dword_3982A]
		call	sub_10433
		add	sp, 8
		jmp	loc_25293
; ---------------------------------------------------------------------------

loc_2519E:
		cmp	word_3A6CA, 34h	; '4'
		jnz	short loc_251DD
		mov	word_39852, 1
		mov	ax, [bp+arg_2]
		mov	[bp+var_6], ax
		mov	ax, [bp+arg_0]
		mov	[bp+var_8], ax
		mov	word ptr dword_3982A, ax
		mov	ax, [bp+var_6]
		mov	word ptr dword_3982A+2,	ax
		push	1
		push	cs
		call	near ptr sub_24E33
		pop	cx

loc_251C7:
		push	1
		push	cs
		call	near ptr sub_24EC2
		pop	cx
		mov	word_39856, 0
		mov	word_3984E, 4
		jmp	loc_25269
; ---------------------------------------------------------------------------

loc_251DD:
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_251FF
		mov	word_39852, 1
		push	1
		push	cs
		call	near ptr sub_24EC2
		pop	cx
		mov	word_39856, 0
		mov	word_3984E, 3
		jmp	short loc_25269
; ---------------------------------------------------------------------------

loc_251FF:
		cmp	word_3A6CA, 44h	; 'D'
		jnz	short loc_25221
		mov	word_39852, 1
		push	1
		push	cs
		call	near ptr sub_24EC2
		pop	cx
		mov	word_39856, 0
		mov	word_3984E, 2
		jmp	short loc_25269
; ---------------------------------------------------------------------------

loc_25221:
		cmp	word_3A6CA, 4Ch	; 'L'
		jnz	short loc_25280
		mov	word_39852, 0
		push	1
		call	sub_EA3E
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		add	sp, 10h
		mov	word_39856, 0
		mov	word_3984E, 0

loc_25269:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 0Ch
		jmp	short loc_25293
; ---------------------------------------------------------------------------

loc_25280:
		cmp	word_3A6CA, 50h	; 'P'
		jle	short loc_25293
		mov	word_3A6CA, 0
		mov	ax, 1
		jmp	loc_2539F
; ---------------------------------------------------------------------------

loc_25293:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2539D
		xor	si, si
		jmp	loc_25396
; ---------------------------------------------------------------------------

loc_252A7:
		cmp	word_3A6CA, 4
		jle	short loc_252CC
		push	large 80010h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D39h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D2Fh]
		call	sub_10433
		add	sp, 8

loc_252CC:
		cmp	word_3A6CA, 28h	; '('
		jl	short loc_252DA
		cmp	word_3A6CA, 34h	; '4'
		jle	short loc_25310

loc_252DA:
		call	IRand
		mov	bx, 0C0h ; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5D2Fh], dx
		call	IRand
		mov	bx, 80h	; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A+2
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5D39h], dx
		jmp	short loc_25374
; ---------------------------------------------------------------------------

loc_25310:
		call	IRand
		mov	bx, 0C0h ; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		sub	dx, [bx+5D2Fh]
		mov	bx, 3
		mov	ax, dx
		cwd
		idiv	bx
		mov	bx, si
		add	bx, bx
		add	ax, [bx+5D2Fh]
		mov	bx, si
		add	bx, bx
		mov	[bx+5D2Fh], ax
		call	IRand
		mov	bx, 80h	; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A+2
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		sub	dx, [bx+5D39h]
		mov	bx, 3
		mov	ax, dx
		cwd
		idiv	bx
		mov	bx, si
		add	bx, bx
		add	ax, [bx+5D39h]
		mov	bx, si
		add	bx, bx
		mov	[bx+5D39h], ax

loc_25374:
		cmp	word_3A6CA, 44h	; 'D'
		jge	short loc_25395
		push	2
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D39h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D2Fh]
		call	sub_177A5
		add	sp, 6

loc_25395:
		inc	si

loc_25396:
		cmp	si, 5
		jl	loc_252A7

loc_2539D:
		xor	ax, ax

loc_2539F:
		pop	si
		leave
		retf
sub_250EE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_253A2	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h

		push	bp
		mov	bp, sp
		mov	dx, [bp+arg_6]
		cmp	byte_34A30, 0
		jnz	short loc_253B4
		mov	ax, [bp+arg_4]
		jmp	short loc_253DF
; ---------------------------------------------------------------------------

loc_253B4:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_253C1
		mov	ax, dx
		jmp	short loc_253DF
; ---------------------------------------------------------------------------

loc_253C1:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_253CF
		mov	ax, [bp+arg_8]
		jmp	short loc_253DF
; ---------------------------------------------------------------------------

loc_253CF:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_253DD
		mov	ax, [bp+arg_A]
		jmp	short loc_253DF
; ---------------------------------------------------------------------------

loc_253DD:
		mov	ax, dx

loc_253DF:
		les	bx, [bp+arg_0]
		mov	es:[bx], ax
		pop	bp
		retf
sub_253A2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_253E7	proc far

var_12		= word ptr -12h
var_10		= qword	ptr -10h
var_8		= qword	ptr -8

		enter	12h, 0
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2546B
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	word_3A6E5, dx
		push	1
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		mov	word_39856, 0
		mov	word_3984E, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		mov	word_39856, 0
		mov	word_3984E, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 1Eh
		push	large 41003Ch
		push	large 370032h
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		jmp	loc_255B1
; ---------------------------------------------------------------------------

loc_2546B:
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_254A0
		push	0FFh
		push	0
		push	2
		push	large 40020h
		push	20h ; ' '
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 10h
		mov	word_3A6E3, 20h	; ' '
		jmp	loc_255B4
; ---------------------------------------------------------------------------

loc_254A0:
		cmp	word_3A6CA, 78h	; 'x'
		jge	loc_25528
		cmp	word_3A6CA, 3Ch	; '<'
		jle	short loc_25528
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_25528
		push	0FFh
		push	0
		push	2
		push	word_3A6E3
		push	word_3A6E3
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		add	word_3A6E3, 8
		push	0FFh
		push	0
		cmp	word_3A6CA, 64h	; 'd'
		jge	short loc_254F7
		mov	al, 2
		jmp	short loc_25504
; ---------------------------------------------------------------------------

loc_254F7:
		cmp	word_3A6CA, 6Eh	; 'n'
		jge	short loc_25502
		mov	al, 8
		jmp	short loc_25504
; ---------------------------------------------------------------------------

loc_25502:
		mov	al, 20h	; ' '

loc_25504:
		push	ax
		push	4
		push	word_3A6E3
		push	word_3A6E3
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 10h
		jmp	loc_255B4
; ---------------------------------------------------------------------------

loc_25528:
		cmp	word_3A6CA, 78h	; 'x'
		jnz	short loc_25556
		push	0FFh
		push	0
		push	20h ; ' '
		push	word_3A6E3
		push	word_3A6E3
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		jmp	short loc_255B4
; ---------------------------------------------------------------------------

loc_25556:
		cmp	word_3A6CA, 96h	; '�
		jnz	short loc_255B4
		push	1
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		add	sp, 12h
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D

loc_255B1:
		add	sp, 0Ch

loc_255B4:
		cmp	word_3A6CA, 46h	; 'F'
		jl	loc_256A5
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_256A5
		cmp	word_3A6E5, 0
		jnz	short loc_255E4
		mov	ax, word_3A6CA
		add	ax, 0FFBAh
		cwd
		idiv	bx
		shl	ax, 6
		mov	[bp+var_12], ax
		jmp	short loc_255FB
; ---------------------------------------------------------------------------

loc_255E4:
		mov	ax, word_3A6CA
		add	ax, 0FFBAh
		mov	bx, 0Ah
		cwd
		idiv	bx
		shl	ax, 6
		mov	dx, 280h
		sub	dx, ax
		mov	[bp+var_12], dx

loc_255FB:
		; Hack (fild [bp+var_12])
		db 0cdh
		db 03bh
		db 046h
		db 0eeh
		; Hack (fstp [bp+var_8])
		db 0cdh
		db 039h
		db 05eh
		db 0f8h
		; Hack (wait)
		db 0cdh
		db 03dh
		; Hack (fld flt_35D8D)
		db 0cdh
		db 035h
		db 006h
		db 0edh
		db 013h
		; Hack (fstp [bp+var_10])
		db 0cdh
		db 039h
		db 05eh
		db 0f0h
		push	large 40019h
		push	7
		; Hack (wait)
		db 0cdh
		db 03dh
		push	word_3A6CC
		; Hack (fld [bp+var_10])
		db 0cdh
		db 039h
		db 046h
		db 0f0h
		call	sub_2395
		push	ax
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		call	sub_2395
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		push	ax
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		cwd
		idiv	bx
		imul	dx, 45h
		add	dx, 4800h
		push	ds
		push	dx
		call	sub_1209D
		push	6
		call	sub_125C9
		add	sp, 16h
		cmp	word_3A6E5, 0
		jnz	short loc_2567E
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fcomp flt_35D91)
		db 0cdh
		db 034h
		db 01eh
		db 0f1h
		db 013h
		; Hack (fnstsw [bp+var_12])
		db 0cdh
		db 039h
		db 07eh
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_12]
		sahf
		jnb	short loc_2569B

loc_2567E:
		cmp	word_3A6E5, 1
		jnz	short loc_256A5
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (fcompp)
		db 0cdh
		db 03ah
		db 0d9h
		; Hack (fnstsw [bp+var_12])
		db 0cdh
		db 039h
		db 07eh
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_12]
		sahf
		jb	short loc_256A5

loc_2569B:
		mov	word_3A6CA, 0
		xor	ax, ax
		leave
		retf
; ---------------------------------------------------------------------------

loc_256A5:
		mov	ax, 1
		leave
		retf
sub_253E7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_256AA	proc far

var_1E		= qword	ptr -1Eh
var_16		= qword	ptr -16h
var_A		= word ptr -0Ah
var_7		= word ptr -7
var_4		= word ptr -4
var_2		= word ptr -2

		enter	0Ah, 0
		push	si
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_25726
		push	1
		call	sub_EA3E
		pop	cx
		push	1
		push	cs
		call	near ptr sub_24EC2
		pop	cx
		mov	word_39856, 0
		mov	word_3984E, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 0Ch
		push	0
		call	sub_EA3E
		pop	cx
		mov	word_39856, 0
		mov	word_3984E, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 0Ch
		push	large 1D0019h
		push	large 15000Fh
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		add	sp, 0Ch

loc_25726:
		cmp	word_3A6CA, 3Ch	; '<'
		jle	loc_257C3
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_257C3
		call	IRand
		mov	bx, 5
		cwd
		idiv	bx
		mov	si, dx
		call	IRand
		cwd
		idiv	word_3A6CC
		mov	ax, word_3A6CC
		dec	ax
		push	dx
		cwd
		sub	ax, dx
		sar	ax, 1
		pop	dx
		sub	dl, al
		add	dl, 40h	; '@'
		mov	byte ptr [bp+var_7], dl
		push	[bp+var_7]
		push	7
		push	ss
		lea	ax, [bp+var_7+1]
		push	ax
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_12053
		add	sp, 0Ch
		push	0		; char
		mov	ax, [bp+var_7+1]
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_16])
		db 0cdh
		db 039h
		db 05eh
		db 0eah
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_4]
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_1E])
		db 0cdh
		db 039h
		db 05eh
		db 0e2h
		mov	bx, si
		add	bx, bx
		; Hack (wait)
		db 0cdh
		db 03dh
		push	word ptr [bx+5D51h] ; int
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D47h] ; int
		push	ds
		push	offset unk_39EC4 ; __int32
		call	sub_21C0D
		add	sp, 1Ah

loc_257C3:
		cmp	word_3A6CA, 3Ch	; '<'
		jl	loc_258AA
		cmp	word_3A6CA, 0A0h ; '?'
		jg	loc_258AA
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_258AA
		xor	si, si
		jmp	loc_2589B
; ---------------------------------------------------------------------------

loc_257EA:
		cmp	word_3A6CA, 3Ch	; '<'
		jle	short loc_2580F
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D51h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D47h]
		call	sub_10433
		add	sp, 8

loc_2580F:
		mov	ax, word_3A6CA
		mov	bx, 10h
		cwd
		idiv	bx
		mov	ax, si
		shl	ax, 2
		push	dx
		cwd
		idiv	bx
		pop	ax
		cmp	ax, dx
		jz	short loc_2582D
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_25861

loc_2582D:
		call	IRand
		mov	bx, 0C0h ; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5D47h], dx
		call	IRand
		mov	bx, 80h	; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A+2
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5D51h], dx

loc_25861:
		cmp	word_3A6CA, 0A0h ; '?'
		jge	short loc_2589A
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		push	4
		mov	ax, [bp+var_2]
		add	ax, 4
		push	ax
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D51h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D47h]
		call	sub_1754D
		add	sp, 0Ah

loc_2589A:
		inc	si

loc_2589B:
		cmp	si, 5
		jl	loc_257EA
		push	7
		call	sub_125C9
		pop	cx

loc_258AA:
		cmp	word_3A6CA, 0AAh ; '?'
		jle	short loc_258BC
		mov	word_3A6CA, 0
		xor	ax, ax
		jmp	short loc_258BF
; ---------------------------------------------------------------------------

loc_258BC:
		mov	ax, 2

loc_258BF:
		pop	si
		leave
		retf
sub_256AA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_258C2	proc far

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		push	si
		cmp	word_3A6CA, 0Ah
		jge	short loc_258D4
		mov	word_3A6FB+1, 0

loc_258D4:
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_25947
		push	1
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		mov	word_39856, 0
		mov	word_3984E, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		mov	word_39856, 0
		mov	word_3984E, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		mov	byte ptr word_3A6FB, 0
		push	large 1C0017h
		push	large 1D000Ch
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		add	sp, 2Ah

loc_25947:
		cmp	word_3A6CA, 3Ch	; '<'
		jl	loc_25AED
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_25AED
		cmp	word_3A6FB+1, 0
		jnz	loc_25AED
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_25977
		push	8
		call	sub_125C9
		pop	cx

loc_25977:
		mov	al, byte ptr word_3A6FB
		mov	ah, 0
		mov	[bp+var_6], ax
		; Hack (fild [bp+var_6])
		db 0cdh
		db 03bh
		db 046h
		db 0fah
		; Hack (fadd dbl_35D95)
		db 0cdh
		db 038h
		db 006h
		db 0f5h
		db 013h
		call	sub_2395
		push	ax
		push	word_3A6FB
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		mov	al, byte ptr word_3A6FB
		add	al, 42h	; 'B'
		push	ax
		mov	al, byte ptr word_3A6FB
		add	al, 40h	; '@'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		mov	al, byte ptr word_3A6FB
		add	al, 82h	; '�
		push	ax
		mov	al, byte ptr word_3A6FB
		add	al, 80h	; '?'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 30h
		mov	al, byte ptr word_3A6FB
		add	al, 0C2h ; '?'
		push	ax
		mov	al, byte ptr word_3A6FB
		add	al, 0C0h ; '?'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 10h
		mov	al, byte ptr word_3A6FB
		add	al, 2
		mov	byte ptr word_3A6FB, al
		cmp	byte ptr word_3A6FB, 40h ; '@'
		jb	loc_25C4A
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		push	0FFh
		push	0
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		mov	word_3A6FB+1, 1
		push	1
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		add	sp, 32h
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 0Ch
		jmp	loc_25C4A
; ---------------------------------------------------------------------------

loc_25AED:
		cmp	word_3A6FB+1, 0
		jz	loc_25B99
		cmp	word_3A6FB+1, 28h ; '('
		jge	loc_25B99
		inc	word_3A6FB+1
		mov	ax, word_3A6FB+1
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_25B3E
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		push	0FFh
		push	0
		push	1
		push	4
		jmp	short loc_25B7A
; ---------------------------------------------------------------------------

loc_25B3E:
		mov	ax, word_3A6FB+1
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	loc_25C4A
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		push	0FFh
		push	0
		push	1
		push	7

loc_25B7A:
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 10h
		jmp	loc_25C4A
; ---------------------------------------------------------------------------

loc_25B99:
		cmp	word_3A6FB+1, 0
		jz	loc_25C4A
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		mov	byte ptr word_3A6FB, 0
		xor	si, si
		jmp	short loc_25C35
; ---------------------------------------------------------------------------

loc_25BCE:
		mov	al, byte ptr word_3A6FB
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		mov	[bp+var_2], ax
		mov	al, byte ptr word_3A6FB
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		mov	[bp+var_4], ax
		push	4
		push	word_3A6CC
		push	ax
		push	[bp+var_2]
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		mov	al, byte ptr word_3A6FB
		add	al, 8
		mov	byte ptr word_3A6FB, al
		inc	si

loc_25C35:
		cmp	si, 20h	; ' '
		jl	short loc_25BCE
		mov	word_3A6CA, 0
		mov	word_3A6FB+1, 0
		xor	ax, ax
		jmp	short loc_25C4D
; ---------------------------------------------------------------------------

loc_25C4A:
		mov	ax, 3

loc_25C4D:
		pop	si
		leave
		retf
sub_258C2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_25C50	proc near

var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4
arg_2		= byte ptr  6
arg_4		= byte ptr  8

		enter	8, 0
		mov	al, [bp+arg_4]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	[bp+var_2], ax
		mov	al, [bp+arg_4]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		mov	[bp+var_4], ax
		mov	al, [bp+arg_2]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	[bp+var_6], ax
		mov	al, [bp+arg_2]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		mov	[bp+var_8], ax
		push	[bp+arg_0]
		push	ax
		push	[bp+var_6]
		push	[bp+var_4]
		push	[bp+var_2]
		call	sub_F342
		add	sp, 0Ah
		leave
		retn	6
sub_25C50	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_25CFD	proc near

var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= byte ptr  4
arg_2		= byte ptr  6

		enter	8, 0
		mov	al, [bp+arg_2]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	[bp+var_2], ax
		mov	al, [bp+arg_2]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		mov	[bp+var_4], ax
		mov	al, [bp+arg_0]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	[bp+var_6], ax
		mov	al, [bp+arg_0]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		mov	[bp+var_8], ax
		push	ax
		push	[bp+var_6]
		push	[bp+var_4]
		push	[bp+var_2]
		call	sub_F2F5
		add	sp, 8
		leave
		retn	4
sub_25CFD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_25DA7	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		mov	bx, [bp+arg_0]
		cmp	bx, 3
		ja	short loc_25DDA
		add	bx, bx
		jmp	cs:off_25DDE[bx]

loc_25DB9:
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		mov	ax, dx
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_25DC8:
		push	cs
		call	near ptr sub_253E7
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_25DCE:
		push	cs
		call	near ptr sub_256AA
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_25DD4:
		push	cs
		call	near ptr sub_258C2
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_25DDA:
		xor	ax, ax
		pop	bp
		retf
sub_25DA7	endp

; ---------------------------------------------------------------------------
off_25DDE	dw offset loc_25DB9
		dw offset loc_25DC8
		dw offset loc_25DCE
		dw offset loc_25DD4

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_25DE6	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		push	0C0h ; '?'
		push	16h
		push	si
		call	sub_25C50
		push	0C0h ; '?'
		push	6Ah ; 'j'
		push	si
		call	sub_25C50
		push	16h
		push	6Ah ; 'j'
		push	si
		call	sub_25C50
		push	40h ; '@'
		push	96h ; '�
		push	si
		call	sub_25C50
		push	40h ; '@'
		push	0EAh ; '�
		push	si
		call	sub_25C50
		push	96h ; '�
		push	0EAh ; '�
		push	si
		call	sub_25C50
		pop	si
		pop	bp
		retn	2
sub_25DE6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_25E28	proc near
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 5
		jge	short loc_25E3D
		mov	word_3A6FE+1, 0
		mov	byte ptr word_3A6FE, 0

loc_25E3D:
		cmp	word_3A6CA, 0Ah
		jl	loc_260D8
		cmp	word_3A6CA, 0Ah
		jnz	short loc_25EB1
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		add	sp, 20h
		mov	byte ptr word_3A6FE, 0
		mov	word_3A6FE+1, 0

loc_25EB1:
		cmp	word_3A6CA, 0Ah
		jl	loc_25FED
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_25FED
		cmp	word_3A6FE+1, 0
		jnz	loc_25FED
		cmp	word_3A6CA, 0Ah
		jnz	short loc_25EE1
		push	8
		call	sub_125C9
		pop	cx

loc_25EE1:
		mov	al, byte ptr word_3A6FE
		add	al, 2
		push	ax
		push	word_3A6FE
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		mov	al, byte ptr word_3A6FE
		add	al, 42h	; 'B'
		push	ax
		mov	al, byte ptr word_3A6FE
		add	al, 40h	; '@'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		mov	al, byte ptr word_3A6FE
		add	al, 82h	; '�
		push	ax
		mov	al, byte ptr word_3A6FE
		add	al, 80h	; '?'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 30h
		mov	al, byte ptr word_3A6FE
		add	al, 0C2h ; '?'
		push	ax
		mov	al, byte ptr word_3A6FE
		add	al, 0C0h ; '?'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 10h
		mov	al, byte ptr word_3A6FE
		add	al, 2
		mov	byte ptr word_3A6FE, al
		cmp	byte ptr word_3A6FE, 40h ; '@'
		jb	loc_260D8
		mov	word_3A6FE+1, 1
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		push	0FFh
		push	0
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 1Eh
		jmp	loc_260D8
; ---------------------------------------------------------------------------

loc_25FED:
		cmp	byte ptr word_3A6FE, 40h ; '@'
		jb	loc_260D8
		inc	word_3A6FE+1
		cmp	word_3A6FE+1, 0Ah
		jnz	short loc_26006
		push	7
		call	sub_25DE6

loc_26006:
		cmp	word_3A6FE+1, 14h
		jle	short loc_26029
		mov	ax, word_3A6FE+1
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26029
		push	bx
		call	sub_25DE6
		push	0FFh
		push	0
		push	1
		push	4
		jmp	short loc_2604C
; ---------------------------------------------------------------------------

loc_26029:
		cmp	word_3A6FE+1, 14h
		jle	short loc_26068
		mov	ax, word_3A6FE+1
		mov	bx, 4
		cwd
		idiv	bx
		cmp	dx, 2
		jnz	short loc_26068
		push	7
		call	sub_25DE6
		push	0FFh
		push	0
		push	1
		push	7

loc_2604C:
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 10h

loc_26068:
		cmp	word_3A6FE+1, 3Ch ; '<'
		jle	short loc_260D8
		push	0C0h ; '?'
		push	16h
		call	sub_25CFD
		push	0C0h ; '?'
		push	6Ah ; 'j'
		call	sub_25CFD
		push	16h
		push	6Ah ; 'j'
		call	sub_25CFD
		push	40h ; '@'
		push	96h ; '�
		call	sub_25CFD
		push	40h ; '@'
		push	0EAh ; '�
		call	sub_25CFD
		push	96h ; '�
		push	0EAh ; '�
		call	sub_25CFD
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		mov	word_3A6CA, 0
		mov	byte ptr word_3A6FE, 0
		mov	word_3A6FE+1, 0
		mov	ax, 1
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_260D8:
		xor	ax, ax
		pop	bp
		retn
sub_25E28	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_260DC	proc far
		push	bp
		mov	bp, sp
		push	si
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26136
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		add	sp, 14h
		mov	word_39888, 0
		mov	word_39880, 1
		jmp	short loc_2617F
; ---------------------------------------------------------------------------

loc_26136:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	short loc_26194
		push	1
		call	sub_EA3E
		mov	word_39888, 0
		mov	word_39880, 2
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		add	sp, 10h
		mov	word_39888, 0
		mov	word_39880, 2

loc_2617F:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		add	sp, 0Ch

loc_26194:
		cmp	word_3A6CA, 0Ah
		jnz	short loc_261ED
		push	large 140012h
		push	large 10000Eh
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		add	sp, 0Ch
		xor	si, si
		jmp	short loc_261E4
; ---------------------------------------------------------------------------

loc_261B6:
		push	large 0
		push	large 0
		push	30h ; '0'
		mov	ax, 100h
		cwd
		idiv	word_3A6CC
		imul	si
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_261E4:
		cmp	si, word_3A6CC
		jl	short loc_261B6
		jmp	loc_2631C
; ---------------------------------------------------------------------------

loc_261ED:
		cmp	word_3A6CA, 10h
		jnz	short loc_26231
		xor	si, si
		jmp	short loc_26228
; ---------------------------------------------------------------------------

loc_261F8:
		push	large 0
		push	large 0
		push	36h ; '6'
		mov	ax, 100h
		cwd
		idiv	word_3A6CC
		imul	si
		add	al, 2
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_26228:
		cmp	si, word_3A6CC
		jl	short loc_261F8
		jmp	loc_2631C
; ---------------------------------------------------------------------------

loc_26231:
		cmp	word_3A6CA, 18h
		jnz	short loc_26275
		xor	si, si
		jmp	short loc_2626C
; ---------------------------------------------------------------------------

loc_2623C:
		push	large 0
		push	large 0
		push	40h ; '@'
		mov	ax, 100h
		cwd
		idiv	word_3A6CC
		imul	si
		add	al, 4
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_2626C:
		cmp	si, word_3A6CC
		jl	short loc_2623C
		jmp	loc_2631C
; ---------------------------------------------------------------------------

loc_26275:
		cmp	word_3A6CA, 20h	; ' '
		jnz	short loc_262B8
		xor	si, si
		jmp	short loc_262B0
; ---------------------------------------------------------------------------

loc_26280:
		push	large 0
		push	large 0
		push	48h ; 'H'
		mov	ax, 100h
		cwd
		idiv	word_3A6CC
		imul	si
		add	al, 6
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_262B0:
		cmp	si, word_3A6CC
		jl	short loc_26280
		jmp	short loc_2631C
; ---------------------------------------------------------------------------

loc_262B8:
		cmp	word_3A6CA, 28h	; '('
		jnz	short loc_262FB
		xor	si, si
		jmp	short loc_262F3
; ---------------------------------------------------------------------------

loc_262C3:
		push	large 0
		push	large 0
		push	50h ; 'P'
		mov	ax, 100h
		cwd
		idiv	word_3A6CC
		imul	si
		add	al, 8
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_262F3:
		cmp	si, word_3A6CC
		jl	short loc_262C3
		jmp	short loc_2631C
; ---------------------------------------------------------------------------

loc_262FB:
		cmp	word_3A6CA, 3Ch	; '<'
		jle	short loc_2631C
		mov	word_3A6CA, 0
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		add	sp, 4
		xor	ax, ax
		jmp	short loc_2631F
; ---------------------------------------------------------------------------

loc_2631C:
		mov	ax, 1

loc_2631F:
		pop	si
		pop	bp
		retf
sub_260DC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26322	proc far

var_3		= word ptr -3

		enter	4, 0
		push	si
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2637D
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		add	sp, 14h
		mov	word_39888, 0
		mov	word_39880, 1
		jmp	short loc_263C6
; ---------------------------------------------------------------------------

loc_2637D:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	short loc_263DB
		push	1
		call	sub_EA3E
		mov	word_39888, 0
		mov	word_39880, 2
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		add	sp, 10h
		mov	word_39888, 0
		mov	word_39880, 2

loc_263C6:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		add	sp, 0Ch

loc_263DB:
		cmp	word_3A6CA, 64h	; 'd'
		jg	loc_264AC
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_264AC
		cmp	word ptr dword_3982A, 100h
		jge	short loc_26407
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		push	ax
		mov	ax, 260h
		jmp	short loc_26413
; ---------------------------------------------------------------------------

loc_26407:
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		xor	ax, ax

loc_26413:
		sub	ax, word ptr dword_3982A
		mov	bx, 0Ah
		cwd
		idiv	bx
		mov	dx, ax
		pop	ax
		imul	dx
		add	ax, word ptr dword_3982A
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		add	ax, ax
		mov	bx, ax
		pop	ax
		mov	[bx+5D5Fh], ax
		call	IRand
		mov	bx, 0C8h ; '?'
		cwd
		idiv	bx
		add	dx, 0C8h ; '?'
		sub	dx, word ptr dword_3982A+2
		mov	bx, 0Ah
		mov	ax, dx
		cwd
		idiv	bx
		push	ax
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		mov	dx, ax
		pop	ax
		imul	dx
		add	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		add	ax, ax
		mov	bx, ax
		pop	ax
		mov	[bx+5D73h], ax
		xor	si, si
		jmp	short loc_2649C
; ---------------------------------------------------------------------------

loc_2647B:
		push	large 40003h
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D75h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D61h]
		call	sub_1754D
		add	sp, 0Ah
		inc	si

loc_2649C:
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		cmp	ax, si
		jg	short loc_2647B
		jmp	loc_26617
; ---------------------------------------------------------------------------

loc_264AC:
		cmp	word_3A6CA, 64h	; 'd'
		jle	loc_26605
		cmp	word_3A6CA, 0E6h ; '�
		jg	loc_26605
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_26605
		cmp	word_3A6CA, 0C8h ; '?'
		jg	loc_265C5
		push	7
		call	sub_125C9
		push	large 40004h
		push	0
		mov	ax, word_3A6CA
		add	ax, 0FF9Ch
		mov	bx, 0Ah
		cwd
		idiv	bx
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+5D73h]
		mov	ax, word_3A6CA
		add	ax, 0FF9Ch
		mov	bx, 0Ah
		cwd
		idiv	bx
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+5D5Fh]
		call	sub_1754D
		add	sp, 0Ch
		mov	ax, word_3A6CA
		add	ax, 0FF9Ch
		mov	bx, 0Ah
		cwd
		idiv	bx
		mov	si, ax
		jmp	short loc_26548
; ---------------------------------------------------------------------------

loc_26527:
		push	large 40003h
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D75h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D61h]
		call	sub_1754D
		add	sp, 0Ah
		inc	si

loc_26548:
		cmp	si, 0Ah
		jl	short loc_26527
		push	large 0D0009h
		push	large 70005h
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		add	sp, 0Ch
		xor	si, si
		jmp	short loc_265BF
; ---------------------------------------------------------------------------

loc_26568:
		call	IRand
		and	al, 7Fh
		mov	byte ptr [bp+var_3], al
		call	IRand
		add	ax, 18h
		and	ax, 3Fh
		mov	[bp+var_3+1], ax
		push	large 0
		push	large 0
		push	ax
		push	[bp+var_3]
		mov	ax, word_3A6CA
		add	ax, 0FF9Ch
		mov	bx, 0Ah
		cwd
		idiv	bx
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+5D73h]
		mov	ax, word_3A6CA
		add	ax, 0FF9Ch
		mov	bx, 0Ah
		cwd
		idiv	bx
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+5D5Fh]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_265BF:
		cmp	si, word_3A6CC
		jl	short loc_26568

loc_265C5:
		cmp	word_3A6CA, 82h	; '�
		jle	short loc_26617
		push	large 200030h
		mov	ax, word_3A6CA
		add	ax, 0FF7Eh
		mov	bx, 0Ah
		cwd
		idiv	bx
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+5D73h]
		mov	ax, word_3A6CA
		add	ax, 0FF7Eh
		mov	bx, 0Ah
		cwd
		idiv	bx
		add	ax, ax
		mov	bx, ax
		push	word ptr [bx+5D5Fh]
		call	sub_10433
		add	sp, 8
		jmp	short loc_26617
; ---------------------------------------------------------------------------

loc_26605:
		cmp	word_3A6CA, 0FAh ; '�
		jle	short loc_26617
		mov	word_3A6CA, 0
		xor	ax, ax
		jmp	short loc_2661A
; ---------------------------------------------------------------------------

loc_26617:
		mov	ax, 2

loc_2661A:
		pop	si
		leave
		retf
sub_26322	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2661D	proc far

var_4		= byte ptr -4
var_3		= word ptr -3

		enter	4, 0
		push	si
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26678
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		add	sp, 14h
		mov	word_39888, 0
		mov	word_39880, 1
		jmp	short loc_266C1
; ---------------------------------------------------------------------------

loc_26678:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	short loc_266D6
		push	1
		call	sub_EA3E
		mov	word_39888, 0
		mov	word_39880, 2
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		add	sp, 10h
		mov	word_39888, 0
		mov	word_39880, 2

loc_266C1:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		add	sp, 0Ch

loc_266D6:
		cmp	word_3A6CA, 1Eh
		jnz	short loc_266F4
		push	large 20002h
		push	large 30006h
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		add	sp, 0Ch

loc_266F4:
		cmp	word_3A6CA, 3Ch	; '<'
		jle	short loc_2672E
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A6CC
		or	dx, dx
		jnz	short loc_2672E
		cmp	word_3A6CA, 78h	; 'x'
		jge	short loc_2672E
		call	IRand
		mov	bx, 5
		cwd
		idiv	bx
		mov	si, dx
		call	IRand
		mov	bx, 15h
		cwd
		idiv	bx
		add	dl, 36h	; '6'
		mov	byte ptr [bp+var_3], dl
		jmp	short loc_26791
; ---------------------------------------------------------------------------

loc_2672E:
		cmp	word_3A6CA, 78h	; 'x'
		jl	loc_267B8
		cmp	word_3A6CA, 0C8h ; '?'
		jge	short loc_267B8
		call	IRand
		mov	bx, 5
		cwd
		idiv	bx
		mov	si, dx
		call	IRand
		mov	bx, 15h
		cwd
		idiv	bx
		add	dl, 36h	; '6'
		mov	byte ptr [bp+var_3], dl
		call	IRand
		test	al, 1
		jz	short loc_2676D
		mov	al, byte ptr word_3A6CA
		add	al, 88h	; '�
		jmp	short loc_26774
; ---------------------------------------------------------------------------

loc_2676D:
		mov	al, byte ptr word_3A6CA
		add	al, 88h	; '�
		neg	al

loc_26774:
		mov	[bp+var_4], al
		mov	al, byte ptr [bp+var_3]
		mov	ah, 0
		mov	dl, [bp+var_4]
		mov	dh, 0
		push	ax
		mov	ax, dx
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	dx, ax
		pop	ax
		imul	dx
		mov	byte ptr [bp+var_3], al

loc_26791:
		push	large 0
		push	large 0
		push	60h ; '`'
		push	[bp+var_3]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D93h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D89h]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h

loc_267B8:
		cmp	word_3A6CA, 3Ch	; '<'
		jl	loc_2689F
		cmp	word_3A6CA, 0C8h ; '?'
		jg	loc_2689F
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2689F
		xor	si, si
		jmp	loc_26890
; ---------------------------------------------------------------------------

loc_267DF:
		cmp	word_3A6CA, 3Ch	; '<'
		jle	short loc_26804
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D93h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D89h]
		call	sub_10433
		add	sp, 8

loc_26804:
		mov	ax, word_3A6CA
		mov	bx, 10h
		cwd
		idiv	bx
		mov	ax, si
		shl	ax, 2
		push	dx
		cwd
		idiv	bx
		pop	ax
		cmp	ax, dx
		jz	short loc_26822
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_26856

loc_26822:
		call	IRand
		mov	bx, 0C0h ; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5D89h], dx
		call	IRand
		mov	bx, 80h	; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A+2
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5D93h], dx

loc_26856:
		cmp	word_3A6CA, 0C8h ; '?'
		jge	short loc_2688F
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	[bp+var_3+1], dx
		push	4
		mov	ax, [bp+var_3+1]
		add	ax, 4
		push	ax
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D93h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D89h]
		call	sub_1754D
		add	sp, 0Ah

loc_2688F:
		inc	si

loc_26890:
		cmp	si, 5
		jl	loc_267DF
		push	7
		call	sub_125C9
		pop	cx

loc_2689F:
		cmp	word_3A6CA, 0DCh ; '?'
		jle	short loc_268B1
		mov	word_3A6CA, 0
		xor	ax, ax
		jmp	short loc_268B4
; ---------------------------------------------------------------------------

loc_268B1:
		mov	ax, 3

loc_268B4:
		pop	si
		leave
		retf
sub_2661D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_268B7	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	si, 63h	; 'c'
		jnz	short loc_268CB
		mov	word_35D42, 0
		jmp	short loc_26933
; ---------------------------------------------------------------------------

loc_268CB:
		mov	bx, si
		cmp	bx, 3
		ja	short loc_26933
		add	bx, bx
		jmp	cs:off_26938[bx]

loc_268D9:
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		mov	ax, dx
		jmp	short loc_26935
; ---------------------------------------------------------------------------

loc_268E8:
		cmp	word_35D42, 0
		jnz	short loc_268FA
		call	sub_25E28
		mov	word_35D42, ax
		mov	ax, 1
		jmp	short loc_26935
; ---------------------------------------------------------------------------

loc_268FA:
		push	cs
		call	near ptr sub_260DC
		jmp	short loc_2692E
; ---------------------------------------------------------------------------

loc_26900:
		cmp	word_35D42, 0
		jnz	short loc_26912
		call	sub_25E28
		mov	word_35D42, ax
		mov	ax, 2
		jmp	short loc_26935
; ---------------------------------------------------------------------------

loc_26912:
		push	cs
		call	near ptr sub_26322
		jmp	short loc_2692E
; ---------------------------------------------------------------------------

loc_26918:
		cmp	word_35D42, 0
		jnz	short loc_2692A
		call	sub_25E28
		mov	word_35D42, ax
		mov	ax, 3
		jmp	short loc_26935
; ---------------------------------------------------------------------------

loc_2692A:
		push	cs
		call	near ptr sub_2661D

loc_2692E:
		mov	word_35D42, ax
		jmp	short loc_26935
; ---------------------------------------------------------------------------

loc_26933:
		xor	ax, ax

loc_26935:
		pop	si
		pop	bp
		retf
sub_268B7	endp

; ---------------------------------------------------------------------------
off_26938	dw offset loc_268D9
		dw offset loc_268E8
		dw offset loc_26900
		dw offset loc_26918

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26940	proc far

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		push	si
		cmp	word_3A6CA, 14h
		jnz	short loc_269A5
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		add	sp, 20h

loc_269A5:
		cmp	word_3A6CA, 14h
		jl	loc_26A94
		cmp	word_3A6CA, 64h	; 'd'
		jg	loc_26A94
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_26A94
		xor	si, si
		jmp	loc_26A85
; ---------------------------------------------------------------------------

loc_269CB:
		cmp	word_3A6CA, 14h
		jle	short loc_269F0
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5DA7h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D9Dh]
		call	sub_10433
		add	sp, 8

loc_269F0:
		mov	ax, word_3A6CA
		mov	bx, 10h
		cwd
		idiv	bx
		mov	ax, si
		shl	ax, 2
		push	dx
		cwd
		idiv	bx
		pop	ax
		cmp	ax, dx
		jz	short loc_26A0E
		cmp	word_3A6CA, 14h
		jnz	short loc_26A42

loc_26A0E:
		call	IRand
		mov	bx, 0C0h ; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5D9Dh], dx
		call	IRand
		mov	bx, 80h	; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3982A+2
		add	dx, 0FFE0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5DA7h], dx

loc_26A42:
		cmp	word_3A6CA, 64h	; 'd'
		jge	short loc_26A84
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		call	IRand
		mov	bx, 10h
		cwd
		idiv	bx
		push	dx
		mov	ax, [bp+var_2]
		add	ax, 4
		push	ax
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5DA7h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5D9Dh]
		call	sub_1754D
		add	sp, 0Ah

loc_26A84:
		inc	si

loc_26A85:
		cmp	si, 5
		jl	loc_269CB
		push	7
		call	sub_125C9
		pop	cx

loc_26A94:
		cmp	word_3A6CA, 14h
		jl	short loc_26ABF
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26ABF
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		add	dx, dx
		mov	ax, 190h
		sub	ax, dx
		push	ax
		call	sub_11738
		pop	cx

loc_26ABF:
		cmp	word_3A6CA, 64h	; 'd'
		jle	short loc_26B17
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		mov	[bp+var_4], ax
		mov	ax, word ptr dword_3982A
		add	ax, 28h	; '('
		mov	[bp+var_6], ax
		mov	word ptr dword_3988E, ax
		mov	ax, [bp+var_4]
		mov	word ptr dword_3988E+2,	ax
		mov	word_398B2, 0
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		push	190h
		call	sub_11738
		add	sp, 0Ah
		mov	word_3A6CA, 0
		mov	ax, 1
		jmp	short loc_26B19
; ---------------------------------------------------------------------------

loc_26B17:
		xor	ax, ax

loc_26B19:
		pop	si
		leave
		retf
sub_26940	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26B1C	proc far

var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	8, 0
		push	si
		push	di
		cmp	word_3A6CA, 14h
		jl	loc_26C11
		cmp	word_3A6CA, 64h	; 'd'
		jg	loc_26C11
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_26C11
		xor	si, si
		jmp	loc_26C02
; ---------------------------------------------------------------------------

loc_26B48:
		cmp	word_3A6CA, 14h
		jle	short loc_26B6D
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5DBBh]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5DB1h]
		call	sub_10433
		add	sp, 8

loc_26B6D:
		mov	ax, word_3A6CA
		mov	bx, 10h
		cwd
		idiv	bx
		mov	ax, si
		shl	ax, 2
		push	dx
		cwd
		idiv	bx
		pop	ax
		cmp	ax, dx
		jz	short loc_26B8B
		cmp	word_3A6CA, 14h
		jnz	short loc_26BBF

loc_26B8B:
		call	IRand
		mov	bx, 0C0h ; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3988E
		add	dx, 0FFB8h
		mov	bx, si
		add	bx, bx
		mov	[bx+5DB1h], dx
		call	IRand
		mov	bx, 80h	; '?'
		cwd
		idiv	bx
		add	dx, word ptr dword_3988E+2
		add	dx, 0FFD0h
		mov	bx, si
		add	bx, bx
		mov	[bx+5DBBh], dx

loc_26BBF:
		cmp	word_3A6CA, 64h	; 'd'
		jge	short loc_26C01
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		call	IRand
		mov	bx, 10h
		cwd
		idiv	bx
		push	dx
		mov	ax, [bp+var_2]
		add	ax, 4
		push	ax
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5DBBh]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+5DB1h]
		call	sub_1754D
		add	sp, 0Ah

loc_26C01:
		inc	si

loc_26C02:
		cmp	si, 5
		jl	loc_26B48
		push	7
		call	sub_125C9
		pop	cx

loc_26C11:
		cmp	word_3A6CA, 14h
		jl	short loc_26C3C
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26C3C
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		add	dx, dx
		mov	ax, 190h
		sub	ax, dx
		push	ax
		call	sub_11738
		pop	cx

loc_26C3C:
		cmp	word_3A6CA, 64h	; 'd'
		jle	loc_26D0B
		push	large 200030h
		push	large [dword_3988E]
		call	sub_10433
		add	sp, 8
		mov	ax, word ptr dword_3988E
		add	ax, 0FFD8h
		mov	di, ax
		mov	ax, word ptr dword_3988E+2
		add	ax, 0FFE0h
		mov	[bp+var_4], ax
		or	di, di
		jge	short loc_26C71
		xor	di, di
		jmp	short loc_26C7A
; ---------------------------------------------------------------------------

loc_26C71:
		cmp	di, 200h
		jle	short loc_26C7A
		mov	di, 200h

loc_26C7A:
		cmp	[bp+var_4], 40h	; '@'
		jge	short loc_26C85
		mov	[bp+var_4], 40h	; '@'

loc_26C85:
		mov	ax, [bp+var_4]
		mov	[bp+var_6], ax
		mov	[bp+var_8], di
		mov	ax, [bp+var_8]
		mov	word ptr dword_3982A, ax
		mov	ax, [bp+var_6]
		mov	word ptr dword_3982A+2,	ax
		push	1
		push	cs
		call	near ptr sub_24E33
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	190h
		call	sub_11738
		add	sp, 24h
		mov	word_3A6CA, 0
		xor	ax, ax
		jmp	short loc_26D0E
; ---------------------------------------------------------------------------

loc_26D0B:
		mov	ax, 1

loc_26D0E:
		pop	di
		pop	si
		leave
		retf
sub_26B1C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26D12	proc far

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= dword	ptr  6
arg_4		= dword	ptr  0Ah

		enter	6, 0
		cmp	word_3A6CA, 3
		jge	short loc_26D30
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 0
		les	bx, [bp+arg_4]
		mov	word ptr es:[bx], 0
		jmp	loc_26DFE
; ---------------------------------------------------------------------------

loc_26D30:
		cmp	word_3A6CA, 3
		jnz	loc_26DB8

loc_26D39:
		call	IRand
		mov	bx, 200h
		cwd
		idiv	bx
		mov	word_3A765, dx
		call	IRand
		mov	bx, 88h	; '�
		cwd
		idiv	bx
		add	dx, 60h	; '`'
		mov	word_3A767, dx
		mov	ax, word ptr dword_3988E
		sub	ax, word_3A765
		mov	[bp+var_2], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		cmp	ax, 80h	; '?'
		jge	short loc_26D82
		mov	ax, word ptr dword_3988E+2
		sub	ax, word_3A767
		mov	[bp+var_4], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		cmp	ax, 40h	; '@'
		jl	short loc_26D39

loc_26D82:
		push	2
		push	large [bp+arg_4]
		push	large [bp+arg_0]
		push	word_3A767
		push	word_3A765
		push	large [dword_3988E]
		call	sub_11FF0
		add	sp, 12h
		mov	ax, word_3A765
		sub	ax, word ptr dword_3988E
		mov	[bp+var_6], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		cwd
		sub	ax, dx
		sar	ax, 1
		mov	word_3A769, ax

loc_26DB8:
		call	IRand
		mov	bx, 5
		cwd
		idiv	bx
		add	dx, 0FFFEh
		mov	bx, 0Ah
		mov	ax, dx
		cwd
		idiv	bx
		les	bx, [bp+arg_4]
		add	es:[bx], ax
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		cmp	ax, word_3A769
		jl	short loc_26DFE
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 0
		les	bx, [bp+arg_4]
		mov	word ptr es:[bx], 0
		mov	word_3A6CA, 0
		mov	ax, 1
		leave
		retf
; ---------------------------------------------------------------------------

loc_26DFE:
		xor	ax, ax
		leave
		retf
sub_26D12	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26E02	proc far

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_3A6CA
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_26E47
		push	large 14001Ch
		push	large 1B0017h
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	cs
		call	near ptr sub_253A2
		push	38h ; '8'
		push	[bp+var_2]
		mov	ax, word ptr dword_3988E+2
		add	ax, 0Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 14h
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 18h

locret_26E47:
		leave
		retf
sub_26E02	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26E49	proc far
		push	bp
		mov	bp, sp
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26E8A
		call	IRand
		test	al, 1
		jz	short loc_26E6A
		push	large 580016h
		jmp	short loc_26E70
; ---------------------------------------------------------------------------

loc_26E6A:
		push	large 580015h

loc_26E70:
		mov	ax, word ptr dword_3988E+2
		add	ax, 0Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 14h
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_26E8A:
		pop	bp
		retf
sub_26E49	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26E8C	proc far
		push	bp
		mov	bp, sp
		mov	ax, word_3A6CA
		mov	bx, 32h	; '2'
		cwd
		idiv	bx
		cmp	dx, 0Ah
		jge	short loc_26ECA
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26ECA
		push	large 550016h
		mov	ax, word ptr dword_3988E+2
		add	ax, 0Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 14h
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_26ECA:
		mov	ax, word_3A6CA
		mov	bx, 32h	; '2'
		cwd
		idiv	bx
		cmp	dx, 19h
		jl	short loc_26F10
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		cmp	dx, 23h	; '#'
		jge	short loc_26F10
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26F10
		push	large 550018h
		mov	ax, word ptr dword_3988E+2
		add	ax, 0Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 14h
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_26F10:
		pop	bp
		retf
sub_26E8C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26F12	proc far
		push	bp
		mov	bp, sp
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26F4D
		push	large 0
		push	large 10001h
		push	2
		call	IRand
		push	ax
		mov	ax, word ptr dword_3988E+2
		add	ax, 0Ch
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 14h
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h

loc_26F4D:
		pop	bp
		retf
sub_26F12	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_26F4F	proc far

var_1		= byte ptr -1

		enter	2, 0
		push	si
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_26FAA
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		add	sp, 14h
		mov	word_39888, 0
		mov	word_39880, 1
		jmp	short loc_26FF3
; ---------------------------------------------------------------------------

loc_26FAA:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	short loc_27008
		push	1
		call	sub_EA3E
		mov	word_39888, 0
		mov	word_39880, 2
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		add	sp, 10h
		mov	word_39888, 0
		mov	word_39880, 2

loc_26FF3:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		add	sp, 0Ch

loc_27008:
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_27088
		push	large 40003h
		push	large 30002h
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		add	sp, 0Ch
		xor	si, si
		jmp	short loc_27080
; ---------------------------------------------------------------------------

loc_2702A:
		push	large 0
		push	large 0
		mov	ax, si
		add	ax, word_3A6CC
		shl	ax, 4
		push	ax
		push	40h ; '@'
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 38h	; '8'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		mov	ax, si
		add	ax, word_3A6CC
		shl	ax, 4
		push	ax
		push	40h ; '@'
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		inc	si

loc_27080:
		cmp	si, 4
		jl	short loc_2702A
		jmp	loc_271EB
; ---------------------------------------------------------------------------

loc_27088:
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_270F1
		xor	si, si
		jmp	short loc_270E9
; ---------------------------------------------------------------------------

loc_27093:
		push	large 0
		push	large 0
		mov	ax, si
		add	ax, word_3A6CC
		shl	ax, 4
		push	ax
		push	50h ; 'P'
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 38h	; '8'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		mov	ax, si
		add	ax, word_3A6CC
		shl	ax, 4
		push	ax
		push	30h ; '0'
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		inc	si

loc_270E9:
		cmp	si, 4
		jl	short loc_27093
		jmp	loc_271D0
; ---------------------------------------------------------------------------

loc_270F1:
		cmp	word_3A6CA, 46h	; 'F'
		jnz	short loc_27159
		xor	si, si
		jmp	short loc_27152
; ---------------------------------------------------------------------------

loc_270FC:
		push	large 0
		push	large 0
		mov	ax, si
		add	ax, word_3A6CC
		shl	ax, 4
		push	ax
		push	68h ; 'h'
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 38h	; '8'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		mov	ax, si
		add	ax, word_3A6CC
		shl	ax, 4
		push	ax
		push	18h
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		inc	si

loc_27152:
		cmp	si, 4
		jl	short loc_270FC
		jmp	short loc_271D0
; ---------------------------------------------------------------------------

loc_27159:
		cmp	word_3A6CA, 50h	; 'P'
		jnz	short loc_271DA
		mov	[bp+var_1], 0
		xor	si, si
		jmp	short loc_271CB
; ---------------------------------------------------------------------------

loc_27168:
		push	large 0
		push	large 0
		mov	ax, word_3A6CC
		add	ax, 2
		shl	ax, 4
		push	ax
		mov	al, 80h	; '?'
		sub	al, [bp+var_1]
		push	ax
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 38h	; '8'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		mov	ax, word_3A6CC
		add	ax, 2
		shl	ax, 4
		push	ax
		push	word ptr [bp+var_1]
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		mov	al, [bp+var_1]
		add	al, 6
		mov	[bp+var_1], al
		inc	si

loc_271CB:
		cmp	si, 0Ah
		jl	short loc_27168

loc_271D0:
		push	7
		call	sub_125C9
		pop	cx
		jmp	short loc_271EB
; ---------------------------------------------------------------------------

loc_271DA:
		cmp	word_3A6CA, 78h	; 'x'
		jl	short loc_271EB
		mov	word_3A6CA, 0
		xor	ax, ax
		jmp	short loc_271EE
; ---------------------------------------------------------------------------

loc_271EB:
		mov	ax, 1

loc_271EE:
		pop	si
		leave
		retf
sub_26F4F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_271F1	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jge	short loc_27201
		mov	word_3A76B, 0

loc_27201:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_27257
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		add	sp, 14h
		mov	word_39888, 0
		mov	word_39880, 1
		jmp	short loc_272A0
; ---------------------------------------------------------------------------

loc_27257:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	short loc_272B5
		push	1
		call	sub_EA3E
		mov	word_39888, 0
		mov	word_39880, 2
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		add	sp, 10h
		mov	word_39888, 0
		mov	word_39880, 2

loc_272A0:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		add	sp, 0Ch

loc_272B5:
		cmp	word_3A6CA, 3Ch	; '<'
		jl	loc_275EF
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_272E1
		push	large 20002h
		push	large 20004h
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		add	sp, 0Ch
		mov	byte ptr word_3A76F, 0

loc_272E1:
		cmp	word_3A6CA, 3Ch	; '<'
		jl	loc_27464
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_27464
		cmp	word_3A76B, 0
		jnz	loc_27464
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_27317
		push	8
		call	sub_125C9
		pop	cx
		mov	ax, word_36C26
		mov	word_3A76D, ax

loc_27317:
		mov	al, byte ptr word_3A76F
		add	al, 2
		push	ax
		push	word_3A76F
		push	1
		push	large 70080h
		push	large 800180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_1786D
		mov	al, byte ptr word_3A76F
		add	al, 42h	; 'B'
		push	ax
		mov	al, byte ptr word_3A76F
		add	al, 40h	; '@'
		push	ax
		push	1
		push	large 70080h
		push	large 800180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_1786D
		mov	al, byte ptr word_3A76F
		add	al, 82h	; '�
		push	ax
		mov	al, byte ptr word_3A76F
		add	al, 80h	; '?'
		push	ax
		push	1
		push	large 70080h
		push	large 800180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_1786D
		add	sp, 30h
		mov	al, byte ptr word_3A76F
		add	al, 0C2h ; '?'
		push	ax
		mov	al, byte ptr word_3A76F
		add	al, 0C0h ; '?'
		push	ax
		push	1
		push	large 70080h
		push	large 800180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_1786D
		add	sp, 10h
		mov	al, byte ptr word_3A76F
		add	al, 2
		mov	byte ptr word_3A76F, al
		cmp	byte ptr word_3A76F, 40h ; '@'
		jb	loc_275EF
		push	0FFh
		push	0
		push	1
		push	large 800080h
		push	180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_17956
		push	0FFh
		push	0
		push	1
		push	large 70080h
		push	large 800180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_1786D
		mov	word_3A76B, 1
		push	1
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		add	sp, 32h
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D

loc_2745E:
		add	sp, 0Ch
		jmp	loc_275EF
; ---------------------------------------------------------------------------

loc_27464:
		cmp	word_3A76B, 0
		jz	loc_27572
		cmp	word_3A76B, 0C8h ; '?'
		jge	loc_27572
		inc	word_3A76B
		mov	ax, word_3A76B
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_274C6
		push	0FFh
		push	0
		push	1
		push	large 800080h
		push	180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_17956
		push	0FFh
		push	0
		push	1
		push	large 70080h
		push	large 800180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_1786D
		add	sp, 1Eh

loc_274C6:
		cmp	word_34A78, 0
		jnz	short loc_274F2
		mov	ax, word_3A76D
		add	ax, 68h	; 'h'
		cmp	ax, word_36C26
		jle	short loc_274E5
		mov	ax, word_3A76D
		add	ax, 0FF80h
		cmp	ax, word_36C26
		jl	short loc_274F2

loc_274E5:
		push	64h ; 'd'
		call	sub_AF20
		pop	cx
		mov	byte_34A4F, 1

loc_274F2:
		cmp	byte_34A4F, 1
		jnz	short loc_274FF
		mov	word_3A76B, 0C8h ; '?'

loc_274FF:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A6CC
		or	dx, dx
		jnz	short loc_27539
		push	48h ; 'H'
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_2751B
		mov	ax, 1Eh
		jmp	short loc_2751E
; ---------------------------------------------------------------------------

loc_2751B:
		mov	ax, 1

loc_2751E:
		push	ax
		push	40h ; '@'
		call	IRand
		mov	bx, 278h
		cwd
		idiv	bx
		push	dx
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_27539:
		cmp	word_3A76B, 0B4h ; '?'
		jle	loc_275EF
		mov	ax, word_3A76B
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_275EF
		push	large 48000Ch
		mov	ax, word ptr dword_3982A+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		jmp	loc_2745E
; ---------------------------------------------------------------------------

loc_27572:
		cmp	word_3A76B, 0C8h ; '?'
		jl	short loc_275EF
		cmp	word_3A76B, 0C8h ; '?'
		jnz	short loc_275A1
		push	0FFh
		push	0
		push	1
		push	large 800080h
		push	180h
		mov	ax, word_3A76D
		add	ax, 10h
		push	ax
		call	sub_17956
		add	sp, 0Eh

loc_275A1:
		inc	word_3A76B
		mov	ax, word_3A76B
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_275D2
		push	large 48000Ch
		mov	ax, word ptr dword_3988E+2
		add	ax, 2Ch	; ','
		push	ax
		mov	ax, word ptr dword_3988E
		add	ax, 3Ch	; '<'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_275D2:
		cmp	word_3A76B, 104h
		jle	short loc_275EF
		mov	word_3A6CA, 0
		mov	word_3A76B, 0
		mov	byte ptr word_3A76F, 0
		xor	ax, ax
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_275EF:
		mov	ax, 1
		pop	bp
		retf
sub_271F1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_275F4	proc far

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		push	si
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2764F
		push	1
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		mov	word_39888, 0
		mov	word_39880, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	2
		push	cs
		call	near ptr sub_24EC2
		add	sp, 14h
		mov	word_39888, 0
		mov	word_39880, 1
		jmp	short loc_27698
; ---------------------------------------------------------------------------

loc_2764F:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	short loc_276AD
		push	1
		call	sub_EA3E
		mov	word_39888, 0
		mov	word_39880, 2
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		push	0
		call	sub_EA3E
		add	sp, 10h
		mov	word_39888, 0
		mov	word_39880, 2

loc_27698:
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3985C
		call	sub_1689D
		add	sp, 0Ch

loc_276AD:
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_27ABB
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_27729
		push	1
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		mov	word_39856, 0
		mov	word_3984E, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		mov	word_39856, 0
		mov	word_3984E, 1
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		mov	byte ptr word_3A76F+1, 0
		push	large 0F0014h
		push	large 1E0028h
		push	ds
		push	offset word_3A6CC
		push	cs
		call	near ptr sub_253A2
		add	sp, 2Ah

loc_27729:
		cmp	word_3A6CA, 3Ch	; '<'
		jl	loc_278BE
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_278BE
		cmp	word_3A771, 0
		jnz	loc_278BE
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_27759
		push	8
		call	sub_125C9
		pop	cx

loc_27759:
		mov	al, byte ptr word_3A76F+1
		add	al, 2
		push	ax
		push	word_3A76F+1
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		mov	al, byte ptr word_3A76F+1
		add	al, 42h	; 'B'
		push	ax
		mov	al, byte ptr word_3A76F+1
		add	al, 40h	; '@'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		mov	al, byte ptr word_3A76F+1
		add	al, 82h	; '�
		push	ax
		mov	al, byte ptr word_3A76F+1
		add	al, 80h	; '?'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 30h
		mov	al, byte ptr word_3A76F+1
		add	al, 0C2h ; '?'
		push	ax
		mov	al, byte ptr word_3A76F+1
		add	al, 0C0h ; '?'
		push	ax
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 10h
		mov	al, byte ptr word_3A76F+1
		add	al, 2
		mov	byte ptr word_3A76F+1, al
		cmp	byte ptr word_3A76F+1, 40h ; '@'
		jb	loc_27A1C
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		push	0FFh
		push	0
		push	1
		push	large 70080h
		push	80h ; '?'
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		mov	word_3A771, 1
		push	1
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		push	1
		push	cs
		call	near ptr sub_24EC2
		add	sp, 32h
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 0Ch
		jmp	loc_27A1C
; ---------------------------------------------------------------------------

loc_278BE:
		cmp	word_3A771, 0
		jz	loc_2796A
		cmp	word_3A771, 28h	; '('
		jge	loc_2796A
		inc	word_3A771
		mov	ax, word_3A771
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2790F
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		push	0FFh
		push	0
		push	1
		push	4
		jmp	short loc_2794B
; ---------------------------------------------------------------------------

loc_2790F:
		mov	ax, word_3A771
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	loc_27A1C
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		push	0FFh
		push	0
		push	1
		push	7

loc_2794B:
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_1786D
		add	sp, 10h
		jmp	loc_27A1C
; ---------------------------------------------------------------------------

loc_2796A:
		cmp	word_3A771, 0
		jz	loc_27A1C
		push	0FFh
		push	0
		push	1
		push	large 800080h
		mov	ax, word ptr dword_3982A+2
		add	ax, 30h	; '0'
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		push	ax
		call	sub_17956
		add	sp, 0Eh
		mov	byte ptr word_3A76F+1, 0
		xor	si, si
		jmp	short loc_27A06
; ---------------------------------------------------------------------------

loc_2799F:
		mov	al, byte ptr word_3A76F+1
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A
		add	ax, 40h	; '@'
		mov	[bp+var_2], ax
		mov	al, byte ptr word_3A76F+1
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 7
		sar	eax, 8
		add	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		mov	[bp+var_4], ax
		push	large 400001h
		push	ax
		push	[bp+var_2]
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		mov	al, byte ptr word_3A76F+1
		add	al, 8
		mov	byte ptr word_3A76F+1, al
		inc	si

loc_27A06:
		cmp	si, 20h	; ' '
		jl	short loc_2799F
		mov	word_3A6CA, 0
		mov	word_3A771, 0
		xor	ax, ax
		jmp	loc_27ABE
; ---------------------------------------------------------------------------

loc_27A1C:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A6CC
		or	dx, dx
		jnz	short loc_27A65
		push	large 40001Bh
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 16h
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 40001Bh
		mov	ax, word ptr dword_3982A+2
		add	ax, 28h	; '('
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 64h	; 'd'
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 18h

loc_27A65:
		mov	ax, word_3A6CC
		add	ax, ax
		push	ax
		mov	ax, word_3A6CA
		cwd
		pop	bx
		idiv	bx
		or	dx, dx
		jnz	short loc_27ABB
		push	large 80014h
		push	large 70032h
		push	190h
		push	word_36C26
		mov	ax, word ptr dword_3982A+2
		add	ax, 1Ch
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 3Ch	; '<'
		push	ax
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		cwd
		idiv	bx
		imul	dx, 45h
		add	dx, 4800h
		push	ds
		push	dx
		call	sub_1209D
		push	6
		call	sub_125C9
		add	sp, 16h

loc_27ABB:
		mov	ax, 1

loc_27ABE:
		pop	si
		leave
		retf
sub_275F4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_27AC1	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		cmp	[bp+arg_0], 1
		jnz	short loc_27AD9
		mov	word_35D44, 0
		mov	word_35D46, 0
		jmp	loc_27B5B
; ---------------------------------------------------------------------------

loc_27AD9:
		mov	bx, word_35D44
		cmp	bx, 3
		ja	short loc_27B5B
		add	bx, bx
		jmp	cs:off_27B5F[bx]

loc_27AE9:
		call	IRand
		mov	bx, 3
		cwd
		idiv	bx
		inc	dx
		mov	word_35D44, dx
		jmp	short loc_27B5B
; ---------------------------------------------------------------------------

loc_27AFB:
		cmp	word_35D46, 0
		jnz	short loc_27B04
		jmp	short loc_27B34
; ---------------------------------------------------------------------------

loc_27B04:
		push	cs
		call	near ptr sub_26F4F
		mov	word_35D46, ax
		cmp	word_35D46, 0
		jnz	short loc_27B5B
		jmp	short loc_27B4A
; ---------------------------------------------------------------------------

loc_27B14:
		cmp	word_35D46, 0
		jnz	short loc_27B1D
		jmp	short loc_27B34
; ---------------------------------------------------------------------------

loc_27B1D:
		push	cs
		call	near ptr sub_271F1
		mov	word_35D46, ax
		cmp	word_35D46, 0
		jnz	short loc_27B5B
		jmp	short loc_27B4A
; ---------------------------------------------------------------------------

loc_27B2D:
		cmp	word_35D46, 0
		jnz	short loc_27B3C

loc_27B34:
		call	sub_25E28
		mov	word_35D46, ax
		jmp	short loc_27B5B
; ---------------------------------------------------------------------------

loc_27B3C:
		push	cs
		call	near ptr sub_275F4
		mov	word_35D46, ax
		cmp	word_35D46, 0
		jnz	short loc_27B5B

loc_27B4A:
		mov	word_35D46, 0
		mov	word_35D44, 0
		mov	ax, 1
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_27B5B:
		xor	ax, ax
		pop	bp
		retf
sub_27AC1	endp

; ---------------------------------------------------------------------------
off_27B5F	dw offset loc_27AE9
		dw offset loc_27AFB
		dw offset loc_27B14
		dw offset loc_27B2D

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_27B67	proc far

arg_0		= dword	ptr  6
arg_4		= dword	ptr  0Ah
arg_8		= dword	ptr  0Eh
arg_C		= word ptr  12h

		push	bp
		mov	bp, sp
		cmp	[bp+arg_C], 1
		jnz	short loc_27B85
		mov	word_35D48, 0
		mov	word_35D4A, 0
		push	1
		push	cs
		call	near ptr sub_27AC1
		pop	cx
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_27B85:
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 1
		jnz	short loc_27C06
		cmp	word_35D48, 0
		jnz	short loc_27BE7
		push	large [bp+arg_8]
		push	large [bp+arg_4]
		push	cs
		call	near ptr sub_26D12
		add	sp, 8
		mov	word_35D48, ax
		cmp	word_35D4A, 0
		jnz	short loc_27BBE
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		inc	dx
		mov	word_35D4A, dx

loc_27BBE:
		mov	bx, word_35D4A
		dec	bx
		cmp	bx, 3
		ja	short loc_27C2F
		add	bx, bx
		jmp	cs:off_27C31[bx]

loc_27BCF:
		push	cs
		call	near ptr sub_26E02
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_27BD5:
		push	cs
		call	near ptr sub_26E49
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_27BDB:
		push	cs
		call	near ptr sub_26F12
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_27BE1:
		push	cs
		call	near ptr sub_26E8C
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_27BE7:
		cmp	word_35D48, 1
		jnz	short loc_27C2F
		push	cs
		call	near ptr sub_26B1C
		les	bx, [bp+arg_0]
		mov	es:[bx], ax
		cmp	word ptr es:[bx], 0
		jnz	short loc_27C2F
		mov	word_35D4A, 0
		jmp	short loc_27C29
; ---------------------------------------------------------------------------

loc_27C06:
		cmp	word_35D48, 0
		jnz	short loc_27C19
		push	0
		push	cs
		call	near ptr sub_27AC1
		pop	cx
		mov	word_35D48, ax
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_27C19:
		push	cs
		call	near ptr sub_26940
		les	bx, [bp+arg_0]
		mov	es:[bx], ax
		cmp	word ptr es:[bx], 1
		jnz	short loc_27C2F

loc_27C29:
		mov	word_35D48, 0

loc_27C2F:
		pop	bp
		retf
sub_27B67	endp

; ---------------------------------------------------------------------------
off_27C31	dw offset loc_27BCF
		dw offset loc_27BD5
		dw offset loc_27BDB
		dw offset loc_27BE1

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_27C39	proc far

var_2A		= byte ptr -2Ah
var_28		= byte ptr -28h
var_26		= byte ptr -26h
var_1E		= byte ptr -1Eh
var_1C		= byte ptr -1Ch
var_1A		= word ptr -1Ah
var_14		= word ptr -14h
var_12		= word ptr -12h
var_10		= word ptr -10h
var_E		= word ptr -0Eh
var_C		= word ptr -0Ch
var_9		= byte ptr -9
var_8		= dword	ptr -8
var_4		= word ptr -4
var_2		= word ptr -2

		enter	2Ah, 0
		push	si
		push	di
		mov	eax, dword_35D4E
		mov	[bp+var_8], eax
		push	ds
		push	offset unk_39EC4
		call	sub_21F19
		add	sp, 4
		cmp	byte_3A6CE, 0
		jnz	loc_281CF
		call	sub_232A4
		push	1
		push	cs
		call	near ptr sub_24E33
		pop	cx
		mov	[bp+var_9], 0
		mov	word_3A773, 0

loc_27C72:
		inc	word_3A773
		xor	si, si
		jmp	loc_27E35
; ---------------------------------------------------------------------------

loc_27C7B:
		mov	al, [bp+var_9]
		mov	ah, 0
		mov	dx, si
		shl	dx, 7
		add	ax, dx
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		imul	eax, 60h
		sar	eax, 8
		add	ax, 130h
		mov	di, ax
		mov	al, [bp+var_9]
		mov	ah, 0
		mov	dx, si
		shl	dx, 7
		add	ax, dx
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		imul	eax, 60h
		sar	eax, 8
		add	ax, 72h	; 'r'
		mov	[bp+var_2], ax
		push	large 200030h
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_10433
		push	large 80003h
		push	0
		push	[bp+var_2]
		push	di
		call	sub_1754D
		add	sp, 12h
		cmp	word_3A773, 1
		jle	loc_27DAF
		push	large 200030h
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_28]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1C]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_10433
		push	large 80002h
		push	0
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_1754D
		add	sp, 12h
		cmp	word_3A773, 2
		jle	short loc_27DAF
		push	large 200030h
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_26]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1A]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_10433
		push	large 80001h
		push	0
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_28]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1C]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_1754D
		add	sp, 12h

loc_27DAF:
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1C]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	dx, [bp+var_1A]
		add	bx, dx
		mov	ss:[bx], ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_28]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	dx, [bp+var_26]
		add	bx, dx
		mov	ss:[bx], ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	dx, [bp+var_1C]
		add	bx, dx
		mov	ss:[bx], ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	dx, [bp+var_28]
		add	bx, dx
		mov	ss:[bx], ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		mov	ss:[bx], di
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		mov	ax, [bp+var_2]
		mov	ss:[bx], ax
		inc	si

loc_27E35:
		cmp	si, 2
		jl	loc_27C7B
		cmp	word_3A773, 78h	; 'x'
		jge	short loc_27E63
		mov	al, [bp+var_9]
		add	al, 18h
		mov	[bp+var_9], al
		mov	ax, 78h	; 'x'
		sub	ax, word_3A773
		mov	bx, 0Ch
		cwd
		idiv	bx
		inc	ax
		push	ax
		call	sub_E364
		pop	cx
		jmp	loc_27C72
; ---------------------------------------------------------------------------

loc_27E63:
		mov	word_3A773, 0
		mov	[bp+var_4], 0

loc_27E6E:
		inc	word_3A773
		cmp	[bp+var_4], 0
		jnz	loc_2802A
		mov	ax, word_3A773
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2802A
		xor	si, si
		jmp	loc_28023
; ---------------------------------------------------------------------------

loc_27E8E:
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		mov	ax, ss:[bx]
		add	ax, 40h	; '@'
		mov	dx, si
		shl	dx, 7
		sub	ax, dx
		mov	di, ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	[bp+var_2], ax
		push	large 200030h
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_10433
		push	large 80003h
		push	0
		push	[bp+var_2]
		push	di
		call	sub_1754D
		push	large 200030h
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_28]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1C]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_10433
		push	large 80002h
		push	0
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_1754D
		push	large 200030h
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_26]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1A]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_10433
		add	sp, 2Ch
		push	large 80001h
		push	0
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_28]
		add	bx, ax
		push	word ptr ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1C]
		add	bx, ax
		push	word ptr ss:[bx]
		call	sub_1754D
		add	sp, 0Ah
		cmp	[bp+var_1A], 280h
		jle	short loc_27F9D
		cmp	[bp+var_14], 0FFE0h
		jge	short loc_27F9D
		mov	[bp+var_4], 1

loc_27F9D:
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1C]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	dx, [bp+var_1A]
		add	bx, dx
		mov	ss:[bx], ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_28]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	dx, [bp+var_26]
		add	bx, dx
		mov	ss:[bx], ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	dx, [bp+var_1C]
		add	bx, dx
		mov	ss:[bx], ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		mov	ax, ss:[bx]
		mov	bx, si
		imul	bx, 6
		lea	dx, [bp+var_28]
		add	bx, dx
		mov	ss:[bx], ax
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_1E]
		add	bx, ax
		mov	ss:[bx], di
		mov	bx, si
		imul	bx, 6
		lea	ax, [bp+var_2A]
		add	bx, ax
		mov	ax, [bp+var_2]
		mov	ss:[bx], ax
		inc	si

loc_28023:
		cmp	si, 2
		jl	loc_27E8E

loc_2802A:
		cmp	word_3A773, 14h
		jle	short loc_280AE
		cmp	word_3A773, 64h	; 'd'
		jge	short loc_280AE
		mov	ax, word_3A773
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_28158
		cmp	word_3A773, 18h
		jz	short loc_28082
		push	word_39834
		mov	ax, word_39832
		shl	ax, 3
		add	ax, 10h
		push	ax
		mov	ax, word_3A773
		add	ax, 0FFFCh
		imul	ax, 6
		push	ax
		mov	ax, 68h	; 'h'
		sub	ax, word_3A773
		push	ax
		mov	ax, word_3A773
		add	ax, 0FFFEh
		push	ax
		push	large [dword_3982A]
		call	sub_11EA1
		add	sp, 0Eh

loc_28082:
		mov	ax, word_3A773
		imul	ax, 6
		push	ax
		mov	ax, 64h	; 'd'
		sub	ax, word_3A773
		push	ax
		mov	ax, word_3A773
		add	ax, 2
		push	ax
		push	0
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_16344
		add	sp, 10h
		jmp	loc_28158
; ---------------------------------------------------------------------------

loc_280AE:
		cmp	word_3A773, 64h	; 'd'
		jnz	short loc_28103
		push	word_39834
		mov	ax, word_39832
		shl	ax, 3
		add	ax, 10h
		push	ax
		push	word_3A773
		mov	ax, 64h	; 'd'
		sub	ax, word_3A773
		push	ax
		mov	ax, word_3A773
		add	ax, 2
		push	ax

loc_280D6:
		push	large [dword_3982A]
		call	sub_11EA1
		mov	word_39856, 0
		mov	word_3984E, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_16733
		add	sp, 1Ah
		jmp	short loc_28158
; ---------------------------------------------------------------------------

loc_28103:
		cmp	word_3A773, 80h	; '?'
		jnz	short loc_28130
		push	1
		push	cs
		call	near ptr sub_24EC2
		push	large 400008h
		push	large 30000h
		push	large [dword_3982A]
		push	ds
		push	offset dword_3982A
		call	sub_16344
		add	sp, 12h
		jmp	short loc_28158
; ---------------------------------------------------------------------------

loc_28130:
		cmp	word_3A773, 82h	; '�
		jnz	short loc_28150
		push	word_39834
		mov	ax, word_39832
		shl	ax, 3
		add	ax, 10h
		push	ax
		push	large 400008h
		push	3
		jmp	short loc_280D6
; ---------------------------------------------------------------------------

loc_28150:
		cmp	word_3A773, 8Ch	; '�
		jg	short loc_28163

loc_28158:
		push	1
		call	sub_E364
		pop	cx
		jmp	loc_27E6E
; ---------------------------------------------------------------------------

loc_28163:
		mov	word_3A6CA, 0
		mov	word_3A773, 0
		mov	byte_3A6CE, 1
		mov	word_39852, 0
		push	1
		call	sub_EA3E
		mov	word_39856, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		mov	word_39856, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 1Ch
		mov	word_3A779, 0
		mov	word_3A777, 1
		mov	byte_3A77F, 0
		jmp	loc_28655
; ---------------------------------------------------------------------------

loc_281CF:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 1
		jnz	loc_282DE
		cmp	byte_3A77F, 0
		jnz	short loc_281F4
		push	word_3A6CA
		push	word_3A6C8
		call	sub_2191C
		add	sp, 4
		mov	byte_3A77F, al

loc_281F4:
		inc	word_3A6CA
		inc	word_3A773
		cmp	word_3A777, 0
		jz	short loc_28211
		push	word_3A777
		push	cs
		call	near ptr sub_25DA7
		pop	cx
		mov	word_3A777, ax
		jmp	short loc_28258
; ---------------------------------------------------------------------------

loc_28211:
		cmp	word_3A779, 0
		jnz	short loc_2823F
		call	IRand
		mov	bx, 88h	; '�
		cwd
		idiv	bx
		add	dx, 40h	; '@'
		push	dx
		call	IRand
		mov	bx, 200h
		cwd
		idiv	bx
		push	dx
		push	cs
		call	near ptr sub_250EE
		add	sp, 4
		mov	word_3A779, ax
		jmp	short loc_28258
; ---------------------------------------------------------------------------

loc_2823F:
		cmp	word_3A779, 1
		jnz	short loc_28258
		push	word_3A777
		push	cs
		call	near ptr sub_25DA7
		pop	cx
		mov	word_3A777, ax
		mov	word_3A779, 0

loc_28258:
		push	large 300040h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		push	ax
		cmp	word_35D4C, 0
		jnz	short loc_28279
		push	ds
		push	offset dword_3982A
		jmp	short loc_2827D
; ---------------------------------------------------------------------------

loc_28279:
		push	ds
		push	offset dword_3988E

loc_2827D:
		call	sub_16970
		add	sp, 4
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1B58h
		push	4
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3A775
		push	ds
		push	offset word_3A773
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A775, 0
		jnz	loc_28655
		cmp	word_3A6C8, 0Ah
		jg	loc_28655
		cmp	word_3A779, 1
		jnz	loc_28655
		mov	byte_3A6CE, 2
		mov	word_3A6CA, 0
		mov	word_3A773, 0
		mov	word_3A777, 0
		jmp	short loc_28322
; ---------------------------------------------------------------------------

loc_282DE:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 2
		jnz	short loc_2832B
		inc	word_3A6CA
		push	large 600100h
		push	cs
		call	near ptr sub_250EE
		add	sp, 4
		mov	word_3A779, ax
		cmp	word_3A779, 1
		jnz	loc_28655
		push	63h ; 'c'
		push	cs
		call	near ptr sub_268B7
		pop	cx
		mov	byte_3A6CE, 3
		mov	word_3A6CA, 0
		mov	word_3A773, 0
		mov	word_3A777, 1

loc_28322:
		mov	word_3A779, 0
		jmp	loc_28655
; ---------------------------------------------------------------------------

loc_2832B:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 3
		jnz	loc_28442
		inc	word_3A6CA
		inc	word_3A773
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_C], ax
		mov	ax, word ptr dword_3982A
		mov	[bp+var_E], ax
		mov	word ptr dword_3985C, ax
		mov	ax, [bp+var_C]
		mov	word ptr dword_3985C+2,	ax
		cmp	word_3A777, 0
		jz	short loc_28368
		push	word_3A777
		push	cs
		call	near ptr sub_268B7
		pop	cx
		mov	word_3A777, ax
		jmp	short loc_283AF
; ---------------------------------------------------------------------------

loc_28368:
		cmp	word_3A779, 0
		jnz	short loc_28396
		call	IRand
		mov	bx, 88h	; '�
		cwd
		idiv	bx
		add	dx, 40h	; '@'
		push	dx
		call	IRand
		mov	bx, 200h
		cwd
		idiv	bx
		push	dx
		push	cs
		call	near ptr sub_250EE
		add	sp, 4
		mov	word_3A779, ax
		jmp	short loc_283AF
; ---------------------------------------------------------------------------

loc_28396:
		cmp	word_3A779, 1
		jnz	short loc_283AF
		push	word_3A777
		push	cs
		call	near ptr sub_268B7
		pop	cx
		mov	word_3A777, ax
		mov	word_3A779, 0

loc_283AF:
		push	large 300040h
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		push	ax
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		push	ax
		cmp	word_35D4C, 0
		jnz	short loc_283D0
		push	ds
		push	offset dword_3982A
		jmp	short loc_283D4
; ---------------------------------------------------------------------------

loc_283D0:
		push	ds
		push	offset dword_3988E

loc_283D4:
		call	sub_16970
		add	sp, 4
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1B58h
		push	4
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3A775
		push	ds
		push	offset word_3A773
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A775, 0
		jnz	loc_28655
		cmp	word_3A6C8, 6
		jg	loc_28655
		cmp	word_3A779, 1
		jnz	loc_28655
		mov	byte_3A6CE, 4
		mov	word_3A6CA, 0
		mov	word_3A773, 0
		mov	word_3A777, 0
		mov	word_3A779, 0
		mov	word_35D4C, 0
		jmp	loc_28655
; ---------------------------------------------------------------------------

loc_28442:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 4
		jnz	short loc_284B3
		inc	word_3A6CA
		cmp	word_3A779, 0
		jnz	short loc_28468
		push	large 600100h
		push	cs
		call	near ptr sub_250EE
		add	sp, 4
		mov	word_3A779, ax
		jmp	short loc_2846F
; ---------------------------------------------------------------------------

loc_28468:
		push	cs
		call	near ptr sub_26940
		mov	word_3A777, ax

loc_2846F:
		cmp	word_3A777, 1
		jnz	loc_28655
		mov	byte_3A6CE, 5
		mov	word_3A6CA, 0
		mov	word_3A773, 0
		mov	word_3A777, 0
		mov	word_3A779, 0
		mov	word_35D4C, 1
		push	1
		push	ds
		push	offset word_3A77B
		push	ds
		push	offset word_3A77D
		push	ds
		push	offset word_35D4C
		push	cs
		call	near ptr sub_27B67
		add	sp, 0Eh
		jmp	loc_28655
; ---------------------------------------------------------------------------

loc_284B3:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 5
		jnz	loc_28655
		inc	word_3A6CA
		inc	word_3A773
		mov	ax, word ptr dword_3982A+2
		mov	[bp+var_10], ax
		mov	ax, word ptr dword_3982A
		mov	[bp+var_12], ax
		mov	word ptr dword_3985C, ax
		mov	ax, [bp+var_10]
		mov	word ptr dword_3985C+2,	ax
		cmp	word_35D4C, 0
		jz	short loc_28539
		push	2
		push	word_3A77B
		push	word_3A77D
		push	0
		push	ds
		push	offset dword_3988E
		call	sub_16733
		add	sp, 0Ch
		mov	ax, word_3A6CA
		mov	bx, 9
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2850F
		mov	word_398B2, 0
		jmp	short loc_28539
; ---------------------------------------------------------------------------

loc_2850F:
		mov	ax, word_3A6CA
		mov	bx, 9
		cwd
		idiv	bx
		cmp	dx, 3
		jnz	short loc_28525
		mov	word_398B2, 1
		jmp	short loc_28539
; ---------------------------------------------------------------------------

loc_28525:
		mov	ax, word_3A6CA
		mov	bx, 9
		cwd
		idiv	bx
		cmp	dx, 6
		jnz	short loc_28539
		mov	word_398B2, 2

loc_28539:
		push	0
		push	ds
		push	offset word_3A77B
		push	ds
		push	offset word_3A77D
		push	ds
		push	offset word_35D4C
		push	cs
		call	near ptr sub_27B67
		add	sp, 0Eh
		cmp	word_35D4C, 0
		jnz	short loc_2855A
		mov	ax, 30h	; '0'
		jmp	short loc_2855D
; ---------------------------------------------------------------------------

loc_2855A:
		mov	ax, 20h	; ' '

loc_2855D:
		push	ax
		cmp	word_35D4C, 0
		jnz	short loc_2856A
		mov	ax, 40h	; '@'
		jmp	short loc_2856D
; ---------------------------------------------------------------------------

loc_2856A:
		mov	ax, 20h	; ' '

loc_2856D:
		push	ax
		cmp	word_35D4C, 0
		jnz	short loc_2857D
		mov	ax, word ptr dword_3982A+2
		add	ax, 20h	; ' '
		jmp	short loc_28580
; ---------------------------------------------------------------------------

loc_2857D:
		mov	ax, word ptr dword_3988E

loc_28580:
		push	ax
		cmp	word_35D4C, 0
		jnz	short loc_28590
		mov	ax, word ptr dword_3982A
		add	ax, 20h	; ' '
		jmp	short loc_28593
; ---------------------------------------------------------------------------

loc_28590:
		mov	ax, word ptr dword_3988E

loc_28593:
		push	ax
		cmp	word_35D4C, 0
		jnz	short loc_285A1
		push	ds
		push	offset dword_3982A
		jmp	short loc_285A5
; ---------------------------------------------------------------------------

loc_285A1:
		push	ds
		push	offset dword_3988E

loc_285A5:
		call	sub_16970
		add	sp, 4
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	1B58h
		push	4
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3A775
		push	ds
		push	offset word_3A773
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	short loc_28655
		call	sub_12589
		push	ds
		push	offset unk_37635
		call	sub_30DEE
		push	1
		push	cs
		call	near ptr sub_24EC2
		push	ds
		push	offset unk_39EC4
		call	sub_21EFF
		add	sp, 0Ah
		xor	si, si
		jmp	short loc_28643
; ---------------------------------------------------------------------------

loc_285FD:
		mov	bx, si
		imul	bx, 45h
		cmp	word ptr [bx+483Ah], 0
		jz	short loc_28642
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4804h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4800h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+480Ch]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4808h]
		call	sub_F2F5
		add	sp, 8
		mov	bx, si
		imul	bx, 45h
		mov	word ptr [bx+483Ah], 0
		jmp	short $+2

loc_28642:
		inc	si

loc_28643:
		cmp	si, 0Ah
		jl	short loc_285FD
		call	sub_12A3A
		push	5

loc_2864F:
		call	sub_20754

loc_28654:
		pop	cx

loc_28655:
		pop	di
		pop	si
		leave
		retf
sub_27C39	endp

seg035		ends

; ===========================================================================

; Segment type:	Pure code
seg036		segment	byte public 'CODE' use16
		assume cs:seg036
		;org 9
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_28659	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h

		push	bp
		mov	bp, sp
		mov	dx, [bp+arg_6]
		cmp	byte_34A30, 0
		jnz	short loc_2866B
		mov	ax, [bp+arg_4]
		jmp	short loc_28696
; ---------------------------------------------------------------------------

loc_2866B:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_28678
		mov	ax, dx
		jmp	short loc_28696
; ---------------------------------------------------------------------------

loc_28678:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_28686
		mov	ax, [bp+arg_8]
		jmp	short loc_28696
; ---------------------------------------------------------------------------

loc_28686:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_28694
		mov	ax, [bp+arg_A]
		jmp	short loc_28696
; ---------------------------------------------------------------------------

loc_28694:
		mov	ax, dx

loc_28696:
		les	bx, [bp+arg_0]
		mov	es:[bx], ax
		pop	bp
		retf
sub_28659	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2869E	proc far
		push	bp
		mov	bp, sp
		push	si
		mov	byte_360CC, 1
		push	large 200005h
		call	sub_C7C
		push	ds
		push	offset aBoss6_l_grp ; "boss6_l.grp"
		call	sub_10BAE
		push	1
		call	sub_EA3E
		push	ds
		push	offset aBoss6_h_grp ; "boss6_h.grp"
		call	sub_10BAE
		push	0
		call	sub_EA3E
		push	4
		call	sub_2091E
		push	ds
		push	offset aTensi_mdt_0 ; "TENSI.MDT"
		call	sub_12549
		push	ds
		push	offset aZigoku_mde_0 ; "zigoku.mde"
		call	sub_12559
		add	sp, 16h
		call	sub_12569
		push	large 2000E1h
		call	sub_C7C
		mov	si, 18Fh
		jmp	short loc_2871C
; ---------------------------------------------------------------------------

loc_28703:
		push	si
		call	sub_11738
		push	1
		push	si
		call	sub_11816
		push	1
		call	sub_E364
		add	sp, 8
		dec	si

loc_2871C:
		or	si, si
		jge	short loc_28703
		push	0
		call	sub_11738
		push	1
		call	sub_EA3E
		push	large [off_35DAB]
		call	sub_10BAE
		push	0
		call	sub_EA3E
		push	28h ; '('
		call	sub_11A7C
		add	sp, 0Ch
		mov	eax, dword_36C16
		mov	random_seed, eax
		pop	si
		pop	bp
		retf
sub_2869E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_28754	proc far
		push	bp
		mov	bp, sp
		mov	word_39854, 1
		push	0
		push	ds
		push	offset aBoss6_1_bos ; "boss6_1.bos"
		push	ds
		push	offset dword_3982A
		call	sub_1568F
		mov	word_39854, 0
		push	0
		push	ds
		push	offset aBoss6_2_bos ; "boss6_2.bos"
		push	ds
		push	offset word_39A29
		call	sub_16B56
		push	1
		push	ds
		push	offset aBoss6_3_bos ; "boss6_3.bos"
		push	ds
		push	offset word_39A1E
		call	sub_16B56
		push	ds
		push	offset aBoss6gr1_grc ; "boss6gr1.grc"
		push	0
		call	sub_1744B
		push	ds
		push	offset aBoss6gr2_grc ; "boss6gr2.grc"
		push	1
		call	sub_1744B
		push	ds
		push	offset aBoss6gr3_grc ; "boss6gr3.grc"
		push	2
		call	sub_1744B
		add	sp, 30h
		push	ds
		push	offset aBoss6gr4_grc ; "boss6gr4.grc"
		push	3
		call	sub_1744B
		call	sub_232A4
		nop
		push	cs
		call	near ptr sub_287D9
		push	large 100002h
		call	sub_10814
		add	sp, 0Ah
		pop	bp
		retf
sub_28754	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_287D9	proc far
		push	bp
		mov	bp, sp
		push	large 1900000h
		push	large 2800000h
		push	large 300090h
		push	130h
		push	ds
		push	offset dword_3982A
		call	sub_166D2
		add	sp, 12h
		mov	word_3983E, 0
		mov	word_39840, 30h	; '0'
		mov	word_39842, 0
		mov	word_39844, 30h	; '0'
		mov	word_3A6C8, 12h
		mov	word_3A1E5, 8
		mov	word_3A1E7, 2
		mov	byte_3A6CE, 0
		mov	word_3A6CA, 0
		mov	word_39852, 0
		mov	word_39A1E, 118h
		mov	word_39A20, 0C0h ; '?'
		mov	word_39A29, 128h
		mov	word_39A2B, 30h	; '0'
		pop	bp
		retf
sub_287D9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_28852	proc near

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		push	si
		push	di
		mov	ax, word_39A29
		mov	[bp+var_2], ax
		mov	ax, word_39A2B
		mov	[bp+var_4], ax
		mov	[bp+var_6], 0
		push	1
		call	sub_EA3E
		pop	cx
		xor	di, di
		jmp	short loc_288A4
; ---------------------------------------------------------------------------

loc_28875:
		xor	si, si
		jmp	short loc_2889E
; ---------------------------------------------------------------------------

loc_28879:
		mov	ax, [bp+var_6]
		add	ax, 80h	; '?'
		push	ax
		mov	ax, di
		shl	ax, 5
		add	ax, [bp+var_4]
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		push	ax
		call	sub_104C2
		add	sp, 6
		inc	[bp+var_6]
		inc	si

loc_2889E:
		cmp	si, 4
		jl	short loc_28879
		inc	di

loc_288A4:
		cmp	di, 3
		jl	short loc_28875
		push	0
		call	sub_EA3E
		pop	cx
		pop	di
		pop	si
		leave
		retn
sub_28852	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_288B5	proc near

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		push	si
		push	di
		mov	[bp+var_6], 0
		mov	ax, word_39A29
		mov	[bp+var_2], ax
		mov	ax, word_39A2B
		mov	[bp+var_4], ax
		xor	di, di
		jmp	short loc_288FF
; ---------------------------------------------------------------------------

loc_288D0:
		xor	si, si
		jmp	short loc_288F9
; ---------------------------------------------------------------------------

loc_288D4:
		mov	ax, [bp+var_6]
		add	ax, 80h	; '?'
		push	ax
		mov	ax, di
		shl	ax, 5
		add	ax, [bp+var_4]
		push	ax
		mov	ax, si
		shl	ax, 5
		add	ax, [bp+var_2]
		push	ax
		call	sub_108EC
		add	sp, 6
		inc	[bp+var_6]
		inc	si

loc_288F9:
		cmp	si, 4
		jl	short loc_288D4
		inc	di

loc_288FF:
		cmp	di, 3
		jl	short loc_288D0
		pop	di
		pop	si
		leave
		retn
sub_288B5	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_28908	proc far
		push	bp
		mov	bp, sp
		push	0
		call	sub_169CB
		push	0
		call	sub_16F1B
		push	1
		call	sub_16F1B
		push	0
		call	sub_17682
		push	1
		call	sub_17682
		push	2
		call	sub_17682
		push	3
		call	sub_17682
		push	2
		call	sub_108AB
		add	sp, 10h
		pop	bp
		retf
sub_28908	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_28948	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah
arg_8		= word ptr  0Ch

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_2]
		cmp	[bp+arg_0], 63h	; 'c'
		jnz	short loc_28967
		mov	word_35DBB, 3E7h
		mov	word_35DBD, 3E7h
		jmp	short loc_289CA
; ---------------------------------------------------------------------------

loc_28967:
		cmp	word_35DBB, 0
		jl	short loc_2899B
		cmp	word_35DBB, 280h
		jge	short loc_2899B
		cmp	word_35DBD, 0
		jl	short loc_2899B
		cmp	word_35DBD, 190h
		jge	short loc_2899B
		push	word_35DBD
		push	word_35DBB
		push	[bp+arg_6]
		push	[bp+arg_8]
		call	sub_F2F5
		add	sp, 8

loc_2899B:
		or	si, si
		jl	short loc_289C2
		cmp	si, 280h
		jge	short loc_289C2
		or	di, di
		jl	short loc_289C2
		cmp	di, 190h
		jge	short loc_289C2
		push	[bp+arg_0]
		push	di
		push	si
		push	[bp+arg_6]
		push	[bp+arg_8]
		call	sub_F342
		add	sp, 0Ah

loc_289C2:
		mov	word_35DBB, si
		mov	word_35DBD, di

loc_289CA:
		pop	di
		pop	si
		pop	bp
		retn	0Ah
sub_28948	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

; int __stdcall	sub_289D0(char,	double,	double,	double,	double)
sub_289D0	proc near

var_1E		= qword	ptr -1Eh
var_16		= qword	ptr -16h
var_E		= dword	ptr -0Eh
var_A		= dword	ptr -0Ah
var_6		= dword	ptr -6
var_2		= word ptr -2
arg_0		= byte ptr  4
arg_2		= qword	ptr  6
arg_A		= qword	ptr  0Eh
arg_12		= qword	ptr  16h
arg_1A		= qword	ptr  1Eh

		enter	1Eh, 0
		push	si
		push	di
		; Hack (fld [bp+arg_1A])
		db 0cdh
		db 039h
		db 046h
		db 01eh
		; Hack (fcomp flt_35F66)
		db 0cdh
		db 034h
		db 01eh
		db 0c6h
		db 015h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jnz	short loc_289FD
		xor	si, si
		jmp	short loc_289F5
; ---------------------------------------------------------------------------

loc_289EF:
		mov	byte ptr [si+141Fh], 0
		inc	si

loc_289F5:
		cmp	si, 1Eh
		jl	short loc_289EF
		jmp	loc_28EA0
; ---------------------------------------------------------------------------

loc_289FD:
		; Hack (fld [bp+arg_1A])
		db 0cdh
		db 039h
		db 046h
		db 01eh
		; Hack (fcomp flt_35F6A)
		db 0cdh
		db 034h
		db 01eh
		db 0cah
		db 015h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jnz	short loc_28A69
		xor	si, si
		jmp	short loc_28A61
; ---------------------------------------------------------------------------

loc_28A16:
		cmp	byte ptr [si+141Fh], 0
		jz	short loc_28A60
		cmp	byte ptr [si+61C0h], 0
		jnz	short loc_28A60
		push	large 30000Ch
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		; Hack (fadd flt_35F6E)
		db 0cdh
		db 034h
		db 006h
		db 0ceh
		db 015h
		call	sub_2395
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		; Hack (fadd flt_35F6E)
		db 0cdh
		db 034h
		db 006h
		db 0ceh
		db 015h
		call	sub_2395
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_28A60:
		inc	si

loc_28A61:
		cmp	si, 1Eh
		jl	short loc_28A16
		jmp	loc_28EA0
; ---------------------------------------------------------------------------

loc_28A69:
		; Hack (fld [bp+arg_1A])
		db 0cdh
		db 039h
		db 046h
		db 01eh
		; Hack (fcomp flt_35F72)
		db 0cdh
		db 034h
		db 01eh
		db 0d2h
		db 015h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jnz	short loc_28AE7
		xor	si, si
		jmp	short loc_28ADF
; ---------------------------------------------------------------------------

loc_28A82:
		cmp	byte ptr [si+141Fh], 0
		jz	short loc_28ADE
		cmp	byte ptr [si+61C0h], 0
		jnz	short loc_28ADE
		xor	di, di
		jmp	short loc_28AD9
; ---------------------------------------------------------------------------

loc_28A94:
		push	large 0
		push	large 0
		push	40h ; '@'
		mov	ax, di
		imul	ax, 2Ah
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		; Hack (fadd flt_35F6E)
		db 0cdh
		db 034h
		db 006h
		db 0ceh
		db 015h
		call	sub_2395
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		; Hack (fadd flt_35F6E)
		db 0cdh
		db 034h
		db 006h
		db 0ceh
		db 015h
		call	sub_2395
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	di

loc_28AD9:
		cmp	di, 6
		jl	short loc_28A94

loc_28ADE:
		inc	si

loc_28ADF:
		cmp	si, 1Eh
		jl	short loc_28A82
		jmp	loc_28EA0
; ---------------------------------------------------------------------------

loc_28AE7:
		; Hack (fld [bp+arg_1A])
		db 0cdh
		db 039h
		db 046h
		db 01eh
		; Hack (fcomp flt_35F76)
		db 0cdh
		db 034h
		db 01eh
		db 0d6h
		db 015h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jnz	short loc_28B62
		xor	si, si
		jmp	short loc_28B5A
; ---------------------------------------------------------------------------

loc_28B00:
		cmp	byte ptr [si+141Fh], 0
		jz	short loc_28B59
		cmp	byte ptr [si+61C0h], 0
		jnz	short loc_28B59
		push	large 0
		push	large 10001h
		push	40h ; '@'
		call	IRand
		and	al, 7Fh
		add	al, 80h	; '?'
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		; Hack (fadd flt_35F6E)
		db 0cdh
		db 034h
		db 006h
		db 0ceh
		db 015h
		call	sub_2395
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		; Hack (fadd flt_35F6E)
		db 0cdh
		db 034h
		db 006h
		db 0ceh
		db 015h
		call	sub_2395
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h

loc_28B59:
		inc	si

loc_28B5A:
		cmp	si, 1Eh
		jl	short loc_28B00
		jmp	loc_28EA0
; ---------------------------------------------------------------------------

loc_28B62:
		; Hack (fld [bp+arg_1A])
		db 0cdh
		db 039h
		db 046h
		db 01eh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (fcompp)
		db 0cdh
		db 03ah
		db 0d9h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jz	loc_28C25
		xor	si, si
		jmp	loc_28C1B
; ---------------------------------------------------------------------------

loc_28B7F:
		mov	al, [si+141Fh]
		cbw
		cmp	ax, 1
		jz	loc_28C1A
		mov	byte ptr [si+141Fh], 1
		mov	ax, si
		add	ax, 61C0h
		mov	word ptr [bp+var_6+2], ds
		mov	word ptr [bp+var_6], ax
		mov	ax, si
		shl	ax, 3
		add	ax, 60B2h
		mov	word ptr [bp+var_A+2], ds
		mov	word ptr [bp+var_A], ax
		mov	ax, si
		shl	ax, 3
		add	ax, 5FC2h
		mov	word ptr [bp+var_E+2], ds
		mov	word ptr [bp+var_E], ax
		; Hack (fld [bp+arg_2])
		db 0cdh
		db 039h
		db 046h
		db 006h
		; Hack (fstp [bp+var_16])
		db 0cdh
		db 039h
		db 05eh
		db 0eah
		; Hack (fld [bp+arg_A])
		db 0cdh
		db 039h
		db 046h
		db 00eh
		; Hack (fstp [bp+var_1E])
		db 0cdh
		db 039h
		db 05eh
		db 0e2h
		; Hack (wait)
		db 0cdh
		db 03dh
		les	bx, [bp+var_E]
		; Hack (fld [bp+var_1E])
		db 0cdh
		db 039h
		db 046h
		db 0e2h
		; Hack (fstp qword ptr es:[bx])
		db 0cdh
		db 03ch
		db 0ddh
		db 01fh
		; Hack (wait)
		db 0cdh
		db 03dh
		les	bx, [bp+var_A]
		; Hack (fld [bp+var_16])
		db 0cdh
		db 039h
		db 046h
		db 0eah
		; Hack (fstp qword ptr es:[bx])
		db 0cdh
		db 03ch
		db 0ddh
		db 01fh
		; Hack (wait)
		db 0cdh
		db 03dh
		les	bx, [bp+var_6]
		mov	byte ptr es:[bx], 19h
		mov	bx, si
		shl	bx, 3
		; Hack (fld [bp+arg_1A])
		db 0cdh
		db 039h
		db 046h
		db 01eh
		; Hack (fstp qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 09fh
		db 0e2h
		db 05dh
		mov	bx, si
		shl	bx, 3
		; Hack (fld [bp+arg_12])
		db 0cdh
		db 039h
		db 046h
		db 016h
		; Hack (fstp qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 09fh
		db 0d2h
		db 05eh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	al, [bp+arg_0]
		mov	[si+61A2h], al
		mov	al, [si+61C0h]
		mov	[si+61DEh], al
		jmp	loc_28EA0
; ---------------------------------------------------------------------------

loc_28C1A:
		inc	si

loc_28C1B:
		cmp	si, 1Eh
		jl	loc_28B7F
		jmp	loc_28EA0
; ---------------------------------------------------------------------------

loc_28C25:
		xor	si, si
		jmp	loc_28CC1
; ---------------------------------------------------------------------------

loc_28C2A:
		cmp	byte ptr [si+141Fh], 0
		jz	loc_28CC0
		mov	al, [si+61C0h]
		cbw
		or	ax, ax
		jle	short loc_28C92
		push	0Fh
		mov	al, [si+61DEh]
		cbw
		push	ax
		mov	al, [si+61C0h]
		cbw
		mov	dx, ax
		pop	ax
		sub	ax, dx
		push	ax
		mov	al, [si+61DEh]
		cbw
		mov	bx, 5
		cwd
		idiv	bx
		mov	bx, ax
		pop	ax
		cwd
		idiv	bx
		inc	ax
		push	ax
		push	1
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		call	sub_2395
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		call	sub_2395
		push	ax
		call	sub_1754D
		add	sp, 0Ah
		dec	byte ptr [si+61C0h]
		jmp	short loc_28CC0
; ---------------------------------------------------------------------------

loc_28C92:
		push	large 200030h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		call	sub_2395
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		call	sub_2395
		push	ax
		call	sub_10433
		add	sp, 8

loc_28CC0:
		inc	si

loc_28CC1:
		cmp	si, 1Eh
		jl	loc_28C2A
		xor	si, si
		jmp	loc_28E99
; ---------------------------------------------------------------------------

loc_28CCD:
		cmp	byte ptr [si+141Fh], 0
		jz	loc_28E98
		cmp	byte ptr [si+61C0h], 0
		jnz	loc_28E98
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5FC2h])
		db 0cdh
		db 039h
		db 087h
		db 0c2h
		db 05fh
		mov	bx, si
		shl	bx, 3
		; Hack (fadd qword ptr [bx+5DE2h])
		db 0cdh
		db 038h
		db 087h
		db 0e2h
		db 05dh
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 09fh
		db 0e2h
		db 05dh
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+60B2h])
		db 0cdh
		db 039h
		db 087h
		db 0b2h
		db 060h
		mov	bx, si
		shl	bx, 3
		; Hack (fadd qword ptr [bx+5ED2h])
		db 0cdh
		db 038h
		db 087h
		db 0d2h
		db 05eh
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 09fh
		db 0d2h
		db 05eh
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (fcompp)
		db 0cdh
		db 03ah
		db 0d9h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		ja	short loc_28D89
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		; Hack (fcomp flt_35F7A)
		db 0cdh
		db 034h
		db 01eh
		db 0dah
		db 015h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		ja	short loc_28D89
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (fcompp)
		db 0cdh
		db 03ah
		db 0d9h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		ja	short loc_28D89
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		; Hack (fcomp flt_35F7E)
		db 0cdh
		db 034h
		db 01eh
		db 0deh
		db 015h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jbe	short loc_28DBF

loc_28D89:
		push	large 200030h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		call	sub_2395
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		call	sub_2395
		push	ax
		call	sub_10433
		add	sp, 8
		mov	byte ptr [si+141Fh], 0
		jmp	loc_28E98
; ---------------------------------------------------------------------------

loc_28DBF:
		push	0Fh
		mov	ax, word_3A6CA
		mov	bx, 5
		cwd
		idiv	bx
		mov	bx, 2
		cwd
		idiv	bx
		add	dx, 6
		push	dx
		push	1
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		call	sub_2395
		push	ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		call	sub_2395
		push	ax
		call	sub_1754D
		add	sp, 0Ah
		cmp	word_34A78, 0
		jnz	loc_28E98
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		mov	ax, word_36C26
		add	ax, 0FFF8h
		mov	[bp+var_2], ax
		; Hack (fild [bp+var_2])
		db 0cdh
		db 03bh
		db 046h
		db 0feh
		; Hack (fcompp)
		db 0cdh
		db 03ah
		db 0d9h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jnb	short loc_28E98
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5DE2h])
		db 0cdh
		db 039h
		db 087h
		db 0e2h
		db 05dh
		mov	ax, word_36C26
		add	ax, 8
		mov	[bp+var_2], ax
		; Hack (fild [bp+var_2])
		db 0cdh
		db 03bh
		db 046h
		db 0feh
		; Hack (fcompp)
		db 0cdh
		db 03ah
		db 0d9h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jbe	short loc_28E98
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		; Hack (fcomp flt_35F82)
		db 0cdh
		db 034h
		db 01eh
		db 0e2h
		db 015h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jbe	short loc_28E98
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+5ED2h])
		db 0cdh
		db 039h
		db 087h
		db 0d2h
		db 05eh
		; Hack (fcomp flt_35F86)
		db 0cdh
		db 034h
		db 01eh
		db 0e6h
		db 015h
		; Hack (fnstsw [bp+var_2])
		db 0cdh
		db 039h
		db 07eh
		db 0feh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		sahf
		jnb	short loc_28E98
		mov	byte_34A4F, 1
		push	64h ; 'd'
		call	sub_AF20
		pop	cx
		jmp	short loc_28EA0
; ---------------------------------------------------------------------------

loc_28E98:
		inc	si

loc_28E99:
		cmp	si, 1Eh
		jl	loc_28CCD

loc_28EA0:
		pop	di
		pop	si
		leave
		retn	22h
sub_289D0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_28EA6	proc near

var_2		= word ptr -2

		enter	2, 0
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_28F0F
		mov	ax, word_3A6CA
		mov	bx, 28h	; '('
		cwd
		idiv	bx
		mov	bx, 0Ah
		mov	ax, dx
		cwd
		idiv	bx
		mov	[bp+var_2], ax
		mov	word_3984E, ax
		push	1
		call	sub_EA3E
		mov	word_39856, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		push	0
		call	sub_EA3E
		mov	word_39856, 0
		push	large 30000h
		push	large 0
		push	ds
		push	offset dword_3982A
		call	sub_1689D
		add	sp, 1Ch

locret_28F0F:
		leave
		retn
sub_28EA6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_28F11	proc near

arg_0		= word ptr  4

		push	bp
		mov	bp, sp
		cmp	[bp+arg_0], 1
		jnz	short loc_28F23
		mov	word_35DDD, 0
		jmp	loc_28FA3
; ---------------------------------------------------------------------------

loc_28F23:
		cmp	word_35DDD, 0
		jnz	short loc_28F32
		mov	word_35DDD, 1
		jmp	short loc_28FA3
; ---------------------------------------------------------------------------

loc_28F32:
		inc	word_35DDD
		cmp	word_35DDD, 2
		jnz	short loc_28F67
		mov	byte_39A32, 0
		push	1
		call	sub_EA3E
		push	ds
		push	offset word_39A29
		call	sub_16D6A
		push	0
		call	sub_EA3E
		push	ds
		push	offset word_39A29
		call	sub_16D6A
		add	sp, 0Ch
		jmp	short loc_28FA3
; ---------------------------------------------------------------------------

loc_28F67:
		cmp	word_35DDD, 10h
		jnz	short loc_28FA3
		mov	byte_39A32, 1
		push	1
		call	sub_EA3E
		push	ds
		push	offset word_39A29
		call	sub_16D6A
		push	0
		call	sub_EA3E
		push	ds
		push	offset word_39A29
		call	sub_16D6A
		add	sp, 0Ch
		mov	word_35DDD, 0
		mov	ax, 1
		pop	bp
		retn	2
; ---------------------------------------------------------------------------

loc_28FA3:
		xor	ax, ax
		pop	bp
		retn	2
sub_28F11	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_28FA9	proc near
		push	bp
		mov	bp, sp
		push	1
		call	sub_EA3E
		call	sub_288B5
		push	0
		call	sub_EA3E
		add	sp, 4
		call	sub_288B5
		pop	bp
		retn
sub_28FA9	endp

; ---------------------------------------------------------------------------

loc_28FC5:
		enter	2, 0
		mov	ax, word_3A6CA
		mov	bx, 0Fh
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_29013
		mov	ax, word_3A6CA
		mov	bx, 3Ch	; '<'
		cwd
		idiv	bx
		mov	bx, 0Fh
		mov	ax, dx
		cwd
		idiv	bx
		mov	[bp-2],	ax
		mov	al, [bp-2]
		mov	byte_39A27, al
		push	1
; ---------------------------------------------------------------------------
		db 9Ah,	1Eh, 1
		db  92h	; 톁EG16 SEGDEF [seg006,0]

; =============== S U B	R O U T	I N E =======================================


sub_28FF6	proc near
		push	cs
		push	ds
		push	offset word_39A1E
		call	sub_16D6A
		push	0
		call	sub_EA3E
		push	ds
		push	offset word_39A1E
		call	sub_16D6A
		add	sp, 0Ch

locret_29013:
		leave
		retn
sub_28FF6	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_29015	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= dword	ptr  8
arg_8		= dword	ptr  0Ch

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_2]
		push	large 0
		push	large 0
		push	70h ; 'p'
		push	40h ; '@'
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_4]
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_8]
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_4]
		add	bx, ax
		mov	ax, 184h
		sub	ax, es:[bx]
		push	ax
		mov	ax, 1
		sub	ax, si
		add	ax, ax
		les	bx, [bp+arg_8]
		add	bx, ax
		mov	ax, es:[bx]
		mov	dx, si
		add	dx, dx
		mov	bx, word ptr [bp+arg_8]
		add	bx, dx
		sub	ax, es:[bx]
		push	ax
		call	iatan2
		mov	byte ptr [bp+arg_0], al
		push	large 0
		push	large 0
		push	70h ; 'p'
		push	[bp+arg_0]
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_4]
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_8]
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		push	large 0
		push	large 0
		push	70h ; 'p'
		mov	al, 80h	; '?'
		sub	al, byte ptr [bp+arg_0]
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_4]
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_8]
		add	bx, ax
		mov	ax, es:[bx]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		pop	si
		pop	bp
		retn	0Ch
sub_29015	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_290F9	proc near

var_1		= byte ptr -1

		enter	2, 0
		push	si
		cmp	word_35DDF, 0
		jnz	short loc_2910D
		push	0
		call	sub_28F11
		mov	word_35DDF, ax

loc_2910D:
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_29589
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_29134
		push	large 9B0096h
		push	large 91008Ch
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch

loc_29134:
		cmp	word_3A6CA, 64h	; 'd'
		jge	loc_291FD
		xor	si, si
		jmp	loc_291F3
; ---------------------------------------------------------------------------

loc_29142:
		mov	ax, si
		imul	ax, 260h
		mov	bx, si
		add	bx, bx
		mov	[bx+61FCh], ax
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6200h], 0C8h ; '?'
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6208h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6204h]
		call	sub_10433
		push	7
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		push	dx
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6200h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+61FCh]
		call	sub_1754D
		add	sp, 12h
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_291D2
		push	large 700001h
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6200h]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+61FCh]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_291D2:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+61FCh]
		mov	bx, si
		add	bx, bx
		mov	[bx+6204h], ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6200h]
		mov	bx, si
		add	bx, bx
		mov	[bx+6208h], ax
		inc	si

loc_291F3:
		cmp	si, 2
		jl	loc_29142
		jmp	loc_29589
; ---------------------------------------------------------------------------

loc_291FD:
		mov	ax, word_3A6CA
		cmp	ax, word_3A780
		jge	loc_29331
		xor	si, si
		jmp	loc_29327
; ---------------------------------------------------------------------------

loc_2920D:
		or	si, si
		jnz	short loc_29216
		mov	ax, 5
		jmp	short loc_29219
; ---------------------------------------------------------------------------

loc_29216:
		mov	ax, 0FFFBh

loc_29219:
		mov	bx, si
		add	bx, bx
		add	[bx+61FCh], ax
		mov	bx, si
		add	bx, bx
		sub	word ptr [bx+6200h], 2
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6208h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6204h]
		call	sub_10433
		push	7
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		push	dx
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6200h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+61FCh]
		call	sub_1754D
		add	sp, 12h
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_29306
		push	large 700001h
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6200h]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+61FCh]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_30368
		mov	bx, si
		add	bx, bx
		mov	ax, 190h
		sub	ax, [bx+6200h]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+61FCh]
		mov	dx, si
		imul	dx, 0A0h
		add	ax, dx
		add	ax, 0FFB0h
		mov	bx, si
		add	bx, bx
		sub	ax, [bx+61FCh]
		add	ax, 0Ch
		push	ax
		call	iatan2
		mov	[bp+var_1], al
		push	large 0
		push	large 0
		push	70h ; 'p'
		push	word ptr [bp+var_1]
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6200h]
		add	ax, 0Ch
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+61FCh]
		add	ax, 0Ch
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 20h

loc_29306:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+61FCh]
		mov	bx, si
		add	bx, bx
		mov	[bx+6204h], ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6200h]
		mov	bx, si
		add	bx, bx
		mov	[bx+6208h], ax
		inc	si

loc_29327:
		cmp	si, 2
		jl	loc_2920D
		jmp	loc_29589
; ---------------------------------------------------------------------------

loc_29331:
		cmp	word_3A6CA, 0C8h ; '?'
		jge	short loc_293A3
		xor	si, si
		jmp	short loc_2939B
; ---------------------------------------------------------------------------

loc_2933D:
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6208h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6204h]
		call	sub_10433
		push	7
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		push	dx
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6200h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+61FCh]
		call	sub_1754D
		add	sp, 12h
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2939A
		push	ds
		push	offset unk_3AB9C
		push	ds
		push	offset unk_3ABA0
		push	si
		push	word ptr [bp+var_1]
		call	sub_29015

loc_2939A:
		inc	si

loc_2939B:
		cmp	si, 2
		jl	short loc_2933D
		jmp	loc_29589
; ---------------------------------------------------------------------------

loc_293A3:
		cmp	word_3A6CA, 0F0h ; '�
		jge	loc_2945E
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_293CE
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	word_3ABAC, dx
		cmp	word_3ABAC, 1
		jnz	short loc_293CE
		call	sub_28FA9

loc_293CE:
		xor	si, si
		jmp	loc_29454
; ---------------------------------------------------------------------------

loc_293D3:
		mov	ax, word_3ABAC
		shl	ax, 2
		mov	dx, 2
		sub	dx, ax
		mov	bx, si
		add	bx, bx
		add	[bx+61FCh], dx
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6208h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6204h]
		call	sub_10433
		push	7
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		push	dx
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6200h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+61FCh]
		call	sub_1754D
		add	sp, 12h
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_29443
		push	ds
		push	offset unk_3AB9C
		push	ds
		push	offset unk_3ABA0
		push	si
		push	word ptr [bp+var_1]
		call	sub_29015

loc_29443:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+61FCh]
		mov	bx, si
		add	bx, bx
		mov	[bx+6204h], ax
		inc	si

loc_29454:
		cmp	si, 2
		jl	loc_293D3
		jmp	loc_29589
; ---------------------------------------------------------------------------

loc_2945E:
		cmp	word_3A6CA, 140h
		jge	loc_2954A
		cmp	word_3A6CA, 0F0h ; '�
		jnz	short loc_294AA
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	word_3ABAE, dx
		cmp	word_3ABAE, 0
		jnz	short loc_29494
		mov	ax, word_3ABAE
		cmp	ax, word_3ABAC
		jnz	short loc_29494
		call	sub_28FA9
		jmp	short loc_294AA
; ---------------------------------------------------------------------------

loc_29494:
		cmp	word_3ABAE, 1
		jnz	short loc_294AA
		mov	ax, word_3ABAE
		cmp	ax, word_3ABAC
		jnz	short loc_294AA
		mov	word_35DDF, 0

loc_294AA:
		xor	si, si
		jmp	loc_29541
; ---------------------------------------------------------------------------

loc_294AF:
		mov	ax, word_3ABAE
		cmp	ax, word_3ABAC
		jz	short loc_294C0
		shl	ax, 2
		mov	dx, 2
		jmp	short loc_294C9
; ---------------------------------------------------------------------------

loc_294C0:
		mov	ax, word_3ABAE
		shl	ax, 3
		mov	dx, 4

loc_294C9:
		sub	dx, ax
		mov	bx, si
		add	bx, bx
		sub	[bx+61FCh], dx
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6208h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6204h]
		call	sub_10433
		push	7
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		push	dx
		push	0
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6200h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+61FCh]
		call	sub_1754D
		add	sp, 12h
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_29530
		push	ds
		push	offset unk_3AB9C
		push	ds
		push	offset unk_3ABA0
		push	si
		push	word ptr [bp+var_1]
		call	sub_29015

loc_29530:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+61FCh]
		mov	bx, si
		add	bx, bx
		mov	[bx+6204h], ax
		inc	si

loc_29541:
		cmp	si, 2
		jl	loc_294AF
		jmp	short loc_29589
; ---------------------------------------------------------------------------

loc_2954A:
		cmp	word_3A6CA, 12Ch
		jle	short loc_29589
		xor	si, si
		jmp	short loc_29575
; ---------------------------------------------------------------------------

loc_29556:
		push	large 200030h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6200h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+61FCh]
		call	sub_10433
		add	sp, 8
		inc	si

loc_29575:
		cmp	si, 2
		jl	short loc_29556
		call	sub_28FA9
		mov	word_3A6CA, 0
		mov	word_35DDF, 0

loc_29589:
		pop	si
		leave
		retn
sub_290F9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2958C	proc near

var_2		= word ptr -2

		enter	2, 0
		push	si
		push	di
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_296EC
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_295EF
		push	large 50004Ch
		push	large 480044h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch
		xor	si, si
		jmp	short loc_295EA
; ---------------------------------------------------------------------------

loc_295BD:
		call	IRand
		mov	bx, 190h
		cwd
		idiv	bx
		add	dx, 78h	; 'x'
		mov	bx, si
		add	bx, bx
		mov	[bx+6210h], dx
		call	IRand
		mov	bx, 64h	; 'd'
		cwd
		idiv	bx
		add	dx, 64h	; 'd'
		mov	bx, si
		add	bx, bx
		mov	[bx+6224h], dx
		inc	si

loc_295EA:
		cmp	si, 0Ah
		jl	short loc_295BD

loc_295EF:
		cmp	word_3A6CA, 96h	; '�
		jge	loc_296DE
		mov	ax, word_3A6CA
		add	ax, 0FFCEh
		mov	bx, 0Ah
		cwd
		idiv	bx
		mov	si, ax
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		cmp	dx, 9
		jz	loc_29698
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		shl	dx, 3
		mov	ax, 40h	; '@'
		sub	ax, dx
		mov	di, ax
		mov	ax, word_3A6CA
		dec	ax
		cwd
		idiv	bx
		shl	dx, 3
		mov	ax, 40h	; '@'
		sub	ax, dx
		mov	[bp+var_2], ax
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		or	dx, dx
		jz	short loc_29665
		push	0FFh
		push	0
		push	1
		push	[bp+var_2]
		push	[bp+var_2]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6224h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6210h]
		call	sub_17956
		add	sp, 0Eh

loc_29665:
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		cmp	dx, 8
		jz	short loc_296EC
		push	0FFh
		push	0
		push	1
		push	4
		push	di
		push	di
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6224h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6210h]
		call	sub_1786D
		add	sp, 10h
		jmp	short loc_296EC
; ---------------------------------------------------------------------------

loc_29698:
		push	6
		call	sub_125C9
		push	large 50019h
		push	4
		push	word_3A780
		push	190h
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		push	dx
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6224h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6210h]
		mov	ax, si
		imul	ax, 45h
		add	ax, 4800h
		push	ds
		push	ax
		call	sub_1209D
		add	sp, 16h
		jmp	short loc_296EC
; ---------------------------------------------------------------------------

loc_296DE:
		cmp	word_3A6CA, 0C8h ; '?'
		jle	short loc_296EC
		mov	word_3A6CA, 0

loc_296EC:
		pop	di
		pop	si
		leave
		retn
sub_2958C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_296F0	proc near

var_2C		= qword	ptr -2Ch
var_24		= qword	ptr -24h
var_1C		= qword	ptr -1Ch
var_14		= qword	ptr -14h
var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	0Ah, 0
		push	si
		cmp	word_3A6CA, 28h	; '('
		jl	loc_29A96
		cmp	byte_35DE1, 0
		jnz	short loc_2970D
		push	0
		call	sub_28F11
		mov	byte_35DE1, al

loc_2970D:
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_29A96
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_29783
		mov	word_35DE3, 0
		mov	word_3AC50, 1540h
		mov	word_3AC52, 400h
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		shl	dx, 3
		mov	ax, 4
		sub	ax, dx
		shl	ax, 4
		mov	word_3AC56, ax
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		shl	dx, 2
		mov	ax, 2
		sub	ax, dx
		shl	ax, 4
		mov	word_3AC54, ax
		push	large 8000Ah
		push	large 0F0014h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch
		push	8
		call	sub_125C9
		pop	cx
		jmp	loc_29A96
; ---------------------------------------------------------------------------

loc_29783:
		cmp	word_3A6CA, 0C8h ; '?'
		jge	loc_298A5
		cmp	word_3AC50, 1400h
		jge	short loc_2979B
		inc	word_3AC56
		jmp	short loc_2979F
; ---------------------------------------------------------------------------

loc_2979B:
		dec	word_3AC56

loc_2979F:
		cmp	word_3AC52, 0A40h
		jge	short loc_297AD
		inc	word_3AC54
		jmp	short loc_297B1
; ---------------------------------------------------------------------------

loc_297AD:
		dec	word_3AC54

loc_297B1:
		push	large 200030h
		mov	ax, word_3AC52
		sar	ax, 4
		push	ax
		mov	ax, word_3AC50
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8
		mov	ax, word_35DE3
		dec	ax
		mov	si, ax
		jmp	short loc_297F6
; ---------------------------------------------------------------------------

loc_297D5:
		push	large 0F0000h
		push	1
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6274h]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6238h]
		call	sub_1754D
		add	sp, 0Ah
		dec	si

loc_297F6:
		or	si, si
		jge	short loc_297D5
		mov	ax, word_3AC56
		add	word_3AC50, ax
		mov	ax, word_3AC54
		add	word_3AC52, ax
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A780
		or	dx, dx
		jnz	short loc_29874
		cmp	word_3AC50, 0
		jl	short loc_29874
		cmp	word_3AC50, 2600h
		jg	short loc_29874
		cmp	word_3AC52, 0
		jl	short loc_29874
		cmp	word_3AC52, 1700h
		jg	short loc_29874
		mov	ax, word_3AC50
		sar	ax, 4
		mov	bx, word_35DE3
		add	bx, bx
		mov	[bx+6238h], ax
		mov	ax, word_3AC52
		sar	ax, 4
		mov	bx, word_35DE3
		add	bx, bx
		mov	[bx+6274h], ax
		push	large 0F0000h
		push	1
		mov	ax, word_3AC52
		sar	ax, 4
		push	ax
		mov	ax, word_3AC50
		sar	ax, 4
		push	ax
		call	sub_1754D
		add	sp, 0Ah
		inc	word_35DE3

loc_29874:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		add	dx, 2
		push	dx
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		push	dx
		push	bx
		mov	ax, word_3AC52
		sar	ax, 4
		push	ax
		mov	ax, word_3AC50
		sar	ax, 4
		push	ax
		call	sub_1754D
		add	sp, 0Ah
		jmp	loc_29A96
; ---------------------------------------------------------------------------

loc_298A5:
		cmp	word_3A6CA, 190h
		jge	loc_29A83
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	loc_29995
		mov	ax, word_3AC54
		mov	[bp+var_6], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		cmp	ax, 4
		jge	short loc_298DB
		cmp	word_3AC54, 0
		jge	short loc_298D5
		mov	ax, 0FFFCh
		jmp	short loc_298D8
; ---------------------------------------------------------------------------

loc_298D5:
		mov	ax, 4

loc_298D8:
		mov	word_3AC54, ax

loc_298DB:
		mov	ax, word_3AC56
		mov	[bp+var_8], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		cmp	ax, 4
		jge	short loc_298FD
		cmp	word_3AC56, 0
		jge	short loc_298F7
		mov	ax, 0FFFCh
		jmp	short loc_298FA
; ---------------------------------------------------------------------------

loc_298F7:
		mov	ax, 4

loc_298FA:
		mov	word_3AC56, ax

loc_298FD:
		mov	ax, word_35DE3
		dec	ax
		mov	si, ax
		jmp	short loc_2997F
; ---------------------------------------------------------------------------

loc_29905:
		call	IRand
		and	al, 7Fh
		add	al, 80h	; '?'
		push	ax
		push	3
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		call	sub_12053
		add	sp, 0Ch
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6238h]
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_14])
		db 0cdh
		db 039h
		db 05eh
		db 0ech
		mov	bx, si
		add	bx, bx
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bx+6274h]
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_1C])
		db 0cdh
		db 039h
		db 05eh
		db 0e4h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_4]
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_24])
		db 0cdh
		db 039h
		db 05eh
		db 0dch
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_2]
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_2C])
		db 0cdh
		db 039h
		db 05eh
		db 0d4h
		push	1		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0
		dec	si

loc_2997F:
		or	si, si
		jge	short loc_29905
		call	sub_28FA9
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	byte_35DE2, dl

loc_29995:
		cmp	word_3AC50, 0FE00h
		jl	loc_29A29
		cmp	word_3AC50, 2800h
		jg	loc_29A29
		cmp	word_3AC52, 0FE00h
		jl	short loc_29A29
		cmp	word_3AC52, 1900h
		jg	short loc_29A29
		push	large 200030h
		mov	ax, word_3AC52
		sar	ax, 4
		push	ax
		mov	ax, word_3AC50
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8
		mov	ax, word_3AC56
		add	word_3AC50, ax
		mov	ax, word_3AC54
		add	word_3AC52, ax
		cmp	word_3AC50, 0
		jl	short loc_29A29
		cmp	word_3AC50, 260h
		jg	short loc_29A29
		cmp	word_3AC52, 0
		jl	short loc_29A29
		cmp	word_3AC52, 170h
		jg	short loc_29A29
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		add	dx, 2
		push	dx
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		push	dx
		push	bx
		push	word_3AC52
		push	word_3AC50
		call	sub_1754D
		add	sp, 0Ah

loc_29A29:
		mov	ax, word_3A6CA
		mov	bx, 10h
		cwd
		idiv	bx
		or	dx, dx
		jz	short loc_29A41
		mov	ax, word_3A6CA
		cwd
		idiv	bx
		cmp	dx, 2
		jnz	short loc_29A96

loc_29A41:
		mov	al, byte_35DE2
		cbw
		add	ax, 3E9h
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_14])
		db 0cdh
		db 039h
		db 05eh
		db 0ech
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_1C])
		db 0cdh
		db 039h
		db 05eh
		db 0e4h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_24])
		db 0cdh
		db 039h
		db 05eh
		db 0dch
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_2C])
		db 0cdh
		db 039h
		db 05eh
		db 0d4h
		push	0		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0
		jmp	short loc_29A96
; ---------------------------------------------------------------------------

loc_29A83:
		cmp	word_3A6CA, 190h
		jnz	short loc_29A96
		mov	word_3A6CA, 0
		mov	byte_35DE1, 0

loc_29A96:
		pop	si
		leave
		retn
sub_296F0	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_29A99	proc near

var_18		= byte ptr -18h
var_E		= byte ptr -0Eh
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	18h, 0
		push	si
		push	di
		cmp	word_3A6CA, 14h
		jnz	short loc_29AAC
		mov	word_3AC60, 0

loc_29AAC:
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_29D85
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_29ADC
		mov	word_3AC58, 0
		mov	word_3AC5A, 0
		mov	word_3AC5E, 2
		mov	word_3AC5C, 0
		push	0Ah
		call	sub_125C9
		pop	cx

loc_29ADC:
		mov	[bp+var_2], 0
		jmp	loc_29D0E
; ---------------------------------------------------------------------------

loc_29AE4:
		push	0Ch
		call	sub_EABB
		pop	cx
		call	IRand
		mov	bx, 8
		cwd
		idiv	bx
		mov	[bp+var_4], dx
		mov	dx, 0A6h ; '?'
		mov	al, 1
		out	dx, al		; Interrupt Controller #2, 8259A
		xor	di, di
		jmp	short loc_29B77
; ---------------------------------------------------------------------------

loc_29B04:
		mov	ax, di
		add	ax, ax
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		pop	dx
		sub	ax, dx
		mov	bx, 50h	; 'P'
		cwd
		idiv	bx
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		cwd
		idiv	bx
		pop	dx
		cmp	dx, ax
		jnz	short loc_29B7C
		mov	ax, di
		add	ax, ax
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		pop	dx
		sub	ax, dx
		mov	bx, 50h	; 'P'
		cwd
		idiv	bx
		push	ax
		mov	ax, word_3AC5C
		cwd
		idiv	bx
		pop	dx
		cmp	dx, ax
		jnz	short loc_29B76
		mov	ax, di
		add	ax, ax
		mov	dx, word_3AC5C
		add	dx, [bp+var_4]
		sub	dx, ax
		jl	short loc_29B76
		les	bx, dword_38928
		add	bx, word_3AC5C
		add	bx, [bp+var_4]
		mov	ax, di
		add	ax, ax
		sub	bx, ax
		mov	ax, es:[bx]
		mov	bx, di
		add	bx, bx
		lea	dx, [bp+var_18]
		add	bx, dx
		mov	ss:[bx], ax

loc_29B76:
		inc	di

loc_29B77:
		cmp	di, 0Ah
		jl	short loc_29B04

loc_29B7C:
		mov	dx, 0A6h ; '?'
		mov	al, 0
		out	dx, al		; Interrupt Controller #2, 8259A
		xor	di, di
		jmp	loc_29C16
; ---------------------------------------------------------------------------

loc_29B87:
		mov	ax, di
		add	ax, ax
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		pop	dx
		sub	ax, dx
		mov	bx, 50h	; 'P'
		cwd
		idiv	bx
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		cwd
		idiv	bx
		pop	dx
		cmp	dx, ax
		jnz	short loc_29C1D
		mov	ax, di
		add	ax, ax
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		pop	dx
		sub	ax, dx
		mov	bx, 50h	; 'P'
		cwd
		idiv	bx
		push	ax
		mov	ax, word_3AC5C
		cwd
		idiv	bx
		pop	dx
		cmp	dx, ax
		jnz	short loc_29C15
		mov	ax, di
		add	ax, ax
		mov	dx, word_3AC5C
		add	dx, [bp+var_4]
		sub	dx, ax
		jl	short loc_29C15
		cmp	di, 2
		jle	short loc_29BE5
		mov	ax, 4
		sub	ax, di
		jmp	short loc_29BE7
; ---------------------------------------------------------------------------

loc_29BE5:
		mov	ax, di

loc_29BE7:
		add	ax, word_3AC5E
		push	ax
		call	sub_EA71
		pop	cx
		les	bx, dword_38928
		add	bx, word_3AC5C
		add	bx, [bp+var_4]
		mov	ax, di
		add	ax, ax
		sub	bx, ax
		mov	si, di
		add	si, si
		lea	ax, [bp+var_18]
		add	si, ax
		mov	ax, ss:[si]
		and	ax, 0FFh
		mov	es:[bx], ax

loc_29C15:
		inc	di

loc_29C16:
		cmp	di, 5
		jl	loc_29B87

loc_29C1D:
		push	0Ch
		call	sub_EA71
		pop	cx
		xor	di, di
		jmp	loc_29CAC
; ---------------------------------------------------------------------------

loc_29C2A:
		mov	ax, di
		add	ax, ax
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		add	ax, 0FFF6h
		pop	dx
		sub	ax, dx
		mov	bx, 50h	; 'P'
		cwd
		idiv	bx
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		cwd
		idiv	bx
		pop	dx
		cmp	dx, ax
		jnz	short loc_29CB8
		mov	ax, di
		add	ax, ax
		push	ax
		mov	ax, word_3AC5C
		add	ax, [bp+var_4]
		add	ax, 0FFF6h
		pop	dx
		sub	ax, dx
		mov	bx, 50h	; 'P'
		cwd
		idiv	bx
		push	ax
		mov	ax, word_3AC5C
		cwd
		idiv	bx
		pop	dx
		cmp	dx, ax
		jnz	short loc_29CAB
		mov	ax, di
		add	ax, ax
		mov	dx, word_3AC5C
		add	dx, [bp+var_4]
		add	dx, 0FFF6h
		sub	dx, ax
		jl	short loc_29CAB
		les	bx, dword_38928
		add	bx, word_3AC5C
		add	bx, [bp+var_4]
		add	bx, 0FFF6h
		mov	ax, di
		add	ax, ax
		sub	bx, ax
		mov	si, di
		add	si, si
		lea	ax, [bp+var_E]
		add	si, ax
		mov	ax, ss:[si]
		and	ax, 0FFh
		mov	es:[bx], ax

loc_29CAB:
		inc	di

loc_29CAC:
		mov	ax, word_3AC60
		add	ax, 2
		cmp	ax, di
		jg	loc_29C2A

loc_29CB8:
		add	word_3AC5A, 4
		mov	ax, word_3AC58
		sar	ax, 3
		mov	dx, word_3AC5A
		shl	dx, 6
		add	ax, dx
		mov	dx, word_3AC5A
		shl	dx, 4
		add	ax, dx
		mov	word_3AC5C, ax
		cmp	word_3AC5C, 7D00h
		jl	short loc_29D06
		mov	word_3AC5A, 0
		add	word_3AC58, 20h	; ' '
		mov	ax, word_3AC58
		sar	ax, 3
		mov	dx, word_3AC5A
		shl	dx, 6
		add	ax, dx
		mov	dx, word_3AC5A
		shl	dx, 4
		add	ax, dx
		mov	word_3AC5C, ax

loc_29D06:
		call	sub_EB05
		inc	[bp+var_2]

loc_29D0E:
		cmp	[bp+var_2], 64h	; 'd'
		jl	loc_29AE4
		cmp	word_3AC58, 260h
		jle	short loc_29D85
		inc	word_3AC60
		mov	word_3A6CA, 31h	; '1'
		cmp	word_3AC60, 3
		jl	short loc_29D85
		push	0
		call	sub_11738
		push	1
		call	sub_EA3E
		mov	bx, [bp+arg_0]
		shl	bx, 2
		push	large dword ptr	[bx+140Bh]
		call	sub_10BAE
		call	sub_EC80
		push	ds
		push	offset unk_35090
		call	sub_C433
		push	0
		call	sub_EA3E
		mov	byte_34A49, 1
		call	sub_190D6
		call	sub_1889C
		push	0FFFFh
		push	word_3A6C8
		call	sub_2191C
		add	sp, 12h
		mov	word_3A6CA, 0

loc_29D85:
		pop	di
		pop	si
		leave
		retn	2
sub_29A99	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_29D8B	proc near

var_6		= word ptr -6
var_4		= byte ptr -4
var_3		= byte ptr -3
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	6, 0
		push	si
		push	di
		mov	ax, word_3A6CA
		mov	bx, 7
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_29E32
		xor	si, si
		jmp	loc_29E2B
; ---------------------------------------------------------------------------

loc_29DA5:
		cmp	byte ptr [si+1445h], 0
		jnz	short loc_29E2A
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	[bp+var_6], dx
		; Hack (fild [bp+var_6])
		db 0cdh
		db 03bh
		db 046h
		db 0fah
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+62C2h])
		db 0cdh
		db 039h
		db 09fh
		db 0c2h
		db 062h
		; Hack (wait)
		db 0cdh
		db 03dh
		cmp	[bp+arg_0], 0
		jnz	short loc_29DD4
		xor	ax, ax
		jmp	short loc_29DD7
; ---------------------------------------------------------------------------

loc_29DD4:
		mov	ax, 18Dh

loc_29DD7:
		mov	[bp+var_6], ax
		; Hack (fild [bp+var_6])
		db 0cdh
		db 03bh
		db 046h
		db 0fah
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+63B2h])
		db 0cdh
		db 039h
		db 09fh
		db 0b2h
		db 063h
		; Hack (wait)
		db 0cdh
		db 03dh
		cmp	[bp+arg_0], 0
		jnz	short loc_29E00
		call	IRand
		mov	bx, 0Fh
		cwd
		idiv	bx
		add	dx, 2
		jmp	short loc_29E10
; ---------------------------------------------------------------------------

loc_29E00:
		call	IRand
		neg	ax
		mov	bx, 0Fh
		cwd
		idiv	bx
		add	dx, 0FFF8h

loc_29E10:
		mov	[bp+var_6], dx
		; Hack (fild [bp+var_6])
		db 0cdh
		db 03bh
		db 046h
		db 0fah
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+64A2h])
		db 0cdh
		db 039h
		db 09fh
		db 0a2h
		db 064h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	byte ptr [si+1445h], 4
		jmp	short loc_29E32
; ---------------------------------------------------------------------------

loc_29E2A:
		inc	si

loc_29E2B:
		cmp	si, 1Eh
		jl	loc_29DA5

loc_29E32:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_29FE3
		xor	si, si
		jmp	loc_29FD7
; ---------------------------------------------------------------------------

loc_29E46:
		cmp	byte ptr [si+1445h], 0
		jz	loc_29FD6
		push	0Ch
		call	sub_EABB
		pop	cx
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+62C2h])
		db 0cdh
		db 039h
		db 087h
		db 0c2h
		db 062h
		; Hack (fdiv flt_35F8A)
 		db 0cdh
		db 034h
		db 036h
		db 0eah
		db 015h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+63B2h])
		db 0cdh
		db 039h
		db 087h
		db 0b2h
		db 063h
		; Hack (fmul flt_35F8E)
 		db 0cdh
		db 034h
		db 00eh
		db 0eeh
		db 015h
		; Hack (faddp st(1), st)
		db 0cdh
		db 03ah
		db 0c1h
		call	sub_2395
		mov	di, ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+62C2h])
		db 0cdh
		db 039h
		db 087h
		db 0c2h
		db 062h
		call	sub_2395
		mov	bx, 8
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		cmp	[bp+var_2], 7
		jnz	short loc_29EA2
		mov	[bp+var_2], 0

loc_29EA2:
		push	1
		call	sub_EA3E
		les	bx, dword_38928
		add	bx, di
		mov	al, es:[bx]
		mov	[bp+var_4], al
		mov	bx, word ptr dword_38928
		add	bx, di
		mov	al, es:[bx+50h]
		mov	[bp+var_3], al
		mov	ax, 0C0h ; '?'
		mov	cl, byte ptr [bp+var_2]
		sar	ax, cl
		and	[bp+var_4], al
		mov	ax, 0C0h ; '?'
		sar	ax, cl
		and	[bp+var_3], al
		push	0Ch
		call	sub_EA71
		push	0
		call	sub_EA3E
		add	sp, 6
		cmp	[bp+var_4], 0
		jz	short loc_29EF8
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_4]
		mov	es:[bx], al

loc_29EF8:
		cmp	[bp+var_3], 0
		jz	short loc_29F0B
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_3]
		mov	es:[bx+50h], al

loc_29F0B:
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+64A2h])
		db 0cdh
		db 039h
		db 087h
		db 0a2h
		db 064h
		mov	bx, si
		shl	bx, 3
		; Hack (fadd qword ptr [bx+63B2h])
		db 0cdh
		db 038h
		db 087h
		db 0b2h
		db 063h
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+63B2h])
		db 0cdh
		db 039h
		db 09fh
		db 0b2h
		db 063h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+62C2h])
		db 0cdh
		db 039h
		db 087h
		db 0c2h
		db 062h
		; Hack (fdiv flt_35F8A)
 		db 0cdh
		db 034h
		db 036h
		db 0eah
		db 015h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+63B2h])
		db 0cdh
		db 039h
		db 087h
		db 0b2h
		db 063h
		; Hack (fmul flt_35F8E)
 		db 0cdh
		db 034h
		db 00eh
		db 0eeh
		db 015h
		; Hack (faddp st(1), st)
		db 0cdh
		db 03ah
		db 0c1h
		call	sub_2395
		mov	di, ax
		cmp	di, 7CB0h
		jge	short loc_29F5B
		or	di, di
		jge	short loc_29F62

loc_29F5B:
		mov	byte ptr [si+1445h], 0
		jmp	short loc_29FD6
; ---------------------------------------------------------------------------

loc_29F62:
		push	0Ch
		call	sub_EABB
		push	1
		call	sub_EA3E
		les	bx, dword_38928
		add	bx, di
		mov	al, es:[bx]
		mov	[bp+var_4], al
		mov	bx, word ptr dword_38928
		add	bx, di
		mov	al, es:[bx+50h]
		mov	[bp+var_3], al
		mov	ax, 0C0h ; '?'
		mov	cl, byte ptr [bp+var_2]
		sar	ax, cl
		and	[bp+var_4], al
		mov	ax, 0C0h ; '?'
		sar	ax, cl
		and	[bp+var_3], al
		mov	al, [si+1445h]
		cbw
		push	ax
		call	sub_EA71
		push	0
		call	sub_EA3E
		add	sp, 8
		cmp	[bp+var_4], 0
		jz	short loc_29FC3
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_4]
		mov	es:[bx], al

loc_29FC3:
		cmp	[bp+var_3], 0
		jz	short loc_29FD6
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_3]
		mov	es:[bx+50h], al

loc_29FD6:
		inc	si

loc_29FD7:
		cmp	si, 1Eh
		jl	loc_29E46
		call	sub_EB05

loc_29FE3:
		pop	di
		pop	si
		leave
		retn	2
sub_29D8B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_29FE9	proc near
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jge	short loc_2A010
		mov	word_35E03, 0FFFFh
		push	large 0A000A0h
		push	large 0A000A0h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch

loc_2A010:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A780
		or	dx, dx
		jnz	short loc_2A022
		mov	word_35E03, 0

loc_2A022:
		cmp	word_35E03, 0
		jnz	short loc_2A031
		push	0
		call	sub_28F11
		mov	word_35E03, ax

loc_2A031:
		cmp	word_35E03, 1
		jnz	short loc_2A073
		push	6
		call	sub_125C9
		mov	word_3AF32, 1540h
		mov	word_3AF36, 400h
		push	70h ; 'p'
		push	ds
		push	offset word_3AF3A
		push	ds
		push	offset word_3AF3C
		push	17Ch
		mov	ax, word_36C26
		add	ax, 0Ch
		push	ax
		push	large 400154h
		call	sub_11FF0
		add	sp, 14h
		mov	word_35E03, 2

loc_2A073:
		cmp	word_35E03, 2
		jnz	short loc_2A0CF
		push	large 80010h
		mov	ax, word_3AF36
		sar	ax, 4
		push	ax
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8
		mov	ax, word_3AF3A
		add	word_3AF36, ax
		cmp	word_3AF36, 18C0h
		jl	short loc_2A0B0
		mov	word_35E03, 3
		call	sub_28FA9
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_2A0B0:
		mov	ax, word_3AF3C
		add	word_3AF32, ax
		push	7
		mov	ax, word_3AF36
		sar	ax, 4
		push	ax
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_17809
		add	sp, 6

loc_2A0CF:
		cmp	word_35E03, 3
		jnz	loc_2A16A
		push	0FFh
		push	0
		push	8
		push	large 60010h
		push	large 300180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_1786D
		push	0FFh
		push	0
		push	8
		push	large 60030h
		push	large 100180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_1786D
		push	0FFh
		push	0
		push	6
		push	large 70018h
		push	large 180180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_1786D
		mov	word_3AF3E, 30h	; '0'
		mov	word_3AF40, 10h
		mov	word_3AF42, 18h
		mov	ax, word_3AF32
		mov	word_3AF34, ax
		call	IRand
		mov	bx, 30h	; '0'
		cwd
		idiv	bx
		mov	ax, 190h
		sub	ax, dx
		mov	word_3AF38, ax
		push	0Ah
		call	sub_125C9
		add	sp, 32h

loc_2A16A:
		cmp	word_35E03, 3
		jl	short loc_2A175
		inc	word_35E03

loc_2A175:
		cmp	word_35E03, 5
		jl	loc_2A2BA
		mov	ax, word_35E03
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2A2BA
		push	bx
		push	10h
		push	word_3AF38
		push	word_3AF34
		call	sub_10433
		push	0FFh
		push	0
		push	8
		push	word_3AF40
		push	word_3AF3E
		push	180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_17956
		push	0FFh
		push	0
		push	8
		push	word_3AF3E
		push	word_3AF40
		push	180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_17956
		push	0FFh
		push	0
		push	6
		push	word_3AF42
		push	word_3AF42
		push	180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_17956
		add	sp, 32h
		sub	word_3AF3E, 6
		add	word_3AF40, 6
		add	word_3AF42, 4
		call	IRand
		mov	bx, 40h	; '@'
		cwd
		idiv	bx
		mov	ax, word_3AF32
		sar	ax, 4
		add	dx, ax
		add	dx, 0FFE4h
		mov	word_3AF34, dx
		call	IRand
		mov	bx, 30h	; '0'
		cwd
		idiv	bx
		mov	ax, 190h
		sub	ax, dx
		mov	word_3AF38, ax
		cmp	word_3AF3E, 8
		jg	short loc_2A245
		mov	word_35E03, 0FFFFh
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_2A245:
		push	0FFh
		push	0
		push	8
		push	5
		push	word_3AF40
		push	word_3AF3E
		push	180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_1786D
		push	0FFh
		push	0
		push	8
		push	5
		push	word_3AF3E
		push	word_3AF40
		push	180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_1786D
		push	0FFh
		push	0
		push	6
		push	7
		push	word_3AF42
		push	word_3AF42
		push	180h
		mov	ax, word_3AF32
		sar	ax, 4
		push	ax
		call	sub_1786D
		add	sp, 30h
		push	7
		push	word_3AF38
		push	word_3AF34
		call	sub_177A5
		add	sp, 6

loc_2A2BA:
		cmp	word_34A78, 0
		jnz	short loc_2A2EB
		mov	ax, word_3AF32
		sar	ax, 4
		add	ax, 20h	; ' '
		cmp	ax, word_36C26
		jle	short loc_2A2EB
		mov	ax, word_3AF32
		sar	ax, 4
		add	ax, 0FFC0h
		cmp	ax, word_36C26
		jge	short loc_2A2EB
		cmp	word_35E03, 3
		jl	short loc_2A2EB
		mov	byte_34A4F, 1

loc_2A2EB:
		pop	bp
		retn
sub_29FE9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2A2ED	proc near
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 5
		jge	short loc_2A313
		mov	byte ptr word_3AF44, 0
		push	large 8000Ah
		push	large 0C0012h
		push	ds
		push	(offset	word_3AF44+1)
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch

loc_2A313:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3AF44+1
		or	dx, dx
		jnz	loc_2A3AA
		mov	byte_386B7, 1
		push	large 0
		push	large 0
		push	38h ; '8'
		mov	al, 0
		sub	al, byte ptr word_3AF44
		push	ax
		push	large 0A00238h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	38h ; '8'
		mov	al, 80h	; '?'
		sub	al, byte ptr word_3AF44
		push	ax
		push	large 0A00238h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		push	large 0
		push	large 0
		push	38h ; '8'
		push	word_3AF44
		push	large 0A00040h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	38h ; '8'
		mov	al, byte ptr word_3AF44
		add	al, 80h	; '?'
		push	ax
		push	large 0A00040h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		mov	al, byte ptr word_3AF44
		add	al, byte ptr word_3AF44+1
		mov	byte ptr word_3AF44, al

loc_2A3AA:
		cmp	word_3A6CA, 1DFh
		jle	short loc_2A3B8
		mov	word_3A6CA, 0

loc_2A3B8:
		pop	bp
		retn
sub_2A2ED	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2A3BA	proc near

var_5		= byte ptr -5
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2A3DC
		push	large 20002h
		push	large 30004h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch

loc_2A3DC:
		mov	ax, word_3A6CA
		mov	bx, 0C8h ; '?'
		cwd
		idiv	bx
		cmp	dx, 96h	; '�
		jl	short loc_2A459
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A780
		or	dx, dx
		jnz	short loc_2A459
		call	IRand
		mov	[bp+var_5], al
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		imul	eax, 28h
		sar	eax, 8
		add	ax, 140h
		mov	[bp+var_2], ax
		mov	al, [bp+var_5]
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		imul	eax, 28h
		sar	eax, 8
		add	ax, 0B4h ; '?'
		mov	[bp+var_4], ax
		push	large 0
		push	large 480002h
		push	0
		push	0
		push	ax
		push	[bp+var_2]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h

loc_2A459:
		cmp	word_3A6CA, 12Bh
		jl	short locret_2A467
		mov	word_3A6CA, 0

locret_2A467:
		leave
		retn
sub_2A3BA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2A469	proc near

var_6		= byte ptr -6
var_5		= byte ptr -5
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		push	si
		push	di
		mov	ax, word_3A6CA
		mov	bx, 7
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2A4C5
		xor	si, si
		jmp	short loc_2A4C0
; ---------------------------------------------------------------------------

loc_2A480:
		cmp	byte ptr [si+1465h], 0
		jnz	short loc_2A4BF
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	bx, si
		add	bx, bx
		mov	[bx+65A7h], dx
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+65E3h], 190h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+661Fh], 0FFFFh
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+665Bh], 0
		mov	byte ptr [si+1465h], 4
		jmp	short loc_2A4C5
; ---------------------------------------------------------------------------

loc_2A4BF:
		inc	si

loc_2A4C0:
		cmp	si, 1Eh
		jl	short loc_2A480

loc_2A4C5:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2A697
		xor	si, si
		jmp	loc_2A68B
; ---------------------------------------------------------------------------

loc_2A4D9:
		cmp	byte ptr [si+1465h], 0
		jz	loc_2A68A
		push	0Ch
		call	sub_EABB
		mov	bx, si
		add	bx, bx
		mov	bx, [bx+665Bh]
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 4
		sar	eax, 8
		mov	bx, si
		add	bx, bx
		add	ax, [bx+65A7h]
		mov	[bp+var_4], ax
		sar	ax, 3
		mov	bx, si
		add	bx, bx
		mov	dx, [bx+65E3h]
		shl	dx, 6
		add	ax, dx
		mov	bx, si
		add	bx, bx
		mov	dx, [bx+65E3h]
		shl	dx, 4
		add	ax, dx
		mov	di, ax
		mov	ax, [bp+var_4]
		and	ax, 7
		mov	[bp+var_2], ax
		push	1
		call	sub_EA3E
		mov	ax, 0A800h
		mov	es, ax
		assume es:nothing
		mov	al, es:[di]
		mov	[bp+var_6], al
		mov	ax, 0A800h
		mov	es, ax
		mov	al, es:[di+50h]
		mov	[bp+var_5], al
		mov	ax, 0C0h ; '?'
		mov	cl, byte ptr [bp+var_2]
		sar	ax, cl
		and	[bp+var_6], al
		mov	ax, 0C0h ; '?'
		sar	ax, cl
		and	[bp+var_5], al
		push	0Ch
		call	sub_EA71
		push	0
		call	sub_EA3E
		add	sp, 8
		cmp	[bp+var_6], 0
		jz	short loc_2A58C
		les	bx, dword_38928
		assume es:nothing
		add	bx, di
		mov	al, [bp+var_6]
		mov	es:[bx], al

loc_2A58C:
		cmp	[bp+var_5], 0
		jz	short loc_2A59F
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_5]
		mov	es:[bx+50h], al

loc_2A59F:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+661Fh]
		mov	bx, si
		add	bx, bx
		add	[bx+65E3h], ax
		mov	bx, si
		add	bx, bx
		inc	word ptr [bx+665Bh]
		mov	bx, si
		add	bx, bx
		mov	bx, [bx+665Bh]
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 4
		sar	eax, 8
		mov	bx, si
		add	bx, bx
		add	ax, [bx+65A7h]
		mov	[bp+var_4], ax
		sar	ax, 3
		mov	bx, si
		add	bx, bx
		mov	dx, [bx+65E3h]
		shl	dx, 6
		add	ax, dx
		mov	bx, si
		add	bx, bx
		mov	dx, [bx+65E3h]
		shl	dx, 4
		add	ax, dx
		mov	di, ax
		mov	ax, [bp+var_4]
		and	ax, 7
		mov	[bp+var_2], ax
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+665Bh], 64h ; 'd'
		jl	short loc_2A618
		mov	byte ptr [si+1465h], 0
		jmp	short loc_2A68A
; ---------------------------------------------------------------------------

loc_2A618:
		push	0Ch
		call	sub_EABB
		push	1
		call	sub_EA3E
		mov	ax, 0A800h
		mov	es, ax
		assume es:nothing
		mov	al, es:[di]
		mov	[bp+var_6], al
		mov	ax, 0A800h
		mov	es, ax
		mov	al, es:[di+50h]
		mov	[bp+var_5], al
		mov	ax, 0C0h ; '?'
		mov	cl, byte ptr [bp+var_2]
		sar	ax, cl
		and	[bp+var_6], al
		mov	ax, 0C0h ; '?'
		sar	ax, cl
		and	[bp+var_5], al
		mov	al, [si+1465h]
		cbw
		push	ax
		call	sub_EA71
		push	0
		call	sub_EA3E
		add	sp, 8
		cmp	[bp+var_6], 0
		jz	short loc_2A677
		les	bx, dword_38928
		assume es:nothing
		add	bx, di
		mov	al, [bp+var_6]
		mov	es:[bx], al

loc_2A677:
		cmp	[bp+var_5], 0
		jz	short loc_2A68A
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_5]
		mov	es:[bx+50h], al

loc_2A68A:
		inc	si

loc_2A68B:
		cmp	si, 1Eh
		jl	loc_2A4D9
		call	sub_EB05

loc_2A697:
		pop	di
		pop	si
		leave
		retn
sub_2A469	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2A69B	proc near
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 5
		jge	short loc_2A6B0
		push	large 0
		push	large 0
		push	63h ; 'c'
		call	sub_28948

loc_2A6B0:
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_2A894
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2A735
		mov	word_3B037, 1CCh
		mov	word_3B039, 78h	; 'x'
		push	10h
		push	ds
		push	offset word_3B03B
		push	ds
		push	offset word_3B03D
		push	190h
		push	word_36C26
		push	word_3B039
		push	word_3B037
		call	sub_11FF0
		mov	ax, word_36C26
		mov	word_3B03F, ax
		push	large 480044h
		push	large 40003Ch
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 1Eh
		push	large 80032h
		push	7
		push	word_3A780
		push	190h
		push	word_36C26
		push	large 7801CCh
		push	ds
		push	offset unk_391A0

loc_2A724:
		call	sub_1209D
		push	6
		call	sub_125C9
		add	sp, 16h
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_2A735:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2A863
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_2A79B
		mov	word_3B037, 0B4h ; '?'
		mov	word_3B039, 78h	; 'x'
		push	10h
		push	ds
		push	offset word_3B03B
		push	ds
		push	offset word_3B03D
		push	190h
		mov	ax, 27Fh
		sub	ax, word_3B03F
		push	ax
		push	word_3B039
		push	word_3B037
		call	sub_11FF0
		add	sp, 12h
		push	large 80032h
		push	7
		push	word_3A780
		push	190h
		mov	ax, 27Fh
		sub	ax, word_3B03F
		push	ax
		push	word_3B039
		push	word_3B037
		push	ds
		push	offset unk_391E5
		jmp	short loc_2A724
; ---------------------------------------------------------------------------

loc_2A79B:
		cmp	word_3A6CA, 96h	; '�
		jl	loc_2A863
		cmp	word_3A6CA, 96h	; '�
		jnz	short loc_2A7FC
		mov	word_3B037, 260h
		mov	word_3B039, 0A4h ; '?'
		push	10h
		push	ds
		push	offset word_3B03B
		push	ds
		push	offset word_3B03D
		push	190h
		push	word_36C26
		push	word_3B039
		push	word_3B037
		call	sub_11FF0
		add	sp, 12h
		push	large 80032h
		push	7
		push	word_3A780
		push	190h
		push	word_36C26
		push	word_3B039
		push	word_3B037
		push	ds
		push	offset unk_3922A
		jmp	loc_2A724
; ---------------------------------------------------------------------------

loc_2A7FC:
		cmp	word_3A6CA, 0C8h ; '?'
		jl	short loc_2A863
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_2A85B
		mov	word_3B037, 18h
		mov	word_3B039, 0A4h ; '?'
		push	10h
		push	ds
		push	offset word_3B03B
		push	ds
		push	offset word_3B03D
		push	190h
		push	word_36C26
		push	word_3B039
		push	word_3B037
		call	sub_11FF0
		add	sp, 12h
		push	large 80032h
		push	7
		push	word_3A780
		push	190h
		push	word_36C26
		push	word_3B039
		push	word_3B037
		push	ds
		push	offset unk_3926F
		jmp	loc_2A724
; ---------------------------------------------------------------------------

loc_2A85B:
		cmp	word_3A6CA, 0FAh ; '�
		jge	short loc_2A886

loc_2A863:
		push	large 1400078h
		push	word_3B037
		push	word_3B039
		push	7
		call	sub_28948
		mov	ax, word_3B03D
		add	word_3B037, ax
		mov	ax, word_3B03B
		add	word_3B039, ax
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_2A886:
		cmp	word_3A6CA, 12Ch
		jle	short loc_2A894
		mov	word_3A6CA, 0

loc_2A894:
		pop	bp
		retn
sub_2A69B	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2A896	proc near
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 32h	; '2'
		jge	short loc_2A8E0
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2A8B2
		push	18Ch
		jmp	short loc_2A8C3
; ---------------------------------------------------------------------------

loc_2A8B2:
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		cmp	dx, 4
		jnz	short loc_2A8C9
		push	194h

loc_2A8C3:
		call	sub_11738
		pop	cx

loc_2A8C9:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2A8F5
		push	7
		call	sub_125C9
		pop	cx
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_2A8E0:
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2A8F5
		push	0
		call	sub_11738
		pop	cx
		mov	word_3A6CA, 0

loc_2A8F5:
		pop	bp
		retn
sub_2A896	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2A8F7	proc near

var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	6, 0
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short locret_2A947
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		mov	[bp+var_4], 40h	; '@'
		push	large 1E0001h
		push	large 10001h
		push	ss
		lea	ax, [bp+var_6]
		push	ax
		push	cs
		call	near ptr sub_28659
		push	2Ch ; ','
		push	[bp+var_6]
		push	[bp+var_4]
		push	[bp+var_2]
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 18h

locret_2A947:
		leave
		retn
sub_2A8F7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2A949	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	word_3A6CA, 5
		jge	short loc_2A960
		push	large 0
		push	large 0
		push	63h ; 'c'
		call	sub_28948

loc_2A960:
		cmp	word_3A6CA, 96h	; '�
		jl	loc_2ABD8
		cmp	word_3A6CA, 96h	; '�
		jnz	short loc_2A99E
		mov	byte ptr word_3B041, 0
		mov	byte ptr word_3B041+1, 1
		push	large 4B0046h
		push	large 41003Ch
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch

loc_2A993:
		push	6
		call	sub_125C9
		pop	cx
		jmp	loc_2ABD8
; ---------------------------------------------------------------------------

loc_2A99E:
		cmp	word_3A6CA, 0C8h ; '?'
		jge	short loc_2AA13
		mov	al, byte ptr word_3B041
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		imul	eax, 8Ch
		sar	eax, 8
		add	ax, 140h
		mov	si, ax
		mov	al, byte ptr word_3B041
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		imul	eax, 8Ch
		sar	eax, 8
		add	ax, 0A0h ; '?'
		mov	di, ax
		push	large 14000A0h
		push	si
		push	ax
		push	7
		call	sub_28948
		mov	al, byte ptr word_3B041+1
		add	byte ptr word_3B041, al
		inc	byte ptr word_3B041+1
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2ABD8
		jmp	short loc_2A993
; ---------------------------------------------------------------------------

loc_2AA13:
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_2AA36
		mov	si, 3E7h
		mov	di, 3E7h
		push	large 14000A0h
		push	si
		push	di
		push	7
		call	sub_28948
		mov	byte ptr word_3B041, 0
		jmp	loc_2ABD8
; ---------------------------------------------------------------------------

loc_2AA36:
		cmp	word_3A6CA, 190h
		jg	loc_2ABCA
		mov	ax, word_3A6CA
		mov	bx, 5
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2ABD8
		mov	al, byte ptr word_3B041
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+8FAh]
		imul	eax, 258h
		sar	eax, 8
		add	ax, 140h
		mov	si, ax
		mov	al, byte ptr word_3B041
		mov	ah, 0
		and	ax, 0FFh
		add	ax, ax
		mov	bx, ax
		movsx	eax, word ptr [bx+87Ah]
		imul	eax, 258h
		sar	eax, 8
		add	ax, 0A0h ; '?'
		mov	di, ax
		push	7
		call	sub_125C9
		pop	cx
		mov	ax, word_3A6CA
		mov	bx, 0Fh
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2AADB
		push	large 40014h
		push	7
		push	word_3A780
		push	di
		push	si
		push	large 0A00140h
		mov	ax, word_3A6CA
		add	ax, 0FF29h
		cwd
		idiv	bx
		mov	bx, 0Ah
		cwd
		idiv	bx
		imul	dx, 45h
		add	dx, 4800h
		push	ds
		push	dx
		call	sub_1209D
		jmp	short loc_2AAF6
; ---------------------------------------------------------------------------

loc_2AADB:
		push	large 0
		push	large 0
		push	64h ; 'd'
		push	word_3B041
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8

loc_2AAF6:
		add	sp, 14h
		push	large 0
		push	large 0
		push	60h ; '`'
		mov	al, byte ptr word_3B041
		add	al, 0FCh ; '�
		push	ax
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	60h ; '`'
		mov	al, byte ptr word_3B041
		add	al, 4
		push	ax
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		; Hack (jl loc_2ABC0)
		db 00fh
		db 08ch
		db 07fh
		db 000h
		push	large 0
		push	large 0
		push	40h ; '@'
		mov	al, byte ptr word_3B041
		add	al, 0FCh ; '�
		push	ax
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	40h ; '@'
		mov	al, byte ptr word_3B041
		add	al, 4
		push	ax
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_2ABC0
		push	large 0
		push	large 0
		push	40h ; '@'
		push	word_3B041
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	30h ; '0'
		push	word_3B041
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h

loc_2ABC0:
		mov	al, byte ptr word_3B041
		add	al, 0Ch
		mov	byte ptr word_3B041, al
		jmp	short loc_2ABD8
; ---------------------------------------------------------------------------

loc_2ABCA:
		cmp	word_3A6CA, 1C2h
		jnz	short loc_2ABD8
		mov	word_3A6CA, 0

loc_2ABD8:
		pop	di
		pop	si
		pop	bp
		retn
sub_2A949	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2ABDC	proc near

var_2A		= qword	ptr -2Ah
var_22		= qword	ptr -22h
var_1A		= qword	ptr -1Ah
var_12		= qword	ptr -12h
var_A		= word ptr -0Ah
var_8		= qword	ptr -8

		enter	0Ah, 0
		cmp	word_3A6CA, 32h	; '2'
		jl	locret_2AECC
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2AC27
		push	large 90008h
		push	large 70006h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch
		mov	word_3B043, 2
		mov	word_3B045, 18Fh
		mov	word_3B047, 2
		mov	word_3B049, 0FFFEh
		mov	word_3B04B, 3
		leave
		retn
; ---------------------------------------------------------------------------

loc_2AC27:
		cmp	word_3A6CA, 64h	; 'd'
		jge	loc_2AE54
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2AC8A
		push	large 200030h
		mov	ax, word_3B045
		add	ax, 0FFE0h
		push	ax
		mov	ax, word_3B043
		add	ax, 0FFE4h
		push	ax
		call	sub_10433
		add	sp, 8
		push	7
		push	word_3B04B
		push	0
		mov	ax, word_3B045
		add	ax, 0FFF0h
		push	ax
		mov	ax, word_3B043
		add	ax, 0FFE8h
		push	ax
		call	sub_1754D
		add	sp, 0Ah
		push	large 1400078h
		push	word_3B043
		push	word_3B045
		push	7
		call	sub_28948

loc_2AC8A:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_2AD01
		push	large 200030h
		mov	ax, word_3B045
		add	ax, 0FFE0h
		push	ax
		mov	ax, 278h
		sub	ax, word_3B043
		add	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8
		push	7
		push	word_3B04B
		push	0
		mov	ax, word_3B045
		add	ax, 0FFF0h
		push	ax
		mov	ax, 278h
		sub	ax, word_3B043
		push	ax
		call	sub_1754D
		add	sp, 0Ah
		push	large 1400078h
		mov	ax, 27Fh
		sub	ax, word_3B043
		push	ax
		push	word_3B045
		push	7
		call	sub_28948
		cmp	word_3B04B, 5
		jge	short loc_2ACFB
		mov	ax, word_3B04B
		inc	ax
		jmp	short loc_2ACFE
; ---------------------------------------------------------------------------

loc_2ACFB:
		mov	ax, 3

loc_2ACFE:
		mov	word_3B04B, ax

loc_2AD01:
		add	word_3B043, 2
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2AE0C
		push	6
		call	sub_125C9
		pop	cx
		mov	ax, word_3A6CA
		add	ax, 0FFC4h
		imul	ax, 0Ah
		add	ax, word_3B043
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		; Hack (fstp [bp+var_8])
		db 0cdh
		db 039h
		db 05eh
		db 0f8h
		push	4
		push	ds
		push	offset word_3B049
		push	ds
		push	offset word_3B047
		push	0
		; Hack (fld [bp+arg_8])
		db 0cdh
		db 039h
		db 046h
		db 0f8h
		call	sub_2395
		push	ax
		mov	ax, word_3B045
		add	ax, 0FFE0h
		push	ax
		push	word_3B043
		call	sub_11FF0
		add	sp, 12h
		mov	ax, word_3B043
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_12])
		db 0cdh
		db 039h
		db 05eh
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, word_3B045
		add	ax, 0FFE0h
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, word_3B047
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_22])
		db 0cdh
		db 039h
		db 05eh
		db 0deh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, word_3B049
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_2A])
		db 0cdh
		db 039h
		db 05eh
		db 0d6h
		push	1		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0
		mov	ax, 27Fh
		sub	ax, word_3B043
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_12])
		db 0cdh
		db 039h
		db 05eh
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, word_3B045
		add	ax, 0FFE0h
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, word_3B047
		neg	ax
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_22])
		db 0cdh
		db 039h
		db 05eh
		db 0deh
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, word_3B049
		mov	[bp+var_A], ax
		; Hack (fild [bp+var_A])
		db 0cdh
		db 03bh
		db 046h
		db 0f6h
		sub	sp, 8
		; Hack (fstp [bp+var_2A])
		db 0cdh
		db 039h
		db 05eh
		db 0d6h
		push	1		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0

loc_2AE0C:
		mov	ax, word_3A6CA
		mov	bx, 6
		cwd
		idiv	bx
		or	dx, dx
		jnz	locret_2AECC
		; Hack (fld flt_35F76)
		db 0cdh
		db 035h
		db 006h
		db 0d6h
		db 015h
		sub	sp, 8
		; Hack (fstp [bp+var_12])
		db 0cdh
		db 039h
		db 05eh
		db 0eeh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_22])
		db 0cdh
		db 039h
		db 05eh
		db 0deh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_2A])
		db 0cdh
		db 039h
		db 05eh
		db 0d6h
		push	0		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0
		leave
		retn
; ---------------------------------------------------------------------------

loc_2AE54:
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_2AE7A
		push	word_3B045
		mov	ax, 27Fh
		sub	ax, word_3B043
		add	ax, 2
		push	ax
		push	large 780140h
		call	sub_F2F5
		add	sp, 8
		leave
		retn
; ---------------------------------------------------------------------------

loc_2AE7A:
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2AEBE
		; Hack (fld flt_35F76)
		db 0cdh
		db 035h
		db 006h
		db 0d6h
		db 015h
		sub	sp, 8
		; Hack (fstp [bp+var_12])
		db 0cdh
		db 039h
		db 05eh
		db 0eeh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_22])
		db 0cdh
		db 039h
		db 05eh
		db 0deh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_2A])
		db 0cdh
		db 039h
		db 05eh
		db 0d6h
		push	0		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0

loc_2AEBE:
		cmp	word_3A6CA, 12Ch
		jl	short locret_2AECC
		mov	word_3A6CA, 0

locret_2AECC:
		leave
		retn
sub_2ABDC	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2AECE	proc near

var_1		= byte ptr -1

		enter	2, 0
		push	si
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_2AFDC
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2AF19
		mov	[bp+var_1], 0
		xor	si, si
		jmp	short loc_2AF11
; ---------------------------------------------------------------------------

loc_2AEEB:
		push	large 0
		push	large 0
		push	20h ; ' '
		push	word ptr [bp+var_1]
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		mov	al, [bp+var_1]
		add	al, 7
		mov	[bp+var_1], al
		inc	si

loc_2AF11:
		cmp	si, 14h
		jl	short loc_2AEEB
		jmp	loc_2AFDC
; ---------------------------------------------------------------------------

loc_2AF19:
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_2AF56
		mov	[bp+var_1], 4
		xor	si, si
		jmp	short loc_2AF4E
; ---------------------------------------------------------------------------

loc_2AF28:
		push	large 0
		push	large 0
		push	30h ; '0'
		push	word ptr [bp+var_1]
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		mov	al, [bp+var_1]
		add	al, 0Ch
		mov	[bp+var_1], al
		inc	si

loc_2AF4E:
		cmp	si, 0Ah
		jl	short loc_2AF28
		jmp	loc_2AFDC
; ---------------------------------------------------------------------------

loc_2AF56:
		cmp	word_3A6CA, 46h	; 'F'
		jnz	short loc_2AF92
		mov	[bp+var_1], 4
		xor	si, si
		jmp	short loc_2AF8B
; ---------------------------------------------------------------------------

loc_2AF65:
		push	large 0
		push	large 0
		push	40h ; '@'
		push	word ptr [bp+var_1]
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		mov	al, [bp+var_1]
		add	al, 0Eh
		mov	[bp+var_1], al
		inc	si

loc_2AF8B:
		cmp	si, 8
		jl	short loc_2AF65
		jmp	short loc_2AFDC
; ---------------------------------------------------------------------------

loc_2AF92:
		cmp	word_3A6CA, 50h	; 'P'
		jnz	short loc_2AFCE
		mov	[bp+var_1], 0Eh
		xor	si, si
		jmp	short loc_2AFC7
; ---------------------------------------------------------------------------

loc_2AFA1:
		push	large 0
		push	large 0
		push	30h ; '0'
		push	word ptr [bp+var_1]
		push	large 0A00140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		mov	al, [bp+var_1]
		add	al, 0Ah
		mov	[bp+var_1], al
		inc	si

loc_2AFC7:
		cmp	si, 0Ah
		jl	short loc_2AFA1
		jmp	short loc_2AFDC
; ---------------------------------------------------------------------------

loc_2AFCE:
		cmp	word_3A6CA, 96h	; '�
		jle	short loc_2AFDC
		mov	word_3A6CA, 0

loc_2AFDC:
		pop	si
		leave
		retn
sub_2AECE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2AFDF	proc near

var_6		= word ptr -6
var_4		= word ptr -4
var_1		= byte ptr -1

		enter	6, 0
		push	si
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_2B2B6
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2B01A
		push	large 8000Ah
		push	large 0D0010h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch
		mov	word_3B04D, 2
		mov	word_3B04F, 18Fh
		jmp	loc_2B2B6
; ---------------------------------------------------------------------------

loc_2B01A:
		cmp	word_3A6CA, 82h	; '�
		jge	loc_2B0F7
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2B07B
		push	large 200030h
		mov	ax, word_3B04F
		add	ax, 0FFE0h
		push	ax
		mov	ax, word_3B04D
		add	ax, 0FFD8h
		push	ax
		call	sub_10433
		push	7
		push	word_3B051
		push	0
		mov	ax, word_3B04F
		add	ax, 0FFF0h
		push	ax
		mov	ax, word_3B04D
		add	ax, 0FFE8h
		push	ax
		call	sub_1754D
		add	sp, 12h
		push	large 1400078h
		push	word_3B04D
		push	word_3B04F
		push	7
		call	sub_28948

loc_2B07B:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_2B0EF
		push	large 200030h
		mov	ax, word_3B04F
		add	ax, 0FFE0h
		push	ax
		mov	ax, 278h
		sub	ax, word_3B04D
		add	ax, 10h
		push	ax
		call	sub_10433
		push	7
		push	word_3B051
		push	0
		mov	ax, word_3B04F
		add	ax, 0FFF0h
		push	ax
		mov	ax, 278h
		sub	ax, word_3B04D
		push	ax
		call	sub_1754D
		add	sp, 12h
		push	large 1400078h
		mov	ax, 27Fh
		sub	ax, word_3B04D
		push	ax
		push	word_3B04F
		push	7
		call	sub_28948
		cmp	word_3B051, 5
		jge	short loc_2B0E9
		mov	ax, word_3B051
		inc	ax
		jmp	short loc_2B0EC
; ---------------------------------------------------------------------------

loc_2B0E9:
		mov	ax, 3

loc_2B0EC:
		mov	word_3B051, ax

loc_2B0EF:
		add	word_3B04D, 8
		jmp	loc_2B2B6
; ---------------------------------------------------------------------------

loc_2B0F7:
		cmp	word_3A6CA, 82h	; '�
		jnz	short loc_2B125
		push	word_3B04F
		mov	ax, 27Fh
		sub	ax, word_3B04D
		add	ax, 8
		push	ax
		push	large 780140h
		call	sub_F2F5
		add	sp, 8
		mov	word_3B04D, 0
		jmp	loc_2B2B6
; ---------------------------------------------------------------------------

loc_2B125:
		cmp	word_3A6CA, 96h	; '�
		jle	loc_2B1E6
		cmp	word_3A6CA, 15Eh
		jge	loc_2B1E6
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2B2B6
		xor	si, si
		jmp	loc_2B1CF
; ---------------------------------------------------------------------------

loc_2B14D:
		mov	ax, word_36C26
		add	ax, 10h
		sub	ax, word_3B04D
		mov	[bp+var_4], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		cmp	ax, 20h	; ' '
		jle	short loc_2B188
		push	large 0
		push	large 0
		lea	ax, [si+30h]
		push	ax
		push	0C0h ; '?'
		mov	ax, word_3B04F
		add	ax, 0FFF8h
		push	ax
		push	word_3B04D
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h

loc_2B188:
		mov	ax, word_36C26
		add	ax, 10h
		mov	dx, 27Fh
		sub	dx, word_3B04D
		sub	ax, dx
		mov	[bp+var_6], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		cmp	ax, 20h	; ' '
		jle	short loc_2B1CC
		push	large 0
		push	large 0
		lea	ax, [si+30h]
		push	ax
		push	0C0h ; '?'
		mov	ax, word_3B04F
		add	ax, 0FFF8h
		push	ax
		mov	ax, 27Fh
		sub	ax, word_3B04D
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h

loc_2B1CC:
		add	si, 10h

loc_2B1CF:
		cmp	si, 40h	; '@'
		jl	loc_2B14D
		add	word_3B04D, 20h	; ' '
		push	7
		call	sub_125C9
		pop	cx
		jmp	loc_2B2B6
; ---------------------------------------------------------------------------

loc_2B1E6:
		cmp	word_3A6CA, 15Eh
		jnz	short loc_2B1FD
		mov	word_3B04D, 0
		mov	word_3B04F, 40h	; '@'
		jmp	loc_2B2B6
; ---------------------------------------------------------------------------

loc_2B1FD:
		cmp	word_3A6CA, 226h
		jge	loc_2B2A8
		mov	ax, word_3A6CA
		cwd
		idiv	word_3A780
		or	dx, dx
		jnz	loc_2B2B6
		xor	si, si
		jmp	loc_2B29A
; ---------------------------------------------------------------------------

loc_2B21A:
		mov	ax, 190h
		sub	ax, word_3B04F
		push	ax
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		sub	dx, word_3B04D
		push	dx
		call	iatan2
		mov	[bp+var_1], al
		push	large 0
		push	large 0
		push	30h ; '0'
		push	word ptr [bp+var_1]
		push	word_3B04F
		push	word_3B04D
		push	ds
		push	offset unk_37635
		call	sub_304B8
		mov	ax, 190h
		sub	ax, word_3B04F
		push	ax
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		sub	dx, word_3B04D
		push	dx
		call	iatan2
		mov	[bp+var_1], al
		push	large 0
		push	large 0
		push	30h ; '0'
		push	word ptr [bp+var_1]
		push	word_3B04F
		mov	ax, 27Fh
		sub	ax, word_3B04D
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		inc	si

loc_2B29A:
		cmp	si, 2
		jl	loc_2B21A
		add	word_3B04D, 20h	; ' '
		jmp	short loc_2B2B6
; ---------------------------------------------------------------------------

loc_2B2A8:
		cmp	word_3A6CA, 258h
		jle	short loc_2B2B6
		mov	word_3A6CA, 0

loc_2B2B6:
		pop	si
		leave
		retn
sub_2AFDF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2B2B9	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_6		= word ptr  0Ah
arg_8		= word ptr  0Ch
arg_A		= word ptr  0Eh
arg_C		= word ptr  10h
arg_E		= word ptr  12h

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_A]
		mov	di, [bp+arg_8]
		cmp	si, 1
		jnz	short loc_2B2D1
		mov	word_3B055, 1
		jmp	short loc_2B33B
; ---------------------------------------------------------------------------

loc_2B2D1:
		cmp	word_3B055, 1
		jnz	short loc_2B349
		mov	ax, si
		cwd
		idiv	di
		or	dx, dx
		jnz	short loc_2B349
		push	0FFh
		push	0
		push	1
		push	word_3B053
		push	word_3B053
		push	[bp+arg_C]
		push	[bp+arg_E]
		call	sub_17956
		add	sp, 0Eh
		cmp	si, [bp+arg_0]
		jl	short loc_2B30B
		mov	word_3B055, 0
		jmp	short loc_2B349
; ---------------------------------------------------------------------------

loc_2B30B:
		push	0FFh
		push	0
		push	1
		push	[bp+arg_4]
		mov	ax, si
		cwd
		idiv	di
		imul	[bp+arg_6]
		add	ax, [bp+arg_2]
		push	ax
		mov	ax, si
		cwd
		idiv	di
		imul	[bp+arg_6]
		add	ax, [bp+arg_2]
		push	ax
		push	[bp+arg_C]
		push	[bp+arg_E]
		call	sub_1786D
		add	sp, 10h

loc_2B33B:
		mov	ax, si
		cwd
		idiv	di
		imul	[bp+arg_6]
		add	ax, [bp+arg_2]
		mov	word_3B053, ax

loc_2B349:
		pop	di
		pop	si
		pop	bp
		retn	10h
sub_2B2B9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2B34F	proc near

var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= byte ptr -6
var_5		= byte ptr -5
var_4		= byte ptr -4
var_3		= byte ptr -3
var_2		= word ptr -2
arg_0		= word ptr  4

		enter	0Ah, 0
		push	si
		push	di
		mov	ax, [bp+arg_0]
		mov	bx, 7
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2B3E0
		xor	si, si
		jmp	short loc_2B3DB
; ---------------------------------------------------------------------------

loc_2B366:
		cmp	byte ptr [si+1483h], 0
		jnz	short loc_2B3DA
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	[bp+var_8], dx
		; Hack (fild [bp+var_8])
		db 0cdh
		db 03bh
		db 046h
		db 0f8h
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+66B7h])
		db 0cdh
		db 039h
		db 09fh
		db 0b7h
		db 066h
		; Hack (wait)
		db 0cdh
		db 03dh
		call	IRand
		mov	bx, 190h
		cwd
		idiv	bx
		mov	[bp+var_8], dx
		; Hack (fild [bp+var_8])
		db 0cdh
		db 03bh
		db 046h
		db 0f8h
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+67A7h])
		db 0cdh
		db 039h
		db 09fh
		db 0a7h
		db 067h
		; Hack (wait)
		db 0cdh
		db 03dh
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2B3BD
		mov	ax, 0FFFAh
		jmp	short loc_2B3C0
; ---------------------------------------------------------------------------

loc_2B3BD:
		mov	ax, 6

loc_2B3C0:
		mov	[bp+var_8], ax
		; Hack (fild [bp+var_8])
		db 0cdh
		db 03bh
		db 046h
		db 0f8h
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+6897h])
		db 0cdh
		db 039h
		db 09fh
		db 097h
		db 068h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	byte ptr [si+1483h], 4
		jmp	short loc_2B3E0
; ---------------------------------------------------------------------------

loc_2B3DA:
		inc	si

loc_2B3DB:
		cmp	si, 1Eh
		jl	short loc_2B366

loc_2B3E0:
		mov	ax, [bp+arg_0]
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2B6E4
		xor	si, si
		jmp	loc_2B6D8
; ---------------------------------------------------------------------------

loc_2B3F4:
		cmp	byte ptr [si+1483h], 0
		jz	loc_2B6D7
		push	0Ch
		call	sub_EABB
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+66B7h])
		db 0cdh
		db 039h
		db 087h
		db 0b7h
		db 066h
		; Hack (fdiv flt_35F8A)
 		db 0cdh
		db 034h
		db 036h
		db 0eah
		db 015h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+67A7h])
		db 0cdh
		db 039h
		db 087h
		db 0a7h
		db 067h
		; Hack (fmul flt_35F8E)
 		db 0cdh
		db 034h
		db 00eh
		db 0eeh
		db 015h
		; Hack (faddp st(1), st)
		db 0cdh
		db 03ah
		db 0c1h
		call	sub_2395
		mov	di, ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+66B7h])
		db 0cdh
		db 039h
		db 087h
		db 0b7h
		db 066h
		call	sub_2395
		mov	bx, 8
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		push	1
		call	sub_EA3E
		add	sp, 4
		les	bx, dword_38928
		add	bx, di
		mov	al, es:[bx]
		mov	[bp+var_6], al
		mov	bx, word ptr dword_38928
		add	bx, di
		mov	al, es:[bx+50h]
		mov	[bp+var_5], al
		mov	ax, 0C0h ; '?'
		mov	cl, byte ptr [bp+var_2]
		sar	ax, cl
		and	[bp+var_6], al
		mov	ax, 0C0h ; '?'
		sar	ax, cl
		and	[bp+var_5], al
		cmp	[bp+var_2], 7
		jnz	short loc_2B4A2
		mov	bx, word ptr dword_38928
		add	bx, di
		mov	al, es:[bx+1]
		mov	[bp+var_4], al
		mov	bx, word ptr dword_38928
		add	bx, di
		mov	al, es:[bx+51h]
		mov	[bp+var_3], al
		and	[bp+var_4], 80h
		and	[bp+var_3], 80h

loc_2B4A2:
		push	0Ch
		call	sub_EA71
		push	0
		call	sub_EA3E
		add	sp, 4
		cmp	[bp+var_6], 0
		jz	short loc_2B4C5
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_6]
		mov	es:[bx], al

loc_2B4C5:
		cmp	[bp+var_5], 0
		jz	short loc_2B4D8
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_5]
		mov	es:[bx+50h], al

loc_2B4D8:
		cmp	[bp+var_2], 7
		jnz	short loc_2B504
		cmp	[bp+var_4], 0
		jz	short loc_2B4F1
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_4]
		mov	es:[bx+1], al

loc_2B4F1:
		cmp	[bp+var_3], 0
		jz	short loc_2B504
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_3]
		mov	es:[bx+51h], al

loc_2B504:
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+6897h])
		db 0cdh
		db 039h
		db 087h
		db 097h
		db 068h
		mov	bx, si
		shl	bx, 3
		; Hack (fadd qword ptr [bx+66B7h])
		db 0cdh
		db 038h
		db 087h
		db 0b7h
		db 066h
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+66B7h])
		db 0cdh
		db 039h
		db 09fh
		db 0b7h
		db 066h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+6897h])
		db 0cdh
		db 039h
		db 087h
		db 097h
		db 068h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (fcompp)
		db 0cdh
		db 03ah
		db 0d9h
		; Hack (fnstsw [bp+var_8])
		db 0cdh
		db 039h
		db 07eh
		db 0f8h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_8]
		sahf
		jbe	short loc_2B545
		; Hack (fld dbl_35F92)
		db 0cdh
		db 039h
		db 006h
		db 0f2h
		db 015h
		jmp	short loc_2B54A
; ---------------------------------------------------------------------------

loc_2B545:
		; Hack (fld dbl_35F9A)
		db 0cdh
		db 039h
		db 006h
		db 0fah
		db 015h

loc_2B54A:
		mov	bx, si
		shl	bx, 3
		; Hack (fadd qword ptr [bx+6897h])
		db 0cdh
		db 038h
		db 087h
		db 097h
		db 068h
		mov	bx, si
		shl	bx, 3
		; Hack (fstp qword ptr [bx+6897h])
		db 0cdh
		db 039h
		db 09fh
		db 097h
		db 068h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+66B7h])
		db 0cdh
		db 039h
		db 087h
		db 0b7h
		db 066h
		; Hack (fdiv flt_35F8A)
 		db 0cdh
		db 034h
		db 036h
		db 0eah
		db 015h
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+67A7h])
		db 0cdh
		db 039h
		db 087h
		db 0a7h
		db 067h
		; Hack (fmul flt_35F8E)
 		db 0cdh
		db 034h
		db 00eh
		db 0eeh
		db 015h
		; Hack (faddp st(1), st)
		db 0cdh
		db 03ah
		db 0c1h
		call	sub_2395
		mov	di, ax
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+66B7h])
		db 0cdh
		db 039h
		db 087h
		db 0b7h
		db 066h
		call	sub_2395
		mov	bx, 8
		cwd
		idiv	bx
		mov	[bp+var_2], dx
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+66B7h])
		db 0cdh
		db 039h
		db 087h
		db 0b7h
		db 066h
		; Hack (fcomp flt_35FA2)
		db 0cdh
		db 034h
		db 01eh
		db 002h
		db 016h
		; Hack (fnstsw [bp+var_8])
		db 0cdh
		db 039h
		db 07eh
		db 0f8h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_8]
		sahf
		jnb	short loc_2B604
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+66B7h])
		db 0cdh
		db 039h
		db 087h
		db 0b7h
		db 066h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (fcompp)
		db 0cdh
		db 03ah
		db 0d9h
		; Hack (fnstsw [bp+var_8])
		db 0cdh
		db 039h
		db 07eh
		db 0f8h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_8]
		sahf
		ja	short loc_2B604
		mov	bx, si
		shl	bx, 3
		; Hack (fld qword ptr [bx+6897h])
		db 0cdh
		db 039h
		db 087h
		db 097h
		db 068h
		call	sub_2395
		mov	[bp+var_A], ax
		cwd
		xor	ax, dx
		sub	ax, dx
		mov	[bp+var_8], ax
		; Hack (fild [bp+var_8])
		db 0cdh
		db 03bh
		db 046h
		db 0f8h
		; Hack (fcomp flt_35FA6)
		db 0cdh
		db 034h
		db 01eh
		db 006h
		db 016h
		; Hack (fnstsw [bp+var_8])
		db 0cdh
		db 039h
		db 07eh
		db 0f8h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	ax, [bp+var_8]
		sahf
		jnb	short loc_2B60C

loc_2B604:
		mov	byte ptr [si+1483h], 0
		jmp	loc_2B6D7
; ---------------------------------------------------------------------------

loc_2B60C:
		push	0Ch
		call	sub_EABB
		push	1
		call	sub_EA3E
		add	sp, 4
		les	bx, dword_38928
		add	bx, di
		mov	al, es:[bx]
		mov	[bp+var_6], al
		mov	bx, word ptr dword_38928
		add	bx, di
		mov	al, es:[bx+50h]
		mov	[bp+var_5], al
		mov	ax, 0C0h ; '?'
		mov	cl, byte ptr [bp+var_2]
		sar	ax, cl
		and	[bp+var_6], al
		mov	ax, 0C0h ; '?'
		sar	ax, cl
		and	[bp+var_5], al
		cmp	[bp+var_2], 7
		jnz	short loc_2B671
		mov	bx, word ptr dword_38928
		add	bx, di
		mov	al, es:[bx+1]
		mov	[bp+var_4], al
		mov	bx, word ptr dword_38928
		add	bx, di
		mov	al, es:[bx+51h]
		mov	[bp+var_3], al
		and	[bp+var_4], 80h
		and	[bp+var_3], 80h

loc_2B671:
		mov	al, [si+1483h]
		cbw
		push	ax
		call	sub_EA71
		push	0
		call	sub_EA3E
		add	sp, 4
		cmp	[bp+var_6], 0
		jz	short loc_2B698
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_6]
		mov	es:[bx], al

loc_2B698:
		cmp	[bp+var_5], 0
		jz	short loc_2B6AB
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_5]
		mov	es:[bx+50h], al

loc_2B6AB:
		cmp	[bp+var_2], 7
		jnz	short loc_2B6D7
		cmp	[bp+var_4], 0
		jz	short loc_2B6C4
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_4]
		mov	es:[bx+1], al

loc_2B6C4:
		cmp	[bp+var_3], 0
		jz	short loc_2B6D7
		les	bx, dword_38928
		add	bx, di
		mov	al, [bp+var_3]
		mov	es:[bx+51h], al

loc_2B6D7:
		inc	si

loc_2B6D8:
		cmp	si, 1Eh
		jl	loc_2B3F4
		call	sub_EB05

loc_2B6E4:
		pop	di
		pop	si
		leave
		retn	2
sub_2B34F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2B6EA	proc near

arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 32h ;	'2'
		jl	loc_2B838
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 32h ;	'2'
		jnz	short loc_2B71C
		push	large 14000B9h
		push	large 10004h
		push	large 100007h
		push	large 2000A0h
		call	sub_2B2B9

loc_2B71C:
		push	large 14000B9h
		les	bx, [bp+arg_0]
		mov	ax, es:[bx]
		add	ax, 0FFCFh
		push	ax
		push	large 40010h
		push	large 70020h
		push	5Ah ; 'Z'
		call	sub_2B2B9
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 64h ;	'd'
		jl	loc_2B838
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 64h ;	'd'
		jnz	short loc_2B780
		mov	word_3B327, 0
		mov	word_3B329, 190h
		mov	word_3B32B, 70h	; 'p'
		mov	word_3B32D+1, 0
		push	large 100012h
		push	large 180020h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch

loc_2B780:
		cmp	word_3B32D+1, 0
		jnz	short loc_2B7E7
		mov	ax, word_3B329
		add	ax, 0FF47h
		push	ax
		mov	ax, word_3B327
		add	ax, 0FEC0h
		push	ax
		call	iatan2
		mov	byte ptr word_3B32D, al
		push	large 0
		push	large 0
		push	word_3B32B
		push	word_3B32D
		push	large 0B90140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		sub	word_3B32B, 4
		mov	ax, word_3A780
		add	word_3B327, ax
		cmp	word_3B327, 280h
		jl	short loc_2B838
		mov	word_3B32D+1, 1
		mov	word_3B32B, 70h	; 'p'
		mov	word_3B327, 280h
		pop	bp
		retn	4
; ---------------------------------------------------------------------------

loc_2B7E7:
		mov	ax, word_3B329
		add	ax, 0FF47h
		push	ax
		mov	ax, word_3B327
		add	ax, 0FEC0h
		push	ax
		call	iatan2
		mov	byte ptr word_3B32D, al
		push	large 0
		push	large 0
		push	word_3B32B
		push	word_3B32D
		push	large 0B90140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		sub	word_3B32B, 4
		mov	ax, word_3A780
		sub	word_3B327, ax
		cmp	word_3B327, 0
		jge	short loc_2B838
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 0

loc_2B838:
		pop	bp
		retn	4
sub_2B6EA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2B83C	proc near

arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		push	si
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 32h ;	'2'
		jl	loc_2BA24
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 32h ;	'2'
		jnz	short loc_2B883
		mov	word_3B330, 0
		mov	word_3B332, 18Fh
		mov	word_3B334, 3
		mov	word_3B336, 3
		push	large 2D0028h
		push	large 23001Eh
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch

loc_2B883:
		cmp	word_3B332, 0B9h ; '?'
		jle	loc_2B97C
		les	bx, [bp+arg_0]
		mov	ax, es:[bx]
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2B8E3
		push	large 200020h
		mov	ax, word_3B332
		add	ax, 0FFF8h
		push	ax
		push	word_3B330
		call	sub_10433
		push	large 14000B9h
		push	word_3B330
		push	word_3B332
		push	7
		call	sub_28948
		push	7
		push	word_3B334
		push	0
		mov	ax, word_3B332
		add	ax, 0FFF0h
		push	ax
		push	word_3B330
		call	sub_1754D
		add	sp, 12h
		jmp	short loc_2B95F
; ---------------------------------------------------------------------------

loc_2B8E3:
		les	bx, [bp+arg_0]
		mov	ax, es:[bx]
		mov	bx, 2
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_2B95F
		push	large 200020h
		mov	ax, word_3B332
		add	ax, 0FFF8h
		push	ax
		mov	ax, 260h
		sub	ax, word_3B330
		push	ax
		call	sub_10433
		push	large 14000B9h
		mov	ax, 27Fh
		sub	ax, word_3B330
		push	ax
		push	word_3B332
		push	7
		call	sub_28948
		push	7
		push	word_3B334
		push	0
		mov	ax, word_3B332
		add	ax, 0FFF0h
		push	ax
		mov	ax, 260h
		sub	ax, word_3B330
		push	ax
		call	sub_1754D
		add	sp, 12h
		mov	ax, word_3B334
		mov	word_3B336, ax
		cmp	word_3B334, 5
		jge	short loc_2B954
		inc	ax
		jmp	short loc_2B957
; ---------------------------------------------------------------------------

loc_2B954:
		mov	ax, 3

loc_2B957:
		mov	word_3B334, ax
		sub	word_3B332, 8

loc_2B95F:
		les	bx, [bp+arg_0]
		mov	ax, es:[bx]
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2BA24
		push	6
		call	sub_125C9
		pop	cx
		jmp	loc_2BA24
; ---------------------------------------------------------------------------

loc_2B97C:
		push	3
		call	sub_125C9
		push	large 280020h
		mov	ax, word_3B332
		add	ax, 0FFF0h
		push	ax
		mov	ax, 260h
		sub	ax, word_3B330
		push	ax
		call	sub_10433
		push	large 320020h
		mov	ax, word_3B332
		add	ax, 0FFF0h
		push	ax
		push	word_3B330
		call	sub_10433
		mov	ax, word_3B332
		add	ax, 4
		push	ax
		push	word_3B330
		push	large 0B90140h
		call	sub_F2F5
		mov	ax, word_3B332
		add	ax, 4
		push	ax
		mov	ax, 27Fh
		sub	ax, word_3B330
		push	ax
		push	large 0B90140h
		call	sub_F2F5
		add	sp, 22h
		xor	si, si
		jmp	short loc_2BA16
; ---------------------------------------------------------------------------

loc_2B9EA:
		push	large 0
		push	large 10001h
		push	10h
		call	IRand
		push	ax
		push	0B9h ; '?'
		mov	ax, 280h
		cwd
		idiv	word_3A780
		imul	si
		push	ax
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si

loc_2BA16:
		cmp	si, word_3A780
		jl	short loc_2B9EA
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 0

loc_2BA24:
		pop	si
		pop	bp
		retn	4
sub_2B83C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2BA29	proc near

arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 50h ;	'P'
		jl	loc_2BB42
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx], 50h ;	'P'
		jnz	short loc_2BA6F
		mov	word_3B338, 0
		mov	word_3B33A, 190h
		mov	word_3B33C, 70h	; 'p'
		mov	word_3B33E+1, 0
		push	large 100012h
		push	large 180020h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch

loc_2BA6F:
		mov	ax, word_3B33E+1
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2BADA
		mov	ax, word_3B33A
		add	ax, 0FF47h
		push	ax
		mov	ax, word_3B338
		add	ax, 0FEC0h
		push	ax
		call	iatan2
		mov	byte ptr word_3B33E, al
		push	large 0
		push	large 0
		push	word_3B33C
		push	word_3B33E
		push	large 0B90140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		sub	word_3B33C, 4
		mov	ax, word_3A780
		add	word_3B338, ax
		cmp	word_3B338, 280h
		jl	short loc_2BB42
		inc	word_3B33E+1
		mov	word_3B33C, 70h	; 'p'
		mov	word_3B338, 280h
		pop	bp
		retn	4
; ---------------------------------------------------------------------------

loc_2BADA:
		mov	ax, word_3B33A
		add	ax, 0FF47h
		push	ax
		mov	ax, word_3B338
		add	ax, 0FEC0h
		push	ax
		call	iatan2
		mov	byte ptr word_3B33E, al
		push	large 0
		push	large 0
		push	word_3B33C
		push	word_3B33E
		push	large 0B90140h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		sub	word_3B33C, 4
		mov	ax, word_3A780
		sub	word_3B338, ax
		cmp	word_3B338, 0
		jge	short loc_2BB42
		inc	word_3B33E+1
		mov	word_3B338, 0
		mov	word_3B33C, 70h	; 'p'
		cmp	word_3B33E+1, 4
		jnz	short loc_2BB42
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 0

loc_2BB42:
		pop	bp
		retn	4
sub_2BA29	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2BB46	proc near

var_1A		= word ptr -1Ah
var_18		= byte ptr -18h
var_10		= byte ptr -10h
var_8		= byte ptr -8
arg_0		= word ptr  4
arg_2		= dword	ptr  6

		enter	1Ah, 0
		push	si
		push	di
		lea	ax, [bp+var_8]
		push	ss
		push	ax
		push	ds
		push	offset unk_35E7D
		mov	cx, 8
		call	SCOPY@
		lea	ax, [bp+var_10]
		push	ss
		push	ax
		push	ds
		push	offset unk_35E85
		mov	cx, 8
		call	SCOPY@
		lea	ax, [bp+var_18]
		push	ss
		push	ax
		push	ds
		push	offset unk_35E8D
		mov	cx, 8
		call	SCOPY@
		cmp	[bp+arg_0], 3E7h
		jnz	short loc_2BB9D
		xor	si, si
		jmp	short loc_2BB95
; ---------------------------------------------------------------------------

loc_2BB8A:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+14A1h], 0
		inc	si

loc_2BB95:
		cmp	si, 1Eh
		jl	short loc_2BB8A
		jmp	loc_2C0C4
; ---------------------------------------------------------------------------

loc_2BB9D:
		les	bx, [bp+arg_2]
		mov	ax, es:[bx]
		cwd
		idiv	[bp+arg_0]
		or	dx, dx
		jnz	loc_2BC43
		xor	si, si
		jmp	loc_2BC3C
; ---------------------------------------------------------------------------

loc_2BBB2:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 0
		jnz	short loc_2BC3B
		call	IRand
		mov	bx, 1900h
		cwd
		idiv	bx
		mov	bx, si
		add	bx, bx
		mov	[bx+69A1h], dx
		call	IRand
		mov	bx, 3E8h
		cwd
		idiv	bx
		add	dx, 4B0h
		mov	bx, si
		add	bx, bx
		mov	[bx+69DDh], dx
		push	28h ; '('
		push	ds
		mov	ax, si
		add	ax, ax
		add	ax, 6A55h
		push	ax
		push	ds
		mov	ax, si
		add	ax, ax
		add	ax, 6A19h
		push	ax
		push	40h ; '@'
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		push	dx
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69DDh]
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		call	sub_11FF0
		add	sp, 12h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+14A1h], 1
		jmp	short loc_2BC43
; ---------------------------------------------------------------------------

loc_2BC3B:
		inc	si

loc_2BC3C:
		cmp	si, 1Eh
		jl	loc_2BBB2

loc_2BC43:
		les	bx, [bp+arg_2]
		mov	ax, es:[bx]
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2C0C4
		xor	si, si
		jmp	loc_2BE93
; ---------------------------------------------------------------------------

loc_2BC5A:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 0
		jz	loc_2BE92
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 1
		jnz	loc_2BD09
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 18B0h
		jge	short loc_2BCCE
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 0
		jl	short loc_2BCCE
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0
		jl	short loc_2BCCE
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0F50h
		jge	short loc_2BCCE
		push	large 80010h
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69DDh]
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		call	sub_10433
		add	sp, 8

loc_2BCCE:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6A19h]
		mov	bx, si
		add	bx, bx
		add	[bx+69A1h], ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6A55h]
		mov	bx, si
		add	bx, bx
		add	[bx+69DDh], ax
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 280h
		jge	loc_2BE92
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+14A1h], 2
		jmp	loc_2BE92
; ---------------------------------------------------------------------------

loc_2BD09:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 5
		jg	loc_2BDAA
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 18B0h
		jge	short loc_2BD70
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 0
		jl	short loc_2BD70
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0
		jl	short loc_2BD70
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0F50h
		jge	short loc_2BD70
		push	large 200030h
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69DDh]
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		call	sub_10433
		add	sp, 8

loc_2BD70:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 5
		jnz	loc_2BE92
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+14A1h], 6
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		add	dx, 3
		mov	bx, si
		add	bx, bx
		mov	[bx+6A55h], dx
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6A19h], 2
		jmp	loc_2BE92
; ---------------------------------------------------------------------------

loc_2BDAA:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 6
		jnz	loc_2BE92
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 18B0h
		jge	short loc_2BE11
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 0
		jl	short loc_2BE11
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0
		jl	short loc_2BE11
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0F50h
		jge	short loc_2BE11
		push	large 80010h
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69DDh]
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		push	ax
		call	sub_10433
		add	sp, 8

loc_2BE11:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6A19h]
		mov	bx, si
		add	bx, bx
		add	[bx+69A1h], ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6A55h]
		mov	bx, si
		add	bx, bx
		add	[bx+69DDh], ax
		mov	bx, si
		add	bx, bx
		dec	word ptr [bx+6A55h]
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+6A55h], 0FFFFh
		jge	short loc_2BE75
		call	IRand
		mov	bx, 14h
		cwd
		idiv	bx
		add	dx, 1Eh
		mov	bx, si
		add	bx, bx
		mov	[bx+6A55h], dx
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+6A19h], 0
		jge	short loc_2BE6A
		mov	ax, 14h
		jmp	short loc_2BE6D
; ---------------------------------------------------------------------------

loc_2BE6A:
		mov	ax, 0FFECh

loc_2BE6D:
		mov	bx, si
		add	bx, bx
		mov	[bx+6A19h], ax

loc_2BE75:
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69DDh]
		mov	bx, 0Ah
		cwd
		idiv	bx
		cmp	ax, 190h
		jle	short loc_2BE92
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+14A1h], 0

loc_2BE92:
		inc	si

loc_2BE93:
		cmp	si, 1Eh
		jl	loc_2BC5A
		xor	si, si
		jmp	loc_2C0BD
; ---------------------------------------------------------------------------

loc_2BE9F:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 0
		jz	loc_2C0BC
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 1
		jnz	loc_2BF45
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 18B0h
		jge	loc_2C0BC
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 0
		jl	loc_2C0BC
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0
		jl	loc_2C0BC
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0F50h
		jge	loc_2C0BC
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		mov	bx, 8
		cwd
		idiv	bx
		mov	bx, si
		add	bx, bx
		push	ax
		mov	ax, [bx+69DDh]
		mov	bx, 0Ah
		cwd
		idiv	bx
		imul	ax, 50h
		pop	dx
		add	dx, ax
		mov	di, dx
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		mov	bx, 8
		cwd
		idiv	bx
		mov	[bp+var_1A], dx
		push	7
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	dx
		push	di
		call	sub_176E5
		add	sp, 0Ah
		jmp	loc_2C0BC
; ---------------------------------------------------------------------------

loc_2BF45:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 5
		jg	short loc_2BFC3
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 18B0h
		jge	short loc_2BFA6
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 0
		jl	short loc_2BFA6
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0
		jl	short loc_2BFA6
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0F50h
		jge	short loc_2BFA6
		push	7
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+14A1h]
		add	ax, 0FFFEh
		push	ax
		push	3
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+69DDh]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+69A1h]
		call	sub_1754D
		add	sp, 0Ah

loc_2BFA6:
		les	bx, [bp+arg_2]
		mov	ax, es:[bx]
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2C0BC
		mov	bx, si
		add	bx, bx
		inc	word ptr [bx+14A1h]
		jmp	loc_2C0BC
; ---------------------------------------------------------------------------

loc_2BFC3:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+14A1h], 6
		jnz	loc_2C0BC
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 18B0h
		jge	loc_2C06B
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69A1h], 0
		jl	loc_2C06B
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0
		jl	short loc_2C06B
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0F50h
		jge	short loc_2C06B
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		mov	bx, 8
		cwd
		idiv	bx
		mov	bx, si
		add	bx, bx
		push	ax
		mov	ax, [bx+69DDh]
		mov	bx, 0Ah
		cwd
		idiv	bx
		imul	ax, 50h
		pop	dx
		add	dx, ax
		mov	di, dx
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		mov	bx, 8
		cwd
		idiv	bx
		mov	[bp+var_1A], dx
		push	7
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+6A19h], 0
		jge	short loc_2C058
		mov	dx, ss
		lea	ax, [bp+var_10]
		jmp	short loc_2C05D
; ---------------------------------------------------------------------------

loc_2C058:
		mov	dx, ss
		lea	ax, [bp+var_18]

loc_2C05D:
		push	dx
		push	ax
		push	[bp+var_1A]
		push	di
		call	sub_176E5
		add	sp, 0Ah

loc_2C06B:
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0E60h
		jle	short loc_2C0BC
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+69DDh], 0F50h
		jge	short loc_2C0BC
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		cmp	ax, word_36C26
		jle	short loc_2C0BC
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+69A1h]
		mov	bx, 0Ah
		cwd
		idiv	bx
		mov	dx, word_36C26
		add	dx, 18h
		cmp	ax, dx
		jge	short loc_2C0BC
		cmp	word_34A78, 0
		jnz	short loc_2C0BC
		mov	byte_34A4F, 1

loc_2C0BC:
		inc	si

loc_2C0BD:
		cmp	si, 1Eh
		jl	loc_2BE9F

loc_2C0C4:
		pop	di
		pop	si
		leave
		retn	6
sub_2BB46	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2C0CA	proc far

var_2A		= qword	ptr -2Ah
var_22		= qword	ptr -22h
var_1A		= qword	ptr -1Ah
var_12		= qword	ptr -12h
var_5		= word ptr -5

		enter	6, 0
		push	si
		push	di
		lea	ax, [bp+var_5+1]
		push	ss
		push	ax
		push	ds
		push	offset unk_35E9B
		mov	cx, 3
		call	SCOPY@
		cmp	word_36C28, 13Ah
		jl	short loc_2C100
		cmp	word_36C28, 15Ah
		jg	short loc_2C100
		cmp	word_36C2A, 68h	; 'h'
		jl	short loc_2C100
		cmp	word_36C2A, 88h	; '�
		jle	short loc_2C110

loc_2C100:
		push	ds
		push	offset dword_3982A
		call	sub_16970
		add	sp, 4
		or	ax, ax
		jz	short loc_2C115

loc_2C110:
		mov	ax, 1
		jmp	short loc_2C117
; ---------------------------------------------------------------------------

loc_2C115:
		xor	ax, ax

loc_2C117:
		mov	byte ptr [bp+var_5], al
		cmp	byte_3A6CE, 0
		jnz	loc_2C399
		mov	word_3A6CA, 0FFFFh
		mov	word_3B433, 0
		mov	word_3B431, 0
		call	sub_232A4
		push	ds
		push	offset unk_35090
		call	sub_C433
		add	sp, 4
		mov	eax, dword_36C16
		mov	random_seed, eax

loc_2C14E:
		inc	word_3A6CA
		cmp	word_3A6CA, 1
		jnz	short loc_2C162
		mov	word_3B435, 10h
		jmp	loc_2C37F
; ---------------------------------------------------------------------------

loc_2C162:
		cmp	word_3A6CA, 2
		jnz	short loc_2C1E5
		mov	si, 20h	; ' '
		jmp	short loc_2C1DC
; ---------------------------------------------------------------------------

loc_2C16E:
		push	large [dword_3892C]
		movsx	eax, word_3B435
		mov	dx, si
		shr	dx, 5
		movzx	edx, dx
		imul	eax, edx
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		add	ax, 0B4h ; '?'
		push	ax
		movsx	eax, word_3B435
		mov	dx, si
		shr	dx, 5
		movzx	edx, dx
		imul	eax, edx
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		add	ax, 130h
		push	ax
		call	sub_1156E
		add	sp, 8
		inc	si

loc_2C1DC:
		cmp	si, 0A0h ; '?'
		jb	short loc_2C16E
		jmp	loc_2C37F
; ---------------------------------------------------------------------------

loc_2C1E5:
		cmp	word_3A6CA, 2
		jle	loc_2C37F
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2C37F
		mov	si, 20h	; ' '
		jmp	short loc_2C270
; ---------------------------------------------------------------------------

loc_2C202:
		push	large [dword_3892C]
		movsx	eax, word_3B435
		mov	dx, si
		shr	dx, 5
		movzx	edx, dx
		imul	eax, edx
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		add	ax, 0B4h ; '?'
		push	ax
		movsx	eax, word_3B435
		mov	dx, si
		shr	dx, 5
		movzx	edx, dx
		imul	eax, edx
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		add	ax, 130h
		push	ax
		call	sub_1156E
		add	sp, 8
		inc	si

loc_2C270:
		cmp	si, 0A0h ; '?'
		jb	short loc_2C202
		add	word_3B435, 10h
		xor	di, di
		mov	si, 20h	; ' '
		jmp	short loc_2C2F2
; ---------------------------------------------------------------------------

loc_2C282:
		push	large [dword_3892C]
		movsx	eax, word_3B435
		mov	dx, si
		shr	dx, 5
		movzx	edx, dx
		imul	eax, edx
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		add	ax, 0B4h ; '?'
		push	ax
		movsx	eax, word_3B435
		mov	dx, si
		shr	dx, 5
		movzx	edx, dx
		imul	eax, edx
		mov	bx, si
		shl	bx, 3
		and	bx, 0FFh
		add	bx, bx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		add	ax, 130h
		push	ax
		call	sub_1156E
		add	sp, 8
		add	di, ax
		inc	si

loc_2C2F2:
		cmp	si, 0A0h ; '?'
		jb	short loc_2C282
		cmp	di, 80h	; '?'
		jb	loc_2C37F
		mov	byte_3A6CE, 1
		mov	word_35E95, 0
		mov	word_35E97, 0
		call	IRand
		mov	bx, 6
		cwd
		idiv	bx
		inc	dx
		mov	word_35E99, dx
		mov	word_3A6CA, 0
		mov	byte_3B437, 0
		call	sub_232D3
		mov	word ptr dword_3982A, 130h
		mov	word ptr dword_3982A+2,	90h ; '�
		call	sub_28852
		push	1
		call	sub_28F11
		; Hack (fld flt_35F66)
		db 0cdh
		db 035h
		db 006h
		db 0c6h
		db 015h
		sub	sp, 8
		; Hack (fstp [bp+var_12])
		db 0cdh
		db 039h
		db 05eh
		db 0eeh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_22])
		db 0cdh
		db 039h
		db 05eh
		db 0deh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_2A])
		db 0cdh
		db 039h
		db 05eh
		db 0d6h
		push	0		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0
		jmp	loc_2CDCE
; ---------------------------------------------------------------------------

loc_2C37F:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jz	loc_2C14E
		push	1
		call	sub_E364
		pop	cx
		jmp	loc_2C14E
; ---------------------------------------------------------------------------

loc_2C399:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 1
		jnz	loc_2C4A1
		cmp	byte_3B437, 0
		jnz	short loc_2C3BE
		push	word_3A6CA
		push	word_3A6C8
		call	sub_2191C
		add	sp, 4
		mov	byte_3B437, al

loc_2C3BE:
		inc	word_3A6CA
		inc	word_3B433
		call	sub_28EA6
		call	loc_28FC5
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		sub	sp, 8
		; Hack (fstp [bp+var_12])
		db 0cdh
		db 039h
		db 05eh
		db 0eeh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_22])
		db 0cdh
		db 039h
		db 05eh
		db 0deh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_2A])
		db 0cdh
		db 039h
		db 05eh
		db 0d6h
		push	0		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0
		cmp	word_35E95, 0
		jnz	short loc_2C40D
		call	sub_2958C
		jmp	short loc_2C423
; ---------------------------------------------------------------------------

loc_2C40D:
		cmp	word_35E95, 1
		jnz	short loc_2C419
		call	sub_290F9
		jmp	short loc_2C423
; ---------------------------------------------------------------------------

loc_2C419:
		cmp	word_35E95, 2
		jnz	short loc_2C423
		call	sub_296F0

loc_2C423:
		cmp	word_3A6CA, 0
		jnz	short loc_2C440
		cmp	word_35E95, 2
		jnz	short loc_2C435
		xor	ax, ax
		jmp	short loc_2C439
; ---------------------------------------------------------------------------

loc_2C435:
		mov	ax, word_35E95
		inc	ax

loc_2C439:
		mov	word_35E95, ax
		inc	word_35E97

loc_2C440:
		push	large 200040h
		push	large 68013Ah
		push	[bp+var_5]
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_5+1]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B431
		push	ds
		push	offset word_3B433
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	short loc_2C47F
		mov	byte_3A6CE, 63h	; 'c'

loc_2C47F:
		mov	ax, word_35E97
		cmp	ax, word_35E99
		jl	loc_2CDCE
		cmp	word_3B431, 0
		jnz	loc_2CDCE
		mov	word_35E97, 0
		mov	byte_3A6CE, 2
		jmp	loc_2C7E2
; ---------------------------------------------------------------------------

loc_2C4A1:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 2
		jnz	short loc_2C4D8
		inc	word_3A6CA
		push	1
		call	sub_29A99
		call	loc_28FC5
		cmp	word_3A6CA, 0
		jnz	loc_2CDCE
		mov	byte_3A6CE, 3
		mov	word_3A6CA, 0
		call	sub_28852
		call	IRand
		mov	bx, 5
		jmp	loc_2C82A
; ---------------------------------------------------------------------------

loc_2C4D8:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 3
		jnz	loc_2C594
		inc	word_3A6CA
		inc	word_3B433
		call	sub_28EA6
		call	loc_28FC5
		push	0
		call	sub_29D8B
		cmp	word_35E95, 0
		jnz	short loc_2C502
		call	sub_29FE9
		jmp	short loc_2C50C
; ---------------------------------------------------------------------------

loc_2C502:
		cmp	word_35E95, 1
		jnz	short loc_2C511
		call	sub_2A3BA

loc_2C50C:
		call	sub_2A2ED
		jmp	short loc_2C51E
; ---------------------------------------------------------------------------

loc_2C511:
		cmp	word_3A6CA, 3Ch	; '<'
		jge	short loc_2C51E
		mov	word_3A6CA, 0

loc_2C51E:
		cmp	word_3A6CA, 0
		jnz	short loc_2C533
		mov	ax, 1
		sub	ax, word_35E95
		mov	word_35E95, ax
		inc	word_35E97

loc_2C533:
		push	large 200040h
		push	large 68013Ah
		push	[bp+var_5]
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_5+1]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B431
		push	ds
		push	offset word_3B433
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	short loc_2C572
		mov	byte_3A6CE, 63h	; 'c'

loc_2C572:
		mov	ax, word_35E97
		cmp	ax, word_35E99
		jl	loc_2CDCE
		cmp	word_3B431, 0
		jnz	loc_2CDCE
		mov	word_35E97, 0
		mov	byte_3A6CE, 4
		jmp	loc_2C7E2
; ---------------------------------------------------------------------------

loc_2C594:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 4
		jnz	short loc_2C5D6
		inc	word_3A6CA
		push	2
		call	sub_29A99
		call	loc_28FC5
		cmp	word_3A6CA, 0
		jnz	loc_2CDCE
		mov	byte_3A6CE, 5
		mov	word_3A6CA, 0
		call	sub_28852
		call	sub_232A4
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		add	dx, 3
		jmp	loc_2C82E
; ---------------------------------------------------------------------------

loc_2C5D6:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 5
		jnz	loc_2C6B0
		inc	word_3A6CA
		inc	word_3B433
		call	sub_28EA6
		call	loc_28FC5
		call	sub_2A469
		cmp	word_35E95, 0
		jnz	short loc_2C5FE
		call	sub_2A69B
		jmp	short loc_2C631
; ---------------------------------------------------------------------------

loc_2C5FE:
		cmp	word_35E95, 1
		jz	short loc_2C61F
		cmp	word_35E95, 2
		jz	short loc_2C62B
		cmp	word_35E95, 3
		jnz	short loc_2C618
		call	sub_2A949
		jmp	short loc_2C631
; ---------------------------------------------------------------------------

loc_2C618:
		cmp	word_35E95, 4
		jnz	short loc_2C624

loc_2C61F:
		call	sub_2A896
		jmp	short loc_2C631
; ---------------------------------------------------------------------------

loc_2C624:
		cmp	word_35E95, 5
		jnz	short loc_2C631

loc_2C62B:
		call	sub_2A69B
		call	sub_2A8F7

loc_2C631:
		cmp	word_3A6CA, 0
		jnz	short loc_2C64F
		cmp	word_35E95, 5
		jnz	short loc_2C644
		mov	ax, 0Ah
		jmp	short loc_2C648
; ---------------------------------------------------------------------------

loc_2C644:
		mov	ax, word_35E95
		inc	ax

loc_2C648:
		mov	word_35E95, ax
		inc	word_35E97

loc_2C64F:
		push	large 200040h
		push	large 68013Ah
		push	[bp+var_5]
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_5+1]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B431
		push	ds
		push	offset word_3B433
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	short loc_2C68E
		mov	byte_3A6CE, 63h	; 'c'

loc_2C68E:
		mov	ax, word_35E97
		cmp	ax, word_35E99
		jl	loc_2CDCE
		cmp	word_3B431, 0
		jnz	loc_2CDCE
		mov	word_35E97, 0
		mov	byte_3A6CE, 6
		jmp	loc_2C7E2
; ---------------------------------------------------------------------------

loc_2C6B0:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 6
		jnz	short loc_2C6F2
		inc	word_3A6CA
		push	3
		call	sub_29A99
		call	loc_28FC5
		cmp	word_3A6CA, 0
		jnz	loc_2CDCE
		mov	byte_3A6CE, 7
		mov	word_3A6CA, 0
		call	sub_28852
		call	sub_232A4
		call	IRand
		mov	bx, 5
		cwd
		idiv	bx
		add	dx, 2
		jmp	loc_2C82E
; ---------------------------------------------------------------------------

loc_2C6F2:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 7
		jnz	loc_2C7F1
		inc	word_3A6CA
		inc	word_3B433
		call	sub_28EA6
		call	loc_28FC5
		push	1
		call	sub_29D8B
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		sub	sp, 8
		; Hack (fstp [bp+var_12])
		db 0cdh
		db 039h
		db 05eh
		db 0eeh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_1A])
		db 0cdh
		db 039h
		db 05eh
		db 0e6h
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_22])
		db 0cdh
		db 039h
		db 05eh
		db 0deh
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		; Hack (wait)
		db 0cdh
		db 03dh
		sub	sp, 8
		; Hack (fstp [bp+var_2A])
		db 0cdh
		db 039h
		db 05eh
		db 0d6h
		push	0		; char
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_289D0
		cmp	word_35E95, 0
		jnz	short loc_2C751
		call	sub_2ABDC
		jmp	short loc_2C767
; ---------------------------------------------------------------------------

loc_2C751:
		cmp	word_35E95, 1
		jnz	short loc_2C75D
		call	sub_2AECE
		jmp	short loc_2C767
; ---------------------------------------------------------------------------

loc_2C75D:
		cmp	word_35E95, 2
		jnz	short loc_2C767
		call	sub_2AFDF

loc_2C767:
		cmp	word_3A6CA, 0
		jnz	short loc_2C784
		cmp	word_35E95, 2
		jnz	short loc_2C779
		xor	ax, ax
		jmp	short loc_2C77D
; ---------------------------------------------------------------------------

loc_2C779:
		mov	ax, word_35E95
		inc	ax

loc_2C77D:
		mov	word_35E95, ax
		inc	word_35E97

loc_2C784:
		push	large 200040h
		push	large 68013Ah
		push	[bp+var_5]
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_5+1]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B431
		push	ds
		push	offset word_3B433
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	short loc_2C7C3
		mov	byte_3A6CE, 63h	; 'c'

loc_2C7C3:
		mov	ax, word_35E97
		cmp	ax, word_35E99
		jl	loc_2CDCE
		cmp	word_3B431, 0
		jnz	loc_2CDCE
		mov	word_35E97, 0
		mov	byte_3A6CE, 8

loc_2C7E2:
		mov	word_35E95, 0
		mov	word_3A6CA, 0
		jmp	loc_2CDCE
; ---------------------------------------------------------------------------

loc_2C7F1:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 8
		jnz	short loc_2C835
		inc	word_3A6CA
		push	0
		call	sub_29A99
		call	loc_28FC5
		cmp	word_3A6CA, 0
		jnz	loc_2CDCE
		mov	byte_3A6CE, 1
		mov	word_3A6CA, 0
		call	sub_28852
		call	sub_232A4
		call	IRand
		mov	bx, 6

loc_2C82A:
		cwd
		idiv	bx
		inc	dx

loc_2C82E:
		mov	word_35E99, dx
		jmp	loc_2CDCE
; ---------------------------------------------------------------------------

loc_2C835:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 63h	; 'c'
		jnz	loc_2CAA8
		mov	word_3A6CA, 0
		mov	word_3B433, 18Fh
		push	ds
		push	offset unk_386B8
		call	sub_2FCAD
		add	sp, 4
		push	ds
		push	offset unk_37635
		call	sub_30DEE
		add	sp, 4
		xor	si, si
		jmp	short loc_2C8AE
; ---------------------------------------------------------------------------

loc_2C868:
		mov	bx, si
		imul	bx, 45h
		cmp	word ptr [bx+483Ah], 0
		jz	short loc_2C8AD
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4804h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4800h]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+480Ch]
		mov	bx, si
		imul	bx, 45h
		push	word ptr [bx+4808h]
		call	sub_F2F5
		add	sp, 8
		mov	bx, si
		imul	bx, 45h
		mov	word ptr [bx+483Ah], 0
		jmp	short $+2

loc_2C8AD:
		inc	si

loc_2C8AE:
		cmp	si, 0Ah
		jb	short loc_2C868
		mov	word_36C28, 258h
		mov	word_36C2A, 118h
		mov	word_36C26, 130h
		; Hack (fld dbl_35FAA)
		db 0cdh
		db 039h
		db 006h
		db 00ah
		db 016h
		; Hack (fstp dbl_34A9C)
		db 0cdh
		db 039h
		db 01eh
		db 0fch
		db 000h
		; Hack (wait)
		db 0cdh
		db 03dh
		mov	word_36C2C, 0
		mov	word_34A7C, 1
		mov	byte_34A57, 0
		mov	byte_34A58, 0
		push	0
		call	sub_19E48
		pop	cx
		mov	word_3B431, 0
		mov	eax, dword_36C16
		mov	random_seed, eax
		call	sub_12589
		push	1
		call	sub_EA3E
		pop	cx
		push	ds
		push	offset aBoss6_grp ; "boss6.grp"
		call	sub_10BAE
		add	sp, 4
		push	large 0
		push	large 0Fh
		call	sub_EB59
		add	sp, 8
		call	sub_232A4
		call	sub_EC80
		push	1
		call	sub_EA3E
		pop	cx
		push	ds
		push	offset aBoss6_a5_grp ; "boss6_a5.grp"
		call	sub_10C31
		add	sp, 4
		push	0
		call	sub_EA3E

loc_2C949:
		pop	cx
		inc	word_3A6CA
		cmp	word_3A6CA, 0C8h ; '?'
		jge	short loc_2C9B1
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2C980
		push	large 0F000Fh
		push	large 0F000Fh
		call	sub_EB59
		add	sp, 8
		push	1A0h
		call	sub_11738
		pop	cx

loc_2C980:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_2C99C
		call	sub_232D3
		push	182h
		call	sub_11738
		pop	cx

loc_2C99C:
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2C9B1
		push	9
		call	sub_125C9
		pop	cx

loc_2C9B1:
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_2C9C6
		call	sub_232D3
		push	0
		call	sub_11738
		pop	cx

loc_2C9C6:
		cmp	word_3A6CA, 0C8h ; '?'
		jle	loc_2CA9E
		xor	si, si
		jmp	short loc_2C9DA
; ---------------------------------------------------------------------------

loc_2C9D4:
		mov	byte ptr [si+4015h], 0
		inc	si

loc_2C9DA:
		cmp	si, 3
		jb	short loc_2C9D4
		push	ds
		push	offset unk_38988
		push	ds
		push	offset unk_35090
		push	0
		call	sub_11A94
		add	sp, 0Ah
		push	1
		call	sub_EA3E
		pop	cx
		push	ds
		push	offset aSyugen_mdt ; "syugen.MDT"
		call	sub_12549
		add	sp, 4
		call	sub_12569
		push	ds
		push	offset aBoss6_a6_grp ; "boss6_a6.grp"
		call	sub_10BAE
		add	sp, 4
		push	large 0
		push	large 6
		call	sub_EB59
		add	sp, 8
		call	sub_EC80
		mov	byte_34A49, 1
		call	sub_190D6
		call	sub_1889C
		push	0
		call	sub_11738
		pop	cx
		mov	word_3A6CA, 0
		mov	word_3B433, 0
		mov	word_35E95, 0
		mov	word_35E97, 0
		mov	byte_3A6CE, 64h	; 'd'
		mov	word_36C24, 0
		mov	word_34A78, 0
		call	sub_232A4
		push	ds
		push	offset unk_35090
		call	sub_C433
		add	sp, 4
		mov	word_3A6C8, 6
		mov	word_3A1E5, 0Ah
		mov	word_3A1E7, 3
		mov	byte_3B437, 0
		push	ds
		push	offset word_3A6CA
		push	3E7h
		call	sub_2BB46
		jmp	loc_2CDCE
; ---------------------------------------------------------------------------

loc_2CA9E:
		push	1
		call	sub_E364
		jmp	loc_2C949
; ---------------------------------------------------------------------------

loc_2CAA8:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 64h	; 'd'
		jnz	loc_2CC9E
		cmp	byte_3B437, 0
		jnz	short loc_2CACD
		push	word_3A6CA
		push	word_3A6C8
		call	sub_2191C
		add	sp, 4
		mov	byte_3B437, al

loc_2CACD:
		inc	word_3A6CA
		inc	word_3B433
		push	word_3A6CA
		call	sub_2B34F
		cmp	word_35E95, 0
		jnz	short loc_2CB05
		push	large 140018h
		push	large 200038h
		push	ds
		push	offset word_3A780
		push	cs
		call	near ptr sub_28659
		add	sp, 0Ch
		cmp	word_3A6CA, 64h	; 'd'
		jle	loc_2CBA4
		jmp	short loc_2CB51
; ---------------------------------------------------------------------------

loc_2CB05:
		cmp	word_35E95, 1
		jz	short loc_2CB6A
		cmp	word_35E95, 2
		jz	short loc_2CB84
		cmp	word_35E95, 3
		jz	loc_2CB9D
		cmp	word_35E95, 4
		jnz	short loc_2CB38
		push	ds
		push	offset word_3A6CA
		push	word_3A780
		call	sub_2BB46
		cmp	word_3A6CA, 12Ch
		jle	short loc_2CBA4
		jmp	short loc_2CB51
; ---------------------------------------------------------------------------

loc_2CB38:
		cmp	word_35E95, 5
		jnz	short loc_2CB59
		push	ds
		push	offset word_3A6CA
		push	1F4h
		call	sub_2BB46
		cmp	word_3A6CA, 0C8h ; '?'
		jle	short loc_2CBA4

loc_2CB51:
		mov	word_3A6CA, 0
		jmp	short loc_2CBA4
; ---------------------------------------------------------------------------

loc_2CB59:
		cmp	word_35E95, 6
		jnz	short loc_2CB73
		push	ds
		push	offset word_3A6CA
		push	1F4h
		call	sub_2BB46

loc_2CB6A:
		push	ds
		push	offset word_3A6CA
		call	sub_2B6EA
		jmp	short loc_2CBA4
; ---------------------------------------------------------------------------

loc_2CB73:
		cmp	word_35E95, 7
		jnz	short loc_2CB8D
		push	ds
		push	offset word_3A6CA
		push	1F4h
		call	sub_2BB46

loc_2CB84:
		push	ds
		push	offset word_3A6CA
		call	sub_2B83C
		jmp	short loc_2CBA4
; ---------------------------------------------------------------------------

loc_2CB8D:
		cmp	word_35E95, 8
		jnz	short loc_2CBA4
		push	ds
		push	offset word_3A6CA
		push	20h ; ' '
		call	sub_2BB46

loc_2CB9D:
		push	ds
		push	offset word_3A6CA
		call	sub_2BA29

loc_2CBA4:
		cmp	word_3A6CA, 0
		jnz	short loc_2CBC2
		cmp	word_35E95, 8
		jnz	short loc_2CBB7
		mov	ax, 4
		jmp	short loc_2CBBB
; ---------------------------------------------------------------------------

loc_2CBB7:
		mov	ax, word_35E95
		inc	ax

loc_2CBBB:
		mov	word_35E95, ax
		inc	word_35E97

loc_2CBC2:
		push	large 200040h
		push	large 68013Ah
		push	[bp+var_5]
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_5+1]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B431
		push	ds
		push	offset word_3B433
		call	sub_21A8A
		add	sp, 22h
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2CC7C
		call	sub_232D3
		cmp	word_35E97, 0
		jnz	short loc_2CC3F
		mov	al, byte_350A2
		cbw
		cmp	ax, 0Ah
		jge	short loc_2CC1D
		inc	byte_350A2
		jmp	short loc_2CC23
; ---------------------------------------------------------------------------

loc_2CC1D:
		mov	word_35E97, 1

loc_2CC23:
		mov	al, byte_350A3
		cbw
		cmp	ax, 0Ah
		jge	short loc_2CC30
		inc	byte_350A3

loc_2CC30:
		mov	al, byte_350A4
		cbw
		cmp	ax, 6
		jge	short loc_2CC6B
		inc	byte_350A4
		jmp	short loc_2CC6B
; ---------------------------------------------------------------------------

loc_2CC3F:
		mov	al, byte_350A2
		cbw
		or	ax, ax
		jle	short loc_2CC4D
		dec	byte_350A2
		jmp	short loc_2CC53
; ---------------------------------------------------------------------------

loc_2CC4D:
		mov	word_35E97, 0

loc_2CC53:
		mov	al, byte_350A3
		cbw
		or	ax, ax
		jle	short loc_2CC5F
		dec	byte_350A3

loc_2CC5F:
		mov	al, byte_350A4
		cbw
		or	ax, ax
		jle	short loc_2CC6B
		dec	byte_350A4

loc_2CC6B:
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4
		call	sub_232A4

loc_2CC7C:
		cmp	word_3A6C8, 0
		jg	loc_2CDCE
		call	sub_12579
		mov	byte_3A6CE, 65h	; 'e'
		mov	word_3A6CA, 0
		mov	word_3B433, 0
		jmp	loc_2CDCE
; ---------------------------------------------------------------------------

loc_2CC9E:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 65h	; 'e'
		jnz	loc_2CDCE
		push	1
		call	sub_EA3E
		pop	cx
		push	ds
		push	offset aBoss6_a6_grp ; "boss6_a6.grp"
		call	sub_10BAE
		add	sp, 4
		push	large 0
		push	large 6
		call	sub_EB59
		add	sp, 8
		call	sub_232A4
		call	sub_EC80
		push	0
		call	sub_EA3E

loc_2CCDC:
		pop	cx
		inc	word_3A6CA
		cmp	word_3A6CA, 0E6h ; '�
		jge	short loc_2CD33
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2CCFF
		push	1A0h
		call	sub_11738
		pop	cx

loc_2CCFF:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_2CD16
		push	182h
		call	sub_11738
		pop	cx

loc_2CD16:
		cmp	word_3A6CA, 0C8h ; '?'
		jge	short loc_2CD33
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2CD33
		push	9
		call	sub_125C9
		pop	cx

loc_2CD33:
		cmp	word_3A6CA, 0AAh ; '?'
		jnz	short loc_2CD40
		call	sub_12589

loc_2CD40:
		cmp	word_3A6CA, 0BEh ; '?'
		jle	short loc_2CDA0
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2CD98
		xor	si, si
		jmp	short loc_2CD87
; ---------------------------------------------------------------------------

loc_2CD59:
		xor	di, di
		jmp	short loc_2CD81
; ---------------------------------------------------------------------------

loc_2CD5D:
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+di+6F0h]
		push	ax
		mov	ax, 6F0h
		or	ax, ax
		jbe	short loc_2CD72
		mov	al, 1
		jmp	short loc_2CD74
; ---------------------------------------------------------------------------

loc_2CD72:
		mov	al, 0

loc_2CD74:
		pop	dx
		sub	dl, al
		mov	bx, si
		imul	bx, 3
		mov	[bx+di+6F0h], dl
		inc	di

loc_2CD81:
		cmp	di, 3
		jb	short loc_2CD5D
		inc	si

loc_2CD87:
		cmp	si, 10h
		jb	short loc_2CD59
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4

loc_2CD98:
		cmp	word_3A6CA, 0E6h ; '�
		jg	short loc_2CDAA

loc_2CDA0:
		push	2
		call	sub_E364
		jmp	loc_2CCDC
; ---------------------------------------------------------------------------

loc_2CDAA:
		push	0
		call	sub_11738
		pop	cx
		push	cs
		call	near ptr sub_28908
		xor	si, si
		jmp	short loc_2CDC4
; ---------------------------------------------------------------------------

loc_2CDBA:
		add	dword_34A5A, 2710h
		inc	si

loc_2CDC4:
		cmp	si, 5
		jb	short loc_2CDBA
		mov	byte_35DAA, 1

loc_2CDCE:
		pop	di
		pop	si
		leave
		retf
sub_2C0CA	endp

seg036		ends

; ===========================================================================

; Segment type:	Pure code
seg037		segment	byte public 'CODE' use16
		assume cs:seg037
		;org 2
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2CDD2	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h

		push	bp

loc_2CDD3:
		mov	bp, sp
		mov	dx, [bp+arg_6]
		cmp	byte_34A30, 0
		jnz	short loc_2CDE4
		mov	ax, [bp+arg_4]
		jmp	short loc_2CE0F
; ---------------------------------------------------------------------------

loc_2CDE4:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_2CDF1
		mov	ax, dx
		jmp	short loc_2CE0F
; ---------------------------------------------------------------------------

loc_2CDF1:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_2CDFF
		mov	ax, [bp+arg_8]
		jmp	short loc_2CE0F
; ---------------------------------------------------------------------------

loc_2CDFF:
		mov	al, byte_34A30
		cbw
		cmp	ax, 3
		jnz	short loc_2CE0D
		mov	ax, [bp+arg_A]
		jmp	short loc_2CE0F
; ---------------------------------------------------------------------------

loc_2CE0D:
		mov	ax, dx

loc_2CE0F:
		les	bx, [bp+arg_0]
		mov	es:[bx], ax
		pop	bp
		retf
sub_2CDD2	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2CE17	proc far

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_6]
		cmp	[bp+arg_8], 63h	; 'c'
		jnz	short loc_2CE36
		mov	word_35FF4, 3E7h
		mov	word_35FF6, 3E7h
		jmp	short loc_2CEA9
; ---------------------------------------------------------------------------

loc_2CE36:
		cmp	word_35FF4, 3E7h
		jz	short loc_2CE7A
		cmp	word_35FF6, 3E7h
		jz	short loc_2CE7A
		cmp	word_35FF4, 0
		jl	short loc_2CE7A
		cmp	word_35FF4, 280h
		jge	short loc_2CE7A
		cmp	word_35FF6, 0
		jl	short loc_2CE7A
		cmp	word_35FF6, 190h
		jge	short loc_2CE7A
		push	word_35FF6
		push	word_35FF4
		push	[bp+arg_2]
		push	[bp+arg_0]
		call	sub_F2F5
		add	sp, 8

loc_2CE7A:
		or	si, si
		jl	short loc_2CEA1
		cmp	si, 280h
		jge	short loc_2CEA1
		or	di, di
		jl	short loc_2CEA1
		cmp	di, 190h
		jge	short loc_2CEA1
		push	[bp+arg_8]
		push	di
		push	si
		push	[bp+arg_2]
		push	[bp+arg_0]
		call	sub_F342
		add	sp, 0Ah

loc_2CEA1:
		mov	word_35FF4, si
		mov	word_35FF6, di

loc_2CEA9:
		pop	di
		pop	si
		pop	bp
		retf
sub_2CE17	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2CEAD	proc far

var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	8, 0
		push	si
		push	di
		mov	byte_360CC, 1
		push	large 200005h
		call	sub_C7C
		push	ds
		push	offset aBoss7_d1_grp ; "boss7_d1.grp"
		call	sub_10BAE
		push	ds
		push	offset unk_35090
		call	sub_C433
		push	4
		call	sub_2091E
		push	1
		call	sub_EA3E
		push	ds
		push	offset aBoss8_a1_grp ; "boss8_a1.grp"
		call	sub_10BAE
		push	0
		call	sub_EA3E
		push	ds
		push	offset aAlice_mdt_0 ; "ALICE.MDT"
		call	sub_12549
		push	ds
		push	offset aZigoku_mde_1 ; "zigoku.mde"
		call	sub_12559
		add	sp, 1Ah
		call	sub_12569
		xor	di, di
		jmp	short loc_2CF26
; ---------------------------------------------------------------------------

loc_2CF11:
		xor	si, si
		jmp	short loc_2CF20
; ---------------------------------------------------------------------------

loc_2CF15:
		mov	bx, di
		imul	bx, 3
		mov	byte ptr [bx+si+6F0h], 0
		inc	si

loc_2CF20:
		cmp	si, 3
		jl	short loc_2CF15
		inc	di

loc_2CF26:
		cmp	di, 10h
		jl	short loc_2CF11
		push	ds
		push	offset unk_35090
		call	sub_EB10
		push	large 2000E1h
		call	sub_C7C
		mov	word_39854, 1
		push	0
		push	ds
		push	offset aBoss8_1_bos ; "boss8_1.bos"
		push	ds
		push	offset dword_3982A
		call	sub_1568F
		mov	word_39854, 0
		mov	word_39886, 1
		push	1
		push	ds
		push	offset aBoss8_e1_bos ; "boss8_e1.bos"
		push	ds
		push	offset dword_3985C
		call	sub_1568F
		mov	word_39886, 0
		mov	word_398B8, 1
		push	2
		push	ds
		push	offset aBoss8_e2_bos ; "boss8_e2.bos"
		push	ds
		push	offset dword_3988E
		call	sub_1568F
		add	sp, 22h
		mov	word_398B8, 0
		xor	di, di
		mov	si, 20h	; ' '
		mov	[bp+var_2], 0
		mov	[bp+var_8], 0

loc_2CFA2:
		push	di
		call	sub_11738
		pop	cx
		add	di, si
		cmp	[bp+var_2], 0
		jnz	short loc_2CFBA
		cmp	di, 64h	; 'd'
		jle	short loc_2CFBA
		inc	[bp+var_2]
		dec	si

loc_2CFBA:
		cmp	[bp+var_2], 1
		jnz	short loc_2CFCA
		cmp	di, 0C8h ; '?'
		jle	short loc_2CFCA
		inc	[bp+var_2]
		dec	si

loc_2CFCA:
		cmp	[bp+var_2], 2
		jnz	short loc_2CFDA
		cmp	di, 12Ch
		jle	short loc_2CFDA
		inc	[bp+var_2]
		dec	si

loc_2CFDA:
		cmp	[bp+var_2], 3
		jnz	short loc_2CFF0
		cmp	di, 190h
		jle	short loc_2CFF0
		mov	[bp+var_2], 0
		dec	si
		sub	di, 190h

loc_2CFF0:
		or	si, si
		jle	loc_2D079
		mov	ax, [bp+var_8]
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2D06B
		mov	[bp+var_4], 0
		jmp	short loc_2D059
; ---------------------------------------------------------------------------

loc_2D00A:
		mov	[bp+var_6], 0
		jmp	short loc_2D050
; ---------------------------------------------------------------------------

loc_2D011:
		mov	bx, [bp+var_4]
		imul	bx, 3
		add	bx, [bp+var_6]
		mov	al, [bx+3FE8h]
		mov	bx, [bp+var_4]
		imul	bx, 3
		add	bx, [bp+var_6]
		cmp	al, [bx+6F0h]
		jle	short loc_2D031
		mov	al, 1
		jmp	short loc_2D033
; ---------------------------------------------------------------------------

loc_2D031:
		mov	al, 0

loc_2D033:
		mov	bx, [bp+var_4]
		imul	bx, 3
		add	bx, [bp+var_6]
		add	al, [bx+6F0h]
		mov	bx, [bp+var_4]
		imul	bx, 3
		add	bx, [bp+var_6]
		mov	[bx+6F0h], al
		inc	[bp+var_6]

loc_2D050:
		cmp	[bp+var_6], 3
		jl	short loc_2D011
		inc	[bp+var_4]

loc_2D059:
		cmp	[bp+var_4], 10h
		jl	short loc_2D00A
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4

loc_2D06B:
		inc	[bp+var_8]
		push	1
		call	sub_E364
		pop	cx
		jmp	loc_2CFA2
; ---------------------------------------------------------------------------

loc_2D079:
		push	0
		call	sub_11738
		push	0
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		push	1
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	1
		call	sub_1117C
		push	2
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	2
		call	sub_1117C
		push	3
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	3
		call	sub_1117C
		push	4
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	4
		call	sub_1117C
		push	5
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	5
		call	sub_1117C
		add	sp, 32h
		push	6
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	6
		call	sub_1117C
		push	28h ; '('
		call	sub_E364
		add	sp, 0Ah
		xor	si, si
		jmp	short loc_2D120
; ---------------------------------------------------------------------------

loc_2D0EC:
		mov	ax, si
		mov	bx, 2
		cwd
		idiv	bx
		shl	dx, 5
		mov	ax, 1A0h
		sub	ax, dx
		push	ax
		call	sub_11738
		pop	cx
		mov	ax, si
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2D117
		push	9
		call	sub_125C9
		pop	cx

loc_2D117:
		push	1
		call	sub_E364
		pop	cx
		inc	si

loc_2D120:
		cmp	si, 20h	; ' '
		jl	short loc_2D0EC
		mov	di, 190h
		jmp	short loc_2D145
; ---------------------------------------------------------------------------

loc_2D12A:
		push	di
		call	sub_11738
		push	20h ; ' '
		push	di
		call	sub_11816
		push	1
		call	sub_E364
		add	sp, 8
		sub	di, 20h	; ' '

loc_2D145:
		or	di, di
		jge	short loc_2D12A
		xor	si, si
		jmp	short loc_2D16E
; ---------------------------------------------------------------------------

loc_2D14D:
		mov	ax, si
		mov	bx, 2
		cwd
		idiv	bx
		shl	dx, 4
		mov	ax, 1A0h
		sub	ax, dx
		push	ax
		call	sub_11738
		push	1
		call	sub_E364
		add	sp, 4
		inc	si

loc_2D16E:
		cmp	si, 20h	; ' '
		jl	short loc_2D14D
		push	1Eh
		call	sub_E364
		push	large 0F000Fh
		push	large 0F0009h
		call	sub_EB59
		push	ds
		push	offset aBoss8_d1_grp ; "boss8_d1.grp"
		call	sub_10C71
		push	ds
		push	offset aBoss8_d2_grp ; "boss8_d2.grp"
		call	sub_10C71
		push	ds
		push	offset aBoss8_d3_grp ; "boss8_d3.grp"
		call	sub_10C71
		push	ds
		push	offset aBoss8_d4_grp ; "boss8_d4.grp"
		call	sub_10C71
		add	sp, 1Ah
		xor	di, di
		jmp	short loc_2D1F0
; ---------------------------------------------------------------------------

loc_2D1B6:
		mov	al, byte_350AB
		cbw
		or	ax, ax
		jle	short loc_2D1C2
		dec	byte_350AB

loc_2D1C2:
		mov	al, byte_350AC
		cbw
		cmp	ax, 9
		jle	short loc_2D1CF
		dec	byte_350AC

loc_2D1CF:
		mov	al, byte_350AD
		cbw
		cmp	ax, 0Ah
		jle	short loc_2D1DC
		dec	byte_350AD

loc_2D1DC:
		push	ds
		push	offset unk_35090
		call	sub_EB10
		push	0Ah
		call	sub_E364
		add	sp, 6
		inc	di

loc_2D1F0:
		cmp	di, 10h
		jl	short loc_2D1B6
		call	sub_EC80
		pop	di
		pop	si
		leave
		retf
sub_2CEAD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D1FE	proc far
		push	bp
		mov	bp, sp
		call	sub_232A4
		nop
		push	cs
		call	near ptr sub_2D20D
		pop	bp
		retf
sub_2D1FE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D20D	proc far
		push	bp
		mov	bp, sp
		mov	word_3A6C8, 12h
		mov	word_3A1E5, 10h
		mov	word_3A1E7, 0Ah
		mov	byte_3A6CE, 0
		mov	word_3A6CA, 0
		mov	word_35FF2, 1
		mov	word_35FF0, 0
		mov	word_35FEE, 2
		pop	bp
		retf
sub_2D20D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D241	proc far
		push	bp
		mov	bp, sp
		push	si
		push	0
		call	sub_169CB
		push	1
		call	sub_169CB
		push	2
		call	sub_169CB
		add	sp, 6
		xor	si, si
		jmp	short loc_2D269
; ---------------------------------------------------------------------------

loc_2D261:
		push	si
		call	sub_110ED
		pop	cx
		inc	si

loc_2D269:
		cmp	si, 7
		jl	short loc_2D261
		pop	si
		pop	bp
		retf
sub_2D241	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D271	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	word_35FF2, 0
		jz	loc_2D340
		cmp	word_35FEE, si
		jz	loc_2D340
		push	1
		call	sub_EA3E
		push	si
		push	large 500118h
		push	ds
		push	offset dword_3982A
		call	sub_1588A
		push	0
		call	sub_EA3E
		push	si
		push	large 500118h
		push	ds
		push	offset dword_3982A
		call	sub_1588A
		add	sp, 18h
		cmp	word_35FF0, 3
		jnz	short loc_2D2EF
		push	1
		call	sub_EA3E
		push	si
		push	large 800118h
		push	ds
		push	offset dword_3988E
		call	sub_1588A
		push	0
		call	sub_EA3E
		add	sp, 0Eh
		push	si
		push	large 800118h
		push	ds
		push	offset dword_3988E
		jmp	short loc_2D334
; ---------------------------------------------------------------------------

loc_2D2EF:
		cmp	word_35FF0, 0
		jz	short loc_2D33C
		push	1
		call	sub_EA3E
		mov	ax, word_35FF0
		dec	ax
		imul	ax, 3
		add	ax, si
		push	ax
		push	large 800118h
		push	ds
		push	offset dword_3985C
		call	sub_1588A
		push	0
		call	sub_EA3E
		add	sp, 0Eh
		mov	ax, word_35FF0
		dec	ax
		imul	ax, 3
		add	ax, si
		push	ax
		push	large 800118h
		push	ds
		push	offset dword_3985C

loc_2D334:
		call	sub_1588A
		add	sp, 0Ah

loc_2D33C:
		mov	word_35FEE, si

loc_2D340:
		pop	si
		pop	bp
		retf
sub_2D271	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D343	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		cmp	word_35FF0, si
		jz	loc_2D40F
		cmp	si, 3
		jnz	short loc_2D38B
		push	1
		call	sub_EA3E
		push	word_35FEE
		push	large 800118h
		push	ds
		push	offset dword_3988E
		call	sub_1588A
		push	0
		call	sub_EA3E
		add	sp, 0Eh
		push	word_35FEE
		push	large 800118h
		push	ds
		push	offset dword_3988E
		jmp	short loc_2D403
; ---------------------------------------------------------------------------

loc_2D38B:
		or	si, si
		jz	short loc_2D3D1
		push	1
		call	sub_EA3E
		lea	ax, [si-1]
		imul	ax, 3
		add	ax, word_35FEE
		push	ax
		push	large 800118h
		push	ds
		push	offset dword_3985C
		call	sub_1588A
		push	0
		call	sub_EA3E
		add	sp, 0Eh
		lea	ax, [si-1]
		imul	ax, 3
		add	ax, word_35FEE
		push	ax
		push	large 800118h
		push	ds
		push	offset dword_3985C
		jmp	short loc_2D403
; ---------------------------------------------------------------------------

loc_2D3D1:
		push	1
		call	sub_EA3E
		push	word_35FEE
		push	large 500118h
		push	ds
		push	offset dword_3982A
		call	sub_1588A
		push	0
		call	sub_EA3E
		add	sp, 0Eh
		push	word_35FEE
		push	large 500118h
		push	ds
		push	offset dword_3982A

loc_2D403:
		call	sub_1588A
		add	sp, 0Ah
		mov	word_35FF0, si

loc_2D40F:
		pop	si
		pop	bp
		retf
sub_2D343	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D412	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_0]
		push	1
		call	sub_EA3E
		push	si
		call	sub_10CDD
		push	0
		call	sub_EA3E
		push	si
		call	sub_10CDD
		add	sp, 8
		pop	si
		pop	bp
		retf
sub_2D412	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D439	proc far

var_7		= word ptr -7
var_4		= word ptr -4
var_2		= word ptr -2

		enter	8, 0
		push	si
		push	di
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2D44D
		push	0
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2D44D:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2D7D3
		cmp	word_3A6CA, 64h	; 'd'
		jnz	loc_2D500
		push	large 1C001Bh
		push	large 180016h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		push	7
		push	ds
		push	offset word_3B43E
		push	ds
		push	offset word_3B43A
		push	large 1800000h
		push	large 0EC013Ch
		call	sub_11FF0
		push	7
		push	ds
		push	offset word_3B440
		push	ds
		push	offset word_3B43C
		push	large 400000h
		push	large 0EC013Ch
		call	sub_11FF0
		add	sp, 30h
		xor	si, si
		jmp	short loc_2D4C5
; ---------------------------------------------------------------------------

loc_2D4B0:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6AA2h], 13Ch
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6AAAh], 0ECh ; '�
		inc	si

loc_2D4C5:
		cmp	si, 4
		jl	short loc_2D4B0
		push	30h ; '0'
		push	word_3B438
		push	large 0BC0138h
		push	ds
		push	offset unk_37635
		call	sub_30368
		push	large 0C000Eh
		push	large 100012h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		push	0Ch
		call	sub_125C9
		add	sp, 1Ah
		jmp	loc_2D7CD
; ---------------------------------------------------------------------------

loc_2D500:
		cmp	word_3B442, 0
		jle	loc_2D5B2
		xor	si, si
		jmp	short loc_2D52C
; ---------------------------------------------------------------------------

loc_2D50D:
		push	large 80010h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6AAAh]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6AA2h]
		call	sub_10433
		add	sp, 8
		inc	si

loc_2D52C:
		cmp	si, 4
		jl	short loc_2D50D
		mov	ax, word_3B43A
		add	word_3B442, ax
		mov	ax, word_3B43E
		add	word_3B44A, ax
		mov	ax, word_3B43A
		sub	word_3B444, ax
		mov	ax, word_3B43E
		add	word_3B44C, ax
		mov	ax, word_3B43C
		add	word_3B446, ax
		mov	ax, word_3B440
		add	word_3B44E, ax
		mov	ax, word_3B43C
		sub	word_3B448, ax
		mov	ax, word_3B440
		add	word_3B450, ax
		cmp	word_3B442, 0
		jg	short loc_2D58B
		mov	word_3B442, 0
		mov	word_3B446, 0
		mov	word_3B444, 278h
		mov	word_3B448, 278h
		jmp	loc_2D7D3
; ---------------------------------------------------------------------------

loc_2D58B:
		xor	si, si
		jmp	short loc_2D5AA
; ---------------------------------------------------------------------------

loc_2D58F:
		push	9
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6AAAh]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6AA2h]
		call	sub_17741
		add	sp, 6
		inc	si

loc_2D5AA:
		cmp	si, 4
		jl	short loc_2D58F
		jmp	loc_2D7D3
; ---------------------------------------------------------------------------

loc_2D5B2:
		cmp	word_3B44A, 40h	; '@'
		jle	short loc_2D62C
		xor	si, si
		jmp	short loc_2D5DC
; ---------------------------------------------------------------------------

loc_2D5BD:
		push	large 80010h
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6AAAh]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6AA2h]
		call	sub_10433
		add	sp, 8
		inc	si

loc_2D5DC:
		cmp	si, 4
		jl	short loc_2D5BD
		sub	word_3B44A, 3
		sub	word_3B44C, 3
		add	word_3B446, 6
		sub	word_3B448, 6
		cmp	word_3B44A, 40h	; '@'
		jg	short loc_2D605
		mov	word_3B44A, 40h	; '@'
		jmp	loc_2D7D3
; ---------------------------------------------------------------------------

loc_2D605:
		xor	si, si
		jmp	short loc_2D624
; ---------------------------------------------------------------------------

loc_2D609:
		push	9
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6AAAh]
		mov	bx, si
		add	bx, bx
		push	word ptr [bx+6AA2h]
		call	sub_17741
		add	sp, 6
		inc	si

loc_2D624:
		cmp	si, 4
		jl	short loc_2D609
		jmp	loc_2D7D3
; ---------------------------------------------------------------------------

loc_2D62C:
		cmp	word_3B452, 0C8h ; '?'
		jge	loc_2D7C7
		inc	word_3B452
		mov	ax, word_3B452
		cwd
		idiv	word_3B438
		or	dx, dx
		jnz	loc_2D7D3
		xor	di, di
		call	IRand
		mov	bx, 0C8h ; '?'
		cwd
		idiv	bx
		add	dx, 40h	; '@'
		mov	[bp+var_2], dx
		call	IRand
		mov	bx, 190h
		cwd
		idiv	bx
		add	dx, 0F0h ; '�
		mov	[bp+var_4], dx
		mov	[bp+var_7+1], 190h
		mov	ax, [bp+var_7+1]
		sub	ax, [bp+var_2]
		push	ax
		mov	ax, [bp+var_4]
		sub	ax, di
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_7], al
		push	large 0
		push	large 0
		push	28h ; '('
		push	[bp+var_7]
		push	[bp+var_2]
		push	di
		push	ds
		push	offset unk_37635
		call	sub_304B8
		mov	di, 278h
		call	IRand
		mov	bx, 0C8h ; '?'
		cwd
		idiv	bx
		add	dx, 40h	; '@'
		mov	[bp+var_2], dx
		call	IRand
		mov	bx, 190h
		cwd
		idiv	bx
		mov	[bp+var_4], dx
		mov	[bp+var_7+1], 190h
		mov	ax, [bp+var_7+1]
		sub	ax, [bp+var_2]
		push	ax
		mov	ax, [bp+var_4]
		sub	ax, di
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_7], al
		push	large 0
		push	large 0
		push	28h ; '('
		push	[bp+var_7]
		push	[bp+var_2]
		push	di
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		mov	[bp+var_2], 40h	; '@'
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	di, dx
		mov	[bp+var_7+1], 190h
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	[bp+var_4], dx
		mov	ax, [bp+var_7+1]
		sub	ax, [bp+var_2]
		push	ax
		mov	ax, [bp+var_4]
		sub	ax, di
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_7], al
		push	large 0
		push	large 0
		push	28h ; '('
		push	[bp+var_7]
		push	[bp+var_2]
		push	di
		push	ds
		push	offset unk_37635
		call	sub_304B8
		mov	[bp+var_2], 40h	; '@'
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	di, dx
		mov	[bp+var_7+1], 190h
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	[bp+var_4], dx
		mov	ax, [bp+var_7+1]
		sub	ax, [bp+var_2]
		push	ax
		mov	ax, [bp+var_4]
		sub	ax, di
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_7], al
		push	large 0
		push	large 0
		push	28h ; '('
		push	[bp+var_7]
		push	[bp+var_2]
		push	di
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		mov	[bp+var_2], 40h	; '@'
		call	IRand
		mov	bx, 280h
		cwd
		idiv	bx
		mov	di, dx
		push	large 28000Ch
		push	[bp+var_2]
		push	dx
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		jmp	short loc_2D7D3
; ---------------------------------------------------------------------------

loc_2D7C7:
		mov	word_3A6CA, 0

loc_2D7CD:
		mov	word_3B452, 0

loc_2D7D3:
		pop	di
		pop	si
		leave
		retf
sub_2D439	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D7D7	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		push	large 0
		push	large 0
		push	word_3B438
		push	[bp+arg_0]
		push	large 0BC0148h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	word_3B438
		push	[bp+arg_0]
		push	large 0BC0128h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		pop	bp
		retf
sub_2D7D7	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D817	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2D828
		push	1
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2D828:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2D8E8
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_2D85A
		mov	byte ptr word_3B454, 40h ; '@'
		mov	word_3B454+1, 0FFFFh
		push	large 700060h
		push	large 500050h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 0Ch

loc_2D85A:
		cmp	word_3A6CA, 8Ch	; '�
		jge	short loc_2D873
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2D873
		push	40h ; '@'
		jmp	short loc_2D8A0
; ---------------------------------------------------------------------------

loc_2D873:
		cmp	word_3A6CA, 0DCh ; '?'
		jge	short loc_2D8A7
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2D8A7
		mov	al, byte ptr word_3B454
		add	al, 5
		mov	byte ptr word_3B454, al
		push	word_3B454
		push	cs
		call	near ptr sub_2D7D7
		pop	cx
		mov	al, 80h	; '?'
		sub	al, byte ptr word_3B454
		push	ax

loc_2D8A0:
		push	cs
		call	near ptr sub_2D7D7
		pop	cx
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_2D8A7:
		cmp	word_3A6CA, 12Ch
		jge	short loc_2D8DA
		mov	ax, word_3A6CA
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2D8DA
		mov	al, byte ptr word_3B454
		add	al, 0F4h ; '�
		mov	byte ptr word_3B454, al
		push	word_3B454
		push	cs
		call	near ptr sub_2D7D7
		mov	al, 80h	; '?'
		sub	al, byte ptr word_3B454
		push	ax
		push	cs
		call	near ptr sub_2D7D7
		add	sp, 4

loc_2D8DA:
		cmp	word_3A6CA, 12Ch
		jl	short loc_2D8E8
		mov	word_3A6CA, 0

loc_2D8E8:
		pop	bp
		retf
sub_2D817	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2D8EA	proc far

var_C		= word ptr -0Ch
var_A		= byte ptr -0Ah
var_8		= byte ptr -8
var_5		= word ptr -5
var_2		= word ptr -2

		enter	0Ch, 0
		push	si
		push	di
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2D8FE
		push	2
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2D8FE:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2DD61
		cmp	word_3A6CA, 64h	; 'd'
		jnz	loc_2D996
		mov	word_3B487, 0
		mov	word_3B489, 0
		xor	si, si
		jmp	short loc_2D935
; ---------------------------------------------------------------------------

loc_2D920:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6AB7h], 138h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6ACBh], 0BCh ; '?'
		inc	si

loc_2D935:
		cmp	si, 5
		jl	short loc_2D920
		mov	ax, 180h
		sub	ax, word_3B46B
		push	ax
		mov	ax, word_36C26
		add	ax, 0Ch
		sub	ax, word_3B457
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_5], al
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2D968
		mov	al, 28h	; '('
		jmp	short loc_2D96A
; ---------------------------------------------------------------------------

loc_2D968:
		mov	al, 0D8h ; '?'

loc_2D96A:
		add	al, byte ptr [bp+var_5]
		mov	byte ptr [bp+var_5], al
		push	[bp+var_5]
		push	6
		push	ds
		push	offset unk_3B483
		push	ds
		push	offset unk_3B47F
		call	sub_12053
		add	sp, 0Ch
		mov	word_3B461, 3E7h
		push	0Ch

loc_2D98D:
		call	sub_125C9
		pop	cx
		jmp	loc_2DD61
; ---------------------------------------------------------------------------

loc_2D996:
		cmp	word_3A6CA, 1F4h
		jge	loc_2DD1B
		xor	si, si
		jmp	loc_2DB6D
; ---------------------------------------------------------------------------

loc_2D9A5:
		mov	bx, si
		imul	bx, 0Ah
		cmp	word ptr [bx+6AB7h], 3E7h
		jz	loc_2DB6C
		push	large 80010h
		mov	bx, si
		imul	bx, 0Ah
		push	word ptr [bx+6AD3h]
		mov	bx, si
		imul	bx, 0Ah
		push	word ptr [bx+6ABFh]
		call	sub_10433
		add	sp, 8
		mov	di, 3
		jmp	short loc_2DA02
; ---------------------------------------------------------------------------

loc_2D9D9:
		push	9
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		push	word ptr [bx+6ACBh]
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		push	word ptr [bx+6AB7h]
		call	sub_17741
		add	sp, 6
		dec	di

loc_2DA02:
		cmp	di, 1
		jge	short loc_2D9D9
		push	7
		mov	bx, si
		imul	bx, 0Ah
		push	word ptr [bx+6ACBh]
		mov	bx, si
		imul	bx, 0Ah
		push	word ptr [bx+6AB7h]
		call	sub_17741
		add	sp, 6
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+6AE7h], 0
		jnz	short loc_2DA39
		mov	bx, si
		add	bx, bx
		mov	ax, word_36C26
		mov	[bx+6AEBh], ax

loc_2DA39:
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, 180h
		sub	ax, [bx+6ACBh]
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6AEBh]
		add	ax, 0Ch
		mov	bx, si
		imul	bx, 0Ah
		sub	ax, [bx+6AB7h]
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_5], al
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2DA76
		mov	al, 28h	; '('
		jmp	short loc_2DA78
; ---------------------------------------------------------------------------

loc_2DA76:
		mov	al, 0D8h ; '?'

loc_2DA78:
		add	al, byte ptr [bp+var_5]
		mov	byte ptr [bp+var_5], al
		push	[bp+var_5]
		push	7
		push	ds
		mov	ax, si
		add	ax, ax
		add	ax, 6AE3h
		push	ax
		push	ds
		mov	ax, si
		add	ax, ax
		add	ax, 6ADFh
		push	ax
		call	sub_12053
		add	sp, 0Ch
		mov	bx, si
		imul	bx, 0Ah
		cmp	word ptr [bx+6ACBh], 12Ch
		jle	short loc_2DAB4
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6AE7h], 1

loc_2DAB4:
		mov	di, 4
		jmp	short loc_2DAF6
; ---------------------------------------------------------------------------

loc_2DAB9:
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		mov	ax, [bx+6AB5h]
		mov	bx, si
		imul	bx, 0Ah
		mov	dx, di
		add	dx, dx
		add	bx, dx
		mov	[bx+6AB7h], ax
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		mov	ax, [bx+6AC9h]
		mov	bx, si
		imul	bx, 0Ah
		mov	dx, di
		add	dx, dx
		add	bx, dx
		mov	[bx+6ACBh], ax
		dec	di

loc_2DAF6:
		cmp	di, 1
		jge	short loc_2DAB9
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6ADFh]
		mov	bx, si
		imul	bx, 0Ah
		add	[bx+6AB7h], ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6AE3h]
		mov	bx, si
		imul	bx, 0Ah
		add	[bx+6ACBh], ax
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, [bx+6AB7h]
		cmp	ax, word_36C26
		jle	short loc_2DB6C
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, word_36C26
		add	ax, 18h
		cmp	[bx+6AB7h], ax
		jge	short loc_2DB6C
		mov	bx, si
		imul	bx, 0Ah
		mov	al, byte_34A59
		mov	ah, 0
		imul	ax, 0Ah
		add	ax, 170h
		cmp	[bx+6ACBh], ax
		jle	short loc_2DB6C
		mov	bx, si
		imul	bx, 0Ah
		cmp	word ptr [bx+6ACBh], 188h
		jge	short loc_2DB6C
		cmp	word_34A78, 0
		jnz	short loc_2DB6C
		mov	byte_34A4F, 1

loc_2DB6C:
		inc	si

loc_2DB6D:
		cmp	si, 2
		jl	loc_2D9A5
		cmp	word_3A6CA, 96h	; '�
		jnz	short loc_2DBEC
		xor	si, si
		jmp	short loc_2DB95
; ---------------------------------------------------------------------------

loc_2DB80:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6AC1h], 138h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6AD5h], 0BCh ; '?'
		inc	si

loc_2DB95:
		cmp	si, 5
		jl	short loc_2DB80
		mov	ax, 180h
		sub	ax, word_3B475
		push	ax
		mov	ax, word_36C26
		add	ax, 0Ch
		sub	ax, word_3B461
		push	ax
		call	iatan2
		mov	byte ptr [bp+var_5], al
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2DBC8
		mov	al, 28h	; '('
		jmp	short loc_2DBCA
; ---------------------------------------------------------------------------

loc_2DBC8:
		mov	al, 0D8h ; '?'

loc_2DBCA:
		add	al, byte ptr [bp+var_5]
		mov	byte ptr [bp+var_5], al
		push	[bp+var_5]
		push	6
		push	ds
		push	offset unk_3B485
		push	ds
		push	offset unk_3B481
		call	sub_12053
		push	0Ch
		call	sub_125C9
		add	sp, 0Eh

loc_2DBEC:
		mov	al, byte_34A30
		cbw
		imul	ax, 28h
		mov	dx, 0F0h ; '�
		sub	dx, ax
		cmp	dx, word_3A6CA
		jge	loc_2DD61
		mov	ax, word_3A6CA
		mov	bx, 28h	; '('
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2DD61
		call	IRand
		mov	bx, 0Ch
		cwd
		idiv	bx
		mov	byte ptr [bp+var_5], dl
		mov	ax, word_3A6CA
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2DC2F
		mov	ax, 19Ah
		jmp	short loc_2DC45
; ---------------------------------------------------------------------------

loc_2DC2F:
		mov	ax, word_3A6CA
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		cmp	dx, 28h	; '('
		jnz	short loc_2DC42
		mov	ax, 13Ch
		jmp	short loc_2DC45
; ---------------------------------------------------------------------------

loc_2DC42:
		mov	ax, 138h

loc_2DC45:
		mov	[bp+var_2], ax
		mov	ax, word_3A6CA
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2DC5A
		mov	ax, 46h	; 'F'
		jmp	short loc_2DC70
; ---------------------------------------------------------------------------

loc_2DC5A:
		mov	ax, word_3A6CA
		mov	bx, 78h	; 'x'
		cwd
		idiv	bx
		cmp	dx, 28h	; '('
		jnz	short loc_2DC6D
		mov	ax, 8Ch	; '�
		jmp	short loc_2DC70
; ---------------------------------------------------------------------------

loc_2DC6D:
		mov	ax, 0BCh ; '?'

loc_2DC70:
		mov	[bp+var_5+1], ax
		xor	si, si
		jmp	loc_2DD0F
; ---------------------------------------------------------------------------

loc_2DC78:
		mov	ax, si
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2DC88
		xor	ax, ax
		jmp	short loc_2DCAE
; ---------------------------------------------------------------------------

loc_2DC88:
		mov	ax, si
		mov	bx, 4
		cwd
		idiv	bx
		cmp	dx, 1
		jnz	short loc_2DC9A
		mov	ax, 10h
		jmp	short loc_2DCAE
; ---------------------------------------------------------------------------

loc_2DC9A:
		mov	ax, si
		mov	bx, 4
		cwd
		idiv	bx
		cmp	dx, 2
		jnz	short loc_2DCAB
		xor	ax, ax
		jmp	short loc_2DCAE
; ---------------------------------------------------------------------------

loc_2DCAB:
		mov	ax, 20h	; ' '

loc_2DCAE:
		add	ax, 28h	; '('
		mov	[bp+var_C], ax
		push	[bp+var_5]
		push	ax
		push	ss
		lea	ax, [bp+var_A]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		call	sub_12053
		push	large 0
		push	large 0
		push	[bp+var_C]
		mov	al, 80h	; '?'
		sub	al, byte ptr [bp+var_5]
		push	ax
		push	[bp+var_5+1]
		push	[bp+var_2]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 20h
		push	large 0
		push	large 0
		push	[bp+var_C]
		push	[bp+var_5]
		push	[bp+var_5+1]
		push	[bp+var_2]
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		mov	al, byte ptr [bp+var_5]
		add	al, 0Ch
		mov	byte ptr [bp+var_5], al
		inc	si

loc_2DD0F:
		cmp	si, 0Ah
		jl	loc_2DC78
		push	7
		jmp	loc_2D98D
; ---------------------------------------------------------------------------

loc_2DD1B:
		xor	si, si
		jmp	short loc_2DD56
; ---------------------------------------------------------------------------

loc_2DD1F:
		xor	di, di
		jmp	short loc_2DD50
; ---------------------------------------------------------------------------

loc_2DD23:
		push	large 80010h
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		push	word ptr [bx+6ACBh]
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		push	word ptr [bx+6AB7h]
		call	sub_10433
		add	sp, 8
		inc	di

loc_2DD50:
		cmp	di, 5
		jl	short loc_2DD23
		inc	si

loc_2DD56:
		cmp	si, 2
		jl	short loc_2DD1F
		mov	word_3A6CA, 0

loc_2DD61:
		pop	di
		pop	si
		leave
		retf
sub_2D8EA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2DD65	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2DD76
		push	0
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2DD76:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2DF0A
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_2DDD9
		push	10h
		push	ds
		push	offset word_3B491
		push	ds
		push	offset word_3B48F
		push	large 400040h
		push	large 0C80122h
		call	sub_11FF0
		mov	word_3B493, 122h
		mov	word_3B495, 0C8h ; '?'
		mov	word_3B499, 30h	; '0'
		push	0Ch
		call	sub_125C9
		mov	word_3B497, 63h	; 'c'
		push	large 60008h
		push	large 0A000Ch
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 20h
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_2DDD9:
		cmp	word_3B497, 63h	; 'c'
		jnz	short loc_2DE24
		push	large 80010h
		push	word_3B495
		push	word_3B493
		call	sub_10433
		add	sp, 8
		mov	ax, word_3B48F
		add	word_3B493, ax
		mov	ax, word_3B491
		add	word_3B495, ax
		cmp	word_3B495, 40h	; '@'
		jg	short loc_2DE1F
		mov	word_3B493, 40h	; '@'
		mov	word_3B495, 40h	; '@'
		mov	word_3B497, 0
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_2DE1F:
		push	9
		jmp	loc_2DEFA
; ---------------------------------------------------------------------------

loc_2DE24:
		cmp	word_3B497, 63h	; 'c'
		jge	loc_2DF0A
		push	large 80010h
		push	word_3B495
		push	word_3B493
		call	sub_10433
		add	sp, 8
		cmp	word_3B497, 0
		jnz	short loc_2DE4E
		xor	ax, ax
		jmp	short loc_2DE5D
; ---------------------------------------------------------------------------

loc_2DE4E:
		cmp	word_3B497, 1
		jnz	short loc_2DE5A
		mov	ax, 0FFF0h
		jmp	short loc_2DE5D
; ---------------------------------------------------------------------------

loc_2DE5A:
		mov	ax, 0FFF8h

loc_2DE5D:
		add	ax, 8
		add	word_3B493, ax
		cmp	word_3B497, 2
		jl	short loc_2DE8D
		add	word_3B495, 8
		inc	word_3B497
		cmp	word_3B497, 0Ah
		jl	short loc_2DE8D
		cmp	word_3B493, 140h
		jle	short loc_2DE88
		mov	ax, 1
		jmp	short loc_2DE8A
; ---------------------------------------------------------------------------

loc_2DE88:
		xor	ax, ax

loc_2DE8A:
		mov	word_3B497, ax

loc_2DE8D:
		cmp	word_3B493, 240h
		jle	short loc_2DEA3
		mov	word_3B497, 2
		mov	word_3B493, 240h
		jmp	short loc_2DEB6
; ---------------------------------------------------------------------------

loc_2DEA3:
		cmp	word_3B493, 40h	; '@'
		jge	short loc_2DEB6
		mov	word_3B497, 2
		mov	word_3B493, 40h	; '@'

loc_2DEB6:
		cmp	word_3B495, 100h
		jl	short loc_2DEC6
		mov	word_3A6CA, 0
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_2DEC6:
		cmp	word_3B497, 2
		jge	short loc_2DEF8
		mov	ax, word_3A6CA
		cwd
		idiv	word_3B438
		or	dx, dx
		jnz	short loc_2DEF8
		push	word_3B499
		push	0Ch
		push	word_3B495
		push	word_3B493
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		add	word_3B499, 2

loc_2DEF8:
		push	6

loc_2DEFA:
		push	word_3B495
		push	word_3B493
		call	sub_17741
		add	sp, 6

loc_2DF0A:
		pop	bp
		retf
sub_2DD65	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2DF0C	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2DF1D
		push	1
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2DF1D:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2DFC8
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_2DF55
		mov	byte_3B49B, 20h	; ' '
		mov	word_3B49C+1, 0FFF8h
		mov	word_3B49F, 0
		push	large 20003h
		push	large 40005h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 0Ch

loc_2DF55:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3B438
		or	dx, dx
		jnz	short loc_2DFBA
		push	0B8h ; '?'
		mov	ax, word_36C26
		add	ax, 0FEEAh
		push	ax
		call	iatan2
		mov	byte ptr word_3B49C, al
		mov	al, byte_3B49B
		add	byte ptr word_3B49C, al
		add	al, byte ptr word_3B49C+1
		mov	byte_3B49B, al
		inc	word_3B49F
		cmp	word_3B49F, 8
		jle	short loc_2DF9C
		mov	ax, 0FFFFh
		imul	word_3B49C+1
		mov	word_3B49C+1, ax
		mov	word_3B49F, 0

loc_2DF9C:
		push	large 0
		push	large 0
		push	30h ; '0'
		push	word_3B49C
		push	large 0BC0138h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h

loc_2DFBA:
		cmp	word_3A6CA, 2BCh
		jl	short loc_2DFC8
		mov	word_3A6CA, 0

loc_2DFC8:
		pop	bp
		retf
sub_2DF0C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2DFCA	proc far

var_1		= byte ptr -1

		enter	2, 0
		push	si
		push	di
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2DFDE
		push	2
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2DFDE:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2E42A
		cmp	word_3A6CA, 64h	; 'd'
		jnz	loc_2E09A
		xor	si, si
		jmp	short loc_2DFFF
; ---------------------------------------------------------------------------

loc_2DFF4:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B61h], 0
		inc	si

loc_2DFFF:
		cmp	si, 4
		jl	short loc_2DFF4
		xor	si, si
		jmp	short loc_2E01D
; ---------------------------------------------------------------------------

loc_2E008:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B01h], 138h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B29h], 0BCh ; '?'
		inc	si

loc_2E01D:
		cmp	si, 5
		jl	short loc_2E008
		mov	ax, 180h
		sub	ax, word_3B4C9
		push	ax
		mov	ax, word_36C26
		add	ax, 0Ch
		sub	ax, word_3B4A1
		push	ax
		call	iatan2
		mov	[bp+var_1], al
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2E050
		mov	al, 28h	; '('
		jmp	short loc_2E052
; ---------------------------------------------------------------------------

loc_2E050:
		mov	al, 0D8h ; '?'

loc_2E052:
		add	al, [bp+var_1]
		mov	[bp+var_1], al
		push	word ptr [bp+var_1]
		push	6
		push	ds
		push	offset unk_3B4F9
		push	ds
		push	offset unk_3B4F1
		call	sub_12053
		add	sp, 0Ch
		mov	si, 1
		jmp	short loc_2E07E
; ---------------------------------------------------------------------------

loc_2E072:
		mov	bx, si
		imul	bx, 0Ah
		mov	word ptr [bx+6B01h], 3E7h
		inc	si

loc_2E07E:
		cmp	si, 4
		jl	short loc_2E072
		push	large 0C000Eh
		push	large 100012h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		jmp	loc_2E3D8
; ---------------------------------------------------------------------------

loc_2E09A:
		cmp	word_3A6CA, 190h
		jge	loc_2E3E4
		xor	si, si
		jmp	loc_2E271
; ---------------------------------------------------------------------------

loc_2E0A9:
		mov	bx, si
		imul	bx, 0Ah
		cmp	word ptr [bx+6B01h], 3E7h
		jz	loc_2E270
		push	large 80010h
		mov	bx, si
		imul	bx, 0Ah
		push	word ptr [bx+6B31h]
		mov	bx, si
		imul	bx, 0Ah
		push	word ptr [bx+6B09h]
		call	sub_10433
		add	sp, 8
		mov	di, 3
		jmp	short loc_2E106
; ---------------------------------------------------------------------------

loc_2E0DD:
		push	9
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		push	word ptr [bx+6B29h]
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		push	word ptr [bx+6B01h]
		call	sub_17741
		add	sp, 6
		dec	di

loc_2E106:
		cmp	di, 1
		jge	short loc_2E0DD
		push	7
		mov	bx, si
		imul	bx, 0Ah
		push	word ptr [bx+6B29h]
		mov	bx, si
		imul	bx, 0Ah
		push	word ptr [bx+6B01h]
		call	sub_17741
		add	sp, 6
		mov	bx, si
		add	bx, bx
		cmp	word ptr [bx+6B61h], 0
		jnz	short loc_2E13D
		mov	bx, si
		add	bx, bx
		mov	ax, word_36C26
		mov	[bx+6B69h], ax

loc_2E13D:
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, 180h
		sub	ax, [bx+6B29h]
		push	ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6B69h]
		add	ax, 0Ch
		mov	bx, si
		imul	bx, 0Ah
		sub	ax, [bx+6B01h]
		push	ax
		call	iatan2
		mov	[bp+var_1], al
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2E17A
		mov	al, 28h	; '('
		jmp	short loc_2E17C
; ---------------------------------------------------------------------------

loc_2E17A:
		mov	al, 0D8h ; '?'

loc_2E17C:
		add	al, [bp+var_1]
		mov	[bp+var_1], al
		push	word ptr [bp+var_1]
		push	7
		push	ds
		mov	ax, si
		add	ax, ax
		add	ax, 6B59h
		push	ax
		push	ds
		mov	ax, si
		add	ax, ax
		add	ax, 6B51h
		push	ax
		call	sub_12053
		add	sp, 0Ch
		mov	bx, si
		imul	bx, 0Ah
		cmp	word ptr [bx+6B29h], 12Ch
		jle	short loc_2E1B8
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B61h], 1

loc_2E1B8:
		mov	di, 4
		jmp	short loc_2E1FA
; ---------------------------------------------------------------------------

loc_2E1BD:
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		mov	ax, [bx+6AFFh]
		mov	bx, si
		imul	bx, 0Ah
		mov	dx, di
		add	dx, dx
		add	bx, dx
		mov	[bx+6B01h], ax
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		mov	ax, [bx+6B27h]
		mov	bx, si
		imul	bx, 0Ah
		mov	dx, di
		add	dx, dx
		add	bx, dx
		mov	[bx+6B29h], ax
		dec	di

loc_2E1FA:
		cmp	di, 1
		jge	short loc_2E1BD
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6B51h]
		mov	bx, si
		imul	bx, 0Ah
		add	[bx+6B01h], ax
		mov	bx, si
		add	bx, bx
		mov	ax, [bx+6B59h]
		mov	bx, si
		imul	bx, 0Ah
		add	[bx+6B29h], ax
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, [bx+6B01h]
		cmp	ax, word_36C26
		jle	short loc_2E270
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, word_36C26
		add	ax, 18h
		cmp	[bx+6B01h], ax
		jge	short loc_2E270
		mov	bx, si
		imul	bx, 0Ah
		mov	al, byte_34A59
		mov	ah, 0
		imul	ax, 0Ah
		add	ax, 170h
		cmp	[bx+6B29h], ax
		jle	short loc_2E270
		mov	bx, si
		imul	bx, 0Ah
		cmp	word ptr [bx+6B29h], 188h
		jge	short loc_2E270
		cmp	word_34A78, 0
		jnz	short loc_2E270
		mov	byte_34A4F, 1

loc_2E270:
		inc	si

loc_2E271:
		cmp	si, 4
		jl	loc_2E0A9
		cmp	word_3A6CA, 96h	; '�
		jnz	short loc_2E2F0
		xor	si, si
		jmp	short loc_2E299
; ---------------------------------------------------------------------------

loc_2E284:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B0Bh], 138h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B33h], 0BCh ; '?'
		inc	si

loc_2E299:
		cmp	si, 5
		jl	short loc_2E284
		mov	ax, 180h
		sub	ax, word_3B4D3
		push	ax
		mov	ax, word_36C26
		add	ax, 0Ch
		sub	ax, word_3B4AB
		push	ax
		call	iatan2
		mov	[bp+var_1], al
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2E2CC
		mov	al, 28h	; '('
		jmp	short loc_2E2CE
; ---------------------------------------------------------------------------

loc_2E2CC:
		mov	al, 0D8h ; '?'

loc_2E2CE:
		add	al, [bp+var_1]
		mov	[bp+var_1], al
		push	word ptr [bp+var_1]
		push	6
		push	ds
		push	offset unk_3B4FB
		push	ds
		push	offset unk_3B4F3
		call	sub_12053
		push	0Ch
		call	sub_125C9
		add	sp, 0Eh

loc_2E2F0:
		cmp	word_3A6CA, 0C8h ; '?'
		jnz	short loc_2E368
		xor	si, si
		jmp	short loc_2E311
; ---------------------------------------------------------------------------

loc_2E2FC:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B15h], 122h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B3Dh], 0C8h ; '?'
		inc	si

loc_2E311:
		cmp	si, 5
		jl	short loc_2E2FC
		mov	ax, 180h
		sub	ax, word_3B4DD
		push	ax
		mov	ax, word_36C26
		add	ax, 0Ch
		sub	ax, word_3B4B5
		push	ax
		call	iatan2
		mov	[bp+var_1], al
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2E344
		mov	al, 28h	; '('
		jmp	short loc_2E346
; ---------------------------------------------------------------------------

loc_2E344:
		mov	al, 0D8h ; '?'

loc_2E346:
		add	al, [bp+var_1]
		mov	[bp+var_1], al
		push	word ptr [bp+var_1]
		push	6
		push	ds
		push	offset unk_3B4FD
		push	ds
		push	offset unk_3B4F5
		call	sub_12053
		push	0Ch
		call	sub_125C9
		add	sp, 0Eh

loc_2E368:
		cmp	word_3A6CA, 0FAh ; '�
		jnz	loc_2E42A
		xor	si, si
		jmp	short loc_2E38B
; ---------------------------------------------------------------------------

loc_2E376:
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B1Fh], 122h
		mov	bx, si
		add	bx, bx
		mov	word ptr [bx+6B47h], 0C8h ; '?'
		inc	si

loc_2E38B:
		cmp	si, 5
		jl	short loc_2E376
		mov	ax, 180h
		sub	ax, word_3B4E7
		push	ax
		mov	ax, word_36C26
		add	ax, 0Ch
		sub	ax, word_3B4BF
		push	ax
		call	iatan2
		mov	[bp+var_1], al
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2E3BE
		mov	al, 28h	; '('
		jmp	short loc_2E3C0
; ---------------------------------------------------------------------------

loc_2E3BE:
		mov	al, 0D8h ; '?'

loc_2E3C0:
		add	al, [bp+var_1]
		mov	[bp+var_1], al
		push	word ptr [bp+var_1]
		push	6
		push	ds
		push	offset unk_3B4FF
		push	ds
		push	offset unk_3B4F7
		call	sub_12053

loc_2E3D8:
		push	0Ch
		call	sub_125C9
		add	sp, 0Eh
		jmp	short loc_2E42A
; ---------------------------------------------------------------------------

loc_2E3E4:
		xor	si, si
		jmp	short loc_2E41F
; ---------------------------------------------------------------------------

loc_2E3E8:
		xor	di, di
		jmp	short loc_2E419
; ---------------------------------------------------------------------------

loc_2E3EC:
		push	large 80010h
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		push	word ptr [bx+6B29h]
		mov	bx, si
		imul	bx, 0Ah
		mov	ax, di
		add	ax, ax
		add	bx, ax
		push	word ptr [bx+6B01h]
		call	sub_10433
		add	sp, 8
		inc	di

loc_2E419:
		cmp	di, 5
		jl	short loc_2E3EC
		inc	si

loc_2E41F:
		cmp	si, 4
		jl	short loc_2E3E8
		mov	word_3A6CA, 0

loc_2E42A:
		pop	di
		pop	si
		leave
		retf
sub_2DFCA	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2E42E	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2E43F
		push	3
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2E43F:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2E703
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_2E478
		mov	word_3B511, 0
		mov	word_3B513, 108h
		mov	word_3B515, 1
		push	large 20002h
		push	large 30005h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 0Ch

loc_2E478:
		cmp	word_3A6CA, 7Dh	; '}'
		jge	short loc_2E49E
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		sub	word_3B513, 8
		jmp	loc_2E697
; ---------------------------------------------------------------------------

loc_2E49E:
		cmp	word_3A6CA, 7Dh	; '}'
		jnz	short loc_2E4D0
		mov	word_3B511, 0
		mov	word_3B513, 40h	; '@'
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		add	word_3B511, 8
		jmp	loc_2E5E0
; ---------------------------------------------------------------------------

loc_2E4D0:
		cmp	word_3A6CA, 0CDh ; '?'
		jge	short loc_2E4F7
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		add	word_3B511, 8
		jmp	loc_2E697
; ---------------------------------------------------------------------------

loc_2E4F7:
		cmp	word_3A6CA, 0CDh ; '?'
		jnz	short loc_2E529
		mov	word_3B511, 27Fh
		mov	word_3B513, 40h	; '@'
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		add	word_3B513, 8
		jmp	short loc_2E580
; ---------------------------------------------------------------------------

loc_2E529:
		cmp	word_3A6CA, 0E6h ; '�
		jge	short loc_2E550
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		add	word_3B513, 8
		jmp	loc_2E697
; ---------------------------------------------------------------------------

loc_2E550:
		cmp	word_3A6CA, 0E6h ; '�
		jnz	short loc_2E589
		mov	word_3B511, 27Fh
		mov	word_3B513, 108h
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		sub	word_3B513, 8

loc_2E580:
		mov	word_3B515, 2
		jmp	loc_2E697
; ---------------------------------------------------------------------------

loc_2E589:
		cmp	word_3A6CA, 0FFh
		jge	short loc_2E5B0
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		sub	word_3B513, 8
		jmp	loc_2E697
; ---------------------------------------------------------------------------

loc_2E5B0:
		cmp	word_3A6CA, 0FFh
		jnz	short loc_2E5E9
		mov	word_3B511, 27Fh
		mov	word_3B513, 40h	; '@'
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		sub	word_3B511, 8

loc_2E5E0:
		mov	word_3B515, 0
		jmp	loc_2E697
; ---------------------------------------------------------------------------

loc_2E5E9:
		cmp	word_3A6CA, 14Fh
		jge	short loc_2E610
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		sub	word_3B511, 8
		jmp	loc_2E697
; ---------------------------------------------------------------------------

loc_2E610:
		cmp	word_3A6CA, 14Fh
		jnz	short loc_2E648
		mov	word_3B511, 0
		mov	word_3B513, 40h	; '@'
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		add	word_3B513, 8
		mov	word_3B515, 1
		jmp	short loc_2E697
; ---------------------------------------------------------------------------

loc_2E648:
		cmp	word_3A6CA, 168h
		jge	short loc_2E66E
		push	6
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		push	cs
		call	near ptr sub_2CE17
		add	sp, 0Ah
		add	word_3B513, 8
		jmp	short loc_2E697
; ---------------------------------------------------------------------------

loc_2E66E:
		cmp	word_3A6CA, 168h
		jnz	short loc_2E697
		sub	word_3B513, 8
		push	word_3B513
		push	word_3B511
		push	large 46019Ah
		call	sub_F2F5
		add	sp, 8
		mov	word_3A6CA, 0

loc_2E697:
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2E6AC
		push	6
		call	sub_125C9
		pop	cx

loc_2E6AC:
		mov	ax, word_3A6CA
		cwd
		idiv	word_3B438
		or	dx, dx
		jnz	short loc_2E703
		push	large 0
		push	large 10001h
		push	20h ; ' '
		call	IRand
		and	al, 7Fh
		push	ax
		push	word_3B513
		push	word_3B511
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 10001h
		push	20h ; ' '
		call	IRand
		and	al, 7Fh
		push	ax
		push	word_3B513
		push	word_3B511
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h

loc_2E703:
		pop	bp
		retf
sub_2E42E	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2E705	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 32h	; '2'
		jl	loc_2E7C2
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2E728
		push	0
		push	cs
		call	near ptr sub_2D412
		push	8
		call	sub_125C9
		add	sp, 4

loc_2E728:
		cmp	word_3A6CA, 3Ch	; '<'
		jl	loc_2E7C2
		cmp	word_3A6CA, 3Ch	; '<'
		jnz	short loc_2E73F
		push	1
		push	cs
		call	near ptr sub_2D412
		pop	cx

loc_2E73F:
		cmp	word_3A6CA, 64h	; 'd'
		jl	short loc_2E7C2
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_2E754
		push	2
		push	cs
		call	near ptr sub_2D412
		pop	cx

loc_2E754:
		cmp	word_3A6CA, 78h	; 'x'
		jl	short loc_2E7C2
		cmp	word_3A6CA, 78h	; 'x'
		jnz	short loc_2E769
		push	3
		push	cs
		call	near ptr sub_2D412
		pop	cx

loc_2E769:
		cmp	word_3A6CA, 8Ch	; '�
		jl	short loc_2E7C2
		cmp	word_3A6CA, 8Ch	; '�
		jnz	short loc_2E780
		push	4
		push	cs
		call	near ptr sub_2D412
		pop	cx

loc_2E780:
		cmp	word_3A6CA, 0A0h ; '?'
		jl	short loc_2E7C2
		cmp	word_3A6CA, 0A0h ; '?'
		jnz	short loc_2E797
		push	5
		push	cs
		call	near ptr sub_2D412
		pop	cx

loc_2E797:
		cmp	word_3A6CA, 0AAh ; '?'
		jl	short loc_2E7C2
		cmp	word_3A6CA, 0AAh ; '?'
		jnz	short loc_2E7AE
		push	6
		push	cs
		call	near ptr sub_2D412
		pop	cx

loc_2E7AE:
		cmp	word_3A6CA, 0C8h ; '?'
		jle	short loc_2E7C2
		mov	word_3A6CA, 0
		mov	word_35FF2, 1

loc_2E7C2:
		pop	bp
		retf
sub_2E705	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2E7C4	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2E803
		push	2
		push	cs
		call	near ptr sub_2D271
		push	1
		push	cs
		call	near ptr sub_2D343
		mov	word_35FF2, 0
		mov	word_3B517, 19Ah
		mov	word_3B519, 46h	; 'F'
		push	large 10002h
		push	large 30005h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 10h

loc_2E803:
		push	cs
		call	near ptr sub_2E705
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2EA01
		cmp	word_3A6CA, 8Ch	; '�
		jge	loc_2E8A1
		mov	ax, word_3A6CA
		cwd
		idiv	word_3B438
		or	dx, dx
		jnz	short loc_2E8A1
		push	large 0
		push	large 10001h
		push	0
		call	IRand
		mov	bx, 7Fh	; ''
		cwd
		idiv	bx
		push	dx
		push	word_3B519
		push	word_3B517
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 10001h
		push	0
		call	IRand
		mov	bx, 7Fh	; ''
		cwd
		idiv	bx
		push	dx
		push	word_3B519
		push	word_3B517
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		mov	ax, 28h	; '('
		cwd
		idiv	word_3B438
		push	ax
		mov	ax, 16h
		cwd
		pop	bx
		idiv	bx
		add	word_3B517, ax
		mov	ax, 28h	; '('
		cwd
		idiv	word_3B438
		push	ax
		mov	ax, 0A2h ; '?'
		cwd
		pop	bx
		idiv	bx
		add	word_3B519, ax

loc_2E8A1:
		cmp	word_3A6CA, 8Ch	; '�
		jnz	short loc_2E8CC
		mov	word_3B517, 1B0h
		mov	word_3B519, 0E8h ; '�
		push	large 20002h
		push	large 20003h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 0Ch

loc_2E8CC:
		cmp	word_3A6CA, 8Ch	; '�
		jl	loc_2EA01
		cmp	word_3A6CA, 96h	; '�
		jge	short loc_2E93B
		push	large 0
		push	large 10001h
		push	0
		call	IRand
		mov	bx, 7Fh	; ''
		cwd
		idiv	bx
		push	dx
		push	word_3B519
		push	word_3B517
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 10001h
		push	0
		call	IRand
		mov	bx, 7Fh	; ''
		cwd
		idiv	bx
		push	dx
		push	word_3B519
		push	word_3B517
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		sub	word_3B517, 17h
		sub	word_3B519, 3

loc_2E93B:
		cmp	word_3A6CA, 96h	; '�
		jnz	short loc_2E966
		mov	word_3B517, 0C6h ; '?'
		mov	word_3B519, 0C6h ; '?'
		push	large 10001h
		push	large 20003h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 0Ch

loc_2E966:
		cmp	word_3A6CA, 96h	; '�
		jl	loc_2EA01
		cmp	word_3A6CA, 0AAh ; '?'
		jge	loc_2EA01
		mov	ax, word_3A6CA
		cwd
		idiv	word_3B438
		or	dx, dx
		jnz	short loc_2EA01
		push	large 0
		push	large 10001h
		push	0
		call	IRand
		mov	bx, 7Fh	; ''
		cwd
		idiv	bx
		push	dx
		push	word_3B519
		push	word_3B517
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 10001h
		push	0
		call	IRand
		mov	bx, 7Fh	; ''
		cwd
		idiv	bx
		push	dx
		push	word_3B519
		push	word_3B517
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		mov	ax, 14h
		cwd
		idiv	word_3B438
		push	ax
		mov	ax, 0FF2Ch
		cwd
		pop	bx
		idiv	bx
		sub	word_3B517, ax
		mov	ax, 14h
		cwd
		idiv	word_3B438
		push	ax
		mov	ax, 80h	; '?'
		cwd
		pop	bx
		idiv	bx
		sub	word_3B519, ax

loc_2EA01:
		pop	bp
		retf
sub_2E7C4	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2EA03	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2EA42
		push	2
		push	cs
		call	near ptr sub_2D271
		push	3
		push	cs
		call	near ptr sub_2D343
		mov	word_35FF2, 0
		mov	word_3B51B, 19Ah
		mov	word_3B51D, 46h	; 'F'
		push	large 480040h
		push	large 300020h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 10h

loc_2EA42:
		push	cs
		call	near ptr sub_2E705
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2EB8F
		cmp	word_3A6CA, 8Ch	; '�
		jge	short loc_2EAAA
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2EAAA
		push	large 0
		push	large 0
		push	word_3B438
		push	20h ; ' '
		push	word_3B51D
		push	word_3B51B
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	word_3B438
		push	60h ; '`'
		push	word_3B51D
		push	word_3B51B
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		inc	word_3B51B
		add	word_3B51D, 0Ch

loc_2EAAA:
		cmp	word_3A6CA, 8Ch	; '�
		jnz	short loc_2EABE
		mov	word_3B51B, 1B0h
		mov	word_3B51D, 0E8h ; '�

loc_2EABE:
		cmp	word_3A6CA, 8Ch	; '�
		jl	loc_2EB8F
		cmp	word_3A6CA, 96h	; '�
		jge	short loc_2EB17
		push	large 0
		push	large 0
		push	word_3B438
		push	20h ; ' '
		push	word_3B51D
		push	word_3B51B
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	word_3B438
		push	60h ; '`'
		push	word_3B51D
		push	word_3B51B
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		sub	word_3B51B, 17h
		sub	word_3B51D, 3

loc_2EB17:
		cmp	word_3A6CA, 96h	; '�
		jnz	short loc_2EB2B
		mov	word_3B51B, 0C6h ; '?'
		mov	word_3B51D, 0C6h ; '?'

loc_2EB2B:
		cmp	word_3A6CA, 96h	; '�
		jl	short loc_2EB8F
		cmp	word_3A6CA, 0AAh ; '?'
		jge	short loc_2EB8F
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2EB8F
		push	large 0
		push	large 0
		push	word_3B438
		push	20h ; ' '
		push	word_3B51D
		push	word_3B51B
		push	ds
		push	offset unk_37635
		call	sub_304B8
		push	large 0
		push	large 0
		push	word_3B438
		push	60h ; '`'
		push	word_3B51D
		push	word_3B51B
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 28h
		sub	word_3B51B, 0FFEBh
		sub	word_3B51D, 0Ch

loc_2EB8F:
		pop	bp
		retf
sub_2EA03	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2EB91	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2EBA2
		push	3
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2EBA2:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2EC98
		cmp	word_3A6CA, 64h	; 'd'
		jnz	short loc_2EBD8
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	word_3B523, dx
		push	large 400050h
		push	large 600080h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 0Ch

loc_2EBD8:
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2EC98
		cmp	word_3B523, 0
		jnz	short loc_2EC00
		mov	ax, word_3A6CA
		add	ax, 0FF9Ch
		cwd
		idiv	bx
		imul	word_3B438
		mov	word_3B51F, ax
		jmp	short loc_2EC19
; ---------------------------------------------------------------------------

loc_2EC00:
		mov	ax, word_3A6CA
		add	ax, 0FF9Ch
		mov	bx, 0Ah
		cwd
		idiv	bx
		imul	word_3B438
		mov	dx, 280h
		sub	dx, ax
		mov	word_3B51F, dx

loc_2EC19:
		mov	word_3B521, 190h
		push	large 5001Eh
		push	large 70044h
		push	word_3B521
		push	word_3B51F
		push	large 46019Ah
		mov	ax, word_3A6CA
		mov	bx, 0Ah
		cwd
		idiv	bx
		cwd
		idiv	bx
		imul	dx, 45h
		add	dx, 4800h
		push	ds
		push	dx
		call	sub_1209D
		push	6
		call	sub_125C9
		add	sp, 16h
		cmp	word_3B523, 0
		jnz	short loc_2EC6C
		cmp	word_3B51F, 280h
		jge	short loc_2EC7A

loc_2EC6C:
		cmp	word_3B523, 1
		jnz	short loc_2EC80
		cmp	word_3B51F, 0
		jg	short loc_2EC80

loc_2EC7A:
		mov	word_3A6CA, 0

loc_2EC80:
		push	large 480017h
		push	large 46019Ah
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch

loc_2EC98:
		pop	bp
		retf
sub_2EB91	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2EC9A	proc far
		push	bp
		mov	bp, sp
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2ECD9
		push	2
		push	cs
		call	near ptr sub_2D271
		push	3
		push	cs
		call	near ptr sub_2D343
		mov	word_35FF2, 0
		mov	word_3B525, 19Ah
		mov	word_3B527, 46h	; 'F'
		push	large 600058h
		push	large 500040h
		push	ds
		push	offset word_3B438
		push	cs
		call	near ptr sub_2CDD2
		add	sp, 10h

loc_2ECD9:
		push	cs
		call	near ptr sub_2E705
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2EDBD
		cmp	word_3A6CA, 8Ch	; '�
		jge	short loc_2ED1E
		mov	ax, word_3A6CA
		mov	bx, 3
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2ED1E
		push	word_3B438
		push	0Ch
		push	word_3B527
		push	word_3B525
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		inc	word_3B525
		add	word_3B527, 0Ch

loc_2ED1E:
		cmp	word_3A6CA, 8Ch	; '�
		jnz	short loc_2ED32
		mov	word_3B525, 1B0h
		mov	word_3B527, 0E8h ; '�

loc_2ED32:
		cmp	word_3A6CA, 8Ch	; '�
		jl	loc_2EDBD
		cmp	word_3A6CA, 96h	; '�
		jge	short loc_2ED68
		push	word_3B438
		push	0Ch
		push	word_3B527
		push	word_3B525
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		sub	word_3B525, 17h
		sub	word_3B527, 3

loc_2ED68:
		cmp	word_3A6CA, 96h	; '�
		jnz	short loc_2ED7C
		mov	word_3B525, 0C6h ; '?'
		mov	word_3B527, 0C6h ; '?'

loc_2ED7C:
		cmp	word_3A6CA, 96h	; '�
		jl	short loc_2EDBD
		cmp	word_3A6CA, 0AAh ; '?'
		jge	short loc_2EDBD
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2EDBD
		push	word_3B438
		push	0Ch
		push	word_3B527
		push	word_3B525
		push	ds
		push	offset unk_37635
		call	sub_30368
		add	sp, 0Ch
		sub	word_3B525, 0FFEBh
		sub	word_3B527, 0Ch

loc_2EDBD:
		pop	bp
		retf
sub_2EC9A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2EDBF	proc far

var_1		= byte ptr -1

		enter	2, 0
		push	si
		cmp	word_3A6CA, 0Ah
		jnz	short loc_2EDD2
		push	3
		push	cs
		call	near ptr sub_2D343
		pop	cx

loc_2EDD2:
		cmp	word_3A6CA, 64h	; 'd'
		jl	loc_2EE7A
		mov	ax, word_3A6CA
		mov	bx, 14h
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2EE20
		xor	si, si
		mov	[bp+var_1], 0
		jmp	short loc_2EE19
; ---------------------------------------------------------------------------

loc_2EDF0:
		push	large 0
		push	large 10001h
		push	20h ; ' '
		push	word ptr [bp+var_1]
		push	large 0C80122h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si
		mov	al, [bp+var_1]
		add	al, 0F4h ; '�
		mov	[bp+var_1], al

loc_2EE19:
		cmp	si, 0Ah
		jl	short loc_2EDF0
		jmp	short loc_2EE64
; ---------------------------------------------------------------------------

loc_2EE20:
		mov	ax, word_3A6CA
		mov	bx, 14h
		cwd
		idiv	bx
		cmp	dx, 0Ah
		jnz	short loc_2EE6C
		xor	si, si
		mov	[bp+var_1], 0
		jmp	short loc_2EE5F
; ---------------------------------------------------------------------------

loc_2EE36:
		push	large 0
		push	large 300004h
		push	20h ; ' '
		push	word ptr [bp+var_1]
		push	large 0C80122h
		push	ds
		push	offset unk_37635
		call	sub_304B8
		add	sp, 14h
		inc	si
		mov	al, [bp+var_1]
		add	al, 0F4h ; '�
		mov	[bp+var_1], al

loc_2EE5F:
		cmp	si, 0Ah
		jl	short loc_2EE36

loc_2EE64:
		push	7
		call	sub_125C9
		pop	cx

loc_2EE6C:
		cmp	word_3A6CA, 12Ch
		jl	short loc_2EE7A
		mov	word_3A6CA, 0

loc_2EE7A:
		pop	si
		leave
		retf
sub_2EDBF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2EE7D	proc far

var_C		= byte ptr -0Ch
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2

		enter	0Ch, 0
		push	si
		push	di
		lea	ax, [bp+var_C]
		push	ss
		push	ax
		push	ds
		push	offset unk_35FFC
		mov	cx, 3
		call	SCOPY@
		cmp	byte_3A6CE, 0
		jnz	short loc_2EED9
		mov	byte_3A6CE, 1
		mov	word_3B52D, 63h	; 'c'
		mov	word_35FF8, 63h	; 'c'
		mov	word_35FFA, 0
		mov	word_3A6CA, 0
		mov	word_3B52B, 0
		mov	word_3B529, 0
		mov	byte_3B52F, 0
		call	sub_232A4
		mov	eax, dword_36C16
		mov	random_seed, eax
		jmp	loc_2FC40
; ---------------------------------------------------------------------------

loc_2EED9:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 1
		jnz	loc_2F02C
		cmp	byte_3B52F, 0
		jnz	short loc_2EEFE
		push	word_3A6CA
		push	word_3A6C8
		call	sub_2191C
		add	sp, 4
		mov	byte_3B52F, al

loc_2EEFE:
		inc	word_3A6CA
		inc	word_3B52B
		cmp	word_36C26, 0C6h ; '?'
		jge	short loc_2EF13
		mov	ax, 1
		jmp	short loc_2EF22
; ---------------------------------------------------------------------------

loc_2EF13:
		cmp	word_36C26, 18Ch
		jle	short loc_2EF1F
		xor	ax, ax
		jmp	short loc_2EF22
; ---------------------------------------------------------------------------

loc_2EF1F:
		mov	ax, 2

loc_2EF22:
		mov	[bp+var_8], ax
		push	ax
		push	cs
		call	near ptr sub_2D271
		pop	cx
		cmp	word_35FF8, 0
		jnz	short loc_2EF38
		push	cs
		call	near ptr sub_2D439
		jmp	short loc_2EF97
; ---------------------------------------------------------------------------

loc_2EF38:
		cmp	word_35FF8, 1
		jnz	short loc_2EF45
		push	cs
		call	near ptr sub_2D817
		jmp	short loc_2EF97
; ---------------------------------------------------------------------------

loc_2EF45:
		cmp	word_35FF8, 2
		jnz	short loc_2EF52
		push	cs
		call	near ptr sub_2D8EA
		jmp	short loc_2EF97
; ---------------------------------------------------------------------------

loc_2EF52:
		cmp	word_35FF8, 63h	; 'c'
		jnz	short loc_2EF97
		cmp	word_3A6CA, 78h	; 'x'
		jle	short loc_2EF97
		mov	word_3A6CA, 1
		call	IRand
		mov	bx, 3
		cwd
		idiv	bx
		mov	word_35FF8, dx
		mov	ax, word_35FF8
		cmp	ax, word_3B52D
		jnz	short loc_2EF8D
		call	IRand
		mov	bx, 3
		cwd
		idiv	bx
		mov	word_35FF8, dx

loc_2EF8D:
		mov	ax, word_35FF8
		mov	word_3B52D, ax
		inc	word_35FFA

loc_2EF97:
		cmp	word_3A6CA, 0
		jnz	short loc_2EFAB
		push	0
		push	cs
		call	near ptr sub_2D343
		pop	cx
		mov	word_35FF8, 63h	; 'c'

loc_2EFAB:
		push	large 280060h
		push	large 780120h
		cmp	word_36C28, 120h
		jl	short loc_2EFDB
		cmp	word_36C28, 160h
		jg	short loc_2EFDB
		cmp	word_36C2A, 0A0h ; '?'
		jg	short loc_2EFDB
		cmp	word_36C2A, 78h	; 'x'
		jl	short loc_2EFDB
		mov	ax, 1
		jmp	short loc_2EFDD
; ---------------------------------------------------------------------------

loc_2EFDB:
		xor	ax, ax

loc_2EFDD:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_C]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B529
		push	ds
		push	offset word_3B52B
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3B529, 0
		jnz	loc_2FC40
		cmp	word_35FFA, 7
		jge	short loc_2F01B
		cmp	word_3A6C8, 10h
		jge	loc_2FC40

loc_2F01B:
		cmp	word_35FF8, 63h	; 'c'
		jnz	loc_2FC40
		mov	byte_3A6CE, 2
		jmp	loc_2F4BC
; ---------------------------------------------------------------------------

loc_2F02C:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 2
		jnz	loc_2F136
		inc	word_3A6CA
		inc	word_3B52B
		cmp	word_36C26, 0C6h ; '?'
		jge	short loc_2F04C
		mov	ax, 1
		jmp	short loc_2F05B
; ---------------------------------------------------------------------------

loc_2F04C:
		cmp	word_36C26, 18Ch
		jle	short loc_2F058
		xor	ax, ax
		jmp	short loc_2F05B
; ---------------------------------------------------------------------------

loc_2F058:
		mov	ax, 2

loc_2F05B:
		mov	[bp+var_8], ax
		push	ax
		push	cs
		call	near ptr sub_2D271
		pop	cx
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2F07F
		push	large 0F000Fh
		push	large 0F0009h
		call	sub_EB59
		add	sp, 8

loc_2F07F:
		cmp	word_3A6CA, 32h	; '2'
		jle	short loc_2F0C5
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2F0C5
		mov	al, byte_350AB
		cbw
		or	ax, ax
		jle	short loc_2F09F
		dec	byte_350AB

loc_2F09F:
		mov	al, byte_350AC
		cbw
		cmp	ax, 9
		jle	short loc_2F0AC
		dec	byte_350AC

loc_2F0AC:
		mov	al, byte_350AD
		cbw
		cmp	ax, 0Ah
		jle	short loc_2F0B9
		dec	byte_350AD

loc_2F0B9:
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4

loc_2F0C5:
		push	large 280060h
		push	large 780120h
		cmp	word_36C28, 120h
		jl	short loc_2F0F5
		cmp	word_36C28, 160h
		jg	short loc_2F0F5
		cmp	word_36C2A, 0A0h ; '?'
		jg	short loc_2F0F5
		cmp	word_36C2A, 78h	; 'x'
		jl	short loc_2F0F5
		mov	ax, 1
		jmp	short loc_2F0F7
; ---------------------------------------------------------------------------

loc_2F0F5:
		xor	ax, ax

loc_2F0F7:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_C]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B529
		push	ds
		push	offset word_3B52B
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3B529, 0
		jnz	loc_2FC40
		cmp	word_3A6CA, 78h	; 'x'
		jle	loc_2FC40
		mov	byte_3A6CE, 3
		jmp	loc_2F5DE
; ---------------------------------------------------------------------------

loc_2F136:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 3
		jnz	loc_2F27C
		inc	word_3A6CA
		inc	word_3B52B
		cmp	word_36C26, 0C6h ; '?'
		jge	short loc_2F156
		mov	ax, 1
		jmp	short loc_2F165
; ---------------------------------------------------------------------------

loc_2F156:
		cmp	word_36C26, 18Ch
		jle	short loc_2F162
		xor	ax, ax
		jmp	short loc_2F165
; ---------------------------------------------------------------------------

loc_2F162:
		mov	ax, 2

loc_2F165:
		mov	[bp+var_8], ax
		push	ax
		push	cs
		call	near ptr sub_2D271
		pop	cx
		cmp	word_35FF8, 0
		jnz	short loc_2F17B
		push	cs
		call	near ptr sub_2DD65
		jmp	short loc_2F1E7
; ---------------------------------------------------------------------------

loc_2F17B:
		cmp	word_35FF8, 1
		jnz	short loc_2F188
		push	cs
		call	near ptr sub_2DF0C
		jmp	short loc_2F1E7
; ---------------------------------------------------------------------------

loc_2F188:
		cmp	word_35FF8, 2
		jnz	short loc_2F195
		push	cs
		call	near ptr sub_2DFCA
		jmp	short loc_2F1E7
; ---------------------------------------------------------------------------

loc_2F195:
		cmp	word_35FF8, 3
		jnz	short loc_2F1A2
		push	cs
		call	near ptr sub_2E42E
		jmp	short loc_2F1E7
; ---------------------------------------------------------------------------

loc_2F1A2:
		cmp	word_35FF8, 63h	; 'c'
		jnz	short loc_2F1E7
		cmp	word_3A6CA, 78h	; 'x'
		jle	short loc_2F1E7
		mov	word_3A6CA, 1
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		mov	word_35FF8, dx
		mov	ax, word_35FF8
		cmp	ax, word_3B52D
		jnz	short loc_2F1DD
		call	IRand
		mov	bx, 4
		cwd
		idiv	bx
		mov	word_35FF8, dx

loc_2F1DD:
		mov	ax, word_35FF8
		mov	word_3B52D, ax
		inc	word_35FFA

loc_2F1E7:
		cmp	word_3A6CA, 0
		jnz	short loc_2F1FB
		push	0
		push	cs
		call	near ptr sub_2D343
		pop	cx
		mov	word_35FF8, 63h	; 'c'

loc_2F1FB:
		push	large 280060h
		push	large 780120h
		cmp	word_36C28, 120h
		jl	short loc_2F22B
		cmp	word_36C28, 160h
		jg	short loc_2F22B
		cmp	word_36C2A, 0A0h ; '?'
		jg	short loc_2F22B
		cmp	word_36C2A, 78h	; 'x'
		jl	short loc_2F22B
		mov	ax, 1
		jmp	short loc_2F22D
; ---------------------------------------------------------------------------

loc_2F22B:
		xor	ax, ax

loc_2F22D:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_C]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B529
		push	ds
		push	offset word_3B52B
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3B529, 0
		jnz	loc_2FC40
		cmp	word_35FFA, 9
		jge	short loc_2F26B
		cmp	word_3A6C8, 0Dh
		jge	loc_2FC40

loc_2F26B:
		cmp	word_35FF8, 63h	; 'c'
		jnz	loc_2FC40
		mov	byte_3A6CE, 4
		jmp	loc_2F4BC
; ---------------------------------------------------------------------------

loc_2F27C:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 4
		jnz	loc_2F386
		inc	word_3A6CA
		inc	word_3B52B
		cmp	word_36C26, 0C6h ; '?'
		jge	short loc_2F29C
		mov	ax, 1
		jmp	short loc_2F2AB
; ---------------------------------------------------------------------------

loc_2F29C:
		cmp	word_36C26, 18Ch
		jle	short loc_2F2A8
		xor	ax, ax
		jmp	short loc_2F2AB
; ---------------------------------------------------------------------------

loc_2F2A8:
		mov	ax, 2

loc_2F2AB:
		mov	[bp+var_8], ax
		push	ax
		push	cs
		call	near ptr sub_2D271
		pop	cx
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2F2CF
		push	large 0F000Fh
		push	large 0F0009h
		call	sub_EB59
		add	sp, 8

loc_2F2CF:
		cmp	word_3A6CA, 32h	; '2'
		jle	short loc_2F315
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2F315
		mov	al, byte_350AB
		cbw
		or	ax, ax
		jle	short loc_2F2EF
		dec	byte_350AB

loc_2F2EF:
		mov	al, byte_350AC
		cbw
		cmp	ax, 9
		jle	short loc_2F2FC
		dec	byte_350AC

loc_2F2FC:
		mov	al, byte_350AD
		cbw
		cmp	ax, 0Ah
		jle	short loc_2F309
		dec	byte_350AD

loc_2F309:
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4

loc_2F315:
		push	large 280060h
		push	large 780120h
		cmp	word_36C28, 120h
		jl	short loc_2F345
		cmp	word_36C28, 160h
		jg	short loc_2F345
		cmp	word_36C2A, 0A0h ; '?'
		jg	short loc_2F345
		cmp	word_36C2A, 78h	; 'x'
		jl	short loc_2F345
		mov	ax, 1
		jmp	short loc_2F347
; ---------------------------------------------------------------------------

loc_2F345:
		xor	ax, ax

loc_2F347:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_C]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B529
		push	ds
		push	offset word_3B52B
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3B529, 0
		jnz	loc_2FC40
		cmp	word_3A6CA, 78h	; 'x'
		jle	loc_2FC40
		mov	byte_3A6CE, 5
		jmp	loc_2F5DE
; ---------------------------------------------------------------------------

loc_2F386:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 5
		jnz	loc_2F4D7
		inc	word_3A6CA
		inc	word_3B52B
		cmp	word_36C26, 0C6h ; '?'
		jge	short loc_2F3A6
		mov	ax, 1
		jmp	short loc_2F3B5
; ---------------------------------------------------------------------------

loc_2F3A6:
		cmp	word_36C26, 18Ch
		jle	short loc_2F3B2
		xor	ax, ax
		jmp	short loc_2F3B5
; ---------------------------------------------------------------------------

loc_2F3B2:
		mov	ax, 2

loc_2F3B5:
		mov	[bp+var_8], ax
		push	ax
		push	cs
		call	near ptr sub_2D271
		pop	cx
		cmp	word_35FF8, 0
		jnz	short loc_2F3CB
		push	cs
		call	near ptr sub_2E7C4
		jmp	short loc_2F42A
; ---------------------------------------------------------------------------

loc_2F3CB:
		cmp	word_35FF8, 1
		jnz	short loc_2F3D8
		push	cs
		call	near ptr sub_2EB91
		jmp	short loc_2F42A
; ---------------------------------------------------------------------------

loc_2F3D8:
		cmp	word_35FF8, 2
		jnz	short loc_2F3E5
		push	cs
		call	near ptr sub_2EA03
		jmp	short loc_2F42A
; ---------------------------------------------------------------------------

loc_2F3E5:
		cmp	word_35FF8, 63h	; 'c'
		jnz	short loc_2F42A
		cmp	word_3A6CA, 78h	; 'x'
		jle	short loc_2F42A
		mov	word_3A6CA, 1
		call	IRand
		mov	bx, 3
		cwd
		idiv	bx
		mov	word_35FF8, dx
		mov	ax, word_35FF8
		cmp	ax, word_3B52D
		jnz	short loc_2F420
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	word_35FF8, dx

loc_2F420:
		mov	ax, word_35FF8
		mov	word_3B52D, ax
		inc	word_35FFA

loc_2F42A:
		cmp	word_3A6CA, 0
		jnz	short loc_2F43E
		push	0
		push	cs
		call	near ptr sub_2D343
		pop	cx
		mov	word_35FF8, 63h	; 'c'

loc_2F43E:
		push	large 280060h
		push	large 780120h
		cmp	word_36C28, 120h
		jl	short loc_2F46E
		cmp	word_36C28, 160h
		jg	short loc_2F46E
		cmp	word_36C2A, 0A0h ; '?'
		jg	short loc_2F46E
		cmp	word_36C2A, 78h	; 'x'
		jl	short loc_2F46E
		mov	ax, 1
		jmp	short loc_2F470
; ---------------------------------------------------------------------------

loc_2F46E:
		xor	ax, ax

loc_2F470:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_C]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B529
		push	ds
		push	offset word_3B52B
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3B529, 0
		jnz	loc_2FC40
		cmp	word_35FFA, 6
		jge	short loc_2F4AE
		cmp	word_3A6C8, 0Ah
		jge	loc_2FC40

loc_2F4AE:
		cmp	word_35FF8, 63h	; 'c'
		jnz	loc_2FC40
		mov	byte_3A6CE, 6

loc_2F4BC:
		mov	word_3A6CA, 0
		mov	word_3B52B, 0
		mov	word_35FF8, 63h	; 'c'
		mov	word_35FFA, 0
		jmp	loc_2FC40
; ---------------------------------------------------------------------------

loc_2F4D7:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 6
		jnz	loc_2F600
		inc	word_3A6CA
		inc	word_3B52B
		cmp	word_36C26, 0C6h ; '?'
		jge	short loc_2F4F7
		mov	ax, 1
		jmp	short loc_2F506
; ---------------------------------------------------------------------------

loc_2F4F7:
		cmp	word_36C26, 18Ch
		jle	short loc_2F503
		xor	ax, ax
		jmp	short loc_2F506
; ---------------------------------------------------------------------------

loc_2F503:
		mov	ax, 2

loc_2F506:
		mov	[bp+var_8], ax
		push	ax
		push	cs
		call	near ptr sub_2D271
		pop	cx
		cmp	word_3A6CA, 32h	; '2'
		jnz	short loc_2F52A
		push	large 0F000Fh
		push	large 0F0009h
		call	sub_EB59
		add	sp, 8

loc_2F52A:
		cmp	word_3A6CA, 32h	; '2'
		jle	short loc_2F570
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2F570
		mov	al, byte_350AB
		cbw
		or	ax, ax
		jle	short loc_2F54A
		dec	byte_350AB

loc_2F54A:
		mov	al, byte_350AC
		cbw
		cmp	ax, 9
		jle	short loc_2F557
		dec	byte_350AC

loc_2F557:
		mov	al, byte_350AD
		cbw
		cmp	ax, 0Ah
		jle	short loc_2F564
		dec	byte_350AD

loc_2F564:
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4

loc_2F570:
		push	large 280060h
		push	large 780120h
		cmp	word_36C28, 120h
		jl	short loc_2F5A0
		cmp	word_36C28, 160h
		jg	short loc_2F5A0
		cmp	word_36C2A, 0A0h ; '?'
		jg	short loc_2F5A0
		cmp	word_36C2A, 78h	; 'x'
		jl	short loc_2F5A0
		mov	ax, 1
		jmp	short loc_2F5A2
; ---------------------------------------------------------------------------

loc_2F5A0:
		xor	ax, ax

loc_2F5A2:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_C]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B529
		push	ds
		push	offset word_3B52B
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3B529, 0
		jnz	loc_2FC40
		cmp	word_3A6CA, 78h	; 'x'
		jle	loc_2FC40
		mov	byte_3A6CE, 7

loc_2F5DE:
		mov	word_3A6CA, 0
		mov	word_3B52B, 0
		mov	word_35FF8, 63h	; 'c'
		mov	word_35FFA, 0
		push	0
		push	cs
		call	near ptr sub_2D343
		pop	cx
		jmp	loc_2FC40
; ---------------------------------------------------------------------------

loc_2F600:
		mov	al, byte_3A6CE
		cbw
		cmp	ax, 7
		jnz	loc_2FC40
		inc	word_3A6CA
		inc	word_3B52B
		cmp	word_36C26, 0C6h ; '?'
		jge	short loc_2F620
		mov	ax, 1
		jmp	short loc_2F62F
; ---------------------------------------------------------------------------

loc_2F620:
		cmp	word_36C26, 18Ch
		jle	short loc_2F62C
		xor	ax, ax
		jmp	short loc_2F62F
; ---------------------------------------------------------------------------

loc_2F62C:
		mov	ax, 2

loc_2F62F:
		mov	[bp+var_8], ax
		push	ax
		push	cs
		call	near ptr sub_2D271
		pop	cx
		cmp	word_35FF8, 0
		jnz	short loc_2F646
		push	cs
		call	near ptr sub_2D439
		jmp	loc_2F720
; ---------------------------------------------------------------------------

loc_2F646:
		cmp	word_35FF8, 1
		jnz	short loc_2F654
		push	cs
		call	near ptr sub_2D817
		jmp	loc_2F720
; ---------------------------------------------------------------------------

loc_2F654:
		cmp	word_35FF8, 2
		jnz	short loc_2F662
		push	cs
		call	near ptr sub_2D8EA
		jmp	loc_2F720
; ---------------------------------------------------------------------------

loc_2F662:
		cmp	word_35FF8, 3
		jnz	short loc_2F670
		push	cs
		call	near ptr sub_2DD65
		jmp	loc_2F720
; ---------------------------------------------------------------------------

loc_2F670:
		cmp	word_35FF8, 4
		jnz	short loc_2F67E
		push	cs
		call	near ptr sub_2DF0C
		jmp	loc_2F720
; ---------------------------------------------------------------------------

loc_2F67E:
		cmp	word_35FF8, 5
		jnz	short loc_2F68C
		push	cs
		call	near ptr sub_2DFCA
		jmp	loc_2F720
; ---------------------------------------------------------------------------

loc_2F68C:
		cmp	word_35FF8, 6
		jnz	short loc_2F69A
		push	cs
		call	near ptr sub_2E42E
		jmp	loc_2F720
; ---------------------------------------------------------------------------

loc_2F69A:
		cmp	word_35FF8, 7
		jnz	short loc_2F6A7
		push	cs
		call	near ptr sub_2E7C4
		jmp	short loc_2F720
; ---------------------------------------------------------------------------

loc_2F6A7:
		cmp	word_35FF8, 8
		jnz	short loc_2F6B4
		push	cs
		call	near ptr sub_2EB91
		jmp	short loc_2F720
; ---------------------------------------------------------------------------

loc_2F6B4:
		cmp	word_35FF8, 9
		jnz	short loc_2F6C1
		push	cs
		call	near ptr sub_2EA03
		jmp	short loc_2F720
; ---------------------------------------------------------------------------

loc_2F6C1:
		cmp	word_35FF8, 0Ah
		jnz	short loc_2F6CE
		push	cs
		call	near ptr sub_2EDBF
		jmp	short loc_2F720
; ---------------------------------------------------------------------------

loc_2F6CE:
		cmp	word_35FF8, 0Bh
		jnz	short loc_2F6DB
		push	cs
		call	near ptr sub_2EC9A
		jmp	short loc_2F720
; ---------------------------------------------------------------------------

loc_2F6DB:
		cmp	word_35FF8, 63h	; 'c'
		jnz	short loc_2F720
		cmp	word_3A6CA, 5
		jle	short loc_2F720
		mov	word_3A6CA, 1
		call	IRand
		mov	bx, 0Ch
		cwd
		idiv	bx
		mov	word_35FF8, dx
		mov	ax, word_35FF8
		cmp	ax, word_3B52D
		jnz	short loc_2F716
		call	IRand
		mov	bx, 2
		cwd
		idiv	bx
		mov	word_35FF8, dx

loc_2F716:
		mov	ax, word_35FF8
		mov	word_3B52D, ax
		inc	word_35FFA

loc_2F720:
		cmp	word_3A6CA, 0
		jnz	short loc_2F734
		push	0
		push	cs
		call	near ptr sub_2D343
		pop	cx
		mov	word_35FF8, 63h	; 'c'

loc_2F734:
		push	large 280060h
		push	large 780120h
		cmp	word_36C28, 120h
		jl	short loc_2F764
		cmp	word_36C28, 160h
		jg	short loc_2F764
		cmp	word_36C2A, 0A0h ; '?'
		jg	short loc_2F764
		cmp	word_36C2A, 78h	; 'x'
		jl	short loc_2F764
		mov	ax, 1
		jmp	short loc_2F766
; ---------------------------------------------------------------------------

loc_2F764:
		xor	ax, ax

loc_2F766:
		push	ax
		push	seg seg032
		push	offset sub_21884
		push	2710h
		push	3
		push	ss
		lea	ax, [bp+var_C]
		push	ax
		push	ds
		push	offset word_3A6C8
		push	ds
		push	offset word_3B529
		push	ds
		push	offset word_3B52B
		call	sub_21A8A
		add	sp, 22h
		cmp	word_3A6C8, 0
		jg	loc_2FC40
		push	ds
		push	offset asc_360A1 ; "\x1B*"
		call	_printf
		add	sp, 4
		push	cs
		call	near ptr sub_2D241
		call	sub_EC0D
		call	sub_12579
		push	large 0
		push	large 0
		call	sub_EB59
		add	sp, 8
		push	7
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		call	sub_EC0D
		push	8
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	large 0F000Fh
		push	large 0F0000h
		call	sub_EB59
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		call	sub_EC0D
		push	9
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	large 0
		push	large 0
		call	sub_EB59
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		call	sub_EC0D
		push	0Ah
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	large 0F000Fh
		push	large 0F0000h
		call	sub_EB59
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		call	sub_EC0D
		push	0Bh
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	large 0
		push	large 0
		call	sub_EB59
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		call	sub_EC0D
		push	0Ch
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	large 0F000Fh
		push	large 0F0000h
		call	sub_EB59
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		call	sub_EC0D
		push	0Dh
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	large 0
		push	large 0
		call	sub_EB59
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		call	sub_EC0D
		push	0Eh
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	large 0F000Fh
		push	large 0F0000h
		call	sub_EB59
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		call	sub_EC0D
		push	0Fh
		push	ds
		push	offset aBoss8_grz ; "boss8.grz"
		push	0
		call	sub_1117C
		add	sp, 8
		push	large 0
		push	large 0
		call	sub_EB59
		add	sp, 8
		push	0
		call	sub_10CDD
		pop	cx
		push	0
		call	sub_110ED
		pop	cx
		push	0Ah
		call	sub_E364
		pop	cx
		mov	word_3A6CA, 0

loc_2F99A:
		inc	word_3A6CA
		mov	ax, word_3A6CA
		mov	bx, 4
		cwd
		idiv	bx
		or	dx, dx
		jnz	short loc_2F9F9
		xor	si, si
		jmp	short loc_2F9E0
; ---------------------------------------------------------------------------

loc_2F9AF:
		xor	di, di
		jmp	short loc_2F9DA
; ---------------------------------------------------------------------------

loc_2F9B3:
		mov	bx, si
		imul	bx, 3
		mov	al, [bx+di+6F0h]
		push	ax
		mov	bx, si
		imul	bx, 3
		cbw
		or	ax, ax
		jle	short loc_2F9CB
		mov	al, 1
		jmp	short loc_2F9CD
; ---------------------------------------------------------------------------

loc_2F9CB:
		mov	al, 0

loc_2F9CD:
		pop	dx
		sub	dl, al
		mov	bx, si
		imul	bx, 3
		mov	[bx+di+6F0h], dl
		inc	di

loc_2F9DA:
		cmp	di, 3
		jl	short loc_2F9B3
		inc	si

loc_2F9E0:
		cmp	si, 10h
		jl	short loc_2F9AF
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4
		push	7
		call	sub_125C9
		pop	cx

loc_2F9F9:
		mov	ax, word_3A6CA
		mov	bx, 2
		cwd
		idiv	bx
		imul	dx, -10h
		mov	ax, 198h
		sub	ax, dx
		push	ax
		call	sub_11738
		pop	cx
		cmp	word_3A6CA, 40h	; '@'
		jg	short loc_2FA23
		push	1
		call	sub_E364
		pop	cx
		jmp	loc_2F99A
; ---------------------------------------------------------------------------

loc_2FA23:
		push	ds
		push	offset a3_0	; "\x1B)3"
		call	_printf
		add	sp, 4
		push	ds
		push	offset a1640m_0	; "\x1B[16;40m"
		call	_printf
		add	sp, 4
		push	ds
		push	offset a00h_0	; "\x1B[0;0H"
		call	_printf
		add	sp, 4
		xor	di, di
		jmp	short loc_2FA62
; ---------------------------------------------------------------------------

loc_2FA4B:
		xor	si, si
		jmp	short loc_2FA5C
; ---------------------------------------------------------------------------

loc_2FA4F:
		push	ds
		push	offset asc_360B8 ; " "
		call	_printf
		add	sp, 4
		inc	si

loc_2FA5C:
		cmp	si, 50h	; 'P'
		jl	short loc_2FA4F
		inc	di

loc_2FA62:
		cmp	di, 19h
		jl	short loc_2FA4B
		push	ds
		push	offset aBoss7_d1_grp ; "boss7_d1.grp"
		call	sub_10BAE
		add	sp, 4
		xor	si, si
		jmp	short loc_2FA8C
; ---------------------------------------------------------------------------

loc_2FA77:
		xor	di, di
		jmp	short loc_2FA86
; ---------------------------------------------------------------------------

loc_2FA7B:
		mov	bx, si
		imul	bx, 3
		mov	byte ptr [bx+di+6F0h], 0
		inc	di

loc_2FA86:
		cmp	di, 3
		jl	short loc_2FA7B
		inc	si

loc_2FA8C:
		cmp	si, 10h
		jl	short loc_2FA77
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4
		push	ds
		push	offset a0	; "\x1B)0"
		call	_printf
		add	sp, 4
		push	ds
		push	offset a0m_0	; "\x1B[0m"
		call	_printf
		add	sp, 4
		push	ds
		push	offset a11h	; "\x1B[1;1H"
		call	_printf
		add	sp, 4
		xor	di, di
		jmp	short loc_2FADC
; ---------------------------------------------------------------------------

loc_2FAC5:
		xor	si, si
		jmp	short loc_2FAD6
; ---------------------------------------------------------------------------

loc_2FAC9:
		push	ds
		push	offset asc_360B8 ; " "
		call	_printf
		add	sp, 4
		inc	si

loc_2FAD6:
		cmp	si, 50h	; 'P'
		jl	short loc_2FAC9
		inc	di

loc_2FADC:
		cmp	di, 19h
		jl	short loc_2FAC5
		xor	si, si
		mov	di, 20h	; ' '
		mov	[bp+var_6], 0

loc_2FAEB:
		push	si
		call	sub_11738
		pop	cx
		add	si, di
		cmp	si, 190h
		jle	short loc_2FAFE
		sub	si, 190h

loc_2FAFE:
		cmp	[bp+var_6], 96h	; '�
		jge	short loc_2FB7F
		mov	ax, [bp+var_6]
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2FC0E
		mov	[bp+var_2], 0
		jmp	short loc_2FB6A
; ---------------------------------------------------------------------------

loc_2FB1B:
		mov	[bp+var_4], 0
		jmp	short loc_2FB61
; ---------------------------------------------------------------------------

loc_2FB22:
		mov	bx, [bp+var_2]
		imul	bx, 3
		add	bx, [bp+var_4]
		mov	al, [bx+3FE8h]
		mov	bx, [bp+var_2]
		imul	bx, 3
		add	bx, [bp+var_4]
		cmp	al, [bx+6F0h]
		jle	short loc_2FB42
		mov	al, 1
		jmp	short loc_2FB44
; ---------------------------------------------------------------------------

loc_2FB42:
		mov	al, 0

loc_2FB44:
		mov	bx, [bp+var_2]
		imul	bx, 3
		add	bx, [bp+var_4]
		add	al, [bx+6F0h]
		mov	bx, [bp+var_2]
		imul	bx, 3
		add	bx, [bp+var_4]
		mov	[bx+6F0h], al
		inc	[bp+var_4]

loc_2FB61:
		cmp	[bp+var_4], 3
		jl	short loc_2FB22
		inc	[bp+var_2]

loc_2FB6A:
		cmp	[bp+var_2], 10h
		jl	short loc_2FB1B
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4
		jmp	loc_2FC06
; ---------------------------------------------------------------------------

loc_2FB7F:
		mov	ax, [bp+var_6]
		mov	bx, 8
		cwd
		idiv	bx
		or	dx, dx
		jnz	loc_2FC0E
		cmp	[bp+var_6], 0C0h ; '?'
		jnz	short loc_2FB9A
		call	sub_12589

loc_2FB9A:
		mov	[bp+var_2], 0
		jmp	short loc_2FBE6
; ---------------------------------------------------------------------------

loc_2FBA1:
		mov	[bp+var_4], 0
		jmp	short loc_2FBDD
; ---------------------------------------------------------------------------

loc_2FBA8:
		mov	bx, [bp+var_2]
		imul	bx, 3
		add	bx, [bp+var_4]
		mov	al, [bx+6F0h]
		push	ax
		mov	bx, [bp+var_2]
		imul	bx, 3
		add	bx, [bp+var_4]
		cbw
		or	ax, ax
		jle	short loc_2FBC8
		mov	al, 0FFh
		jmp	short loc_2FBCA
; ---------------------------------------------------------------------------

loc_2FBC8:
		mov	al, 0

loc_2FBCA:
		pop	dx
		add	dl, al
		mov	bx, [bp+var_2]
		imul	bx, 3
		add	bx, [bp+var_4]
		mov	[bx+6F0h], dl
		inc	[bp+var_4]

loc_2FBDD:
		cmp	[bp+var_4], 3
		jl	short loc_2FBA8
		inc	[bp+var_2]

loc_2FBE6:
		cmp	[bp+var_2], 10h
		jl	short loc_2FBA1
		push	ds
		push	offset unk_35090
		call	sub_EB10
		add	sp, 4
		cmp	byte_350A5, 0
		jz	short loc_2FC1C
		cmp	[bp+var_6], 0DCh ; '?'
		jge	short loc_2FC0E

loc_2FC06:
		push	7
		call	sub_125C9
		pop	cx

loc_2FC0E:
		inc	[bp+var_6]
		push	1
		call	sub_E364
		pop	cx
		jmp	loc_2FAEB
; ---------------------------------------------------------------------------

loc_2FC1C:
		push	0
		call	sub_11738
		pop	cx
		xor	si, si
		jmp	short loc_2FC32
; ---------------------------------------------------------------------------

loc_2FC28:
		add	dword_34A5A, 2710h
		inc	si

loc_2FC32:
		cmp	si, 5
		jl	short loc_2FC28
		push	cs
		call	near ptr sub_2D241
		mov	byte_35DAA, 1

loc_2FC40:
		pop	di
		pop	si
		leave
		retf
sub_2EE7D	endp

seg037		ends

; ===========================================================================

; Segment type:	Pure code
seg038		segment	byte public 'CODE' use16
		assume cs:seg038
		;org 4
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2FC44	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	di, [bp+arg_4]
		or	di, di
		jl	short loc_2FCA9
		cmp	di, 27Fh
		jg	short loc_2FCA9
		xor	si, si
		jmp	short loc_2FCA4
; ---------------------------------------------------------------------------

loc_2FC5A:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+30h], 1
		jz	short loc_2FCA3
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+38h], 0
		jnz	short loc_2FCA3
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	es:[bx], di
		mov	ax, [bp+arg_6]
		mov	es:[bx+10h], ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+30h], 1
		push	1
		call	sub_125C9
		pop	cx
		les	bx, [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+38h], 0
		jmp	short loc_2FCA9
; ---------------------------------------------------------------------------

loc_2FCA3:
		inc	si

loc_2FCA4:
		cmp	si, 8
		jl	short loc_2FC5A

loc_2FCA9:
		pop	di
		pop	si
		pop	bp
		retf
sub_2FC44	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2FCAD	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		xor	si, si
		jmp	short loc_2FD20
; ---------------------------------------------------------------------------

loc_2FCB5:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+30h], 0
		jz	short loc_2FCEB
		push	large 100010h
		mov	ax, si
		add	ax, ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, ax
		push	word ptr es:[bx+10h]
		push	word ptr es:[bx]
		call	sub_10433
		add	sp, 8
		les	bx, [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+30h], 0
		jmp	short loc_2FD1F
; ---------------------------------------------------------------------------

loc_2FCEB:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+38h], 0
		jz	short loc_2FD1F
		push	large 100010h
		mov	ax, si
		add	ax, ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, ax
		push	word ptr es:[bx+10h]
		push	word ptr es:[bx]
		call	sub_10433
		add	sp, 8
		les	bx, [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+38h], 0

loc_2FD1F:
		inc	si

loc_2FD20:
		cmp	si, 8
		jl	short loc_2FCB5
		pop	si
		pop	bp
		retf
sub_2FCAD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2FD28	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		xor	si, si
		jmp	loc_2FE42
; ---------------------------------------------------------------------------

loc_2FD31:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+30h], 1
		jnz	short loc_2FDAE
		push	large 100010h
		mov	ax, si
		add	ax, ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, ax
		push	word ptr es:[bx+10h]
		push	word ptr es:[bx]
		call	sub_10433
		add	sp, 8
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		sub	word ptr es:[bx+10h], 0Ch
		cmp	word_34A86, 0
		jnz	short loc_2FD8C
		push	word_36C2A
		push	word_36C28
		push	si
		push	large [bp+arg_0]
		nop
		push	cs
		call	near ptr sub_2FE4C
		add	sp, 0Ah
		cmp	ax, 1
		jz	loc_2FE41

loc_2FD8C:
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		cmp	word ptr es:[bx+10h], 40h ; '@'
		jl	short loc_2FDA1
		push	0
		jmp	loc_2FE27
; ---------------------------------------------------------------------------

loc_2FDA1:
		les	bx, [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+30h], 0
		jmp	loc_2FE41
; ---------------------------------------------------------------------------

loc_2FDAE:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+38h], 0
		jz	loc_2FE41
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	al, es:[bx+38h]
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		inc	ax
		push	ax
		push	1
		mov	ax, si
		add	ax, ax
		mov	bx, word ptr [bp+arg_0]
		add	bx, ax
		push	word ptr es:[bx+10h]
		push	word ptr es:[bx]
		call	sub_19915
		add	sp, 8
		les	bx, [bp+arg_0]
		add	bx, si
		inc	byte ptr es:[bx+38h]
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+38h], 7
		jbe	short loc_2FE14
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+38h], 0
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+30h], 0
		jmp	short loc_2FE41
; ---------------------------------------------------------------------------

loc_2FE14:
		les	bx, [bp+arg_0]
		add	bx, si
		mov	al, es:[bx+38h]
		mov	ah, 0
		mov	bx, 4
		cwd
		idiv	bx
		inc	ax
		push	ax

loc_2FE27:
		push	1
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		push	word ptr es:[bx+10h]
		push	word ptr es:[bx]
		call	sub_19A62
		add	sp, 8

loc_2FE41:
		inc	si

loc_2FE42:
		cmp	si, 8
		jl	loc_2FD31
		pop	si
		pop	bp
		retf
sub_2FD28	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2FE4C	proc far

var_E		= qword	ptr -0Eh
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_6]
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+30h], 0
		jz	loc_2FF1E
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, di
		cmp	ax, 20h	; ' '
		jge	loc_2FF1E
		mov	ax, es:[bx]
		sub	ax, di
		cmp	ax, 0FFF0h
		jle	loc_2FF1E
		mov	ax, es:[bx+10h]
		sub	ax, [bp+arg_8]
		cmp	ax, 20h	; ' '
		jge	loc_2FF1E
		mov	ax, es:[bx+10h]
		sub	ax, [bp+arg_8]
		cmp	ax, 0FFF0h
		jle	short loc_2FF1E
		mov	ax, es:[bx]
		sub	ax, di
		cmp	ax, 8
		jle	short loc_2FEB2
		mov	word_34A7C, 1
		jmp	short loc_2FEE6
; ---------------------------------------------------------------------------

loc_2FEB2:
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, di
		cmp	ax, 8
		jnz	short loc_2FECD
		mov	word_34A7C, 0
		jmp	short loc_2FEE6
; ---------------------------------------------------------------------------

loc_2FECD:
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, di
		cmp	ax, 0FFF0h
		jle	short loc_2FEE6
		mov	word_34A7C, 2

loc_2FEE6:
		push	2		; int
		; Hack (fldz)
		db 0cdh
		db 035h
		db 0eeh
		sub	sp, 8
		; Hack (fstp [bp+var_E])
		db 0cdh
		db 039h
		db 05eh
		db 0f2h
		; Hack (wait)
		db 0cdh
		db 03dh
		call	sub_C62D
		add	sp, 0Ah
		les	bx, [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+30h], 0
		push	word_34A7C
		call	sub_C6E8
		pop	cx
		call	sub_C5B4
		add	word_36C2A, ax
		mov	ax, 1
		jmp	short loc_2FF20
; ---------------------------------------------------------------------------

loc_2FF1E:
		xor	ax, ax

loc_2FF20:
		pop	di
		pop	si
		pop	bp
		retf
sub_2FE4C	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2FF24	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	di, [bp+arg_4]
		xor	si, si
		jmp	loc_2FFB4
; ---------------------------------------------------------------------------

loc_2FF31:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+30h], 0
		jz	short loc_2FFB3
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+38h], 1
		jz	short loc_2FFB3
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	ax, es:[bx]
		sub	ax, di
		cmp	ax, 6
		jg	short loc_2FFB3
		mov	ax, es:[bx]
		sub	ax, di
		cmp	ax, 0FFF2h
		jl	short loc_2FFB3
		mov	ax, es:[bx+10h]
		sub	ax, [bp+arg_6]
		cmp	ax, 6
		jg	short loc_2FFB3
		mov	ax, es:[bx+10h]
		sub	ax, [bp+arg_6]
		cmp	ax, 0FFF2h
		jl	short loc_2FFB3
		push	large 100010h
		push	word ptr es:[bx+10h]
		push	word ptr es:[bx]
		call	sub_10433
		les	bx, [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+30h], 0
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+38h], 1
		push	10h
		call	sub_125C9
		add	sp, 0Ah
		mov	ax, 1
		jmp	short loc_2FFBD
; ---------------------------------------------------------------------------

loc_2FFB3:
		inc	si

loc_2FFB4:
		cmp	si, 8
		jl	loc_2FF31
		xor	ax, ax

loc_2FFBD:
		pop	di
		pop	si
		pop	bp
		retf
sub_2FF24	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_2FFC1	proc far

arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	di, [bp+arg_4]
		xor	si, si
		jmp	short loc_3003C
; ---------------------------------------------------------------------------

loc_2FFCD:
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx+30h], 0
		jz	short loc_3003B
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		cmp	es:[bx], di
		jl	short loc_3003B
		mov	ax, di
		add	ax, [bp+arg_8]
		cmp	es:[bx], ax
		jg	short loc_3003B
		mov	ax, es:[bx+10h]
		cmp	ax, [bp+arg_6]
		jl	short loc_3003B
		mov	ax, [bp+arg_6]
		add	ax, [bp+arg_A]
		cmp	es:[bx+10h], ax
		jg	short loc_3003B
		push	large 100010h
		push	word ptr es:[bx+10h]
		push	word ptr es:[bx]
		call	sub_10433
		les	bx, [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+30h], 0
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		mov	byte ptr es:[bx+38h], 1
		push	10h
		call	sub_125C9
		add	sp, 0Ah
		mov	ax, 1
		jmp	short loc_30043
; ---------------------------------------------------------------------------

loc_3003B:
		inc	si

loc_3003C:
		cmp	si, 8
		jl	short loc_2FFCD
		xor	ax, ax

loc_30043:
		pop	di
		pop	si
		pop	bp
		retf
sub_2FFC1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30047	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		cmp	[bp+arg_0], 0
		jnz	short loc_30065
		push	1083h
		call	@$bnew$qui	; operator new(uint)
		pop	cx
		mov	word ptr [bp+arg_0+2], dx
		mov	word ptr [bp+arg_0], ax
		or	ax, dx
		jz	short loc_300AA

loc_30065:
		mov	ax, word ptr [bp+arg_0]
		mov	word_3B530, ax
		xor	si, si
		jmp	short loc_30081
; ---------------------------------------------------------------------------

loc_3006F:
		mov	bx, word_3B530
		mov	byte ptr [bx], 0
		mov	word ptr [bx+18h], 0
		inc	si
		add	word_3B530, 2Ah	; '*'

loc_30081:
		cmp	si, 64h	; 'd'
		jl	short loc_3006F
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx+1068h],	0
		xor	si, si
		jmp	short loc_300A5
; ---------------------------------------------------------------------------

loc_30094:
		mov	ax, si
		add	ax, ax
		les	bx, [bp+arg_0]
		add	bx, ax
		mov	word ptr es:[bx+106Ah],	0
		inc	si

loc_300A5:
		cmp	si, 0Ah
		jl	short loc_30094

loc_300AA:
		mov	dx, word ptr [bp+arg_0+2]
		mov	ax, word ptr [bp+arg_0]
		pop	si
		pop	bp
		retf
sub_30047	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_300B3	proc far

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= dword	ptr  0Ah
arg_8		= dword	ptr  0Eh
arg_C		= word ptr  12h
arg_E		= byte ptr  14h

		push	bp
		mov	bp, sp
		push	si
		mov	si, [bp+arg_C]
		mov	ax, 180h
		sub	ax, [bp+arg_2]
		push	ax
		mov	ax, word_36C26
		add	ax, 0Ch
		sub	ax, [bp+arg_0]
		push	ax
		call	iatan2
		add	al, [bp+arg_E]
		mov	[bp+arg_E], al
		movsx	eax, si
		mov	dl, [bp+arg_E]
		mov	dh, 0
		and	dx, 0FFh
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+8FAh]
		imul	eax, edx
		sar	eax, 8
		les	bx, [bp+arg_4]
		mov	es:[bx], ax
		movsx	eax, si
		mov	dl, [bp+arg_E]
		mov	dh, 0
		and	dx, 0FFh
		add	dx, dx
		mov	bx, dx
		movsx	edx, word ptr [bx+87Ah]
		imul	eax, edx
		sar	eax, 8
		les	bx, [bp+arg_8]
		mov	es:[bx], ax
		pop	si
		pop	bp
		retf
sub_300B3	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30123	proc far

var_2		= byte ptr -2
var_1		= byte ptr -1
arg_0		= dword	ptr  6
arg_4		= dword	ptr  0Ah
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h
arg_C		= dword	ptr  12h
arg_10		= word ptr  16h
arg_12		= word ptr  18h

		enter	2, 0
		push	si
		push	di
		mov	di, [bp+arg_8]
		xor	si, si
		mov	[bp+var_1], 0
		mov	[bp+var_2], 0
		mov	bx, di
		dec	bx
		cmp	bx, 1Dh
		ja	loc_30320
		add	bx, bx
		jmp	cs:off_3032C[bx]

loc_30147:
		les	bx, [bp+arg_4]
		mov	ax, [bp+arg_A]
		mov	es:[bx], ax
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx], 0
		jmp	short loc_3017D
; ---------------------------------------------------------------------------

loc_3015A:
		push	[bp+arg_A]
		push	large [bp+arg_4]
		push	large [bp+arg_0]
		push	180h
		mov	ax, word_36C26
		add	ax, 8
		push	ax
		push	[bp+arg_12]
		push	[bp+arg_10]
		call	sub_11FF0
		add	sp, 12h

loc_3017D:
		mov	si, 1
		jmp	loc_30320
; ---------------------------------------------------------------------------

loc_30183:
		mov	[bp+var_2], 8

loc_30187:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 0
		jnz	short loc_3019A
		mov	al, [bp+var_2]
		add	al, 4
		mov	[bp+var_1], al
		jmp	short loc_301AE
; ---------------------------------------------------------------------------

loc_3019A:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 1
		jnz	short loc_301AE
		mov	al, 0FCh ; '�
		sub	al, [bp+var_2]
		mov	[bp+var_1], al
		mov	si, 1

loc_301AE:
		cmp	di, 15h
		jge	loc_302ED
		jmp	loc_302C1
; ---------------------------------------------------------------------------

loc_301B8:
		mov	[bp+var_2], 5

loc_301BC:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 0
		jnz	short loc_301CB
		mov	[bp+var_1], 0
		jmp	short loc_301F2
; ---------------------------------------------------------------------------

loc_301CB:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 1
		jnz	short loc_301DE
		mov	al, [bp+var_2]
		add	al, 4
		mov	[bp+var_1], al
		jmp	short loc_301F2
; ---------------------------------------------------------------------------

loc_301DE:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 2
		jnz	short loc_301F2
		mov	al, 0FCh ; '�
		sub	al, [bp+var_2]
		mov	[bp+var_1], al
		mov	si, 1

loc_301F2:
		cmp	di, 15h
		jge	loc_302ED
		jmp	loc_302C1
; ---------------------------------------------------------------------------

loc_301FC:
		mov	[bp+var_2], 4

loc_30200:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 0
		jnz	short loc_30210
		mov	al, [bp+var_2]
		add	al, 4
		jmp	short loc_30233
; ---------------------------------------------------------------------------

loc_30210:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 1
		jnz	short loc_30220
		mov	al, 0FCh ; '�
		sub	al, [bp+var_2]
		jmp	short loc_30233
; ---------------------------------------------------------------------------

loc_30220:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 2
		jnz	short loc_30238
		mov	al, [bp+var_2]
		mov	ah, 0
		imul	ax, 3
		add	al, 0Ch

loc_30233:
		mov	[bp+var_1], al
		jmp	short loc_30253
; ---------------------------------------------------------------------------

loc_30238:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 3
		jnz	short loc_30253
		mov	al, [bp+var_2]
		mov	ah, 0
		imul	ax, 3
		mov	dl, 0F4h ; '�
		sub	dl, al
		mov	[bp+var_1], dl
		mov	si, 1

loc_30253:
		cmp	di, 15h
		jge	loc_302ED
		jmp	short loc_302C1
; ---------------------------------------------------------------------------

loc_3025C:
		mov	[bp+var_2], 4

loc_30260:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 0
		jnz	short loc_3026F
		mov	[bp+var_1], 0
		jmp	short loc_302BC
; ---------------------------------------------------------------------------

loc_3026F:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 1
		jnz	short loc_3027F
		mov	al, [bp+var_2]
		add	al, 4
		jmp	short loc_3029F
; ---------------------------------------------------------------------------

loc_3027F:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 2
		jnz	short loc_3028F
		mov	al, 0FCh ; '�
		sub	al, [bp+var_2]
		jmp	short loc_3029F
; ---------------------------------------------------------------------------

loc_3028F:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 3
		jnz	short loc_302A4
		mov	al, [bp+var_2]
		add	al, al
		add	al, 8

loc_3029F:
		mov	[bp+var_1], al
		jmp	short loc_302BC
; ---------------------------------------------------------------------------

loc_302A4:
		les	bx, [bp+arg_C]
		cmp	word ptr es:[bx], 4
		jnz	short loc_302BC
		mov	al, [bp+var_2]
		add	al, al
		mov	dl, 0F8h ; '�
		sub	dl, al
		mov	[bp+var_1], dl
		mov	si, 1

loc_302BC:
		cmp	di, 15h
		jge	short loc_302ED

loc_302C1:
		mov	al, [bp+var_1]
		add	al, 40h	; '@'
		mov	[bp+var_1], al
		jmp	short loc_3030A
; ---------------------------------------------------------------------------

loc_302CB:
		call	IRand
		and	al, 0Fh
		add	al, 0F9h ; '�
		mov	[bp+var_1], al
		mov	si, 1
		jmp	short loc_302ED
; ---------------------------------------------------------------------------

loc_302DC:
		call	IRand
		and	al, 3Fh
		add	al, 20h	; ' '
		mov	[bp+var_1], al
		mov	si, 1
		jmp	short loc_3030A
; ---------------------------------------------------------------------------

loc_302ED:
		push	word ptr [bp+var_1]
		push	[bp+arg_A]
		push	large [bp+arg_4]
		push	large [bp+arg_0]
		push	[bp+arg_12]
		push	[bp+arg_10]
		push	cs
		call	near ptr sub_300B3
		add	sp, 10h
		jmp	short loc_30320
; ---------------------------------------------------------------------------

loc_3030A:
		push	word ptr [bp+var_1]
		push	[bp+arg_A]
		push	large [bp+arg_4]
		push	large [bp+arg_0]
		call	sub_12053
		add	sp, 0Ch

loc_30320:
		les	bx, [bp+arg_C]
		inc	word ptr es:[bx]
		mov	ax, si
		pop	di
		pop	si
		leave
		retf
sub_30123	endp

; ---------------------------------------------------------------------------
off_3032C	dw offset loc_30147
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_30320
		dw offset loc_3015A
		dw offset loc_30183
		dw offset loc_30187
		dw offset loc_301B8
		dw offset loc_301BC
		dw offset loc_301FC
		dw offset loc_30200
		dw offset loc_3025C
		dw offset loc_30260
		dw offset loc_30183
		dw offset loc_30187
		dw offset loc_301B8
		dw offset loc_301BC
		dw offset loc_301FC
		dw offset loc_30200
		dw offset loc_3025C
		dw offset loc_30260
		dw offset loc_302CB
		dw offset loc_302DC

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30368	proc far

var_A		= word ptr -0Ah
var_8		= word ptr -8
var_6		= word ptr -6
var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h

		enter	0Ah, 0
		push	si
		push	di
		mov	di, [bp+arg_4]
		mov	si, [bp+arg_A]
		mov	[bp+var_4], 0
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx+1068h],	64h ; 'd'
		jg	loc_304B4
		cmp	di, 280h
		jge	loc_304B4
		cmp	[bp+arg_6], 38h	; '8'
		jl	loc_304B4
		cmp	di, 0FFF8h
		jl	loc_304B4
		cmp	[bp+arg_6], 190h
		jg	loc_304B4
		cmp	byte_34A30, 0
		jnz	short loc_303B1
		xor	ax, ax
		jmp	short loc_303D0
; ---------------------------------------------------------------------------

loc_303B1:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_303BF
		mov	ax, 6
		jmp	short loc_303D0
; ---------------------------------------------------------------------------

loc_303BF:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_303CD
		mov	ax, 0Ch
		jmp	short loc_303D0
; ---------------------------------------------------------------------------

loc_303CD:
		mov	ax, 12h

loc_303D0:
		add	si, ax
		les	bx, dword_3919C
		mov	ax, es:[bx+19h]
		imul	si
		mov	bx, 28h	; '('
		cwd
		idiv	bx
		add	si, ax
		cmp	si, 10h
		jge	short loc_303EC
		mov	si, 10h

loc_303EC:
		mov	ax, word ptr [bp+arg_0]
		mov	word_3B530, ax
		mov	[bp+var_2], 0
		jmp	loc_304AC
; ---------------------------------------------------------------------------

loc_303FA:
		mov	bx, word_3B530
		cmp	byte ptr [bx], 1
		jz	loc_304A4
		mov	bx, word_3B530
		cmp	word ptr [bx+20h], 0
		jnz	loc_304A4
		mov	bx, word_3B530
		mov	word ptr [bx+1Eh], 0
		mov	ax, di
		shl	ax, 4
		mov	[bx+2],	ax
		mov	ax, [bp+arg_6]
		shl	ax, 4
		mov	[bx+4],	ax
		mov	[bx+22h], di
		mov	ax, [bp+arg_6]
		mov	[bx+24h], ax
		les	bx, [bp+arg_0]
		cmp	byte ptr es:[bx+1082h],	0
		jz	short loc_3044A
		mov	bx, word_3B530
		mov	word ptr [bx+20h], 1
		jmp	short loc_30451
; ---------------------------------------------------------------------------

loc_3044A:
		mov	bx, word_3B530
		mov	byte ptr [bx], 1

loc_30451:
		mov	bx, word_3B530
		mov	ax, [bp+arg_8]
		mov	[bx+0Eh], ax
		mov	word ptr [bx+0Ah], 0FFFFh
		mov	word ptr [bx+1Ah], 0
		les	bx, [bp+arg_0]
		inc	word ptr es:[bx+1068h]
		push	[bp+arg_6]
		push	di
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	si
		push	[bp+arg_8]
		push	ss
		lea	ax, [bp+var_A]
		push	ax
		push	ss
		lea	ax, [bp+var_8]
		push	ax
		push	cs
		call	near ptr sub_30123
		add	sp, 14h
		mov	[bp+var_6], ax
		mov	bx, word_3B530
		mov	ax, [bp+var_8]
		mov	[bx+10h], ax
		mov	ax, [bp+var_A]
		mov	[bx+12h], ax
		cmp	[bp+var_6], 1
		jz	short loc_304B4

loc_304A4:
		inc	[bp+var_2]
		add	word_3B530, 2Ah	; '*'

loc_304AC:
		cmp	[bp+var_2], 64h	; 'd'
		jl	loc_303FA

loc_304B4:
		pop	di
		pop	si
		leave
		retf
sub_30368	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_304B8	proc far

var_4		= word ptr -4
var_2		= word ptr -2
arg_0		= dword	ptr  6
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch
arg_8		= word ptr  0Eh
arg_A		= word ptr  10h
arg_C		= word ptr  12h
arg_E		= word ptr  14h
arg_10		= word ptr  16h
arg_12		= word ptr  18h

		enter	4, 0
		push	si
		push	di
		mov	si, [bp+arg_A]
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx+1068h],	64h ; 'd'
		jg	loc_30634
		cmp	byte_34A30, 0
		jnz	short loc_304D9
		xor	ax, ax
		jmp	short loc_304F8
; ---------------------------------------------------------------------------

loc_304D9:
		mov	al, byte_34A30
		cbw
		cmp	ax, 1
		jnz	short loc_304E7
		mov	ax, 6
		jmp	short loc_304F8
; ---------------------------------------------------------------------------

loc_304E7:
		mov	al, byte_34A30
		cbw
		cmp	ax, 2
		jnz	short loc_304F5
		mov	ax, 0Ch
		jmp	short loc_304F8
; ---------------------------------------------------------------------------

loc_304F5:
		mov	ax, 12h

loc_304F8:
		add	si, ax
		les	bx, dword_3919C
		mov	ax, es:[bx+19h]
		imul	si
		mov	bx, 28h	; '('
		cwd
		idiv	bx
		add	si, ax
		cmp	si, 10h
		jge	short loc_30514
		mov	si, 10h

loc_30514:
		mov	ax, word ptr [bp+arg_0]
		mov	word_3B530, ax
		xor	di, di
		jmp	loc_3062D
; ---------------------------------------------------------------------------

loc_3051F:
		mov	bx, word_3B530
		cmp	byte ptr [bx], 1
		jz	loc_30627
		mov	bx, word_3B530
		cmp	word ptr [bx+20h], 0
		jnz	loc_30627
		mov	bx, word_3B530
		mov	word ptr [bx+1Eh], 0
		mov	ax, [bp+arg_4]
		shl	ax, 4
		mov	[bx+2],	ax
		mov	ax, [bp+arg_6]
		shl	ax, 4
		mov	[bx+4],	ax
		mov	ax, [bp+arg_4]
		mov	[bx+22h], ax
		mov	ax, [bp+arg_6]
		mov	[bx+24h], ax
		les	bx, [bp+arg_0]
		cmp	byte ptr es:[bx+1082h],	0
		jz	short loc_30573
		mov	bx, word_3B530
		mov	word ptr [bx+20h], 1
		jmp	short loc_3057A
; ---------------------------------------------------------------------------

loc_30573:
		mov	bx, word_3B530
		mov	byte ptr [bx], 1

loc_3057A:
		mov	bx, word_3B530
		mov	word ptr [bx+0Eh], 0
		mov	al, byte ptr [bp+arg_C]
		mov	[bx+1],	al
		mov	word ptr [bx+0Ah], 0FFFFh
		mov	word ptr [bx+1Ah], 0
		les	bx, [bp+arg_0]
		inc	word ptr es:[bx+1068h]
		mov	ax, [bp+arg_10]
		shl	ax, 4
		mov	bx, word_3B530
		mov	[bx+6],	ax
		mov	ax, [bp+arg_12]
		shl	ax, 4
		mov	[bx+8],	ax
		cmp	[bp+arg_C], 5
		jnz	short loc_305F9
		push	[bp+arg_8]
		push	[bp+arg_E]
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		call	sub_12053
		add	sp, 0Ch
		mov	bx, word_3B530
		mov	ax, [bp+var_2]
		mov	[bx+14h], ax
		mov	ax, [bp+var_4]
		mov	[bx+16h], ax
		mov	ax, [bx+4]
		sub	ax, [bx+8]
		push	ax
		mov	ax, [bx+2]
		sub	ax, [bx+6]
		push	ax
		call	iatan2
		mov	bx, word_3B530
		mov	[bx+26h], ax

loc_305F9:
		push	[bp+arg_8]
		push	si
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		call	sub_12053
		add	sp, 0Ch
		mov	bx, word_3B530
		mov	ax, [bp+arg_E]
		mov	[bx+1Ch], ax
		mov	ax, [bp+var_2]
		mov	[bx+10h], ax
		mov	ax, [bp+var_4]
		mov	[bx+12h], ax
		jmp	short loc_30634
; ---------------------------------------------------------------------------

loc_30627:
		inc	di
		add	word_3B530, 2Ah	; '*'

loc_3062D:
		cmp	di, 64h	; 'd'
		jl	loc_3051F

loc_30634:
		pop	di
		pop	si
		leave
		retf
sub_304B8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30638	proc far

var_4		= word ptr -4
var_2		= word ptr -2

		enter	4, 0
		mov	bx, word_3B530
		mov	al, [bx+1]
		mov	ah, 0
		dec	ax
		mov	bx, ax
		cmp	bx, 5
		ja	locret_30893
		add	bx, bx
		jmp	cs:off_30895[bx]

loc_30656:
		mov	bx, word_3B530
		mov	ax, [bx+1Ch]
		jmp	loc_3088C
; ---------------------------------------------------------------------------

loc_30660:
		mov	bx, word_3B530
		cmp	word ptr [bx+28h], 0
		jnz	short loc_3067A
		call	IRand
		and	ax, 1
		inc	ax
		mov	bx, word_3B530
		mov	[bx+28h], ax

loc_3067A:
		mov	bx, word_3B530
		cmp	word ptr [bx+28h], 1
		jnz	short loc_3069B
		push	word ptr [bx+26h]
		push	word ptr [bx+1Ch]
		push	ds
		mov	ax, word_3B530
		add	ax, 12h
		push	ax
		push	ds
		mov	ax, word_3B530
		add	ax, 10h
		jmp	short loc_306B4
; ---------------------------------------------------------------------------

loc_3069B:
		mov	bx, word_3B530
		push	word ptr [bx+26h]
		push	word ptr [bx+1Ch]
		push	ds
		mov	ax, word_3B530
		add	ax, 10h
		push	ax
		push	ds
		mov	ax, word_3B530
		add	ax, 12h

loc_306B4:
		push	ax
		call	sub_12053
		add	sp, 0Ch
		mov	bx, word_3B530
		add	word ptr [bx+26h], 8
		cmp	word ptr [bx+26h], 100h
		jle	locret_30893
		push	word ptr [bx+1Ch]
		push	ds
		mov	ax, word_3B530
		add	ax, 12h
		push	ax
		push	ds
		mov	ax, word_3B530
		add	ax, 10h
		push	ax
		push	180h
		mov	ax, word_36C26
		add	ax, 8
		push	ax
		mov	ax, [bx+4]
		sar	ax, 4
		push	ax
		mov	ax, [bx+2]
		sar	ax, 4
		push	ax
		call	sub_11FF0
		add	sp, 12h
		mov	bx, word_3B530
		mov	word ptr [bx+0Eh], 0Ch
		mov	word ptr [bx+26h], 0
		leave
		retf
; ---------------------------------------------------------------------------

loc_30711:
		mov	bx, word_3B530
		cmp	word ptr [bx+2], 0
		jle	short loc_3072F
		mov	ax, [bx+2]
		sar	ax, 4
		cmp	ax, 2780h
		jge	short loc_3072F
		cmp	word ptr [bx+4], 460h
		jg	locret_30893

loc_3072F:
		mov	bx, word_3B530
		mov	ax, [bx+10h]
		neg	ax
		mov	[bx+10h], ax
		mov	word ptr [bx+12h], 0
		mov	byte ptr [bx+1], 1
		cmp	word ptr [bx+2], 0
		jg	short loc_3074F
		mov	word ptr [bx+2], 10h

loc_3074F:
		mov	bx, word_3B530
		cmp	word ptr [bx+2], 2780h
		jl	short loc_3075F
		mov	word ptr [bx+2], 2770h

loc_3075F:
		mov	bx, word_3B530
		cmp	word ptr [bx+4], 400h
		jg	locret_30893
		mov	word ptr [bx+4], 410h
		leave
		retf
; ---------------------------------------------------------------------------

loc_30773:
		mov	bx, word_3B530
		mov	ax, [bx+4]
		sar	ax, 4
		cmp	ax, 46h	; 'F'
		jg	locret_30893
		mov	word ptr [bx+10h], 0
		mov	ax, [bx+1Ch]
		mov	[bx+12h], ax
		mov	byte ptr [bx+1], 0
		mov	ax, [bx+4]
		sar	ax, 4
		cmp	ax, 40h	; '@'
		jg	locret_30893
		mov	word ptr [bx+4], 410h
		leave
		retf
; ---------------------------------------------------------------------------

loc_307A7:
		mov	bx, word_3B530
		mov	bx, [bx+26h]
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+8FAh]
		shl	eax, 8
		sar	eax, 8
		mov	bx, word_3B530
		add	ax, [bx+6]
		mov	[bx+2],	ax
		mov	bx, [bx+26h]
		and	bx, 0FFh
		add	bx, bx
		movsx	eax, word ptr [bx+87Ah]
		shl	eax, 8
		sar	eax, 8
		mov	bx, word_3B530
		add	ax, [bx+8]
		mov	[bx+4],	ax
		mov	ax, [bx+14h]
		add	[bx+6],	ax
		mov	ax, [bx+16h]
		add	[bx+8],	ax
		mov	word ptr [bx+10h], 0
		mov	word ptr [bx+12h], 0
		add	word ptr [bx+26h], 4
		leave
		retf
; ---------------------------------------------------------------------------

loc_30809:
		mov	bx, word_3B530
		push	word ptr [bx+1Ch]
		push	ss
		lea	ax, [bp+var_4]
		push	ax
		push	ss
		lea	ax, [bp+var_2]
		push	ax
		push	180h
		mov	ax, word_36C26
		add	ax, 8
		push	ax
		mov	ax, [bx+4]
		sar	ax, 4
		push	ax
		mov	ax, [bx+2]
		sar	ax, 4
		push	ax
		call	sub_11FF0
		add	sp, 12h
		mov	bx, word_3B530
		cmp	word ptr [bx+4], 1400h
		jge	short locret_30893
		mov	ax, [bx+10h]
		cmp	ax, [bp+var_2]
		jle	short loc_30852
		mov	ax, 0FFFFh
		jmp	short loc_30865
; ---------------------------------------------------------------------------

loc_30852:
		mov	bx, word_3B530
		mov	ax, [bx+10h]
		cmp	ax, [bp+var_2]
		jge	short loc_30863
		mov	ax, 1
		jmp	short loc_30865
; ---------------------------------------------------------------------------

loc_30863:
		xor	ax, ax

loc_30865:
		mov	bx, word_3B530
		add	[bx+10h], ax
		mov	ax, [bx+12h]
		cmp	ax, [bp+var_4]
		jle	short loc_30879
		mov	ax, 0FFFFh
		jmp	short loc_3088C
; ---------------------------------------------------------------------------

loc_30879:
		mov	bx, word_3B530
		mov	ax, [bx+12h]
		cmp	ax, [bp+var_4]
		jge	short loc_3088A
		mov	ax, 1
		jmp	short loc_3088C
; ---------------------------------------------------------------------------

loc_3088A:
		xor	ax, ax

loc_3088C:
		mov	bx, word_3B530
		add	[bx+12h], ax

locret_30893:
		leave
		retf
sub_30638	endp

; ---------------------------------------------------------------------------
off_30895	dw offset loc_30656
		dw offset loc_30660
		dw offset loc_30711
		dw offset loc_30773
		dw offset loc_307A7
		dw offset loc_30809

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_308A1	proc far

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, 0A800h
		mov	es, ax
		assume es:nothing
		mov	ax, [bp+arg_0]
		sar	ax, 3
		mov	dx, [bp+arg_2]
		shl	dx, 6
		add	ax, dx
		shr	dx, 2
		add	ax, dx
		mov	di, ax
		mov	ax, [bp+arg_0]
		and	ax, 7
		shl	ax, 4
		mov	bx, [bp+arg_4]
		shl	bx, 7
		add	ax, bx
		add	ax, 172Fh
		mov	si, ax
		mov	cx, 8

loc_308D9:
		movsw
		add	di, 4Eh	; 'N'
		cmp	di, 7D00h
		jge	short loc_308E5
		loop	loc_308D9

loc_308E5:
		pop	di
		pop	si
		pop	bp
		retf
sub_308A1	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_308E9	proc far

arg_0		= word ptr  6
arg_2		= word ptr  8
arg_4		= word ptr  0Ah

		push	bp
		mov	bp, sp
		push	7
		call	sub_EA71
		push	[bp+arg_4]
		push	[bp+arg_2]
		push	[bp+arg_0]
		push	cs
		call	near ptr sub_308A1
		add	sp, 8
		call	sub_EB05
		pop	bp
		retf
sub_308E9	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_3090A	proc far

var_1		= byte ptr -1
arg_4		= word ptr  0Ah
arg_6		= word ptr  0Ch

		enter	2, 0
		push	si
		push	di
		mov	di, [bp+arg_4]
		xor	si, si
		jmp	loc_309BE
; ---------------------------------------------------------------------------

loc_30918:
		mov	al, [si+3D48h]
		mov	ah, 0
		cmp	ax, 1
		jnz	short loc_3096F
		mov	bx, si
		add	bx, bx
		mov	ax, di
		sub	ax, [bx+3D18h]
		cmp	ax, 10h
		jge	short loc_30966
		mov	bx, si
		add	bx, bx
		mov	ax, di
		sub	ax, [bx+3D18h]
		cmp	ax, 0FFF8h
		jle	short loc_30966
		mov	bx, si
		add	bx, bx
		mov	ax, [bp+arg_6]
		sub	ax, [bx+3D28h]
		cmp	ax, 10h
		jge	short loc_30966
		mov	bx, si
		add	bx, bx
		mov	ax, [bp+arg_6]
		sub	ax, [bx+3D28h]
		cmp	ax, 0FFF8h
		jle	short loc_30966
		mov	ax, 1
		jmp	short loc_30968
; ---------------------------------------------------------------------------

loc_30966:
		xor	ax, ax

loc_30968:
		cmp	ax, 1
		jz	loc_30AF2

loc_3096F:
		mov	bx, si
		add	bx, bx
		lea	ax, [di+8]
		sub	ax, [bx+3D18h]
		cmp	ax, 10h
		jge	short loc_309B4
		mov	bx, si
		add	bx, bx
		lea	ax, [di+8]
		sub	ax, [bx+3D18h]
		cmp	ax, 0FFF8h
		jle	short loc_309B4
		mov	bx, si
		add	bx, bx
		mov	ax, [bp+arg_6]
		sub	ax, [bx+3D28h]
		cmp	ax, 10h
		jge	short loc_309B4
		mov	bx, si
		add	bx, bx
		mov	ax, [bp+arg_6]
		sub	ax, [bx+3D28h]
		cmp	ax, 0FFF8h
		jle	short loc_309B4
		mov	ax, 1
		jmp	short loc_309B6
; ---------------------------------------------------------------------------

loc_309B4:
		xor	ax, ax

loc_309B6:
		cmp	ax, 1
		jz	loc_30AF2
		inc	si

loc_309BE:
		cmp	si, 3
		jl	loc_30918
		mov	bx, word_3B530
		cmp	word ptr [bx+1Eh], 0
		jnz	loc_30AF6
		mov	ax, di
		sub	ax, word_36C28
		cmp	ax, 20h	; ' '
		jge	short loc_30A04
		mov	ax, di
		sub	ax, word_36C28
		cmp	ax, 0FFF8h
		jle	short loc_30A04
		mov	ax, [bp+arg_6]
		sub	ax, word_36C2A
		cmp	ax, 20h	; ' '
		jge	short loc_30A04
		mov	ax, [bp+arg_6]
		sub	ax, word_36C2A
		cmp	ax, 0FFF8h
		jle	short loc_30A04
		mov	ax, 1
		jmp	short loc_30A06
; ---------------------------------------------------------------------------

loc_30A04:
		xor	ax, ax

loc_30A06:
		cmp	ax, 1
		jz	short loc_30A47
		lea	ax, [di+8]
		sub	ax, word_36C28
		cmp	ax, 20h	; ' '
		jge	short loc_30A40
		lea	ax, [di+8]
		sub	ax, word_36C28
		cmp	ax, 0FFF8h
		jle	short loc_30A40
		mov	ax, [bp+arg_6]
		sub	ax, word_36C2A
		cmp	ax, 20h	; ' '
		jge	short loc_30A40
		mov	ax, [bp+arg_6]
		sub	ax, word_36C2A
		cmp	ax, 0FFF8h
		jle	short loc_30A40
		mov	ax, 1
		jmp	short loc_30A42
; ---------------------------------------------------------------------------

loc_30A40:
		xor	ax, ax

loc_30A42:
		cmp	ax, 1
		jnz	short loc_30A5E

loc_30A47:
		mov	bx, word_3B530
		sar	word ptr [bx+12h], 1
		sar	word ptr [bx+10h], 1
		mov	word ptr [bx+1Eh], 1
		add	word_360CD, 0Ah
		jmp	loc_30AF6
; ---------------------------------------------------------------------------

loc_30A5E:
		cmp	byte_34A57, 1
		jnz	loc_30AF6
		mov	ax, word_36C26
		add	ax, 0FFF8h
		mov	dx, di
		sub	dx, ax
		cmp	dx, 30h	; '0'
		jge	short loc_30AA0
		mov	ax, word_36C26
		add	ax, 0FFF8h
		mov	dx, di
		sub	dx, ax
		cmp	dx, 0FFF8h
		jle	short loc_30AA0
		mov	ax, [bp+arg_6]
		add	ax, 0FEA0h
		cmp	ax, 30h	; '0'
		jge	short loc_30AA0
		mov	ax, [bp+arg_6]
		add	ax, 0FEA0h
		cmp	ax, 0FFF8h
		jle	short loc_30AA0
		mov	ax, 1
		jmp	short loc_30AA2
; ---------------------------------------------------------------------------

loc_30AA0:
		xor	ax, ax

loc_30AA2:
		cmp	ax, 1
		jnz	short loc_30AF6
		mov	bx, word_3B530
		mov	ax, [bx+2]
		sar	ax, 4
		mov	dx, word_36C26
		add	dx, 0Ch
		cmp	ax, dx
		jg	short loc_30AC2
		mov	[bp+var_1], 80h	; '?'
		jmp	short loc_30AC6
; ---------------------------------------------------------------------------

loc_30AC2:
		mov	[bp+var_1], 0

loc_30AC6:
		push	word ptr [bp+var_1]
		push	80h ; '?'
		push	ds
		mov	ax, word_3B530
		add	ax, 12h
		push	ax
		push	ds
		mov	ax, word_3B530
		add	ax, 10h
		push	ax
		call	sub_12053
		add	sp, 0Ch
		mov	bx, word_3B530
		cmp	word ptr [bx+0Eh], 0
		jnz	short loc_30AF2
		mov	byte ptr [bx+1], 0

loc_30AF2:
		xor	ax, ax
		jmp	short loc_30AF9
; ---------------------------------------------------------------------------

loc_30AF6:
		mov	ax, 1

loc_30AF9:
		pop	di
		pop	si
		leave
		retf
sub_3090A	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30AFD	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		mov	bx, word_3B530
		inc	word ptr [bx+1Eh]
		cmp	word ptr [bx+1Eh], 15h
		jle	short loc_30B1D
		mov	word ptr [bx+1Eh], 0
		mov	byte ptr [bx], 0
		les	bx, [bp+arg_0]
		assume es:nothing
		dec	word ptr es:[bx+1068h]

loc_30B1D:
		pop	bp
		retf
sub_30AFD	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30B1F	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		les	bx, [bp+arg_0]
		cmp	word ptr es:[bx+1080h],	0
		jnz	short loc_30B33
		mov	ax, 1
		jmp	short loc_30B35
; ---------------------------------------------------------------------------

loc_30B33:
		xor	ax, ax

loc_30B35:
		les	bx, [bp+arg_0]
		mov	es:[bx+1080h], ax
		push	word ptr [bp+arg_0+2]
		push	bx
		nop
		push	cs
		call	near ptr sub_30F70
		add	sp, 4
		mov	ax, word ptr [bp+arg_0]
		mov	word_3B530, ax
		xor	si, si
		jmp	loc_30C9F
; ---------------------------------------------------------------------------

loc_30B54:
		mov	bx, word_3B530
		cmp	byte ptr [bx], 0
		jz	loc_30C99
		cmp	byte_360CC, 0
		jz	short loc_30B78
		les	bx, [bp+arg_0]
		mov	ax, si
		mov	cx, 2
		cwd
		idiv	cx
		cmp	es:[bx+1080h], dx
		jnz	short loc_30BA4

loc_30B78:
		mov	bx, word_3B530
		cmp	word ptr [bx+18h], 0
		jnz	short loc_30BA4
		cmp	word ptr [bx+0Ah], 0FFFFh
		jz	short loc_30BA4
		push	large 80010h
		mov	ax, [bx+0Ch]
		sar	ax, 4
		push	ax
		mov	ax, [bx+0Ah]
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8

loc_30BA4:
		mov	bx, word_3B530
		cmp	word ptr [bx+0Eh], 0
		jnz	short loc_30BBF
		cmp	byte ptr [bx+1], 0
		jz	short loc_30BBF
		push	large [bp+arg_0]
		push	cs
		call	near ptr sub_30638
		add	sp, 4

loc_30BBF:
		mov	bx, word_3B530
		cmp	word ptr [bx+12h], 80h ; '?'
		jle	short loc_30BCF
		mov	word ptr [bx+12h], 80h ; '?'

loc_30BCF:
		mov	bx, word_3B530
		cmp	word ptr [bx+10h], 80h ; '?'
		jle	short loc_30BDF
		mov	word ptr [bx+10h], 80h ; '?'

loc_30BDF:
		mov	bx, word_3B530
		mov	ax, [bx+12h]
		add	[bx+4],	ax
		mov	ax, [bx+10h]
		add	[bx+2],	ax
		cmp	word ptr [bx+1Eh], 0
		jnz	short loc_30C46
		mov	ax, [bx+4]
		sar	ax, 4
		push	ax
		mov	ax, [bx+2]
		sar	ax, 4
		push	ax
		push	ds
		push	offset unk_386B8
		push	cs
		call	near ptr sub_2FF24
		add	sp, 8
		or	ax, ax
		jz	short loc_30C46
		mov	bx, word_3B530
		mov	word ptr [bx+1Eh], 0
		mov	byte ptr [bx], 0
		les	bx, [bp+arg_0]
		dec	word ptr es:[bx+1068h]
		push	large 80010h
		mov	bx, word_3B530
		mov	ax, [bx+0Ch]
		sar	ax, 4
		push	ax
		mov	ax, [bx+0Ah]
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8

loc_30C46:
		mov	bx, word_3B530
		cmp	word ptr [bx+4], 1900h
		jge	short loc_30C65
		cmp	word ptr [bx+4], 400h
		jl	short loc_30C65
		cmp	word ptr [bx+2], 2780h
		jge	short loc_30C65
		cmp	word ptr [bx+2], 0
		jg	short loc_30C99

loc_30C65:
		mov	bx, word_3B530
		mov	byte ptr [bx], 0
		les	bx, [bp+arg_0]
		dec	word ptr es:[bx+1068h]
		mov	bx, word_3B530
		mov	word ptr [bx+1Eh], 0
		push	large 80010h
		mov	ax, [bx+0Ch]
		sar	ax, 4
		push	ax
		mov	ax, [bx+0Ah]
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8

loc_30C99:
		inc	si
		add	word_3B530, 2Ah	; '*'

loc_30C9F:
		cmp	si, 64h	; 'd'
		jl	loc_30B54
		push	ds
		push	offset unk_386B8
		push	cs
		call	near ptr sub_2FD28
		add	sp, 4
		mov	ax, word ptr [bp+arg_0]
		mov	word_3B530, ax
		xor	si, si
		jmp	loc_30DE4
; ---------------------------------------------------------------------------

loc_30CBC:
		mov	bx, word_3B530
		cmp	byte ptr [bx], 0
		jz	loc_30DDE
		cmp	byte_360CC, 0
		jz	short loc_30CE9
		les	bx, [bp+arg_0]
		mov	ax, es:[bx+1080h]
		and	ax, 1
		push	ax
		mov	ax, si
		mov	bx, 2
		cwd
		idiv	bx
		pop	ax
		cmp	ax, dx
		jnz	loc_30D76

loc_30CE9:
		mov	bx, word_3B530
		mov	ax, [bx+4]
		sar	ax, 4
		push	ax
		mov	ax, [bx+2]
		sar	ax, 4
		push	ax
		push	large [bp+arg_0]
		push	cs
		call	near ptr sub_3090A
		add	sp, 8
		cmp	ax, 1
		jnz	short loc_30D5D
		mov	bx, word_3B530
		cmp	word ptr [bx+18h], 1
		jnz	short loc_30D1A
		mov	word ptr [bx+18h], 0

loc_30D1A:
		mov	bx, word_3B530
		cmp	word ptr [bx+1Eh], 0
		jnz	short loc_30D28
		push	0
		jmp	short loc_30D42
; ---------------------------------------------------------------------------

loc_30D28:
		mov	bx, word_3B530
		cmp	word ptr [bx+1Eh], 0Ah
		jg	short loc_30D36
		push	1
		jmp	short loc_30D42
; ---------------------------------------------------------------------------

loc_30D36:
		mov	bx, word_3B530
		cmp	word ptr [bx+1Eh], 14h
		jge	short loc_30D66
		push	2

loc_30D42:
		mov	bx, word_3B530
		mov	ax, [bx+4]
		sar	ax, 4
		push	ax
		mov	ax, [bx+2]
		sar	ax, 4
		push	ax
		push	cs
		call	near ptr sub_308E9
		add	sp, 6
		jmp	short loc_30D66
; ---------------------------------------------------------------------------

loc_30D5D:
		mov	bx, word_3B530
		mov	word ptr [bx+18h], 1

loc_30D66:
		mov	bx, word_3B530
		mov	ax, [bx+2]
		mov	[bx+0Ah], ax
		mov	ax, [bx+4]
		mov	[bx+0Ch], ax

loc_30D76:
		mov	bx, word_3B530
		inc	word ptr [bx+1Ah]
		cmp	word ptr [bx+1Eh], 0
		jz	short loc_30D90
		push	large [bp+arg_0]
		push	cs
		call	near ptr sub_30AFD
		add	sp, 4
		jmp	short loc_30DDE
; ---------------------------------------------------------------------------

loc_30D90:
		push	large [bp+arg_0]
		nop
		push	cs
		call	near ptr sub_30F06
		add	sp, 4
		or	ax, ax
		jz	short loc_30DDE
		mov	bx, word_3B530
		cmp	word ptr [bx+18h], 0
		jnz	short loc_30DC6
		push	large 80010h
		mov	ax, [bx+0Ch]
		sar	ax, 4
		push	ax
		mov	ax, [bx+0Ah]
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8

loc_30DC6:
		mov	bx, word_3B530
		mov	byte ptr [bx], 0
		les	bx, [bp+arg_0]
		dec	word ptr es:[bx+1068h]
		mov	bx, word_3B530
		mov	word ptr [bx+1Eh], 0

loc_30DDE:
		inc	si
		add	word_3B530, 2Ah	; '*'

loc_30DE4:
		cmp	si, 64h	; 'd'
		jl	loc_30CBC
		pop	si
		pop	bp
		retf
sub_30B1F	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30DEE	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	ax, word ptr [bp+arg_0]
		mov	word_3B530, ax
		xor	si, si
		jmp	short loc_30E42
; ---------------------------------------------------------------------------

loc_30DFC:
		mov	bx, word_3B530
		cmp	byte ptr [bx], 0
		jz	short loc_30E3C
		mov	bx, word_3B530
		cmp	word ptr [bx+18h], 0
		jnz	short loc_30E2B
		push	large 80010h
		mov	ax, [bx+4]
		sar	ax, 4
		push	ax
		mov	ax, [bx+2]
		sar	ax, 4
		push	ax
		call	sub_10433
		add	sp, 8

loc_30E2B:
		mov	bx, word_3B530
		mov	word ptr [bx+1Eh], 0
		mov	byte ptr [bx], 0
		mov	word ptr [bx+20h], 0

loc_30E3C:
		inc	si
		add	word_3B530, 2Ah	; '*'

loc_30E42:
		cmp	si, 64h	; 'd'
		jl	short loc_30DFC
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx+1068h],	0
		pop	si
		pop	bp
		retf
sub_30DEE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30E54	proc far

var_2		= word ptr -2
arg_0		= word ptr  6

		enter	2, 0
		push	si
		mov	ax, [bp+arg_0]
		mov	word_3B530, ax
		xor	si, si
		jmp	short loc_30EC0
; ---------------------------------------------------------------------------

loc_30E63:
		mov	bx, word_3B530
		cmp	byte ptr [bx], 0
		jz	short loc_30EBA
		mov	bx, word_3B530
		cmp	word ptr [bx+1Eh], 0
		jnz	short loc_30EBA
		mov	bx, word_3B530
		mov	ax, [bx+12h]
		mov	[bp+var_2], ax
		; Hack (fild [bp+var_2])
		db 0cdh
		db 03bh
		db 046h
		db 0feh
		; Hack (fdiv flt_3624F)
		db 0cdh
		db 034h
		db 036h
		db 0afh
		db 018h
		call	sub_2395
		mov	bx, word_3B530
		mov	[bx+12h], ax
		mov	ax, [bx+10h]
		mov	[bp+var_2], ax
		; Hack (fild [bp+var_2])
		db 0cdh
		db 03bh
		db 046h
		db 0feh
		; Hack (fdiv flt_3624F)
		db 0cdh
		db 034h
		db 036h
		db 0afh
		db 018h
		call	sub_2395
		mov	bx, word_3B530
		mov	[bx+10h], ax
		mov	word ptr [bx+1Eh], 1
		add	word_360CD, 0Ah

loc_30EBA:
		inc	si
		add	word_3B530, 2Ah	; '*'

loc_30EC0:
		cmp	si, 64h	; 'd'
		jl	short loc_30E63
		pop	si
		leave
		retf
sub_30E54	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30EC8	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		mov	ax, word ptr [bp+arg_0]
		mov	word_3B530, ax
		xor	dx, dx
		jmp	short loc_30EF5
; ---------------------------------------------------------------------------

loc_30ED5:
		mov	bx, word_3B530
		cmp	byte ptr [bx], 0
		jz	short loc_30EEF
		mov	bx, word_3B530
		mov	byte ptr [bx], 0
		mov	word ptr [bx+1Eh], 0
		mov	word ptr [bx+20h], 0

loc_30EEF:
		inc	dx
		add	word_3B530, 2Ah	; '*'

loc_30EF5:
		cmp	dx, 64h	; 'd'
		jl	short loc_30ED5
		les	bx, [bp+arg_0]
		mov	word ptr es:[bx+1068h],	0
		pop	bp
		retf
sub_30EC8	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30F06	proc far
		push	bp
		mov	bp, sp
		cmp	word_34A78, 1
		jz	short loc_30F6C
		mov	bx, word_3B530
		cmp	word ptr [bx+1Eh], 0
		jnz	short loc_30F6C
		mov	bx, word_3B530
		mov	ax, [bx+2]
		sar	ax, 4
		mov	dx, word_36C26
		add	dx, 4
		cmp	ax, dx
		jl	short loc_30F6C
		mov	ax, [bx+2]
		sar	ax, 4
		mov	dx, word_36C26
		add	dx, 14h
		cmp	ax, dx
		jg	short loc_30F6C
		mov	ax, [bx+4]
		sar	ax, 4
		mov	dl, byte_34A59
		mov	dh, 0
		shl	dx, 3
		add	dx, 170h
		cmp	ax, dx
		jl	short loc_30F6C
		mov	ax, [bx+4]
		sar	ax, 4
		cmp	ax, 188h
		jge	short loc_30F6C
		mov	byte_34A4F, 1
		mov	ax, 1
		pop	bp
		retf
; ---------------------------------------------------------------------------

loc_30F6C:
		xor	ax, ax
		pop	bp
		retf
sub_30F06	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_30F70	proc far

arg_0		= word ptr  6

		push	bp
		mov	bp, sp
		push	si
		mov	ax, [bp+arg_0]
		mov	word_3B530, ax
		xor	si, si
		jmp	loc_31004
; ---------------------------------------------------------------------------

loc_30F7F:
		mov	bx, word_3B530
		cmp	word ptr [bx+20h], 0
		jz	short loc_30FFE
		mov	bx, word_3B530
		inc	word ptr [bx+20h]
		cmp	word ptr [bx+20h], 2
		jnz	short loc_30F9A
		push	0
		jmp	short loc_30FC2
; ---------------------------------------------------------------------------

loc_30F9A:
		mov	bx, word_3B530
		cmp	word ptr [bx+20h], 5
		jnz	short loc_30FB6
		push	0
		push	word ptr [bx+24h]
		push	word ptr [bx+22h]
		call	sub_113A6
		add	sp, 6
		jmp	short loc_30FFE
; ---------------------------------------------------------------------------

loc_30FB6:
		mov	bx, word_3B530
		cmp	word ptr [bx+20h], 6
		jnz	short loc_30FD8
		push	1

loc_30FC2:
		push	7
		mov	bx, word_3B530
		push	word ptr [bx+24h]
		push	word ptr [bx+22h]
		call	sub_1133E
		add	sp, 8
		jmp	short loc_30FFE
; ---------------------------------------------------------------------------

loc_30FD8:
		mov	bx, word_3B530
		cmp	word ptr [bx+20h], 9
		jnz	short loc_30FFE
		push	1
		push	word ptr [bx+24h]
		push	word ptr [bx+22h]
		call	sub_113A6
		add	sp, 6
		mov	bx, word_3B530
		mov	word ptr [bx+20h], 0
		mov	byte ptr [bx], 1

loc_30FFE:
		inc	si
		add	word_3B530, 2Ah	; '*'

loc_31004:
		cmp	si, 64h	; 'd'
		jl	loc_30F7F
		pop	si
		pop	bp
		retf
sub_30F70	endp

; ---------------------------------------------------------------------------
		dw 0
seg038		ends

; ---------------------------------------------------------------------------
; ===========================================================================

; Segment type:	Pure code
seg039		segment	byte public 'CODE' use16
		assume cs:seg039
; START	OF FUNCTION CHUNK FOR sub_31050
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

loc_31010:
		pop	di
		pop	es
		pop	dx
		pop	cx

loc_31014:
		pop	bx
		pop	si
		pop	ds
		clc
		retf
; ---------------------------------------------------------------------------

loc_31019:
		mov	al, byte ptr ds:[022h]
		mov	ah, byte ptr ds:[020h]
		; Hack (fnclex)
		db 0cdh
		db 037h
		db 0e2h
		test	ah, 80h
		jz	short loc_31010
		not	al
		and	al, ah
		jmp	loc_31165
; ---------------------------------------------------------------------------

loc_3102F:
		les	di, [si+6]
		test	bl, 8
		jnz	short loc_3103F
		mov	bx, es
		and	bx, 0F000h
		mov	es, bx
		assume es:nothing

loc_3103F:
		test	byte ptr es:[di], 80h
		jnz	short loc_31046
		inc	di

loc_31046:
		mov	bx, es:[di]
		xchg	bh, bl
		jmp	short loc_31096
; END OF FUNCTION CHUNK	FOR sub_31050
; ---------------------------------------------------------------------------
		jmp	short loc_310B1
; ---------------------------------------------------------------------------
		nop

; =============== S U B	R O U T	I N E =======================================


sub_31050	proc far

; FUNCTION CHUNK AT 0000 SIZE 0000003D BYTES

		push	ds
		push	si
		push	bx
		push	cx
		push	dx
		push	es
		push	di
		mov	ds, ax
		mov	al, byte ptr ds:[026h]
		or	al, al
		mov	bx, ax
		jz	short loc_31019
		mov	si, 33h	; '3'
		; Hack (fnstenv byte ptr [si])
		db 0d9h
		db 034h
		wait
		mov	ax, [si+2]
		test	al, 80h
		jz	short loc_31010
		fclex
		mov	dx, ax
		mov	al, [si]
		mov	dh, dl
		or	al, 40h
		and	dl, al
		and	dl, 7Fh
		mov	[si+2],	dl
		; The original executable has two wait instructions here, but TASM
		; would add a third one for some reason?
		wait
		fldenv	byte ptr [si]
		not	al
		and	al, dh
		or	bx, word ptr ds:[027h]
		cmp	bl, 3
		jge	short loc_3102F
		mov	bx, [si+8]

loc_31096:
		and	bh, 7
		mov	dh, bl
		and	dh, 0C0h
		cmp	dh, 0C0h ; '?'
		jz	short loc_310A6
		and	bl, 38h

loc_310A6:
		wait
		sti
		test	al, 1
		jz	short loc_310B1
		mov	al, 40h	; '@'
		jmp	loc_31165
; ---------------------------------------------------------------------------

loc_310B1:
		test	al, 2
		jz	short loc_3110A
		mov	cx, 8

loc_310B8:
		call	sub_31178
		wait
		fincstp
		loop	loc_310B8
		mov	ax, bx
		shr	ax, 1
		and	al, 9Ch
		cmp	al, 80h	; '?'
		jz	short loc_310D2
		cmp	al, 94h	; '�
		jz	short loc_310D2
		and	al, 98h
		cmp	al, 8

loc_310D2:
		jz	short loc_31108
		; Hack (fnstcw word ptr ds:051h)
		db 0d9h
		db 03eh
		db 051h
		db 000h
		wait
		or	byte ptr ds:051h, 2
		wait
		fldcw	word ptr ds:051h
		les	di, [si+0Ah]
		assume es:nothing
		cmp	bx, 30h	; '0'
		jnz	short loc_310F1
		wait
		fld	dword ptr es:[di]
		jmp	short loc_310FB
; ---------------------------------------------------------------------------

loc_310F1:
		cmp	bx, 430h
		jnz	short loc_31101
		wait
		fld	qword ptr es:[di]

loc_310FB:
		call	sub_31178
		mov	bx, 0DEF9h

loc_31101:
		wait
		mov	di, word ptr ds:[02Dh]
		jmp	short loc_3113B
; ---------------------------------------------------------------------------

loc_31108:
		jmp	short loc_31153
; ---------------------------------------------------------------------------

loc_3110A:
		mov	ah, byte ptr ds:[022h]
		not	ah
		and	ah, al
		and	ah, 7Fh
		jnz	short loc_31165
		test	al, 5
		jnz	short loc_31129
		test	al, 18h
		jz	short loc_31157
		mov	ax, bx
		shr	ax, 1
		and	al, 0E8h
		cmp	al, 88h	; '�
		jnz	short loc_31157

loc_31129:
		; Hack (fnstcw word ptr ds:051h)
		db 0d9h
		db 03eh
		db 051h
		db 000h
		wait
		mov	ax, word ptr ds:051h
		or	byte ptr ds:051h, 3Fh
		wait
		fldcw	word ptr ds:051h

loc_3113B:
		push	cs
		call	near ptr sub_311C5
		add	sp, 0Ah
		fstsw	word ptr ds:051h
		fclex
		mov	ax, word ptr ds:051h
		and	al, 3Fh
		or	byte ptr ds:[045h], al

loc_31153:
		wait
		fldcw	word ptr [si]
		clc

loc_31157:
		pop	di
		pop	es
		pop	dx
		pop	cx
		pop	bx
		pop	si
		pop	ds
		jb	short locret_31164
		pop	ax
		pop	ax
		pop	ax
		iret
; ---------------------------------------------------------------------------

locret_31164:
		retf
; ---------------------------------------------------------------------------

loc_31165:
		xor	dx, dx
		mov	bx, ax

loc_31169:
		inc	dx
		shr	bx, 1
		jnb	short loc_31169
		mov	word ptr ds:[029h], dx
		mov	ax, 29h	; ')'
		stc
		jmp	short loc_31157
sub_31050	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_31178	proc near
		wait
		fxam
		fstsw	word ptr ds:[051h]
		wait
		mov	ah, byte ptr ds:[052h]
		sahf
		jnb	short loc_3118B
		jnz	short loc_3118D
		retn
; ---------------------------------------------------------------------------

loc_3118B:
		jz	short loc_31192

loc_3118D:
		jb	short locret_31191
		jnp	short loc_31199

locret_31191:
		retn
; ---------------------------------------------------------------------------

loc_31192:
		wait
		fstp	st
		wait
		fldz
		retn
; ---------------------------------------------------------------------------

loc_31199:
		wait
		fstp	tbyte ptr ds:[047h]
		wait
		fild	qword ptr ds:[047h]
		mov	ax, word ptr ds:[04Fh]
		mov	dx, ax
		and	dh, 80h
		wait
		fstp	tbyte ptr ds:[047h]
		xor	ah, dh
		wait
		add	ax, word ptr ds:[04Fh]
		sub	ax, 403Eh
		xor	ah, dh
		mov	word ptr ds:[04Fh], ax
		wait
		fld	tbyte ptr ds:[047h]
		retn
sub_31178	endp


; =============== S U B	R O U T	I N E =======================================


sub_311C5	proc far
		mov	word ptr ds:[02Dh], di
		mov	dx, 0EA90h
		push	dx
		mov	dx, bx
		and	bl, 0C0h
		cmp	bl, 0C0h ; '?'
		jz	short loc_311DA
		or	dl, 7

loc_311DA:
		or	dh, 0D8h
		xchg	dh, dl
		push	dx
		mov	dx, 269Bh
		push	dx
		mov	dx, ss
		xor	dx, word ptr ds:[027h]
		push	dx
		mov	dx, sp
		add	dx, 2
		push	dx
		les	bx, [si+0Ah]
		retf
sub_311C5	endp ; sp-analysis failed

; ---------------------------------------------------------------------------
		dd 0
		dd 0
		dw 0
		db    0
		; Hack. Let's better use bytes for accuracy here.
tbyte_31200	db 035h, 0c2h, 068h, 021h, 0a2h, 0dah, 00fh, 0c9h, 0feh, 03fh
tbyte_3120A	db 035h, 0c2h, 068h, 021h, 0a2h, 0dah, 00fh, 0c9h, 0ffh, 03fh
flt_31214	dd -5.1110893e38
flt_31218	dd -5.1117124e38
		db 0, 4Ah, 0C0h, 0FFh
flt_31220	dd 0.5
tbyte_31224	db 085h, 064h, 0deh, 0f9h, 033h, 0f3h, 004h, 0b5h, 0ffh, 03fh
flt_3122E	dd 3.4028237e38
; ---------------------------------------------------------------------------
		mov	cl, 0
		jmp	short loc_3123C
; ---------------------------------------------------------------------------
		mov	cl, 2
		jmp	short loc_3123C
; ---------------------------------------------------------------------------
		mov	cl, 4

loc_3123C:
		wait
		fxam
		push	bp
		mov	bp, sp
		lea	sp, [bp-2]
		fstsw	word ptr [bp-2]
		wait
		mov	ah, [bp-1]
		sahf
		jb	short loc_3125F
		jnz	short loc_31280
		cmp	cl, 2
		jnz	short loc_3125D
		wait
		fstp	st
		wait
		fld1

loc_3125D:
		jmp	short loc_3127D
; ---------------------------------------------------------------------------

loc_3125F:
		jz	short loc_3126F
		jnp	short loc_3126F
		wait
		fstp	st
		wait
		fld	cs:flt_31214
		wait
		ftst

loc_3126F:
		jmp	short loc_3127D
; ---------------------------------------------------------------------------

loc_31271:
		wait
		fcompp
		wait
		fld	cs:flt_31214
		wait
		ftst

loc_3127D:
		jmp	loc_31327
; ---------------------------------------------------------------------------

loc_31280:
		wait
		fabs
		wait
		fld	tbyte ptr cs:tbyte_31200
		wait
		fxch	st(1)
		wait
		fprem
		mov	ch, 2
		and	ch, ah
		shr	ch, 1
		fstsw	word ptr [bp-2]
		wait
		mov	ah, [bp-1]
		sahf
		jp	short loc_31271
		mov	al, 3
		and	al, ah
		shl	ah, 1
		shl	ah, 1
		rcl	al, 1
		add	al, 0FCh ; '�
		rcl	al, 1
		cmp	cl, 2
		jnz	short loc_312B7
		add	al, cl
		mov	ch, 0

loc_312B7:
		and	al, 7
		test	al, 1
		jz	short loc_312C2
		wait
		fsubp	st(1), st
		jmp	short loc_312C5
; ---------------------------------------------------------------------------

loc_312C2:
		wait
		fstp	st(1)

loc_312C5:
		wait
		fptan
		cmp	cl, 4
		jz	short loc_312F6
		test	al, 3
		jp	short loc_312D4
		wait
		fxch	st(1)

loc_312D4:
		wait
		fld	st(1)
		wait
		fmul	st, st
		wait
		fxch	st(1)
		wait
		fmul	st, st
		wait
		faddp	st(1), st
		wait
		fsqrt
		shr	al, 1
		shr	al, 1
		xor	al, ch
		jz	short loc_312F1
		wait
		fchs

loc_312F1:
		wait
		fdivp	st(1), st
		jmp	short loc_31327
; ---------------------------------------------------------------------------

loc_312F6:
		mov	ah, al
		shr	ah, 1
		and	ah, 1
		xor	ah, ch
		jz	short loc_31304
		wait
		fchs

loc_31304:
		test	al, 3
		jp	short loc_31324
		wait
		fxch	st(1)
		wait
		ftst
		fstsw	word ptr [bp-2]
		wait
		test	byte ptr [bp-1], 40h
		jz	short loc_31324
		wait
		fcompp
		wait
		fld	cs:flt_3122E
		jmp	short loc_31327
; ---------------------------------------------------------------------------

loc_31324:
		wait
		fdivp	st(1), st

loc_31327:
		mov	sp, bp
		pop	bp
		retn
; ---------------------------------------------------------------------------
		wait
		fxam
		push	bp
		mov	bp, sp
		lea	sp, [bp-2]
		fstsw	word ptr [bp-2]
		wait
		mov	ah, [bp-1]
		sahf
		xchg	ax, cx
		jb	short loc_31344
		jnz	short loc_3135E
		jmp	short loc_31390
; ---------------------------------------------------------------------------

loc_31344:
		jz	short loc_31390
		jnp	short loc_31390
		wait
		fstp	st
		wait
		fld	tbyte ptr cs:tbyte_3120A
		jmp	short loc_31388
; ---------------------------------------------------------------------------

loc_31353:
		wait
		fcompp
		wait
		fld	tbyte ptr cs:tbyte_31200
		jmp	short loc_31388
; ---------------------------------------------------------------------------

loc_3135E:
		wait
		fabs
		wait
		fld1
		wait
		fcom	st(1)
		fstsw	word ptr [bp-2]
		wait
		mov	ah, [bp-1]
		sahf
		jz	short loc_31353
		jnb	short loc_31377
		wait
		fxch	st(1)

loc_31377:
		wait
		fpatan
		jnb	short loc_31388
		wait
		fld	tbyte ptr cs:tbyte_3120A
		wait
		fsubp	st(1), st
		xor	ch, 2

loc_31388:
		test	ch, 2
		jz	short loc_31390
		wait
		fchs

loc_31390:
		mov	sp, bp
		pop	bp
		retn
; ---------------------------------------------------------------------------
		wait
		fld1
		jmp	short loc_313A1
; ---------------------------------------------------------------------------
		wait
		fldlg2
		jmp	short loc_313A1
; ---------------------------------------------------------------------------
		wait
		fldln2

loc_313A1:
		wait
		fxch	st(1)
		push	bp
		mov	bp, sp
		wait
		fxam
		lea	sp, [bp-0Ah]
		fstsw	word ptr [bp-0Ah]
		wait
		mov	ah, [bp-9]
		sahf
		jb	short loc_313C4
		jz	short loc_313BF
		test	ah, 2
		jz	short loc_313E1

loc_313BF:
		wait
		fstp	st
		jmp	short loc_313D3
; ---------------------------------------------------------------------------

loc_313C4:
		jz	short loc_313DC
		wait
		fstp	st(1)
		jnp	short loc_313DC
		wait
		fstp	st(1)
		test	ah, 2
		jz	short loc_31405

loc_313D3:
		wait
		fstp	st
		wait
		fld	cs:flt_31218

loc_313DC:
		wait
		ftst
		jmp	short loc_31405
; ---------------------------------------------------------------------------

loc_313E1:
		wait
		fld	st
		wait
		fstp	tbyte ptr [bp-0Ah]
		wait
		cmp	word ptr [bp-2], 3FFFh
		jnz	short loc_31402
		cmp	word ptr [bp-4], 8000h
		jnz	short loc_31402
		wait
		fld1
		wait
		fsubp	st(1), st
		wait
		fyl2xp1
		jmp	short loc_31405
; ---------------------------------------------------------------------------

loc_31402:
		wait
		fyl2x

loc_31405:
		mov	sp, bp
		pop	bp
		retn
; ---------------------------------------------------------------------------
		sub	cx, cx
		jmp	short loc_3141F
; ---------------------------------------------------------------------------
		wait
		fldl2t
		mov	cl, 1
		wait
		fxch	st(1)
		jmp	short loc_3141F
; ---------------------------------------------------------------------------
		wait
		fldl2e
		mov	cl, 1
		wait
		fxch	st(1)

loc_3141F:
		wait
		fxam
		push	bp
		mov	bp, sp
		lea	sp, [bp-4]
		fstsw	word ptr [bp-4]
		jcxz	short loc_31431
		wait
		fxch	st(1)

loc_31431:
		wait
		mov	ah, [bp-3]
		sahf
		jb	short loc_31448
		jnz	short loc_31463
		wait
		fstp	st
		jcxz	short loc_31442
		wait
		fstp	st

loc_31442:
		wait
		fld1
		jmp	loc_314EC
; ---------------------------------------------------------------------------

loc_31448:
		jcxz	short loc_3144D
		wait
		fstp	st

loc_3144D:
		jz	short loc_3145D
		jnp	short loc_3145D
		wait
		fstp	st
		wait
		fld	cs:flt_3122E
		jmp	loc_314E1
; ---------------------------------------------------------------------------

loc_3145D:
		wait
		ftst
		jmp	loc_314EC
; ---------------------------------------------------------------------------

loc_31463:
		jcxz	short loc_31468
		wait
		fmulp	st(1), st

loc_31468:
		wait
		fabs
		wait
		fcom	cs:flt_31220
		fstsw	word ptr [bp-4]
		wait
		test	byte ptr [bp-3], 41h
		jz	short loc_31487
		wait
		f2xm1
		wait
		fld1
		wait
		faddp	st(1), st
		jmp	short loc_314E1
; ---------------------------------------------------------------------------

loc_31487:
		wait
		fld1
		wait
		fld	st(1)
		fstcw	word ptr [bp-4]
		wait
		fscale
		or	byte ptr [bp-3], 0Fh
		wait
		fldcw	word ptr [bp-4]
		wait
		frndint
		and	byte ptr [bp-3], 0F3h
		wait
		fldcw	word ptr [bp-4]
		wait
		fist	word ptr [bp-2]
		wait
		fxch	st(1)
		wait
		fchs
		wait
		fxch	st(1)
		wait
		fscale
		wait
		fstp	st(1)
		wait
		fsubp	st(1), st
		wait
		f2xm1
		wait
		fld1
		wait
		faddp	st(1), st
		shr	word ptr [bp-2], 1
		jnb	short loc_314D4
		wait
		fld	tbyte ptr cs:tbyte_31224
		wait
		fmulp	st(1), st

loc_314D4:
		wait
		fild	word ptr [bp-2]
		wait
		fxch	st(1)
		wait
		fscale
		wait
		fstp	st(1)

loc_314E1:
		test	ah, 2
		jz	short loc_314EC
		wait
		fld1
		wait
		fdivrp	st(1), st

loc_314EC:
		mov	sp, bp
		pop	bp
		retn

; =============== S U B	R O U T	I N E =======================================

; Attributes: library function bp-based	frame

e087_Entry	proc far

var_2		= word ptr -2
arg_1		= byte ptr  7

		push	bp
		mov	bp, sp
		push	ax
		push	si
		push	ds
		test	[bp+arg_1], 2
		jz	short loc_314FD
		sti

loc_314FD:
		lds	si, [bp+2]
		mov	ax, ds
		xor	ax, ss:27h
		mov	ds, ax
		mov	ax, [si-1]
		sub	al, 34h	; '4'
		cmp	al, 8
		jnb	short loc_31567
		cmp	ax, 0E303h
		jz	short loc_3153C
		cmp	ax, 0E007h
		jnz	short loc_3152D
		cmp	byte ptr ss:26h, 2
		jge	short loc_3152D
		fstsw	[bp+var_2]
		inc	word ptr [bp+2]
		jmp	short loc_3158A
; ---------------------------------------------------------------------------

loc_3152D:
		sub	si, 2
		mov	byte ptr [si], 9Bh ; '�
		add	byte ptr [si+1], 0A4h ;	'?'

loc_31537:
		mov	[bp+2],	si
		jmp	short loc_3158A
; ---------------------------------------------------------------------------

loc_3153C:
		fninit
		inc	word ptr [bp+2]
		mov	word ptr ss:20h, 4100h
		mov	word ptr ss:22h, 3Fh ; '?'
		mov	word ptr ss:45h, 0
		mov	ax, ss:31h
		mov	ss:2Dh,	ax
		mov	word ptr ss:24h, 0
		jmp	short loc_3158A
; ---------------------------------------------------------------------------

loc_31567:
		ja	short loc_3158F
		test	ah, 20h
		jnz	short loc_3159C
		sub	si, 2
		mov	[bp+2],	si
		mov	byte ptr [si], 9Bh ; '�
		inc	si
		mov	al, ah
		and	ax, 7C0h
		shr	al, 1
		shr	al, 1
		shr	al, 1
		xor	al, 18h
		add	ax, 0D826h
		mov	[si], ax

loc_3158A:
		pop	ds
		pop	si
		pop	ax
		pop	bp
		iret
; ---------------------------------------------------------------------------

loc_3158F:
		cmp	al, 9
		ja	short loc_3159C
		sub	si, 2
		mov	word ptr [si], 9B90h
		jmp	short loc_31537
; ---------------------------------------------------------------------------

loc_3159C:
		int	3		; Trap to Debugger
		jmp	short loc_3158A
e087_Entry	endp

; ---------------------------------------------------------------------------
		db 22h,	2, 26h,	2, 2Ah,	2, 1Bh,	3, 8Eh,	3, 84h,	3, 89h
		db 3, 7, 4, 0F9h, 3, 0FDh, 3
; ---------------------------------------------------------------------------

e087_Shortcut:
		sti
		push	ax
		push	si
		push	es
		push	bp
		mov	bp, sp
		les	si, [bp+8]
		lods	byte ptr es:[si]
		mov	[bp+8],	si
		cbw
		xchg	ax, si
		push	cx
		call	word ptr cs:[si+5A3h]
		pop	cx
		pop	bp
		pop	es
		pop	si
		pop	ax
		iret
seg039		ends

; ===========================================================================

; Segment type:	Pure code
seg040		segment	byte public 'CODE' use16
		assume cs:seg040
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing
byte_315D0	db 87h,	0E2h, 0, 0Ch, 18h, 24h,	30h, 3Ch, 48h, 54h, 60h
		db 6Ch,	78h, 84h, 90h, 9Ch, 0A8h, 0B4h

; =============== S U B	R O U T	I N E =======================================


sub_315E2	proc near
		push	dx
		push	si
		mov	dx, [si+6]
		and	dh, 7Fh
		or	dx, [si]
		or	dx, [si+2]
		or	dx, [si+4]
		jnz	short loc_31614
		cmp	bx, 0FFFFh
		jz	short loc_31610
		cmp	word ptr [bx+8], 4001h
		jl	short loc_31610
		mov	dx, [bx+6]
		and	dh, 7Fh
		or	dx, [bx]
		or	dx, [bx+2]
		or	dx, [bx+4]
		jnz	short loc_31654

loc_31610:
		clc

loc_31611:
		pop	si
		pop	dx
		retn
; ---------------------------------------------------------------------------

loc_31614:
		cmp	bx, 0FFFFh
		jz	short loc_31656
		cmp	word ptr [bx+8], 4001h
		jl	short loc_31656
		mov	dx, [bx+6]
		and	dh, 7Fh
		or	dx, [bx]
		or	dx, [bx+2]
		or	dx, [bx+4]
		jz	short loc_31656
		mov	dx, [si+6]
		cmp	dx, [bx+6]
		ja	short loc_31656
		jb	short loc_31654
		mov	dx, [si+4]
		cmp	dx, [bx+4]
		ja	short loc_31656
		jb	short loc_31654
		mov	dx, [si+2]
		cmp	dx, [bx+2]
		ja	short loc_31656
		jb	short loc_31654
		mov	dx, [si]
		cmp	dx, [bx]
		ja	short loc_31656

loc_31654:
		mov	si, bx

loc_31656:
		push	di
		mov	ch, 1
		call	sub_33CD9
		mov	cx, 6
		cld
		rep movsw
		stc
		pop	di
		jmp	short loc_31611
sub_315E2	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_3167E

loc_31666:
		mov	al, [si+0Ah]

loc_31669:
		mov	[bp-5],	al
		mov	word ptr [bp-4], 4001h
		nop
		jmp	short loc_316B1
; ---------------------------------------------------------------------------

loc_31674:
		mov	di, [bp+4]
		nop
		call	sub_32423

loc_3167B:
		jmp	loc_31811
; END OF FUNCTION CHUNK	FOR sub_3167E

; =============== S U B	R O U T	I N E =======================================


sub_3167E	proc near

; FUNCTION CHUNK AT 0096 SIZE 00000018 BYTES

		push	bx
		push	di
		mov	bx, di
		mov	di, [bp+4]
		nop
		call	sub_315E2
		pop	di
		pop	bx
		jb	short loc_3167B
		cmp	bx, 4001h
		jl	short loc_31666
		mov	al, [bp-6]
		or	al, al
		jnz	short loc_31674
		jmp	short loc_31666
sub_3167E	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_316C3

loc_3169C:
		mov	bx, 0FFFFh
		mov	al, [di+0Ah]
		xor	al, cl
		mov	si, di
		mov	di, [bp+4]
		nop
		call	sub_315E2
		jb	short loc_3167B
		jmp	short loc_31669
; ---------------------------------------------------------------------------

loc_316B1:
		mov	ax, [si]
		mov	bx, [si+2]
		mov	cx, [si+4]
		mov	dx, [si+6]
		jmp	loc_317FE
; END OF FUNCTION CHUNK	FOR sub_316C3

; =============== S U B	R O U T	I N E =======================================


sub_316BF	proc near
		mov	cl, 1
		jmp	short loc_316C5
sub_316BF	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_316C3	proc near

var_6		= byte ptr -6
var_5		= byte ptr -5
var_4		= word ptr -4
var_2		= byte ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

; FUNCTION CHUNK AT 00CC SIZE 00000023 BYTES

		mov	cl, 0

loc_316C5:
		push	bp
		mov	bp, sp
		lea	sp, [bp-6]
		push	si
		push	di
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_2]
		mov	al, cl
		xor	al, [di+0Ah]
		xor	al, [si+0Ah]
		mov	[bp+var_6], al
		mov	ax, [si+8]
		mov	bx, [di+8]
		cmp	ax, 4001h
		jge	short sub_3167E
		cmp	bx, 4001h
		jge	short loc_3169C
		cmp	ax, bx
		jge	short loc_316FB
		xor	cl, [di+0Ah]
		xchg	ax, bx
		xchg	si, di
		jmp	short loc_316FE
; ---------------------------------------------------------------------------

loc_316FB:
		mov	cl, [si+0Ah]

loc_316FE:
		mov	[bp+var_5], cl
		mov	cx, [si+8]
		mov	[bp+var_4], cx
		cmp	bx, 0C001h
		jle	short loc_316B1
		sub	ax, bx
		cmp	ax, 41h	; 'A'
		jg	short loc_316B1
		mov	bx, [di+2]
		mov	cx, [di+4]
		mov	dx, [di+6]
		mov	di, [di]
		xchg	ax, di
		mov	[bp+var_2], 0
		sub	di, 8
		jl	short loc_31741

loc_31729:
		mov	[bp+var_2], al
		mov	al, ah
		mov	ah, bl
		mov	bl, bh
		mov	bh, cl
		mov	cl, ch
		mov	ch, dl
		mov	dl, dh
		mov	dh, 0
		sub	di, 8
		jge	short loc_31729

loc_31741:
		and	di, 7
		jz	short loc_31754

loc_31746:
		shr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ax, 1
		rcr	[bp+var_2], 1
		dec	di
		jnz	short loc_31746

loc_31754:
		cmp	[bp+var_6], 0
		jnz	short loc_31777
		add	ax, [si]
		adc	bx, [si+2]
		adc	cx, [si+4]
		adc	dx, [si+6]
		jnb	short loc_317DE
		rcr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ax, 1
		rcr	[bp+var_2], 1
		inc	[bp+var_4]
		jmp	short loc_317DE
; ---------------------------------------------------------------------------

loc_31777:
		xor	[bp+var_5], 1
		sub	ax, [si]
		sbb	bx, [si+2]
		sbb	cx, [si+4]
		sbb	dx, [si+6]
		jnb	short loc_317A0
		xor	[bp+var_5], 1
		not	dx
		not	cx
		not	bx
		not	ax
		neg	[bp+var_2]
		cmc
		adc	ax, di
		adc	bx, di
		adc	cx, di
		adc	dx, di

loc_317A0:
		mov	si, 8

loc_317A3:
		or	dh, dh
		jnz	short loc_317DC
		mov	dh, dl
		mov	dl, ch
		mov	ch, cl
		mov	cl, bh
		mov	bh, bl
		mov	bl, ah
		mov	ah, al
		mov	al, [bp+var_2]
		mov	[bp+var_2], 0
		sub	[bp+var_4], 8
		dec	si
		jge	short loc_317A3
		mov	[bp+var_4], 0C001h
		mov	[bp+var_5], 0
		jmp	short loc_317FE
; ---------------------------------------------------------------------------

loc_317CE:
		dec	[bp+var_4]
		shl	[bp+var_2], 1
		rcl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx

loc_317DC:
		jns	short loc_317CE

loc_317DE:
		shl	[bp+var_2], 1
		adc	ax, di
		adc	bx, di
		adc	cx, di
		adc	dx, di
		jnb	short loc_317F0
		rcr	dx, 1
		inc	[bp+var_4]

loc_317F0:
		cmp	[bp+var_4], 4001h
		jge	short loc_31819
		cmp	[bp+var_4], 0C001h
		jle	short loc_31822

loc_317FE:
		cld
		mov	di, [bp+arg_0]
		stosw
		xchg	ax, bx
		stosw
		xchg	ax, cx
		stosw
		xchg	ax, dx
		stosw
		mov	ax, [bp+var_4]
		stosw
		mov	al, [bp+var_5]
		stosb

loc_31811:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	6
; ---------------------------------------------------------------------------

loc_31819:
		mov	ch, 8
		mov	[bp+var_4], 4001h
		jmp	short loc_31829
; ---------------------------------------------------------------------------

loc_31822:
		mov	ch, 10h
		mov	[bp+var_4], 0C001h

loc_31829:
		call	sub_33CD9
		mov	[bp+var_5], 0
		sub	ax, ax
		mov	bx, ax
		mov	cx, ax
		cwd
		jmp	short loc_317FE
sub_316C3	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_3188D

loc_31839:
		mov	ax, 4001h

loc_3183C:
		mov	di, [bp+arg_0]
		mov	cl, [bp+var_6]
		call	sub_3240D

loc_31845:
		pop	ax
		jmp	loc_3191D
; ---------------------------------------------------------------------------

loc_31849:
		push	di
		mov	bx, di
		mov	di, [bp+arg_0]
		call	sub_315E2
		pop	di
		jb	short loc_31845
		cmp	word ptr [di+8], 0C001h
		jle	short loc_31874
		jmp	short loc_31839
; ---------------------------------------------------------------------------

loc_3185E:
		push	si
		mov	bx, 0FFFFh
		mov	si, di
		mov	di, [bp+arg_0]
		call	sub_315E2
		pop	si
		jb	short loc_31845
		cmp	word ptr [si+8], 0C001h
		jg	short loc_31839

loc_31874:
		mov	di, [bp+arg_0]
		call	sub_32423
		jmp	short loc_31845
; ---------------------------------------------------------------------------

loc_3187C:
		mov	ch, 8
		call	sub_33CD9
		jmp	short loc_31839
; ---------------------------------------------------------------------------

loc_31883:
		mov	ch, 10h
		call	sub_33CD9

loc_31888:
		mov	ax, 0C001h
		jmp	short loc_3183C
; END OF FUNCTION CHUNK	FOR sub_3188D

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_3188D	proc near

var_6		= byte ptr -6
arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8
arg_1A		= word ptr  1Eh

; FUNCTION CHUNK AT 0269 SIZE 00000054 BYTES

		push	bp
		mov	bp, sp
		push	si
		push	di
		cld
		mov	si, [bp+arg_4]
		mov	di, [bp+arg_2]
		mov	cl, [si+0Ah]
		xor	cl, [di+0Ah]
		push	cx
		mov	dx, 4001h
		mov	bx, [di+8]
		mov	cx, 0C001h
		mov	ax, [si+8]
		cmp	ax, dx
		jge	short loc_31849
		cmp	bx, dx
		jge	short loc_3185E
		cmp	ax, cx
		jle	short loc_31888
		cmp	bx, cx
		jle	short loc_31888
		add	ax, bx
		dec	ax
		cmp	ax, 4001h
		jge	short loc_3187C
		inc	ax
		cmp	ax, 0C001h
		jle	short loc_31883
		push	word ptr [si+6]
		push	word ptr [si+4]
		push	word ptr [si+2]
		push	word ptr [si]
		sub	sp, 4
		push	word ptr [di+6]
		push	word ptr [di+4]
		push	word ptr [di+2]
		push	word ptr [di]
		xchg	ax, di
		mov	bp, sp
		call	sub_31923
		add	sp, 14h
		or	dx, dx
		js	short loc_318FB
		dec	di
		shl	si, 1
		rcl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		rcl	dx, 1

loc_318FB:
		shl	si, 1
		adc	ax, 0
		jnb	short loc_3190D
		adc	bx, ax
		adc	cx, ax
		adc	dx, ax
		jnb	short loc_3190D
		rcr	dx, 1
		inc	di

loc_3190D:
		mov	si, di
		mov	di, [bp+arg_1A]
		stosw
		xchg	ax, bx
		stosw
		xchg	ax, cx
		stosw
		xchg	ax, dx
		stosw
		xchg	ax, si
		stosw
		pop	ax
		stosb

loc_3191D:
		pop	di
		pop	si
		pop	bp
		retn	6
sub_3188D	endp


; =============== S U B	R O U T	I N E =======================================


sub_31923	proc near
		push	di
		sub	di, di
		mov	cx, di
		mov	si, di
		test	byte ptr [bp+0Fh], 80h
		jz	short loc_31936
		mov	cx, [bp+0]
		mov	si, [bp+2]

loc_31936:
		test	byte ptr [bp+3], 80h
		jz	short loc_3194B
		add	cx, [bp+0Ch]
		adc	si, [bp+0Eh]
		adc	di, di
		test	byte ptr [bp+0Fh], 80h
		jz	short loc_3194B
		dec	di

loc_3194B:
		sub	bx, bx
		mov	ax, [bp+0Ch]
		mul	word ptr [bp+4]
		add	cx, ax
		adc	si, dx
		adc	di, 0
		mov	ax, [bp+10h]
		or	ax, ax
		jz	short loc_31978
		mul	word ptr [bp+0]
		add	cx, ax
		adc	si, dx
		adc	di, 0
		mov	ax, [bp+10h]
		mul	word ptr [bp+2]
		add	si, ax
		adc	di, dx
		adc	bx, 0

loc_31978:
		mov	ax, [bp+0Ch]
		mul	word ptr [bp+6]
		add	si, ax
		adc	di, dx
		adc	bx, 0
		mov	ax, [bp+0Eh]
		mul	word ptr [bp+4]
		add	si, ax
		adc	di, dx
		adc	bx, 0
		mov	ax, [bp+12h]
		or	ax, ax
		jz	short loc_319A3
		mul	word ptr [bp+0]
		add	si, ax
		adc	di, dx
		adc	bx, 0

loc_319A3:
		sub	cx, cx
		push	si
		mov	si, cx
		mov	ax, [bp+0Eh]
		mul	word ptr [bp+6]
		add	di, ax
		adc	bx, dx
		adc	cx, 0
		mov	ax, [bp+10h]
		or	ax, ax
		jz	short loc_319D3
		mul	word ptr [bp+4]
		add	di, ax
		adc	bx, dx
		adc	cx, 0
		mov	ax, [bp+10h]
		mul	word ptr [bp+6]
		add	bx, ax
		adc	cx, dx
		adc	si, 0

loc_319D3:
		mov	ax, [bp+12h]
		or	ax, ax
		jz	short loc_319FE
		mul	word ptr [bp+2]
		add	di, ax
		adc	bx, dx
		adc	cx, 0
		adc	si, 0
		mov	ax, [bp+12h]
		mul	word ptr [bp+4]
		add	bx, ax
		adc	cx, dx
		adc	si, 0
		mov	ax, [bp+12h]
		mul	word ptr [bp+6]
		add	cx, ax
		adc	si, dx

loc_319FE:
		mov	dx, si
		xchg	ax, di
		pop	si
		pop	di
		retn
sub_31923	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_31A5A

loc_31A04:
		mov	si, di
		mov	di, [bp+arg_0]
		nop
		call	sub_315E2
		jb	short loc_31A3E
		cmp	word ptr [bx+8], 4001h
		jl	short loc_31A46
		call	sub_32423
		jmp	short loc_31A3E
; ---------------------------------------------------------------------------

loc_31A1B:
		mov	si, bx
		mov	bx, 0FFFFh
		mov	di, [bp+arg_0]
		nop
		call	sub_315E2
		jb	short loc_31A3E
		jmp	short loc_31A30
; ---------------------------------------------------------------------------

loc_31A2B:
		mov	ch, 4

loc_31A2D:
		call	sub_33CD9

loc_31A30:
		mov	ax, 4001h

loc_31A33:
		mov	cl, [bp-7]
		nop
		mov	di, [bp+arg_0]
		nop
		call	sub_3240D

loc_31A3E:
		jmp	loc_31DA2
; ---------------------------------------------------------------------------

loc_31A41:
		mov	ch, 10h
		call	sub_33CD9

loc_31A46:
		mov	ax, 0C001h
		jmp	short loc_31A33
; ---------------------------------------------------------------------------

loc_31A4B:
		mov	ch, 8
		jmp	short loc_31A2D
; ---------------------------------------------------------------------------

loc_31A4F:
		mov	ax, [bp-012h]
		or	ax, [bp-014h]
		jnz	short loc_31AB6
		jmp	loc_31DAE
; END OF FUNCTION CHUNK	FOR sub_31A5A

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_31A5A	proc near

var_14		= word ptr -14h
var_12		= word ptr -12h
var_10		= word ptr -10h
var_E		= word ptr -0Eh
var_C		= word ptr -0Ch
var_A		= word ptr -0Ah
var_8		= byte ptr -8
var_7		= byte ptr -7
var_6		= word ptr -6
arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

; FUNCTION CHUNK AT 0434 SIZE 00000056 BYTES
; FUNCTION CHUNK AT 07DE SIZE 00000023 BYTES

		push	bp
		mov	bp, sp
		push	si
		push	di
		lea	sp, [bp-0Ch]
		mov	di, [bp+arg_2]
		mov	bx, [bp+arg_4]
		cld
		mov	al, [bx+0Ah]
		xor	al, [di+0Ah]
		mov	[bp+var_7], al
		mov	si, [di+8]
		mov	ax, [bx+8]
		cmp	si, 4001h
		jge	short loc_31A04
		cmp	ax, 4001h
		jge	short loc_31A1B
		cmp	si, 0C001h
		jle	short loc_31A2B
		cmp	ax, 0C001h
		jle	short loc_31A46
		sub	ax, si
		cmp	ax, 4001h
		jge	short loc_31A4B
		cmp	ax, 0C001h
		jle	short loc_31A41
		mov	dx, [di+6]
		push	dx
		mov	cx, [di+4]
		push	cx
		push	word ptr [di+2]
		push	word ptr [di]
		mov	[bp+var_6], ax
		mov	[bp+var_8], 0
		mov	di, [bx+6]
		mov	si, [bx+4]
		jcxz	short loc_31A4F

loc_31AB6:
		xchg	ax, cx
		mov	cx, [bx+2]
		mov	bx, [bx]
		cmp	di, dx
		jb	short loc_31B3A
		mov	[bp+var_8], 1
		sub	bx, [bp+var_14]
		sbb	cx, [bp+var_12]
		sbb	si, ax
		sbb	di, dx
		jnb	short loc_31B3A
		sub	ax, ax
		cwd
		sub	ax, si
		sbb	dx, di
		div	[bp+var_E]
		mov	[bp+var_A], ax
		mul	[bp+var_E]
		add	si, ax
		adc	di, dx
		mov	ax, [bp+var_10]
		mul	[bp+var_A]
		add	cx, ax
		adc	si, dx
		adc	di, 0
		mov	ax, [bp+var_12]
		mul	[bp+var_A]
		add	bx, ax
		adc	cx, dx
		adc	si, 0
		adc	di, 0
		mov	ax, [bp+var_14]
		mul	[bp+var_A]
		neg	[bp+var_A]
		sbb	[bp+var_8], 0
		add	bx, dx
		adc	cx, 0
		adc	si, 0
		adc	di, 0
		xchg	ax, di
		jl	short loc_31B35
		cmp	si, [bp+var_E]
		jb	short loc_31B37
		add	[bp+var_A], 1
		adc	[bp+var_8], 0
		sub	di, [bp+var_14]
		sbb	bx, [bp+var_12]
		sbb	cx, [bp+var_10]
		sbb	si, [bp+var_E]

loc_31B35:
		jl	short loc_31B9D

loc_31B37:
		jmp	loc_31C06
; ---------------------------------------------------------------------------

loc_31B3A:
		mov	ax, si
		mov	dx, di
		div	[bp+var_E]
		mov	[bp+var_A], ax
		mul	[bp+var_E]
		sub	si, ax
		sbb	di, dx
		mov	ax, [bp+var_10]
		mul	[bp+var_A]
		sub	cx, ax
		sbb	si, dx
		sbb	di, 0
		mov	ax, [bp+var_12]
		mul	[bp+var_A]
		sub	bx, ax
		sbb	cx, dx
		sbb	si, 0
		sbb	di, 0
		mov	ax, [bp+var_14]
		mul	[bp+var_A]
		neg	ax
		sbb	bx, dx
		sbb	cx, 0
		sbb	si, 0
		sbb	di, 0
		xchg	ax, di
		jge	short loc_31B37
		mov	dx, si
		neg	dx
		cmp	dx, [bp+var_E]
		jb	short loc_31B9D
		sub	[bp+var_A], 1
		sbb	[bp+var_8], 0
		add	di, [bp+var_14]
		adc	bx, [bp+var_12]
		adc	cx, [bp+var_10]
		adc	si, [bp+var_E]
		jge	short loc_31C06

loc_31B9D:
		sub	ax, ax
		cwd
		sub	ax, cx
		sbb	dx, si
		div	[bp+var_E]
		mov	[bp+var_C], ax
		mul	[bp+var_E]
		add	cx, ax
		adc	si, dx
		mov	ax, [bp+var_10]
		mul	[bp+var_C]
		add	bx, ax
		adc	cx, dx
		adc	si, 0
		mov	ax, [bp+var_12]
		mul	[bp+var_C]
		add	di, ax
		adc	bx, dx
		adc	cx, 0
		adc	si, 0
		mov	ax, [bp+var_14]
		mul	[bp+var_C]
		sub	ax, ax
		neg	[bp+var_C]
		sbb	[bp+var_A], ax
		sbb	[bp+var_8], al
		add	di, dx
		adc	bx, ax
		adc	cx, ax
		adc	si, ax
		jl	short loc_31C64
		cmp	cx, [bp+var_E]
		jb	short loc_31C03
		add	[bp+var_C], 1
		adc	[bp+var_A], ax
		adc	[bp+var_8], al
		sub	di, [bp+var_12]
		sbb	bx, [bp+var_10]
		sbb	cx, [bp+var_E]
		jl	short loc_31C64

loc_31C03:
		jmp	loc_31CB9
; ---------------------------------------------------------------------------

loc_31C06:
		mov	ax, cx
		mov	dx, si
		div	[bp+var_E]
		mov	[bp+var_C], ax
		mul	[bp+var_E]
		sub	cx, ax
		sbb	si, dx
		mov	ax, [bp+var_10]
		mul	[bp+var_C]
		sub	bx, ax
		sbb	cx, dx
		sbb	si, 0
		mov	ax, [bp+var_12]
		mul	[bp+var_C]
		sub	di, ax
		sbb	bx, dx
		sbb	cx, 0
		sbb	si, 0
		mov	ax, [bp+var_14]
		mul	[bp+var_C]
		sub	ax, ax
		sub	di, dx
		sbb	bx, ax
		sbb	cx, ax
		sbb	si, ax
		jge	short loc_31CB9
		mov	dx, cx
		neg	dx
		cmp	dx, [bp+var_E]
		jb	short loc_31C64
		sub	[bp+var_C], 1
		sbb	[bp+var_A], ax
		sbb	[bp+var_8], al
		add	di, [bp+var_12]
		adc	bx, [bp+var_10]
		adc	cx, [bp+var_E]
		jge	short loc_31CB9

loc_31C64:
		sub	ax, ax
		cwd
		sub	ax, bx
		sbb	dx, cx
		div	[bp+var_E]
		mov	si, ax
		mul	[bp+var_E]
		add	bx, ax
		adc	cx, dx
		mov	ax, [bp+var_10]
		mul	si
		add	di, ax
		adc	bx, dx
		adc	cx, 0
		mov	ax, [bp+var_12]
		mul	si
		sub	ax, ax
		neg	si
		sbb	[bp+var_C], ax
		sbb	[bp+var_A], ax
		sbb	[bp+var_8], al
		add	di, dx
		adc	bx, ax
		adc	cx, ax
		jl	short loc_31D01
		cmp	bx, [bp+var_E]
		jb	short loc_31CB6
		add	si, 1
		adc	[bp+var_C], ax
		adc	[bp+var_A], ax
		adc	[bp+var_8], al
		sub	di, [bp+var_10]
		sbb	bx, [bp+var_E]
		jl	short loc_31D01

loc_31CB6:
		jmp	loc_31D43
; ---------------------------------------------------------------------------

loc_31CB9:
		mov	ax, bx
		mov	dx, cx
		div	[bp+var_E]
		mov	si, ax
		mul	[bp+var_E]
		sub	bx, ax
		sbb	cx, dx
		mov	ax, [bp+var_10]
		mul	si
		sub	di, ax
		sbb	bx, dx
		sbb	cx, 0
		mov	ax, [bp+var_12]
		mul	si
		sub	ax, ax
		sub	di, dx
		sbb	bx, ax
		sbb	cx, ax
		jge	short loc_31D43
		mov	dx, bx
		neg	dx
		cmp	dx, [bp+var_E]
		jb	short loc_31D01
		sub	si, 1
		sbb	[bp+var_C], ax
		sbb	[bp+var_A], ax
		sbb	[bp+var_8], al
		add	di, [bp+var_10]
		adc	bx, [bp+var_E]
		jge	short loc_31D43

loc_31D01:
		mov	ax, [bp+var_10]
		shr	ax, 1
		neg	ax
		mov	cx, [bp+var_E]
		add	ax, cx
		sub	dx, dx
		sub	ax, di
		sbb	dx, bx
		mov	bx, [bp+var_C]
		mov	di, [bp+var_A]
		cmp	dx, cx
		jnb	short loc_31D38
		div	cx
		sub	dx, cx
		neg	dx
		neg	ax

loc_31D25:
		mov	dl, [bp+var_8]
		sbb	si, 0
		jnb	short loc_31D61
		sbb	bx, 0
		sbb	di, 0
		sbb	dl, 0
		jmp	short loc_31D61
; ---------------------------------------------------------------------------

loc_31D38:
		sub	ax, ax
		cwd
		stc
		jmp	short loc_31D25
; ---------------------------------------------------------------------------

loc_31D3E:
		sub	ax, ax
		cwd
		jmp	short loc_31D5E
; ---------------------------------------------------------------------------

loc_31D43:
		mov	ax, [bp+var_10]
		shr	ax, 1
		neg	ax
		cwd
		add	ax, di
		adc	dx, bx
		mov	bx, [bp+var_C]
		mov	di, [bp+var_A]
		mov	cx, [bp+var_E]
		cmp	dx, cx
		jnb	short loc_31D3E
		div	cx

loc_31D5E:
		mov	dl, [bp+var_8]

loc_31D61:
		shr	dl, 1
		jnb	short loc_31D72
		rcr	di, 1
		rcr	bx, 1
		rcr	si, 1
		rcr	ax, 1
		rcr	dh, 1
		inc	[bp+var_6]

loc_31D72:
		shr	cx, 1
		sub	ch, dh
		mov	cx, [bp+var_6]
		adc	ax, 0
		jnb	short loc_31D89
		adc	si, ax
		adc	bx, ax
		adc	di, ax
		jnb	short loc_31D89
		rcr	di, 1
		inc	cx

loc_31D89:
		cmp	cx, 4001h
		jge	short loc_31DAB
		mov	dx, di
		mov	di, [bp+arg_0]
		cld
		stosw
		xchg	ax, si
		stosw
		xchg	ax, bx
		stosw
		xchg	ax, dx
		stosw
		xchg	ax, cx
		stosw
		mov	al, [bp+var_7]
		stosb

loc_31DA2:
		lea	sp, [bp-4]
		pop	di
		pop	si
		pop	bp
		retn	6
; ---------------------------------------------------------------------------

loc_31DAB:
		jmp	loc_31A30
sub_31A5A	endp ; sp-analysis failed

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_31A5A

loc_31DAE:
		mov	cx, dx
		mov	dx, di
		xchg	ax, si
		cmp	dx, cx
		jb	short loc_31DBD
		sub	dx, cx
		mov	[bp+var_8], 1

loc_31DBD:
		div	cx
		xchg	ax, di
		mov	ax, [bx+2]
		div	cx
		mov	bx, [bx]
		xchg	ax, bx
		div	cx
		xchg	ax, si
		sub	ax, ax
		div	cx
		jmp	short loc_31D5E
; END OF FUNCTION CHUNK	FOR sub_31A5A
; ---------------------------------------------------------------------------
		mov	si, word ptr ds:[02Dh]
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [si+8]
		cmp	ax, 0C001h
		jle	short loc_31E0B
		cmp	ax, 4001h
		jge	short loc_31E0F
		cmp	byte ptr [si+0Ah], 0
		jnz	short loc_31E19
		call	sub_3243B
		call	sub_31E2A
		mov	di, word ptr ds:[02Dh]
		push	si
		push	di
		push	si
		call	sub_31A5A
		push	di
		push	si
		push	si
		call	sub_316C3
		dec	word ptr [si+8]
		add	word ptr ds:[02Dh], 0Ch

loc_31E0B:
		pop	di
		pop	si
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_31E0F:
		mov	bx, 0FFFFh
		mov	di, si
		call	sub_315E2
		jmp	short loc_31E0B
; ---------------------------------------------------------------------------

loc_31E19:
		mov	ch, 1
		call	sub_33CD9
		mov	di, si
		call	sub_323F7
		mov	word ptr [di+8], 4001h
		jmp	short loc_31E0B

; =============== S U B	R O U T	I N E =======================================


sub_31E2A	proc near
		push	si
		push	di
		mov	di, word ptr ds:[02Dh]
		mov	bx, [di+8]
		mov	dx, [di+6]
		mov	ax, [di+4]
		mov	cx, [di+2]
		sar	bx, 1
		jnb	short loc_31E47
		inc	bx
		shr	dx, 1
		rcr	ax, 1
		rcr	cx, 1

loc_31E47:
		cmp	dx, 0FFFEh
		jnb	short loc_31E69
		push	bx
		push	cx
		mov	cx, dx
		mov	bx, ax
		mov	si, dx
		stc
		rcr	si, 1

loc_31E57:
		div	si
		dec	si
		cmp	si, ax
		jbe	short loc_31E70
		inc	si
		add	si, ax
		rcr	si, 1
		mov	dx, cx
		mov	ax, bx
		jmp	short loc_31E57
; ---------------------------------------------------------------------------

loc_31E69:
		stc
		rcr	dx, 1
		rcr	ax, 1
		jmp	short loc_31E87
; ---------------------------------------------------------------------------

loc_31E70:
		inc	si
		cmp	si, ax
		jnb	short loc_31E76
		xchg	ax, si

loc_31E76:
		pop	cx
		pop	bx
		xchg	ax, cx
		div	si
		sub	dx, dx
		add	si, cx
		rcr	si, 1
		rcr	ax, 1
		adc	ax, dx
		adc	dx, si

loc_31E87:
		cld
		sub	cx, cx
		xchg	ax, cx
		stosw
		stosw
		xchg	ax, cx
		stosw
		xchg	ax, dx
		stosw
		xchg	ax, bx
		stosw
		mov	al, 0
		stosb
		pop	di
		pop	si
		retn
sub_31E2A	endp

; ---------------------------------------------------------------------------
		db 0
		db    2
		db  40h	; @
		db  42h	; B
		db    1
		db    3
		db  41h	; A
		db  43h	; C

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_31EA1	proc near

var_A		= word ptr -0Ah
var_4		= word ptr -4
var_2		= byte ptr -2

		push	bp
		mov	bp, sp
		push	word ptr [di+0Ah]
		lea	sp, [bp-6]
		push	si
		push	di
		mov	ax, [di]
		mov	bx, [di+2]
		mov	cx, [di+4]
		mov	dx, [di+6]
		mov	[bp+var_4], 0
		mov	di, [di+8]
		sub	di, [si+8]
		jge	short loc_31EDB
		jmp	short loc_31F17
; ---------------------------------------------------------------------------

loc_31EC6:
		inc	di
		jmp	short loc_31F06
; ---------------------------------------------------------------------------

loc_31EC9:
		dec	di
		jl	short loc_31EC6
		shl	[bp+var_4], 1
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx
		jb	short loc_31EF4
		jns	short loc_31EC9

loc_31EDB:
		cmp	dx, [si+6]
		ja	short loc_31EF4
		jb	short loc_31EC9
		cmp	cx, [si+4]
		ja	short loc_31EF4
		jb	short loc_31EC9
		cmp	bx, [si+2]
		ja	short loc_31EF4
		jb	short loc_31EC9
		cmp	ax, [si]
		jb	short loc_31EC9

loc_31EF4:
		inc	[bp+var_4]
		sub	ax, [si]
		sbb	bx, [si+2]
		sbb	cx, [si+4]
		sbb	dx, [si+6]
		or	di, di
		jg	short loc_31EC9

loc_31F06:
		or	dx, dx
		js	short loc_31F17
		jz	short loc_31F4F

loc_31F0C:
		dec	di
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx
		jns	short loc_31F0C

loc_31F17:
		add	di, [si+8]

loc_31F1A:
		push	di
		mov	di, [bp+var_A]
		stosw
		xchg	ax, bx
		stosw
		xchg	ax, cx
		stosw
		xchg	ax, dx
		stosw
		pop	ax
		stosw
		mov	al, [bp+var_2]
		stosb
		and	byte ptr ds:[021h], 0B8h
		mov	di, 7
		mov	ax, [bp+var_4]
		cmp	[bp+var_2], 1
		jnz	short loc_31F3E
		neg	ax

loc_31F3E:
		and	di, ax
		mov	dl, cs:[di+8C9h]
		or	byte ptr ds:[021h], dl
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_31F4F:
		xchg	dx, cx
		xchg	cx, bx
		xchg	ax, bx
		sub	di, 10h
		or	dx, dx
		jnz	short loc_31F06
		xchg	dx, cx
		xchg	cx, bx
		sub	di, 10h
		or	dx, dx
		jnz	short loc_31F06
		xchg	dx, cx
		sub	di, 10h
		or	dx, dx
		jnz	short loc_31F06
		mov	di, 0C001h
		sub	dx, dx
		sub	cx, cx
		sub	bx, bx
		sub	ax, ax
		jmp	short loc_31F1A
sub_31EA1	endp

; ---------------------------------------------------------------------------
; START	OF FUNCTION CHUNK FOR sub_31FA9

loc_31F7C:
		mov	dx, [si+6]
		and	dh, 7Fh
		or	dx, [si]
		or	dx, [si+2]
		or	dx, [si+4]
		jz	short loc_31FBF

loc_31F8C:
		mov	ch, 1
		call	sub_33CD9
		mov	ax, 4500h
		jmp	loc_32027
; ---------------------------------------------------------------------------

loc_31F97:
		mov	dx, [di+6]
		and	dh, 7Fh
		or	dx, [di]
		or	dx, [di+2]
		or	dx, [di+4]
		jnz	short loc_31F8C
		jmp	short loc_31FC5
; END OF FUNCTION CHUNK	FOR sub_31FA9

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_31FA9	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6

; FUNCTION CHUNK AT 09AC SIZE 0000002D BYTES

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, [bp+arg_2]
		mov	di, [bp+arg_0]
		mov	ax, [si+8]
		mov	bx, [di+8]
		cmp	ax, 4001h
		jge	short loc_31F7C

loc_31FBF:
		cmp	bx, 4001h
		jge	short loc_31F97

loc_31FC5:
		mov	dx, ax
		cmp	ax, bx
		jg	short loc_31FCD
		mov	dx, bx

loc_31FCD:
		cmp	dx, 0C001h
		jle	short loc_3200E
		mov	cl, [si+0Ah]
		cmp	cl, [di+0Ah]
		jl	short loc_32024
		jg	short loc_3201A
		cmp	ax, bx
		jl	short loc_32015
		jg	short loc_3201F
		mov	ax, [si+6]
		cmp	ax, [di+6]
		jnz	short loc_32013
		mov	ch, 3
		and	ch, byte ptr ds:[023h]
		jz	short loc_32031
		mov	ax, [si+4]
		cmp	ax, [di+4]
		jnz	short loc_32013
		mov	ax, [si+2]
		cmp	ax, [di+2]
		jnz	short loc_32013
		cmp	ch, 2
		jz	short loc_32053
		mov	ax, [si]
		cmp	ax, [di]
		jnz	short loc_32013

loc_3200E:
		mov	ax, 4000h
		jmp	short loc_32027
; ---------------------------------------------------------------------------

loc_32013:
		ja	short loc_3201F

loc_32015:
		cmp	cl, 0
		jnz	short loc_32024

loc_3201A:
		mov	ax, 100h
		jmp	short loc_32027
; ---------------------------------------------------------------------------

loc_3201F:
		cmp	cl, 0
		jnz	short loc_3201A

loc_32024:
		mov	ax, 0

loc_32027:
		mov	byte ptr ds:[021h], ah
		pop	di
		pop	si
		pop	bp
		retn	4
; ---------------------------------------------------------------------------

loc_32031:
		mov	bx, [si]
		sub	bx, [di]
		mov	bx, [si+2]
		sbb	bx, [di+2]
		mov	bx, [si+4]
		sbb	bx, [di+4]
		ja	short loc_3204C
		neg	bx
		and	bx, 0FF80h
		jz	short loc_3200E
		jmp	short loc_32015
; ---------------------------------------------------------------------------

loc_3204C:
		and	bx, 0FF80h
		jz	short loc_3200E
		jmp	short loc_3201F
; ---------------------------------------------------------------------------

loc_32053:
		mov	bx, [si]
		sub	bx, [di]
		ja	short loc_32062
		neg	bx
		and	bh, 0FCh
		jz	short loc_3200E
		jmp	short loc_32015
; ---------------------------------------------------------------------------

loc_32062:
		and	bh, 0FCh
		jz	short loc_3200E
		jmp	short loc_3201F
sub_31FA9	endp


; =============== S U B	R O U T	I N E =======================================


sub_32069	proc near
		mov	ax, 4000h
		cmp	word ptr [si+8], 0C001h
		jle	short loc_32086
		cmp	word ptr [si+8], 4001h
		jge	short loc_3208B

loc_3207A:
		mov	ax, 100h
		cmp	byte ptr [si+0Ah], 1
		jz	short loc_32086
		mov	ax, 0

loc_32086:
		mov	byte ptr ds:[021h], ah
		retn
; ---------------------------------------------------------------------------

loc_3208B:
		mov	dx, [si+6]
		and	dh, 7Fh
		or	dx, [si]
		or	dx, [si+2]
		or	dx, [si+4]
		jz	short loc_3207A
		mov	ch, 1
		call	sub_33CD9
		mov	ax, 4500h
		jmp	short loc_32086
sub_32069	endp


; =============== S U B	R O U T	I N E =======================================


sub_320A5	proc near
		mov	ax, 4000h
		cmp	word ptr [si+8], 0C001h
		jle	short loc_320C2
		cmp	word ptr [si+8], 4001h
		jge	short loc_320C7
		mov	ax, 400h

loc_320B9:
		cmp	byte ptr [si+0Ah], 1
		jnz	short loc_320C2
		or	ax, 200h

loc_320C2:
		mov	byte ptr ds:[021h], ah
		retn
; ---------------------------------------------------------------------------

loc_320C7:
		mov	ax, 500h
		mov	dx, [si+6]
		and	dh, 7Fh
		or	dx, [si]
		or	dx, [si+2]
		or	dx, [si+4]
		jz	short loc_320B9
		mov	ax, 100h
		jmp	short loc_320B9
sub_320A5	endp


; =============== S U B	R O U T	I N E =======================================


sub_320DF	proc near
		mov	ax, [si+4]
		mov	dx, [si+6]
		mov	bx, [si+8]
		mov	cl, [si+0Ah]
		cmp	word ptr [si], 0
		jnz	short loc_320FF
		cmp	word ptr [si+2], 0
		jnz	short loc_320FF
		test	al, 7Fh
		jnz	short loc_320FF
		test	ah, 1
		jz	short loc_3210E

loc_320FF:
		add	al, al
		adc	ah, 0
		adc	dx, 0
		jnb	short loc_3210E
		rcr	dx, 1
		rcr	ax, 1
		inc	bx

loc_3210E:
		add	bx, 7Eh	; '~'
		jle	short loc_32145
		cmp	bx, 0FFh
		jge	short loc_32130

loc_32119:
		shl	dx, 1
		shr	cl, 1
		rcr	bl, 1
		rcr	dx, 1
		mov	al, ah
		mov	ah, dl
		mov	dl, dh
		mov	dh, bl
		stosw
		xchg	ax, dx
		stosw
		sub	di, 4
		retn
; ---------------------------------------------------------------------------

loc_32130:
		cmp	word ptr [si+8], 4001h
		jge	short loc_32140
		mov	ch, 8
		call	sub_33CD9
		sub	dx, dx
		sub	ax, ax

loc_32140:
		mov	bx, 0FFh
		jmp	short loc_32119
; ---------------------------------------------------------------------------

loc_32145:
		cmp	word ptr [si+8], 0C001h
		jle	short loc_32151
		mov	ch, 10h
		call	sub_33CD9

loc_32151:
		sub	bx, bx
		mov	dx, bx
		mov	ax, bx
		jmp	short loc_32119
sub_320DF	endp


; =============== S U B	R O U T	I N E =======================================


sub_32159	proc near
		mov	ax, es:[si]
		mov	dx, es:[si+2]
		push	si
		sub	si, si
		shl	dx, 1
		rcl	si, 1
		sub	bx, bx
		add	bl, dh
		jz	short loc_3219B
		cmp	dh, 0FFh
		jz	short loc_32196
		sub	bx, 7Eh	; '~'

loc_32175:
		stc
		rcr	dl, 1

loc_32178:
		mov	dh, dl
		mov	dl, ah
		mov	ch, al
		mov	cl, 0
		sub	ax, ax
		mov	[di], ax
		mov	[di+2],	ax
		mov	[di+4],	cx
		mov	[di+6],	dx
		mov	[di+8],	bx
		xchg	ax, si
		mov	[di+0Ah], al
		pop	si
		retn
; ---------------------------------------------------------------------------

loc_32196:
		mov	bx, 4001h
		jmp	short loc_32175
; ---------------------------------------------------------------------------

loc_3219B:
		mov	cx, dx
		or	cx, ax
		jz	short loc_321AF
		sub	bx, 7Eh	; '~'
		shr	dl, 1

loc_321A6:
		add	ax, ax
		adc	dl, dl
		js	short loc_32178
		dec	bx
		jmp	short loc_321A6
; ---------------------------------------------------------------------------

loc_321AF:
		mov	bx, 0C001h
		jmp	short loc_32178
sub_32159	endp

; ---------------------------------------------------------------------------
		mov	es, cx
		assume es:seg000

; =============== S U B	R O U T	I N E =======================================


sub_321B6	proc near
		push	di
		mov	ax, [si+1]
		mov	di, [si+3]
		mov	cx, [si+5]
		mov	dl, [si+7]
		mov	bx, [si+8]
		mov	dh, 3
		and	dh, al
		or	dh, [si]
		jnz	short loc_321D2
		test	al, 8
		jz	short loc_321E3

loc_321D2:
		add	ax, 4
		adc	di, 0
		adc	cx, 0
		adc	dl, 0
		jnb	short loc_321E3
		rcr	dl, 1
		inc	bx

loc_321E3:
		add	bx, 3FEh
		jle	short loc_3222B
		cmp	bx, 7FFh
		jge	short loc_32238

loc_321EF:
		and	al, 0F8h
		shl	dl, 1
		shr	bx, 1
		rcr	dl, 1
		or	al, bh
		mov	dh, bl
		mov	bx, di
		shr	di, 1
		rcr	ax, 1
		rcr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		shr	di, 1
		rcr	ax, 1
		rcr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		or	al, [si+0Ah]
		shr	di, 1
		rcr	ax, 1
		rcr	dx, 1
		rcr	cx, 1
		rcr	bx, 1

loc_3221E:
		pop	di
		cld
		stosw
		xchg	ax, bx
		stosw
		xchg	ax, cx
		stosw
		xchg	ax, dx
		stosw
		sub	di, 8
		retn
; ---------------------------------------------------------------------------

loc_3222B:
		sub	dx, dx
		cmp	word ptr [si+8], 0C001h
		jle	short loc_32247
		mov	ch, 10h
		jmp	short loc_32244
; ---------------------------------------------------------------------------

loc_32238:
		cmp	word ptr [si+8], 4001h
		jge	short loc_32254
		mov	dx, 0FFE0h
		mov	ch, 8

loc_32244:
		call	sub_33CD9

loc_32247:
		or	dl, [si+0Ah]
		ror	dx, 1
		sub	cx, cx
		mov	bx, cx
		mov	ax, cx
		jmp	short loc_3221E
; ---------------------------------------------------------------------------

loc_32254:
		mov	bx, 7FFh
		jmp	short loc_321EF
sub_321B6	endp

; ---------------------------------------------------------------------------
		mov	si, bx
		mov	es, ax
		assume es:nothing

; =============== S U B	R O U T	I N E =======================================


sub_3225D	proc near
		mov	dx, es:[si+6]
		mov	cx, 5
		shl	dx, 1
		rcl	ch, 1
		mov	[di+0Ah], ch
		shr	dx, cl
		jz	short loc_322D2
		cmp	dx, 7FFh
		jz	short loc_322B8
		mov	bl, 10h
		sub	dx, 3FEh

loc_3227B:
		mov	[di+8],	dx
		mov	dx, es:[si+5]
		and	dh, 0Fh
		or	dh, bl
		mov	cx, es:[si+3]
		mov	bx, es:[si+1]
		mov	ah, es:[si]
		mov	al, 0
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		rcl	dx, 1
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		rcl	dx, 1
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		rcl	dx, 1

loc_322AC:
		mov	[di], ax
		mov	[di+2],	bx
		mov	[di+4],	cx
		mov	[di+6],	dx
		retn
; ---------------------------------------------------------------------------

loc_322B8:
		mov	bx, 0Fh
		and	bl, es:[si+6]
		or	bx, es:[si+4]
		or	bx, es:[si+2]
		or	bx, es:[si]
		mov	dx, 4001h
		or	bl, 10h
		jmp	short loc_3227B
; ---------------------------------------------------------------------------

loc_322D2:
		mov	bx, 0Fh
		and	bl, es:[si+6]
		or	bx, es:[si+4]
		or	bx, es:[si+2]
		or	bx, es:[si]
		jnz	short loc_322EB
		mov	dx, 0C001h
		jmp	short loc_3227B
; ---------------------------------------------------------------------------

loc_322EB:
		mov	dx, es:[si+5]
		and	dh, 0Fh
		mov	cx, es:[si+3]
		mov	bx, es:[si+1]
		mov	ah, es:[si]
		mov	al, 4

loc_322FF:
		dec	al
		shl	ah, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx
		jns	short loc_322FF
		push	ax
		mov	ah, 0
		sub	ax, 4FEh
		mov	[di+8],	ax
		pop	ax
		mov	al, 0
		jmp	short loc_322AC
sub_3225D	endp

; ---------------------------------------------------------------------------
		mov	es, cx

; =============== S U B	R O U T	I N E =======================================


sub_3231B	proc near
		cld
		movsw
		movsw
		movsw
		movsw
		lodsw
		mov	cl, [si]
		cmp	ax, 4001h
		jge	short loc_3233B
		add	ax, 3FFEh
		jl	short loc_32340

loc_3232D:
		shl	ax, 1
		shr	cl, 1
		rcr	ax, 1
		stosw
		sub	di, 0Ah
		sub	si, 0Ah
		retn
; ---------------------------------------------------------------------------

loc_3233B:
		mov	ax, 7FFFh
		jmp	short loc_3232D
; ---------------------------------------------------------------------------

loc_32340:
		sub	ax, ax
		jmp	short loc_3232D
sub_3231B	endp

; ---------------------------------------------------------------------------
		mov	si, bx
		mov	es, ax
		assume es:seg000

; =============== S U B	R O U T	I N E =======================================


sub_32348	proc near
		push	si
		mov	cx, ds
		mov	dx, es
		mov	es, cx
		assume es:dseg
		mov	ds, dx
		assume ds:seg000
		std
		lea	si, [si+8]
		lea	di, [di+0Ah]
		lodsw
		xchg	ax, bx
		sub	ax, ax
		shl	bx, 1
		rcl	ax, 1
		stosb
		dec	di
		shr	bx, 1
		jz	short loc_32379
		sub	bx, 3FFEh
		xchg	ax, bx
		stosw
		movsw
		movsw
		movsw
		movsw

loc_32370:
		cld
		mov	es, dx
		assume es:seg000
		mov	ds, cx
		assume ds:dseg
		inc	di
		inc	di
		pop	si
		retn
; ---------------------------------------------------------------------------

loc_32379:
		mov	ax, 0C001h
		stosw
		sub	ax, ax
		stosw
		stosw
		stosw
		stosw
		jmp	short loc_32370
sub_32348	endp

; ---------------------------------------------------------------------------
		db 7 dup(0), 80h, 1, 3 dup(0)

; =============== S U B	R O U T	I N E =======================================


sub_32391	proc near
		mov	ax, 0DB5h
		jmp	short loc_323FA
sub_32391	endp

; ---------------------------------------------------------------------------
byte_32396	db 0FEh, 8Ah, 1Bh, 0CDh, 4Bh, 78h, 9Ah,	0D4h, 2, 3 dup(0)
		db 0B8h, 0C6h, 0Dh, 0EBh, 53h, 0BBh, 0F0h, 17h,	5Ch, 29h
		db 3Bh,	0AAh, 0B8h, 1, 3 dup(0), 0B8h, 0D7h, 0Dh, 0EBh
		db 42h,	35h, 0C2h, 68h,	21h, 0A2h, 0DAh, 0Fh, 0C9h, 2
		db 3 dup(0)

; =============== S U B	R O U T	I N E =======================================


sub_323C4	proc near
		mov	ax, 0DE8h
		jmp	short loc_323FA
sub_323C4	endp

; ---------------------------------------------------------------------------
		db  99h	; �
		db 0F7h	; �
		db 0CFh	; ?
		db 0FBh	; �
		db  84h	; �
		db  9Ah	; �
		db  20h
		db  9Ah	; �
		db 0FFh
		db 0FFh
		db    0
		db    0
unk_323D5	db 0B8h	; ?
		db 0F9h	; �
		db  0Dh
		db 0EBh	; �
		db  20h
		db 0ACh	; ?
		db  79h	; y
		db 0CFh	; ?
		db 0D1h	; ?
		db 0F7h	; �
		db  17h
		db  72h	; r
		db 0B1h	; ?
		db    0
		db    0
		db    0
		db    0

; =============== S U B	R O U T	I N E =======================================


sub_323E6	proc near
		mov	ax, 0E0Ah
		jmp	short loc_323FA
sub_323E6	endp

; ---------------------------------------------------------------------------
		db 8 dup(0), 1,	0C0h, 2	dup(0)

; =============== S U B	R O U T	I N E =======================================


sub_323F7	proc near
		mov	ax, 0E1Bh

loc_323FA:
		push	ds
		mov	cx, cs
		mov	ds, cx
		assume ds:seg040
		xchg	ax, si
		cld
		mov	cx, 5
		rep movsw
		movsb
		sub	di, 0Bh
		xchg	ax, si
		pop	ds
		assume ds:dseg
		retn
sub_323F7	endp


; =============== S U B	R O U T	I N E =======================================


sub_3240D	proc near
		cld
		push	di
		push	ax
		cmp	ax, 0C001h
		mov	ax, 0
		stosw
		stosw
		stosw
		rcr	ax, 1
		stosw
		pop	ax
		stosw
		mov	al, cl
		stosb
		pop	di
		retn
sub_3240D	endp


; =============== S U B	R O U T	I N E =======================================


sub_32423	proc near
		mov	ch, 1
		call	sub_33CD9
		push	di
		sub	ax, ax
		cld
		stosw
		stosw
		stosw
		mov	ah, 0C0h ; '?'
		stosw
		mov	ax, 4001h
		stosw
		mov	al, 1
		stosb
		pop	di
		retn
sub_32423	endp


; =============== S U B	R O U T	I N E =======================================


sub_3243B	proc near
		push	di
		push	es
		mov	di, ss
		mov	es, di
		assume es:nothing
		sub	word ptr ds:[02Dh], 0Ch
		mov	di, word ptr ds:[02Dh]
		cld
		mov	cx, 5
		rep movsw
		movsb
		pop	es
		pop	di
		sub	si, 0Bh
		retn
sub_3243B	endp


; =============== S U B	R O U T	I N E =======================================


sub_32457	proc near
		push	si
		push	di
		sub	word ptr ds:[02Dh], 0Ch
		mov	di, word ptr ds:[02Dh]
		push	ds
		push	es
		push	ds
		pop	es
		assume es:dseg
		push	cs
		pop	ds
		assume ds:seg040
		cld
		mov	cx, 5
		rep movsw
		movsb
		pop	es
		assume es:nothing
		pop	ds
		assume ds:dseg
		pop	di
		pop	si
		retn
sub_32457	endp


; =============== S U B	R O U T	I N E =======================================


sub_32474	proc near
		push	si
		mov	si, word ptr ds:[02Dh]
		cld
		mov	cx, 5
		rep movsw
		movsb
		inc	si
		mov	word ptr ds:[02Dh], si
		sub	di, 0Bh
		pop	si
		retn
sub_32474	endp


; =============== S U B	R O U T	I N E =======================================


sub_3248A	proc near
		push	si
		push	di
		push	es
		mov	si, word ptr ds:[02Dh]
		lea	di, [si-0Ch]
		mov	word ptr ds:[02Dh], di
		cld
		mov	cx, ss
		mov	es, cx
		mov	cx, 5
		rep movsw
		movsb
		pop	es
		pop	di
		pop	si
		retn
sub_3248A	endp


; =============== S U B	R O U T	I N E =======================================


sub_324A7	proc near
		push	si
		push	di
		mov	si, word ptr ds:[02Dh]
		mov	di, si
		cld
		push	es
		mov	cx, ss
		mov	es, cx
		mov	cx, 5

loc_324B8:
		lodsw
		xchg	ax, [di+0Ch]
		stosw
		loop	loc_324B8
		lodsb
		xchg	al, [di+0Ch]
		stosb
		pop	es
		pop	di
		pop	si
		retn
sub_324A7	endp


; =============== S U B	R O U T	I N E =======================================


sub_324C8	proc near
		mov	ax, es:[si]
		sub	cx, cx
		cwd
		xor	ax, dx
		sub	ax, dx
		jz	short loc_32506
		and	dl, 1

loc_324D7:
		mov	bx, cx
		xchg	ax, cx
		shl	ax, 1

loc_324DC:
		rcr	ax, 1
		inc	bx
		shr	cx, 1
		rcr	ax, 1
		jcxz	short loc_324EC
		inc	bx
		shr	cx, 1
		jnz	short loc_324DC
		rcr	ax, 1

loc_324EC:
		mov	[di+0Ah], dl
		mov	[di+8],	bx
		mov	[di+6],	ax
		mov	[di+4],	cx
		mov	[di+2],	cx
		mov	[di], cx
		retn
; ---------------------------------------------------------------------------
		sub	cx, cx
		mov	dx, cx
		or	ax, ax
		jnz	short loc_324D7

loc_32506:
		mov	bx, 0C001h
		jmp	short loc_324EC
sub_324C8	endp


; =============== S U B	R O U T	I N E =======================================


sub_3250B	proc near
		mov	cx, [si+8]
		cmp	cx, 10h

loc_32511:
		jg	short loc_32583
		cmp	cx, 0C001h
		jle	short loc_3258D
		mov	bx, [si+6]
		sub	ax, ax
		or	cx, cx
		jge	short loc_32526
		shr	bx, 1
		rcr	dx, 1

loc_32526:
		mov	dx, [si+4]
		or	cx, cx
		jle	short loc_32535

loc_3252D:
		shl	dx, 1
		rcl	bx, 1
		rcl	ax, 1
		loop	loc_3252D

loc_32535:
		or	dx, [si]
		or	dx, [si+2]
		or	bl, dh
		or	bl, dl
		mov	cl, 0Ch
		and	cl, byte ptr ds:[023h]
		cmp	cl, 0Ch
		jz	short loc_32573
		cmp	cl, 0
		jz	short loc_32564
		add	cl, [si+0Ah]
		cmp	cl, 4
		jz	short loc_32573
		cmp	cl, 9
		jz	short loc_32573
		neg	bx
		adc	ax, 0
		jb	short loc_32583
		jmp	short loc_32573
; ---------------------------------------------------------------------------

loc_32564:
		mov	dl, 1
		and	dl, al
		or	bl, dl
		add	bx, 7FFFh
		adc	ax, 0
		jb	short loc_32583

loc_32573:
		cmp	byte ptr [si+0Ah], 1
		jz	short loc_32591
		sahf
		jns	short loc_32597
		cmp	byte ptr ds:[05Ch], 1
		jz	short loc_32597

loc_32583:
		mov	ch, 8
		call	sub_33CD9
		mov	ax, 8000h
		jmp	short loc_32597
; ---------------------------------------------------------------------------

loc_3258D:
		sub	ax, ax
		jmp	short loc_32597
; ---------------------------------------------------------------------------

loc_32591:
		neg	ax
		jz	short loc_32597
		jns	short loc_32583

loc_32597:
		mov	byte ptr ds:[05Ch], 0
		mov	es:[di], ax
		retn
sub_3250B	endp


; =============== S U B	R O U T	I N E =======================================


sub_325A0	proc near
		mov	byte ptr ds:[05Ch], 1
		mov	cx, [si+8]
		cmp	cx, 10h
		jmp	loc_32511
sub_325A0	endp


; =============== S U B	R O U T	I N E =======================================


sub_325AE	proc near
		push	si
		push	di
		cld
		mov	cx, 5
		rep movsw
		movsb
		pop	di
		pop	si
		xchg	si, di
		lea	si, [si+8]
		cmp	word ptr [si], 0C001h
		jle	short locret_325D3
		cmp	word ptr [si], 4001h
		jge	short loc_325D4
		dec	word ptr [si]
		call	sub_324C8
		mov	word ptr [si], 1

locret_325D3:
		retn
; ---------------------------------------------------------------------------

loc_325D4:
		mov	word ptr [si], 0C001h
		mov	word ptr [di+8], 0Dh
		mov	byte ptr [di+7], 80h ; '?'
		jmp	short locret_325D3
sub_325AE	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_325E3	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, [si+8]
		cmp	cx, 0Fh
		jg	short loc_325F8
		or	cx, cx
		jg	short loc_32602
		sub	ax, ax
		jmp	short loc_32614
; ---------------------------------------------------------------------------

loc_325F8:
		mov	ch, 8
		call	sub_33CD9
		mov	ax, 7FFFh
		jmp	short loc_3260C
; ---------------------------------------------------------------------------

loc_32602:
		mov	ax, [si+6]
		neg	cl
		add	cl, 10h
		shr	ax, cl

loc_3260C:
		cmp	byte ptr [si+0Ah], 1
		jnz	short loc_32614
		neg	ax

loc_32614:
		mov	cx, [di+8]
		cmp	cx, 0C001h
		jle	short loc_32632
		cmp	cx, 4001h
		jge	short loc_32632
		add	ax, cx
		cmp	ax, 0C001h
		jle	short loc_32640
		cmp	ax, 4001h
		jge	short loc_32636
		mov	[di+8],	ax

loc_32632:
		pop	di
		pop	si
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_32636:
		mov	ch, 8
		call	sub_33CD9
		mov	ax, 4001h
		jmp	short loc_32648
; ---------------------------------------------------------------------------

loc_32640:
		mov	ch, 10h
		call	sub_33CD9
		mov	ax, 0C001h

loc_32648:
		call	sub_3240D
		jmp	short loc_32632
sub_325E3	endp


; =============== S U B	R O U T	I N E =======================================


sub_3264D	proc near
		mov	cx, dx
		xchg	ax, bx
		jmp	short loc_32661
sub_3264D	endp


; =============== S U B	R O U T	I N E =======================================


sub_32652	proc near
		mov	cx, dx
		xchg	ax, bx
		mov	dx, 0
		jmp	short loc_32673
sub_32652	endp


; =============== S U B	R O U T	I N E =======================================


sub_3265A	proc near
		mov	bx, es:[si]
		mov	cx, es:[si+2]

loc_32661:
		sub	ax, ax
		mov	dx, 0
		or	cx, cx
		jns	short loc_32673
		not	cx
		neg	bx
		sbb	cx, 0FFFFh
		mov	dl, 1

loc_32673:
		mov	[di+0Ah], dl
		mov	dl, 10h
		or	cx, cx
		jnz	short loc_32688
		xchg	bx, cx
		mov	dl, 0
		jcxz	short loc_326A0
		jmp	short loc_32688
; ---------------------------------------------------------------------------

loc_32684:
		rcr	bx, 1
		rcr	ax, 1

loc_32688:
		inc	dx
		shr	cx, 1
		jnz	short loc_32684
		rcr	bx, 1
		rcr	ax, 1

loc_32691:
		mov	[di+8],	dx
		mov	[di+6],	bx
		mov	[di+4],	ax
		mov	[di+2],	cx
		mov	[di], cx
		retn
; ---------------------------------------------------------------------------

loc_326A0:
		mov	dx, 0C001h
		jmp	short loc_32691
sub_3265A	endp


; =============== S U B	R O U T	I N E =======================================


sub_326A5	proc near
		mov	byte ptr ds:[05Ch], 1
		mov	cx, [si+8]
		cmp	cx, 20h	; ' '
		jmp	short loc_326B8
sub_326A5	endp


; =============== S U B	R O U T	I N E =======================================


sub_326B2	proc near
		mov	cx, [si+8]
		cmp	cx, 20h	; ' '

loc_326B8:
		jg	short loc_326ED
		or	cx, cx
		jge	short loc_326FA
		cmp	cx, 0C001h
		jle	short loc_326D7
		mov	bl, 0Ch
		and	bl, byte ptr ds:[023h]
		add	bl, [si+0Ah]
		cmp	bl, 5
		jz	short loc_326DD
		cmp	bl, 8
		jz	short loc_326DD

loc_326D7:
		sub	dx, dx
		mov	ax, dx
		jmp	short loc_326F7
; ---------------------------------------------------------------------------

loc_326DD:
		sub	dx, dx
		mov	ax, 1
		cmp	bl, 5
		jnz	short loc_326F7
		neg	ax
		not	dx
		jmp	short loc_326F7
; ---------------------------------------------------------------------------

loc_326ED:
		mov	ch, 8
		call	sub_33CD9
		mov	dx, 8000h
		sub	ax, ax

loc_326F7:
		jmp	loc_32791
; ---------------------------------------------------------------------------

loc_326FA:
		mov	bx, [si+2]
		or	bl, [si]
		or	bl, [si+1]
		mov	ax, [si+4]
		mov	dx, [si+6]
		sub	cl, 10h
		ja	short loc_3271D

loc_3270D:
		or	al, bl
		or	al, bh
		xchg	ax, bx
		xchg	ax, dx
		sub	dx, dx
		add	cl, 10h
		jle	short loc_3270D
		and	cl, 0Fh

loc_3271D:
		jcxz	short loc_3273C
		push	si
		mov	si, 0FFFFh
		rol	dx, cl
		rol	ax, cl
		shl	si, cl
		mov	cx, si
		and	cx, ax
		xor	ax, cx
		and	si, dx
		xor	dx, si
		or	ax, si
		or	bl, bh
		or	bl, cl
		mov	bh, ch
		pop	si

loc_3273C:
		mov	cl, 0Ch
		and	cl, byte ptr ds:[023h]
		cmp	cl, 0Ch
		jz	short loc_32784
		cmp	cl, 0
		jz	short loc_3275F
		add	cl, [si+0Ah]
		cmp	cl, 4
		jz	short loc_32784
		cmp	cl, 9
		jz	short loc_32784
		neg	bx
		jb	short loc_32769
		jmp	short loc_32784
; ---------------------------------------------------------------------------

loc_3275F:
		mov	cl, 1
		and	cl, al
		or	bl, cl
		add	bx, 7FFFh

loc_32769:
		adc	ax, 0
		adc	dx, 0
		jns	short loc_32784
		cmp	byte ptr [si+0Ah], 1
		jnz	short loc_32781
		cmp	dx, 8000h
		jnz	short loc_32781
		or	ax, ax
		jz	short loc_32784

loc_32781:
		jmp	loc_326ED
; ---------------------------------------------------------------------------

loc_32784:
		cmp	byte ptr [si+0Ah], 1
		jnz	short loc_32791
		not	dx
		neg	ax
		sbb	dx, 0FFFFh

loc_32791:
		mov	byte ptr ds:[05Ch], 0
		mov	es:[di], ax
		mov	es:[di+2], dx
		retn
sub_326B2	endp


; =============== S U B	R O U T	I N E =======================================


sub_3279E	proc near
		push	bp
		push	si
		mov	ax, es:[si]
		mov	bx, es:[si+2]
		mov	cx, es:[si+4]
		mov	dx, es:[si+6]
		mov	bp, 0
		or	dx, dx
		jl	short loc_327C9
		jg	short loc_327DE
		or	cx, cx
		jnz	short loc_327DE
		or	bx, bx
		jnz	short loc_327DE
		or	ax, ax
		jnz	short loc_327DE
		mov	si, 0C001h
		jmp	short loc_327FC
; ---------------------------------------------------------------------------

loc_327C9:
		not	dx
		not	cx
		not	bx
		neg	ax
		cmc
		adc	bx, 0
		adc	cx, 0
		adc	dx, 0
		mov	bp, 1

loc_327DE:
		mov	si, 40h	; '@'

loc_327E1:
		or	dx, dx
		jnz	short loc_327EF
		xchg	dx, cx
		xchg	cx, bx
		xchg	ax, bx
		sub	si, 10h
		jmp	short loc_327E1
; ---------------------------------------------------------------------------

loc_327EF:
		js	short loc_327FC

loc_327F1:
		dec	si
		add	ax, ax
		adc	bx, bx
		adc	cx, cx
		adc	dx, dx
		jns	short loc_327F1

loc_327FC:
		mov	[di+8],	si
		mov	[di+6],	dx
		mov	[di+4],	cx
		mov	[di+2],	bx
		mov	[di], ax
		xchg	ax, bp
		mov	[di+0Ah], al
		pop	si
		pop	bp
		retn
sub_3279E	endp


; =============== S U B	R O U T	I N E =======================================


sub_32811	proc near
		push	bp
		push	di
		mov	cx, [si+8]
		cmp	cx, 3Fh	; '?'
		jg	short loc_32854
		or	cx, cx
		jge	short loc_32865
		cmp	cx, 0C001h
		jle	short loc_32838
		mov	bl, 0Ch
		and	bl, byte ptr ds:[023h]
		add	bl, [si+0Ah]
		cmp	bl, 5
		jz	short loc_3283C
		cmp	bl, 8
		jz	short loc_3283C

loc_32838:
		sub	bp, bp
		jmp	short loc_3285C
; ---------------------------------------------------------------------------

loc_3283C:
		sub	bp, bp
		mov	dx, bp
		mov	ax, 1
		cmp	bl, 5
		mov	bx, bp
		jnz	short loc_32862
		neg	ax
		not	bx
		not	dx
		not	bp
		jmp	short loc_32862
; ---------------------------------------------------------------------------

loc_32854:
		mov	ch, 8
		call	sub_33CD9
		mov	bp, 8000h

loc_3285C:
		sub	dx, dx
		mov	bx, dx
		mov	ax, bx

loc_32862:
		jmp	loc_328F6
; ---------------------------------------------------------------------------

loc_32865:
		mov	bp, [si+6]
		mov	dx, [si+4]
		mov	bx, [si+2]
		mov	di, [si]
		sub	ax, ax
		sub	cl, 30h	; '0'
		ja	short loc_3288D

loc_32877:
		or	al, ah
		mov	ah, 0
		or	ax, di
		mov	di, bx
		mov	bx, dx
		mov	dx, bp
		sub	bp, bp
		add	cl, 10h
		jle	short loc_32877
		and	cl, 0Fh

loc_3288D:
		neg	cl
		jz	short loc_328A2
		add	cl, 10h

loc_32894:
		or	al, ah
		shr	bp, 1
		rcr	dx, 1
		rcr	bx, 1
		rcr	di, 1
		rcr	ah, 1
		loop	loc_32894

loc_328A2:
		mov	cl, 0Ch
		and	cl, byte ptr ds:[023h]
		cmp	cl, 0Ch
		jz	short loc_328DD
		cmp	cl, 0
		jz	short loc_328C7
		add	cl, [si+0Ah]
		cmp	cl, 4
		jz	short loc_328DD
		cmp	cl, 9
		jz	short loc_328DD
		neg	ax
		jb	short loc_328D0
		jmp	short loc_328DD
; ---------------------------------------------------------------------------

loc_328C5:
		jmp	short loc_32854
; ---------------------------------------------------------------------------

loc_328C7:
		mov	cl, 1
		and	cx, di
		or	al, cl
		add	ax, 7FFFh

loc_328D0:
		mov	cx, 0
		adc	di, cx
		adc	bx, cx
		adc	dx, cx
		adc	bp, cx
		js	short loc_328C5

loc_328DD:
		xchg	ax, di
		cmp	byte ptr [si+0Ah], 1
		jnz	short loc_328F6
		not	bp
		not	dx
		not	bx
		neg	ax
		cmc
		adc	bx, 0
		adc	dx, 0
		adc	bp, 0

loc_328F6:
		pop	di
		stosw
		xchg	ax, bx
		stosw
		xchg	ax, dx
		stosw
		xchg	ax, bp
		stosw
		sub	di, 8
		pop	bp
		retn
sub_32811	endp

; ---------------------------------------------------------------------------
		mov	si, word ptr ds:[02Dh]

; =============== S U B	R O U T	I N E =======================================


sub_32907	proc near
		push	bp
		push	si
		push	di
		xchg	bp, si
		mov	cx, [bp+8]
		cmp	cx, 40h	; '@'
		jge	short loc_32945
		or	cx, cx
		jge	short loc_32962
		cmp	cx, 0C001h
		jle	short loc_32936
		mov	ch, 20h	; ' '
		call	sub_33CD9
		mov	cl, 0Ch
		and	cl, byte ptr ds:[023h]
		add	cl, [bp+0Ah]
		cmp	cl, 5
		jz	short loc_3293D
		cmp	cl, 8
		jz	short loc_3293D

loc_32936:
		sub	bx, bx
		mov	si, 0C001h
		jmp	short loc_3294E
; ---------------------------------------------------------------------------

loc_3293D:
		mov	si, 1
		mov	bx, 8000h
		jmp	short loc_3294E
; ---------------------------------------------------------------------------

loc_32945:
		jz	short loc_3295F
		mov	ch, 20h	; ' '
		call	sub_33CD9
		jmp	short loc_3295F
; ---------------------------------------------------------------------------

loc_3294E:
		sub	ax, ax
		mov	[bp+0],	ax
		mov	[bp+2],	ax
		mov	[bp+4],	ax
		mov	[bp+6],	bx
		mov	[bp+8],	si

loc_3295F:
		jmp	loc_32A12
; ---------------------------------------------------------------------------

loc_32962:
		mov	si, 38h	; '8'
		and	si, cx
		xor	cx, si
		shr	si, 1
		shr	si, 1
		shr	si, 1
		neg	si
		add	si, 7
		cmp	si, 7
		jnz	short loc_3297F
		mov	ah, 0
		mov	al, [bp+si]
		jmp	short loc_32981
; ---------------------------------------------------------------------------

loc_3297F:
		mov	ax, [bp+si]

loc_32981:
		sub	bx, bx
		mov	di, si

loc_32985:
		dec	di
		jl	short loc_3298E
		or	bl, [bp+di]
		mov	[bp+di], bh
		jmp	short loc_32985
; ---------------------------------------------------------------------------

loc_3298E:
		mov	dx, 0FFh
		and	cl, 7
		shr	dx, cl
		mov	di, dx
		inc	di
		and	dx, ax
		jnz	short loc_329A1
		or	bl, bl
		jz	short loc_32A12

loc_329A1:
		mov	ch, 20h	; ' '
		call	sub_33CD9
		xor	ax, dx
		mov	cl, 0Ch
		and	cl, byte ptr ds:[023h]
		cmp	cl, 0Ch
		jz	short loc_329CB
		cmp	cl, 0
		jz	short loc_329D6
		add	cl, [bp+0Ah]
		cmp	cl, 4
		jz	short loc_329CB
		cmp	cl, 9
		jz	short loc_329CB
		or	bl, dl
		jnz	short loc_329EC
		jmp	short loc_32A12
; ---------------------------------------------------------------------------

loc_329CB:
		mov	[bp+si], al
		cmp	byte ptr [bp+7], 0
		jnz	short loc_32A12
		jmp	loc_32936
; ---------------------------------------------------------------------------

loc_329D6:
		or	bl, bl
		jnz	short loc_329E6
		test	ax, di
		jnz	short loc_329E6
		add	dx, dx
		cmp	dx, di
		jbe	short loc_329CB
		jmp	short loc_329EC
; ---------------------------------------------------------------------------

loc_329E6:
		add	dx, dx
		cmp	dx, di
		jb	short loc_329CB

loc_329EC:
		sub	si, 7
		jl	short loc_329FA
		add	ax, di
		mov	[bp+si+7], al
		neg	ah
		jmp	short loc_32A09
; ---------------------------------------------------------------------------

loc_329FA:
		add	ax, di
		mov	[bp+si+7], ax
		inc	si

loc_32A00:
		inc	si
		jg	short loc_32A09
		adc	byte ptr [bp+si+7], 0
		jb	short loc_32A00

loc_32A09:
		jnb	short loc_32A12
		stc
		rcr	word ptr [bp+6], 1
		inc	word ptr [bp+8]

loc_32A12:
		pop	di
		pop	si
		pop	bp
		retn
sub_32907	endp


; =============== S U B	R O U T	I N E =======================================


sub_32A16	proc near
		push	bp
		push	si
		push	di
		mov	bp, word ptr ds:[02Dh]
		mov	ax, [bp+0]
		mov	bx, [bp+2]
		mov	cx, [bp+4]
		mov	dx, [bp+6]
		sub	di, di
		mov	si, [bp+8]
		cmp	si, 0C001h
		jz	short loc_32A55
		cmp	si, 0FFF0h
		jg	short loc_32A46
		mov	di, ax
		mov	ax, bx
		mov	bx, cx
		mov	cx, dx
		sub	dx, dx
		add	si, 10h

loc_32A46:
		inc	si
		jg	short loc_32A55
		shr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ax, 1
		rcr	di, 1
		jmp	short loc_32A46
; ---------------------------------------------------------------------------

loc_32A55:
		shl	di, 1
		mov	di, 0
		adc	ax, di
		adc	bx, di
		adc	cx, di
		adc	dx, di
		mov	[bp+0],	ax
		mov	[bp+2],	bx
		mov	[bp+4],	cx
		mov	[bp+6],	dx
		mov	bx, di
		mov	cx, di
		mov	si, di
		test	byte ptr [bp+3], 80h
		jz	short loc_32A84
		mov	bx, [bp+0]
		mov	cx, [bp+2]
		shl	bx, 1
		rcl	cx, 1

loc_32A84:
		mov	ax, [bp+0]
		mul	word ptr [bp+4]
		add	bx, ax
		adc	cx, dx
		adc	si, di
		add	bx, ax
		adc	cx, dx
		adc	si, di
		mov	bx, cx
		mov	cx, si
		sub	si, si
		mov	ax, [bp+2]
		mul	word ptr [bp+4]
		add	bx, ax
		adc	cx, dx
		adc	si, di
		add	bx, ax
		adc	cx, dx
		adc	si, di
		mov	ax, [bp+0]
		mul	word ptr [bp+6]
		add	bx, ax
		adc	cx, dx
		adc	si, di
		add	bx, ax
		adc	cx, dx
		adc	si, di
		shl	bx, 1
		adc	cx, di
		adc	si, di
		mov	bx, cx
		mov	cx, si
		sub	si, si
		mov	ax, [bp+4]
		mul	ax
		add	bx, ax
		adc	cx, dx
		adc	si, di
		mov	ax, [bp+6]
		mul	word ptr [bp+2]
		add	bx, ax
		adc	cx, dx
		adc	si, di
		add	bx, ax
		adc	cx, dx
		adc	si, di
		mov	ax, [bp+6]
		mul	word ptr [bp+4]
		add	cx, ax
		adc	si, dx
		adc	di, di
		add	cx, ax
		adc	si, dx
		adc	di, 0
		mov	ax, [bp+6]
		mul	ax
		add	si, ax
		adc	di, dx
		mov	[bp+0],	bx
		mov	[bp+2],	cx
		mov	[bp+4],	si
		mov	[bp+6],	di
		mov	byte ptr [bp+0Ah], 0
		mov	word ptr [bp+8], 0
		pop	di
		pop	si
		pop	bp
		retn
sub_32A16	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_32B1E	proc near

arg_0		= word ptr  4
arg_2		= word ptr  6
arg_6		= byte ptr  0Ah
arg_12		= byte ptr  16h

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	ds
		push	es
		mov	al, 0Ch
		mul	byte ptr [bp+arg_2]
		sub	ax, 0Ch
		xchg	ax, si
		add	si, [bp+arg_0]
		call	sub_32457
		mov	di, si

loc_32B36:
		dec	byte ptr [bp+arg_2]
		jle	short loc_32BB3
		push	bp
		mov	bp, word ptr ds:[02Dh]
		mov	al, [bp+arg_12]
		xor	[bp+arg_6], al
		call	sub_31923
		mov	[bp+0],	ax
		mov	[bp+2],	bx
		mov	[bp+arg_0], cx
		mov	[bp+arg_2], dx
		sub	di, 0Ch
		mov	bx, cs:[di]
		mov	cx, cs:[di+2]
		mov	dx, cs:[di+4]
		mov	si, cs:[di+6]
		mov	al, cs:[di+0Ah]
		cmp	al, [bp+arg_6]
		jz	short loc_32BA4
		sub	bx, [bp+0]
		sbb	cx, [bp+2]
		sbb	dx, [bp+arg_0]
		sbb	si, [bp+arg_2]
		jnb	short loc_32B92
		not	si
		not	dx
		not	cx
		neg	bx
		cmc
		adc	cx, 0
		adc	dx, 0
		adc	si, 0
		xor	al, 1

loc_32B92:
		mov	[bp+0],	bx
		mov	[bp+2],	cx
		mov	[bp+arg_0], dx
		mov	[bp+arg_2], si
		mov	[bp+arg_6], al
		pop	bp
		jmp	short loc_32B36
; ---------------------------------------------------------------------------

loc_32BA4:
		add	[bp+0],	bx
		adc	[bp+2],	cx
		adc	[bp+arg_0], dx
		adc	[bp+arg_2], si
		pop	bp
		jmp	short loc_32B36
; ---------------------------------------------------------------------------

loc_32BB3:
		mov	si, word ptr ds:[02Dh]
		cld
		lodsw
		xchg	ax, bx
		lodsw
		xchg	ax, cx
		lodsw
		xchg	ax, dx
		lodsw
		xchg	ax, di
		lodsw
		lodsb
		inc	si
		mov	word ptr ds:[02Dh], si
		xchg	si, di
		sub	di, di
		cmp	al, 1
		jnz	short loc_32BE0
		not	si
		not	dx
		not	cx
		neg	bx
		cmc
		adc	cx, di
		adc	dx, di
		adc	si, di
		jmp	short loc_32BF2
; ---------------------------------------------------------------------------

loc_32BE0:
		stc
		rcr	si, 1
		rcr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		adc	bx, di
		adc	cx, di
		adc	dx, di
		adc	si, di
		inc	di

loc_32BF2:
		mov	ax, word ptr ds:[02Dh]
		xchg	ax, di
		xchg	ax, bx
		stosw
		xchg	ax, cx
		stosw
		xchg	ax, dx
		stosw
		xchg	ax, si
		stosw
		xchg	ax, bx
		stosw
		mov	al, 0
		stosb
		pop	es
		pop	ds
		pop	di
		pop	si
		pop	bp
		retn	4
sub_32B1E	endp

; ---------------------------------------------------------------------------
byte_32C0B	db 8
					; Method
		db 0
		db 0			; Procedure
		db 0
		db 0Ah dup(0), 0B6h, 6 dup(0AAh), 2Ah, 2 dup(0), 1, 0
		db 3, 24h, 5 dup(22h), 2, 4 dup(0), 0B3h, 0E4h,	0, 0Dh
		db 0D0h, 0, 0Dh, 3 dup(0), 1, 0, 6Eh, 8, 4Bh, 0C7h, 3Bh
		db 2Eh,	6 dup(0), 0C6h,	40h, 16h, 99h, 6Bh, 5 dup(0), 1
		db 0, 0Ch, 45h,	92h, 0B0h, 8 dup(0), 0D5h, 45h,	0D6h, 7	dup(0)
		db 1, 0
word_32C6D	dw 8
		db 0Ch dup(0), 88h, 6 dup(0FFh), 7Fh, 2	dup(0),	1, 0, 0A6h
		db 9Ah,	5 dup(0AAh), 0Ah, 4 dup(0), 7Fh, 0E6h, 4, 5Bh
		db 0B0h, 5, 5Bh, 3 dup(0), 1, 0, 0EFh, 26h, 9Bh, 1, 1Ah
		db 0A0h, 1, 5 dup(0), 1Dh, 0CEh, 0DCh, 93h, 9Fh, 4, 4 dup(0)
		db 1, 0, 0Fh, 0B1h, 4Bh, 0F7h, 8, 7 dup(0), 3, 0D8h, 7Bh
		db 0Ch,	6 dup(0), 1, 0

; =============== S U B	R O U T	I N E =======================================


sub_32CCF	proc near
		call	sub_3243B
		call	sub_32A16
sub_32CCF	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_32CD5	proc near
		push	word ptr cs:byte_32C0B
		mov	ax, 163Dh
		push	ax
		call	sub_32B1E
		push	word ptr ds:[02Dh]
		push	si
		push	si
		call	sub_3188D
		add	word ptr ds:[02Dh], 0Ch
		retn
sub_32CD5	endp


; =============== S U B	R O U T	I N E =======================================


sub_32CF0	proc near
		call	sub_32A16
sub_32CF0	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_32CF3	proc near
		push	cs:word_32C6D
		mov	ax, 169Fh
		push	ax
		call	sub_32B1E
		retn
sub_32CF3	endp


; =============== S U B	R O U T	I N E =======================================


sub_32D00	proc near
		call	sub_3243B
		call	sub_32A16
		call	sub_3248A
		call	sub_32CD5
		call	sub_32CF3
		retn
sub_32D00	endp

; ---------------------------------------------------------------------------
		db 35h,	0C2h, 68h, 21h,	0A2h, 0DAh, 0Fh, 0C9h, 1, 3 dup(0)
word_32D1C	dw 8
		db 0Ch dup(0), 57h, 6 dup(55h),	1, 2 dup(0), 1,	0, 0BEh
		db 32h,	4 dup(33h), 3, 5 dup(0), 7Dh, 1Eh, 49h,	92h, 24h
		db 9, 4	dup(0),	1, 0, 0BCh, 0FEh, 0C6h,	71h, 1Ch, 7 dup(0)
		db 5Ch,	0FFh, 16h, 5Dh,	6 dup(0), 1, 0,	0D8h, 0BBh, 3Ah
		db 1, 8	dup(0),	0Ah, 0Ch, 4, 7 dup(0), 1, 8 dup(0), 0E7h
		db 0FDh, 0FFh, 2 dup(0), 0BDh, 0A4h, 0D6h, 7Bh,	0EEh, 64h
		db 5Ch,	0B3h, 2	dup(0FFh), 2 dup(0), 0B5h, 85h,	47h, 0FCh
		db 74h,	30h, 11h, 0A1h,	0Bh dup(0), 80h, 1, 3 dup(0), 9Ch
		db 0FAh, 64h, 0B0h, 0B2h, 1Dh, 7, 0E6h,	0FEh, 0FFh, 2 dup(0)
		db 9Ch,	0FAh, 64h, 0B0h, 0B2h, 1Dh, 7, 0E6h, 2 dup(0FFh)
		db 2 dup(0), 0F5h, 0BBh, 4Bh, 4, 46h, 56h, 85h,	0ACh, 4	dup(0)
		db 0E6h, 6Eh, 0D9h, 1Fh, 0BDh, 9, 0FAh,	0E9h, 0FEh, 0FFh
		db 2 dup(0), 8Dh, 7Bh, 35h, 0BDh, 5Bh, 84h, 0DDh, 0F6h
		db 2 dup(0FFh),	2 dup(0), 7Fh, 0D5h, 35h, 2, 0DBh, 80h
		db 73h,	0CCh, 4	dup(0)

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_32DF6	proc near

var_2		= word ptr -2

		push	bp
		mov	bp, sp
		lea	sp, [bp-2]
		push	si
		push	di
		push	si
		push	di
		push	si
		call	sub_31A5A
		mov	[bp+var_2], 0
		mov	di, 17AEh

loc_32E0C:
		cmp	[bp+var_2], 3
		jnb	short loc_32E33
		xchg	si, di
		call	sub_32457
		xchg	di, si
		push	si
		push	word ptr ds:[02Dh]
		call	sub_31FA9
		add	word ptr ds:[02Dh], 0Ch
		cmp	ax, 0
		jnz	short loc_32E33
		inc	[bp+var_2]
		add	di, 0Ch
		jmp	short loc_32E0C
; ---------------------------------------------------------------------------

loc_32E33:
		cmp	[bp+var_2], 0
		jnz	short loc_32E3E
		call	sub_32EA9
		jmp	short loc_32EA3
; ---------------------------------------------------------------------------

loc_32E3E:
		mov	bx, [bp+var_2]
		dec	bx
		; Hack (mov bl, cs:[bx+2])
		db 02eh
		db 08ah
		db 09fh
		db 002h
		db 000h
		mov	[bp+var_2], bx
		add	bx, 1802h
		mov	di, bx
		xchg	si, di
		call	sub_32457
		xchg	di, si
		push	si
		mov	di, word ptr ds:[02Dh]
		push	di
		lea	ax, [di-0Ch]
		mov	word ptr ds:[02Dh], ax
		push	ax
		call	sub_316BF
		push	si
		push	di
		push	si
		call	sub_3188D
		call	sub_32391
		push	di
		push	si
		push	si
		call	sub_316C3
		push	word ptr ds:[02Dh]
		push	si
		push	si
		call	sub_31A5A
		add	word ptr ds:[02Dh], 18h
		call	sub_32EA9
		mov	di, [bp+var_2]
		add	di, 17DEh
		xchg	si, di
		call	sub_32457
		xchg	di, si
		push	word ptr ds:[02Dh]
		push	si
		push	si
		call	sub_316C3
		add	word ptr ds:[02Dh], 0Ch

loc_32EA3:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
sub_32DF6	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_32EA9	proc near
		push	si
		push	di
		call	sub_3243B
		cmp	word ptr [si+8], 0FFE0h
		jg	short loc_32EBB
		mov	di, si
		call	sub_32474
		jmp	short loc_32EDD
; ---------------------------------------------------------------------------

loc_32EBB:
		mov	di, word ptr ds:[02Dh]
		add	word ptr [di+8], 3
		call	sub_32A16
		push	cs:word_32D1C
		mov	ax, 174Eh
		push	ax
		call	sub_32B1E
		push	di
		push	si
		push	si
		call	sub_3188D
		add	word ptr ds:[02Dh], 0Ch

loc_32EDD:
		pop	di
		pop	si
		retn
sub_32EA9	endp

; ---------------------------------------------------------------------------
word_32EE0	dw 0Dh
		db 0Ch dup(0), 3, 6 dup(0), 40h, 4 dup(0), 0A9h, 6 dup(0AAh)
		db 0Ah,	4 dup(0), 78h, 6 dup(55h), 1, 4	dup(0),	26h, 23h
		db 5 dup(22h), 5 dup(0), 1Ch, 2Bh, 0D8h, 82h, 2Dh, 0D8h
		db 2, 5	dup(0),	0FCh, 0F9h, 33h, 40h, 3, 34h, 6	dup(0)
		db 14h,	52h, 3,	34h, 40h, 3, 6 dup(0), 1Eh, 6Ch, 0C7h
		db 3Bh,	2Eh, 7 dup(0), 4Ch, 0B0h, 0C9h,	4Fh, 2,	7 dup(0)
		db 91h,	0Eh, 0E6h, 1Ah,	8 dup(0), 51h, 76h, 1Fh, 1, 8 dup(0)
		db 0C5h, 2Ch, 0Bh, 9 dup(0)

; =============== S U B	R O U T	I N E =======================================


sub_32F7E	proc near
		push	bp
		push	si
		push	di
		mov	bp, word ptr ds:[02Dh]
		lea	di, [bp-0Ch]
		mov	word ptr ds:[02Dh], di
		call	sub_323E6
		push	di
		push	si
		push	si
		call	sub_3188D
		mov	word ptr ds:[02Dh], bp
		mov	di, [si+8]
		cmp	di, 0FFC0h
		jle	short loc_32FF8
		mov	ax, [si]
		mov	bx, [si+2]
		mov	cx, [si+4]
		mov	dx, [si+6]
		inc	di
		jge	short loc_32FC6

loc_32FAF:
		shr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ax, 1
		inc	di
		jl	short loc_32FAF
		adc	ax, 0
		adc	bx, 0
		adc	cx, 0
		adc	dx, 0

loc_32FC6:
		sub	word ptr ds:[02Dh], 0Ch
		cld
		mov	di, word ptr ds:[02Dh]
		stosw
		xchg	ax, bx
		stosw
		xchg	ax, cx
		stosw
		xchg	ax, dx
		stosw
		sub	ax, ax
		stosw
		stosb
		sub	di, 0Bh
		push	cs:word_32EE0
		mov	ax, 1912h
		push	ax
		call	sub_32B1E
		mov	ax, word ptr ds:[02Dh]
		push	ax
		push	si
		push	si
		call	sub_3188D
		add	word ptr ds:[02Dh], 0Ch

loc_32FF8:
		pop	di
		pop	si
		pop	bp
		retn
sub_32F7E	endp

; ---------------------------------------------------------------------------
		db 0BBh, 0F0h, 17h, 5Ch, 29h, 3Bh, 0AAh, 0B8h, 1, 3 dup(0)
word_33008	dw 9
		db 0Ch dup(0), 68h, 6 dup(55h),	5, 4 dup(0), 0BAh, 34h
		db 5 dup(33h), 5 dup(0), 0A7h, 0C3h, 48h, 92h, 24h, 49h
		db 2, 5	dup(0),	4Dh, 5Dh, 22h, 0C7h, 71h, 1Ch, 6 dup(0)
		db 24h,	56h, 0EBh, 5Ch,	74h, 1,	6 dup(0), 39h, 0ADh, 0ECh
		db 0B1h, 13h, 7	dup(0),	0FDh, 0D6h, 80h, 0Fh, 1, 7 dup(0)
		db 0B5h, 7Ah, 0E4h, 10h, 8 dup(0)

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_33076	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		push	word ptr [di+8]
		push	si
		push	di
		mov	ax, [di]
		mov	bx, [di+2]
		mov	cx, [di+4]
		mov	dx, [di+6]
		cmp	dx, 0B505h
		ja	short loc_3309F
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		rcl	dx, 1
		mov	si, 0
		dec	[bp+var_2]
		jmp	short loc_330B4
; ---------------------------------------------------------------------------

loc_3309F:
		not	dx
		not	cx
		not	bx
		neg	ax
		cmc
		adc	bx, 0
		adc	cx, 0
		adc	dx, 0
		mov	si, 1

loc_330B4:
		sub	di, di

loc_330B6:
		or	dx, dx
		jnz	short loc_330D3
		xchg	ax, bx
		xchg	ax, cx
		xchg	ax, dx
		sub	di, 10h
		cmp	di, 0FFC0h
		jg	short loc_330B6
		sub	word ptr ds:[02Dh], 0Ch
		mov	di, word ptr ds:[02Dh]
		call	sub_323F7
		jmp	short loc_33100
; ---------------------------------------------------------------------------

loc_330D3:
		js	short loc_330E0

loc_330D5:
		dec	di
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx
		jns	short loc_330D5

loc_330E0:
		push	si
		push	di
		push	dx
		push	cx
		push	bx
		push	ax
		mov	si, sp
		call	sub_33166
		mov	si, 1A2Ch
		call	sub_32457
		mov	si, word ptr ds:[02Dh]
		mov	ax, sp
		push	si
		push	ax
		push	si
		call	sub_3188D
		add	sp, 0Ch

loc_33100:
		lea	si, [bp+var_2]
		sub	word ptr ds:[02Dh], 0Ch
		mov	di, word ptr ds:[02Dh]
		call	sub_324C8
		lea	si, [di+0Ch]
		push	si
		push	di
		push	di
		call	sub_316C3
		push	di
		push	[bp+var_4]
		push	[bp+var_4]
		call	sub_3188D
		add	word ptr ds:[02Dh], 18h
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
sub_33076	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_3312D	proc near

var_2		= word ptr -2

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, di
		call	sub_3243B
		mov	si, word ptr ds:[02Dh]
		call	sub_33166
		mov	si, 1A2Ch
		call	sub_32457
		mov	si, word ptr ds:[02Dh]
		push	si
		lea	si, [si+0Ch]
		push	si
		push	si
		call	sub_3188D
		push	si
		push	[bp+var_2]
		push	[bp+var_2]
		call	sub_3188D
		add	word ptr ds:[02Dh], 18h
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
sub_3312D	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_33166	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	word ptr [si+8], 0FFC0h
		jle	short loc_331B7
		sub	word ptr ds:[02Dh], 0Ch
		mov	di, word ptr ds:[02Dh]
		call	sub_32391
		inc	word ptr [di+8]
		push	si
		push	di
		push	di
		call	sub_316C3
		push	si
		push	di
		push	di
		call	sub_31A5A
		call	sub_3248A
		mov	bx, word ptr ds:[02Dh]
		add	word ptr [bx+8], 2
		call	sub_32A16
		push	cs:word_33008
		mov	ax, 1A3Ah
		push	ax
		call	sub_32B1E
		push	word ptr ds:[02Dh]
		push	di
		push	si
		call	sub_3188D
		inc	word ptr [si+8]
		add	word ptr ds:[02Dh], 18h

loc_331B7:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
sub_33166	endp

; ---------------------------------------------------------------------------
		mov	cl, 0
		jmp	short loc_331C7
; ---------------------------------------------------------------------------
		mov	cl, 2
		jmp	short loc_331C7
; ---------------------------------------------------------------------------
		mov	cl, 4

loc_331C7:
		mov	es, di
		mov	bp, sp
		mov	di, word ptr ds:[02Dh]
		mov	ch, [di+0Ah]
		push	cx
		push	ax
		cmp	word ptr [di+8], 0FFE0h
		jg	short loc_331E5
		cmp	cl, 2
		jnz	short loc_331E2
		call	sub_32391

loc_331E2:
		jmp	loc_3329F
; ---------------------------------------------------------------------------

loc_331E5:
		cmp	word ptr [di+8], 40h ; '@'
		jle	short loc_331F6
		call	sub_32423
		mov	word ptr [di+6], 21h ; '!'
		jmp	loc_3329F
; ---------------------------------------------------------------------------

loc_331F6:
		mov	byte ptr [di+0Ah], 0
		lea	si, [di-0Ch]
		mov	word ptr ds:[02Dh], si
		xchg	di, si
		call	sub_323C4
		xchg	di, si
		sub	word ptr [si+8], 2
		call	sub_31EA1
		and	al, 7
		mov	[bp-4],	al
		mov	bl, [bp-2]
		cmp	bl, 4
		jz	short loc_33257
		add	bl, [bp-4]
		and	bl, 7
		mov	[bp-4],	bl
		shr	bx, 1
		jnb	short loc_3323A
		xchg	di, si
		call	sub_323C4
		xchg	di, si
		sub	word ptr [si+8], 2
		push	si
		push	di
		push	di
		call	sub_316BF

loc_3323A:
		mov	word ptr ds:[02Dh], di
		mov	si, di
		test	byte ptr [bp-4], 3
		jp	short loc_3324B
		call	sub_32CF0
		jmp	short loc_3324E
; ---------------------------------------------------------------------------

loc_3324B:
		call	sub_32CCF

loc_3324E:
		mov	bl, [bp-4]
		shr	bl, 1
		shr	bl, 1
		jmp	short loc_33293
; ---------------------------------------------------------------------------

loc_33257:
		test	byte ptr [bp-4], 1
		jz	short loc_3326E
		xchg	si, di
		call	sub_323C4
		xchg	si, di
		sub	word ptr [si+8], 2
		push	si
		push	di
		push	di
		call	sub_316BF

loc_3326E:
		mov	word ptr ds:[02Dh], di
		mov	si, di
		call	sub_32D00
		lea	di, [si-0Ch]
		mov	ax, si
		test	byte ptr [bp-4], 3
		jp	short loc_33284
		xchg	si, di

loc_33284:
		xchg	ax, di
		push	si
		push	ax
		push	di
		call	sub_31A5A
		mov	bl, [bp-4]
		shr	bl, 1
		and	bl, 1

loc_33293:
		cmp	byte ptr [bp-2], 2
		jz	short loc_3329C
		xor	bl, [bp-1]

loc_3329C:
		mov	[di+0Ah], bl

loc_3329F:
		mov	word ptr ds:[02Dh], di
		mov	sp, bp
		retn
; ---------------------------------------------------------------------------
		mov	es, di
		mov	si, word ptr ds:[02Dh]
		lea	di, [si-0Ch]
		mov	word ptr ds:[02Dh], di
		call	sub_32391
		mov	ax, [si+8]
		cmp	ax, 4001h
		jge	short loc_332F6
		cmp	ax, 0C001h
		jle	short loc_332F1
		mov	cl, 0
		mov	bx, si
		dec	ax
		jl	short loc_332D1
		call	sub_324A7
		mov	bx, di
		mov	cl, 1

loc_332D1:
		mov	ch, 0
		xchg	ch, [bx+0Ah]
		push	cx
		call	sub_32DF6
		pop	cx
		cmp	cl, 1
		jnz	short loc_332EE
		push	cx
		call	sub_323C4
		dec	word ptr [di+8]
		push	di
		push	si
		push	si
		call	sub_316BF
		pop	cx

loc_332EE:
		mov	[si+0Ah], ch

loc_332F1:
		mov	word ptr ds:[02Dh], si
		retn
; ---------------------------------------------------------------------------

loc_332F6:
		mov	di, si
		push	word ptr [si+0Ah]
		call	sub_323C4
		pop	ax
		mov	[si+0Ah], al
		dec	word ptr [si+8]
		jmp	short loc_332F1
; ---------------------------------------------------------------------------
		mov	es, di
		mov	si, word ptr ds:[02Dh]
		lea	di, [si-0Ch]
		mov	word ptr ds:[02Dh], di
		call	sub_323E6
		jmp	short loc_3333B
; ---------------------------------------------------------------------------
		mov	es, di
		mov	si, word ptr ds:[02Dh]
		lea	di, [si-0Ch]
		mov	word ptr ds:[02Dh], di
		call	sub_32391
		jmp	short loc_3333B
; ---------------------------------------------------------------------------
		mov	es, di
		mov	si, word ptr ds:[02Dh]
		lea	di, [si-0Ch]
		mov	word ptr ds:[02Dh], di
		call	near ptr unk_323D5

loc_3333B:
		call	sub_324A7
		cmp	byte ptr [di+0Ah], 0
		jnz	short loc_3335D
		mov	ax, [di+8]
		cmp	ax, 0C001h
		jle	short loc_33359
		cmp	ax, 4001h
		jge	short loc_3335D
		call	sub_33076

loc_33354:
		mov	word ptr ds:[02Dh], si
		retn
; ---------------------------------------------------------------------------

loc_33359:
		mov	ch, 4
		jmp	short loc_3335F
; ---------------------------------------------------------------------------

loc_3335D:
		mov	ch, 1

loc_3335F:
		call	sub_33CD9
		mov	ax, 4001h
		mov	di, si
		mov	cl, 0
		call	sub_3240D
		cmp	ch, 1
		jnz	short loc_33354
		mov	word ptr [di+6], 0C000h
		jmp	short loc_33354
; ---------------------------------------------------------------------------
		mov	ax, 0DE3h
		jmp	short loc_3338B
; ---------------------------------------------------------------------------
		mov	es, di
		mov	si, word ptr ds:[02Dh]
		lea	di, [si-0Ch]
		jmp	short loc_333A4
; ---------------------------------------------------------------------------
		mov	ax, 0DD2h

loc_3338B:
		mov	es, di
		mov	si, word ptr ds:[02Dh]
		lea	di, [si-0Ch]
		mov	word ptr ds:[02Dh], di
		call	ax
		push	si
		push	di
		push	si
		call	sub_3188D
		mov	word ptr ds:[02Dh], si

loc_333A4:
		mov	bp, sp
		mov	ax, 0
		push	ax
		mov	ax, [si+8]
		cmp	ax, 0Ch
		jg	short loc_33400
		cmp	ax, 0FFC0h
		jle	short loc_3342C
		call	sub_3248A
		inc	word ptr [di+8]
		push	word ptr ds:[022h]
		and	byte ptr ds:[023h], 0F3h
		or	byte ptr ds:[023h], 4
		mov	si, di
		call	sub_32907
		pop	word ptr ds:[022h]
		push	ax
		mov	di, sp
		call	sub_3250B
		dec	word ptr [si+8]
		lea	di, [si+0Ch]
		push	di
		push	si
		push	di
		call	sub_316BF
		pop	ax
		sar	ax, 1
		jnb	short loc_33448
		mov	word ptr [si], 6485h
		mov	word ptr [si+2], 0F9DEh
		mov	word ptr [si+4], 0F333h
		mov	word ptr [si+6], 0B504h
		jmp	short loc_3345B
; ---------------------------------------------------------------------------

loc_33400:
		cmp	ax, 4001h
		jnz	short loc_33415
		mov	ax, 7FFFh
		and	ax, [si+6]
		or	ax, [si+4]
		or	ax, [si+2]
		or	ax, [si]
		jnz	short loc_33433

loc_33415:
		cmp	byte ptr [si+0Ah], 0
		jnz	short loc_33441
		mov	di, si
		mov	ch, 8
		call	sub_33CD9
		mov	ax, 4001h
		mov	cl, 0
		call	sub_3240D
		jmp	short loc_33481
; ---------------------------------------------------------------------------

loc_3342C:
		mov	di, si
		call	sub_32391
		jmp	short loc_33481
; ---------------------------------------------------------------------------

loc_33433:
		mov	word ptr [si+6], 0C000h
		mov	di, si
		mov	ch, 1
		call	sub_33CD9
		jmp	short loc_33481
; ---------------------------------------------------------------------------

loc_33441:
		mov	di, si
		call	sub_323F7
		jmp	short loc_33481
; ---------------------------------------------------------------------------

loc_33448:
		mov	word ptr [si], 0
		mov	word ptr [si+2], 0
		mov	word ptr [si+4], 0
		mov	word ptr [si+6], 8000h

loc_3345B:
		inc	ax
		mov	[si+8],	ax
		mov	byte ptr [si+0Ah], 0
		mov	di, si
		lea	si, [di+0Ch]
		call	sub_32F7E
		push	si
		push	di
		push	si
		call	sub_3188D
		push	si
		push	di
		push	si
		call	sub_316C3
		cmp	byte ptr [bp-2], 1
		jnz	short loc_33481
		xor	byte ptr [si+0Ah], 1

loc_33481:
		mov	word ptr ds:[02Dh], si
		mov	sp, bp
		retn

; =============== S U B	R O U T	I N E =======================================


sub_33488	proc near
		push	bx
		push	cx
		push	dx
		mov	cl, 4
		mov	ch, 0Ah
		mov	bx, es:[si]
		mov	al, bh
		shr	al, cl
		mul	ch
		mov	dl, 0Fh
		and	dl, bh
		add	al, dl
		mul	ch
		mov	dx, 0F0h ; '�
		and	dl, bl
		shr	dx, cl
		add	ax, dx
		mov	cx, 0Ah
		mul	cx
		and	bx, 0Fh
		add	ax, bx
		pop	dx
		pop	cx
		pop	bx
		retn
sub_33488	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_334B7	proc near

var_4		= word ptr -4
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	al, es:[si+9]
		and	ax, 80h
		rol	al, 1
		mov	[di+0Ah], al
		mov	cl, 4
		mov	al, es:[si+8]
		shl	ax, cl
		shr	al, cl
		aad
		mov	di, 2710h
		mul	di
		xchg	ax, bx
		lea	si, [si+6]
		call	sub_33488
		add	ax, bx
		adc	dl, dh
		mov	bx, dx
		mul	di
		xchg	ax, bx
		mov	cx, dx
		mul	di
		add	cx, ax
		adc	dl, dh
		sub	si, 2
		call	sub_33488
		add	ax, bx
		adc	cx, 0
		adc	dl, dh
		push	si
		mov	bx, dx
		mul	di
		xchg	ax, cx
		mov	si, dx
		mul	di
		xchg	ax, bx
		xchg	di, dx
		mul	dx
		add	bx, si
		adc	di, ax
		pop	si
		sub	si, 2
		call	sub_33488
		add	ax, cx
		adc	bx, dx
		adc	di, dx
		mov	si, 2710h
		mul	si
		xchg	ax, bx
		mov	cx, dx
		mul	si
		xchg	ax, si
		xchg	di, dx
		mul	dx
		add	cx, si
		adc	di, ax
		adc	dx, 0
		mov	si, [bp+var_2]
		call	sub_33488
		add	bx, ax
		adc	cx, 0
		adc	di, 0
		adc	dx, 0
		mov	ax, 40h	; '@'

loc_33548:
		or	dx, dx
		jnz	short loc_33559
		sub	ax, 10h
		jz	short loc_3357D
		xchg	dx, di
		xchg	di, cx
		xchg	cx, bx
		jmp	short loc_33548
; ---------------------------------------------------------------------------

loc_33559:
		js	short loc_33566

loc_3355B:
		dec	ax
		shl	bx, 1
		rcl	cx, 1
		rcl	di, 1
		adc	dx, dx
		jns	short loc_3355B

loc_33566:
		mov	si, [bp+var_4]
		mov	[si], bx
		mov	[si+2],	cx
		mov	[si+4],	di
		mov	[si+6],	dx
		mov	[si+8],	ax
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_3357D:
		mov	ax, 0C001h
		jmp	short loc_33566
sub_334B7	endp


; =============== S U B	R O U T	I N E =======================================


sub_33582	proc near
		push	ax
		push	cx
		mov	al, 64h	; 'd'
		mov	cl, 4
		xchg	ax, dx
		div	dl
		mov	dl, ah
		aam
		shl	ah, cl
		or	ah, al
		xchg	ax, dx
		aam
		shl	ah, cl
		or	al, ah
		mov	ah, dh
		stosw
		pop	cx
		pop	ax
		retn
sub_33582	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_335A0	proc near

var_2		= word ptr -2

		push	bp
		mov	bp, sp
		push	si
		push	di
		cld
		mov	ax, [si+8]
		mov	bx, [si]
		mov	cx, [si+2]
		mov	dx, [si+6]
		mov	si, [si+4]
		cmp	ax, 0
		jl	short loc_335F1
		sub	ax, 3Ch	; '<'
		jl	short loc_335DD
		jg	short loc_335F3
		cmp	dx, 0DE0Bh
		jb	short loc_335DD
		ja	short loc_335F3
		cmp	si, 6B3Ah
		jb	short loc_335DD
		ja	short loc_335F3
		cmp	cx, 763Fh
		jb	short loc_335DD
		ja	short loc_335F3
		cmp	bx, 0FFF0h
		ja	short loc_335F3

loc_335DD:
		mov	ah, 0
		sub	al, 4

loc_335E1:
		add	al, 10h
		jg	short loc_335F5
		mov	ah, bh
		mov	bx, cx
		mov	cx, si
		mov	si, dx
		sub	dx, dx
		jmp	short loc_335E1
; ---------------------------------------------------------------------------

loc_335F1:
		jmp	short loc_3365A
; ---------------------------------------------------------------------------

loc_335F3:
		jmp	short loc_33663
; ---------------------------------------------------------------------------

loc_335F5:
		sub	al, 10h
		jge	short loc_33607

loc_335F9:
		shr	dx, 1
		rcr	si, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ah, 1
		inc	al
		jl	short loc_335F9

loc_33607:
		add	ah, ah
		adc	bx, 0
		adc	cx, 0
		adc	si, 0
		adc	dx, 0
		xchg	ax, si
		mov	si, 2710h
		div	si
		xchg	ax, cx
		div	si
		xchg	ax, bx
		div	si
		call	sub_33582
		sub	dx, dx
		xchg	ax, cx
		div	si
		xchg	ax, bx
		div	si
		xchg	ax, cx
		div	si
		call	sub_33582
		mov	dx, bx
		xchg	ax, cx
		div	si
		xchg	ax, cx
		div	si
		call	sub_33582
		mov	dx, cx
		div	si
		call	sub_33582
		aam
		mov	cl, 4
		shl	ah, cl
		or	al, ah
		stosb

loc_3364D:
		mov	si, [bp+var_2]
		mov	al, [si+0Ah]
		ror	al, 1
		stosb
		pop	di
		pop	si
		pop	bp
		retn
; ---------------------------------------------------------------------------

loc_3365A:
		mov	al, 0

loc_3365C:
		mov	cx, 9
		rep stosb
		jmp	short loc_3364D
; ---------------------------------------------------------------------------

loc_33663:
		mov	ch, 8
		call	sub_33CD9
		mov	al, 99h	; '�
		jmp	short loc_3365C
sub_335A0	endp

; ---------------------------------------------------------------------------
off_3366C	dw offset loc_3376E
		dw offset loc_33778
		dw offset loc_33782
		dw offset loc_3378C
		dw offset loc_33796
		dw offset loc_3379D
		dw offset loc_337BB
		dw offset loc_337A4
off_3367C	dw offset loc_33B4C
		dw offset loc_33BC1
		dw offset loc_33C31
		dw offset loc_33C33
off_33684	dw offset sub_32159
		dw offset sub_3265A
		dw offset sub_3225D
		dw offset sub_324C8
off_3368C	dw offset sub_3384C
		dw offset sub_33853
		dw offset sub_3385D
		dw offset sub_3385A
		dw offset sub_33864
		dw offset sub_33863
		dw offset sub_3386C
		dw offset sub_3386B
off_3369C	dw offset sub_32159
		dw offset sub_3265A
		dw offset sub_3225D
		dw offset sub_324C8
off_336A4	dw offset sub_320DF
		dw offset sub_326B2
		dw offset sub_321B6
		dw offset sub_3250B
off_336AC	dw offset sub_338E4
		dw offset sub_338DE
		dw offset sub_33945
		dw offset sub_339B3
		dw offset sub_338ED
		dw offset sub_339C3
		dw offset sub_338DE
		dw offset sub_339A3
off_336BC	dw offset sub_338F8
		dw offset sub_338DE
		dw offset sub_33921
		dw offset sub_339E0
		dw offset sub_33977
		dw offset sub_339ED
		dw offset sub_3397C
		dw offset sub_339D3
; ---------------------------------------------------------------------------

loc_336CC:
		mov	ch, 1
		call	sub_33CD9
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_336D4:
		ja	short loc_336FA
		test	ah, 20h
		jnz	short loc_336CC
		mov	al, ah
		inc	dx
		mov	di, ds
		and	al, 0C0h
		jz	short loc_336F2
		cmp	al, 80h	; '?'
		mov	di, ss
		jb	short loc_336F2
		mov	di, [bp+0]
		ja	short loc_336F2
		mov	di, [bp+14h]

loc_336F2:
		lods	byte ptr es:[si]
		xchg	ah, al
		and	al, 7
		jmp	short loc_33737
; ---------------------------------------------------------------------------

loc_336FA:
		cmp	al, 9
		jnz	short loc_33712
		mov	ax, es
		xor	ax, ss:27h
		mov	es, ax
		push	es
		pop	es
		mov	word ptr es:[si-3], 0E489h
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_33712:
		jmp	loc_33D16
; ---------------------------------------------------------------------------
		db  55h	; U
		db    0
; ---------------------------------------------------------------------------

loc_33717:
		sti
		cld
		push	ax
		push	cx
		push	dx
		push	bx
		push	ds
		push	bp
		push	si
		push	di
		push	es
		mov	bp, sp
		mov	ss:53h,	bp
		les	si, [bp+12h]
		mov	dl, 0
		dec	si
		lods	word ptr es:[si]
		sub	al, 34h	; '4'
		cmp	al, 8
		jnb	short loc_336D4

loc_33737:
		mov	bx, 0C007h
		and	bl, ah
		and	bh, ah
		xchg	ax, cx
		cmp	bh, 0C0h ; '?'
		jnb	short loc_337AB
		cmp	bh, 40h	; '@'
		ja	short loc_3375B
		jz	short loc_3375F
		sub	ax, ax
		cmp	bl, 6
		jnz	short loc_33762
		lods	word ptr es:[si]
		mov	[bp+12h], si
		mov	si, ds
		jmp	short loc_337C0
; ---------------------------------------------------------------------------

loc_3375B:
		lods	word ptr es:[si]
		jmp	short loc_33762
; ---------------------------------------------------------------------------

loc_3375F:
		lods	byte ptr es:[si]
		cbw

loc_33762:
		mov	[bp+12h], si
		mov	bh, 0
		shl	bx, 1
		jmp	cs:off_3366C[bx]

loc_3376E:
		add	ax, [bp+0Ah]
		add	ax, [bp+4]
		mov	si, ds
		jmp	short loc_337C0
; ---------------------------------------------------------------------------

loc_33778:
		add	ax, [bp+0Ah]
		add	ax, [bp+2]
		mov	si, ds
		jmp	short loc_337C0
; ---------------------------------------------------------------------------

loc_33782:
		add	ax, [bp+6]
		add	ax, [bp+4]
		mov	si, ss
		jmp	short loc_337C0
; ---------------------------------------------------------------------------

loc_3378C:
		add	ax, [bp+6]
		add	ax, [bp+2]
		mov	si, ss
		jmp	short loc_337C0
; ---------------------------------------------------------------------------

loc_33796:
		add	ax, [bp+4]
		mov	si, ds
		jmp	short loc_337C0
; ---------------------------------------------------------------------------

loc_3379D:
		add	ax, [bp+2]
		mov	si, ds
		jmp	short loc_337C0
; ---------------------------------------------------------------------------

loc_337A4:
		add	ax, [bp+0Ah]
		mov	si, ds
		jmp	short loc_337C0
; ---------------------------------------------------------------------------

loc_337AB:
		mov	[bp+12h], si
		mov	ax, ss
		mov	ds, ax
		mov	es, ax
		test	cl, 1
		jz	short loc_337EC
		jmp	short loc_337D2
; ---------------------------------------------------------------------------

loc_337BB:
		add	ax, [bp+6]
		mov	si, ss

loc_337C0:
		xchg	ax, si
		cmp	dl, 1
		jnz	short loc_337C7
		xchg	ax, di

loc_337C7:
		mov	es, ax
		mov	ax, ss
		mov	ds, ax
		test	cl, 1
		jz	short loc_337EC

loc_337D2:
		cmp	ch, 0C0h ; '?'
		jnb	short loc_337DA
		jmp	loc_33873
; ---------------------------------------------------------------------------

loc_337DA:
		test	ch, 20h
		jnz	short loc_337E2
		jmp	loc_33A1A
; ---------------------------------------------------------------------------

loc_337E2:
		mov	bx, 6
		and	bl, cl
		jmp	cs:off_3367C[bx]
; ---------------------------------------------------------------------------

loc_337EC:
		mov	ax, 38h	; '8'
		and	al, ch
		shr	ax, 1
		shr	ax, 1
		xchg	ax, bp
		cmp	ch, 0C0h ; '?'
		jnb	short loc_33825
		mov	di, word ptr ds:[02Dh]
		sub	di, 0Ch
		mov	word ptr ds:[02Dh], di
		mov	bx, 6
		and	bl, cl
		call	cs:off_33684[bx]
		mov	cx, ss
		mov	es, cx
		mov	si, 0Ch
		mov	bx, di
		lea	ax, [bx+si]
		mov	dx, ax
		mov	cx, 268Ch
		jmp	cs:off_3368C[bp]
; ---------------------------------------------------------------------------

loc_33825:
		mov	bh, 0
		; Hack (mov bl, cs:[bx+2])
		db 02eh
		db 08ah
		db 09fh
		db 002h
		db 000h
		mov	ax, word ptr ds:[02Dh]
		add	bx, ax
		test	cl, 4
		mov	dx, ax
		jz	short loc_3383A
		mov	dx, bx

loc_3383A:
		sub	si, si
		test	cl, 2
		jz	short loc_33844
		mov	si, 0Ch

loc_33844:
		mov	cx, 268Ch
		jmp	cs:off_3368C[bp]

; =============== S U B	R O U T	I N E =======================================


sub_3384C	proc near
		push	ax
		push	bx
		push	dx
		push	cx
		jmp	sub_316C3
sub_3384C	endp


; =============== S U B	R O U T	I N E =======================================


sub_33853	proc near
		push	ax
		push	bx
		push	dx
		push	cx
		jmp	sub_3188D
sub_33853	endp


; =============== S U B	R O U T	I N E =======================================


sub_3385A	proc near
		add	si, 0Ch
sub_3385A	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_3385D	proc near
		push	ax
		push	bx
		push	cx
		jmp	sub_31FA9
sub_3385D	endp


; =============== S U B	R O U T	I N E =======================================


sub_33863	proc near
		xchg	ax, bx
sub_33863	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_33864	proc near
		push	ax
		push	bx
		push	dx
		push	cx
		jmp	sub_316BF
sub_33864	endp


; =============== S U B	R O U T	I N E =======================================


sub_3386B	proc near
		xchg	ax, bx
sub_3386B	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_3386C	proc near
		push	ax
		push	bx
		push	dx
		push	cx
		jmp	sub_31A5A
sub_3386C	endp

; ---------------------------------------------------------------------------

loc_33873:
		mov	bp, 6
		and	bp, cx
		test	ch, 20h
		jnz	short loc_338BF
		test	ch, 10h
		jnz	short loc_3389C
		test	ch, 8
		jnz	short loc_338DB
		mov	di, word ptr ds:[02Dh]
		mov	ax, 0FFF4h
		add	di, ax
		mov	word ptr ds:[024h], ax
		mov	ax, 2687h
		push	ax
		jmp	cs:off_3369C[bp]
; ---------------------------------------------------------------------------

loc_3389C:
		mov	di, word ptr ds:[02Dh]
		xchg	si, di
		test	ch, 8
		jnz	short loc_338B0
		mov	ax, 2691h
		push	ax
		jmp	cs:off_336A4[bp]
; ---------------------------------------------------------------------------

loc_338B0:
		mov	word ptr ds:[024h], 0Ch
		mov	ax, 2687h
		push	ax
		jmp	cs:off_336A4[bp]
; ---------------------------------------------------------------------------

loc_338BF:
		mov	ax, 8
		and	al, ch
		or	bp, ax
		mov	ax, 2691h
		push	ax
		test	ch, 10h
		jnz	short loc_338D4
		jmp	cs:off_336AC[bp]
; ---------------------------------------------------------------------------

loc_338D4:
		xchg	si, di
		jmp	cs:off_336BC[bp]
; ---------------------------------------------------------------------------

loc_338DB:
		jmp	loc_33C61

; =============== S U B	R O U T	I N E =======================================


sub_338DE	proc near
		mov	ch, 1
		call	sub_33CD9
		retn
sub_338DE	endp


; =============== S U B	R O U T	I N E =======================================


sub_338E4	proc near
		mov	cl, 4
		mov	ax, es:[si+2]
		mov	word ptr ds:[020h], ax
sub_338E4	endp ; sp-analysis failed


; =============== S U B	R O U T	I N E =======================================


sub_338ED	proc near
		mov	ax, es:[si]
		mov	word ptr ds:[022h], ax
		mov	ch, 0
		jmp	sub_33CD9
sub_338ED	endp


; =============== S U B	R O U T	I N E =======================================


sub_338F8	proc near
		call	sub_33977
		call	sub_3397C
		mov	ax, word ptr ds:[031h]
		sub	ax, word ptr ds:[02Dh]
		mov	cx, 60h	; '`'
		cmp	ax, cx
		jb	short loc_3390D
		xchg	ax, cx

loc_3390D:
		mov	dl, 0Ch
		div	dl
		xchg	ax, cx
		add	cx, cx
		mov	ax, 0FFFFh
		shr	ax, cl
		stosw
		sub	ax, ax
		stosw
		stosw
		stosw
		stosw
		retn
sub_338F8	endp


; =============== S U B	R O U T	I N E =======================================


sub_33921	proc near
		call	sub_338F8
		mov	si, word ptr ds:[02Dh]
		mov	bp, es:[di-0Ah]
		neg	bp
		dec	bp

loc_3392F:
		jz	short loc_33940
		call	sub_3231B
		add	si, 0Ch
		add	di, 0Ah
		shl	bp, 1
		shl	bp, 1
		jmp	short loc_3392F
; ---------------------------------------------------------------------------

loc_33940:
		mov	word ptr ds:[02Dh], si
		retn
sub_33921	endp


; =============== S U B	R O U T	I N E =======================================


sub_33945	proc near
		mov	di, word ptr ds:[02Dh]
		mov	bp, es:[si+4]
		neg	bp
		dec	bp
		jz	short sub_338E4
		add	si, 5Eh	; '^'

loc_33955:
		sub	si, 0Ah
		shr	bp, 1
		shr	bp, 1
		jnb	short loc_33955

loc_3395E:
		sub	di, 0Ch
		call	sub_32348
		sub	si, 0Ah
		shr	bp, 1
		shr	bp, 1
		jb	short loc_3395E
		add	si, 0FFFCh
		mov	word ptr ds:[02Dh], di
		jmp	sub_338E4
sub_33945	endp


; =============== S U B	R O U T	I N E =======================================


sub_33977	proc near
		mov	ax, word ptr ds:[022h]
		stosw
		retn
sub_33977	endp


; =============== S U B	R O U T	I N E =======================================


sub_3397C	proc near
		mov	ax, word ptr ds:[031h]
		sub	ax, word ptr ds:[02Dh]
		mov	cx, 60h	; '`'
		cmp	ax, cx
		jb	short loc_3398B
		xchg	ax, cx

loc_3398B:
		neg	ax
		mov	cl, 0Ch
		idiv	cl
		and	al, 7
		mov	cl, 3
		shl	al, cl
		mov	cx, word ptr ds:[020h]
		and	ch, 0C7h
		or	ch, al
		xchg	ax, cx
		stosw
		retn
sub_3397C	endp


; =============== S U B	R O U T	I N E =======================================


sub_339A3	proc near
		mov	di, word ptr ds:[02Dh]
		sub	di, 0Ch
		call	sub_3279E
		sub	word ptr ds:[02Dh], 0Ch
		retn
sub_339A3	endp


; =============== S U B	R O U T	I N E =======================================


sub_339B3	proc near
		mov	di, word ptr ds:[02Dh]
		sub	di, 0Ch
		call	sub_334B7
		sub	word ptr ds:[02Dh], 0Ch
		retn
sub_339B3	endp


; =============== S U B	R O U T	I N E =======================================


sub_339C3	proc near
		mov	di, word ptr ds:[02Dh]
		sub	di, 0Ch
		call	sub_32348
		sub	word ptr ds:[02Dh], 0Ch
		retn
sub_339C3	endp


; =============== S U B	R O U T	I N E =======================================


sub_339D3	proc near
		mov	si, word ptr ds:[02Dh]
		call	sub_32811
		add	word ptr ds:[02Dh], 0Ch
		retn
sub_339D3	endp


; =============== S U B	R O U T	I N E =======================================


sub_339E0	proc near
		mov	si, word ptr ds:[02Dh]
		call	sub_335A0
		add	word ptr ds:[02Dh], 0Ch
		retn
sub_339E0	endp


; =============== S U B	R O U T	I N E =======================================


sub_339ED	proc near
		mov	si, word ptr ds:[02Dh]
		call	sub_3231B
		add	word ptr ds:[02Dh], 0Ch
		retn
sub_339ED	endp

; ---------------------------------------------------------------------------
off_339FA	dw offset loc_33A39
		dw offset loc_33A93
		dw offset loc_33A4C
		dw offset loc_33A47
		dw offset loc_33A9A
		dw offset loc_33A93
		dw offset loc_33A9A
		dw offset loc_33A9A
		dw offset loc_33A8E
		dw offset loc_33A93
		dw offset loc_33AAB
		dw offset loc_33AB6
		dw offset loc_33AB6
		dw offset loc_33A93
		dw offset loc_33AB6
		dw offset loc_33AB6
; ---------------------------------------------------------------------------

loc_33A1A:
		mov	bh, 0
		; Hack (mov bl, cs:[bx+2])
		db 02eh
		db 08ah
		db 09fh
		db 002h
		db 000h
		mov	si, word ptr ds:[02Dh]
		add	si, bx
		mov	bl, 18h
		and	bl, ch
		and	cl, 6
		or	bl, cl
		cld
		mov	cx, 6
		jmp	cs:off_339FA[bx]

loc_33A39:
		sub	word ptr ds:[02Dh], 0Ch
		mov	di, word ptr ds:[02Dh]
		rep movsw
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_33A47:
		mov	di, 0Ch
		jmp	short loc_33A4F
; ---------------------------------------------------------------------------

loc_33A4C:
		mov	di, 0

loc_33A4F:
		mov	ax, word ptr ds:[031h]
		sub	ax, 0Ch
		cmp	si, ax
		jz	short loc_33A69
		xchg	di, si
		mov	ax, 4001h
		mov	cl, 0
		call	sub_3240D
		add	word ptr ds:[02Dh], si
		jmp	short loc_33AC2
; ---------------------------------------------------------------------------

loc_33A69:
		add	di, 0Ch
		mov	dx, di
		mov	cx, si
		sub	cx, word ptr ds:[02Dh]
		jz	short loc_33A88
		push	ss
		pop	es
		sub	si, 2
		mov	di, word ptr ds:[031h]
		sub	di, 2
		std
		shr	cx, 1
		rep movsw
		cld

loc_33A88:
		add	word ptr ds:[02Dh], dx
		jmp	short loc_33AC2
; ---------------------------------------------------------------------------

loc_33A8E:
		test	ch, 7
		jz	short loc_33AC2

loc_33A93:
		mov	ch, 1
		call	sub_33CD9
		jmp	short loc_33AC2
; ---------------------------------------------------------------------------

loc_33A9A:
		mov	di, word ptr ds:[02Dh]

loc_33A9E:
		mov	ax, [di]
		xchg	ax, [si]
		stosw
		add	si, 2
		loop	loc_33A9E
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_33AAB:
		mov	di, si
		mov	si, word ptr ds:[02Dh]
		rep movsw
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_33AB6:
		mov	di, si
		mov	si, word ptr ds:[02Dh]
		rep movsw
		mov	word ptr ds:[02Dh], si

loc_33AC2:
		jmp	loc_33C61
; ---------------------------------------------------------------------------
		db 8 dup(4), 7 dup(0), 2 dup(4), 8, 6, 8, 6, 4,	2, 0, 0Ah
		db 8, 3	dup(4),	0Ah, 2 dup(4)
off_33AE5	dw offset sub_33B25
		dw offset sub_33B2A
		dw offset sub_33B37
		dw offset sub_33B37
		dw offset sub_32069
		dw offset sub_320A5
		dw offset sub_33B37
		dw offset sub_33B37
		dw offset sub_32391
		db 0D2h, 0Dh, 0E3h, 0Dh, 0F4h, 0Dh, 5, 0Eh, 16h, 0Eh, 27h
		db 0Eh,	67h, 25h, 0AEh,	19h, 0A6h, 1Ah,	30h, 17h, 26h
		db 18h,	5Fh, 25h, 67h, 25h, 67h, 25h, 67h, 25h,	0D1h, 8
		db 5Dh,	1Bh, 5,	8, 67h,	25h, 37h, 2 dup(13h), 10h, 67h
		db 25h,	67h, 25h

; =============== S U B	R O U T	I N E =======================================


sub_33B25	proc near
		xor	byte ptr [si+0Ah], 1
		retn
sub_33B25	endp


; =============== S U B	R O U T	I N E =======================================


sub_33B2A	proc near
		mov	byte ptr [si+0Ah], 0
		retn
sub_33B2A	endp

; ---------------------------------------------------------------------------
		push	si
		push	di
		call	sub_325AE
		pop	di
		pop	si
		retn

; =============== S U B	R O U T	I N E =======================================


sub_33B37	proc far
		mov	ch, 1
		call	sub_33CD9
		jmp	loc_33C61
; ---------------------------------------------------------------------------
		retn
; ---------------------------------------------------------------------------
off_33B40	dw offset loc_33B5F
		dw offset loc_33B96
		dw offset loc_33B72
		dw offset loc_33B81
		dw offset loc_33B9E
		dw offset loc_33BB1
; ---------------------------------------------------------------------------

loc_33B4C:
		mov	bx, 1Fh
		and	bl, ch
		mov	al, cs:[bx+24F5h]
		cbw
		xchg	ax, di
		shl	bx, 1
		jmp	cs:off_33B40[di]

loc_33B5F:
		mov	di, word ptr ds:[02Dh]
		sub	di, 0Ch
		call	cs:off_33AE5[bx]
		mov	word ptr ds:[02Dh], di
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_33B72:
		mov	si, word ptr ds:[02Dh]
		mov	di, si
		mov	ax, 2691h
		push	ax
		jmp	cs:off_33AE5[bx]
; ---------------------------------------------------------------------------

loc_33B81:
		mov	si, word ptr ds:[02Dh]
		mov	di, si
		sub	di, 0Ch
		call	cs:off_33AE5[bx]
		mov	word ptr ds:[02Dh], di
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_33B96:
		add	word ptr ds:[02Dh], 0Ch
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_33B9E:
		mov	di, word ptr ds:[02Dh]
		lea	si, [di+0Ch]
		call	cs:off_33AE5[bx]
		mov	word ptr ds:[02Dh], si
		jmp	loc_33C61
; ---------------------------------------------------------------------------

loc_33BB1:
		mov	di, word ptr ds:[02Dh]
		lea	si, [di+0Ch]
		mov	ax, 2691h
		push	ax
		jmp	cs:off_33AE5[bx]
; ---------------------------------------------------------------------------

loc_33BC1:
		and	ch, 1Fh
		cmp	ch, 3
		jnz	short loc_33C1E
		mov	word ptr ds:[059h], 2
		mov	word ptr ds:[055h], 6D65h
		mov	word ptr ds:[057h], 8775h
		mov	word ptr ds:[024h], 0
		mov	di, word ptr ds:[031h]
		mov	word ptr ds:[02Dh], di
		mov	bx, word ptr ds:[02Fh]
		sub	bx, di
		neg	bx
		mov	ax, 4001h
		mov	cl, 0
		call	sub_3240D
		mov	byte ptr [di+7], 0C0h ;	'?'
		lea	si, [di+0Ah]
		sub	di, 2
		mov	cx, word ptr ds:[02Fh]
		sub	cx, di
		neg	cx
		shr	cx, 1
		std
		rep movsw
		mov	word ptr ds:[020h], 4100h
		mov	word ptr ds:[022h], 33Fh
		jmp	short loc_33C2F
; ---------------------------------------------------------------------------

loc_33C1E:
		cmp	ch, 2
		jnz	short loc_33C2A
		mov	byte ptr ds:[020h], 0
		jmp	short loc_33C2F
; ---------------------------------------------------------------------------

loc_33C2A:
		mov	ch, 1
		call	sub_33CD9

loc_33C2F:
		jmp	short loc_33C61
; ---------------------------------------------------------------------------

loc_33C31:
		jmp	short loc_33C2A
; ---------------------------------------------------------------------------

loc_33C33:
		test	ch, 1Fh
		jnz	short loc_33C2A
		mov	ax, word ptr ds:[02Dh]
		sub	ax, word ptr ds:[031h]
		mov	cl, 0Ch
		idiv	cl
		and	al, 7
		mov	cl, 3
		shl	al, cl
		mov	cx, word ptr ds:[020h]
		and	ch, 0C7h
		or	ch, al
		mov	[bp+10h], cx
		jmp	short loc_33C61
; ---------------------------------------------------------------------------
		mov	si, ss:24h
		add	ss:2Dh,	si

loc_33C61:
		mov	ax, ss:2Fh
		cmp	ss:2Dh,	ax
		jb	short loc_33C7B

loc_33C6C:
		mov	sp, ss:53h
		pop	es
		pop	di
		pop	si
		pop	bp
		pop	ds
		pop	bx
		pop	dx
		pop	cx
		pop	ax
		iret
; ---------------------------------------------------------------------------

loc_33C7B:
		mov	ch, 40h	; '@'
		mov	di, word ptr ds:[031h]
		mov	word ptr ds:[02Dh], di
		call	sub_33CD9
		int	3		; Trap to Debugger
		jmp	short loc_33C6C
sub_33B37	endp ; sp-analysis failed

; ---------------------------------------------------------------------------
		in	ax, dx
		sbb	si, cx
		sbb	si, bp
		sbb	bp, bp
		sbb	si, cx
		sbb	si, bp
		sbb	dx, si
		sbb	al, 37h	; '7'
		sbb	ax, 1D49h
		pop	bx
		sbb	ax, 1DA8h
		lodsw
		sbb	ax, 1DB8h

loc_33CA5:
		sti
		cld
		push	ax
		push	cx
		push	dx
		push	bx
		push	ds
		push	bp
		push	si
		push	di
		push	es
		mov	bp, sp
		mov	ss:53h,	sp
		lds	si, [bp+12h]
		lodsb
		mov	[bp+12h], si
		mov	di, ss
		mov	ds, di
		cbw
		xchg	ax, bx
		cmp	bl, 0E6h ; '�
		jb	short loc_33CD2
		mov	ax, 2691h
		push	ax
		jmp	word ptr cs:[bx+26D5h]
; ---------------------------------------------------------------------------

loc_33CD2:
		mov	ch, 1
		call	sub_33CD9
		jmp	short loc_33C61

; =============== S U B	R O U T	I N E =======================================


sub_33CD9	proc near
		push	ax
		push	cx
		push	ds
		push	ss
		pop	ds
		mov	al, byte ptr ds:[020h]
		mov	cl, byte ptr ds:[022h]
		and	cl, 7Fh
		xor	cl, 7Fh
		or	al, ch
		mov	ah, al
		and	ah, cl
		xor	ah, al
		test	ah, 8
		jz	short loc_33CFA
		or	al, 20h

loc_33CFA:
		test	al, cl
		jz	short loc_33D0D
		or	al, 80h
		mov	byte ptr ds:[020h], al
		and	al, cl
		cmp	al, 20h	; ' '
		jnz	short loc_33D16
		pop	ds
		pop	cx
		pop	ax
		retn
; ---------------------------------------------------------------------------

loc_33D0D:
		and	al, 7Fh
		mov	byte ptr ds:[020h], al
		pop	ds
		pop	cx
		pop	ax
		retn
; ---------------------------------------------------------------------------

loc_33D16:
		call	sub_1987
		cmp	ax, 0FFFFh
		jz	short loc_33D2E
		mov	ah, 35h
		int	21h		; DOS -	2+ - GET INTERRUPT VECTOR
					; AL = interrupt number
					; Return: ES:BX	= value	of interrupt vector
		mov	ss:61h,	bx
		mov	word ptr ss:63h, es

loc_33D2E:
		mov	sp, ss:53h
		pop	es
		pop	di
		pop	si
		pop	bp
		pop	ds
		pop	bx
		pop	dx
		pop	cx
		pop	ax
		jmp	dword ptr ss:61h
sub_33CD9	endp

; ---------------------------------------------------------------------------
		dd 0
		dd 0
		dd 0
		dw 0
		db 0
seg040		ends

; ===========================================================================

; Segment type:	Pure code
seg041		segment	byte public 'CODE' use16
		assume cs:seg041
		assume es:nothing, ss:nothing, ds:dseg,	fs:nothing, gs:nothing

include libs/BorlandC/ctor2[textc].asm
include libs/BorlandC/ctor3[textc].asm
include libs/BorlandC/strings[textc].asm
		dd 0, 0
seg041		ends

; ===========================================================================
