/// Score data file encryption and decryption algorithms

// Encrypts backwards.
#define scoredat_encode_byte_at(p, feedback, key1, key2) { \
	p[0] = (p[0] - (key1 + feedback)); \
	feedback = p[0]; \
	_AL = key2; \
	_asm { ror feedback, 3 } \
	feedback ^= _AL; \
}

// Decrypts forwards.
#define scoredat_decode_byte_at(p, tmp, key1, key2) { \
	tmp = p[1]; \
	_AL = key2; \
	_asm { ror tmp, 3 } \
	tmp ^= _AL; \
	p[0] = (key1 + tmp + p[0]); \
}
