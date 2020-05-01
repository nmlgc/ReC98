enum popup_id_t {
	POPUP_ID_HISCORE_ENTRY = 0,
	POPUP_ID_EXTEND = 1,
	POPUP_ID_BONUS = 2,
	POPUP_ID_FULL_POWERUP = 3,
	#if (GAME == 5)
		POPUP_ID_DREAMBONUS_MAX = 4,
	#endif
};

extern unsigned char bgm_title_id;	// only used in TH04
extern popup_id_t popup_id_new;
extern nearfunc_t_near overlay_text;
extern nearfunc_t_near popup;
extern unsigned long popup_bonus;

void pascal near popup_update_and_render(void);

/// Stage and BGM titles
/// --------------------
extern unsigned char popup_boss_bgm_frame;
extern unsigned char popup_titles_frame;

void pascal near popup_titles_invalidate(void);
void pascal near popup_titles_update_and_render(void);
void pascal near popup_boss_bgm_update_and_render(void);
/// --------------------
