POPUP_LEN = 8

public _stage_title_len, _stage_bgm_title_len, _boss_bgm_title_len
_stage_title_len	dw ?
_stage_bgm_title_len	dw ?
if GAME eq 4
	public _stage_title_id
	_stage_title_id	db ?
		evendata
endif
_boss_bgm_title_len	dw ?

public _popup_gaiji_len, _popup_id_cur, _popup_dest_reached, _popup_shiftbuf
public _popup_cur_tram_left, _popup_dest_tram_left, _bgm_title_id
public _overlay_popup_id_new, _overlay1, _overlay2, _titles_frame
public _overlay_popup_bonus
_popup_gaiji_len	dw ?
_popup_id_cur	db ?
_popup_dest_reached	db ?
_popup_shiftbuf	db	(POPUP_LEN + 1) dup(?)
	evendata
if GAME eq 5
	dd    ?	;
endif
_popup_cur_tram_left	dw ?
_popup_dest_tram_left	dw ?
_bgm_title_id	db ?
_overlay_popup_id_new	db ?
_overlay1	dw ?
_overlay2	dw ?
_titles_frame	db ?
	evendata
_overlay_popup_bonus	dd ?

if (GAME eq 5)
	public _stage_title, _stage_bgm_title, _boss_bgm_title
	_stage_title    	dd ?
	_stage_bgm_title	dd ?
	_boss_bgm_title 	dd ?
endif
