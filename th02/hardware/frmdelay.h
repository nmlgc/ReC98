// Blocks until [frames] number of VSync interrupts have occurred, and returns
// at the beginning of the following vertical blanking interval.
void pascal frame_delay(int frames);
void pascal frame_delay_2(int frames);
