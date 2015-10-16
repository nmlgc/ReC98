; master library - BGM
;
; Description:
;	初期化・後始末をする
;
; Function/Procedures:
;	int bgm_init(int bufsiz);
;	void bgm_finish(void);
;
; Parameters:
;	bufsiz			1パートあたりのバッファサイズ
;
; Returns:
;	BGM_COMPLETE		正常終了
;	BGM_OVERFLOW		メモリが足りない
;
; Binding Target:
;	Microsoft-C / Turbo-C / Turbo Pascal
;
; Running Target:
;	PC-9801V
;
; Requiring Resources:
;	CPU: V30
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
;	femy(淀  文武)		: オリジナル・C言語版
;	steelman(千野  裕司)	: アセンブリ言語版
;	恋塚
;
; Revision History:
;	93/12/19 Initial: b_inifin.asm / master.lib 0.22 <- bgmlibs.lib 1.12
;	94/ 4/11 [M0.23] AT互換機対応
;	95/ 2/14 [M0.22k] mem_AllocID対応
;       95/ 4/ 1 [M0.22k] メモリ不足時のメモリ開放もれを修正
;	95/ 4/ 2 [M0.22k] BUGFIX EFSメモリの確保サイズが256要素には足りなかった

MRETURN macro
	pop	DI
	pop	SI
	leave
	ret	2
	EVEN
endm

func BGM_INIT	; bgm_init() {
	push	BP
	mov	BP,SP
	sub	SP,2
	push	SI
	push	DI
	@@bsize	= (RETSIZE+1)*2
	@@bsize2	= -2

	nopcall	GET_MACHINE

	cmp	glb.init,0
	je	short B_INIT_NOTINITIALIZED1
	xor	AX,AX			; BGM_COMPLETE
	MRETURN

B_INIT_NOTINITIALIZED1:
	;bsize2 = bufsiz;
	mov	DX,[BP+@@bsize]
	mov	[BP+@@bsize2],DX
	or	DX,DX
	jg	short B_INIT_SETBUFSIZE
	mov	word ptr [BP+@@bsize2],BUFMAX
B_INIT_SETBUFSIZE:
	mov	AX,[BP+@@bsize2]
	mov	glb.bufsiz,AX

	;曲バッファ確保
	mov	DI,offset part
B_INIT_ALLOCATEMBUF:
	;if ((part[cnt].mbuf = MK_FP(hmem_allocbyte(bsize2),0)) == NULL)
	mov	mem_AllocID,MEMID_bgm
	push	word ptr [BP+@@bsize2]
	nopcall	HMEM_ALLOCBYTE
	mov	word ptr [DI].mbuf+2,AX
	mov	word ptr [DI].mbuf,0
	jnc	short B_INIT_MBUFALLOCATED
	mov	AX,BGM_OVERFLOW
	MRETURN
B_INIT_MBUFALLOCATED:
	add	DI,type SPART
	cmp	DI,offset part + (type SPART * PMAX)
	jne	short B_INIT_ALLOCATEMBUF

	;効果音バッファ確保
	mov	DI,offset esound
B_INIT_ALLOCATESBUF:
	;if ((esound[cnt].sbuf = MK_FP(hmem_allocbyte(SBUFMAX * sizeof(uint) + 1),0)) == NULL)
	mov	mem_AllocID,MEMID_efs
	push	(SBUFMAX * 2)+1
	nopcall	HMEM_ALLOCBYTE
	mov	word ptr [DI].sbuf+2,AX
	mov	word ptr [DI].sbuf,0
	jnc	short B_INIT_SBUFALLOCATED
	push	word ptr [DI].mbuf+2
	mov	word ptr [DI].mbuf+2,0
	nopcall	HMEM_FREE
	mov	AX,BGM_OVERFLOW
	MRETURN
B_INIT_SBUFALLOCATED:
	add	DI,type SESOUND
	cmp	DI,offset esound + (type SESOUND * SMAX)
	jne	short B_INIT_ALLOCATESBUF

	;BGMOFF
	mov	glb.rflg,OFF
	;登録曲数
	mov	glb.mnum,0
	;セレクト中曲番号
	mov	glb.mcnt,0
	;パート数
	mov	glb.pnum,PMAX
	;パートカウンタ
	mov	glb.pcnt,0
	;終了パート数
	mov	glb.fin,0
	;リピートON
	mov	glb.repsw,ON
	;処理カウンタ
	mov	glb.tcnt,0
	;曲バッファ末尾 
	mov	glb.buflast,0
	;曲ごとのテンポ情報 

	CLD

	mov	CX,MMAX
	mov	DI,offset glb.mtp
	push	DS
	pop	ES
	mov	AX,DEFTEMPO
	rep 	stosw
	;効果音OFF
	mov	glb.effect,OFF
	;登録効果音数
	mov	glb.snum,0
	;セレクト中効果音番号
	mov	glb.scnt,0
	;演奏処理ON
	mov	glb.music,ON
	;効果音処理ON
	mov	glb.sound,ON
	;glb.clockbase = ((ulong)TVAL1ms * 120UL);
	;tempo120のタイマカウント
	test	Machine_State,10h	; PC/AT
	jz	short B_INIT_PC98
	mov	AX,TVALATORG_RTC
	jmp	short B_INIT_SET_CLOCKBASE
B_INIT_PC98:
	xor	AX,AX
	mov	ES,AX
	test	byte ptr ES:[0501H],80h
	mov	AX,TVAL8ORG
	jnz	short B_INIT_CLOCK8MHZ
	mov	AX,TVAL10ORG
B_INIT_CLOCK8MHZ:
B_INIT_SET_CLOCKBASE:
	and	AX,0fffeh
	mov	DX,DEFTEMPO
	mul	DX
	mov	word ptr glb.clockbase+2,DX
	mov	word ptr glb.clockbase,AX

	push	DEFTEMPO
	nopcall	BGM_SET_TEMPO

	;バッファクリア
	mov	BX,offset part.mbuf
	xor	DX,DX
	xor	AX,AX
B_INIT_BUFFERCLEARLOOP:
	les	DI,[BX]
	mov	CX,glb.bufsiz
	shr	CX,1
	rep	stosw
	adc	CX,CX
	rep	stosb
	add	BX,type SPART
	inc	DX
	cmp	DX,PMAX
	jl	short B_INIT_BUFFERCLEARLOOP

	nopcall	_BGM_TIMER_INIT

	;BEEPモード設定
	test	Machine_State,10h	; PC/AT
	jz	short B_INIT_PC98_2
B_INIT_PCAT_2:
	mov	AX,TVALATORG/2
	mov	CX,AX
	mov	AL,0b6h	; CNT#2, L-H WORD, 方形波, binary
	out	BEEP_MODE_AT,AL		; AT
	mov	AL,CL	; 下位
	out	BEEP_CNT_AT,AL		; AT
	mov	AL,CH	; 上位, count start
	out	BEEP_CNT_AT,AL		; AT
	jmp	short B_INIT_DONE
	EVEN

B_INIT_PC98_2:
	;bgm_bell_mode(3, (INPB( CLOCK_CHK ) & 0x20) ? 998 : 1229);
	xor	AX,AX
	mov	ES,AX
	test	byte ptr ES:[0501H],80h
	mov	AX,TVAL8ORG/2
	jnz	short B_INIT_CLOCK8MHZ_2
	mov	AX,TVAL10ORG/2
B_INIT_CLOCK8MHZ_2:
	mov	CX,AX
	;OUTB(BEEP_MODE, ((mode & 0x03) << 1) | 0x70);
	mov	AL,3
	shl	AL,1
	or	AL,70h
	mov	DX,BEEP_MODE
	out	DX,AL			; 98
	;OUTB(BEEP_CNT, spval & 0x00ff);
	mov	AL,CL
	mov	DX,BEEP_CNT
	out	DX,AL			; 98
	;OUTB(BEEP_CNT, spval >> 8);
	mov	AL,CH
	out	DX,AL			; 98

B_INIT_DONE:
	mov	glb.init,TRUE
	xor	AX,AX			; BGM_COMPLETE
	MRETURN
endfunc			; }

func BGM_FINISH		; bgm_finish() {
	push	SI
	cmp	glb.init,0
	je	short @@NOTINITIALIZED2
	nopcall	BGM_STOP_PLAY
	nopcall	BGM_STOP_SOUND
	nopcall	_BGM_TIMER_FINISH
	mov	glb.init,0
@@NOTINITIALIZED2:

	;曲バッファ解放
	mov	SI,offset part
@@FREEMBUF:
	mov	AX,word ptr [SI].mbuf+2
	cmp	AX,0
	je	short @@NOMBUF
	push	AX
	nopcall	HMEM_FREE
	mov	word ptr [SI].mbuf+2,0
@@NOMBUF:
	add	SI,type SPART
	cmp	SI,offset part+(type SPART*PMAX)
	jne	short @@FREEMBUF

	;効果音バッファ解放
	mov	SI,offset esound
@@FREESBUF:
	;if (esound[cnt].sbuf != NULL)
	mov	AX,word ptr [SI].sbuf+2
	cmp	AX,0
	je	short @@NOSBUF
	push	AX
	nopcall	HMEM_FREE
	mov	word ptr [SI].sbuf+2,0
@@NOSBUF:
	add	SI,type SESOUND
	cmp	SI,offset esound+(type SESOUND*SMAX)
	jne	short @@FREESBUF

	pop	SI
	ret
endfunc		; }
