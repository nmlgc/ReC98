// VRAM page flipping
// ------------------

#define page_show(page)  	_outportb_(0xA4, page)
#define page_access(page)	_outportb_(0xA6, page)
