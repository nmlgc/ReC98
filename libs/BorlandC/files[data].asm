FILE	struc ; (standard type)
level		dw ?
flags		dw ?
fd		db ?
hold		db ?
_bsize		dw ?	; Yes, calling it just "bsize" crashes TASM.
dPtr@		buffer, ?
dPtr@		curp, ?
istemp		dw ?
token		dw ?	; offset (dseg)
ends

; FILE _streams [_NFILE_]
_streams	label byte
stdin		FILE <0, 209h, 0, 0, 0, 0, 0, 0, offset stdin>
stdout		FILE <0, 20Ah, 1, 0, 0, 0, 0, 0, offset stdout>
stderr		FILE <0, 202h, 2, 0, 0, 0, 0, 0, offset stderr>
stdaux		FILE <0, 243h, 3, 0, 0, 0, 0, 0, offset stdaux>
stdprn		FILE <0, 242h, 4, 0, 0, 0, 0, 0, offset stdprn>
files		FILE 15 dup(<0>)

 ; unsigned int _nfile
__nfile		dw 20
; unsigned int _openfd[_NFILE_]
_openfd		dw 6001h
		dw 6002h
		dw 6002h
		dw 0A004h
		dw 0A002h
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
		dw  0
