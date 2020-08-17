/* ReC98 / TH05
 * ------------
 * Rendering code for all bosses
 */

/// Structures
/// ----------
#define BOSS_PARTICLE_COUNT 64
#define LINESET_LINE_COUNT 20
#define LINESET_COUNT 4

// `boss_` to differentiate this structure from `s2particle_t`, which uses the
// same sprites.
struct boss_particle_t {
	SPPoint pos; // [x] == Subpixel::None() indicates a dead particle

	// [pos] is reset to this value once it has left the playfield, restarting
	// the particle movement.
	SPPoint origin;

	SPPoint velocity;
	int age;
	unsigned char angle;
	unsigned char patnum;	// if 0, calculated from [age] during rendering
};

// Each final rendered line effectively corresponds to the diameter of the
// described circle, with the two line points at +[angle] and -[angle].
struct lineset_t {
	SPPoint center[LINESET_LINE_COUNT];
	Subpixel velocity_y;
	Subpixel radius[LINESET_LINE_COUNT];
	unsigned char angle[LINESET_LINE_COUNT];
};

extern boss_particle_t boss_particles[BOSS_PARTICLE_COUNT];
extern lineset_t linesets[LINESET_COUNT];
/// ----------
