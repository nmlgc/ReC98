public GAIJI_LOAD
gaiji_load	proc near
		push	bp
		mov	bp, sp
		call	gaiji_backup
		call	gaiji_entry_bfnt pascal, ds, offset aMikoft_bft
		pop	bp
		retn
gaiji_load	endp


public GAIJI_FREE
gaiji_free	proc near
		push	bp
		mov	bp, sp
		call	gaiji_restore
		pop	bp
		retn
gaiji_free	endp
