include th03/math/subpixel.inc

speed_t struc
	aligned  SPPoint8 <?>
	diagonal SPPoint8 <?>
speed_t ends

playchar_speeds_t struc
	motion speed_t <?>
	gauge_charge db ?
playchar_speeds_t ends

public _PLAYCHAR_SPEEDS
_PLAYCHAR_SPEEDS label playchar_speeds_t
	db (4 shl 4),     (4 shl 4),     (3 shl 4),      (3 shl 4),      32	; Reimu
	db (4 shl 4) + 8, (4 shl 4) + 8, (3 shl 4) +  6, (3 shl 4) +  6, 20	; Mima
	db (4 shl 4),     (4 shl 4),     (3 shl 4),      (3 shl 4),      28	; Marisa
	db (3 shl 4) + 4, (3 shl 4) + 4, (2 shl 4) + 14, (2 shl 4) + 14, 14	; Ellen
	db (4 shl 4) + 4, (4 shl 4) + 4, (3 shl 4) +  4, (3 shl 4) +  4, 28	; Kotohime
	db (3 shl 4) + 8, (3 shl 4) + 8, (2 shl 4) + 12, (2 shl 4) + 12, 32	; Kana
	db (4 shl 4) + 8, (4 shl 4) + 8, (3 shl 4) +  6, (3 shl 4) +  6, 16	; Rikako
	db (5 shl 4),     (5 shl 4),     (4 shl 4),      (4 shl 4),      28	; Chiyuri
	db (5 shl 4),     (5 shl 4),     (4 shl 4),      (4 shl 4),      20	; Yumemi
	db (size playchar_speeds_t) dup(0)
