		public _localeconv
_localeconv	proc far
		push	si
		push	di
		mov	dx, ds
		mov	ax, offset __localeconvention
		pop	di
		pop	si
		ret
_localeconv	endp
