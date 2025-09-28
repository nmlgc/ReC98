// Multiple entry points
// ---------------------

enum entrypoint_t {
	EP_OP,
#if (GAME == 1)
	EP_MAIN,
#endif
	EP_CUTSCENE,
	EP_COUNT,
};

// Consistent names to allow this code to be reused for later games as well.
int main_setup(int argc, const char *argv[]);
int main_op(int argc, const char *argv[]);
#if (GAME == 1)
int main_main(int argc, const char *argv[]);
#endif
int main_cutscene(int argc, const char *argv[]);

// Called before the process quits to DOS, but not when switching entry points.
// Should remove any TSRs that were spawned in main_setup(). This function may
// be called from a different process than the one that ran main_setup(), so it
// won't have access to the same globals. Any shutdown-relevant state must
// therefore be kept in the resident structure.
void main_shutdown(void);

// Restarts the binary at the given entry point.
void entrypoint_exec(entrypoint_t entrypoint);
