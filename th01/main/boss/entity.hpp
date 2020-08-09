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

	// Copies the .BOS header data of this instance to the given variables. In
	// practice, only used to copy these values from one CBossEntity to
	// another.
	void bos_metadata_get(
		int &image_count, unsigned char &slot, int &vram_w, int &h
	) const;

	/// Blitting
	/// --------
	// All of functions with an [image] parameter use that image from
	// [bos_slot], *not* the [bos_image] of this instance.
	// All of these also make an attempt at clipping the sprite at the left
	// and right edges of VRAM. This only really works if [left] is a multiple
	// of 16 and inside the [-RES_X, RES_X[ range, though, and is pretty much
	// broken otherwise.

	// Blits [image] to (⌊left/8⌋*8, top).
	// Additionally clips at the bottom edge of VRAM.
	void put_8(int left, int top, int image) const;

	// Precisely restores pixels according to the alpha mask of [image] from
	// VRAM page 1, starting at (⌊left/8⌋*8, top).
	// Additionally clips at the top and bottom edges of VRAM.
	void unput_8(int left, int top, int image) const;

	// Like put_8(), but restores all pixels in the blitted sprite
	// rectangle from VRAM page 1 prior to blitting.
	// Additionally clips at the top and bottom edges of VRAM.
	void unput_and_put_8(int left, int top, int image) const;

	// Blits line #[row] of [image] to (left, top).
	// Additionally clips at the bottom edge of VRAM.
	void put_1line(int left, int y, int image, int row) const;

	// Like put_1line(), but restores all pixels along the line from VRAM page
	// 1 prior to blitting the line.
	void unput_and_put_1line(int left, int y, int image, int row) const;

	// Blits [image] with a wave function applied to the starting X coordinate
	// for each row, based at the given (left, top) point. Used for Elis'
	// entrance animation.
	// Calls put_1line() for each row, and clips the sprite accordingly.
	void wave_put(
		int left, int top, int image, int len, int amp, int phase
	) const;

	// Like wave_put(), but calls unput_and_put_1line() for each line instead.
	// For a sloppy, EGC-accelerated unblitter function, see egc_wave_unput().
	void wave_unput_and_put(
		int left, int top, int image, int len, int amp, int phase
	) const;

	// Tries to unblit the two sprites at (left_1, top) and (left_2, top) that
	// were previously blitted with the given wave function using the EGC, but
	// fails.
	void egc_sloppy_wave_unput_double_broken(
		int left_1, int top, int unused,
		int len_1, int amp_1, int phase_1,
		int left_2,
		int len_2, int amp_2, int phase_2
	) const;

	// Blits the 16×8 pixels of [bos_image] in [bos_slot] starting at
	// (bos_left, bos_top), relative to the top-left corner of the sprite, to
	//	((⌊cur_left/8⌋ + bos_left/8⌋) * 8, (cur_top + bos_top))
	// after precisely restoring pixels according to the alpha mask of the
	// pixels to be blitted from VRAM page 1.
	// Additionally clips at the top and bottom edges of VRAM.
	void unput_and_put_16x8_8(int bos_left, int bos_top) const;

	// Restores the pixels inside the entire ([vram_w]*8)×[h] rectangle
	// starting at (cur_left, cur_top) from VRAM page 1.
	void sloppy_unput(void) const;
	/// --------

	/// Movement
	/// --------
protected:
	void move(const int &delta_x, const int &delta_y) {
		prev_delta_x = delta_x;
		prev_delta_y = delta_y;
		prev_left = cur_left;
		prev_top = cur_top;

		cur_left += prev_delta_x;
		if(move_clamp.left > cur_left) {
			cur_left = move_clamp.left;
		}
		if(move_clamp.right < cur_left) {
			cur_left = move_clamp.right;
		}

		cur_top += prev_delta_y;
		if(cur_top < move_clamp.top) {
			cur_top = move_clamp.top;
		}
		if(cur_top > move_clamp.bottom) {
			cur_top = move_clamp.bottom;
		}
	}

public:
	// Sets [cur_left], [cur_top], [unknown], and the [move_clamp] area.
	void pos_set(
		int left,
		int top,
		int unknown,
		int move_clamp_left,
		int move_clamp_right,
		int move_clamp_top,
		int move_clamp_bottom
	);

	// (Just read the actual function code, it's impossible to summarize
	// without spelling every single line here.)
	void move_lock_unput_and_put_8(
		int unused, int delta_x, int delta_y, int lock_frames
	);
	/// --------
};
