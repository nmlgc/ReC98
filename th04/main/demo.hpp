// Properly declared, DEMO?.REC uses this structure:
template <size_t Frames> struct REC {
	input_replay_t input[Frames];
	bool shift[Frames];
};

// The above declaration would also work with the overly long TH05 Extra Stage
// Clear replay. However, ZUN not only uses the same pointer for both that
// replay and regular ones, he also only accesses the [shift] flag via adding
// either DEMO_N or DEMO_N_EXTRA to the stage frame index. TH05 calculates that
// additional offset at the beginning of the function… so yeah, declaring this
// as anything more semantic than a meaningless buffer of bytes would just add
// a lot of unneeded complexity to the one function that reads from this
// buffer.
extern uint8_t *DemoBuf; /* ZUN symbol [MAGNet2010] */

#define demo_end() { \
	HMem<uint8_t>::free(DemoBuf); \
	palette_black_out((GAME == 5) ? 8 : 10); \
	/* TODO: Replace with the decompiled call \
	 * 	GameExecl(BINARY_OP); \
	 * once that function is only called from the same segment */ \
	_asm { \
		push	ds; \
		push	offset BINARY_OP; \
		nop; \
		push 	cs; \
		call	near ptr GameExecl; \
	} \
}

// Assigns the next frame out of [DemoBuf] to [key_det] and [shiftkey].
void near DemoPlay();
