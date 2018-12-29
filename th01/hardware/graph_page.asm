public _graph_showpage_func, _graph_accesspage_func
; void __cdecl graph_showpage_func(char page)
_graph_showpage_func	proc far

@@page		= byte ptr  6

	push	bp
	mov	bp, sp
	graph_showpage [bp+@@page]
	pop	bp
	retf
_graph_showpage_func	endp


; void __cdecl _graph_accesspage_func(char page)
_graph_accesspage_func	proc far
@@page		= word ptr  6

	push	bp
	mov	bp, sp
	mov	bx, [bp+@@page]
	mov	_graph_page, bl
	graph_accesspage bl
	pop	bp
	retf
_graph_accesspage_func	endp
