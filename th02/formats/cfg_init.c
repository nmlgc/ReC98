void cfg_init(resident_t __seg *resident_seg)
{
	const char *fn = CFG_FN;
	cfg_options_t opts = OPTS_DEFAULT;
	int handle = dos_axdx(0x3D02, fn);
	if(handle > 0) {
		dos_seek(handle, sizeof(opts), SEEK_SET);
	} else {
		handle = dos_create(fn, _A_ARCH);
		dos_write(handle, &opts, sizeof(opts));
	}
	dos_write(handle, &resident_seg, sizeof(resident_seg));
	dos_write(handle, &debug, sizeof(debug));
	dos_close(handle);
}
