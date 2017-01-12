; CDG slot structure.

CDGSlot struc
	; Size of a single bitplane.
	bitplane_size dw ?

	; Only used by custom functions that apply effects on the image. The core
	; CDG functions mainly use the two pre-calculated values
	; [vram_byte_at_bottom_left] and [width_divided_by_32] instead.
	pixel_width dw ?
	pixel_height dw ?

	; (640 / 8) * (pixel_height - 1)
	vram_byte_at_bottom_left dw ?

	; Divided by 8 because of 1bpp planar, divided by 4 because ZUN tends to
	; blit 4 bytes at a time, using the REP MOVSD instruction with this value.
	width_divided_by_32 dw ?

	; Number of images in this file.
	num_images db ?

	; Alpha flag for all images in this file. Unused in TH03, where all files
	; are assumed to have an alpha plane.
	; • 0 = no alpha (4 planes per image)
	; • 1 = separate 1bpp alpha plane (5 planes per image)
	; • 2 = alpha-only (1 plane per image)
	alpha db ?

	; Memory segments of the loaded data.
	sgm_alpha dw ?
	sgm_colors dw ?
CDGSlot ends
