// Coordinates referenced by the Music Room
// ----------------------------------------

static const unsigned int PIANO_PART_COUNT = 6;

#define piano_part_top(part_id) (\
	PIANO_TOP + (part_id * PIANO_H_PADDED) \
)

static const screen_y_t PIANO_TOP = 64;
static const pixel_t PIANO_H = 15;
static const pixel_t PIANO_PADDING_BOTTOM = 3;
static const pixel_t PIANO_H_PADDED = (PIANO_H + PIANO_PADDING_BOTTOM);
static const screen_y_t PIANO_BOTTOM = piano_part_top(PIANO_PART_COUNT);
// ----------------------------------------

// Initializes note rendering and draws blank pianos for all monitored PMD
// channels.
void piano_setup_and_put_initial(void);

// Renders the currently played PMD notes.
void piano_render(void);
