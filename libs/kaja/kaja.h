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

	// Returns the type of PMD driver in AL, as well as its version in DX.
	// AL values relevant for PC-98 Touhou:
	// • AL = 0xFF: Resident but no sound source
	// • AL = 0x00: PMD.COM (for PC-9801-26K / OPN)
	// • AL ≥ 0x01: Any other driver compatible to the PC-9801-86 / OPNA
	PMD_GET_DRIVER_TYPE_AND_VERSION = 0x09,

	PMD_GET_SE_ADDRESS = 0x0B,
	PMD_SE_PLAY = 0x0C,
	PMD_GET_WORKAREA_ADDRESS = 0x10,

	// Returns the sizes of the song (AL), instrument (AH), and sound effect
	// (DL) buffers, in KiB. These can be customized on the PMD command line
	// with the /M, /V and /E options respectively.
	PMD_GET_BUFFER_SIZES = 0x22,

	_kaja_func_t_FORCE_UINT16 = 0xFFFF
} kaja_func_t;

#define PMD 0x60
#define MMD 0x61

// Memory structure of a KAJA interrupt service routine, pointed to by its
// address stored in the x86 interrupt vector. Used for identifying whether
// PMD or MMD are installed at a certain IRQ#, by checking [magic].
typedef struct {
	uint8_t jmp[2];  	// JMP to the code
	uint8_t magic[3];	// "PMD" or "MMD"
} kaja_isr_t;

#define kaja_isr_magic_matches(isr, magic1, magic2, magic3) \
	(((kaja_isr_t *)(isr))->magic[0] == magic1) && \
	(((kaja_isr_t *)(isr))->magic[1] == magic2) && \
	(((kaja_isr_t *)(isr))->magic[2] == magic3)

// MMDFUNC.DOC and https://gist.github.com/devinacker/bdc58cfdba6a1ee80449
// both imply that this is a hardcoded property of the MMD format
#define MMD_TICKS_PER_QUARTER_NOTE 48

// Work area structure names and fields taken from pmdwin.h
// --------------------------------------------------------
#define ONKAI_REST (-1)
#define ONKAI_OCTAVE_MASK (0xF0)
#define ONKAI_NOTE_MASK (0x0F)

// 演奏中のデータエリア
typedef struct qqtag {

	// 演奏中のアドレス (曲データ先頭番地+1からのoffset)
	unsigned char near *address;
	//  演奏が終わった時の戻り先アドレス (同上)
	unsigned char near *partloop;
	// 現在発音中の音符の 残り Length 値;
	unsigned char leng;
	// gatetime値。gatetime ≧ 残りLength が成立した時点で、Keyoff
	unsigned char qdat;

	// (TH05 doesn't use those and we can't know the signedness of a lot of
	// these, so...)
	char dummy[79];

	// 演奏中の音階　オクターブ×16 + 音階(c～b=0～11),rest=255
	char onkai;
} QQ;

typedef struct OpenWorktag {
	QQ near *FMPart[6];
	QQ near *SSGPart[3];
	QQ near *PCMPart[1];
	QQ near *RhythmPart[1];
} OPEN_WORK;
// --------------------------------------------------------
