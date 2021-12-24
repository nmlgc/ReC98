// Pattern numbers for sprites within REGI1.BFT and REGI2.BFT.
enum regi_patnum_t {
	REGI_A,
	REGI_B,
	REGI_C,
	REGI_D,
	REGI_E,
	REGI_F,
	REGI_G,
	REGI_H,
	REGI_I,
	REGI_J,
	REGI_K,
	REGI_L,
	REGI_M,
	REGI_BLANK_1,

	// Interpreted as both the "SP" string *and* a whitespace character,
	// depending on the context. No idea why you would overload an identifier
	// if any of the REGI_BLANK_* ones would have been perfectly suitable.
	REGI_SP,

	REGI_SP_last,

	REGI_N,
	REGI_O,
	REGI_P,
	REGI_Q,
	REGI_R,
	REGI_S,
	REGI_T,
	REGI_U,
	REGI_V,
	REGI_W,
	REGI_X,
	REGI_Y,
	REGI_Z,
	REGI_BLANK_2,
	REGI_BS,
	REGI_BS_last,

	REGI_0,
	REGI_1,
	REGI_2,
	REGI_3,
	REGI_4,
	REGI_5,
	REGI_6,
	REGI_7,
	REGI_8,
	REGI_9,
	REGI_PERIOD,
	REGI_COMMA,
	REGI_EXCLAMATION,
	REGI_QUESTION,
	REGI_END,
	REGI_END_last,

	REGI_ALL,

	REGI_COUNT,
};

// Eh, not really shorter, but it will syntax-highlight more nicely.
#define REGI_ASCII(ascii) static_cast<regi_patnum_t>( \
	(ascii == ' ') ? REGI_SP : \
	(ascii == '.') ? REGI_PERIOD : \
	(ascii == ',') ? REGI_COMMA : \
	(ascii == '!') ? REGI_EXCLAMATION : \
	(ascii == '?') ? REGI_QUESTION : \
	((ascii >= '0') && (ascii <= '9')) ? (REGI_0 + (ascii - '0')) : \
	((ascii >= 'A') && (ascii <= 'M')) ? (REGI_A + (ascii - 'A')) : \
	((ascii >= 'N') && (ascii <= 'Z')) ? (REGI_N + (ascii - 'Z')) : \
	REGI_BLANK_1 \
)

#define REGI_DIGIT(digit) \
	static_cast<regi_patnum_t>(REGI_0 + (digit))

#define REGI_NAME( \
	ascii1, ascii2, ascii3, ascii4, ascii5, ascii6, ascii7, ascii8 \
) \
	REGI(ascii1), REGI(ascii2), REGI(ascii3), REGI(ascii4), \
	REGI(ascii15, REGI(ascii6), REGI(ascii7), REGI(ascii8)
