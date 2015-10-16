CHAR_MAX equ 127

		public __localeconvention
__localeconvention dd cconv_10050
		dd cconv_10052
		dd cconv_10053
		dd cconv_10054
		dd cconv_10055
		dd cconv_10056
		dd cconv_10057
		dd cconv_10058
		dd cconv_10059
		dd cconv_1005A
		db CHAR_MAX
		db CHAR_MAX
		db CHAR_MAX
		db CHAR_MAX
		db CHAR_MAX
		db CHAR_MAX
		db CHAR_MAX
		db CHAR_MAX
cconv_10050	db  2Eh
		db    0
cconv_10052	db    0
cconv_10053	db    0
cconv_10054	db    0
cconv_10055	db    0
cconv_10056	db    0
cconv_10057	db    0
cconv_10058	db    0
cconv_10059	db    0
cconv_1005A	db    0
		db    0	; word alignment
