#include "th03/formats/enedat.hpp"
#include <malloc.h>
#include <mem.h>
#include <process.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Slice iteration
// ---------------

class FileSlice {
	uint8_t *start;
	uint8_t *p;
	size_t rem;

	bool check(size_t bytes_expected) const;
	void skip(size_t bytes_to_skip) {
		rem -= bytes_to_skip;
		p += bytes_to_skip;
	}

public:
	const size_t size;
	const char *fn;

	size_t tell(void) const {
		return (size - rem);
	}

	size_t remaining(void) const {
		return rem;
	}

	bool peek(void *out, size_t bytes_to_read);
	bool read(void *out, size_t bytes_to_read);

	FileSlice subslice(size_t bytes) {
		if(check(bytes)) {
			FileSlice ret(fn, nullptr, 0);
			return ret;
		}
		FileSlice ret(fn, start, (tell() + bytes));
		ret.skip(tell());
		skip(bytes);
		return ret;
	}

	FileSlice(const char *fn, uint8_t *buf, size_t size) :
		start(buf), p(buf), rem(size), size(size), fn(fn) {
	}
};

bool FileSlice::check(size_t bytes_expected) const
{
	if(rem < bytes_expected) {
		fprintf(
			stderr,
			"%s: Error reading %u bytes at position %u (buffer is only %u bytes large)",
			fn,
			bytes_expected,
			tell(),
			size
		);
		return true;
	}
	return false;
}

bool FileSlice::peek(void *out, size_t bytes_to_read)
{
	if(check(bytes_to_read)) {
		return true;
	}
	memcpy(out, p, bytes_to_read);
	return false;
}

bool FileSlice::read(void *out, size_t bytes_to_read)
{
	if(peek(out, bytes_to_read)) {
		return true;
	}
	skip(bytes_to_read);
	return false;
}
// ---------------

enum dump_value_type_t {
	T_BOOL,
	T_U8,
	T_ANGLE,
	T_ANGLE_SPEED,
	T_SUBPIXEL,
	T_POINT,
	T_SUBPIXEL_POINT,
	T_U8_ARRAY,
};

uint8_t enedat_dump_param_len(va_list& ap, dump_value_type_t type)
{
	switch(type) {
	case T_BOOL:
		va_arg(ap, bool);
		return 5;
	case T_U8:
		va_arg(ap, uint8_t);
		return 3;
	case T_ANGLE:
		va_arg(ap, unsigned char);
		return 5;
	case T_ANGLE_SPEED:
		va_arg(ap, int8_t);
		return 2;
	case T_SUBPIXEL:
		va_arg(ap, Subpixel);
		return (2 + 4);
	case T_POINT:
	case T_SUBPIXEL_POINT:
		va_arg(ap, Subpixel);
		va_arg(ap, Subpixel);
		return (2 * (2 + 4));
	case T_U8_ARRAY: {
		const size_t count = va_arg(ap, size_t);
		va_arg(ap, const uint8_t *);
		return (1 + ((3 + 1) * count) + 1);
	}
	}
	return 0;
}

void enedat_dump_op(const char *name, ...)
{
	static const char SUBPIXEL_FRACT[SUBPIXEL_FACTOR][5] = {
		"0",
		"0625",
		"125",
		"1875",
		"25",
		"3125",
		"375",
		"4375",
		"5",
		"5625",
		"625",
		"6875",
		"75",
		"8125",
		"875",
		"9375",
	};

	size_t len = (strlen(name) + 2);
	unsigned int param_count = 0;
	{
		va_list ap;
		va_start(ap, name);
		while(1) {
			const char *name = va_arg(ap, const char *);
			if(!name) {
				break;
			}
			len += (strlen(name) + 3);
			len += enedat_dump_param_len(ap, va_arg(ap, dump_value_type_t));
			param_count++;
		}
	}
	const bool wrap = (len >= 72);
	printf("\t\t%s(", name);

	va_list ap;
	va_start(ap, name);
	for(unsigned int i = 0; i < param_count; i++) {
		const char *name = va_arg(ap, const char *);
		if(i != 0) {
			printf(",");
		}
		if(wrap) {
			printf("\n\t\t\t");
		} else if(i != 0) {
			printf(" ");
		}
		printf("%s: ", name);

		switch(va_arg(ap, dump_value_type_t)) {
		case T_BOOL:
			printf("%s", (va_arg(ap, bool) ? "true" : "false"));
			break;

		case T_U8:
			printf("%u", va_arg(ap, uint8_t));
			break;

		case T_ANGLE: {
			unsigned char angle = va_arg(ap, unsigned char);
			char sign = ((angle >= 0x80) ? '-' : '+');
			uint8_t value = ((angle >= 0x80) ? (0x100 - angle) : angle);
			printf("%c0x%02X", sign, value);
			break;
		}

		case T_ANGLE_SPEED:
			printf("%+d", va_arg(ap, int8_t));
			break;

		case T_SUBPIXEL: {
			const Subpixel v = va_arg(ap, Subpixel);
			printf("%d.%s", v.to_pixel(), SUBPIXEL_FRACT[v % SUBPIXEL_FACTOR]);
			break;
		}

		case T_POINT: {
			const pixel_t x = va_arg(ap, Subpixel);
			const pixel_t y = va_arg(ap, Subpixel);
			printf("(x: %d, y: %d)", x, y);
			break;
		}

		case T_SUBPIXEL_POINT: {
			const Subpixel x = va_arg(ap, Subpixel);
			const Subpixel y = va_arg(ap, Subpixel);
			printf(
				"(x: %d.%s, y: %d.%s)",
				x.to_pixel(),
				SUBPIXEL_FRACT[x % SUBPIXEL_FACTOR],
				y.to_pixel(),
				SUBPIXEL_FRACT[y % SUBPIXEL_FACTOR]
			);
			break;
		}

		case T_U8_ARRAY: {
			const size_t count = va_arg(ap, size_t);
			const uint8_t *arr = va_arg(ap, uint8_t *);
			printf("[");
			for(size_t i = 0; i < count; i++) {
				if(i != 0) {
					printf(", ");
				}
				printf("%u", arr[i]);
			}
			printf("]");
			break;
		}
		}
	}
	printf("%s);\n", (wrap ? "\n\t\t" : ""));
}

bool enedat_dump_op_with_no_parameters(FileSlice& buf, const char *name)
{
	enedat_op_t p;
	if(buf.read(&p, sizeof(p))) {
		return true;
	}
	enedat_dump_op(name, nullptr, 0);
	return false;
}

bool enedat_dump_op_duration(FileSlice& buf, const char *name)
{
	enedat_op_duration_t p;
	if(buf.read(&p, sizeof(p))) {
		return true;
	}
	enedat_dump_op(name, "duration", T_U8, p.duration, nullptr);
	return false;
}

int enedat_dump_script(FileSlice& buf)
{
	while(buf.remaining() > 0) {
		enedat_op_code_t code;
		if(buf.peek(&code, sizeof(code))) {
			return 13;
		}
		switch(code) {
		case EO_STOP:
			if(enedat_dump_op_with_no_parameters(buf, "stop")) {
				return true;
			}
			break;

		case EO_MOVE_LINEAR:
		case EO_MOVE_LINEAR_STOP_AT_PLAYER_Y:
		case EO_MOVE_LINEAR_STOP_AT_PLAYER_X: {
			enedat_op_linear_t p;
			if(buf.read(&p, sizeof(p))) {
				return (14 + code);
			}
			const char *name;
			if(code == EO_MOVE_LINEAR_STOP_AT_PLAYER_X) {
				name = "move_linear_stop_at_player_x";
			} else if(code == EO_MOVE_LINEAR_STOP_AT_PLAYER_Y) {
				name = "move_linear_stop_at_player_y";
			} else {
				name = "move_linear";
			}
			enedat_dump_op(
				name,
				"angle", T_ANGLE, p.angle,
				"speed", T_SUBPIXEL, p.speed.v,
				"duration", T_U8, p.duration,
				nullptr
			);
			break;
		}

		case EO_MOVE_CIRCULAR: {
			enedat_op_circular_t p;
			if(buf.read(&p, sizeof(p))) {
				return (14 + code);
			}
			enedat_dump_op(
				"move_circular",
				"angle_start", T_ANGLE, p.angle_start,
				"speed", T_SUBPIXEL, p.speed.v,
				"angle_speed", T_ANGLE_SPEED, p.angle_speed,
				"duration", T_U8, p.duration,
				nullptr
			);
			break;
		}

		case EO_WAIT: {
			if(enedat_dump_op_duration(buf, "wait")) {
				return (14 + code);
			}
			break;
		}

		case EO_MOVE_SINE_X:
		case EO_MOVE_SINE_Y: {
			enedat_op_sine_t p;
			struct sine_op_t {
				const char *op;
				const char *speed;
				const char *velocity;
			};
			static const sine_op_t OP_LABELS[2] = {
				{ "move_sine_x", "speed_x", "velocity_y" },
				{ "move_sine_y", "speed_y", "velocity_x" },
			};
			if(buf.read(&p, sizeof(p))) {
				return (14 + code);
			}
			const sine_op_t& labels = OP_LABELS[code == EO_MOVE_SINE_Y];
			enedat_dump_op(
				labels.op,
				labels.speed, T_SUBPIXEL, p.speed_on_sine_axis.v,
				"angle_speed", T_ANGLE_SPEED, p.angle_speed,
				labels.velocity, T_SUBPIXEL, p.velocity_on_linear_axis.v,
				"duration", T_U8, p.duration,
				nullptr
			);
			break;
		}

		case EO_MOVE: {
			if(enedat_dump_op_duration(buf, "move")) {
				return (14 + code);
			}
			break;
		}

		case EO_MOVE_WITH_SPEED: {
			enedat_op_speed_t p;
			if(buf.read(&p, sizeof(p))) {
				return (14 + code);
			}
			enedat_dump_op(
				"move_with_speed",
				"speed", T_SUBPIXEL, p.speed.v,
				"duration", T_U8, p.duration,
				nullptr
			);
			break;
		}

		case EO_MOVE_CIRCULAR_PLUS: {
			enedat_op_circular_plus_t p;
			if(buf.read(&p, sizeof(p))) {
				return (14 + code);
			}
			enedat_dump_op(
				"move_circular_plus",
				"angle_start", T_ANGLE, p.angle_start,
				"speed", T_SUBPIXEL, p.speed.v,
				"angle_speed", T_ANGLE_SPEED, p.angle_speed,
				"velocity_plus",
					T_SUBPIXEL_POINT,
					p.velocity_x_plus.v,
					p.velocity_y_plus.v,
				"duration", T_U8, p.duration,
				nullptr
			);
			break;
		}

		case EO_SPAWN: {
			enum {
				SIZE_ARRAY_COUNT = (
					sizeof(((enedat_op_spawn_t *)(nullptr))->size_words) /
					sizeof(((enedat_op_spawn_t *)(nullptr))->size_words[0])
				),
				HP_ARRAY_COUNT = (
					sizeof(((enedat_op_spawn_t *)(nullptr))->hp) /
					sizeof(((enedat_op_spawn_t *)(nullptr))->hp[0])
				)
			};
			enedat_op_spawn_t p;
			if(buf.read(&p, sizeof(p))) {
				return (14 + code);
			}
			const pixel_t center_x = (p.center_x_divided_by_8 * 8);
			const pixel_t center_y = (p.center_y_divided_by_8 * 8);
			{for(int i = 0; i < SIZE_ARRAY_COUNT; i++) {
				p.size_words[i] *= 16;
			}}
			enedat_dump_op(
				"spawn",
				"center", T_POINT, center_x, center_y,
				"size", T_U8_ARRAY, SIZE_ARRAY_COUNT, p.size_words,
				"hp", T_U8_ARRAY, HP_ARRAY_COUNT, p.hp,
				"clip_x", T_BOOL, p.clip_x,
				"clip_bottom", T_BOOL, p.clip_bottom,
				"unused", T_U8, p.unused,
				nullptr
			);
			break;
		}

		case EO_CLIP_X:
			if(enedat_dump_op_with_no_parameters(buf, "clip_x")) {
				return (14 + code);
			}
			break;

		default:
			fprintf(
				stderr,
				"%s: Unknown opcode %u at position %u",
				buf.fn,
				code,
				buf.tell()
			);
			return (14 + code);
		}
	}
	return 0;
}

int enedat_dump(FileSlice& buf)
{
	enedat_header_t header;
	if(buf.read(&header, sizeof(header))) {
		return 9;
	}
	if(buf.remaining() > header.size) {
		fprintf(
			stderr,
			"%s: Size from header (%u bytes) larger than remaining file size (%u bytes)",
			buf.fn,
			header.size,
			buf.remaining()
		);
		return 10;
	}

	unsigned int formation_i = 0;
	while(buf.remaining() > 0) {
		uint16_t enemy_count;
		if(buf.read(&enemy_count, sizeof(enemy_count))) {
			return 11;
		}
		if(enemy_count == 0) {
			break;
		}
		if(formation_i != 0) {
			printf("\n");
		}
		printf("Formation %u\n", formation_i);
		for(uint16_t enemy_i = 0; enemy_i < enemy_count; enemy_i++) {
			uint8_t script_size;
			if(buf.read(&script_size, sizeof(script_size))) {
				return 12;
			}

			printf("\tEnemy %u\n", enemy_i);
			int script_ret = enedat_dump_script(buf.subslice(script_size));
			if(script_ret) {
				return script_ret;
			}
		}
		formation_i++;
	}
	return 0;
}

int file_size_error(const char *fn, int ret)
{
	fprintf(stderr, "%s: Error determining file size", fn);
	perror("");
	return ret;
}

int enedat_dump(const char *fn, FILE *fp)
{
	long origin = ftell(fp);
	if(origin == -1) {
		return file_size_error(fn, 3);
	}
	if(fseek(fp, 0, SEEK_END)) {
		return file_size_error(fn, 4);
	}
	long size = ftell(fp);
	if(size == -1) {
		return file_size_error(fn, 5);
	}
	if(fseek(fp, origin, SEEK_SET)) {
		return file_size_error(fn, 6);
	}

	uint8_t *buf = static_cast<uint8_t *>(malloc(size));
	if(!buf) {
		fprintf(stderr, "%s: Error allocating %d bytes", fn, size);
		return 7;
	}

	size_t ret = fread(buf, 1, size, fp);
	if(ret != size) {
		fprintf(
			stderr,
			"%s: Error reading %ld bytes? (only read %u bytes)",
			fn,
			size,
			ret
		);
		return 8;
	}

	FileSlice buffer(fn, buf, size);
	ret = enedat_dump(buffer);
	free(buf);
	return ret;
}

int enedat_dump(const char *fn)
{
	FILE *fp = fopen(fn, "rb");
	if(!fp) {
		fprintf(stderr, "%s: ", fn);
		perror("");
		return 2;
	}
	int ret = enedat_dump(fn, fp);
	fclose(fp);
	return ret;
}

int __cdecl main(int argc, const char **argv)
{
	if(argc != 2) {
		fprintf(stderr, "Usage: %s ENEDAT.DAT\n", argv[0]);
		return 1;
	}
	return enedat_dump(argv[1]);
}
