#include "th03/formats/scorecry.hpp"

void pascal near scoredat_encode_and_save(rank_t rank)
{
	uint8_t near *p;
	int i;
	uint8_t feedback;
	uint16_t sum = 0;

	hi.score.key1 = irand();
	hi.score.key2 = irand();
	hi.score.unknown = irand();

	// ZUN bloat: These conditions are only true within MAINL.EXE anyway. No
	// need to fork the code into binary-specific versions.
	//
	// ZUN landmine: This function is not just called after entering your name
	// in the High Score menu, but also when potentially recreating YUME.NEM
	// while trying to load that file at the start of the menu. If this happens
	// for a 1CC where these conditions are true, this branch sets the clear
	// flag for *every* difficulty, not just the one you've actually cleared.
	//
	// This is a landmine because YUME.NEM would only ever be recreated in "1CC
	// mode" if the file was deleted or tampered with outside of our control
	// while the game is running. To get a 1CC in the first place, you must
	// have gone through character selection, which also (re-)creates YUME.NEM
	// if necessary.
	// TH03 also offers no benefits for a 1CC on specific difficulties, or even
	// just a visual indication like TH04 and TH05 do. 1CC'ing *any* difficulty
	// is all that matters for unlocking Chiyuri and Yumemi. So we might as
	// well restrict the clear flag to the correct difficulty with an added
	// `resident->rank == rank` condition to avoid confusing anyone.
#if (BINARY == 'L')
	if((resident->story_stage == STAGE_ALL) && (resident->rem_credits == 3)) {
		hi.score.cleared = SCOREDAT_CLEARED;
	}
#endif

	scoredat_sum(sum, p, i);
	hi.sum = sum;

	// Encraption
	p = reinterpret_cast<uint8_t near *>(&hi.score.key1);
	p--;
	feedback = hi.score.key2;
	i = (sizeof(hi.score) - 1);
	while(i >= 0) {
		scoredat_encode_byte_at(p, feedback, hi.score.key1, hi.score.key2);
		i--;
		p--;
	}

	// Save
	file_append(SCOREDAT_FN_PTR);
	file_seek((rank * sizeof(scoredat_section_t)), SEEK_SET);
	file_write(&hi, sizeof(scoredat_section_t));
	file_close();
}
