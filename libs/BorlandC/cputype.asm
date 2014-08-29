cputype		proc near
		pushf
		pop	bx
		mov	ax, 0FFFh
		and	ax, bx
		push	ax
		popf
		pushf
		pop	ax
		and	ax, 0F000h
		cmp	ax, 0F000h
		mov	__8086,	0
		jz	short @@ret
		or	bx, 0F000h
		push	bx
		popf
		pushf
		pop	ax
		and	ax, 0F000h
		mov	__8086,	2
		jz	short @@ret
		mov	edx, esp
		and	sp, 0FFFCh
		pushfd
		pop	eax
		mov	ecx, eax
		xor	eax, 40000h
		push	eax
		popfd
		pushfd
		pop	eax
		xor	eax, ecx
		mov	__8086,	3
		mov	esp, edx
		jz	short @@ret
		mov	__8086,	4

@@ret:
		retn
cputype		endp
