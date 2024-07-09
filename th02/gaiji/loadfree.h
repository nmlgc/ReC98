// Backs up the contents of the PC-98 gaiji RAM, then replaces its contents
// with the TH02-specific gaiji.
void near gaiji_load(void);

// Restores the backup made by gaiji_load().
void near gaiji_free(void);
