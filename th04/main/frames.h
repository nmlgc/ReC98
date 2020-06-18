extern unsigned long frames_unused;

// Stage-relative frame counter. Reset to 0 when moving to a new stage.
extern unsigned int stage_frame;
extern unsigned char stage_frame_mod2;
extern unsigned char stage_frame_mod4;
extern unsigned char stage_frame_mod8;
extern unsigned char stage_frame_mod16;

// Total number of frames, across all stages, whose rendering took longer than
// the vsync time of a single frame. (Pausing the game will also increment
// this value!)
extern unsigned long total_slow_frames;
// Total number of frames rendered, across all stages (= including bosses)
extern unsigned long total_frames;
// Total number of .STD VM frames rendered, across all stages (= excluding
// bosses)
extern unsigned int total_std_frames;
