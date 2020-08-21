void pi_slot_palette_apply(int slot)
{
	palette_set_all(pi_slot_headers[slot].palette);
	palette_show();
}

void pi_slot_put(screen_x_t left, vram_y_t top, int slot)
{
	char *row_p = pi_slot_buffers[slot];
	pixel_t y;
	for(y = 0; y < pi_slot_headers[slot].ysize; y++) {
		graph_pack_put_8(left, top, row_p, pi_slot_headers[slot].xsize);
		top++;
		if(top >= RES_Y) {
			top -= RES_Y;
		}
		row_p += pi_slot_headers[slot].xsize / 2;
		row_p = MK_FP(
			(int)((unsigned long)(row_p) >> 16) + (FP_OFF(row_p) >> 4),
			FP_OFF(row_p) & 0xF
		);
	}
}
