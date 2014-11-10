HUGE_VAL = _huge_dble
_LHUGE_VAL = _huge_ldble

ifdef UsingINF

_huge_flt	dw 0, 07F80h
_huge_dble	dw 0, 0, 0, 07FF0h
_huge_ldble	dw 0, 0, 0, 08000h, 07FFFh

else

_huge_flt	dw -1, 07F7Fh
_huge_dble	dw -1, -1, -1, 07FEFh
_huge_ldble	dw -1, -1, -1, -1, 07FFEh

endif

_indefinite	dw 0, 07FC0h
_tiny_ldble	dw 0, 0, 0, 08000h, 1
