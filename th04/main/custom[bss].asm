custom_t struc
	db 26 dup (?)
custom_t ends

public _custom_entities
_custom_entities	custom_t CUSTOM_COUNT dup (<?>)
	custom_t <?> ; 1 additional unused one, for some reason?
