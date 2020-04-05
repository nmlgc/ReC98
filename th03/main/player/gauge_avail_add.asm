public GAUGE_AVAIL_ADD
gauge_avail_add	proc near

@@charge		= byte ptr  4
@@pid		= byte ptr  6

	push	bp
	mov	bp, sp
	push	si
	mov	al, [bp+@@pid]
	mov	ah, 0
	shl	ax, 7
	add	ax, offset _players
	mov	si, ax
	cmp	[si+player_t.hyper_active], 0
	jnz	short @@ret
	cmp	[si+gauge_avail], GAUGE_MAX
	jnb	short @@ret
	mov	al, [bp+@@charge]
	mov	ah, 0
	add	[si+gauge_avail], ax
	cmp	[si+gauge_avail], GAUGE_MAX
	jbe	short @@ret
	mov	[si+gauge_avail], GAUGE_MAX

@@ret:
	pop	si
	pop	bp
	retn	4
gauge_avail_add	endp
