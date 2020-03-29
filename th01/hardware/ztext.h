// master.lib text function reimplementations
// ------------------------------------------
typedef enum {
	CURSOR_HIDE,
	CURSOR_BLOCK,
	CURSOR_UNDERLINE,

	_z_text_cursor_t_FORCE_INT = 0xFFFF
} z_text_cursor_t;

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
// ------------------------------------------
