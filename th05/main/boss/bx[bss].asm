FIREWAVE_COUNT = 2

firewave_t struc
	FW_alive	db ?
	FW_is_right	db ?
	FW_bottom	dw ?
	FW_amp	dw ?
firewave_t ends

public _firewaves
_firewaves	firewave_t FIREWAVE_COUNT dup (<?>)
