extern volatile int z_vsync_Count1;
extern volatile int z_vsync_Count2;

void vsync_init(void);
void z_vsync_wait(void);
void vsync_exit(void);
