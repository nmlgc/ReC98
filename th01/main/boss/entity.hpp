struct area_t {
	int left, right, top, bottom;
};

// An individual entity rendered with sprites from a .BOS file. May or may not
// be animated, and may or may not have a hitbox for collision with the Orb.
class CBossEntity {
public:
	int cur_left;
	int cur_top;
	int prev_left;
	int prev_top;
	int vram_w;
	int h;
	area_t move_clamp;	// Relative to VRAM
	area_t hitbox_orb;	// Relative to [cur_left] and [cur_top]

	// Never actually read outside of the functions that set them...
	int prev_delta_y;
	int prev_delta_x;

	int bos_image_count;
	int zero_1;
	int bos_image;
	int unknown;
	bool16 hitbox_orb_inactive;
	bool16 loading;
	int move_lock_frame;
	int zero_2;
	char zero_3;
	unsigned char bos_slot;

	// Loads all images from the .BOS file with the given [fn] inside the
	// currently active packfile into the given .BOS [slot], and keeps the
	// .BOS metadata in this class. Always returns 0.
	int bos_load(const char fn[PF_FN_LEN], int slot);
};
