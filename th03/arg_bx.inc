; Reimplementation of TASM's ARG directive for those weirdly micro-optimized
; ASM functions that keep their base pointer in BX. The ENTER instruction of
; the original ARG directive is replaced with ´MOV BX, SP`. Afterwards, use
; `ret_bx` to emit the correct `RET` instruction for the given number of
; parameters.
; [distance] must be either NEAR or FAR, matching the function this macro is
; used in.
;
; [params] uses the same colon-separated `name:type` syntax as the original
; ARG directive. Since all of those functions (thankfully) use the Pascal
; calling convention, they need to be declared in reverse order, compared to
; the C declaration.
; Unfortunately, the names can't be prefixed with @@, as that would make them
; local to the macro. Hacking around this with NOLOCALS, PUSHSTATE, and
; POPSTATE would break local labels for the usage code. So, just use a single
; @ instead... or a clean namespace.
;
; MODDERS: Replace with the regular ARG and RET directives in the usage code,
; and delete this file.
arg_bx macro distance:req, params:vararg
	; Expanding a text macro on the left side of `=` only seems to work in
	; QUIRKS mode?!
	PUSHSTATE
	QUIRKS

	@bp = ((-distance and 0FFFFh) * word)
	@sp = @bp
	for @@param, params
		@@colon_pos	instr 	<@@param>, <:>
		@@name     	substr	<@@param>, 1, (@@colon_pos - 1)
		@@type     	substr	<@@param>, (@@colon_pos + 1)

		@@local_err	substr	<@@param>, 1, 2
		errifidn	@@local_err, <@@> "arg_bx: @@ in parameter names is not supported"

		; % at the beginning of the line (!) forces expansion of the text
		; macro @@name... in QUIRKS mode.
%		@@name	=	@@type ptr ss:[bx+@sp]

		; The stack is word-aligned...
		@sp = (@sp + ((@@type + 1) and (not 1)))
	endm
	ret_bx	macro
		ret	(@sp - @bp)
	endm
	POPSTATE

	; This allows `ret_bx` to be used in functions with no parameters as well,
	; e.g. if parameters were removed between games. Simply don't pass any
	; [params], and this macro will turn itself to a no-op, with `ret_bx` not
	; clearing any parameters either.
	if (@sp ne @bp)
		mov	bx, sp
	endif
endm
