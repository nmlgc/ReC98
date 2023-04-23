#include <alloc.h>
#include <conio.h>
#include <stdio.h>
#include "th01/main/debug.hpp"
#include "th01/shiftjis/debug.hpp"

// State
// -----

bool mode_debug;
bool16 mode_test = false;
bool16 test_damage = false;
unsigned long frames_since_start_of_binary;
uint32_t coreleft_prev;
// -----

void out_of_memory_exit(void)
{
	puts(ERROR_OUT_OF_MEMORY);
	exit(1);
}

inline void debug_coreleft(void) {
	printf("    coreleft %7lu bytes free\n", coreleft());
}

void debug_mem_node(const char label[], void far* node)
{
	printf("%s", label);
	printf(" : [%Fp] -> ", node);
	switch(heapchecknode(node)) {
	case _HEAPEMPTY:  	puts(MEM_NODE_HEAPEMPTY); break;
	case _HEAPCORRUPT:	puts(MEM_NODE_CORRUPT); break;
	case _BADNODE:    	puts(MEM_NODE_BADNODE); break;
	case _FREEENTRY:  	puts(MEM_NODE_FREEENTRY); break;
	case _USEDENTRY:  	puts(MEM_NODE_USEDENTRY); break;
	}
}

void debug_mem(void)
{
	uint32_t ptn_size_boss = 0;

print_stats:
	#define recurse() { \
		z_text_clear_inlined(); /* ZUN bloat */ \
		goto print_stats; \
	}

	ptn_size_boss = 0;
	if(mode_test == true) {
		z_graph_hide();
		z_text_clear_inlined();
		puts(MEM_TITLE "\n");
		printf("old coreleft %7lu bytes free\n", coreleft_prev);
		debug_coreleft();
		printf("    kabe_n = %d\n", obstacles.count);
		printf("    pnl_n  = %d\n", cards.count);

		// Refers to the card part of [stageobj_bgs].
		printf(" pnl_n buf = %7lu\n", ptn_sizeof_array(cards.count));

		for(int i = 0; i < PTN_SLOT_COUNT; i++) {
			printf(MEM_PTN_PREFIX "ptn %d  = %7lu\n",
				i, ptn_sizeof_array(ptn_image_count[i])
			);
			if((i >= PTN_SLOT_BOSS_1) && (i != PTN_SLOT_BG_HUD)) {
				ptn_size_boss += ptn_sizeof_array(ptn_image_count[i]);
			}
		}
		puts("\n");

		// Not really "all"...
		printf("all   ptn   = %7lu\n", ptn_size_boss);

		// Wouldn't it make more sense to just show the obstacle part here?
		printf("kabe  mem   = %7lu\n", stageobj_bgs_size);

		printf("mask  mem   = %7u\n", hud_bg_size);

		// Again, this implies that we're subtracting *all* .PTNs...
		printf("old - ptn   = %7lu\n", (coreleft_prev - ptn_size_boss));

		printf("etc   mem   = %7ld\n\n",
			(coreleft_prev - coreleft() - stageobj_bgs_size)
		);

		puts("Z = PTN FREE, X = BOSS FREE, UP = TAMA DEL, DOWN = REWIRTE, ret = NODE CHEAK");
	}

	while(!input_mem_leave) {
		frame_delay(3);
		input_sense(false);
		if(input_shot) {
			stageobj_bgs_free(); // For the third time, that's not *all*...
			recurse();
		} else if(input_strike) {
			for(int i = 0; i < BOS_ENTITY_SLOT_COUNT; i++) {
				bos_entity_free(i);
			}
			recurse();
		} else if(input_up) {
			Pellets.unput_and_reset_nonclouds();
			recurse();
		} else if(input_down) {
			recurse();
		} else if(input_ok) {
			z_text_clear_inlined();
			for(int i = 0; i < PTN_SLOT_COUNT; i++) {
				debug_mem_node("PTN ", ptn_images[i]);
			}
			debug_mem_node("MASK", hud_bg);
			debug_mem_node("KABE", stageobj_bgs);
		}
	}
}

void debug_show_game(void)
{
	if(mode_test == true) {
		z_graph_show();
		z_text_clear_inlined();
	}
}

void debug_vars(void)
{
	static long memory_check_cycle;
	static screen_x_t player_left_prev;

	memory_check_cycle++;
	if((memory_check_cycle % 1000) == 100) {
		text_cursor_move_1_based(0, 3);
		debug_coreleft();
	}

	text_cursor_move_1_based(60, 3);
	printf("HEAP Cheak  ");
	switch(heapcheck()) {
	case _HEAPEMPTY:
		printf("EMPTY   ");
		break;
	case _HEAPOK:
		printf("OK      ");
		break;
	case _HEAPCORRUPT:
		printf("CORRUPT ");
		mdrv2_se_play(5); // Remember that this function runs every frame!
		while(!input_ok) {
			input_sense(0);
		}
		break;
	}

	text_cursor_move_1_based(0, 2);
	if(player_left_prev != player_left) {
		printf("gx = %3d", player_left);
		player_left_prev = player_left;
	}

	text_cursor_move_1_based(0, 4);
	printf(
		" kbhit:%d,dir:%d, sp:%d, sh:%d, exit:%d, end:%d\n",
		kbhit(), input_lr, input_shot, input_strike, paused, player_is_hit
	);

	text_cursor_move_1_based(0, 5); // ZUN bloat: Already done via \n

	printf(
		" main:%7lu, rand:%7lu, bomb:%6d, timer:%7lu\n",
		bomb_frames,
		frame_rand,
		bomb_doubletap_frames,
		frames_since_start_of_binary
	);
}
