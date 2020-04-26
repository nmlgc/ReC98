// Redefined versions of master.lib's grcg_setmode() and grcg_setcolor().
void near grcg_setmode_rmw_seg1(void);
void near grcg_setmode_tdw(void);

// In contrast to master.lib's own grcg_setcolor(), these keep the current
// GRCG mode, and reenable interrupts before returning.
#define grcg_setcolor_direct_seg1(col) \
	_AH = col; \
	grcg_setcolor_direct_seg1_raw();
void near grcg_setcolor_direct_seg1_raw(void);

#define grcg_setcolor_direct_seg3(col) \
	_AH = col; \
	grcg_setcolor_direct_seg3_raw();
void near grcg_setcolor_direct_seg3_raw(void);
