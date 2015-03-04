#define SE_COUNT 33

unsigned char snd_se_playing = -1;
unsigned char snd_se_priorities[SE_COUNT] = {
	0, 0, 32, 9, 2, 16, 5, 6, 48, 8, 9, 5, 16, 10, 17, 12, 32, 32, 16
};
unsigned char snd_se_priority_frames[SE_COUNT] = {
	0, 0, 36, 16, 4, 16, 8, 10, 48, 80, 24, 17, 11, 4, 80, 16, 48, 74, 32
};
unsigned char snd_se_frame = 0;
