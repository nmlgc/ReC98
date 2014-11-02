__realcvt	proc near
ifdef __HUGE__
		mov	es, cs:DGROUP@@
		jmp	es:[__RealCvtVector]
else
		jmp	[__RealCvtVector]
endif
__realcvt	endp
