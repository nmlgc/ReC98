; Additional data after the last translation unit in C land.

	.386
	.model use16 large

	.data

include th01/hardware/vsync[data].asm
include th01/hardware/ztext[data].asm
include th01/core/initexit[data].asm

	end
