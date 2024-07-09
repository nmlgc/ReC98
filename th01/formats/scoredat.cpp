#include <stdio.h>
#include <string.h>
#include "shiftjis.hpp"
#include "libs/master.lib/master.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/formats/scoredat.hpp"
#include "th01/shiftjis/fns.hpp"
#include "th01/shiftjis/scoredat.hpp"

// State
// -----

int8_t* scoredat_names; // Yeah, technically a scoredat_name_t.
shiftjis_kanji_t* scoredat_routes;
int16_t* scoredat_stages;
score_t* scoredat_score;
// -----

#define scoredat_fn(buf) { \
	switch(rank) { \
	case RANK_EASY:   	strcpy(fn, SCOREDAT_FN_EASY);   	break; \
	case RANK_NORMAL: 	strcpy(fn, SCOREDAT_FN_NORMAL); 	break; \
	case RANK_HARD:   	strcpy(fn, SCOREDAT_FN_HARD);   	break; \
	case RANK_LUNATIC:	strcpy(fn, SCOREDAT_FN_LUNATIC);	break; \
	} \
}

int8_t scoredat_name_byte_encode(int8_t byte)
{
	return (byte + SCOREDAT_NAME_KEY);
}

int8_t scoredat_name_byte_decode(int8_t byte)
{
	return (byte + (0x100 - SCOREDAT_NAME_KEY));
}

score_t scoredat_hiscore_get()
{
	return scoredat_score[0];
}

void scoredat_recreate()
{
	int i;
	int16_t stage;
	const shiftjis_kanji_t route = SCOREDAT_ROUTE_NONE;
	score_t score;

	// Will be name-encoded, and therefore modified in the .data section!
	char *name = scoredat_name_default;

	const char *magic = SCOREDAT_MAGIC;
	char fn[16];

	scoredat_fn(fn);

	if(file_create(fn) == 0) {
		return;
	}
	file_write(magic, sizeof(SCOREDAT_MAGIC) - 1);

	stage = SCOREDAT_PLACES;
	score = (SCOREDAT_PLACES * 100);
	for(i = 0; i < SCOREDAT_NAME_BYTES; i++) {
		name[i] = scoredat_name_byte_encode(name[i]);
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		file_write(name, SCOREDAT_NAME_BYTES);
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		file_write(&score, sizeof(score));
		score = score - 100;
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		file_write(&stage, sizeof(stage));
		stage = stage - 1;
	}
	for(i = 0; i < SCOREDAT_PLACES; i++) {
		file_write(&route, sizeof(shiftjis_kanji_t));
	}
	file_close();
}

int scoredat_load()
{
	union {
		char magic[sizeof(SCOREDAT_MAGIC) - 1];
		char space[50];
	} buf;
	char fn[16];

	scoredat_fn(fn);
	if(!file_exist(fn)) {
		scoredat_recreate();
	}

	if(file_ropen(fn) == 0) {
		puts(SCOREDAT_ERROR_NOT_FOUND);
		return 1;
	}
	file_read(buf.magic, sizeof(buf.magic));
	// Who cares about the last three bytes anyway, right.
	if(memcmp(buf.magic, SCOREDAT_MAGIC, 4)) {
		file_close();
		puts(SCOREDAT_ERROR_INVALID);
		return 1;
	}

	scoredat_names = new int8_t[SCOREDAT_NAMES_SIZE];
	scoredat_stages = new int16_t[SCOREDAT_PLACES];
	scoredat_routes = new shiftjis_kanji_t[SCOREDAT_PLACES];
	scoredat_score = new score_t[SCOREDAT_PLACES];

	file_read(scoredat_names, SCOREDAT_NAMES_SIZE);
	file_read(scoredat_score, sizeof(score_t) * SCOREDAT_PLACES);
	file_read(scoredat_stages, sizeof(int16_t) * SCOREDAT_PLACES);
	file_read(scoredat_routes, (sizeof(shiftjis_kanji_t) * SCOREDAT_PLACES));
	file_close();

	for(int i = 0; i < SCOREDAT_NAMES_SIZE; i++) {
		scoredat_names[i] = scoredat_name_byte_decode(scoredat_names[i]);
	}
	return 0;
}

void scoredat_save(void)
{
	const char magic[sizeof(SCOREDAT_MAGIC)] = SCOREDAT_MAGIC; // ZUN bloat
	char fn[16];
	scoredat_fn(fn);

	if(!file_create(fn)) {
		return;
	}
	file_write(magic, sizeof(SCOREDAT_MAGIC) - 1);
	for(int i = 0; i < SCOREDAT_NAMES_SIZE; i++) {
		scoredat_names[i] = scoredat_name_byte_encode(scoredat_names[i]);
	}
	file_write(scoredat_names, SCOREDAT_NAMES_SIZE);
	file_write(scoredat_score, (sizeof(score_t) * SCOREDAT_PLACES));
	file_write(scoredat_stages, (sizeof(int16_t) * SCOREDAT_PLACES));
	file_write(scoredat_routes, (sizeof(shiftjis_kanji_t) * SCOREDAT_PLACES));
	file_close();
}

void scoredat_name_get(int place, unsigned char str[SCOREDAT_NAME_BYTES + 1])
{
	for(int i = 0; i < SCOREDAT_NAME_BYTES; i++) {
		str[i] = scoredat_names[(place * SCOREDAT_NAME_BYTES) + i];
	}
	str[SCOREDAT_NAME_BYTES] = '\0';
}

void scoredat_free(void)
{
	delete[] scoredat_names;
	delete[] scoredat_stages;
	delete[] scoredat_routes;
	delete[] scoredat_score;
}
