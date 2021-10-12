/// Durations
/// ---------

#define SWING_FRAMES_PER_CEL 3
#define SWING_FRAMES 23
#define SHOTCOMBO_FRAMES_PER_CEL 6
/// ---------

/// .BOS sprite IDs
/// ---------------

#define SWING_CELS 8
#define FLIPKICK_CELS 6
#define SHOTCOMBO_CELS 4
static const int SLIDE_CELS = 2;

// miko_ac.bos
enum player_48x48_cel_t {
	C_SWING = 0,
	C_SWING_last = (C_SWING + SWING_CELS - 1),

	C_L_FLIPKICK,
	C_L_FLIPKICK_last = (C_L_FLIPKICK + FLIPKICK_CELS - 1),
	C_R_FLIPKICK,
	C_R_FLIPKICK_last = (C_R_FLIPKICK + FLIPKICK_CELS - 1),

	C_L_SHOTCOMBO,
	C_L_SHOTCOMBO_last = (C_L_SHOTCOMBO + SHOTCOMBO_CELS - 1),
	C_R_SHOTCOMBO,
	C_R_SHOTCOMBO_last = (C_R_SHOTCOMBO + SHOTCOMBO_CELS - 1),

	_player_48x48_cel_t_FORCE_INT16 = 0x7FFF
};

// miko_ac2.bos
enum player_48x32_cel_t {
	C_L_SLIDE,
	C_L_SLIDE_last = (C_L_SLIDE + SLIDE_CELS - 1),
	C_R_SLIDE,
	C_R_SLIDE_last = (C_R_SLIDE + SLIDE_CELS - 1),
	C_L_SLIDEKICK,
	C_R_SLIDEKICK,

	_player_48x32_cel_t_FORCE_INT16 = 0x7FFF
};
/// ---------------
