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
public _popup_cur_tram_x, _popup_dest_tram_x, _bgm_title_id, _POPUP_ID_NEW
public _overlay_text_fp, _POPUP_FP, _popup_byte_unknown, _popup_bonus
_popup_gaiji_len	dw ?
_popup_id_cur	db ?
_popup_dest_reached	db ?

; Buffer used for shifting in the popup text from the right of the playfield.
; Only used while the text isn't fully visible.
_popup_shiftbuf	db	(POPUP_LEN + 1) dup(?)
	db ?	; (word alignment)
if GAME eq 5
	dd    ?	;
endif
_popup_cur_tram_x	dw ?
_popup_dest_tram_x	dw ?
_bgm_title_id	db ?
_popup_id_new	db ?
_overlay_text_fp	dw ?
_popup_fp	dw ?
_popup_byte_unknown	db ?
		db ?
_popup_bonus	dd ?
