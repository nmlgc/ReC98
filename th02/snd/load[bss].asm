SND_LOAD_FN_LEN equ 13
public _snd_load_fn
_snd_load_fn db SND_LOAD_FN_LEN dup(?)
	db ? ; word alignment
