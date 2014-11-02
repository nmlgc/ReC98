EMU_PROG	segment	para public 'CODE' use16
		assume cs:EMU_PROG
		assume es:nothing, ss:nothing, ds:nothing, fs:nothing, gs:nothing
		db 87h
		db 0E2h
byte_10052	db 0, 0Ch, 18h,	24h, 30h, 3Ch, 48h, 54h, 60h, 6Ch, 78h
		db 84h,	90h, 9Ch, 0A8h,	0B4h

emu086_10062	proc near
		push	dx
		push	si

emu086_10064:
		mov	dx, [si+6]
		and	dh, 7Fh
		or	dx, [si]
		or	dx, [si+2]
		or	dx, [si+4]
		jnz	short emu086_10094
		cmp	bx, 0FFFFh
		jz	short emu086_10090
		cmp	word ptr [bx+8], 4001h
		jl	short emu086_10090
		mov	dx, [bx+6]
		and	dh, 7Fh
		or	dx, [bx]
		or	dx, [bx+2]
		or	dx, [bx+4]
		jnz	short emu086_100D4

emu086_10090:
		clc

emu086_10091:
		pop	si
		pop	dx
		retn

emu086_10094:
		cmp	bx, 0FFFFh
		jz	short emu086_100D6
		cmp	word ptr [bx+8], 4001h
		jl	short emu086_100D6
		mov	dx, [bx+6]
		and	dh, 7Fh
		or	dx, [bx]
		or	dx, [bx+2]
		or	dx, [bx+4]
		jz	short emu086_100D6
		mov	dx, [si+6]
		cmp	dx, [bx+6]
		ja	short emu086_100D6
		jb	short emu086_100D4
		mov	dx, [si+4]
		cmp	dx, [bx+4]
		ja	short emu086_100D6
		jb	short emu086_100D4
		mov	dx, [si+2]
		cmp	dx, [bx+2]
		ja	short emu086_100D6
		jb	short emu086_100D4
		mov	dx, [si]
		cmp	dx, [bx]
		ja	short emu086_100D6

emu086_100D4:
		mov	si, bx

emu086_100D6:
		push	di
		mov	ch, 1
		call	emu086_12759
		mov	cx, 6
		cld
		rep movsw
		stc
		pop	di
		jmp	short emu086_10091
emu086_10062	endp

; START	OF FUNCTION CHUNK FOR emu086_100FE

emu086_100E6:
		mov	al, [si+0Ah]

emu086_100E9:
		mov	[bp-5],	al
		mov	word ptr [bp-4], 4001h
		nop
		jmp	short emu086_10131

emu086_100F4:
		mov	di, [bp+4]
		nopcall	emu086_10EA3

emu086_100FB:
		jmp	emu086_10291
; END OF FUNCTION CHUNK	FOR emu086_100FE


emu086_100FE	proc near

; FUNCTION CHUNK AT 0096 SIZE 00000018 BYTES

		push	bx
		push	di
		mov	bx, di
		mov	di, [bp+4]
		nopcall	emu086_10062
		pop	di
		pop	bx
		jb	short emu086_100FB
		cmp	bx, 4001h
		jl	short emu086_100E6
		mov	al, [bp-6]
		or	al, al
		jnz	short emu086_100F4
		jmp	short emu086_100E6
emu086_100FE	endp

; START	OF FUNCTION CHUNK FOR emu086_10143

emu086_1011C:
		mov	bx, 0FFFFh
		mov	al, [di+0Ah]
		xor	al, cl
		mov	si, di
		mov	di, [bp+4]
		nopcall	emu086_10062
		jb	short emu086_100FB
		jmp	short emu086_100E9

emu086_10131:
		mov	ax, [si]
		mov	bx, [si+2]
		mov	cx, [si+4]
		mov	dx, [si+6]
		jmp	emu086_1027E
; END OF FUNCTION CHUNK	FOR emu086_10143


emu086_1013F	proc near
		mov	cl, 1
		jmp	short emu086_10145
emu086_1013F	endp


emu086_10143	proc near
var_6		= byte ptr -6
var_5		= byte ptr -5
var_4		= word ptr -4
var_2		= byte ptr -2
arg_0		= word ptr  4
arg_2		= word ptr  6
arg_4		= word ptr  8

; FUNCTION CHUNK AT 00CC SIZE 00000023 BYTES

		mov	cl, 0

emu086_10145:
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
		jge	short emu086_100FE
		cmp	bx, 4001h
		jge	short emu086_1011C
		cmp	ax, bx
		jge	short emu086_1017B
		xor	cl, [di+0Ah]
		xchg	ax, bx
		xchg	si, di
		jmp	short emu086_1017E

emu086_1017B:
		mov	cl, [si+0Ah]

emu086_1017E:
		mov	[bp+var_5], cl
		mov	cx, [si+8]
		mov	[bp+var_4], cx
		cmp	bx, 0C001h
		jle	short emu086_10131
		sub	ax, bx
		cmp	ax, 41h	; 'A'
		jg	short emu086_10131
		mov	bx, [di+2]
		mov	cx, [di+4]
		mov	dx, [di+6]
		mov	di, [di]
		xchg	ax, di
		mov	[bp+var_2], 0
		sub	di, 8
		jl	short emu086_101C1

emu086_101A9:
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
		jge	short emu086_101A9

emu086_101C1:
		and	di, 7
		jz	short emu086_101D4

emu086_101C6:
		shr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ax, 1
		rcr	[bp+var_2], 1
		dec	di
		jnz	short emu086_101C6

emu086_101D4:
		cmp	[bp+var_6], 0
		jnz	short emu086_101F7
		add	ax, [si]
		adc	bx, [si+2]
		adc	cx, [si+4]
		adc	dx, [si+6]
		jnb	short emu086_1025E
		rcr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ax, 1
		rcr	[bp+var_2], 1
		inc	[bp+var_4]
		jmp	short emu086_1025E

emu086_101F7:
		xor	[bp+var_5], 1
		sub	ax, [si]
		sbb	bx, [si+2]
		sbb	cx, [si+4]
		sbb	dx, [si+6]
		jnb	short emu086_10220
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

emu086_10220:
		mov	si, 8

emu086_10223:
		or	dh, dh
		jnz	short emu086_1025C
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
		jge	short emu086_10223
		mov	[bp+var_4], 0C001h
		mov	[bp+var_5], 0
		jmp	short emu086_1027E

emu086_1024E:
		dec	[bp+var_4]
		shl	[bp+var_2], 1
		rcl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx

emu086_1025C:
		jns	short emu086_1024E

emu086_1025E:
		shl	[bp+var_2], 1
		adc	ax, di
		adc	bx, di
		adc	cx, di
		adc	dx, di
		jnb	short emu086_10270
		rcr	dx, 1
		inc	[bp+var_4]

emu086_10270:
		cmp	[bp+var_4], 4001h
		jge	short emu086_10299
		cmp	[bp+var_4], 0C001h
		jle	short emu086_102A2

emu086_1027E:
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

emu086_10291:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn	6

emu086_10299:
		mov	ch, 8
		mov	[bp+var_4], 4001h
		jmp	short emu086_102A9

emu086_102A2:
		mov	ch, 10h
		mov	[bp+var_4], 0C001h

emu086_102A9:
		call	emu086_12759
		mov	[bp+var_5], 0
		sub	ax, ax
		mov	bx, ax
		mov	cx, ax
		cwd
		jmp	short emu086_1027E
emu086_10143	endp

; START	OF FUNCTION CHUNK FOR emu086_1030D

emu086_102B9:
		mov	ax, 4001h

emu086_102BC:
		mov	di, [bp+arg_0]
		mov	cl, [bp+var_6]
		call	emu086_10E8D

emu086_102C5:
		pop	ax
		jmp	emu086_1039D

emu086_102C9:
		push	di
		mov	bx, di
		mov	di, [bp+arg_0]
		call	emu086_10062
		pop	di
		jb	short emu086_102C5
		cmp	word ptr [di+8], 0C001h
		jle	short emu086_102F4
		jmp	short emu086_102B9

emu086_102DE:
		push	si
		mov	bx, 0FFFFh
		mov	si, di
		mov	di, [bp+arg_0]
		call	emu086_10062
		pop	si
		jb	short emu086_102C5
		cmp	word ptr [si+8], 0C001h
		jg	short emu086_102B9

emu086_102F4:
		mov	di, [bp+arg_0]
		call	emu086_10EA3
		jmp	short emu086_102C5

emu086_102FC:
		mov	ch, 8
		call	emu086_12759
		jmp	short emu086_102B9

emu086_10303:
		mov	ch, 10h
		call	emu086_12759

emu086_10308:
		mov	ax, 0C001h
		jmp	short emu086_102BC
; END OF FUNCTION CHUNK	FOR emu086_1030D

emu086_1030D	proc near
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
		jge	short emu086_102C9
		cmp	bx, dx
		jge	short emu086_102DE
		cmp	ax, cx
		jle	short emu086_10308
		cmp	bx, cx
		jle	short emu086_10308
		add	ax, bx
		dec	ax
		cmp	ax, 4001h
		jge	short emu086_102FC
		inc	ax
		cmp	ax, 0C001h
		jle	short emu086_10303
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
		call	emu086_103A3
		add	sp, 14h
		or	dx, dx
		js	short emu086_1037B
		dec	di
		shl	si, 1
		rcl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		rcl	dx, 1

emu086_1037B:
		shl	si, 1
		adc	ax, 0
		jnb	short emu086_1038D
		adc	bx, ax
		adc	cx, ax
		adc	dx, ax
		jnb	short emu086_1038D
		rcr	dx, 1
		inc	di

emu086_1038D:
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

emu086_1039D:
		pop	di
		pop	si
		pop	bp
		retn	6
emu086_1030D	endp


emu086_103A3	proc near
		push	di
		sub	di, di
		mov	cx, di
		mov	si, di
		test	byte ptr [bp+0Fh], 80h
		jz	short emu086_103B6
		mov	cx, [bp+0]
		mov	si, [bp+2]

emu086_103B6:
		test	byte ptr [bp+3], 80h
		jz	short emu086_103CB
		add	cx, [bp+0Ch]
		adc	si, [bp+0Eh]
		adc	di, di
		test	byte ptr [bp+0Fh], 80h
		jz	short emu086_103CB
		dec	di

emu086_103CB:
		sub	bx, bx
		mov	ax, [bp+0Ch]
		mul	word ptr [bp+4]
		add	cx, ax
		adc	si, dx
		adc	di, 0
		mov	ax, [bp+10h]
		or	ax, ax
		jz	short emu086_103F8
		mul	word ptr [bp+0]
		add	cx, ax
		adc	si, dx
		adc	di, 0
		mov	ax, [bp+10h]
		mul	word ptr [bp+2]
		add	si, ax
		adc	di, dx
		adc	bx, 0

emu086_103F8:
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
		jz	short emu086_10423
		mul	word ptr [bp+0]
		add	si, ax
		adc	di, dx
		adc	bx, 0

emu086_10423:
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
		jz	short emu086_10453
		mul	word ptr [bp+4]
		add	di, ax
		adc	bx, dx
		adc	cx, 0
		mov	ax, [bp+10h]
		mul	word ptr [bp+6]
		add	bx, ax
		adc	cx, dx
		adc	si, 0

emu086_10453:
		mov	ax, [bp+12h]
		or	ax, ax
		jz	short emu086_1047E
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

emu086_1047E:
		mov	dx, si
		xchg	ax, di
		pop	si
		pop	di
		retn
emu086_103A3	endp

; START	OF FUNCTION CHUNK FOR emu086_104DA

emu086_10484:
		mov	si, di
		mov	di, [bp+arg_0]
		nopcall	emu086_10062
		jb	short emu086_104BE
		cmp	word ptr [bx+8], 4001h
		jl	short emu086_104C6
		call	emu086_10EA3
		jmp	short emu086_104BE

emu086_1049B:
		mov	si, bx
		mov	bx, 0FFFFh
		mov	di, [bp+arg_0]
		nopcall	emu086_10062
		jb	short emu086_104BE
		jmp	short emu086_104B0

emu086_104AB:
		mov	ch, 4

emu086_104AD:
		call	emu086_12759

emu086_104B0:
		mov	ax, 4001h

emu086_104B3:
		mov	cl, [bp-7]
		nop
		mov	di, [bp+arg_0]
		nopcall	emu086_10E8D

emu086_104BE:
		jmp	emu086_10822

emu086_104C1:
		mov	ch, 10h
		call	emu086_12759

emu086_104C6:
		mov	ax, 0C001h
		jmp	short emu086_104B3

emu086_104CB:
		mov	ch, 8
		jmp	short emu086_104AD

emu086_104CF:
		mov	ax, [bp-12h]
		or	ax, [bp-14h]
		jnz	short emu086_10536
		jmp	emu086_1082E
; END OF FUNCTION CHUNK	FOR emu086_104DA

emu086_104DA	proc near
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
		jge	short emu086_10484
		cmp	ax, 4001h
		jge	short emu086_1049B
		cmp	si, 0C001h
		jle	short emu086_104AB
		cmp	ax, 0C001h
		jle	short emu086_104C6
		sub	ax, si
		cmp	ax, 4001h
		jge	short emu086_104CB
		cmp	ax, 0C001h
		jle	short emu086_104C1
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
		jcxz	short emu086_104CF

emu086_10536:
		xchg	ax, cx
		mov	cx, [bx+2]
		mov	bx, [bx]
		cmp	di, dx
		jb	short emu086_105BA
		mov	[bp+var_8], 1
		sub	bx, [bp+var_14]
		sbb	cx, [bp+var_12]
		sbb	si, ax
		sbb	di, dx
		jnb	short emu086_105BA
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
		jl	short emu086_105B5
		cmp	si, [bp+var_E]
		jb	short emu086_105B7
		add	[bp+var_A], 1
		adc	[bp+var_8], 0
		sub	di, [bp+var_14]
		sbb	bx, [bp+var_12]
		sbb	cx, [bp+var_10]
		sbb	si, [bp+var_E]

emu086_105B5:
		jl	short emu086_1061D

emu086_105B7:
		jmp	emu086_10686

emu086_105BA:
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
		jge	short emu086_105B7
		mov	dx, si
		neg	dx
		cmp	dx, [bp+var_E]
		jb	short emu086_1061D
		sub	[bp+var_A], 1
		sbb	[bp+var_8], 0
		add	di, [bp+var_14]
		adc	bx, [bp+var_12]
		adc	cx, [bp+var_10]
		adc	si, [bp+var_E]
		jge	short emu086_10686

emu086_1061D:
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
		jl	short emu086_106E4
		cmp	cx, [bp+var_E]
		jb	short emu086_10683
		add	[bp+var_C], 1
		adc	[bp+var_A], ax
		adc	[bp+var_8], al
		sub	di, [bp+var_12]
		sbb	bx, [bp+var_10]
		sbb	cx, [bp+var_E]
		jl	short emu086_106E4

emu086_10683:
		jmp	emu086_10739

emu086_10686:
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
		jge	short emu086_10739
		mov	dx, cx
		neg	dx
		cmp	dx, [bp+var_E]
		jb	short emu086_106E4
		sub	[bp+var_C], 1
		sbb	[bp+var_A], ax
		sbb	[bp+var_8], al
		add	di, [bp+var_12]
		adc	bx, [bp+var_10]
		adc	cx, [bp+var_E]
		jge	short emu086_10739

emu086_106E4:
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
		jl	short emu086_10781
		cmp	bx, [bp+var_E]
		jb	short emu086_10736
		add	si, 1
		adc	[bp+var_C], ax
		adc	[bp+var_A], ax
		adc	[bp+var_8], al
		sub	di, [bp+var_10]
		sbb	bx, [bp+var_E]
		jl	short emu086_10781

emu086_10736:
		jmp	emu086_107C3

emu086_10739:
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
		jge	short emu086_107C3
		mov	dx, bx
		neg	dx
		cmp	dx, [bp+var_E]
		jb	short emu086_10781
		sub	si, 1
		sbb	[bp+var_C], ax
		sbb	[bp+var_A], ax
		sbb	[bp+var_8], al
		add	di, [bp+var_10]
		adc	bx, [bp+var_E]
		jge	short emu086_107C3

emu086_10781:
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
		jnb	short emu086_107B8
		div	cx
		sub	dx, cx
		neg	dx
		neg	ax

emu086_107A5:
		mov	dl, [bp+var_8]
		sbb	si, 0
		jnb	short emu086_107E1
		sbb	bx, 0
		sbb	di, 0
		sbb	dl, 0
		jmp	short emu086_107E1

emu086_107B8:
		sub	ax, ax
		cwd
		stc
		jmp	short emu086_107A5

emu086_107BE:
		sub	ax, ax
		cwd
		jmp	short emu086_107DE

emu086_107C3:
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
		jnb	short emu086_107BE
		div	cx

emu086_107DE:
		mov	dl, [bp+var_8]

emu086_107E1:
		shr	dl, 1
		jnb	short emu086_107F2
		rcr	di, 1
		rcr	bx, 1
		rcr	si, 1
		rcr	ax, 1
		rcr	dh, 1
		inc	[bp+var_6]

emu086_107F2:
		shr	cx, 1
		sub	ch, dh
		mov	cx, [bp+var_6]
		adc	ax, 0
		jnb	short emu086_10809
		adc	si, ax
		adc	bx, ax
		adc	di, ax
		jnb	short emu086_10809
		rcr	di, 1
		inc	cx

emu086_10809:
		cmp	cx, 4001h
		jge	short emu086_1082B
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

emu086_10822:
		lea	sp, [bp-4]
		pop	di
		pop	si
		pop	bp
		retn	6

emu086_1082B:
		jmp	emu086_104B0

emu086_1082E:
		mov	cx, dx
		mov	dx, di
		xchg	ax, si
		cmp	dx, cx
		jb	short emu086_1083D
		sub	dx, cx
		mov	[bp+var_8], 1

emu086_1083D:
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
		jmp	short emu086_107DE
emu086_104DA	endp ; sp-analysis failed

		mov	si, word ptr ds:__emu+0Dh

emu086_10855	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	ax, [si+8]
		cmp	ax, 0C001h
		jle	short emu086_1088B
		cmp	ax, 4001h
		jge	short emu086_1088F
		cmp	byte ptr [si+0Ah], 0
		jnz	short emu086_10899
		call	emu086_10EBB
		call	emu086_108AA
		mov	di, word ptr ds:__emu+0Dh
		push	si
		push	di
		push	si
		call	emu086_104DA
		push	di
		push	si
		push	si
		call	emu086_10143
		dec	word ptr [si+8]
		add	word ptr ds:__emu+0Dh, 0Ch

emu086_1088B:
		pop	di
		pop	si
		pop	bp
		retn

emu086_1088F:
		mov	bx, 0FFFFh
		mov	di, si
		call	emu086_10062
		jmp	short emu086_1088B

emu086_10899:
		mov	ch, 1
		call	emu086_12759
		mov	di, si
		call	emu086_10E77
		mov	word ptr [di+8], 4001h
		jmp	short emu086_1088B
emu086_10855	endp


emu086_108AA	proc near
		push	si
		push	di
		mov	di, word ptr ds:__emu+0Dh
		mov	bx, [di+8]
		mov	dx, [di+6]
		mov	ax, [di+4]
		mov	cx, [di+2]
		sar	bx, 1
		jnb	short emu086_108C7
		inc	bx
		shr	dx, 1
		rcr	ax, 1
		rcr	cx, 1

emu086_108C7:
		cmp	dx, 0FFFEh
		jnb	short emu086_108E9
		push	bx
		push	cx
		mov	cx, dx
		mov	bx, ax
		mov	si, dx
		stc
		rcr	si, 1

emu086_108D7:
		div	si
		dec	si
		cmp	si, ax
		jbe	short emu086_108F0
		inc	si
		add	si, ax
		rcr	si, 1
		mov	dx, cx
		mov	ax, bx
		jmp	short emu086_108D7

emu086_108E9:
		stc
		rcr	dx, 1
		rcr	ax, 1
		jmp	short emu086_10907

emu086_108F0:
		inc	si
		cmp	si, ax
		jnb	short emu086_108F6
		xchg	ax, si

emu086_108F6:
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

emu086_10907:
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
emu086_108AA	endp

byte_10919	db 0, 2, 40h, 42h, 1, 3, 41h, 43h

emu086_10921	proc near
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
		jge	short emu086_1095B
		jmp	short emu086_10997

emu086_10946:
		inc	di
		jmp	short emu086_10986

emu086_10949:
		dec	di
		jl	short emu086_10946
		shl	[bp+var_4], 1
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx
		jb	short emu086_10974
		jns	short emu086_10949

emu086_1095B:
		cmp	dx, [si+6]
		ja	short emu086_10974
		jb	short emu086_10949
		cmp	cx, [si+4]
		ja	short emu086_10974
		jb	short emu086_10949
		cmp	bx, [si+2]
		ja	short emu086_10974
		jb	short emu086_10949
		cmp	ax, [si]
		jb	short emu086_10949

emu086_10974:
		inc	[bp+var_4]
		sub	ax, [si]
		sbb	bx, [si+2]
		sbb	cx, [si+4]
		sbb	dx, [si+6]
		or	di, di
		jg	short emu086_10949

emu086_10986:
		or	dx, dx
		js	short emu086_10997
		jz	short emu086_109CF

emu086_1098C:
		dec	di
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx
		jns	short emu086_1098C

emu086_10997:
		add	di, [si+8]

emu086_1099A:
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
		and	ds:__emu+1, 0B8h
		mov	di, 7
		mov	ax, [bp+var_4]
		cmp	[bp+var_2], 1
		jnz	short emu086_109BE
		neg	ax

emu086_109BE:
		and	di, ax
		mov	dl, cs:byte_10919[di]
		or	ds:__emu+1, dl
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn

emu086_109CF:
		xchg	dx, cx
		xchg	cx, bx
		xchg	ax, bx
		sub	di, 10h
		or	dx, dx
		jnz	short emu086_10986
		xchg	dx, cx
		xchg	cx, bx
		sub	di, 10h
		or	dx, dx
		jnz	short emu086_10986
		xchg	dx, cx
		sub	di, 10h
		or	dx, dx
		jnz	short emu086_10986
		mov	di, 0C001h
		sub	dx, dx
		sub	cx, cx
		sub	bx, bx
		sub	ax, ax
		jmp	short emu086_1099A
emu086_10921	endp

; START	OF FUNCTION CHUNK FOR emu086_10A29

emu086_109FC:
		mov	dx, [si+6]
		and	dh, 7Fh
		or	dx, [si]
		or	dx, [si+2]
		or	dx, [si+4]
		jz	short emu086_10A3F

emu086_10A0C:
		mov	ch, 1
		call	emu086_12759
		mov	ax, 4500h
		jmp	emu086_10AA7

emu086_10A17:
		mov	dx, [di+6]
		and	dh, 7Fh
		or	dx, [di]
		or	dx, [di+2]
		or	dx, [di+4]
		jnz	short emu086_10A0C
		jmp	short emu086_10A45
; END OF FUNCTION CHUNK	FOR emu086_10A29

emu086_10A29	proc near
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
		jge	short emu086_109FC

emu086_10A3F:
		cmp	bx, 4001h
		jge	short emu086_10A17

emu086_10A45:
		mov	dx, ax
		cmp	ax, bx
		jg	short emu086_10A4D
		mov	dx, bx

emu086_10A4D:
		cmp	dx, 0C001h
		jle	short emu086_10A8E
		mov	cl, [si+0Ah]
		cmp	cl, [di+0Ah]
		jl	short emu086_10AA4
		jg	short emu086_10A9A
		cmp	ax, bx
		jl	short emu086_10A95
		jg	short emu086_10A9F
		mov	ax, [si+6]
		cmp	ax, [di+6]
		jnz	short emu086_10A93
		mov	ch, 3
		and	ch, ds:__emu+3
		jz	short emu086_10AB1
		mov	ax, [si+4]
		cmp	ax, [di+4]
		jnz	short emu086_10A93
		mov	ax, [si+2]
		cmp	ax, [di+2]
		jnz	short emu086_10A93
		cmp	ch, 2
		jz	short emu086_10AD3
		mov	ax, [si]
		cmp	ax, [di]
		jnz	short emu086_10A93

emu086_10A8E:
		mov	ax, 4000h
		jmp	short emu086_10AA7

emu086_10A93:
		ja	short emu086_10A9F

emu086_10A95:
		cmp	cl, 0
		jnz	short emu086_10AA4

emu086_10A9A:
		mov	ax, 100h
		jmp	short emu086_10AA7

emu086_10A9F:
		cmp	cl, 0
		jnz	short emu086_10A9A

emu086_10AA4:
		mov	ax, 0

emu086_10AA7:
		mov	ds:__emu+1, ah
		pop	di
		pop	si
		pop	bp
		retn	4

emu086_10AB1:
		mov	bx, [si]
		sub	bx, [di]
		mov	bx, [si+2]
		sbb	bx, [di+2]
		mov	bx, [si+4]
		sbb	bx, [di+4]
		ja	short emu086_10ACC
		neg	bx
		and	bx, 0FF80h
		jz	short emu086_10A8E
		jmp	short emu086_10A95

emu086_10ACC:
		and	bx, 0FF80h
		jz	short emu086_10A8E
		jmp	short emu086_10A9F

emu086_10AD3:
		mov	bx, [si]
		sub	bx, [di]
		ja	short emu086_10AE2
		neg	bx
		and	bh, 0FCh
		jz	short emu086_10A8E
		jmp	short emu086_10A95

emu086_10AE2:
		and	bh, 0FCh
		jz	short emu086_10A8E
		jmp	short emu086_10A9F
emu086_10A29	endp


emu086_10AE9	proc near
		mov	ax, 4000h
		cmp	word ptr [si+8], 0C001h
		jle	short emu086_10B06
		cmp	word ptr [si+8], 4001h
		jge	short emu086_10B0B

emu086_10AFA:
		mov	ax, 100h
		cmp	byte ptr [si+0Ah], 1
		jz	short emu086_10B06
		mov	ax, 0

emu086_10B06:
		mov	ds:__emu+1, ah
		retn

emu086_10B0B:
		mov	dx, [si+6]
		and	dh, 7Fh
		or	dx, [si]
		or	dx, [si+2]
		or	dx, [si+4]
		jz	short emu086_10AFA
		mov	ch, 1
		call	emu086_12759
		mov	ax, 4500h
		jmp	short emu086_10B06
emu086_10AE9	endp


emu086_10B25	proc near
		mov	ax, 4000h
		cmp	word ptr [si+8], 0C001h
		jle	short emu086_10B42
		cmp	word ptr [si+8], 4001h
		jge	short emu086_10B47
		mov	ax, 400h

emu086_10B39:
		cmp	byte ptr [si+0Ah], 1
		jnz	short emu086_10B42
		or	ax, 200h

emu086_10B42:
		mov	ds:__emu+1, ah
		retn

emu086_10B47:
		mov	ax, 500h
		mov	dx, [si+6]
		and	dh, 7Fh
		or	dx, [si]
		or	dx, [si+2]
		or	dx, [si+4]
		jz	short emu086_10B39
		mov	ax, 100h
		jmp	short emu086_10B39
emu086_10B25	endp



emu086_10B5F	proc near
		mov	ax, [si+4]
		mov	dx, [si+6]
		mov	bx, [si+8]
		mov	cl, [si+0Ah]
		cmp	word ptr [si], 0
		jnz	short emu086_10B7F
		cmp	word ptr [si+2], 0
		jnz	short emu086_10B7F
		test	al, 7Fh
		jnz	short emu086_10B7F
		test	ah, 1
		jz	short emu086_10B8E

emu086_10B7F:
		add	al, al
		adc	ah, 0
		adc	dx, 0
		jnb	short emu086_10B8E
		rcr	dx, 1
		rcr	ax, 1
		inc	bx

emu086_10B8E:
		add	bx, 7Eh	; '~'
		jle	short emu086_10BC5
		cmp	bx, 0FFh
		jge	short emu086_10BB0

emu086_10B99:
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

emu086_10BB0:
		cmp	word ptr [si+8], 4001h
		jge	short emu086_10BC0
		mov	ch, 8
		call	emu086_12759
		sub	dx, dx
		sub	ax, ax

emu086_10BC0:
		mov	bx, 0FFh
		jmp	short emu086_10B99

emu086_10BC5:
		cmp	word ptr [si+8], 0C001h
		jle	short emu086_10BD1
		mov	ch, 10h
		call	emu086_12759

emu086_10BD1:
		sub	bx, bx
		mov	dx, bx
		mov	ax, bx
		jmp	short emu086_10B99
emu086_10B5F	endp


emu086_10BD9	proc near
		mov	ax, es:[si]
		mov	dx, es:[si+2]
		push	si
		sub	si, si
		shl	dx, 1
		rcl	si, 1
		sub	bx, bx
		add	bl, dh
		jz	short emu086_10C1B
		cmp	dh, 0FFh
		jz	short emu086_10C16
		sub	bx, 7Eh	; '~'

emu086_10BF5:
		stc
		rcr	dl, 1

emu086_10BF8:
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

emu086_10C16:
		mov	bx, 4001h
		jmp	short emu086_10BF5

emu086_10C1B:
		mov	cx, dx
		or	cx, ax
		jz	short emu086_10C2F
		sub	bx, 7Eh	; '~'
		shr	dl, 1

emu086_10C26:
		add	ax, ax
		adc	dl, dl
		js	short emu086_10BF8
		dec	bx
		jmp	short emu086_10C26

emu086_10C2F:
		mov	bx, 0C001h
		jmp	short emu086_10BF8
emu086_10BD9	endp

		mov	es, cx

emu086_10C36	proc near
		push	di
		mov	ax, [si+1]
		mov	di, [si+3]
		mov	cx, [si+5]
		mov	dl, [si+7]
		mov	bx, [si+8]
		mov	dh, 3
		and	dh, al
		or	dh, [si]
		jnz	short emu086_10C52
		test	al, 8
		jz	short emu086_10C63

emu086_10C52:
		add	ax, 4
		adc	di, 0
		adc	cx, 0
		adc	dl, 0
		jnb	short emu086_10C63
		rcr	dl, 1
		inc	bx

emu086_10C63:
		add	bx, 3FEh
		jle	short emu086_10CAB
		cmp	bx, 7FFh
		jge	short emu086_10CB8

emu086_10C6F:
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

emu086_10C9E:
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

emu086_10CAB:
		sub	dx, dx
		cmp	word ptr [si+8], 0C001h
		jle	short emu086_10CC7
		mov	ch, 10h
		jmp	short emu086_10CC4

emu086_10CB8:
		cmp	word ptr [si+8], 4001h
		jge	short emu086_10CD4
		mov	dx, 0FFE0h
		mov	ch, 8

emu086_10CC4:
		call	emu086_12759

emu086_10CC7:
		or	dl, [si+0Ah]
		ror	dx, 1
		sub	cx, cx
		mov	bx, cx
		mov	ax, cx
		jmp	short emu086_10C9E

emu086_10CD4:
		mov	bx, 7FFh
		jmp	short emu086_10C6F
emu086_10C36	endp

		mov	si, bx
		mov	es, ax

emu086_10CDD	proc near
		mov	dx, es:[si+6]
		mov	cx, 5
		shl	dx, 1
		rcl	ch, 1
		mov	[di+0Ah], ch
		shr	dx, cl
		jz	short emu086_10D52
		cmp	dx, 7FFh
		jz	short emu086_10D38
		mov	bl, 10h
		sub	dx, 3FEh

emu086_10CFB:
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

emu086_10D2C:
		mov	[di], ax
		mov	[di+2],	bx
		mov	[di+4],	cx
		mov	[di+6],	dx
		retn

emu086_10D38:
		mov	bx, 0Fh
		and	bl, es:[si+6]
		or	bx, es:[si+4]
		or	bx, es:[si+2]
		or	bx, es:[si]
		mov	dx, 4001h
		or	bl, 10h
		jmp	short emu086_10CFB

emu086_10D52:
		mov	bx, 0Fh
		and	bl, es:[si+6]
		or	bx, es:[si+4]
		or	bx, es:[si+2]
		or	bx, es:[si]
		jnz	short emu086_10D6B
		mov	dx, 0C001h
		jmp	short emu086_10CFB

emu086_10D6B:
		mov	dx, es:[si+5]
		and	dh, 0Fh
		mov	cx, es:[si+3]
		mov	bx, es:[si+1]
		mov	ah, es:[si]
		mov	al, 4

emu086_10D7F:
		dec	al
		shl	ah, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx
		jns	short emu086_10D7F
		push	ax
		mov	ah, 0
		sub	ax, 4FEh
		mov	[di+8],	ax
		pop	ax
		mov	al, 0
		jmp	short emu086_10D2C
emu086_10CDD	endp

		mov	es, cx

emu086_10D9B	proc near
		cld
		movsw
		movsw
		movsw
		movsw
		lodsw
		mov	cl, [si]
		cmp	ax, 4001h
		jge	short emu086_10DBB
		add	ax, 3FFEh
		jl	short emu086_10DC0

emu086_10DAD:
		shl	ax, 1
		shr	cl, 1
		rcr	ax, 1
		stosw
		sub	di, 0Ah
		sub	si, 0Ah
		retn

emu086_10DBB:
		mov	ax, 7FFFh
		jmp	short emu086_10DAD

emu086_10DC0:
		sub	ax, ax
		jmp	short emu086_10DAD
emu086_10D9B	endp

		mov	si, bx
		mov	es, ax

emu086_10DC8	proc near
		push	si
		mov	cx, ds
		mov	dx, es
		mov	es, cx
		mov	ds, dx
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
		jz	short emu086_10DF9
		sub	bx, 3FFEh
		xchg	ax, bx
		stosw
		movsw
		movsw
		movsw
		movsw

emu086_10DF0:
		cld
		mov	es, dx
		mov	ds, cx
		inc	di
		inc	di
		pop	si
		retn

emu086_10DF9:
		mov	ax, 0C001h
		stosw
		sub	ax, ax
		stosw
		stosw
		stosw
		stosw
		jmp	short emu086_10DF0
emu086_10DC8	endp

byte_10E05	db 0, 0, 0, 0, 0, 0, 0,	80h, 1,	0, 0
		db ?

emu086_10E11	proc near
		mov	ax, offset byte_10E05
		jmp	short emu086_10E7A
emu086_10E11	endp

byte_10E16	db 0FEh, 8Ah, 1Bh, 0CDh, 4Bh, 78h, 9Ah,	0D4h, 2, 0, 0
		db ?

emu086_10E22	proc near
		mov	ax, offset byte_10E16
		jmp	short emu086_10E7A
emu086_10E22	endp

byte_10E27	db 0BBh, 0F0h, 17h, 5Ch, 29h, 3Bh, 0AAh, 0B8h, 1, 0, 0
		db ?

emu086_10E33	proc near
		mov	ax, offset byte_10E27
		jmp	short emu086_10E7A
emu086_10E33	endp

byte_10E38	db 35h,	0C2h, 68h, 21h,	0A2h, 0DAh, 0Fh, 0C9h, 2, 0, 0
		db ?

emu086_10E44	proc near
		mov	ax, offset byte_10E38
		jmp	short emu086_10E7A
emu086_10E44	endp

byte_10E49	db 99h,	0F7h, 0CFh, 0FBh, 84h, 9Ah, 20h, 9Ah, 0FFh, 0FFh
		db 0, ?

emu086_10E55	proc near
		mov	ax, offset byte_10E49
		jmp	short emu086_10E7A
emu086_10E55	endp

byte_10E5A	db 0ACh, 79h, 0CFh, 0D1h, 0F7h,	17h, 72h, 0B1h,	0, 0, 0
		db ?

emu086_10E66	proc near
		mov	ax, offset byte_10E5A
		jmp	short emu086_10E7A
emu086_10E66	endp

byte_10E6B	db 0, 0, 0, 0, 0, 0, 0,	0, 1, 0C0h, 0
		db ?

emu086_10E77	proc near
		mov	ax, offset byte_10E6B

emu086_10E7A:
		push	ds
		mov	cx, cs
		mov	ds, cx
		xchg	ax, si
		cld
		mov	cx, 5
		rep movsw
		movsb
		sub	di, 0Bh
		xchg	ax, si
		pop	ds
		retn
emu086_10E77	endp


emu086_10E8D	proc near
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
emu086_10E8D	endp


emu086_10EA3	proc near
		mov	ch, 1
		call	emu086_12759
		push	di
		sub	ax, ax
		cld
		stosw
		stosw
		stosw
		mov	ah, 0C0h ; 'À'
		stosw
		mov	ax, 4001h
		stosw
		mov	al, 1
		stosb
		pop	di
		retn
emu086_10EA3	endp


emu086_10EBB	proc near
		push	di
		push	es
		mov	di, ss
		mov	es, di
		sub	word ptr ds:__emu+0Dh, 0Ch
		mov	di, word ptr ds:__emu+0Dh
		cld
		mov	cx, 5
		rep movsw
		movsb
		pop	es
		pop	di
		sub	si, 0Bh
		retn
emu086_10EBB	endp


emu086_10ED7	proc near
		push	si
		push	di
		sub	word ptr ds:__emu+0Dh, 0Ch
		mov	di, word ptr ds:__emu+0Dh
		push	ds
		push	es
		push	ds
		pop	es
		push	cs
		pop	ds
		cld
		mov	cx, 5
		rep movsw
		movsb
		pop	es
		pop	ds
		pop	di
		pop	si
		retn
emu086_10ED7	endp


emu086_10EF4	proc near
		push	si
		mov	si, word ptr ds:__emu+0Dh
		cld
		mov	cx, 5
		rep movsw
		movsb
		inc	si
		mov	word ptr ds:__emu+0Dh, si
		sub	di, 0Bh
		pop	si
		retn
emu086_10EF4	endp


emu086_10F0A	proc near
		push	si
		push	di
		push	es
		mov	si, word ptr ds:__emu+0Dh
		lea	di, [si-0Ch]
		mov	word ptr ds:__emu+0Dh, di
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
emu086_10F0A	endp


emu086_10F27	proc near
		push	si
		push	di
		mov	si, word ptr ds:__emu+0Dh
		mov	di, si
		cld
		push	es
		mov	cx, ss
		mov	es, cx
		mov	cx, 5

emu086_10F38:
		lodsw
		xchg	ax, [di+0Ch]
		stosw
		loop	emu086_10F38
		lodsb
		xchg	al, [di+0Ch]
		stosb
		pop	es
		pop	di
		pop	si
		retn
emu086_10F27	endp


emu086_10F48	proc near
		mov	ax, es:[si]
		sub	cx, cx
		cwd
		xor	ax, dx
		sub	ax, dx
		jz	short emu086_10F86
		and	dl, 1

emu086_10F57:
		mov	bx, cx
		xchg	ax, cx
		shl	ax, 1

emu086_10F5C:
		rcr	ax, 1
		inc	bx
		shr	cx, 1
		rcr	ax, 1
		jcxz	short emu086_10F6C
		inc	bx
		shr	cx, 1
		jnz	short emu086_10F5C
		rcr	ax, 1

emu086_10F6C:
		mov	[di+0Ah], dl
		mov	[di+8],	bx
		mov	[di+6],	ax
		mov	[di+4],	cx
		mov	[di+2],	cx
		mov	[di], cx
		retn
		sub	cx, cx
		mov	dx, cx
		or	ax, ax
		jnz	short emu086_10F57

emu086_10F86:
		mov	bx, 0C001h
		jmp	short emu086_10F6C
emu086_10F48	endp


emu086_10F8B	proc near
		mov	cx, [si+8]
		cmp	cx, 10h

emu086_10F91:
		jg	short emu086_11003
		cmp	cx, 0C001h
		jle	short emu086_1100D
		mov	bx, [si+6]
		sub	ax, ax
		or	cx, cx
		jge	short emu086_10FA6
		shr	bx, 1
		rcr	dx, 1

emu086_10FA6:
		mov	dx, [si+4]
		or	cx, cx
		jle	short emu086_10FB5

emu086_10FAD:
		shl	dx, 1
		rcl	bx, 1
		rcl	ax, 1
		loop	emu086_10FAD

emu086_10FB5:
		or	dx, [si]
		or	dx, [si+2]
		or	bl, dh
		or	bl, dl
		mov	cl, 0Ch
		and	cl, ds:__emu+3
		cmp	cl, 0Ch
		jz	short emu086_10FF3
		cmp	cl, 0
		jz	short emu086_10FE4
		add	cl, [si+0Ah]
		cmp	cl, 4
		jz	short emu086_10FF3
		cmp	cl, 9
		jz	short emu086_10FF3
		neg	bx
		adc	ax, 0
		jb	short emu086_11003
		jmp	short emu086_10FF3

emu086_10FE4:
		mov	dl, 1
		and	dl, al
		or	bl, dl
		add	bx, 7FFFh
		adc	ax, 0
		jb	short emu086_11003

emu086_10FF3:
		cmp	byte ptr [si+0Ah], 1
		jz	short emu086_11011
		sahf
		jns	short emu086_11017
		cmp	ds:__emu+3Ch, 1
		jz	short emu086_11017

emu086_11003:
		mov	ch, 8
		call	emu086_12759
		mov	ax, 8000h
		jmp	short emu086_11017

emu086_1100D:
		sub	ax, ax
		jmp	short emu086_11017

emu086_11011:
		neg	ax
		jz	short emu086_11017
		jns	short emu086_11003

emu086_11017:
		mov	ds:__emu+3Ch, 0
		mov	es:[di], ax
		retn
emu086_10F8B	endp


emu086_11020	proc near
		mov	ds:__emu+3Ch, 1
		mov	cx, [si+8]
		cmp	cx, 10h
		jmp	emu086_10F91
emu086_11020	endp


emu086_1102E	proc near
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
		jle	short locret_11053
		cmp	word ptr [si], 4001h
		jge	short emu086_11054
		dec	word ptr [si]
		call	emu086_10F48
		mov	word ptr [si], 1

locret_11053:
		retn

emu086_11054:
		mov	word ptr [si], 0C001h
		mov	word ptr [di+8], 0Dh
		mov	byte ptr [di+7], 80h ; '€'
		jmp	short locret_11053
emu086_1102E	endp


emu086_11063	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	cx, [si+8]
		cmp	cx, 0Fh
		jg	short emu086_11078
		or	cx, cx
		jg	short emu086_11082
		sub	ax, ax
		jmp	short emu086_11094

emu086_11078:
		mov	ch, 8
		call	emu086_12759
		mov	ax, 7FFFh
		jmp	short emu086_1108C

emu086_11082:
		mov	ax, [si+6]
		neg	cl
		add	cl, 10h
		shr	ax, cl

emu086_1108C:
		cmp	byte ptr [si+0Ah], 1
		jnz	short emu086_11094
		neg	ax

emu086_11094:
		mov	cx, [di+8]
		cmp	cx, 0C001h
		jle	short emu086_110B2
		cmp	cx, 4001h
		jge	short emu086_110B2
		add	ax, cx
		cmp	ax, 0C001h
		jle	short emu086_110C0
		cmp	ax, 4001h
		jge	short emu086_110B6
		mov	[di+8],	ax

emu086_110B2:
		pop	di
		pop	si
		pop	bp
		retn

emu086_110B6:
		mov	ch, 8
		call	emu086_12759
		mov	ax, 4001h
		jmp	short emu086_110C8

emu086_110C0:
		mov	ch, 10h
		call	emu086_12759
		mov	ax, 0C001h

emu086_110C8:
		call	emu086_10E8D
		jmp	short emu086_110B2
emu086_11063	endp


emu086_110CD	proc near
		mov	cx, dx
		xchg	ax, bx
		jmp	short emu086_110E1
emu086_110CD	endp


emu086_110D2	proc near
		mov	cx, dx
		xchg	ax, bx
		mov	dx, 0
		jmp	short emu086_110F3
emu086_110D2	endp


emu086_110DA	proc near
		mov	bx, es:[si]
		mov	cx, es:[si+2]

emu086_110E1:
		sub	ax, ax
		mov	dx, 0
		or	cx, cx
		jns	short emu086_110F3
		not	cx
		neg	bx
		sbb	cx, 0FFFFh
		mov	dl, 1

emu086_110F3:
		mov	[di+0Ah], dl
		mov	dl, 10h
		or	cx, cx
		jnz	short emu086_11108
		xchg	bx, cx
		mov	dl, 0
		jcxz	short emu086_11120
		jmp	short emu086_11108

emu086_11104:
		rcr	bx, 1
		rcr	ax, 1

emu086_11108:
		inc	dx
		shr	cx, 1
		jnz	short emu086_11104
		rcr	bx, 1
		rcr	ax, 1

emu086_11111:
		mov	[di+8],	dx
		mov	[di+6],	bx
		mov	[di+4],	ax
		mov	[di+2],	cx
		mov	[di], cx
		retn

emu086_11120:
		mov	dx, 0C001h
		jmp	short emu086_11111
emu086_110DA	endp


emu086_11125	proc near
		mov	ds:__emu+3Ch, 1
		mov	cx, [si+8]
		cmp	cx, 20h	; ' '
		jmp	short emu086_11138
emu086_11125	endp


emu086_11132	proc near
		mov	cx, [si+8]
		cmp	cx, 20h	; ' '

emu086_11138:
		jg	short emu086_1116D
		or	cx, cx
		jge	short emu086_1117A
		cmp	cx, 0C001h
		jle	short emu086_11157
		mov	bl, 0Ch
		and	bl, ds:__emu+3
		add	bl, [si+0Ah]
		cmp	bl, 5
		jz	short emu086_1115D
		cmp	bl, 8
		jz	short emu086_1115D

emu086_11157:
		sub	dx, dx
		mov	ax, dx
		jmp	short emu086_11177

emu086_1115D:
		sub	dx, dx
		mov	ax, 1
		cmp	bl, 5
		jnz	short emu086_11177
		neg	ax
		not	dx
		jmp	short emu086_11177

emu086_1116D:
		mov	ch, 8
		call	emu086_12759
		mov	dx, 8000h
		sub	ax, ax

emu086_11177:
		jmp	emu086_11211

emu086_1117A:
		mov	bx, [si+2]
		or	bl, [si]
		or	bl, [si+1]
		mov	ax, [si+4]
		mov	dx, [si+6]
		sub	cl, 10h
		ja	short emu086_1119D

emu086_1118D:
		or	al, bl
		or	al, bh
		xchg	ax, bx
		xchg	ax, dx
		sub	dx, dx
		add	cl, 10h
		jle	short emu086_1118D
		and	cl, 0Fh

emu086_1119D:
		jcxz	short emu086_111BC
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

emu086_111BC:
		mov	cl, 0Ch
		and	cl, ds:__emu+3
		cmp	cl, 0Ch
		jz	short emu086_11204
		cmp	cl, 0
		jz	short emu086_111DF
		add	cl, [si+0Ah]
		cmp	cl, 4
		jz	short emu086_11204
		cmp	cl, 9
		jz	short emu086_11204
		neg	bx
		jb	short emu086_111E9
		jmp	short emu086_11204

emu086_111DF:
		mov	cl, 1
		and	cl, al
		or	bl, cl
		add	bx, 7FFFh

emu086_111E9:
		adc	ax, 0
		adc	dx, 0
		jns	short emu086_11204
		cmp	byte ptr [si+0Ah], 1
		jnz	short emu086_11201
		cmp	dx, 8000h
		jnz	short emu086_11201
		or	ax, ax
		jz	short emu086_11204

emu086_11201:
		jmp	emu086_1116D

emu086_11204:
		cmp	byte ptr [si+0Ah], 1
		jnz	short emu086_11211
		not	dx
		neg	ax
		sbb	dx, 0FFFFh

emu086_11211:
		mov	ds:__emu+3Ch, 0
		mov	es:[di], ax
		mov	es:[di+2], dx
		retn
emu086_11132	endp


emu086_1121E	proc near
		push	bp
		push	si
		mov	ax, es:[si]
		mov	bx, es:[si+2]
		mov	cx, es:[si+4]
		mov	dx, es:[si+6]
		mov	bp, 0
		or	dx, dx
		jl	short emu086_11249
		jg	short emu086_1125E
		or	cx, cx
		jnz	short emu086_1125E
		or	bx, bx
		jnz	short emu086_1125E
		or	ax, ax
		jnz	short emu086_1125E
		mov	si, 0C001h
		jmp	short emu086_1127C

emu086_11249:
		not	dx
		not	cx
		not	bx
		neg	ax
		cmc
		adc	bx, 0
		adc	cx, 0
		adc	dx, 0
		mov	bp, 1

emu086_1125E:
		mov	si, 40h	; '@'

emu086_11261:
		or	dx, dx
		jnz	short emu086_1126F
		xchg	dx, cx
		xchg	cx, bx
		xchg	ax, bx
		sub	si, 10h
		jmp	short emu086_11261

emu086_1126F:
		js	short emu086_1127C

emu086_11271:
		dec	si
		add	ax, ax
		adc	bx, bx
		adc	cx, cx
		adc	dx, dx
		jns	short emu086_11271

emu086_1127C:
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
emu086_1121E	endp


emu086_11291	proc near
		push	bp
		push	di
		mov	cx, [si+8]
		cmp	cx, 3Fh	; '?'
		jg	short emu086_112D4
		or	cx, cx
		jge	short emu086_112E5
		cmp	cx, 0C001h
		jle	short emu086_112B8
		mov	bl, 0Ch
		and	bl, ds:__emu+3
		add	bl, [si+0Ah]
		cmp	bl, 5
		jz	short emu086_112BC
		cmp	bl, 8
		jz	short emu086_112BC

emu086_112B8:
		sub	bp, bp
		jmp	short emu086_112DC

emu086_112BC:
		sub	bp, bp
		mov	dx, bp
		mov	ax, 1
		cmp	bl, 5
		mov	bx, bp
		jnz	short emu086_112E2
		neg	ax
		not	bx
		not	dx
		not	bp
		jmp	short emu086_112E2

emu086_112D4:
		mov	ch, 8
		call	emu086_12759
		mov	bp, 8000h

emu086_112DC:
		sub	dx, dx
		mov	bx, dx
		mov	ax, bx

emu086_112E2:
		jmp	emu086_11376

emu086_112E5:
		mov	bp, [si+6]
		mov	dx, [si+4]
		mov	bx, [si+2]
		mov	di, [si]
		sub	ax, ax
		sub	cl, 30h	; '0'
		ja	short emu086_1130D

emu086_112F7:
		or	al, ah
		mov	ah, 0
		or	ax, di
		mov	di, bx
		mov	bx, dx
		mov	dx, bp
		sub	bp, bp
		add	cl, 10h
		jle	short emu086_112F7
		and	cl, 0Fh

emu086_1130D:
		neg	cl
		jz	short emu086_11322
		add	cl, 10h

emu086_11314:
		or	al, ah
		shr	bp, 1
		rcr	dx, 1
		rcr	bx, 1
		rcr	di, 1
		rcr	ah, 1
		loop	emu086_11314

emu086_11322:
		mov	cl, 0Ch
		and	cl, ds:__emu+3
		cmp	cl, 0Ch
		jz	short emu086_1135D
		cmp	cl, 0
		jz	short emu086_11347
		add	cl, [si+0Ah]
		cmp	cl, 4
		jz	short emu086_1135D
		cmp	cl, 9
		jz	short emu086_1135D
		neg	ax
		jb	short emu086_11350
		jmp	short emu086_1135D

emu086_11345:
		jmp	short emu086_112D4

emu086_11347:
		mov	cl, 1
		and	cx, di
		or	al, cl
		add	ax, 7FFFh

emu086_11350:
		mov	cx, 0
		adc	di, cx
		adc	bx, cx
		adc	dx, cx
		adc	bp, cx
		js	short emu086_11345

emu086_1135D:
		xchg	ax, di
		cmp	byte ptr [si+0Ah], 1
		jnz	short emu086_11376
		not	bp
		not	dx
		not	bx
		neg	ax
		cmc
		adc	bx, 0
		adc	dx, 0
		adc	bp, 0

emu086_11376:
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
emu086_11291	endp

		mov	si, word ptr ds:__emu+0Dh

emu086_11387	proc near
		push	bp
		push	si
		push	di
		xchg	bp, si
		mov	cx, [bp+8]
		cmp	cx, 40h	; '@'
		jge	short emu086_113C5
		or	cx, cx
		jge	short emu086_113E2
		cmp	cx, 0C001h
		jle	short emu086_113B6
		mov	ch, 20h	; ' '
		call	emu086_12759
		mov	cl, 0Ch
		and	cl, ds:__emu+3
		add	cl, [bp+0Ah]
		cmp	cl, 5
		jz	short emu086_113BD
		cmp	cl, 8
		jz	short emu086_113BD

emu086_113B6:
		sub	bx, bx
		mov	si, 0C001h
		jmp	short emu086_113CE

emu086_113BD:
		mov	si, 1
		mov	bx, 8000h
		jmp	short emu086_113CE

emu086_113C5:
		jz	short emu086_113DF
		mov	ch, 20h	; ' '
		call	emu086_12759
		jmp	short emu086_113DF

emu086_113CE:
		sub	ax, ax
		mov	[bp+0],	ax
		mov	[bp+2],	ax
		mov	[bp+4],	ax
		mov	[bp+6],	bx
		mov	[bp+8],	si

emu086_113DF:
		jmp	emu086_11492

emu086_113E2:
		mov	si, 38h	; '8'
		and	si, cx
		xor	cx, si
		shr	si, 1
		shr	si, 1
		shr	si, 1
		neg	si
		add	si, 7
		cmp	si, 7
		jnz	short emu086_113FF
		mov	ah, 0
		mov	al, [bp+si]
		jmp	short emu086_11401

emu086_113FF:
		mov	ax, [bp+si]

emu086_11401:
		sub	bx, bx
		mov	di, si

emu086_11405:
		dec	di
		jl	short emu086_1140E
		or	bl, [bp+di]
		mov	[bp+di], bh
		jmp	short emu086_11405

emu086_1140E:
		mov	dx, 0FFh
		and	cl, 7
		shr	dx, cl
		mov	di, dx
		inc	di
		and	dx, ax
		jnz	short emu086_11421
		or	bl, bl
		jz	short emu086_11492

emu086_11421:
		mov	ch, 20h	; ' '
		call	emu086_12759
		xor	ax, dx
		mov	cl, 0Ch
		and	cl, ds:__emu+3
		cmp	cl, 0Ch
		jz	short emu086_1144B
		cmp	cl, 0
		jz	short emu086_11456
		add	cl, [bp+0Ah]
		cmp	cl, 4
		jz	short emu086_1144B
		cmp	cl, 9
		jz	short emu086_1144B
		or	bl, dl
		jnz	short emu086_1146C
		jmp	short emu086_11492

emu086_1144B:
		mov	[bp+si], al
		cmp	byte ptr [bp+7], 0
		jnz	short emu086_11492
		jmp	emu086_113B6

emu086_11456:
		or	bl, bl
		jnz	short emu086_11466
		test	ax, di
		jnz	short emu086_11466
		add	dx, dx
		cmp	dx, di
		jbe	short emu086_1144B
		jmp	short emu086_1146C

emu086_11466:
		add	dx, dx
		cmp	dx, di
		jb	short emu086_1144B

emu086_1146C:
		sub	si, 7
		jl	short emu086_1147A
		add	ax, di
		mov	[bp+si+7], al
		neg	ah
		jmp	short emu086_11489

emu086_1147A:
		add	ax, di
		mov	[bp+si+7], ax
		inc	si

emu086_11480:
		inc	si
		jg	short emu086_11489
		adc	byte ptr [bp+si+7], 0
		jb	short emu086_11480

emu086_11489:
		jnb	short emu086_11492
		stc
		rcr	word ptr [bp+6], 1
		inc	word ptr [bp+8]

emu086_11492:
		pop	di
		pop	si
		pop	bp
		retn
emu086_11387	endp


emu086_11496	proc near
		push	bp
		push	si
		push	di
		mov	bp, word ptr ds:__emu+0Dh
		mov	ax, [bp+0]
		mov	bx, [bp+2]
		mov	cx, [bp+4]
		mov	dx, [bp+6]
		sub	di, di
		mov	si, [bp+8]
		cmp	si, 0C001h
		jz	short emu086_114D5
		cmp	si, 0FFF0h
		jg	short emu086_114C6
		mov	di, ax
		mov	ax, bx
		mov	bx, cx
		mov	cx, dx
		sub	dx, dx
		add	si, 10h

emu086_114C6:
		inc	si
		jg	short emu086_114D5
		shr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ax, 1
		rcr	di, 1
		jmp	short emu086_114C6

emu086_114D5:
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
		jz	short emu086_11504
		mov	bx, [bp+0]
		mov	cx, [bp+2]
		shl	bx, 1
		rcl	cx, 1

emu086_11504:
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
emu086_11496	endp


emu086_1159E	proc near
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
		call	emu086_10ED7
		mov	di, si

emu086_115B6:
		dec	byte ptr [bp+arg_2]
		jle	short emu086_11633
		push	bp
		mov	bp, word ptr ds:__emu+0Dh
		mov	al, [bp+arg_12]
		xor	[bp+arg_6], al
		call	emu086_103A3
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
		jz	short emu086_11624
		sub	bx, [bp+0]
		sbb	cx, [bp+2]
		sbb	dx, [bp+arg_0]
		sbb	si, [bp+arg_2]
		jnb	short emu086_11612
		not	si
		not	dx
		not	cx
		neg	bx
		cmc
		adc	cx, 0
		adc	dx, 0
		adc	si, 0
		xor	al, 1

emu086_11612:
		mov	[bp+0],	bx
		mov	[bp+2],	cx
		mov	[bp+arg_0], dx
		mov	[bp+arg_2], si
		mov	[bp+arg_6], al
		pop	bp
		jmp	short emu086_115B6

emu086_11624:
		add	[bp+0],	bx
		adc	[bp+2],	cx
		adc	[bp+arg_0], dx
		adc	[bp+arg_2], si
		pop	bp
		jmp	short emu086_115B6

emu086_11633:
		mov	si, word ptr ds:__emu+0Dh
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
		mov	word ptr ds:__emu+0Dh, si
		xchg	si, di
		sub	di, di
		cmp	al, 1
		jnz	short emu086_11660
		not	si
		not	dx
		not	cx
		neg	bx
		cmc
		adc	cx, di
		adc	dx, di
		adc	si, di
		jmp	short emu086_11672

emu086_11660:
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

emu086_11672:
		mov	ax, word ptr ds:__emu+0Dh
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
emu086_1159E	endp

word_1168B	dw 8
word_1168D	dw 0
		dw 0
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 0AAB6h
		dw 0AAAAh
		dw 0AAAAh
		dw 2AAAh
		dw 0
		db 1
		db ?
		dw 2403h
		dw 2222h
		dw 2222h
		dw 222h
		dw 0
		db 0
		db ?
		dw 0E4B3h
		dw 0D00h
		dw 0D0h
		dw 0Dh
		dw 0
		db 1
		db ?
		dw 86Eh
		dw 0C74Bh
		dw 2E3Bh
		dw 0
		dw 0
		db 0
		db ?
		dw 40C6h
		dw 9916h
		dw 6Bh
		dw 0
		dw 0
		db 1
		db ?
		dw 450Ch
		dw 0B092h
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 45D5h
		dw 0D6h
		dw 0
		dw 0
		dw 0
		db 1
		db ?
word_116ED	dw 8
word_116EF	dw 0
		dw 0
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 0FF88h
		dw 0FFFFh
		dw 0FFFFh
		dw 7FFFh
		dw 0
		db 1
		db ?
		dw 9AA6h
		dw 0AAAAh
		dw 0AAAAh
		dw 0AAAh
		dw 0
		dw ?
		dw 0E67Fh
		dw 5B04h
		dw 5B0h
		dw 5Bh
		dw 0
		db 1
		db ?
		dw 26EFh
		dw 19Bh
		dw 0A01Ah
		dw 1
		dw 0
		db 0
		db ?
		dw 0CE1Dh
		dw 93DCh
		dw 49Fh
		dw 0
		dw 0
		db 1
		db ?
		dw 0B10Fh
		dw 0F74Bh
		dw 8
		dw 0
		dw 0
		db 0
		db ?
		dw 0D803h
		dw 0C7Bh
		dw 0
		dw 0
		dw 0
		db 1
		db ?

emu086_1174F	proc near
		call	emu086_10EBB
		call	emu086_11496

emu086_11755:
		push	cs:word_1168B
		mov	ax, offset word_1168D
		push	ax
		call	emu086_1159E
		push	word ptr ds:__emu+0Dh
		push	si
		push	si
		call	emu086_1030D
		add	word ptr ds:__emu+0Dh, 0Ch
		retn
emu086_1174F	endp


emu086_11770	proc near
		call	emu086_11496

emu086_11773:
		push	cs:word_116ED
		mov	ax, offset word_116EF
		push	ax
		call	emu086_1159E
		retn
emu086_11770	endp


emu086_11780	proc near
		call	emu086_10EBB
		call	emu086_11496
		call	emu086_10F0A
		call	emu086_11755
		call	emu086_11773
		retn
emu086_11780	endp

		dw 0C235h
		dw 2168h
		dw 0DAA2h
		dw 0C90Fh
		dw 1
		db 0
		db ?
word_1179C	dw 8
word_1179E	dw 0
		dw 0
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 5557h
		dw 5555h
		dw 5555h
		dw 155h
		dw 0
		db 1
		db ?
		dw 32BEh
		dw 3333h
		dw 3333h
		dw 3
		dw 0
		db 0
		db ?
		dw 1E7Dh
		dw 9249h
		dw 924h
		dw 0
		dw 0
		db 1
		db ?
		dw 0FEBCh
		dw 71C6h
		dw 1Ch
		dw 0
		dw 0
		db 0
		db ?
		dw 0FF5Ch
		dw 5D16h
		dw 0
		dw 0
		dw 0
		db 1
		db ?
		dw 0BBD8h
		dw 13Ah
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 0C0Ah
		dw 4
		dw 0
		dw 0
		dw 0
		db 1
		db ?
word_117FE	dw 0
		dw 0
		dw 0
		dw 0E700h
		dw 0FFFDh
		db 0
		db ?
		dw 0A4BDh
		dw 7BD6h
		dw 64EEh
		dw 0B35Ch
		dw 0FFFFh
		db 0
		db ?
		dw 85B5h
		dw 0FC47h
		dw 3074h
		dw 0A111h
		dw 0
		db 0
		db ?
		dw 0
		dw 0
		dw 0
		dw 8000h
		dw 1
		db 0
		db ?
word_1182E	dw 0FA9Ch
		dw 0B064h
		dw 1DB2h
		dw 0E607h
		dw 0FFFEh
		db 0
		db ?
		dw 0FA9Ch
		dw 0B064h
		dw 1DB2h
		dw 0E607h
		dw 0FFFFh
		db 0
		db ?
		dw 0BBF5h
		dw 44Bh
		dw 5646h
		dw 0AC85h
		dw 0
		db 0
		db ?
word_11852	dw 6EE6h
		dw 1FD9h
		dw 9BDh
		dw 0E9FAh
		dw 0FFFEh
		db 0
		db ?
		dw 7B8Dh
		dw 0BD35h
		dw 845Bh
		dw 0F6DDh
		dw 0FFFFh
		db 0
		db ?
		dw 0D57Fh
		dw 235h
		dw 80DBh
		dw 0CC73h
		dw 0
		db 0
		db ?

emu086_11876	proc near
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		lea	sp, [bp-2]
		push	si
		push	di
		push	si
		push	di
		push	si
		call	emu086_104DA
		mov	[bp+var_2], 0
		mov	di, offset word_117FE

emu086_1188C:
		cmp	[bp+var_2], 3
		jnb	short emu086_118B3
		xchg	si, di
		call	emu086_10ED7
		xchg	di, si
		push	si
		push	word ptr ds:__emu+0Dh
		call	emu086_10A29
		add	word ptr ds:__emu+0Dh, 0Ch
		cmp	ax, 0
		jnz	short emu086_118B3
		inc	[bp+var_2]
		add	di, 0Ch
		jmp	short emu086_1188C

emu086_118B3:
		cmp	[bp+var_2], 0
		jnz	short emu086_118BE
		call	emu086_11929
		jmp	short emu086_11923

emu086_118BE:
		mov	bx, [bp+var_2]
		dec	bx
		mov	bl, cs:byte_10052[bx]
		mov	[bp+var_2], bx
		add	bx, offset word_11852
		mov	di, bx
		xchg	si, di
		call	emu086_10ED7
		xchg	di, si
		push	si
		mov	di, word ptr ds:__emu+0Dh
		push	di
		lea	ax, [di-0Ch]
		mov	word ptr ds:__emu+0Dh, ax
		push	ax
		call	emu086_1013F
		push	si
		push	di
		push	si
		call	emu086_1030D
		call	emu086_10E11
		push	di
		push	si
		push	si
		call	emu086_10143
		push	word ptr ds:__emu+0Dh
		push	si
		push	si
		call	emu086_104DA
		add	word ptr ds:__emu+0Dh, 18h
		call	emu086_11929
		mov	di, [bp+var_2]
		add	di, offset word_1182E
		xchg	si, di
		call	emu086_10ED7
		xchg	di, si
		push	word ptr ds:__emu+0Dh
		push	si
		push	si
		call	emu086_10143
		add	word ptr ds:__emu+0Dh, 0Ch

emu086_11923:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
emu086_11876	endp ; sp-analysis failed


emu086_11929	proc near
		push	si
		push	di
		call	emu086_10EBB
		cmp	word ptr [si+8], 0FFE0h
		jg	short emu086_1193B
		mov	di, si
		call	emu086_10EF4
		jmp	short emu086_1195D

emu086_1193B:
		mov	di, word ptr ds:__emu+0Dh
		add	word ptr [di+8], 3
		call	emu086_11496
		push	cs:word_1179C
		mov	ax, offset word_1179E
		push	ax
		call	emu086_1159E
		push	di
		push	si
		push	si
		call	emu086_1030D
		add	word ptr ds:__emu+0Dh, 0Ch

emu086_1195D:
		pop	di
		pop	si
		retn
emu086_11929	endp

word_11960	dw 0Dh
word_11962	dw 0
		dw 0
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 3
		dw 0
		dw 0
		dw 4000h
		dw 0
		db 0
		db ?
		dw 0AAA9h
		dw 0AAAAh
		dw 0AAAAh
		dw 0AAAh
		dw 0
		db 0
		db ?
		dw 5578h
		dw 5555h
		dw 5555h
		dw 155h
		dw 0
		db 0
		db ?
		dw 2326h
		dw 2222h
		dw 2222h
		dw 22h
		dw 0
		db 0
		db ?
		dw 2B1Ch
		dw 82D8h
		dw 0D82Dh
		dw 2
		dw 0
		db 0
		db ?
		dw 0F9FCh
		dw 4033h
		dw 3403h
		dw 0
		dw 0
		db 0
		db ?
		dw 5214h
		dw 3403h
		dw 340h
		dw 0
		dw 0
		db 0
		db ?
		dw 6C1Eh
		dw 3BC7h
		dw 2Eh
		dw 0
		dw 0
		db 0
		db ?
		dw 0B04Ch
		dw 4FC9h
		dw 2
		dw 0
		dw 0
		db 0
		db ?
		dw 0E91h
		dw 1AE6h
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 7651h
		dw 11Fh
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 2CC5h
		dw 0Bh
		dw 0
		dw 0
		dw 0
		db 0
		db ?

emu086_119FE	proc near
		push	bp
		push	si
		push	di
		mov	bp, word ptr ds:__emu+0Dh
		lea	di, [bp-0Ch]
		mov	word ptr ds:__emu+0Dh, di
		call	emu086_10E66
		push	di
		push	si
		push	si
		call	emu086_1030D
		mov	word ptr ds:__emu+0Dh, bp
		mov	di, [si+8]
		cmp	di, 0FFC0h
		jle	short emu086_11A78
		mov	ax, [si]
		mov	bx, [si+2]
		mov	cx, [si+4]
		mov	dx, [si+6]
		inc	di
		jge	short emu086_11A46

emu086_11A2F:
		shr	dx, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ax, 1
		inc	di
		jl	short emu086_11A2F
		adc	ax, 0
		adc	bx, 0
		adc	cx, 0
		adc	dx, 0

emu086_11A46:
		sub	word ptr ds:__emu+0Dh, 0Ch
		cld
		mov	di, word ptr ds:__emu+0Dh
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
		push	cs:word_11960
		mov	ax, offset word_11962
		push	ax
		call	emu086_1159E
		mov	ax, word ptr ds:__emu+0Dh
		push	ax
		push	si
		push	si
		call	emu086_1030D
		add	word ptr ds:__emu+0Dh, 0Ch

emu086_11A78:
		pop	di
		pop	si
		pop	bp
		retn
emu086_119FE	endp

word_11A7C	dw 0F0BBh
		dw 5C17h
		dw 3B29h
		dw 0B8AAh
		dw 1
		db 0
		db ?
word_11A88	dw 9
word_11A8A	dw 0
		dw 0
		dw 0
		dw 0
		dw 0
		db 0
		db ?
		dw 5568h
		dw 5555h
		dw 5555h
		dw 555h
		dw 0
		db 0
		db ?
		dw 34BAh
		dw 3333h
		dw 3333h
		dw 33h
		dw 0
		db 0
		db ?
		dw 0C3A7h
		dw 9248h
		dw 4924h
		dw 2
		dw 0
		db 0
		db ?
		dw 5D4Dh
		dw 0C722h
		dw 1C71h
		dw 0
		dw 0
		db 0
		db ?
		dw 5624h
		dw 5CEBh
		dw 174h
		dw 0
		dw 0
		db 0
		db ?
		dw 0AD39h
		dw 0B1ECh
		dw 13h
		dw 0
		dw 0
		db 0
		db ?
		dw 0D6FDh
		dw 0F80h
		dw 1
		dw 0
		dw 0
		db 0
		db ?
		dw 7AB5h
		dw 10E4h
		dw 0
		dw 0
		dw 0
		db 0
		db ?

emu086_11AF6	proc near
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
		ja	short emu086_11B1F
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		rcl	dx, 1
		mov	si, 0
		dec	[bp+var_2]
		jmp	short emu086_11B34

emu086_11B1F:
		not	dx
		not	cx
		not	bx
		neg	ax
		cmc
		adc	bx, 0
		adc	cx, 0
		adc	dx, 0
		mov	si, 1

emu086_11B34:
		sub	di, di

emu086_11B36:
		or	dx, dx
		jnz	short emu086_11B53
		xchg	ax, bx
		xchg	ax, cx
		xchg	ax, dx
		sub	di, 10h
		cmp	di, 0FFC0h
		jg	short emu086_11B36
		sub	word ptr ds:__emu+0Dh, 0Ch
		mov	di, word ptr ds:__emu+0Dh
		call	emu086_10E77
		jmp	short emu086_11B80

emu086_11B53:
		js	short emu086_11B60

emu086_11B55:
		dec	di
		shl	ax, 1
		rcl	bx, 1
		rcl	cx, 1
		adc	dx, dx
		jns	short emu086_11B55

emu086_11B60:
		push	si
		push	di
		push	dx
		push	cx
		push	bx
		push	ax
		mov	si, sp
		call	emu086_11BE6
		mov	si, offset word_11A7C
		call	emu086_10ED7
		mov	si, word ptr ds:__emu+0Dh
		mov	ax, sp
		push	si
		push	ax
		push	si
		call	emu086_1030D
		add	sp, 0Ch

emu086_11B80:
		lea	si, [bp+var_2]
		sub	word ptr ds:__emu+0Dh, 0Ch
		mov	di, word ptr ds:__emu+0Dh
		call	emu086_10F48
		lea	si, [di+0Ch]
		push	si
		push	di
		push	di
		call	emu086_10143
		push	di
		push	[bp+var_4]
		push	[bp+var_4]
		call	emu086_1030D
		add	word ptr ds:__emu+0Dh, 18h
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
emu086_11AF6	endp


emu086_11BAD	proc near
var_2		= word ptr -2

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	si, di
		call	emu086_10EBB
		mov	si, word ptr ds:__emu+0Dh
		call	emu086_11BE6
		mov	si, offset word_11A7C
		call	emu086_10ED7
		mov	si, word ptr ds:__emu+0Dh
		push	si
		lea	si, [si+0Ch]
		push	si
		push	si
		call	emu086_1030D
		push	si
		push	[bp+var_2]
		push	[bp+var_2]
		call	emu086_1030D
		add	word ptr ds:__emu+0Dh, 18h
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
emu086_11BAD	endp


emu086_11BE6	proc near
		push	bp
		mov	bp, sp
		push	si
		push	di
		cmp	word ptr [si+8], 0FFC0h
		jle	short emu086_11C37
		sub	word ptr ds:__emu+0Dh, 0Ch
		mov	di, word ptr ds:__emu+0Dh
		call	emu086_10E11
		inc	word ptr [di+8]
		push	si
		push	di
		push	di
		call	emu086_10143
		push	si
		push	di
		push	di
		call	emu086_104DA
		call	emu086_10F0A
		mov	bx, word ptr ds:__emu+0Dh
		add	word ptr [bx+8], 2
		call	emu086_11496
		push	cs:word_11A88
		mov	ax, offset word_11A8A
		push	ax
		call	emu086_1159E
		push	word ptr ds:__emu+0Dh
		push	di
		push	si
		call	emu086_1030D
		inc	word ptr [si+8]
		add	word ptr ds:__emu+0Dh, 18h

emu086_11C37:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retn
emu086_11BE6	endp


emu086_11C3D	proc near
		mov	cl, 0
		jmp	short emu086_11C47

emu086_11C41:
		mov	cl, 2
		jmp	short emu086_11C47

emu086_11C45:
		mov	cl, 4

emu086_11C47:
		mov	es, di
		mov	bp, sp
		mov	di, word ptr ds:__emu+0Dh
		mov	ch, [di+0Ah]
		push	cx
		push	ax
		cmp	word ptr [di+8], 0FFE0h
		jg	short emu086_11C65
		cmp	cl, 2
		jnz	short emu086_11C62
		call	emu086_10E11

emu086_11C62:
		jmp	emu086_11D1F

emu086_11C65:
		cmp	word ptr [di+8], 40h ; '@'
		jle	short emu086_11C76
		call	emu086_10EA3
		mov	word ptr [di+6], 21h ; '!'
		jmp	emu086_11D1F

emu086_11C76:
		mov	byte ptr [di+0Ah], 0
		lea	si, [di-0Ch]
		mov	word ptr ds:__emu+0Dh, si
		xchg	di, si
		call	emu086_10E44
		xchg	di, si
		sub	word ptr [si+8], 2
		call	emu086_10921
		and	al, 7
		mov	[bp-4],	al
		mov	bl, [bp-2]
		cmp	bl, 4
		jz	short emu086_11CD7
		add	bl, [bp-4]
		and	bl, 7
		mov	[bp-4],	bl
		shr	bx, 1
		jnb	short emu086_11CBA
		xchg	di, si
		call	emu086_10E44
		xchg	di, si
		sub	word ptr [si+8], 2
		push	si
		push	di
		push	di
		call	emu086_1013F

emu086_11CBA:
		mov	word ptr ds:__emu+0Dh, di
		mov	si, di
		test	byte ptr [bp-4], 3
		jp	short emu086_11CCB
		call	emu086_11770
		jmp	short emu086_11CCE

emu086_11CCB:
		call	emu086_1174F

emu086_11CCE:
		mov	bl, [bp-4]
		shr	bl, 1
		shr	bl, 1
		jmp	short emu086_11D13

emu086_11CD7:
		test	byte ptr [bp-4], 1
		jz	short emu086_11CEE
		xchg	si, di
		call	emu086_10E44
		xchg	si, di
		sub	word ptr [si+8], 2
		push	si
		push	di
		push	di
		call	emu086_1013F

emu086_11CEE:
		mov	word ptr ds:__emu+0Dh, di
		mov	si, di
		call	emu086_11780
		lea	di, [si-0Ch]
		mov	ax, si
		test	byte ptr [bp-4], 3
		jp	short emu086_11D04
		xchg	si, di

emu086_11D04:
		xchg	ax, di
		push	si
		push	ax
		push	di
		call	emu086_104DA
		mov	bl, [bp-4]
		shr	bl, 1
		and	bl, 1

emu086_11D13:
		cmp	byte ptr [bp-2], 2
		jz	short emu086_11D1C
		xor	bl, [bp-1]

emu086_11D1C:
		mov	[di+0Ah], bl

emu086_11D1F:
		mov	word ptr ds:__emu+0Dh, di
		mov	sp, bp
		retn
emu086_11C3D	endp


emu086_11D26	proc near
		mov	es, di
		mov	si, word ptr ds:__emu+0Dh
		lea	di, [si-0Ch]
		mov	word ptr ds:__emu+0Dh, di
		call	emu086_10E11
		mov	ax, [si+8]
		cmp	ax, 4001h
		jge	short emu086_11D76
		cmp	ax, 0C001h
		jle	short emu086_11D71
		mov	cl, 0
		mov	bx, si
		dec	ax
		jl	short emu086_11D51
		call	emu086_10F27
		mov	bx, di
		mov	cl, 1

emu086_11D51:
		mov	ch, 0
		xchg	ch, [bx+0Ah]
		push	cx
		call	emu086_11876
		pop	cx
		cmp	cl, 1
		jnz	short emu086_11D6E
		push	cx
		call	emu086_10E44
		dec	word ptr [di+8]
		push	di
		push	si
		push	si
		call	emu086_1013F
		pop	cx

emu086_11D6E:
		mov	[si+0Ah], ch

emu086_11D71:
		mov	word ptr ds:__emu+0Dh, si
		retn

emu086_11D76:
		mov	di, si
		push	word ptr [si+0Ah]
		call	emu086_10E44
		pop	ax
		mov	[si+0Ah], al
		dec	word ptr [si+8]
		jmp	short emu086_11D71
emu086_11D26	endp


emu086_11D87	proc near
		mov	es, di
		mov	si, word ptr ds:__emu+0Dh
		lea	di, [si-0Ch]
		mov	word ptr ds:__emu+0Dh, di
		call	emu086_10E66
		jmp	short emu086_11DBB

emu086_11D99:
		mov	es, di
		mov	si, word ptr ds:__emu+0Dh
		lea	di, [si-0Ch]
		mov	word ptr ds:__emu+0Dh, di
		call	emu086_10E11
		jmp	short emu086_11DBB

emu086_11DAB:
		mov	es, di
		mov	si, word ptr ds:__emu+0Dh
		lea	di, [si-0Ch]
		mov	word ptr ds:__emu+0Dh, di
		call	emu086_10E55

emu086_11DBB:
		call	emu086_10F27
		cmp	byte ptr [di+0Ah], 0
		jnz	short emu086_11DDD
		mov	ax, [di+8]
		cmp	ax, 0C001h
		jle	short emu086_11DD9
		cmp	ax, 4001h
		jge	short emu086_11DDD
		call	emu086_11AF6

emu086_11DD4:
		mov	word ptr ds:__emu+0Dh, si
		retn

emu086_11DD9:
		mov	ch, 4
		jmp	short emu086_11DDF

emu086_11DDD:
		mov	ch, 1

emu086_11DDF:
		call	emu086_12759
		mov	ax, 4001h
		mov	di, si
		mov	cl, 0
		call	emu086_10E8D
		cmp	ch, 1
		jnz	short emu086_11DD4
		mov	word ptr [di+6], 0C000h
		jmp	short emu086_11DD4
emu086_11D87	endp



emu086_11DF8	proc near
		mov	ax, offset emu086_10E33
		jmp	short emu086_11E0B

emu086_11DFD:
		mov	es, di
		mov	si, word ptr ds:__emu+0Dh
		lea	di, [si-0Ch]
		jmp	short emu086_11E24

emu086_11E08:
		mov	ax, offset emu086_10E22

emu086_11E0B:
		mov	es, di
		mov	si, word ptr ds:__emu+0Dh
		lea	di, [si-0Ch]
		mov	word ptr ds:__emu+0Dh, di
		call	ax ; emu086_10E33
		push	si
		push	di
		push	si
		call	emu086_1030D
		mov	word ptr ds:__emu+0Dh, si

emu086_11E24:
		mov	bp, sp
		mov	ax, 0
		push	ax
		mov	ax, [si+8]
		cmp	ax, 0Ch
		jg	short emu086_11E80
		cmp	ax, 0FFC0h
		jle	short emu086_11EAC
		call	emu086_10F0A
		inc	word ptr [di+8]
		push	word ptr ds:__emu+2
		and	ds:__emu+3, 0F3h
		or	ds:__emu+3, 4
		mov	si, di
		call	emu086_11387
		pop	word ptr ds:__emu+2
		push	ax
		mov	di, sp
		call	emu086_10F8B
		dec	word ptr [si+8]
		lea	di, [si+0Ch]
		push	di
		push	si
		push	di
		call	emu086_1013F
		pop	ax
		sar	ax, 1
		jnb	short emu086_11EC8
		mov	word ptr [si], 6485h
		mov	word ptr [si+2], 0F9DEh
		mov	word ptr [si+4], 0F333h
		mov	word ptr [si+6], 0B504h
		jmp	short emu086_11EDB

emu086_11E80:
		cmp	ax, 4001h
		jnz	short emu086_11E95
		mov	ax, 7FFFh
		and	ax, [si+6]
		or	ax, [si+4]
		or	ax, [si+2]
		or	ax, [si]
		jnz	short emu086_11EB3

emu086_11E95:
		cmp	byte ptr [si+0Ah], 0
		jnz	short emu086_11EC1
		mov	di, si
		mov	ch, 8
		call	emu086_12759
		mov	ax, 4001h
		mov	cl, 0
		call	emu086_10E8D
		jmp	short emu086_11F01

emu086_11EAC:
		mov	di, si
		call	emu086_10E11
		jmp	short emu086_11F01

emu086_11EB3:
		mov	word ptr [si+6], 0C000h
		mov	di, si
		mov	ch, 1
		call	emu086_12759
		jmp	short emu086_11F01

emu086_11EC1:
		mov	di, si
		call	emu086_10E77
		jmp	short emu086_11F01

emu086_11EC8:
		mov	word ptr [si], 0

emu086_11ECC:
		mov	word ptr [si+2], 0
		mov	word ptr [si+4], 0
		mov	word ptr [si+6], 8000h

emu086_11EDB:
		inc	ax
		mov	[si+8],	ax
		mov	byte ptr [si+0Ah], 0
		mov	di, si
		lea	si, [di+0Ch]
		call	emu086_119FE
		push	si
		push	di
		push	si
		call	emu086_1030D
		push	si
		push	di
		push	si
		call	emu086_10143
		cmp	byte ptr [bp-2], 1
		jnz	short emu086_11F01
		xor	byte ptr [si+0Ah], 1

emu086_11F01:
		mov	word ptr ds:__emu+0Dh, si
		mov	sp, bp
		retn
emu086_11DF8	endp


emu086_11F08	proc near
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
		mov	dx, 0F0h ; 'ð'
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
emu086_11F08	endp


emu086_11F37	proc near
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
		call	emu086_11F08
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
		call	emu086_11F08
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
		call	emu086_11F08
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
		call	emu086_11F08
		add	bx, ax
		adc	cx, 0
		adc	di, 0
		adc	dx, 0
		mov	ax, 40h	; '@'

emu086_11FC8:
		or	dx, dx
		jnz	short emu086_11FD9
		sub	ax, 10h
		jz	short emu086_11FFD
		xchg	dx, di
		xchg	di, cx
		xchg	cx, bx
		jmp	short emu086_11FC8

emu086_11FD9:
		js	short emu086_11FE6

emu086_11FDB:
		dec	ax
		shl	bx, 1
		rcl	cx, 1
		rcl	di, 1
		adc	dx, dx
		jns	short emu086_11FDB

emu086_11FE6:
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

emu086_11FFD:
		mov	ax, 0C001h
		jmp	short emu086_11FE6
emu086_11F37	endp


emu086_12002	proc near
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
emu086_12002	endp


emu086_12020	proc near
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
		jl	short emu086_12071
		sub	ax, 3Ch	; '<'
		jl	short emu086_1205D
		jg	short emu086_12073
		cmp	dx, 0DE0Bh
		jb	short emu086_1205D
		ja	short emu086_12073
		cmp	si, 6B3Ah
		jb	short emu086_1205D
		ja	short emu086_12073
		cmp	cx, 763Fh
		jb	short emu086_1205D
		ja	short emu086_12073
		cmp	bx, 0FFF0h
		ja	short emu086_12073

emu086_1205D:
		mov	ah, 0
		sub	al, 4

emu086_12061:
		add	al, 10h
		jg	short emu086_12075
		mov	ah, bh
		mov	bx, cx
		mov	cx, si
		mov	si, dx
		sub	dx, dx
		jmp	short emu086_12061

emu086_12071:
		jmp	short emu086_120DA

emu086_12073:
		jmp	short emu086_120E3

emu086_12075:
		sub	al, 10h
		jge	short emu086_12087

emu086_12079:
		shr	dx, 1
		rcr	si, 1
		rcr	cx, 1
		rcr	bx, 1
		rcr	ah, 1
		inc	al
		jl	short emu086_12079

emu086_12087:
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
		call	emu086_12002
		sub	dx, dx
		xchg	ax, cx
		div	si
		xchg	ax, bx
		div	si
		xchg	ax, cx
		div	si
		call	emu086_12002
		mov	dx, bx
		xchg	ax, cx
		div	si
		xchg	ax, cx
		div	si
		call	emu086_12002
		mov	dx, cx
		div	si
		call	emu086_12002
		aam
		mov	cl, 4
		shl	ah, cl
		or	al, ah
		stosb

emu086_120CD:
		mov	si, [bp+var_2]
		mov	al, [si+0Ah]
		ror	al, 1
		stosb
		pop	di
		pop	si
		pop	bp
		retn

emu086_120DA:
		mov	al, 0

emu086_120DC:
		mov	cx, 9
		rep stosb
		jmp	short emu086_120CD

emu086_120E3:
		mov	ch, 8
		call	emu086_12759
		mov	al, 99h	; '™'
		jmp	short emu086_120DC
emu086_12020	endp

emu086_120EC	dw offset emu086_121EE
		dw offset emu086_121F8
		dw offset emu086_12202
		dw offset emu086_1220C
		dw offset emu086_12216
		dw offset emu086_1221D
		dw offset emu086_1223B
		dw offset emu086_12224
emu086_120FC	dw offset emu086_125CC
		dw offset e287_FPU_Control
		dw offset emu086_126B1
		dw offset emu086_126B3
emu086_12104	dw offset emu086_10BD9
		dw offset emu086_110DA
		dw offset emu086_10CDD
		dw offset emu086_10F48
emu086_1210C	dw offset emu086_122CC
		dw offset emu086_122D3
		dw offset emu086_122DD
		dw offset emu086_122DA
		dw offset emu086_122E4
		dw offset emu086_122E3
		dw offset emu086_122EC
		dw offset emu086_122EB
emu086_1211C	dw offset emu086_10BD9
		dw offset emu086_110DA
		dw offset emu086_10CDD
		dw offset emu086_10F48
emu086_12124	dw offset emu086_10B5F
		dw offset emu086_11132
		dw offset emu086_10C36
		dw offset emu086_10F8B
emu086_1212C	dw offset emu086_12364
		dw offset emu086_1235E
		dw offset emu086_123C5
		dw offset emu086_12433
		dw offset emu086_1236D
		dw offset emu086_12443
		dw offset emu086_1235E
		dw offset emu086_12423
emu086_1213C	dw offset emu086_12378
		dw offset emu086_1235E
		dw offset emu086_123A1
		dw offset emu086_12460
		dw offset emu086_123F7
		dw offset emu086_1246D
		dw offset emu086_123FC
		dw offset emu086_12453
; START	OF FUNCTION CHUNK FOR e086_Entry

emu086_1214C:
		mov	ch, 1
		call	emu086_12759
		jmp	emu086_126E1

emu086_12154:
		ja	short emu086_1217A
		test	ah, 20h
		jnz	short emu086_1214C
		mov	al, ah
		inc	dx
		mov	di, ds
		and	al, 0C0h
		jz	short emu086_12172
		cmp	al, 80h	; '€'
		mov	di, ss
		jb	short emu086_12172
		mov	di, [bp+0]
		ja	short emu086_12172
		mov	di, [bp+14h]

emu086_12172:
		lods	byte ptr es:[si]
		xchg	ah, al
		and	al, 7
		jmp	short emu086_121B7

emu086_1217A:
		cmp	al, 9
		jnz	short emu086_12192
		mov	ax, es
		xor	ax, word ptr ss:__emu+7
		mov	es, ax
		push	es
		pop	es
		mov	word ptr es:[si-3], 0E489h
		jmp	emu086_126E1

emu086_12192:
		jmp	EmuVectorException
; END OF FUNCTION CHUNK	FOR e086_Entry
		dw offset __emu+35h

		public e086_Entry
e086_Entry	proc far

; FUNCTION CHUNK AT 20FC SIZE 00000049 BYTES
; FUNCTION CHUNK AT 22A3 SIZE 0000006B BYTES
; FUNCTION CHUNK AT 244A SIZE 000000AB BYTES
; FUNCTION CHUNK AT 257C SIZE 00000075 BYTES

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
		mov	word ptr ss:__emu+33h, bp

		public rs1
rs1:
		les	si, [bp+12h]
		mov	dl, 0
		dec	si
		lods	word ptr es:[si]
		sub	al, 34h	; '4'
		cmp	al, 8
		jnb	short emu086_12154

emu086_121B7:
		mov	bx, 0C007h
		and	bl, ah
		and	bh, ah
		xchg	ax, cx
		cmp	bh, 0C0h ; 'À'
		jnb	short emu086_1222B
		cmp	bh, 40h	; '@'
		ja	short emu086_121DB
		jz	short emu086_121DF
		sub	ax, ax
		cmp	bl, 6
		jnz	short emu086_121E2
		lods	word ptr es:[si]
		mov	[bp+12h], si
		mov	si, ds
		jmp	short emu086_12240

emu086_121DB:
		lods	word ptr es:[si]
		jmp	short emu086_121E2

emu086_121DF:
		lods	byte ptr es:[si]
		cbw

emu086_121E2:
		mov	[bp+12h], si
		mov	bh, 0
		shl	bx, 1
		jmp	cs:emu086_120EC[bx]

emu086_121EE:
		add	ax, [bp+0Ah]
		add	ax, [bp+4]
		mov	si, ds
		jmp	short emu086_12240

emu086_121F8:
		add	ax, [bp+0Ah]
		add	ax, [bp+2]
		mov	si, ds
		jmp	short emu086_12240

emu086_12202:
		add	ax, [bp+6]
		add	ax, [bp+4]
		mov	si, ss
		jmp	short emu086_12240

emu086_1220C:
		add	ax, [bp+6]
		add	ax, [bp+2]
		mov	si, ss
		jmp	short emu086_12240

emu086_12216:
		add	ax, [bp+4]
		mov	si, ds
		jmp	short emu086_12240

emu086_1221D:
		add	ax, [bp+2]
		mov	si, ds
		jmp	short emu086_12240

emu086_12224:
		add	ax, [bp+0Ah]
		mov	si, ds
		jmp	short emu086_12240

emu086_1222B:
		mov	[bp+12h], si
		mov	ax, ss
		mov	ds, ax
		mov	es, ax
		test	cl, 1
		jz	short emu086_1226C
		jmp	short emu086_12252

emu086_1223B:
		add	ax, [bp+6]
		mov	si, ss

emu086_12240:
		xchg	ax, si
		cmp	dl, 1
		jnz	short emu086_12247
		xchg	ax, di

emu086_12247:
		mov	es, ax
		mov	ax, ss
		mov	ds, ax
		test	cl, 1
		jz	short emu086_1226C

emu086_12252:
		cmp	ch, 0C0h ; 'À'
		jnb	short emu086_1225A
		jmp	emu086_122F3

emu086_1225A:
		test	ch, 20h
		jnz	short emu086_12262
		jmp	emu086_1249A

emu086_12262:
		mov	bx, 6
		and	bl, cl
		jmp	cs:emu086_120FC[bx]

emu086_1226C:
		mov	ax, 38h	; '8'
		and	al, ch
		shr	ax, 1
		shr	ax, 1
		xchg	ax, bp
		cmp	ch, 0C0h ; 'À'
		jnb	short emu086_122A5
		mov	di, word ptr ds:__emu+0Dh
		sub	di, 0Ch
		mov	word ptr ds:__emu+0Dh, di
		mov	bx, 6
		and	bl, cl
		call	cs:emu086_12104[bx]
		mov	cx, ss
		mov	es, cx
		mov	si, 0Ch
		mov	bx, di
		lea	ax, [bx+si]
		mov	dx, ax
		mov	cx, offset emu086_126DC
		jmp	cs:emu086_1210C[bp]

emu086_122A5:
		mov	bh, 0
		mov	bl, cs:byte_10052[bx]
		mov	ax, word ptr ds:__emu+0Dh
		add	bx, ax
		test	cl, 4
		mov	dx, ax
		jz	short emu086_122BA
		mov	dx, bx

emu086_122BA:
		sub	si, si
		test	cl, 2
		jz	short emu086_122C4
		mov	si, 0Ch

emu086_122C4:
		mov	cx, offset emu086_126DC
		jmp	cs:emu086_1210C[bp]
e086_Entry	endp ; sp-analysis failed


emu086_122CC	proc near
		push	ax
		push	bx
		push	dx
		push	cx
		jmp	emu086_10143
emu086_122CC	endp


emu086_122D3	proc near
		push	ax
		push	bx
		push	dx
		push	cx
		jmp	emu086_1030D
emu086_122D3	endp


emu086_122DA	proc near
		add	si, 0Ch

emu086_122DD:
		push	ax
		push	bx
		push	cx
		jmp	emu086_10A29
emu086_122DA	endp


emu086_122E3	proc near
		xchg	ax, bx

emu086_122E4:
		push	ax
		push	bx
		push	dx
		push	cx
		jmp	emu086_1013F
emu086_122E3	endp


emu086_122EB	proc near
		xchg	ax, bx

emu086_122EC:
		push	ax
		push	bx
		push	dx
		push	cx
		jmp	emu086_104DA
emu086_122EB	endp

; START	OF FUNCTION CHUNK FOR e086_Entry

emu086_122F3:
		mov	bp, 6
		and	bp, cx
		test	ch, 20h
		jnz	short emu086_1233F
		test	ch, 10h
		jnz	short emu086_1231C
		test	ch, 8
		jnz	short emu086_1235B
		mov	di, word ptr ds:__emu+0Dh
		mov	ax, 0FFF4h
		add	di, ax
		mov	word ptr ds:__emu+4, ax
		mov	ax, offset emu086_126D7
		push	ax
		jmp	cs:emu086_1211C[bp]

emu086_1231C:
		mov	di, word ptr ds:__emu+0Dh
		xchg	si, di
		test	ch, 8
		jnz	short emu086_12330
		mov	ax, offset emu086_126E1
		push	ax
		jmp	cs:emu086_12124[bp]

emu086_12330:
		mov	word ptr ds:__emu+4, 0Ch
		mov	ax, offset emu086_126D7
		push	ax
		jmp	cs:emu086_12124[bp]

emu086_1233F:
		mov	ax, 8
		and	al, ch
		or	bp, ax
		mov	ax, offset emu086_126E1
		push	ax
		test	ch, 10h
		jnz	short emu086_12354
		jmp	cs:emu086_1212C[bp]

emu086_12354:
		xchg	si, di
		jmp	cs:emu086_1213C[bp]

emu086_1235B:
		jmp	emu086_126E1
; END OF FUNCTION CHUNK	FOR e086_Entry

emu086_1235E	proc near
		mov	ch, 1
		call	emu086_12759
		retn
emu086_1235E	endp


emu086_12364	proc near
		mov	cl, 4
		mov	ax, es:[si+2]
		mov	word ptr ds:__emu, ax

emu086_1236D:
		mov	ax, es:[si]
		mov	word ptr ds:__emu+2, ax
		mov	ch, 0
		jmp	emu086_12759
emu086_12364	endp


emu086_12378	proc near
		call	emu086_123F7
		call	emu086_123FC
		mov	ax, word ptr ds:__emu+11h
		sub	ax, word ptr ds:__emu+0Dh
		mov	cx, 60h	; '`'
		cmp	ax, cx
		jb	short emu086_1238D
		xchg	ax, cx

emu086_1238D:
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
emu086_12378	endp


emu086_123A1	proc near
		call	emu086_12378
		mov	si, word ptr ds:__emu+0Dh
		mov	bp, es:[di-0Ah]
		neg	bp
		dec	bp

emu086_123AF:
		jz	short emu086_123C0
		call	emu086_10D9B
		add	si, 0Ch
		add	di, 0Ah
		shl	bp, 1
		shl	bp, 1
		jmp	short emu086_123AF

emu086_123C0:
		mov	word ptr ds:__emu+0Dh, si
		retn
emu086_123A1	endp


emu086_123C5	proc near
		mov	di, word ptr ds:__emu+0Dh
		mov	bp, es:[si+4]
		neg	bp
		dec	bp
		jz	short emu086_12364
		add	si, 5Eh	; '^'

emu086_123D5:
		sub	si, 0Ah
		shr	bp, 1
		shr	bp, 1
		jnb	short emu086_123D5

emu086_123DE:
		sub	di, 0Ch
		call	emu086_10DC8
		sub	si, 0Ah
		shr	bp, 1
		shr	bp, 1
		jb	short emu086_123DE
		add	si, 0FFFCh
		mov	word ptr ds:__emu+0Dh, di
		jmp	emu086_12364
emu086_123C5	endp


emu086_123F7	proc near
		mov	ax, word ptr ds:__emu+2
		stosw
		retn
emu086_123F7	endp


emu086_123FC	proc near
		mov	ax, word ptr ds:__emu+11h
		sub	ax, word ptr ds:__emu+0Dh
		mov	cx, 60h	; '`'
		cmp	ax, cx
		jb	short emu086_1240B
		xchg	ax, cx

emu086_1240B:
		neg	ax
		mov	cl, 0Ch
		idiv	cl
		and	al, 7
		mov	cl, 3
		shl	al, cl
		mov	cx, word ptr ds:__emu
		and	ch, 0C7h
		or	ch, al
		xchg	ax, cx
		stosw
		retn
emu086_123FC	endp


emu086_12423	proc near
		mov	di, word ptr ds:__emu+0Dh
		sub	di, 0Ch
		call	emu086_1121E
		sub	word ptr ds:__emu+0Dh, 0Ch
		retn
emu086_12423	endp


emu086_12433	proc near
		mov	di, word ptr ds:__emu+0Dh
		sub	di, 0Ch
		call	emu086_11F37
		sub	word ptr ds:__emu+0Dh, 0Ch
		retn
emu086_12433	endp


emu086_12443	proc near
		mov	di, word ptr ds:__emu+0Dh
		sub	di, 0Ch
		call	emu086_10DC8
		sub	word ptr ds:__emu+0Dh, 0Ch
		retn
emu086_12443	endp


emu086_12453	proc near
		mov	si, word ptr ds:__emu+0Dh
		call	emu086_11291
		add	word ptr ds:__emu+0Dh, 0Ch
		retn
emu086_12453	endp


emu086_12460	proc near
		mov	si, word ptr ds:__emu+0Dh
		call	emu086_12020
		add	word ptr ds:__emu+0Dh, 0Ch
		retn
emu086_12460	endp


emu086_1246D	proc near
		mov	si, word ptr ds:__emu+0Dh
		call	emu086_10D9B
		add	word ptr ds:__emu+0Dh, 0Ch
		retn
emu086_1246D	endp

emu086_1247A	dw offset emu086_124B9
		dw offset emu086_12513
		dw offset emu086_124CC
		dw offset emu086_124C7
		dw offset emu086_1251A
		dw offset emu086_12513
		dw offset emu086_1251A
		dw offset emu086_1251A
		dw offset emu086_1250E
		dw offset emu086_12513
		dw offset emu086_1252B
		dw offset emu086_12536
		dw offset emu086_12536
		dw offset emu086_12513
		dw offset emu086_12536
		dw offset emu086_12536
; START	OF FUNCTION CHUNK FOR e086_Entry

emu086_1249A:
		mov	bh, 0
		mov	bl, cs:byte_10052[bx]
		mov	si, word ptr ds:__emu+0Dh
		add	si, bx
		mov	bl, 18h
		and	bl, ch
		and	cl, 6
		or	bl, cl
		cld
		mov	cx, 6
		jmp	cs:emu086_1247A[bx]

emu086_124B9:
		sub	word ptr ds:__emu+0Dh, 0Ch
		mov	di, word ptr ds:__emu+0Dh
		rep movsw
		jmp	emu086_126E1

emu086_124C7:
		mov	di, 0Ch
		jmp	short emu086_124CF

emu086_124CC:
		mov	di, 0

emu086_124CF:
		mov	ax, word ptr ds:__emu+11h
		sub	ax, 0Ch
		cmp	si, ax
		jz	short emu086_124E9
		xchg	di, si
		mov	ax, 4001h
		mov	cl, 0
		call	emu086_10E8D
		add	word ptr ds:__emu+0Dh, si
		jmp	short emu086_12542

emu086_124E9:
		add	di, 0Ch
		mov	dx, di
		mov	cx, si
		sub	cx, word ptr ds:__emu+0Dh
		jz	short emu086_12508
		push	ss
		pop	es
		sub	si, 2
		mov	di, word ptr ds:__emu+11h
		sub	di, 2
		std
		shr	cx, 1
		rep movsw
		cld

emu086_12508:
		add	word ptr ds:__emu+0Dh, dx
		jmp	short emu086_12542

emu086_1250E:
		test	ch, 7
		jz	short emu086_12542

emu086_12513:
		mov	ch, 1
		call	emu086_12759
		jmp	short emu086_12542

emu086_1251A:
		mov	di, word ptr ds:__emu+0Dh

emu086_1251E:
		mov	ax, [di]
		xchg	ax, [si]
		stosw
		add	si, 2
		loop	emu086_1251E
		jmp	emu086_126E1

emu086_1252B:
		mov	di, si
		mov	si, word ptr ds:__emu+0Dh
		rep movsw
		jmp	emu086_126E1

emu086_12536:
		mov	di, si
		mov	si, word ptr ds:__emu+0Dh
		rep movsw
		mov	word ptr ds:__emu+0Dh, si

emu086_12542:
		jmp	emu086_126E1
; END OF FUNCTION CHUNK	FOR e086_Entry
byte_12545	db 4, 4, 4, 4, 4, 4, 4,	4, 0, 0, 0, 0, 0, 0, 0,	4, 4, 8
		db 6, 8, 6, 4, 2, 0, 10, 8, 4, 4, 4, 10, 4, 4
emu086_12565	dw offset emu086_125A5
		dw offset emu086_125AA
		dw offset emu086_125B7
		dw offset emu086_125B7
		dw offset emu086_10AE9
		dw offset emu086_10B25
		dw offset emu086_125B7
		dw offset emu086_125B7
		dw offset emu086_10E11
		dw offset emu086_10E22
		dw offset emu086_10E33
		dw offset emu086_10E44
		dw offset emu086_10E55
		dw offset emu086_10E66
		dw offset emu086_10E77
		dw offset emu086_125B7
		dw offset emu086_119FE
		dw offset emu086_11AF6
		dw offset emu086_11780
		dw offset emu086_11876
		dw offset emu086_125AF
		dw offset emu086_125B7
		dw offset emu086_125B7
		dw offset emu086_125B7
		dw offset emu086_10921
		dw offset emu086_11BAD
		dw offset emu086_10855
		dw offset emu086_125B7
		dw offset emu086_11387
		dw offset emu086_11063
		dw offset emu086_125B7
		dw offset emu086_125B7

emu086_125A5	proc near
		xor	byte ptr [si+0Ah], 1
		retn
emu086_125A5	endp


emu086_125AA	proc near
		mov	byte ptr [si+0Ah], 0
		retn
emu086_125AA	endp


emu086_125AF	proc near
		push	si
		push	di
		call	emu086_1102E
		pop	di
		pop	si
		retn
emu086_125AF	endp


emu086_125B7	proc far
		mov	ch, 1
		call	emu086_12759
		jmp	emu086_126E1
		retn
emu086_125B7	endp

emu086_125C0	dw offset emu086_125DF
		dw offset emu086_12616
		dw offset emu086_125F2
		dw offset emu086_12601
		dw offset emu086_1261E
		dw offset emu086_12631
; START	OF FUNCTION CHUNK FOR e086_Entry

emu086_125CC:
		mov	bx, 1Fh
		and	bl, ch
		mov	al, cs:byte_12545[bx]
		cbw
		xchg	ax, di
		shl	bx, 1
		jmp	cs:emu086_125C0[di]

emu086_125DF:
		mov	di, word ptr ds:__emu+0Dh
		sub	di, 0Ch
		call	cs:emu086_12565[bx]
		mov	word ptr ds:__emu+0Dh, di
		jmp	emu086_126E1

emu086_125F2:
		mov	si, word ptr ds:__emu+0Dh
		mov	di, si
		mov	ax, offset emu086_126E1
		push	ax
		jmp	cs:emu086_12565[bx]

emu086_12601:
		mov	si, word ptr ds:__emu+0Dh
		mov	di, si
		sub	di, 0Ch
		call	cs:emu086_12565[bx]
		mov	word ptr ds:__emu+0Dh, di
		jmp	emu086_126E1

emu086_12616:
		add	word ptr ds:__emu+0Dh, 0Ch
		jmp	emu086_126E1

emu086_1261E:
		mov	di, word ptr ds:__emu+0Dh
		lea	si, [di+0Ch]
		call	cs:emu086_12565[bx]
		mov	word ptr ds:__emu+0Dh, si
		jmp	emu086_126E1

emu086_12631:
		mov	di, word ptr ds:__emu+0Dh
		lea	si, [di+0Ch]
		mov	ax, offset emu086_126E1
		push	ax
		jmp	cs:emu086_12565[bx]
; END OF FUNCTION CHUNK	FOR e086_Entry


		public e287_FPU_Control
e287_FPU_Control proc far
		and	ch, 1Fh
		cmp	ch, 3
		jnz	short emu086_1269E
		mov	word ptr ds:__emu+39h, 2
		mov	word ptr ds:__emu+35h, 6D65h
		mov	word ptr ds:__emu+37h, 8775h
		mov	word ptr ds:__emu+4, 0
		mov	di, word ptr ds:__emu+11h
		mov	word ptr ds:__emu+0Dh, di
		mov	bx, word ptr ds:__emu+0Fh
		sub	bx, di
		neg	bx
		mov	ax, 4001h
		mov	cl, 0
		call	emu086_10E8D
		mov	byte ptr [di+7], 0C0h ;	'À'
		lea	si, [di+0Ah]
		sub	di, 2
		mov	cx, word ptr ds:__emu+0Fh
		sub	cx, di
		neg	cx
		shr	cx, 1
		std
		rep movsw
		mov	word ptr ds:__emu, 4100h
		mov	word ptr ds:__emu+2, 33Fh
		jmp	short emu086_126AF

emu086_1269E:
		cmp	ch, 2
		jnz	short emu086_126AA
		mov	ds:__emu, 0
		jmp	short emu086_126AF

emu086_126AA:
		mov	ch, 1
		call	emu086_12759

emu086_126AF:
		jmp	short emu086_126E1

emu086_126B1:
		jmp	short emu086_126AA

emu086_126B3:
		test	ch, 1Fh
		jnz	short emu086_126AA
		mov	ax, word ptr ds:__emu+0Dh
		sub	ax, word ptr ds:__emu+11h
		mov	cl, 0Ch
		idiv	cl
		and	al, 7
		mov	cl, 3
		shl	al, cl
		mov	cx, word ptr ds:__emu
		and	ch, 0C7h
		or	ch, al
		mov	[bp+10h], cx
		jmp	short emu086_126E1

emu086_126D7:
		mov	si, word ptr ss:__emu+4

emu086_126DC:
		add	word ptr ss:__emu+0Dh, si

emu086_126E1:
		mov	ax, word ptr ss:__emu+0Fh
		cmp	word ptr ss:__emu+0Dh, ax
		jb	short emu086_126FB

emu086_126EC:
		mov	sp, word ptr ss:__emu+33h
		pop	es
		pop	di
		pop	si
		pop	bp
		pop	ds
		pop	bx
		pop	dx
		pop	cx
		pop	ax

		public rs2
rs2:
		iret

emu086_126FB:
		mov	ch, 40h	; '@'
		mov	di, word ptr ds:__emu+11h
		mov	word ptr ds:__emu+0Dh, di
		call	emu086_12759
		int	3		; Trap to Debugger
		jmp	short emu086_126EC
e287_FPU_Control endp

		dw offset emu086_11C3D
		dw offset emu086_11C41
		dw offset emu086_11C45
		dw offset emu086_11C3D
		dw offset emu086_11C41
		dw offset emu086_11C45
		dw offset emu086_11D26
		dw offset emu086_11D87
		dw offset emu086_11D99
		dw offset emu086_11DAB
		dw offset emu086_11DF8
		dw offset emu086_11DFD
		dw offset emu086_11E08

		public e086_Shortcut
e086_Shortcut	proc near
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
		mov	word ptr ss:__emu+33h, sp
		lds	si, [bp+12h]
		lodsb
		mov	[bp+12h], si
		mov	di, ss
		mov	ds, di
		cbw
		xchg	ax, bx
		cmp	bl, 0E6h ; 'æ'
		jb	short emu086_12752
		mov	ax, offset emu086_126E1
		push	ax
		jmp	word ptr cs:e086_Shortcut[bx]

emu086_12752:
		mov	ch, 1
		call	emu086_12759
		jmp	short emu086_126E1
e086_Shortcut	endp


emu086_12759	proc near
		push	ax
		push	cx
		push	ds
		push	ss
		pop	ds
		mov	al, ds:__emu
		mov	cl, ds:__emu+2
		and	cl, 7Fh
		xor	cl, 7Fh
		or	al, ch
		mov	ah, al
		and	ah, cl
		xor	ah, al
		test	ah, 8
		jz	short emu086_1277A
		or	al, 20h

emu086_1277A:
		test	al, cl
		jz	short emu086_1278D
		or	al, 80h
		mov	ds:__emu, al
		and	al, cl
		cmp	al, 20h	; ' '
		jnz	short EmuVectorException
		pop	ds
		pop	cx
		pop	ax
		retn

emu086_1278D:
		and	al, 7Fh
		mov	ds:__emu, al
		pop	ds
		pop	cx
		pop	ax
		retn
emu086_12759	endp


		public EmuVectorException
EmuVectorException proc	near
		call	__fpuint
		cmp	ax, 0FFFFh
		jz	short emu086_127AE
		mov	ah, 35h	; '5'
		int	21h
		mov	word ptr ss:__emu+41h, bx
		mov	word ptr ss:__emu+43h, es

emu086_127AE:
		mov	sp, word ptr ss:__emu+33h
		pop	es
		pop	di
		pop	si
		pop	bp
		pop	ds
		pop	bx
		pop	dx
		pop	cx
		pop	ax
		jmp	dword ptr ss:__emu+41h
EmuVectorException endp

EMU_PROG	ends
