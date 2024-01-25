inline void touhou_reiiden_animate_char(shiftjis_kanji_t shiftjis) {
	mdrv2_se_play(14);
	tram_x16_kanji_center_reverse(shiftjis_to_jis(shiftjis));
	frame_delay(8);
}

inline void touhou_reiiden_animate(void) {
	touhou_reiiden_animate_char('');
	touhou_reiiden_animate_char('ϋ');
	touhou_reiiden_animate_char('');
	touhou_reiiden_animate_char('θΛ');
	touhou_reiiden_animate_char('Ω');
	touhou_reiiden_animate_char('`');
}
