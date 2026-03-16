#include "th03/common.h"

#define GAUGE_MAX (0xFF << 4)

typedef uint16_t gauge_t;
typedef uint8_t gauge_perbyte_t;

void pascal near gauge_avail_add(pid_t pid, uint8_t charge);
