extern unsigned char pointnum_operator;
extern unsigned char pointnum_operand;

// Blits the given point[num] sprite to the given position. Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
void pascal near pointnum_put(int left, int top, unsigned int num);
