#define SCOREDAT_MAGIC "HISCORE"
#define SCOREDAT_PLACES 10
#define SCOREDAT_NAME_KANJI 8
// Actually creates slightly different assembly compared to sizeof() on a
// int8_t array!
#define SCOREDAT_NAME_BYTES (SCOREDAT_NAME_KANJI * 2)
#define SCOREDAT_NAMES_SIZE (SCOREDAT_PLACES * SCOREDAT_NAME_BYTES)
#define SCOREDAT_ROUTE_LEN 2

#define SCOREDAT_CLEARED 40
#define SCOREDAT_CLEARED_MAKAI (SCOREDAT_CLEARED + 10)
#define SCOREDAT_CLEARED_JIGOKU (SCOREDAT_CLEARED + 20)

#define SCOREDAT_NAME_KEY 0x9C

// Encodes or decodes a single name byte.
int8_t scoredat_name_byte_encode(int8_t byte);
int8_t scoredat_name_byte_decode(int8_t byte);

// On-disk structure of the REYHI*.DAT files.
// For reference, never actually used by the game itself
struct scoredat_t {
	// Not null-terminated!
	char magic[sizeof(SCOREDAT_MAGIC) - 1];

	// Exclusively used to store full-width Shift-JIS code points.
	// Not null-terminated.
	int16_t name[SCOREDAT_PLACES][SCOREDAT_NAME_KANJI];

	uint32_t points[SCOREDAT_PLACES];
	int16_t stage[SCOREDAT_PLACES];
	twobyte_t route[SCOREDAT_PLACES];
};

extern int8_t* scoredat_names; // Yeah, technically a scoredat_name_t.
extern int16_t* scoredat_stages;
extern int32_t* scoredat_points;
extern int8_t* scoredat_routes; // Yeah, technically a twobyte_t.

// Byte-wise access to [scoredat_routes].
inline int8_t& scoredat_route_byte(int place, int byte)
{
	if(byte == 0) {
		return scoredat_routes[place * SCOREDAT_ROUTE_LEN];
	}
	return scoredat_routes[(place * SCOREDAT_ROUTE_LEN) + byte];
}

// Null-terminated version of scoredat_name_t, used internally.
typedef StupidBytewiseWrapperAround<struct {
	int16_t codepoint[SCOREDAT_NAME_KANJI + 1];
}> scoredat_name_z_t;

// Loads the score file for the current [rank], recreating it if necessary.
// Returns 0 on success, 1 on failure.
int scoredat_load();

// Returns the high score for the difficulty previously loaded by
// scoredat_load().
uint32_t scoredat_hiscore_get();

// Sets [str] to the null-terminated name at the given [place] for the
// difficulty previously loaded by scoredat_load().
void scoredat_name_get(int place, char str[SCOREDAT_NAME_BYTES + 1]);
