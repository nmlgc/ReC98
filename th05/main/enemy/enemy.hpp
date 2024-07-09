#include "th04/main/bullet/bullet.hpp"
#include "th04/main/item/item.hpp"

#define ENEMY_CLIP_NONE 0x00
#define ENEMY_CLIP_X 0x01
#define ENEMY_CLIP_Y 0x10

// See TH04's version for documentation on the fields that originated in that
// game.
struct enemy_t {
	unsigned char flag;
	unsigned char age;
	PlayfieldMotion pos;
	int hp;
	int score;
	unsigned char near *script;
	int script_ip;
	SubpixelLength8 speed;
	unsigned char patnum_base;
	unsigned char cur_instr_frame;
	unsigned char loop_i;
	unsigned char angle;
	unsigned char angle_delta;
	unsigned char anim_cels;
	unsigned char anim_frames_per_cel;
	unsigned char anim_cur_cel; // still technically unnecessary

	char clip;

	item_type_t item;
	bool damaged_this_frame;
	bool can_be_damaged;
	bool autofire;
	bool kills_player_on_collision;
	bool spawned_in_left_half;
	unsigned char autofire_cur_frame;
	unsigned char autofire_interval;
	BulletTemplate bullet_template;

	// Custom type ID, set in the spawn parameters. Can be used to parametrize
	// scripts via conditional jumps based on this value.
	unsigned char subtype;

	int8_t unused_1; // ZUN bloat
	int16_t unused_2; // ZUN bloat
	int8_t unused_3; // ZUN bloat
	int8_t padding[5]; // ZUN bloat
};

#include "th04/main/enemy/enemy.hpp"
