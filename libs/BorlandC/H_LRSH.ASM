; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of the 'CODE' segment declaration (for obvious reasons)

;[]-----------------------------------------------------------------[]
;|      H_LRSH.ASM -- long shift right                               |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        public  LXRSH@
        public  F_LXRSH@
        public  N_LXRSH@

N_LXRSH@:
        pop     bx                      ;fix up for far return
        push    cs
        push    bx
LXRSH@:
F_LXRSH@:
        cmp     cl,16
        jae     @@lsh@small
        mov     bx,dx                   ; save the high bits
        shr     ax,cl                   ; now shift each half
        sar     dx,cl
;
;                       We now have a hole in AX where the lower bits of
;                       DX should have been shifted.  So we must take our
;                       copy of DX and do a reverse shift to get the proper
;                       bits to be or'ed into AX.
;
        neg     cl
        add     cl,16
        shl     bx,cl
        or      ax,bx
        retf
@@lsh@small:
        sub     cl,16                   ; for shifts more than 15, do this
                                        ; short sequence.
        xchg    ax,dx                   ;
        cwd                             ; We have now done a shift by 16.
        sar     ax,cl                   ; Now shift the remainder.
        retf
