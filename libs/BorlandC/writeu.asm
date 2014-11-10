; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of the 'CODE' segment declaration (for obvious reasons)
; * removal of external function references (and subsequent correction of
;   their symbols in the code)

;[]-----------------------------------------------------------------[]
;|      WRITEU.ASM -- User entry point for write()                   |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
;
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
;

;----------------------------------------------------------------------
; Define user entry point write, which merely jumps to __write.

ifdef   _BUILDRTLDLL                    ; DLL library

Proc@   write, __CDECL__
        publicdll _write

elseifdef       __PAS__                 ; PASCAL-callable library

PubProc@ WRITE, __PASCAL__
write@   equ     WRITE

else                                    ; Normal C library
PubProc@ write, __CDECL__
endif

        jmp     ___write                ; jump to internal function

EndProc@ write
