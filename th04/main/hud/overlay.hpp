/// TRAM text overlaid on top of the playfield
/// ------------------------------------------

#pragma codeseg HUD_OVRL_TEXT main_01

#include "th02/main/hud/overlay.hpp"

extern nearfunc_t_near overlay1; // Rendered first
extern nearfunc_t_near overlay2; // Rendered second

// Fills the playfield area on the text RAM with transparent spaces.
void near overlay_wipe(void);

// Fills the playfield area on the text RAM with black, effectively hiding the
// playfield in the process.
void near overlay_black(void);

// Stage transitions
// -----------------

#ifdef OVERLAY_FADE_CELS
	static const int OVERLAY_FADE_INTERVAL = 8;
	static const int OVERLAY_FADE_DURATION = (
		(OVERLAY_FADE_CELS + 1) * OVERLAY_FADE_INTERVAL
	);
#endif

// Needs to be here to get the effect of `#pragma codeseg`.
void pascal near overlay_stage_enter_update_and_render(void);
void pascal near overlay_stage_leave_update_and_render(void);

// Shows the fade-in effect, followed by either the stage or BGM title or the
// blinking DEMO PLAY text.
inline void overlay_stage_enter(void) {
	overlay1 = overlay_stage_enter_update_and_render;
}

// Shows the fade-out effect. Must be called after a corresponding
// overlay_stage_enter() transition!
inline void overlay_stage_leave(void) {
	overlay1 = overlay_stage_leave_update_and_render;
}
// -----------------

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

// Needs to be here to get the effect of `#pragma codeseg`.
void pascal near overlay_popup_update_and_render(void);

inline void overlay_popup_show(popup_id_t popup_new) {
	overlay_popup_id_new = popup_new;
	overlay2 = overlay_popup_update_and_render;
}
// ----------------------------------------------------------------------------

// Stage and BGM titles
// --------------------

extern unsigned char bgm_title_id;	// only used in TH04

void near overlay_titles_invalidate(void);
void pascal near overlay_titles_update_and_render(void);
void pascal near overlay_boss_bgm_update_and_render(void);
// --------------------

#pragma codeseg
