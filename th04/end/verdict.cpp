#include "pc98.h"

// If `true`, skill_apply_and_graph_percentage_put() will subtract the
// calculated fraction from [skill] rather than add it.
extern bool skill_subtract;

extern uint32_t skill;

// ZUN bloat: Turn into a parameter of graph_3_digit_put().
extern bool graph_3_digit_put_as_fixed_2_digit;

// Assumes that [num] is a 3-digit number and renders it right-aligned to the
// given VRAM position.
void pascal near graph_3_digit_put(
	screen_x_t left, screen_y_t top, uint16_t num
)
;

// Calculates ([share] / [total]), applies the result × 1,000,000 to [skill],
// and renders it as a right-aligned 3.2-digit percentage to the given VRAM
// position.
void pascal near skill_apply_and_graph_percentage_put(
	screen_x_t left, screen_y_t top, uint16_t total, uint16_t share
)
;

// Calculates ([num] / 1,000,000) and renders the result as a right-aligned
// 3.2-digit fraction to the given VRAM position.
void pascal near graph_fraction_of_million_put(
	screen_x_t left, screen_y_t top, uint32_t num
)
;
