inline void touhou_reiiden_animate_char(uint16_t shiftjis) {
	mdrv2_se_play(14);
	tram_x16_kanji_center_reverse(shiftjis_to_jis(shiftjis));
	frame_delay(8);
}

inline void touhou_reiiden_animate(void) {
	touhou_reiiden_animate_char('“Œ');
	touhou_reiiden_animate_char('•û');
	touhou_reiiden_animate_char('š');
	touhou_reiiden_animate_char('èË');
	touhou_reiiden_animate_char('ˆÙ');
	touhou_reiiden_animate_char('“`');
}
