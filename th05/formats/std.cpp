/// Map tile section order + enemy script format
/// --------------------------------------------
/// TH05 adds stage and BGM titles to the format, and assumes that the tile
/// section IDs come pre-multiplied by the element size of the section offset
/// lookup array – see tiles_fill_initial() for details. The rest of the format
/// is identical to TH04.

#pragma option -zPmain_01

#include "th04/formats/std.hpp"
#include "th04/main/hud/overlay.hpp"
#include "th04/main/stage/stage.hpp"
#include "th04/main/tile/tile.hpp"
#include "th04/main/playfld.hpp"
#include "libs/master.lib/master.hpp"
#include "platform/x86real/flags.hpp"
#include "x86real.h"

void near std_load(void)
{
	extern char std_fn[];

	// Storing the file size in the data segment (and thus, the same segment as
	// [std_fn]) is very convenient, as we don't have to overwrite DS for the
	// INT 21h, AH=3Fh call...
	extern uint16_t std_size_in_data_segment;

	// ZUN bloat: …except that we still need to copy the value onto the stack
	// to access it while DS is pointing to [std_seg].
	uint16_t std_size;

	#define enemy_scripts_remaining _DL
	#define enemy_script_p reinterpret_cast<void near * near*>(_BX)

	_asm { push ds; }
	std_free();

	std_fn[3] = ('0' + stage_id);

	// DOS file open
	_DX = FP_OFF(std_fn);
	_AX = 0x3D00;
	geninterrupt(0x21);
	_BX = _AX;
	// ZUN landmine: No error handling

	// DOS file read (into DS:DX)
	_DX = FP_OFF(&std_size_in_data_segment);
	_AH = 0x3F;
	_CX = sizeof(std_size_in_data_segment);
	geninterrupt(0x21);

	// hmem_allocbyte() already preserves BX, but it's nice to have that intent
	// separately spelled out.
	_asm { push bx; }
	{
		std_size = std_size_in_data_segment;
		_ES = _DS = reinterpret_cast<uint16_t>(std_seg) = (
			reinterpret_cast<uint16_t>(hmem_allocbyte(std_size))
		);
		_DI = 0;
	}
	_asm { pop bx; }

	// DOS file read (into DS:DX)
	_DX = _DI;
	_AH = 0x3F;
	_CX = std_size;
	geninterrupt(0x21);

	// DOS file close
	_AH = 0x3E;
	geninterrupt(0x21);
	_asm { pop ds; }

	stage_title = reinterpret_cast<shiftjis_t far *>(MK_FP(_ES, _DI));

	// ZUN landmine: Should clear the direction flag to ensure that this
	// strlen() operation actually scans this string and not everything before.
	_AX = 0;
	_CX = 0xFFFF;
	asm { repne scasb; } // ES:DI = one byte past terminating '\0'
	stage_bgm_title = reinterpret_cast<shiftjis_t far *>(MK_FP(_ES, _DI));
	asm { repne scasb; }
	boss_bgm_title = reinterpret_cast<shiftjis_t far *>(MK_FP(_ES, _DI));
	asm { repne scasb; }

	asm { lea ax, [di + 1 + ((PLAYFIELD_H / TILE_H) / TILE_ROWS_PER_SECTION)]; }
	std_map_section_p = _AX;
	tile_row_in_section = 0;

	// Advance to scroll speed section
	// -------------------------------

	// ZUN bloat: `MOVZX AX, BYTE PTR ES:[DI]`. A regular pointer read compiles
	// into `MOV AL, ES:[DI]; MOV AH, 0`, which is 1 byte longer, but 1 cycle
	// faster on a 486. Doesn't really justify reaching to instructions
	// unsupported by Turbo C++ 4.0J, does it?
	__emit__(0x26, 0x0F, 0xB6, 0x05);

	_DI += (1 + _AX); // Map section count + the count byte itself
	asm { lea ax, [di + 1 + ((PLAYFIELD_H / TILE_H) / TILE_ROWS_PER_SECTION)]; }
	std_scroll_speed = reinterpret_cast<SubpixelLength8 near *>(_AX);
	__emit__(0x26, 0x0F, 0xB6, 0x05); // MOVZX AX, BYTE PTR ES:[DI]
	// -------------------------------

	// ZUN bloat: Assigning the chunk size??? This indeed makes no semantic
	// sense. The first frame only wants [scroll_speed] to be non-zero, and
	// then it will read the intended speed from [std_scroll_speed]. Assigning
	// a fixed initialization constant like 0xFF would have been clearer.
	scroll_speed.v = _AL;

	// Advance to enemy script section
	_DI += (_AX + 1);
	enemy_scripts_remaining = *reinterpret_cast<uint8_t far *>(MK_FP(_ES, _DI));
	_DI++;

	enemy_script_p = &std_enemy_scripts[0];
	do {
		__emit__(0x26, 0x0F, 0xB6, 0x05); // MOVZX AX, BYTE PTR ES:[DI]
		_DI++;
		*enemy_script_p++ = reinterpret_cast<void near *>(_DI);
		_DI += _AX;
		enemy_scripts_remaining--;
	} while(!FLAGS_ZERO);

	_DI++;
	std_ip = MK_FP(_ES, _DI);
	stage_vm = std_run;

	#undef enemy_script_p
	#undef enemy_scripts_remaining
}

void near std_free(void)
{
	if(std_seg) {
		hmem_free(std_seg);
		std_seg = nullptr;
	}
}
