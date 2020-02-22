cfg_options_t struc
	CFG_rank	db ?
	lives	db ?
	bombs	db ?
	CFG_bgm_mode	db ?
	CFG_se_mode 	db ?
	CFG_turbo_mode	db ?
cfg_options_t ends

cfg_t	struc
	opts	cfg_options_t <?>
	resident_sgm	dw ?
	CFG_debug	db ?
	opts_sum	db ?
cfg_t	ends

CFG_LIVES_MAX = 6
CFG_LIVES_DEFAULT = 3

if GAME eq 5
	CFG_BOMBS_MAX = 3
else
	CFG_BOMBS_MAX = 2
endif
CFG_BOMBS_DEFAULT = CFG_BOMBS_MAX
