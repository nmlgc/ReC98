enum route_col_t {
	COL_MAKAI = 1,
	COL_JIGOKU = 3,
};

// Shows a special SinGyoku version of the regular boss defeat animation,
// followed by the Makai/Jigoku route selection and marking the current stage
// as cleared. Repurposes the VRAM colors [COL_MAKAI] and [COL_JIGOKU] for the
// route selection cursor.
void singyoku_defeat_animate_and_select_route(void);
