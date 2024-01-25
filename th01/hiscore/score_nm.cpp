void scoredat_name_get(int place, unsigned char str[SCOREDAT_NAME_BYTES + 1])
{
	for(int i = 0; i < SCOREDAT_NAME_BYTES; i++) {
		str[i] = scoredat_names[(place * SCOREDAT_NAME_BYTES) + i];
	}
	str[SCOREDAT_NAME_BYTES] = '\0';
}
