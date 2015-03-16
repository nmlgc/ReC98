extern unsigned char snd_se_playing;
extern unsigned char snd_se_priorities[];
extern unsigned char snd_se_priority_frames[];
extern unsigned char snd_se_frame;

#pragma option -k-

void snd_se_reset(void)
{
	snd_se_frame = 0;
	snd_se_playing = 0xFF;
}

#pragma codestring "\x90"

void snd_se_play(int new_se)
{
	if(!snd_fm_possible) {
		return;
	}
	if(snd_se_playing == 0xFF) {
		snd_se_playing = new_se;
	} else if(snd_se_priorities[snd_se_playing] <= snd_se_priorities[new_se]) {
		snd_se_playing = new_se;
		snd_se_frame = 0;
	}
}

void snd_se_update(void)
{
	if(snd_fm_possible && snd_se_playing != 0xFF) {
		if(snd_se_frame == 0) __asm {
			mov	ah, PMD_SE_PLAY
			mov	al, snd_se_playing
			int	PMD
		}
		snd_se_frame++;
		if(snd_se_priority_frames[snd_se_playing] < snd_se_frame) {
			snd_se_frame = 0;
			snd_se_playing = -1;
		}
	}
}
