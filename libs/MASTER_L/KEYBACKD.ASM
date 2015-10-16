; master library
;
; Description:
;	キーの戻し領域
;
; Global Variables:
;	key_back_buffer	
;
; Author:
;	恋塚昭彦
;
; Revision History:
;	94/ 4/ 5 Initial: keyback.asm/master.lib 0.23
;

	public _key_back_buffer,key_back_buffer
key_back_buffer label word
_key_back_buffer	dw 0
