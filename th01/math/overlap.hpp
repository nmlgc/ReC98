// Generic overlap testing macros for collision detection.
#define overlap_xywh_xywh_lt_gt(x1, y1, w1, h1, x2, y2, w2, h2) ( \
	(((x1) - (x2)) < (w2)) && \
	(((x1) - (x2)) > -(w1)) && \
	(((y1) - (y2)) < (h2)) && \
	(((y1) - (y2)) > -(h1)) \
)

#define overlap_xywh_xywh_le_ge(x1, y1, w1, h1, x2, y2, w2, h2) ( \
	(((x1) - (x2)) <= (w2)) && \
	(((x1) - (x2)) >= -(w1)) && \
	(((y1) - (y2)) <= (h2)) && \
	(((y1) - (y2)) >= -(h1)) \
)

#define overlap_xy_ltrb_lt_gt(x1, y1, left2, top2, right2, bottom2) ( \
	((x1) > (left2)) && \
	((x1) < (right2)) && \
	((y1) > (top2)) && \
	((y1) < (bottom2)) \
)

#define overlap_xy_lrtb_le_ge(x1, y1, left2, top2, right2, bottom2) ( \
	((x1) >= (left2)) && \
	((x1) <= (right2)) && \
	((y1) >= (top2)) && \
	((y1) <= (bottom2)) \
)

#define overlap_xyxy_lrtb_le_ge(x1, y1, left2, top2, right2, bottom2) ( \
	((x1) >= (left2)) && \
	((y1) <= (bottom2)) && \
	((x1) <= (right2)) && \
	((y1) >= (top2)) \
)

#define overlap_xy_lrbt_le_ge(x1, y1, left2, top2, right2, bottom2) ( \
	((x1) >= (left2)) && \
	((x1) <= (right2)) && \
	((y1) <= (bottom2)) && \
	((y1) >= (top2)) \
)

#define overlap_xy_rltb_lt_ge(x1, y1, left2, top2, right2, bottom2) ( \
	((x1) < (right2)) && \
	((x1) >= (left2)) && \
	((y1) >= (top2)) && \
	((y1) < (bottom2)) \
)

#define overlap_xy_xywh_le_ge(x1, y1, x2, y2, w2, h2) \
	overlap_xy_lrtb_le_ge(x1, y1, x2, y2, (x2 + w2), (y2 + h2))

#define overlap_xy_xywh_le_ge_2(x1, y1, x2, y2, w2, h2) \
	overlap_xy_lrbt_le_ge(x1, y1, x2, y2, (x2 + w2), (y2 + h2))

// Ugly, and should not exist, but generates one fewer instruction when used
// with _AX and _DX register pseudovariables...
#define overlap_offcenter_1d_inplace_fast(delta, dist_edge1, dist_edge2) ( \
	(unsigned int)((delta) += dist_edge1, delta) <= (dist_edge1 + dist_edge2) \
)

#define overlap_offcenter_inplace_fast( \
	delta_x, delta_y, dist_to_left, dist_to_top, dist_to_right, dist_to_bottom \
) ( \
	overlap_offcenter_1d_inplace_fast(delta_x, dist_to_left, dist_to_right) && \
	overlap_offcenter_1d_inplace_fast(delta_y, dist_to_top, dist_to_bottom) \
)

#define overlap_1d_inplace_fast(delta, extent) ( \
	(unsigned int)((delta) += (extent / 2), delta) <= (extent) \
)

#define overlap_wh_inplace_fast(delta_x, delta_y, w, h) ( \
	overlap_1d_inplace_fast(delta_x, w) && overlap_1d_inplace_fast(delta_y, h) \
)

#define overlap_points_wh_fast(p1, p2, p1_w, p1_h) ( \
	((unsigned int)((p1.x - p2.x) + (p1_w / 2)) <= (p1_w)) && \
	((unsigned int)((p1.y - p2.y) + (p1_h / 2)) <= (p1_h)) \
)
