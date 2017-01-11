int pi_load(int slot, const char *fn)
{
	int ret = graph_pi_load_pack(fn, &pi_headers[slot], &pi_buffers[slot]);
	return ret;
}
