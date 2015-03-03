void pascal frame_delay(int frames)
{
	vsync_reset1();
	while(vsync_Count1 < frames) {}
}
