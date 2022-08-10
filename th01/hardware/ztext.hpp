// master.lib text function reimplementations
// ------------------------------------------

typedef enum {
	CURSOR_HIDE,
	CURSOR_BLOCK,
	CURSOR_UNDERLINE,

	_z_text_cursor_t_FORCE_UINT16 = 0xFFFF
} z_text_cursor_t;

// Attribute bits for z_text_vputsa(), completely differing from the PC-98
// hardware text attribute bits. Probably because they match the default
// [z_Palettes] colors?
#define Z_ATRB_BLUE     	0x1
#define Z_ATRB_GREEN    	0x2
#define Z_ATRB_RED      	0x4
#define Z_ATRB_CYAN     	(Z_ATRB_BLUE | Z_ATRB_GREEN)
#define Z_ATRB_MAGENTA  	(Z_ATRB_BLUE | Z_ATRB_RED)
#define Z_ATRB_YELLOW   	(Z_ATRB_GREEN | Z_ATRB_RED)
#define Z_ATRB_WHITE    	(Z_ATRB_BLUE | Z_ATRB_GREEN | Z_ATRB_RED)
#define Z_ATRB_BLINK    	0x100
#define Z_ATRB_REVERSE  	0x200
#define Z_ATRB_UNDERLINE	0x400
#define Z_ATRB_VLINE    	0x800

void z_text_init(void);
void z_text_25line(void);
void z_text_20line(void);
void z_text_systemline_show(void);
void z_text_systemline_hide(void);
void z_text_clear(void);
void z_text_show(void);
void z_text_hide(void);
void z_text_setcursor(z_text_cursor_t type);
void z_text_print(const char *cmd);
void z_text_vputsa(
	tram_x_t x, tram_y_t y, int z_atrb, const sshiftjis_t *fmt, ...
);
// ------------------------------------------
