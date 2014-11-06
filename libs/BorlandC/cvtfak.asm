; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of external data and function references (and subsequent
;   correction of their symbols in the code)
; * code for non-text segments being moved to separate slices

;[]-----------------------------------------------------------------[]
;|      CVTFAK.ASM -- abort when float isn't present                 |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

;       Public references

                public  __cvtfak
__cvtfak        equ     0

;-------------------------------------------------------------------------
;               Get printf() specific part of message
;-------------------------------------------------------------------------
_FakRealCvt     proc near
                mov     dx, offset DGROUP: RealMSG      ; Message address
                jmp     short DisplayMessage            ; Display the message
_FakRealCvt     endp

;-------------------------------------------------------------------------
;               Get scanf() specific part of message
;-------------------------------------------------------------------------
_FakScanTod     proc near
                mov     dx, offset DGROUP: ScanMSG      ; Message address
;
; By letting the _FakScanTod PROC to 'fall into' the 'DisplayMessage' routine
; we save the cost of a JMP instruction.  This is a somewhat cheap trick but
; the purpose is quite clear here.

DisplayMessage  LABEL   NEAR

;-------------------------------------------------------------------------
;               Display FLOAT not linked message
;-------------------------------------------------------------------------
IFDEF   __HUGE__
                mov     ds, cs:DGROUP@@                 ; Get DS if we're huge
ENDIF

                mov     cx, lgth_UNIQ                   ; Message length
                mov     ah, 040H                        ; Write
                mov     bx, 2                           ;   to
                int     021h                            ;      'stdout'

                mov     cx, lgth_Common                 ; Common msg length
                mov     dx, offset DGROUP: CommonMSG    ; Common msg address
                mov     ah, 040H                        ; Write to
                int     021h                            ;      'stdout'
                jmp     __abort                         ; abort();

_FakScanTod     endp
