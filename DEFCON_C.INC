proc_defconv macro nam
	endp_defconv macro nam
		_&nam endp
	endm
	public _&nam
	_&nam proc c
endm
