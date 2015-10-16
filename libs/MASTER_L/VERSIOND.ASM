; Subject:
;	Master.lib Version String Definition
;
; Author:
;	恋塚昭彦
; 
; Revision History:
;	92/12/22 Initial( version 0.10 )
;	93/ 1/27 version 0.11
;	93/ 2/12 medium,compact
;	93/ 2/14 version 0.12
;	93/ 3/11 version 0.13
;	93/ 3/23 version 0.14
;	93/ 4/12 version 0.15
;	93/ 5/16 version 0.16
;	93/ 5/17 version 0.17
;	93/ 6/ 1 version 0.18
;	93/ 6/27 version 0.19
;	93/ 8/10 version 0.20
;	93/11/24 version 0.21
;	94/ 2/ 7 version 0.22
;	94/ 2/21 version 0.22a
;	95/  /   version 0.23

VERS	macro lab,str
	public lab
lab	db 'MASTER', str,'.LIB Version '
	endm

IF @MODEL LE 2
	VERS _Master_Version_NEAR,'S'
ELSEIF @MODEL EQ 5
	VERS _Master_Version_FAR,'L'
ELSEIF @MODEL EQ 4
	VERS _Master_Version_MEDIUM,'M'
ELSEIF @MODEL EQ 3
	VERS _Master_Version_COMPACT,'C'
ENDIF
	public _Master_Version
	public _Master_Copyright
_Master_Version db '0.23', ' '
_Master_Copyright label byte
	db 'Copyright (c)1995 '
	db 'A.Koizuka,'
	db 'Kazumi,'
	db 'steelman,'
	db 'iR,'
;	db ','		; 改造した場合はここに名前を追加すること
	db 'All rights reserved.',0
	db 0 ; word alignment
