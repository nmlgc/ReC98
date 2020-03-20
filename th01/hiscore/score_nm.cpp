void scoredat_name_get(int place, char str[SCOREDAT_NAME_BYTES + 1])
{
	for(int i = 0; i < SCOREDAT_NAME_BYTES; i++) {
		str[i] = scoredat_name_byte((place * SCOREDAT_NAME_BYTES) + i);
	}
	str[SCOREDAT_NAME_BYTES] = '\0';
}
