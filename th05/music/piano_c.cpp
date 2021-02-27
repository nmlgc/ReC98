/// Helper functions
/// ----------------

// Additionally takes:
// • `void far *vram_at_x0_and_top_of_part<es:di>`
// • `int fm_part_id` in SI
// • `void __seg *original_data_ds` in FS
// Draws a piano with the currently pressed note retrieved from [qq]. In
// addition to SI, the part is also indicated through the VRAM offset in
// ES:DI.
void __fastcall near piano_fm_part_put_raw(
	int16_t ax_unused, int16_t dx_unused, QQ near *near *qq
);

// Returns the currently played note from [qq] as a KAJA onkai value, or
// ONKAI_REST if none is played.
char __fastcall near piano_current_note_from(
	int16_t ax_unused, int16_t dx_unused, QQ near *near *qq
 );

// Additionally takes:
// • `void far *vram_at_x0_and_top_of_part<es:di>`
// Draws a blank piano, for the part is indicated through the VRAM offset in
// ES:DI.
void near piano_part_keys_put_raw();

// Additionally takes:
// • `void far *vram_at_x0_and_top_of_part<es:di>`
// Draws the key given in [onkai] as pressed. The part is indicated through
// the VRAM offset in ES:DI.
void __fastcall near piano_pressed_key_put(char onkai);

// Additionally takes:
// • `void far *vram_at_x0_and_top_of_part<es:di>`
// Blits a piano label character to the top-left VRAM position indicated in
// ES:DI. Assumes that the GRCG is active.
void __fastcall near piano_label_put_raw(piano_label_t label_char);
/// ----------------
