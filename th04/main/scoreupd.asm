	.386
	locals

include libs/master.lib/master.inc
include th02/main/hud/hud.inc
include th04/main/hud/overlay.inc
include th02/score.inc
include th02/gaiji/boldfont.inc

SCORE_DIGIT_HIGHEST = SCORE_DIGITS - 1
; Also ignoring the last digit. (= 61,110 points)
SCORE_DELTA_FRAME_LIMIT = 6111
if SCORE_DELTA_FRAME_LIMIT ge 100000
	.err "SCORE_DELTA_FRAME_LIMIT can't have more than 5 decimal digits"
endif

; Declaring everything here rather than inside a segment avoids fixup
; overflows… yup.

	extrn _score:byte:SCORE_DIGITS
	extrn _hiscore:byte:SCORE_DIGITS
	extrn _hiscore_popup_shown:byte
	extrn _score_delta:dword
	extrn _score_delta_frame:dword

	extrn _FIVE_DIGIT_POWERS_OF_10:word

	extrn _hud_gaiji_row:byte:SCORE_DIGITS

	extrn _overlay_popup_id_new:byte
	extrn _overlay2:word
	@OVERLAY_POPUP_UPDATE_AND_RENDER$QV procdesc near

if GAME eq 4
	extrn _score_unused:byte
	extrn _temp_lebcd:byte

	MAIN_01 group MAIN_0_TEXT
	MAIN_0_TEXT	segment byte public 'CODE' use16
		SCORE_EXTEND_UPDATE_AND_RENDER procdesc near
	MAIN_0_TEXT ends
else
	_temp_lebcd equ _hud_gaiji_row
endif

MAIN_01 group MAIN_01_TEXT

; ----------------------------------------------------------------------------

MAIN_01_TEXT	segment	word public 'CODE' use16
	assume cs:MAIN_01

; ============================================================================

; Renders both the current and high score. In contrast to TH02, it also
; displays the continues digit.

; void pascal near hud_score_put(void);
public HUD_SCORE_PUT
HUD_SCORE_PUT	proc pascal near
@@gaiji_p equ bx
@@score_p equ si
@@y equ di

	push	si
	push	di

	mov	@@score_p, offset _hiscore[SCORE_DIGIT_HIGHEST]
	mov	@@y, 4

@@lebcd_to_gaiji:
	mov	cx, SCORE_DIGITS
	mov	@@gaiji_p, offset _hud_gaiji_row

@@digit_loop:
	mov	al, [@@score_p]
	add	al, GB_DIGITS
	mov	[@@gaiji_p], al
	inc	@@gaiji_p
	dec	@@score_p
	loop	@@digit_loop
	call	GAIJI_PUTSA pascal, HUD_LEFT, @@y, ds, offset _hud_gaiji_row, TX_WHITE
	add	@@y, 2

	; Put exactly two lines, high score at (56, 4), and current score at
	; (56, 6).
	; You might notice that @@score_p is only assigned once. Yes, the code
	; assumes that @@score_p now points at the end of _score, which in turn
	; assumes it's placed exactly before _hiscore in memory, with no padding.
	cmp	@@y, 6
	jz	@@lebcd_to_gaiji

	; And if that wasn't enough already, ZUN pops the registers in the wrong
	; order. Good thing it doesn't matter for any caller of this function!
	;
	; This could have easily been fixed by either defining two (or better,
	; three) LOCAL variables, or the USES directive if you *really* insist on
	; using registers. Both of which would have automatically inserted the
	; correct cleanup instructions before RET. Even in the 90's, "using an
	; assembler" did very much *not* mean "having to manually spell out every
	; instruction executed on the CPU"…
	pop	si
	pop	di
	ret
HUD_SCORE_PUT	endp

; ============================================================================

; void pascal near score_update_and_render(void);
public SCORE_UPDATE_AND_RENDER
SCORE_UPDATE_AND_RENDER	proc near

; The TH04 version is functionally identical, just less optimized.
if GAME eq 5
	@@delta_remaining_word equ dx
	@@delta_remaining_char equ dl
else
	@@delta_remaining_word equ cx
	@@delta_remaining_char equ cl
endif

	mov	eax, _score_delta
	or	eax, eax
	jz	short @@ret
	cmp	_score_delta_frame, eax
	jbe	short @@calculate_frame_delta
	mov	word ptr _score_delta_frame, ax

@@calculate_frame_delta:
	shr	eax, 5
	or	eax, eax
	jnz	short @@clamp_delta_to_frame_limit
	inc	ax
	jmp	short @@prefer_larger_delta

@@clamp_delta_to_frame_limit:
	cmp	eax, SCORE_DELTA_FRAME_LIMIT
	jbe	short @@prefer_larger_delta
	mov	ax, SCORE_DELTA_FRAME_LIMIT

@@prefer_larger_delta:
	cmp	word ptr _score_delta_frame, ax
	jnb	short @@commit_frame_delta
	mov	word ptr _score_delta_frame, ax

@@commit_frame_delta:
	mov	@@delta_remaining_word, word ptr _score_delta_frame
	jmp	short @@update
; ---------------------------------------------------------------------------

@@render:
	cmp	_hiscore_popup_shown, 0
	jnz	short @@subtract_frame_delta_and_render
	or	al, al
	jz	short @@subtract_frame_delta_and_render
	mov	_hiscore_popup_shown, 1
	mov	_overlay_popup_id_new, POPUP_ID_HISCORE_ENTRY
	mov	_overlay2, offset @overlay_popup_update_and_render$qv

@@subtract_frame_delta_and_render:
	mov	eax, _score_delta_frame
	sub	_score_delta, eax
	call	HUD_SCORE_PUT
if GAME eq 4
	mov	_score_unused, 0
	call	SCORE_EXTEND_UPDATE_AND_RENDER
endif

@@ret:
	retn
; ---------------------------------------------------------------------------
	even

@@update:
	push	si
	push	di
if GAME eq 5
	push	ds
	pop	es

	@@bcd_p equ di
	@@po10_p equ bx

	; Since the delta can have at most 5 digits, we only have to work on the
	; range from _temp_lebcd[4] (highest) to _temp_lebcd[0] (lowest).
	; Zeroing the remaining 3 digits is simply more convenient to do in a
	; single 32-bit instruction if _temp_lebcd[4] is also (unnecessarily)
	; zeroed.
	mov	dword ptr _temp_lebcd[4], 0
else
	@@bcd_p equ bx
	@@po10_p equ si
endif
	mov	@@bcd_p, offset _temp_lebcd[4]
	mov	@@po10_p, offset _FIVE_DIGIT_POWERS_OF_10
if GAME eq 5
	; 4 divisions, the units place doesn't need a separate one.
	mov	cx, 4
endif

@@delta_to_bcd:
	mov	ax, @@delta_remaining_word
	; 16-bit DIV interprets DX:AX as a 32-bit divisor…
	xor	dx, dx
	; … and returns the remainder in DX, so we actually aren't losing
	; anything here.
	div	word ptr [@@po10_p]
if GAME eq 5
	add	@@po10_p, 2
else
	mov	@@delta_remaining_word, dx
endif

	mov	[@@bcd_p], al
	dec	@@bcd_p

if GAME eq 5
	loop	@@delta_to_bcd
else
	add	@@po10_p, 2
	cmp	word ptr [@@po10_p], 1
	ja	@@delta_to_bcd
endif

@@last_digit:
	mov	[@@bcd_p], @@delta_remaining_char

	; Obviously skipping the continues digit…
	mov	si, offset _score[1]
	; … and the last one seen from there doesn't need special BCD treatment
	; either.
	mov	cx, SCORE_DIGITS - 2
	; Yes, completely unnecessary in TH05, considering the next instruction.
	xor	ah, ah

	; @@bcd_p == _temp_lebcd[0]
@@add_next_digit_to_score:
if GAME eq 5
	movzx	ax, byte ptr [@@bcd_p]
else
	mov	al, [@@bcd_p]
endif
	add	al, [si]
	aaa	; AL < 9, AH = carry
	mov	[si], al
	inc	@@bcd_p
	inc	si
	; Add the carry to next score digit. May now be 0Ah, but who cares, it's
	; fixed via AAA on the next digit anyway… *except* if it's already the
	; highest one, which is exactly where the infamous >100 million score
	; glitch comes from.
	add	[si], ah
if GAME eq 4
	mov	ah, 0
endif
	loop	@@add_next_digit_to_score
	mov	al, [@@bcd_p]
	add	[si], al

	; Is this the high score?
@@is_hiscore equ dl ; Never read, though

if GAME eq 4
	push	ds
	pop	es
;	assume es:_DATA
endif
	mov	si, offset _score[SCORE_DIGIT_HIGHEST]
	mov	di, offset _hiscore[SCORE_DIGIT_HIGHEST]
	xor	@@is_hiscore, @@is_hiscore
	mov	cx, SCORE_DIGITS
	cmp	_hiscore_popup_shown, 0
	jnz	short @@hiscore_confirmed

@@check_next_digit_for_hiscore:
	mov	al, [si]
	cmp	[di], al
	ja	short @@hiscore_denied
	jb	short @@hiscore_confirmed
	dec	di
	dec	si
	loop	@@check_next_digit_for_hiscore

@@hiscore_confirmed:
	; Copy the remaining number of digits in CX, backwards (STD!)
if GAME eq 5
	cli
endif
	std
	rep movsb
	cld
if GAME eq 5
	sti
endif
	inc	@@is_hiscore

@@hiscore_denied:
	mov	al, @@is_hiscore
	pop	di
	pop	si
	jmp	@@render
SCORE_UPDATE_AND_RENDER	endp
MAIN_01_TEXT	ends

	end
