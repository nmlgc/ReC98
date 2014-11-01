ifdef   FP87
_Emu_   equ     0               ; no emulation, '87 required
else
_Emu_   equ     1               ; emulator
endif

        public  FIDRQQ          ; wait, esc
        public  FIARQQ          ; wait, DS:
        public  FICRQQ          ; wait, CS:
        public  FIERQQ          ; wait, ES:
        public  FISRQQ          ; wait, SS:
        public  FIWRQQ          ; nop, wait
        public  FJARQQ          ; Esc nn -> DS:nn
        public  FJCRQQ          ; Esc nn -> CS:nn
        public  FJSRQQ          ; Esc nn -> ES:nn

; Use full emulator if _Emu_ is true.

if      _Emu_

FIDRQQ  equ     05C32h
FIARQQ  equ     0FE32h
FICRQQ  equ     00E32h
FIERQQ  equ     01632h
FISRQQ  equ     00632h
FIWRQQ  equ     0A23Dh
FJARQQ  equ     04000h
FJCRQQ  equ     0C000h
FJSRQQ  equ     08000h

else

FIDRQQ  equ     00000h
FIARQQ  equ     00000h
FICRQQ  equ     00000h
FIERQQ  equ     00000h
FISRQQ  equ     00000h
FIWRQQ  equ     00000h
FJARQQ  equ     00000h
FJCRQQ  equ     00000h
FJSRQQ  equ     00000h

endif

originalVectors	dd 0Ch dup(?)
FPEpriorVector	dd ?
fpinit_platform	db 0
fpinit_100B5	dw 0FFFFh
fpinit_100B7	db ?
fpinit_100B8	db 0
plus_inf	dd 7F800000h

; borrowed from T. Pascal, DOS 3.1 BIOS
; avoid DOS 3.2 stack swap
int75handler    proc    far
        push    ax
        xor     al, al                  ; Clear BUSY latch
        out     0F0h, al
        mov     al, 20H                 ; End-of-interrupt
        out     0A0h, al
        out     20h, al
        pop     ax
        int     2
        iret
int75handler    endp

nec_fpinit_100CC	proc near
		push	ax
		mov	al, 20h
		out	8, al
		jmp	short $+2
		mov	al, 0Bh
		out	8, al
		jmp	short $+2
		in	al, 8
		or	al, al
		jnz	short @@loc_100E3
		mov	al, 20h
		out	0, al

@@loc_100E3:
		pop	ax
		jmp	short $+2
nec_fpinit_100CC	endp

int2handler	proc far
		push	ax
		mov	ax, seg __emu
		call	e087_Trap
		jb	short @@err
		pop	ax
; ---------------------------------------------------------------------------
		db 0EAh
nmi		dw 2 dup(?)
; ---------------------------------------------------------------------------

@@err:
		xchg	ax, bx
		mov	ax, seg	__8087
		mov	ds, ax
		call	__fperror
		pop	ax

int2handler_ret:
		iret
int2handler	endp

emu1st		proc near
		push	ds
		push	si
		push	di
		mov	ax, seg	__8087
		mov	ds, ax

; set end of FPU stack
		mov	ax, offset __emu + SIZE_FPU
		mov	word ptr ss:__emu+0Fh, ax
		add	ax, 0C0h
		mov	word ptr ss:__emu+11h, ax
		mov	ax, __protected
		mov	word ptr ss:__emu+7, ax
		push	ds
		push	cs
		pop	ds
		; assume ds:nothing
		mov	ax, ds
		xor	ax, word ptr ss:__emu+7
		mov	ds, ax
		; assume ds:DGROUP
		mov	ax, 3534h
		mov	cx, 11
		mov	di, offset originalVectors

@@rememberLoop:
		int	21h
		mov	[di], bx
		mov	word ptr [di+2], es
		add	di, 4
		inc	ax
		loop	@@rememberLoop
		push	ds
		push	di
		mov	cl, 0
		mov	ax, seg __8087
		mov	ds, ax
		cmp	__8087, 0
		jz	short @@IBM
		mov	ah, 4
		xor	cx, cx
		int	1Ah
		mov	cl, 2
		cmp	ch, 19h
		jz	short @@IBM
		cmp	ch, 20h
		jz	short @@IBM
		mov	cl, 1

@@IBM:
		pop	di
		pop	ds
		assume ds:seg fpinit_platform
		mov	ds:fpinit_platform, cl
		cmp	cl, 2
		jnz	short @@loc_10182
; grab INT 75h
		mov	ax, 3575h
		int	21h
		mov	[di], bx
		mov	word ptr [di+2], es
		add	di, 4
; grab INT 2
		mov	ax, 3502h
		jmp	short @@loc_10199

@@loc_10182:
		cmp	cl, 1
		jnz	short @@loc_101B0
		push	sp
		pop	ax
		cmp	ax, sp
		mov	ax, 3510h
		jz	short @@loc_10199
		in	al, 0Ah
		and	al, 40h
		mov	ds:fpinit_100B7, al
		mov	al, 16h

@@loc_10199:
		mov	bl, al
		mov	bh, 25h
		mov	ds:fpinit_100B5, bx
		int	21h
		mov	[di], bx
		mov	word ptr [di+2], es
		mov	ds:nmi,	bx
		mov	ds:nmi+2, es

@@loc_101B0:
		pop	ds
		assume ds:seg __psp
		mov	bx, -1
		mov	es, __psp

; Look for a "87" environment variable.
; Each variable	is ended by a 0	and a zero-length variable stops
; the environment. The environment can NOT be greater than 32k.

		; assume es:nothing
		mov	es, word ptr es:2Ch ; environment segment
		; assume es:nothing
		sub	di, di		; ES:[di] points to environ
		mov	cx, 7FFFh	; Environment cannot be	> 32 Kbytes
		mov	al, 0
		cld

@@env87next:
		repne scasb		; direction flag is clear
		jcxz	short @@env87done ; count exhausted imply end
		cmp	al, es:[di]	; double zero bytes imply end
		jz	short @@env87done
		cmp	word ptr es:[di], '78'
		jnz	short @@env87next
		mov	dx, es:[di+2]
		cmp	dl, '='
		jnz	short @@env87next
		inc	bx
		and	dh, not	('y' - 'Y')
		cmp	dh, 'Y'
		jnz	short @@env87done
		inc	bx

@@env87done:
		pop	di
		pop	si
		xor	ax, ax
		or	bx, bx
		jz	short @@set_flag
		jg	short @@loc_1022E
		mov	cx, __8087
		jcxz	short @@loc_10250

@@TestPresence:
		fninit
		mov	__8087, 0
		fnstcw	__8087
		mov	cx, 20

@@delay_1:
		loop	@@delay_1	; Delay	awhile
		mov	cx, __8087	; Get NPX control word
		and	cx, 0F3Fh	; Mask off undefined bits
		cmp	cx, 33Fh	; Do we	have a math coprocessor
		jnz	short @@test_done	; No ...
		mov	__8087, -1
		fnstsw	__8087	; Store the status word
		mov	cx, 14h

@@delay_2:
		loop	@@delay_2	; Delay	awhile
		test	__8087, 0B8BFh ; All bits off that should be?
		jnz	short @@test_done

@@loc_1022E:
		inc	ax
		push	sp
		pop	cx
		cmp	cx, sp
		jnz	short @@test_done
		fninit
		fld	cs:plus_inf
		fchs
		fcomp	cs:plus_inf	; compare +INF to -INF
		fstsw	ax		; we have a 287	or better
		sahf
		mov	al, 2
		jz	short @@test_done ; equal on 80287 only
		inc	ax

@@test_done:
		cbw

@@set_flag:
		mov	__8087, ax

@@loc_10250:
		mov	ss:__emu+6, al
		pop	ds
emu1st		endp

		emul
		public ___fpreset
___fpreset	proc near
@@temp1		= dword	ptr -8
@@temp2		= dword	ptr -4

		push	ds
		push	bp
		mov	bp, sp
		sub	sp, 8
		mov	bx, seg __8087
		mov	ds, bx
		cmp	__8087, 0
		mov	word ptr [bp+@@temp1], offset e087_Entry
		mov	word ptr [bp+@@temp1+2], seg e087_Entry
		mov	word ptr [bp+@@temp2], offset e087_Shortcut
		mov	word ptr [bp+@@temp2+2], seg e087_Shortcut
		jnz	short @@doCapture
		mov	word ptr [bp+@@temp1], offset e086_Entry
		mov	word ptr [bp+@@temp1+2], seg e086_Entry
		mov	word ptr [bp+@@temp2], offset e086_Shortcut
		mov	word ptr [bp+@@temp2+2], seg e086_Shortcut

@@doCapture:
		mov	ax, 2534h
		mov	cx, 10
		lds	dx, [bp+@@temp1]

@@captureLoop:
		int	21h
		inc	ax
		loop	@@captureLoop
		mov	ax, 253Eh
		lds	dx, [bp+@@temp2]
		int	21h
		mov	ds, bx
		cmp	__8087, 0
		jnz	short @@loc_102D8
		mov	word ptr ss:__emu+41h, offset int2handler
		mov	word ptr ss:__emu+43h, cs
		push	cs
		pop	ds
		mov	ax, ds
		xor	ax, word ptr ss:__emu+7
		mov	ds, ax
		assume	ds:seg nmi
		mov	ds:nmi,	offset int2handler_ret
		mov	ds:nmi+2, cs
		mov	ds:fpinit_100B5, -1
		jmp	short @@init87

@@loc_102D8:
		push	cs
		pop	ds
		cmp	ds:fpinit_platform, 2
		jnz	short @@loc_10306
		mov	ax, ds:fpinit_100B5
		mov	dx, offset int2handler
		int	21h
		mov	ds, bx
		assume	ds:seg __8087
		cmp	__8087, 0
		jz	short @@init87
		mov	ax, __version
		xchg	ah, al
		cmp	ax, 1403h
		jnz	short @@init87
		mov	ax, 2575h
		push	cs
		pop	ds
		assume	ds:seg fpinit_platform
		mov	dx, offset int75handler
		int	21h

@@loc_10306:
		cmp	ds:fpinit_platform, 1
		jnz	short @@init87
		mov	ax, ds:fpinit_100B5
		mov	dx, offset int2handler
		cmp	al, 16h
		jnz	short @@loc_1031A
		mov	dx, offset nec_fpinit_100CC

@@loc_1031A:
		int	21h
		cmp	al, 16h
		jnz	short @@init87
		pushf
		cli
		in	al, 0Ah
		and	al, 0BFh
		out	0Ah, al
		popf

@@init87:
		mov	ds, bx
		mov	cs:fpinit_100B8, 1
		; Hack (this is not assembling to an emulated fninit for some reason?)
		db	0CDh, 037h, 0E3h
		mov	word ptr ss:__emu+21h, 0
		mov	word ptr ss:__emu+23h, 0
		assume	ds:seg __default87
		mov	ax, __default87
		mov	word ptr [bp+@@temp1], ax
		cmp	__8087, 3
		jl	short @@control
		or	word ptr [bp+@@temp1], 2

@@control:
		push	si
		fldcw	word ptr [bp+@@temp1]
		pop	si
		mov	ax, word ptr [bp+@@temp1]
		and	word ptr ss:__emu+2, ax
		xor	ax, ax
		cwd
		mov	sp, bp
		pop	bp
		pop	ds
		ret
___fpreset	endp

		public emuLast
emuLast		proc near
		push	ds
		mov	ax, seg __8087
		mov	ds, ax
		cmp	cs:fpinit_100B8, 0
		jz	short @@done
		push	ds
		finit
		mov	ax, 2534h
		mov	bx, offset originalVectors
		mov	cx, 11

@@restoreLoop:
		lds	dx, cs:[bx]
		assume	ds:seg __8087
		int	21h
		add	bx, 4
		inc	ax
		loop	@@restoreLoop
		pop	ds
		cmp	__8087, 0
		jz	short @@done
		cmp	cs:fpinit_platform, 2
		jnz	short @@loc_103AA
		mov	ax, 2575h
		lds	dx, cs:[bx]
		int	21h
		add	bx, 4

@@loc_103AA:
		mov	ax, cs:fpinit_100B5
		cmp	cs:fpinit_platform, 1
		jnz	short @@loc_103C8
		cmp	al, 16h
		jnz	short @@loc_103C8
		xchg	ax, dx
		pushf
		cli
		in	al, 0Ah
		or	al, cs:fpinit_100B7
		out	0Ah, al
		popf
		xchg	ax, dx

@@loc_103C8:
		lds	dx, cs:[bx]
		int	21h

@@done:
		mov	cs:fpinit_100B8, 0
		pop	ds
		ret
emuLast		endp

		public __fpuint
__fpuint	proc far
		mov	ax, cs:fpinit_100B5
		ret
__fpuint	endp
