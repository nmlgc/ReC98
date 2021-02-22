include libs/kaja/kaja.inc
include th03/arg_bx.inc
include th04/snd/snd.inc

	extrn _snd_bgm_mode:byte

SHARED_	segment word public 'CODE' use16
	assume cs:SHARED_

public SND_KAJA_INTERRUPT
snd_kaja_interrupt proc far
	cmp	_snd_bgm_mode, SND_BGM_OFF
	jz	short @@ret

arg_bx	far, @ax:word

	mov	ax, @ax
	cmp	_snd_bgm_mode, SND_BGM_MIDI
	jz	short @@midi
	int	PMD
	jmp	short @@ret

@@midi:
	int	MMD

@@ret:
	ret_bx
snd_kaja_interrupt endp
	even
SHARED_	ends

	end
