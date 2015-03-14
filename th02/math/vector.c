// Slightly different parameter list compared to the TH01 version!
void pascal vector(int *dx, int *dy, unsigned char angle, int r)
{
	*dx = ((long)r * CosTable8[angle]) >> 8;
	*dy = ((long)r * SinTable8[angle]) >> 8;
}

void pascal vector_between(
	int x1, int y1, int x2, int y2, unsigned char base_angle, int *dx, int *dy, int r
)
{
	base_angle = iatan2(y2 - y1, x2 - x1) + base_angle;
	*dx = ((long)r * CosTable8[base_angle]) >> 8;
	*dy = ((long)r * SinTable8[base_angle]) >> 8;
}
