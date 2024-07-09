void pascal map_load(const char* fn)
{
	char magic[MAP_MAGIC_SIZE];

	file_ropen(fn);
	file_read(magic, sizeof(magic));
	file_read(map_section_tiles, sizeof(map_section_tiles));
	file_close();
}
