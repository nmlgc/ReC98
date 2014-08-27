; master library - (pf.lib)
;
; Description:
;	pf.lib関連のグローバル変数定義
;
; Global Variables:
;	bbufsiz
;	pferrno
;	pfkey
;
; Author:
;	iR
;	恋塚昭彦
;
; Revision History:
; PFGLOBAL.ASM         249 94-09-17   23:06
;	95/ 1/10 Initial: pf.asm/master.lib 0.23

	public bbufsiz,_bbufsiz
_bbufsiz label word
bbufsiz		dw	BBUFSIZE

	public pferrno,_pferrno
_pferrno label word
pferrno		dw	PFEZERO

	public pfkey,_pfkey
_pfkey label byte
pfkey		db	0
