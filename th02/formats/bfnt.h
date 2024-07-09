// Supposedly a limitation of master.lib's BFNT functions according to
// MASTER.MAN, but not actually an issue with any of the functions used by the
// games, which do in fact support arbitrarily large sprite widths.
// Nevertheless, this is why ZUN split all logical sprites wider than 64 pixels
// into multiple physical ones.
#define BFNT_ASSUMED_MAX_W 64
#define bfnt_parts_x(w) ( \
	(w > BFNT_ASSUMED_MAX_W) ? (w / BFNT_ASSUMED_MAX_W) : w \
)
