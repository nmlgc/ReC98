; master library - (pf.lib)
;
; Description:
;	ファイルのオープン (TH02 version)
;
; Functions/Procedures:
;	pf_t pfopen(const char *parfile,const char far *file);
;
; Parameters:
;	parfile		parファイル
;	file		オープンしたいファイル名
;
; Returns:
;
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	MS-DOS
;
; Requiring Resources:
;	CPU: 186
;
; Notes:
;	TH02's version removes the EXE-related functionality from the original
;	function, and introduces custom magic constants for compressed and
;	uncompressed files that take up two bytes instead of one, losing any
;	features related to the original check byte in the process. Oh, and it
;	adds a pointless "seek counter" that effectively limits the number of
;	files in an archive to 255.
;
; Assembly Language Note:
;
;
; Compiler/Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Author:
;	iR
;	恋塚昭彦
;	ZUN
;
; Revision History:
; PFOPEN.ASM       5,703 94-09-17   23:22
;	95/ 1/10 Initial: pfopen.asm/master.lib 0.23
;	95/ 2/14 [M0.22k] mem_AllocID対応
;	95/ 5/22 [M0.23] small/mediumで誤動作していたので"file"をfar化

pfHeader	struc
	hd_type	dw	?		; unsigned short type 圧縮タイプ
	hd_aux	db	?		; unsigned char aux 補助フラグ
	hd_fnm	db	13 dup(?)	; char filename[13] ファイル名
	hd_psz	dd	?		; long packsize 格納サイズ
	hd_osz	dd	?		; long orgsize オリジナルサイズ
	hd_ofs	dd	?		; long offset (ZUN)
	hd_rsv	db	4 dup(?)	; char reserve[4] 予約
pfHeader	ends

; ParHeader の type の値
	ZUN_PF_NONE	equ	0F388h	; 無圧縮
	ZUN_PF_LEN	equ	9595h	; ランレングス

exeHeader	struc
	eh_M	db	?
	eh_Z	db	?
	eh_mod	dw	?
	eh_page	dw	?
exeHeader	ends

func PFOPEN	; pfopen() {
	enter	size pfHeader,0
	push	SI
	push	DI

	;arg	parfile:dataptr,file:dataptr
	@@parfile	= (RETSIZE+1+2)*2
	@@file	= (RETSIZE+1)*2

	;local	header:pfHeader
	@@header = -(size pfHeader)

	; PFILE用バッファ取得
	mov	mem_AllocID,MEMID_pfile
	push	size PFILE
	_call	HMEM_ALLOCBYTE
	jnb	PFOPEN_1
	jmp	PFOPEN_nomem

PFOPEN_1:
	mov	SI,AX			; PFILE構造体のセグメント

	; parファイルをオープン
	push	word ptr [BP+@@parfile+2]
	push	word ptr [BP+@@parfile]
	_call	BOPENR

	or	AX,AX
	jnz	PFOPEN_2
	jmp	PFOPEN_free

PFOPEN_2:
	mov	ES,SI
	mov	ES:[pf_bf],AX

	; ターゲットファイルまでシーク
	lea	DI,[BP+@@header]
	;call	SEEK Pascal,DI,SI,[BP+parfile],[BP+file]
	push	DI		; _ss * header
	push	SI		; pf
	push	word ptr [BP+@@parfile+2]
	push	word ptr [BP+@@parfile]
	push	word ptr [BP+@@file+2]
	push	word ptr [BP+@@file]
	call	near ptr SEEK

	or	AX,AX
	jnz	short PFOPEN_close

	; 暗号化の有無に対応して内部1byte読出し関数をセットする
	mov	AX,offset PFGETX1
	mov	word ptr ES:[pf_getx],AX
	;	pf系関数はすべて同じセグメントである

	; 復号化用キー
	mov	AL,pfkey
	mov	ES:[pf_key],AL

	mov	AX,SS:[DI+pfHeader.hd_type]
	cmp	AX,ZUN_PF_NONE
	je	short PFOPEN_pf_none
	cmp	AX,ZUN_PF_LEN
	je	short PFOPEN_pf_len
	mov	AX,PFEUNKNOWN
	jmp	short PFOPEN_close

PFOPEN_pf_none:
	mov	AX,word ptr ES:[pf_getx]
	mov	word ptr ES:[pf_getc],AX
	jmp	short PFOPEN_return

PFOPEN_pf_len:
	mov	word ptr ES:[pf_getc],offset PFGETC1
	mov	ES:[pf_cnt],0
	mov	ES:[pf_ch],EOF

PFOPEN_return:
	mov	AX,word ptr SS:[DI+pfHeader.hd_psz]
	mov	DX,word ptr SS:[DI+pfHeader.hd_psz + 2]
	mov	word ptr ES:[pf_size],AX
	mov	word ptr ES:[pf_size + 2],DX

	mov	AX,word ptr SS:[DI+pfHeader.hd_osz]
	mov	DX,word ptr SS:[DI+pfHeader.hd_osz + 2]
	mov	word ptr ES:[pf_osize],AX
	mov	word ptr ES:[pf_osize + 2],DX

	xor	AX,AX
	mov	word ptr ES:[pf_read],AX
	mov	word ptr ES:[pf_read + 2],AX
	mov	word ptr ES:[pf_loc],AX
	mov	word ptr ES:[pf_loc + 2],AX

	mov	AX,SI
	jmp	short PFOPEN_q

PFOPEN_close:
	mov	word ptr pferrno,AX

	push	ES:[pf_bf]
	_call	BCLOSER
PFOPEN_free:
	push	SI
	_call	HMEM_FREE
	jmp	short PFOPEN_error
PFOPEN_nomem:
	mov	byte ptr pferrno,PFENOMEM
PFOPEN_error:
	xor	AX,AX

PFOPEN_q:
	pop	DI
	pop	SI
	leave
	ret	(2+DATASIZE)*2
endfunc	; }

;-----------------------------------------------------------------------------
; seek(pfHeader _ss *header, pf_t pf, const char MASTER_PTR *parfile,const char MASTER_PTR *file)
;-----------------------------------------------------------------------------
SEEK	proc near	; {
	enter	size exeHeader,0
	push	SI
	push	DI
	push	ES

	;arg	header:dataptr,pf:word, parfile:dataptr,file:dataptr
	@@header	= (1+2+2+DATASIZE)*2
	@@pf	= (1+1+2+DATASIZE)*2
	@@parfile	= (1+1+2)*2
	@@file	= (1+1)*2

	;local	exeh:exeHeader
	@@exeh = -(size exeHeader)

	mov	SI,[BP+@@pf]		; PFILE構造体のセグメント

	mov	ES,SI
	xor	AX,AX
	mov	word ptr ES:[pf_home],AX
	mov	word ptr ES:[pf_home + 2],AX

	; [DX:]BX = strrchr(parfile,'.');
	_push	DS
	push	SI
	CLD
	xor	BX,BX
	_mov	DX,BX
	_lds	SI,[BP+@@parfile]
STRRCHR_LOOP:
	lodsb
	cmp	AL,0
	jz	short STRRCHR_DONE
	cmp	AL,'.'
	jne	short STRRCHR_LOOP
	lea	BX,[SI-1]
	_mov	DX,DS
	jmp	short STRRCHR_LOOP
STRRCHR_DONE:
	pop	SI
	_pop	DS
    l_ <mov	AX,DX>
    l_ <or	AX,BX>
    s_ <test	BX,BX>
	jz	short SEEK_seek

SEEK_seek:
	mov	DI,[BP+@@header]
	mov	pf_limit,0
SEEK_loop:
	; ヘッダをリード
	mov	ES,SI
	;call	BREAD Pascal,DI,size pfHeader,ES:[pf_bf]
	_push	SS
	push	DI
	push	size pfHeader
	push	ES:[pf_bf]
	_call	BREAD

	inc	pf_limit
	cmp	pf_limit, 255
	mov	BX,PFENOTFOUND
	jz	short SEEK_error

	cmp	AX,size pfHeader
	jne	short SEEK_error

	mov	ES,SI
	add	word ptr ES:[pf_home],AX
	adc	word ptr ES:[pf_home + 2],0

	; ヘッダの正当性をチェック
	mov	AX,SS:[DI+pfHeader.hd_type]
	and	ax, ax
	mov	BX,PFEILPFILE
	jz	short SEEK_error

	; ファイル名が不可視の場合、比較のためもとに戻す
	lea	BX,[DI+pfHeader.hd_fnm]
SEEK_not:	cmp	byte ptr SS:[BX],0
	je	short SEEK_cmp
	not	byte ptr SS:[BX]
	inc	BX
	jmp	short SEEK_not

SEEK_cmp:
	lea	BX,[DI+pfHeader.hd_fnm]

	push	word ptr [BP+@@file+2]
	push	word ptr [BP+@@file]
	_push	SS
	push	BX
	call	near ptr STR_IEQ
	mov	AX,0

	jnz	short SEEK_return
	jmp	short SEEK_loop

SEEK_error:
	mov	AX,BX

SEEK_return:
	mov	ES,SI
	mov	AX,word ptr SS:[DI+pfHeader.hd_ofs]
	mov	DX,word ptr SS:[DI+pfHeader.hd_ofs + 2]
	mov	word ptr ES:[pf_home],AX
	mov	word ptr ES:[pf_home + 2],DX

	push	ES:[pf_bf]
	push	DX
	push	AX
	push	0
	_call	BSEEK_
	pop	ES
	pop	DI
	pop	SI
	leave
	ret	(2+2+DATASIZE)*2
SEEK	endp		; }
