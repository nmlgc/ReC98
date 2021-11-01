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
