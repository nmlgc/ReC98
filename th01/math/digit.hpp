#define digit_count(num) ( \
	(num >= 10000) ? 5 : \
	(num >= 1000) ? 4 : \
	(num >= 100) ? 3 : \
	(num >= 10) ? 2 \
	: 1 \
)
