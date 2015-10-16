; master library - 
;
; Description:
;	ジョイスティック操作の終了
;
; Function/Procedures:
;	void js_end( void ) ;
;
; Parameters:
;	none
;
; Returns:
;	none
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	MS-DOS
;
; Requiring Resources:
;	CPU: 
;
; Notes:
;	キーバッファをクリアするだけです。
;
; Assembly Language Note:
;	
;
; Compiler/Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Author:
;	恋塚昭彦
;
; Revision History:
;	93/ 5/12 Initial: jsend.asm/master.lib 0.16

func JS_END	; {
	nopcall	DOS_KEYCLEAR
	ret
endfunc		; }
