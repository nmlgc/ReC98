		public @string@case_sensitive
; string::case_sensitive
@string@case_sensitive dw 1
		public @string@paranoid_check
; string::paranoid_check
@string@paranoid_check dw 0
		public @string@skip_white
; string::skip_white
@string@skip_white dw 1
		public @string@initial_capac
; string::initial_capac
@string@initial_capac dw 3Fh
		public @string@resize_inc
; string::resize_inc
@string@resize_inc dw 40h
		public @string@freeboard
; string::freeboard
@string@freeboard dw 3Fh
aStringReferenc	db 'String reference out of range',0
aStringRefere_0	db 'String reference out of range',0
aStringRefere_1	db 'String reference out of range',0
