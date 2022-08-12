#include <alloc.h>
#include <stdio.h>
#include "th01/main/debug.hpp"
#include "th01/shiftjis/debug.hpp"

void out_of_memory_exit(void)
{
	puts(ERROR_OUT_OF_MEMORY);
	exit(1);
}

inline void debug_coreleft(void) {
	printf("    coreleft %7lu bytes free\n", coreleft());
}

void pascal debug_mem_node(const char label[], void far* node)
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
			stageobj_bgs_free_wrap(); // For the third time, that's not *all*...
			recurse();
		} else if(input_strike) {
			for(int i = 0; i < BOS_ENTITY_SLOT_COUNT; i++) {
				bos_entity_free(i);
			}
			recurse();
		} else if(input_up) {
			Pellets.unput_and_reset();
			recurse();
		} else if(input_down) {
			recurse();
		} else if(input_ok) {
			z_text_clear_inlined();
			for(int i = 0; i < PTN_SLOT_COUNT; i++) {
				debug_mem_node("PTN ", ptn_images[i]);
			}
			debug_mem_node("MASK", hud_bg);
			debug_mem_node("KABE\0\x1B[3;0H", stageobj_bgs);
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
