// TH02 stores its 48×48 faces for in-game dialogs as 3×3 sets of .MPN tiles in
// MIKO_K.PTN… yup.

#define FACE_TILES_X (FACE_W / TILE_W)
#define FACE_TILES_Y (FACE_H / TILE_H)

#define FACE_TILE_STRIDE 16

// The 20 faces are arranged by placing a 5×4 grid of 3×3 tiles on the left
// side of a 16×12 grid. This results in the inner (face_col, face_row) values
// for the outer .MPN tile IDs:
//
//    012 345 678 9AB CDE F
//   ┌───────────────────┐
// 0 │0  |1  |2  |3  |4  |
// 1 │ , | , | , | , | , |
// 2 │  0|  0|  0|  0|  0|
//   ├───────────────────┤
// 3 │0  |1  |2  |3  |4  |
// 4 │ , | , | , | , | , |
// 5 │  1|  1|  1|  1|  1|
//   ├───────────────────┤
// 6 │0  |1  |2  |3  |4  |
// 7 │ , | , | , | , | , |
// 8 │  2|  2|  2|  2|  2|
//   ├───────────────────┤
// 9 │0  |1  |2  |3  |4  |
// A │ , | , | , | , | , |
// B │  3|  3|  3|  3|  3|
//   └───────────────────┘
#define topleft_id_at(face_col, face_row) ( \
	(face_row * FACE_TILES_Y * FACE_TILE_STRIDE) + (face_col * FACE_TILES_X) \
)

// Only stores the top-left ID for every face; the remaining ones can be
// calculated from the tile layout.
typedef enum face_tile_topleft_t {
	FACE_REIMU_NEUTRAL = topleft_id_at(0, 0),
	FACE_REIMU_HUSHED = topleft_id_at(1, 0),
	FACE_REIMU_ANGRY = topleft_id_at(2, 0),
	FACE_REIMU_JOY = topleft_id_at(3, 0),
	FACE_REIMU_FROWN = topleft_id_at(4, 0),
	FACE_REIMU_FALL = topleft_id_at(0, 1),
	FACE_REIMU_CRY = topleft_id_at(1, 1),
	FACE_REIMU_QUESTION = topleft_id_at(2, 1),
	FACE_REIMU_SWEAT = topleft_id_at(3, 1),
	FACE_REIMU_FLIRTY = topleft_id_at(4, 1), // Best guess given its usage... :/
	FACE_GENJII = topleft_id_at(0, 2),
	FACE_RIKA = topleft_id_at(1, 2),
	FACE_MEIRA_NEUTRAL = topleft_id_at(2, 2),
	FACE_MIMA_SMILE = topleft_id_at(3, 2),
	FACE_MIMA_FROWN = topleft_id_at(4, 2),
	FACE_MARISA_SMILE = topleft_id_at(0, 3),
	FACE_MARISA_FROWN = topleft_id_at(1, 3),
	FACE_MEIRA_SWEAT = topleft_id_at(2, 3),
	FACE_EXRIKA_SMILE = topleft_id_at(3, 3),
	FACE_EXRIKA_FROWN = topleft_id_at(4, 3),

	// Fills the face area with hardware color 0 and doesn't blit any tile.
	FACE_COL_0 = 0xFF,
};

#undef topleft_id_at

inline int face_tile_id(
	int topleft, // ACTUAL TYPE: face_tile_topleft_t
	int inner_col,
	int inner_row
) {
	return (topleft + (inner_row * FACE_TILE_STRIDE) + inner_col);
}
