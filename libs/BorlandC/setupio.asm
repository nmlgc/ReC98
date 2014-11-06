; void near _setupio( void )
public __setupio
__setupio proc near

		push	si
		push	di
if LDATA
		mov	cx, 5
else
		mov	dx, 5
endif
		jmp	short @@loc_43AC
; ---------------------------------------------------------------------------

@@loc_438A:
if LDATA
		mov	bx, cx
else
		mov	bx, dx
endif
		add	bx, bx
		mov	_openfd[bx], 0
if LDATA
		mov	ax, _NFILE
		imul	cx
		mov	dx, ax
		mov	bx, ax
		mov	_streams.fd[bx], -1
		add	ax, offset _streams
		mov	bx, dx
		mov	_streams.token[bx], ax
		inc	cx
else
		mov	bx, dx
		mov	cl, 4
		shl	bx, cl
		mov	_streams.fd[bx], -1
		mov	ax, dx
		shl	ax, cl
		add	ax, offset _streams
		mov	bx, dx
		shl	bx, cl
		mov	_streams.token[bx], ax
		inc	dx
endif

@@loc_43AC:
if LDATA
		cmp	cx, __nfile
else
		cmp	dx, __nfile
endif
		jb	short @@loc_438A
		mov	al, stdin.fd
		cbw
		push	ax		; handle
		nopcall	_isatty
		pop	cx
		or	ax, ax
		jnz	short @@loc_43C7
		and	stdin.flags, 0FDFFh

@@loc_43C7:
		mov	ax, 200h
		push	ax		; size
		test	byte ptr stdin.flags+1, 2
		jz	short @@loc_43D7
		mov	ax, 1
		jmp	short @@loc_43D9
; ---------------------------------------------------------------------------

@@loc_43D7:
		xor	ax, ax

@@loc_43D9:
		push	ax		; type
		xor	ax, ax
		push	ax		; buf
if LDATA
		push	ax
		push	ds
		mov	ax, offset stdin
		push	ax		; stream
		nopcall	_setvbuf
		add	sp, 0Ch
else
		mov	ax, offset stdin
		push	ax		; stream
		call	_setvbuf
		add	sp, 8
endif
		mov	al, stdout.fd
		cbw
		push	ax		; handle
		nopcall	_isatty
		pop	cx
		or	ax, ax
		jnz	short @@loc_4400
		and	stdout.flags, 0FDFFh

@@loc_4400:
		mov	ax, 200h
		push	ax		; size
		test	byte ptr stdout.flags+1, 2
		jz	short @@loc_4410
		mov	ax, 2
		jmp	short @@loc_4412
; ---------------------------------------------------------------------------

@@loc_4410:
		xor	ax, ax

@@loc_4412:
		push	ax		; type
		xor	ax, ax
		push	ax		; buf
if LDATA
		push	ax
		push	ds
		mov	ax, offset stdout
		push	ax		; stream
		nopcall	_setvbuf
		add	sp, 0Ch
else
		mov	ax, offset stdout
		push	ax		; stream
		call	_setvbuf
		add	sp, 8
endif
		pop	di
		pop	si
		retn
__setupio	endp
