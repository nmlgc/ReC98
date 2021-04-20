#include "th02/formats/mpn.hpp"

// Internal .MPN slot structure
struct mpn_t {
	mpn_image_t *images;
	size_t count;
	Palette8 palette;
	int8_t unused[10];
};

// TH04 reserves memory for 8 slots, but only actually uses the first one.
static const int MPN_COUNT = 8;

extern mpn_t mpn_slots[MPN_COUNT];

// Frees the .MPN images in the given [slot].
void pascal mpn_free(int slot);

// Sets the hardware color palette to the one in the given .MPN [slot].
void pascal mpn_palette_show(int slot);
