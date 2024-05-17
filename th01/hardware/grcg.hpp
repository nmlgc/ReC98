// Suboptimal and procedural GRCG macros.
// (Still better than master.lib's proper functions though.)

#undef grcg_off

#define grcg_setmode(mode) \
	outportb(0x7C, mode)
#define grcg_off() \
	outportb(0x7C, 0)
