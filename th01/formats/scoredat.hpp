#define SCOREDAT_MAGIC "HISCORE"
#define SCOREDAT_PLACES 10
#define SCOREDAT_NAME_KANJI 8

// Actually creates slightly different assembly compared to sizeof() on an
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

#if 0
// On-disk structure of the REYHI*.DAT files.
// For reference, never actually used by the game itself
struct scoredat_t {
	// Not null-terminated!
	char magic[sizeof(SCOREDAT_MAGIC) - 1];

	// Not null-terminated.
	shiftjis_kanji_t name[SCOREDAT_PLACES][SCOREDAT_NAME_KANJI];

	score_t score[SCOREDAT_PLACES];
	int16_t stage[SCOREDAT_PLACES];
	shiftjis_kanji_t route[SCOREDAT_PLACES];
};
#endif

// Loads the score file for the current [rank], recreating it if necessary.
// Returns 0 on success, 1 on failure.
int scoredat_load();

// Loads only the high score for the current [rank] into the resident
// structure.
void scoredat_load_hiscore();

// Sets [str] to the null-terminated name at the given [place] for the
// difficulty previously loaded by scoredat_load().
void scoredat_name_get(int place, char str[SCOREDAT_NAME_BYTES + 1]);
