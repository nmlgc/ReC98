; master library - (pf.lib)
;
; Description:
;	ファイルのオープン (TH03 version)
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
;	CPU: 186 (386 for TH05 version)
;
; Notes:
;	The TH03 version improves upon the original by preloading all pfHeader
;	structures of an archive on pfstart(). In doing this, seeking to the
;	desired file becomes much more efficient and the SEEK function can be
;	eliminated entirely. For some reason, It also saw fit to reduce the
;	size fields in pfHeader to 16-bit for some reason.
;
;	TH05 further optimizes the implementation by using 32-bit registers
;	and instructions where possible, and removing unnecessary instructions
;	left over from the original function.
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
	hd_psz	dw	?		; unsigned short packsize 格納サイズ
	hd_osz	dw	?		; unsigned short orgsize オリジナルサイズ
	hd_ofs	dd	?		; long offset (ZUN)
	hd_rsv	db	8 dup(?)	; char reserve[8] 予約
pfHeader	ends

; ParHeader の type の値
	ZUN_PF_NONE	equ	0F388h	; 無圧縮
	ZUN_PF_LEN	equ	9595h	; ランレングス

func PFOPEN	; pfopen() {
if GAME eq 5
	push	bp
	mov	bp, sp
else
	enter	0, 0
endif
	push	SI
	push	DI

	;arg	parfile:dataptr,file:dataptr
	@@parfile	= (RETSIZE+1+2)*2
	@@file	= (RETSIZE+1)*2

	; PFILE用バッファ取得
if GAME ne 5
	mov	mem_AllocID,MEMID_pfile
endif
	push	size PFILE
	_call	HMEM_ALLOCBYTE
	jb	PFOPEN_nomem

	mov	SI,AX			; PFILE構造体のセグメント

	; parファイルをオープン
if GAME eq 5
	push	large dword ptr [BP+@@parfile]
else
	push	word ptr [BP+@@parfile+2]
	push	word ptr [BP+@@parfile]
endif
	_call	BOPENR

	or	AX,AX
	jz	PFOPEN_free

PFOPEN_2:
	mov	ES,SI
	mov	ES:[pf_bf],AX

	mov	ax, pfint21_entries
	mov	fs, ax
	xor	ax, ax
	mov	di, ax

PFOPEN_loop:
if GAME eq 5
	cmp	byte ptr fs:[di+pfHeader.hd_type], 0	; End of list?
	jz	PFOPEN_close
	lea	bx, [di+pfHeader.hd_fnm]
	push	large dword ptr [bp+@@file]
else
	mov	al, byte ptr fs:[di+pfHeader.hd_type]
	mov	bx, PFENOTFOUND	; End of list?
	or	al, al
	jz	short PFOPEN_seek_error
	mov	bx, pfHeader.hd_fnm
	add	bx, di
	push	word ptr [BP+@@file+2]
	push	word ptr [BP+@@file]
endif
	push	fs
	push	bx
	call	STR_IEQ
	jnz	short PFOPEN_seek
	add	di, size pfHeader
	jmp	short PFOPEN_loop

PFOPEN_seek_error:
if GAME ne 5
	mov	AX,BX
endif
PFOPEN_seek:
	mov	ES,SI
if GAME eq 5
	mov	eax, fs:[di+pfHeader.hd_ofs]
	mov	es:[pf_home], eax
	push	es:[pf_bf]
	push	eax
else
	mov	AX,word ptr FS:[DI+pfHeader.hd_ofs]
	mov	DX,word ptr FS:[DI+pfHeader.hd_ofs + 2]
	mov	word ptr ES:[pf_home],AX
	mov	word ptr ES:[pf_home + 2],DX
	push	ES:[pf_bf]
	push	DX
	push	AX
endif
	push	0
	_call	BSEEK_

	mov	ax, offset PFGETX0
	mov	dl, fs:[di+pfHeader.hd_aux]
if GAME eq 5
	or	dl, dl
	mov	es, si
else
	mov	es, si
	or	dl, dl
endif
	jz	short PFOPEN_type
	mov	es:[PFILE.pf_key], dl
	mov	ax, offset pfgetx1

PFOPEN_type:
	mov	es:[PFILE.pf_getx], ax
if GAME ne 5
	mov	es, cx
endif
	mov	ax, fs:[di+pfHeader.hd_type]
if GAME ne 5
	mov	es, si
endif
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
if GAME eq 5
	movzx	ebx, fs:[di+pfHeader.hd_psz]
	movzx	edx, fs:[di+pfHeader.hd_osz]
	mov	es:[pf_size], ebx
	mov	es:[pf_osize], edx
	xor	eax, eax
	mov	es:[pf_read], eax
	mov	es:[pf_loc], eax
else
	mov	bx, fs:[di+pfHeader.hd_psz]
	mov	dx, fs:[di+pfHeader.hd_osz]
	xor	ax, ax
	mov	word ptr ES:[pf_size],BX
	mov	word ptr ES:[pf_size + 2],AX
	mov	word ptr ES:[pf_osize],DX
	mov	word ptr ES:[pf_osize + 2],AX
	mov	word ptr ES:[pf_read],AX
	mov	word ptr ES:[pf_read + 2],AX
	mov	word ptr ES:[pf_loc],AX
	mov	word ptr ES:[pf_loc + 2],AX
endif

	mov	AX,SI
	jmp	short PFOPEN_q

PFOPEN_close:
if GAME eq 5
	mov	es, si
else
	mov	word ptr pferrno,AX
endif

	push	ES:[pf_bf]
	_call	BCLOSER
PFOPEN_free:
	push	SI
	_call	HMEM_FREE
	jmp	short PFOPEN_error
PFOPEN_nomem:
if GAME ne 5
	mov	byte ptr pferrno,PFENOMEM
endif
PFOPEN_error:
	xor	AX,AX

PFOPEN_q:
	pop	DI
	pop	SI
if GAME eq 5
	pop	bp
else
	leave
endif
	ret	(2+DATASIZE)*2
endfunc	; }
