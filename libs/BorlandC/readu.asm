; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of the 'CODE' segment declaration (for obvious reasons)
; * removal of external function references (and subsequent correction of
;   their symbols in the code)

;[]-----------------------------------------------------------------[]
;|      READU.ASM -- User entry point for read()                     |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
;
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
;

;----------------------------------------------------------------------
; Define user entry point read, which merely jumps to __read.

ifdef   _BUILDRTLDLL                    ; DLL library

Proc@   read, __CDECL__
        publicdll _read

elseifdef       __PAS__                 ; PASCAL-callable library

PubProc@ READ, __PASCAL__
read@   equ     READ

else                                    ; Normal C library
PubProc@ read, __CDECL__
endif

        jmp     ___read                 ; jump to internal function

EndProc@ read
