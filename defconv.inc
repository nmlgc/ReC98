if GAME ge 3
	proc_defconv macro nam
		endp_defconv macro nam
			&nam endp
		endm
		public nam
		nam proc pascal
	endm
else
	proc_defconv macro nam
		endp_defconv macro nam
			_&nam endp
		endm
		public _&nam
		_&nam proc c
	endm
endif
