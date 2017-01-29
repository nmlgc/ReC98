; Masks the bits of an 1bpp image word that should be written to the first
; VRAM word if that image should be positioned at X = (array_index % 16).
WORD_PUT_PATTERN label word
	db 11111111b, 11111111b
	db 01111111b, 11111111b
	db 00111111b, 11111111b
	db 00011111b, 11111111b
	db 00001111b, 11111111b
	db 00000111b, 11111111b
	db 00000011b, 11111111b
	db 00000001b, 11111111b
	db 00000000b, 11111111b
	db 00000000b, 01111111b
	db 00000000b, 00111111b
	db 00000000b, 00011111b
	db 00000000b, 00001111b
	db 00000000b, 00000111b
	db 00000000b, 00000011b
	db 00000000b, 00000001b
