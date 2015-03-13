/* ReC98
 * -----
 * Code segment #14 of TH01's REIIDEN.EXE
 */

#include <master.h>

// Slightly different parameter lists compared to later games!
void vector_between(int x1, int y1, int x2, int y2, int *dx, int *dy, int r)
{
	unsigned char angle = iatan2(y2 - y1, x2 - x1);
	*dx = ((long)r * CosTable8[angle]) >> 8;
	*dy = ((long)r * SinTable8[angle]) >> 8;
}

void vector(int *dx, int *dy, int r, unsigned char angle)
{
	*dx = ((long)r * CosTable8[angle]) >> 8;
	*dy = ((long)r * SinTable8[angle]) >> 8;
}
