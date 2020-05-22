extern const char SCOREDAT_ROUTE_NONE[];
extern char scoredat_name_default[];
extern const char SCOREDAT_MAGIC_0[];
extern const char SCOREDAT_MAGIC_1[];
extern const char SCOREDAT_FN_EASY_0[];
extern const char SCOREDAT_FN_EASY_1[];
extern const char SCOREDAT_FN_NORMAL_0[];
extern const char SCOREDAT_FN_NORMAL_1[];
extern const char SCOREDAT_FN_HARD_0[];
extern const char SCOREDAT_FN_HARD_1[];
extern const char SCOREDAT_FN_LUNATIC_0[];
extern const char SCOREDAT_FN_LUNATIC_1[];

#define scoredat_fn(buf, inst) \
	switch(rank) { \
	case RANK_EASY:   	strcpy(fn, SCOREDAT_FN_EASY_##inst);	break; \
	case RANK_NORMAL: 	strcpy(fn, SCOREDAT_FN_NORMAL_##inst);	break; \
	case RANK_HARD:   	strcpy(fn, SCOREDAT_FN_HARD_##inst);	break; \
	case RANK_LUNATIC:	strcpy(fn, SCOREDAT_FN_LUNATIC_##inst);	break; \
	}

int8_t scoredat_name_byte_encode(int8_t byte)
{
	return (byte + SCOREDAT_NAME_KEY);
}

int8_t scoredat_name_byte_decode(int8_t byte)
{
	return (byte + (0x100 - SCOREDAT_NAME_KEY));
}

#pragma warn -rch

void scoredat_recreate()
{
	int i;
	int16_t stage;
	const char *route;
	int32_t points;
#if (BINARY == 'E')
	FILE *fp;
#endif
	// Will be name-encoded, and therefore modified in the .data section!
	char *name;
	const char *magic;
	char fn[16];

	route = SCOREDAT_ROUTE_NONE;
	name = scoredat_name_default;
	magic = SCOREDAT_MAGIC_0;
	scoredat_fn(fn, 0);

	scoredat_cli();
	if(scoredat_create(fn) == 0) {
		goto end;
		return;
	}
	scoredat_write(magic, sizeof(SCOREDAT_MAGIC) - 1);

	stage = SCOREDAT_PLACES;
	points = (SCOREDAT_PLACES * 100);
	for(i = 0; i < SCOREDAT_NAME_BYTES; i++) {
		name[i] = scoredat_name_byte_encode(name[i]);
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		scoredat_write(name, SCOREDAT_NAME_BYTES);
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		scoredat_write(&points, sizeof(points));
		points = points - 100;
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		scoredat_write(&stage, sizeof(stage));
		stage = stage - 1;
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		scoredat_write(route, sizeof(twobyte_t));
	}
	scoredat_close();
end:
	scoredat_sti();
}

int scoredat_load()
{
	union {
		char magic[sizeof(SCOREDAT_MAGIC) - 1];
		char space[50];
	} buf;
	char fn[16];
#if (BINARY == 'E')
	FILE *fp;
#endif

	scoredat_fn(fn, 1);
	if(!scoredat_exist(fn)) {
		scoredat_recreate();
	}

	scoredat_cli();
	if(scoredat_ropen(fn) == 0) {
		scoredat_error(SCOREDAT_ERROR_NOT_FOUND);
		scoredat_sti();
		return 1;
	}
	scoredat_read(buf.magic, sizeof(buf.magic));
	// Who cares about the last three bytes anyway, right.
	if(memcmp(buf.magic, SCOREDAT_MAGIC_1, 4)) {
		scoredat_close();
		scoredat_error(SCOREDAT_ERROR_INVALID);
		scoredat_sti();
		return 1;
	}

	scoredat_names = new int8_t[SCOREDAT_NAMES_SIZE];
	scoredat_stages = new int16_t[SCOREDAT_PLACES];
	scoredat_routes = new int8_t[SCOREDAT_ROUTE_LEN * SCOREDAT_PLACES];
	scoredat_points = new int32_t[SCOREDAT_PLACES];

	scoredat_read(scoredat_names, SCOREDAT_NAMES_SIZE);
	scoredat_read(scoredat_points, sizeof(int32_t) * SCOREDAT_PLACES);
	scoredat_read(scoredat_stages, sizeof(int16_t) * SCOREDAT_PLACES);
	scoredat_read(scoredat_routes, SCOREDAT_ROUTE_LEN * SCOREDAT_PLACES);
	scoredat_close();

	for(int i = 0; i < SCOREDAT_NAMES_SIZE; i++) {
		scoredat_names[i] = scoredat_name_byte_decode(scoredat_names[i]);
	}
	scoredat_sti();
	return 0;
}
