if GAME ge 3
	proc_defconv macro nam_lower:req, NAM_UPPER:req
		endp_defconv macro
			NAM_UPPER endp
		endm
		public NAM_UPPER
		NAM_UPPER proc pascal far
	endm
else
	proc_defconv macro nam_lower:req, NAM_UPPER:req
		endp_defconv macro
			_&nam_lower endp
		endm
		public _&nam_lower
		_&nam_lower proc c far
	endm
endif
