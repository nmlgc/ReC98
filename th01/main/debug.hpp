extern bool mode_debug;
extern bool16 mode_test;

// Deals damage to every damageable object on screen if true.
extern bool16 test_damage;

// set_new_handler() that immediately exit()s the game with an error message.
void out_of_memory_exit(void);

/// Memory info screen
/// ------------------

extern uint32_t coreleft_prev;

// Hides the graphics layer and enters a memory usage screen with some debug
// options, in a blocking way. Set [input_mem_leave] to `true` to return to
// the game.
void debug_mem();

// Reactivates the graphics layer and clears the text layer.
void debug_show_game();
/// ------------------
