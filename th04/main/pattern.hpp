// A danmaku pattern function with no fixed maximum time. Fires projectiles in
// repeating cycles until no longer called.
typedef void (near *near pattern_loop_func_t)(void);

// A danmaku pattern function that runs for a limited amount of time. Should
// return `true` when done.
typedef bool (near *near pattern_oneshot_func_t)(void);
