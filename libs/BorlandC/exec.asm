; *Not* the original file, but an edit to turn it into an includable slice.
; Changes include:
; * removal of RULES.ASI to eliminate redundancy
; * removal of external data declarations
; * removal of the segment macro references (for obvious reasons)
; * and a section of code in CopyPathName, where the Japanese / PC-98 version
;   of the Borland C runtime verifies the executable type in advance, and also
;   checks the entire file extension rather than just its first letter
;   (presumably to eliminate false positives when dealing with Shift-JIS).

;[]-----------------------------------------------------------------[]
;|      EXEC.ASM -- Execute a program with Overlay                   |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        ;* Miscellaneous equates */

ExeSignature    equ     05A4Dh

        ;/* Data for the Loader */

LdDesc          STRUC
LdErrorMsg      db      'Exec failure.',00Dh,00Ah
LdStack         db      80H dup(?)      ;Loader stack
LdPSP           dw      ?               ;PSP address
LdPathName      db      80 dup(?)       ;File to be loaded
LdAX            dw      ?               ;Parse file name results
LdExeSignature  dw      ?               ;EXE header buffer
LdLength        dw      ?
LdNbPages       dw      ?
LdNbItems       dw      ?
LdHdrSize       dw      ?
LdMin           dw      ?
LdMax           dw      ?
LdSS            dw      ?
LdSP            dw      ?
LdCheckSum      dw      ?
LdIP            dw      ?
LdCS            dw      ?
LdLoadAddr      dw      ?               ;Load Overlay interface block
LdRelocFactor   dw      ?               ;Relocation factor to be used
LdDesc          ENDS

        SUBTTL  Loader program
        PAGE
;/*                                                      */
;/*------------------------------------------------------*/
;/*                                                      */
;/*     Loader Program                                   */
;/*     --------------                                   */
;/*                                                      */
;/*------------------------------------------------------*/
;/*                                                      */
LoaderDatas     db      size LdDesc dup (0)
_Loader         PROC    NEAR            ;CX = EnvSeg, DX = End of Memory

        ;/* Setup segment registers */

                xor     di, di
                mov     ax, cs
                mov     ds, ax
                mov     es, ax
                cli
                mov     ss, ax
                lea     sp, [di+LdPSP]
                sti

        ;/* Load The Program */

                push    cx
                push    dx
                mov     ax, 4B03h
                lea     bx, [di+LdLoadAddr]
                lea     dx, [di+LdPathName]
                int     21h
                pop     dx
                pop     cx
                jb      LoadError
                xor     di, di
                cli
                mov     ss, [di+LdSS]
                mov     sp, [di+LdSP]
                sti
                mov     bp, sp
                xor     ax, ax
                push    ax              ;Return to MSDOS for .COM
                mov     ax, [di+LdPSP]
                mov     ds, ax
                mov     es, ax
                mov     es:[2h], dx      ;Set End of Program into PSP
                mov     es:[2ch], cx     ;Set EnvSeg into PSP
                mov     ax, cs:[di+LdAX] ;AX = validity of FCBs
                jmp     dword ptr cs:[LdIP]

        ;/* Fatal Error if unable to load the program */

LoadError       label   near
                mov     ah, 040h
                mov     bx, 2
                mov     cx, LdStack - LdErrorMsg
                xor     dx, dx
                int     21h             ;Error message on stderr
                mov     ax, 4C02h
                int     21h             ;exit(2)
_Loader         ENDP
LoaderSize      equ     ($ - LoaderDatas + 15) / 16
wLoaderSize     equ     LoaderSize * 8
LoaderVector    dd      _Loader - LoaderDatas
        SUBTTL  Loader program
        PAGE
;/*                                                      */
;/*------------------------------------------------------*/
;/*                                                      */
;/* int _exec(pathP, cmdP, envP);                        */
;/*     char    *pathP;                                  */
;/*     char    *cmdP;                                   */
;/*     char    *envP;                                   */
;/*                                                      */
;/*------------------------------------------------------*/
;/*                                                      */

pathP           equ     4

IF LDATA
cmdP            equ     pathP + 4
envP            equ     cmdP + 4
ELSE
cmdP            equ     pathP + 2
envP            equ     cmdP + 2
ENDIF

FileHandle      equ     2
MemSize         equ     FileHandle + 2
EnvSize         equ     MemSize + 2
EnvAddr         equ     EnvSize + 4
OldEnv          equ     EnvAddr + 2

OldEnvSave      dw      ?
UseOldEnv       db      1                       ;flag, defaults to true

                public  __exec
__exec          proc    near
                push    bp
                mov     bp, sp
                sub     sp, OldEnv
                cld
                push    si
                push    ds
                push    di
                push    es

IFDEF   __HUGE__
                mov     ds, cs:DGROUP@@         ; Get DS if we're huge
ENDIF
                mov     ax,__envseg             ;save old environment
                mov     cs:OldEnvSave,ax

        ;/* Open the file to be loaded */

                mov     ax, 3d00h
                pushDS_
                LDS_    dx, [bp+pathP]
                int     21h
                popDS_
                mov     [bp-FileHandle], ax
                jnb     CopyCmdLine
                jmp     ExecExit

        ;/* Copy the command line into the PSP */

CopyCmdLine     label   near
IFDEF   __HUGE__
                mov     ax, seg _psp@
                mov     ds, ax
ENDIF
                mov     es, _psp@
                mov     LoaderDatas.LdPSP, es
                mov     ax, es:[2ch]
                mov     [bp-OldEnv], ax
                mov     di, 080h
                pushDS_
                LDS_    si, [bp+cmdP]
                lodsb
                mov     dx, si           ;Save cmdP for parse
                stosb
                xor     cx, cx
                mov     cl, al
                inc     cx
                rep     movsb

        ;/* Parse the command line for FCBs */

                mov     ax, 2901h
                mov     si, dx
                mov     di, 05ch
                int     21h             ;Build FCB 1 in PSP
                mov     byte ptr LoaderDatas.LdAX, al

FindWhite       label   near
                mov     al,[si]
                cmp     al,20h         ; Space
                je      NextFCB
                cmp     al,09h         ; Tab
                je      NextFCB
                cmp     al,0dh         ; Carriage Return
                je      NextFCB
                inc     si
                jmp     FindWhite

NextFCB         label   near
                mov     ax, 2901h
                mov     di, 06ch
                int     21h             ;Build FCB 2 in PSP
                mov     byte ptr LoaderDatas.LdAX+1, al
                popDS_

        ;/* Get the maximum memory block size */

                mov     ah, 4Ah
                mov     bx, -1
                int     21h
                cmp     byte ptr _version@, 3
                jnb     GetMaxMem
                sub     bx, 280h

GetMaxMem       label   near
                mov     [bp-MemSize], bx

        ;/* Compute environment size */

IF LDATA
                mov     ax, [bp+envP]
                mov     dx, [bp+envP+2]
ELSE
                mov     ax, [bp+envP]
                or      ax, ax
                mov     dx, ds
                jnz     DoWeHaveAnEnv
                cwd
ENDIF

DoWeHaveAnEnv   label   near
                mov     bx, ax
                or      bx, dx
                jnz     WeHaveAnEnv
                xor     ax, ax
                mov     di, ax
                jmp     short SetEnvSize

WeHaveAnEnv     label   near
                mov     es, dx
                mov     di, ax
                push    di
                mov     cx, -1
                xor     ax, ax

GetEnvSize      label   near
                repnz   scasb
                cmp     es:[di], al
                jne     GetEnvSize
                dec     cx
                add     di, 3
                repnz   scasb           ;/* EnvSize += PathSize */
                dec     cx
                mov     ax, cx
                neg     ax
                pop     di

SetEnvSize      label   near
                mov     [bp-EnvAddr], di
                mov     [bp-EnvAddr+2], es
                add     ax, 15
                mov     cx, 4
                shr     ax, cl
                mov     [bp-EnvSize], ax

                mov     si,__envseg     ;get the arena header for the environ
                dec     si
                mov     es,si
                cmp     ax,word ptr es:[03]     ;can we use the orig environ?
                jbe     SavePath

                dec     cs:UseOldEnv            ;set to false
                inc     ax
                sub     [bp-MemSize], ax        ;Reserve space for Env

        ;/* Save the pathname of the file to be loaded */
SavePath        label   near
                LDS_    si, [bp+pathP]
                push    cs
                pop     es
                lea     di, LoaderDatas.LdPathName

CopyPathName    label   near
                lodsb
                stosb
                or      al, al
                jnz     CopyPathName

        ;/* Process the file according to its type */

                mov     bx, [bp-FileHandle]

; PC-98 / Japanese-specific code below...
; ---
                push    ds
                pop     es
                push    cs
                pop     ds
                mov     di, offset LoaderDatas
                mov     ah, 3fh
                mov     cx, LdLoadAddr - LdExeSignature
                lea     dx, [di+LdExeSignature]
                int     21h
                jb      ExecError
                cmp     [di+LdExeSignature], ExeSignature
                jz      EXEFile
                mov     ax, es:[si-5]
                or      ah, ' ' ; one space
                cmp     ax, 'c.'
                jnz     NoExec
                mov     ax, es:[si-3]
                or      ax, '  ' ; two spaces
                cmp     ax, 'mo'
                jnz     NoExec
                jmp     COMFile

NoExec          label   near
                mov     ax, 11

        ;/* Here comes all Exec Error */

ExecError       label   near
                push    ax
                mov     ah, 3eh
                mov     bx, [bp-FileHandle]
                int     21h
                pop     ax
                jmp     ExecExit

        ;/* This file must be an .EXE file */

EXEFile         label   near
                mov     ax, [di+LdNbPages]
                xor     dx, dx
                mov     dl, ah
                mov     ah, al
                xor     al, al
                shl     ax, 1
                rcl     dx, 1            ;DX:AX = NbPages * 512
                add     ax, [di+LdLength]
                adc     dx, 0
                mov     cx, 4

EXECompute      label   near
                shr     dx, 1
                rcr     ax, 1
                loop    EXECompute
                inc     ax
                sub     ax, [di+LdHdrSize]
                add     ax, [di+LdMin]
                xchg    bx, ax
                mov     ax, [di+LdPSP]
                add     ax, 16
                add     [di+LdCS], ax
                add     [di+LdSS], ax
                xchg    ax, bx
                jmp     short IsItEnough

        ;/* The file to be loaded is .COM file */

COMFile         label   near
                mov     ax, 4202h
                xor     cx, cx
                xor     dx, dx
                int     21h
                mov     cx, 4

COMCompute      label   near
                shr     dx, 1
                rcr     ax, 1
                loop    COMCompute
                inc     ax
                xchg    bx, ax
                mov     ax, [di+LdPSP]
                mov     [di+LdCS], ax
                mov     [di+LdIP], 0100h
                mov     [di+LdSS], ax
                add     ax, 16
                xchg    ax, bx

IsItEnough      label   near    ;AX = Pgm requirements, BX = Pgm Load Addr
                mov     [di+LdLoadAddr], bx
                mov     [di+LdRelocFactor], bx
                add     ax, LoaderSize
                cmp     ax, [bp-MemSize]
                mov     ax, 8
                jna     $+5
                jmp     ExecError

        ;/* Close the file before load it */

                mov     ah, 3eh
                mov     bx, [bp-FileHandle]
                int     21h

        ;/* Takes all the memory above the current program */

                mov     es, [di+LdPSP]
                mov     ah, 4ah
                mov     bx, [bp-MemSize]
                int     21h
                jnb     $+5
                jmp     ExecError

        ;/* Move the Loader before loading the overlay */

                add     bx, [di+LdPSP]
                mov     dx, bx                   ;Save end of memory
                sub     bx, LoaderSize+1
                mov     word ptr LoaderVector+2, bx
                mov     es, bx
                mov     cx, wLoaderSize
                mov     si, offset LoaderDatas
                xor     di, di
                rep     movsw

        ;/* Copy the environment */

                mov     es, [bp-OldEnv]
                mov     cx, [bp-EnvSize]
                cmp     cs:UseOldEnv,0
                jne     ReUseEnv

                mov     ah, 48h
                mov     bx, cx
                int     21h
                jb      ExecExit
                jmp     short CopyEnv

ReUseEnv:       mov     ax, cs:OldEnvSave
CopyEnv:        mov     es, ax
                xor     di, di
                lds     si, [bp-EnvAddr]
                add     cx, cx
                add     cx, cx
                add     cx, cx
                rep     movsw
                push    es

        ;/* Call exit procedures. Note: do not close file handles */
        ;/* Once we do this we can't go back!                     */

                push    dx
                push    ds
                mov     ds, cs:DGROUP@@         ; Get DS
                nopcall __cexit
                pop     ds
                pop     dx

        ;/* Free the old environment space */

                cmp     cs:UseOldEnv,0
                jne     ReadyToOverlay
                mov     es, cs:OldEnvSave
                mov     ah, 49h
                int     21h

        ;/* Jump to Loader and overlay the current program */

ReadyToOverlay  label   near
                pop     cx
                jmp     LoaderVector

        ;/* All error conditions set _doserrno and errno */

ExecExit        label   near
                pop     es
                pop     di
                pop     ds
                pop     si
                push    ax
                call    __IOERROR
                mov     sp, bp
                pop     bp
                ret
__exec          endp
