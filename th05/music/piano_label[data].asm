PIANO_LABEL_FONT_H = 8

public _PIANO_LABEL_FONT
_PIANO_LABEL_FONT label byte
pl_F = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	  111111b
	db	 1100000b
	db	11000000b
	db	11111110b
	db	10000000b
	db	10000000b
	db	11000000b
	db	 1000000b
pl_M = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	 1100110b
	db	10101001b
	db	10011001b
	db	10000001b
	db	10000001b
	db	10000001b
	db	11000011b
	db	 1000010b
pl_1 = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	  111100b
	db	     100b
	db	     100b
	db	     100b
	db	     100b
	db	     100b
	db	    1100b
	db	    1000b
pl_2 = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	  111100b
	db	 1000010b
	db	10000001b
	db	        1
	db	     110b
	db	   11000b
	db	 1100001b
	db	 1111110b
pl_3 = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	  111100b
	db	 1000010b
	db	        1
	db	    1110b
	db	        1
	db	11000001b
	db	 1000010b
	db	 1111100b
pl_4 = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	    1100b
	db	   10010b
	db	  100010b
	db	 1000010b
	db	 1000010b
	db	 1111111b
	db	      10b
	db	      10b
pl_5 = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	  111110b
	db	 1000000b
	db	10000000b
	db	10111100b
	db	 1000010b
	db	        1
	db	10000010b
	db	 1111100b
pl_S = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	 1111110b
	db	11000001b
	db	10000000b
	db	 1110000b
	db	    1110b
	db	        1
	db	10000011b
	db	 1111110b
pl_G = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
	db	  111110b
	db	 1100011b
	db	11000000b
	db	10000000b
	db	10000110b
	db	11000001b
	db	 1100011b
	db	  111100b
pl_COUNT = ($ - _PIANO_LABEL_FONT) / PIANO_LABEL_FONT_H
