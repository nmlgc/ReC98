public PIANO_LABEL_PUT_RAW
piano_label_put_raw	proc near
	xor	ah, ah
	shl	al, 3
	add	ax, offset _PIANO_LABEL_FONT
	mov	si, ax
	mov	cx, PIANO_LABEL_FONT_H

@@row_loop:
	movsb
	add	di, ROW_SIZE - 1
	loop	@@row_loop
	retn
piano_label_put_raw	endp
