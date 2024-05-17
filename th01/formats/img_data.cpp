// ZUN bloat: This file should not exist, as it causes the data for the .PTN
// and .GRZ formats to be needlessly linked into OP.EXE and FUUIN.EXE. Just
// declare the data local to the respective translation unit.

#include "platform.h"
#include "pc98.h"
#include "th01/formats/grz.h"
#include "th01/formats/ptn_data.hpp"

#if (BINARY != 'E')
	// TODO: Move into vplanset.cpp once we're close to done with TH02-TH04.
	dots8_t far *VRAM_PLANE_B;
	dots8_t far *VRAM_PLANE_R;
	dots8_t far *VRAM_PLANE_G;
	dots8_t far *VRAM_PLANE_E;
#endif


static int8_t unused[80]; // ZUN bloat

// .GRP and .PTN
// -------------

bool16 flag_palette_show = true;
// -------------

// .GRP
// ----

Palette4 grp_palette;
bool16 flag_grp_put = true;
static bool flag_grp_unused[3] = { false }; // ZUN bloat
// ----

// .PTN
// ----

ptn_t* ptn_images[PTN_SLOT_COUNT];
int8_t ptn_image_count[PTN_SLOT_COUNT] = { 0 };
// ----

// .GRZ
// ----

uint8_t* rle_streams[GRX_COUNT];

// Actually a Planar<dots8_t*>, but used like a dots8_t* everywhere.
dots8_t* planar_streams[GRX_COUNT][PLANAR_STREAM_PER_GRX_COUNT];

uint8_t planar_stream_count[GRX_COUNT];
// ----

// .GRP again
// ----------

#if (BINARY == 'E')
	int grp_palette_tone = 100;
#endif
bool flag_grp_colorkey = false;
int8_t* grp_buf;
// ----------

#if (BINARY == 'E')
	// TODO: Move into vplanset.cpp once we're close to done with TH02-TH04.
	dots8_t far *VRAM_PLANE_B;
	dots8_t far *VRAM_PLANE_R;
	dots8_t far *VRAM_PLANE_G;
	dots8_t far *VRAM_PLANE_E;
#endif
