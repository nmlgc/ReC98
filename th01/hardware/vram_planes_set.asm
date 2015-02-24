; void vram_planes_set(void)
vram_planes_set	proc
	push	bp
	mov	bp, sp
	mov	_VRAM_PLANE_B, 0A8000000h
	mov	_VRAM_PLANE_R, 0B0000000h
	mov	_VRAM_PLANE_G, 0B8000000h
	mov	_VRAM_PLANE_E, 0E0000000h
	pop	bp
	ret
vram_planes_set	endp
