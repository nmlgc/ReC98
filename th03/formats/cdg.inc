if GAME ge 4
	CDG_COLORS = 0
	CDG_COLORS_AND_ALPHA = 1
	CDG_ALPHA = 2

	CDG_SLOT_COUNT = 64
else
	CDG_COLORS_AND_ALPHA = 0

	CDG_SLOT_COUNT = 32
endif

cdg_t struc
	CDG_plane_size dw ?
	pixel_w dw ?
	pixel_h dw ?
	offset_at_bottom_left dw ?
	vram_dword_w dw ?
	image_count db ?
	plane_layout db ?
	seg_alpha dw ?
	seg_colors dw ?
cdg_t ends
