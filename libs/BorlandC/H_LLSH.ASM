; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of the 'CODE' segment declaration (for obvious reasons)

;[]-----------------------------------------------------------------[]
;|      H_LLSH.ASM -- long shift left                                |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        public  LXLSH@
        public  F_LXLSH@
        public  N_LXLSH@

N_LXLSH@:
        pop     bx                      ;fix up for far return
        push    cs
        push    bx
LXLSH@:
F_LXLSH@:
        cmp     cl,16
        jae     @@lsh@small
        mov     bx,ax                   ; save the low bits
        shl     ax,cl                   ; now shift each half
        shl     dx,cl
;
;                       We now have a hole in DX where the upper bits of
;                       AX should have been shifted.  So we must take our
;                       copy of AX and do a reverse shift to get the proper
;                       bits to be or'ed into DX.
;
        neg     cl
        add     cl,16
        shr     bx,cl
        or      dx,bx
        retf
@@lsh@small:
        sub     cl,16                   ; for shifts more than 15, do this
                                        ; short sequence.
        xchg    ax,dx
        xor     ax,ax                   ; We have now done a shift by 16.
        shl     dx,cl                   ; Now shift the remainder.
        retf
