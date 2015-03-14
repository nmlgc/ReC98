int pi_slot_load(int slot, const char *fn)
{
	int ret = graph_pi_load_pack(
		fn, &pi_slot_headers[slot], &pi_slot_buffers[slot]
	);
	return ret;
}
