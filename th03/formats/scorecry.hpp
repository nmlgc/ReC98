/// Score data file decryption algorithm

// Decrypts forwards.
#define scoredat_decode_byte_at(p, tmp, key1, key2) { \
	tmp = p[1]; \
	_AL = key2; \
	__asm {	ror tmp, 3 } \
	tmp ^= _AL; \
	p[0] = (key1 + tmp + p[0]); \
}
