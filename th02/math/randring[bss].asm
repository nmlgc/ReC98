; Ring buffer of random numbers.

RANDRING_SIZE = 256

; TH05 wants it publicly...
public _randring
public _randring_p

_randring db RANDRING_SIZE dup (?)
if GAME ge 4
	_randring_p dw ?
else
	_randring_p db ?
	db ?
endif
