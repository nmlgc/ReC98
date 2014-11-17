ext_exe	db	'.exe',0

; Unnecessary counter limiting the number of files in an archive.
; At every call to pfopen's SEEK function, this is reset, incremented
; for every file skipped when seeking to a particular one, and aborts
; once it reaches 255. Only actually used in TH02, though.
pf_limit	db 0
