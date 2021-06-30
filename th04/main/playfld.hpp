#include "th02/main/playfld.hpp"

#if defined(SUBPIXEL_HPP) && defined(MOTION_HPP)
	struct PlayfieldMotion : public MotionBase<PlayfieldPoint> {
		// Moves by one step, and returns the new current position.
		// The _seg1() and _seg3() variants are provided for near calls within
		// code segment #1 (rendering) and code segment #3 (update),
		// respectively.
		// Note that some calls to these functions directly access the returned
		// value through the AX (X) and DX (Y) registers.
		PlayfieldPoint pascal near update_seg1();
		PlayfieldPoint pascal near update_seg3();
	};
#endif

// Fills the playfield area on the text RAM with transparent spaces.
void near playfield_tram_wipe(void);
// Fills the playfield area on the text RAM with black, effectively hiding the
// playfield in the process.
void near playfield_tram_black(void);

#define playfield_bg_put(left, top, cdg_slot) \
	cdg_put_noalpha_8((PLAYFIELD_LEFT + left), (PLAYFIELD_TOP + top), cdg_slot)
