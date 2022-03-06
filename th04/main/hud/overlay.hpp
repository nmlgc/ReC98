/// TRAM text overlaid on top of the playfield
/// -------------------------------------------

extern nearfunc_t_near overlay1; // Rendered first
extern nearfunc_t_near overlay2; // Rendered second

// Fills the playfield area on the text RAM with transparent spaces.
void near overlay_wipe(void);

// Fills the playfield area on the text RAM with black, effectively hiding the
// playfield in the process.
void near overlay_black(void);

// Popup messages for common gameplay events, shown at the top of the playfield
// ----------------------------------------------------------------------------

enum popup_id_t {
	POPUP_ID_HISCORE_ENTRY = 0,
	POPUP_ID_EXTEND = 1,
	POPUP_ID_BONUS = 2,
	POPUP_ID_FULL_POWERUP = 3,
	#if (GAME == 5)
		POPUP_ID_DREAMBONUS_MAX = 4,
	#endif

	_popup_id_t_FORCE_UINT8 = 0xFF
};

extern popup_id_t overlay_popup_id_new;
extern unsigned long overlay_popup_bonus;

#define overlay_popup_show(popup_new) \
	/* Yup, the only known way of assigning a `near` function to a `near` */ \
	/* function pointer from a group outside the one where the `near` */ \
	/* function was declared in involves lying to the compiler about the */ \
	/* true distance of the function. That's also why we can't correctly */ \
	/* declare this function at global scope. */ \
	void pascal far overlay_popup_update_and_render(void); \
	\
	overlay_popup_id_new = popup_new; \
	overlay2 = reinterpret_cast<nearfunc_t_near>( \
		overlay_popup_update_and_render \
	);
// ----------------------------------------------------------------------------

// Stage and BGM titles
// --------------------

extern unsigned char bgm_title_id;	// only used in TH04

void near overlay_titles_invalidate(void);
void pascal near overlay_titles_update_and_render(void);
void pascal near overlay_boss_bgm_update_and_render(void);
// --------------------
