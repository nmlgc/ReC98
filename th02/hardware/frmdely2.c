void pascal frame_delay_2(int frames)
{
	vsync_reset1();
	while(vsync_Count1 < frames) {}
}
