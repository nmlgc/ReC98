	public mem_TopSeg, mem_MyOwn, mem_AllocID, mem_Reserve
	public _mem_TopSeg, _mem_MyOwn, _mem_AllocID, _mem_Reserve

_mem_TopSeg label word
mem_TopSeg	dw	0
	public mem_MyOwn
_mem_MyOwn label word
mem_MyOwn	dw	0

	public mem_AllocID
_mem_AllocID label word
mem_AllocID	dw	0

	public mem_Reserve
_mem_Reserve label word
mem_Reserve	dw	256		; 4096 bytes空ける
