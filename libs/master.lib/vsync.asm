; master library - PC-9801
;
; Description:
;	VSYNC割り込み
;		開始 - vsync_start
;		終了 - vsync_end
;
; Function/Procedures:
;	void vsync_start(void) ;
;	void vsync_end(void) ;
;	void vsync_leave(void) ;
;
; Parameters:
;	none
;
; Returns:
;	none
;
; Global Variables:
;	unsigned volatile vsync_Count1, vsync_Count2 ;
;		VSYNC割り込み毎に増加し続けるカウンタ。
;		vsync_startで 0 に設定されます。
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	PC-9801
;
; Requiring Resources:
;	CPU: 8086
;
; Notes:
;	・vsync_startを行ったら、必ずvsync_endを実行してください。
;	　これを怠るとプログラム終了後ハングアップします。
;	・vsync_startを２度以上実行すると、２度目以降はカウンタを
;	　リセットするだけになります。
;	・vsync_endを、vsync_startを行わずに実行しても何もしません。
;
; Compiler/Assembler:
;	TASM 3.0
;	OPTASM 1.6
;
; Author:
;	恋塚昭彦
;
; Revision History:
;	92/11/21 Initial
;	93/ 2/10 vsync_Proc用処理追加
;	93/ 4/19 割り込みルーチンでCLDを忘れていた
;	93/ 6/24 [M0.19] CLI-STIを pushf-CLI-popfに変更
;	93/ 8/ 8 [M0.20] vsync_waitを vsyncwai.asmに分離
;	95/ 1/30 [M0.23] vsync_Delayによる遅延追加
;	95/ 1/31 [M0.23] vsync_start() 31kHzか否かでvsync_Delayに値を設定する

CRTBIOS_VECT	EQU 18h
VSYNC_VECT	EQU 0ah
VSYNC_IMR		EQU 2	; 割り込みマスクレジスタ
VSYNC_DISABLE	EQU 4

raw_crtbios	dw	?	; int 18h ( CRT BIOS )
raw_crtbios_seg	dw	?

; VSYNC割り込みの初期設定と開始
;	void vsync_start( void ) ;
func VSYNC_START
	xor	AX,AX
	push	AX
	push	AX
	call	GRAPH_EXTMODE
	and	AX,0ch
	cmp	AX,0ch
	mov	vsync_Delay,13311
	je	short @@NOW_31KHz
	mov	vsync_Delay,0		; 24kHz
@@NOW_31KHz:

	xor	AX,AX
	mov	vsync_Count1,AX
	mov	vsync_Count2,AX

	cmp	vsync_OldMask,AL ; house keeping
	jne	short @@S_IGNORE

	mov	AL,VSYNC_VECT	; VSYNC割り込みベクタの設定と保存
	push	AX
	push	CS
	mov	AX,offset VSYNC_COUNT
	push	AX
	nopcall	DOS_SETVECT
	mov	word ptr vsync_OldVect,AX
	mov	word ptr vsync_OldVect + 2,DX

	pushf
	CLI			; 以前のVSYNC割り込みマスクの取得と
	in	AL,VSYNC_IMR		; VSYNC割り込みの許可
	mov	AH,AL
	and	AL,NOT VSYNC_DISABLE
	out	VSYNC_IMR,AL
	popf
	or	AH,NOT VSYNC_DISABLE
	mov	vsync_OldMask,AH

	mov	AX,CRTBIOS_VECT	; CRT BIOS割り込みベクタの設定と保存
	push	AX
	push	CS
	mov	AX,offset CRTBIOS_COOK
	push	AX
	nopcall	DOS_SETVECT
	mov	CS:raw_crtbios, AX
	mov	CS:raw_crtbios_seg, DX

	out	64h,AL		; VSYNC割り込みの起動許可
@@S_IGNORE:
	ret
	EVEN
endfunc

; INT 18h にVSYNC割り込み再起動を入れる
CRTBIOS_COOK proc
	pushf
	call	DWORD PTR CS:raw_crtbios
	out	64h,AL		; VSYNC割り込みの起動許可
	iret
	EVEN
CRTBIOS_COOK endp


; INT 0ah VSYNC割り込み
VSYNC_COUNT proc far
	push	AX
	push	DS
	mov	AX,seg DGROUP
	mov	DS,AX

	mov	AX,vsync_Delay
	add	vsync_delay_count,AX
	jc	short @@VSYNC_COUNT_END

	inc	vsync_Count1
	inc	vsync_Count2

	cmp	WORD PTR vsync_Proc+2,0
	je	short @@VSYNC_COUNT_END
	push	BX
	push	CX
	push	DX
	push	SI	; for pascal
	push	DI	; for pascal
	push	ES
	CLD
	call	DWORD PTR vsync_Proc
	pop	ES
	pop	DI	; for pascal
	pop	SI	; for pascal
	pop	DX
	pop	CX
	pop	BX
	CLI

@@VSYNC_COUNT_END:
	pop	DS
	mov	AL,20h		; EOI
	out	0,AL		; send EOI to master PIC
	out	64h,AL		; VSYNC割り込みの起動許可
	pop	AX
	iret
	EVEN
VSYNC_COUNT endp


; VSYNC割り込みの終了と復元
;	void vsync_end( void ) ;
;	void vsync_leave( void );
	public VSYNC_LEAVE
func VSYNC_END
VSYNC_LEAVE label proc
	cmp	vsync_OldMask,0 ; house keeping
	je	short @@E_IGNORE

	mov	AX,CRTBIOS_VECT	; CRT BIOS割り込みベクタの復元
	push	AX
	push	CS:raw_crtbios_seg
	push	CS:raw_crtbios
	nopcall	DOS_SETVECT

	pushf
	CLI
	in	AL,VSYNC_IMR		; VSYNC割り込みを禁止する
	or	AL,4
	out	VSYNC_IMR,AL
	popf

	mov	AX,VSYNC_VECT	; VSYNC割り込みベクタの復元
	push	AX
	push	word ptr vsync_OldVect + 2
	push	word ptr vsync_OldVect
	nopcall	DOS_SETVECT

	pushf
	CLI
	in	AL,VSYNC_IMR		; VSYNC割り込みマスクの復元
	and	AL,vsync_OldMask
	out	VSYNC_IMR,AL
	popf
	out	64h,AL		; VSYNC割り込みの起動許可

	xor	AL,AL
	mov	vsync_OldMask,AL

@@E_IGNORE:
	ret
	EVEN
endfunc
