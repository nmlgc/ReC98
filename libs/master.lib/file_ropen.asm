; master library - MS-DOS
;
; Description:
;	ファイルの読み込みオープン
;
; Function/Procedures:
;	int file_ropen( const char * filename ) ;
;
; Parameters:
;	char * filename	ファイル名
;
; Returns:
;	1 = 成功
;	0 = 失敗 ( すでに何かが開かれている、見つからない )
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	MS-DOS
;
; Requiring Resources:
;	CPU: 8086
;
; Notes:
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
;	92/11/17 Initial
;	92/12/ 1
;	93/ 5/ 9 [M0.16] Pascal対応
;	93/ 5/14 [M0.17] ↑これで大ハグ発生したので修正

func FILE_ROPEN
	push	BP
	mov	BP,SP

	; 引数
	@@filename = (RETSIZE+1)*2

	xor	AX,AX
	mov	BX,file_Handle
	cmp	BX,-1			; 既に何か開いていたら駄目
	jne	short @@EXIT

if LDATA
	push	word ptr [BP+@@filename+2]
endif
	push	word ptr [BP+@@filename]
	nopcall	DOS_ROPEN		; ファイルの読み込みオープン
	sbb	BX,BX
	or	AX,BX			; エラーなら -1
	mov	file_Handle,AX
	xor	AX,AX
	mov	file_InReadBuf,AX
	mov	WORD PTR file_BufferPos,AX
	mov	WORD PTR file_BufferPos+2,AX
	mov	file_BufPtr,AX
	mov	file_Eof,AX
	mov	file_ErrorStat,AX
	lea	AX,[BX+1]		; OK = 1, FAULT = 0
@@EXIT:
	pop	BP
	ret	DATASIZE*2
	EVEN
endfunc
