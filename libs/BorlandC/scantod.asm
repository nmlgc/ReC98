; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of the segment declarations (for obvious reasons)
; * one underscore instead of two for every function name in order to better
;   differentiate the actual implementation from the jump procedures here

;[]-----------------------------------------------------------------[]
;|      SCANTOD.asm -- Ascii to double conversion                    |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
;
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
;

;       Segment and Group declarations

                public _scantod
_scantod       proc near
IFDEF   __HUGE__
ExtSym@         DGROUP@, WORD, __PASCAL__
                mov     es, cs:DGROUP@@
                jmp     ES:[__ScanTodVector]
ELSE
                jmp     [__ScanTodVector]
ENDIF
_scantod        endp


                public _scanrslt
_scanrslt      proc near
IFDEF   __HUGE__
ExtSym@         DGROUP@, WORD, __PASCAL__
                mov     es, cs:DGROUP@@
                jmp     ES:[__ScanTodVector + 2]
ELSE
                jmp     [__ScanTodVector + 2]
ENDIF
_scanrslt       endp

                public _scanpop
_scanpop       proc near
IFDEF   __HUGE__
ExtSym@         DGROUP@, WORD, __PASCAL__
                mov     es, cs:DGROUP@@
                jmp     ES:[__ScanTodVector + 4]
ELSE
                jmp     [__ScanTodVector + 4]
ENDIF
_scanpop        endp
