#define MUSIC_CMT_LEN MUSIC_CMT_LINE_COUNT * MUSIC_CMT_LINE_LEN
char music_cmt[MUSIC_CMT_LINE_COUNT][MUSIC_CMT_LINE_LEN];

void pascal near music_cmt_load(int track)
{
	int i;
	file_ropen(MUSIC_CMT_FILE);
	file_seek(track * MUSIC_CMT_LEN, SEEK_SET);
	file_read(music_cmt, MUSIC_CMT_LEN);
	file_close();
	for(i = 0; i < MUSIC_CMT_LINE_COUNT; i++) {
		music_cmt[i][MUSIC_CMT_LINE_LEN - 2] = 0;
	}
}
