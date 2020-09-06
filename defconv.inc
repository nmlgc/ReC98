if GAME ge 3
	proc_defconv macro NAM_UPPER:req, nam_lower:req
		endp_defconv macro
			NAM_UPPER endp
		endm
		public NAM_UPPER
		NAM_UPPER proc pascal
	endm
else
	proc_defconv macro NAM_UPPER:req, nam_lower:req
		endp_defconv macro
			_&nam_lower endp
		endm
		public _&nam_lower
		_&nam_lower proc c
	endm
endif
