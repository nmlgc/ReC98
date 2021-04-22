typedef struct {
	char magic[4]; // = "MPTN"
	char count;
	char unused;
} mpn_header_t;

#define MPN_SIZE (8 * 16)

extern unsigned char mpn_count;
extern int *mpn_buffer;
extern Palette8 mpn_palette;

// Reads the .MPN file with the given [fn] into the newly reallocated
// [mpn_buffer], and sets [mpn_count] and [mpn_palette] accordingly.
int pascal mpn_load(const char *fn);

// Like mpn_load(), but sets the hardware palette to the one in [fn]'s header.
int pascal mpn_load_palette_show(const char *fn);

void mpn_free(void);
