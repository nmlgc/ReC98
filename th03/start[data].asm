include th03/chars.inc

public _demo_chars, _demo_rand
_demo_chars	label byte
	db	(1 + (PLAYCHAR_MIMA     * 2)),	(1 + (PLAYCHAR_REIMU  * 2))
	db	(1 + (PLAYCHAR_MARISA   * 2)),	(1 + (PLAYCHAR_RIKAKO * 2))
	db	(1 + (PLAYCHAR_ELLEN    * 2)),	(1 + (PLAYCHAR_KANA   * 2))
	db	(1 + (PLAYCHAR_KOTOHIME * 2)),	(1 + (PLAYCHAR_MARISA * 2))
_demo_rand	label dword
	dd	600
	dd	1000
	dd	3200
	dd	500
