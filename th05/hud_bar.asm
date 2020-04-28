	.186	; The 8086 couldn't into PUSH imm8?!
	locals

include libs/master.lib/master.inc
include th02/main/hud/hud.inc
include th04/gaiji/gaiji.inc

extrn _hud_gaiji_row:byte:HUD_TRAM_W

; ----------------------------------------------------------------------------

MAIN_01_TEXT	segment	word public 'CODE' use16
	assume cs:MAIN_01_TEXT

; void pascal near hud_bar_put(
; 	unsigned int y, unsigned char value, unsigned int atrb
; );
public HUD_BAR_PUT
HUD_BAR_PUT	proc near
@@atrb	= word ptr ss:[bx+2]
@@value	= byte ptr ss:[bx+4]
@@y    	= word ptr ss:[bx+6]

	mov	bx, sp
	push	di
	push	ds
	pop	es
	mov	di, offset _hud_gaiji_row
	push	HUD_X
	push	@@y
	push	ds
	push	di
	push	@@atrb
	mov	al, g_BAR_MAX
	mov	cx, HUD_TRAM_W
	mov	bl, @@value
	cmp	bl, BAR_MAX
	jb	short @@below_max

@@at_max:
	stosb
	inc	al
	loop	@@at_max
	jmp	short @@put
; ---------------------------------------------------------------------------

@@below_max:
	mov	dl, bl
	dec	al
	jmp	short @@cell_still_fully_filled?
; ---------------------------------------------------------------------------

@@cell_is_fully_filled:
	stosb

@@cell_still_fully_filled?:
	dec	cx
	sub	dl, BAR_GAIJI_MAX
	jg	short @@cell_is_fully_filled
	mov	al, bl
	dec	al
	and	al, BAR_GAIJI_MAX - 1
	add	al, G_BAR
	stosb
	mov	al, g_EMPTY
	rep stosb

@@put:
	call	GAIJI_PUTSA
	pop	di
	retn	6
HUD_BAR_PUT	endp
MAIN_01_TEXT	ends

	end
