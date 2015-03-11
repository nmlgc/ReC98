public _txesc_25line, _txesc_20line, _txesc_systemline_show, _txesc_systemline_hide, _txesc_clear
_txesc_25line	db 1Bh,'[>3l',0
_txesc_20line	db 1Bh,'[>3h',0
_txesc_systemline_show	db 1Bh,'[>1l',0
_txesc_systemline_hide	db 1Bh,'[>1h',0
_txesc_clear	db 1Bh,'[2J',0
	db 0	; word alignment
