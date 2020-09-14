;
; +-------------------------------------------------------------------------+
; |   This file has been generated by The Interactive Disassembler (IDA)    |
; |        Copyright (c) 2009 by Hex-Rays, <support@hex-rays.com>           |
; +-------------------------------------------------------------------------+
;
; Input MD5   : 9466D867385BD4CC0A6FD3E3D4E9FB01

; File Name   : th04/ZUN.COM:MEMCHK (-M)
; Format      : MS-DOS COM-file
; Base Address: 0h Range: 100h-10E2h Loaded length: FE2h
; OS type   :  MS DOS
; Application type:  Executable 16bit

		.286

DGROUP	group _TEXT, _DATA

_TEXT		segment byte 'CODE' use16
		assume cs:_TEXT

; =============== S U B R O U T I N E =======================================

; Attributes: bp-based frame

; int __cdecl main(int argc, const char **argv, const char **envp)
public _main
_main  proc near

var_2		= word ptr -2
argc		= word ptr  4
argv		= word ptr  6
envp		= word ptr  8

		enter	2, 0
		call	sub_3B6
		mov	[bp+var_2], ax
		push	offset DGROUP:asc_E8E	; "空きメインメモリチェック\n\n"
		call	sub_38E
		cmp	[bp+var_2], 7530h
		ja	short loc_389
		push	offset DGROUP:aVVxvVSlvsvVvvi ; "ちょっと足りないかも、もう少し増やして"...
		call	sub_38E
		mov	ax, 0FFh
		leave
		retn
; ---------------------------------------------------------------------------

loc_389:
		xor	ax, ax
		leave
		retn
_main  endp
		db 0

; =============== S U B R O U T I N E =======================================


sub_38E  proc near
		mov	bx, sp
		mov	cx, si
		mov	si, ss:[bx+2]
		lodsb
		or	al, al
		jz	short loc_3B0
		mov	ah, 2

loc_39D:
		cmp	al, 0Ah
		jnz	short loc_3A7
		mov	dl, 0Dh
		int	21h		; DOS - DISPLAY OUTPUT
					; DL = character to send to standard output
		mov	al, 0Ah

loc_3A7:
		mov	dl, al
		int	21h		; DOS - DISPLAY OUTPUT
					; DL = character to send to standard output
		lodsb
		or	al, al
		jnz	short loc_39D

loc_3B0:
		mov	si, cx
		retn	2
sub_38E  endp
		nop

; =============== S U B R O U T I N E =======================================


sub_3B6  proc near
		mov	ah, 48h
		mov	bx, 0FFFFh
		int	21h		; DOS - 2+ - ALLOCATE MEMORY
					; BX = number of 16-byte paragraphs desired
		cmp	ax, 8
		jnz	short loc_3C6
		mov	ax, bx
		clc
		retn
; ---------------------------------------------------------------------------

loc_3C6:
		xor	ax, ax
		stc
		retn
sub_3B6  endp
_TEXT	ends

_DATA	segment byte 'DATA' use16
asc_E8E	db '空きメインメモリチェック',0Ah
	db 0Ah,0
aVVxvVSlvsvVvvi	db 'ちょっと足りないかも、もう少し増やしてから起動してね',0
_DATA	ends

		end
