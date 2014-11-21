E87_PROG		segment	para public 'CODE' use16
		assume cs:E87_PROG
		assume es:nothing, ss:nothing, ds:_STACK, fs:nothing, gs:nothing
		option noemulator

e87trap_10070:
		pop	di
		pop	es
		pop	dx
		pop	cx
		pop	bx
		pop	si
		pop	ds
		clc
		retf

e87trap_10079:
		mov	al, ds:__emu+2
		mov	ah, ds:__emu
		db	0CDh, 037h, 0E2h	; Hack (we need an emulated FNCLEX here)
		test	ah, 80h
		jz	short e87trap_10070
		not	al
		and	al, ah
		jmp	e87trap_101C5

e87trap_1008F:
		les	di, [si+6]
		test	bl, 8
		jnz	short e87trap_1009F
		mov	bx, es
		and	bx, 0F000h
		mov	es, bx
		assume es:nothing

e87trap_1009F:
		test	byte ptr es:[di], 80h
		jnz	short e87trap_100A6
		inc	di

e87trap_100A6:
		mov	bx, es:[di]
		xchg	bh, bl
		jmp	short e87trap_100F6
; END OF FUNCTION CHUNK	FOR e087_Trap
		jmp	short e87trap_10111
		nop


		public e087_Trap
e087_Trap	proc far

; FUNCTION CHUNK AT 0000 SIZE 0000003D BYTES

		push	ds
		push	si
		push	bx
		push	cx
		push	dx
		push	es
		push	di
		mov	ds, ax
		mov	al, ds:__emu+6
		or	al, al
		mov	bx, ax
		jz	short e87trap_10079
		mov	si, (offset __emu+13h)
		fnstenv	byte ptr [si]
		wait
		mov	ax, [si+2]
		test	al, 80h
		jz	short e87trap_10070
		fclex
		mov	dx, ax
		mov	al, [si]
		mov	dh, dl
		or	al, 40h
		and	dl, al
		and	dl, 7Fh
		mov	[si+2],	dl
		wait
		fldenv	byte ptr [si]
		not	al
		and	al, dh
		or	bx, word ptr ds:__emu+7
		cmp	bl, 3
		jge	short e87trap_1008F
		mov	bx, [si+8]

e87trap_100F6:
		and	bh, 7
		mov	dh, bl
		and	dh, 0C0h
		cmp	dh, 0C0h ; 'À'
		jz	short e87trap_10106
		and	bl, 38h

e87trap_10106:
		wait
		sti
		test	al, 1
		jz	short e87trap_10111
		mov	al, 40h	; '@'
		jmp	e87trap_101C5

e87trap_10111:
		test	al, 2
		jz	short e87trap_1016A
		mov	cx, 8

e87trap_10118:
		call	e87trap_101D8
		wait
		fincstp
		loop	e87trap_10118
		mov	ax, bx
		shr	ax, 1
		and	al, 9Ch
		cmp	al, 80h	; '€'
		jz	short e87trap_10132
		cmp	al, 94h	; '”'
		jz	short e87trap_10132
		and	al, 98h
		cmp	al, 8

e87trap_10132:
		jz	short e87trap_10168
		fnstcw	word ptr ds:__emu+31h
		wait
		or	ds:__emu+31h, 2
		wait
		fldcw	word ptr ds:__emu+31h
		les	di, [si+0Ah]
		assume es:nothing
		cmp	bx, 30h	; '0'
		jnz	short e87trap_10151
		wait
		fld	dword ptr es:[di]
		jmp	short e87trap_1015B

e87trap_10151:
		cmp	bx, 430h
		jnz	short e87trap_10161
		wait
		fld	qword ptr es:[di]

e87trap_1015B:
		call	e87trap_101D8
		mov	bx, 0DEF9h

e87trap_10161:
		wait
		mov	di, word ptr ds:__emu+0Dh
		jmp	short e87trap_1019B

e87trap_10168:
		jmp	short e87trap_101B3

e87trap_1016A:
		mov	ah, ds:__emu+2
		not	ah
		and	ah, al
		and	ah, 7Fh
		jnz	short e87trap_101C5
		test	al, 5
		jnz	short e87trap_10189
		test	al, 18h
		jz	short e87trap_101B7
		mov	ax, bx
		shr	ax, 1
		and	al, 0E8h
		cmp	al, 88h	; 'ˆ'
		jnz	short e87trap_101B7

e87trap_10189:
		fnstcw	word ptr ds:__emu+31h
		wait
		mov	ax, word ptr ds:__emu+31h
		or	ds:__emu+31h, 3Fh
		wait
		fldcw	word ptr ds:__emu+31h

e87trap_1019B:
		push	cs
		call	near ptr e87trap_10225
		add	sp, 0Ah
		fstsw	word ptr ds:__emu+31h
		fclex
		mov	ax, word ptr ds:__emu+31h
		and	al, 3Fh
		or	ds:__emu+25h, al

e87trap_101B3:
		wait
		fldcw	word ptr [si]
		clc

e87trap_101B7:
		pop	di
		pop	es
		pop	dx
		pop	cx
		pop	bx
		pop	si
		pop	ds
		jb	short e87trap_101C4
		pop	ax
		pop	ax
		pop	ax
		iret

e87trap_101C4:
		retf

e87trap_101C5:
		xor	dx, dx
		mov	bx, ax

e87trap_101C9:
		inc	dx
		shr	bx, 1
		jnb	short e87trap_101C9
		mov	word ptr ds:__emu+9, dx
		mov	ax, (offset __emu+9)
		stc
		jmp	short e87trap_101B7
e087_Trap	endp ; sp-analysis failed


e87trap_101D8	proc near
		wait
		fxam
		fstsw	word ptr ds:__emu+31h
		wait
		mov	ah, ds:__emu+32h
		sahf
		jnb	short e87trap_101EB
		jnz	short e87trap_101ED
		retn

e87trap_101EB:
		jz	short e87trap_101F2

e87trap_101ED:
		jb	short e87trap_101F1
		jnp	short e87trap_101F9

e87trap_101F1:
		retn

e87trap_101F2:
		wait
		fstp	st
		wait
		fldz
		retn

e87trap_101F9:
		wait
		fstp	tbyte ptr ds:__emu+27h
		wait
		fild	qword ptr ds:__emu+27h
		mov	ax, word ptr ds:__emu+2Fh
		mov	dx, ax
		and	dh, 80h
		wait
		fstp	tbyte ptr ds:__emu+27h
		xor	ah, dh
		wait
		add	ax, word ptr ds:__emu+2Fh
		sub	ax, 403Eh
		xor	ah, dh
		mov	word ptr ds:__emu+2Fh, ax
		wait
		fld	tbyte ptr ds:__emu+27h
		retn
e87trap_101D8	endp


e87trap_10225	proc far
		mov	word ptr ds:__emu+0Dh, di
		mov	dx, 0EA90h
		push	dx
		mov	dx, bx
		and	bl, 0C0h
		cmp	bl, 0C0h ; 'À'
		jz	short e87trap_1023A
		or	dl, 7

e87trap_1023A:
		or	dh, 0D8h
		xchg	dh, dl
		push	dx
		mov	dx, 269Bh
		push	dx
		mov	dx, ss
		xor	dx, word ptr ds:__emu+7
		push	dx
		mov	dx, sp
		add	dx, 2
		push	dx
		les	bx, [si+0Ah]
		retf
e87trap_10225	endp ; sp-analysis failed

		db 11 dup(0)

E87_PROG	ends
