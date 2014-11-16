; master library - (pf.lib)
;
; Description:
;	オートマチックモード。int 21hにフックする/解除する
;
; Functions/Procedures:
;	void pfstart(const char *parfile);
;	void pfend(void);
;
; Parameters:
;	parfile		parアーカイブファイル名
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
;	CPU: 186
;
; Notes:
;	
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
;
; Revision History:
; PFINT21.ASM       6,253 94-09-17   23:22
;	95/ 1/10 Initial: pfint21.asm/master.lib 0.23

;		global	C _fstrncpy	: proc
;;		global	C printf	: proc				;DBG

;;trapc		dw	0						;DBG
org_int21	dd	0
on_hook		db	0

th03_archive_header_t struc
	entries_size dw ?
	unk dw ?
	entries_count dw ?
	key dw ?
	zero db 8 dup(0)
th03_archive_header_t ends

func PFSTART	; pfstart() {
	;arg	parfile:dataptr
	@@parfile = (RETSIZE+1)*2
if GAME eq 5
	local	@@parheader:th03_archive_header_t

	enter	size th03_archive_header_t, 0
	push	si
	push	di
else
	push	BP
	mov	BP,SP

	CLD
endif
	; すでに start してないかチェック
	mov	AX,word ptr CS:org_int21
	or	AX,word ptr CS:org_int21+2
if (GAME eq 2) or (GAME eq 5)
	jnz	short PFSTART_copy
else
	jz	short PFSTART_1
	jmp	PFSTART_copy
endif

PFSTART_1:
if (GAME eq 3) or (GAME eq 4)
	push	di
	push	si
	push	word ptr [bp+@@parfile+2]
	push	word ptr [bp+@@parfile]
	call	file_ropen
	push	size th03_archive_header_t
	call	hmem_allocbyte
	mov	di, ax
	push	ax
	push	0
	push	size th03_archive_header_t
	call	file_read
	mov	ax, di
	mov	es, ax
	mov	di, es:[th03_archive_header_t.entries_size]
	mov	si, es:[th03_archive_header_t.key]
	push	ax
	call	hmem_free
elseif (GAME eq 5)
	push	large dword ptr [bp+@@parfile]
	call	file_ropen
	lea	ax, @@parheader
	push	ss
	push	ax
	push	size th03_archive_header_t
	call	file_read
	mov	di, @@parheader.th03_archive_header_t.entries_size
	mov	si, @@parheader.th03_archive_header_t.key
endif
if GAME ge 3
	push	di
	call	hmem_allocbyte
	mov	pfint21_entries, ax
	push	ax
	push	0
	push	di
	call	file_read
	call	file_close
	mov	cx, di
	mov	ax, pfint21_entries
	mov es, ax
	mov	ax, si
	xor bx, bx

PFSTART_decrypt:
	xor	es:[bx], al
	sub	al, es:[bx]
	inc	bx
	loop	PFSTART_decrypt
if GAME ne 5
	pop	si
	pop	di
endif
endif
	; DOSファンクションリクエストのエントリを退避
	msdos	GetInterruptVector,21h
	mov	word ptr CS:org_int21,BX
	mov	word ptr CS:org_int21+2,ES

	; 変数の初期化
	mov	pfint21_pf,0
	mov	pfint21_handle,-1

	; 新しいファンクションリクエストエントリをセット
	push	DS
	push	CS
	pop	DS
	mov	DX,offset pfint21
	msdos	SetInterruptVector,21h
	pop	DS

PFSTART_copy:
	;strcpy( parfilename, parfile )
if GAME le 4
	push	SI
	push	DI
endif
	_push	DS

	mov	CX,-1	; CX = strlen(parfile)+1
	mov	AL,0
	s_push	DS
	s_pop	ES
	_les	DI,[BP+@@parfile]
	repne	scasb
	not	CX
	sub	DI,CX

	mov	SI,DI	; copy
	mov	DI,offset parfilename
	_push	DS
	_push	ES
	_pop	DS
	_pop	ES
	shr	CX,1
	rep	movsw
	adc	CX,CX
	rep	movsb

	_pop	DS
	pop	DI
	pop	SI

if GAME le 4
	pop	BP
else
	leave
endif
	ret	(DATASIZE)*2
endfunc	; }


func PFEND	; pfend() {
	mov	AX,word ptr CS:org_int21
	or	AX,word ptr CS:org_int21+2
	jz	short PFEND_return

if GAME eq 5
	push	pfint21_entries
	call	hmem_free
endif

	; ファンクションリクエストエントリを元に戻す
	push	DS
	lds	DX,CS:org_int21
	msdos	SetInterruptVector,21h
	pop	DS
	xor	AX,AX
	mov	word ptr CS:org_int21,AX
	mov	word ptr CS:org_int21+2,AX

	; オープン中のハンドルがあればクローズ
	cmp	pfint21_pf,AX
	je	short PFEND_return

	push	pfint21_pf
	_call	PFCLOSE

if (GAME eq 3) or (GAME eq 4)
	push	pfint21_entries
	call	hmem_free
endif

PFEND_return:
	ret
endfunc	; }


pfint21	proc	far	; {
;;	inc	trapc						;DBG
	cmp	CS:on_hook,0
	jz	short _Hook
	jmp	dword ptr CS:org_int21

	_Hook:
	pusha		; push	AX CX DX BX SP BP SI DI
	push	DS
	push	ES
	mov	BP,SP
	mov	DI,DGROUP
	mov	DS,DI
	assume	DS:DGROUP

	_FLAGS = + 24
	_CS = +22
	_IP = +20
	_AX = +18
	_CX = +16
	_DX = +14
	_BX = +12
	_SP = +10
	_BP = +8
	_SI = +6
	_DI = +4
	_DS = +2
	_ES = +0

	inc	CS:on_hook
	; 割込みフラグを割込み前に戻す
	push	word ptr [BP+_FLAGS]
	popf

;;		pusha							;DBG
;;		call	printf C,offset DGROUP:string,trapc,AX,BX,CX,DX
;;		popa							;DBG

	; AH(ファンクション)でswitch
	mov	byte ptr CS:default,AH
	mov	SI,offset switch_table - 4
i_switch:
	add	SI,4
	cmp	AH,CS:[SI]
	jne	short i_switch
	mov	DI,pfint21_handle
	jmp	word ptr CS:[SI + 2]

	switch_table	label	word
	dw	OpenHandle,		_Open
	dw	CloseHandle,		_Close
	dw	ReadHandle,		_Read
	dw	MoveFilePointer,	_MoveFilePointer
	dw	ForceDuplicateFileHandle,_CheckHandle2
	dw	WriteHandle,		_CheckHandle
	dw	DuplicateFileHandle,	_CheckHandle
	dw	EndProcess,		_Terminate
	dw	GetSetDateTimeofFile,	_CheckHandle
	dw	LockUnlock,		_CheckHandle
	dw	IOCTL,			_IOCTL
	default	dw	?,			_Thru	; 番兵


	;-------------------------------------------------------------------
	;	OpenHandle
	;		DS:DX	パス名
	;		AL	ファイルアクセスコントロール
_Open:
	test	AL,0fh
if GAME le 4
	jz	_Open1		; リードモードでない
	jmp	_Thru
_Open1:
	or	DI,DI
	js	_Open2		; 既にオープンしている
	jmp	_Thru
else
	jnz	_Thru
	or	DI,DI
	jns	_Thru
endif
_Open2:
;		mov	DI,offset DGROUP:filename	; lea	DI,filename
;		call	_fstrncpy C,DI,DS,DX,[BP+_DS],length filename
;		call	PFOPEN Pascal,offset DGROUP:[parfilename],DI

	;call	PFOPEN Pascal,offset DGROUP:[parfilename],DX
	_push	DS
	push	offset parfilename
	push	word ptr [BP+_DS]
	push	DX
	_call	PFOPEN
				; この場合 DS==ssを確認したほうがよい

	or	AX,AX
if GAME le 4
	jnz	_Open3		; 無条件にthruはよくないかも
	jmp	_Thru
_Open3:
else
	jz	_Thru
endif
	mov	pfint21_pf,AX
	mov	ES,AX
	mov	ES,ES:[pf_bf]
	mov	AX,ES:[b_hdl]	; pf->bf->handle
	mov	pfint21_handle,AX
	jmp	_OK

	;-------------------------------------------------------------------
	;	CloseHandle
	;		BX	ファイルハンドル
_Close:
	cmp	BX,DI		; ハンドルチェック
if GAME le 4
	jz	_Close1
	jmp	_Thru
_Close1:
else
	jnz	_Thru
endif
	push	pfint21_pf
	_call	PFCLOSE

	mov	pfint21_pf,0
	mov	pfint21_handle,-1
	jmp	_OK

	;-------------------------------------------------------------------
	;	ReadHandle
	;		BX	ファイルハンドル
	;		DS:DX	バッファの位置
	;		CX	読み込むべきバイト数
_Read:
	cmp	BX,DI		; ハンドルチェック
	jne	short _Thru

	;call	PFREAD Pascal,[BP+_DS],DX,CX,pf
	push	word ptr [BP+_DS]
	push	DX
	push	CX
	push	pfint21_pf
	_call	PFREAD

	jmp	_OK

	;-------------------------------------------------------------------
	;	MoveFilePointer
	;		BX	ファイルハンドル
	;		CX:DX	移動するバイト数
	;		AL	移動方法 00:先頭 01:カレント 02:最後
_MoveFilePointer:
	cmp	BX,DI		; ハンドルチェック
	jne	short _Thru

	or	CX,CX
	jl	short _Error		; 負のオフセットは不可
	cmp	AL,1
	je	short i_seek
	jl	short i_seek_top

	; ファイルの終りからの移動は、終わりに移動するだけ
	mov	ES,pfint21_pf
	mov	DX,word ptr ES:[pf_osize]
	mov	CX,word ptr ES:[pf_osize+2]
	sub	DX,word ptr ES:[pf_loc]
	sbb	CX,word ptr ES:[pf_loc+2]
	jmp	short i_seek

i_seek_top:
	push	CX
	push	DX
	push	pfint21_pf
	_call	PFREWIND
	pop	DX
	pop	CX
i_seek:
	push	pfint21_pf
	push	CX
	push	DX
	_call	PFSEEK	; 戻り値 DX AX が現在位置

	; 現在位置を返す
	mov	[BP+_DX],DX
	jmp	short _OK

	;-------------------------------------------------------------------
	;	EndProcess
	;
_Terminate:
	; フックを戻してから終了
	lds	DX,CS:org_int21
	msdos	SetInterruptVector,21h
	jmp	short _Thru

	;-------------------------------------------------------------------
	;	IOCTRL
_IOCTL:
	mov	cl,AL
	mov	AX,1
	shl	AX,cl
	test	AX,CS:IOCTL_table
	jnz	short _CheckHandle
	jmp	short _Thru

	IOCTL_table	dw	0001010011001111b
	;	bit
	;	0	Get IOCTL Data
	;	1	Set IOCTL Data
	;	2	Recieve IOCTL Character
	;	3	Send IOCTL Character
	;	6	Get Input IOCTL Status
	;	7	Get Output IOCTL Status
	;	a	IOCTL is Redirected Handle
	;	c	Generic IOCTL (for handle)

	;-------------------------------------------------------------------
	;	ハンドルのチェック
_CheckHandle2:
	mov	CX,DI		; ハンドルチェック
	je	short _Error		; エラーにしないでクローズする
				; 方がよいかも

_CheckHandle:
	cmp	BX,DI		; ハンドルチェック
	je	short _Error

	;-------------------------------------------------------------------
_Thru:
	dec	CS:on_hook
	;	mov	CX,[org_int21.ofst]
	;	mov	AX,[org_int21.sgmt]
	;	xchg	CX,[BP+_CX]
	;	xchg	AX,[BP+_AX]
	;	pop	ES DS DI SI BP BX BX DX
	push	word ptr [BP+_FLAGS]
	popf
	;	retf
	pop	ES
	pop	DS
	popa
	cli
	jmp	dword ptr CS:org_int21

	;-------------------------------------------------------------------
_Error:
	or	byte ptr [BP+_FLAGS],01h	; stc
	mov	AX,1		; 適切なエラーコードを返すべきだが
				; とりあえず固定で1を返す
	jmp	short i_return

	;-------------------------------------------------------------------
_OK:
	and	byte ptr [BP+_FLAGS],0feh	; clc

i_return:
	mov	[BP+_AX],AX
	dec	CS:on_hook
	pop	ES
	pop	DS
	;	assume	DS:NOTHING
	popa		; pop	DI SI BP SP BX DX CX AX
	iret
pfint21	endp		; }
