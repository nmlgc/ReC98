; master library - BGM
;
; Description:
;
;
; Function/Procedures:
;	void _bgm_pinit(PART near *part2);
;
; Parameters:
;
;
; Returns:
;
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
;
; Revision History:
;	93/12/19 Initial: b_pinit.asm / master.lib 0.22 <- bgmlibs.lib 1.12

func _BGM_PINIT
	mov	BX,SP
	part2	= (RETSIZE+0)*2
	mov	DX,SS:[BX+part2]
	;楽譜ポインタ設定 
	;part2->ptr = part2->mbuf + glb.track[glb.mcnt - 1];
	mov	BX,glb.mcnt
	dec	BX
	shl	BX,1
	mov	AX,glb.track[BX]
	mov	BX,DX
	add	AX,word ptr [BX].SPART.mbuf
	mov	word ptr [BX].SPART.pptr,AX
	mov	AX,word ptr [BX].SPART.mbuf+2
	mov	word ptr [BX].SPART.pptr+2,AX
	;オクターブ = 4
	mov	[BX].SPART.oct,DEFOCT
	;音符 = R
	mov	[BX].SPART.note,REST
	;音長 = 四分音符
	mov	AX,DEFLEN
	mov	[BX].SPART.dflen,AX
	mov	[BX].SPART.len,AX
	;音長カウンタ
	mov	[BX].SPART.lcnt,DEFLCNT
	;テヌートOFF
	mov	[BX].SPART.tnt,OFF
	ret	2
endfunc
