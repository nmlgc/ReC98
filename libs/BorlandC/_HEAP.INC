;[]-----------------------------------------------------------------[]
;|      _HEAP.INC                                                    |
;|                                                                   |
;|      C/C++ Run Time Library        version 4.0                    |
;|                                                                   |
;|      Copyright (c) 1987, 1991 by Borland International Inc.       |
;|      All Rights Reserved.                                         |
;[]-----------------------------------------------------------------[]

;-----------------------------------------------------------------------
; Values returned by some of the heap routines.
;-----------------------------------------------------------------------
_HEAPEMPTY	EQU	1
_HEAPOK		EQU	2
_FREEENTRY	EQU	3
_USEDENTRY	EQU	4
_HEAPEND	EQU	5
_HEAPCORRUPT	EQU	-1
_BADNODE	EQU	-2
_BADVALUE	EQU	-3

