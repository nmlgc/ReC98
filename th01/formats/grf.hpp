/// Run-length encoded, 16-color, image format using hardcoded sizes
/// ----------------------------------------------------------------
/// TH01 has no generic implementation of this format, only the specialized
/// one for the HUD, loading and blitting MASK.GRF. Which only reads the first
/// bitplane from that file – the other ones are exactly identical, though.
/// However, the 4 size fields, as well as the palette, indicate that .GRF was
/// in fact originally designed as a 16-color format.
///
/// In contrast to .GRX, .GRF uses a separate RLE command + pixel data stream
/// for each bitplane, with a customizable [rle_run_byte].

#define GRF_MAGIC "HGRF"

#pragma push(pack, 1)
typedef struct {
	char magic[sizeof(GRF_MAGIC) - 1];
	int8_t unknown1; // Image count?
	uint8_t rle_run_byte;
	int16_t unknown2;
	Planar<uint16_t> rle_size;
	Palette4 pal;
} grf_header_t;
#pragma pop
/// ----------------------------------------------------------------
