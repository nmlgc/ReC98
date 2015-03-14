void game_exit_to_dos(void)
{
	game_exit();
	key_beep_on();
	text_systemline_on();
	text_cursor_on();
}
