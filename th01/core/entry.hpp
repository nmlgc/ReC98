// Multiple entry points
// ---------------------

enum entrypoint_t {
	EP_OP,
	EP_MAIN,
	EP_CUTSCENE,
	EP_COUNT,
};

int __cdecl main(int argc, const char *argv[]);

// Consistent names to allow this code to be reused for later games as well.
int main_op(int argc, const char *argv[]);
int main_main(int argc, const char *argv[]);
int main_cutscene(int argc, const char *argv[]);

// Restarts the binary at the given entry point.
void entrypoint_exec(entrypoint_t entrypoint);
