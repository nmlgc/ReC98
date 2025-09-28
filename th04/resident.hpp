#ifndef TH04_RESIDENT_HPP
#define TH04_RESIDENT_HPP

#include "th04/score.h"

#define RES_ID "HUMAConfig"
struct resident_t {
	char id[sizeof(RES_ID)];
	unsigned char rem_lives;
	unsigned char credit_lives;
	unsigned char rem_bombs;
	unsigned char credit_bombs;
	unsigned char rank;
	unsigned char bgm_mode;

	// (indicating regular game play progression)
	unsigned char stage;

	unsigned char playchar_ascii;

	// (used for loading data files, directly inserted into file name
	// templates)
	char stage_ascii;

	long rand;
	unsigned char se_mode;
	char shottype;
	bool debug;
	const char near *pmd_fn; // relative to the data segment of `DEBLOAT.EXE`
	score_lebcd_t score_last;

	// (directly inserted into the ending .TXT file name template)
	char end_type_ascii;

	unsigned int std_frames;	// (excluding bosses, see th04/frames.h)
	unsigned int items_spawned;
	unsigned int items_collected;
	unsigned int point_items_collected;
	unsigned int max_valued_point_items_collected;
	unsigned char end_sequence;
	unsigned char miss_count;
	unsigned char bombs_used;
	uint8_t shutdown_flags;

	// *Not* spawned. # of enemies that either left the screen or were killed.
	unsigned int enemies_gone;

	unsigned int enemies_killed;
	unsigned int graze;
	unsigned char cfg_lives;
	unsigned char cfg_bombs;
	unsigned char demo_stage;
	int8_t unused_3; // ZUN bloat
	unsigned char demo_num;
	int8_t unused_4; // ZUN bloat
	unsigned long slow_frames;
	unsigned long frames;	// (including bosses, see th04/frames.h)
	bool zunsoft_shown;
	bool turbo_mode;
	int8_t unused_5[182]; // ZUN bloat
};

extern resident_t far *resident;

#endif /* TH04_RESIDENT_HPP */
