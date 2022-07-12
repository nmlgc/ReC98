// Memory for up to 64 entities of a single extra custom type, specific to a
// stage or boss portion, with sizeof(custom_t) bytes per entity.
// To define such a custom type, declare your own structure, then
// reinterpret_cast [custom_entities] to that type.

#define CUSTOM_COUNT 64

typedef struct {
	uint8_t flag;
	uint8_t angle;
	PlayfieldMotion pos;
	uint16_t val1;
	uint16_t val2;
	int16_t sprite;
	int16_t val3;
	int16_t damage;
	SubpixelLength8 speed;
	int8_t padding;	// Unused across all custom entities in ZUN's code
} custom_t;

extern custom_t custom_entities[CUSTOM_COUNT];

#define custom_assert_count(derived_type, derived_count) \
	static_assert( \
		(sizeof(derived_type) * derived_count) <= \
		(sizeof(custom_t) * CUSTOM_COUNT) \
	)
