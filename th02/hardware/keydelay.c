int key_delay_sense(void)
{
	extern char key_delay_groups[3];
	int ret;
	ret  = key_sense(key_delay_groups[0]);
	ret |= key_sense(key_delay_groups[1]);
	ret |= key_sense(key_delay_groups[2]);
	frame_delay(2);
	ret |= key_sense(key_delay_groups[0]);
	ret |= key_sense(key_delay_groups[1]);
	ret |= key_sense(key_delay_groups[2]);
	return ret;
}

void key_delay(void)
{
	while(key_delay_sense()) {}
	while(!key_delay_sense()) {}
}
