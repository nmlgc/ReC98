// Stage background tile section definitions
// -----------------------------------------
// TH02 starts with a very simple fixed-size format, describing 16 unique
// sections of 8 tile rows each. The .DT1 format arranges these sections into
// the complete [map] of a stage.

// Column-major index of a tile within the tile source area.
typedef unsigned char tile_image_id_t;

// Not checked by the game.
#define MAP_MAGIC "MIKO_MAP  "
static const unsigned int MAP_MAGIC_SIZE = (sizeof(MAP_MAGIC) - 1);

static const unsigned int MAP_ROWS_PER_SECTION = 8;
static const unsigned int MAP_BITS_PER_SECTION = 3;
static const unsigned int MAP_SECTION_COUNT = 16;
static const unsigned int MAP_LENGTH_MAX = 320;

typedef uint8_t map_section_id_t;

struct map_section_tiles_t {
	tile_image_id_t row[MAP_ROWS_PER_SECTION][TILES_X];
};

// On-disk .MAP format
struct map_t {
	char magic[MAP_MAGIC_SIZE];
	map_section_tiles_t sections[MAP_SECTION_COUNT];
};

// All unique sections of tiles used in the [map].
extern map_section_tiles_t map_section_tiles[MAP_SECTION_COUNT];

// Defines the complete map of a stage by stringing together the various
// [map_sections], from the bottom/start to the top/end.
extern map_section_id_t map[MAP_LENGTH_MAX];

// *Not* at the top of the playfield. Very important distinction.
extern unsigned int map_full_row_at_top_of_screen;

// In tile sections.
extern int map_length;

// Loads the [map_sections] from the given file.
void pascal map_load(const char* fn);
