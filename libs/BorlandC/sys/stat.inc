; stat.h
; Definitions used for file status functions

; Traditional names for bits in st_mode.
S_IFMT  equ 0F000h  ; file type mask
S_IFDIR equ 04000h  ; directory
S_IFIFO equ 01000h  ; FIFO special
S_IFCHR equ 02000h  ; character special
S_IFBLK equ 03000h  ; block special
S_IFREG equ 08000h  ; or just 0x0000, regular
S_IREAD equ 00100h  ; owner may read
S_IWRITE equ 00080h ; owner may write
S_IEXEC equ 00040h  ; owner may execute <directory search>
