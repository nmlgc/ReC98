public ARC_LOAD
arc_load	proc far

arg_0		= dword	ptr  6

		push	bp
		mov	bp, sp
		push	si
		push	di
		push	800h
		call	@$bnwa$qui
		pop	cx
		mov	word ptr _arc_pfs+2, dx
		mov	word ptr _arc_pfs, ax
		pushd	[bp+arg_0]
		call	file_ropen
		xor	si, si
		jmp	short loc_17102
; ---------------------------------------------------------------------------

loc_170EA:
		les	bx, [bp+arg_0]
		add	bx, si
		mov	al, es:[bx]
		mov	_arc_fn[si], al
		mov	bx, word ptr [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx], 0
		jz	short loc_17107
		inc	si

loc_17102:
		cmp	si, 0Dh
		jl	short loc_170EA

loc_17107:
		pushd	[_arc_pfs]
		push	800h
		call	file_read
		call	file_close
		xor	si, si
		jmp	short loc_17160
; ---------------------------------------------------------------------------

loc_1711D:
		mov	ax, si
		shl	ax, 5
		les	bx, _arc_pfs
		add	bx, ax
		cmp	byte ptr es:[bx], 0
		jz	short loc_17165
		xor	di, di
		jmp	short loc_1715A
; ---------------------------------------------------------------------------

loc_17132:
		mov	ax, si
		shl	ax, 5
		les	bx, _arc_pfs
		add	bx, ax
		cmp	byte ptr es:[bx+di+3], 0
		jz	short loc_1715F
		mov	ax, si
		shl	ax, 5
		les	bx, _arc_pfs
		add	bx, ax
		mov	al, es:[bx+di+3]
		not	al
		mov	es:[bx+di+3], al
		inc	di

loc_1715A:
		cmp	di, 0Dh
		jl	short loc_17132

loc_1715F:
		inc	si

loc_17160:
		cmp	si, 40h
		jl	short loc_1711D

loc_17165:
		mov	_arc_num_files, si
		pop	di
		pop	si
		pop	bp
		retf	4
arc_load	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public ARC_FREE
arc_free	proc far
		push	bp
		mov	bp, sp
		pushd	[_arc_pfs] ; font
		call	@$bdla$qnv
		add	sp, 4
		pop	bp
		retf
arc_free	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

@at_pos_of$qnxc	proc near

arg_0		= dword	ptr  4

		push	bp
		mov	bp, sp
		push	si
		xor	si, si
		jmp	short loc_171C2
; ---------------------------------------------------------------------------

loc_17189:
		les	bx, [bp+arg_0]
		add	bx, si
		mov	al, es:[bx]
		cbw
		push	ax
		call	_toupper
		pop	cx
		mov	dx, _file_num
		shl	dx, 5
		les	bx, _arc_pfs
		add	bx, dx
		push	ax
		mov	al, es:[bx+si+3]
		cbw
		pop	dx
		cmp	dx, ax
		jnz	short loc_171C7
		les	bx, [bp+arg_0]
		add	bx, si
		cmp	byte ptr es:[bx], 0
		jnz	short loc_171C1
		mov	ax, 1
		jmp	short loc_171C9
; ---------------------------------------------------------------------------

loc_171C1:
		inc	si

loc_171C2:
		cmp	si, 0Dh
		jl	short loc_17189

loc_171C7:
		xor	ax, ax

loc_171C9:
		pop	si
		pop	bp
		retn	4
@at_pos_of$qnxc	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

@crapt$qncui	proc near

arg_0		= word ptr  4
arg_2		= dword	ptr  6

		push	bp
		mov	bp, sp
		xor	dx, dx
		jmp	short loc_171E1
; ---------------------------------------------------------------------------

loc_171D5:
		les	bx, [bp+arg_2]
		add	bx, dx
		mov	al, _arc_key
		xor	es:[bx], al
		inc	dx

loc_171E1:
		cmp	dx, [bp+arg_0]
		jb	short loc_171D5
		pop	bp
		retn	6
@crapt$qncui	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

@cache_next$qv	proc near

var_1		= byte ptr -1

		enter	2, 0
		cmp	_cache_bytes_read, 0
		jnz	short loc_17202
		pushd	[_cache]
		push	100h
		call	file_read

loc_17202:
		les	bx, _cache
		add	bx, _cache_bytes_read
		mov	al, es:[bx]
		mov	[bp+var_1], al
		mov	al, _arc_key
		xor	[bp+var_1], al
		inc	_cache_bytes_read
		cmp	_cache_bytes_read, 100h
		jb	short loc_17228
		mov	_cache_bytes_read, 0

loc_17228:
		mov	al, [bp+var_1]
		leave
		retn
@cache_next$qv	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

@unrle$qui	proc near

var_C		= dword	ptr -0Ch
var_8		= dword	ptr -8
var_3		= byte ptr -3
var_2		= byte ptr -2
var_1		= byte ptr -1
arg_0		= word ptr  4

		enter	0Ch, 0
		mov	[bp+var_8], 0
		mov	[bp+var_C], 0
		call	@cache_next$qv
		mov	[bp+var_3], al
		inc	[bp+var_8]
		jmp	short loc_172C5
; ---------------------------------------------------------------------------

loc_1724D:
		les	bx, _file_data
		add	bx, word ptr [bp+var_C]
		mov	al, [bp+var_3]
		mov	es:[bx], al
		mov	[bp+var_1], al
		inc	[bp+var_C]
		call	@cache_next$qv
		mov	[bp+var_3], al
		inc	[bp+var_8]
		mov	al, [bp+var_1]
		cmp	al, [bp+var_3]
		jnz	short loc_1724D
		les	bx, _file_data
		add	bx, word ptr [bp+var_C]
		mov	al, [bp+var_3]

loc_1727D:
		mov	es:[bx], al
		inc	[bp+var_C]
		call	@cache_next$qv
		mov	[bp+var_2], al
		inc	[bp+var_8]
		jmp	short loc_172A4
; ---------------------------------------------------------------------------

loc_17290:
		les	bx, _file_data
		add	bx, word ptr [bp+var_C]
		mov	al, [bp+var_1]
		mov	es:[bx], al
		inc	[bp+var_C]
		dec	[bp+var_2]

loc_172A4:
		cmp	[bp+var_2], 0
		ja	short loc_17290
		call	@cache_next$qv
		mov	[bp+var_3], al
		inc	[bp+var_8]
		cmp	al, [bp+var_1]
		jnz	short loc_172C5
		les	bx, _file_data
		add	bx, word ptr [bp+var_C]
		mov	al, [bp+var_1]
		jmp	short loc_1727D
; ---------------------------------------------------------------------------

loc_172C5:
		movzx	eax, [bp+arg_0]
		cmp	eax, [bp+var_8]
		jg	loc_1724D
		leave
		retn	2
@unrle$qui	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public ARC_FILE_LOAD
arc_file_load	proc far

var_4		= byte ptr -4
var_3		= byte ptr -3
arg_0		= dword	ptr  6

		enter	4, 0
		push	si
		lea	ax, [bp+var_4]
		push	ss
		push	ax
		push	ds
		push	offset aRLE_TYPE
		mov	cx, 3
		call	SCOPY@
		mov	_file_num, 0
		xor	si, si
		jmp	short loc_17306
; ---------------------------------------------------------------------------

loc_172F6:
		pushd	[bp+arg_0]
		call	@at_pos_of$qnxc
		or	ax, ax
		jnz	short loc_1730C
		inc	_file_num
		inc	si

loc_17306:
		cmp	si, _arc_num_files
		jl	short loc_172F6

loc_1730C:
		mov	ax, _file_num
		shl	ax, 5
		mov	dx, word ptr _arc_pfs+2
		mov	bx, word ptr _arc_pfs
		add	bx, ax
		mov	word ptr _file_pf+2, dx
		mov	word ptr _file_pf, bx
		push	ds
		push	offset _arc_fn
		call	file_ropen
		les	bx, _file_pf
		pushd	dword ptr es:[bx+18h]
		push	0
		call	file_seek
		les	bx, _file_pf
		mov	al, es:[bx]
		cmp	al, [bp+var_4]
		jnz	short loc_17359
		mov	al, es:[bx+1]
		cmp	al, [bp+var_3]
		jnz	short loc_17359
		mov	_file_compressed, 1
		jmp	short loc_1735E
; ---------------------------------------------------------------------------

loc_17359:
		mov	_file_compressed, 0

loc_1735E:
		mov	_file_pos, 0
		les	bx, _file_pf
		push	word ptr es:[bx+14h]
		call	@$bnwa$qui
		pop	cx
		mov	word ptr _file_data+2, dx
		mov	word ptr _file_data, ax
		cmp	_file_compressed, 0
		jz	short loc_173B0
		push	100h
		call	@$bnwa$qui
		pop	cx
		mov	word ptr _cache+2, dx
		mov	word ptr _cache, ax
		mov	_cache_bytes_read, 0
		les	bx, _file_pf
		push	word ptr es:[bx+10h]
		call	@unrle$qui
		pushd	[_cache]
		call	@$bdla$qnv
		add	sp, 4
		jmp	short loc_173D2
; ---------------------------------------------------------------------------

loc_173B0:
		pushd	[_file_data]
		les	bx, _file_pf
		push	word ptr es:[bx+10h]
		call	file_read
		pushd	[_file_data]
		les	bx, _file_pf
		push	word ptr es:[bx+10h]
		call	@crapt$qncui

loc_173D2:
		call	file_close
		pop	si
		leave
		retf	4
arc_file_load	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public ARC_FILE_GET
arc_file_get	proc far

var_4		= dword	ptr -4
arg_0		= word ptr  6
arg_2		= dword	ptr  8

		enter	4, 0
		mov	eax, [bp+arg_2]
		mov	[bp+var_4], eax
		xor	dx, dx
		jmp	short loc_17415
; ---------------------------------------------------------------------------

loc_173EC:
		movzx	eax, _file_pos
		les	bx, _file_pf
		cmp	eax, es:[bx+14h]
		jge	short locret_1741A
		les	bx, _file_data
		add	bx, _file_pos
		mov	al, es:[bx]
		les	bx, [bp+var_4]
		add	bx, dx
		mov	es:[bx], al
		inc	_file_pos
		inc	dx

loc_17415:
		cmp	dx, [bp+arg_0]
		jb	short loc_173EC

locret_1741A:
		leave
		retf	6
arc_file_get	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public ARC_FILE_SEEK
arc_file_seek	proc far

arg_0		= byte ptr  6

		push	bp
		mov	bp, sp
		mov	al, [bp+arg_0]
		cbw
		mov	_file_pos, ax
		pop	bp
		retf	2
arc_file_seek	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame
public ARC_FILE_FREE
arc_file_free	proc far
		push	bp
		mov	bp, sp
		pushd	[_file_data]
		call	@$bdla$qnv
		add	sp, 4
		pop	bp
		retf
arc_file_free	endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

@arc_file_size$qv	proc far
		push	bp
		mov	bp, sp
		les	bx, _file_pf
		mov	ax, es:[bx+14h]
		pop	bp
		retf
@arc_file_size$qv	endp
