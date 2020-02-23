void near pascal cfg_load(void);

// Saves the .CFG file, without changing its resident segment pointer.
void near pascal cfg_save(void);

// Like cfg_save(), but resets the resident segment pointer to zero.
void near pascal cfg_save_exit(void);
