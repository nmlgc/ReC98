void input_reset_sense(void)
{
	input_lr = false;
	input_up = false;
	input_down = false;
	input_ok = false;
	paused = false;
	input_shot = false;
	input_strike = false;
	input_mem_enter = false;
	input_mem_leave = false;

	input_sense(true);
}
