/// EMS cache area
/// --------------
/// Stores situational .CDG images that can later be copied into conventional
/// memory as needed.
/// (Yes, this is not how you make optimal use of EMS memory.)

#if (GAME == 5)
	#define EMS_NAME "GENSOEMS"
#else
	#define EMS_NAME "KAIKIEMS"
#endif

// Layout
// ------
// This is technically a structure of Planar<dots8_t[]> elements with the
// given size. But since such a structure would exceed 64 KiB, we can't declare
// it as such for a 16-bit compiler. Using an enum won't work either, as Turbo
// C++ 4.0J silently degrades any signed 32-bit values to signed 16-bit ones
// at compile time. That only leaves constants, unfortunately.
// MODDERS: Just remove the needless assignments of hardcoded offset values,
// they only provide unnecessary (and unsafe) padding. Define them in terms of
// their predecessor instead.

#define sizeof_planar_rect(w, h) \
	((((w) / BYTE_DOTS) * h) * static_cast<uint32_t>(PLANE_COUNT))

static const uint32_t EMS_EYECATCH_OFFSET = 0;
static const uint32_t EMS_EYECATCH_END = (
	EMS_EYECATCH_OFFSET + sizeof_planar_rect(EYECATCH_W, EYECATCH_H)
);
static const uint32_t EMS_PLAYCHAR_BOMB_BG_OFFSET = 34000;
static const uint32_t EMS_PLAYCHAR_BOMB_BG_END = (EMS_PLAYCHAR_BOMB_BG_OFFSET +
	sizeof_planar_rect(BOMB_BG_W_MAX, BOMB_BG_H_MAX)
);
#if (GAME == 5)
	static const uint32_t EMS_FACESET_PLAYCHAR_OFFSET = 100000;
#else
	static const uint32_t EMS_FACESET_PLAYCHAR_OFFSET = 94000;
#endif
static const uint32_t EMS_FACESET_PLAYCHAR_END = (EMS_FACESET_PLAYCHAR_OFFSET +
	(FACESET_PLAYCHAR_COUNT * sizeof_planar_rect(FACE_W, FACE_H))
);
#if (GAME == 5)
	static const uint32_t EMS_FACESET_BOSS_OFFSET = 200000;
	static const uint32_t EMS_FACESET_BOSS_END = (EMS_FACESET_BOSS_OFFSET +
		(FACESET_BOSS_COUNT * sizeof_planar_rect(FACE_W, FACE_H))
	);
	static const uint32_t EMSSIZE = 320000; /* ZUN symbol [MAGNet2010] */
#else
	static const uint32_t EMSSIZE = 180000; /* ZUN symbol [MAGNet2010] */
#endif
// ------

extern seg_t Ems; /* ZUN symbol [MAGNet2010] */

void near ems_allocate_and_preload_eyecatch(void);

// MODDERS: Doesn't actually limit the amount of copied .CDG images to at most
// PLAYCHAR_FACESET_COUNT, and instead copies all currently loaded color/alpha
// bitplanes, starting at CDG_FACESET_PLAYCHAR, until reaching a slot with no
// alpha plane. Therefore, CDG_FACESET_BOSS is assumed to be freed prior to
// calling this function.
// (As long as original game data is used, this might only become a problem
// with TH04 Reimu though, who has the only faceset with the maximum image
// count.)
void near bomb_bg_load__ems_preload_playchar_cdgs(void);

#if (GAME == 5)
	void pascal near ems_preload_boss_faceset(const char *fn);
#endif

void near eyecatch_animate(void);

// Helper functions
// ----------------

#define allocate_and_load_from_ems(dst_seg, src_off, size) { \
	reinterpret_cast<void __seg *>(dst_seg) = hmem_allocbyte(size); \
	ems_read(Ems, src_off, dst_seg, size); \
}
// ----------------
/// --------------
