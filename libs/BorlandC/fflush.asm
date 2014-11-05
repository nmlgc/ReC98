; int __cdecl fflush(FILE *fp)
public _fflush
_fflush		proc
@@count		= word ptr -2
@@fp		= DPTR_	2 + dPtrSize

		push	bp
		mov	bp, sp
		sub	sp, 2
		push	si
		push	di
if LDATA
		mov	ax, word ptr [bp+@@fp]
		or	ax, word ptr [bp+@@fp+2]
		jnz	short @@fflush_fp
		nopcall	_flushall
		jmp	@@fflush_ret_0

@@fflush_fp:
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+12h]
		cmp	ax, word ptr [bp+@@fp]
		jz	short @@fflush_level
		jmp	@@fflush_ret_eof

@@fflush_level:
		les	bx, [bp+@@fp]
		cmp	word ptr es:[bx], 0
		jl	short @@fflush_write
		test	byte ptr es:[bx+2], 8
		jnz	short @@fflush_no_unget
		mov	dx, es:[bx+0Eh]
		mov	ax, word ptr [bp+@@fp]
		add	ax, 5
		cmp	dx, word ptr [bp+@@fp+2]
		jz	short @@fflush_hold
		jmp	@@fflush_ret_0

@@fflush_hold:
		cmp	es:[bx+0Ch], ax
		jnz	short @@fflush_ret_0

@@fflush_no_unget:
		les	bx, [bp+@@fp]
		mov	word ptr es:[bx], 0
		mov	dx, es:[bx+0Eh]
		mov	ax, word ptr [bp+@@fp]
		add	ax, 5
		cmp	dx, word ptr [bp+@@fp+2]
		jnz	short @@fflush_ret_0
		cmp	es:[bx+0Ch], ax
		jnz	short @@fflush_ret_0
		mov	dx, es:[bx+0Ah]
		mov	ax, es:[bx+8]
		mov	es:[bx+0Eh], dx
		mov	es:[bx+0Ch], ax
		jmp	short @@fflush_ret_0

@@fflush_write:
		les	bx, [bp+@@fp]
		mov	ax, es:[bx+6]
		add	ax, es:[bx]
		inc	ax
		mov	[bp+@@count], ax
		sub	es:[bx], ax
		push	ax
		mov	dx, es:[bx+0Ah]
		mov	ax, es:[bx+8]
		mov	es:[bx+0Eh], dx
		mov	es:[bx+0Ch], ax
		push	dx
		push	ax
		mov	al, es:[bx+4]
		cbw
		push	ax
		nopcall	___write
		add	sp, 8
		cmp	ax, [bp+@@count]
		jz	short @@fflush_ret_0
		les	bx, [bp+@@fp]
		test	byte ptr es:[bx+3], 2
		jnz	short @@fflush_ret_0
		or	word ptr es:[bx+2], 10h
else
		cmp	[bp+@@fp], 0
		jnz	short @@fflush_fp
		call	_flushall
		jmp	short @@fflush_ret_0

@@fflush_fp:
		mov	bx, [bp+@@fp]
		mov	ax, [bx+0Eh]
		cmp	ax, [bp+@@fp]
		jnz	short @@fflush_ret_eof
		mov	bx, [bp+@@fp]
		cmp	word ptr [bx], 0
		jl	short @@fflush_write
		test	byte ptr [bx+2], 8
		jnz	short @@fflush_no_unget
		mov	ax, [bp+@@fp]
		add	ax, 5
		cmp	[bx+0Ah], ax
		jnz	short @@fflush_ret_0

@@fflush_no_unget:
		mov	bx, [bp+@@fp]
		mov	word ptr [bx], 0
		mov	ax, [bp+@@fp]
		add	ax, 5
		cmp	[bx+0Ah], ax
		jnz	short @@fflush_ret_0
		mov	ax, [bx+8]
		mov	[bx+0Ah], ax
		jmp	short @@fflush_ret_0

@@fflush_write:
		mov	bx, [bp+@@fp]
		mov	ax, [bx+6]
		add	ax, [bx]
		inc	ax
		mov	[bp+@@count], ax
		sub	[bx], ax
		push	ax		; len
		mov	ax, [bx+8]
		mov	[bx+0Ah], ax
		push	ax		; buf
		mov	al, [bx+4]
		cbw
		push	ax		; handle
		call	___write
		add	sp, 6
		cmp	ax, [bp+@@count]
		jz	short @@fflush_ret_0
		mov	bx, [bp+@@fp]
		test	byte ptr [bx+3], 2
		jnz	short @@fflush_ret_0
		or	word ptr [bx+2], 10h
endif

@@fflush_ret_eof:
		mov	ax, 0FFFFh
		jmp	short @@fflush_ret

@@fflush_ret_0:
		xor	ax, ax

@@fflush_ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_fflush		endp
