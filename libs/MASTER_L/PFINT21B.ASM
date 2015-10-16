parfilename	db	128 dup(?)
;filename	db	128 dup(?)
pfint21_pf		dw	?
pfint21_handle		dw	?
if GAME ge 3
; Segment containing the decrypted entry headers.
pfint21_entries	dw ?
endif
