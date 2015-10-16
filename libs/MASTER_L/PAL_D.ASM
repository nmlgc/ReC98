	public _PaletteTone,PaletteTone
PaletteTone label word
_PaletteTone	dw 100

	public _PalettesInit,PalettesInit
PalettesInit label byte
		;	 R,   G,   B
_PalettesInit	db	000h,000h,000h	; 0
		db	000h,000h,0FFh	; 1
		db	0FFh,000h,000h	; 2
		db	0FFh,000h,0FFh	; 3
		db	000h,0FFh,000h	; 4
		db	000h,0FFh,0FFh	; 5
		db	0FFh,0FFh,000h	; 6
		db	0FFh,0FFh,0FFh	; 7
		db	077h,077h,077h	; 8
		db	000h,000h,0AAh	; 9
		db	0AAh,000h,000h	; 10
		db	0AAh,000h,0AAh	; 11
		db	000h,0AAh,000h	; 12
		db	000h,0AAh,0AAh	; 13
		db	0AAh,0AAh,000h	; 14
		db	0AAh,0AAh,0AAh	; 15

	public _PaletteNote,PaletteNote
PaletteNote label word
_PaletteNote	dw	0

	public _ResPalSeg,ResPalSeg
ResPalSeg label word
_ResPalSeg	dw	0

	public _SdiExists,SdiExists
SdiExists label word
_SdiExists	dw	0
