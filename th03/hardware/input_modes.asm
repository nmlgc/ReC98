public INPUT_MODE_INTERFACE
input_mode_interface	proc far
	push	bp
	mov	bp, sp
	nopcall	_input_reset_sense_key_held
	cmp	js_bexist, 0
	jz	short @@nojoy
	call	js_sense
	mov	ax, js_stat
	or	_input_sp, ax

@@nojoy:
	mov	ax, _input_mp_p1
	or	_input_sp, ax
	pop	bp
	retf
input_mode_interface	endp


public INPUT_MODE_KEY_VS_KEY
input_mode_key_vs_key	proc far
	push	bp
	mov	bp, sp
	nopcall	_input_reset_sense_key_held
	pop	bp
	retf
input_mode_key_vs_key	endp


public INPUT_MODE_JOY_VS_KEY
input_mode_joy_vs_key	proc far
	push	bp
	mov	bp, sp
	nopcall	_input_reset_sense_key_held
	cmp	js_bexist, 0
	jz	short loc_EDA2
	call	js_sense
	mov	ax, js_stat
	mov	_input_mp_p1, ax
	mov	ax, _input_sp
	mov	_input_mp_p2, ax

loc_EDA2:
	pop	bp
	retf
input_mode_joy_vs_key	endp


public INPUT_MODE_KEY_VS_JOY
input_mode_key_vs_joy	proc far
	push	bp
	mov	bp, sp
	nopcall	_input_reset_sense_key_held
	cmp	js_bexist, 0
	jz	short @@nojoy
	call	js_sense
	mov	ax, js_stat
	mov	_input_mp_p2, ax
	mov	ax, _input_sp
	mov	_input_mp_p1, ax

@@nojoy:
	pop	bp
	retf
input_mode_key_vs_joy	endp


public INPUT_MODE_1P_VS_CPU
input_mode_1p_vs_cpu	proc far
	push	bp
	mov	bp, sp
	nopcall	_input_reset_sense_key_held
	mov	ax, _input_sp
	or	_input_mp_p1, ax
	cmp	js_bexist, 0
	jz	short @@nojoy
	call	js_sense
	mov	ax, js_stat
	or	_input_mp_p1, ax

@@nojoy:
	mov	_input_mp_p2, INPUT_NONE
	pop	bp
	retf
input_mode_1p_vs_cpu	endp


public INPUT_MODE_CPU_VS_1P
input_mode_cpu_vs_1p	proc far
	push	bp
	mov	bp, sp
	nopcall	_input_reset_sense_key_held
	mov	ax, _input_sp
	or	ax, _input_mp_p1
	mov	_input_mp_p2, ax
	cmp	js_bexist, 0
	jz	short loc_EE15
	call	js_sense
	mov	ax, js_stat
	or	_input_mp_p2, ax

loc_EE15:
	mov	_input_mp_p1, INPUT_NONE
	pop	bp
	retf
input_mode_cpu_vs_1p	endp


public INPUT_MODE_CPU_VS_CPU
input_mode_cpu_vs_cpu	proc far
	push	bp
	mov	bp, sp
	nopcall	_input_reset_sense_key_held
	test	_input_sp.hi, high INPUT_CANCEL
	jnz	short @@map
	test	_input_sp.hi, high INPUT_OK
	jz	short @@ret

@@map:
	mov	_input_sp, INPUT_CANCEL

@@ret:
	mov	_input_mp_p1, INPUT_NONE
	mov	_input_mp_p2, INPUT_NONE
	pop	bp
	retf
input_mode_cpu_vs_cpu	endp


public INPUT_MODE_ATTRACT
input_mode_attract	proc far
	push	bp
	mov	bp, sp
	nopcall	_input_reset_sense_key_held
	cmp	js_bexist, 0
	jz	short @@nojoy
	call	js_sense
	mov	ax, js_stat
	or	_input_sp, ax

@@nojoy:
	mov	ax, _input_mp_p1
	or	_input_sp, ax
	mov	_input_mp_p1, INPUT_NONE
	mov	_input_mp_p2, INPUT_NONE
	pop	bp
	retf
input_mode_attract	endp
