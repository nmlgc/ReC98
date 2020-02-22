cfg_options_t struc
	CFG_bgm_mode	db ?
	CFG_key_mode	db ?
	CFG_rank    	db ?
		dw ?
cfg_options_t ends

cfg_t	struc
	opts	cfg_options_t <?>
	resident_sgm	dw ?
	CFG_debug	db ?
cfg_t	ends
