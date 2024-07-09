// Fixed-size memory block for entities of a custom type, specific to a stage
// or boss portion. To define such a custom type, declare your own structure,
// then reinterpret_cast [custom_entities] to that type.

#include "th04/main/playfld.hpp"

#if (GAME == 5)
	#define CUSTOM_COUNT 64

	struct custom_t {
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
	};
#else
	#define CUSTOM_COUNT 32

	struct custom_t {
		uint8_t flag;
		uint8_t angle;
		point_t center;
		int16_t val1;
		Subpixel origin_y;
		PlayfieldPoint velocity;
		uint16_t val2;
		int16_t distance;
		int16_t val3;
		int16_t hp;
		int16_t damage_this_frame;
		uint8_t val4;
		uint8_t angle_speed;
	};
#endif

extern custom_t custom_entities[CUSTOM_COUNT];

#define custom_assert_count(derived_type, derived_count) \
	static_assert( \
		(sizeof(derived_type) * derived_count) <= \
		(sizeof(custom_t) * CUSTOM_COUNT) \
	)
