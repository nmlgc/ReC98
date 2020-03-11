extern int vsync_frame;

void vsync_init(void);
void z_vsync_wait(void);
void vsync_exit(void);

void frame_delay(unsigned int frames);
