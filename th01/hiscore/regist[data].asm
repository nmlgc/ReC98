public _ALPHABET_A
public _ALPHABET_SPACE, _ALPHABET_LEFT, _ALPHABET_RIGHT, _ALPHABET_ENTER

if BINARY eq 'E'
	public _ALPHABET_KANJI_FMT_0, _ALPHABET_KANJI_FMT_1
	public _ALPHABET_KANJI_FMT_2, _ALPHABET_KANJI_FMT_3
	_ALPHABET_KANJI_FMT_0	db '%c%c',0
	_ALPHABET_A		db 'ａ',0
	_ALPHABET_KANJI_FMT_1	db '%c%c',0
	_ALPHABET_KANJI_FMT_2	db '%c%c',0
	_ALPHABET_KANJI_FMT_3	db '%c%c',0
else
	_ALPHABET_A		db 'ａ',0
endif
_ALPHABET_SPACE	db 'SP',0
_ALPHABET_LEFT 	db '←',0
_ALPHABET_RIGHT	db '→',0
_ALPHABET_ENTER	db '終',0

public _REGIST_HEADER_PLACE, _REGIST_HEADER_NAME
public _REGIST_HEADER_SCORE, _REGIST_HEADER_STAGE_ROUTE
public _REGIST_PLACE_0, _REGIST_PLACE_1, _REGIST_PLACE_2, _REGIST_PLACE_3
public _REGIST_PLACE_4, _REGIST_PLACE_5, _REGIST_PLACE_6, _REGIST_PLACE_7
public _REGIST_PLACE_8, _REGIST_PLACE_9
public _REGIST_STAGE_MAKAI, _REGIST_STAGE_JIGOKU, _REGIST_STAGE_ROUTE_DASH
_REGIST_HEADER_PLACE      	db '　霊　位　',0
_REGIST_HEADER_NAME       	db '　　名　　前　　',0
_REGIST_HEADER_SCORE      	db '　　得　　点　　',0
_REGIST_HEADER_STAGE_ROUTE	db 'ステージ・ルート',0
_REGIST_PLACE_0	db '　靈　神　',0
_REGIST_PLACE_1	db '太元帥明王',0
_REGIST_PLACE_2 db '　天　仙　',0
_REGIST_PLACE_3	db '　神　仙　',0
_REGIST_PLACE_4	db '　地　仙　',0
_REGIST_PLACE_5	db '　人　仙　',0
_REGIST_PLACE_6	db '　仙　女　',0
_REGIST_PLACE_7	db '陰　陽　師',0
_REGIST_PLACE_8	db '靈　媒　師',0
_REGIST_PLACE_9	db '修　業　者',0
_REGIST_STAGE_MAKAI 	db '魔界',0
_REGIST_STAGE_JIGOKU	db '地獄',0
_REGIST_STAGE_ROUTE_DASH	db '−',0
if BINARY eq 'E'
	public _REGIST_ROUTE_FMT
	_REGIST_ROUTE_FMT	db '%c%c',0

	public _ALPHABET_SPACE_0, _ALPHABET_LEFT_0
	public _ALPHABET_RIGHT_0, _ALPHABET_ENTER_0, _ALPHABET_KANJI_FMT_4
	public _REGIST_STRING_FMT_0, _REGIST_STRING_FMT_1
	_ALPHABET_SPACE_0	db 'SP',0
	_ALPHABET_LEFT_0 	db '←',0
	_ALPHABET_RIGHT_0	db '→',0
	_ALPHABET_ENTER_0	db '終',0
	_ALPHABET_KANJI_FMT_4	db '%c%c',0
	_REGIST_STRING_FMT_0	db '%s',0
	_REGIST_STRING_FMT_1	db '%s',0
	_SCOREDAT_FN_EASY_2   	db 'REYHIES.DAT',0
	_SCOREDAT_FN_NORMAL_2 	db 'REYHINO.DAT',0
	_SCOREDAT_FN_HARD_2   	db 'REYHIHA.DAT',0
	_SCOREDAT_FN_LUNATIC_2	db 'REYHILU.DAT',0
endif
public _SCOREDAT_FOPEN_WB
_SCOREDAT_FOPEN_WB	db 'wb',0
_REGIST_TITLE_RANK_EASY   	db '　イージー　',0
_REGIST_TITLE_RANK_NORMAL 	db '　ノーマル　',0
_REGIST_TITLE_RANK_HARD   	db '　ハード　　',0
_REGIST_TITLE_RANK_LUNATIC	db 'ルナティック',0

if BINARY eq 'E'
	public _REGIST_TITLE_FMT
	_REGIST_TITLE_FMT		db '東方靈異伝　強者の記録　%s',0
else
	public _REGIST_BG_NOT_CLEARED, _REGIST_BG_CLEARED
	public _REGIST_TITLE_1, _REGIST_TITLE_2
	_REGIST_BG_NOT_CLEARED	db 'game_o.grp',0
	_REGIST_BG_CLEARED    	db 'endm_a.grp',0
	_REGIST_TITLE_1	db '東方靈異伝　強者の記録　',0
	_REGIST_TITLE_2	db '東方靈異伝　強者の記録',0
endif
