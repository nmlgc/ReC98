O_RDONLY    equ 1
O_WRONLY    equ 2
O_RDWR      equ 4

; Flag values for open only
O_CREAT     equ 00100h ; create and open file
O_TRUNC     equ 00200h ; open with truncation
O_EXCL      equ 00400h ; exclusive open

; The "open flags" defined above are not needed after open, hence they
; are re-used for other purposes when the file is running.  Sorry, it's
; getting crowded !
_O_RUNFLAGS equ 00700h
_O_WRITABLE equ 00100h ; file is not read-only
_O_EOF      equ 00200h ; set when text file hits ^Z

; a file in append mode may be written to only at its end.
O_APPEND    equ 00800h  ; to end of file

; MSDOS special bits
O_CHANGED   equ 01000h  ; user may read these bits, but
O_DEVICE    equ 02000h  ;   only RTL\io functions may touch.
O_TEXT      equ 04000h  ; CR-LF translation
O_BINARY    equ 08000h  ; no translation

; DOS 3.x options
O_NOINHERIT equ 080h
O_DENYALL   equ 010h
O_DENYWRITE equ 020h
O_DENYREAD  equ 030h
O_DENYNONE  equ 040h
