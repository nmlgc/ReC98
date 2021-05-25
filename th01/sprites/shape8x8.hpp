typedef enum {
	SHAPE8X8_DIAMOND,
	SHAPE8X8_STAR,
	SHAPE8X8_FLAKE,
	SHAPE8X8_COUNT
} shape8x8_t;

// For consistency in usage code...
static const pixel_t DIAMOND_W = 8;
static const pixel_t DIAMOND_H = 8;

extern const dot_rect_t(8, 8) sSHAPE8X8[SHAPE8X8_COUNT];
