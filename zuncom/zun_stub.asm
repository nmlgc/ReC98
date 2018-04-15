		.8086
		.model tiny
		.code
		org 100h
start:
		jmp	short entry

var102		dw 0
aNoComSoft	db 'No COM-Soft !!!',13,10,10,'$'

entry:
		cld
		mov	cx, word ptr proc_count
		or	cx, cx
		jz	short error
		mov	si, 80h
		lodsb
		or	al, al
		jz	short print_procs
		
@scanargs:
		lodsb
		cmp	al, 13
		jz	short print_procs
		cmp	al, 32
		jz	short @scanargs
		jmp	short findentry

; Outputs names of all embedded COM files and then exits
print_procs:
		mov	cx, word ptr proc_count
		mov	si, offset proc_names
		mov	dl, 13
		mov	ah, 2		; INT=21/AH=02h - WRITE CHARACTER TO STANDARD OUTPUT
		int	21h
		mov	dl, 10
		int	21h
@outerloop:
		push	cx
		mov	dl, 32
		int	21h
		mov	cx, 8
@innerloop:
		lodsb
		mov	dl, al
		int	21h
		loop	@innerloop
		mov	dl, 32
		int	21h
		pop	cx
		loop	@outerloop
		mov	dl, 13
		int	21h
		mov	dl, 10
		int	21h
		mov	ah, 4Ch		; INT=21/AH=4Ch - TERMINATE WITH RETURN CODE
		int	21h
; ---------------------------------------------------------------------------

findentry:
		mov	bx, offset proc_entries
		mov	cx, word ptr proc_count
		mov	si, offset proc_names
@loop:
		mov	word ptr var102, si
		mov	di, 5Dh		; Standard FCB 1 filename
		push	cx
		mov	cx, 8
		repe cmpsb
		jz	short fixup
		add	bx, 2
		mov	si, word ptr var102
		add	si, 8
		pop	cx
		loop	@loop

error:
		mov	dx, offset aNoComSoft
		mov	ah, 9		; INT=21/AH=09h - WRITE STRING TO STANDARD OUTPUT
		int	21h
		mov	ah, 4Ch		; INT=21/AH=4Ch - TERMINATE WITH RETURN CODE
		int	21h
; ---------------------------------------------------------------------------

; Fixup FCB and args before continuing
; BX points to the entry in proc_entries
fixup:
		; Copy FCB 2 into FCB 1
		mov	di, 5Ch
		mov	si, 6Ch
		mov	cx, 10h
		rep movsb
		; Move arguments
		mov	si, 80h
		lodsb
		mov	dl, al
@skipspace:
		lodsb
		dec	dl
		cmp	al, 32
		jz	short @skipspace
@skipnonspace:
		lodsb
		dec	dl
		cmp	al, 13
		jz	short @moveargs
		cmp	al, 32
		jnz	short @skipnonspace
@moveargs:
		inc	dl
		mov	di, 80h
		mov	al, dl
		stosb
		or	dl,dl
		jz	short @emptyargs
		dec	si
		mov	cl, dl
		xor	ch, ch
		rep movsb
@emptyargs:
		mov	byte ptr [di], 13
		; setup registers for moventry
		mov	ax, [bx]
		mov	cx, [bx+2]
		mov	si, ax
		sub	cx, ax
		mov	di, 100h
		jmp	moveup_indirect

; ---------------------------------------------------------------------------
		include bin\zuncom\gensize.inc

	IF GAME EQ 2

proc_count	dw 4

proc_names	db 'ONGCHK  '
		db 'ZUNINIT '
		db 'ZUN_RES '
		db 'ZUNSOFT '
		db 28 dup('        ')
proc_entries	dw offset ongchk
		dw offset zuninit
		dw offset zun_res
		dw offset zunsoft
		dw offset moveup	; last entry points to moveup
		dw 28 dup(0)
moveup_indirect:
		call	moveup
ongchk:		org $+GENSIZE_ONGCHK
zuninit:	org $+GENSIZE_ZUNINIT2
zun_res:	org $+GENSIZE_ZUN_RES
zunsoft:	org $+GENSIZE_ZUNSOFT

	ELSEIF GAME EQ 3

proc_count	dw 5
proc_names	db '-1      '
		db '-2      '
		db '-3      '
		db '-4      '
		db '-5      '
		db 27 dup('        ')
proc_entries	dw offset ongchk
		dw offset zuninit
		dw offset zunsoft
		dw offset zunsp
		dw offset res_yume
		dw offset moveup	; last entry points to moveup
		dw 27 dup(0)
moveup_indirect:
		call	moveup
ongchk:		org $+GENSIZE_ONGCHK
zuninit:	org $+GENSIZE_ZUNINIT2
zunsoft:	org $+GENSIZE_ZUNSOFT
zunsp:		org $+GENSIZE_ZUNSP
res_yume:	org $+GENSIZE_RES_YUME

	ELSEIF GAME EQ 4

proc_count	dw 4
proc_names	db '-O      '
		db '-I      '
		db '-S      '
		db '-M      '
		db 28 dup('        ')
proc_entries	dw offset ongchk
		dw offset zuninit
		dw offset res_huma
		dw offset memchk
		dw offset moveup
		dw 28 dup(0)
moveup_indirect:
		call	moveup
ongchk:		org $+GENSIZE_ONGCHK
zuninit:	org $+GENSIZE_ZUNINIT4
res_huma:	org $+GENSIZE_RES_HUMA
memchk:		org $+GENSIZE_MEMCHK4

	ELSEIF GAME EQ 5

proc_count	dw 5
proc_names	db '-O      '
		db '-I      '
		db '-S      '
		db '-G      '
		db '-M      '
		db 27 dup('        ')
proc_entries	dw offset ongchk
		dw offset zuninit
		dw offset res_kso
		dw offset gjinit
		dw offset memchk
		dw offset moveup
		dw 27 dup(0)
moveup_indirect:
		call	moveup
ongchk:		org $+GENSIZE_ONGCHK
zuninit:	org $+GENSIZE_ZUNINIT5
res_kso:	org $+GENSIZE_RES_KSO
gjinit:		org $+GENSIZE_GJINIT
memchk:		org $+GENSIZE_MEMCHK5

	ENDIF
; ---------------------------------------------------------------------------
moveup:		; the following code is split into moveup.asm
		;rep movsb
		;pop	ax
		;mov	ax, 100h
		;push	ax
		;retn
; ---------------------------------------------------------------------------
		END start
