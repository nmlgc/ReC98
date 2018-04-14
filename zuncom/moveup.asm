		.8086
		.model tiny
		.code
		org 100h ;doesn't matter, needed for linker
moveup:
		rep movsb
		pop	ax
		mov	ax, 100h
		push	ax
		retn
		END moveup
