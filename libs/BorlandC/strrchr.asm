; int __cdecl __far strrchr(char *s, char c)
public _strrchr
_strrchr	proc far

@@ss		= dword	ptr -4
@@s		= dword	ptr  6
@@c		= byte ptr  0Ah

		push	bp
		mov	bp, sp
		sub	sp, 4
		push	si
		push	di
		push	word ptr [bp+@@s+2]
		push	word ptr [bp+@@s]	; s
		nopcall	_strlen
		pop	cx
		pop	cx
		inc	ax
		mov	cx, ax
		mov	dx, word ptr [bp+@@s+2]
		mov	ax, word ptr [bp+@@s]
		add	ax, cx
		mov	word ptr [bp+@@ss+2], dx
		mov	word ptr [bp+@@ss], ax
		jmp	short @@loc_5DF9
; ---------------------------------------------------------------------------

@@loc_5DE2:
		dec	word ptr [bp+@@ss]
		les	bx, [bp+@@ss]
		mov	al, es:[bx]
		cmp	al, [bp+@@c]
		jnz	short @@loc_5DF8
		mov	dx, word ptr [bp+@@ss+2]
		mov	ax, word ptr [bp+@@ss]
		jmp	short @@loc_5E01
; ---------------------------------------------------------------------------

@@loc_5DF8:
		dec	cx

@@loc_5DF9:
		or	cx, cx
		jnz	short @@loc_5DE2
		xor	dx, dx
		xor	ax, ax

@@loc_5E01:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		retf
_strrchr	endp
