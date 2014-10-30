; character classes
_IS_SP       equ   1   ; space
_IS_DIG      equ   2   ; digit
_IS_UPP      equ   4   ; upper case
_IS_LOW      equ   8   ; lower case
_IS_HEX      equ  16   ; [0..9] or [A-F] or [a-f]
_IS_CTL      equ  32   ; control
_IS_PUN      equ  64   ; punctuation
_IS_BLK      equ 128   ; blank

_IS_ALPHA    equ (_IS_UPP | _IS_LOW)
_IS_ALNUM    equ (_IS_DIG | _IS_ALPHA)
_IS_GRAPH    equ (_IS_ALNUM | _IS_HEX | _IS_PUN)
