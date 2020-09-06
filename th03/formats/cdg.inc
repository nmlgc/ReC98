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

vram_plane_next macro seg:req, label_loop:req
	; Next segment...
	mov	ax, seg
	add	ax, SEG_PLANE_DIST_BRG
	mov	seg, ax

	; Still in the R or G segment?
	cmp	ax, (SEG_PLANE_G + SEG_PLANE_DIST_BRG)
	jb	short label_loop

	; Already in the E segment?
	cmp	ax, (SEG_PLANE_G + (SEG_PLANE_DIST_BRG * 2))
	jnb	short @@vram_plane_next_done

	; Make the large jump between G and E
	add	ax, (SEG_PLANE_DIST_E - SEG_PLANE_DIST_BRG)
	mov	seg, ax
	jmp	short label_loop

@@vram_plane_next_done:
endm
