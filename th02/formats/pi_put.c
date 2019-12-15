void pi_slot_palette_apply(int slot)
{
	palette_set_all(pi_slot_headers[slot].palette);
	palette_show();
}

void pi_slot_put(int x, int y, int slot)
{
	char *row_p = pi_slot_buffers[slot];
	int row_num;
	for(row_num = 0; row_num < pi_slot_headers[slot].ysize; row_num++) {
		graph_pack_put_8(x, y, row_p, pi_slot_headers[slot].xsize);
		y++;
		if(y >= RES_Y) {
			y -= RES_Y;
		}
		row_p += pi_slot_headers[slot].xsize / 2;
		row_p = MK_FP(
			(int)((unsigned long)(row_p) >> 16) + (FP_OFF(row_p) >> 4),
			FP_OFF(row_p) & 0xF
		);
	}
}
