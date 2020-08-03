typedef enum {
	SHAPE8X8_DIAMOND,
	SHAPE8X8_STAR,
	SHAPE8X8_FLAKE,
	SHAPE8X8_COUNT
} shape8x8_t;

typedef struct {
	dots8_t rows[8];
} dots8x8_t;

extern const dots8x8_t sSHAPE8X8[SHAPE8X8_COUNT];
