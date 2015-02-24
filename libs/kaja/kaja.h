/* ReC98
 * -----
 * Function numbers for the PMD and MMD drivers, according to PMDDATA.DOC and
 * MMDFUNC.DOC. Functions prefixed with KAJA are available in both drivers.
 * Only includes functions that are actually used in the games.
 */

typedef enum {
	KAJA_SONG_PLAY = 0x00,
	KAJA_SONG_STOP = 0x01,
	KAJA_SONG_FADE = 0x02,
	KAJA_GET_SONG_MEASURE = 0x05,
	KAJA_GET_SONG_ADDRESS = 0x06,
	KAJA_GET_VOLUME = 0x08,
	PMD_GET_DRIVER_VERSION = 0x09,
	PMD_GET_SE_ADDRESS = 0x0B,
	PMD_SE_PLAY = 0x0C,
	PMD_GET_WORKAREA_ADDRESS = 0x10,
} kaja_func_t;

#define PMD 0x60
