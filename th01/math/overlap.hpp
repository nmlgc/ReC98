// Generic overlap testing macros for collision detection.
#define overlap_lt_gt(x1, y1, w1, h1, x2, y2, w2, h2) ( \
	(((x1) - (x2)) < (w2)) && \
	(((x1) - (x2)) > -(w1)) && \
	(((y1) - (y2)) < (h2)) && \
	(((y1) - (y2)) > -(h1)) \
)

#define overlap_le_ge(x1, y1, w1, h1, x2, y2, w2, h2) ( \
	(((x1) - (x2)) <= (w2)) && \
	(((x1) - (x2)) >= -(w1)) && \
	(((y1) - (y2)) <= (h2)) && \
	(((y1) - (y2)) >= -(h1)) \
)

#define overlap_point_le_ge(x1, y1, left2, top2, right2, bottom2) ( \
	((x1) >= (left2)) && \
	((x1) <= (right2)) && \
	((y1) >= (top2)) && \
	((y1) <= (bottom2)) \
)

#define overlap_point_le_ge_wh(x1, y1, left2, top2, w2, h2) \
	overlap_point_le_ge(x1, y1, left2, top2, (left2 + w2), (top2 + h2))
