#include "th03/common.h"

// Position flags
// --------------

typedef uint8_t enemy_pos_type_t;

// Clips the enemy at the left and right edges of the playfield.
static const enemy_pos_type_t EPT_CLIP_X = 0x01;

// Clips the enemy at the bottom edge of the playfield.
static const enemy_pos_type_t EPT_CLIP_BOTTOM = 0x02;

// If set, horizontal spawn positions and movement velocities are applied as
// given in the script. If not set, they are horizontally mirrored. (Yes, this
// would have been easier to describe if it were the other way round.)
static const enemy_pos_type_t EPT_DO_NOT_MIRROR_X = 0x80;
// --------------

// Constants
// ---------

// TH03 generates a sequence of 256 random formations and formation directions
// for each round.
static const int FORMATION_RING_SIZE = 256;
// ---------

// State
// -----

extern uint8_t __seg *formation_type_ring;
extern enemy_pos_type_t __seg *formation_pos_type_ring;
extern uint8_t formation_p[PLAYER_COUNT];
extern uint8_t formation_count;
// -----
