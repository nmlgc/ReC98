enum enemy_flag_t {
	EF_FREE = 0,
	EF_ALIVE = 1,
	EF_KILLED = 2,
	EF_ALIVE_FIRST_FRAME = 3,

	// Yes, the kill animation doesn't use the perfectly suitable animation
	// system, but is implemented in terms of the [flag].
	EF_KILL_ANIM = 0x80,
	EF_KILL_ANIM_last = (EF_KILL_ANIM + PAT_ENEMY_KILL - 1)
};

#if GAME == 4
struct enemy_t {
	unsigned char flag;
	unsigned char age;
	PlayfieldMotion pos;
	unsigned char patnum_base;
	int8_t unused_1; // ZUN bloat
	int hp;
	int16_t unused_2; // ZUN bloat
	int score;
	unsigned char near *script;
	int script_ip;

	// Certain instructions are executed once per frame, up to a number of
	// frames given in some parameter of the instruction, before [script_ip]
	// is pointed to the next one. This member tracks the current frame of
	// this enemy's currently running blocking multi-frame instruction.
	unsigned char cur_instr_frame;

	// Current loop counter for the LOOP instruction. Resets to 0 once the
	// amount of loops given in the instruction's parameter has been reached,
	// allowing a new loop to run. Since there's only one such counter, LOOP
	// instructions can't be nested.
	unsigned char loop_i;

	Subpixel speed;
	unsigned char angle;

	// Certain instructions add this to [angle] for every frame they are
	// executed.
	unsigned char angle_delta;

	// Clips the enemy once it leaves the playfield. If not clipped along the
	// X or Y axis, the [script] will continue to run if the enemy has left
	// the playfield on that axis, and it will continue to take up a slot in
	// [enemies].
	bool clip_x;
	bool clip_y;

	int8_t unused_3; // ZUN bloat
	item_type_t item;
	bool damaged_this_frame;

	// Animation parameters. Final patnum is
	//	[patnum_base] + (([age] / [anim_frames_per_cel]) % [anim_cels]
	unsigned char anim_cels;
	unsigned char anim_frames_per_cel;
	unsigned char anim_cur_cel; // technically unnecessary

	bool can_be_damaged;
	bool autofire;
	bool kills_player_on_collision;

	// Not updated to reflect the current playfield half the enemy is in!
	bool spawned_in_left_half;

	bullet_template_t bullet_template;

	// If [autofire] is true, the enemy fires bullets, according to its
	// template, every [autofire_interval] number of frames, with
	// [autofire_cur_frame] tracking the current one.
	unsigned char autofire_cur_frame;
	unsigned char autofire_interval;
};
#endif

#define ENEMY_COUNT 32

extern enemy_t enemies[ENEMY_COUNT];
extern enemy_t near *enemy_cur;

#define ENEMY_POS_RANDOM 999.0f

void pascal near enemies_invalidate(void);
void pascal near enemies_render(void);
