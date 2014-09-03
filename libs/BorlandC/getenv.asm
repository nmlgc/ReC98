; char *__cdecl	getenv(const char *nameP)
_getenv		proc DIST
@@envP		= DPTR_ -(dPtrSize)
@@nameP		= DPTR_ 2 + dPtrSize

		push	bp
		mov	bp, sp
		sub	sp, dPtrSize
		push	si
		push	di
		LES_	di, [bp+@@nameP]
if LDATA
		mov	ax, es
		or	ax, di
else
		push	ds
		pop	es
		or	di, di
endif
		jz	short @@VarNotFound
		mov	al, 0
		mov	ah, ES_[di]
		mov	cx, -1
		cld
		repne scasb
		not	cx
		dec	cx
		jz	short @@VarNotFound

ifdef __HUGE__
		mov	di, seg environ@
		mov	ds, di
endif
		LES_	di, environ@
if LDATA
		mov	word ptr [bp+@@envP+2], es
		mov	bx, es
		or	bx, di
else
		or	di, di
endif
		mov	word ptr [bp+@@envP], di
		jnz	short @@FirstVariable

@@VarNotFound:
		xor	dx, dx
		xor	ax, ax
		jmp	short @@ret

@@NextVariable:
		add	word ptr [bp+@@envP], dPtrSize
		LES_	di, [bp+@@envP]

@@FirstVariable:
		LES_	di, ES_[di]
if LDATA
		mov	bx, es
		or	bx, di
else
		or	di, di
endif
		jz	short @@VarNotFound
		mov	al, ES_[di]
		or	al, al
		jz	short @@VarNotFound
		cmp	ah, al
		jnz	short @@NextVariable
		mov	bx, cx
		cmp	byte ptr es:[bx+di], '='
		jnz	short @@NextVariable
		pushDS_
		LDS_	si, [bp+@@nameP]
		repe cmpsb
		popDS_
		xchg	cx, bx
		jne	short @@NextVariable
		inc	di
		mov	ax, di
		mov	dx, es

@@ret:
		pop	di
		pop	si
		mov	sp, bp
		pop	bp
		ret
_getenv		endp
