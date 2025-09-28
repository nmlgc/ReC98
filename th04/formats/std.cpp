/// Map tile section order + enemy script format
/// --------------------------------------------

#pragma option -zPmain_01

#include "x86real.h"
#include "libs/master.lib/master.hpp"
#include "th04/resident.hpp"
#include "th04/formats/std.hpp"
#include "th04/main/playfld.hpp"
#include "th04/main/scroll.hpp"
#include "th04/main/tile/tile.hpp"

void near std_load(void)
{
	extern char* std_fn;

	uint16_t std_size;
	uint8_t chunk_size;
	uint8_t enemy_scripts_remaining;

	std_free();

	std_fn[3] = resident->stage_ascii;
	file_ropen(std_fn);
	file_read(&std_size, sizeof(std_size));
	file_read(&chunk_size, sizeof(chunk_size));
	std_size--; // Exclude [chunk_size]
	std_seg = reinterpret_cast<uint8_t __seg *>(hmem_allocbyte(std_size));

	_ES = FP_SEG(std_seg);
	uint8_t __es* std_off = 0;
	file_read(std_off, std_size);
	file_close();

	_ES = FP_SEG(std_seg);
	std_map_section_id = ((PLAYFIELD_H / TILE_H) / TILE_ROWS_PER_SECTION);
	tile_row_in_section = 0;

	// Advance to scroll speed section
	std_off += chunk_size;
	chunk_size = *std_off;
	std_scroll_speed = (
		reinterpret_cast<SubpixelLength8 near *>(std_off) +
		(TILES_Y / TILE_ROWS_PER_SECTION)
	);

	// ZUN bloat: Assigning the chunk size??? This indeed makes no semantic
	// sense. The first frame only wants [scroll_speed] to be non-zero, and
	// then it will read the intended speed from [std_scroll_speed]. Assigning
	// a fixed initialization constant like 0xFF would have been clearer.
	scroll_speed = *reinterpret_cast<SubpixelLength8 __es *>(std_off);

	// Advance to enemy script section
	std_off += (chunk_size + 1);  // Include [chunk_size]
	int enemy_script_i = 0;

	// ZUN landmine: Should be limited to STD_ENEMY_SCRIPT_COUNT.
	enemy_scripts_remaining = *(std_off++);

	do {
		chunk_size = *(std_off++);
		std_enemy_scripts[enemy_script_i++] = reinterpret_cast<void near *>(
			std_off
		);
		std_off += chunk_size;
		enemy_scripts_remaining--;
	} while(enemy_scripts_remaining > 0);

	std_off++;
	std_ip = std_off;
	stage_vm = std_run;
}

void near std_free(void)
{
	if(std_seg) {
		hmem_free(std_seg);
		std_seg = nullptr;
	}
}
