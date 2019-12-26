/* ReC98
 * -----
 * TH02 high score pre-save encoding
 */

#define SCOREDAT_ENCODE() \
	int i; \
	hi.score.points_sum = 0; \
	hi.score.g_name_first_sum = 0; \
	hi.score.stage_sum = 0; \
	hi.score_sum = 0; \
	for(i = 0; i < SCOREDAT_PLACES; i++) { \
		hi.score.points_sum += hi.score.points[i]; \
		hi.score.g_name_first_sum += hi.score.g_name[i][0]; \
		hi.score.stage_sum += hi.score.stage[i]; \
	} \
	for(i = 0; i < sizeof(hi.score); i++) { \
		hi.score_sum += *((unsigned char*)(&hi.score) + i); \
		*((unsigned char*)(&hi.score) + i) += 0x12; \
	}
