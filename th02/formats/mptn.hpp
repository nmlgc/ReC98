typedef struct {
	char magic[4]; // = "MPTN"
	char count;
	char unused;
} mptn_header_t;

#define MPTN_SIZE (8 * 16)

extern unsigned char mptn_count;
extern int *mptn_buffer;
extern Palette8 mptn_palette;

// Reads the MPTN file with the given [fn] into the newly reallocated
// [mptn_buffer], and sets [mptn_count] and [mptn_palette] accordingly.
int pascal mptn_load(const char *fn);

// Like mptn_load(), but sets the hardware palette to the one in [fn]'s
// header.
int pascal mptn_load_palette_show(const char *fn);

void mptn_free(void);
