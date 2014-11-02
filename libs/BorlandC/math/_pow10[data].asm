e0to7		dd 1.0,	1.0e1, 1.0e2, 1.0e3, 1.0e4, 1.0e5, 1.0e6, 1.0e7

; Exponents > 4932 become infinities.  Exponents < -4932 become 0.

; These values have been calculated with extra precision to ensure
; that the last bit is rounded correctly.
e8    	dd 1.0e8
e16   	dq 1.0e16
e32   	dw 0B59Eh, 02B70h, 0ADA8h, 09DC5h, 04069h
e64   	dw 0A6D5h, 0FFCFh, 01F49h, 0C278h, 040D3h
e128  	dw 08CE0h, 080E9h, 047C9h, 093BAh, 041A8h
e256  	dw 0DE8Eh, 09DF9h, 0EBFBh, 0AA7Eh, 04351h
e512  	dw 091C7h, 0A60Eh, 0A0AEh, 0E319h, 046A3h
e1024	dw 00C17h, 08175h, 07586h, 0C976h, 04D48h
e2048	dw 05DE5h, 0C53Dh, 03B5Dh, 09E8Bh, 05A92h
e4096	dw 0979Bh, 08A20h, 05202h, 0C460h, 07525h
eINF	dd 7F800000h
