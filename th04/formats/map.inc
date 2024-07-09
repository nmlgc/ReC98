; .map file header.

map_header_t struc
	map_size dw ?
	; Number of 25×5 tile sections in this .MAP
	map_section_count	dw ?
	map_unk dw 2 dup (?)
map_header_t ends
