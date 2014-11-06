; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of external data and function references (and subsequent
;   correction of their symbols in the code)
; * removal of the segment declarations (for obvious reasons)
; * nopcall to ensure binary compatibility to the original builds of the PC-98
;   Touhou games

;[]-----------------------------------------------------------------[]
;|      SETENVP.ASM -- Prepare Environment                           |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        SUBTTL  Prepare Environment
        PAGE

;       Allocate a buffer to hold environment variables

__setenvp       proc near
                push    si
                push    di

IF      LDATA EQ 0
                mov     cx, _envLng@
                push    cx
                call    _malloc
                pop     cx
                mov     di, ax
                or      ax, ax
                jz      _Failed         ; Memory allocation failed
                push    ds
                push    ds
                pop     es
                mov     ds, _envseg@
                xor     si, si
                cld
                rep     movsb
                pop     ds
                mov     di, ax
ELSE
                mov     es, _envseg@
                xor     di, di
ENDIF

;       Allocate a buffer to hold envp array

                push    es              ; Save Environment Segment address
                push    _envSize@
                nopcall _malloc
                pop     bx
                mov     bx, ax
                pop     es              ; Restore Environment Segment address
IF      LDATA
                mov     word ptr environ@, ax
                mov     word ptr environ@+2, dx
                push    ds
                mov     ds, dx
                or      ax, dx
ELSE
                mov     word ptr environ@, ax
                or      ax, ax
ENDIF
                jnz     SetEnviron
                nop                     ; Touhou PC-98 compatibility
                nop                     ; Touhou PC-98 compatibility
_Failed         label   near            ; Memory allocation failed
                jmp     __abort


;       Now, store environment variables address

SetEnviron      label   near
                xor     ax, ax
                mov     cx, -1
IF  LDATA
                cmp byte ptr es:[di], 0     ; Is the environment empty?
ELSE
                cmp byte ptr [di], 0        ; Is the environment empty?
ENDIF
                je  SetEnviron1
SetEnviron0     label   near
                mov     [bx], di
IF      LDATA
                mov     [bx+2], es
                add     bx, 4
ELSE
                add     bx, 2
ENDIF
                repnz   scasb
                cmp     es:[di], al
                jne     SetEnviron0         ; Set next pointer
SetEnviron1     label   near
IF      LDATA
                mov     [bx], ax
                mov     [bx+2], ax
                pop     ds
ELSE
                mov     [bx], ax
ENDIF
                pop     di
                pop     si

IF      LDATA
                mov     ax,word ptr _environ+2
                mov     word ptr __C0environ+2,ax
ENDIF
                mov     ax,word ptr _environ
                mov     word ptr __C0environ,ax

                ret

__setenvp       endp
