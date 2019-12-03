PIANO_X = 384
PIANO_Y = 64
PIANO_H = 15
PIANO_PADDING_BOTTOM = 3
PIANO_H_PADDED = (PIANO_H + PIANO_PADDING_BOTTOM)

PIANO_LABEL_DIST_X = 32
PIANO_LABEL_DIST_Y = 4

PIANO_LABEL_X = PIANO_X - PIANO_LABEL_DIST_X
PIANO_LABEL_Y = PIANO_Y + PIANO_LABEL_DIST_Y

piano_label_puts	macro row:req, chr1:req, chr2:req, chr3:req
	piano_label_putc	0, row, chr1
	piano_label_putc	1, row, chr2
	piano_label_putc	2, row, chr3
endm

piano_label_putc	macro col:req, row:req, chr:req
	mov 	al, chr
	mov 	di, ((PIANO_LABEL_Y + (row * PIANO_H_PADDED)) * ROW_SIZE) + ((PIANO_LABEL_X + (col * PIANO_LABEL_FONT_W)) / 8)
	call	piano_label_put_raw
endm
