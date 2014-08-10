; int bfill(bf_t bf);
public bfill

bfill		proc far

@@bf		= word ptr  6

		push	bp
		mov	bp, sp
		push	ds
		mov	ds, [bp+@@bf]
		mov	bx, ds:[0]
		mov	cx, ds:[6]
		mov	dx, 8
		mov	ah, 3Fh
		int	21h		; DOS -	2+ - READ FROM FILE WITH HANDLE
					; BX = file handle, CX = number	of bytes to read
					; DS:DX	-> buffer
		jb	short @@_error
		or	ax, ax
		jz	short @@_error
		dec	ax
		mov	ds:[2], ax
		mov	word ptr ds:[4], 1
		mov	al, byte ptr ds:[8]
		xor	ah, ah
		pop	ds
		pop	bp
		retf	2
; ---------------------------------------------------------------------------

@@_error:
		xor	ax, ax
		mov	ds:[2], ax
		dec	ax
		pop	ds
		pop	bp
		retf	2
bfill		endp
