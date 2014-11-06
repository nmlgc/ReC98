; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of external data and function references (and subsequent
;   correction of their symbols in the code)
; * code for non-text segments being moved to separate slices
; * and two changes specific to the Japanese / PC-98 version. These are:
;   * BadProgName moved in front of NextChar
;   * and an additional section in NextChar to check for DBCS lead bytes

;[]-----------------------------------------------------------------[]
;|      SETARGV.ASM -- Parse Command Line                            |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        SUBTTL  Parse Command Line
        PAGE
;/*                                                     */
;/*-----------------------------------------------------*/
;/*                                                     */
;/*     Parse Command Line                              */
;/*     ------------------                              */
;/*                                                     */
;/*-----------------------------------------------------*/
;/*                                                     */
PSPCmd          equ     00080h

SavedDS         dw      ?

ifdef   WILD

;------------------------------------------------------------------------------
;
; Not enough space on stack for the program name.
;
BadProgName     label   near
                jmp     abort@

                public  __wildargv
__wildargv      proc near

else

__setargv       proc near
endif

;==============================================================================
;       First, save caller context and Return Address
; Please be aware that this code was hacked from TC 2.0 to work with the
; new startup/exit method.  Since setargv tries to put the arguments on
; the stack it has to make an assumption about what is already on the
; stack.  Under 2.0 all that was on the stack was the return address into
; the startup code.  Under the new startup/exit method there is a return
; address (always near), a saved DS, and another near return address.
; setargv really needs to be rewritten but for now this hack is in place
; to make it work.  If you change what is on the stack in any way you will
; have to change this code!

                pop     word ptr SavedReturn
                pop     word ptr SavedDS2
                pop     word ptr SavedReturn2
                mov     SavedDS, ds
                mov     SavedSI, si
                mov     SavedDI, di
                cld

;       Compute Command Line size

                mov     es, _psp@
                mov     si, PSPCmd      ; ES: SI = Command Line address
                xor     ah, ah
                lods    byte ptr es:[si]
                inc     ax              ; AX = Command Line size including \r
                mov     bp, es
                xchg    dx, si          ; BP:DX = Command Line address
                xchg    bx, ax          ; BX    = Command line size

;       Compute Program Name size

                mov     si, _envLng@
                inc     si
                inc     si              ; SI = Program name offset
                mov     cx, 1           ; CX = Filename size (includes \0)
                cmp     _osmajor@, 3
                jb      NoProgramName
                mov     es, _envseg@
                mov     di, si          ; SI = argv[0] address
                mov     cl, 07fh
                xor     al, al
                repnz   scasb
                jcxz    BadProgName
                xor     cl, 07fh        ; CX = Filename size (includes \0)
NoProgramName   label   near

;       Reserve space for the arguments

                push    ax              ; To be sure nothing in SS:FFFF
                mov     ax, cx
ifndef  WILD
                add     ax, bx
endif
                inc     ax
                and     ax, not 1
                mov     di, sp
                sub     di, ax
                jb      BadProgName
                mov     sp, di          ; SS:DI = Command Line storage address

;       Copy ProgName to the stack

                push    es
                pop     ds
                push    ss
                pop     es
ifndef  WILD
                push    cx
endif
                dec     cx
                rep     movsb
                xor     al, al
                stosb                   ; ASCIIZ string

;       Process Command Line.

;==============================================================================
ifdef WILD
;==============================================================================

;
; The value of "wild_attr" is used in the "findfirst" call as the file
; attribute.
;
; The default value is 0, which will only include "regular" files.
;
; Adding 10H to this value will include directories, 04h will include system
; files, and 02h will include hidden files.
;

wild_attr       equ     0                       ; include only regular files

;------------------------------------------------------------------------------

ffblk           struc

ff_reserved     db      21 dup (?)
ff_attrib       db      ?
ff_ftime        dw      ?
ff_fdate        dw      ?
ff_fsize        dd      ?
ff_name         db      14 dup (?)

ffblk           ends

wild_init_space equ     128                     ; initial buffer allocation
wild_more_space equ     256                     ; buffer size increment

;------------------------------------------------------------------------------

wild_buff_addr  equ     [bp]
wild_buff_size  equ     [bp+4]
wild_buff_max   equ     [bp+6]
wild_arg_src    equ     [bp+8]
wild_arg_dst    equ     [bp+10]

wild_argument   equ     [bp+12]
wild_destin     equ     [bp+16]
wild_path_len   equ     [bp+20]
wild_argc       equ     [bp+22]

wild_DTA_save   equ     [bp+24]
wild_ffblk      equ     [bp+28]

wild_frame_size equ     28 + TYPE ffblk

;------------------------------------------------------------------------------

                mov     cx, bp                  ; save segment of command line
                dec     bx                      ; don't need trailing \0

                sub     sp, wild_frame_size
                mov     bp, sp                  ; bp points at local variables

                push    dx                      ; save cmd line addr
                push    cx                      ; save cmd line seg
                push    bx                      ; save cmd line size
                mov     ax, wild_init_space
                mov     wild_buff_size, ax      ; save initial size
ifndef  __HUGE__
                mov     ds, SavedDS
endif
                push    ax
                call    sbrk@
                pop     cx                      ; toss parameter
                pop     cx                      ; restore cmd line size
                pop     ds                      ; restore cmd line seg
                pop     si                      ; restore cmd line addr

                mov     wild_buff_addr, ax      ; save offset
if      LDATA
                mov     wild_buff_addr+2, dx    ; save segment
                and     ax, dx
else
                mov     wild_buff_addr+2, ss    ; seg = SS
endif
                cmp     ax, -1
                je      NoSbrkSpace             ; abort if not enough space
                add     ax, wild_buff_size
                mov     wild_buff_max, ax       ; save max offset

                mov     ah, 2fh
                int     21h                     ; get current DTA
                mov     wild_DTA_save, bx
                mov     wild_DTA_save+2, es
                push    ds
                push    ss                      ; fflbk is on stack
                pop     ds
                lea     dx, wild_ffblk
                mov     ah, 1ah
                int     21h                     ; switch DTA to ffblk
                pop     ds

                les     di, dword ptr wild_buff_addr
                xor     dx, dx                  ; dx = # of arguments
;
; Start new argument.
;
NewArg:         mov     wild_arg_dst, di
                xor     bh, bh                  ; bh = wildcard flag
;
; Skip leading whitespace.
;
ArgCopy:        mov     wild_arg_src, si        ; save address of argument
                call    GetChar
                jc      ArgCopyDone             ; jump if no more characters
                jz      ArgCopyLoop
                cmp     al, ' '
                je      ArgCopy                 ; skip whitespace
                cmp     al, 9
                je      ArgCopy
                cmp     al, 13
                je      ArgCopy
                cmp     al, '"'
                je      ArgQuote                ; jump if quoted string
;
; Loop to copy unquoted argument.
;
ArgCopyLoop:    call    ArgPushChar             ; store character in destination
                call    GetChar
                jc      ArgComplete             ; jump if end of line
                jz      ArgCopyLoop             ; jump if \"
                cmp     al, ' '
                je      ArgComplete             ; whitespace terminates
                cmp     al, 9
                je      ArgComplete
                cmp     al, 13
                je      ArgComplete             ; whitespace terminates
                cmp     al, '"'
                jne     ArgCopyLoop
ArgComplete:    call    ProcessArg              ; copy or expand argument
                jmp     SHORT NewArg

NoSbrkSpace:    jmp     abort@                  ; error jump

;
; Here if quoted argument.
;
ArgQuote:       call    GetChar
                jc      QuoteDone
                jz      QuoteNext
                cmp     al, '"'                 ; terminating quote ?
                je      QuoteDone
                cmp     al, 13                  ; hit end of line (CR)?
                je      QuoteDone
QuoteNext:      call    ArgPushChar             ; store character in destination
                jmp     SHORT ArgQuote
;
; End of a quoted argument. Push terminating null, do not expand.
;
QuoteDone:      xor     al, al
                call    ArgPushChar             ; push terminating null
                inc     dx                      ; bump arg count
                jmp     SHORT NewArg            ; go get more

;------------------------------------------------------------------------------
;
; Here when done expanding command line. Go build the argv array.
;
ArgCopyDone:    mov     ax, di                  ; ax = unused space
                sub     ax, wild_buff_max
                jz      ArgNoWaste              ; skip if all used
                push    dx
                push    di
ifndef  __HUGE__
                mov     ds, SavedDS
endif
                push    ax
                call    sbrk@                   ; release unused memory
                pop     cx                      ; toss parameter
                pop     di
                pop     dx
ArgNoWaste:     lds     si, dword ptr wild_buff_addr
                mov     cx, di
                sub     cx, si                  ; cx = number of bytes in expanded line
                inc     dx                      ; count program name
                jmp     BuildArgv

;------------------------------------------------------------------------------
;
; Routine to retrieve the next character from the command line.
;       Sets CF when end of line reached.
;       Sets ZF when \ character found (i.e. \")
;
;       bh.bit0 set if wildcard chars found (* or ?)
;       bh.bit1 set if \ character found (\")
;
GetChar         proc    near

                jcxz    GchEnd                  ; jump if no more
                lodsb
                dec     cx
                cmp     al, '\'                 ; escape ?
                je      GchEsc
                cmp     al, '?'
                je      GchWild
                cmp     al, '*'
                je      GchWild
GchRet:         or      ah, 1                   ; clear CF and ZF
                ret
GchWild:        test    bh, bh
                jnz     GchRet                  ; give up if \" has been found
                or      bh, 1
                ret
GchEsc:         jcxz    GchRet                  ; check for \ at end of line
                cmp     byte ptr [si],'"'
                jne     GchRet                  ; only \" is special
                lodsb
                dec     cx
                mov     bh, 2                   ; set \ flag
                xor     ah, ah                  ; clear CF, set ZF
                ret
GchEnd:         stc
                ret

GetChar         endp

;------------------------------------------------------------------------------
;
; Routine to expand a wildcard parameter.
;
;       DS:SI   =       argument address
;       ES:DI   =       destination
; Returns:
;       CX      =       number of expanded arguments (0 = no match)
;
WildExpand      proc    near

                push    ds
                mov     wild_argument, si
                mov     wild_argument+2, ds
                mov     wild_destin, di
                mov     wild_destin+2, es
                mov     word ptr wild_argc, 0
;
; Find the length of the path prefix, if any.
;
                mov     bx, si
WildFindPath:   lodsb
                and     al, al
                jz      WildEndPath
                cmp     al, '\'
                je      WildDelimiter
                cmp     al, ':'
                je      WildDelimiter
                cmp     al, '\'
                jne     WildFindPath
WildDelimiter:  mov     bx, si                  ; save addr past last delimiter
                jmp     SHORT WildFindPath
WildEndPath:    sub     bx, wild_argument
                mov     wild_path_len, bx

                mov     ah, 4eh
                mov     cx, wild_attr           ; file attribute
                lds     dx, dword ptr wild_argument
                int     21h                     ; find first matching file ...
                jc      WildDone
;
; We have a matching file. Add it to the destination string (unless "." or "..")
;
WildAddArg:
;
; If directories are included (10h set in wild_attr), ignore "." and ".."
;
if      wild_attr  AND 16
                push    ss
                pop     ds
                lea     si,wild_ffblk.ff_name
                cmp     byte ptr [si],'.'       ; skip if doesn't start with "."
                jne     WildNoDir
                cmp     byte ptr [si+1],0       ; check for "."
                je      WildNameNext
                cmp     word ptr [si+1],'.'     ; check for ".."
                je      WildNameNext
WildNoDir:
endif

                inc     word ptr wild_argc
                les     di, dword ptr wild_destin
                mov     cx, wild_path_len       ; prefix filename with path
                jcxz    WildCopyName
                lds     si, dword ptr wild_argument
WildCopyPath:   lodsb
                call    ArgPushChar
                loop    WildCopyPath
WildCopyName:   lea     si,wild_ffblk.ff_name   ; copy filename from ffblk
WildNameLoop:   lods    byte ptr ss:[si]
                push    ax
                call    ArgPushChar             ; store char in destination
                pop     ax
                and     al, al                  ; continue until \0
                jnz     WildNameLoop
                mov     wild_destin, di
WildNameNext:   mov     ah, 4fh
                int     21h                     ; find next matching file
                jnc     WildAddArg
;
; Done with expansion. Restore ES:DI, set CX, and return.
;
WildDone:       mov     cx, wild_argc
                les     di, dword ptr wild_destin
                pop     ds
                ret

WildExpand      endp

;------------------------------------------------------------------------------
;
; Routine to store a character in the destination string.
;
ArgPushChar     proc    near

                cmp     di, wild_buff_max       ; space available ?
                jae     ArgMoreSpace
                stosb                           ; yes --> store character
                ret
;
; No more argument space. Grab some more memory through sbrk.
;
ArgMoreSpace:   push    ds
                push    es
                push    si
                push    di
                push    ax
                push    bx
                push    cx
                push    dx

ifndef  __HUGE__
                mov     ds, SavedDS
endif
                mov     ax, wild_more_space
                add     wild_buff_size, ax      ; bump allocated size
                add     wild_buff_max, ax       ; bump end pointer
                push    ax
                call    sbrk@
                pop     cx
if      LDATA
                and     ax, dx
endif
                cmp     ax, -1
                je      NoArgSpace              ; abort if not enough space

                pop     dx
                pop     cx
                pop     bx
                pop     ax
                pop     di
                pop     si
                pop     es
                pop     ds
                stosb                           ; store character
                ret

ArgPushChar     endp

;------------------------------------------------------------------------------
;
; Not enough space to process the command line .... abort.
;
NoArgSpace:     jmp     abort@

;------------------------------------------------------------------------------
;
; Routine to process an argument.
;
ProcessArg      proc    near

                push    bx
                xor     al, al
                call    ArgPushChar             ; null-terminate
                pop     bx
                test    bh, 1                   ; wildcards present ?
                jnz     ArgWild
                inc     dx                      ; bump arg count
                ret
;
; We have a wildcard argument. Expand it.
;
ArgWild:        push    cx
                push    [si]                    ; save word following argument
                mov     byte ptr [si],0         ; null-terminate argument
                xchg    si, wild_arg_src        ; si = argument address
                push    di
                mov     di, wild_arg_dst
                push    dx
                call    WildExpand
                pop     dx
                pop     bx
                and     cx, cx                  ; see if any matched
                jnz     ArgWildSome
                mov     di, bx                  ; none ---> use unexpanded argument
                mov     cx, 1                   ; bump arg count by 1
ArgWildSome:    add     dx, cx
                mov     si, wild_arg_src
                pop     [si]                    ; restore word following argument
                pop     cx
                ret

ProcessArg      endp

;------------------------------------------------------------------------------
;
; Build the argv array. [DS:SI] is the expanded command line, CX its length.
; DX has the number of arguments (including the program name).
;
BuildArgv:      push    ds
                push    dx
                lds     dx, dword ptr wild_DTA_save
                mov     ah, 1ah
                int     21h                     ; switch to original DTA
                pop     dx
                pop     ds

                add     sp, wild_frame_size     ; remove local variables

                mov     es,SavedDS
                mov     es:[DGROUP:_argc@], dx
                inc     dx                      ; argv ends with a NULL pointer
                shl     dx, 1                   ;   argc * 2    (LDATA = 0)
IF      LDATA
                shl     dx, 1                   ;   argc * 4    (LDATA = 1)
ENDIF
                mov     bx, sp                  ; point to program name
                mov     bp, sp
                sub     bp, dx
                jb      NoArgSpace
                mov     sp, bp                  ; SS:BP = argv array address
                mov     word ptr es:[DGROUP:_argv@], bp
IF      LDATA
                mov     word ptr es:[DGROUP:_argv@+2], ss
ENDIF
                mov     [bp], bx                ; set argv[0] to program name
IF      LDATA
                mov     [bp+2], ss              ; program name is on the stack
ENDIF
                add     bp, dPtrSize

SetArgvX        label   near
                jcxz    SetLastArg
                mov     [bp], si                ; Set argv[n]
IF      LDATA
                mov     [bp+2], ds
ENDIF
                add     bp, dPtrSize
CopyArg         label   near
                lodsb
                or      al, al
                loopnz  CopyArg
                jz      SetArgvX
SetLastArg      label   near
                xor     ax, ax
                mov     [bp], ax
IF      LDATA
                mov     [bp+2], ax
ENDIF
                mov     ds, SavedDS

;==============================================================================
else
;==============================================================================

                mov     ds, bp
                xchg    si, dx          ; DS: SI = Command Line address
                xchg    bx, cx          ; CX = Command Line size including \r
                mov     ax, bx
                mov     dx, ax          ; AX = BX = DX = 0
                inc     bx              ; BX = Nb of arguments (at least 1)
Processing      label   near
                call    NextChar
                ja      NotQuote        ; Not a quote and there are more
InString        label   near
                jb      BuildArgv       ; Command line is empty now
                cmp     al, 13
                je      EndArgument
                call    NextChar        ; \r    is an argument separator
                ja      InString        ; Not a quote and there are more
NotQuote        label   near
                cmp     al, ' '
                je      EndArgument     ; Space is an argument separator
                cmp     al, 13
                je      EndArgument     ; \r    is an argument separator
                cmp     al, 9
                jne     Processing      ; \t    is an argument separator
EndArgument     label   near
                xor     al, al          ; Space and TAB are argument separators
                jmp     short Processing

;       Invalid program name

BadProgName     label   near
                nop                     ; PC-98 / Japanese-specific
                nop                     ; PC-98 / Japanese-specific
                jmp     __abort

;       Character test function used in SetArgs
;               On entry AL holds the previous character
;               On exit  AL holds the next character
;                        ZF on if the next character is quote (") and AL = 0
;                        CF on if end of command line and AL = 0

NextChar        PROC    NEAR
                or      ax, ax
                jz      NextChar0
                inc     dx              ; DX = Actual length of CmdLine
                stosb
                or      al, al
                jnz     NextChar0
                inc     bx              ; BX = Number of parameters
NextChar0       label   near
                xchg    ah, al
                xor     al, al
                stc
                jcxz    NextChar2       ; End of command line --> CF ON
                lodsb
                dec     cx
; PC-98 / Japanese-specific code below...
; ---
                cmp     dh, 1
                jz      NextCharSJIS0
                xor     dh, dh
                push    ax
                push    bx
                push    cx
                push    dx
                push    ds
                push    es
                mov     ds, SavedDS
                push    ax
                nopcall ___path_isdbcsleadbyte
                or      ax, ax
                pop     cx
                pop     es
                pop     ds
                pop     dx
                pop     cx
                pop     bx
                pop     ax
                jz      NextCharSJIS1

NextCharSJIS0:
                inc     dh

NextCharSJIS1:
                cmp     dh, 0
                jnz     NextChar1
; ---
                sub     al, '"'
                jz      NextChar2       ; Quote found --> AL = 0 and ZF ON
                add     al, '"'
                cmp     al,'\'
                jne     NextChar1       ; It is not a \
                cmp     byte ptr ds:[si], '"'
                jne     NextChar1       ; Only " is transparent after \
                lodsb
                dec     cx
NextChar1       label   near
                or      si, si          ; Be sure both CF & ZF are OFF
NextChar2       label   near
                ret
NextChar        ENDP

;       Now, build the argv array

BuildArgv       label   near
                pop     cx
                xor     dh, dh          ; PC-98 / Japanese-specific
                add     cx, dx          ; CX = Argument area size
                mov     ds, SavedDS
                mov     _argc@, bx
                inc     bx              ; argv ends with a NULL pointer
                add     bx, bx          ;        argc * 2       (LDATA = 0)
IF      LDATA
                add     bx, bx          ;        argc * 4       (LDATA = 1)
ENDIF
                mov     si, sp
                mov     bp, sp
                sub     bp, bx
                jb      BadProgName
                mov     sp, bp          ; SS:BP = argv array address
                mov     word ptr _argv@, bp
IF      LDATA
                mov     word ptr _argv@+2, ss
ENDIF
SetArgvX        label   near
                jcxz    SetLastArg
                mov     [bp], si        ; Set argv[n]
IF      LDATA
                mov     [bp+2], ss
ENDIF
                add     bp, dPtrSize
CopyArg         label   near
                lods    byte ptr ss:[si]
                or      al, al
                loopnz  CopyArg
                jz      SetArgvX
SetLastArg      label   near
                xor     ax, ax
                mov     [bp], ax
IF      LDATA
                mov     [bp+2], ax
ENDIF

;==============================================================================
endif           ;       ifdef WILD
;==============================================================================

;       Restore caller context and exit

                mov     ds,SavedDS
                mov     si,SavedSI
                mov     di,SavedDI
                push    word ptr SavedReturn2
                push    word ptr SavedDS2
                mov     ax,__argc
                mov     __C0argc,ax
IF      LDATA
                mov     ax,word ptr __argv+2
                mov     word ptr __C0argv+2,ax
ENDIF
                mov     ax,word ptr __argv
                mov     word ptr __C0argv,ax

                jmp     word ptr SavedReturn
ifdef   WILD
__wildargv      endp
else
__setargv       endp
endif
