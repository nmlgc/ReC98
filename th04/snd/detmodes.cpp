#pragma option -zCSHARED

#include "platform.h"
#include "x86real.h"
#include "libs/kaja/kaja.h"
extern "C" {
#include "th04/snd/snd.h"

int pascal snd_determine_modes(int req_bgm_mode, int req_se_mode)
{
	snd_pmd_resident();
	if(req_bgm_mode == SND_BGM_MIDI) {
		snd_mmd_resident();
	}
	// ZUN bug: We should be returning if neither driver is resident!

	_AH = PMD_GET_DRIVER_TYPE_AND_VERSION;
	geninterrupt(PMD);
	if(_AL == 0xFF) {
		snd_bgm_mode = SND_BGM_OFF;
	} else if(_AL == 0x00) {
		snd_bgm_mode = SND_BGM_FM26;
	} else {
		snd_bgm_mode = SND_BGM_FM86;
	}

	if(req_se_mode == SND_SE_FM) {
		_AX = (snd_bgm_active() ? SND_SE_FM : SND_SE_OFF);
		snd_se_mode = _AX;
	} else if(req_se_mode == SND_SE_BEEP) {
		snd_se_mode = SND_SE_BEEP;
	} else {
		snd_se_mode = SND_SE_OFF;
	}

	// We tentatively set [snd_bgm_mode] above, but do we even want any?
	if(req_bgm_mode == SND_BGM_OFF) {
		snd_bgm_mode = SND_BGM_OFF;
	} else if((req_bgm_mode == SND_BGM_MIDI) && snd_midi_possible) {
		snd_bgm_mode = SND_BGM_MIDI;
	} else if((req_bgm_mode == SND_BGM_FM26) && snd_bgm_active()) {
		snd_bgm_mode = SND_BGM_FM26;
	}

	return snd_bgm_mode;
}

}
