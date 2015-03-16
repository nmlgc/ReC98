/* ReC98
 * -----
 * Main include file
 */

#include <master.h>
#include <stddef.h>

// master.lib extensions
// ---------------------
#define palette_entry_rgb_show(fn) \
	palette_entry_rgb(fn); \
	palette_show();
// ---------------------

// Macros
// ------
#define CLAMP_INC(val, max) \
	(val)++; \
	if((val) > (max)) { \
		(val) = (max); \
	}

#define CLAMP_DEC(val, min) \
	(val)--; \
	if((val) < (min)) { \
		(val) = (min); \
	}

#define RING_INC(val, ring_end) \
	(val)++; \
	if((val) > (ring_end)) { \
		(val) = 0; \
	}

#define RING_DEC(val, ring_end) \
	(val)--; \
	if((val) < 0) { \
		(val) = ring_end; \
	}

// Resident structure
#define RES_ID_LEN sizeof(RES_ID)
#define RES_ID_STRLEN (RES_ID_LEN - 1)
#define RES_PARASIZE ((sizeof(resident_t) + 0xF) >> 4)
// ------

#define RES_X 640
#define RES_Y 400

// PC-98 VRAM planes
// -----------------
typedef enum {
	PL_B, PL_R, PL_G, PL_E, PL_COUNT
} vram_plane_t;

typedef struct {
	char B, R, G, E;
} vram_planar_8_pixels_t;

typedef struct {
	int B, R, G, E;
} vram_planar_16_pixels_t;

// Since array subscripts create slightly different assembly in places, we
// offer both variants.
extern char *VRAM_PLANE[PL_COUNT];
extern char *VRAM_PLANE_B;
extern char *VRAM_PLANE_G;
extern char *VRAM_PLANE_R;
extern char *VRAM_PLANE_E;

#define ROW_SIZE (RES_X / 8)
#define PLANE_SIZE (ROW_SIZE * RES_Y)

#define PLANE_DWORD_BLIT(dst, src) \
	for(p = 0; p < PLANE_SIZE; p += 4) { \
		*(long*)((dst) + p) = *(long*)((src) + p); \
	}

#define VRAM_OFFSET(x, y) ((x) >> 3) + (y << 6) + (y << 4)

void pascal vram_planes_set(void);
// -----------------

// PC-98 keyboard
// --------------
typedef enum {
	K0_ESC = 0x01,
	K0_1 = 0x02,
	K0_2 = 0x04,
	K0_3 = 0x08,
	K0_4 = 0x10,
	K0_5 = 0x20,
	K0_6 = 0x40,
	K0_7 = 0x80
} keygroup_0;

typedef enum {
	K1_8 = 0x01,
	K1_9 = 0x02,
	K1_0 = 0x04,
	K1_MINUS = 0x08,
	K1_CIRCUMFLEX = 0x10,
	K1_YEN = 0x20,
	K1_BACKSPACE = 0x40,
	K1_TAB = 0x80
} keygroup_1;

typedef enum {
	K2_Q = 0x01,
	K2_W = 0x02,
	K2_E = 0x04,
	K2_R = 0x08,
	K2_T = 0x10,
	K2_Y = 0x20,
	K2_U = 0x40,
	K2_I = 0x80
} keygroup_2;

typedef enum {
	K3_O = 0x01,
	K3_P = 0x02,
	K3_AT = 0x04,
	K3_LBRACKET = 0x08,
	K3_RETURN = 0x10,
	K3_A = 0x20,
	K3_S = 0x40,
	K3_D = 0x80
} keygroup_3;

typedef enum {
	K4_F = 0x01,
	K4_G = 0x02,
	K4_H = 0x04,
	K4_J = 0x08,
	K4_K = 0x10,
	K4_L = 0x20,
	K4_PLUS = 0x40,
	K4_ASTERISK = 0x80
} keygroup_4;

typedef enum {
	K5_RBRACKET = 0x01,
	K5_Z = 0x02,
	K5_X = 0x04,
	K5_C = 0x08,
	K5_V = 0x10,
	K5_B = 0x20,
	K5_N = 0x40,
	K5_M = 0x80
} keygroup_5;

typedef enum {
	K6_COMMA = 0x01,
	K6_PERIOD = 0x02,
	K6_SLASH = 0x04,
	K6_UNDERSCORE = 0x08,
	K6_SPACE = 0x10,
	K6_XFER = 0x20,
	K6_ROLL_UP = 0x40,
	K6_ROLL_DOWN = 0x80
} keygroup_6;

typedef enum {
	K7_INS = 0x01,
	K7_DEL = 0x02,
	K7_ARROW_UP = 0x04,
	K7_ARROW_LEFT = 0x08,
	K7_ARROW_RIGHT = 0x10,
	K7_ARROW_DOWN = 0x20,
	K7_HOME_CLR = 0x40,
	K7_END = 0x80
} keygroup_7;

typedef enum {
	K8_NUM_MINUS = 0x01,
	K8_NUM_DIV = 0x02,
	K8_NUM_7 = 0x04,
	K8_NUM_8 = 0x08,
	K8_NUM_9 = 0x10,
	K8_NUM_MUL = 0x20,
	K8_NUM_4 = 0x40,
	K8_NUM_5 = 0x80
} keygroup_8;

typedef enum {
	K9_NUM_6 = 0x01,
	K9_NUM_PLUS = 0x02,
	K9_NUM_1 = 0x04,
	K9_NUM_2 = 0x08,
	K9_NUM_3 = 0x10,
	K9_NUM_EQUALS = 0x20,
	K9_NUM_0 = 0x40,
	K9_NUM_COMMA = 0x80
} keygroup_9;

typedef enum {
	K10_NUM_PERIOD = 0x01,
	K10_NFER = 0x02,
	K10_VF1 = 0x04,
	K10_VF2 = 0x08,
	K10_VF3 = 0x10,
	K10_VF4 = 0x20,
	K10_VF5 = 0x40
} keygroup_10;

typedef enum {
	K11_NUM = 0x02,

	// Couldn't find any info whatsoever on the next three, but they're
	// listed in MEMSYS.TXT, so...
	K11_SYMBOL_SHIFT = 0x04,
	K11_VOWEL_SHIFT = 0x08,
	K11_CONSONANT_SHIFT = 0x10,

	K11_HOME = 0x40
} keygroup_11;

typedef enum {
	K12_STOP = 0x01,
	K12_COPY = 0x02,
	K12_F1 = 0x04,
	K12_F2 = 0x08,
	K12_F3 = 0x10,
	K12_F4 = 0x20,
	K12_F5 = 0x40,
	K12_F6 = 0x80
} keygroup_12;

typedef enum {
	K13_F7 = 0x01,
	K13_F8 = 0x02,
	K13_F9 = 0x04,
	K13_F10 = 0x08
} keygroup_13;

typedef enum {
	K14_SHIFT = 0x01,
	K14_CAPS = 0x02,
	K14_KANA = 0x04,
	K14_GRPH = 0x08,
	K14_CTRL = 0x10
} keygroup_14;
// --------------
