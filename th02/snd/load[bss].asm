SND_LOAD_SONG equ (KAJA_GET_SONG_ADDRESS shl 8)
SND_LOAD_SE equ (PMD_GET_SE_ADDRESS shl 8)

SND_LOAD_FN_LEN equ 13
public _snd_load_fn
_snd_load_fn db SND_LOAD_FN_LEN dup(?)
	db ? ; word alignment
