; int __cdecl stricmp(const char *s1, const char *s2)
public _stricmp
_stricmp	proc far

@@s1		= dword	ptr  6
@@s2		= dword	ptr  0Ah

		push	bp
		mov	bp, sp
		push	si
		push	di
		mov	dx, ds
		cld
		lds	si, [bp+@@s1]
		les	di, [bp+@@s2]
		xor	ax, ax
		mov	bx, ax
		mov	cx, 617Ah ; CH = 'a',  CL = 'z'

@@cmi_nextCh:
		lodsb
		mov	bl, es:[di]
		or	al, al
		jz	short @@cmi_end
		scasb
		jz	short @@cmi_nextCh
		cmp	al, ch
		jb	short @@cmi_blUpper
		cmp	al, cl
		ja	short @@cmi_blUpper
		sub	al, 20h	; ' '

@@cmi_blUpper:
		cmp	bl, ch
		jb	short @@cmi_compareAgain
		cmp	bl, cl
		ja	short @@cmi_compareAgain
		sub	bl, 20h	; ' '

@@cmi_compareAgain:
		cmp	al, bl
		jz	short @@cmi_nextCh

@@cmi_end:
		sub	ax, bx
		mov	ds, dx
		pop	di
		pop	si
		pop	bp
		retf
_stricmp	endp
