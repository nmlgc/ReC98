_STACK		segment	para stack 'STACK' use16
		db 20h dup(?)
include libs/BorlandC/math/emuvars[stack].asm
		db 1Bh dup(?)
_STACK		ends
