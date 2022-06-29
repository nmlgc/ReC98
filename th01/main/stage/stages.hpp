extern bool16 stage_cleared;

// Amount of time until the player has to HARRY UP.
extern unsigned int stage_timer;

// Default filenames for the background image and music. Adjusted by
// scene_init_and_load().
extern char default_grp_fn[15];
extern char default_bgm_fn[15];

// Specifies whether PTN_SLOT_STG contains the full set of sprites required for
// card-flipping stages (`false`), or the trimmed-down version for boss stages
// (`true`).
extern bool ptn_slot_stg_has_reduced_sprites;

// Render the initial stage screen and animations, depending on whether the
// current stage is the [first_stage_in_scene]. If this is the case, this
// function must be called with VRAM page 0 as the accessed page.
void stage_entrance(int stage_id, const char* bg_fn, bool16 clear_vram_page_0);

// Loads the contents of STAGE[id].DAT, and sets [default_grp_fn] and
// [default_bgm_fn] accordingly. [id] must be ≥0 and ≤9.
// (Defined in stageobj.cpp.)
void scene_init_and_load(unsigned char id);
